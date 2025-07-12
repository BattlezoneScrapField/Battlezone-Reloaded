#include "GameCommon.h"
#include "AiCommon.h"
#include "AiMission.h"
#include "AiProcess.h"
#include "PowerUp.h"
#include "ScriptUtils.h"

char *sounds[3] =
{
	"ch03003.wav",
	"ch03004.wav",
	"ch03005.wav"
};

char *back[3] =
{
	"east_back",
	"north_back",
	"west_back"
};

char *closeTo[3] = 
{
	"east_exit",
	"north_exit",
	"west_exit"
};

char *explosionSpot[15] =
{
	"east_exit", "east_exit", "east_exit", "east_exit", "east_exit",
	"north_exit", "north_exit", "north_exit", "north_exit", "north_exit",
	"west_exit", "west_exit", "west_exit", "west_exit", "west_exit"
};

char *spawns[6] =
{
	"apc_east",
	"apc_east",
	"apc_north",
	"apc_north",
	"apc_west",
	"apc_west",
};

char *apcFollow[6] =
{
	"east_path",
	"east_path",
	"north_path",
	"north_path",
	"west_path",
	"west_path"
};

char *defends[6] =
{
	"east_defend",
	"east_defend",
	"north_defend",
	"north_defend",
	"west_defend",
	"west_defend"
};


/*
	Chinese03Mission
*/

class Chinese03Mission : public AiMission {
	DECLARE_RTIME(Chinese03Mission)
public:
	Chinese03Mission();
	~Chinese03Mission();

	virtual bool Load(file fp);
	virtual bool PostLoad(void);
	virtual bool Save(file fp);

	virtual void Update(void);

	virtual void AddObject(GameObject *gameObj);

private:
	void Setup();
	void Execute();
	void AddObject(Handle h);
	
	// bools
	union {
		struct {
			bool
				// record whether the init code has been done
				startDone,

				// objectives
				objective1Complete,
				objective2Complete,
				objective3Complete,

				// cameras
				cameraReady[2], cameraComplete[2],

				// in howitzer?
				inHowitzer[6],
				howitzerReady[6],

				// apcs turned around?
				turnedAround[3],

				// triggers
				trigger1Done,

				// won or lost?
				won, lost,
				
				b_last;
		};
		bool b_array[26];
	};

	// floats
	union {
		struct {
			float
				openingSoundTime,
				apcSpawnTime,
				factorySpawnTime,
				explosionTime[15],
				generalSpawnTime,
				f_last;
		};
		float f_array[19];
	};

	// handles
	union {
		struct {
			Handle
				// the user
				user,
				lastUser,

				// units
				howitzers[6],
				apc[6],
				general,
				factory,
				armoury,
				
				// navs
				
				// place holder
				h_last;
		};
		Handle h_array[17];
	};

	// integers
	union {
		struct {
			int
				generalApc,
				// sounds
				openingSound,
				lose1Sound,
				lose2Sound,
				winSound,
				sound9,
				
				i_last;
		};
		int i_array[6];
	};
};

IMPLEMENT_RTIME(Chinese03Mission)

Chinese03Mission::Chinese03Mission()
{
}

Chinese03Mission::~Chinese03Mission()
{
}

bool Chinese03Mission::Load(file fp)
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

bool Chinese03Mission::PostLoad(void)
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

bool Chinese03Mission::Save(file fp)
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

void Chinese03Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

void Chinese03Mission::AddObject(Handle h)
{
}

void Chinese03Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

void Chinese03Mission::Setup()
{
	int i = 0;
	startDone = FALSE;
	objective1Complete = FALSE;
	objective2Complete = FALSE;
	objective3Complete = FALSE;
	for (i = 0; i < 6; i++)
	{
		inHowitzer[i] = FALSE;
		howitzerReady[i] = FALSE;
	}
	for (i = 0; i < 6; i++)
		turnedAround[i] = FALSE;
	trigger1Done = FALSE;
	
	// cameras
	for (i = 0; i < 2; i++)
	{
		cameraReady[i] = FALSE;
		cameraComplete[i] = FALSE;
	}
	
	// units
	user = NULL;
	lastUser = NULL;
	howitzers[0] = GetHandle("howitzer_1");
	howitzers[1] = GetHandle("howitzer_2");
	howitzers[2] = GetHandle("howitzer_3");
	howitzers[3] = GetHandle("howitzer_4");
	howitzers[4] = GetHandle("howitzer_5");
	howitzers[5] = GetHandle("howitzer_6");
	for (i = 0; i < 6; i++)
		apc[i] = NULL;
	general = NULL;
	factory = NULL;
	armoury = NULL;

	
	// navs
	
	// sounds
	openingSound = NULL;
	lose1Sound = NULL;
	lose2Sound = NULL;
	winSound = NULL;
	sound9 = NULL;
	
	// times
	openingSoundTime = 999999.9f;
	apcSpawnTime = 999999.9f;
	factorySpawnTime = 999999.9f;
	for (i = 0; i < 15; i++)
		explosionTime[i] = 999999.9f;
	generalSpawnTime = 999999.9f;
	
	// ints
	generalApc = -1;
}

void Chinese03Mission::Execute()
{
	int i = 0;
	lastUser = user;
	user = GetPlayerHandle(); //assigns the player a handle every frame

	if (!startDone)
	{
		SetPilot(1, 10);
		SetScrap(1, 0);

		// don't do this part after the first shot
		startDone = TRUE;

		openingSoundTime = GetTime() + 1.0;

		ClearObjectives();
		AddObjective("ch03001.otf", WHITE);

		for (i = 0; i < 6; i++)
		{
			SetObjectiveOn(howitzers[i]);
			SetPerceivedTeam(howitzers[i], 2);
		}

		StartCockpitTimer(780.0, 30.0, 10.0);

		factorySpawnTime = GetTime() + 480.0;
	}

	if (openingSoundTime < GetTime())
	{
		openingSoundTime = 999999.9f;

		openingSound = AudioMessage("ch03001.wav");
	}

	if (openingSound != NULL && IsAudioMessageDone(openingSound))
	{
		openingSound = NULL;
	}

	if (!objective1Complete && GetCockpitTimer() <= 0.0 && !lost && !won)
	{
		lost = TRUE;
		FailMission(GetTime() + 1.0, "ch03lsea.des");
	}

	if (!objective1Complete)
	{
		objective1Complete = TRUE;
		for (i = 0; i < 6; i++)
		{
			if (user == howitzers[i] && !inHowitzer[i])
			{
				inHowitzer[i] = TRUE;
				AudioMessage("ch03002.wav");
			}
			
			if (!howitzerReady[i])
			{
				// test to see if ready
				if (GetCurHealth(howitzers[i]) > 400 &&
					GetCurAmmo(howitzers[i]) > 400)
				{
					howitzerReady[i] = TRUE;
				}

				if (howitzerReady[i])
					SetObjectiveOff(howitzers[i]);
				else
					objective1Complete = FALSE;
			}
			else /* if (howitzerReady[i]) */
			{
				if (user != howitzers[i] && inHowitzer[i])
				{
					// set the pilot
					GameObject *obj = GameObjectHandle::GetObj(howitzers[i]);
					_ASSERTMSG0(obj != NULL, "NULL Howitzer");
					if (obj->GetAIProcess() == NULL)
					{
						obj->curPilot = 0;//*(PrjID*)"cspilo\0";
						AiProcess::Attach(this, obj);
					}
					SetPerceivedTeam(howitzers[i], 2);
				}
			}
		}

		if (objective1Complete)
		{
			StopCockpitTimer();
			HideCockpitTimer();
			
			ClearObjectives();
			AddObjective("ch03001.otf", GREEN);
			AddObjective("ch03002.otf", WHITE);

			apcSpawnTime = GetTime();
			Handle h = BuildObject("apcamr", 1, "nav_base");
			SetName(h, "CCA Base");
		}
	}

	if (apcSpawnTime < GetTime())
	{
		apcSpawnTime = 999999.9f;
		
		// spawn the apcs
		generalApc = rand() % 6;
		generalSpawnTime = GetTime();
		for (i = 0; i < 6; i++)
		{
			apc[i] = BuildObject((generalApc == i ? "svapcq" : "svapcr"), 2, spawns[i]);
			SetPerceivedTeam(apc[i], 1);
			Goto(apc[i], apcFollow[i], 1);

			Handle h;
			h = BuildObject("svtank", 2, defends[i]);
			Defend2(h, apc[i], 1);
			h = BuildObject("svtank", 2, defends[i]);
			Defend2(h, apc[i], 1);
			h = BuildObject("svhraz", 2, defends[i]);
			Defend2(h, apc[i], 1);
			h = BuildObject("svfigh", 2, defends[i]);
			Defend2(h, apc[i], 1);
		}
		general = apc[generalApc];

		_DEBUGMSG1("General APC spawned at %s", spawns[generalApc]);
	}

	if (factorySpawnTime < GetTime())
	{
		factorySpawnTime = 999999.9f;

		// spawn the factory
		factory = BuildObject("cvmufa", 1, "factory");
		Goto(factory, "factory_path", 1);
		AddScrap(1, 100);
		armoury = BuildObject("cvslfa", 1, "factory");
		Goto(armoury, "factory_path", 1);
		//Handle h;
		//h = BuildObject("cvscav", 1, "factory");
		//Goto(h, "factory_path", 1);
		//h = BuildObject("cvscav", 1, "factory");
		//Goto(h, "factory_path", 1);
		//h = BuildObject("cvscav", 1, "factory");
		//Goto(h, "factory_path", 1);
		//h = BuildObject("cvscav", 1, "factory");
		//Goto(h, "factory_path", 1);

		AddScrap(1, 100);
	}

	if (factory != NULL && GetHealth(factory) <= 0.0f && !lost && !won)
	{
		lost = TRUE;
		FailMission(GetTime() + 1.0f, "ch03lsee.des");
	}

	if (objective1Complete && !objective2Complete)
	{
		for (i = 0; i < 3; i++)
		{
			if (!turnedAround[i])
			{
				if (GetDistance(apc[2*i], closeTo[i]) < 40.0 ||
					GetDistance(apc[2*i+1], closeTo[i]) < 40.0)
				{
					turnedAround[i] = TRUE;
					AudioMessage(sounds[i]);

					Goto(apc[2*i], back[i], 1);
					Goto(apc[2*i+1], back[i], 1);

					// get the howies to attack
					Attack(howitzers[2*i], apc[2*i], 1);
					Attack(howitzers[2*i+1], apc[2*i+1], 1);

					// start the explosions
					explosionTime[5*i] = GetTime();
					explosionTime[5*i+1] = GetTime() + 5;
					explosionTime[5*i+2] = GetTime() + 10;
					explosionTime[5*i+3] = GetTime() + 15;
					explosionTime[5*i+4] = GetTime() + 20;
				}
			}
		}
	}

	for (i = 0; i < 15; i++)
	{
		if (explosionTime[i] <= GetTime())
		{
			explosionTime[i] = 999999.9f;
			MakeExplosion(explosionSpot[i], "xgasxpl");
		}
	}

	// general apc destroyed?
	if (general != NULL && GetHealth(general) <= 0.0 && !lost && !won)
	{
		lost = TRUE;
		lose1Sound = AudioMessage("ch03008.wav");
	}

	if (lose1Sound != NULL && IsAudioMessageDone(lose1Sound))
	{
		FailMission(GetTime() + 1.0, "ch03lsec.des");
	}

	if (lose2Sound != NULL && IsAudioMessageDone(lose2Sound))
	{
		FailMission(GetTime() + 1.0, "ch03lsed.des");
	}

	if (general != NULL && (generalSpawnTime + 120.0f) < GetTime() && 
		GetDistance(general, "base_fail") < 50.0 && !lost)
	{
		lost = TRUE;
		sound9 = AudioMessage("ch03009.wav");
	}

	if (sound9 != NULL && IsAudioMessageDone(sound9))
	{
		sound9 = NULL;
		FailMission(GetTime() + 1.0, "ch03lsed.des");
	}

	if (!objective2Complete && generalApc != -1 && GetTeamNum(general) == 1)
	{
		objective2Complete = TRUE;
		AudioMessage("ch03006.wav");
		ClearObjectives();
		AddObjective("ch03001.otf", GREEN);
		AddObjective("ch03002.otf", GREEN);
		AddObjective("ch03003.otf", WHITE);
	}

	if (objective2Complete && !trigger1Done && 
		GetDistance(general, "trigger_1") < 30.0)
	{
		trigger1Done = TRUE;

		for (i = 0; i < 6; i++)
		{
			Handle h = BuildObject("svfigh", 2, "apc_attack");
			Attack(h, general, 1);
		}

		for (i = 0; i < 4; i++)
		{
			Handle h = BuildObject("svfigh", 2, "apc_attack_2");
			Attack(h, general, 1);
		}

		Handle h;
		h = BuildObject("svtank", 2, "factory_attack");
		Attack(h, factory, 1);
		h = BuildObject("svtank", 2, "factory_attack");
		Attack(h, factory, 1);
		h = BuildObject("svtank", 2, "factory_attack");
		Attack(h, factory, 1);
		h = BuildObject("svfigh", 2, "factory_attack");
		Attack(h, factory, 1);
		h = BuildObject("svfigh", 2, "factory_attack");
		Attack(h, factory, 1);
	}

	if (objective2Complete && !won && GetDistance(general, "won_mission") < 30.0f && !lost)
	{
		won = TRUE;
		SucceedMission(GetTime() + 1.0, "ch03win.des");
	}
}
