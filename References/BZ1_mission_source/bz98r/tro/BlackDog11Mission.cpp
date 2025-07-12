

#include "AiMission.h"
#include "AiProcess.h"
#include "ScriptUtils.h"
#include "ColorFade.h"
#include "AudioMessage.h"
#include "SRANDOM.H"

const int unitBase = 6;
const int attacks[] =
{
	0,
	2,
	4,
	8,
	11,
	14,
	23
};
const char *attackSpawns[] =
{
	"attack_1",
	"attack_2",
	"attack_3",
	"attack_4",
	"attack_5",
	"attack_6"
};

const char *attackUnits[] =
{
	"cvhraz",	// attack 1
	"cvhraz",
	"cvhtnk",	// attack 2
	"cvhraz",
	"cvhraz",	// atttack 3
	"cvhraz", 
	"cvhtnk",
	"cvhtnk",
	"cvhtnk",	// attack 4
	"cvhtnk",
	"cvhtnk",
	"cvhraz",	// attack 5
	"cvhraz", 
	"cvhraz",
	"cvhtnk",	// attack 6
	"cvhtnk",
	"cvhtnk",
	"cvfigh",
	"cvfigh",
	"cvfigh",
	"cvhraz",
	"cvhraz",
	"cvhraz",
	NULL		// end
};

const int defends[] =
{
	0,
	4,
	9,
	14,
	21,
	30,
	42
};
const char *defendSpawns[] =
{
	"defend_1",
	"defend_2",
	"defend_3",
	"defend_4",
	"defend_5",
	"defend_6"
};
const char *defendUnits[] =
{
	"cvtnk",	// defend 1
	"cvtnk",
	"cvfigh",
	"cvfigh",
	"cvfigh",	// defend 2
	"cvfigh",
	"cvfigh",
	"cvhtnk",
	"cvltnk",
	"cvtnk",	// defend 3
	"cvtnk",
	"cvtnk",
	"cvfigh",
	"cvfigh",
	"cvfigh",	// defend 4
	"cvfigh",
	"cvfigh",
	"cvfigh",
	"cvtnk",
	"cvtnk",
	"cvtnk",
	"cvhtnk",	// defend 5
	"cvhtnk",
	"cvhtnk",
	"cvhtnk",
	"cvtnk",
	"cvtnk",
	"cvtnk",
	"cvfigh",
	"cvfigh",
	"cvhtnk",	// defend 6
	"cvhtnk",
	"cvhtnk",
	"cvhtnk",
	"cvtnk",
	"cvtnk",
	"cvtnk",
	"cvtnk",
	"cvfigh",
	"cvfigh", 
	"cvfigh",
	"cvfigh",
	NULL		// end
};

#define NUM_UNITS	71
//const int numUnits = unitBase + attacks[7] + defends[7];

/*
	BlackDog11Mission
*/

class BlackDog11Mission : public AiMission {
	DECLARE_RTIME(BlackDog11Mission)
public:
	BlackDog11Mission();
	~BlackDog11Mission();

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
				cameraReady[2], cameraComplete[2],

				// pilot transfer
				apcWantsToTransferPilot,
				pilotTransferring,

				toldToGo,

				// attacks?
				attacksSent,

				// got within 400 metres of nav_end?
				navDistanceOk,

				// have the retreat units spawned?
				retreatSpawned,

				// sound played?
				sound4Played, sound5Played, sound6Played,

				// cockpit timer
				cockpitTimerActive,

				// portal explosion?
				explodePortal,

				// have we lost?
				lost, won,

				b_last;
		};
		bool b_array[21];
	};

	// floats
	union {
		struct {
			float
				recyclerGoTime,
				drive1Time,
				attackTimes[6],
				goToPortalTime,
				cameraDestructTime,
				explodeTime,
				explodeDelay,
				explode1Time,
				explode2Time,
				explode3Time,
				explode4Time,
				aerial1Time,
				aerial2Time,
				portalTime,
				sound8Time,
				sound9Time,
				sound12Time,
				f_last;
		};
		float f_array[22];
	};

	// handles
	union {
		struct {
			BZHandle
				// *** User stuff
				user,

				// *** Units
				recycler,
				apc,
				pilot,
				enemy[NUM_UNITS],
				retreats[12],

				// buildings
				portal,

				// nav beacons
				navRecycler,
				navEnd,

				h_last;
		};
		BZHandle h_array[19 + NUM_UNITS];
	};

	// integers
	union {
		struct {
			int32_t
				portalStage,

				// *** Sounds
				winMessage,
				introSound,
				sound4, sound5, sound6,
				sound8, sound10, sound12,

				i_last;
		};
		int32_t i_array[9];
	};
};

IMPLEMENT_RTIME(BlackDog11Mission)

BlackDog11Mission::BlackDog11Mission()
{
}

BlackDog11Mission::~BlackDog11Mission()
{
}

bool BlackDog11Mission::Load(file fp)
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

bool BlackDog11Mission::PostLoad(void)
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

bool BlackDog11Mission::Save(file fp)
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

void BlackDog11Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

void BlackDog11Mission::AddObject(BZHandle h)
{
}

void BlackDog11Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

void BlackDog11Mission::Setup()
{
	int i = 0;
	startDone = BZFALSE;
	objective1Complete = BZFALSE;
	objective2Complete = BZFALSE;
	objective3Complete = BZFALSE;
	apcWantsToTransferPilot = BZFALSE;
	pilotTransferring = BZFALSE;
	attacksSent = BZFALSE;
	navDistanceOk = BZFALSE;
	retreatSpawned = BZFALSE;
	cockpitTimerActive = BZFALSE;
	toldToGo = BZFALSE;
	explodePortal = BZFALSE;
	for (i = 0; i < 2; i++)
		cameraReady[i] = cameraComplete[i] = BZFALSE;
	sound4Played = NULL;
	sound5Played = NULL;
	sound6Played = NULL;

	// units
	recycler = GetHandle("recycler");
	portal = GetHandle("portal");
	apc = GetHandle("apc");
	for (i = 0; i < NUM_UNITS; i++)
		enemy[i] = NULL;
	enemy[0] = GetHandle("enemy_1");
	enemy[1] = GetHandle("enemy_2");
	enemy[2] = GetHandle("enemy_3");
	enemy[3] = GetHandle("enemy_4");
	enemy[4] = GetHandle("enemy_5");
	enemy[5] = GetHandle("enemy_6");
	pilot = NULL;
	navEnd = NULL;
	navRecycler = NULL;
	for (i = 0; i < 12; i++)
		retreats[i] = NULL;

	// sounds
	winMessage = NULL;
	introSound = NULL;
	sound4 = NULL;
	sound5 = NULL;
	sound6 = NULL;
	sound8 = NULL;
	sound10 = NULL;
	sound12 = NULL;

	// times
	drive1Time = 999999.9f;
	for (i = 0; i < 6; i++)
		attackTimes[i] = 999999.9f;
	goToPortalTime = 999999.9f;
	cameraDestructTime = 999999.9f;
	explodeTime = 999999.9f;
	explodeDelay = 999999.9f;
	explode1Time = 999999.9f;
	explode2Time = 999999.9f;
	explode3Time = 999999.9f;
	explode4Time = 999999.9f;
	portalTime = 999999.9f;
	portalStage = 0;
	recyclerGoTime = 999999.9f;
	aerial1Time = 999999.9f;
	aerial2Time = 999999.9f;
	sound8Time = 999999.9f;
	sound9Time = 999999.9f;
	sound12Time = 999999.9f;

	assert(NUM_UNITS == (unitBase + attacks[6] + defends[6]));
}


void BlackDog11Mission::Execute()
{
	int i = 0;
	user = GetPlayerHandle(); //assigns the player a handle every frame

	if (!startDone)
	{
		SetScrap(1,100);
		SetPilot(1,10);

		// setup the initial objectives
		ClearObjectives();
		AddObjective("bd11001.otf", WHITE);
		
		// don't do this part after the first shot
		startDone = BZTRUE;

		navRecycler = BuildObject("apcamr", 1, "recy_nav");
		SetName(navRecycler, "Recycler");

//#define TEST_EXPLOSION
#ifdef TEST_EXPLOSION
		SetPerceivedTeam(user, 2);
		goToPortalTime = GetTime();
#endif
	}
#ifndef TEST_EXPLOSION
	// is the recycler dead?
	if (!lost && GetHealth(recycler) <= 0.0f && !won)
	{
		lost = BZTRUE;
		if (navDistanceOk)
			FailMission(GetTime() + 1.0f, "bd11lseb.des");
		else
			FailMission(GetTime() + 1.0f, "bd11lsed.des");
	}

	// has the apc made it to the recycler yet?
	if (!objective1Complete && GetHealth(apc) <= 0.0f && !won && !lost)
	{
		lost = BZTRUE;
		FailMission(GetTime() + 1.0f, "bd11lsea.des");
	}

	if (!cameraComplete[0])
	{
		if (!cameraReady[0])
		{
			cameraReady[0] = BZTRUE;
			CameraReady();

			introSound = AudioMessage("bd11001.wav");
		}

		bool arrived = CameraPath("camera_start", 1000, 1600, recycler);

		if (CameraCancelled())
		{
			arrived = BZTRUE;
			StopAudioMessage(introSound);
		}
		if (arrived)
		{
			CameraFinish();
			cameraComplete[0] = BZTRUE;
		}
	}

	// is the apc close enough to the "pilot transfer point" ?
	if (!objective1Complete && !pilotTransferring)
	{
		float distance = GetDistance(apc, recycler);
		BZHandle enemy = GetNearestEnemy(apc);
		if (distance < 50.0f && GetDistance(apc, enemy) > 200.0f)
		{
			// stop the apc
			Stop(apc, 1);

			// spawn the pilot
			pilotTransferring = BZTRUE;
			pilot = BuildObject("aspilo", 1, apc);
			Retreat(pilot, recycler, 1);
		} 
	}

	if (pilotTransferring)
	{
		GiveMaxHealth(pilot);
		// has the pilot been killed?
		if (!lost && GetHealth(pilot) <= 0.0f && !won)
		{
			lost = BZTRUE;
			FailMission(GetTime() + 1.0f, "bd11lsec.des");
		}


		float dist = GetDistance(pilot, recycler);
		if (dist < 50.0)   //BD Recycler was a lot smaller in the Original TRO
		{
			pilotTransferring = BZFALSE;
			objective1Complete = BZTRUE;
			RemoveObject(pilot);
			pilot = NULL;
			GameObject *o = GameObjectHandle::GetObj(recycler);
		//	o->curPilot = (GameObjectClass *)*(PrjID*)"bspilo\0";
			o->curPilot = GameObjectClass::Find("bspilo\0");


			AiProcess::Attach(this, o);

			recyclerGoTime = GetTime() + 2.0f;
			// play sound
			AudioMessage("bd11002.wav");
		}
	}

	if (recyclerGoTime < GetTime())
	{
		toldToGo = BZTRUE;
		SetTeamNum(recycler, 1);
		recyclerGoTime = 999999.9f;
		// get the recycler moving to the geiser
		Goto(recycler, "recycler_path", 1);

		// setup drive 1 attack
		drive1Time = GetTime() + 20.0f;	
	}

	if (toldToGo && isAtEndOfPath(recycler, "recycler_path"))
	{
		toldToGo = BZFALSE;
		ClearObjectives();
		AddObjective("bd11001.otf", GREEN);
		AddObjective("bd11002.otf", WHITE);
		//Goto(recycler, GetHandle("geyser_1"));
	}

	if (!attacksSent && GetDistance(recycler, "wave_trigger") < 50.0f)
	{
		// start attacks
		attacksSent = BZTRUE;
		attackTimes[0] = GetTime() + 2 * 60.0f;
		attackTimes[1] = GetTime() + 5 * 60.0f;
		attackTimes[2] = GetTime() + 9 * 60.0f;
		attackTimes[3] = GetTime() + 14 * 60.0f;
		attackTimes[4] = GetTime() + 18 * 60.0f;
		attackTimes[5] = GetTime() + 21 * 60.0f;

		goToPortalTime = GetTime() + 26 * 60.0f;
		aerial1Time = GetTime() + 8 * 60.0f;
		aerial1Time = GetTime() + 13 * 60.0f;

		BZHandle h;
		h = BuildObject("cvltnk", 2, "drive_2");
		Attack(h, recycler);
		h = BuildObject("cvltnk", 2, "drive_2");
		Attack(h, recycler);
		h = BuildObject("cvltnk", 2, "drive_2");
		Attack(h, recycler);
		h = BuildObject("cvhraz", 2, "drive_2");
		Attack(h, recycler);
		h = BuildObject("cvhraz", 2, "drive_2");
		Attack(h, recycler);
	}

	if (objective1Complete)
	{
		float h = GetHealth(recycler);
		// check the recycler's health
		if (h > 0.5)
		{
			// do nothing
		}
		else if (!sound4Played && h > 0.25)
		{
			sound4Played = BZTRUE;
			sound4 = AudioMessage("bd11004.wav");
		}
		else if (!sound5Played && h > 0.15)
		{
			// stop any previous sounds
			StopAudioMessage(sound4);

			sound5Played = BZTRUE;
			sound5 = AudioMessage("bd11005.wav");
		}
		else if (!sound6Played && h > 0.0)
		{
			// stop any previous sounds
			StopAudioMessage(sound4);
			StopAudioMessage(sound5);

			sound6Played = BZTRUE;
			sound6 = AudioMessage("bd11006.wav");
		}
	}

	if (drive1Time < GetTime())
	{
		drive1Time = 999999.9f;

		BZHandle h = BuildObject("cvwalk", 2, "drive_1");
		Attack(h, recycler, 1);
		h = BuildObject("cvwalk", 2, "drive_1");
		Attack(h, recycler, 1);
		h = BuildObject("cvltnk", 2, "drive_1");
		Attack(h, recycler, 1);
		h = BuildObject("cvltnk", 2, "drive_1");
		Attack(h, recycler, 1);
	}

	if (aerial1Time < GetTime())
	{
		aerial1Time = 999999.9f;

		for (i = 0; i < 8; i++)
		{
			BZHandle h = BuildObject("cssold", 2, "aerial_1", 400);
			Attack(h, recycler);
		}
	}

	if (aerial2Time < GetTime())
	{
		aerial2Time = 999999.9f;

		for (i = 0; i < 8; i++)
		{
			BZHandle h = BuildObject("cssold", 2, "aerial_1", 400);
			Attack(h, recycler);
		}
	}

	for (i = 0; i < 6 && attacksSent; i++)
	{
		if (attackTimes[i] < GetTime())
		{
			int j = 0;

			// so this attack doesn't happen again
			attackTimes[i] = 999999.9f;

			// build the attackers
			int numAttackers = attacks[i+1] - attacks[i];
			for (j = 0; j < numAttackers; j++)
			{
				// build the enemy
				int unum = unitBase + attacks[i] + defends[i] + j;
				assert(enemy[unum] == BZINVALIDHANDLE);
				enemy[unum] = BuildObject(attackUnits[attacks[i] + j], 2, attackSpawns[i]);
				SetCloaked(enemy[unum]);
				Attack(enemy[unum], recycler);
			}

			// build the defenders
			int numDefenders = defends[i+1] - defends[i];
			for (j = 0; j < numDefenders; j++)
			{
				BZHandle h = BZINVALIDHANDLE;
				int unum = unitBase + attacks[i+1] + defends[i] + j;
				assert(enemy[unum] == BZINVALIDHANDLE);
				h = enemy[unum] = BuildObject(defendUnits[defends[i] + j], 2, defendSpawns[i]);
				SetCloaked(enemy[unum]);
				int anum = unitBase + attacks[i] + defends[i] + (j % numAttackers);
				assert(enemy[anum] != BZINVALIDHANDLE);
				Defend2(h, enemy[anum], 1);
			}
		}
	}
#endif
	if (goToPortalTime < GetTime())
	{
		goToPortalTime = 999999.9f;
		ClearObjectives();
		AddObjective("bd11002.otf", GREEN);
		objective2Complete = BZTRUE;

		// spawn the nav
		//navEnd = BuildObject("apcamr", 1, "nav_end");
		AudioMessage("bd11007.wav");
		sound8Time = GetTime() + 3.0f;
	}

	if (sound8Time < GetTime())
	{
		sound8Time = 999999.9f;
		sound8 = AudioMessage("bd11008.wav");
	}

	if (sound8 != BZINVALIDHANDLE && IsAudioMessageDone(sound8))
	{
		sound8 = NULL;
		sound9Time = GetTime() + 5.0f;
	}

	if (sound9Time < GetTime())
	{
		sound9Time = 999999.9f;
		AudioMessage("bd11009.wav");
		sound12Time = GetTime() + 5.0f;
	}

	if (sound12Time < GetTime())
	{
		sound12Time = 999999.9f;
		sound12 = AudioMessage("bd11012.wav");
	}

	if (sound12 != 0 && IsAudioMessageDone(sound12))
	{
		sound12 = 0;
		
		ClearObjectives();
		AddObjective("bd11003.otf", WHITE);

		SetObjectiveOn(portal);

		// set up bombing sequence
		explode1Time = GetTime() + 90.0f;
		explode2Time = GetTime() + 90.0f + 2.0f;
		explode3Time = GetTime() + 90.0f + 4.0f;
		explode4Time = GetTime() + 90.0f + 6.0f;

		// start the timer
		StartCockpitTimer(90, 30, 10);
		cockpitTimerActive = BZTRUE;
	}

	if (cockpitTimerActive && GetCockpitTimer() <= 0.0)
	{
		cockpitTimerActive = BZFALSE;
		HideCockpitTimer();
		navDistanceOk = BZTRUE;

		if (explodeTime == 999999.9f)
		{
			// player did not reach portal early
			// start portal detonation sequence
			sound10 = AudioMessage("bd11010.wav");
			explodeTime = GetTime() + 30.0f;
			cameraDestructTime = explodeTime - 1.0f;
			ClearObjectives();
			AddObjective("bd11004.otf", RED);
			StartCockpitTimer(30, 30, 30);
			SetTarget(user, portal);
			portalOut(portal, 0.0f);
			StartEarthquake(0.0f);
		}
	}

	if (!explodePortal && explode1Time < 999999.9f && explodeTime == 999999.9f && IsWithin(user, portal, 200.0f))
	{
		// cancel the main timer
		cockpitTimerActive = BZFALSE;
		navDistanceOk = BZTRUE;

		// player reached portal early
		// start portal detonation sequence
		sound10 = AudioMessage("bd11010.wav");
		explodeTime = GetTime() + 30.0f;
		cameraDestructTime = explodeTime - 1.0f;
		ClearObjectives();
		AddObjective("bd11004.otf", RED);
		StartCockpitTimer(30, 30, 30);
		SetTarget(user, portal);
		portalOut(portal, 0.0f);
		StartEarthquake(1.0f);
	}

	if (!explodePortal && explodeTime < 999999.9f)
	{
		// 0 at beginning, 1 at end
		float ratio = 1.0f - (explodeTime - GetTime()) / 30.0f;
		float noise = Clamp((1.0f - ratio) * (1.0f - ratio) + 0.2f * ratio * Noise1D(10.0f * GetTime()), 0.0f, 1.0f);
		if (rand() < int(RAND_MAX / 2 * ratio * ratio))
			portalIn(portal, noise);
		else
			portalOut(portal, noise);
		UpdateEarthQuake(4.0f * ratio * ratio);
	}

	// 4 explosions
	if (explode1Time < GetTime())
	{
		explode1Time = 999999.9f;
		MakeExplosion("dw_1", "xpltrsk");
	}

	if (explode2Time < GetTime())
	{
		explode2Time = 999999.9f;
		MakeExplosion("dw_2", "xpltrsk");
	}

	if (explode3Time < GetTime())
	{
		explode3Time = 999999.9f;
		MakeExplosion("dw_3", "xpltrsk");
	}

	if (explode4Time < GetTime())
	{
		explode4Time = 999999.9f;
		MakeExplosion("dw_4", "xpltrsk");
	}

	if (cameraDestructTime < GetTime())
	{
		cameraDestructTime = 999999.9f;
		CameraReady();
		CameraPath("camera_destruct", 1000, 0, portal);
	}

	if (explodeTime < GetTime())
	{
		explodeTime = 999999.9f;
		explodeDelay = GetTime() + 3.0f;
		ColorFade_SetFade(2.0f, 0.5f, 255, 255, 255);
		explodePortal = BZTRUE;
		// using large/AGP assets
		// (alternative was "xpltrsp")
		MakeExplosion(portal, "xpltrso");
	}

	if (explodeDelay < GetTime())
	{
		// finish the camera
		CameraFinish();

		explodeDelay = 999999.9f;

		winMessage = AudioMessage("bd11011.wav");

		ClearObjectives();
	}

	if (winMessage != 0 && !won && !lost)
	{
		if (IsAudioMessageDone(winMessage))
		{
			won = BZTRUE;
			SucceedMission(GetTime() + 3.0f, "bd11win.des");
		}
	}

	if (GetHealth(portal) <= 0.0f && !explodePortal && !won && !lost)
	{
		lost = BZTRUE;
		FailMission(GetTime() + 1.0f, "bd11lsee.des");
	}
}

const std::set<PrjID>& BlackDog11Mission::GetPreloadGameObjects()
{
	static std::set<PrjID> retval = AiMission::PrjIDFromStrings(
	{ "apcamr", "aspilo", "cvltnk", "cvhraz", "cvwalk", "cssold", "cvhtnk", "cvfigh", "cvtnk" }
	);
	return retval;
}
