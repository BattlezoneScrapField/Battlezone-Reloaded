
#include "Inst02Mission.h"

/*
	Inst02Mission
*/


static class Inst02MissionClass : AiMissionClass {
public:
	Inst02MissionClass(const char *name) : AiMissionClass(name)
	{
	}
	int Matches(const char *matches)
	{
		if (strcmp(matches, name) == 0)
			return BZTRUE;
		if (strcmp(matches, "inst02") == 0)
			return BZTRUE;
		if (strcmp(matches, "inst03") == 0)
			return BZTRUE;
		if (strcmp(matches, "inst04") == 0)
			return BZTRUE;
		if (strcmp(matches, "inst05") == 0)
			return BZTRUE;
		if (strcmp(matches, "inst06") == 0)
			return BZTRUE;
		if (strcmp(matches, "inst07") == 0)
			return BZTRUE;
		if (strcmp(matches, "inst08") == 0)
			return BZTRUE;
		if (strcmp(matches, "test") == 0)
			return BZTRUE;
		if (strcmp(matches, "test01") == 0)
			return BZTRUE;
		if (strcmp(matches, "test02") == 0)
			return BZTRUE;
		if (strcmp(matches, "test03") == 0)
			return BZTRUE;
	
		return BZFALSE;
	}
	AiMission *Build(void)
	{
		return new Inst02Mission;
	}
} Inst02MissionClass("inst02");

IMPLEMENT_RTIME(Inst02Mission)

Inst02Mission::Inst02Mission(void)
{
}

Inst02Mission::~Inst02Mission()
{
	
}

bool Inst02Mission::Load(file fp)
{
	return AiMission::Load(fp);
}

bool Inst02Mission::Save(file fp)
{
	return AiMission::Save(fp);
}

const std::set<std::string>& Inst02Mission::GetPreloadSet()
{
	static std::set<std::string> retval = {};
	if (retval.empty()) return AiMission::GetPreloadSet();
	return retval;
}
