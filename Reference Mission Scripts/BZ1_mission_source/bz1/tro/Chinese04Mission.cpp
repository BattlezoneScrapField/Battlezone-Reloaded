#include "GameCommon.h"
#include "AiCommon.h"
#include "AiMission.h"
#include "AiProcess.h"
#include "PowerUp.h"
#include "ScriptUtils.h"


/*
	Chinese04Mission
*/

class Chinese04Mission : public AiMission {
	DECLARE_RTIME(Chinese04Mission)
public:
	Chinese04Mission();
	~Chinese04Mission();

	virtual bool Load(file fp);
	virtual bool PostLoad(void);
	virtual bool Save(file fp);

	void resetObjectives();

	virtual void Update(void);

	virtual void AddObject(GameObject *gameObj);
	void UnitsAttackPlayer();

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
				target_silo_inspected,
				endNear,
				insideCloakedShip,
				
				b_last;
		};
		bool b_array[4];
	};

	// floats
	union {
		struct {
			float
				stateTimer,  // timer to say when the next state starts
				portalTimeOut,

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

				target_silo,
				navPoints[6],
				portal,

				cca_factory,
				factory,

				attackuser1[25],
				attackuser2[4],
				attackuser3[4],
				attackuser4[4],
				attackuser5[4],
				attackuser6[6],

				fakePlayer,

				empty[25],
				turret[4],

				// place holder
				h_last;
		};
		Handle h_array[89];
	};

	// integers
	union {
		struct {
			int
				missionState,
				uptonavpoint,
				attackedAlready,

				soundHandle,

				coreFailSound,

				i_last;
		};
		int i_array[5];
	};
};

IMPLEMENT_RTIME(Chinese04Mission)

Chinese04Mission::Chinese04Mission()
{
}

Chinese04Mission::~Chinese04Mission()
{
}

bool Chinese04Mission::Load(file fp)
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

bool Chinese04Mission::PostLoad(void)
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

bool Chinese04Mission::Save(file fp)
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

void Chinese04Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

void Chinese04Mission::AddObject(Handle h)
{
}

void Chinese04Mission::Update(void)
{
	AiMission::Update();
	Execute();
}


#define MS_STARTUP				1
#define MS_STARTSCENE			2
#define MS_PLAYSOUND7			3
#define MS_NEARNAVS				4
#define MS_WAITFORID			6
#define WS_WAITFORSOUND2	7
#define MS_WAITFORALARM		8
#define MS_CAMERAALARM		9
#define MS_NEARSILO				10
#define MS_INSPECTSILO		11
#define MS_WAITFORSOUND2	12
#define MS_WAITFORSOUND3	13
#define MS_WAITFORSOUND8	14
#define MS_WAITFORPORTAL	15
#define MS_CAMERAEND			16
#define MS_END					  100



void Chinese04Mission::resetObjectives()
{
	ClearObjectives();

	if(missionState >= MS_WAITFORID)
	{
		AddObjective("ch04001.otf", GREEN);
	}
	else if(missionState >= MS_NEARNAVS)
	{
		AddObjective("ch04001.otf", WHITE);
	}

	if(target_silo_inspected)
	{
		AddObjective("ch04002.otf", GREEN);
	}
	else if(missionState >= MS_WAITFORID)
	{
		AddObjective("ch04002.otf", WHITE);
	}

	if(missionState >= MS_WAITFORSOUND2)
	{
		AddObjective("ch04003.otf", WHITE);
	}
}


void Chinese04Mission::UnitsAttackPlayer()
{
	int i;

	if(user == olduser)
	{
		return;
	}

	for(i = 0; i < 25; i++)
	{
		if(IsAlive(attackuser1[i]))
		{
			Attack(attackuser1[i], user);
		}
	}

	for(i = 0; i < 4; i++)
	{
		if(IsAlive(attackuser2[i]))
		{
			Attack(attackuser2[i], user);
		}
	}

	if(missionState >= MS_WAITFORSOUND3)
	{
		for(i = 0; i < 4; i++)
		{
			if(IsAlive(attackuser3[i]))
			{
				Attack(attackuser3[i], user);
			}

			if(IsAlive(attackuser4[i]))
			{
				Attack(attackuser4[i], user);
			}

			if(IsAlive(attackuser5[i]))
			{
				Attack(attackuser5[i], user);
			}
		}

		for(i = 0; i < 6; i++)
		{
			if(IsAlive(attackuser6[i]))
			{
				Attack(attackuser6[i], user);
			}
		}
	}
}


void Chinese04Mission::Setup()
{
	target_silo = GetHandle("target_silo");
	navPoints[0] = GetHandle("nav_1");
	cca_factory = GetHandle("cca_factory");
	factory = GetHandle("factory");
	portal = GetHandle("portal");

	for (int i = 0; i < 25; i++)
	{
		char buf[32] = "";
		sprintf(buf, "empty_%i", i + 1);
		empty[i] = GetHandle(buf);
	}

	for (i = 0; i < 4; i++)
	{
		char buf[32] = "";
		sprintf(buf, "turret_%i", i + 1);
		turret[i] = GetHandle(buf);
	}

	target_silo_inspected = FALSE;
	insideCloakedShip = TRUE;
	missionState = MS_STARTUP;
	attackedAlready = 0;
	coreFailSound = 0;
}

void Chinese04Mission::Execute()
{
	int i = 0;
//	Handle temp;
	Distance dist;
//	GameObject *o, *o2;
	GameObject *o;

	user = GetPlayerHandle(); //assigns the player a handle every frame

	o = GameObjectHandle::GetObj(factory);

	if(o->GetCurHealth() != o->GetMaxHealth())
	{
		o->AddHealth(o->GetMaxHealth() - o->GetCurHealth());
	}

	o = GameObjectHandle::GetObj(portal);

	if(o->GetCurHealth() != o->GetMaxHealth())
	{
		o->AddHealth(o->GetMaxHealth() - o->GetCurHealth());
	}

	if(missionState == MS_CAMERAEND)
	{
		o = GameObjectHandle::GetObj(user);

		if(o->GetCurHealth() != o->GetMaxHealth())
		{
			o->AddHealth(o->GetMaxHealth() - o->GetCurHealth());
		}
	}

	if(attackedAlready && missionState <= MS_WAITFORPORTAL)
	{
		UnitsAttackPlayer();
	}

	if(missionState != MS_STARTUP && user != olduser)
	{
		if(insideCloakedShip)
		{
			Decloak(olduser);
			enableCloaking(olduser, FALSE);
		}

		insideCloakedShip = FALSE;
	}


	switch(missionState)
	{
		case MS_STARTUP:
		{
			SetScrap(1,0);
			SetPilot(1,10);
			olduser = user;

			missionState = MS_STARTSCENE;
			
			soundHandle = AudioMessage("ch04001.wav");
			CameraReady();
		}

		case MS_STARTSCENE:
		{
			BOOL arrived = CameraPath("camera_start", 1000, 1200, target_silo);

			if(arrived || CameraCancelled())
			{
				StopAudioMessage(soundHandle);
				CameraFinish();
				missionState = MS_PLAYSOUND7;
				stateTimer = GetTime() + 5;
			}
			break;
		}

		case MS_PLAYSOUND7:
		{
			if(stateTimer < GetTime())
			{
				AudioMessage("ch04007.wav");
				StartCockpitTimer(2 * 60 + 10);
				missionState = MS_NEARNAVS;
				uptonavpoint = 0;
				resetObjectives();
				SetUserTarget(navPoints[0]);
			}
			break;
		}

		case MS_NEARNAVS:
		{
			if(GetCockpitTimer() < 1)
			{
				AudioMessage("ch04006.wav");
				FailMission(GetTime() + 2.0f, "ch04lsea.des");
				missionState = MS_END;
				break;
			}

			if(GetDistance(user, navPoints[uptonavpoint]) < 50)
			{
				char navlabel[10];

				if(uptonavpoint >= 5)
				{
					for(i = 0; i <= uptonavpoint; i++)
					{
						RemoveObject(navPoints[i]);
					}


					HideCockpitTimer();
					missionState = MS_WAITFORID;
					resetObjectives();
//					SetUserTarget(target_silo);
					SetPerceivedTeam(user, 2);

//					navPoints[0] = BuildObject("apcamr", 1, "nav_silo");
//					SetName(navPoints[0], "Silo");
//					SetUserTarget(navPoints[0]);

					SetObjectiveOn(target_silo);
				}
				else
				{
					uptonavpoint++;

					sprintf(navlabel, "nav_%d", uptonavpoint + 1);
					navPoints[uptonavpoint] = BuildObject("apcamr", 1, navlabel);

					if(uptonavpoint == 5)
					{
						SetName(navPoints[uptonavpoint], "Pit Entrance");
					}

					SetUserTarget(navPoints[uptonavpoint]);
				}
			}
			break;
		}

		case MS_WAITFORID:
		{
			target_silo_inspected = IsInfo(target_silo);
			dist = GetDistance(user, "trigger_1");

//			if(dist <= 70 || ((!insideCloakedShip || !isCloaked(user)) && dist <= 400) || target_silo_inspected)
			if(dist <= 70 || target_silo_inspected)
			{
				soundHandle = 0;
/*
				if(insideCloakedShip)
				{
					if(isCloaked(user))
					{
						soundHandle = AudioMessage("ch04002.wav");
						Decloak(user);
					}
					enableCloaking(user, FALSE);
				}
*/
				missionState = WS_WAITFORSOUND2;
			}
			break;
		}

		case WS_WAITFORSOUND2:
		{
			if(soundHandle == 0 || IsAudioMessageDone(soundHandle))
			{
//				soundHandle = AudioMessage("ch04003.wav");
				stateTimer = GetTime() + 1;
				missionState = MS_WAITFORALARM;
			}
			break;
		}

		case MS_WAITFORALARM:
		{
			if(stateTimer < GetTime())
			{
				Retreat(BuildObject("sspilo", 2, "pilot_1"), empty[0]);
				Retreat(BuildObject("sspilo", 2, "pilot_2"), empty[1]);
				Retreat(BuildObject("sspilo", 2, "pilot_3"), empty[2]);
				Retreat(BuildObject("sspilo", 2, "pilot_4"), empty[3]);
				Retreat(BuildObject("sspilo", 2, "pilot_5"), empty[4]);
				Retreat(BuildObject("sspilo", 2, "pilot_6"), empty[5]);
				Retreat(BuildObject("sspilo", 2, "pilot_11"), empty[10]);
				Retreat(BuildObject("sspilo", 2, "pilot_14"), empty[13]);
				Retreat(BuildObject("sspilo", 2, "pilot_17"), empty[16]);
				Retreat(BuildObject("sspilo", 2, "pilot_25"), empty[24]);

				missionState = MS_CAMERAALARM;
				stateTimer = GetTime() + 5;
				CameraReady();
			}
			else
			{
				break;
			}
		}

		case MS_CAMERAALARM:
		{
			CameraPath("camera_alarm", 2000, 0, cca_factory);
/*
			if(soundHandle && IsAudioMessageDone(soundHandle))
			{
				soundHandle = 0;
				AudioMessage("ch04003.wav");
			}
*/
			if(CameraCancelled() || stateTimer < GetTime())
			{
				CameraFinish();

				Retreat(BuildObject("sspilo", 2, "pilot_7"), empty[6]);
				Retreat(BuildObject("sspilo", 2, "pilot_8"), empty[7]);
				Retreat(BuildObject("sspilo", 2, "pilot_9"), empty[8]);
				Retreat(BuildObject("sspilo", 2, "pilot_10"), empty[9]);
				Retreat(BuildObject("sspilo", 2, "pilot_12"), empty[11]);
				Retreat(BuildObject("sspilo", 2, "pilot_13"), empty[12]);
/*
				temp = GetHandle("empty_15");
				Retreat(BuildObject("sspilo", 2, temp), temp);
				temp = GetHandle("empty_16");
				Retreat(BuildObject("sspilo", 2, temp), temp);
				temp = GetHandle("empty_18");
				Retreat(BuildObject("sspilo", 2, temp), temp);
				temp = GetHandle("empty_19");
				Retreat(BuildObject("sspilo", 2, temp), temp);
				temp = GetHandle("empty_20");
				Retreat(BuildObject("sspilo", 2, temp), temp);
				temp = GetHandle("empty_21");
				Retreat(BuildObject("sspilo", 2, temp), temp);
				temp = GetHandle("empty_22");
				Retreat(BuildObject("sspilo", 2, temp), temp);
				temp = GetHandle("empty_23");
				Retreat(BuildObject("sspilo", 2, temp), temp);
				temp = GetHandle("empty_24");
				Retreat(BuildObject("sspilo", 2, temp), temp);
*/

				if(!isCloaked(user))
				{
					attackedAlready = 1;
					SetPerceivedTeam(user, 1);

					for(i = 0; i < 25; i++)
					{
						attackuser1[i] = empty[i];
						Attack(attackuser1[i], user);
					}

					for(i = 0; i < 4; i++)
					{
						attackuser2[i] = turret[i];
						Attack(attackuser2[i], user);
					}
				}
				else
				{
					attackedAlready = 0;
				}

				missionState = MS_NEARSILO;
			}
			break;
		}

		case MS_NEARSILO:
/*
			if(soundHandle && IsAudioMessageDone(soundHandle))
			{
				soundHandle = 0;
				AudioMessage("ch04003.wav");
			}
*/
			if(attackedAlready)
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
					enableCloaking(user, FALSE);
				}
			}

			if(GetDistance(user, target_silo) <= 200)
			{
				Goto(BuildObject("svfigh", 2, "fighter_1"), "figh1_path");
				Goto(BuildObject("svfigh", 2, "fighter_2"), "figh2_path");
				missionState = MS_INSPECTSILO;
			}
			break;

		case MS_INSPECTSILO:
			if(attackedAlready)
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
					enableCloaking(user, FALSE);
				}
			}

			if(!target_silo_inspected)
			{
				target_silo_inspected = IsInfo(target_silo);
			}

			if(target_silo_inspected)
			{
				soundHandle = 0;

				SetObjectiveOff(target_silo);

				missionState = MS_WAITFORSOUND2;
				
				stateTimer = GetTime() + 45;

				resetObjectives();

				if(!attackedAlready)
				{
					if(isCloaked(user))
					{
						soundHandle = AudioMessage("ch04002.wav");
						Decloak(user);
					}
					enableCloaking(user, FALSE);

					attackedAlready = 1;
					SetPerceivedTeam(user, 1);

					for(i = 0; i < 25; i++)
					{
						attackuser1[i] = empty[i];
						Attack(attackuser1[i], user);
					}

					for(i = 0; i < 4; i++)
					{
						attackuser2[i] = turret[i];
						Attack(attackuser2[i], user);
					}
				}
			}
			break;

		case MS_WAITFORSOUND2:
			if(soundHandle == 0 || IsAudioMessageDone(soundHandle))
			{
				soundHandle = AudioMessage("ch04003.wav");

				for(i = 0; i < 4; i++)
				{
					attackuser3[i] = BuildObject("svfigha", 2, "chase_1");
					Attack(attackuser3[i], user);
					attackuser4[i] = BuildObject("svtanka", 2, "chase_2");
					Attack(attackuser4[i], user);
					attackuser5[i] = BuildObject("svfigha", 2, "chase_3");
					Attack(attackuser5[i], user);
				}

				attackuser6[0] = BuildObject("svfigh", 2, "portal_units");
				attackuser6[1] = BuildObject("svfigh", 2, "portal_units");
				attackuser6[2] = BuildObject("svfigh", 2, "portal_units");
				attackuser6[3] = BuildObject("svfigh", 2, "portal_units");
				attackuser6[4] = BuildObject("svfigh", 2, "portal_units");
				attackuser6[5] = BuildObject("svfigh", 2, "portal_units");

				activatePortal(portal, TRUE);

				missionState = MS_WAITFORSOUND3;
			}
			break;

		case MS_WAITFORSOUND3:
			if(IsAudioMessageDone(soundHandle))
			{
				soundHandle = AudioMessage("ch04008.wav");

				missionState = MS_WAITFORSOUND8;
			}
			break;

		case MS_WAITFORSOUND8:
			if(IsAudioMessageDone(soundHandle))
			{
				portalTimeOut = GetTime() + (60 * 2) + 15;

//				RemoveObject(navPoints[0]);
				navPoints[0] = BuildObject("apcamr", 1, "nav_base");
				SetUserTarget(navPoints[0]);
				missionState = MS_WAITFORPORTAL;
			}
			break;


 			

		case MS_WAITFORPORTAL:
			if(portalTimeOut < GetTime())
			{
				FailMission(GetTime() + 2.0f, "ch04lseb.des");
				missionState = MS_END;
				break;
			}

			if(GetDistance(user, portal) < 100)
			{
				RemoveObject(navPoints[0]);
				HideCockpitTimer();

				GameObject *gameObj = GameObjectHandle::GetObj(user);

//				fakePlayer = BuildObject((char *)&gameObj->GetClass()->cfg, 1, user);

				SetPerceivedTeam(user, 2);

				o = GameObjectHandle::GetObj(user);
//				o2 = GameObjectHandle::GetObj(fakePlayer);

				if(o->GetCurHealth() != o->GetMaxHealth())
				{
//					o2->AddHealth(o->GetCurHealth() - o2->GetCurHealth() );
					o->AddHealth(o->GetMaxHealth() - o->GetCurHealth());
				}
				
//				Goto(fakePlayer, "auto_end");

				Hide(user);
				missionState = MS_CAMERAEND;
				CameraReady();

				endNear = FALSE;
				stateTimer = 0;
			}
			break;

		case MS_CAMERAEND:
		{
			BOOL arrived;
			
			if(!endNear)
			{
				arrived = CameraPathDir("auto_end", 500, 3000);
			}
			else
			{
				CameraPathDir("auto_end", 500, 0);
			}

//			if(!endNear && GetCurrentCommand(fakePlayer) == CMD_NONE)
			if(!endNear && arrived)
			{
				endNear = TRUE;
				stateTimer = GetTime() + 2;
			}

			if(endNear)
			{
				if(stateTimer < GetTime())
				{
					deactivatePortal(portal);
					missionState = MS_END;
					SucceedMission(GetTime() + 4, "ch04win.des");
				}
			}
			break;
		}
	}

	if(user != olduser)
	{
		olduser = user;
	}
}
