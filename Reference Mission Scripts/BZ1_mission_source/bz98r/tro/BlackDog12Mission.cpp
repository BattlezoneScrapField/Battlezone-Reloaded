

#include "AiMission.h"
#include "ScriptUtils.h"
#include "AudioMessage.h"

// low health warnings
const char *warnings[4] =
{
	// shield warnings
	"bd12005.wav",
	"bd12006.wav",
	"bd12007.wav",
	"bd12008.wav"
};

const char *desporSpawnSpots[4] =
{
	"despor_1",
	"despor_2",
	"despor_3",
	"despor_4"
};


/*
	BlackDog12Mission
*/
class BlackDog12Mission : public AiMission {
	DECLARE_RTIME(BlackDog12Mission)
public:
	BlackDog12Mission();
	~BlackDog12Mission();

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

				// cameras
				cameraReady[2],
				cameraComplete[2],

				// sounds
				camera1SoundPlayed,
				portalDeadSoundPlayed,

				// delays initialized
				delaysInitialized,

				// health low warnings?
				healthLow[8],

				// despor units
				desporSpawned[4],

				// have we lost?
				lost, won,

				b_last;
		};
		bool b_array[25];
	};

	// floats
	union {
		struct {
			float
				delays[10],
				camera1SoundDelay,
				scrapDelay,
				portalOnTime,
				portalOffTime,
				f_last;
		};
		float f_array[14];
	};

	// handles
	union {
		struct {
			BZHandle
				// *** User stuff
				user,

				// *** Units
				recycler,
				portal,
				shields[4],
				power[4],
				goal[4],
								
				h_last;
		};
		BZHandle h_array[15];
	};

	// integers
	union {
		struct {
			int32_t
				// *** Sounds
				winSound,
				introSound,
				portalDeadSound,

				i_last;
		};
		int32_t i_array[3];
	};
};

IMPLEMENT_RTIME(BlackDog12Mission)

BlackDog12Mission::BlackDog12Mission()
{
}

BlackDog12Mission::~BlackDog12Mission()
{
}

bool BlackDog12Mission::Load(file fp)
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

bool BlackDog12Mission::PostLoad(void)
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

bool BlackDog12Mission::Save(file fp)
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

void BlackDog12Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

void BlackDog12Mission::AddObject(BZHandle h)
{
}

void BlackDog12Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

void BlackDog12Mission::Setup()
{
	int i = 0;
	startDone = BZFALSE;
	objective1Complete = BZFALSE;
	objective2Complete = BZFALSE;
	objective3Complete = BZFALSE;
	camera1SoundPlayed = BZFALSE;
	portalDeadSoundPlayed = BZFALSE;
	for (i = 0; i < 8 ; i++)
	{
		healthLow[i] = BZFALSE;
	}

	// cameras
	for (i = 0; i < 2; i++)
	{
		cameraReady[i] = BZFALSE;
		cameraComplete[i] = BZFALSE;
	}

	// sounds
	winSound = NULL;
	introSound = NULL;

	// units
	portal = GetHandle("portal");
	shields[0] = GetHandle("shield_1");
	shields[1] = GetHandle("shield_2");
	shields[2] = GetHandle("shield_3");
	shields[3] = GetHandle("shield_4");
	power[0] = GetHandle("power_1");
	power[1] = GetHandle("power_2");
	power[2] = GetHandle("power_3");
	power[3] = GetHandle("power_4");
	goal[0] = GetHandle("goal_1");
	goal[1] = GetHandle("goal_2");
	goal[2] = GetHandle("goal_3");
	goal[3] = GetHandle("goal_4");

	// delays
	camera1SoundDelay = 999999.9f;
	scrapDelay = 999999.9f;
	for (i = 0; i < 10; i++)
		delays[i] = 999999.9f;
	portalOnTime = 999999.9f;
	portalOffTime = 999999.9f;
}


void BlackDog12Mission::Execute()
{
	int i = 0;
	user = GetPlayerHandle(); //assigns the player a handle every frame

	if (!startDone)
	{
		SetScrap(1,50);
		SetScrap(2,10);
		SetPilot(1,10);

		// don't do this part after the first shot
		startDone = BZTRUE;
	}

	if (!cameraComplete[0])
	{
		if (!cameraReady[0])
		{
			cameraReady[0] = BZTRUE;
			CameraReady();
			camera1SoundDelay = GetTime() + 3.0f;
		}

		bool arrived = CameraPath("camera_start", 300, 2000, portal);

		if (camera1SoundDelay < GetTime())
		{
			camera1SoundDelay = 999999.9f;
			camera1SoundPlayed = BZTRUE;
			introSound = AudioMessage("bd12001.wav");
		}

		if (CameraCancelled())
		{
			arrived = BZTRUE;
			if (introSound != BZINVALIDHANDLE)
				StopAudioMessage(introSound);
		}

		if (arrived)
		{
			CameraFinish();
			cameraComplete[0] = BZTRUE;
			
			// show objectives
			ClearObjectives();
			AddObjective("bd12001.otf", WHITE);
		}
	}

	// objects spawned
	if (!delaysInitialized)
	{
		delaysInitialized = BZTRUE;

		delays[0] = GetTime() + 120.0f; // 2 minutes
		delays[1] = GetTime() + 240.0f; // 4 minutes
		delays[2] = GetTime() + 360.0f; // 6 minutes
		delays[3] = GetTime() + 480.0f; // 8 minutes
		delays[4] = GetTime() + 13 * 60.0f; // 13 minutes
		portalOnTime = delays[4] - 2.0f;
		delays[5] = GetTime() + 546.0f; // 9.1 minutes
		delays[6] = GetTime() + 552.0f; // 9.2 minutes
		portalOffTime = delays[6] + 2.0f;
		delays[7] = delays[4]+5.0f; // 9.2 minutes + 3 seconds

		scrapDelay = 60.0f;
	}

	// delay 1
	if (delays[0] < GetTime())
	{
		delays[0] = 999999.9f;

		// 3 fighters
		BZHandle a1 = BuildObject("cvfigh", 2, "attack_1");
		SetCloaked(a1);
		Attack(a1, power[0], 1);
		BZHandle a2 = BuildObject("cvfigh", 2, "attack_1");
		SetCloaked(a2);
		Attack(a2, power[0], 1);
		BZHandle a3 = BuildObject("cvfigh", 2, "attack_1");
		SetCloaked(a3);
		Attack(a3, power[0], 1);

		// 2 defenders
		BZHandle d1 = BuildObject("cvtnk", 2, "defend_1");
		SetCloaked(d1);
		Defend2(d1, a1, 1);
		BZHandle d2 = BuildObject("cvtnk", 2, "defend_1");
		SetCloaked(d2);
		Defend2(d2, a2, 1);
	}

	// delay 2
	if (delays[1] < GetTime())
	{
		delays[1] = 999999.9f;

		// 3 fighters
		BZHandle a1 = BuildObject("cvfigh", 2, "attack_2");
		SetCloaked(a1);
		Attack(a1, power[1], 1);
		BZHandle a2 = BuildObject("cvfigh", 2, "attack_2");
		SetCloaked(a2);
		Attack(a2, power[1], 1);
		BZHandle a3 = BuildObject("cvfigh", 2, "attack_2");
		SetCloaked(a3);
		Attack(a3, power[1], 1);
		
		// 1 heavy tank
		BZHandle a4 = BuildObject("cvhtnk", 2, "attack_2");
		SetCloaked(a4);
		Attack(a4, power[1], 1);

		// defenders
		BZHandle d1 = BuildObject("cvfigh", 2, "defend_2");
		SetCloaked(d1);
		Defend2(d1, a1, 1);
		BZHandle d2 = BuildObject("cvfigh", 2, "defend_2");
		SetCloaked(d2);
		Defend2(d2, a2, 1);
		BZHandle d3 = BuildObject("cvfigh", 2, "defend_2");
		SetCloaked(d3);
		Defend2(d3, a3, 1);
		BZHandle d4 = BuildObject("cvhtnk", 2, "defend_2");
		SetCloaked(d4);
		Defend2(d4, a4, 1);
	}

	// delay 3
	if (delays[2] < GetTime())
	{
		delays[2] = 999999.9f;

		// 2 bombers
		BZHandle a1 = BuildObject("cvhraz", 2, "attack_3");
		SetCloaked(a1);
		Attack(a1, power[2], 1);
		BZHandle a2 = BuildObject("cvhraz", 2, "attack_3");
		SetCloaked(a2);
		Attack(a2, power[2], 1);
		
		// 2 fighters
		BZHandle a3 = BuildObject("cvfigh", 2, "attack_3");
		SetCloaked(a3);
		Attack(a3, power[2], 1);
		BZHandle a4 = BuildObject("cvfigh", 2, "attack_3");
		SetCloaked(a4);
		Attack(a4, power[2], 1);
		
		// defenders
		BZHandle d1 = BuildObject("cvtnk", 2, "defend_3");
		SetCloaked(d1);
		Defend2(d1, a1, 1);
		BZHandle d2 = BuildObject("cvtnk", 2, "defend_3");
		SetCloaked(d2);
		Defend2(d2, a2, 1);
		BZHandle d3 = BuildObject("cvfigh", 2, "defend_3");
		SetCloaked(d3);
		Defend2(d3, a3, 1);
		BZHandle d4 = BuildObject("cvfigh", 2, "defend_3");
		SetCloaked(d4);
		Defend2(d4, a4, 1);
	}

	// delay 4
	if (delays[3] < GetTime())
	{
		delays[3] = 999999.9f;

		// attacker 1
		BZHandle a1 = BuildObject("cvwalk", 2, "attack_4");
		Attack(a1, shields[0], 1);
		// and it's defence
		BZHandle d1 = BuildObject("cvltnk", 2, "defend_4");
		SetCloaked(d1);
		Defend2(d1, a1, 1);
		BZHandle d2 = BuildObject("cvltnk", 2, "defend_4");
		SetCloaked(d2);
		Defend2(d2, a1, 1);

		// attacker 2
		BZHandle a2 = BuildObject("cvwalk", 2, "attack_5");
		Attack(a2, shields[1], 1);
		// and it's defence
		BZHandle d3 = BuildObject("cvltnk", 2, "defend_5");
		SetCloaked(d3);
		Defend2(d3, a2, 1);
		BZHandle d4 = BuildObject("cvltnk", 2, "defend_5");
		SetCloaked(d4);
		Defend2(d4, a2, 1);

		// attacker 3
		BZHandle a3 = BuildObject("cvwalk", 2, "attack_6");
		Attack(a3, shields[2], 1);
		// and it's defence
		BZHandle d5 = BuildObject("cvtnk", 2, "defend_6");
		SetCloaked(d5);
		Defend2(d5, a3, 1);
		BZHandle d6 = BuildObject("cvtnk", 2, "defend_6");
		SetCloaked(d6);
		Defend2(d6, a3, 1);

		// attacker 4
		BZHandle a4 = BuildObject("cvwalk", 2, "attack_7");
		Attack(a4, shields[3], 1);
		// and it's defence
		BZHandle d7 = BuildObject("cvtnk", 2, "defend_7");
		SetCloaked(d7);
		Defend2(d7, a4, 1);
		BZHandle d8 = BuildObject("cvtnk", 2, "defend_7");
		SetCloaked(d8);
		Defend2(d8, a4, 1);

		// attacker 5
		BZHandle a5 = BuildObject("cvwalk", 2, "attack_8");
		Attack(a5, portal, 1);
		// and it's defence
		BZHandle d9 = BuildObject("cvhtnk", 2, "defend_8");
		SetCloaked(d9);
		Defend2(d9, a5, 1);
		BZHandle d10 = BuildObject("cvhtnk", 2, "defend_8");
		SetCloaked(d10);
		Defend2(d10, a5, 1);
	}

	// turn on/off the portal
	if (portalOnTime < GetTime())
	{
		portalOnTime = 999999.9f;
		activatePortal(portal, false);
	}

	if (portalOffTime < GetTime())
	{
		portalOffTime = 999999.9f;
		deactivatePortal(portal);
	}

	// delay 5
	if (delays[4] < GetTime())
	{
		delays[4] = 999999.9f;

		recycler = BuildObjectAtPortal("bvrecyd", 1, portal);
		VECTOR_3D PortalRecyc_pos={1841,104.3,101030};   //position to head for when leaving the portal. Used to head for "follow" but this caused pathfinding issues if tanks etc were in the way, causing the recycler to be inoperable for a long period.
		
		Goto(recycler,PortalRecyc_pos,1);


	}

	// delay 6
	if (delays[5] < GetTime())
	{
		delays[5] = 999999.9f;

		BZHandle h;
		h = BuildObjectAtPortal("bvtank", 1, portal);
		Goto(h, "follow", 1);
		h = BuildObjectAtPortal("bvtank", 1, portal);
		Goto(h, "follow", 1);
	}

	// delay 7
	if (delays[6] < GetTime())
	{
		delays[6] = 999999.9f;

		BZHandle h = BuildObjectAtPortal("bvfigh", 1, portal);
		Goto(h, "follow", 1);
	}

	// delay 8
	if (delays[7] < GetTime())
	{
		delays[7] = 999999.9f;

		ClearObjectives();
		AddObjective("bd12001.otf", GREEN);
		AddObjective("bd12002.otf", WHITE);
		objective1Complete = BZTRUE;
	}

	// check the goals
	if (objective1Complete && !objective2Complete)
	{
		objective2Complete = BZTRUE;
		for (int i = 0; i < 4; i++)
		{
			if (GetHealth(goal[i]) > 0.0)
			{
				objective2Complete = BZFALSE;
				break;
			}
		}

		if (objective2Complete)
		{
			// start the sound
			winSound = AudioMessage("bd12003.wav");
		}
	}

	if (objective2Complete && !won && !lost)
	{
		if (IsAudioMessageDone(winSound))
		{
			won = BZTRUE;
			SucceedMission(GetTime() + 1.0f, "bd12win.des");
		}
	}

	// spawn scrap
	if (scrapDelay < GetTime())
	{
		scrapDelay = GetTime() + 60.0f;

		BuildObject("npscr1", 0, "scrap_1");
		BuildObject("npscr1", 0, "scrap_1");
		BuildObject("npscr1", 0, "scrap_1");
		BuildObject("npscr1", 0, "scrap_2");
		BuildObject("npscr1", 0, "scrap_2");
		BuildObject("npscr1", 0, "scrap_2");
	}

	// low health warnings?
	for (i = 0; i < 4; i++)
	{
		// check the power units
		if (!healthLow[i] && GetHealth(power[i]) < 0.25)
		{
			healthLow[i] = BZTRUE;
			AudioMessage(warnings[i]);
		}

		// check the shield units
		if (!healthLow[4+i] && GetHealth(shields[i]) < 0.25)
		{
			healthLow[4+i] = BZTRUE;
			AudioMessage(warnings[i]);
		}
	}

	// shields or power dead?
	for (i = 0; i < 4; i++)
	{
		if (!desporSpawned[i])
		{
			if (GetHealth(power[i]) <= 0.0 ||
				GetHealth(shields[i]) <= 0.0)
			{
				desporSpawned[i] = BZTRUE;
				BZHandle h;
				h = BuildObject("cvltnk", 2, desporSpawnSpots[i]);
				SetCloaked(h);
				Attack(h, portal, 1);
				h = BuildObject("cvltnk", 2, desporSpawnSpots[i]);
				SetCloaked(h);
				Attack(h, portal, 1);
			}
		}
	}

	// portal is indestructible while all four shields are alive and powered
	if (!desporSpawned[0] && !desporSpawned[1] && !desporSpawned[2] && !desporSpawned[3])
	{
		GiveMaxHealth(portal);
	}

	// portal dead?
	if (GetHealth(portal) <= 0.0f && !portalDeadSoundPlayed)
	{
		portalDeadSoundPlayed = BZTRUE;
		portalDeadSound = AudioMessage("bd12004.wav");
	}

	if (portalDeadSoundPlayed && !lost && !won)
	{
		if (IsAudioMessageDone(portalDeadSound))
		{
			lost = BZTRUE;
			FailMission(GetTime() + 2.0f, "bd12lsea.des");
		}

	}
}

const std::set<PrjID>& BlackDog12Mission::GetPreloadGameObjects()
{
	static std::set<PrjID> retval = AiMission::PrjIDFromStrings(
	{ "cvfigh", "cvtnk", "cvhtnk", "cvhraz", "cvwalk", "cvltnk", "cvhtnk", "npscr1", "bvrecyd" }
	);
	return retval;
}
