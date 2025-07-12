#include "GameCommon.h"
#include "..\fun3d\GameObjectHandle.h"
#include "..\fun3d\Mult04Mission.h"
#include "..\fun3d\Net.h"
#include "..\fun3d\NetPlayers.h"
#include "..\fun3d\SpawnPoint.h"
#include "..\fun3d\ScriptUtils.h"
#include "..\fun3d\UserProcess.h"

#include "..\gamelgc\running.h"

struct prup {
	int powerup;
	float time;
	char str[20];
	bool waiting;
};

#define INIT	0
#define RUN		1

class Mult04Event : public AiProcess {
	DECLARE_RTIME(Mult04Event)
public:
	Mult04Event(void);
	Mult04Event(AiMission *mission);
	void Execute(void);
private:
	int state;
	int bad_guy[3];
	struct prup pup[16];
};

IMPLEMENT_RTIME(Mult04Event)

Mult04Event::Mult04Event(void)
{
	_ASSERTE(false);
}

Mult04Event::Mult04Event(AiMission *mission): AiProcess(mission, NULL)
{
	state = INIT;
	for (int i = 0; i < sizeof (bad_guy) / sizeof(bad_guy[0]); i++)
		bad_guy[i] = 0;
	for (int j = 0; j < sizeof (pup) / sizeof(pup[0]); j++)
	{
		sprintf(pup[j].str, "path_%d", j);
	}
}

void Mult04Event::Execute(void)
{
	if (Net::GetHosting())
	{
		if (state == INIT)
		{
			state = RUN;
			for (int i = 0; i < sizeof (pup) / sizeof(pup[0]); i++)
			{
				GameObject *g;
				
				if (i % 2)
					pup[i].powerup = BuildObject("apammo",2, pup[i].str);
				else
					pup[i].powerup = BuildObject("aprepa",2, pup[i].str);
				g = GameObjectHandle::GetObj(pup[i].powerup);
				if (g)
					g->SetLocal();

				pup[i].waiting = false;
			}
		}
		else
		{
			for (int i = 0; i < sizeof (pup) / sizeof(pup[0]); i++)
			{
				if (0 == GameObjectHandle::GetObj(pup[i].powerup) && false == pup[i].waiting)
				{
					pup[i].waiting = true;
					pup[i].time = Get_TimeLocal() + 10.0f;
				}
				if (pup[i].waiting && Get_TimeLocal() > pup[i].time)
				{
					if (i % 2)
						pup[i].powerup = BuildObject("apammo",2, pup[i].str);
					else
						pup[i].powerup = BuildObject("aprepa",2, pup[i].str);
					GameObject *g = GameObjectHandle::GetObj(pup[i].powerup);
					if (g)
						g->SetLocal();
					pup[i].waiting = false;
				}
			}
		}
#if 0
		for (int i = 0; i < sizeof (bad_guy) / sizeof(bad_guy[0]); i++)
		{
			if (0 == GameObjectHandle::GetObj(bad_guy[i]))
			{
				GameObjectClass *gameObjectClass;
				PrjID config = 0;
				memcpy((char *) &config, "svfigh", 6);
				
				gameObjectClass = GameObjectClass::Find(config);
				_ASSERTE(gameObjectClass);
				
				// We are hosting so give yourself a spawn point.
				SpawnPoint *spawnPoint = SpawnPoint::GetSafest();
				_ASSERTE(spawnPoint);
				
				VECTOR_3D pos = spawnPoint->GetLocation();
				MAT_3D mat = Identity_Matrix;
				mat.posit_x = pos.x;
				mat.posit_y = pos.y;
				mat.posit_z = pos.z;
				
				GameObject *gameObject = gameObjectClass->Build(mat, 2, false);
				gameObject->SetLocal();
				
				fMission->AddObject(gameObject);
				
				bad_guy[i] = GameObjectHandle::Find(gameObject);
			}
		}
#endif
	}
}

static class Mult04MissionClass : AiMissionClass {
public:
	Mult04MissionClass(char *name) : AiMissionClass(name)
	{
	}
	int Matches(char *matches)
	{
		if (strcmp(matches, name) == 0)
			return TRUE;
		if (strncmp(matches, "mult04", 6) == 0)
			return TRUE;
		return FALSE;
	}
	AiMission *Build(void)
	{
		return new Mult04Mission;
	}
} Mult04MissionClass("mult04");

IMPLEMENT_RTIME(Mult04Mission)

Mult04Mission::Mult04Mission(void)
{
	new Mult04Event(this);

	Net::SetDeathMatch(false);

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

	GameObject *gameObject = gameObjectClass->Build(mat, Net::Team, true);

	gameObject->SetLocal();

	new UserProcess(this, gameObject);
	config = 0;
	if (Net::odfName[0] == 'a')
		memcpy((char *) &config, "avrecy", 6);
	else
		memcpy((char *) &config, "svrecy", 6);
	
	gameObjectClass = GameObjectClass::Find(config);
	_ASSERTE(gameObjectClass);
	
	mat.posit.x += 50.0f;
	mat.posit.z += 50.0f;
	mat.posit.y = Terrain_FindFloor(mat.posit.x, mat.posit.z) + 2.0f;
	
	gameObject = gameObjectClass->Build(mat, Net::Team, false);
	_ASSERTE(gameObject);
	gameObject->GetTeamList()->AddScrap(20);
	gameObject->SetLocal();
//	gameObject->hasPilot = true;
	this->AddObject(gameObject);
}

Mult04Mission::~Mult04Mission()
{
}

bool Mult04Mission::Load(file fp)
{
	return AiMission::Load(fp);
}

bool Mult04Mission::Save(file fp)
{
	return AiMission::Save(fp);
}

int Mult04Mission::GetTeam(int team)
{
	return team;
}

void Mult04Mission::Respawn(void)
{
	SetRunning(RUN_WAS_FAILURE);
	/*
	_ASSERTE(theNet);
	GameObjectClass *gameObjectClass;
	PrjID config = 0;
	memcpy((char *) &config, Net::odfName, strlen(Net::odfName));
	gameObjectClass = GameObjectClass::Find(config);
	_ASSERTE(gameObjectClass);
	VECTOR_3D pos = theNet->GetStartLocation();
	MAT_3D mat = Identity_Matrix;
	mat.posit_x = pos.x;
	mat.posit_y = pos.y;
	mat.posit_z = pos.z;
	GameObject *gameObject = gameObjectClass->Build(mat, Net::Team, true);
	gameObject->SetLocal();
	new UserProcess(this, gameObject);
	*/
}

bool Mult04Mission::EjectCraftCreate(void)
{
	return false;
}