#include "GameCommon.h"
#include "AiCommon.h"
#include "AiMission.h"
#include "AiProcess.h"
#include "PowerUp.h"
#include "ScriptUtils.h"

/*
	BlackDog13Mission
*/

class BlackDog13Mission : public AiMission {
	DECLARE_RTIME(BlackDog13Mission)
public:
	BlackDog13Mission();
	~BlackDog13Mission();

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

				// silo defenders
				defendersSpawned[6],

				// have all the silos been recycled yet?
				recycled[6],
				silosRecycled,
				recycleChecked,
				sound2Played,

				arrived,

				// have we lost?
				lost, won,

				b_last;
		};
		bool b_array[26];
	};

	// floats
	union {
		struct {
			float
				wave1Time,
				wave2Time,
				wave3Time,
				wave4Time,
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
				lastUser,
				
				// *** Units
				recycler, 
				chinRecycler,
				silos[6],
				
				// nav beacons
				
				h_last;
		};
		Handle h_array[10];
	};

	// integers
	union {
		struct {
			int
				scrapValue,
				lastScrapValue,

				// *** Sounds
				sound1,
				sound3,
				sound4,
				sound5,
				
				i_last;
		};
		int i_array[6];
	};
};

IMPLEMENT_RTIME(BlackDog13Mission)

BlackDog13Mission::BlackDog13Mission()
{
}

BlackDog13Mission::~BlackDog13Mission()
{
}

bool BlackDog13Mission::Load(file fp)
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

bool BlackDog13Mission::PostLoad(void)
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

bool BlackDog13Mission::Save(file fp)
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

void BlackDog13Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

void BlackDog13Mission::AddObject(Handle h)
{
}

void BlackDog13Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

void BlackDog13Mission::Setup()
{
	int i = 0;
	startDone = FALSE;
	objective1Complete = FALSE;
	objective2Complete = FALSE;
	objective3Complete = FALSE;
	for (i = 0; i < 2; i++)
		cameraReady[i] = cameraComplete[i] = FALSE;
	for (i = 0; i < 6; i++)
	{
		recycled[i] = FALSE;
		defendersSpawned[i] = FALSE;
	}
	silosRecycled = FALSE;
	sound2Played = FALSE;
	arrived = FALSE;
	recycleChecked = FALSE;
	
	// units
	user = NULL;
	lastUser = NULL;
	recycler = GetHandle("recycler");
	chinRecycler = GetHandle("chin_recycler");
	silos[0] = GetHandle("chin_silo1");
	silos[1] = GetHandle("chin_silo2");
	silos[2] = GetHandle("chin_silo3");
	silos[3] = GetHandle("chin_silo4");
	silos[4] = GetHandle("chin_silo5");
	silos[5] = GetHandle("chin_silo6");
	
	// sounds
	sound1 = NULL;
	sound3 = NULL;
	sound4 = NULL;
	sound5 = NULL;
	
	// times
	wave1Time = 999999.9f;
	wave2Time = 999999.9f;
	wave3Time = 999999.9f;
	wave4Time = 999999.9f;
	
	// ints
	lastScrapValue = 0;
	scrapValue = 0;
}


void BlackDog13Mission::Execute()
{
	int i = 0;
	lastUser = user;
	user = GetPlayerHandle(); //assigns the player a handle every frame
	
	if (!startDone)
	{
		SetScrap(1,30);
		SetPilot(1,10);

		// don't do this part after the first shot
		startDone = TRUE;

		wave1Time = GetTime() + 3 * 60.0f;
		wave2Time = GetTime() + 10 * 60.0f;
		wave3Time = GetTime() + 15 * 60.0f;
		wave4Time = GetTime() + 30 * 60.0f;
		
		StartCockpitTimer(45*60, 30, 10);

		// label the navs
		Handle h;
		h = GetHandle("nav_chin_silo1");
		SetName(h, "Scrap Field");
		h = GetHandle("nav_chin_silo2");
		SetName(h, "Scrap Field");
		h = GetHandle("nav_chin_silo3");
		SetName(h, "Scrap Field");
		h = GetHandle("nav_chin_silo4");
		SetName(h, "Scrap Field");
		h = GetHandle("nav_chin_silo5");
		SetName(h, "Scrap Field");
		h = GetHandle("nav_chin_silo6");
		SetName(h, "Scrap Field");
	}

	lastScrapValue = scrapValue;
	scrapValue = GetScrap(1);

	if (!cameraComplete[0])
	{
		if (!cameraReady[0])
		{
			CameraReady();
			cameraReady[0] = TRUE;

			sound1 = AudioMessage("bd13001.wav");
		}

		bool seqDone = FALSE;
		if (!arrived)
			arrived = CameraPath("camera_intro", 500, 1500, silos[5]);
		if (arrived && IsAudioMessageDone(sound1))
			seqDone = TRUE;

		if (CameraCancelled())
		{
			seqDone = TRUE;
			StopAudioMessage(sound1);
		}
		if (seqDone)
		{
			cameraComplete[0] = TRUE;
			CameraFinish();

			ClearObjectives();
			AddObjective("bd13001.otf", WHITE);
		}
	}

	if (wave1Time < GetTime())
	{
		wave1Time = 999999.9f;
		char *units[7] = { "cvfigh", "cvfigh", "cvfigh", "cvfigh", "cvltnk", "cvltnk", "cvtnk" };

		for (i = 0; i < 7; i++)
		{
			Handle h = BuildObject(units[i], 2, "spawn_attack_waves");
			Goto(h, recycler, 1);
		}
	}

	if (wave2Time < GetTime())
	{
		wave2Time = 999999.9f;
		char *units[6] = { "cvrckt", "cvrckt", "cvltnk", "cvltnk", "cvtnk", "cvtnk" };

		for (i = 0; i < 6; i++)
		{
			Handle h = BuildObject(units[i], 2, "spawn_attack_waves");
			Goto(h, recycler, 1);
		}
	}

	if (wave3Time < GetTime())
	{
		wave3Time = 999999.9f;

		char *units[9] = { "cvhraz", "cvhraz", "cvhraz", 
			"cvfigh", "cvfigh", "cvfigh", "cvfigh", "cvfigh", "cvfigh" };

		for (i = 0; i < 9; i++)
		{
			Handle h = BuildObject(units[i], 2, "spawn_attack_waves");
			Goto(h, recycler, 1);
		}
	}

	if (wave4Time < GetTime())
	{
		wave4Time = 999999.9f;

		char *units[6] = { "cvfigh", "cvfigh", "cvfigh", "cvfigh", "cvhtnk", "cvhtnk" };

		for (i = 0; i < 6; i++)
		{
			Handle h = BuildObject(units[i], 2, "spawn_attack_waves");
			Goto(h, recycler, 1);
		}
	}

	if (!defendersSpawned[0] && GetDistance(user, silos[0]))
	{
		defendersSpawned[0] = TRUE;

		Handle h;
		h = BuildObject("cvfigh", 2, "spawn_defend1");
		Defend2(h, silos[0]);
		h = BuildObject("cvfigh", 2, "spawn_defend1");
		Defend2(h, silos[0]);
		h = BuildObject("cvltnk", 2, "spawn_defend6");
		Defend2(h, silos[0]);
		h = BuildObject("cvltnk", 2, "spawn_defend6");
		Defend2(h, silos[0]);
	}
	if (!defendersSpawned[1] && GetDistance(user, silos[1]))
	{
		defendersSpawned[1] = TRUE;

		Handle h;
		h = BuildObject("cvltnk", 2, "spawn_defend1");
		Defend2(h, silos[1]);
		h = BuildObject("cvltnk", 2, "spawn_defend1");
		Defend2(h, silos[1]);
		h = BuildObject("cvltnk", 2, "spawn_defend6");
		Defend2(h, silos[1]);
		h = BuildObject("cvltnk", 2, "spawn_defend6");
		Defend2(h, silos[1]);
	}
	if (!defendersSpawned[2] && GetDistance(user, silos[2]))
	{
		defendersSpawned[2] = TRUE;

		Handle h;
		h = BuildObject("cvfigh", 2, "spawn_defend1");
		Defend2(h, silos[2]);
		h = BuildObject("cvfigh", 2, "spawn_defend1");
		Defend2(h, silos[2]);
		h = BuildObject("cvrckt", 2, "spawn_defend6");
		Defend2(h, silos[2]);
		h = BuildObject("cvrckt", 2, "spawn_defend6");
		Defend2(h, silos[2]);
	}
	if (!defendersSpawned[3] && GetDistance(user, silos[3]))
	{
		defendersSpawned[3] = TRUE;

		Handle h;
		h = BuildObject("cvtnk", 2, "spawn_defend1");
		Defend2(h, silos[3]);
		h = BuildObject("cvtnk", 2, "spawn_defend1");
		Defend2(h, silos[3]);
		h = BuildObject("cvltnk", 2, "spawn_defend6");
		Defend2(h, silos[3]);
		h = BuildObject("cvltnk", 2, "spawn_defend6");
		Defend2(h, silos[3]);
	}
	if (!defendersSpawned[4] && GetDistance(user, silos[4]))
	{
		defendersSpawned[4] = TRUE;

		Handle h;
		h = BuildObject("cvfigh", 2, "spawn_defend1");
		Defend2(h, silos[4]);
		h = BuildObject("cvfigh", 2, "spawn_defend1");
		Defend2(h, silos[4]);
		h = BuildObject("cvfigh", 2, "spawn_defend6");
		Defend2(h, silos[4]);
		h = BuildObject("cvfigh", 2, "spawn_defend6");
		Defend2(h, silos[4]);
	}
	if (!defendersSpawned[5] && GetDistance(user, silos[5]))
	{
		defendersSpawned[5] = TRUE;

		Handle h;
		h = BuildObject("cvhtnk", 2, "spawn_defend1");
		Defend2(h, silos[5]);
		h = BuildObject("cvhtnk", 2, "spawn_defend1");
		Defend2(h, silos[5]);
		h = BuildObject("cvfigh", 2, "spawn_defend6");
		Defend2(h, silos[5]);
		h = BuildObject("cvfigh", 2, "spawn_defend6");
		Defend2(h, silos[5]);
	}

	if (!recycleChecked && GetCockpitTimer() <= 0.0 && !lost && !won)
	{
		recycleChecked = TRUE;
		if (silosRecycled)
		{
			HideCockpitTimer();
		}
		else
		{
			lost = TRUE;
			sound5 = AudioMessage("bd13005.wav");
		}
	}

	if (sound5 != NULL && IsAudioMessageDone(sound5))
	{
		sound5 = NULL;
		FailMission(GetTime() + 1.0, "bd13lsea.des");
	}

	if (!silosRecycled && !lost && !won)
	{
		// check to see if any silos are gone this frame
		int numSilosGone = 0;

		for (i = 0; i < 6; i++)
		{
			if (recycled[i])
				continue;

			if (GetHealth(silos[i]) <= 0.0)
			{
				// find all the construction rigs in the world
				// did any of them just recycle this silo?
				bool r = isRecycledByTeam(silos[i], 1);
				if (r)
				{
					recycled[i] = TRUE;
				}
				else
				{
					lost = TRUE;
					FailMission(GetTime() + 1.0, "bd13lsec.des");
				}
			}
		}

		// check to see if they're all recycled
		silosRecycled = TRUE;
		for (i = 0; i < 6; i++)
		{
			if (!recycled[i])
				silosRecycled = FALSE;
		}
	}

	if (silosRecycled && !sound2Played)
	{
		HideCockpitTimer();
		recycleChecked = TRUE;
		sound2Played = TRUE;

		AudioMessage("bd13002.wav");

		ClearObjectives();
		AddObjective("bd13001.otf", GREEN);
		AddObjective("bd13002.otf", WHITE);
	}

	// has the player lost his recycler?
	if (GetHealth(recycler) <= 0.0 && !lost && !won)
	{
		lost = TRUE;
		sound4 = AudioMessage("bd13004.wav");
	}

	if (sound4 != NULL && IsAudioMessageDone(sound4))
	{
		sound4 = NULL;
		FailMission(GetTime() + 1.0, "bd13lseb.des");
	}

	// has the chinese recycler taken any damage?
	if (GetHealth(chinRecycler) < 1.0 && !silosRecycled && !lost && !won)
	{
		lost = TRUE;
		FailMission(GetTime() + 1.0, "bd13lsed.des");
	}

	if (GetHealth(chinRecycler) <= 0.0 && silosRecycled && !won && !lost)
	{
		won = TRUE;
		sound3 = AudioMessage("bd13003.wav");
	}

	if (sound3 != NULL && IsAudioMessageDone(sound3))
	{
		sound3 = NULL;
		SucceedMission(GetTime() + 1.0, "bd13win.des");
	}
}