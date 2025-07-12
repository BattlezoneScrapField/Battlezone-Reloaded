#include "GameCommon.h"
#include "AiCommon.h"
#include "AiMission.h"
#include "AiProcess.h"
#include "PowerUp.h"
#include "ScriptUtils.h"


/*
	Chinese08Mission
*/

class Chinese08Mission : public AiMission {
	DECLARE_RTIME(Chinese08Mission)
public:
	Chinese08Mission();
	~Chinese08Mission();

	virtual bool Load(file fp);
	virtual bool PostLoad(void);
	virtual bool Save(file fp);

	void resetObjectives();

	virtual void Update(void);

	virtual void AddObject(GameObject *gameObj);
	bool checkAPCs();
	void checkSpawns();

private:
	void Setup();
	void Execute();
	void AddObject(Handle h);

	// bools
	union {
		struct {
			bool
				// have we lost?
				lost, 

				spawn_1,
				spawn_2,
				spawn_3,
				spawn_4,
				spawn_5,
				spawn_6,
				
				west_powerDead,
				east_powerDead,
				west_commDead,
				east_commDead,

				startwalker,
				apc3objectiveon,
				howitzerobjectiveon,

				b_last;
		};
		bool b_array[14];
	};

	// floats
	union {
		struct {
			float
				stateTimer,  // timer to say when the next state starts
				apcInLine,

				f_last;
		};
		float f_array[2];
	};

	// handles
	union {
		struct {
			Handle
				// the user
				user,
				olduser,

				west_1_1,
				west_1_2, 
				west_1_3, 
				west_1_4, 
				east_1_1,
				east_1_2, 
				east_1_3,
				east_1_4,

				howitzer_nw,
				howitzer_ne,

				west_power,
				east_power,

				west_comm,
				east_comm,

				west_bolt,
				east_bolt,

				walker_1,
				
				apc[5],

				magpull[6],
				west_mag[4],
				east_mag[4],

				snipers[26],

				nav,

				recycler,
				factory,

				// place holder
				h_last;
		};
		Handle h_array[67];
	};

	// integers
	union {
		struct {
			int
				missionState,
				userCloakState,

				soundHandle,
				coreFailSound,

				i_last;
		};
		int i_array[4];
	};
};

IMPLEMENT_RTIME(Chinese08Mission)

Chinese08Mission::Chinese08Mission()
{
}

Chinese08Mission::~Chinese08Mission()
{
}

bool Chinese08Mission::Load(file fp)
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

bool Chinese08Mission::PostLoad(void)
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

bool Chinese08Mission::Save(file fp)
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

void Chinese08Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

void Chinese08Mission::AddObject(Handle h)
{
}

void Chinese08Mission::Update(void)
{
	AiMission::Update();
	Execute();
}


#define MS_STARTUP					1
#define MS_WAITFORCLOAK			2
#define MS_WAITFORTRIGGER		3
#define MS_CAMERATRIGGER		4
#define MS_SPAWNAPC1				5
#define MS_SPAWNAPC2				6
#define MS_SPAWNAPC3				7
#define MS_SPAWNAPC4				8
#define MS_SPAWNAPC5				9
#define MS_WAITFORSCAP			10
#define MS_WAITSTARTSOUND4	11
#define MS_DISPLAYOBJ6			12
#define MS_WAITFORSOUND4		13
#define MS_DISPLAYOBJ1			14
#define MS_TRIGGER1					15
#define MS_WAITFORJUMPOUT		16
#define MS_WAITFORWRECKER		17
#define MS_BANGCAMERA				18
#define MS_BANGCAMERA2			19
#define MS_DISPODJ5					20
#define MS_TRIGGERNWNE			21
#define MS_DISPOBJ7					22
#define MS_DESTROYPOWERS		23
#define MS_DISPOBJ2					24
#define MS_WAITFORSOUND8		25
#define MS_DESTROYTOWERS		26
#define MS_WRECKER10				27
#define MS_WRECKER22				28
#define MS_WRECKER33				29
#define MS_WRECKER42				30
#define MS_WRECKER55				31
#define MS_WRECKER70				32
#define MS_WRECKER85				33
#define MS_WRECKER92				34
#define MS_WRECKER100				35
#define MS_WRECKER106				36
#define MS_END							100


bool Chinese08Mission::checkAPCs()
{
	int i;
	Handle temp;

	temp = apc[4];
	if(!IsAlive(temp) && GetHealth(apc[4]) <= 0)
	{
		missionState = MS_END;
		FailMission(GetTime() + 2.0f, "ch08lsed.des");
		return TRUE;
	}

	if(GetDistance(apc[3], "break_point") < 50)
	{
		apcInLine = 2;
	}

	temp = apc[4];
	if(!IsAlive(temp) && apcInLine == 0)
	{
		apcInLine = GetTime() + 25;
	}
	else if(apcInLine > 2 && apcInLine < GetTime())
	{
		if(GetDistance(apc[4], apc[3]) > 100)
		{
			AudioMessage("ch08005.wav");
			missionState = MS_END;
			FailMission(GetTime() + 20.0f, "ch08lseb.des");
			return TRUE;
		}

		apcInLine = 1;
	}
	else if(apcInLine == 1)
	{
		if(GetDistance(apc[4], apc[3]) > 100)
		{
			AudioMessage("ch08005.wav");
			missionState = MS_END;
			FailMission(GetTime() + 20.0f, "ch08lsee.des");
			return TRUE;
		}
	}

	for(i = 0; i < 4; i++)
	{
		temp = apc[i];
		if(!IsAlive(temp))
		{
			missionState = MS_END;
			FailMission(GetTime() + 2.0f, "ch08lsed.des");
			return TRUE;
		}
	}

	return FALSE;
}


void Chinese08Mission::checkSpawns()
{
	Handle temp;
	int i;

	if(!spawn_1)
	{
		temp = GetNearestUnitOnTeam("spawn_1", 0, 1);

		if(temp)
		{
			if(GetDistance(temp, "spawn_1") < 100)
			{
				spawn_1 = TRUE;

				for(i = 0; i < 3; i++)
				{
					Goto(BuildObject("svfigh", 2, "wave_1"), "wave_1");
				}
			}
		}
	}

	if(!spawn_2)
	{
		temp = GetNearestUnitOnTeam("spawn_2", 0, 1);

		if(temp)
		{
			if(GetDistance(temp, "spawn_2") < 100)
			{
				spawn_2 = TRUE;

				for(i = 0; i < 3; i++)
				{
					Goto(BuildObject("svfigh", 2, "wave_2"), "wave_2");
				}

				for(i = 0; i < 5; i++)
				{
					Goto(BuildObject("svtank", 2, "wave_2"), "wave_2");
				}
			}
		}
	}

	if(!spawn_2)
	{
		temp = GetNearestUnitOnTeam("spawn_2a", 0, 1);

		if(temp)
		{
			if(GetDistance(temp, "spawn_2a") < 100)
			{
				spawn_2 = TRUE;

				for(i = 0; i < 3; i++)
				{
					Goto(BuildObject("svfigh", 2, "wave_2"), "wave_2");
				}

				for(i = 0; i < 5; i++)
				{
					Goto(BuildObject("svtank", 2, "wave_2"), "wave_2");
				}
			}
		}
	}

	if(!spawn_3)
	{
		temp = GetNearestUnitOnTeam("spawn_3", 0, 1);

		if(temp)
		{
			if(GetDistance(temp, "spawn_3") < 100)
			{
				spawn_3 = TRUE;

				for(i = 0; i < 3; i++)
				{
					Goto(BuildObject("svfigh", 2, "wave_3"), "wave_3");
				}

				for(i = 0; i < 5; i++)
				{
					Goto(BuildObject("svtank", 2, "wave_3"), "wave_3");
				}
			}
		}
	}

	if(!spawn_3)
	{
		temp = GetNearestUnitOnTeam("spawn_3a", 0, 1);

		if(temp)
		{
			if(GetDistance(temp, "spawn_3a") < 100)
			{
				spawn_3 = TRUE;

				for(i = 0; i < 3; i++)
				{
					Goto(BuildObject("svfigh", 2, "wave_3"), "wave_3");
				}

				for(i = 0; i < 5; i++)
				{
					Goto(BuildObject("svtank", 2, "wave_3"), "wave_3");
				}
			}
		}
	}

	if(!spawn_4)
	{
		temp = GetNearestUnitOnTeam("spawn_4", 0, 1);

		if(temp)
		{
			if(GetDistance(temp, "spawn_4") < 100)
			{
				spawn_4 = TRUE;

				for(i = 0; i < 3; i++)
				{
					Goto(BuildObject("svwalk", 2, "wave_4"), "wave_4");
				}
			}
		}
	}


	if(!spawn_5)
	{
		temp = GetNearestUnitOnTeam("spawn_5", 0, 1);

		if(temp)
		{
			if(GetDistance(temp, "spawn_5") < 100)
			{
				spawn_5 = TRUE;

				for(i = 0; i < 3; i++)
				{
					Goto(BuildObject("svfigh", 2, "wave_5"), "wave_5");
				}

				for(i = 0; i < 5; i++)
				{
					Goto(BuildObject("svtank", 2, "wave_5"), "wave_5");
				}
			}
		}
	}


	if(!spawn_6)
	{
		temp = GetNearestUnitOnTeam("spawn_6", 0, 1);

		if(temp)
		{
			if(GetDistance(temp, "spawn_6") < 100)
			{
				spawn_6 = TRUE;

				for(i = 0; i < 3; i++)
				{
					Goto(BuildObject("svfigh", 2, "wave_6"), "wave_6");
				}

				for(i = 0; i < 5; i++)
				{
					Goto(BuildObject("svtank", 2, "wave_6"), "wave_6");
				}
			}
		}
	}
}


void Chinese08Mission::resetObjectives()
{
	ClearObjectives();

/*
	if(missionState == MS_DISPLAYOBJ1)
	{
		AddObjective("ch08001.otf", GREEN);
	}
	else 
*/
  if(missionState >= MS_WAITFORSCAP && missionState < MS_WAITSTARTSOUND4)
	{
		AddObjective("ch08001.otf", WHITE);
	}

/*
	if(missionState == MS_DISPLAYOBJ6)
	{
		AddObjective("ch08006.otf", GREEN);
	}
	else 
*/
  if(missionState >= MS_WAITSTARTSOUND4 && missionState < MS_DISPLAYOBJ1)
	{
		AddObjective("ch08006.otf", WHITE);
	}
/*
	if(missionState == MS_DISPODJ5)
	{
		AddObjective("ch08005.otf", GREEN);
	}
	else 
*/
	if(missionState >= MS_DISPLAYOBJ1 && missionState < MS_DISPODJ5)
	{
		AddObjective("ch08005.otf", WHITE);
	}

/*
	if(missionState == MS_DISPOBJ7)
	{
		AddObjective("ch08007.otf", GREEN);
	}
	else 
*/
	if(missionState >= MS_DISPODJ5 && missionState < MS_DISPOBJ7)
	{
		AddObjective("ch08007.otf", WHITE);
	}

/*
	if(missionState == MS_DISPOBJ2)
	{
		AddObjective("ch08002.otf", GREEN);
	}
	else 
*/
	if(missionState >= MS_DISPOBJ7 && missionState < MS_DISPOBJ2)
	{
		AddObjective("ch08002.otf", WHITE);
	}

	
	if(missionState >= MS_WRECKER106)
	{
		AddObjective("ch08004.otf", GREEN);
	}
	else if(missionState >= MS_DISPOBJ2) 
	{
		AddObjective("ch08004.otf", WHITE);
	}
/*
	if(missionState >= MS_WRECKER10)
	{
		AddObjective("ch08003.otf", GREEN);
	}
	else if(missionState >= MS_DISPOBJ2)
	{
		AddObjective("ch08003.otf", WHITE);
	}
*/
}


void Chinese08Mission::Setup()
{
	int i;
	char buf[20];

	west_1_1 = GetHandle("west_1_1");
	west_1_2 = GetHandle("west_1_2");
	west_1_3 = GetHandle("west_1_3");
	west_1_4 = GetHandle("west_1_4");
	east_1_1 = GetHandle("east_1_1");
	east_1_2 = GetHandle("east_1_2");
	east_1_3 = GetHandle("east_1_3");
	east_1_4 = GetHandle("east_1_4");
	nav = GetHandle("nav");
	SetName(nav, "Base");
	howitzer_nw = GetHandle("howitzer_nw");
	howitzer_ne = GetHandle("howitzer_ne");
	west_power = GetHandle("west_power");
	east_power = GetHandle("east_power");
	east_bolt = GetHandle("east_bolt");
	west_bolt = GetHandle("west_bolt");

	walker_1 = GetHandle("walker_1");
	
	for(i = 0; i < 6; i++)
	{
		sprintf(buf, "magpull_%d", i + 1);
		magpull[i] = GetHandle(buf);
	}

	for(i = 0; i < 4; i++)
	{
		sprintf(buf, "west_mag_%d", i + 1);
		west_mag[i] = GetHandle(buf);

		sprintf(buf, "east_mag_%d", i + 1);
		east_mag[i] = GetHandle(buf);
	}


	for(i = 0; i < 26; i++)
	{
		sprintf(buf, "sniper_%d", i + 1);
		snipers[i] = GetHandle(buf);
	}

	west_comm = GetHandle("west_comm");
	east_comm = GetHandle("east_comm");

	spawn_1 = FALSE;
	spawn_2 = FALSE;
	spawn_3 = FALSE;
	spawn_4 = FALSE;
	spawn_5 = FALSE;
	spawn_6 = FALSE;

	west_powerDead = FALSE;
	east_powerDead = FALSE;
	west_commDead = FALSE;
	east_commDead = FALSE;

	apcInLine = 0;

	missionState = MS_STARTUP;
	userCloakState = 0;
}

void Chinese08Mission::Execute()
{
	int i = 0;
	bool cameraFinishedRet;
	Handle temp;

	user = GetPlayerHandle(); //assigns the player a handle every frame

	if(missionState < MS_END && missionState > MS_BANGCAMERA)
	{
		if(!IsAlive(recycler) && !IsAlive(factory))
		{
			FailMission(GetTime() + 2.0f, "ch08lsea.des");
			missionState = MS_END;
		}
	}

	if(missionState == MS_STARTUP || olduser != user)
	{
		for(i = 0; i < 26; i++)
		{
			Attack(snipers[i], user);
		}
	}

	if(missionState >= MS_SPAWNAPC1 && missionState <= MS_WAITFORSCAP && soundHandle && IsAudioMessageDone(soundHandle))
	{
		soundHandle = 0;

		temp = BuildObject("apcamr", 1, "apc_nav");
		SetName(temp, "APC Convoy");
		SetUserTarget(temp);
	}

	if(userCloakState == 0)
	{
		if(GetDistance(user, "east_cloak") < 200 || GetDistance(user, "west_cloak") < 200)
		{
			if(isCloaked(user))
			{
				coreFailSound = AudioMessage("ch04002.wav");
				Decloak(user);
			}

			userCloakState = 1;
			enableCloaking(user, FALSE);
		}
	}
	else
	{
		if(coreFailSound)
		{
			if(IsAudioMessageDone(coreFailSound))
			{
				coreFailSound = 0;
			}
		}
		else if(isCloaked(user))
		{
			coreFailSound = AudioMessage("ch04002.wav");
			Decloak(user);
		}
	}


	switch(missionState)
	{
		case MS_STARTUP:
		{
			olduser = user;

			SetAIP("chmisn08.aip");
			SetScrap(1, 0);
			SetPilot(1, 10);
			SetScrap(2, 0);

			AudioMessage("ch08001.wav");

			missionState = MS_WAITFORTRIGGER;

			Cloak(west_1_1);
			Cloak(west_1_2);
			Cloak(west_1_3);
			Cloak(west_1_4);
			Cloak(east_1_1);
			Cloak(east_1_2);
			Cloak(east_1_3);
			Cloak(east_1_4);

			CameraReady();
			break;
		}

		case MS_WAITFORCLOAK:
			break;

		case MS_WAITFORTRIGGER:
			CameraPath("cut_1", 2000, 0, west_1_1); 

			if(GetDistance(west_1_1, "cut_trigger") < 50 || GetDistance(east_1_1, "cut_trigger") < 50)
			{
				missionState = MS_CAMERATRIGGER;
				stateTimer = GetTime() + 22;
			}
			break;

		case MS_CAMERATRIGGER:
			CameraPath("cut_1", 2000, 0, west_1_1); 

			if(stateTimer && stateTimer < GetTime())
			{
				CameraFinish();
				missionState = MS_SPAWNAPC1;
				stateTimer = GetTime() + 30;
				AudioMessage("ch08002.wav");

				RemoveObject(west_1_1);
				RemoveObject(west_1_2);
				RemoveObject(west_1_3);
				RemoveObject(west_1_4);
				RemoveObject(east_1_1);
				RemoveObject(east_1_2);
				RemoveObject(east_1_3);
				RemoveObject(east_1_4);
				RemoveObject(walker_1);
			}
			break;

		case MS_SPAWNAPC1:
			if(stateTimer < GetTime())
			{
				soundHandle = AudioMessage("ch08003.wav");

				apc[0] = BuildObject("svapc", 2, "apc_spawn");
				SetName(apc[0], "apc_1");
				Goto(apc[0], "apc_path");

				temp = BuildObject("svfigh", 2, "apc_escort");
				Defend2(temp, apc[0]);

				temp = BuildObject("svfigh", 2, "apc_escort");
				Defend2(temp, apc[0]);

				missionState = MS_SPAWNAPC2;
				resetObjectives();
				stateTimer = GetTime() + 5;
			}
			break;

		case MS_SPAWNAPC2:
			if(stateTimer < GetTime())
			{
				apc[1] = BuildObject("svapc", 2, "apc_spawn");
				SetName(apc[1], "apc_2");
				Goto(apc[1], "apc_path");

				missionState = MS_SPAWNAPC3;
				resetObjectives();
				stateTimer = GetTime() + 5;
			}
			break;

		case MS_SPAWNAPC3:
			if(stateTimer < GetTime())
			{
				apc[2] = BuildObject("svapc", 2, "apc_spawn");
				SetName(apc[2], "apc_3");
				Goto(apc[2], "apc_path");

				missionState = MS_SPAWNAPC4;
				resetObjectives();
				stateTimer = GetTime() + 5;
			}
			break;

		case MS_SPAWNAPC4:
			if(stateTimer < GetTime())
			{
				apc[3] = BuildObject("svapc", 2, "apc_spawn");
				SetName(apc[3], "apc_4");
				Goto(apc[3], "apc_path");

				missionState = MS_SPAWNAPC5;
				resetObjectives();
				stateTimer = GetTime() + 5;
			}
			break;

		case MS_SPAWNAPC5:
			if(stateTimer < GetTime())
			{
				apc[4] = BuildObject("svapc", 2, "apc_spawn");
				SetName(apc[4], "apc_5");
				Goto(apc[4], "apc_path");

				missionState = MS_WAITFORSCAP;
				resetObjectives();

//				SetUserTarget(apc[4]);
				startwalker = FALSE;
			}
			break;

		case MS_WAITFORSCAP:
			if(checkAPCs())
			{
				break;
			}

			if(apc[4] == user && GetDistance(apc[4], nav) <= 30)
			{
				stateTimer = GetTime() + 5;
				missionState = MS_WAITSTARTSOUND4;
				resetObjectives();
			}
#if 0
			if(!startwalker && GetDistance(apc[0], walker_1) < 200)
			{
				Goto(walker_1, "walker_path");
				startwalker = TRUE;
			}
#endif
			if(GetDistance(apc[3], "apc_fail") < 30 || (GetDistance(apc[4], "trigger_1") < 30 && GetDistance(apc[3], "apc_fail") > 300))
			{
				AudioMessage("ch08005.wav");
				missionState = MS_END;
				FailMission(GetTime() + 20.0f, "ch08lsec.des");
				break;
			}
			break;

		case MS_WAITSTARTSOUND4:
			if(checkAPCs())
			{
				break;
			}
#if 0
			if(!startwalker && GetDistance(apc[0], walker_1) < 200)
			{
				Goto(walker_1, "walker_path");
				startwalker = TRUE;
			}
#endif
			if(((GetDistance(apc[3], "apc_fail") < 50) && (apc[4] != user || GetDistance(apc[3], user) > 75))
						 || (GetDistance(apc[4], "trigger_1") < 30 && GetDistance(apc[3], "apc_fail") > 300))
			{
				AudioMessage("ch08005.wav");
				missionState = MS_END;
				FailMission(GetTime() + 20.0f, "ch08lsec.des");
				break;
			}

			if(stateTimer < GetTime())
			{
				SetScrap(1, 100);
				soundHandle = AudioMessage("ch08004.wav");
				missionState = MS_DISPLAYOBJ6;
				resetObjectives();
				missionState = MS_WAITFORSOUND4;

				SetObjectiveOn(apc[3]);
				apc3objectiveon = TRUE;
			}
			break;

		case MS_WAITFORSOUND4:
			if(checkAPCs())
			{
				break;
			}
#if 0
			if(!startwalker && GetDistance(apc[0], walker_1) < 200)
			{
				Goto(walker_1, "walker_path");
				startwalker = TRUE;
			}
#endif
			if(apc3objectiveon && GetDistance(apc[3], user) < 100)
			{
				apc3objectiveon = FALSE;
				SetObjectiveOff(apc[3]);
			}

			if(((GetDistance(apc[3], "apc_fail") < 50) && (apc[4] != user || GetDistance(apc[3], user) > 75)) 
						 || (GetDistance(apc[4], "trigger_1") < 30 && GetDistance(apc[3], "apc_fail") > 300))
			{
				AudioMessage("ch08005.wav");
				missionState = MS_END;
				FailMission(GetTime() + 20.0f, "ch08lsec.des");
				break;
			}

			if(IsAudioMessageDone(soundHandle))
			{
/*
				recycler = BuildObject("cvrecy", 1, "military_spawn");
				Goto(recycler, "military_path");
				factory = BuildObject("cvmuf", 1, "military_spawn");
				Goto(factory, "military_path");
				Goto(BuildObject("cvslf", 1, "military_spawn"), "military_path");
*/
				missionState = MS_DISPLAYOBJ1;
				resetObjectives();
				missionState = MS_TRIGGER1;
			}
			break;

		case MS_TRIGGER1:
			if(checkAPCs())
			{
				break;
			}

			if(apc3objectiveon && GetDistance(apc[3], user) < 100)
			{
				apc3objectiveon = FALSE;
				SetObjectiveOff(apc[3]);
			}

			if(((GetDistance(apc[3], "apc_fail") < 50) && (apc[4] != user || GetDistance(apc[3], user) > 75))
						 || (GetDistance(apc[4], "trigger_1") < 30 && GetDistance(apc[3], "apc_fail") > 300))
			{
				AudioMessage("ch08005.wav");
				missionState = MS_END;
				FailMission(GetTime() + 20.0f, "ch08lsec.des");
				break;
			}

			if(apc[4] == user && GetDistance(user, "trigger_1") < 30)
			{
				AudioMessage("ch08006.wav");
				missionState = MS_WAITFORJUMPOUT;
				stateTimer = GetTime() + 20;
			}
			break;

		case MS_WAITFORJUMPOUT:
			if(stateTimer < GetTime())
			{
				missionState = MS_END;
				FailMission(GetTime() + 2.0f, "ch08lseg.des");
				break;
			}

			if(apc[4] != user)
			{
				//Goto(walker_1, "walker_return");

				SetPerceivedTeam(user, 2);

				missionState = MS_WAITFORWRECKER;
				stateTimer = GetTime() + 20;
				//Goto(walker_1, "walker_return");
			}
			break;

		case MS_WAITFORWRECKER:
			if(apc[4] == user) 
			{
				missionState = MS_END;
				FailMission(GetTime() + 2.0f, "ch08lseg.des");
				break;
			}

			if(stateTimer < GetTime())
			{
				CameraReady();
				missionState = MS_BANGCAMERA;
				stateTimer = GetTime() + 5;
			}
			break;

		case MS_BANGCAMERA:
			CameraPath("cut_bang", 2000, 0, apc[4]); 

			cameraFinishedRet = CameraCancelled();
			if(stateTimer < GetTime() || cameraFinishedRet)
			{
				if (useD3D & 4)
				{
					MakeExplosion(apc[4], "xpltrsr");
				} 
				else
				{
					MakeExplosion(apc[4], "xpltrss");
				}	

				MakeExplosion("wrecker_1", "xpltrsd");
				SetPerceivedTeam(user, 1);

				// remove mag pull's
				for(i = 0; i < 6; i++)
				{
					RemoveObject(magpull[i]);
				}

				recycler = BuildObject("cvrecy", 1, "military_spawn");
				Goto(recycler, "military_path");
				factory = BuildObject("cvmuf", 1, "military_spawn");
				Goto(factory, "military_path");
				Goto(BuildObject("cvslf", 1, "military_spawn"), "military_path");
				SetScrap(1, GetMaxScrap(1));

				if(cameraFinishedRet)
				{
					CameraFinish();
					missionState = MS_DISPODJ5;
					resetObjectives();
					missionState = MS_TRIGGERNWNE;

					stateTimer = GetTime() + (5 * 60);
				}
				else
				{
					stateTimer = GetTime() + 5;
					missionState = MS_BANGCAMERA2;
				}
			}
			break;

		case MS_BANGCAMERA2:
			CameraPath("cut_bang", 2000, 0, apc[4]); 

			if(stateTimer < GetTime() || CameraCancelled())
			{
				CameraFinish();
				missionState = MS_DISPODJ5;
				resetObjectives();
				missionState = MS_TRIGGERNWNE;
				
				stateTimer = GetTime() + (5 * 60);
			}
			break;

		case MS_TRIGGERNWNE:
			if(stateTimer && stateTimer < GetTime())
			{
				stateTimer = 0;

				SetScrap(2, 100);

				//for(i = 0; i < 6; i++)
				//{
				//	Hunt(BuildObject("svscav", 2, "scavs"));
				//}
			}

			if(GetDistance(user, "nw_trigger") <= 60)
			{
				AudioMessage("ch08007.wav");
				AudioMessage("ch08008.wav");

				SetObjectiveOn(howitzer_nw);
				SetObjectiveOn(howitzer_ne);
				howitzerobjectiveon = TRUE;
				SetObjectiveOn(west_power);
				SetObjectiveOn(east_power);
				SetObjectiveOn(west_comm);
				SetObjectiveOn(east_comm);

				missionState = MS_DISPOBJ7;
				resetObjectives();
				missionState = MS_DESTROYPOWERS;
				
				SetUserTarget(howitzer_nw);
			}
			else if(GetDistance(user, "ne_trigger") <= 60)
			{
				AudioMessage("ch08007.wav");
				AudioMessage("ch08008.wav");

				SetObjectiveOn(howitzer_nw);
				SetObjectiveOn(howitzer_ne);
				howitzerobjectiveon = TRUE;
				SetObjectiveOn(west_power);
				SetObjectiveOn(east_power);
				SetObjectiveOn(west_comm);
				SetObjectiveOn(east_comm);

				missionState = MS_DISPOBJ7;
				resetObjectives();
				missionState = MS_DESTROYPOWERS;
				
				SetUserTarget(howitzer_ne);
			}
			break;

		case MS_DESTROYPOWERS:
			if((west_powerDead || east_powerDead || west_commDead || east_commDead) && GetCockpitTimer() < 1)
			{
				FailMission(GetTime() + 2.0f, "ch08lsef.des");
				missionState = MS_END;
				break;
			}

			if(stateTimer && stateTimer < GetTime())
			{
				stateTimer = 0;

				SetScrap(2, 50);
			}

			if(howitzerobjectiveon && (user == howitzer_nw || user == howitzer_ne))
			{
				howitzerobjectiveon = FALSE;
				SetObjectiveOff(howitzer_nw);
				SetObjectiveOff(howitzer_ne);
			}


			if(!west_powerDead && !IsAlive(west_power))
			{
				west_powerDead = TRUE;

				if(!east_powerDead && !west_commDead && !east_commDead)
				{
					StartCockpitTimer(60 * 4.5);
				}

				// remove west_mag units...
				for(i = 0; i < 4; i++)
				{
					RemoveObject(west_mag[i]);
				}
				RemoveObject(west_bolt);
			}

			if(!west_commDead && !IsAlive(west_comm))
			{
				west_commDead = TRUE;

				if(!east_powerDead && !west_powerDead && !east_commDead)
				{
					StartCockpitTimer(60 * 4.5);
				}
			}

			if(!east_powerDead && !IsAlive(east_power))
			{
				east_powerDead = TRUE;

				if(!west_powerDead && !east_commDead && !west_commDead)
				{
					StartCockpitTimer(60 * 4.5);
				}

				// remove east_mag units...
				for(i = 0; i < 4; i++)
				{
					RemoveObject(east_mag[i]);
				}
				RemoveObject(west_bolt);
			}

			if(!east_commDead && !IsAlive(east_comm))
			{
				east_commDead = TRUE;

				if(!east_powerDead && !west_powerDead && !west_commDead)
				{
					StartCockpitTimer(60 * 4.5);
				}
			}

			if(west_powerDead && east_powerDead && west_commDead && east_commDead)
			{
				HideCockpitTimer();
				missionState = MS_DISPOBJ2;
				resetObjectives();
				missionState = MS_WRECKER10;
				stateTimer = GetTime() + 40;
/*
				soundHandle = AudioMessage("ch08008.wav");

				missionState = MS_DISPOBJ2;
				resetObjectives();
				missionState = MS_WAITFORSOUND8;
*/
			}
			break;

		case MS_WAITFORSOUND8:
			if(IsAudioMessageDone(soundHandle))
			{
				missionState = MS_DESTROYTOWERS;
				StartCockpitTimer(60 + 40);
			}
			break;

		case MS_DESTROYTOWERS:
			if(GetCockpitTimer() < 1)
			{
				FailMission(GetTime() + 2.0f, "ch08lsef.des");
				missionState = MS_END;
				break;
			}

			if(!IsAlive(west_comm) && !IsAlive(east_comm))
			{
				HideCockpitTimer();
				missionState = MS_WRECKER10;
				resetObjectives();
				stateTimer = GetTime() + 10;
			}
			break;

		case MS_WRECKER10:
			if(stateTimer < GetTime())
			{
				MakeExplosion("day_1", "xpltrsd");
				MakeExplosion("day_1a", "xpltrsd");
				stateTimer = GetTime() + 12;
				missionState = MS_WRECKER22;
			}
			break;

		case MS_WRECKER22:
			if(stateTimer < GetTime())
			{
				MakeExplosion("day_2", "xpltrsd");
				MakeExplosion("day_2a", "xpltrsd");
				stateTimer = GetTime() + 11;
				missionState = MS_WRECKER33;
			}
			break;

		case MS_WRECKER33:
			if(stateTimer < GetTime())
			{
				MakeExplosion("day_3", "xpltrsd");
				stateTimer = GetTime() + 9;
				missionState = MS_WRECKER42;
			}
			break;

		case MS_WRECKER42:
			if(stateTimer < GetTime())
			{
				MakeExplosion("day_4", "xpltrsd");
				MakeExplosion("day_4a", "xpltrsd");
				stateTimer = GetTime() + 13;
				missionState = MS_WRECKER55;
			}
			break;

		case MS_WRECKER55:
			if(stateTimer < GetTime())
			{
				MakeExplosion("day_5", "xpltrsd");
				MakeExplosion("day_5a", "xpltrsd");
				stateTimer = GetTime() + 15;
				missionState = MS_WRECKER70;
			}
			break;

		case MS_WRECKER70:
			if(stateTimer < GetTime())
			{
				MakeExplosion("day_6", "xpltrsd");
				stateTimer = GetTime() + 15;
				missionState = MS_WRECKER85;
			}
			break;

		case MS_WRECKER85:
			if(stateTimer < GetTime())
			{
				MakeExplosion("day_7", "xpltrsd");
				MakeExplosion("day_7a", "xpltrsd");
				stateTimer = GetTime() + 7;
				missionState = MS_WRECKER92;
			}
			break;

		case MS_WRECKER92:
			if(stateTimer < GetTime())
			{
				MakeExplosion("day_8", "xpltrsd");
				MakeExplosion("day_8a", "xpltrsd");
				stateTimer = GetTime() + 8;
				missionState = MS_WRECKER100;
			}
			break;

		case MS_WRECKER100:
			if(stateTimer < GetTime())
			{
				MakeExplosion("day_9", "xpltrsd");
				MakeExplosion("day_9a", "xpltrsd");
				stateTimer = GetTime() + 6;
				missionState = MS_WRECKER106;
			}
			break;

		case MS_WRECKER106:
			if(stateTimer < GetTime())
			{
				MakeExplosion("day_10", "xpltrsd");
				AudioMessage("ch08009.wav");
				missionState = MS_END;

				resetObjectives();
				SucceedMission(GetTime() + 10.0, "ch08win.des");
				// play avi...
			}
			break;
	}

	checkSpawns();

	olduser = user;
}

