
#include "AiMission.h"
#include "ScriptUtils.h"
#include "ColorFade.h"
#include "AudioMessage.h"

extern "C"{
#include "audio.h"
}

const char *otf2[2] = { "ch07002n.otf", "ch07002e.otf" };

const char *specials[] =
{
	"svapcc",	// Toni
	"svapcd",	// Richard
	"svapce",	// Mick
	"svapcf",	// Shane
	"svapcg",	// Matt
	"svapch",	// Kochun
	"svapci",	// Tom
	"svapcj",	// Stephen
	"svapck",	// Dan
	"svapcl",	// Joel
	"svapcm",	// Crista
	"svapcn",	// David
	"svapco",	// Support
	"svapcp",	// Robert
	"svapcs"	// Buffy the Vampire Slayer
};

/*
	Chinese07Mission
*/

class Chinese07Mission : public AiMission {
	DECLARE_RTIME(Chinese07Mission)
public:
	Chinese07Mission();
	~Chinese07Mission();

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
	BZHandle getBase();
	
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
				cameraReady[3], cameraComplete[3],

				// burgler
				doBurglarSequence,
				burglarSequencePlayed,
				detected,

				// north or east?
				doNorthSequence,
				doEastSequence,
				arrived,

				// zn attacks
				znAttacked[7],

				// convoy
				convoySpawned,

				// bomb destroyed?
				bombDestroyed,

				// got in fighter?
				gotInFighter,
				gotOutOfFighter,

				// snipers spawned
				snipersSpawned,

				// sounds played?
				sound6Played,

				// been told to attack player?
				toldToAttackFighter[7],

				// misc. triggers
				triggered,

				// backups
				backup1, backup2, backup3, backup4,

				// rescue units
				rescue,

				// player is in a hauler?
				inHauler,
				
				// won or lost?
				won, lost,
				
				b_last;
		};
		bool b_array[45];
	};

	// floats
	union {
		struct {
			float
				figh1Time,
				figh2Time,
				figh3Time,
				burglarStopTime,
				cinBurglarTimeout,
				foot1Time,
				sound5Time,
				convoyTime,
				f_last;
		};
		float f_array[8];
	};

	// handles
	union {
		struct {
			BZHandle
				// the user
				user,
				lastUser,
				
				// units
				commTower,
				fakePlayer,
				relicApc,
				foot[6],
				fighters[7],
				bombs[2],
				endGuy[6],

				// ammo stuff
				ammo1, ammo2, repair1, repair2,
				
				// navs
				navBridge,
				
				// place holder
				h_last;
		};
		BZHandle h_array[31];
	};

	// integers
	union {
		struct {
			int32_t
				direction,	// 0 = north
							// 1 = east
				relic,		// apc # with relic
				convoyCount,	// number of convoy units spawned
				
				// sounds
				openingSound,
				seqSound,
				winSound,
				sound7,
				
				i_last;
		};
		int32_t i_array[7];
	};
};

IMPLEMENT_RTIME(Chinese07Mission)

Chinese07Mission::Chinese07Mission()
{
}

Chinese07Mission::~Chinese07Mission()
{
}

bool Chinese07Mission::Load(file fp)
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

bool Chinese07Mission::PostLoad(void)
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

bool Chinese07Mission::Save(file fp)
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

void Chinese07Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

void Chinese07Mission::AddObject(BZHandle h)
{
}

void Chinese07Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

void Chinese07Mission::Setup()
{
	int i = 0;
	startDone = BZFALSE;
	objective1Complete = BZFALSE;
	objective2Complete = BZFALSE;
	objective3Complete = BZFALSE;
	doBurglarSequence = BZFALSE;
	burglarSequencePlayed = BZFALSE;
	detected = BZFALSE;
	doNorthSequence = BZFALSE;
	doEastSequence = BZFALSE;
	convoySpawned = BZFALSE;
	bombDestroyed = BZFALSE;
	gotInFighter = BZFALSE;
	gotOutOfFighter = BZFALSE;
	snipersSpawned = BZFALSE;
	sound6Played = BZFALSE;
	triggered = BZFALSE;
	arrived = BZFALSE;
	backup1 = BZFALSE;
	backup2 = BZFALSE;
	backup3 = BZFALSE;
	backup4 = BZFALSE;
	rescue = BZFALSE;
	inHauler = BZFALSE;
	
	// cameras
	for (i = 0; i < 3; i++)
	{
		cameraReady[i] = BZFALSE;
		cameraComplete[i] = BZFALSE;
	}

	for (i = 0; i < 7; i++)
		znAttacked[i] = BZFALSE;
	for (i = 0; i < 7; i++)
		toldToAttackFighter[i] = BZFALSE;
	
	// units
	user = NULL;
	lastUser = NULL;
	commTower = GetHandle("commtower");
	relicApc = NULL;
	foot[0] = GetHandle("foot_1_1");
	foot[1] = GetHandle("foot_1_2");
	foot[2] = GetHandle("foot_1_3");
	foot[3] = GetHandle("foot_2_1");
	foot[4] = GetHandle("foot_2_2");
	foot[5] = GetHandle("foot_2_3");
	fighters[0] = GetHandle("figh_1_1");
	fighters[1] = GetHandle("figh_1_2");
	fighters[2] = GetHandle("figh_1_3");
	fighters[3] = GetHandle("figh_2_1");
	fighters[4] = GetHandle("figh_2_2");
	fighters[5] = GetHandle("figh_3_1");
	fighters[6] = GetHandle("figh_3_2");
	bombs[0] = GetHandle("bomb_north");
	bombs[1] = GetHandle("bomb_east");
	for (i = 0; i < 6; i++)
		endGuy[i] = NULL;
	ammo1 = GetHandle("ammo_1");
	ammo2 = GetHandle("ammo_2");
	repair1 = GetHandle("repair_1");
	repair2 = GetHandle("repair_2");
	
	// navs
	navBridge = NULL;
	
	// sounds
	openingSound = NULL;
	seqSound = NULL;
	winSound = NULL;
	sound7 = NULL;
	
	// times
	figh1Time = 999999.9f;
	figh2Time = 999999.9f;
	figh3Time = 999999.9f;
	sound5Time = 999999.9f;
	burglarStopTime = 999999.9f;
	foot1Time = 999999.9f;
	convoyTime = 999999.9f;
	cinBurglarTimeout = 999999.9f;

	// ints
	direction = rand() % 2;
	relic = rand() % 3;
	convoyCount = 0;
}

BZHandle Chinese07Mission::getBase()
{
	BZHandle h[5];
	int numH = 0;
	if (numH == 0)
		return NULL;
	else
		return h[rand() % numH];
}

void Chinese07Mission::Execute()
{
	int i = 0;
	lastUser = user;
	user = GetPlayerHandle(); //assigns the player a handle every frame

	if (!startDone)
	{
		SetPilot(1, 10);
		SetScrap(1, 8);

		// don't do this part after the first shot
		startDone = BZTRUE;
		burglarStopTime = GetTime() + 90.0f;
		sound5Time = GetTime() + 13 * 60.0f;
		convoyTime = GetTime() + 14 * 60.0f;
	}

	if (user != lastUser && !doBurglarSequence)
		SetPerceivedTeam(user, 1);
	
	if (!cameraComplete[0])
	{
		if (!cameraReady[0])
		{
			cameraReady[0] = BZTRUE;
			CameraReady();
			openingSound = AudioMessage("ch07001.wav");
		}

		bool arrived = CameraPath("cin_start", 800, 2400, commTower);

		if (CameraCancelled())
		{
			arrived = BZTRUE;
			StopAudioMessage(openingSound);
		}
		if (arrived)
		{
			CameraFinish();
			cameraComplete[0] = BZTRUE;
			ClearObjectives();
			AddObjective("ch07001.otf", WHITE);
		}
	}
	
	// if the fighters are close enough
	for (i = 0; i < 7; i++)
	{
		if (IsAlive(fighters[i]) && !toldToAttackFighter[i] && GetDistance(user, fighters[i]) < 160.0f)
		{
			Attack(fighters[i], user, 1);
			toldToAttackFighter[i] = BZTRUE;
		}
	}

	if (!burglarSequencePlayed && GetDistance(user, commTower) < 30.0f)
	{
		doBurglarSequence = BZTRUE;
		burglarSequencePlayed = BZTRUE;
	}

	if (doBurglarSequence)
	{
		if (!cameraReady[1])
		{
			CameraReady();
			cameraReady[1] = BZTRUE;

			Hide(user);
			SetPerceivedTeam(user, 2);
			fakePlayer = BuildObject("sspilo", 0, "fake_spn");
			Goto(fakePlayer, "fake_vanish", 1);
		}

		CameraPath("cin_burglar", 400, 0, commTower);
		if (fakePlayer != BZINVALIDHANDLE && GetDistance(fakePlayer, "fake_vanish") < 10.0f)
		{
			RemoveObject(fakePlayer);
			fakePlayer = NULL;
			cinBurglarTimeout = GetTime() + 3.0f;
		}

		if (cinBurglarTimeout < GetTime() ||
			CameraCancelled())
		{
			CameraFinish();
			if (fakePlayer != BZINVALIDHANDLE)
				RemoveObject(fakePlayer);
			SetPerceivedTeam(user, 1);
			UnHide(user);
			SetPosition(user, "burglar_exit");
			doBurglarSequence = BZFALSE;

			if (direction == 0)
				doNorthSequence = BZTRUE;
			else if (direction == 1)
				doEastSequence = BZTRUE;

			objective1Complete = BZTRUE;
		}
	}

	if (doNorthSequence)
	{
		if (!cameraReady[2])
		{
			cameraReady[2] = BZTRUE;
			CameraReady();
			seqSound = AudioMessage("ch07002.wav");
			navBridge = BuildObject("apcamr", 1, "nav_north");
			SetName(navBridge, "North Bridge");
		}

		bool seqDone = BZFALSE;
		if (!arrived)
			arrived = CameraPath("cin_north", 1600, 1800, bombs[0]);
		if (arrived && IsAudioMessageDone(seqSound))
			seqDone = BZTRUE;

		if (CameraCancelled())
		{
			seqDone = BZTRUE;
			StopAudioMessage(seqSound);
		}
		if (seqDone)
		{
			CameraFinish();
			doNorthSequence = BZFALSE;

			ClearObjectives();
			AddObjective("ch07001.otf", GREEN);
			AddObjective("ch07002n.otf", WHITE);
			foot1Time = GetTime() + 10.0f;
		}
	}

	if (doEastSequence)
	{
		if (!cameraReady[2])
		{
			Trace("East Sequence now playing");
			cameraReady[2] = BZTRUE;
			CameraReady();
			seqSound = AudioMessage("ch07003.wav");
			navBridge = BuildObject("apcamr", 1, "nav_east");
			SetName(navBridge, "East Bridge");
		}

		bool seqDone = BZFALSE;
		if (!arrived)
			arrived = CameraPath("cin_east", 1600, 1800, bombs[1]);
		if (arrived && IsAudioMessageDone(seqSound))
			seqDone = BZTRUE;

		if (CameraCancelled())
		{
			seqDone = BZTRUE;
			StopAudioMessage(seqSound);
		}
		if (seqDone)
		{
			CameraFinish();
			doEastSequence = BZFALSE;

			ClearObjectives();
			AddObjective("ch07001.otf", GREEN);
			AddObjective("ch07002e.otf", WHITE);
			foot1Time = GetTime() + 10.0f;
		}
	}

	if (foot1Time < GetTime())
	{
		foot1Time = 999999.9f;

		// sick 'em
		for (i = 0; i < 6; i++)
		{
			if (IsAlive(foot[i]))
				Attack(foot[i], user, 1);
		}
		AudioMessage("ch07004.wav");

	}

		if (!znAttacked[0] && GetDistance(user, "zn_1_trig") < 900.0f)
		{
			znAttacked[0] = BZTRUE;

			BZHandle h;
			h = BuildObject("ssusera", 2, "zn_1_snip_1_spn");
			Attack(h, user);
			h = BuildObject("svturr", 2, "zn_1_turr_1_spn");
			Attack(h, user);
			h = BuildObject("sspilo", 2, "zn_1_pilo_1_spn");
			Attack(h, user);
		}

		if (!znAttacked[1] && GetDistance(user, "zn_2_trig") < 900.0f)
		{
			znAttacked[1] = BZTRUE;

			BZHandle h;
			h = BuildObject("ssusera", 2, "zn_2_snip_1_spn");
			Attack(h, user);
			h = BuildObject("svturr", 2, "zn_2_turr_1_spn");
			Attack(h, user);
			h = BuildObject("sspilo", 2, "zn_2_pilo_1_spn");
			Attack(h, user);
		}

		if (!znAttacked[2] && GetDistance(user, "zn_3_trig") < 900.0f)
		{
			znAttacked[2] = BZTRUE;

			BZHandle h;
			h = BuildObject("ssusera", 2, "zn_3_snip_1_spn");
			Attack(h, user);
			h = BuildObject("sspilo", 2, "zn_3_snip_3_spn");
			Attack(h, user);
			h = BuildObject("svturr", 2, "zn_3_turr_1_spn");
			Attack(h, user);
		}

		if (!znAttacked[3] && GetDistance(user, "zn_4_trig") < 900.0f)
		{
			znAttacked[3] = BZTRUE;

			BZHandle h;
			h = BuildObject("ssusera", 2, "zn_4_snip_1_spn");
			Attack(h, user);
			h = BuildObject("sspilo", 2, "zn_4_snip_2_spn");
			Attack(h, user);
			h = BuildObject("svturr", 2, "zn_4_turr_1_spn");
			Attack(h, user);
		}

		if (!znAttacked[4] && GetDistance(user, "zn_5_trig") < 900.0f)
		{
			znAttacked[4] = BZTRUE;

			BZHandle h;
			h = BuildObject("ssusera", 2, "zn_5_snip_1_spn");
			Attack(h, user);
			h = BuildObject("svturr", 2, "zn_5_turr_1_spn");
			Attack(h, user);
			h = BuildObject("sspilo", 2, "zn_5_pilo_1_spn");
			Attack(h, user);
		}

		if (!znAttacked[5] && GetDistance(user, "zn_6_trig") < 900.0f)
		{
			znAttacked[5] = BZTRUE;

			BZHandle h;
			h = BuildObject("ssusera", 2, "zn_6_snip_1_spn");
			Attack(h, user);
			h = BuildObject("svturr", 2, "zn_6_turr_2_spn");
			Attack(h, user);
		}

		if (!znAttacked[6] && GetDistance(user, "zn_7_trig") < 900.0f)
		{
			znAttacked[06] = BZTRUE;

			BZHandle h;
			h = BuildObject("ssusera", 2, "zn_7_snip_1_spn");
			Attack(h, user);
			h = BuildObject("sspilo", 2, "zn_7_snip_2_spn");
			Attack(h, user);
		}

	if (sound5Time < GetTime() && burglarSequencePlayed)
	{
		sound5Time = 999999.9f;
		AudioMessage("ch07005.wav");
	}

	if (convoyTime < GetTime())
	{
		// spawn the convoy
		static const char *spawn[2] = { "north_spn", "east_spn" };
		static const char *path[2] = { "north_path", "east_path" };

		BZHandle h;
		if (convoyCount == relic)
		{
			h = BuildObject("svapca", 2, spawn[direction]);
			relicApc = h;
		}
		else
		{
//#ifndef _DEBUG
			if (((convoyCount == 2) ||
				(convoyCount == 1 && relic == 2)))
			{
				int numMembers = SIZEOF(specials);
				h = BuildObject(specials[rand() % numMembers], 2, spawn[direction]);
			}
			else
//#endif
				h = BuildObject("svapcb", 2, spawn[direction]);
		}

		Goto(h, path[direction]);
		GameObject *o = GameObjectHandle::GetObj(h);
		o->curPilot = 0;
		

		BZHandle d = BuildObject("svfigh", 2, spawn[direction]);
		o = GameObjectHandle::GetObj(d);
		o->curPilot = 0;
		Defend2(d, h, 1);
		
		convoyCount++;
		if (convoyCount == 3)
		{
			convoyTime = 999999.9f;
			convoySpawned = BZTRUE;
		}
		else
		{
			convoyTime = GetTime() + 8.0f;
		}
	}

	if (/* convoySpawned && */ !triggered)
	{
		static const char *trig[2] = { "north_trig", "east_trig" };
		static const char *spawn[2][2] = {	"sold_north_1_spn", "sold_north_2_spn",
										"sold_east_1_spn", "sold_east_2_spn" };
		static const char *spawn2[2][2] = {	"pilo_north_1_spn", "pilo_north_2_spn",
										"pilo_east_1_spn", "pilo_east_2_spn" };
		if (GetDistance(user, trig[direction]) < 350.0f)
		{
			triggered = BZTRUE;
			BZHandle h = BuildObject("sssold", 2, spawn[direction][0]);
			Attack(h, user, 1);
			h = BuildObject("sssold", 2, spawn[direction][1]);
			Attack(h, user, 1);
			h = BuildObject("sspilo", 2, spawn2[direction][0]);
			Attack(h, user, 1);
			h = BuildObject("sspilo", 2, spawn2[direction][1]);
			Attack(h, user, 1);

			objective2Complete = BZTRUE;
			ClearObjectives();
			if (objective1Complete)
				AddObjective("ch07001.otf", GREEN);
			else
				AddObjective("ch07001.otf", WHITE);
			if (burglarSequencePlayed)
				AddObjective(otf2[direction], GREEN);
			AddObjective("ch07003.otf", WHITE);
		}
	}

	if (!bombDestroyed)
	{
		static const char *expl[2] = { "expl_north_spn", "expl_east_spn" };
		static const char *spn[2][3] = {	"north_sold_1_spn", "north_sold_2_spn", "north_sold_3_spn",
									"east_sold_1_spn", "east_sold_2_spn", "east_sold_3_spn" };
		
		if (GetHealth(bombs[direction]) <= 0.0)
		{
			//Trace("bomb was destroyed, %s should go boom now",
			//	expl[direction]);
			bombDestroyed = BZTRUE;
			// using large/AGP assets
			// (alternative was "xtorxpla")
			MakeExplosion(expl[direction], "xtorxplb");
			
			BZHandle h;
			h = BuildObject("sspilo", 2, spn[direction][0]);
			Attack(h, user);
			h = BuildObject("sspilo", 2, spn[direction][1]);
			Attack(h, user);
		}
	}

	if (relicApc != BZINVALIDHANDLE && GetHealth(relicApc) <= 0.0 && !objective3Complete)
	{
		objective3Complete = BZTRUE;

		ClearObjectives();
		if (objective1Complete)
			AddObjective("ch07001.otf", GREEN);
		else
			AddObjective("ch07001.otf", WHITE);
		if (burglarSequencePlayed)
			AddObjective(otf2[direction], GREEN);
		AddObjective("ch07003.otf", GREEN);
		AddObjective("ch07004.otf", WHITE);

		AudioMessage("ch07008.wav");
		BZHandle h;
		h = BuildObject("apcamr", 1, "nav_end");
		SetName(h, "Drop Zone");
	}

	if (objective3Complete)
	{
		if (!backup1 && GetDistance(user, "zn_8_trig") < 800.0f)
		{
			backup1 = BZTRUE;
			BZHandle h;
			h = BuildObject("sspilo", 2, "back_1_1_spn");
			Attack(h, user);
			h = BuildObject("sspilo", 2, "back_1_2_spn");
			Attack(h, user);
		}
		if (!backup2 && GetDistance(user, "zn_9_trig") < 800.0f)
		{
			backup2 = BZTRUE;
			BZHandle h;
			h = BuildObject("sspilo", 2, "back_2_1_spn");
			Attack(h, user);
			h = BuildObject("sspilo", 2, "back_2_2_spn");
			Attack(h, user);
		}

		if (!backup3 && GetDistance(user, "nav_end") < 1000.0f)
		{
			backup3 = BZTRUE;
			BZHandle h;
			h = BuildObject("sspilo", 2, "pilo_end_1_spn");
			Attack(h, user);
			h = BuildObject("sspilo", 2, "pilo_end_2_spn");
			Attack(h, user);
			h = BuildObject("sspilo", 2, "pilo_end_3_spn");
			Attack(h, user);
		}

		if (!backup4 && GetDistance(user, "zn_3_trig") < 800.0f)
		{
			backup4 = BZTRUE;
			BZHandle h;
			h = BuildObject("sspilo", 2, "back_1_5_spn");
			Attack(h, user);
			h = BuildObject("sspilo", 2, "back_1_6_spn");
			Attack(h, user);
		}
	}

	if (relicApc != BZINVALIDHANDLE && !lost && !won)
	{
		static const char *spot1[2] = { "north_wav", "east_wav" };
		static const char *spot2[2] = { "north_fail", "east_fail" };
		if (GetDistance(relicApc, spot1[direction]) < 50.0f &&
			!sound6Played)
		{
			sound6Played = BZTRUE;
			AudioMessage("ch07006.wav");
		}
		if (GetDistance(relicApc, spot2[direction]) < 50.0f)
		{
			lost = BZTRUE;
			sound7 = AudioMessage("ch07007.wav");
		}
	}

	if (sound7 != BZINVALIDHANDLE && IsAudioMessageDone(sound7))
	{
		sound7 = BZINVALIDHANDLE;
		FailMission(GetTime() + 1.0f, "ch07lose.des");
	}

	if (objective3Complete && GetDistance(user, "nav_end") < 170.0f &&
		!snipersSpawned)
	{
		snipersSpawned = BZTRUE;

		BZHandle h = BuildObject("ssusera", 2, "snip_end_1_spn");
		endGuy[0] = h;
		Attack(h, user, 1);
		h = BuildObject("ssusera", 2, "snip_end_2_spn");
		endGuy[1] = h;
		Attack(h, user, 1);
		h = BuildObject("sspilo", 2, "snip_end_3_spn");
		endGuy[2] = h;
		Attack(h, user, 1);
		h = BuildObject("sssold", 2, "sold_end_1_spn");
		endGuy[3] = h;
		Attack(h, user, 1);
		h = BuildObject("sspilo", 2, "sold_end_2_spn");
		endGuy[4] = h;
		Attack(h, user, 1);
		h = BuildObject("sspilo", 2, "sold_end_3_spn");
		endGuy[5] = h;
		Attack(h, user, 1);
	}

	if (objective3Complete && GetDistance(user, "nav_end") < 140.0f &&
		!rescue)
	{
		rescue = BZTRUE;

		BZHandle h;
		h = BuildObject("cspilo", 1, "rescue_1_spn", 200);
		h = BuildObject("cspilo", 1, "rescue_2_spn", 200);
		h = BuildObject("cspilo", 1, "rescue_3_spn", 200);
		h = BuildObject("cspilo", 1, "rescue_4_spn", 200);
		h = BuildObject("cspilo", 1, "rescue_5_spn", 200);
	}

	if (objective3Complete && snipersSpawned && GetDistance(user, "nav_end") < 50.0f && !won && !lost)
	{
		// make sure all the snipers are dead
		won = BZTRUE;
		for (i = 0; i < 6; i++)
		{
			if (IsAlive(endGuy[i]))
			{
				won = BZFALSE;
				break;
			}
		}

		if (won)
		{
			winSound = AudioMessage("ch07009.wav");

			ClearObjectives();
			if (objective1Complete)
				AddObjective("ch07001.otf", GREEN);
			else
				AddObjective("ch07001.otf", WHITE);
			if (burglarSequencePlayed)
				AddObjective(otf2[direction], GREEN);
			AddObjective("ch07003.otf", GREEN);
			AddObjective("ch07004.otf", GREEN);
		}
	}

	if (winSound != BZINVALIDHANDLE && IsAudioMessageDone(winSound))
	{
		winSound = BZINVALIDHANDLE;
		SucceedMission(GetTime() + 1.0f, "ch07win.des");
	}

	// check distances to ammo stuff
	if (ammo1 != BZINVALIDHANDLE && GetDistance(user, ammo1) < 5.0f)
	{
		if (GiveMaxAmmo(user))
		{
			ColorFade_SetFade(1.0f, 5.0f, 0, 255, 0);
			DoAudioNew("repair.wav", NULL, NULL);
			RemoveObject(ammo1);
			ammo1 = NULL;
		}
	}
	if (ammo2 != BZINVALIDHANDLE && GetDistance(user, ammo2) < 5.0f)
	{
		if (GiveMaxAmmo(user))
		{
			ColorFade_SetFade(1.0f, 5.0f, 0, 255, 0);
			DoAudioNew("repair.wav", NULL, NULL);
			RemoveObject(ammo2);
			ammo2 = NULL;
		}
	}
	if (repair1 != BZINVALIDHANDLE && GetDistance(user, repair1) < 5.0f)
	{
		if (GiveMaxHealth(user))
		{
			ColorFade_SetFade(1.0f, 5.0f, 0, 255, 0);
			DoAudioNew("repair.wav", NULL, NULL);
			RemoveObject(repair1);
			repair1 = NULL;
		}
	}
	if (repair2 != BZINVALIDHANDLE && GetDistance(user, repair2) < 5.0f)
	{
		if (GiveMaxHealth(user))
		{
			ColorFade_SetFade(1.0f, 5.0f, 0, 255, 0);
			DoAudioNew("repair.wav", NULL, NULL);
			RemoveObject(repair2);
			repair2 = NULL;
		}
	}
}

const std::set<PrjID>& Chinese07Mission::GetPreloadGameObjects()
{
	static std::set<PrjID> retval = AiMission::PrjIDFromStrings(
	{ "apcamr", "cspilo", "sssold", " ssusera", "svapca", "svapcb", "svfigh"
	"svturr", "svapcc", "svapcd", "svapce", "svapcf", "svapcg", "svapch",
	"svapci", "svapcj", "svapck", "svapcl", "svapcm", "svapcn", "svapco",
	"svapcp", "svapcs" }
	);
	return retval;
}
