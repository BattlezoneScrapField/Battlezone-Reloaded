#include "GameCommon.h"
#include "AiCommon.h"
#include "AiMission.h"
#include "AiProcess.h"
#include "PowerUp.h"
#include "ScriptUtils.h"


char *randomUnits[10] = 
{
	"cvfigh",
	"cvfigh",
	"cvfigh",
	"cvfigh",
	"cvfigh",
	"cvltnk",
	"cvltnk",
	"cvtnk",
	"cvtnk",
	"cvrckt" 
};

/*
	BlackDog03Mission
*/
class BlackDog03Mission : public AiMission {
	DECLARE_RTIME(BlackDog03Mission)
public:
	BlackDog03Mission();
	~BlackDog03Mission();

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

				// objectives complete?
				objective1Complete,
				objective2Complete,
				objective3Complete,

				// sounds
				soundComplete[10],

				// stuff activated?
				activateStuff,

				// apc spawned?
				apcSpawned,
				triggerAmbush,

				// is the recycler on the initial path still?
				recyclerOnPath,
				recyclerDeployed,

				// first random attack spawned?
				firstRandomAttackDone,

				// sound8 played?
				sound8Played,

				// have we lost?
				lost, won,

				b_last;
		};
		bool b_array[23];
	};

	// floats
	union {
		struct {
			float
				sound1Delay,
				sound2Delay,
				sound3Delay,
				sound4Delay,
				randomDelay,
				spawnRecyclerAttackTime1,
				spawnRecyclerAttackTime2,
				spawnRecyclerAttackTime3,
				apcAttackTime,
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

				// *** Units
				recycler,
				navDelta,
				apc,
				killMeNow[2],
				geyser1,
				evilGuys[4],
								
				h_last;
		};
		Handle h_array[11];
	};

	// integers
	union {
		struct {
			int
				// *** Sounds
				soundHandle[10],

				i_last;
		};
		int i_array[10];
	};
};

IMPLEMENT_RTIME(BlackDog03Mission)

BlackDog03Mission::BlackDog03Mission()
{
}

BlackDog03Mission::~BlackDog03Mission()
{
}

bool BlackDog03Mission::Load(file fp)
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

bool BlackDog03Mission::PostLoad(void)
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

bool BlackDog03Mission::Save(file fp)
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

void BlackDog03Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

void BlackDog03Mission::AddObject(Handle h)
{
}

void BlackDog03Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

void BlackDog03Mission::Setup()
{
	int i = 0;
	startDone = FALSE;
	objective1Complete = FALSE;
	objective2Complete = FALSE;
	objective3Complete = FALSE;
	activateStuff = FALSE;
	apcSpawned = FALSE;
	firstRandomAttackDone = FALSE;
	recyclerOnPath = FALSE;
	recyclerDeployed = FALSE;
	sound8Played = FALSE;
	triggerAmbush = FALSE;

	for (i = 0; i < 10; i++)
	{
		soundComplete[i] = FALSE;
		soundHandle[i] = NULL;
	}

	// handles
	recycler = GetHandle("recycler");
	navDelta = GetHandle("nav_delta");
	SetName(navDelta, "Nav Delta");
	apc = NULL;
	killMeNow[0] = GetHandle("bobcat_kill_me_now");
	killMeNow[1] = GetHandle("scout_kill_me_now");
	geyser1 = GetHandle("geyser1");
	evilGuys[0] = GetHandle("evil_scout1");
	evilGuys[1] = GetHandle("evil_scout2");
	evilGuys[2] = GetHandle("evil_scout3");
	//evilGuys[3] = GetHandle("evil_scout4");
	//evilGuys[2] = GetHandle("evil_scout5");
	evilGuys[3] = GetHandle("evil_tank1");

	// delays
	sound1Delay = 999999.9f;
	sound2Delay = 999999.9f;
	sound3Delay = 999999.9f;
	sound4Delay = 999999.9f;
	randomDelay = 999999.9f;
	spawnRecyclerAttackTime1 = 999999.9f;
	spawnRecyclerAttackTime2 = 999999.9f;
	spawnRecyclerAttackTime3 = 999999.9f;
	apcAttackTime = 999999.9f;
}


void BlackDog03Mission::Execute()
{
	int i = 0;
	user = GetPlayerHandle(); //assigns the player a handle every frame

	if (!startDone)
	{
		SetScrap(1,8);
		SetPilot(1,10);

		// don't do this part after the first shot
		startDone = TRUE;

		ClearObjectives();
		AddObjective("bd03001.otf", WHITE);

		spawnRecyclerAttackTime2 = GetTime() + 7 * 60.0f;
		spawnRecyclerAttackTime3 = GetTime() + 11 * 60.0f;

		apcAttackTime = GetTime() + 9 * 60.0f;
		sound4Delay = GetTime() + 7 * 60.0f;
		randomDelay = GetTime() + 10 * 60.0f;

		// get the evil guys to be cloaked
		for (i = 0; i < 4; i++)
			SetCloaked(evilGuys[i]);

		SetCloaked(GetHandle("evil_scout4"));
		SetCloaked(GetHandle("evil_scout5"));
	}

	if (!soundComplete[0])
	{
		if (soundHandle[0] == NULL)
		{
			// start the sound
			soundHandle[0] = AudioMessage("bd03001.wav");

			CameraReady();
		}

		CameraPath("camera_intro", 1000, 0, user);

		if (CameraCancelled())
		{
			StopAudioMessage(soundHandle[0]);
		}

		if (IsAudioMessageDone(soundHandle[0]))
		{
			// complete
			soundHandle[0] = NULL;
			soundComplete[0] = TRUE;

			CameraFinish();
		}
	}

	if (soundComplete[0] && !soundComplete[1])
	{
		if (soundHandle[1] == NULL)
		{
			// start the sound
			soundHandle[1] = AudioMessage("bd03002.wav");

			CameraReady();

			// get the recycler moving
			Goto(recycler, "path_recycler_travel", 1);
			recyclerOnPath = TRUE;
			
			// get the "excort" to follow
			Follow(killMeNow[0], recycler, 1);
			Follow(killMeNow[1], recycler, 1);
		}

		CameraPath("camera_recycler", 400, 200, recycler);

		if (CameraCancelled())
		{
			StopAudioMessage(soundHandle[1]);
		}
		if (IsAudioMessageDone(soundHandle[1]))
		{
			// complete
			soundHandle[1] = NULL;
			soundComplete[1] = TRUE;

			CameraFinish();

			// remove the stuff
			RemoveObject(killMeNow[0]);
			RemoveObject(killMeNow[1]);

			sound1Delay = GetTime() + 60.0f;
		}
	}

	if (recyclerOnPath && isAtEndOfPath(recycler, "path_recycler_travel"))
	{
		recyclerOnPath = FALSE;
		Goto(recycler, geyser1, 1);

		Handle t1 = BuildObject("cvturr", 2, "spawn_turret_1");
		Handle t2 = BuildObject("cvturr", 2, "spawn_turret_2");
		Handle h = BuildObject("cvfigh", 2, "spawn_turret_guard1");
		SetCloaked(h);
		Defend2(h, t1);
		h = BuildObject("cvfigh", 2, "spawn_turret_guard1");
		SetCloaked(h);
		Defend2(h, t2);
		h = BuildObject("cvfigh", 2, "spawn_turret_guard2");
		SetCloaked(h);
		Defend2(h, t1);
		h = BuildObject("cvfigh", 2, "spawn_turret_guard2");
		SetCloaked(h);
		Defend2(h, t2);
	}

	if (!recyclerDeployed && isDeployed(recycler))
	{
		recyclerDeployed = TRUE;
		//BuildObject("bvscav", 1, "spawn_scav");
		//BuildObject("bvturr", 1, "spawn_turret");
		spawnRecyclerAttackTime1 = GetTime() + 30.0f;
	}

	// recycler attack
	if (spawnRecyclerAttackTime1 < GetTime())
	{
		spawnRecyclerAttackTime1 = 999999.9f;

		Handle h = BuildObject("cvfigh", 2, "spawn_recycler_attack");
		Attack(h, recycler, 1);
		h = BuildObject("cvfigh", 2, "spawn_recycler_attack");
		Attack(h, recycler, 1);
	}

	if (spawnRecyclerAttackTime2 < GetTime())
	{
		spawnRecyclerAttackTime2 = 999999.9f;

		Handle h = BuildObject("cvfigh", 2, "spawn_recycler_attack");
		SetCloaked(h);
		Goto(h, "path_recycler_attack",0);
		h = BuildObject("cvfigh", 2, "spawn_recycler_attack");
		SetCloaked(h);
		Goto(h, "path_recycler_attack",0);
		h = BuildObject("cvfigh", 2, "spawn_recycler_attack");
		SetCloaked(h);
		Goto(h, "path_recycler_attack",0);
		h = BuildObject("cvtnk", 2, "spawn_recycler_attack");
		SetCloaked(h);
		Goto(h, "path_recycler_attack",0);
		h = BuildObject("cvtnk", 2, "spawn_recycler_attack");
		SetCloaked(h);
		Goto(h, "path_recycler_attack",0);
	}

	if (spawnRecyclerAttackTime3 < GetTime())
	{
		spawnRecyclerAttackTime3 = 999999.9f;

		Handle h = BuildObject("cvfigh", 2, "spawn_recycler_attack");
		Goto(h, "path_recycler_attack", 1);
		h = BuildObject("cvfigh", 2, "spawn_recycler_attack");
		Goto(h, "path_recycler_attack", 1);
	}

	if (soundComplete[1] && !activateStuff)
	{
		activateStuff = TRUE;
#if 0
		// get the enemies into hunt mode
		for (i = 0; i < 4; i++)
			Attack(evilGuys[i], user);
#endif
	}

	if (sound1Delay < GetTime() && !soundComplete[2])
	{
		if (soundHandle[2] == NULL)
		{
			// start the sound
			soundHandle[2] = AudioMessage("bd03003.wav");

		}

		if (IsAudioMessageDone(soundHandle[2]))
		{
			// complete
			soundHandle[2] = NULL;
			soundComplete[2] = TRUE;

			sound1Delay = 999999.9f;
			sound2Delay = GetTime() + 30.0f;
		}
	}

	if (sound2Delay < GetTime() && !soundComplete[3])
	{
		if (soundHandle[3] == NULL)
		{
			// start the sound
			soundHandle[3] = AudioMessage("bd03004.wav");

		}

		if (IsAudioMessageDone(soundHandle[3]))
		{
			// complete
			soundHandle[3] = NULL;
			soundComplete[3] = TRUE;

			sound2Delay = 999999.9f;
			sound3Delay = GetTime() + 10.0f;

			ClearObjectives();
			AddObjective("bd03001.otf", WHITE);
			AddObjective("bd03002.otf", WHITE);
		}
	}

	if (sound3Delay < GetTime() && !soundComplete[4])
	{
		if (soundHandle[4] == NULL)
		{
			// start the sound
			soundHandle[4] = AudioMessage("bd03005.wav");

		}

		if (IsAudioMessageDone(soundHandle[4]))
		{
			// complete
			soundHandle[4] = NULL;
			soundComplete[4] = TRUE;

			sound3Delay = 999999.9f;
		}
	}

	// when the player reaches the reycler by the nav
	if (GetDistance(user, recycler) < 75.0 && !(objective1Complete && objective2Complete))
	{
		objective1Complete = TRUE;
		objective2Complete = TRUE;

		// play the message
		AudioMessage("bd03006.wav");

		ClearObjectives();
		AddObjective("bd03001.otf", GREEN);
		AddObjective("bd03002.otf", GREEN);
	}

	if (sound4Delay < GetTime() && !soundComplete[5])
	{
		if (soundHandle[5] == NULL)
		{
			// start the sound
			soundHandle[5] = AudioMessage("bd03007.wav");

			ClearObjectives();
			AddObjective("bd03003.otf", WHITE);
		}

		if (IsAudioMessageDone(soundHandle[5]))
		{
			// complete
			soundHandle[5] = NULL;
			soundComplete[5] = TRUE;

			sound4Delay = 999999.9f;

			apc = BuildObject("bvapcb", 1, "spawn_apc");
			Goto(apc, "path_apc_travel", 1);
			SetObjectiveOn(apc);
			Handle h = BuildObject("bvraz", 1, "spawn_apc");
			Defend2(h, apc);
			h = BuildObject("bvraz", 1, "spawn_apc");
			Defend2(h, apc);
			apcSpawned = TRUE;
		}
	}

	if (apcAttackTime < GetTime())
	{
		apcAttackTime = 999999.9f;
		Handle h;
		h = BuildObject("cvfighf", 2, "spawn_attack_apc");
		Attack(h, apc);
	}

	if (randomDelay < GetTime())
	{
		randomDelay = GetTime() + 90.0f; // 1.5 minutes later

		// spawn random units
		Handle h;
		h = BuildObject(randomUnits[rand() % 10], 2, "spawn_random_1");
		Attack(h, apc);
		h = BuildObject(randomUnits[rand() % 10], 2, "spawn_random_2");
		Hunt(h, 1);
		h = BuildObject(randomUnits[rand() % 10], 2, "spawn_random_3");
		Attack(h, apc);
		h = BuildObject(randomUnits[rand() % 10], 2, "spawn_random_4");
		Hunt(h, 1);
	}

	// has the apc been damaged yet?
	if (apcSpawned && GetHealth(apc) < 0.98 && !sound8Played)
	{
		AudioMessage("bd03008.wav");
		sound8Played = TRUE;
	}

	// has the apc arrived safely?
	if (apcSpawned && GetDistance(apc, navDelta) < 75.0f && !won && !lost)
	{
		won = TRUE;
		soundHandle[7] = AudioMessage("bd03009.wav");
	}

	if (apcSpawned && GetDistance(apc, "trigger_ambush") < 50.0f && !triggerAmbush)
	{
		static char *choices[3] = { "cvfigh", "cvltnk", "cvtnk" };
		triggerAmbush = TRUE;

		Handle h1 = BuildObject(choices[rand() % 3], 2, "spawn_recycler_attack");
		SetCloaked(h1);
		Follow(h1, apc, 0);
		Handle h2 = BuildObject(choices[rand() % 3], 2, "spawn_recycler_attack");
		SetCloaked(h2);
		Follow(h2, apc, 0);
	}

	if (!soundComplete[7] && soundHandle[7] != NULL)
	{
		if (IsAudioMessageDone(soundHandle[7]))
		{
			soundComplete[7] = TRUE;
			soundHandle[7] = NULL;
			SucceedMission(GetTime() + 2.0f, "bd03win.des");
		}
	}

	// is the recycler dead?
	if (GetHealth(recycler) <= 0.0f && !lost && !won)
	{
		lost = TRUE;
		soundHandle[6] = AudioMessage("bd03012.wav");
	}

	if (!soundComplete[6] && soundHandle[6] != NULL)
	{
		if (IsAudioMessageDone(soundHandle[6]))
		{
			soundComplete[6] = TRUE;
			soundHandle[6] = NULL;
			FailMission(GetTime() + 2.0f, "bd03lsea.des");
		}
	}

	// is the apc dead?
	if (apcSpawned && GetHealth(apc) <= 0.0f && !lost && !won)
	{
		soundHandle[8] = AudioMessage("bd03010.wav");
		lost = TRUE;
	}

	if (!soundComplete[8] && soundHandle[8] != NULL)
	{
		if (IsAudioMessageDone(soundHandle[8]))
		{
			soundComplete[8] = TRUE;
			soundHandle[8] = NULL;
			soundHandle[9] = AudioMessage("bd03011.wav");
		}
	}

	if (!soundComplete[9] && soundHandle[9] != NULL)
	{
		if (IsAudioMessageDone(soundHandle[9]))
		{
			soundComplete[9] = TRUE;
			soundHandle[9] = NULL;
			FailMission(GetTime() + 2.0f, "bd03lseb.des");
		}
	}
}