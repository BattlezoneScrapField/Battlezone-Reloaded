#include "AiMission.h"

//
// AISchedule Mission
class MPMission : public AiMission {
public:
	MPMission(void);
	~MPMission();
	void Update(void);
	virtual const std::set<std::string>& GetPreloadSet();
};

//
// AISchedule Mission Class
//
static class MPMissionClass : AiMissionClass {
public:
	MPMissionClass(const char *name) : AiMissionClass(name)
	{
	}
	int Matches(const char *matches)
	{
		if (strcmp(matches, name) == 0)
			return BZTRUE;
		if (strcmp(matches, "mp") == 0)
			return BZTRUE;
		if (strcmp(matches, "bowlmp") == 0)
			return BZTRUE;
		if (strcmp(matches, "warmp") == 0)
			return BZTRUE;
		if (strcmp(matches, "test5") == 0)
			return BZTRUE;
		return BZFALSE;
	}
	AiMission *Build(void) {
		return new MPMission();
	}
} mpMission("MP");

MPMission::MPMission(void)
{
}

MPMission::~MPMission()
{
}

void MPMission::Update(void)
{
	AiMission::Update();
}

const std::set<std::string>& MPMission::GetPreloadSet()
{
	static std::set<std::string> retval = {};
	if (retval.empty()) return AiMission::GetPreloadSet();
	return retval;
}
