

#include "AiMission.h"
#include "ScriptUtils.h"
#include "ColorFade.h"
#include "AudioMessage.h"

/*
	BlackDog15Mission
*/

class BlackDog15Mission : public AiMission {
	DECLARE_RTIME(BlackDog15Mission)
public:
	BlackDog15Mission();
	~BlackDog15Mission();

	virtual bool Load(file fp) override;
	virtual bool PostLoad(void) override;
	virtual bool Save(file fp) override;

	virtual void Update(void) override;

	virtual void AddObject(GameObject *gameObj) override;

	virtual const std::set<PrjID>& GetPreloadGameObjects() override;
private:
	void Setup();
	void Execute();
	void AddObject(BZHandle h);

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
			BZHandle
				// *** User stuff
				user,
				lastUser,
				
				// *** Units
				intro1, intro2,
				units[100],
				
				// nav beacons
				
				h_last;
		};
		BZHandle h_array[104];
	};

	// integers
	union {
		struct {
			int32_t
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
		int32_t i_array[8];
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
	if (!getFriends()->HasNetPurchased(ENetPurchaseType::troExpansion))
		return false;
	if (missionSave)
	{
		int i;

		// init bools
		int b_count = &b_last - b_array;
		assert(b_count == SIZEOF(b_array));
		for (i = 0; i < b_count; i++)
			b_array[i] = false;

		// init floats
		int f_count = &f_last - f_array;
		assert(f_count == SIZEOF(f_array));
		for (i = 0; i < f_count; i++)
			f_array[i] = 99999.0f;

		// init handles
		int h_count = &h_last - h_array;
		assert(h_count == SIZEOF(h_array));
		for (i = 0; i < h_count; i++)
			h_array[i] = 0;

		// init ints
		int i_count = &i_last - i_array;
		assert(i_count == SIZEOF(i_array));
		for (i = 0; i < i_count; i++)
			i_array[i] = 0;

		Setup();
		return AiMission::Load(fp);
	}

	bool ret = true;

	// bools
	int b_count = &b_last - b_array;
	assert(b_count == SIZEOF(b_array));
	ret = ret && in(fp, b_array, sizeof(b_array));

	// floats
	int f_count = &f_last - f_array;
	assert(f_count == SIZEOF(f_array));
	ret = ret && in(fp, f_array, sizeof(f_array));

	// Handles
	int h_count = &h_last - h_array;
	assert(h_count == SIZEOF(h_array));
	ret = ret && in(fp, h_array, sizeof(h_array));

	// ints
	int i_count = &i_last - i_array;
	assert(i_count == SIZEOF(i_array));
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
	assert(b_count == SIZEOF(b_array));
	ret = ret && out(fp, b_array, sizeof(b_array), "b_array");

	// floats
	int f_count = &f_last - f_array;
	assert(f_count == SIZEOF(f_array));
	ret = ret && out(fp, f_array, sizeof(f_array), "f_array");

	// Handles
	int h_count = &h_last - h_array;
	assert(h_count == SIZEOF(h_array));
	ret = ret && out(fp, h_array, sizeof(h_array), "h_array");

	// ints
	int i_count = &i_last - i_array;
	assert(i_count == SIZEOF(i_array));
	ret = ret && out(fp, i_array, sizeof(i_array), "i_array");

	ret = ret && AiMission::Save(fp);
	return ret;
}

void BlackDog15Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

void BlackDog15Mission::AddObject(BZHandle h)
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
	startDone = BZFALSE;
	wonLost = BZFALSE;
	objective1Complete = BZFALSE;
	objective2Complete = BZFALSE;
	objective3Complete = BZFALSE;
	sound10Played = BZFALSE;
	allUnitsSpawned = BZFALSE;
	doingCamera = BZFALSE;
	doingExplosion = BZFALSE;
	doingCountdown = BZFALSE;
	
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
	int i = 0;
	lastUser = user;
	user = GetPlayerHandle(); //assigns the player a handle every frame
	int lpad= GetHandle("launch");
	AddHealth(lpad,10000);
	
	// SOE #1
	if (!startDone)
	{
		SetScrap(1,50);
		SetPilot(1,10);

		// don't do this part after the first shot
		startDone = BZTRUE;

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
	if (sound1 != BZINVALIDHANDLE && IsAudioMessageDone(sound1))
	{
		sound1 = BZINVALIDHANDLE;
		sound2Time = GetTime() + 20.0f;
	}

	if (!sound10Played && GetDistance(user, "chin_launch") < 300.0f)
	{
		sound10Played = BZTRUE;
		AudioMessage("bd15010.wav");
	}

	// SOE #2
	if (sound2Time < GetTime())
	{
		sound2Time = 999999.9f;
		sound2 = AudioMessage("bd15002.wav");

		BZHandle h;
		h = BuildObject("cvfigh", 2, "spawn_west_wave");
		units[numUnits++] = h;
		Goto(h, "path_west_wave");
		SetObjectiveOn(h);
	}

	if (sound2 != BZINVALIDHANDLE && IsAudioMessageDone(sound2))
	{
		sound2 = BZINVALIDHANDLE;
		sound3Time = GetTime() + 40.0f;
	}

	// SOE #3
	if (sound3Time < GetTime())
	{
		sound3Time = 999999.9f;
		sound3 = AudioMessage("bd15003.wav");

		BZHandle h;
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

	if (sound3 != BZINVALIDHANDLE && IsAudioMessageDone(sound3))
	{
		sound3 = BZINVALIDHANDLE;
		sound4Time = GetTime() + 120.0f;
	}

	// SOE #4
	if (sound4Time < GetTime())
	{
		sound4Time = 999999.9f;
		sound4 = AudioMessage("bd15004.wav");

		BZHandle h;
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

	if (sound4 != BZINVALIDHANDLE && IsAudioMessageDone(sound4))
	{
		sound4 = BZINVALIDHANDLE;
		sound5Time = GetTime() + 180.0f;
	}

	// SOE #5
	if (sound5Time < GetTime())
	{
		sound5Time = 999999.9f;
		AudioMessage("bd15005.wav");

		BZHandle h;
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

		BZHandle h;
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

		BZHandle h;
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

		allUnitsSpawned = BZTRUE;
	}

	// SOE #7
	for (i = 0; i < numUnits && !wonLost; i++)
	{
		if (GetDistance(units[i], "chin_launch") < 100.0f)
		{
			sound11 = AudioMessage("bd15011.wav");
			wonLost = BZTRUE;
			break;
		}
	}

	if (sound11 != BZINVALIDHANDLE && IsAudioMessageDone(sound11))
	{
		sound11 = BZINVALIDHANDLE;
		sound12Time = GetTime() + 5.0f;
	}

	if (sound12Time < GetTime())
	{
		sound12Time = 999999.9f;
		sound12 = AudioMessage("bd15012.wav");
	}

	if (sound12 != BZINVALIDHANDLE && IsAudioMessageDone(sound12))
	{
		sound12 = BZINVALIDHANDLE;
		FailMission(GetTime(), "bd15lose.des");
	}

	// SOE #8
	if (allUnitsSpawned && !objective1Complete)
	{
		objective1Complete = BZTRUE;

		for (i = 0; i < numUnits; i++)
		{
			if (IsAlive(units[i]))
			{
				objective1Complete = BZFALSE;
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
	if (sound7 != BZINVALIDHANDLE && IsAudioMessageDone(sound7))
	{
		sound7 = BZINVALIDHANDLE;
		doingCountdown = BZTRUE;
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
		SucceedMission(GetTime() + 5.0f, "bd15win.des");

		doingExplosion = BZTRUE;
		ColorFade_SetFade(1.0f, 0.5f, 255, 255, 255);
		// using large/AGP assets
		// (alternative was "xpltrsp")
		MakeExplosion("spawn_explosion1", "xpltrso");
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
			doingCamera = BZTRUE;
		}
	}
}

const std::set<PrjID>& BlackDog15Mission::GetPreloadGameObjects()
{
	static std::set<PrjID> retval = AiMission::PrjIDFromStrings(
	{ "cvapc", "cvfigh", "cvhaul", "cvltnk", "cvtnk", "cvapc", 
	"cvhtnk", "cvhraz" }
	);
	return retval;
}
