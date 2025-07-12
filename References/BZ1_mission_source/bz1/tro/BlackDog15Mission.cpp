#include "GameCommon.h"
#include "AiCommon.h"
#include "AiMission.h"
#include "AiProcess.h"
#include "PowerUp.h"
#include "ScriptUtils.h"
#include "ColorFade.h"

/*
	BlackDog15Mission
*/

class BlackDog15Mission : public AiMission {
	DECLARE_RTIME(BlackDog15Mission)
public:
	BlackDog15Mission();
	~BlackDog15Mission();

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

				// objective complete?
				objective1Complete, 
				objective2Complete,
				objective3Complete,

				// camera info
				doingCamera,
				doingExplosion,
				doingCountdown,

				// sounds played?
				sound10Played,

				// all opposition spawned?
				allUnitsSpawned,

				// have we won/lost?
				wonLost,

				b_last;
		};
		bool b_array[10];
	};

	// floats
	union {
		struct {
			float
				sound2Time,
				sound3Time,
				sound4Time,
				sound5Time,
				sound6Time,
				sound8Time,
				sound9Time,
				sound12Time,
				eastWaveTime,
				f_last;
		};
		float f_array[9];
	};

	// handles
	union {
		struct {
			Handle
				// *** User stuff
				user,
				lastUser,
				
				// *** Units
				intro1, intro2,
				units[100],
				
				// nav beacons
				
				h_last;
		};
		Handle h_array[104];
	};

	// integers
	union {
		struct {
			int
				numUnits,

				// *** Sounds
				sound1,
				sound2,
				sound3,
				sound4,
				sound7,
				sound11,
				sound12,
				
				i_last;
		};
		int i_array[8];
	};
};

IMPLEMENT_RTIME(BlackDog15Mission)

BlackDog15Mission::BlackDog15Mission()
{
}

BlackDog15Mission::~BlackDog15Mission()
{
}

bool BlackDog15Mission::Load(file fp)
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

bool BlackDog15Mission::PostLoad(void)
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

bool BlackDog15Mission::Save(file fp)
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

void BlackDog15Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

void BlackDog15Mission::AddObject(Handle h)
{
}

void BlackDog15Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

void BlackDog15Mission::Setup()
{
	int i = 0;
	startDone = FALSE;
	wonLost = FALSE;
	objective1Complete = FALSE;
	objective2Complete = FALSE;
	objective3Complete = FALSE;
	sound10Played = FALSE;
	allUnitsSpawned = FALSE;
	doingCamera = FALSE;
	doingExplosion = FALSE;
	doingCountdown = FALSE;
	
	// units
	user = NULL;
	lastUser = NULL;
	for (i = 0; i < 100; i++)
		units[i] = NULL;
	intro1 = NULL;//GetHandle("chin_fighter_intro1");
	intro2 = NULL;//GetHandle("chin_fighter_intro2");
	
	// sounds
	sound1 = NULL;
	sound2 = NULL;
	sound3 = NULL;
	sound4 = NULL;
	sound7 = NULL;
	sound11 = NULL;
	sound12 = NULL;
	
	// times
	sound2Time = 999999.9f;
	sound3Time = 999999.9f;
	sound4Time = 999999.9f;
	sound5Time = 999999.9f;
	sound6Time = 999999.9f;
	sound8Time = 999999.9f;
	sound9Time = 999999.9f;
	sound12Time = 999999.9f;
	eastWaveTime = 999999.9f;

	// ints
	numUnits = 0;
}


void BlackDog15Mission::Execute()
{
	_ASSERTMSG1(numUnits < 100, "numUnits = %i", numUnits);
	int i = 0;
	lastUser = user;
	user = GetPlayerHandle(); //assigns the player a handle every frame

	// SOE #1
	if (!startDone)
	{
		SetScrap(1,50);
		SetPilot(1,10);

		// don't do this part after the first shot
		startDone = TRUE;

		ClearObjectives();
		AddObjective("bd15001.otf", WHITE);

		sound1 = AudioMessage("bd15001.wav");
//#define DO_EXPLOSION
#ifdef DO_EXPLOSION
		sound7 = AudioMessage("bd15007.wav");
#endif
	}
#ifndef DO_EXPLOSION
	// SOE #1
	if (sound1 != NULL && IsAudioMessageDone(sound1))
	{
		sound1 = NULL;
		sound2Time = GetTime() + 20.0f;
	}

	if (!sound10Played && GetDistance(user, "chin_launch") < 300.0f)
	{
		sound10Played = TRUE;
		AudioMessage("bd15010.wav");
	}

	// SOE #2
	if (sound2Time < GetTime())
	{
		sound2Time = 999999.9f;
		sound2 = AudioMessage("bd15002.wav");

		Handle h;
		h = BuildObject("cvfigh", 2, "spawn_west_wave");
		units[numUnits++] = h;
		Goto(h, "path_west_wave");
		SetObjectiveOn(h);
	}

	if (sound2 != NULL && IsAudioMessageDone(sound2))
	{
		sound2 = NULL;
		sound3Time = GetTime() + 40.0f;
	}

	// SOE #3
	if (sound3Time < GetTime())
	{
		sound3Time = 999999.9f;
		sound3 = AudioMessage("bd15003.wav");

		Handle h;
		h = BuildObject("cvfigh", 2, "spawn_south_wave");
		units[numUnits++] = h;
		Goto(h, "path_south_wave");
		SetObjectiveOn(h);
		h = BuildObject("cvfigh", 2, "spawn_south_wave");
		units[numUnits++] = h;
		Goto(h, "path_south_wave");
		SetObjectiveOn(h);
		h = BuildObject("cvfigh", 2, "spawn_south_wave");
		units[numUnits++] = h;
		Goto(h, "path_south_wave");
		SetObjectiveOn(h);
		h = BuildObject("cvltnk", 2, "spawn_south_wave");
		units[numUnits++] = h;
		Goto(h, "path_south_wave");
		SetObjectiveOn(h);
		h = BuildObject("cvtnk", 2, "spawn_south_wave");
		units[numUnits++] = h;
		Goto(h, "path_south_wave");
		SetObjectiveOn(h);
		h = BuildObject("cvapc", 2, "spawn_south_wave");
		units[numUnits++] = h;
		Goto(h, "path_south_wave");
		SetObjectiveOn(h);
	}

	if (sound3 != NULL && IsAudioMessageDone(sound3))
	{
		sound3 = NULL;
		sound4Time = GetTime() + 120.0f;
	}

	// SOE #4
	if (sound4Time < GetTime())
	{
		sound4Time = 999999.9f;
		sound4 = AudioMessage("bd15004.wav");

		Handle h;
		h = BuildObject("cvapc", 2, "spawn_north_wave");
		units[numUnits++] = h;
		Goto(h, "path_north_wave");
		SetObjectiveOn(h);
		h = BuildObject("cvapc", 2, "spawn_north_wave");
		units[numUnits++] = h;
		Goto(h, "path_north_wave");
		SetObjectiveOn(h);
		h = BuildObject("cvapc", 2, "spawn_north_wave");
		units[numUnits++] = h;
		Goto(h, "path_north_wave");
		SetObjectiveOn(h);
		h = BuildObject("cvhtnk", 2, "spawn_north_wave");
		units[numUnits++] = h;
		Goto(h, "path_north_wave");
		SetObjectiveOn(h);
		h = BuildObject("cvtnk", 2, "spawn_north_wave");
		units[numUnits++] = h;
		Goto(h, "path_north_wave");
		SetObjectiveOn(h);
		h = BuildObject("cvtnk", 2, "spawn_north_wave");
		units[numUnits++] = h;
		Goto(h, "path_north_wave");
		SetObjectiveOn(h);
		h = BuildObject("cvtnk", 2, "spawn_north_wave");
		units[numUnits++] = h;
		Goto(h, "path_north_wave");
		SetObjectiveOn(h);
	}

	if (sound4 != NULL && IsAudioMessageDone(sound4))
	{
		sound4 = NULL;
		sound5Time = GetTime() + 180.0f;
	}

	// SOE #5
	if (sound5Time < GetTime())
	{
		sound5Time = 999999.9f;
		AudioMessage("bd15005.wav");

		Handle h;
		h = BuildObject("cvfigh", 2, "spawn_east_wave");
		units[numUnits++] = h;
		Goto(h, "path_east_wave");
		SetObjectiveOn(h);
		h = BuildObject("cvfigh", 2, "spawn_east_wave");
		units[numUnits++] = h;
		Goto(h, "path_east_wave");
		SetObjectiveOn(h);
		h = BuildObject("cvfigh", 2, "spawn_east_wave");
		units[numUnits++] = h;
		Goto(h, "path_east_wave");
		SetObjectiveOn(h);
		h = BuildObject("cvltnk", 2, "spawn_east_wave");
		units[numUnits++] = h;
		Goto(h, "path_east_wave");
		SetObjectiveOn(h);
		h = BuildObject("cvltnk", 2, "spawn_east_wave");
		units[numUnits++] = h;
		Goto(h, "path_east_wave");
		SetObjectiveOn(h);
		h = BuildObject("cvltnk", 2, "spawn_east_wave");
		units[numUnits++] = h;
		Goto(h, "path_east_wave");
		SetObjectiveOn(h);

		eastWaveTime = GetTime() + 60.0f;
	}

	if (eastWaveTime < GetTime())
	{
		eastWaveTime = 999999.9f;

		Handle h;
		h = BuildObject("cvltnk", 2, "spawn_east_wave");
		units[numUnits++] = h;
		Goto(h, "path_east_wave");
		SetObjectiveOn(h);
		h = BuildObject("cvltnk", 2, "spawn_east_wave");
		units[numUnits++] = h;
		Goto(h, "path_east_wave");
		SetObjectiveOn(h);
		h = BuildObject("cvhraz", 2, "spawn_east_wave");
		units[numUnits++] = h;
		Goto(h, "path_east_wave");
		SetObjectiveOn(h);
		h = BuildObject("cvhraz", 2, "spawn_east_wave");
		units[numUnits++] = h;
		Goto(h, "path_east_wave");
		SetObjectiveOn(h);
		h = BuildObject("cvfigh", 2, "spawn_east_wave");
		units[numUnits++] = h;
		Goto(h, "path_east_wave");
		SetObjectiveOn(h);
		h = BuildObject("cvfigh", 2, "spawn_east_wave");
		units[numUnits++] = h;
		Goto(h, "path_east_wave");
		SetObjectiveOn(h);

		sound6Time = GetTime() + 180.0f;
	}

	// SOE #6
	if (sound6Time < GetTime())
	{
		sound6Time = 999999.9f;
		AudioMessage("bd15006.wav");

		Handle h;
		h = BuildObject("cvhtnk", 2, "spawn_south_wave");
		units[numUnits++] = h;
		Goto(h, "path_south_wave");
		SetObjectiveOn(h);
		h = BuildObject("cvfigh", 2, "spawn_north_wave");
		units[numUnits++] = h;
		Goto(h, "path_north_wave");
		SetObjectiveOn(h);
		h = BuildObject("cvfigh", 2, "spawn_north_wave");
		units[numUnits++] = h;
		Goto(h, "path_north_wave");
		SetObjectiveOn(h);
		h = BuildObject("cvapc", 2, "spawn_west_wave");
		units[numUnits++] = h;
		Goto(h, "path_west_wave");
		SetObjectiveOn(h);
		h = BuildObject("cvapc", 2, "spawn_west_wave");
		units[numUnits++] = h;
		Goto(h, "path_west_wave");
		SetObjectiveOn(h);
		h = BuildObject("cvhaul", 2, "spawn_west_wave");
		units[numUnits++] = h;
		Goto(h, "path_west_wave");
		SetObjectiveOn(h);

		allUnitsSpawned = TRUE;
	}

	// SOE #7
	for (i = 0; i < numUnits && !wonLost; i++)
	{
		if (GetDistance(units[i], "chin_launch") < 100.0f)
		{
			sound11 = AudioMessage("bd15011.wav");
			wonLost = TRUE;
			break;
		}
	}

	if (sound11 != NULL && IsAudioMessageDone(sound11))
	{
		sound11 = NULL;
		sound12Time = GetTime() + 5.0f;
	}

	if (sound12Time < GetTime())
	{
		sound12Time = 999999.9f;
		sound12 = AudioMessage("bd15012.wav");
	}

	if (sound12 != NULL && IsAudioMessageDone(sound12))
	{
		sound12 = NULL;
		FailMission(GetTime(), "bd15lose.des");
	}

	// SOE #8
	if (allUnitsSpawned && !objective1Complete)
	{
		objective1Complete = TRUE;

		for (i = 0; i < numUnits; i++)
		{
			if (IsAlive(units[i]))
			{
				objective1Complete = FALSE;
				break;
			}
		}

		if (objective1Complete)
		{
			sound7 = AudioMessage("bd15007.wav");
			ClearObjectives();
			AddObjective("bd15001.otf", GREEN);
			AddObjective("bd15002.otf", WHITE);
		}
	}
#endif
	if (sound7 != NULL && IsAudioMessageDone(sound7))
	{
		sound7 = NULL;
		doingCountdown = TRUE;
		StartCockpitTimer(30, 10, 5);
		//explTime = GetTime() + 32.0f;
		//cameraTime = GetTime() + 30.0f;
		//sound8Time = GetTime() + 32.0f;
	}

	// SOE #9
	if (doingCountdown && GetCockpitTimer() <= 0 && !doingExplosion)
	{
		// hopefully, if the player get's caught in the explosion,
		// this success won't happen
		HideCockpitTimer();
		SucceedMission(GetTime() + 5.0, "bd15win.des");

		doingExplosion = TRUE;
		ColorFade_SetFade(1.0f, 0.5f, 255, 255, 255);
		if (useD3D & 4)
			MakeExplosion("spawn_explosion1", "xpltrso");
		else
			MakeExplosion("spawn_explosion1", "xpltrsp");
	}

	if (doingCountdown && GetCockpitTimer() <= 2 && !doingCamera)
	{
		float dist = GetDistance(user, "spawn_explosion1");
		//if (dist > 800.0f)
		{
			//sound9 = AudioMessage("bd15013.wav");
			// focus on the explosion
			CameraReady();
			CameraPathPath("camera_finale", 2400, 0, "spawn_explosion1");
			doingCamera = TRUE;
		}
	}
}