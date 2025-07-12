#include "LuaMission.h"
#include "PathSpawn.h"
#include "PowerUp.h"
#include "ScriptUtils.h"
#include "ParameterDB.h"
#include "TeamSlots.h"
#include "AudioMessage.h"
#include "strhelp.h"

extern "C" char msn_filename[MAX_ASSETNAME_SIZE];

/*
Inst4XMission - code for user built missions
*/

class Inst4XMission : public LuaMission {
	DECLARE_RTIME(Inst4XMission)
public:
	Inst4XMission(void);
	~Inst4XMission();

	virtual bool Load(file fp) override;
	virtual bool PostLoad(void) override;
	virtual bool Save(file fp) override;

	virtual void Start(void) override;
	virtual void Update(void) override;

	virtual void AddObject(GameObject *gameObj) override;

	virtual const std::set<std::string>& GetPreloadSet() override;
private:
	void Setup(void);
	void AddObject(BZHandle h);
	void Execute(void);

	PathSpawn *pathSpawn;

	// bools
	union {
		struct {
			bool
				firstFrame, gameOver, timerRunning,
				b_last;
		};
		bool b_array[3];
	};

	// floats
	union {
		struct {
			float
				float_1,
				timeLeft,
				f_last;
		};
		float f_array[2];
	};

	// handles
	union {
		struct {
			BZHandle
				handle_1, 
				h_last;
		

		};
		BZHandle h_array[1];
	};

	// integers
	union {
		struct {
			int32_t
				int_1,
				i_last;
		};
		int32_t i_array[1];
	};

	// other values
	const char* shellSuccess;		// shell success text named in ODF
	const char* shellFail;		// shell failure text named in ODF
	const char* missionObjective;	// OTF file named in ODF
	const char* startVoice;		//wave file that plays when mission is loaded
	long shellOutOfTime;	//shell success or failure number 0 is fail, 1 is success
	long failCondition;		// type of condition where player fails mission
	long successCondition;	// type of condition where player succeeds mission
	bool loaded;

};

void Inst4XMission::Setup(void)
{
	pathSpawn = new PathSpawn(this);
	firstFrame = true;
	gameOver = false;
	timeLeft = 0.0f;
	timerRunning = false;

	shellSuccess = "";		// shell success text named in ODF
	shellFail = "";			// shell failure text named in ODF
	missionObjective = "";	// OTF file named in ODF
	startVoice = "";		//wave file that plays when mission is loaded
	shellOutOfTime = 0;		//shell success or failure number 0 is fail, 1 is success
	failCondition = 0;		// type of condition where player fails mission
	successCondition = 0;	// type of condition where player succeeds mission
	loaded = true;
}

void Inst4XMission::AddObject(BZHandle h)
{
}

void Inst4XMission::Start(void)
{
	LuaMission::Start();

	if (loaded) {
		char odf[14];
		memset(odf, 0, sizeof(odf));
		char *dot = strchr(msn_filename, '.');
		assert(dot != NULL);
		int len = dot - msn_filename;
		if (len > 8)
			len = 8;
		strncpy(odf, msn_filename, len);
		strcat(odf, ".odf");		
		loaded = false;
		if (ItemExists(odf)) {
			ParameterDB p(odf);
			p.Get(0, 0x3986dd43 /* "startVoice" */, &startVoice, startVoice);
			p.Get(0, 0x2de2fe6c /* "missionObjective" */, &missionObjective, missionObjective);
			p.Get(0, 0x198af464 /* "shellSuccess" */, &shellSuccess, shellSuccess);
			p.Get(0, 0xc79eb669 /* "shellFail" */, &shellFail, shellFail);
			p.Get(0, 0x152e9876 /* "failCondition" */, &failCondition, failCondition);
			p.Get(0, 0x84d79505 /* "successCondition" */, &successCondition, successCondition);
			p.Get(0, 0xb4ef8667 /* "shellOutOfTime" */, &shellOutOfTime, shellOutOfTime);
		}
	}
	
	if (firstFrame) {
		firstFrame = false;
		// set scrap / pilots
		char odf[14];
		memset(odf, 0, sizeof(odf));
		char *dot = strchr(msn_filename, '.');
		assert(dot != NULL);
		int len = dot - msn_filename;
		if (len > 8)
			len = 8;
		strncpy(odf, msn_filename, len);
		strcat(odf, ".odf");
		long myPilots = 0;
		long hisPilots = 30;
		long myScrap = 30;
		long hisScrap = 45;
		if (ItemExists(odf)) {
			ParameterDB p(odf);
			p.Get(0, 0x8af01d94 /* "myPilots" */, &myPilots, myPilots);
			p.Get(0, 0xb2ce525c /* "hisPilots" */, &hisPilots, hisPilots);
			p.Get(0, 0xa5739020 /* "myScrap" */, &myScrap, myScrap);
			p.Get(0, 0xc4283588 /* "hisScrap" */, &hisScrap, hisScrap);
			p.Get(0, 0x1752b305 /* "timeLeft" */, &timeLeft, timeLeft);
		}

			
		// add pilots
		Team &myTeam = Team::GetTeam(1);
		long addMyPilots = myPilots - myTeam.GetMaxPilot();
		if (addMyPilots < 0)
			addMyPilots = 0;
		myTeam.AddMaxPilot(addMyPilots);
		myTeam.AddPilot(myPilots);
		Team &hisTeam = Team::GetTeam(2);
		long addHisPilots = hisPilots - hisTeam.GetMaxPilot();
		if (addHisPilots < 0)
			addHisPilots = 0;
		hisTeam.AddMaxPilot(addHisPilots);
		hisTeam.AddPilot(hisPilots);

		// add scrap
		long addMyScrap = myScrap - myTeam.GetMaxScrap();
		if (addMyScrap < 0)
			addMyScrap = 0;
		myTeam.AddMaxScrap(addMyScrap);
		myTeam.AddScrap(myScrap);
		long addHisScrap = hisScrap - hisTeam.GetMaxScrap();
		if (addHisScrap < 0)
			addHisScrap = 0;
		hisTeam.AddMaxScrap(addHisScrap);
		hisTeam.AddScrap(hisScrap);

		// load aip
		memset(odf, 0, sizeof(odf));
		strncpy(odf, msn_filename, len);
		strcat(odf, ".aip");
		if (!ItemExists(odf)) {
			strcpy(odf, "misn14.aip");
		}
		SetAIP(odf);
		if (startVoice[0])
			AudioMessage (startVoice);
		ClearObjectives ();
		AddObjective (missionObjective, WHITE);
	//create a timer
		if (timeLeft >= 0.1f)
		{
			StartCockpitTimer (long(timeLeft),45,15);
			timerRunning = true;
		}
	}
}

void Inst4XMission::Execute(void)
{
	// check end conditions
	Team &hisTeam = Team::GetTeam(2);
	// if no success condition is defined, entire soviet offense and defense must be killed
	if (
		!gameOver &&
		(hisTeam.FirstFilledSlot(TEAM_SLOT_RECYCLER, TEAM_SLOT_CONSTRUCT) == -1) &&
		(hisTeam.FirstFilledSlot(TEAM_SLOT_MIN_OFFENSE, TEAM_SLOT_MAX_OFFENSE) == -1) &&
		(hisTeam.FirstFilledSlot(TEAM_SLOT_MIN_DEFENSE, TEAM_SLOT_MAX_DEFENSE) == -1)
		)
	{
		gameOver = true;
		ClearObjectives ();
		AddObjective (missionObjective, GREEN);
		SucceedMission(Get_Time() + 5.0f, shellSuccess);
	}
	// if condition is 1 then only soviet recycler needs to be destroyed
	if (
		(successCondition == 1) &&
		(!gameOver) &&
		(hisTeam.FirstFilledSlot(TEAM_SLOT_RECYCLER, TEAM_SLOT_CONSTRUCT) == -1)
		)
	{
		gameOver = true;
		ClearObjectives ();
		AddObjective (missionObjective, GREEN);
		SucceedMission(Get_Time() + 5.0f, shellSuccess);
	}


	Team &myTeam = Team::GetTeam(1);
	// if fail condition is 1, and then if US recycler is destroyed, you lose
	if (
		(failCondition == 1) &&
		(!gameOver) &&
		(myTeam.FirstFilledSlot(TEAM_SLOT_RECYCLER, TEAM_SLOT_CONSTRUCT) == -1)
		)
	{
		gameOver = true;
		ClearObjectives ();
		AddObjective (missionObjective, RED);
		FailMission(Get_Time() + 5.0f, shellFail);
	}
	//the fail condition if you run out of time
	if (
		(!gameOver) &&
		(GetCockpitTimer() <= 0) &&
		(timerRunning == true) &&
		(shellOutOfTime == 0)
		)
	{
		gameOver = true;
		ClearObjectives ();
		AddObjective (missionObjective, RED);
		FailMission(Get_Time() + 5.0f, shellFail);
	}

	if (
		(!gameOver) &&
		(GetCockpitTimer() <= 0) &&
		(timerRunning == true) &&
		(shellOutOfTime == 1)
		)
	{
		gameOver = true;
		ClearObjectives ();
		AddObjective (missionObjective, GREEN);
		SucceedMission(Get_Time() + 5.0f, shellSuccess);
	}

}

IMPLEMENT_BASE_RTIME(Inst4XMission, LuaMission)

Inst4XMission::Inst4XMission(void)
{
	pathSpawn = NULL;
}

Inst4XMission::~Inst4XMission()
{
	delete pathSpawn;
}

void Inst4XMission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	LuaMission::AddObject(gameObj);
}

bool Inst4XMission::Load(file fp)
{
	if (missionSave) {
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
		return LuaMission::Load(fp);
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

	ret = ret && LuaMission::Load(fp);
	return ret;
}

bool Inst4XMission::PostLoad(void)
{
	if (missionSave)
		return LuaMission::PostLoad();

	bool ret = true;

	int h_count = &h_last - h_array;
	for (int i = 0; i < h_count; i++)
		h_array[i] = ConvertHandle(h_array[i]);

	ret = ret && LuaMission::PostLoad();

	return ret;
}

bool Inst4XMission::Save(file fp)
{
	if (missionSave)
		return LuaMission::Save(fp);

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

	ret = ret && LuaMission::Save(fp);
	return ret;
}

void Inst4XMission::Update(void)
{
	LuaMission::Update();
	Execute();
}

static class Inst4XMissionClass : AiMissionClass {
public:
	Inst4XMissionClass(const char *name) : AiMissionClass(name)
	{
	}
	int Matches(const char *matches)
	{
		if (strnicmp(matches, name, strlen(name)) == 0)
			return BZTRUE;
		return BZFALSE;
	}
	AiMission *Build(void)
	{
		return new Inst4XMission;
	}
} Inst4XMissionClass("UsrMsn");

const std::set<std::string>& Inst4XMission::GetPreloadSet()
{
	static std::set<std::string> retval = {};
	if (retval.empty()) return AiMission::GetPreloadSet();
	return retval;
}
