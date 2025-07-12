#include "GameCommon.h"

//
// AISchedule Mission
class MPMission : public AiMission {
public:
	MPMission(void);
	~MPMission();
	void Update(void);
};

//
// AISchedule Mission Class
//
static class MPMissionClass : AiMissionClass {
public:
	MPMissionClass(char *name) : AiMissionClass(name)
	{
	}
	int Matches(char *matches)
	{
		if (strcmp(matches, name) == 0)
			return TRUE;
		if (strcmp(matches, "mp") == 0)
			return TRUE;
		if (strcmp(matches, "bowlmp") == 0)
			return TRUE;
		if (strcmp(matches, "warmp") == 0)
			return TRUE;
		if (strcmp(matches, "test5") == 0)
			return TRUE;
		return FALSE;
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
