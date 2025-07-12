#include "GameCommon.h"
#include "..\fun3d\GameObjectHandle.h"
#include "..\fun3d\Mult03Mission.h"
#include "..\fun3d\Net.h"
#include "..\fun3d\NetPlayers.h"
#include "..\fun3d\SpawnPoint.h"
#include "..\fun3d\ScriptUtils.h"
#include "..\fun3d\UserProcess.h"

struct prup {
	int powerup;
	float time;
	char str[20];
	bool waiting;
};

#define INIT	0
#define RUN		1

class Mult03Event : public AiProcess {
	DECLARE_RTIME(Mult03Event)
public:
	Mult03Event(void);
	Mult03Event(AiMission *mission);
	void Execute(void);
private:
	int state;
	int bad_guy[3];
	struct prup pup[16];
};

IMPLEMENT_RTIME(Mult03Event)

Mult03Event::Mult03Event(void)
{
	_ASSERTE(false);
}

Mult03Event::Mult03Event(AiMission *mission): AiProcess(mission, NULL)
{
	state = INIT;
	for (int i = 0; i < sizeof (bad_guy) / sizeof(bad_guy[0]); i++)
		bad_guy[i] = 0;
	for (int j = 0; j < sizeof (pup) / sizeof(pup[0]); j++)
	{
		sprintf(pup[j].str, "path_%d", j);
	}
}

void Mult03Event::Execute(void)
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

static class Mult03MissionClass : AiMissionClass {
public:
	Mult03MissionClass(char *name) : AiMissionClass(name)
	{
	}
	int Matches(char *matches)
	{
		if (strcmp(matches, name) == 0)
			return TRUE;
		if (strncmp(matches, "mult03", 6) == 0)
			return TRUE;
		return FALSE;
	}
	AiMission *Build(void)
	{
		return new Mult03Mission;
	}
} Mult03MissionClass("mult03");

IMPLEMENT_RTIME(Mult03Mission)

Mult03Mission::Mult03Mission(void)
{
}

void Mult03Mission::Init(void)
{
	new Mult03Event(this);

	Net::SetDeathMatch(true);
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

	GameObject *gameObject = gameObjectClass->Build(mat,Net::Team, true);

//	GameObject *gameObject = gameObjectClass->Build(mat, 1, true);

	gameObject->SetLocal();

//	SetupUserProcess(gameObject->GetOBJ76());

	new UserProcess(this, gameObject);
}

Mult03Mission::~Mult03Mission()
{
}

bool Mult03Mission::Load(file fp)
{
	return AiMission::Load(fp);
}

bool Mult03Mission::Save(file fp)
{
	return AiMission::Save(fp);
}

int Mult03Mission::GetTeam(int team)
{
	return team;
}

void Mult03Mission::Respawn(void)
{
	_ASSERTE(theNet);
	GameObjectClass *gameObjectClass;
	PrjID config = 0;
	memcpy((char *) &config, Net::odfName, strlen(Net::odfName));
	gameObjectClass = GameObjectClass::Find(config);
	_ASSERTE(gameObjectClass);
	MAT_3D mat = Identity_Matrix;
	mat.posit = theNet->GetStartLocation();
	GameObject *gameObject = gameObjectClass->Build(mat, Net::Team, true);
	gameObject->SetLocal();
	new UserProcess(this, gameObject);
}

bool Mult03Mission::EjectCraftCreate(void)
{
	return true;
}