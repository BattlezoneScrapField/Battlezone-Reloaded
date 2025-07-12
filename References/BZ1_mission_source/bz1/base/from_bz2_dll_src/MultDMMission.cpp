#include "GameCommon.h"
#include "..\fun3d\GameObjectHandle.h"
#include "..\fun3d\MultDMMission.h"
#include "..\fun3d\Net.h"
#include "..\fun3d\NetPlayers.h"
#include "..\fun3d\SpawnPoint.h"
#include "..\fun3d\ScriptUtils.h"
#include "..\fun3d\UserProcess.h"
#include "..\fun3d\AiUtil.h"
#include "..\network\score.h"

extern void Toggle_NetworkTimer(void);

extern int king_of_the_hill_game;
extern int stratgy_game;

static GameObject *MyBuildObject(char *odf, int team, const VECTOR_3D &p)
{
	PrjID id = 0;
	strncpy((char *)&id, odf, 8);
	GameObjectClass *objClass = GameObjectClass::Find(id);
	if (objClass == NULL)
		return NULL;
	MAT_3D trans = Identity_Matrix;
	trans.posit = p;
	GameObject *gameObj = objClass->Build(trans, team);
	if (gameObj == NULL)
		return NULL;
//	AiMission::GetCurrent()->AddObject(gameObj);
	return gameObj;
}

static Handle MyBuildObject(char *odf, int team, Name path)
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

extern void do_escape(void);
extern int NetEscapeUp;

struct myprup {
	int powerup;
	float time;
	float dt;
	char str[20];
	char odf[10];
	bool waiting;
};

#define INIT	0
#define RUN		1

class MultDMEvent : public AiProcess {
	DECLARE_RTIME(MultDMEvent)
public:
	MultDMEvent(void);
	MultDMEvent(AiMission *mission);
	void Execute(void);
private:
	int state;
	struct myprup pup[100];
	int number;
	int doing_king_of_the_hill;
	float king_x;
	float king_z;
	int king_dist;
	int starttimer;
	DWORD dwNextTimeLimit;
	float fTimeInZone;
	float fTimeInZoneLast;
};

IMPLEMENT_RTIME(MultDMEvent)

MultDMEvent::MultDMEvent(void)
{
	_ASSERTE(false);
}

MultDMEvent::MultDMEvent(AiMission *mission): AiProcess(mission, NULL)
{
	state = INIT;
	starttimer = 1;
	fTimeInZone = 0.0f;
	fTimeInZoneLast = 0.0f;

	doing_king_of_the_hill = 0;

	king_of_the_hill_game = 0;
	stratgy_game = 0;
	AiPathList::iterator i;
	for (number = 0, i = AiPath::pathList.begin(); number < sizeof(pup) / sizeof(pup[0]) &&
		i != AiPath::pathList.end(); i++)
	{
		AiPath &curPath = **i;
		if (curPath.label == NULL)
			continue;
		if (strncmp(curPath.label, "king", 4) == 0)
		{
			Score::bDoingKing = true;
			doing_king_of_the_hill = 1;
			king_of_the_hill_game = 1;
			king_x = curPath.points[0].x;
			king_z = curPath.points[0].z;
			king_dist = atoi(&(curPath.label[4]));
			if (king_dist < 1)
				king_dist = 1;
			king_dist = king_dist * king_dist;
			continue;
		}
		strcpy(pup[number].str, curPath.label);
		strcpy(pup[number].odf, curPath.label);
		char *ptr = strchr(pup[number].odf, '_');
		if (ptr) *ptr = 0;
		ptr++;
		char tmp[20];
		strcpy(tmp, ptr);
		ptr = strchr(tmp, '_');
		if (ptr) *ptr = 0;
		int v = atoi(tmp);
		if (v > 0)
			pup[number].dt = (float) v;
		else
			pup[number].dt = 10.0f;
		number++;
	}
}

static int network_time = 0;
static DWORD dwLastTime = 0;


void Toggle_NetworkTimer(void)
{
	// toggle the timer flag
	network_time = !network_time;

	if (network_time)
	{
		// show the mission timer
		CockpitTimer::ShowTimer();
	}
	else
	{
		// hide the mission timer
		CockpitTimer::HideTimer();
	}
}

void MultDMEvent::Execute(void)
{
	DWORD dwNow = GetTickCount();
	DWORD dwNetNow = Get_Time_Long();

	if (network_time)
	{
		dwNetNow = dwNetNow / 1000;
		if (dwLastTime > dwNetNow + 2)
			dwLastTime = dwNetNow - 1;
		if (dwNetNow > dwLastTime)
		{
			CockpitTimer::SetTimerUp(dwNetNow);
			dwLastTime = dwNetNow;
		}
	}

	if (doing_king_of_the_hill)
	{
		GameObject *g = GameObject::GetUser();
		if (g)
		{
			VECTOR_3D k = {king_x, 0.0f, king_z};
			
			if (Dist2DSq(k, g->GetPosition()) < (float) king_dist)
			{

				// Only update the variable when the guy has been in there longer than
				// one second.
				fTimeInZone += TimeStep();
				if (fTimeInZone > fTimeInZoneLast + 1.0f)
				{
					Increment_Player_TimeInZone(fTimeInZone - fTimeInZoneLast);
					fTimeInZoneLast = fTimeInZone;
				}
			}
		}
	}

	if (Net::GetHosting())
	{
		if (state == INIT)
		{
			state = RUN;
			for (int i = 0; i < number; i++)
			{
				GameObject *g;
				pup[i].powerup = MyBuildObject(pup[i].odf, 0, pup[i].str);
				g = GameObjectHandle::GetObj(pup[i].powerup);
				if (g)
					g->SetLocal();

				pup[i].waiting = false;
			}
		}
		else
		{
			if (Net::KillLimit > 0)
			{
				int kills = GetTotalKills();

				if (kills >= Net::KillLimit)
				{
					Net::bStopGame = true;
					if (NetEscapeUp == 0)
						do_escape();
					return;
				}
			}

			if (Net::TimeLimit > 0)
			{
				if (starttimer)
				{
					starttimer = 0;
					StartCockpitTimer(Net::TimeLimit * 60.0f, 120.0f, 60.0f);
				}
				
				long t = GetCockpitTimer();



				if (t <= 0)
				{
					Net::bStopGame = true;
					if (NetEscapeUp == 0)
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
					WORD *w = (WORD *) &(buf[0]);
					*w = TIMER_PACKET_ID;
					long *timer = (long *) (w + 1);
					*timer = t;
					dp_result_t dp_result = Net::Send(Net::dp, Net_GetMyPlayerID(), dp_ID_BROADCAST,
						dp_SEND_UNRELIABLE, buf, 10);
					_ASSERTE(dp_RES_OK == dp_result);
				}

			}
			if (doing_king_of_the_hill)
			{
				ObjectList &list = *GameObject::objectList;
				ObjectList::iterator i;
				for (i = list.begin(); i != list.end(); i++)
				{
					GameObject *o = *i;
					VECTOR_3D k = {king_x, 0.0f, king_z};

					if (Dist2DSq(k, o->GetPosition()) < (float) king_dist)
					{
						Score::PlayerKing(o->GetPlayerID(), TimeStep());
					}
				}
				
			}
			for (int i = 0; i < number; i++)
			{
				if (0 == GameObjectHandle::GetObj(pup[i].powerup) && false == pup[i].waiting)
				{
					pup[i].waiting = true;
					pup[i].time = Get_TimeLocal() + pup[i].dt;
				}
				if (pup[i].waiting && Get_TimeLocal() > pup[i].time)
				{
					GameObject *g;
					pup[i].powerup = MyBuildObject(pup[i].odf, 0, pup[i].str);
					g = GameObjectHandle::GetObj(pup[i].powerup);
					if (g)
						g->SetLocal();
					
					pup[i].waiting = false;
				}
			}
		}
	}
}

static class MultDMMissionClass : AiMissionClass {
public:
	MultDMMissionClass(char *name) : AiMissionClass(name)
	{
	}
	int Matches(char *matches)
	{
		if (strnicmp(matches, name, strlen(name)) == 0)
			return TRUE;
		if (strnicmp(matches, "mult01", strlen("mult01")) == 0)
			return TRUE;
		if (strnicmp(matches, "mult03", strlen("mult03")) == 0)
			return TRUE;
		return FALSE;
	}
	AiMission *Build(void)
	{
		return new MultDMMission;
	}
} MultDMMissionClass("multDM");

IMPLEMENT_RTIME(MultDMMission)

MultDMMission::MultDMMission(void)
{
	recently_killed = false;
	killed = 0;
	camera = false;
}


void MultDMMission::Init(void)
{
	if (!theNet)
		return;

	new MultDMEvent(this);

	Net::SetDeathMatch(true);

	if (Net_IsNetGame())
	{
		_ASSERTE(theNet);
		
		GameObjectClass *gameObjectClass;
		PrjID config = 0;
		
		memcpy((char *) &config, Net::odfName, strlen(Net::odfName));
		
		gameObjectClass = GameObjectClass::Find(config);
		_ASSERTE(gameObjectClass);
		
		if (Net::GetHosting())
		{
			// We are hosting so give yourself a spawn point.
			SpawnPoint *spawnPoint = SpawnPoint::GetSafest();
			_ASSERTE(spawnPoint);
			
			theNet->SetStartLocation(spawnPoint->GetLocation());
			NetPlayer *netPlayer = NetPlayer::Find(theNet->GetMyPlayerID());
			_ASSERTE(netPlayer);
			netPlayer->SetWaitingForSpawnPoint(false);
		}

		MAT_3D mat = Identity_Matrix;
		mat.posit = theNet->GetStartLocation();
		
		Net::Team = 1;
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
				if (objClass->nation == AMERICAN_NATION)
				{
					if (gameObject == GameObject::GetUser())
					{
						gameObject->curPilot = *(PrjID *)"asuser\0";
					}
					else
					{
						gameObject->curPilot = *(PrjID *)"aspilo\0";
					}
				}
				else if (objClass->nation == SOVIET_NATION)
				{
					if (gameObject == GameObject::GetUser())
					{
						gameObject->curPilot = *(PrjID *)"ssuser\0";
					}
					else
					{
						gameObject->curPilot = *(PrjID *)"sspilo\0";
					}
				}
				else
				{
					_ASSERT(0);
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
}

bool MultDMMission::Load(file fp)
{
	return AiMission::Load(fp);
}

bool MultDMMission::Save(file fp)
{
	return AiMission::Save(fp);
}

// We are on team 1 and everyone else is on team 2
int MultDMMission::GetTeam(int team)
{
	if (team != 0)
		return 2;
	else
		return 0;
//	return team;
}

void MultDMMission::Respawn(void)
{
	_ASSERTE(theNet);
	GameObjectClass *gameObjectClass;
	PrjID config = 0;
	memcpy((char *) &config, Net::odfName, strlen(Net::odfName));
	gameObjectClass = GameObjectClass::Find(config);
	_ASSERTE(gameObjectClass);
	VECTOR_3D pos = theNet->GetStartLocation();
	MAT_3D mat = Identity_Matrix;
	mat.posit = pos;
	Net::Team = 1;
	GameObject *gameObject = gameObjectClass->Build(mat,Net::Team);
	gameObject->SetAsUser();
	gameObject->SetTeam(Net::Team);
	EnableInputs();
	Set_View (gameObject, GK_COCKPIT_VIEW);
//	new UserProcess(this, gameObject);
	gameObject->SetLocal();
	
	if (gameObject->curPilot == 0)
	{
		// get the game object class
		GameObjectClass *objClass = gameObject->GetClass();
		
		// if the object needs a pilot
		if (objClass->pilotCost > 0)
		{
			if (objClass->nation == AMERICAN_NATION)
			{
				if (gameObject == GameObject::GetUser())
				{
					gameObject->curPilot = *(PrjID *)"asuser\0";
				}
				else
				{
					gameObject->curPilot = *(PrjID *)"aspilo\0";
				}
			}
			else if (objClass->nation == SOVIET_NATION)
			{
				if (gameObject == GameObject::GetUser())
				{
					gameObject->curPilot = *(PrjID *)"ssuser\0";
				}
				else
				{
					gameObject->curPilot = *(PrjID *)"sspilo\0";
				}
			}
			else
			{
				_ASSERT(0);
			}
		}
	}
}

bool MultDMMission::EjectCraftCreate(void)
{
	return true;
}

extern void fsm_camera_trans_path_dir(AiPath *path, int *height, int *velocity);

void MultDMMission::Update(void)
{
	AiMission::Update();
}