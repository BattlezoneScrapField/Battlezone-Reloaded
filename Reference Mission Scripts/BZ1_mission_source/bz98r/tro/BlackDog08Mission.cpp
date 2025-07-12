

#include "AiMission.h"
#include "AiProcess.h"
#include "ScriptUtils.h"
#include "audiomessage.h"
#include "LabelMap.h"
#include "scrapfield.h"



#define SECONDS_TO_REPROGRAM_PORTAL	(3 * 60)
#define PILOT_SECONDS_WAIT_BEFORE_HEADING_TO_PORTAL 60
#define SECONDS_BEFORE_APC_APPEARS_FROM_PORTAL 90

const char * attackers[10] =
{
	"cvltnk",
	"cvltnk",
	"cvltnk",
	"cvfigh",
	"cvfigh",
	"cvfigh",
	"cvfigh",
	"cvfigh",
	"cvtnk",
	"cvltnk"
};

/*
	BlackDog08Mission
*/

class BlackDog08Mission : public AiMission {
	DECLARE_RTIME(BlackDog08Mission)
public:
	BlackDog08Mission();
	~BlackDog08Mission();

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
				arrived,

				// has the pilot spawned?
				pilotSpawned1,
				pilotSpawned2,

				// portal been reprogrammed?
				portalReprogrammed,

				// apc heading back?
				apcHeadingBack,

				// apc commandeered?
				apcCommandeered,

				// schedule loses?
				scheduleLose1,
				scheduleLose2,
				scheduleLose3,

				// have we lost?
				lost, won,

				b_last;
		};
		bool b_array[19];
	};

	// floats
	union {
		struct {
			float
				secondCameraTime,
				activateTime,
				attackWaveTime,
				apcTime,
				apcPilotTime1,
				apcPilotTime2,
				apcGoBackTime,
				sound3Time,
				f_last;
		};
		float f_array[8];
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
				factory,
				command,
				waveHandle,
				
				// buildings
				portal,

				// nav beacons
				navPortal,
				navBase,

				// pilots
				pilot,

				h_last;
		};
		BZHandle h_array[10];
	};

	// integers
	union {
		struct {
			int32_t
				// *** Sounds
				loseSound2,
				loseSound3,
				winSound,
				introSound,
				intro2Sound,

				waveCount,
				i_last;
		};
		int32_t i_array[6];
	};
};

IMPLEMENT_RTIME(BlackDog08Mission)

BlackDog08Mission::BlackDog08Mission()
{
}

BlackDog08Mission::~BlackDog08Mission()
{
}

bool BlackDog08Mission::Load(file fp)
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

bool BlackDog08Mission::PostLoad(void)
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

bool BlackDog08Mission::Save(file fp)
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

void BlackDog08Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

void BlackDog08Mission::AddObject(BZHandle h)
{
}

void BlackDog08Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

void BlackDog08Mission::Setup()
{
	int i = 0;
	startDone = BZFALSE;
	objective1Complete = BZFALSE;
	objective2Complete = BZFALSE;
	objective3Complete = BZFALSE;
	for (i = 0; i < 2; i++)
		cameraReady[i] = cameraComplete[i] = BZFALSE;
	arrived = BZFALSE;
	pilotSpawned1 = BZFALSE;
	pilotSpawned2 = BZFALSE;
	portalReprogrammed = BZFALSE;
	apcHeadingBack = BZFALSE;
	scheduleLose1 = BZFALSE;
	scheduleLose2 = BZFALSE;
	scheduleLose3 = BZFALSE;
	apcCommandeered = BZFALSE;

	// units
	recycler = GetHandle("recycler");
	portal = GetHandle("portal");
	command = GetHandle("command");
	factory = GetHandle("factory");
	navPortal = GetHandle("nav_portal");
	SetName(navPortal, GetTextLabel("names", "Portal"));
	navBase = GetHandle("nav_base");
	SetName(navBase, "Black Dog Base");
	apc = NULL;
	waveHandle = NULL;

	// sounds
	introSound = NULL;
	intro2Sound = NULL;
	winSound = NULL;
	loseSound2 = NULL;
	loseSound3 = NULL;

	// ints
	waveCount = 0;

	// times
	secondCameraTime = 999999.9f;
	attackWaveTime = 999999.9f;
	apcTime = 999999.9f;
	apcPilotTime1 = 999999.9f;
	apcPilotTime2 = 999999.9f;
	apcGoBackTime = 999999.9f;
	sound3Time = 999999.9f;
	activateTime = 999999.9f;
}


void BlackDog08Mission::Execute()
{
	int i = 0;
	user = GetPlayerHandle(); //assigns the player a handle every frame

	if (!startDone)
	{
		SetScrap(1, 100);
		SetPilot(1, 10);
		VECTOR_3D scrappos={1236,68,101013};
		MakeScrapField(scrappos,2);

		// don't do this part after the first shot
		startDone = BZTRUE;
		//#define TEST_PORTAL
#ifdef TEST_PORTAL
		SetPerceivedTeam(user, 2);
#endif
	}

	if (!cameraComplete[0])
	{
		if (!cameraReady[0])
		{
			cameraReady[0] = BZTRUE;
			CameraReady();

			introSound = AudioMessage("bd08001.wav");
		}

		bool seqDone = BZFALSE;
		if (!arrived)
			arrived = CameraPath("path_camera_intro", 2000, 1500, user);
		if (arrived && IsAudioMessageDone(introSound))
			seqDone = BZTRUE;

		if (CameraCancelled())
		{
			seqDone = BZTRUE;
			StopAudioMessage(introSound);
		}
		if (seqDone)
		{
			arrived = BZFALSE;
			CameraFinish();
			cameraComplete[0] = BZTRUE;
			secondCameraTime = GetTime() + 25.0f;
		}
	}

	if (secondCameraTime < GetTime() && !cameraComplete[1])
	{
		if (!cameraReady[1])
		{
			cameraReady[1] = BZTRUE;
			CameraReady();

			intro2Sound = AudioMessage("bd08002.wav");

			ClearObjectives();
			AddObjective("bd08001.otf", WHITE);

			// attack wave
			activateTime = GetTime() + 0.5f;
#ifndef TEST_PORTAL
			apcTime = GetTime() + SECONDS_BEFORE_APC_APPEARS_FROM_PORTAL;
#else
			apcTime = GetTime() + 15.0f;
#endif
		}

		arrived = CameraPath("path_portalcam", 4000, 1000, portal);

		if (arrived ||
			CameraCancelled())
		{
			CameraFinish();
			cameraComplete[1] = BZTRUE;
			//StopAudioMessage(intro2Sound);
			//sound3Time = GetTime() + 5.0f;
		}
	}

	if (activateTime < GetTime())
	{
		activatePortal(portal, false);
		if (isPortalActive(portal))
		{
			attackWaveTime = GetTime() + 1.0f;
			activateTime = 999999.9f;
		}
	}
#ifndef TEST_PORTAL
	if (attackWaveTime < GetTime())
	{
		if (apcTime < GetTime() + 45.0f)
		{
			// temporarily disable the attack 
			// wave so that the apc can arrive
			attackWaveTime = 999999.9f;
		}
		else
		{
			BZHandle h = BuildObjectAtPortal(attackers[rand() % 10], 2, portal);
			if ((rand() % 100) < 50)
				Goto(h, "attack_path1", 1);
			else
				Goto(h, "attack_path2", 1);
			waveCount++;
			if (waveCount < 2)
				attackWaveTime = GetTime() + 4.0f;
			else
			{
				waveCount = 0;
				attackWaveTime = GetTime() + 30.0f;
			}
		}
	}
#endif
	if (apcTime < GetTime())
	{
		apcTime = 999999.9f;
		apc = BuildObjectAtPortal("cvapc", 2, portal);
		SetPerceivedTeam(apc, 0);

		Goto(apc, "portal_out", 1);
		attackWaveTime = GetTime() + 30.0f;
		apcPilotTime1 = GetTime() + 20.0f;
		sound3Time = GetTime() + 1.0f;
	}

	if (sound3Time < GetTime())
	{
		sound3Time = 999999.9f;
		AudioMessage("bd08003.wav");
	}

	if (apcPilotTime1 < GetTime())
	{
		apcPilotTime1 = 999999.9f;
		Stop(apc, 1);

		GameObject *o = GameObjectHandle::GetObj(apc);
		assert(o != NULL);
		o->curPilot = 0;
		pilot = BuildObject("cspilo", 2, apc); //PilotGetOut(apc);
		SetPerceivedTeam(apc, 0);

		Retreat(pilot, portal, 1);
		pilotSpawned1 = BZTRUE;

		ClearObjectives();
		AddObjective("bd08001.otf", WHITE);
		AddObjective("bd08002.otf", WHITE);

		SetObjectiveOn(apc);
	}

	if (pilotSpawned1)
	{
		if (isTouching(pilot, portal))
		{
			RemoveObject(pilot);
			pilotSpawned1 = BZFALSE;
			cockpitTimer.SetTimerDown(SECONDS_TO_REPROGRAM_PORTAL);
			cockpitTimer.ShowTimer();
#ifndef TEST_PORTAL
			apcPilotTime2 = GetTime() + SECONDS_TO_REPROGRAM_PORTAL;
#else
			apcPilotTime2 = GetTime() + 15.0f;
#endif
		}
		else if (GetHealth(pilot) <= 0.0)
		{
			// pilot killed before reprogramming the portal
			scheduleLose2 = BZTRUE;
			pilotSpawned1 = BZFALSE;
		}
	}

	if (apcPilotTime2 < GetTime())
	{
		cockpitTimer.HideTimer();
		apcPilotTime2 = 999999.9f;
		pilot = BuildObject("cspilo", 2, "spawn_pilot");
		GameObject *o = GameObjectHandle::GetObj(apc);
		if (o)
		{
			o->curPilot = GameObjectClass::Find("cspilo");//(GameObjectClass *)*(PrjID*)"cspilo";
		}
		RemovePilot(apc);
		SetPerceivedTeam(apc, 0);

		Retreat(pilot, apc, 1);
		pilotSpawned2 = BZTRUE;
		portalReprogrammed = BZTRUE;
		AudioMessage("bd08004.wav");
		deactivatePortal(portal);

		ClearObjectives();
		AddObjective("bd08002.otf", GREEN);
		AddObjective("bd08003.otf", WHITE);

		attackWaveTime = 999999.9f;
	}

	if (pilotSpawned2 && !IsValid(pilot))
	{
		// Pilot was killed outside vehicle.  Make vehicle pilotable
	}

	if (pilotSpawned2 && GetTeamNum(apc) == 1)
	{
		pilotSpawned2 = BZFALSE;
		Attack(pilot, apc);
	}

	if (pilotSpawned2 && GetHealth(pilot) <= 0.0f)
	{
		pilot = NULL;
		pilotSpawned2 = BZFALSE;
	}

	if (pilotSpawned2 && isTouching(pilot, apc))
	{
		pilotSpawned2 = BZFALSE;
		apcGoBackTime = GetTime() + PILOT_SECONDS_WAIT_BEFORE_HEADING_TO_PORTAL;
		GameObject *o = GameObjectHandle::GetObj(apc);
		assert(o != NULL);
		if (o->curPilot == 0)
		{
			o->curPilot = GameObjectClass::Find("cspilo");//(GameObjectClass *)*(PrjID*)"cspilo";
			AiProcess::Attach(this, o);
			RemoveObject(pilot);
			pilot = NULL;
			SetPerceivedTeam(apc, 0);
		}
		else
		{
			Attack(pilot, user);
		}
	}

	if (apcGoBackTime < GetTime())
	{
		apcGoBackTime = 999999.9f;

		if (IsAliveAndPilot(apc))
		{
			apcHeadingBack = BZTRUE;
			activatePortal(portal, true);
//			Retreat(apc, "portal_out", 1);
			Goto(apc, portal, 1);
			
		}
	}

	if (apcHeadingBack && GetTeamNum(apc) == 1)
	{
		apcHeadingBack = BZFALSE;
	}

	if (apcHeadingBack && !lost && !won)
	{
		if (isTouching(apc, portal))
		{
			RemoveObject(apc);
			apc = NULL;
			apcHeadingBack = BZFALSE;

			// the player has lost
			scheduleLose2 = BZTRUE;
		}
	}

	// have we lost any significant units?
	if ((GetHealth(recycler) <= 0.0f ||
		//GetHealth(factory) <= 0.0f ||
		GetHealth(command) <= 0.0f) &&
		!lost && !won)
	{
		scheduleLose2 = BZTRUE;
	}
	else if (apc != BZINVALIDHANDLE &&
		GetHealth(apc) <= 0.0f &&
		!lost && !won)
	{
		apc = NULL;
		scheduleLose3 = BZTRUE;
	}

	if (scheduleLose2)
	{
		scheduleLose2 = BZFALSE;
		loseSound2 = AudioMessage("bd08006.wav");
		lost = BZTRUE;
		
	}

	if (loseSound2 != BZINVALIDHANDLE)
	{
		if (IsAudioMessageDone(loseSound2))
		{
			loseSound2 = NULL;
			FailMission(GetTime() + 1.0f, "bd08lsea.des");
		}
	}

	if (scheduleLose3)
	{
		scheduleLose3 = BZFALSE;
		loseSound3 = AudioMessage("bd08006.wav");
		lost = BZTRUE;
	}

	if (loseSound3 != BZINVALIDHANDLE)
	{
		if (IsAudioMessageDone(loseSound3))
		{
			loseSound3 = NULL;
			FailMission(GetTime() + 1.0f, "bd08lseb.des");
		}
	}

	if (apc != BZINVALIDHANDLE && !apcCommandeered)
	{
		if (GetTeamNum(apc) == 1)
		{
			apcCommandeered = BZTRUE;
		}
	}

	if (apcCommandeered &&
		portalReprogrammed &&
		winSound == BZINVALIDHANDLE && !won && !lost)
	{
		won = BZTRUE;
		winSound = AudioMessage("bd08007.wav");
	}

	if (winSound != BZINVALIDHANDLE && IsAudioMessageDone(winSound))
	{
		SucceedMission(GetTime() + 1.0f, "bd08win.des");
		winSound = BZINVALIDHANDLE;
	}

	// has the portal been destroyed?
	if (GetHealth(portal) <= 0.0 && !won && !lost)
	{
		lost = BZTRUE;
		FailMission(GetTime() + 1.0f, "bd08lsec.des");
	}
}

const std::set<PrjID>& BlackDog08Mission::GetPreloadGameObjects()
{
	static std::set<PrjID> retval = AiMission::PrjIDFromStrings(
	{ "cspilo", "cvapc", "cvltnk", "cvfigh", "cvtnk" }
	);
	return retval;
}
