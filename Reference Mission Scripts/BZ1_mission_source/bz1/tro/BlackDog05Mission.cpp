#include "GameCommon.h"
#include "AiCommon.h"
#include "AiMission.h"
#include "AiProcess.h"
#include "PowerUp.h"
#include "ScriptUtils.h"


/*
	BlackDog05Mission
*/


class BlackDog05Mission : public AiMission {
	DECLARE_RTIME(BlackDog05Mission)
public:
	BlackDog05Mission();
	~BlackDog05Mission();

	virtual bool Load(file fp);
	virtual bool PostLoad(void);
	virtual bool Save(file fp);

	virtual void Update(void);

	virtual void AddObject(GameObject *gameObj);

private:
	void Setup();
	void Execute();
	void AddObject(Handle h);

	void resetObjectives();

	// bools
	union {
		struct {
			bool
				// record whether the init code has been done
				startDone,

				// have we lost?
				lost, won,

				// met the objectives?
				objective1Complete,
				objective2Complete,

				// cameras
				cameraReady, cameraComplete[2],

				// wait
				waitsInitialized, waitOver[5],

				// quitters
				quittersSpawned,
				quitterMovieDone,

				b_last;
		};
		bool b_array[16];
	};

	// floats
	union {
		struct {
			float
				waitTime[5],
				rearAttackTime1,
				rearAttackTime2,
				howitzerTime,
				quitterDelay,
				bomberTime,
				portalTime,
				quitterCamTime,
				f_last;
		};
		float f_array[12];
	};

	// handles
	union {
		struct {
			Handle
				// the user
				user,

				// recycler
				recycler, 

				// portal
				portal,

				// badguys (0-14 = units, 15-18 = attack1,
				// 19-22 = attack2, 23-27 = attack3,
				// 28-33 = attack4
				// 34-38 = rear_attack 1
				// 39-43 = rear_attack 2
				// 44-45 = howit
				units[46],
				
				// quiters
				quitters[6],

				h_last;
		};
		Handle h_array[55];
	};

	// integers
	union {
		struct {
			int
				numBombers,
				whichTimer,
				portalStage,

				// sounds
				quitterSound,
				introSound,
				sound6,

				i_last;
		};
		int i_array[6];
	};
};

IMPLEMENT_RTIME(BlackDog05Mission)

BlackDog05Mission::BlackDog05Mission()
{
}

BlackDog05Mission::~BlackDog05Mission()
{
}

bool BlackDog05Mission::Load(file fp)
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

bool BlackDog05Mission::PostLoad(void)
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

bool BlackDog05Mission::Save(file fp)
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

void BlackDog05Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

void BlackDog05Mission::AddObject(Handle h)
{
#if 0
	if (numBombers >= 7)
		return;

	GameObject *obj = GameObjectHandle::GetObj(h);
	if (obj->GetTeam() == GameObject::GetUserTeam())
	{
		// get the object's team slot
		int slot = obj->GetTeamSlot();

		// get the object's class
		GameObjectClass *c = obj->GetClass();
		_ASSERTE(c != NULL);

		if ((slot >= TEAM_SLOT_MIN_OFFENSE) && (slot <= TEAM_SLOT_MAX_OFFENSE))
		{
			// offensive unit built
			numBombers++;
			if (numBombers == 7)
			{
				objective1Complete = TRUE;
				resetObjectives();

				// start the new counter
				StopCockpitTimer();
				StartCockpitTimer(40 * 60, 60, 10);
				whichTimer = 2;
			}
		}
	}
#endif
}

void BlackDog05Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

void BlackDog05Mission::Setup()
{
	int i = 0;
	startDone = FALSE;
	lost = FALSE;
	won = FALSE;
	objective1Complete = FALSE;
	objective2Complete = FALSE;
	quitterMovieDone = FALSE;

	// handles
	recycler = GetHandle("recycler");
	portal = GetHandle("portal");
	units[0] = GetHandle("unit_1");
	units[1] = GetHandle("unit_2");
	units[2] = GetHandle("unit_3");
	units[3] = GetHandle("unit_4");
	units[4] = GetHandle("unit_5");
	units[5] = GetHandle("unit_6");
	units[6] = GetHandle("unit_7");
	units[7] = GetHandle("unit_8");
	units[8] = GetHandle("unit_9");
	units[9] = GetHandle("unit_10");
	units[10] = GetHandle("unit_11");
	units[11] = GetHandle("unit_12");
	units[12] = GetHandle("unit_13");
	units[13] = GetHandle("unit_14");
	units[14] = GetHandle("unit_15");
	for (i = 15; i < 46; i++)
		units[i] = NULL;
	introSound = NULL;
	sound6 = NULL;

	// number of bombers built
	numBombers = 0;
	whichTimer = 0;

	quitterDelay = 999999.0f;
	bomberTime = 999999.9f;
	rearAttackTime1 = 999999.9f;
	rearAttackTime2 = 999999.9f;
	howitzerTime = 999999.9f;
	quitterCamTime = 999999.9f;
	portalTime = -1;
	portalStage = 0;
}

void BlackDog05Mission::Execute()
{
	int i = 0;
	user = GetPlayerHandle(); //assigns the player a handle every frame

	if (!startDone)
	{
		SetScrap(1,8);
		SetPilot(1,10);

		// setup the initial objectives
		ClearObjectives();
	
		//portal = BuildObject("cbport", 0, "portal");
		
		// don't do this part after the first shot
		startDone = TRUE;
#if 0
		// debugging stuff
		cameraComplete[0] = TRUE;
		objective1Complete = TRUE;
		objective2Complete = TRUE;
#endif
	}

		// start the camera going
	if (!cameraComplete[0])
	{
		if (!cameraReady)
		{
			// get the camera ready
			CameraReady();
			
			// start the audio
			introSound = AudioMessage("bd05001.wav");

			resetObjectives();

			cameraReady = TRUE;
		}

		BOOL arrived = CameraPath("camera_start_arc", 3000, 2000, recycler);
		
		if (CameraCancelled())
		{
			arrived = TRUE;
			StopAudioMessage(introSound);
		}
		if (arrived)
		{
			// if the audio is complete
			CameraFinish();
			cameraComplete[0] = TRUE;
			cameraReady = FALSE;

			ClearObjectives();
			AddObjective("bd05001.otf", WHITE);
		}
	}

	// setup the time delays
	if (!waitsInitialized)
	{
		waitTime[0] = GetTime() + 240.0;
		waitTime[1] = GetTime() + 300.0;
		waitTime[2] = GetTime() + 540.0;
		waitTime[3] = GetTime() + 840.0;
		waitTime[4] = GetTime() + 1140.0;

		howitzerTime = GetTime() + 420;
		rearAttackTime1 = GetTime() + 450;
		rearAttackTime2 = GetTime() + 660;
 
		waitsInitialized = TRUE;
	}

	// check each of the time delays
	if (!waitOver[0] && waitTime[0] < GetTime())
	{
		AudioMessage("bd05002.wav");
		waitOver[0] = TRUE;
	}

	if (!waitOver[1] && waitTime[1] < GetTime())
	{
		// spawn first wave
		units[15] = BuildObject("cvfigh", 2, "first_wave");
		SetCloaked(units[15]);
		Goto(units[15], recycler, 1);
		units[16] = BuildObject("cvfigh", 2, "first_wave");
		SetCloaked(units[16]);
		Goto(units[16], recycler, 1);
		units[17] = BuildObject("cvltnk", 2, "first_wave");
		SetCloaked(units[17]);
		Goto(units[17], recycler, 1);
		units[18] = BuildObject("cvltnk", 2, "first_wave");
		SetCloaked(units[18]);
		Goto(units[18], recycler, 1);

		// these guys should just attack the general base area
		waitOver[1] = TRUE;
	}

	if (!waitOver[2] && waitTime[2] < GetTime())
	{
		// spawn first wave
		units[19] = BuildObject("cvltnk", 2, "second_wave");
		SetCloaked(units[19]);
		Attack(units[19], recycler, 1);
		units[20] = BuildObject("cvltnk", 2, "second_wave");
		SetCloaked(units[20]);
		Attack(units[20], recycler, 1);
		units[21] = BuildObject("cvtnk", 2, "second_wave");
		SetCloaked(units[21]);
		Attack(units[21], recycler, 1);
		units[22] = BuildObject("cvtnk", 2, "second_wave");
		SetCloaked(units[22]);
		Attack(units[22], recycler, 1);

		waitOver[2] = TRUE;
	}

	if (!waitOver[3] && waitTime[3] < GetTime())
	{
		units[23] = BuildObject("cvtnk", 2, "third_wave");
		SetCloaked(units[23]);
		Goto(units[23], recycler, 1);
		units[24] = BuildObject("cvtnk", 2, "third_wave");
		SetCloaked(units[24]);
		Goto(units[24], recycler, 1);
		units[25] = BuildObject("cvhraz", 2, "third_wave");
		SetCloaked(units[25]);
		Goto(units[25], recycler, 1);
		units[26] = BuildObject("cvhraz", 2, "third_wave");
		SetCloaked(units[26]);
		Goto(units[26], recycler, 1);
		units[27] = BuildObject("cvwalk", 2, "third_wave");
		SetCloaked(units[27]);
		Goto(units[27], recycler, 1);

		// attack general base area

		waitOver[3] = TRUE;
	}

	if (!waitOver[4] && waitTime[4] < GetTime())
	{

		units[28] = BuildObject("cvtnk", 2, "fourth_wave");
		SetCloaked(units[28]);
		Goto(units[28], recycler, 1);
		units[29] = BuildObject("cvtnk", 2, "fourth_wave");
		SetCloaked(units[29]);
		Goto(units[29], recycler, 1);
		units[30] = BuildObject("cvhraz", 2, "fourth_wave");
		SetCloaked(units[30]);
		Goto(units[30], recycler, 1);
		units[31] = BuildObject("cvhraz", 2, "fourth_wave");
		SetCloaked(units[31]);
		Goto(units[31], recycler, 1);
		units[32] = BuildObject("cvwalk", 2, "fourth_wave");
		SetCloaked(units[32]);
		Goto(units[32], recycler, 1);
		units[33] = BuildObject("cvwalk", 2, "fourth_wave");
		SetCloaked(units[33]);
		Goto(units[33], recycler, 1);

		// attack anything blackdog

		waitOver[4] = TRUE;
	}

	if (rearAttackTime1 < GetTime())
	{
		rearAttackTime1 = 999999.9f;

		units[34] = BuildObject("cvtnk", 2, "rear_attack");
		SetCloaked(units[34]);
		Attack(units[34], recycler, 1);
		units[35] = BuildObject("cvtnk", 2, "rear_attack");
		SetCloaked(units[35]);
		Attack(units[35], recycler, 1);
		units[36] = BuildObject("cvtnk", 2, "rear_attack");
		SetCloaked(units[36]);
		Attack(units[36], recycler, 1);
		units[37] = BuildObject("cvtnk", 2, "rear_attack");
		SetCloaked(units[37]);
		Attack(units[37], recycler, 1);
		units[38] = BuildObject("cvtnk", 2, "rear_attack");
		SetCloaked(units[38]);
		Attack(units[38], recycler, 1);
	}

	if (rearAttackTime2 < GetTime())
	{
		rearAttackTime2 = 999999.9f;

		units[39] = BuildObject("cvtnk", 2, "rear_attack");
		SetCloaked(units[39]);
		Attack(units[39], recycler, 1);
		units[40] = BuildObject("cvtnk", 2, "rear_attack");
		SetCloaked(units[40]);
		Attack(units[40], recycler, 1);
		units[41] = BuildObject("cvtnk", 2, "rear_attack");
		SetCloaked(units[41]);
		Attack(units[41], recycler, 1);
		units[42] = BuildObject("cvtnk", 2, "rear_attack");
		SetCloaked(units[42]);
		Attack(units[42], recycler, 1);
		units[43] = BuildObject("cvtnk", 2, "rear_attack");
		SetCloaked(units[43]);
		Attack(units[43], recycler, 1);
	}

	if (howitzerTime < GetTime())
	{
		howitzerTime = 999999.9f;

		units[44] = BuildObject("cvartl", 2, "howit");
		SetCloaked(units[44]);
		Goto(units[44], recycler, 1);
		units[45] = BuildObject("cvartl", 2, "howit");
		SetCloaked(units[45]);
		Goto(units[45], recycler, 1);
	}

	if (!objective2Complete && waitOver[4])
	{
		// test to see if everything has been beaten
		bool allDead = TRUE;
		for (int i = 0; i < 46; i++)
		{
			if (IsAlive(units[i]))
			{
				allDead = FALSE;
				break;
			}
		}
		objective2Complete = allDead;
		if (objective2Complete)
		{
			AudioMessage("bd05004.wav");
			resetObjectives();
		}
	}

	if (objective2Complete && !quittersSpawned)
	{
		quitters[0] = BuildObject("cvtnk", 2, "quitters");
		quitters[1] = BuildObject("cvtnk", 2, "quitters");
		quitters[2] = BuildObject("cvwalk", 2, "quitters");
		quitters[3] = BuildObject("cvwalk", 2, "quitters");
		quitters[4] = BuildObject("cspilo", 2, "quitters");
		quitters[5] = BuildObject("cvltnk", 2, "quitters");

		// have these bastards head towards the portal
		for (int i = 0; i < 6; i++)
			Retreat(quitters[i], "portal_in", 1);

		quittersSpawned = TRUE;
		activatePortal(portal, true);
	}

	if (quittersSpawned)
	{
		bool allGone = TRUE;
		for (i = 0; i < 6; i++)
		{
			if (quitters[i] == NULL)
				continue;
			
			if (!IsAlive(quitters[i]))
			{
				quitters[i] = NULL;
			}
			else if (isTouching(quitters[i], portal))
			{
				RemoveObject(quitters[i]);
				quitters[i] = NULL;
			}
		}
		if (allGone)
		{
		}
	}

	if (quittersSpawned && cameraComplete[0] && !cameraComplete[1])
	{
		if (!cameraReady)
		{
			// get the camera ready
			CameraReady();
			
			// start the audio
			quitterSound = AudioMessage("bd05005.wav");
			quitterCamTime = GetTime() + 15.0f;

			cameraReady = TRUE;
		}

		bool seqDone = FALSE;
		CameraPath("camera_retreat", 3000, 0, portal);
		
		// if we're done the sound, start the time delay
		if (quitterSound != NULL &&
			IsAudioMessageDone(quitterSound))
		{
			quitterDelay = GetTime() + 3.0f;
			quitterSound = NULL;
		}

		if (quitterDelay < GetTime() && quitterCamTime < GetTime())
			seqDone = TRUE;

		// cancelled or out of time?
		if (seqDone ||
			CameraCancelled())
		{
			// if the audio is complete
			CameraFinish();
			cameraComplete[1] = TRUE;
			cameraReady = FALSE;
			quitterMovieDone = TRUE;
		}
	}

	if (objective1Complete && objective2Complete && quitterMovieDone && !won && !lost)
	{
		sound6 = AudioMessage("bd05006.wav");
		won = TRUE;
	}

	if (sound6 != NULL && IsAudioMessageDone(sound6))
	{
		sound6 = NULL;
		SucceedMission(0.1f, "bd05win.des");
	}
}

void BlackDog05Mission::resetObjectives()
{
	ClearObjectives();
	// objective 1
	if (objective1Complete)
		AddObjective("bd05001.otf", GREEN);
	else
		AddObjective("bd05001.otf", WHITE);
}