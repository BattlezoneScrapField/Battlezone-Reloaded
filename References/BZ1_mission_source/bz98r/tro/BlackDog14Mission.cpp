

#include "AiMission.h"
#include "ScriptUtils.h"
#include "AudioMessage.h"

/*
	BlackDog14Mission
*/

class BlackDog14Mission : public AiMission {
	DECLARE_RTIME(BlackDog14Mission)
public:
	BlackDog14Mission();
	~BlackDog14Mission();

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

				// attacks
				attack1, attack2,

				// have we won/lost?
				wonLost,

				b_last;
		};
		bool b_array[11];
	};

	// floats
	union {
		struct {
			float
				initialTime,
				sound2Time,
				sound3Time,
				sound4Time,
				wavesTime,
				scavTime,
				f_last;
		};
		float f_array[6];
	};

	// handles
	union {
		struct {
			BZHandle
				// *** User stuff
				user,
				lastUser,
				
				// *** Units
				recycler,
				chinRecycler,
				apc,
				
				// nav beacons
				
				h_last;
		};
		BZHandle h_array[5];
	};

	// integers
	union {
		struct {
			int32_t
				// *** Sounds
				sound1,
				sound6,
				sound7,
				sound8,
				
				i_last;
		};
		int32_t i_array[4];
	};
};

IMPLEMENT_RTIME(BlackDog14Mission)

BlackDog14Mission::BlackDog14Mission()
{
}

BlackDog14Mission::~BlackDog14Mission()
{
}

bool BlackDog14Mission::Load(file fp)
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

bool BlackDog14Mission::PostLoad(void)
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

bool BlackDog14Mission::Save(file fp)
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

void BlackDog14Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

void BlackDog14Mission::AddObject(BZHandle h)
{
}

void BlackDog14Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

void BlackDog14Mission::Setup()
{
	int i = 0;
	startDone = BZFALSE;
	wonLost = BZFALSE;
	objective1Complete = BZFALSE;
	objective2Complete = BZFALSE;
	objective3Complete = BZFALSE;
	for (i = 0; i < 2; i++)
		cameraReady[i] = cameraComplete[i] = BZFALSE;
	attack1 = BZFALSE;
	attack2 = BZFALSE;
	
	// units
	user = NULL;
	lastUser = NULL;
	apc = NULL;
	recycler = GetHandle("recycler");
	chinRecycler = GetHandle("chin_recycler");
	
	// sounds
	sound1 = NULL;
	sound6 = NULL;
	sound7 = NULL;
	sound8 = NULL;
	
	// times
	initialTime = 999999.9f;
	sound2Time = 999999.9f;
	sound3Time = 999999.9f;
	sound4Time = 999999.9f;
	wavesTime = 999999.9f;
	scavTime = 999999.9f;
}


void BlackDog14Mission::Execute()
{
	int i = 0;
	lastUser = user;
	user = GetPlayerHandle(); //assigns the player a handle every frame

	// SOE #1
	if (!startDone)
	{
		SetAIP("bdmisn14.aip");
		SetScrap(1,4);
		SetPilot(1,10);
		SetScrap(2, 0);
		SetPilot(2, 100);

		// don't do this part after the first shot
		startDone = BZTRUE;

		sound1 = AudioMessage("bd14001.wav");

		initialTime = GetTime();

		// cloak some of the units
		SetCloaked(GetHandle("start1_1"));
		SetCloaked(GetHandle("start1_2"));
		SetCloaked(GetHandle("start1_3"));
		SetCloaked(GetHandle("start2_1"));
		SetCloaked(GetHandle("start2_2"));
		SetCloaked(GetHandle("start2_3"));
	}

	if (sound1 != BZINVALIDHANDLE && IsAudioMessageDone(sound1))
	{
		sound1 = BZINVALIDHANDLE;
	}

	if (initialTime < GetTime())
	{
		initialTime = 999999.9f;

		BZHandle h;
		h = BuildObject("cvfigh", 2, "spawn_initial_attack");
		SetCloaked(h);
		Goto(h, "path_initial_attack");
		h = BuildObject("cvfigh", 2, "spawn_initial_attack");
		SetCloaked(h);
		Goto(h, "path_initial_attack");
		h = BuildObject("cvfigh", 2, "spawn_initial_attack");
		SetCloaked(h);
		Goto(h, "path_initial_attack");
		h = BuildObject("cvhraz", 2, "spawn_initial_attack");
		SetCloaked(h);
		Goto(h, "path_initial_attack");
		h = BuildObject("cvhraz", 2, "spawn_initial_attack");
		SetCloaked(h);
		Goto(h, "path_initial_attack");

		ClearObjectives();
		AddObjective("bd14001.otf", WHITE);

		sound2Time = GetTime() + 120.0f;
		wavesTime = GetTime() + 240.0f;
	}

	// SOE #2
	if (sound2Time < GetTime())
	{
		sound2Time = 999999.9f;
		AudioMessage("bd14002.wav");
		ClearObjectives();
		AddObjective("bd14001.otf", WHITE);
		AddObjective("bd14002.otf", WHITE);
	}

	// SOE #3
	if (wavesTime < GetTime())
	{
		wavesTime = 999999.9f;

		BZHandle h;
		h = BuildObject("cvhtnk", 2, "spawn_attack_waves");
		SetCloaked(h);
		Goto(h, "path_attack_waves");
		h = BuildObject("cvhtnk", 2, "spawn_attack_waves");
		SetCloaked(h);
		Goto(h, "path_attack_waves");
		h = BuildObject("cvfigh", 2, "spawn_attack_waves");
		SetCloaked(h);
		Goto(h, "path_attack_waves");
		h = BuildObject("cvfigh", 2, "spawn_attack_waves");
		SetCloaked(h);
		Goto(h, "path_attack_waves");
		h = BuildObject("cvfigh", 2, "spawn_attack_waves");
		SetCloaked(h);
		Goto(h, "path_attack_waves");
		h = BuildObject("cvfigh", 2, "spawn_attack_waves");
		SetCloaked(h);
		Goto(h, "path_attack_waves");
		h = BuildObject("cvltnk", 2, "spawn_attack_waves");
		SetCloaked(h);
		Goto(h, "path_attack_waves");
		h = BuildObject("cvltnk", 2, "spawn_attack_waves");
		SetCloaked(h);
		Goto(h, "path_attack_waves");
		h = BuildObject("cvltnk", 2, "spawn_attack_waves");
		SetCloaked(h);
		Goto(h, "path_attack_waves");

		sound3Time = GetTime() + 5 * 60.0f;
	}

	// SOE #4 (missing) 

	// SOE #5
	if (sound3Time < GetTime())
	{
		sound3Time = 999999.9f;

		AudioMessage("bd14003.wav");

		BZHandle h;
		apc = BuildObject("cvapcc", 2, "spawn_apc");
		SetObjectiveOn(apc);
		Goto(apc, "path_apc_travel");
		h = BuildObject("cvtnk", 2, "spawn_apc");
		Defend2(h, apc);
		h = BuildObject("cvtnk", 2, "spawn_apc");
		Defend2(h, apc);
		h = BuildObject("cvtnk", 2, "spawn_apc");
		Defend2(h, apc);
		h = BuildObject("cvtnk", 2, "spawn_apc");
		Defend2(h, apc);

		// attackers
		h = BuildObject("cvhraz", 2, "spawn_attack_waves");
		SetCloaked(h);
		Goto(h, "path_attack_waves");
		h = BuildObject("cvhraz", 2, "spawn_attack_waves");
		SetCloaked(h);
		Goto(h, "path_attack_waves");
		h = BuildObject("cvhraz", 2, "spawn_attack_waves");
		SetCloaked(h);
		Goto(h, "path_attack_waves");
		h = BuildObject("cvhraz", 2, "spawn_attack_waves");
		SetCloaked(h);
		Goto(h, "path_attack_waves");
		h = BuildObject("cvltnk", 2, "spawn_attack_waves");
		SetCloaked(h);
		Goto(h, "path_attack_waves");
		h = BuildObject("cvltnk", 2, "spawn_attack_waves");
		SetCloaked(h);
		Goto(h, "path_attack_waves");
		h = BuildObject("cvltnk", 2, "spawn_attack_waves");
		SetCloaked(h);
		Goto(h, "path_attack_waves");
		h = BuildObject("cvltnk", 2, "spawn_attack_waves");
		SetCloaked(h);
		Goto(h, "path_attack_waves");
		BZHandle w1 = BuildObject("cvwalk", 2, "spawn_attack_waves");
		SetCloaked(h);
		Goto(w1, "path_attack_waves");
		BZHandle w2 = BuildObject("cvwalk", 2, "spawn_attack_waves");
		SetCloaked(h);
		Goto(w2, "path_attack_waves");
		BZHandle w3 = BuildObject("cvwalk", 2, "spawn_attack_waves");
		SetCloaked(h);
		Goto(w3, "path_attack_waves");
		h = BuildObject("cvtnkc", 2, "spawn_attack_waves");
		Follow(h, w1);
		h = BuildObject("cvtnkc", 2, "spawn_attack_waves");
		Follow(h, w2);
		h = BuildObject("cvtnkc", 2, "spawn_attack_waves");
		Follow(h, w3);
		

		sound4Time = GetTime() + 50.0f;
	}

	// SOE #6
	if (sound4Time < GetTime())
	{
		sound4Time = 999999.9f;
		if(IsAlive(apc))
		   {
			   AudioMessage("bd14004.wav");
		   }
	}

	// SOE #7
	if (!objective2Complete && apc != BZINVALIDHANDLE && GetHealth(apc) <= 0.0)
	{
		SetObjectiveOff(apc);
		objective2Complete = BZTRUE;

		AudioMessage("bd14005.wav");

		ClearObjectives();
		AddObjective("bd14002.otf", GREEN);
		AddObjective("bd14003.otf", WHITE);

		scavTime = GetTime() + 4 * 60.0f;
	}

	if (scavTime < GetTime())
	{
		scavTime = 999999.9f;

		BuildObject("cvscav", 2, "spawn_scav");
		BuildObject("cvscav", 2, "spawn_scav");
	}

	// SOE #8
	if (!objective3Complete && GetHealth(chinRecycler) <= 0.0 && !wonLost)
	{
		wonLost = BZTRUE;
		objective3Complete = BZTRUE;

		ClearObjectives();
		AddObjective("bd14002.otf", GREEN);
		AddObjective("bd14003.otf", GREEN);

		sound6 = AudioMessage("bd14006.wav");
	}

	if (sound6 != BZINVALIDHANDLE && IsAudioMessageDone(sound6))
	{
		sound6 = BZINVALIDHANDLE;
		SucceedMission(GetTime(), "bd14win.des");
	}

	// SOE #9
	if (!objective3Complete && isAtEndOfPath(apc, "path_apc_travel") && !wonLost)
	{
		wonLost = BZTRUE;
		sound7 = AudioMessage("bd14007.wav");

		ClearObjectives();
		AddObjective("bd14001.otf", RED);
		AddObjective("bd14002.otf", RED);
	}

	if (sound7 != BZINVALIDHANDLE && IsAudioMessageDone(sound7))
	{
		sound7 = BZINVALIDHANDLE;
		FailMission(GetTime(), "bd14lsea.des");
	}

	// SOE #10
	if (GetHealth(recycler) <= 0.0 && !wonLost)
	{
		wonLost = BZTRUE;
		sound8 = AudioMessage("bd14008.wav");
	}

	if (sound8 != BZINVALIDHANDLE && IsAudioMessageDone(sound8))
	{
		sound8 = BZINVALIDHANDLE;
		FailMission(GetTime(), "bd14lseb.des");
	}

	if (!attack1 && GetDistance(user, "trigger_attack_1") < 150.0)
	{
		attack1 = BZTRUE;

		for (i = 0; i < 4; i++)
		{
			BZHandle h = BuildObject("cvhraz", 2, "spawn_attack_1");
			Goto(h, "path_attack_1");
			SetCloaked(h);
		}
		for (i = 0; i < 4; i++)
		{
			BZHandle h = BuildObject("cvltnk", 2, "spawn_attack_1");
			Goto(h, "path_attack_1");
			SetCloaked(h);
		}
		for (i = 0; i < 2; i++)
		{
			BZHandle h = BuildObject("cvwalk", 2, "spawn_defend");
			Goto(h, "path_defend");
		}
		for (i = 0; i < 5; i++)
		{
			BZHandle h = BuildObject("cvltnk", 2, "spawn_defend");
			Goto(h, "path_defend");
		}
	}

	if (!attack2 && GetDistance(user, "trigger_attack_2") < 150.0)
	{
		attack2 = BZTRUE;

		for (i = 0; i < 6; i++)
		{
			BZHandle h = BuildObject("cvhraz", 2, "spawn_attack_2");
			Goto(h, "path_attack_2");
			SetCloaked(h);
		}
	}
}

const std::set<PrjID>& BlackDog14Mission::GetPreloadGameObjects()
{
	static std::set<PrjID> retval = AiMission::PrjIDFromStrings(
	{ "cvfigh", "cvhraz", "cvhtnk", "cvltnk", "cvapcc", 
	"cvtnk", "cvwalk", "cvtnkc", "cvscav" }
	);
	return retval;
}
