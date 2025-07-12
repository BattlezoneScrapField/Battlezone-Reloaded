
#include "AiMission.h"
#include "ScriptUtils.h"
#include "AudioMessage.h"


class BlackDog02Mission : public AiMission {
	DECLARE_RTIME(BlackDog02Mission)
public:
	BlackDog02Mission();
	~BlackDog02Mission();

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

	void resetObjectives();

	// bools
	union {
		struct {
			bool
				// have we lost?
				lost, 
				recyclerRetreated,

				b_last;
		};
		bool b_array[2];
	};

	// floats
	union {
		struct {
			float
				stateTimer,  // timer to say when the next state starts
				recyclerHealth, // so I know when it's been hit..
				deadTimer,
				f_last;
		};
		float f_array[3];
	};

	// handles
	union {
		struct {
			BZHandle
				// the user
				user,

				// recycler handle
				recycler,

				// wave 1 handles
				wave1_scout1,
				wave1_scout2,
        wave1_tank1,

				// wave 2 handles
				wave2_scout1,
				wave2_scout2,
        wave2_scout3,
        wave2_scout4,

				// massive attack wave
				enemy_scout1,
				enemy_scout2,
				enemy_scout3,
				enemy_scout4,
				enemy_ltnk1,
				enemy_ltnk2,
				enemy_tank1,
				enemy_tank2,

				enemy_turret1,
				enemy_turret2,
				enemy_turret3,
				enemy_turret4,

				// nav alpha (what else could it be???)
				nav_alpha,

				// harrass wave
				harrass_scout1,
				harrass_ltnk1,

				// bomber attack on recycler
				bomber1_scripted,
				bomber2_scripted,

				h_last;
		};
		BZHandle h_array[26];
	};

	// integers
	union {
		struct {
			int32_t
				// the state of the mission
				missionState,

				// sound BZHandle
				soundhandle,

				i_last;
		};
		int32_t i_array[2];
	};
};


#define MS_STARTUP						0
#define MS_FIRSTWAVE					1
#define MS_WAITFORSOUND1			2
#define MS_WAITFORWAVE1				3
#define MS_PLAYDECLOCK				4
#define MS_WAITINGOBJ2				5
#define MS_WAVE1DEAD					6
#define MS_WAITFORWAVE2				7
#define MS_WAVE2DEAD					8
#define MS_PLAYSOUND4					9
#define MS_WAITFORSOUND4			10
#define MS_WAITFORSOUND5			11
#define MS_HARRASDEAD					13
#define MS_WAITFORBOMBERRUN		14
#define MS_BOMBERRUN					15
#define MS_RECYCLERDIE				16
#define MS_ENDWAIT						17
#define MS_END								18


IMPLEMENT_RTIME(BlackDog02Mission)

BlackDog02Mission::BlackDog02Mission()
{
}

BlackDog02Mission::~BlackDog02Mission()
{
}

bool BlackDog02Mission::Load(file fp)
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

bool BlackDog02Mission::PostLoad(void)
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

bool BlackDog02Mission::Save(file fp)
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

void BlackDog02Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

void BlackDog02Mission::AddObject(BZHandle h)
{
/*
	if (missionState == MS_WAITFORFACTORY && IsOdf(h, "bvmuf"))
	{
		// set to first wave and setup the timer till it kicks off
		missionState = MS_WAITFORWAVE1;
		stateTimer = GetTime() + (60 + 5); // 30 seconds to build factory??
//		stateTimer = GetTime() + (5); // 30 seconds to build factory??
		resetObjectives();
	}
*/
}

void BlackDog02Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

void BlackDog02Mission::resetObjectives()
{
	ClearObjectives();

	if(missionState < MS_HARRASDEAD) //13
	{
		if(missionState >= MS_WAVE1DEAD) //6
		{
			AddObjective("bd02001.otf", GREEN);
		}
		else
		{
			AddObjective("bd02001.otf", WHITE);
		}	

		if(missionState >= MS_WAITFORSOUND4) //10
		{
			AddObjective("bd02002.otf", GREEN);
		}
		else if(missionState >= MS_WAVE1DEAD) //6
		{
			AddObjective("bd02002.otf", WHITE);
		}
	}

	if(missionState >= MS_END) //18
	{
		AddObjective("bd02003.otf", RED);
	}
	else if(missionState >= MS_HARRASDEAD) //13
	{
		AddObjective("bd02003.otf", WHITE);
	}
}

void BlackDog02Mission::Setup()
{
	int i = 0;
	lost = BZFALSE;
	recycler = GetHandle("recycler");
	enemy_turret1 = GetHandle("enemy_turret1");
	enemy_turret2 = GetHandle("enemy_turret2");
	enemy_turret3 = GetHandle("enemy_turret3");
	enemy_turret4 = GetHandle("enemy_turret4");
	missionState = MS_STARTUP;
}

void BlackDog02Mission::Execute()
{
	user = GetPlayerHandle(); //assigns the player a handle every frame

	if(missionState < MS_RECYCLERDIE) //16
	{
		if(!lost && !IsAlive(user))
		{
			if(deadTimer)
			{
				if(deadTimer < GetTime())
				{
					FailMission(GetTime() + 2.0f, "bd02lose.des");
					lost = BZTRUE;
					return;
				}
			}
			else
			{
				deadTimer = GetTime() + 2;
			}
		}
		else if(lost)
		{
			return;
		}
		else
		{
			deadTimer = 0;
		}
	}

	if(missionState < MS_RECYCLERDIE) //16
	{
		if(!IsAlive(recycler))
		{
			FailMission(GetTime() + 2.0f, "bd02lsea.des");
			lost = BZTRUE;
		}
	}

	float bomberdist1;
	float bomberdist2;

	switch(missionState)
	{
		case MS_STARTUP: //0
		{
			SetScrap(1, 30);
			SetPilot(1, 10);

			// setup the cloaked turrets
			SetCloaked(enemy_turret1);
			SetCloaked(enemy_turret2);
			SetCloaked(enemy_turret3);
			SetCloaked(enemy_turret4);


			// setup the initial objectives
			resetObjectives();
			missionState = MS_FIRSTWAVE;
			stateTimer = GetTime() + 2;
		}
		break;

		case MS_FIRSTWAVE: //1
		{
			if(stateTimer < GetTime())
			{
				soundhandle = AudioMessage("bd02001.wav");
				missionState = MS_WAITFORSOUND1;
				stateTimer = 0;
			}
			break;
		}

		case MS_WAITFORSOUND1: //2
		{
			if (IsAudioMessageDone(soundhandle))
			{
				missionState = MS_WAITFORWAVE1;
				stateTimer = GetTime() + 20;
			}
			break;
		}

		case MS_WAITFORWAVE1: //3
		{
			if(stateTimer < GetTime())
			{
				wave1_scout1 = BuildObject("cvfigh", 2, "spawn_wave1_scout1");
				wave1_scout2 = BuildObject("cvfigh", 2, "spawn_wave1_scout2");

				AudioMessage("bd02002.wav");

				CameraReady();
	
				missionState = MS_PLAYDECLOCK;

				Goto(wave1_scout1, "wave1_scout1_attackpath");
				Goto(wave1_scout2, "wave1_scout2_attackpath");
			}
			else
			{
				break;
			}
		}

		case MS_PLAYDECLOCK: //4
		{
			BZBOOLEAN arrived = CameraPath("camera_decloak", 2000, 1000, wave1_scout1);

			if(arrived || CameraCancelled())
			{
				CameraFinish();
				missionState = MS_WAITINGOBJ2;
				stateTimer = GetTime() + 5;
			}
			break;
		}

		case MS_WAITINGOBJ2: //5
			if(stateTimer < GetTime())
			{
				missionState = MS_WAVE1DEAD;
				AudioMessage("bd02003.wav");
				resetObjectives();
			}
			break;

		case 	MS_WAVE1DEAD: //6
			if(!IsAlive(wave1_scout1) && !IsAlive(wave1_scout2) && !IsAlive(wave1_tank1))
			{
				missionState = MS_WAITFORWAVE2;
				stateTimer = GetTime() + 20;
			}
			break;

		case MS_WAITFORWAVE2: //7
			if(stateTimer < GetTime())
			{
				missionState = MS_WAVE2DEAD;
				wave2_scout1 = BuildObject("cvfigh", 2, "spawn_wave2_scout1");
				wave2_scout2 = BuildObject("cvfigh", 2, "spawn_wave2_scout2");

				Goto(wave2_scout1, "wave2_scout1_attackpath");
				Goto(wave2_scout2, "wave2_scout2_attackpath");
			}
			break;

		case MS_WAVE2DEAD: //8
			if(!IsAlive(wave2_scout1) && !IsAlive(wave2_scout2) && !IsAlive(wave2_scout3) && !IsAlive(wave2_scout4))
			{
				missionState = MS_PLAYSOUND4;
				stateTimer = GetTime() + 10;
			}
			break;

		case MS_PLAYSOUND4: //9
			if(stateTimer < GetTime())
			{
				soundhandle = AudioMessage("bd02004.wav");
				missionState = MS_WAITFORSOUND4;
				resetObjectives();

				enemy_scout1 = BuildObject("cvfigh", 2, "spawn_enemy_scout1");
				enemy_scout2 = BuildObject("cvfigh", 2, "spawn_enemy_scout2");
				enemy_ltnk1 = BuildObject("cvltnk", 2, "spawn_enemy_ltnk");
				enemy_tank1 = BuildObject("cvtnk", 2, "spawn_enemy_tank");

				Goto(enemy_scout1, "spawn_nav_alpha");
				Goto(enemy_scout2, "spawn_nav_alpha");
				Goto(enemy_ltnk1, "spawn_nav_alpha");
				Goto(enemy_tank1, "spawn_nav_alpha");

				if(IsAlive(enemy_turret1))
				{
					Goto(enemy_turret1, "path_turret1");
				}

				if(IsAlive(enemy_turret2))
				{
					Goto(enemy_turret2, "path_turret2");
				}

				if(IsAlive(enemy_turret3))
				{
					Goto(enemy_turret3, "path_turret3");
				}

				if(IsAlive(enemy_turret4))
				{
					Goto(enemy_turret4, "path_turret4");
				}

				CameraReady();
			}
			else
			{
				break;
			}

		case MS_WAITFORSOUND4: //10
			CameraPath("camera_massive_attack", 2000, 10, enemy_tank1);

			if (IsAudioMessageDone(soundhandle))
			{
				soundhandle = AudioMessage("bd02005.wav");
				missionState = MS_WAITFORSOUND5;
			}
			break;

		case MS_WAITFORSOUND5: //11
			CameraPath("camera_massive_attack", 2000, 10, enemy_tank1);

			if (IsAudioMessageDone(soundhandle))
			{
				CameraFinish();

				RemoveObject(enemy_scout1);
				RemoveObject(enemy_scout2);
				RemoveObject(enemy_scout3);
				RemoveObject(enemy_scout4);
				RemoveObject(enemy_ltnk1);
				RemoveObject(enemy_ltnk2);
				RemoveObject(enemy_tank1);
				RemoveObject(enemy_tank2);
				
				nav_alpha = BuildObject("apcamr", 1, "spawn_nav_alpha");
				SetName(nav_alpha, "Nav Alpha");

				missionState = MS_HARRASDEAD;
				stateTimer = GetTime() + 4;
				
				resetObjectives();

				Goto(recycler, "path_recycler_retreat");
				recyclerRetreated = BZFALSE;

				harrass_scout1 = BuildObject("cvfigh", 2, "spawn_scout1_harrass");
				harrass_ltnk1 = BuildObject("cvltnk", 2, "spawn_ltnk1_harrass");

				Goto(harrass_scout1, user);
				Goto(harrass_ltnk1, user);
			}
			break;

		case MS_HARRASDEAD: //13

			if(!recyclerRetreated && GetDistance(recycler, "trigger_1") < 100)
			{
				int i;
				BZHandle temp;

				for(i = 0; i < 2; i++)
				{
					temp = BuildObject("cvfigh", 2, "fighter_1");
					Attack(temp, user);
				}

				recyclerRetreated = BZTRUE;
			}

			if(GetCurrentCommand(recycler) == CMD_NONE)
			{
				if (IsAlive(recycler)) //BHD-1962
				{
					Stop(recycler);
					soundhandle = AudioMessage("bd02006.wav"); //thrusters damaged

					missionState = MS_WAITFORBOMBERRUN;
				}
			}
			break;

		case MS_WAITFORBOMBERRUN: //14
			if(IsAudioMessageDone(soundhandle))
			{
				RemoveObject(harrass_scout1);
				RemoveObject(harrass_ltnk1);
				RemoveObject(enemy_turret1);
				RemoveObject(enemy_turret2);
				RemoveObject(enemy_turret3);
				RemoveObject(enemy_turret4);

				AudioMessage("bd02007.wav"); //bomber coming from the east, get out of there
				
				bomber1_scripted	= BuildObject("cvhraz", 2, "spawn_bomber_1");
				Attack(bomber1_scripted, recycler);

				bomber2_scripted	= BuildObject("cvhraz", 2, "spawn_bomber_2");
				Attack(bomber2_scripted, recycler);

				recyclerHealth = GetHealth(recycler);
				soundhandle = 0;

				stateTimer = GetTime() + 10;

				missionState = MS_BOMBERRUN;
			}
			break;

		case MS_BOMBERRUN: //15
			if(bomber1_scripted)
			{
				GameObject *o = GameObjectHandle::GetObj(bomber1_scripted);

				if(o && (o->GetCurHealth() != o->GetMaxHealth()))
				{
					o->AddHealth(o->GetMaxHealth() - o->GetCurHealth());
				}
			}

			if(bomber2_scripted)
			{
				GameObject *o = GameObjectHandle::GetObj(bomber2_scripted);

				if(o && (o->GetCurHealth() != o->GetMaxHealth()))
				{
					o->AddHealth(o->GetMaxHealth() - o->GetCurHealth());
				}
			}

			if(recyclerHealth > GetHealth(recycler)) //BHD-2085
			{
				GameObject *o = GameObjectHandle::GetObj(recycler);
				if (o) o->SetCurHealth(recyclerHealth);
			}

			bomberdist1=(GetDistance(bomber1_scripted, "camera_bomber_chasecam"));
			bomberdist2=(GetDistance(bomber2_scripted, "camera_bomber_chasecam"));

			if ((bomberdist1 <= 60) || (bomberdist2 <= 60) || (stateTimer < GetTime())) //BHD-2085
			{
				CameraReady();
				stateTimer = 0;
				missionState = MS_RECYCLERDIE;
			}
			break;

		case MS_RECYCLERDIE: //16
		{
			if(bomber1_scripted)
			{
				GameObject *o = GameObjectHandle::GetObj(bomber1_scripted);

				if(o && (o->GetCurHealth() != o->GetMaxHealth()))
				{
					o->AddHealth(o->GetMaxHealth() - o->GetCurHealth());
				}

				if (o && (o->GetCurAmmo() != o->GetMaxAmmo()))
				{
					o->AddAmmo(o->GetMaxAmmo() - o->GetCurAmmo());
				}
			}

			if(bomber2_scripted)
			{
				GameObject *o = GameObjectHandle::GetObj(bomber2_scripted);

				if(o && (o->GetCurHealth() != o->GetMaxHealth()))
				{
					o->AddHealth(o->GetMaxHealth() - o->GetCurHealth());
				}

				if (o && (o->GetCurAmmo() != o->GetMaxAmmo()))
				{
					o->AddAmmo(o->GetMaxAmmo() - o->GetCurAmmo());
				}
			}

			CameraPath("camera_bomber_chasecam", 1000, 0, recycler);

			if(recyclerHealth && recyclerHealth != GetHealth(recycler)) // it's been hit...
			{
				recyclerHealth = 0;
				stateTimer = GetTime() + 10;
				AudioMessage("bd02008.wav");
			}

			if (stateTimer != 0 && (stateTimer < GetTime()))
			{
				GameObject *o = GameObjectHandle::GetObj(recycler);
				if (o)
					o->SetCurHealth(o->GetMaxHealth() * 0.05f);
				stateTimer = 0;
			}

			if(!soundhandle && !IsAlive(recycler))
			{
				stateTimer = 0;
				soundhandle = AudioMessage("bd02009.wav");
			}

			if (soundhandle && IsAudioMessageDone(soundhandle))
			{
				missionState = MS_ENDWAIT;
				stateTimer = GetTime() + 3;
				resetObjectives();
			}
			break;
		}

		case MS_ENDWAIT: //17
			CameraPath("camera_bomber_chasecam", 1000, 0, recycler);

			if(stateTimer < GetTime())
			{
				missionState = MS_END;
				CameraFinish();
				SucceedMission(GetTime() + 5.0f, "bd02win.des");
			}
			break;
	}
}

const std::set<PrjID>& BlackDog02Mission::GetPreloadGameObjects()
{
	static std::set<PrjID> retval = AiMission::PrjIDFromStrings(
	{ "apcamr", "cvfigh", "cvhraz", "cvltnk", "cvtnk" }
	);
	return retval;
}
