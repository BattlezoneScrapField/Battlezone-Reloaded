

#include "AiMission.h"
#include "ScriptUtils.h"
#include "AudioMessage.h"


#define WIN_TRIGGER_DISTANCE_APC_TO_RECYCLER 75.0f

const char *randomUnits[10] =
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
			BZHandle
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
		BZHandle h_array[11];
	};

	// integers
	union {
		struct {
			int32_t
				// *** Sounds
				soundHandle[10],

				i_last;
		};
		int32_t i_array[10];
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

void BlackDog03Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

void BlackDog03Mission::AddObject(BZHandle h)
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
	startDone = BZFALSE;
	objective1Complete = BZFALSE;
	objective2Complete = BZFALSE;
	objective3Complete = BZFALSE;
	activateStuff = BZFALSE;
	apcSpawned = BZFALSE;
	firstRandomAttackDone = BZFALSE;
	recyclerOnPath = BZFALSE;
	recyclerDeployed = BZFALSE;
	sound8Played = BZFALSE;
	triggerAmbush = BZFALSE;

	for (i = 0; i < 10; i++)
	{
		soundComplete[i] = BZFALSE;
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
	
	//TEST CODE SO I CAN BEAT THIS LEVEL

	

	if (navDelta)
	{
		SetCurHealth(navDelta, 10000.0f);
		SetMaxHealth(navDelta, 10000.0f);

	}

	//TEST CODE TO DETECT BROKEN data
	/*
	if (apc)
	{
		SetCurHealth(apc, 10000.0f);
		SetMaxHealth(apc, 10000.0f);

	}

	
	if (!(navDelta = GetHandle("nav_delta")) )// (check to see has become NULL for some reason)
	{
		Trace("WARNING: Save Data is corrupt\n");
	}

	*/

	if (!startDone)
	{
		SetScrap(1,8);
		SetPilot(1,10);

		// don't do this part after the first shot
		startDone = BZTRUE;

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
		if (soundHandle[0] == BZINVALIDHANDLE)
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
			soundComplete[0] = BZTRUE;

			CameraFinish();
		}
	}

	if (soundComplete[0] && !soundComplete[1])
	{
		if (soundHandle[1] == BZINVALIDHANDLE)
		{
			// start the sound
			soundHandle[1] = AudioMessage("bd03002.wav");

			CameraReady();

			// get the recycler moving
			Goto(recycler, "path_recycler_travel", 1);
			recyclerOnPath = BZTRUE;
			
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
			soundComplete[1] = BZTRUE;

			CameraFinish();

			// remove the stuff
			RemoveObject(killMeNow[0]);
			RemoveObject(killMeNow[1]);

			sound1Delay = GetTime() + 60.0f;
		}
	}

	if (recyclerOnPath && isAtEndOfPath(recycler, "path_recycler_travel"))
	{
		recyclerOnPath = BZFALSE;
		Goto(recycler, geyser1, 1);

		BZHandle t1 = BuildObject("cvturr", 2, "spawn_turret_1");
		BZHandle t2 = BuildObject("cvturr", 2, "spawn_turret_2");
		BZHandle h = BuildObject("cvfigh", 2, "spawn_turret_guard1");
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
		recyclerDeployed = BZTRUE;
		BuildObject("bvscav", 1, "spawn_scav");
		BZHandle H=BuildObject("bvturr", 1, "spawn_turret");
		Defend2(H, recycler, 0);
		H=BuildObject("bvturr", 1, H);
		Defend2(H, recycler, 0);
		AddScrap(1, 24);
		spawnRecyclerAttackTime1 = GetTime() + 30.0f;
	}

	// recycler attack
	if (spawnRecyclerAttackTime1 < GetTime())
	{
		spawnRecyclerAttackTime1 = 999999.9f;

		BZHandle h = BuildObject("cvfigh", 2, "spawn_recycler_attack");
		Attack(h, recycler, 1);
		h = BuildObject("cvfigh", 2, "spawn_recycler_attack");
		Attack(h, recycler, 1);
	}

	if (spawnRecyclerAttackTime2 < GetTime())
	{
		spawnRecyclerAttackTime2 = 999999.9f;

		BZHandle h = BuildObject("cvfigh", 2, "spawn_recycler_attack");
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

		BZHandle h = BuildObject("cvfigh", 2, "spawn_recycler_attack");
		Goto(h, "path_recycler_attack", 1);
		h = BuildObject("cvfigh", 2, "spawn_recycler_attack");
		Goto(h, "path_recycler_attack", 1);
	}

	if (soundComplete[1] && !activateStuff)
	{
		activateStuff = BZTRUE;
	}

	if (sound1Delay < GetTime() && !soundComplete[2])
	{
		if (soundHandle[2] == BZINVALIDHANDLE)
		{
			// start the sound
			soundHandle[2] = AudioMessage("bd03003.wav");

		}

		if (IsAudioMessageDone(soundHandle[2]))
		{
			// complete
			soundHandle[2] = NULL;
			soundComplete[2] = BZTRUE;

			sound1Delay = 999999.9f;
			sound2Delay = GetTime() + 30.0f;
		}
	}

	if (sound2Delay < GetTime() && !soundComplete[3])
	{
		if (soundHandle[3] == BZINVALIDHANDLE)
		{
			// start the sound
			soundHandle[3] = AudioMessage("bd03004.wav");

		}

		if (IsAudioMessageDone(soundHandle[3]))
		{
			// complete
			soundHandle[3] = NULL;
			soundComplete[3] = BZTRUE;

			sound2Delay = 999999.9f;
			sound3Delay = GetTime() + 10.0f;

			ClearObjectives();
			AddObjective("bd03001.otf", WHITE);
			AddObjective("bd03002.otf", WHITE);
		}
	}

	if (sound3Delay < GetTime() && !soundComplete[4])
	{
		if (soundHandle[4] == BZINVALIDHANDLE)
		{
			// start the sound
			soundHandle[4] = AudioMessage("bd03005.wav");

		}

		if (IsAudioMessageDone(soundHandle[4]))
		{
			// complete
			soundHandle[4] = NULL;
			soundComplete[4] = BZTRUE;

			sound3Delay = 999999.9f;
		}
	}

	// when the player reaches the reycler by the nav
	if (GetDistance(user, recycler) < 75.0 && !(objective1Complete && objective2Complete))
	{
		objective1Complete = BZTRUE;
		objective2Complete = BZTRUE;

		// play the message
		AudioMessage("bd03006.wav");

		ClearObjectives();
		AddObjective("bd03001.otf", GREEN);
		AddObjective("bd03002.otf", GREEN);
	}

	if (sound4Delay < GetTime() && !soundComplete[5])
	{
		if (soundHandle[5] == BZINVALIDHANDLE)
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
			soundComplete[5] = BZTRUE;

			sound4Delay = 999999.9f;

			apc = BuildObject("bvapcb", 1, "spawn_apc");
			Goto(apc, "path_apc_travel", 1);
			SetObjectiveOn(apc);
			BZHandle h = BuildObject("bvraz", 1, "spawn_apc");
			Defend2(h, apc, 0);
			h = BuildObject("bvraz", 1, "spawn_apc");
			Defend2(h, apc, 0);
			apcSpawned = BZTRUE;
		}
	}

	if (apcAttackTime < GetTime())
	{
		apcAttackTime = 999999.9f;
		BZHandle h;
		h = BuildObject("cvfighf", 2, "spawn_attack_apc");
		Attack(h, apc);
	}

	if (randomDelay < GetTime())
	{
		randomDelay = GetTime() + 90.0f; // 1.5 minutes later

		// spawn random units
		BZHandle h;
		h = BuildObject(randomUnits[rand() % 10], 2, "spawn_random_1");
		Follow(h, apc);
		h = BuildObject(randomUnits[rand() % 10], 2, "spawn_random_2");
		Follow(h, apc);
		h = BuildObject(randomUnits[rand() % 10], 2, "spawn_random_3");
		Follow(h, apc);
		h = BuildObject(randomUnits[rand() % 10], 2, "spawn_random_4");
		Follow(h, apc);
	}

	// has the apc been damaged yet?
	if (apcSpawned && GetHealth(apc) < 0.98 && !sound8Played)
	{
		AudioMessage("bd03008.wav");
		sound8Played = BZTRUE;
	}

	// has the apc arrived safely?

	float distanceFromRecycler = GetDistance(apc, navDelta);


	if ((apcSpawned) && (distanceFromRecycler< WIN_TRIGGER_DISTANCE_APC_TO_RECYCLER) && (!won) && (!lost))
	{
		won = BZTRUE;
		soundHandle[7] = AudioMessage("bd03009.wav");
	}

	if (apcSpawned && GetDistance(apc, "trigger_ambush") < 50.0f && !triggerAmbush)
	{
		static const char *choices[3] = { "cvfigh", "cvltnk", "cvtnk" };
		triggerAmbush = BZTRUE;

		BZHandle h1 = BuildObject(choices[rand() % 3], 2, "spawn_recycler_attack");
		SetCloaked(h1);
		Follow(h1, apc, 0);
		BZHandle h2 = BuildObject(choices[rand() % 3], 2, "spawn_recycler_attack");
		SetCloaked(h2);
		Follow(h2, apc, 0);
	}

	if (!soundComplete[7] && soundHandle[7] != BZINVALIDHANDLE)
	{
		if (IsAudioMessageDone(soundHandle[7]))
		{
			soundComplete[7] = BZTRUE;
			soundHandle[7] = NULL;
			SucceedMission(GetTime() + 2.0f, "bd03win.des");
		}
	}

	// is the recycler dead?
	if (GetHealth(recycler) <= 0.0f && !lost && !won)
	{
		lost = BZTRUE;
		soundHandle[6] = AudioMessage("bd03012.wav");
	}

	if (!soundComplete[6] && soundHandle[6] != BZINVALIDHANDLE)
	{
		if (IsAudioMessageDone(soundHandle[6]))
		{
			soundComplete[6] = BZTRUE;
			soundHandle[6] = NULL;
			FailMission(GetTime() + 2.0f, "bd03lsea.des");
		}
	}

	// is the apc dead?
	if (apcSpawned && GetHealth(apc) <= 0.0f && !lost && !won)
	{
		soundHandle[8] = AudioMessage("bd03010.wav");
		lost = BZTRUE;
	}

	if (!soundComplete[8] && soundHandle[8] != BZINVALIDHANDLE)
	{
		if (IsAudioMessageDone(soundHandle[8]))
		{
			soundComplete[8] = BZTRUE;
			soundHandle[8] = NULL;
			soundHandle[9] = AudioMessage("bd03011.wav");
		}
	}

	if (!soundComplete[9] && soundHandle[9] != BZINVALIDHANDLE)
	{
		if (IsAudioMessageDone(soundHandle[9]))
		{
			soundComplete[9] = BZTRUE;
			soundHandle[9] = NULL;
			FailMission(GetTime() + 2.0f, "bd03lseb.des");
		}
	}
}

const std::set<PrjID>& BlackDog03Mission::GetPreloadGameObjects()
{
	static std::set<PrjID> retval = AiMission::PrjIDFromStrings(
	{ "cvturr", "cvfigh", "cvtnk", "cvltnk", "cvrckt", 
	"bvscav", "bvturr", "bvapcb", "bvraz", "cvfighf" }
	);
	return retval;
}
