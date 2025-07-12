#include "GameCommon.h"
#include "AiCommon.h"
#include "AiMission.h"
#include "AiProcess.h"
#include "PowerUp.h"
#include "ScriptUtils.h"


/*
	Chinese02Mission
*/

class Chinese02Mission : public AiMission {
	DECLARE_RTIME(Chinese02Mission)
public:
	Chinese02Mission();
	~Chinese02Mission();

	virtual bool Load(file fp);
	virtual bool PostLoad(void);
	virtual bool Save(file fp);

	virtual void Update(void);

	virtual void AddObject(GameObject *gameObj);

private:
	void Setup();
	void Execute();
	void AddObject(Handle h);
	Handle getLiveApc();
	Handle getBase();

	// bools
	union {
		struct {
			bool
				// record whether the init code has been done
				startDone,

				// objectives
				objective1Complete,
				objective2Complete,

				// cameras
				cameraReady[2], cameraComplete[2],
				cameraArrived,

				// attacks destroyed?
				attack3Destroyed,
				attack5Destroyed,

				// apc situation
				apcSpawned,
				apcDamaged,
				apcArrived[3],
				apcTrigger1,
				apcTrigger2,
				apcAtHangar,

				// walker
				walkerAttack1,
				walkerAttack2,
				walkerAttack3,

				// won or lost?
				won, lost,
				
				b_last;
		};
		bool b_array[23];
	};

	// floats
	union {
		struct {
			float
				openingSoundTime,
				cameraPauseTime,
				sound2Time,
				attack5DestroyedSpawnTime,
				attack8Time,
				convoyTime,
				convoyAttack1Time,
				walkerTime,
				hangarAttack5Time,
				hangarAttack6Time,
				annoyTime,
				f_last;
		};
		float f_array[11];
	};

	// handles
	union {
		struct {
			Handle
				// the user
				user,

				// units
				recycler,
				hangar,
				factory,
				armoury,
				commTower,
				attack3[5],
				attack5[5],
				apc[3],
				walker,

				// navs
				convoyIntercept,

				// place holder
				h_last;
		};
		Handle h_array[21];
	};

	// integers
	union {
		struct {
			int
				// sounds
				openingSound,
				lose1Sound,
				lose2Sound,
				winSound,
				
				i_last;
		};
		int i_array[4];
	};
};

IMPLEMENT_RTIME(Chinese02Mission)

Chinese02Mission::Chinese02Mission()
{
}

Chinese02Mission::~Chinese02Mission()
{
}

bool Chinese02Mission::Load(file fp)
{
	if (missionSave) 
	{
		int i;

		// init bools
		int b_count = &b_last - b_array;
		_ASSERTE(b_count == SIZEOF(b_array));
		for (i = 0; i < b_count; i++)
			b_array[i] = false;

		// init floats
		int f_count = &f_last - f_array;
		_ASSERTE(f_count == SIZEOF(f_array));
		for (i = 0; i < f_count; i++)
			f_array[i] = 99999.0f;

		// init handles
		int h_count = &h_last - h_array;
		_ASSERTE(h_count == SIZEOF(h_array));
		for (i = 0; i < h_count; i++)
			h_array[i] = 0;

		// init ints
		int i_count = &i_last - i_array;
		_ASSERTE(i_count == SIZEOF(i_array));
		for (i = 0; i < i_count; i++)
			i_array[i] = 0;

		Setup();
		return AiMission::Load(fp);
	}

	bool ret = true;

	// bools
	int b_count = &b_last - b_array;
	_ASSERTE(b_count == SIZEOF(b_array));
	ret = ret && in(fp, b_array, sizeof(b_array));

	// floats
	int f_count = &f_last - f_array;
	_ASSERTE(f_count == SIZEOF(f_array));
	ret = ret && in(fp, f_array, sizeof(f_array));

	// Handles
	int h_count = &h_last - h_array;
	_ASSERTE(h_count == SIZEOF(h_array));
	ret = ret && in(fp, h_array, sizeof(h_array));

	// ints
	int i_count = &i_last - i_array;
	_ASSERTE(i_count == SIZEOF(i_array));
	ret = ret && in(fp, i_array, sizeof(i_array));

	ret = ret && AiMission::Load(fp);
	return ret;
}

bool Chinese02Mission::PostLoad(void)
{
	if (missionSave)
		return AiMission::PostLoad();

	bool ret = true;

	int h_count = &h_last - h_array;
	for (int i = 0; i < h_count; i++)
		h_array[i] = ConvertHandle(h_array[i]);

	ret = ret && AiMission::PostLoad();

	return ret;
}

bool Chinese02Mission::Save(file fp)
{
	if (missionSave)
		return AiMission::Save(fp);

	bool ret = true;

	// bools
	int b_count = &b_last - b_array;
	_ASSERTE(b_count == SIZEOF(b_array));
	ret = ret && out(fp, b_array, sizeof(b_array), "b_array");

	// floats
	int f_count = &f_last - f_array;
	_ASSERTE(f_count == SIZEOF(f_array));
	ret = ret && out(fp, f_array, sizeof(f_array), "f_array");

	// Handles
	int h_count = &h_last - h_array;
	_ASSERTE(h_count == SIZEOF(h_array));
	ret = ret && out(fp, h_array, sizeof(h_array), "h_array");

	// ints
	int i_count = &i_last - i_array;
	_ASSERTE(i_count == SIZEOF(i_array));
	ret = ret && out(fp, i_array, sizeof(i_array), "i_array");

	ret = ret && AiMission::Save(fp);
	return ret;
}

void Chinese02Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

void Chinese02Mission::AddObject(Handle h)
{
}

void Chinese02Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

void Chinese02Mission::Setup()
{
	int i = 0;
	startDone = FALSE;
	objective1Complete = FALSE;
	objective2Complete = FALSE;
	cameraArrived = FALSE;
	attack3Destroyed = FALSE;
	attack5Destroyed = FALSE;
	apcSpawned = FALSE;
	apcDamaged = FALSE;
	apcArrived[0] = FALSE;
	apcArrived[1] = FALSE;
	apcArrived[2] = FALSE;
	apcTrigger1 = FALSE;
	apcTrigger2 = FALSE;
	apcAtHangar = FALSE;
	walkerAttack1 = FALSE;
	walkerAttack2 = FALSE;
	walkerAttack3 = FALSE;
	
	// cameras
	for (i = 0; i < 2; i++)
	{
		cameraReady[i] = FALSE;
		cameraComplete[i] = FALSE;
	}
	
	// units
	user = NULL;
	recycler = GetHandle("recycler");
	hangar = GetHandle("hanger");
	commTower = GetHandle("comm_tower");
	armoury = GetHandle("armory");
	attack3[0] = GetHandle("attack_3_1");
	attack3[1] = GetHandle("attack_3_2");
	attack3[2] = GetHandle("attack_3_3");
	attack3[3] = GetHandle("attack_3_4");
	attack3[4] = GetHandle("attack_3_5");
	attack5[0] = GetHandle("attack_5_1");
	attack5[1] = GetHandle("attack_5_2");
	attack5[2] = GetHandle("attack_5_3");
	attack5[3] = GetHandle("attack_5_4");
	attack5[4] = GetHandle("attack_5_5");
	apc[0] = NULL;
	apc[1] = NULL;
	apc[2] = NULL;
	walker = NULL;
	
	// navs
	convoyIntercept = NULL;
	
	// sounds
	openingSound = NULL;
	lose1Sound = NULL;
	lose2Sound = NULL;
	winSound = NULL;
	
	// times
	openingSoundTime = 999999.9f;
	cameraPauseTime = 999999.9f;
	sound2Time = 999999.9f;
	attack5DestroyedSpawnTime = 999999.9f;
	attack8Time = 999999.9f;
	convoyTime = 999999.9f;
	convoyAttack1Time = 999999.9f;
	walkerTime = 999999.9f;
	hangarAttack5Time = 999999.9f;
	hangarAttack6Time = 999999.9f;
	annoyTime = 999999.9f;
}

Handle Chinese02Mission::getLiveApc()
{
	Handle h[3];
	int numApc = 0;
	for (int i = 0; i < 3; i++)
	{
		if (GetHealth(apc[i]) > 0.0)
			h[numApc++] = apc[i];
	}

	if (numApc == 0)
		return NULL;
	else
		return h[rand() % numApc];
}

Handle Chinese02Mission::getBase()
{
	Handle h[4];
	int numBase = 0;
	
	if (GetHealth(hangar) > 0.0)
			h[numBase++] = hangar;
	if (GetHealth(recycler) > 0.0)
			h[numBase++] = recycler;
	if (GetHealth(armoury) > 0.0)
			h[numBase++] = armoury;
	if (GetHealth(commTower) > 0.0)
			h[numBase++] = commTower;
	
	if (numBase == 0)
		return user;
	else
		return h[rand() % numBase];
}


void Chinese02Mission::Execute()
{
	int i = 0;
	user = GetPlayerHandle(); //assigns the player a handle every frame

	if (!startDone)
	{
		SetScrap(1,30);
		SetPilot(1,10);

		// don't do this part after the first shot
		startDone = TRUE;

		// disable all cloaking for this mission
		enableAllCloaking(FALSE);

		openingSoundTime = GetTime() + 1.0;
	}

	if (!cameraComplete[0])
	{
		if (!cameraReady[0])
		{
			cameraReady[0] = TRUE;
			CameraReady();
		}

		
		bool complete = FALSE;
		if (!cameraArrived)
		{
			cameraArrived = CameraPath("camera_start", 800, 2000, hangar);
			if (cameraArrived)
				cameraPauseTime = GetTime() + 2.0;
		}
		else if (cameraPauseTime < GetTime())
			complete = TRUE;
		
		if (CameraCancelled())
		{
			complete = TRUE;
			StopAudioMessage(openingSound);
		}

		if (complete)
		{
			CameraFinish();
			cameraComplete[0] = TRUE;

			ClearObjectives();
			AddObjective("ch02001.otf", WHITE);

			sound2Time = GetTime() + 60.0f;
			annoyTime = GetTime() + 120.0f;
			openingSoundTime = 999999.9f;
		}
	}

	if (annoyTime < GetTime())
	{
		annoyTime = GetTime() + 120.0f;

		Handle h;
		h = BuildObject("svltnk", 2, "annoy_1");
		Hunt(h, 1);
		h = BuildObject("svltnk", 2, "annoy_1");
		Hunt(h, 1);
		h = BuildObject("svfigh", 2, "annoy_1");
		Hunt(h, 1);
		h = BuildObject("svfigh", 2, "annoy_1");
		Hunt(h, 1);
	}

	if (openingSoundTime < GetTime())
	{
		openingSoundTime = 999999.9f;

		openingSound = AudioMessage("ch02001.wav");
	}

	if (openingSound != NULL && IsAudioMessageDone(openingSound))
	{
		openingSound = NULL;
	}

	if (sound2Time < GetTime())
	{
		sound2Time = 999999.9f;
		AudioMessage("ch02002.wav");
	}

	// are our important units destroyed?
	if (GetHealth(hangar) <= 0.0 && !lost && !won)
	{
		lost = TRUE;
		lose1Sound = AudioMessage("ch02006.wav");
	}

	if (lose1Sound != NULL && IsAudioMessageDone(lose1Sound))
	{
		lose1Sound = NULL;
		FailMission(GetTime() + 1.0, "ch02lsea.des");
	}

	// have we lost 2 or more APCs?
	if (apcSpawned && !lost && !won)
	{
		int apcDead = 0;
		for (i = 0; i < 3; i++)
		{
			if (GetHealth(apc[i]) <= 0.0 && !apcArrived[i])
				apcDead++;
		}

		if (apcDead >= 2)
		{
			lost = TRUE;
			lose2Sound = AudioMessage("ch02006.wav");
		}
	}

	if (lose2Sound != NULL && IsAudioMessageDone(lose2Sound))
	{
		lose2Sound = NULL;
		FailMission(GetTime() + 1.0, "ch02lseb.des");
	}

	// attack_3 destroyed?
	if (!attack3Destroyed)
	{
		attack3Destroyed = TRUE;
		for (i = 0; i < 5; i++)
		{
			if (IsAlive(attack3[i]))
			{
				attack3Destroyed = FALSE;
				break;
			}
		}

		if (attack3Destroyed)
		{
			Handle h = BuildObject("svartl", 2, "hanger_attack_2");
			Attack(h, hangar, 1);
		}
	}

	// attack_5 destroyed?
	if (!attack5Destroyed)
	{
		attack5Destroyed = TRUE;
		for (i = 0; i < 5; i++)
		{
			if (IsAlive(attack5[i]))
			{
				attack5Destroyed = FALSE;
				break;
			}
		}

		if (attack5Destroyed)
		{
			attack5DestroyedSpawnTime = GetTime() + 60.0f;
		}
	}

	if (attack5DestroyedSpawnTime < GetTime())
	{
		attack5DestroyedSpawnTime = 999999.9f;

		Handle h;

		// spawn at attack_6
		h = BuildObject("svfigh", 2, "attack_6");
		Goto(h, "attack_6_path", 1);
		h = BuildObject("svfigh", 2, "attack_6");
		Goto(h, "attack_6_path", 1);
		h = BuildObject("svfigh", 2, "attack_6");
		Goto(h, "attack_6_path", 1);
		h = BuildObject("svtank", 2, "attack_6");
		Goto(h, "attack_6_path", 1);
		h = BuildObject("svtank", 2, "attack_6");
		Goto(h, "attack_6_path", 1);
		h = BuildObject("svtank", 2, "attack_6");
		Goto(h, "attack_6_path", 1);
		h = BuildObject("svwalk", 2, "attack_6");
		Goto(h, "attack_6_path", 1);
		h = BuildObject("svwalk", 2, "attack_6");
		Goto(h, "attack_6_path", 1);
		h = BuildObject("svwalk", 2, "attack_6");
		Goto(h, "attack_6_path", 1);

		// spawn at attack_7
		h = BuildObject("svfigh", 2, "attack_7");
		Goto(h, getBase(), 1);
		h = BuildObject("svfigh", 2, "attack_7");
		Goto(h, getBase(), 1);
		h = BuildObject("svfigh", 2, "attack_7");
		Goto(h, getBase(), 1);
		h = BuildObject("svtank", 2, "attack_7");
		Goto(h, getBase(), 1);
		h = BuildObject("svtank", 2, "attack_7");
		Goto(h, getBase(), 1);
		h = BuildObject("svtank", 2, "attack_7");
		Goto(h, getBase(), 1);
		h = BuildObject("svwalk", 2, "attack_7");
		Goto(h, getBase(), 1);
		h = BuildObject("svwalk", 2, "attack_7");
		Goto(h, getBase(), 1);
		h = BuildObject("svwalk", 2, "attack_7");
		Goto(h, getBase(), 1);

		// spawn at hanger_attack_3
		h = BuildObject("svhraz", 2, "hanger_attack_3");
		Attack(h, hangar, 1);
		h = BuildObject("svhraz", 2, "hanger_attack_3");
		Attack(h, hangar, 1);

		// setup for walker spawn time
		walkerTime = GetTime() + 240.0;
	}

	if (walkerTime < GetTime())
	{
		walkerTime = 999999.9f;

		walker = BuildObject("svwalk", 0, "walker_spawn");
		SetObjectiveOn(walker);
		SetPerceivedTeam(walker, 1);
		Retreat(walker, "walker_path");
		AudioMessage("ch02007.wav");
		//AudioMessage("ch02008.wav");

		// setup for hangar attack
		hangarAttack5Time = GetTime() + 10.0f;
		
		// set up for attack_8
		attack8Time = GetTime() + 300.0f;

		// objectives
		ClearObjectives();
		AddObjective("ch02001.otf", WHITE);
		AddObjective("ch02003.otf", WHITE);
	}
#if 0
	if (walker != NULL && !walkerAttack1 && GetDistance(walker, "walker_attack_1") < 300)
	{
		walkerAttack1 = TRUE;

		Handle h;
		h = BuildObject("svfigh", 2, "walker_attack_1");
		Attack(h, walker, 1);
		h = BuildObject("svfigh", 2, "walker_attack_1");
		Attack(h, walker, 1);
	}
#endif
	if (walker != NULL && !walkerAttack2 && GetDistance(walker, "walker_attack_2") < 200)
	{
		walkerAttack2 = TRUE;

		Handle h;
		h = BuildObject("svfigh", 2, "walker_attack_2");
		Attack(h, walker, 1);
		h = BuildObject("svfigh", 2, "walker_attack_2");
		Attack(h, walker, 1);
		h = BuildObject("svltnk", 2, "walker_attack_2");
		Attack(h, walker, 1);
		h = BuildObject("svltnk", 2, "walker_attack_2");
		Attack(h, walker, 1);
		h = BuildObject("svtank", 2, "walker_attack_2");
		Attack(h, walker, 1);
		h = BuildObject("svtank", 2, "walker_attack_2");
		Attack(h, walker, 1);
	}

	if (walker != NULL && !walkerAttack3 && GetDistance(walker, "walker_attack_3") < 200)
	{
		walkerAttack3 = TRUE;

		Handle h;
		//h = BuildObject("svhraz", 2, "walker_attack_3");
		//Attack(h, walker, 1);
		//h = BuildObject("svhraz", 2, "walker_attack_3");
		//Attack(h, walker, 1);
		h = BuildObject("svltnk", 2, "walker_attack_3");
		Attack(h, walker, 1);
		h = BuildObject("svltnk", 2, "walker_attack_3");
		Attack(h, walker, 1);
		h = BuildObject("svtank", 2, "walker_attack_3");
		Attack(h, walker, 1);
		h = BuildObject("svtank", 2, "walker_attack_3");
		Attack(h, walker, 1);
	}

	if (walker != NULL && GetHealth(walker) <= 0.0f && !lost && !won)
	{
		lost = TRUE;
		FailMission(GetTime(), "ch02lsec.des");
	}

	if (walker != NULL && isAtEndOfPath(walker, "walker_path"))
	{
		SetTeamNum(walker, 1);
		Recycle(walker);
		walker = NULL;

		AudioMessage("ch02008.wav");
	}

	if (hangarAttack5Time < GetTime())
	{
		hangarAttack5Time = 999999.9f;

		Handle h = BuildObject("svartl", 2, "hanger_attack_5");
		Attack(h, hangar, 1);
	}

	if (attack8Time < GetTime())
	{
		attack8Time = 999999.9f;

		Handle h;
		h = BuildObject("svtank", 2, "attack_8");
		Goto(h, getBase(), 1);
		h = BuildObject("svtank", 2, "attack_8");
		Goto(h, getBase(), 1);
		h = BuildObject("svtank", 2, "attack_8");
		Goto(h, getBase(), 1);
		h = BuildObject("svwalk", 2, "attack_8");
		Goto(h, getBase(), 1);
		h = BuildObject("svwalk", 2, "attack_8");
		Goto(h, getBase(), 1);
		h = BuildObject("svwalk", 2, "attack_8");
		Goto(h, getBase(), 1);
		h = BuildObject("svwalk", 2, "attack_8");
		Goto(h, getBase(), 1);

		convoyTime = GetTime() + 270.0f;
	}

	// spawn the convoy
	if (convoyTime < GetTime())
	{
		convoyTime = 999999.9f;

		AudioMessage("ch02003.wav");

		// spawn the APCs
		apcSpawned = TRUE;
		apc[0] = BuildObject("cvapcb", 1, "convoy_units");
		Goto(apc[0], "convoy_path");
		apc[1] = BuildObject("cvapcb", 1, "convoy_units");
		Goto(apc[1], "convoy_path");
		apc[2] = BuildObject("cvapcb", 1, "convoy_units");
		Goto(apc[2], "convoy_path");

		// spawn the scouts
		Handle h;
		h = BuildObject("cvfighc", 1, "convoy_defend");
		Defend2(h, apc[0], 1);
		h = BuildObject("cvfighc", 1, "convoy_defend");
		Defend2(h, apc[0], 1);
		h = BuildObject("cvfighc", 1, "convoy_defend");
		Defend2(h, apc[1], 1);
		h = BuildObject("cvfighc", 1, "convoy_defend");
		Defend2(h, apc[1], 1);
		h = BuildObject("cvfighc", 1, "convoy_defend");
		Defend2(h, apc[2], 1);
		h = BuildObject("cvfighc", 1, "convoy_defend");
		Defend2(h, apc[2], 1);

		convoyAttack1Time = GetTime() + 60.0f;
		hangarAttack6Time = GetTime() + 5 * 60.0f;
	}

	if (hangarAttack6Time < GetTime())
	{
		hangarAttack6Time = 999999.9f;

		for (i = 0; i < 2; i++)
		{
			Handle h = BuildObject("svartl", 2, "hanger_attack_6");
			Attack(h, hangar, 1);
		}
	}

	if (convoyAttack1Time < GetTime())
	{
		convoyAttack1Time = 999999.9f;

		Handle h;

		// spawn convoy_attack_1
		h = BuildObject("svfigh", 2, "convoy_attack_1");
		Goto(h, getLiveApc(), 1);
		h = BuildObject("svfigh", 2, "convoy_attack_1");
		Goto(h, getLiveApc(), 1);
		h = BuildObject("svfigh", 2, "convoy_attack_1");
		Goto(h, getLiveApc(), 1);
		h = BuildObject("svfigh", 2, "convoy_attack_1");
		Goto(h, getLiveApc(), 1);
		
		// convoy_attack_2
		h = BuildObject("svartl", 2, "convoy_attack_2");
		Goto(h, getLiveApc(), 1);
		// convoy_attack_3
		h = BuildObject("svartl", 2, "convoy_attack_3");
		Goto(h, getLiveApc(), 1);
		// convoy_attack_4
		h = BuildObject("svartl", 2, "convoy_attack_4");
		Goto(h, getLiveApc(), 1);
		// convoy_attack_5
		h = BuildObject("svartl", 2, "convoy_attack_5");
		Goto(h, getLiveApc(), 1);
		// convoy_attack_6
		h = BuildObject("svartl", 2, "convoy_attack_6");
		Goto(h, getLiveApc(), 1);
		// convoy_attack_7
		h = BuildObject("svartl", 2, "convoy_attack_7");
		Goto(h, getLiveApc(), 1);
		// convoy_attack_8
		h = BuildObject("svartl", 2, "convoy_attack_8");
		Goto(h, getLiveApc(), 1);
		// convoy_attack_9
		h = BuildObject("svartl", 2, "convoy_attack_9");
		Goto(h, getLiveApc(), 1);
	}

	if (apcSpawned && !apcDamaged)
	{
		// check the health
		for (i = 0; i < 3; i++)
		{
			if (GetHealth(apc[i]) < 1.0)
			{
				apcDamaged = TRUE;
				break;
			}
		}

		if (apcDamaged)
		{
			AudioMessage("ch02004.wav");
			convoyIntercept = BuildObject("cpcamr", 1, "nav_convoy");
			SetName(convoyIntercept, "Convoy Intercept");

			ClearObjectives();
			AddObjective("ch02001.otf", WHITE);
			AddObjective("ch02002.otf", WHITE);
		}
	}

	if (apcSpawned && !apcTrigger1)
	{
		// if any of the APCs are within 30 units of trigger_point_1
		// then do this stuff
		if (GetDistance(apc[0], "trigger_point_1") < 30.0 ||
			GetDistance(apc[1], "trigger_point_1") < 30.0 ||
			GetDistance(apc[2], "trigger_point_1") < 30.0)
		{
			apcTrigger1 = TRUE;

			Handle h;
			h = BuildObject("svfigh", 2, "convoy_attack_10");
			Goto(h, getLiveApc(), 1);
			h = BuildObject("svfigh", 2, "convoy_attack_10");
			Goto(h, getLiveApc(), 1);
			h = BuildObject("svfigh", 2, "convoy_attack_10");
			Goto(h, getLiveApc(), 1);
			h = BuildObject("svfigh", 2, "convoy_attack_10");
			Goto(h, getLiveApc(), 1);
			h = BuildObject("svfigh", 2, "convoy_attack_10");
			Goto(h, getLiveApc(), 1);
			h = BuildObject("svfigh", 2, "convoy_attack_10");
			Goto(h, getLiveApc(), 1);
			h = BuildObject("svhraz", 2, "hanger_attack_3");
			Attack(h, hangar, 1);
			h = BuildObject("svhraz", 2, "hanger_attack_3");
			Attack(h, hangar, 1);
			h = BuildObject("svhraz", 2, "hanger_attack_3");
			Attack(h, hangar, 1);
		}
	}

	if (apcSpawned && !apcTrigger2)
	{
		// if any of the APCs are within 40 units of trigger_point_2
		// then do this stuff
		if (GetDistance(apc[0], "trigger_point_2") < 40.0 ||
			GetDistance(apc[1], "trigger_point_2") < 40.0 ||
			GetDistance(apc[2], "trigger_point_2") < 40.0)
		{
			apcTrigger2 = TRUE;

			Handle h;
			// attack_9
			h = BuildObject("svtank", 2, "attack_9");
			Goto(h, getBase(), 1);
			h = BuildObject("svtank", 2, "attack_9");
			Goto(h, getBase(), 1);
			h = BuildObject("svtank", 2, "attack_9");
			Goto(h, getBase(), 1);
			h = BuildObject("svtank", 2, "attack_9");
			Goto(h, getBase(), 1);
			h = BuildObject("svltnk", 2, "attack_9");
			Goto(h, getBase(), 1);
			h = BuildObject("svltnk", 2, "attack_9");
			Goto(h, getBase(), 1);

			// attack_10
			h = BuildObject("svtank", 2, "attack_10");
			Goto(h, getBase(), 1);
			h = BuildObject("svtank", 2, "attack_10");
			Goto(h, getBase(), 1);
			h = BuildObject("svltnk", 2, "attack_10");
			Goto(h, getBase(), 1);
			h = BuildObject("svltnk", 2, "attack_10");
			Goto(h, getBase(), 1);
			h = BuildObject("svrckt", 2, "attack_10");
			Goto(h, getBase(), 1);
			h = BuildObject("svrckt", 2, "attack_10");
			Goto(h, getBase(), 1);

			// hanger_attack_4
			h = BuildObject("svhraz", 2, "hanger_attack_4");
			Attack(h, hangar, 1);
			h = BuildObject("svhraz", 2, "hanger_attack_4");
			Attack(h, hangar, 1);
			h = BuildObject("svhraz", 2, "hanger_attack_4");
			Attack(h, hangar, 1);
		}
	}

	if (apcSpawned && !apcAtHangar)
	{
		// if any of the APCs are within 30 units of the hangar
		// then do this stuff
		if (GetDistance(apc[0], hangar) < 30.0 ||
			GetDistance(apc[1], hangar) < 30.0 ||
			GetDistance(apc[2], hangar) < 30.0)
		{
			apcAtHangar = TRUE;

			StartCockpitTimer(30);
			won = TRUE;
			winSound = AudioMessage("ch02005.wav");
		}
	}

	if (winSound != NULL && IsAudioMessageDone(winSound))
	{
		winSound = NULL;
		SucceedMission(GetTime() + 1.0, "ch02win.des");
	}
}
