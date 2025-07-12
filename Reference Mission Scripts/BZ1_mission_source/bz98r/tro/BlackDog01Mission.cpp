

#include "AiMission.h"
#include "ScriptUtils.h"
#include "AudioMessage.h"

/*
	BlackDog01Mission
*/

// messages
#define NUM_MESSAGES	4
#define BD01002 0
#define BD01003 1
#define BD01004 2
#define BD01005 3


class BlackDog01Mission : public AiMission {
	DECLARE_RTIME(BlackDog01Mission)
public:
	BlackDog01Mission();
	~BlackDog01Mission();

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
	void resetObjectives();

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
				cameraReady, cameraComplete[2],
				
				// have we been called to the beacon?
				scavengersCreated, 

				// sounds
				soundStarted[NUM_MESSAGES], soundPlayed[NUM_MESSAGES],

				// beacon
				beaconSpawned1, beaconSpawned2,

				// ambush is retreating
				ambushRetreat,

				// waves
				wave1Ready, wave2Ready,

				b_last;
		};
		bool b_array[13 + 2 * NUM_MESSAGES];
	};

	// floats
	union {
		struct {
			float
				// time when the camera will stop
				wave2Delay,
				delayTime1,
				delayTime2,
				delayTime3,
				sound8Time,
				sound9Time,
				sound6Time,
				sound7Time,
				f_last;
		};
		float f_array[8];
	};

	// handles
	union {
		struct {
			BZHandle
				// the user
				user,

				// recycler
				recycler,

				// wingmen
				wingman1, wingman2,

				// scavenger(s) that the player creates
				scavengers[2],

				// bad guys
				badGuy1_ambush, badGuy2_ambush,
				badGuy1_wave1, badGuy2_wave1, badGuy3_wave1, badGuy4_wave1,
				badGuy1_wave2, badGuy2_wave2, badGuy3_wave2, badGuy4_wave2, badGuy5_wave2,

				// beacon
				beacon, 

				// place holder
				h_last;
		};
		BZHandle h_array[18];
	};

	// integers
	union {
		struct {
			int32_t
				// sound handles
				soundHandle[NUM_MESSAGES],
				openingSound,
				attackSound,
				sound6, sound7, 
				sound8, sound9,

				i_last;
		};
		int32_t i_array[6 + NUM_MESSAGES];
	};
};

IMPLEMENT_RTIME(BlackDog01Mission)

BlackDog01Mission::BlackDog01Mission()
{
}

BlackDog01Mission::~BlackDog01Mission()
{
}

bool BlackDog01Mission::Load(file fp)
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

bool BlackDog01Mission::PostLoad(void)
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

bool BlackDog01Mission::Save(file fp)
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

void BlackDog01Mission::AddObject(GameObject *gameObj)
{
	// if we still have scavengers to create, then test what we just made
	if (!scavengersCreated)
		AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

void BlackDog01Mission::AddObject(BZHandle h)
{
}

void BlackDog01Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

void BlackDog01Mission::Setup()
{
	int i = 0;
	startDone = BZFALSE;
	objective1Complete = BZFALSE;
	objective2Complete = BZFALSE;
	objective3Complete = BZFALSE;

	// cameras
	cameraComplete[0] = cameraComplete[1] = BZFALSE;
	cameraReady = BZFALSE;
	
	// load up the handles
	recycler = GetHandle("recycler");
	wingman1 = GetHandle("wingman1_bobcat");
	wingman2 = GetHandle("wingman2_bobcat");
	badGuy1_ambush = NULL;
	badGuy2_ambush = NULL;
	badGuy1_wave1 = NULL; 
	badGuy2_wave1 = NULL; 
	badGuy3_wave1 = NULL; 
	badGuy4_wave1 = NULL; 
	badGuy1_wave2 = NULL; 
	badGuy2_wave2 = NULL;
	badGuy3_wave2 = NULL; 
	badGuy4_wave2 = NULL;
	badGuy5_wave2 = NULL;
	beacon = NULL;
	
	// scavengers
	scavengers[0] = scavengers[1] = NULL;
	scavengersCreated = BZFALSE;

	// sounds played yet?
	for (i = 0; i < 9; i++)
	{
		soundStarted[i] = BZFALSE;
		soundPlayed[i] = BZFALSE;
	}
	openingSound = NULL;
	attackSound = NULL;
	sound6 = NULL;
	sound7 = NULL;
	sound8 = NULL;
	sound9 = NULL;

	// beacon spawned?
	beaconSpawned1 = BZFALSE;
	beaconSpawned2 = BZFALSE;

	// has the ambush retreated?
	ambushRetreat = BZFALSE;

	// wave1
	wave1Ready = BZFALSE;
	wave2Ready = BZFALSE;

	wave2Delay = 999999.0f;
	delayTime1 = 999999.0f;
	delayTime2 = 999999.0f;
	delayTime3 = 999999.0f;
	sound6Time = 999999.9f;
	sound7Time = 999999.9f;
	sound8Time = 999999.9f;
	sound9Time = 999999.9f;
}

#define PLAY_SOUND_AND_WAIT(a) \
{ \
	if (!soundStarted[a])\
	{\
		soundStarted[a] = BZTRUE;\
		soundHandle[a] = AudioMessage(#a ".WAV");\
	}\
	if (!soundPlayed[a])\
	{\
		if (IsAudioMessageDone(soundHandle[a]))\
			soundPlayed[a] = BZTRUE;\
		else\
			return;\
	}\
}

void BlackDog01Mission::Execute()
{
	user = GetPlayerHandle(); //assigns the player a BZHandle every frame

	if (!startDone)
	{
		SetScrap(1,12);
		SetPilot(1,10);

		// objectives
		resetObjectives();

		Goto(recycler, "start_path_recycler");

		VECTOR_3D	stopPos = { 1012, 5, 101435 };

		Goto(recycler, stopPos, 1);


		Goto(wingman1, "start_path_wingman1");
		Goto(wingman2, "start_path_wingman2");

		// play the opening sound
		openingSound = AudioMessage("bd01001.wav");

		// don't do this part after the first shot
		startDone = BZTRUE;

		//SucceedMission(GetTime(), "bd01win.des");
	}

	// if we lose the recycler, play the "failure" message
	if (GetHealth(recycler) <= 0.0 && !soundStarted[BD01005])
	{
		soundStarted[BD01005] = BZTRUE;
		soundHandle[BD01005] = AudioMessage("bd01005.wav");
	}

	// when the sound's done, end the mission
	if (soundStarted[BD01005] && !soundPlayed[BD01005])
	{
		if (IsAudioMessageDone(soundHandle[BD01005]))
		{
			FailMission(GetTime() + 4.0f, "bd01lsea.des"); // lost the recycler
			soundPlayed[BD01005] = BZTRUE;
		}
	}

	// start the camera going
	if (!cameraComplete[0])
	{
		if (!cameraReady)
		{
			// get the camera ready
			CameraReady();
			
			// start the audio

			cameraReady = BZTRUE;
		}

		BZBOOLEAN arrived = CameraPath("camera_start_arc", 3000, 3500, recycler);
		
		if (CameraCancelled())
		{
			arrived = BZTRUE;
			StopAudioMessage(openingSound);
		}
		if (arrived)
		{
			CameraFinish();
			cameraComplete[0] = BZTRUE;
			cameraReady = BZFALSE;
			sound8Time = GetTime() + 90.0f;
		}
	}

	if (sound8Time < GetTime())
	{
		sound8Time = 999999.9f;
		if (!isDeployed(recycler))
		{
			sound8 = AudioMessage("bd01008.wav");
		}
	}

	if (sound8 != BZINVALIDHANDLE && IsAudioMessageDone(sound8))
	{
		sound8 = BZINVALIDHANDLE;
		sound9Time = GetTime() + 30.0f;
	}

	if (sound9Time < GetTime())
	{
		sound9Time = 999999.9f;
		if (!isDeployed(recycler))
		{
			sound9 = AudioMessage("bd01009.wav");
		}
	}

	if (sound9 != BZINVALIDHANDLE && IsAudioMessageDone(sound9))
	{
		sound9 = NULL;
		FailMission(GetTime() + 1.0f, "bd01lseb.des");
	}

	if (!scavengersCreated)  // this variable should change names since we're
							// not waiting for scavengers to be created anymore
	{
		if (isDeployed(recycler))
		{
			scavengersCreated = BZTRUE;
			delayTime1 = GetTime() + 20.0f;
			sound8Time = 999999.9f;
			sound9Time = 999999.9f;
			objective1Complete = BZTRUE;
			resetObjectives();
		}
	}

	// if the player doesn't have scavengers created yet, don't continue
	if (!scavengersCreated)
		return;

	if (GetTime() < delayTime1) // delayTime1 is set in AddObject
		return;

	if (!beaconSpawned1)
	{
		// spawn our beacon
		beaconSpawned1 = BZTRUE;
		beacon = BuildObject("apcamr", 1, "spawn_nav_beacon");
		SetName(beacon, "Nav Alpha");
		badGuy1_ambush = BuildObject("cvfigh", 2, "spawn_attack_ambush");
		GameObject *o = GameObjectHandle::GetObj(badGuy1_ambush);
		assert(o != NULL);
		o->curPilot = 0;
		Patrol(badGuy1_ambush, "ambush_patrol_path", 1);
		Cloak(badGuy1_ambush);
		badGuy2_ambush = BuildObject("cvfigh", 2, "spawn_attack_ambush");
		o = GameObjectHandle::GetObj(badGuy2_ambush);
		assert(o != NULL);
		o->curPilot = 0;
		Patrol(badGuy2_ambush, "ambush_patrol_path", 1);
		Cloak(badGuy2_ambush);
	}

	PLAY_SOUND_AND_WAIT(BD01002)

	if (!beaconSpawned2)
	{
		// spawn our beacon
		beaconSpawned2 = BZTRUE;
		
		// try to select the beacon here so that the little window shows up
		SetUserTarget(beacon);

		// also setup new objectives
		resetObjectives();

		sound6Time = GetTime() + 60.0f;
	}

	if (sound6Time < GetTime() + 60.0f ||
		sound7Time < GetTime() + 30.0f)
	{
		// check to see if any ally units near the nav
		BZHandle h = GetNearestUnitOnTeam("spawn_nav_beacon", 0, 1);
		float dist = GetDistance(h, "spawn_nav_beacon");
		if (dist < 100.0f ||
			!isCloaked(badGuy1_ambush) ||
			!isCloaked(badGuy2_ambush))
		{
			objective2Complete = BZTRUE;
			sound6Time = 999999.9f;
			sound7Time = 999999.9f;
			resetObjectives();
		}
	}

	if (sound6Time < GetTime())
	{
		sound6Time = 999999.9f;
		sound6 = AudioMessage("bd01006.wav");
	}

	if (sound6 != BZINVALIDHANDLE && IsAudioMessageDone(sound6))
	{
		sound6 = BZINVALIDHANDLE;
		sound7Time = GetTime() + 30.0f;
	}

	if (sound7Time < GetTime())
	{
		sound7Time = 999999.9f;
		sound7 = AudioMessage("bd01007.wav");
	}

	if (sound7 != BZINVALIDHANDLE && IsAudioMessageDone(sound7))
	{
		sound7 = BZINVALIDHANDLE;
		FailMission(GetTime() + 1.0f, "bd01lsec.des");
	}

	// ok, wait until one of the 2 ambushers is dead
	if (!ambushRetreat)
	{
		if (!IsAlive(badGuy1_ambush))
		{
			// retreat #2
			Retreat(badGuy2_ambush, "ambush_retreat_path", 1); 
			Cloak(badGuy2_ambush);
			delayTime2 = GetTime() + 5.0f;
			ambushRetreat = BZTRUE;
		}
		else if (!IsAlive(badGuy2_ambush))
		{
			Retreat(badGuy1_ambush, "ambush_retreat_path", 1);
			Cloak(badGuy1_ambush);
			delayTime2 = GetTime() + 5.0f;
			ambushRetreat = BZTRUE;
		}
	}

	if (!objective2Complete && GetDistance(user, beacon) < 100.0f)
	{
		objective2Complete = BZTRUE;
		sound6Time = 999999.9f;
		sound7Time = 999999.9f;
		resetObjectives();
	}

	// if one of the ambushers hasn't retreated yet, don't continue
	if (!ambushRetreat)
		return;

	if (GetTime() < delayTime2)  // time delay
		return;

	if (!wave1Ready)
	{
		wave1Ready = BZTRUE;
		badGuy1_wave1 = BuildObject("cvfigh", 2, "spawn_attack_wave1");
		Attack(badGuy1_wave1, recycler, 1);
		SetCloaked(badGuy1_wave1);
		Decloak(badGuy1_wave1);
		badGuy2_wave1 = BuildObject("cvfigh", 2, "spawn_attack_wave1_1");
		Attack(badGuy2_wave1, recycler, 1);
		SetCloaked(badGuy2_wave1);
		Decloak(badGuy2_wave1);

		wave2Delay = GetTime() + 60.0f;

		// add in the other objectives
		resetObjectives();
	}

	if (!cameraComplete[1])
	{
		if (!cameraReady)
		{
			// get the camera ready
			CameraReady();
			
			// start the audio

			cameraReady = BZTRUE;

			// get any survivers of the ambush to continue
			if (IsAlive(badGuy1_ambush))
				Attack(badGuy1_ambush, recycler, 1);
			if (IsAlive(badGuy2_ambush))
				Attack(badGuy2_ambush, recycler, 1);

			// play the sound
			attackSound = AudioMessage("bd01003.wav");
		}
		
		BZBOOLEAN arrived = CameraPath("camera_attack_view", 2000, 1000, badGuy1_wave1);

		if (CameraCancelled())
		{
			arrived = BZTRUE;

			StopAudioMessage(attackSound);
		}

		if (arrived)
		{
			// if the audio is complete
			CameraFinish();
			cameraComplete[1] = BZTRUE;
			cameraReady = BZFALSE;

			badGuy3_wave1 = BuildObject("cvfigh", 2, "spawn_attack_wave1a");
			Attack(badGuy3_wave1, recycler, 1);
			SetCloaked(badGuy3_wave1);
			Decloak(badGuy3_wave1);
			badGuy4_wave1 = BuildObject("cvfigh", 2, "spawn_attack_wave2");
			Attack(badGuy4_wave1, recycler, 1);
			SetCloaked(badGuy4_wave1);
			Decloak(badGuy4_wave1);
		}
	}

	// don't continue until the delay is done
	if (wave2Delay > GetTime())
		return;

	// have we killed everything?
	if (!IsAlive(badGuy1_wave1) &&
		!IsAlive(badGuy2_wave1) &&
		!IsAlive(badGuy3_wave1) &&
		!IsAlive(badGuy4_wave1) &&
		!IsAlive(badGuy1_ambush) &&
		!IsAlive(badGuy2_ambush) &&
		!soundStarted[BD01004])
	{
		// start the "congrats" message
		soundStarted[BD01004] = BZTRUE;
		soundHandle[BD01004] = AudioMessage("bd01004.wav");

		objective3Complete = BZTRUE;
		resetObjectives();
	}

	// when the sound's done, end the level
	if (soundStarted[BD01004] && !soundPlayed[BD01004])
	{
		if (IsAudioMessageDone(soundHandle[BD01004]))
		{
			soundPlayed[BD01004] = BZTRUE;
			SucceedMission(GetTime() + 4.0f, "bd01win.des");
		}
	}
}

void BlackDog01Mission::resetObjectives()
{
	ClearObjectives();
	if (objective1Complete)
		AddObjective("bd01001.otf", GREEN);
	else
		AddObjective("bd01001.otf", WHITE);

	if (!beaconSpawned2)
		return;

	if (objective2Complete)
		AddObjective("bd01002.otf", GREEN);
	else
		AddObjective("bd01002.otf", WHITE);

	if (!wave1Ready)
		return;

	if (objective3Complete)
		AddObjective("bd01003.otf", GREEN);
	else
		AddObjective("bd01003.otf", WHITE);
}

const std::set<PrjID>& BlackDog01Mission::GetPreloadGameObjects()
{
	static std::set<PrjID> retval = AiMission::PrjIDFromStrings(
	{ "apcamr", "cvfigh" }
	);
	return retval;
}
