#include "GameCommon.h"
#include "AiCommon.h"
#include "AiMission.h"
#include "AiProcess.h"
#include "PowerUp.h"
#include "ScriptUtils.h"
#include "ColorFade.h"

/*
	Chinese01Mission
*/

class Chinese01Mission : public AiMission {
	DECLARE_RTIME(Chinese01Mission)
public:
	Chinese01Mission();
	~Chinese01Mission();

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
				objective4Complete,
				objective5Complete,

				// cameras
				cameraReady[2], cameraComplete[2],

				// has the hangar been identified?
				hangarIdentified,

				// has the recycler been destroyed?
				recyclerDeployed,

				// tug near the nav?
				tugNearNav,

				// second wave of arial units spawned?
				arialsSpawned,

				// camera focus on explosion?
				focusOnExplosion,
				doingExplosion,
				doNuke,

				// sounds
				sound12Played,

				// decoys spawned?
				decoySpawned,

				// won or lost?
				won, lost,
				
				b_last;
		};
		bool b_array[21];
	};

	// floats
	union {
		struct {
			float
				openingSoundTime,
				armourySoundTime,
				wave1Time,
				wave2Time,
				wave3Time,
				wave4Time,
				wave5Time,
				arial1Time,
				arial2Time,
				tugTime,
				explodeTime,
				f_last;
		};
		float f_array[11];
	};

	// handles
	union {
		struct {
			Handle
				// the user
				user,

				// units
				recycler,
				tug,
				escort1,
				escort2,
				detectors[10],

				// buildings
				hangar,
				commTower,
				bbTower,

				// ??
				relic,
				
				// nav beacons
				navStart,
				navTug,
				navEnd,

				// place holder
				h_last;
		};
		Handle h_array[22];
	};

	// integers
	union {
		struct {
			int
				// sounds
				openingSound,
				hangarSound,
				armourySound,
				tugDiedSound,
				detectedSound,
				failedSound,
				
				
				i_last;
		};
		int i_array[6];
	};
};

IMPLEMENT_RTIME(Chinese01Mission)

Chinese01Mission::Chinese01Mission()
{
}

Chinese01Mission::~Chinese01Mission()
{
}

bool Chinese01Mission::Load(file fp)
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

bool Chinese01Mission::PostLoad(void)
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

bool Chinese01Mission::Save(file fp)
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

void Chinese01Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

void Chinese01Mission::AddObject(Handle h)
{
}

void Chinese01Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

void Chinese01Mission::Setup()
{
	int i = 0;
	startDone = FALSE;
	objective1Complete = FALSE;
	objective2Complete = FALSE;
	objective3Complete = FALSE;
	objective4Complete = FALSE;
	objective5Complete = FALSE;
	hangarIdentified = FALSE;
	recyclerDeployed = FALSE;
	tugNearNav = FALSE;
	arialsSpawned = FALSE;
	focusOnExplosion = FALSE;
	doingExplosion = FALSE;
	doNuke = FALSE;
	sound12Played = FALSE;
	decoySpawned = FALSE;

	// cameras
	for (i = 0; i < 2; i++)
	{
		cameraReady[i] = FALSE;
		cameraComplete[i] = FALSE;
	}
	
	// units
	hangar = GetHandle("target_1");
	commTower= GetHandle("target_2");
	bbTower = GetHandle("bb_tower");
	recycler = NULL;
	tug = NULL;
	relic = NULL;
	escort1 = NULL;
	escort2 = NULL;
	detectors[0] = GetHandle("sp_turret_1");
	detectors[1] = GetHandle("sp_turret_2");
	detectors[2] = GetHandle("sp_turret_3");
	detectors[3] = GetHandle("sp_tower_1");
	detectors[4] = GetHandle("sp_tower_2");
	detectors[5] = GetHandle("sp_tower_3");
	detectors[6] = GetHandle("sp_tower_4");
	detectors[7] = GetHandle("sp_tower_5");
	detectors[8] = GetHandle("sp_tower_6");
	detectors[9] = GetHandle("sp_tower_7");
	
	// navs
	navStart = NULL;
	navTug = NULL;
	navEnd = NULL;

	// sounds
	openingSound = NULL;
	hangarSound = NULL;
	armourySound = NULL;
	tugDiedSound = NULL;
	failedSound = NULL;
	detectedSound = NULL;

	// times
	openingSoundTime = 999999.9f;
	armourySoundTime = 999999.9f;
	wave1Time = 999999.9f;
	wave2Time = 999999.9f;
	wave3Time = 999999.9f;
	wave4Time = 999999.9f;
	wave5Time = 999999.9f;
	arial1Time = 999999.9f;
	arial2Time = 999999.9f;
	tugTime = 999999.9f;
	explodeTime = 999999.9f;
}

void Chinese01Mission::Execute()
{
	int i = 0;
	user = GetPlayerHandle(); //assigns the player a handle every frame

	if (!startDone)
	{
		SetScrap(1,0);
		SetPilot(1,10);

		// don't do this part after the first shot
		startDone = TRUE;

		openingSoundTime = GetTime() + 5.0;

		// disable all cloaking for this mission
		enableAllCloaking(FALSE);
#if 0
		relic = BuildObject("obdata", 0, "relic_loc");
		SetObjectiveOn(relic);
		tug = BuildObject("svhaula", 2, user);
		//nuke = BuildObject("obdata", 0, tug);
		//setCargo(tug, nuke);
		//tugEquipedWithNuke = TRUE;
		SetObjectiveOn(tug);
		SetPerceivedTeam(user, 2);
		objective3Complete = TRUE;
		SetObjectiveOn(hangar);
#endif
	}
#if 1
	if (openingSoundTime < GetTime())
	{
		openingSoundTime = 999999.9f;

		openingSound = AudioMessage("ch01001.wav");
	}

	if (openingSound != NULL && IsAudioMessageDone(openingSound))
	{
		openingSound = NULL;

		// spawn the nav camera
		navStart = BuildObject("apcamr", 1, "nav_start");
		SetName(navStart, "CCA Base");

		ClearObjectives();
		AddObjective("ch01001.otf", WHITE);
	}

	if (!hangarIdentified && IsInfo(hangar))
	{
		hangarIdentified = TRUE;

		// play the message
		hangarSound = AudioMessage("ch01002.wav");

		// update objectives
		ClearObjectives();
		AddObjective("ch01001.otf", GREEN);
		objective1Complete = TRUE;
	}

	if (hangarSound != NULL && IsAudioMessageDone(hangarSound))
	{
		hangarSound = NULL;

		armourySoundTime = GetTime() + 15.0f;
	}

	if (armourySoundTime < GetTime())
	{
		armourySoundTime = 999999.9f;

		armourySound = AudioMessage("ch01003.wav");
	}

	if (armourySound != NULL && IsAudioMessageDone(armourySound))
	{
		armourySound = NULL;

		// spawn the armoury
		BuildObject("cvslfb", 1, "armoury");
		AudioMessage("ch01004.wav");

		// update objectives
		ClearObjectives();
		AddObjective("ch01001.otf", GREEN);
		AddObjective("ch01002.otf", WHITE);

		AddScrap(1, 99);
	}

	if (!objective2Complete && GetHealth(commTower) <= 0.0f)
	{
		objective2Complete = TRUE;

		AudioMessage("ch01005.wav");

		recycler = BuildObject("cvrecyd", 1, "recycler");
		AddScrap(1, 50);

		// update objectives
		ClearObjectives();
		AddObjective("ch01001.otf", GREEN);
		AddObjective("ch01002.otf", GREEN);
	}

	if (recycler != NULL && !recyclerDeployed && isDeployed(recycler))
	{
		recyclerDeployed = TRUE;

		wave1Time = GetTime() + 60.0f;
	}

	if (wave1Time < GetTime())
	{
		wave1Time = 999999.9f;

		// spawn the first wave
		Handle h;
		h = BuildObject("svfigh", 2, "wave_1");
		Goto(h, "follow_1", 1);
		h = BuildObject("svfigh", 2, "wave_1");
		Goto(h, "follow_1", 1);
		h = BuildObject("svfigh", 2, "wave_1");
		Goto(h, "follow_1", 1);
		h = BuildObject("svfigh", 2, "wave_1");
		Goto(h, "follow_1", 1);
		h = BuildObject("svtank", 2, "wave_1");
		Goto(h, "follow_1", 1);
		h = BuildObject("svtank", 2, "wave_1");
		Goto(h, "follow_1", 1);
		h = BuildObject("svtank", 2, "wave_1");
		Goto(h, "follow_1", 1);
		h = BuildObject("svtank", 2, "wave_1");
		Goto(h, "follow_1", 1);

		// time to next wave
		wave2Time = GetTime() + 300.0f;
	}

	if (wave2Time < GetTime())
	{
		wave2Time = 999999.9f;

		// spawn the second wave
		Handle h;
		h = BuildObject("svtank", 2, "wave_2");
		Goto(h, "follow_2", 1);
		h = BuildObject("svtank", 2, "wave_2");
		Goto(h, "follow_2", 1);
		h = BuildObject("svtank", 2, "wave_2");
		Goto(h, "follow_2", 1);
		h = BuildObject("svtank", 2, "wave_2");
		Goto(h, "follow_2", 1);
		h = BuildObject("svltnk", 2, "wave_2");
		Goto(h, "follow_2", 1);
		h = BuildObject("svltnk", 2, "wave_2");
		Goto(h, "follow_2", 1);
		h = BuildObject("svltnk", 2, "wave_2");
		Goto(h, "follow_2", 1);
		h = BuildObject("svfigh", 2, "wave_2");
		Goto(h, "follow_2", 1);
		h = BuildObject("svfigh", 2, "wave_2");
		Goto(h, "follow_2", 1);

		// time to next wave
		wave3Time = GetTime() + 300.0f;
	}

	if (wave3Time < GetTime())
	{
		wave3Time = 999999.9f;

		// spawn the second wave
		Handle h;
		h = BuildObject("svtank", 2, "wave_3");
		Goto(h, "follow_3", 1);
		h = BuildObject("svtank", 2, "wave_3");
		Goto(h, "follow_3", 1);
		h = BuildObject("svtank", 2, "wave_3");
		Goto(h, "follow_3", 1);
		h = BuildObject("svtank", 2, "wave_3");
		Goto(h, "follow_3", 1);
		h = BuildObject("svtank", 2, "wave_3");
		Goto(h, "follow_3", 1);
		h = BuildObject("svtank", 2, "wave_3");
		Goto(h, "follow_3", 1);
		h = BuildObject("svtank", 2, "wave_3");
		Goto(h, "follow_3", 1);
		h = BuildObject("svtank", 2, "wave_3");
		Goto(h, "follow_3", 1);
		h = BuildObject("svtank", 2, "wave_3");
		Goto(h, "follow_3", 1);
		h = BuildObject("svhraz", 2, "wave_3");
		Goto(h, "follow_3", 1);
		h = BuildObject("svhraz", 2, "wave_3");
		Goto(h, "follow_3", 1);
		h = BuildObject("svhraz", 2, "wave_3");
		Goto(h, "follow_3", 1);

		// next attack
		arial1Time = GetTime() + 180.0f;
	}

	if (arial1Time < GetTime())
	{
		arial1Time = 999999.9f;
		
		// spawn the arial units
		Handle h;
		h = BuildObject("sspilo", 2, "aerial_1", 200);
		Attack(h, recycler, 1);
		h = BuildObject("sspilo", 2, "aerial_1", 200);
		Attack(h, recycler, 1);
		h = BuildObject("sspilo", 2, "aerial_1", 200);
		Attack(h, recycler, 1);
		h = BuildObject("sspilo", 2, "aerial_1", 200);
		Attack(h, recycler, 1);
		h = BuildObject("sspilo", 2, "aerial_1", 200);
		Attack(h, recycler, 1);
		h = BuildObject("sspilo", 2, "aerial_1", 200);
		Attack(h, recycler, 1);

		// next attack
		arial2Time = GetTime() + 30.0f;
	}

	if (arial2Time < GetTime())
	{
		arial2Time = 999999.9f;

		// spawn the arial units
		Handle h;
		h = BuildObject("sssold", 2, "aerial_2", 200);
		Attack(h, recycler, 1);
		h = BuildObject("sssold", 2, "aerial_2", 200);
		Attack(h, recycler, 1);
		h = BuildObject("sssold", 2, "aerial_2", 200);
		Attack(h, recycler, 1);
		h = BuildObject("sssold", 2, "aerial_2", 200);
		Attack(h, recycler, 1);

		// next attack
		wave4Time = GetTime() + 60.0f;
	}

	if (wave4Time < GetTime())
	{
		wave4Time = 999999.9f;

		// spawn the wave
		Handle h;
		h = BuildObject("svtank", 2, "wave_4");
		Goto(h, "follow_4", 1);
		h = BuildObject("svtank", 2, "wave_4");
		Goto(h, "follow_4", 1);
		h = BuildObject("svtank", 2, "wave_4");
		Goto(h, "follow_4", 1);
		h = BuildObject("svtank", 2, "wave_4");
		Goto(h, "follow_4", 1);
		h = BuildObject("svhraz", 2, "wave_4");
		Goto(h, "follow_4", 1);
		h = BuildObject("svhraz", 2, "wave_4");
		Goto(h, "follow_4", 1);
		h = BuildObject("svhraz", 2, "wave_4");
		Goto(h, "follow_4", 1);
		h = BuildObject("svhraz", 2, "wave_4");
		Goto(h, "follow_4", 1);
		h = BuildObject("svltnk", 2, "wave_4");
		Goto(h, "follow_4", 1);
		h = BuildObject("svltnk", 2, "wave_4");
		Goto(h, "follow_4", 1);
		h = BuildObject("svltnk", 2, "wave_4");
		Goto(h, "follow_4", 1);
		h = BuildObject("svltnk", 2, "wave_4");
		Goto(h, "follow_4", 1);

		// tug time
		tugTime = GetTime() + 120.0f;
	}

	if (tugTime < GetTime())
	{
		tugTime = 999999.9f;

		tug = BuildObject("svhaula", 2, "relic_tug");
		Goto(tug, "tug_path", 1);

		Handle h;
		h = BuildObject("svfigh", 2, "tug_defend");
		Defend2(h, tug, 1);
		h = BuildObject("svfigh", 2, "tug_defend");
		Defend2(h, tug, 1);
	}

	if (tug != NULL && !tugNearNav && GetDistance(tug, "nav_tug", 0) < 1000.0f)
	{
		tugNearNav = TRUE;

		AudioMessage("ch01006.wav");

		navTug = BuildObject("apcamr", 1, "nav_tug");

		// update objectives
		ClearObjectives();
		AddObjective("ch01002.otf", GREEN);
		AddObjective("ch01003.otf", WHITE);
	}

	// has the tug been killed?
	if (tug != NULL && GetHealth(tug) <= 0.0f && !lost && !won)
	{
		lost = TRUE;

		failedSound = AudioMessage("ch01011.wav");
	}

	if (failedSound != NULL && IsAudioMessageDone(failedSound))
	{
		failedSound = NULL;

		FailMission(GetTime() + 1.0, "ch01lseb.des");
	}

	// has the tug gotten away from us?
	if (tug != NULL && GetDistance(tug, "tug_fail") < 350.0f && GetTeamNum(tug) == 2 && !lost && !won)
	{
		FailMission(GetTime() + 1.0f, "ch01lsea.des");
		lost = TRUE;
	}

	// is the tug within 75 metres of the recycler?
	if (tug != NULL && GetDistance(tug, recycler) < 75.0f && !objective3Complete)
	{
		// message
		AudioMessage("ch01007.wav");

		// attack
		escort1 = BuildObject("svfigh", 1, "fighters");
		SetPerceivedTeam(escort1, 2);
		SetIndependence(escort1, 0);
		SetPerceivedTeam(escort1, 2);
		Goto(escort1, "fighters_to", 1);
		escort2 = BuildObject("svfigh", 1, "fighters");
		SetPerceivedTeam(escort2, 2);
		SetIndependence(escort2, 0);
		SetPerceivedTeam(escort2, 2);
		Goto(escort2, "fighters_to", 1);

		// update objectives
		objective3Complete = TRUE;
		ClearObjectives();
		AddObjective("ch01003.otf", GREEN);
		AddObjective("ch01004.otf", WHITE);

		// spawn the relic
		relic = BuildObject("obdata", 0, "relic_loc");

		// units
		Handle h;
		h = BuildObject("svtank", 2, "wave_5");
		Goto(h, "follow_5");
		h = BuildObject("svtank", 2, "wave_5");
		Goto(h, "follow_5");
		h = BuildObject("svtank", 2, "wave_5");
		Goto(h, "follow_5");
		h = BuildObject("svtank", 2, "wave_5");
		Goto(h, "follow_5");
		h = BuildObject("svhraz", 2, "wave_5");
		Goto(h, "follow_5");
		h = BuildObject("svhraz", 2, "wave_5");
		Goto(h, "follow_5");
		h = BuildObject("svhraz", 2, "wave_5");
		Goto(h, "follow_5");
		h = BuildObject("svhraz", 2, "wave_5");
		Goto(h, "follow_5");
		h = BuildObject("svltnk", 2, "wave_5");
		Goto(h, "follow_5");
		h = BuildObject("svltnk", 2, "wave_5");
		Goto(h, "follow_5");
		h = BuildObject("svltnk", 2, "wave_5");
		Goto(h, "follow_5");
		h = BuildObject("svltnk", 2, "wave_5");
		Goto(h, "follow_5");
		h = BuildObject("svturrb", 2, "wave_5");
		Goto(h, "follow_5");
		h = BuildObject("svturrb", 2, "wave_5");
		Goto(h, "follow_5");
		h = BuildObject("svturrb", 2, "wave_5");
		Goto(h, "follow_5");
		h = BuildObject("svturrb", 2, "wave_5");
		Goto(h, "follow_5");
	}

	if (objective3Complete && !objective4Complete && !lost && !won)
	{
		bool withinRange = FALSE;
		for (i = 0; i < 10; i++)
		{
			if (IsAlive(detectors[i]) && GetDistance(user, detectors[i]) < 150.0f)
			{
				withinRange = TRUE;
				break;
			}
		}
			
		if (!arialsSpawned && withinRange)
		{
			// spawn the arial units
			Handle h;
			h = BuildObject("sspilo", 2, "aerial_3", 100);
			h = BuildObject("sspilo", 2, "aerial_3", 100);
			h = BuildObject("sspilo", 2, "aerial_3", 100);
			h = BuildObject("sspilo", 2, "aerial_3", 100);
			h = BuildObject("sssold", 2, "aerial_4", 100);
			h = BuildObject("sssold", 2, "aerial_4", 100);
			h = BuildObject("sssold", 2, "aerial_4", 100);
			h = BuildObject("sssold", 2, "aerial_4", 100);
			h = BuildObject("sssold", 2, "aerial_4", 100);
			h = BuildObject("sssold", 2, "aerial_4", 100);
			arialsSpawned = TRUE;
		}

	
		// are we currently being escorted?
		if (isFollowing(escort1, user) &&
			isFollowing(escort2, user))
		{
			// we're being escorted, we're safe
		}
		else if (withinRange)
		{
			// our cover is blown
			lost = TRUE;
			detectedSound = AudioMessage("ch01008.wav");
			_ASSERTE(!objective4Complete);
		}
	}

	if (objective3Complete && !objective4Complete)
	{
		// are we currently being escorted?
		if (isFollowing(escort1, user) &&
			isFollowing(escort2, user))
		{
			// we're being escorted, we're safe
			SetPerceivedTeam(user, 2);
		}
		else
		{
			SetPerceivedTeam(user, 1);
		}
	}

	// we've been detected
	if (detectedSound != NULL && IsAudioMessageDone(detectedSound))
	{
		detectedSound = NULL;
		//failedSound = AudioMessage("ch01011.wav");
		FailMission(GetTime(), "ch01lsec.des");
	}
#endif
	// if we get the relic
	if (objective3Complete && !objective4Complete && 
		relic != NULL && tug != NULL && GetCargo(tug) == relic)
	{
		//_DEBUGMSG0("Relic picked up by Tug");
		objective4Complete = TRUE;

		// reset objectives
		ClearObjectives();
		AddObjective("ch01004.otf", GREEN);
		AddObjective("ch01005.otf", WHITE);

		navEnd = BuildObject("apcamr", 1, "nav_end");
		_ASSERTE(navEnd != NULL);
		SetName(navEnd, "Safe Distance");
		SetObjectiveOn(navEnd);

		StartCockpitTimer(180, 15, 5);
		explodeTime = GetTime() + 30.0f;
	}

	if (objective4Complete && !decoySpawned)
	{
		// are we close enough to the turrets?
		bool withinRange = FALSE;
		for (i = 0; i < 10; i++)
		{
			if (IsAlive(detectors[i]) && GetDistance(user, detectors[i]) < 300.0f)
			{
				withinRange = TRUE;
				break;
			}
		}

		if (withinRange)
		{
			decoySpawned = TRUE;

			// decoy sound
			AudioMessage("ch01009.wav");

			for (i = 0; i < 7; i++)
			{
				Handle h = BuildObject("cvhtnk", 1, "decoy_units");
				Goto(h, detectors[rand() % 10], 1);
			}
		}
	}

	if (objective4Complete && !doingExplosion)
	{
		if (GetCockpitTimer() <= 0)
		{
			explodeTime = 999999.9f;
			HideCockpitTimer();

			// make the thing explode
			doNuke = TRUE;
			doingExplosion = TRUE;
			ColorFade_SetFade(1.0f, 0.5f, 255, 255, 255);
		}
		else if (GetCockpitTimer() <= 2.0 && !focusOnExplosion)
		{
			// pre-explosion
			float nukeDistance = GetDistance(navEnd, hangar) - 50;
			if (GetDistance(user, hangar) > nukeDistance && !focusOnExplosion)
			{
				CameraReady();
				CameraPath("cut_end", 3000, 0, bbTower);
				focusOnExplosion = TRUE;
			}
		}
	}

	if (doNuke)
	{
		doNuke = FALSE;

		// where's the relic?
		float nukeDistance = GetDistance(navEnd, hangar) - 50.0f;
		if (GetDistance(relic, hangar) > nukeDistance)
		{
			SucceedMission(GetTime() + 3.0, "ch01win.des");
			won = TRUE;
		}
		else
		{
			FailMission(GetTime() + 3.0, "ch01lsee.des");
			lost = TRUE;
		}
		if (useD3D & 4)
			MakeExplosion("spawn_explosion1", "xpltrsn");
		else
			MakeExplosion("spawn_explosion1", "xpltrsq");
	}

	// has the recycler been lost?
	if (recycler != NULL && GetHealth(recycler) <= 0.0 && !objective3Complete &&
		!lost && !won)
	{
		lost = TRUE;
		FailMission(GetTime() + 1.0, "ch01lsed.des");
	}
}
