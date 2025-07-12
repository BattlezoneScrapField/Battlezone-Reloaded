

#include "AiMission.h"
#include "Recycler.h"
#include "ScriptUtils.h"
#include "srandom.h"
#include "AudioMessage.h"

/*
	BlackDog06Mission
*/


class BlackDog06Mission : public AiMission {
	DECLARE_RTIME(BlackDog06Mission)
public:
	BlackDog06Mission();
	~BlackDog06Mission();

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

				// portal ours?
				portalours,

				// recycler dropped off
				recyclerDropped,

				randomAttack,

				b_last;
		};
		bool b_array[4];
	};

	// floats
	union {
		struct {
			float
				stateTimer,  // timer to say when the next state starts
				stateTimer2,
				stateTimer3,
				stateTimer4,
				f_last;
		};
		float f_array[4];
	};

	// handles
	union {
		struct {
			BZHandle
				// the user
				user,

				// user recycler
				recycler,

				// portal
				portal,

				// your support 
				bdtank[10],

				// silo attack run handles
				silo_attack[10],

				// 2bdest units
				h2bdest[6],

				// portal attackers
				portalattack[2],

				// random attackers
				randomattack[5],

				badguy[3],

				apchandle,

				h_last;
		};
		BZHandle h_array[40];
	};

	// integers
	union {
		struct {
			int32_t
				// the state of the mission
				missionState,

				// sound BZHandle
				soundhandle,

				// number of fighters attacking tho the portal (2-5)
//				portalAttackNum,

				// portal attack stage
//				portalAttackStage,

				i_last;
		};
		int32_t i_array[2];
	};
};


#define MS_STARTUP							0
#define MS_STARTCAMERA					1
#define MS_WAITING1							2
#define MS_WAITFORSOUND2				3
#define MS_WAITING2							4
#define MS_FAKEATTACKCAMERA			5
#define MS_WAITFORALL2BDESTDEAD	6
#define MS_WAITFORREDDEVIL			7
#define MS_WAITFORBADGUY				8
#define MS_WAITFORBADGUY1DIE		9
#define MS_WAITFORBADGUY2				10
#define MS_WAITFORBADGUY2DIE		11
#define MS_WAITFORSOUND3				12
#define MS_WAITFOROBJECTIVE2		13
#define MS_WAITFORRECYCLER			14
#define MS_WAITFORBADGUY3				15
#define MS_WAITFORAPC						16
#define MS_ENDCUTSCENE					17
#define MS_WAITING3							18
#define MS_WAITAPCFINISHED			19
#define MS_WAITAPCOUT						20
#define MS_WAITFORSOUND8				21
#define MS_WAITING4							22
#define MS_RECYCLERDEAD					23
#define MS_ATTACKTOEARLY				24



IMPLEMENT_RTIME(BlackDog06Mission)

BlackDog06Mission::BlackDog06Mission()
{
}

BlackDog06Mission::~BlackDog06Mission()
{
}

bool BlackDog06Mission::Load(file fp)
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

bool BlackDog06Mission::PostLoad(void)
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

bool BlackDog06Mission::Save(file fp)
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

void BlackDog06Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

void BlackDog06Mission::AddObject(BZHandle h)
{
}


void BlackDog06Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

void BlackDog06Mission::resetObjectives()
{
	ClearObjectives();

	if(missionState >= MS_WAITFORSOUND3)
	{
		AddObjective("bd06001.otf", GREEN);
	}
	else if(missionState >= MS_WAITING1)
	{
		AddObjective("bd06001.otf", WHITE);
	}	

	if(portalours)
	{
		AddObjective("bd06002.otf", GREEN);
	}
	else if(missionState >= MS_WAITFORRECYCLER)
	{
		AddObjective("bd06002.otf", WHITE);
	}
}

void BlackDog06Mission::Setup()
{
	int i = 0;
	lost = BZFALSE;
	portalours = BZFALSE;
	recycler = NULL;
	stateTimer4 = stateTimer3 = 0;

//	portalAttackStage = 0;
//	portalAttackNum = 0;
	randomAttack = BZTRUE;

	portal = GetHandle("portal");

	for(i = 0; i < 10; i++)
	{
		char name[15];

		sprintf(name, "silo_attack%d", i + 1);
		silo_attack[i] = GetHandle(name);

		sprintf(name, "bdtank_%d", i + 1);
		bdtank[i] = GetHandle(name);
	}

	h2bdest[0] = GetHandle("2bdest_1");
	h2bdest[1] = GetHandle("2bdest_2");
	h2bdest[2] = GetHandle("2bdest_3");
	h2bdest[3] = GetHandle("2bdest_7");
	h2bdest[4] = GetHandle("2bdest_9");
	h2bdest[5] = GetHandle("2bdest_10");

	missionState = MS_STARTUP;
}

void BlackDog06Mission::Execute()
{
	int i;
	int apclist = 0;
	BZHandle temp;
	PrjID cfg = StrToID("bvapc");
	float r;

	SetMaxHealth(portal, 0.0f);		//make portal indestructible as it is vulnerable to stray hits.


	user = GetPlayerHandle(); //assigns the player a handle every frame

	if(!lost)
	{
		if(!portalours && recycler)
		{
			// count number of APC's left..
			// KM 2016-11-13: use the craft list to avoid checking scrap and other irrelevant objects
			CraftList &list = Craft::craftList;

			for (CraftList::iterator i = list.begin(); i != list.end(); i++) 
			{
				// KM 2016-11-13: make sure the APC is commandable
				// (player-controlled, destroyed, or empty APCs don't qualify)
				Craft *o = *i;
				if(o->GetClass()->cfg == cfg && o->CanCommand())
				{
					BZHandle apc = o->GetHandle();
					if(GetDistance(apc, "apc_in") < 100)
					{
						AddHealth(apc,10000);  //PREVENT APC BEING KILLED DURING CUTSCENE
						Goto(apc, "apc_in");
						SetCritical(apc);


						apchandle = apc;
						portalours = BZTRUE;
						soundhandle = NULL;
						
						resetObjectives();

						temp = BuildObject("cvartl", 2, "portal_attack_1");
						Attack(temp, portal);
						temp = BuildObject("cvartl", 2, "portal_attack_1");
						Attack(temp, portal);
						temp = BuildObject("cvartl", 2, "portal_attack_1");
						Attack(temp, portal);

						missionState = MS_ENDCUTSCENE;
						stateTimer = 0;
						CameraReady();
						break;
					}
					else
					{
							if(GetDistance(apc, "apc_in") < 200)  //prevent APC being killed immediatley prior to cutcscene
							{
									AddHealth(apc,10000);
							}
					}

					apclist++;
				}
			}

			if(!portalours && apclist == 0 && !IsAlive(recycler))
			{

				missionState = MS_RECYCLERDEAD;
				soundhandle = AudioMessage("bd06006.wav");
			}
		}

		if(!IsAlive(portal))
		{
			FailMission(GetTime() + 2.0f, "bd06lseb.des");
			lost = BZTRUE;
		}
	}
	else if(lost)
	{
		return;
	}

	if(stateTimer4 && stateTimer4 < GetTime())
	{
		// spawn and attack player...
		for(i = 0; i < 2; i++)
		{
			float diff = GetTime() - stateTimer4;
			if (diff < 1.0f)
			{
				portalOut(portal, 1.0f - diff);
			}
			else if (!IsValid(portalattack[i]))
			{
				portalOut(portal, diff - 1.0f);

				r = Random();

				if(r < 0.33)
				{
					portalattack[i] = BuildObjectAtPortal("cvfigh", 2, portal);
				}
				else if(r < 0.66)
				{
					portalattack[i] = BuildObjectAtPortal("cvtnk", 2, portal);
				}
				else
				{
					portalattack[i] = BuildObjectAtPortal("cvrckt", 2, portal);
				}

				Goto(portalattack[i], "camera_go");
			}
			else if (diff < 2.0f)
			{
				portalOut(portal, diff - 1.0f);
			}
			else
			{
				stateTimer4 = GetTime() + 80;
				portalattack[0] = portalattack[1] = NULL;
			}
		}
	}

	if(stateTimer3 && stateTimer3 < GetTime())
	{
		for(i = 0; i < 4; i++)
		{
			if (!IsValid(randomattack[i]))
			{
				r = Random();
				if (r < 0.5)
				{
					randomattack[i] = BuildObject("cvfigh", 2, "attack_always");
				}
				else
				{
					randomattack[i] = BuildObject("cvtnk", 2, "attack_always");
				}
				Hunt(randomattack[i]);
			}
		}
		stateTimer3 = GetTime() + 60 * 2;
	}
	

	switch(missionState)
	{
		case MS_STARTUP:
		{
			SetScrap(1,75);
			SetPilot(1,10);

			// setup the initial objectives
			resetObjectives();
			missionState = MS_STARTCAMERA;
			stateTimer = GetTime() + 2;
			soundhandle = 0;
			CameraReady();
		}
//		break;

		case MS_STARTCAMERA:
		{
			BZBOOLEAN arrived = CameraPath("camera_start", 1000, 2500, portal);

			if(arrived || CameraCancelled())
			{
				CameraFinish();
				missionState = MS_WAITING1;
				resetObjectives();
				stateTimer = GetTime() + 20;
//				resetObjectives();

				stateTimer2 = GetTime() + (11 * 60);
//				StartCockpitTimer(11 * 60);
			}

			if(stateTimer < GetTime())
			{
				if(!soundhandle)
				{
					soundhandle = AudioMessage("bd06001.wav");
				}
//				else if (IsAudioMessageDone(soundhandle))
//				{
//					missionState = MS_WAITING1;
//				}
			}
			break;
		}

		case MS_WAITING1:
		{
			if(stateTimer < GetTime())
			{
				soundhandle = AudioMessage("bd06002.wav");

				for(i = 0; i < 10; i++)
				{
					Goto(silo_attack[i], "fake_attack");
				}

				missionState = MS_WAITFORSOUND2;
			}
			else
			{
				GameObject *o;

				for(i = 0; i < 10; i++)
				{
/*
					if(i < 5)
					{
						o = GameObjectHandle::GetObj(bdtank[i]);

						if(o->GetCurHealth() != o->GetMaxHealth())
						{
							missionState = MS_ATTACKTOEARLY;
							soundhandle = AudioMessage("bd06007.wav");
						}
					}
*/
					
					o = GameObjectHandle::GetObj(silo_attack[i]);
					
					if(o->GetCurHealth() != o->GetMaxHealth())
					{
					missionState = MS_ATTACKTOEARLY;
					soundhandle = AudioMessage("bd06007.wav");
					}
					
				}
			}
			break;
		}

		case MS_WAITFORSOUND2:
			if(IsAudioMessageDone(soundhandle))
			{
				missionState = MS_WAITING2;
				stateTimer = GetTime() + 1;
			}
			break;

		case MS_WAITING2:
			if(stateTimer < GetTime())
			{
				missionState = MS_FAKEATTACKCAMERA;
				stateTimer = GetTime() + 10;
				CameraReady();
			}
			else
			{
				break;
			}

		case MS_FAKEATTACKCAMERA:
		{
			BZBOOLEAN arrived = CameraPath("camera_go", 2000, 2000, silo_attack[3]);

			if(arrived || CameraCancelled() || stateTimer < GetTime())
			{
				for(i = 0; i < 10; i++)
				{
					RemoveObject(silo_attack[i]);
				}

				CameraFinish();
				stateTimer2 = 10 * 60.0;
				missionState = MS_WAITFORALL2BDESTDEAD;
			}
			break;
		}

		case MS_WAITFORALL2BDESTDEAD:
		{
			// out of time?
//			if(GetCockpitTimer() < 1)
			if(stateTimer2 < GetTime())
			{
				FailMission(GetTime() + 2.0f, "bd06lsed.des");
				lost = BZTRUE;
				break;
			}
			else if (!cockpitTimer.IsVisible())
			{
				cockpitTimer.SetTimerDown(long(stateTimer2 - GetTime()));
				cockpitTimer.ShowTimer();
			}

			// are they all dead?
			for(i = 0; i < 6; i++)
			{
				if(IsAlive(h2bdest[i]))
				{
					break;
				}
			}

			if(i >= 6)
			{
				// all dead...
				// now random spawn...
				cockpitTimer.HideTimer();
				missionState = MS_WAITFORREDDEVIL;
				resetObjectives();

				stateTimer = GetTime() + (60 * 1.5f);
				stateTimer3 = GetTime() + 60 + 50;
				stateTimer4 = GetTime() + 80;
				portalattack[0] = portalattack[1] = NULL;
				randomattack[0] = NULL;
				randomattack[1] = NULL;
				randomattack[2] = NULL;
				randomattack[3] = NULL;
				randomattack[4] = NULL;

				soundhandle = 0;
				recyclerDropped = BZFALSE;
//				HideCockpitTimer();
			}
			break;
		}


		case MS_WAITFORREDDEVIL:
			if(stateTimer < GetTime())
			{
				int maxgoodguysdead = 0;
				// count how many bdtank's are alive.
				for(i = 0; i < 10 || maxgoodguysdead == 5; i++)
				{
					if(!IsAlive(bdtank[i]))
					{
						maxgoodguysdead++;
					}
				}

				for(i = 0; i < maxgoodguysdead; i++)
				{
					temp = BuildObject("bvrdeva", 1, "backup_1");
					Goto(temp, "backup_path");
				}

				stateTimer = GetTime() + 60 + 30;
				missionState = MS_WAITFORBADGUY;
			}
			break;

		case MS_WAITFORBADGUY:
			if(stateTimer < GetTime())
			{
				badguy[0] = BuildObject("cvtnk", 2, "attack_1");
				Attack(badguy[0], user);

				badguy[1] = BuildObject("cvtnk", 2, "attack_1");
				Attack(badguy[1], user);

				missionState = MS_WAITFORBADGUY1DIE;
			}
			break;

		case MS_WAITFORBADGUY1DIE:
			if(!IsAlive(badguy[0]))
			{
				stateTimer = GetTime() + (60 * 3);
				missionState = MS_WAITFORBADGUY2;
			}
			break;

		case MS_WAITFORBADGUY2:
			if(stateTimer < GetTime())
			{
				badguy[0] = BuildObject("cvtnk", 2, "attack_2");
				Attack(badguy[0], user);

				badguy[1] = BuildObject("cvtnk", 2, "attack_2");
				Attack(badguy[1], user);

				badguy[2] = BuildObject("cvtnk", 2, "attack_2");
				Attack(badguy[2], user);

				missionState = MS_WAITFORBADGUY2DIE;
			}
			break;

		case MS_WAITFORBADGUY2DIE:
			if(!IsAlive(badguy[0]) && !IsAlive(badguy[1]) && !IsAlive(badguy[2]))
			{
				missionState = MS_WAITFORSOUND3;
				resetObjectives();

				soundhandle = AudioMessage("bd06003.wav");
			}
			break;

		case MS_WAITFORSOUND3:
			if(IsAudioMessageDone(soundhandle))
			{
				recycler = BuildObject("bvrecy", 1, "recycler_spawn");
				Goto(recycler, "recycler_path");

				temp = BuildObject("bvrdeva", 1, "recycler_spawn");
				Follow(temp, recycler);
				temp = BuildObject("bvrdeva", 1, "recycler_spawn");

				Follow(temp, recycler);
				stateTimer = GetTime() + 30;
				missionState = MS_WAITFOROBJECTIVE2;
			}
			break;

		case MS_WAITFOROBJECTIVE2:
			if(stateTimer < GetTime())
			{
				missionState = MS_WAITFORRECYCLER;
				resetObjectives();
			}
			break;

		case MS_WAITFORRECYCLER:
			if(GetCurrentCommand(recycler) == CMD_NONE)
			{
				// deploy
				Recycler *myRecycler = (Recycler *) GameObjectHandle::GetObj(recycler);
				myRecycler->Deploy();

				AudioMessage("bd06004.wav");

				missionState = MS_WAITFORBADGUY3;
				stateTimer = GetTime() + 60;
			}
			break;

		case MS_WAITFORBADGUY3:
			temp = BuildObject("cvtnk", 2, "attack_3");
			Hunt(temp);
		
			temp = BuildObject("cvtnk", 2, "attack_3");
			Hunt(temp);
		
			temp = BuildObject("cvtnk", 2, "attack_3");
			Hunt(temp);
		
			temp = BuildObject("cvtnk", 2, "attack_3");
			Hunt(temp);
		
			temp = BuildObject("cvtnk", 2, "attack_3");
			Hunt(temp);

			missionState = MS_WAITFORAPC;
			break;

		case MS_WAITFORAPC:
			break;

		case MS_ENDCUTSCENE:
		{
			if(apchandle && GetCurrentCommand(apchandle) == CMD_NONE)
			{
				RemoveObject(apchandle);
				apchandle = NULL;
				soundhandle = AudioMessage("bd06009.wav");
				stateTimer2 = GetTime() + 60;
			}

			if(soundhandle && IsAudioMessageDone(soundhandle))
			{
				soundhandle = NULL;

				for(i = 0; i < 7; i++)
				{
					temp = BuildObject("cvtnk", 2, "dummy_1");
					Goto(temp, "dummy_1_path");
				}

				stateTimer = GetTime() + 3;
			}

			BZBOOLEAN arrived = CameraPath("camera_end_scene", 2000, 0, apchandle);

			if(arrived || (stateTimer && (CameraCancelled() || stateTimer < GetTime())))
			{
				CameraFinish();
				missionState = MS_WAITING3;
				stateTimer = GetTime() + 5;
			}
			break;
		}

		case MS_WAITING3:
			if(stateTimer < GetTime())
			{
				for(i = 0; i < 7; i++)
				{
					temp = BuildObject("cvfigh", 2, "portal_attack_2");
					Attack(temp, portal);
				}
				missionState = MS_WAITAPCFINISHED;
			}
			break;

		case MS_WAITAPCFINISHED:
			if(stateTimer2 < GetTime())
			{
				apchandle = BuildObject("bvapc", 1, "portal");;
				Goto(apchandle, "apc_out");
				missionState = MS_WAITAPCOUT;
			}
			break;

		case MS_WAITAPCOUT:
			if(GetCurrentCommand(apchandle) == CMD_NONE)
			{
				SucceedMission(GetTime() + 10.0f, "bd06wina.des");
				lost = BZTRUE;
			}
			break;
/*
				soundhandle = AudioMessage("bd06008.wav");
				missionState = MS_WAITFORSOUND8;
			}
			break;

		case MS_WAITFORSOUND8:
			if(IsAudioMessageDone(soundhandle))
			{
				missionState = MS_WAITING4;
				stateTimer = GetTime() + 5;
			}
			break;

		case MS_WAITING4:
			if(stateTimer < GetTime())
			{
				AudioMessage("bd06005.wav");
				SucceedMission(GetTime() + 10.0f, "bd06wina.des");
				lost = BZTRUE;
			}
			break;
*/
		case MS_RECYCLERDEAD:
		{
			if(IsAudioMessageDone(soundhandle))
			{
				FailMission(GetTime() + 2.0f, "bd06lsec.des");
				lost = BZTRUE;
			}
			break;
		}

		case MS_ATTACKTOEARLY:
		{
			if(IsAudioMessageDone(soundhandle))
			{
				FailMission(GetTime() + 2.0f, "bd06lsea.des");
				lost = BZTRUE;
			}
			break;
		}
	}
}

const std::set<PrjID>& BlackDog06Mission::GetPreloadGameObjects()
{
	static std::set<PrjID> retval = AiMission::PrjIDFromStrings(
	{ "cvartl", "cvfigh", "cvtnk", "bvrdeva", "bvrecy", "bvrdeva", "bvapc" }
	);
	return retval;
}
