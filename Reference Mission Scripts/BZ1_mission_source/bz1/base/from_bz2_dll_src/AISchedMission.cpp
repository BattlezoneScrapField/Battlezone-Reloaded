#include "GameCommon.h" //"..\fun3d\GameCommon.h"

class EmptyMission : public AiMission {
	DECLARE_RTIME(EmptyMission)
public:
	EmptyMission(void);
	~EmptyMission();

	void Update(void);
};

static class EmptyMissionClass : AiMissionClass {
public:
	EmptyMissionClass(char *name) : AiMissionClass(name)
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
		return new EmptyMission;
	}
} EmptyMissionClass("empty");

IMPLEMENT_RTIME(EmptyMission)

EmptyMission::EmptyMission(void)
{
}

EmptyMission::~EmptyMission()
{
}

void EmptyMission::Update(void)
{
	AiMission::Update();
}
