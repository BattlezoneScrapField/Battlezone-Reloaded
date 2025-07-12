#include "GameCommon.h"

#include "..\fun3d\Inst02Mission.h"

/*
	Inst02Mission
*/


static class Inst02MissionClass : AiMissionClass {
public:
	Inst02MissionClass(char *name) : AiMissionClass(name)
	{
	}
	int Matches(char *matches)
	{
		if (strcmp(matches, name) == 0)
			return TRUE;
		if (strcmp(matches, "inst02") == 0)
			return TRUE;
		if (strcmp(matches, "inst03") == 0)
			return TRUE;
		if (strcmp(matches, "inst04") == 0)
			return TRUE;
		if (strcmp(matches, "inst05") == 0)
			return TRUE;
		if (strcmp(matches, "inst06") == 0)
			return TRUE;
		if (strcmp(matches, "inst07") == 0)
			return TRUE;
		if (strcmp(matches, "inst08") == 0)
			return TRUE;
		if (strcmp(matches, "test") == 0)
			return TRUE;
		if (strcmp(matches, "test01") == 0)
			return TRUE;
		if (strcmp(matches, "test02") == 0)
			return TRUE;
		if (strcmp(matches, "test03") == 0)
			return TRUE;
	
		return FALSE;
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
