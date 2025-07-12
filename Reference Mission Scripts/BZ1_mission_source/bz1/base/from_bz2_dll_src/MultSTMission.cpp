#include "GameCommon.h"
#include "..\fun3d\MultSTMission.h"
#include "..\fun3d\Net.h"
#include "..\fun3d\NetPlayers.h"
#include "..\fun3d\ScriptUtils.h"
#include "..\fun3d\SpawnPoint.h"
#include "..\fun3d\UserProcess.h"
#include "..\fun3d\TextRemap.h"

#include "..\network\score.h"

#include "..\gamelgc\running.h"

extern int read_text_label(char *screen, char *label, char* text);
extern void do_escape(void);

extern int king_of_the_hill_game;
extern int stratgy_game;

static class MultSTMissionClass : AiMissionClass {
public:
	MultSTMissionClass(char *name) : AiMissionClass(name)
	{
	}
	int Matches(char *matches)
	{
		if (strnicmp(matches, name, strlen(name)) == 0)
			return TRUE;
		if (strnicmp(matches, "mult02", strlen("mult02")) == 0)
			return TRUE;
		if (strnicmp(matches, "mult04", strlen("mult04")) == 0)
			return TRUE;
		
		return FALSE;
	}
	AiMission *Build(void)
	{
		return new MultSTMission;
	}
} MultSTMissionClass("multST");

IMPLEMENT_RTIME(MultSTMission)

// Hack to stop the back key when i loose the mission.
extern int mission_stop;

// Move the initialization stuff till after
MultSTMission::MultSTMission(void)
{
	king_of_the_hill_game = 0;
	stratgy_game = 1;
	mission_stop = 0;
	recently_killed = false;
	killed = 0;
	camera = false;
}

void MultSTMission::Init(void)
{
	if (!theNet)
		return;

	Net::SetDeathMatch(false);

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

	switch(gameObjectClass->nation)
	{
	case AMERICAN_NATION:
		config = *(PrjID *)"avrecy\0";
		break;
	case SOVIET_NATION:
		config = *(PrjID *)"svrecy\0";
		break;
	case ALIEN_NATION:
		_ASSERTE(false);
		config = *(PrjID *)"avrecy\0";
		break;
	case UNKNOWN_NATION:
		_ASSERTE(false);
		config = *(PrjID *)"avrecy\0";
		break;
	default:
		_ASSERTE(false);
		break;
	}

	gameObjectClass = GameObjectClass::Find(config);
	_ASSERTE(gameObjectClass);
	
	mat.posit.x += 50.0f;
	mat.posit.z += 50.0f;
	mat.posit.y = Terrain_FindFloor(mat.posit.x, mat.posit.z) + 2.0f;
	
	gameObject = gameObjectClass->Build(mat, Net::Team, false);
	_ASSERTE(gameObject);
	gameObject->GetTeamList()->AddScrap(20);
	gameObject->SetLocal();
	this->AddObject(gameObject);
}

MultSTMission::~MultSTMission()
{
}

bool MultSTMission::Load(file fp)
{
	return AiMission::Load(fp);
}

bool MultSTMission::Save(file fp)
{
	return AiMission::Save(fp);
}

int MultSTMission::GetTeam(int team)
{
	return team;
}

void MultSTMission::Respawn(void)
{
	//	Net::bStopGame = true;
	Net::iLivesLeft--;
	Decrement_Player_Lives();
	if (Net::iLivesLeft <= 0)
	{
		Net::SendLives(Net::iLivesLeft);
		mission_stop = 1;
		do_escape();
	}
	else
	{
		_ASSERTE(theNet);
		GameObjectClass *gameObjectClass;
		PrjID config = *(PrjID *) Net::odfName;
		gameObjectClass = GameObjectClass::Find(config);
		_ASSERTE(gameObjectClass);
		if (gameObjectClass->nation == AMERICAN_NATION)
		{
			config = *(PrjID *) "asuser\0";
		}
		else
		{
			config = *(PrjID *) "ssuser\0";
		}
		gameObjectClass = GameObjectClass::Find(config);
		_ASSERTE(gameObjectClass);
		MAT_3D mat = Identity_Matrix;
		mat.posit = theNet->GetStartLocation();
		GameObject *gameObject = gameObjectClass->Build(mat, Net::Team);
		gameObject->SetAsUser();
		gameObject->SetTeam(Net::Team);
		EnableInputs();
		Set_View (gameObject, GK_COCKPIT_VIEW);
		gameObject->SetLocal();
//		new UserProcess(this, gameObject);
	}
}

bool MultSTMission::EjectCraftCreate(void)
{
	return false;
}

static char *target = NULL;
static char *message = NULL;

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
				
				char *player;
				player = NetPlayer_GetPlayerName(g->GetPlayerID());
				
				if (player)
				{
					if (target == NULL)
						target = TextRemap::Find("multi_message","player");
					if (message == NULL)
						message = TextRemap::Find("multi_message","defeated");
					char strbuf[256];
					sprintf(strbuf,"%s %s %s",target, player, message);
					DisplayMessage(strbuf);
				}
				killed = killedHand;
			}
		}
	}
}

extern void fsm_camera_trans_path_dir(AiPath *path, int *height, int *velocity);

static DWORD StopCamera = 0;

void MultSTMission::Update(void)
{
	AiMission::Update();
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
		StopCamera = GetTickCount() + 2000;
	}
	if (camera)
	{
		fsm_camera_trans_path_dir(aipath, &height, &speed);
		if (CameraCancelled() || GetTickCount() > StopCamera)
		{
			CameraFinish();
			delete aipath;
			camera = false;
		}
	}
}