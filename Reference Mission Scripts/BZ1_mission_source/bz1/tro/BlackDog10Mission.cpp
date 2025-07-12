#include "GameCommon.h"
#include "AiCommon.h"
#include "AiMission.h"
#include "AiProcess.h"
#include "PowerUp.h"
#include "ScriptUtils.h"


/*
	BlackDog10Mission
*/

char *defences[4] = {	"defend_a",
						"defend_b",
						"defend_c",
						"defend_d" };
char *defenceUnits[4][9] = {	{"cvtnk", "cvtnk", "cvltnk", "cvltnk", "cvfigh", "cvfigh", NULL},
								{"cvfigh", "cvfigh", "cvfigh", "cvwalk", "cvhtnk", "cvtnk", NULL},
								{"cvtnk", "cvtnk", "cvtnk", "cvfigh", "cvfigh", "cvwalk", NULL},
								{"cvfigh", "cvfigh", "cvfigh", "cvfigh", "cvtnk", "cvtnk", "cvtnk", "cvwalk", NULL} };
char *patrols[4] = {	"patrol_a",
						"patrol_b",
						"patrol_c",
						"patrol_d" };
char *patrolUnits[4][6] = {		{"cvfigh", "cvfigh", "cvfigh", "cvfigh", "cvtnk", NULL},
								{"cvfigh", "cvfigh", "cvfigh", "cvfigh", "cvtnk", NULL},
								{"cvfigh", "cvfigh", "cvfigh", "cvfigh", "cvtnk", NULL},
								{"cvfigh", "cvfigh", "cvfigh", "cvfigh", "cvtnk", NULL} };

class BlackDog10Mission : public AiMission {
	DECLARE_RTIME(BlackDog10Mission)
public:
	BlackDog10Mission();
	~BlackDog10Mission();

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
				
				// camera info
				cameraReady[3], cameraComplete[3],
				arrived,

				// items spawned?
				apcSpawned,
				recyclerSpawned,
				defencesSpawned[4],
				patrolsSpawned[4],

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
				navDelay,
				apcDelay,
				apcCameraTimeout,
				cameraTime,
				f_last;
		};
		float f_array[4];
	};

	// handles
	union {
		struct {
			Handle
				// *** User stuff
				user,

				// *** Units
				destroy[6],
				apc,
				recycler,
								
				h_last;
		};
		Handle h_array[9];
	};

	// integers
	union {
		struct {
			int
				// *** Sounds
				introSound,
				navSound,
				winSound,

				i_last;
		};
		int i_array[3];
	};
};

IMPLEMENT_RTIME(BlackDog10Mission)

BlackDog10Mission::BlackDog10Mission()
{
}

BlackDog10Mission::~BlackDog10Mission()
{
}

bool BlackDog10Mission::Load(file fp)
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

bool BlackDog10Mission::PostLoad(void)
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

bool BlackDog10Mission::Save(file fp)
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

void BlackDog10Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

void BlackDog10Mission::AddObject(Handle h)
{
}

void BlackDog10Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

void BlackDog10Mission::Setup()
{
	int i = 0;
	startDone = FALSE;
	objective1Complete = FALSE;
	for (i = 0; i < 3; i++)
		cameraReady[i] = cameraComplete[i] = FALSE;
	arrived = FALSE;
	apcSpawned = FALSE;
	for (i = 0; i < 4; i++)
		defencesSpawned[i] = FALSE;
	for (i = 0; i < 4; i++)
		patrolsSpawned[i] = FALSE;
	
	// setup handles
	destroy[0] = GetHandle("destroy_1");
	destroy[1] = GetHandle("destroy_2");
	destroy[2] = GetHandle("destroy_3");
	destroy[3] = GetHandle("destroy_4");
	destroy[4] = GetHandle("destroy_5");
	destroy[5] = GetHandle("destroy_6");
	introSound = NULL;
	navSound = NULL;
	winSound = NULL;
	apc = NULL;
	recycler = NULL;

	// timeouts
	navDelay = 999999.9f;
	apcDelay = 999999.9f;
	apcCameraTimeout = 999999.9f;
	cameraTime = 999999.9f;
}

void checkAmbush(float distance, char *spawn_spot, bool &spawned, char *units[])
{
	// if we're already spawned, then leave
	if (spawned)
		return;

	Handle h = GetNearestUnitOnTeam(spawn_spot, 0, 1);
	if (h == NULL)
		return;

	// is the closest unit close enough?
	if (GetDistance(h, spawn_spot, 0) < distance)
	{
		spawned = TRUE;

		// yep, spawn the units
		char **ptr = units;
		while (*ptr != NULL)
		{
			Handle h = BuildObject(*ptr, 2, spawn_spot);
			Hunt(h);
			ptr++;
		}
	}
}

void BlackDog10Mission::Execute()
{
	int i = 0;
	user = GetPlayerHandle(); //assigns the player a handle every frame

	if (!startDone)
	{
		SetScrap(1,100); // we start with 100 scrap
		SetScrap(2,0); // enemy starts with 0 scrap
		SetPilot(1,10);

		// setup the initial objectives
		ClearObjectives();
		AddObjective("bd10001.otf", WHITE);
		
		// don't do this part after the first shot
		startDone = TRUE;
	}

	// should we spawn the defences?
	for (i = 0; i < 4; i++)
		checkAmbush(400.0, defences[i], defencesSpawned[i], defenceUnits[i]);

	// how about the patrols?
	for (i = 0; i < 4; i++)
		checkAmbush(400.0, patrols[i], patrolsSpawned[i], patrolUnits[i]);

	if (!cameraComplete[0])
	{
		if (!cameraReady[0])
		{
			// get the camera ready
			CameraReady();
			
			// start the audio
			introSound = AudioMessage("bd10001.wav");

			cameraReady[0] = TRUE;
		}

		bool seqDone = FALSE;
		if (!arrived)
			arrived = CameraPath("camera_start", 3000, 2000, destroy[3]);
		if (arrived && IsAudioMessageDone(introSound) && cameraTime == 999999.9f)
			cameraTime = GetTime() + 2.0f;
		if (cameraTime < GetTime())
			seqDone = TRUE;

		if (CameraCancelled())
		{
			seqDone = TRUE;
			StopAudioMessage(introSound);
		}
		if (seqDone)
		{
			CameraFinish();
			cameraComplete[0] = TRUE;
		}
	}

	if (!objective1Complete)
	{
		// have we killed all the "destroy" units?
		// assume we have
		objective1Complete = TRUE;
		for (int i = 0; i < 6; i++)
		{
			if (GetHealth(destroy[i]) > 0.0f)
			{
				// nope, not yet
				objective1Complete = FALSE;
				break;
			}
		}
		if (objective1Complete)
			navDelay = GetTime() + 10.0f;
	}

	if (objective1Complete && navDelay < GetTime())
	{
		navDelay = 999999.9f;

		// spawn the nav beacon
		BuildObject("apcamr", 1, "navcam_end");

		// start the sound
		navSound = AudioMessage("bd10002.wav");
	}

	if (objective1Complete && navSound != NULL &&
		IsAudioMessageDone(navSound))
	{
		navSound = NULL;
		apcDelay = GetTime() + 5.0;
	}

	if (objective1Complete && apcDelay < GetTime())
	{
		apcDelay = 999999.9f;

		// spawn the APC
		apcSpawned = TRUE;
		apc = BuildObject("bvapc", 1, "apc");
		Goto(apc, "apc_path", 1);

		// spawn the portal
		BuildObject("cbport", 0, "portal");
	}

	if (apcSpawned && !cameraComplete[1])
	{
		if (!cameraReady[1])
		{
			// get the camera ready
			CameraReady();
			
			cameraReady[1] = TRUE;

			apcCameraTimeout = GetTime() + 7.0f;	
		}

		CameraPath("camera_apc", 30, 200, apc);
		
		if (apcCameraTimeout < GetTime() ||
			CameraCancelled())
		{
			CameraFinish();
			cameraComplete[1] = TRUE;
			apcCameraTimeout = 999999.9f;
		}
	}

	if (cameraComplete[1] && !recyclerSpawned)
	{
		recyclerSpawned = TRUE;

		recycler = BuildObject("bvrecy", 1, "recycler");
		Goto(recycler, "recycler_path", 1);

		for (i = 0; i < 6; i++)
		{
			Handle h = BuildObject("cvtnka", 1, "capture");
			SetIndependence(h, 0);
			Follow(h, recycler, 1);
		}
	}

	if (recyclerSpawned && !cameraComplete[2])
	{
		if (!cameraReady[2])
		{
			// get the camera ready
			CameraReady();
			
			// start the audio
			winSound = AudioMessage("bd10003.wav");

			cameraReady[2] = TRUE;
			arrived = FALSE;
			cameraTime = GetTime() + 10.0f;
		}

		bool seqDone = FALSE;
		if (!arrived)
		{
			arrived = CameraPath("camera_end", 30, 200, recycler);
		}
		if (IsAudioMessageDone(winSound) && cameraTime < GetTime())
			seqDone = TRUE;

		if (CameraCancelled())
		{
			seqDone = TRUE;
			StopAudioMessage(winSound);
		}

		if (seqDone)
		{
			//CameraFinish();
			cameraComplete[2] = TRUE;
			SucceedMission(GetTime() + 1.0f, "bd10win.des");
		}
	}
}