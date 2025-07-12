

#include "AiMission.h"
#include "ScriptUtils.h"
#include "AudioMessage.h"

/*
	BlackDog09Mission
*/

class BlackDog09Mission : public AiMission {
	DECLARE_RTIME(BlackDog09Mission)
public:
	BlackDog09Mission();
	~BlackDog09Mission();

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

				// triggered?
				trigger1,
				oneOfTheEnemy,

				// deviate units spawned?
				deviateSpawned,

				// told to go to the beacons?
				gotoBeacon2,
				gotoBeacon3,

				// sounds
				sound7Played,
				sound2Played,

				// tanks arrived at beacons?
				tankArrived1,
				tankArrived2,
				tankArrived3,

				// strayed from the pack
				strayed,

				// portal active?
				portalActive,

				// have we lost?
				lost, won,

				b_last;
		};
		bool b_array[22];
	};

	// floats
	union {
		struct {
			float
				sound1Time,
				sound2Time,
				sound3Time,
				sound6Time,
				orderGotoTime1,
				deviateTime,
				tankTimeout,
				f_last;
		};
		float f_array[7];
	};

	// handles
	union {
		struct {
			BZHandle
				// *** User stuff
				user,
				lastUser,
				fakeUser,

				// *** Units
				portal,
				cvtnk1,
				cvtnk2,
				cvtnk3,
				cvtnk4,
				cvtnk5,

				// nav beacons
				beacon1,
				beacon2,
				beacon3,
				
				h_last;
		};
		BZHandle h_array[12];
	};

	// integers
	union {
		struct {
			int32_t
				// *** Sounds
				winSound,
				sound1,
				sound2,
				sound3,
				sound5,
				sound7,
				
				i_last;
		};
		int32_t i_array[6];
	};
};

IMPLEMENT_RTIME(BlackDog09Mission)

BlackDog09Mission::BlackDog09Mission()
{
}

BlackDog09Mission::~BlackDog09Mission()
{
}

bool BlackDog09Mission::Load(file fp)
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

bool BlackDog09Mission::PostLoad(void)
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

bool BlackDog09Mission::Save(file fp)
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

void BlackDog09Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

void BlackDog09Mission::AddObject(BZHandle h)
{
}

void BlackDog09Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

void BlackDog09Mission::Setup()
{
	int i = 0;
	startDone = BZFALSE;
	objective1Complete = BZFALSE;
	objective2Complete = BZFALSE;
	objective3Complete = BZFALSE;
	for (i = 0; i < 2; i++)
		cameraReady[i] = cameraComplete[i] = BZFALSE;
	gotoBeacon2 = BZFALSE;
	gotoBeacon3 = BZFALSE;
	sound7Played = BZFALSE;
	deviateSpawned = BZFALSE;
	tankArrived1 = BZFALSE;
	tankArrived2 = BZFALSE;
	tankArrived3 = BZFALSE;
	trigger1 = BZFALSE;
	strayed = BZFALSE;
	oneOfTheEnemy = BZFALSE;
	sound2Played = BZFALSE;
	portalActive = BZFALSE;
	
	// units
	user = NULL;
	lastUser = NULL;
	portal = GetHandle("portal");
	cvtnk1 = GetHandle("cvtnk1");
	cvtnk2 = GetHandle("cvtnk2");
	cvtnk3 = GetHandle("cvtnk3");
	cvtnk4 = GetHandle("cvtnk4");
	cvtnk5 = GetHandle("cvtnk5");
	beacon1 = NULL;
	beacon2 = NULL;
	beacon3 = NULL;
	
	// sounds
	sound1 = NULL;
	sound2 = NULL;
	sound3 = NULL;
	sound5 = NULL;
	sound7 = NULL;
	winSound = NULL;
	
	// times
	sound1Time = 999999.9f;
	sound2Time = 999999.9f;
	sound3Time = 999999.9f;
	sound6Time = 999999.9f;
	orderGotoTime1 = 999999.9f;
	deviateTime = 999999.9f;
	tankTimeout = 999999.9f;
}


void BlackDog09Mission::Execute()
{
	int i = 0;
	lastUser = user;
	user = GetPlayerHandle(); //assigns the player a handle every frame

	if (!startDone)
	{
		SetScrap(1,0);
		SetPilot(1,0);

		// don't do this part after the first shot
		startDone = BZTRUE;

		sound1Time = GetTime() + 1.0f;

		ClearObjectives();
		AddObjective("bd09001.otf", WHITE);
		SetObjectiveOn(cvtnk1);

	}

	// SOE #1
	if (sound1Time < GetTime())
	{
		sound1Time = 999999.9f;

		sound1 = AudioMessage("bd09001.wav");
	}

	if (sound1 != BZINVALIDHANDLE && IsAudioMessageDone(sound1))
	{
		sound1 = BZINVALIDHANDLE;

		sound2Time = GetTime() + 15.0f;
	}

	// SOE #2
	if (sound2Time < GetTime())
	{
		sound2Time = 999999.9f;

		if (IsOdf(user, "cvapc") && !strayed)
		{
			sound2Played = BZTRUE;
			oneOfTheEnemy = BZTRUE;
						
			sound2 = AudioMessage("bd09002.wav");
			AddObjective("bd09004.otf", WHITE);
		}
	}

	if (!sound2Played && !IsOdf(user, "cvapc") && !strayed)
	{
		strayed = BZTRUE;
		oneOfTheEnemy = BZFALSE;
		SetPerceivedTeam(user, 1);

		// get the guys to attack
		Attack(cvtnk2, user);
		Attack(cvtnk3, user);
		Attack(cvtnk4, user);
		Attack(cvtnk5, user);
		deviateTime = GetTime() + 1.0f;

		ClearObjectives();
		AddObjective("bd09003.otf", WHITE);
	}

	if (sound2 != BZINVALIDHANDLE && IsAudioMessageDone(sound2))
	{
		sound2 = BZINVALIDHANDLE;
		//SetPerceivedTeam(user, 2);
	}

	if (oneOfTheEnemy)
		SetPerceivedTeam(user,2);
	else if (strayed)
		SetPerceivedTeam(user, 1);

	// SOE #3
	if (objective1Complete && !strayed)
	{
		// check distance to each of the other cvtnks
		Distance dist = (75.0f + (gotoBeacon3 ? 75.0f : 0) + (objective2Complete ? 75.0f : 0));
		if ((GetDistance(user, cvtnk2) > dist || (cvtnk2 == BZINVALIDHANDLE) || (cvtnk2 == user)) &&
			(GetDistance(user, cvtnk3) > dist || (cvtnk3 == BZINVALIDHANDLE) || (cvtnk3 == user)) &&
			(GetDistance(user, cvtnk4) > dist || (cvtnk4 == BZINVALIDHANDLE) || (cvtnk4 == user)) &&
			(GetDistance(user, cvtnk5) > dist || (cvtnk5 == BZINVALIDHANDLE) || (cvtnk5 == user)))
		{
			oneOfTheEnemy = BZFALSE;
			strayed = BZTRUE;
			
			// cut to SOE #10
			deviateTime = GetTime() + 2.0f;
		}
	}

	// SOE #4
	if (!strayed && !objective1Complete && (user == cvtnk1 || user == cvtnk2 || user == cvtnk3 || user == cvtnk4 || user == cvtnk5) && sound2Played)
	{
		oneOfTheEnemy = BZFALSE;
		objective1Complete = BZTRUE;
		SetObjectiveOff(cvtnk1);

		sound3Time = GetTime() + 5.0f;

		beacon1 = BuildObject("apcamr", 1, "spawn_beacon1");
	}

	if (!objective1Complete && (!IsValid(cvtnk1) || !IsValid(cvtnk2) || !IsValid(cvtnk3) || !IsValid(cvtnk3) || !IsValid(cvtnk4) || !IsValid(cvtnk5)))
	{
		SetPerceivedTeam(user, 1);
		oneOfTheEnemy = BZFALSE;
		strayed = BZTRUE;

		// cut to SOE #10
		deviateTime = GetTime() + 2.0f;
	}

	if (sound3Time < GetTime() && !deviateSpawned)
	{
		sound3Time = 999999.9f;
		sound3 = AudioMessage("bd09003.wav");
	}

	if (sound3 != BZINVALIDHANDLE && IsAudioMessageDone(sound3))
	{
		sound3 = BZINVALIDHANDLE;
		ClearObjectives();
		AddObjective("bd09001.otf", GREEN);
		AddObjective("bd09002.otf", WHITE);

		orderGotoTime1 = GetTime() + 1.0f;
	}

	// SOE #5
	if (orderGotoTime1 < GetTime())
	{
		orderGotoTime1 = 999999.9f;
		if (IsAlive(cvtnk2))
			Goto(cvtnk2, "tank_path", 1);
		if (IsAlive(cvtnk3))
			Goto(cvtnk3, "tank_path", 1);
		if (IsAlive(cvtnk4))
			Goto(cvtnk4, "tank_path", 1);
		if (IsAlive(cvtnk5))
			Goto(cvtnk5, "tank_path", 1);
	}

	// SOE #6
	if (!tankArrived1)
	{
		// have any of the tanks arrived?
		if (GetDistance(beacon1, cvtnk1) < 100.0f ||
			GetDistance(beacon1, cvtnk2) < 100.0f ||
			GetDistance(beacon1, cvtnk3) < 100.0f ||
			GetDistance(beacon1, cvtnk4) < 100.0f ||
			GetDistance(beacon1, cvtnk5) < 100.0f)
		{
			tankArrived1 = BZTRUE;

			// spawn the next beacon
			beacon2 = BuildObject("apcamr", 1, "spawn_beacon2");
		}
	}

	if (objective1Complete && !gotoBeacon2 && !deviateSpawned)
	{
		// has the player arrived?
		if (GetDistance(user, beacon1) < 100.0f)
		{
			gotoBeacon2 = BZTRUE;
			AudioMessage("bd09004.wav");
		}
	}

	// SOE #7
	if (!tankArrived2)
	{
		// have any of the tanks arrived?
		if (GetDistance(beacon2, cvtnk1) < 100.0f ||
			GetDistance(beacon2, cvtnk2) < 100.0f ||
			GetDistance(beacon2, cvtnk3) < 100.0f ||
			GetDistance(beacon2, cvtnk4) < 100.0f ||
			GetDistance(beacon2, cvtnk5) < 100.0f)
		{
			tankArrived2 = BZTRUE;

			// spawn the next beacon
			beacon3 = BuildObject("apcamr", 1, "spawn_beacon3");
		}
	}

	if (objective1Complete && !gotoBeacon3 && !deviateSpawned)
	{
		// has the player arrived?
		if (GetDistance(user, beacon2) < 100.0f)
		{
			gotoBeacon3 = BZTRUE;
			AudioMessage("bd09005.wav");
			sound6Time = GetTime() + 5.0f;
		}
	}

	// #SOE #8
	if (sound6Time < GetTime())
	{
		sound6Time = 999999.9f;
		AudioMessage("bd09006.wav");
		SetObjectiveOn(portal);
	}

	if (objective1Complete && !objective2Complete)
	{
		if (gotoBeacon2 && gotoBeacon3 && GetDistance(user, beacon3) < 100.0f)
		{
			objective2Complete = BZTRUE;

			ClearObjectives();
			AddObjective("bd09001.otf", GREEN);
			AddObjective("bd09002.otf", GREEN);
			AddObjective("bd09003.otf", WHITE);
		}
	}

	// SOE #10
	if (deviateTime < GetTime() && !deviateSpawned)
	{
		SetPerceivedTeam(user, 1);

		ClearObjectives();
		if (objective1Complete)
			AddObjective("bd09001.otf", GREEN);
		if (objective2Complete)
			AddObjective("bd09002.otf", GREEN);
		AddObjective("bd09003.otf", WHITE);


		deviateTime = 999999.9f;
		deviateSpawned = BZTRUE;
		BZHandle h;
		h = BuildObject("cvfigh", 2, "spawn_deviate1");
		Attack(h, user);
		if (!objective1Complete || !gotoBeacon3)
		{
			h = BuildObject("cvfigh", 2, "spawn_deviate1");
			Attack(h, user);
		}
		if (!objective2Complete)
		{
			h = BuildObject("cvltnk", 2, "spawn_deviate2");
			Attack(h, user);
		}
		if (!objective1Complete || !gotoBeacon3)
		{
			h = BuildObject("cvltnk", 2, "spawn_deviate2");
			Attack(h, user);
		}
		if (!objective2Complete)
		{
			h = BuildObject("cvhtnk", 2, "spawn_deviate3");
			Attack(h, user);
			h = BuildObject("cvrckt", 2, "spawn_deviate4");
			Attack(h, user);
		}
		else
		{
			h = BuildObject("cvfigh", 2, "spawn_deviate4");
			Attack(h, user);
		}
		if (!objective1Complete || !gotoBeacon3)
		{
			h = BuildObject("cvrckt", 2, "spawn_deviate4");
			Attack(h, user);
		}
		h = BuildObject("cvfigh", 2, "spawn_deviate5");
		Attack(h, user);
		if (!objective1Complete || !gotoBeacon3)
		{
			h = BuildObject("cvfigh", 2, "spawn_deviate5");
			Attack(h, user);
		}
		if (!objective2Complete)
		{
			h = BuildObject("cvtnk", 2, "spawn_deviate6");
			Attack(h, user);
		}
		if (!objective1Complete || !gotoBeacon3)
		{
			h = BuildObject("cvtnk", 2, "spawn_deviate6");
			Attack(h, user);
		}
		
		AudioMessage("bd09007.wav");

		ObjectList &list = *GameObject::objectList;
		for (ObjectList::iterator i = list.begin(); i != list.end(); i++) 
		{
			GameObject *o = *i;
			BZHandle h = GameObjectHandle::Find(o);
			if (IsOdf(h, "cvturrc"))
			{
				Attack(h, user);
			}
		}
	}
	
	if (objective1Complete && !IsOdf(user, "cvtnkb") && tankTimeout < 0)
	{
		tankTimeout = GetTime() + 10 * 60.0f;
	}

	if (tankTimeout > 0 && IsOdf(user, "cvtnkb"))
	{
		// player is back into a cvtnk
		tankTimeout = -1;
	}

	if (tankTimeout > 0 && tankTimeout < GetTime() && !won && !lost)
	{
		// the player has been out of the tank for too long
		lost = BZTRUE;
		tankTimeout = -1;
		FailMission(GetTime() + 1.0f, "bd09lose.des");
	}

	// SOE #11
	if (GetDistance(user, "trigger_1") <  200.0f && !trigger1)
	{
		trigger1 = BZTRUE;

		for (i = 0; i < 2 /* 5 */; i++)
		{
			BZHandle h = BuildObject("cvtnkb", 2, "last_one");
			Attack(h, user);
		}
	}

	// SOE #12
	if (GetDistance(user, portal) < 250.0f && !portalActive)
	{
		portalActive = BZTRUE;
		activatePortal(portal, true);
		winSound = AudioMessage("bd09008.wav");
	}

	// You only win if you take a tank through the portal...
	if (isTouching(user, portal) && !won && !lost)
	{
		if (IsOdf(user, "cvtnkb"))
		{
			won = BZTRUE;
			SucceedMission(GetTime(), "bd09win.des");
		}
		else
		{
			// the player has been out of the tank for too long
			lost = BZTRUE;
			tankTimeout = -1;
			FailMission(GetTime() + 1.0f, "bd09lose.des");
		}

	}

	// lost the portal?
	if (GetHealth(portal) <= 0.0 && !lost && !won)
	{
		lost = BZTRUE;
		FailMission(GetTime() + 1.0f, "bd09lseb.des");
	}
}

const std::set<PrjID>& BlackDog09Mission::GetPreloadGameObjects()
{
	static std::set<PrjID> retval = AiMission::PrjIDFromStrings(
	{ "apcamr", "cvfigh", "cvltnk", "cvtnk", "cvhtnk", "cvrckt", "cvtnkb" }
	);
	return retval;
}
