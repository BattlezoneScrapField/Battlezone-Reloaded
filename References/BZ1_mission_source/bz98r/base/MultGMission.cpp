#include "GameObjectHandle.h"
#include "Net.h"
#include "NetPlayers.h"
#include "SpawnPoint.h"
#include "ScriptUtils.h"
#include "UserProcess.h"
#include "gameNetInterface.h"
#include "p2p.h"
#include "LabelMap.h"

#include "score.h"
#include "strhelp.h"

#include "input.h"
#include "terramap.h"
class MultGEvent;

class MultGMission : public AiMission, private CGameNetP2PHandler {
	DECLARE_RTIME(MultGMission)
public:
	MultGMission(void);
	~MultGMission();
	virtual bool IsMP() override;
	virtual bool Load(file fp) override;
	virtual bool Save(file fp) override;
	virtual void Respawn(void) override;
	virtual void Init(void) override;
	virtual bool EjectCraftCreate(void) override;
	virtual void Update(void) override;
	virtual const std::set<std::string>& GetPreloadSet() override;
	virtual const std::set<PrjID>& GetPreloadGameObjects() override;

	static MultGEvent *multGEvent;
private:
	virtual void OnP2PReceived(CGameNetP2P& p2p, const NetPlayerIdExt& source, const unsigned char *data, size_t size) override;
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
	virtual void Execute(void) override;
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
	assert(false);
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

extern "C" float respawn_timer;
extern "C" int respawn;

MultGEvent *MultGMission::multGEvent;

void MultGEvent::refresh_flags(void)
{
	goal1amessage = 1;
	goal1bmessage = 1;
	goal2amessage = 1;
	goal2bmessage = 1;

	
	if (!IsAlive(goal1a))
	{
		goal1a = BuildObject("abstor",1, "goal1a");
	}
	if (!IsAlive(goal1b))
	{
		goal1b = BuildObject("abstor",1, "goal1b");
	}
	if (!IsAlive(goal2a))
	{
		goal2a = BuildObject("abstor",2, "goal2a");
	}
	if (!IsAlive(goal2b))
	{
		goal2b = BuildObject("abstor",2, "goal2b");
	}
}

void MultGEvent::Execute(void)
{
	
	if (Net::bStopGame) return;
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
			VECTOR_3D pos = { start.x, 0.0f, start.z };

			MAT_3D m = gUserObject->GetTransform();

			m.posit_x = pos.x;
			m.posit_z = pos.z;
			m.posit_y = Terrain_FindFloor(pos.x, pos.z);
			gUserObject->SetTransform(m);


//			respawn_timer = Get_TimeLocal() + 2.0f;
//			respawn = 1;
		}
	}

	if (starttimer)
	{
		starttimer = 0;
		StartCockpitTimer(540, 362, 180);
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
				if (pup[i].str[0] == 'a')
					pup[i].powerup = BuildObject("apammo",0, pup[i].str);
				else
					pup[i].powerup = BuildObject("aprepa",0, pup[i].str);
				pup[i].waiting = false;
			}
			{
				goal1a = BuildObject("abstor",1, "goal1a");
				goal1b = BuildObject("abstor",1, "goal1b");
				goal2a = BuildObject("abstor",2, "goal2a");
				goal2b = BuildObject("abstor",2, "goal2b");
			}
		}
		else
		{

			// Write messages depending on what blows up.
			if(goal1amessage && !IsAlive(goal1a))
			{
				const char *t = GetTextLabel("multi_message", "team_1_flag_1");
				Net_BroadCastMessage(t);
				DisplayMessage(t);
				goal1amessage = 0;
			}
			if(goal1bmessage && !IsAlive(goal1b))
			{
				const char *t = GetTextLabel("multi_message", "team_1_flag_2");
				Net_BroadCastMessage(t);
				DisplayMessage(t);
				goal1bmessage = 0;
			}
			if(goal2amessage && !IsAlive(goal2a))
			{
				const char *t = GetTextLabel("multi_message", "team_2_flag_1");
				Net_BroadCastMessage(t);
				DisplayMessage(t);
				goal2amessage = 0;
			}
			if(goal2bmessage && !IsAlive(goal2b))
			{
				const char *t = GetTextLabel("multi_message", "team_2_flag_2");
				Net_BroadCastMessage(t);
				DisplayMessage(t);
				goal2bmessage = 0;
			}

			if (GetCockpitTimer() < 1)
			{
				char buffer[10] = { '#', 'R', 0 };
				NetPlayer::Broadcast(buffer, 3);
				reset = 1;
				Net_BroadCastMessage("Time Has Run Out");
				DisplayMessage("Time Has Run Out");
				refresh_flags();
			}
			if (!IsAlive(goal2a) && !IsAlive(goal2b))
			{
				char buffer[] = { '#', 'R', 1 };
				NetPlayer::Broadcast(buffer, 3);
				reset = 1;
				Net_BroadCastMessage("Team 2 has lost its flags, Score 1 for team 1");
				DisplayMessage("Team 2 has lost its flags, Score 1 for team 1");
				refresh_flags();
			}
			if (!IsAlive(goal1a) && !IsAlive(goal1b))
			{
				char buffer[] = { '#', 'R', 2 };
				NetPlayer::Broadcast(buffer, 3);
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
					pup[i].waiting = false;
				}
			}
		}
	}
}

static class MultGMissionClass : AiMissionClass {
public:
	MultGMissionClass(const char *name) : AiMissionClass(name)
	{
	}
	int Matches(const char *matches)
	{
		if (strnicmp(matches, name, strlen(name)) == 0)
			return BZTRUE;
		return BZFALSE;
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

void MultGMission::OnP2PReceived(CGameNetP2P& p2p, const NetPlayerIdExt& source, const unsigned char *data, size_t size)
{
	if (data[0] == '#' && data[1] == 'R')
	{
		// If we got a mission reset packet then reset.
		MultGMission::multGEvent->reset = 1;
	}
}

void MultGMission::Init(void)
{
	if (!theNet)
		return;
	
	CGameNetP2P *p2p = getP2PHandler();
	if (p2p) p2p->AddP2PHandler(CGameNetP2P::P2PSubsystem('#'), this);

	multGEvent = new MultGEvent(this);

	Net::SetDeathMatch(true);

	if (Net_IsNetGame())
	{
		assert(theNet);
		
		GameObjectClass *gameObjectClass;
		PrjID config = StringToPrjID(Net::odfName);
		gameObjectClass = GameObjectClass::Find(config);
		assert(gameObjectClass);
		
//		if (Net::GetHosting())
//		{
//			// We are hosting so give yourself a spawn point.
//			SpawnPoint *spawnPoint = SpawnPoint::GetSafest();
//			assert(spawnPoint);
//			
//			theNet->SetStartLocation(spawnPoint->GetLocation());
//			NetPlayer *netPlayer = NetPlayer::Find(theNet->GetMyPlayerID());
//			assert(netPlayer);
//			netPlayer->SetWaitingForSpawnPoint(false);
//		}

		NetPlayer *netPlayer = NetPlayer::Find(theNet->GetMyPlayerIDExt());
		netPlayer->SetWaitingForSpawnPoint(false);

		char tmp[20];

		Trace("Creating player that is on team %d\n", Net::Team);
//		if (Net::Team != 1)
//			Net::Team = 2;
//		Net::Team = (Net::Team % 2) + 1;
		sprintf(tmp, "team%da", Net::Team);
		AiPath *p = AiPath::Find(tmp);
		VECTOR_2D &start = p->points[0];
		VECTOR_3D pos = { start.x, 0.0f, start.z };

//		VECTOR_3D pos = theNet->GetStartLocation();
		MAT_3D mat = Identity_Matrix;
		mat.posit_x = pos.x;
		mat.posit_y = pos.y;
		mat.posit_z = pos.z;
		
		GameObject *gameObject = gameObjectClass->Build(mat,Net::Team, true);
		
		//	GameObject *gameObject = gameObjectClass->Build(mat, 1, true);
		
		gameObject->SetLocal();
		
		new UserProcess(this, gameObject);

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

MultGMission::~MultGMission()
{
	CGameNetP2P *p2p = getP2PHandler();
	if (p2p) p2p->RemoveP2PHandler(CGameNetP2P::P2PSubsystem('#'), this);
}

bool MultGMission::Load(file fp)
{
	return AiMission::Load(fp);
}

bool MultGMission::Save(file fp)
{
	return AiMission::Save(fp);
}

void MultGMission::Respawn(void)
{
	assert(theNet);
	GameObjectClass *gameObjectClass;
	PrjID config = StringToPrjID(Net::odfName);
	gameObjectClass = GameObjectClass::Find(config);
	assert(gameObjectClass);

	char tmp[20];
	sprintf(tmp, "team%da", Net::Team);
	AiPath *p = AiPath::Find(tmp);
	VECTOR_2D &start = p->points[0];
	VECTOR_3D pos = { start.x, 0.0f, start.z };

//	VECTOR_3D pos = theNet->GetStartLocation();
	MAT_3D mat = Identity_Matrix;
	mat.posit_x = pos.x;
	mat.posit_y = pos.y;
	mat.posit_z = pos.z;
	GameObject *gameObject = gameObjectClass->Build(mat, Net::Team, true);
	gameObject->SetAsUser(); 
	gameObject->SetTeam(Net::Team);

	gameObject->SetLocal();
//	new UserProcess(this, gameObject);
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

bool MultGMission::EjectCraftCreate(void)
{
	return true;
}

extern void fsm_camera_trans_path_dir(AiPath *path, int *height, int *velocity);

void MultGMission::Update(void)
{
	AiMission::Update();
}

const std::set<std::string>& MultGMission::GetPreloadSet()
{
	static std::set<std::string> retval = {};
	if (retval.empty()) return AiMission::GetPreloadSet();
	return retval;
}

const std::set<PrjID>& MultGMission::GetPreloadGameObjects()
{
	static std::set<PrjID> retval;
	retval = GetAllowedVehicles(msn_filename, false, false);
	return retval;
}

bool MultGMission::IsMP()
{
	return true;
}
