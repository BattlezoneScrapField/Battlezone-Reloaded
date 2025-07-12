#include "GameObjectHandle.h"
#include "SpawnPoint.h"
#include "ScriptUtils.h"
#include "UserProcess.h"
#include "LuaMission.h"
#include "PathSpawn.h"
#include "strhelp.h"

class Inst03Mission : public LuaMission {
	DECLARE_RTIME(Inst03Mission)
public:
	Inst03Mission(void);
	~Inst03Mission();
	virtual bool Load(file fp) override;
	virtual bool Save(file fp) override;
	virtual void Init(void) override;
	virtual void Start(void) override;
	virtual void Update(void) override;
	virtual const std::set<std::string>& GetPreloadSet() override;
	PathSpawn *pathSpawn;
};

static class Inst03MissionClass : AiMissionClass {
public:
	Inst03MissionClass(const char *name) : AiMissionClass(name)
	{
	}
	int Matches(const char *matches)
	{
		if (strnicmp(matches, name, strlen(name)) == 0)
			return BZTRUE;
		if (strnicmp(matches, "play", strlen("play")) == 0)
			return BZTRUE;
		return BZFALSE;
	}
	AiMission *Build(void)
	{
		return new Inst03Mission;
	}
} Inst03MissionClass("play");

IMPLEMENT_RTIME(Inst03Mission)

Inst03Mission::Inst03Mission(void)
{
	pathSpawn = 0;
}


void Inst03Mission::Init(void)
{
}

Inst03Mission::~Inst03Mission()
{
}

bool Inst03Mission::Load(file fp)
{
	return LuaMission::Load(fp);
}

bool Inst03Mission::Save(file fp)
{
	return LuaMission::Save(fp);
}

void Inst03Mission::Start(void)
{
	LuaMission::Start();

	if ( pathSpawn == 0 )
	{
		pathSpawn = new PathSpawn(this);
	}
}

void Inst03Mission::Update(void)
{
	LuaMission::Update();
}

const std::set<std::string>& Inst03Mission::GetPreloadSet()
{
	static std::set<std::string> retval = {};
	if (retval.empty()) return AiMission::GetPreloadSet();
	return retval;
}
