#include "GameCommon.h"
#include "AiCommon.h"
#include "AiMission.h"
#include "AiProcess.h"
#include "PowerUp.h"
#include "ScriptUtils.h"

/*
	Chinese06Mission
*/

class Chinese06Mission : public AiMission {
	DECLARE_RTIME(Chinese06Mission)
public:
	Chinese06Mission();
	~Chinese06Mission();

	virtual bool Load(file fp);
	virtual bool PostLoad(void);
	virtual bool Save(file fp);

	virtual void Update(void);

	virtual void AddObject(GameObject *gameObj);

private:
	void Setup();
	void Execute();
	void AddObject(Handle h);
	Handle getBase();
	
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
				cameraReady[2], cameraComplete[2],

				// random thingy done?
				ranDone,
				turnTraitor,
				reinfDestroyed,
				alien1,

				// won or lost?
				won, lost,
				
				b_last;
		};
		bool b_array[14];
	};

	// floats
	union {
		struct {
			float
				openingSoundTime,
				sound2Time,
				sound3Time,
				sound4Time,
				ranTime,
				annoyStartTime,
				annoyTime,
				giveScrapTime,
				moreRanTime,
				f_last;
		};
		float f_array[9];
	};

	// handles
	union {
		struct {
			Handle
				// the user
				user,
				
				// units
				recycler,
				factory,
				armoury,
				silo1,
				silo2,
				reinf[12],
				psu[4],
				annoy[10],
				
				// navs
				
				// place holder
				h_last;
		};
		Handle h_array[32];
	};

	// integers
	union {
		struct {
			int
				ranChoice,
				// sounds
				openingSound,
				sound2, sound3, sound4,

				// annoyanced
				maxAnnoy,
				numAnnoyRounds,

				i_last;
		};
		int i_array[7];
	};
};

IMPLEMENT_RTIME(Chinese06Mission)

Chinese06Mission::Chinese06Mission()
{
}

Chinese06Mission::~Chinese06Mission()
{
}

bool Chinese06Mission::Load(file fp)
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

bool Chinese06Mission::PostLoad(void)
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

bool Chinese06Mission::Save(file fp)
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

void Chinese06Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

void Chinese06Mission::AddObject(Handle h)
{
}

void Chinese06Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

void Chinese06Mission::Setup()
{
	int i = 0;
	startDone = FALSE;
	objective1Complete = FALSE;
	objective2Complete = FALSE;
	objective3Complete = FALSE;
	ranDone = FALSE;
	turnTraitor = FALSE;
	reinfDestroyed = FALSE;
	alien1 = FALSE;
	
	// cameras
	for (i = 0; i < 2; i++)
	{
		cameraReady[i] = FALSE;
		cameraComplete[i] = FALSE;
	}
	
	// units
	user = NULL;
	recycler = GetHandle("avrecy2_recycler");
	factory = GetHandle("avmuf2_factory");
	armoury = GetHandle("avslf2_armory");
	silo1 = GetHandle("absilo2_scrapsilo");
	silo2 = GetHandle("absilo3_scrapsilo");
	for (i = 0; i < 12; i++)
		reinf[i] = NULL;
	psu[0] = GetHandle("psu_1");
	psu[1] = GetHandle("psu_2");
	psu[2] = GetHandle("psu_3");
	psu[3] = GetHandle("psu_4");
	for (i = 0; i < 10; i++)
		annoy[i] = NULL;
	
	// navs
	
	// sounds
	openingSound = NULL;
	sound2 = NULL;
	sound3 = NULL;
	sound4 = NULL;

	// times
	openingSoundTime = 999999.9f;
	sound2Time = 999999.9f;
	sound3Time = 999999.9f;
	sound4Time = 999999.9f;
	ranTime = 999999.9f;
	annoyStartTime = 999999.9f;
	annoyTime = 999999.9f;
	giveScrapTime = 999999.9f;
	moreRanTime = 999999.9f;

	// ints
	maxAnnoy = 10;
	numAnnoyRounds = 0;
	ranChoice = 0;
}

Handle Chinese06Mission::getBase()
{
	Handle h[5];
	int numH = 0;

	if (GetHealth(recycler) > 0.0f)
		h[numH++] = recycler;
	if (GetHealth(factory) > 0.0f)
		h[numH++] = factory;
	if (GetHealth(armoury) > 0.0f)
		h[numH++] = armoury;
	if (GetHealth(silo1) > 0.0f)
		h[numH++] = silo1;
	if (GetHealth(silo2) > 0.0f)
		h[numH++] = silo2;

	if (numH == 0)
		return NULL;
	else
		return h[rand() % numH];
}

void Chinese06Mission::Execute()
{
	int i = 0;
	user = GetPlayerHandle(); //assigns the player a handle every frame

	if (!startDone)
	{
		SetAIP("chmisn06.aip");
		SetPilot(1, 10);
		SetScrap(2, 0);
		SetScrap(1, 50);

		// don't do this part after the first shot
		startDone = TRUE;

		openingSoundTime = GetTime() + 2.0;
		sound2Time = GetTime() + 60.0f;
		annoyStartTime = GetTime() + 10 * 60.0f;
		giveScrapTime = GetTime() + 20 * 60.0f;

		//BuildObject("cvtnk", 1, user);
	}

	if (giveScrapTime < GetTime())
	{
		giveScrapTime = 999999.9f;
		AddScrap(2, 50);
	}

	if (openingSoundTime < GetTime())
	{
		openingSoundTime = 999999.9f;

		openingSound = AudioMessage("ch06001.wav");

		ClearObjectives();
		AddObjective("ch06001.otf", WHITE);
	}

	if (openingSound != NULL && IsAudioMessageDone(openingSound))
	{
		openingSound = NULL;
	}

	if (sound2Time < GetTime())
	{
		sound2Time = 999999.9f;

		sound2 = AudioMessage("ch06002.wav");
	}

	if (sound2 != NULL && IsAudioMessageDone(sound2))
	{
		sound2 = NULL;

		Handle h = BuildObject("apcamr", 1, "nav_1");
		SetName(h, "CCA Base");

		sound3Time = GetTime() + 15.0f;
	}

	if (sound3Time < GetTime())
	{
		sound3Time = 999999.9f;

		sound3 = AudioMessage("ch06003.wav");
	}

	if (sound3 != NULL && IsAudioMessageDone(sound3))
	{
		sound3 = NULL;
		sound4Time = GetTime() + 1.0f;
	}

	if (sound4Time < GetTime())
	{
		sound4Time = 999999.9f;

		sound4 = AudioMessage("ch06004.wav");
	}

	if (sound4 != NULL && IsAudioMessageDone(sound4))
	{
		sound4 = NULL;
		ranTime = GetTime() + 180.0f;
	}

	if (ranTime < GetTime())
	{
		ranTime = 999999.9f;

		char *ran[3] = { "ran_1", "ran_2", "ran_3" };
		char *ranPath[3] = { "ran_1_path", "ran_2_path", "ran_3_path" };
		int num = rand() % 3;
		char *spawn = ran[num];
		char *path = ranPath[num];
		ranChoice = num;

		reinf[0] = BuildObject("cvfigh", 1, spawn);
		reinf[1] = BuildObject("cvfigh", 1, spawn);
		reinf[2] = BuildObject("cvfigh", 1, spawn);
		reinf[3] = BuildObject("cvfigh", 1, spawn);
		reinf[4] = BuildObject("cvtnk", 1, spawn);
		reinf[5] = BuildObject("cvtnk", 1, spawn);
		reinf[6] = BuildObject("cvtnk", 1, spawn);
		reinf[7] = BuildObject("cvtnk", 1, spawn);
		reinf[8] = BuildObject("cvhraz", 1, spawn);
		reinf[9] = BuildObject("cvhraz", 1, spawn);
		reinf[10] = BuildObject("cvhraz", 1, spawn);
		reinf[11] = BuildObject("cvhraz", 1, spawn);
		

		for (i = 0; i < 12; i++)
		{

			SetPerceivedTeam(reinf[i], 2);
			Goto(reinf[i], path, 1);

			// put a sspilo in each one
			GameObject *o = GameObjectHandle::GetObj(reinf[i]);
			_ASSERTE(o != NULL);
			o->curPilot = *(PrjID*)"sspilo";
		}

		ranDone = TRUE;
	}

	if (ranDone && !turnTraitor)
	{
		char *path[3] = { "ran_1_trigger", "ran_2_trigger", "ran_3_trigger" };
		char *p = path[ranChoice];

		for (i = 0; i < 12; i++)
		{
			if (GetHealth(reinf[i]) < 0.70) // come under attack?
			{
				turnTraitor = TRUE;
				break;
			}
			else if (IsAlive(reinf[i]) && GetDistance(reinf[i], p) < 75.0f)
			{
				// gone far enough?
				turnTraitor = TRUE;
				break;
			}
		}

		if (turnTraitor)
		{
			//_DEBUGMSG0("Setting traitor's team number to 2");
			for (i = 0; i < 12; i++)
			{
				SetTeamNum(reinf[i], 2);
				SetPerceivedTeam(reinf[i], 2);
				Attack(reinf[i], getBase(), 0);
			}
			AudioMessage("ch06005.wav");
			moreRanTime = GetTime() + 2 * 60.0f;
		}
	}


	if (moreRanTime < GetTime())
	{
		char *others[3] = { NULL, NULL };
		int num = 0;
		if (ranChoice != 0)
			others[num++] = "ran_1";
		if (ranChoice != 1)
			others[num++] = "ran_2";
		if (ranChoice != 2)
			others[num++] = "ran_3";
		char *p = others[rand() % 2];
		for (i = 0; i < 4; i++)
		{
			Handle h = BuildObject("svfigh", 2, p);
			Attack(h, getBase(), 0);
		}
		for (i = 0; i < 4; i++)
		{
			Handle h = BuildObject("svtank", 2, p);
			Attack(h, getBase(), 0);
		}
	}

	if (ranDone && !reinfDestroyed)
	{
		reinfDestroyed = TRUE;
		for (i = 0; i < 12; i++)
		{
			if (IsAlive(reinf[i]))
			{
				reinfDestroyed = FALSE;
			}
		}

		if (reinfDestroyed)
		{
			AudioMessage("ch06006.wav");
		}
	}

	if (reinfDestroyed && !won && !lost)
	{
		won = TRUE;
		// see if everything on the mission is dead

		ObjectList &list = *GameObject::objectList;
		for (ObjectList::iterator i = list.begin(); i != list.end(); i++) 
		{
			GameObject *o = *i;

			if (o->GetTeam() != 2)
				continue;

			Handle h = GameObjectHandle::Find(o);
			if (IsAlive(h))
			{
				won = FALSE;
			}
		}

		if (won)
		{
			SucceedMission(GetTime() + 1.0, "ch06win.des");
		}
	}

	if (GetHealth(recycler) <= 0.0 && GetHealth(factory) <= 0.0 && !lost && !won)
	{
		lost = TRUE;
		FailMission(GetTime(), "ch06lsea.des");
	}

	if (annoyStartTime < GetTime())
	{
		// is the recycler or factory within range?
		if (GetDistance(recycler, "activate_1") < 500 ||
			GetDistance(recycler, "activate_2") < 500 ||
			GetDistance(factory, "activate_1") < 500 ||
			GetDistance(factory, "activate_2") < 500)
		{
			annoyTime = GetTime();
			annoyStartTime = 999999.9f;
		}
		else
		{
			// check again in 60 seconds
			annoyStartTime = GetTime() + 60.0f; 
		}
	}

	if (annoyTime < GetTime())
	{
		// are the psu units still alive?
		if (IsAlive(psu[0]) ||
			IsAlive(psu[1]) ||
			IsAlive(psu[2]) ||
			IsAlive(psu[3]))
		{
			static char *units[4] = 
			{
				"svfigh", "svltnk", "svtank", "svhraz"
			};
			annoyTime = GetTime() + 5 * 60.0f;
			numAnnoyRounds++;
			if (numAnnoyRounds == 3)
				maxAnnoy = 6;

			// spawn
			for (i = 0; i < maxAnnoy; i++)
			{
				if (annoy[i] != NULL && GetHealth(annoy[i]) > 0.0f)
					continue;

				annoy[i] = BuildObject(units[rand() % 4], 2, "annoy_1");
				Goto(annoy[i], "annoy_1_path");
			}
		}
		else
		{
			// these raids stop now
			annoyTime = 999999.9f;
		}
		
	}
}
