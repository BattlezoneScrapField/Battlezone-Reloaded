#include "logger.h"
#include "MultSTMission.h"
#include "PathSpawn.h"
#include "Net.h"
#include "NetPlayers.h"
#include "ScriptUtils.h"
#include "SpawnPoint.h"
#include "UserProcess.h"
#include "LabelMap.h"
#include "bzshell.h"
#include "Person.h"
#include "strhelp.h"
#include "running.h"
#include "srandom.h"
#include "input.h"
#include "terramap.h"


extern int king_of_the_hill_game;
extern int stratgy_game;

static class MultSTMissionClass : AiMissionClass {
public:
	MultSTMissionClass(const char *name) : AiMissionClass(name)
	{
	}
	int Matches(const char *matches)
	{
		if (strnicmp(matches, name, strlen(name)) == 0)
			return BZTRUE;
		if (strnicmp(matches, "mult02", strlen("mult02")) == 0)
			return BZTRUE;
		if (strnicmp(matches, "mult04", strlen("mult04")) == 0)
			return BZTRUE;
		
		return BZFALSE;
	}
	AiMission *Build(void)
	{
		return new MultSTMission;
	}
} MultSTMissionClass("multST");

IMPLEMENT_BASE_RTIME(MultSTMission, LuaMission)


// Move the initialization stuff till after
MultSTMission::MultSTMission(void)
{
	pathSpawn = NULL;
	king_of_the_hill_game = 0;
	stratgy_game = 1;
	mission_stop = false;
	recently_killed = false;
	killed = 0;
	camera = false;
	dwLastTime = 0;
	SetAIControl(2, false);
}

void MultSTMission::Init(void)
{
	if (!theNet)
		return;
	if (Net::bStopGame) return;
	pathSpawn = new PathSpawn(this);

	Net::SetDeathMatch(false);

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

	// get the recycler matching the player
	config = GetMatchedRecycler(config, Net::bNations);
	if (!config)
		Trace("Could not find a recycler variant for %s", gameObjectClass->odf);

	gameObjectClass = GameObjectClass::Find(config);
	assert(gameObjectClass);
	
	mat.posit_x += 20.0f;
	mat.posit_z += 20.0f;
	mat.posit_y = Terrain_FindFloor(mat.posit_x, mat.posit_z) + 2.0f;
	
	gameObject = gameObjectClass->Build(mat, Net::Team, false);
	assert(gameObject);
	gameObject->GetTeamList()->AddScrap(20);
	gameObject->SetLocal();
	this->AddObject(gameObject);
}

MultSTMission::~MultSTMission()
{
	delete pathSpawn;
}

bool MultSTMission::Load(file fp)
{
	return LuaMission::Load(fp);
}

bool MultSTMission::Save(file fp)
{
	return LuaMission::Save(fp);
}

void MultSTMission::Respawn(void)
{
	//	Net::bStopGame = true;
	if (Net::iLivesLeft <= 0)
	{
		mission_stop = true;
		//SetRunning(RUN_WAS_QUIT);
		do_escape();
	}
	else
	{
		assert(theNet);
		GameObjectClass *gameObjectClass;
		PrjID config = StringToPrjID(Net::odfName);
		gameObjectClass = GameObjectClass::Find(config);
		assert(gameObjectClass);
		gameObjectClass = gameObjectClass->userClass;
		assert(gameObjectClass);
		VECTOR_3D pos = theNet->GetStartLocation();
		MAT_3D mat = Identity_Matrix;
		mat.posit_x = pos.x + 20.0f * (Random() - Random());
		mat.posit_y = pos.y + 50.0f;
		mat.posit_z = pos.z + 20.0f * (Random() - Random());
		GameObject *gameObject = gameObjectClass->Build(mat, Net::Team);
		gameObject->SetAsUser();
		gameObject->SetTeam(Net::Team);
		gameObject->SetLocal();
//		new UserProcess(this, gameObject);

		while (Pop_Camera());
		EnableInputs();
		Set_View (gameObject->GetEntity(), GK_COCKPIT_VIEW);
	}
}

bool MultSTMission::EjectCraftCreate(void)
{
	return false;
}

/*
static int linus_only_runs_once = 1;
static char target[256] = "Player";
static char message[256] = "Has Been Defeated";
*/

void MultSTMission::SetMostRecentKilled(int killedHand)
{
	if (killed != killedHand)
	{
		GameObject *g = GameObjectHandle::GetObj(killedHand);
		if (g)
		{
			// Only do this if it was a person that got killed.
			if (CLASS_PERSON == g->GetClass()->sig)
			{
				recently_killed = true;
				pos = g->GetPosition();
				killed = killedHand;
			}
		}
	}
}

extern void fsm_camera_trans_path_dir(AiPath *path, int *height, int *velocity);

static uint32_t StopCamera = 0;

void MultSTMission::Update(void)
{
	LuaMission::Update();

	if (cockpitTimer.IsVisible())
	{
		uint32_t dwNetNow = Get_Time_Long();
		dwNetNow = dwNetNow / 1000;
		if (dwLastTime > dwNetNow + 2)
			dwLastTime = dwNetNow - 1;
		if (dwNetNow > dwLastTime)
		{
			cockpitTimer.SetTimerUp(dwNetNow);
			dwLastTime = dwNetNow;
		}
	}

	if (!camera && recently_killed)
	{
		recently_killed = false;
		VECTOR_3D v = pos;
		v.x += 10.0f;
		v.y += 10.0f;
		v.z += 10.0f;
		height = 10;
		speed = 10;
		aipath = new AiPath(v, pos);
		CameraReady();
		camera = true;
		StopCamera = Get_TimeNow() + 2000;
	}
	if (camera)
	{
		fsm_camera_trans_path_dir(aipath, &height, &speed);
		if (CameraCancelled() || Get_TimeNow() > StopCamera)
		{
			CameraFinish();
			delete aipath;
			camera = false;
		}
	}
}

const std::set<std::string>& MultSTMission::GetPreloadSet()
{
	static std::set<std::string> retval = {};
	if (retval.empty()) return AiMission::GetPreloadSet();
	return retval;
}

const std::set<PrjID>& MultSTMission::GetPreloadGameObjects()
{
	static std::set<PrjID> retval;
	retval = GetAllowedVehicles(msn_filename, true, Net::bNations);
	return retval;
}
