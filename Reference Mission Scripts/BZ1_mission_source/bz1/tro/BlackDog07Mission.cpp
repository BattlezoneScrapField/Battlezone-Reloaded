#include "GameCommon.h"
#include "AiCommon.h"
#include "AiMission.h"
#include "AiProcess.h"
#include "PowerUp.h"
#include "ScriptUtils.h"

/*
	BlackDog07Mission
*/
class BlackDog07Mission : public AiMission {
	DECLARE_RTIME(BlackDog07Mission)
public:
	BlackDog07Mission();
	~BlackDog07Mission();

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

				// waves spawned?
				wavesSpawned,

				// have we lost?
				lost, won,

				b_last;
		};
		bool b_array[7];
	};

	// floats
	union {
		struct {
			float
				sound1Time,
				sound2Time,
				sound3Time,
				waveDelay[2],
				annoyTime,
				f_last;
		};
		float f_array[6];
	};

	// handles
	union {
		struct {
			Handle
				// *** User stuff
				user,

				// *** Units
				mustDestroy[11],
				mustSave[3],
				waveUnits1[3],
				waveUnits2[8],
				
				h_last;
		};
		Handle h_array[26];
	};

	// integers
	union {
		struct {
			int
				// *** Sounds
				sound1, sound2, sound3,

				i_last;
		};
		int i_array[3];
	};
};

IMPLEMENT_RTIME(BlackDog07Mission)

BlackDog07Mission::BlackDog07Mission()
{
}

BlackDog07Mission::~BlackDog07Mission()
{
}

bool BlackDog07Mission::Load(file fp)
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

bool BlackDog07Mission::PostLoad(void)
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

bool BlackDog07Mission::Save(file fp)
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

void BlackDog07Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

void BlackDog07Mission::AddObject(Handle h)
{
}

void BlackDog07Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

void BlackDog07Mission::Setup()
{
	int i = 0;
	startDone = FALSE;
	objective1Complete = FALSE;
	objective2Complete = FALSE;
	objective3Complete = FALSE;
	wavesSpawned = TRUE;

	// units
	mustSave[0] = GetHandle("recycler");
	mustSave[1] = GetHandle("myfactory");
	mustSave[2] = GetHandle("my_hq");
	mustDestroy[0] = GetHandle("chin_recycler");
	mustDestroy[1] = GetHandle("chin_factory");
	mustDestroy[2] = GetHandle("chin_solar1");
	mustDestroy[3] = GetHandle("chin_solar2");
	mustDestroy[4] = GetHandle("chin_solar3");
	mustDestroy[5] = GetHandle("chin_tower1");
	mustDestroy[6] = GetHandle("chin_tower2");
	mustDestroy[7] = GetHandle("chin_tower3");
	mustDestroy[8] = GetHandle("chin_supply");
	mustDestroy[9] = GetHandle("chin_hq");
	mustDestroy[10] = GetHandle("chin_hangar");
	waveUnits1[0] = GetHandle("chin_scout1");
	waveUnits1[1] = GetHandle("chin_scout2");
	waveUnits1[2] = GetHandle("chin_scout3");
	waveUnits2[0] = GetHandle("chin_scout4");
	waveUnits2[1] = GetHandle("chin_scout5");
	waveUnits2[2] = GetHandle("chin_scout6");
	waveUnits2[3] = GetHandle("chin_ltnk1");
	waveUnits2[4] = GetHandle("chin_ltnk2");
	waveUnits2[5] = GetHandle("chin_tank1");
	waveUnits2[6] = GetHandle("chin_bomber1");
	waveUnits2[7] = GetHandle("chin_bomber2");

	// label the nav beacons
	Handle h = GetHandle("nav_mybase");
	SetName(h, "Black Dog Base");
	h = GetHandle("nav_chinbase");
	SetName(h, "Chinese Base");

	// sounds
	sound1 = NULL;
	sound2 = NULL;
	sound3 = NULL;

	// delays
	sound1Time = 999999.9f;
	sound2Time = 999999.9f;
	sound3Time = 999999.9f;
	waveDelay[0] = 999999.9f;
	waveDelay[1] = 999999.9f;
	annoyTime = 999999.9f;
}


void BlackDog07Mission::Execute()
{
	int i = 0;
	user = GetPlayerHandle(); //assigns the player a handle every frame

	if (!startDone)
	{
		SetAIP("bdmisn07.aip");
		SetScrap(1,8);
		SetPilot(1,10);

		// don't do this part after the first shot
		startDone = TRUE;

		sound1Time = GetTime() + 5.0f;
	}

	// sound1
	if (sound1Time < GetTime())
	{
		sound1Time = 999999.9f;
		sound1 = AudioMessage("bd07001.wav");
	}

	if (sound1 != NULL && IsAudioMessageDone(sound1))
	{
		sound1 = NULL;
		sound2Time = GetTime() + 1.0f;
	}

	// sound 2
	if (sound2Time < GetTime())
	{
		sound2Time = 999999.9f;
		sound2 = AudioMessage("bd07002.wav");
	}

	if (sound2 != NULL && IsAudioMessageDone(sound2))
	{
		sound2 = NULL;
		sound3Time = GetTime() + 2.0f;
	}

	// sound 3
	if (sound3Time < GetTime())
	{
		sound3Time = 999999.9f;
		sound3 = AudioMessage("bd07003.wav");
	}

	if (sound3 != NULL && IsAudioMessageDone(sound3))
	{
		sound3 = NULL;
		
		// set the objectives
		ClearObjectives();
		AddObjective("bd07001.otf", WHITE);
	}

	if (waveDelay[0] < GetTime())
	{
		waveDelay[0] = 999999.9f;
		waveDelay[1] = GetTime() + 30.0f;

		// get first wave to attack
		for (i = 0; i < 3; i++)
			Goto(waveUnits1[i], "attack_path1", 1);
	}

	if (waveDelay[1] < GetTime())
	{
		waveDelay[1] = 999999.9f;

		// get second wave to attack
		for (i = 0; i < 8; i++)
			Goto(waveUnits2[i], "attack_path2", 1);

		wavesSpawned = TRUE;
	}

	if (wavesSpawned && !objective1Complete)
	{
		objective1Complete = TRUE;
		for (i = 0; i < 3; i++)
		{
			if (IsAlive(waveUnits1[i]))
			{
				objective1Complete = FALSE;
				break;
			}
		}
		for (i = 0; i < 8; i++)
		{
			if (IsAlive(waveUnits2[i]))
			{
				objective1Complete = FALSE;
				break;
			}
		}

		if (objective1Complete)
		{
			ClearObjectives();
			AddObjective("bd07002.otf", WHITE);

			AudioMessage("bd07004.wav");

			annoyTime = GetTime() + 1.0f;
			int scrap = GetScrap(2);
			if (scrap < 40)
				SetScrap(2, 40);
		}
	}

	if (annoyTime < GetTime())
	{
		annoyTime = GetTime() + 5 * 60.0f;

		for (i = 0; i < 3; i++)
		{
			Handle h = BuildObject("cvfigh", 2, "annoy_1");
			Attack(h, user);
		}
		for (i = 0; i < 2; i++)
		{
			Handle h = BuildObject("cvltnk", 2, "annoy_1");
			Attack(h, user);
		}
	}

	// have we met all the goals?
	if (!won && !lost)
	{
		won = TRUE;
		for (int i = 0; i < 11; i++)
		{
			if (IsAlive(mustDestroy[i]))
			{
				won = FALSE;
				break;
			}
		}

		// have we won?
		if (won)
		{
			ClearObjectives();
			AddObjective("bd07002.otf", GREEN);
			SucceedMission(GetTime() + 1.0f, "bd07win.des");
		}
	}

	if (!lost && !won)
	{
		lost = TRUE;
		for (int i = 0; i < 3; i++)
		{
			if (GetHealth(mustSave[i]) > 0.0f)
			{
				lost = FALSE;
				break;
			}
		}

		// have we lost?
		if (lost)
		{
			FailMission(GetTime() + 1.0f, "bd07lose.des");
		}
	}
}