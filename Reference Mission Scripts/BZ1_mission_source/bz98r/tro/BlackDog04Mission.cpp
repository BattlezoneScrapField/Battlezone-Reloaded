

#include "AiMission.h"
#include "ScriptUtils.h"
#include "AudioMessage.h"

/*
	BlackDog04Mission
*/

class BlackDog04Mission : public AiMission {
	DECLARE_RTIME(BlackDog04Mission)
public:
	BlackDog04Mission();
	~BlackDog04Mission();

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

				// cameras
				cameraReady[3], cameraComplete[3],

				// been told to hyjack the scav?
				gotoScav,

				// objective complete?
				objective1Complete, 
				objective2Complete,
				objective3Complete,
				
				// in the base?
				inBaseArea,
				doAttack,
				startAttack,
				outOfScav,

				// fighters spawned?
				fightersSpawned,

				// trigger1
				trigger1,

				// has the player id'd the fragment?
				idFragment,
				gotFragment,

				// return_?
				returnAttack[4],

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
				cameraCompleteDelay,
				getInScavTimeout,
				portalCamTime,
				portalOffTime,
				portalUnitTime[2],
				portalSoundTime,
				inBaseSoundTime,
				sound4Time,
				bomberTime,
				f_last;
		};
		float f_array[10];
	};

	// handles
	union {
		struct {
			BZHandle
				// the user
				user,
				lastUser,

				// the pilot during the initial camera stuff
				// and the navs he's creating
				pilot, nav1, nav2,

				// the silo
				silo, 

				// turrets
				turret[9],

				// portal
				portal,
				portalUnit[2],

				// fragment
				fragment,

				// nav beacon
				navBeacon,

				// hauler
				hauler,

				// scav3
				scav1, scav2,
				scav3,

				h_last;
		};
		BZHandle h_array[24];
	};

	// integers
	union {
		struct {
			int32_t
				// "goto scav" message
				scavMessage,

				// intro sound
				introSound,
				sound4,
				sound5, sound6,

				// portal sound
				portalSound,

				// congratulations message
				congrats,

				// in base sounds
				inBaseSound1,
				inBaseSound2,

				
				i_last;
		};
		int32_t i_array[9];
	};
};

IMPLEMENT_RTIME(BlackDog04Mission)

BlackDog04Mission::BlackDog04Mission()
{
}

BlackDog04Mission::~BlackDog04Mission()
{
}

bool BlackDog04Mission::Load(file fp)
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

bool BlackDog04Mission::PostLoad(void)
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

bool BlackDog04Mission::Save(file fp)
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

void BlackDog04Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

void BlackDog04Mission::AddObject(BZHandle h)
{
}

void BlackDog04Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

void BlackDog04Mission::Setup()
{
	int i = 0;
	startDone = BZFALSE;
	cameraReady[0] =
		cameraReady[1] =
		cameraReady[2] = BZFALSE;
	cameraComplete[0] = 
		cameraComplete[1] = 
		cameraComplete[2] = BZFALSE;
	inBaseArea = BZFALSE;
	outOfScav = BZFALSE;
	trigger1 = BZFALSE;
	idFragment = BZFALSE;
	gotFragment = BZFALSE;
	for (i = 0; i < 4; i++)
		returnAttack[i] = NULL;
	
	// handles
	lastUser = NULL;
	user = NULL;
	silo = GetHandle("silo");
	portal = GetHandle("portal");
	scav1 = GetHandle("scav_1");
	scav2 = GetHandle("scav_2");
	scav3 = GetHandle("scav_3");
	fragment = GetHandle("fragment");
	navBeacon = NULL;
	pilot = NULL;
	nav1 = nav2 = NULL;
	for (i = 0; i < 2; i++)
		portalUnit[i] = NULL;
	hauler = GetHandle("hauler_1");
	turret[0] = GetHandle("turret_1");
	turret[1] = GetHandle("turret_2");
	turret[2] = GetHandle("turret_3");
	turret[3] = GetHandle("turret_4");
	turret[4] = GetHandle("turret_5");
	turret[5] = GetHandle("turret_6");
	turret[6] = GetHandle("turret_7");
	turret[7] = GetHandle("turret_8");
	turret[8] = GetHandle("turret_9");

	// states
	lost = BZFALSE;
	won = BZFALSE;
	objective1Complete = BZFALSE;
	objective2Complete = BZFALSE;
	objective3Complete = BZFALSE;
	fightersSpawned = BZFALSE;
	doAttack = BZFALSE;
	startAttack = BZFALSE;
	
	// sound handles
	congrats = NULL;
	scavMessage = NULL;
	introSound = NULL;
	portalSound = NULL;
	inBaseSound1 = NULL;
	inBaseSound2 = NULL;

	// waits
	cameraCompleteDelay = 999999.9f;
	getInScavTimeout = 999999.0f;
	portalCamTime = 999999.9f;
	inBaseSoundTime = 999999.9f;
	portalUnitTime[0] = 999999.9f;
	portalUnitTime[1] = 999999.9f;
	bomberTime = 999999.9f;
	portalOffTime = 999999.9f;
}

void BlackDog04Mission::Execute()
{
	int i = 0;
	lastUser = user;
	user = GetPlayerHandle(); //assigns the player a handle every frame

	if (!startDone)
	{
		SetScrap(1,8);
		SetPilot(1,10);

		// setup the initial objectives
		ClearObjectives();
		
		// don't do this part after the first shot
		startDone = BZTRUE;

		SetCommand(scav1, CMD_SCAVENGE);
		SetCommand(scav2, CMD_SCAVENGE);
	}

	// SOE #1

	// start the camera going
	if (!cameraComplete[0])
	{
		if (!cameraReady[0])
		{
			// get the camera ready
			CameraReady();
		
			// spawn the pilot
			pilot = BuildObject("aspilo", 1, "pilot");
			Goto(pilot, "pilot_path", 1);
			Hide(user);

			// start the audio
			introSound = AudioMessage("bd04001.wav");

			cameraReady[0] = BZTRUE;
		}

		BZBOOLEAN arrived = CameraPath("camera_start_up", 750, 400, pilot);
		
		// should we spawn the beacons?
		if (nav1 == BZINVALIDHANDLE && GetDistance(pilot, "nav_1", 0) < 20.0)
			nav1 = BuildObject("apcamr", 0, "nav_1");
		if (nav2 == BZINVALIDHANDLE && GetDistance(pilot, "nav_2", 0) < 20.0)
		{
			nav2 = BuildObject("apcamr", 0, "nav_2");
			cameraCompleteDelay = GetTime() + 2.0f;
		}

		if (CameraCancelled())
		{
			arrived = BZTRUE;
			StopAudioMessage(introSound);
		}
		if (arrived ||
			cameraCompleteDelay < GetTime())
		{
			// if the audio is complete
			CameraFinish();
			cameraComplete[0] = BZTRUE;
			cameraReady[0] = BZFALSE;
			cameraCompleteDelay = 999999.9f;

			// remove the pilot
			RemoveObject(pilot);
			pilot = NULL;
			UnHide(user);

			// if the nav's don't exist, add them
			if (nav1 == BZINVALIDHANDLE)
				nav1 = BuildObject("apcamr", 0, "nav_1");
			if (nav2 == BZINVALIDHANDLE)
				nav2 = BuildObject("apcamr", 0, "nav_2");

			SetPerceivedTeam(user, 2);
		}
	}

	// SOE #2
	if (cameraComplete[0] && !cameraComplete[1])
	{
		if (!cameraReady[1])
		{
			// setup the camera
			cameraReady[1] = BZTRUE;
			cameraComplete[1] = BZFALSE;
			CameraReady();

			activatePortal(portal, false);

			portalCamTime = GetTime() + 6.0f;
			portalSoundTime = GetTime() + 4.0f; // 2 seconds before the sound
			portalUnitTime[0] = GetTime() + 1.5f;
			portalUnitTime[1] = GetTime() + 4.0f;
			portalOffTime = GetTime() + 7.0f;
		}

		CameraPath("camera_portal", 3000, 0, portal);
		
		if (CameraCancelled())
		{
			portalCamTime = -1;
			StopAudioMessage(portalSound);
		}

		if (portalCamTime < GetTime())
		{
			portalCamTime = 999999.9f;
			cameraReady[1] = BZFALSE;
			cameraComplete[1] = BZTRUE;
			CameraFinish();
		}
		else if (portalSoundTime < GetTime())
		{
			portalSoundTime = 999999.9f;
			portalSound = AudioMessage("bd04002.wav");
		}
	}

	for (i = 0; i < 2; i++)
	{
		if (portalUnitTime[i] < GetTime())
		{
			portalUnitTime[i] = 999999.9f;
			portalUnit[i] = BuildObjectAtPortal("cvfigh", 2, portal);
			Goto(portalUnit[i], "unit_path", 1);
		}
	}

	if (portalOffTime < GetTime())
	{
		portalOffTime = 999999.9f;
		deactivatePortal(portal);
	}

	// SOE #3
	if (cameraComplete[1] && !gotoScav)
	{
		scavMessage = AudioMessage("bd04003.wav");

		ClearObjectives();
		AddObjective("bd04001.otf", WHITE);
		SetObjectiveOn(scav3);
		SetObjectiveName(scav3, "Scavenger");
		
		gotoScav = BZTRUE;

		// set the target
		SetUserTarget(scav3);
		getInScavTimeout = GetTime() + 120.0f;
	}

	// time out and play message again
	if (!objective1Complete && getInScavTimeout < GetTime())
	{
		getInScavTimeout = GetTime() + 120.0f;
		scavMessage = AudioMessage("bd04003.wav");
	}

	// are we in the scav?
	if (user == scav3)
	{
		if (!objective1Complete && !objective2Complete)
		{
			// stop the "goto scav" message if it's still playing
			if (!IsAudioMessageDone(scavMessage))
				StopAudioMessage(scavMessage);
			
			ClearObjectives();
			AddObjective("bd04001.otf", GREEN);
			AddObjective("bd04002.otf", WHITE);
			objective1Complete = BZTRUE;

			SetObjectiveOff(scav3);
			getInScavTimeout = 999999.0f;

			Goto(scav1, "scav_path");
			Goto(scav2, "scav_path");
			AudioMessage("bd04010.wav");
			SetObjectiveOn(portal);
		}
	}

	// SOE #4
	if (!trigger1 && scav3 == user && GetDistance(scav3, "trigger_1") < 400.0f)
	{
		trigger1 = BZTRUE;
	}

	if (isIn(user, "base_limit") && !inBaseArea)
	{
		inBaseArea = BZTRUE;
		if (trigger1) 
			; // we're safe since we went by trigger_1
		else if (user == scav3)
			inBaseSound1 = AudioMessage("bd04005.wav");
		else
			doAttack = BZTRUE;
	}

	if (inBaseSound1 != BZINVALIDHANDLE && IsAudioMessageDone(inBaseSound1))
	{
		inBaseSound1 = BZINVALIDHANDLE;
		inBaseSoundTime = GetTime() + 1.0f;
	}

	if (inBaseSoundTime < GetTime())
	{
		inBaseSoundTime = 999999.9f;
		inBaseSound2 = AudioMessage("bd04006.wav");
	}

	if (inBaseSound2 != BZINVALIDHANDLE && IsAudioMessageDone(inBaseSound2))
	{
		inBaseSound2 = NULL;
		doAttack = BZTRUE;
	}

	if (doAttack)
	{
		//doAttack = BZFALSE;
		if (!startAttack ||
			lastUser != user)
		{
			startAttack = BZTRUE;

			// turrets lock on and attack
			for (i = 0; i < 9; i++)
				Attack(turret[i], user, 1);
		}
	}

	if (!objective2Complete && IsInfo("cbport"))
	{
		// do objectives
		ClearObjectives();
		AddObjective("bd04004.otf", WHITE);

		sound4Time = GetTime() + 2.0f;
		objective2Complete = BZTRUE;
		SetObjectiveOff(portal);

		StartCockpitTimer(60, 15, 5);
	}

	// play the audio message after a 2 second delay
	if (sound4Time < GetTime())
	{
		sound4Time = 999999.9f;
		sound4 = AudioMessage("bd04004.wav");
	}

	// once played
	if (sound4 != BZINVALIDHANDLE && IsAudioMessageDone(sound4))
	{
		sound4 = BZINVALIDHANDLE;
	}

	if (((!sound6)&&(!sound5)&&(!doAttack))&&(objective2Complete) && (!idFragment) && (GetCockpitTimer() <= 0.0))
	{
		HideCockpitTimer();

		sound5 = AudioMessage("bd04005.wav");
	}

	// once played
	if (sound5 != BZINVALIDHANDLE && IsAudioMessageDone(sound5))
	{
		sound5 = BZINVALIDHANDLE;
		sound6 = AudioMessage("bd04006.wav");
	}

	// once played
	if (sound6 != BZINVALIDHANDLE && IsAudioMessageDone(sound6))
	{
		sound6 = BZINVALIDHANDLE;
		doAttack = BZTRUE;
	}

	// SOE #4a	
	if (objective2Complete && !idFragment && IsInfo("obdataa"))
	{
		StopCockpitTimer();
		HideCockpitTimer();
			
		idFragment = BZTRUE;

		AudioMessage("bd04007.wav");

		ClearObjectives();
		AddObjective("bd04003.otf", WHITE);
		objective3Complete = BZTRUE;
	}

	if (objective3Complete && !outOfScav)
	{
		if (user != scav3)
		{
			outOfScav = BZTRUE;
			doAttack = BZTRUE;
		}
	}

	// SOE #4b
	if (!gotFragment)
	{
		if (GetTug(fragment) == user)
		{
			gotFragment = BZTRUE;

			navBeacon = BuildObject("apcamr", 1, "rv_scout");
			//SetUserTarget(navBeacon);

			BZHandle h;
			h = BuildObject("bvfigh", 1, "escort_units");
			h = BuildObject("bvfigh", 1, "escort_units");
			h = BuildObject("bvfigh", 1, "escort_units");
			h = BuildObject("bvtank", 1, "escort_units");
			h = BuildObject("bvtank", 1, "escort_units");
			h = BuildObject("bvtank", 1, "escort_units");
			bomberTime = GetTime() + 30.0f;
		}
	}

	if (bomberTime < GetTime())
	{
		bomberTime = 999999.9f;
		BZHandle h, h1;
		h1 = BuildObject("bvhraza", 1, "bomber_wing_x5_spawn_point");
		SetMaxHealth(h1, 7000);
		SetCurHealth(h1, 7000);
		Goto(h1, "trigger_1");
		h = BuildObject("bvhraza", 1, "bomber_wing_x5_spawn_point");
		//Goto(h, "trigger_1");
		Defend2(h, h1);
		h = BuildObject("bvhraza", 1, "bomber_wing_x5_spawn_point");
		//Goto(h, "trigger_1");
		Defend2(h, h1);
		h = BuildObject("bvhraza", 1, "bomber_wing_x5_spawn_point");
		//Goto(h, "trigger_1");
		Defend2(h, h1);
		h = BuildObject("bvhraza", 1, "bomber_wing_x5_spawn_point");
		//Goto(h, "trigger_1");
		Defend2(h, h1);

		navBeacon = BuildObject("apcamr", 1, "proposed_end_area");
		SetName(navBeacon, "Drop Zone");
		SetObjectiveOn(navBeacon);
		//SetUserTarget(navBeacon);
		
		// spawn the fighers to kill the player here
		int i;
		for (i = 0; i < 5; i++) // down from 6
		{
			BZHandle h = BuildObject("cvfighg", 2, "chinese_scout_x6_spawn_point");
			Attack(h, hauler, 1);
		}

		for (i = 0; i < 2; i++)
		{
			BZHandle h = BuildObject("cvfighg", 2, "attack_1");
			Attack(h, hauler, 1);
		}

		for (i = 0; i < 3; i++) // down from 4
		{
			BZHandle h = BuildObject("cvfighg", 2, "attack_2");
			Attack(h, hauler, 1);
		}

		for (i = 0; i < 1; i++) // down from 2
		{
			BZHandle h = BuildObject("cvtnk", 2, "attack_3");
			Attack(h, hauler, 1);
		}
	}

	for (i = 0; i < 4; i++)
	{
		static const char *spots[4] = { "return_1", "return_2", "return_3", "return_4" };
		if (returnAttack[i])
			continue;

		if (GetDistance(hauler, spots[i]) < 300.0f)
		{
			returnAttack[i] = BZTRUE;

			BZHandle h;
			h = BuildObject("cvfigh", 2, spots[i]);
			Attack(h, hauler);
			h = BuildObject("cvfigh", 2, spots[i]);
			Attack(h, hauler);
			//h = BuildObject("cvfigh", 2, spots[i]);
			//Attack(h, hauler);
		}
	}

	if (GetHealth(hauler) <= 0.0 && !lost && !won)
	{
		FailMission(GetTime() + 1.0f, "bd04lose.des");
		lost = BZTRUE;
	}


	// SOE #5
	if (objective3Complete && GetDistance(fragment, navBeacon) < 50.0 && !won && !lost)
	{
		ClearObjectives();
		AddObjective("bd04003.otf", GREEN);

		won = BZTRUE;
		congrats = AudioMessage("bd04008.wav");
	}

	if (congrats != BZINVALIDHANDLE && IsAudioMessageDone(congrats))
	{
		congrats = BZINVALIDHANDLE;
		SucceedMission(0.1f, "bd04win.des");
	}

	// what if the portal is destroyed?
	if (GetHealth(portal) <= 0.0f && !won && !lost)
	{
		lost = BZTRUE;
		FailMission(GetTime() + 1.0f, "bd04lose.des");
	}
}
	
const std::set<PrjID>& BlackDog04Mission::GetPreloadGameObjects()
{
	static std::set<PrjID> retval = AiMission::PrjIDFromStrings(
	{ "aspilo", "apcamr", "bvfigh", "bvtank", "bvhraza", "cvfigh", "cvfighg" }
	);
	return retval;
}
