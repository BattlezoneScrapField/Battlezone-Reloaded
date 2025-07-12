#include "GameCommon.h"
#include "AiCommon.h"
#include "AiMission.h"
#include "AiProcess.h"
#include "PowerUp.h"
#include "ScriptUtils.h"

char *attackers[10] = 
{
	"cvtnk",
	"cvtnk",
	"cvltnk",
	"cvfigh",
	"cvfigh",
	"cvfigh",
	"cvfigh",
	"cvfigh",
	"cvrckt",
	"cvhraz"
};

/*
	BlackDog08Mission
*/

class BlackDog08Mission : public AiMission {
	DECLARE_RTIME(BlackDog08Mission)
public:
	BlackDog08Mission();
	~BlackDog08Mission();

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
			Handle
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
		Handle h_array[10];
	};

	// integers
	union {
		struct {
			int
				// *** Sounds
				loseSound2,
				loseSound3,
				winSound,
				introSound,
				intro2Sound,

				waveCount,
				i_last;
		};
		int i_array[6];
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

void BlackDog08Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

void BlackDog08Mission::AddObject(Handle h)
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
	startDone = FALSE;
	objective1Complete = FALSE;
	objective2Complete = FALSE;
	objective3Complete = FALSE;
	for (i = 0; i < 2; i++)
		cameraReady[i] = cameraComplete[i] = FALSE;
	arrived = FALSE;
	pilotSpawned1 = FALSE;
	pilotSpawned2 = FALSE;
	portalReprogrammed = FALSE;
	apcHeadingBack = FALSE;
	scheduleLose1 = FALSE;
	scheduleLose2 = FALSE;
	scheduleLose3 = FALSE;
	apcCommandeered = FALSE;

	// units
	recycler = GetHandle("recycler");
	portal = GetHandle("portal");
	command = GetHandle("command");
	factory = GetHandle("factory");
	navPortal = GetHandle("nav_portal");
	SetName(navPortal, "Portal");
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
		SetScrap(1,100);
		SetPilot(1,10);

		// don't do this part after the first shot
		startDone = TRUE;
//#define TEST_PORTAL
#ifdef TEST_PORTAL
		SetPerceivedTeam(user, 2);
#endif
	}

	if (!cameraComplete[0])
	{
		if (!cameraReady[0])
		{
			cameraReady[0] = TRUE;
			CameraReady();

			introSound = AudioMessage("bd08001.wav");
		}

		bool seqDone = FALSE;
		if (!arrived)
			arrived = CameraPath("path_camera_intro", 800, 1500, user);
		if (arrived && IsAudioMessageDone(introSound))
			seqDone = TRUE;

		if (CameraCancelled())
		{
			seqDone = TRUE;
			StopAudioMessage(introSound);
		}
		if (seqDone)
		{
			arrived = FALSE;
			CameraFinish();
			cameraComplete[0] = TRUE;
			secondCameraTime = GetTime() + 25.0;
		}
	}

	if (secondCameraTime < GetTime() && !cameraComplete[1])
	{
		if (!cameraReady[1])
		{
			cameraReady[1] = TRUE;
			CameraReady();

			intro2Sound = AudioMessage("bd08002.wav");

			ClearObjectives();
			AddObjective("bd08001.otf", WHITE);

			// attack wave
			activateTime = GetTime() + 0.5;
#ifndef TEST_PORTAL
			apcTime = GetTime() + 90.0f;
#else
			apcTime = GetTime() + 15.0f;
#endif
		}

		arrived = CameraPath("path_portalcam", 4000, 1000, portal);
		
		if (arrived ||
			CameraCancelled())
		{
			CameraFinish();
			cameraComplete[1] = TRUE;
			//StopAudioMessage(intro2Sound);
			//sound3Time = GetTime() + 5.0f;
		}
	}

	if (activateTime < GetTime())
	{
		activatePortal(portal, false);
		if (isPortalActive(portal))
		{
			attackWaveTime = GetTime() + 1.0;
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
			Handle h = BuildObjectAtPortal(attackers[rand() % 10], 2, portal);
			if (rand() % 100 < 50)
				Goto(h, "attack_path1", 1);
			else
				Goto(h, "attack_path2", 1);
			waveCount++;
			if (waveCount < 4)
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
		_ASSERTMSG0(apc != NULL, "Failed to create APC");
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
		_ASSERTE(o != NULL);
		o->curPilot = 0;
		pilot = BuildObject("cspilo", 2, apc); //PilotGetOut(apc);
		SetPerceivedTeam(apc, 0);
		
		Retreat(pilot, portal, 1);
		pilotSpawned1 = TRUE;

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
			pilotSpawned1 = FALSE;
#ifndef TEST_PORTAL
			apcPilotTime2 = GetTime() + 9 * 60.0;
#else
			apcPilotTime2 = GetTime() + 15.0f;
#endif
		}
		else if (GetHealth(pilot) <= 0.0)
		{
			// pilot killed before reprogramming the portal
			scheduleLose2 = TRUE;
			pilotSpawned1 = FALSE;
		}
	}

	if (apcPilotTime2 < GetTime())
	{
		apcPilotTime2 = 999999.9f;
		pilot = BuildObject("cspilo", 2, "spawn_pilot");
		RemovePilot(apc);
		Retreat(pilot, apc, 1);
		pilotSpawned2 = TRUE;
		portalReprogrammed = TRUE;
		AudioMessage("bd08004.wav");
		deactivatePortal(portal);

		ClearObjectives();
		AddObjective("bd08002.otf", GREEN);
		AddObjective("bd08003.otf", WHITE);

		attackWaveTime = 999999.9f;
	}

	if (pilotSpawned2 && GetTeam(apc) == 1)
	{
		pilotSpawned2 = FALSE;
		Attack(pilot, apc);
	}

	if (pilotSpawned2 && GetHealth(pilot) <= 0.0f)
	{
		pilot = NULL;
		pilotSpawned2 = FALSE;
	}

	if (pilotSpawned2 && isTouching(pilot, apc))
	{
		pilotSpawned2 = FALSE;
		apcGoBackTime = GetTime() + 25.0f;
		GameObject *o = GameObjectHandle::GetObj(apc);
		_ASSERTE(o != NULL);
		if(o->curPilot == 0)
		{
			AiProcess::Attach(this, o);
			o->curPilot = *(PrjID*)"cspilo";
			RemoveObject(pilot);
			pilot = NULL;
			SetPerceivedTeam(apc, 2);
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
			apcHeadingBack = TRUE;
			activatePortal(portal, true);
			Retreat(apc, "portal_in", 1);
		}
	}

	if (apcHeadingBack && GetTeamNum(apc) == 1)
	{
		apcHeadingBack = FALSE;
	}

	if (apcHeadingBack && !lost && !won)
	{
		if (isTouching(apc, portal))
		{
			RemoveObject(apc);
			apc = NULL;
			apcHeadingBack = FALSE;

			// the player has lost
			scheduleLose2 = TRUE;
		}
	}

	// have we lost any significant units?
	if ((GetHealth(recycler) <= 0.0f ||
		//GetHealth(factory) <= 0.0f ||
		GetHealth(command) <= 0.0f) &&
		!lost && !won)
	{
		scheduleLose2 = TRUE;
	}
	else if (apc != NULL &&
		GetHealth(apc) <= 0.0f &&
		!lost && !won)
	{
		apc = NULL;
		scheduleLose3 = TRUE;
	}

	if (scheduleLose2)
	{
		scheduleLose2 = FALSE;
		loseSound2 = AudioMessage("bd08006.wav");
		lost = TRUE;
		
	}

	if (loseSound2 != NULL)
	{
		if (IsAudioMessageDone(loseSound2))
		{
			loseSound2 = NULL;
			FailMission(GetTime() + 1.0, "bd08lsea.des");
		}
	}

	if (scheduleLose3)
	{
		scheduleLose3 = FALSE;
		loseSound3 = AudioMessage("bd08006.wav");
		lost = TRUE;
	}

	if (loseSound3 != NULL)
	{
		if (IsAudioMessageDone(loseSound3))
		{
			loseSound3 = NULL;
			FailMission(GetTime() + 1.0, "bd08lseb.des");
		}
	}

	if (apc != NULL && !apcCommandeered)
	{
		if (GetTeamNum(apc) == 1)
		{
			apcCommandeered = TRUE;
		}
	}

	if (apcCommandeered &&
		portalReprogrammed &&
		winSound == NULL && !won && !lost)
	{
		won = TRUE;
		winSound = AudioMessage("bd08007.wav");
	}

	if (winSound != NULL && IsAudioMessageDone(winSound))
	{
		SucceedMission(GetTime() + 1.0, "bd08win.des");
		winSound = NULL;
	}

	// has the portal been destroyed?
	if (GetHealth(portal) <= 0.0 && !won && !lost)
	{
		lost = TRUE;
		FailMission(GetTime() + 1.0, "bd08lsec.des");
	}
}