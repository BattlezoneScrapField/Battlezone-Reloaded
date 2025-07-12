#include "GameCommon.h"

#include "..\fun3d\AiMission.h"
#include "..\fun3d\PowerUp.h"
#include "..\fun3d\ScriptUtils.h"
#include "..\fun3d\ParameterDB.h"
#include "..\worldldr\zfsaux.h"

extern char msn_filename[MAX_ASSETNAME_SIZE];

/*
Inst4XMission - code for user built missions
*/

class Inst4XMission : public AiMission {
	DECLARE_RTIME(Inst4XMission)
public:
	Inst4XMission(void);
	~Inst4XMission();

	virtual bool Load(file fp);
	virtual bool PostLoad(void);
	virtual bool Save(file fp);

	virtual void Update(void);

	virtual void AddObject(GameObject *gameObj);

private:
	void Setup(void);
	void AddObject(Handle h);
	void Execute(void);

	// bools
	union {
		struct {
			bool
				firstFrame, gameOver,
				b_last;
		};
		bool b_array[2];
	};

	// floats
	union {
		struct {
			float
				float_1,
				f_last;
		};
		float f_array[1];
	};

	// handles
	union {
		struct {
			Handle
				handle_1,
				h_last;
		};
		Handle h_array[1];
	};

	// integers
	union {
		struct {
			int
				int_1,
				i_last;
		};
		int i_array[1];
	};
};

void Inst4XMission::Setup(void)
{
	firstFrame = true;
	gameOver = false;
}

void Inst4XMission::AddObject(Handle h)
{
}

void Inst4XMission::Execute(void)
{
	if (firstFrame) {
		firstFrame = false;
		// set scrap / pilots
		char odf[14];
		memset(odf, 0, sizeof(odf));
		char *dot = strchr(msn_filename, '.');
		_ASSERT(dot != NULL);
		int len = dot - msn_filename;
		if (len > 8)
			len = 8;
		strncpy(odf, msn_filename, len);
		strcat(odf, ".odf");

		// open mission parameter file
		ParameterDB::Open(odf);

		// get mission parameters
		long myPilots;
		ParameterDB::GetLong(odf, "Mission", "myPilots", &myPilots, 0);
		long hisPilots;
		ParameterDB::GetLong(odf, "Mission", "hisPilots", &hisPilots, 30);
		long myScrap;
		ParameterDB::GetLong(odf, "Mission", "myScrap", &myScrap, 30);
		long hisScrap;
		ParameterDB::GetLong(odf, "Mission", "hisScrap", &hisScrap, 45);

		// close mission parameter file
		ParameterDB::Close(odf);

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
		if (!zixIsFileInIndex(odf)) {
			strcpy(odf, "misn14.aip");
		}
		SetAIP(odf);
	}
	// check end conditions
	Team &hisTeam = Team::GetTeam(2);
	if (
		!gameOver &&
		(hisTeam.FirstFilledSlot(TEAM_SLOT_RECYCLER, TEAM_SLOT_CONSTRUCT) == -1) &&
		(hisTeam.FirstFilledSlot(TEAM_SLOT_MIN_OFFENSE, TEAM_SLOT_MAX_OFFENSE) == -1) &&
		(hisTeam.FirstFilledSlot(TEAM_SLOT_MIN_DEFENSE, TEAM_SLOT_MAX_DEFENSE) == -1)
		)
	{
		gameOver = true;
		SucceedMission(Get_Time() + 5.0f);
	}
}

IMPLEMENT_RTIME(Inst4XMission)

Inst4XMission::Inst4XMission(void)
{
}

Inst4XMission::~Inst4XMission()
{
}

void Inst4XMission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

bool Inst4XMission::Load(file fp)
{
	if (missionSave) {
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

bool Inst4XMission::PostLoad(void)
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

bool Inst4XMission::Save(file fp)
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

void Inst4XMission::Update(void)
{
	AiMission::Update();
	Execute();
}

static class Inst4XMissionClass : AiMissionClass {
public:
	Inst4XMissionClass(char *name) : AiMissionClass(name)
	{
	}
	int Matches(char *matches)
	{
		if (strnicmp(matches, name, strlen(name)) == 0)
			return TRUE;
		return FALSE;
	}
	AiMission *Build(void)
	{
		return new Inst4XMission;
	}
} Inst4XMissionClass("UsrMsn");
