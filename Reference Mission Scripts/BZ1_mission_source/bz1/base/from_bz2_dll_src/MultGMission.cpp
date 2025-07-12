#include "GameCommon.h"
#include "..\fun3d\GameObjectHandle.h"
#include "..\fun3d\Net.h"
#include "..\fun3d\NetPlayers.h"
#include "..\fun3d\SpawnPoint.h"
#include "..\fun3d\ScriptUtils.h"
#include "..\fun3d\UserProcess.h"

class MultGEvent;

class MultGMission : public AiMission {
	DECLARE_RTIME(MultGMission)
public:
	MultGMission(void);
	~MultGMission();
	bool Load(file fp);
	bool Save(file fp);
	virtual int GetTeam(int team);
	virtual void Respawn(void);
	virtual void Init(void);
	virtual bool EjectCraftCreate(void);

	static MultGEvent *multGEvent;
};


struct prup {
	int powerup;
	float time;
	char str[20];
	bool waiting;
};

#define INIT	0
#define RUN		1

class MultGEvent : public AiProcess {
	DECLARE_RTIME(MultGEvent)

public:
	MultGEvent(void);
	MultGEvent(AiMission *mission);
	void Execute(void);
	void refresh_flags(void);

private:
	int state;
	int bad_guy[3];
	struct prup pup[30];
	int goal1a;
	int goal1b;
	int goal2a;
	int goal2b;
	int starttimer;
	int goal1amessage;
	int goal1bmessage;
	int goal2amessage;
	int goal2bmessage;

public:
	int reset;
};

IMPLEMENT_RTIME(MultGEvent)

MultGEvent::MultGEvent(void)
{
	_ASSERTE(false);
}

MultGEvent::MultGEvent(AiMission *mission): AiProcess(mission, NULL)
{
	starttimer = 1;
	reset = 0;
	state = INIT;
	for (int i = 0; i < sizeof (bad_guy) / sizeof(bad_guy[0]); i++)
		bad_guy[i] = 0;
	for (int j = 0; j < sizeof (pup) / sizeof(pup[0]); j++)
	{
		if (j % 2)
			sprintf(pup[j].str, "ammo%d", j / 2);
		else
			sprintf(pup[j].str, "repa%d", j / 2);
	}
}

extern float respawn_timer;
extern int respawn;

MultGEvent *MultGMission::multGEvent;

void MultGEvent::refresh_flags(void)
{
	GameObject *g;

	goal1amessage = 1;
	goal1bmessage = 1;
	goal2amessage = 1;
	goal2bmessage = 1;

	
	if (!IsAlive(goal1a))
	{
		goal1a = BuildObject("abstor",1, "goal1a");
		g = GameObjectHandle::GetObj(goal1a);
		if (g) g->SetLocal();
	}
	if (!IsAlive(goal1b))
	{
		goal1b = BuildObject("abstor",1, "goal1b");
		g = GameObjectHandle::GetObj(goal1b);
		if (g) g->SetLocal();
	}
	if (!IsAlive(goal2a))
	{
		goal2a = BuildObject("abstor",2, "goal2a");
		g = GameObjectHandle::GetObj(goal2a);
		if (g) g->SetLocal();
	}
	if (!IsAlive(goal2b))
	{
		goal2b = BuildObject("abstor",2, "goal2b");
		g = GameObjectHandle::GetObj(goal2b);
		if (g) g->SetLocal();
	}
}

void MultGEvent::Execute(void)
{
	if (reset)
	{
		reset = 0;
		starttimer = 1;
		GameObject *gUserObject = GameObject::GetUser();
		if (gUserObject)
		{
//			gUserObject->hasPilot = 0;
//			gUserObject->Explode();
			char tmp[20];
			sprintf(tmp, "team%da", Net::Team);
			AiPath *p = AiPath::Find(tmp);
			VECTOR_2D &start = p->points[0];

			MAT_3D m = gUserObject->GetTransform();
			m.posit.x = start.x;
			m.posit.z = start.z;
			m.posit.y = Terrain_FindFloor(start.x, start.z);
			gUserObject->SetTransform(m);


//			respawn_timer = Get_Time() + 2.0f;
//			respawn = 1;
		}
	}

	if (starttimer)
	{
		starttimer = 0;
		StartCockpitTimer(540.0f, 362.0f, 180.0f);
	}

	if (Net::GetHosting())
	{
		if (state == INIT)
		{
			goal1amessage = 1;
			goal1bmessage = 1;
			goal2amessage = 1;
			goal2bmessage = 1;

			state = RUN;
			for (int i = 0; i < sizeof (pup) / sizeof(pup[0]); i++)
			{
				GameObject *g;
				
				if (pup[i].str[0] == 'a')
					pup[i].powerup = BuildObject("apammo",0, pup[i].str);
				else
					pup[i].powerup = BuildObject("aprepa",0, pup[i].str);
				g = GameObjectHandle::GetObj(pup[i].powerup);
				if (g)
					g->SetLocal();

				pup[i].waiting = false;
			}
			{
				GameObject *g;
				
				goal1a = BuildObject("abstor",1, "goal1a");
				g = GameObjectHandle::GetObj(goal1a);
				if (g) g->SetLocal();

				goal1b = BuildObject("abstor",1, "goal1b");
				g = GameObjectHandle::GetObj(goal1b);
				if (g) g->SetLocal();

				goal2a = BuildObject("abstor",2, "goal2a");
				g = GameObjectHandle::GetObj(goal2a);
				if (g) g->SetLocal();

				goal2b = BuildObject("abstor",2, "goal2b");
				g = GameObjectHandle::GetObj(goal2b);
				if (g) g->SetLocal();
			}
		}
		else
		{

			// Write messages depending on what blows up.
			if(goal1amessage && !IsAlive(goal1a))
			{
				Net_BroadCastMessage("Team 1 has lost flag 1");
				DisplayMessage("Team 1 has lost flag 1");
				goal1amessage = 0;
			}
			if(goal1bmessage && !IsAlive(goal1b))
			{
				Net_BroadCastMessage("Team 1 has lost flag 2");
				DisplayMessage("Team 1 has lost flag 2");
				goal1bmessage = 0;
			}
			if(goal2amessage && !IsAlive(goal2a))
			{
				Net_BroadCastMessage("Team 2 has lost flag 1");
				DisplayMessage("Team 2 has lost flag 1");
				goal2amessage = 0;
			}
			if(goal2bmessage && !IsAlive(goal2b))
			{
				Net_BroadCastMessage("Team 2 has lost flag 2");
				DisplayMessage("Team 2 has lost flag 2");
				goal2bmessage = 0;
			}

			if (GetCockpitTimer() < 1)
			{
				char buffer[10];
				WORD *w = (WORD *) buffer;
				char *ptr = (char *) (w + 1);
				*w = 'SS';
				*ptr = 'R';
				Net_BroadCast(buffer, 10);
				reset = 1;
				Net_BroadCastMessage("Time Has Run Out");
				DisplayMessage("Time Has Run Out");
				refresh_flags();
			}
			if (!IsAlive(goal2a) && !IsAlive(goal2b))
			{
				char buffer[10];
				WORD *w = (WORD *) buffer;
				char *ptr = (char *) (w + 1);
				*w = 'SS';
				*ptr = 'R';
				Net_BroadCast(buffer, 10);
				reset = 1;
				Net_BroadCastMessage("Team 2 has lost its flags, Score 1 for team 1");
				DisplayMessage("Team 2 has lost its flags, Score 1 for team 1");
				refresh_flags();
			}
			if (!IsAlive(goal1a) && !IsAlive(goal1b))
			{
				char buffer[10];
				WORD *w = (WORD *) buffer;
				char *ptr = (char *) (w + 1);
				*w = 'SS';
				*ptr = 'R';
				Net_BroadCast(buffer, 10);
				reset = 1;
				Net_BroadCastMessage("Team 1 has lost its flags, Score 1 for team 2");
				DisplayMessage("Team 1 has lost its flags, Score 1 for team 2");
				refresh_flags();
			}

			for (int i = 0; i < sizeof (pup) / sizeof(pup[0]); i++)
			{
				if (0 == GameObjectHandle::GetObj(pup[i].powerup) && false == pup[i].waiting)
				{
					pup[i].waiting = true;
					pup[i].time = Get_TimeLocal() + 10.0f;
				}
				if (pup[i].waiting && Get_TimeLocal() > pup[i].time)
				{
					if (pup[i].str[0] == 'a')
						pup[i].powerup = BuildObject("apammo",0, pup[i].str);
					else
						pup[i].powerup = BuildObject("aprepa",0, pup[i].str);
					GameObject *g = GameObjectHandle::GetObj(pup[i].powerup);
					if (g)
						g->SetLocal();
					pup[i].waiting = false;
				}
			}
		}
	}
}

static class MultGMissionClass : AiMissionClass {
public:
	MultGMissionClass(char *name) : AiMissionClass(name)
	{
	}
	int Matches(char *matches)
	{
		if (strnicmp(matches, name, strlen(name)) == 0)
			return TRUE;
		return FALSE;
	}
	AiMission *Build(void)
	{
		return new MultGMission;
	}
} MultGMissionClass("multG");

IMPLEMENT_RTIME(MultGMission)

MultGMission::MultGMission(void)
{
}

static int MyMessageHandler(char *buffer, int size)
{
	WORD *w = (WORD *) buffer;
	char *ptr = (char *) (w + 1);

	if (*w == 'SS')
	{
		// If we got an R then reset.
		if (*ptr == 'R')
		{
			MultGMission::multGEvent->reset = 1;
		}
		// Tell net the we handled this message
		return 1;
	}
	else
		return 0;		// Let net handle this message
}

void MultGMission::Init(void)
{
	if (!theNet)
		return;

	theNet->MessageHandler = MyMessageHandler;

	multGEvent = new MultGEvent(this);

	Net::SetDeathMatch(true);

	if (Net_IsNetGame())
	{
		_ASSERTE(theNet);
		
		GameObjectClass *gameObjectClass;
		PrjID config = 0;
		
		memcpy((char *) &config, Net::odfName, strlen(Net::odfName));
		
		gameObjectClass = GameObjectClass::Find(config);
		_ASSERTE(gameObjectClass);
		
//		if (Net::GetHosting())
//		{
//			// We are hosting so give yourself a spawn point.
//			SpawnPoint *spawnPoint = SpawnPoint::GetSafest();
//			_ASSERTE(spawnPoint);
//			
//			theNet->SetStartLocation(spawnPoint->GetLocation());
//			NetPlayer *netPlayer = NetPlayer::Find(theNet->GetMyPlayerID());
//			_ASSERTE(netPlayer);
//			netPlayer->SetWaitingForSpawnPoint(false);
//		}

		NetPlayer *netPlayer = NetPlayer::Find(theNet->GetMyPlayerID());
		netPlayer->SetWaitingForSpawnPoint(false);

		char tmp[20];

		_RPTF1(_CRT_WARN, "Creating player that is on team %d\n", Net::Team);
		if (Net::Team != 1)
			Net::Team = 2;
//		Net::Team = (Net::Team % 2) + 1;
		sprintf(tmp, "team%da", Net::Team);
		AiPath *p = AiPath::Find(tmp);
		VECTOR_2D &start = p->points[0];
		VECTOR_3D pos = { start.x, 0.0f, start.z };

//		VECTOR_3D pos = theNet->GetStartLocation();
		MAT_3D mat = Identity_Matrix;
		mat.posit = pos;
		
		GameObject *gameObject = gameObjectClass->Build(mat,Net::Team, true);
		
		//	GameObject *gameObject = gameObjectClass->Build(mat, 1, true);
		
		gameObject->SetLocal();
		
		//	SetupUserProcess(gameObject->GetOBJ76());
		
		new UserProcess(this, gameObject);
	}
}

MultGMission::~MultGMission()
{
}

bool MultGMission::Load(file fp)
{
	return AiMission::Load(fp);
}

bool MultGMission::Save(file fp)
{
	return AiMission::Save(fp);
}

int MultGMission::GetTeam(int team)
{
	return team;
}

void MultGMission::Respawn(void)
{
	_ASSERTE(theNet);
	GameObjectClass *gameObjectClass;
	PrjID config = 0;
	memcpy((char *) &config, Net::odfName, strlen(Net::odfName));
	gameObjectClass = GameObjectClass::Find(config);
	_ASSERTE(gameObjectClass);

	char tmp[20];
	sprintf(tmp, "team%da", Net::Team);
	AiPath *p = AiPath::Find(tmp);
	VECTOR_2D &start = p->points[0];
	VECTOR_3D pos = { start.x, 0.0f, start.z };

//	VECTOR_3D pos = theNet->GetStartLocation();
	MAT_3D mat = Identity_Matrix;
	mat.posit = pos;
	GameObject *gameObject = gameObjectClass->Build(mat, Net::Team, true);
	gameObject->SetLocal();
	new UserProcess(this, gameObject);
}

bool MultGMission::EjectCraftCreate(void)
{
	return true;
}