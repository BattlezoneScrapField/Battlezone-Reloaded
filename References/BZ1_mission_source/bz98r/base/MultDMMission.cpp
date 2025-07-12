#include "logger.h"
#include "GameObjectHandle.h"
#include "MultDMMission.h"
#include "PathSpawn.h"
#include "Net.h"
#include "NetPlayers.h"
#include "SpawnPoint.h"
#include "ScriptUtils.h"
#include "UserProcess.h"
#include "AiUtil.h"
#include "score.h"
#include "gameNetInterface.h"
#include "LabelMap.h"
#include "strhelp.h"
#include "running.h"
#include "input.h"

extern int king_of_the_hill_game;
extern int stratgy_game;

/* leftovers...
static GameObject *MyBuildObject(char *odf, int team, const VECTOR_3D &p)
{
	GameObjectClass *objClass = GameObjectClass::Find(odf);
	if (objClass == NULL)
		return NULL;
	MAT_3D trans = Identity_Matrix;
	SetPositionV(&trans, (VECTOR_3D *)&p);
	GameObject *gameObj = objClass->Build(trans, team);
	if (gameObj == NULL)
		return NULL;
	if (Net::GetHosting())
		gameObj->SetLocal();
//	AiMission::GetCurrent()->AddObject(gameObj);
	return gameObj;
}

static BZHandle MyBuildObject(char *odf, int team, Name path)
{
	AiPath *p = AiPath::Find(path);
	if (p == NULL)
		return 0;
	VECTOR_2D &start = p->points[0];
	float ground;
	Terrain_GetHeightAndNormal(start.x, start.z, &ground, NULL);
	VECTOR_3D where = { start.x, ground, start.z };
	GameObject *resultObj = MyBuildObject(odf, team, where);
	if (resultObj == NULL)
		return 0;
	return GameObjectHandle::Find(resultObj);
}
*/

class MultDMEvent : public AiProcess {
	DECLARE_RTIME(MultDMEvent)
public:
	MultDMEvent(void);
	MultDMEvent(AiMission *mission);
	void Execute(void) override;
private:
	int doing_king_of_the_hill;
	struct Circle
	{
		float x;
		float z;
		float radius;
	};
	std::vector<Circle> circles;
	std::vector<const AiPath *> areas;
	int starttimer;
	uint32_t dwNextTimeLimit;
	float fTimeInZone;
	float fTimeInZoneLast;

	uint32_t dwLastTime;
};

IMPLEMENT_RTIME(MultDMEvent)

MultDMEvent::MultDMEvent(void)
{
	assert(false);
}

MultDMEvent::MultDMEvent(AiMission *mission): AiProcess(mission, NULL)
{
	starttimer = 1;
	fTimeInZone = 0.0f;
	fTimeInZoneLast = 0.0f;

	dwLastTime = 0;

	doing_king_of_the_hill = 0;

	king_of_the_hill_game = 0;
	stratgy_game = 0;
	AiPathList::iterator i;
	for (i = AiPath::pathList.begin(); i != AiPath::pathList.end(); i++)
	{
		AiPath &curPath = **i;
		if (curPath.label != NULL && strnicmp(curPath.label, "king", 4) == 0)
		{
			doing_king_of_the_hill = 1;
			king_of_the_hill_game = 1;
			if (isdigit(curPath.label[4]) || curPath.pointCount < 3)
			{
				for (int j = 0; j < curPath.pointCount; ++j)
				{
					Circle circle;
					circle.x = curPath.points[j].x;
					circle.z = curPath.points[j].z;
					circle.radius = (float)Max(1, atoi(&curPath.label[4]));
					circles.push_back(circle);
				}
			}
			else
			{
				areas.push_back(&curPath);
			}
		}
	}
}

void MultDMEvent::Execute(void)
{
		
	if (Net::bStopGame) return;
	uint32_t dwNow = Get_TimeNow();
	uint32_t dwNetNow = Get_Time_Long();

	if (Net::TimeLimit <= 0 && cockpitTimer.IsVisible())
	{
		dwNetNow = dwNetNow / 1000;
		if (dwLastTime > dwNetNow + 2)
			dwLastTime = dwNetNow - 1;
		if (dwNetNow > dwLastTime)
		{
			cockpitTimer.SetTimerUp(dwNetNow);
			dwLastTime = dwNetNow;
		}
	}

	if (doing_king_of_the_hill)
	{
		GameObject *g = GameObject::GetUser();
		if (g)
		{
			const VECTOR_3D &pos = g->GetPosition();

			int inside = 0;
			for (std::vector<Circle>::iterator c = circles.begin(); c != circles.end(); ++c)
			{
				VECTOR_3D k = {c->x, 0.0f, c->z};
				if (Dist2DSq(k, pos) <= c->radius * c->radius)
					++inside;
			}
			for (std::vector<const AiPath *>::iterator a = areas.begin(); a != areas.end(); ++a)
			{
				if (GetWindingNumber(*a, pos) != 0)
					++inside;
			}
			if (inside > 0)
			{
				// Only update the variable when the guy has been in there longer than
				// one second.
				fTimeInZone += TimeStepActual();
				if (fTimeInZone >= fTimeInZoneLast + 1.0f)
				{
					Increment_Player_TimeInZone(fTimeInZone - fTimeInZoneLast);
					fTimeInZoneLast = fTimeInZone;
				}
			}
		}
	}

	if (starttimer && GetCockpitTimer()) {
		// Don't reset the timer if HOST changes
		starttimer = 0;
	}
	if (Net::GetHosting())
	{
		if (Net::KillLimit > 0)
		{
			int kills = GetTotalKills();

			if (kills >= Net::KillLimit)
			{
				Net::bStopGame = true;
				do_escape();
				return;
			}
		}

		if (Net::TimeLimit > 0)
		{
			if (starttimer)
			{
				starttimer = 0;
				StartCockpitTimer(Net::TimeLimit * 60, 120, 60);
			}
			
			long t = GetCockpitTimer();



			if (t <= 0)
			{
				Net::bStopGame = true;
				do_escape();
				return;
			}

			// Update the time limit timer.
			if (dwNextTimeLimit > dwNow + 10000)
				dwNextTimeLimit = dwNow;
			if (dwNow > dwNextTimeLimit || t <= 0)
			{
				dwNextTimeLimit = dwNow + 10000;
				char buf[20];
				uint16_t *w = (uint16_t *)&(buf[0]);
				*w = TIMER_PACKET_ID;
				long *timer = (long *) (w + 1);
				*timer = t;
				NetPlayer::Broadcast(buf, sizeof(uint16_t) + sizeof(long), CGameNetP2P::P2PSendUnreliable);
			}

		}
	}
}

static class MultDMMissionClass : AiMissionClass {
public:
	MultDMMissionClass(const char *name) : AiMissionClass(name)
	{
	}
	int Matches(const char *matches)
	{
		if (strnicmp(matches, name, strlen(name)) == 0)
			return BZTRUE;
		if (strnicmp(matches, "mult01", strlen("mult01")) == 0)
			return BZTRUE;
		if (strnicmp(matches, "mult03", strlen("mult03")) == 0)
			return BZTRUE;
		return BZFALSE;
	}
	AiMission *Build(void)
	{
		return new MultDMMission;
	}
} MultDMMissionClass("multDM");

IMPLEMENT_RTIME(MultDMMission)

MultDMMission::MultDMMission(void)
{
	multEvent = NULL;
	pathSpawn = NULL;
	recently_killed = false;
	killed = 0;
	camera = false;
	SetAIControl(2, false);
}


void MultDMMission::Init(void)
{
	if (!theNet)
		return;

	multEvent = new MultDMEvent(this);
	pathSpawn = new PathSpawn(this);

	Net::SetDeathMatch(true);

	if (Net_IsNetGame())
	{
		assert(theNet);
		
		GameObjectClass *gameObjectClass;
		PrjID config = StringToPrjID(Net::odfName);
		gameObjectClass = GameObjectClass::Find(config);
		assert(gameObjectClass);
		
		if (Net::GetHosting())
		{
			// We are hosting so give yourself a spawn point.
			SpawnPoint *spawnPoint = SpawnPoint::GetRandom(Net::Team);
			if (!spawnPoint)
			{
				if (SpawnPoint::spawnPointList && !SpawnPoint::spawnPointList->empty())
				{
					DisplayMessage(GetTextLabel("multi_error", "no_spawn_avail"));
					GetLogger()->WriteLog("Could not get a spawn point\n");
				}
				else
				{
					DisplayMessage(GetTextLabel("multi_error", "no_spawn_points"));
					GetLogger()->WriteLog("Map has no spawn points\n");
				}
				Net::bStopGame = true;
				if (GetRunning() != RUN_WAS_QUIT) // We failed and reported already
					do_escape();
				return;
			}
			
			theNet->SetStartLocation(spawnPoint->GetLocation());
			NetPlayer *netPlayer = NetPlayer::Find(theNet->GetMyPlayerIDExt());
			assert(netPlayer);
			netPlayer->SetWaitingForSpawnPoint(false);

			// assign the spawn point
			netPlayer->SpawnPointer = spawnPoint;
			spawnPoint->Assign(netPlayer);
		}
		VECTOR_3D pos = theNet->GetStartLocation();
		MAT_3D mat = Identity_Matrix;
		mat.posit_x = pos.x;
		mat.posit_y = pos.y;
		mat.posit_z = pos.z;
		
		GameObject *gameObject = gameObjectClass->Build(mat,Net::Team, true);
		new UserProcess(this, gameObject);
		gameObject->SetLocal();
		
		if (gameObject->curPilot == 0)
		{
			// get the game object class
			GameObjectClass *objClass = gameObject->GetClass();
			
			// if the object needs a pilot
			if (objClass->pilotCost > 0)
			{
				// assign pilot from the class
				if (gameObject == GameObject::GetUser())
				{
					gameObject->curPilot = objClass->userClass;
				}
				else
				{
					gameObject->curPilot = objClass->pilotClass;
				}
			}
		}
	}
}

void MultDMMission::SetMostRecentKilled(int killedHand)
{
	if (killed != killedHand)
	{
		recently_killed = true;
		GameObject *g = GameObjectHandle::GetObj(killedHand);
		if (g)
			pos = g->GetPosition();
		killed = killedHand;
	}
}

MultDMMission::~MultDMMission()
{
	delete pathSpawn;
	delete multEvent;
}

bool MultDMMission::Load(file fp)
{
	return LuaMission::Load(fp);
}

bool MultDMMission::Save(file fp)
{
	return LuaMission::Save(fp);
}

void MultDMMission::Respawn(void)
{
	assert(theNet);
	GameObjectClass *gameObjectClass;
	PrjID config = StringToPrjID(Net::odfName);
	gameObjectClass = GameObjectClass::Find(config);
	assert(gameObjectClass);
	//VECTOR_3D pos = theNet->GetStartLocation();
	VECTOR_3D pos = theNet->GetStartLocation();
	SpawnPoint *spawnPoint = SpawnPoint::GetWeighted(Net::Team);
	if (spawnPoint)
		pos = spawnPoint->GetLocation();
	MAT_3D mat = Identity_Matrix;
	mat.posit_x = pos.x;
	mat.posit_y = pos.y;
	mat.posit_z = pos.z;
	GameObject *gameObject = gameObjectClass->Build(mat,Net::Team);
	gameObject->SetAsUser();
	gameObject->SetTeam(Net::Team);
//	new UserProcess(this, gameObject);
	gameObject->SetLocal();
	
	if (gameObject->curPilot == 0)
	{
		// get the game object class
		GameObjectClass *objClass = gameObject->GetClass();
		
		// if the object needs a pilot
		if (objClass->pilotCost > 0)
		{
			// assign pilot from the class
			if (gameObject == GameObject::GetUser())
			{
				gameObject->curPilot = objClass->userClass;
			}
			else
			{
				gameObject->curPilot = objClass->pilotClass;
			}
		}
	}

	while (Pop_Camera());
	EnableInputs();
	Set_View (gameObject->GetEntity(), GK_COCKPIT_VIEW);
}

bool MultDMMission::EjectCraftCreate(void)
{
	return true;
}

extern void fsm_camera_trans_path_dir(AiPath *path, int *height, int *velocity);

void MultDMMission::Update(void)
{
	LuaMission::Update();
}

void MultDMMission::AddObject(GameObject *gameObj)
{
	if (gameObj->GetTeam() != 0)
	{
		LuaMission::AddObject(gameObj);
	}
}

const std::set<std::string>& MultDMMission::GetPreloadSet()
{
	static std::set<std::string> retval = {};
	if (retval.empty()) return AiMission::GetPreloadSet();
	return retval;
}

const std::set<PrjID>& MultDMMission::GetPreloadGameObjects()
{
	static std::set<PrjID> retval;
	retval = GetAllowedVehicles(msn_filename, false, false);
	return retval;
}
