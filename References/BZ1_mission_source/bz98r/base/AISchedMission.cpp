#include "AiMission.h"
#include "strhelp.h"
#include <string>

class EmptyMission : public AiMission {
	DECLARE_RTIME(EmptyMission)
public:
	EmptyMission(void);
	~EmptyMission();

	virtual void Update(void) override;
	virtual const std::set<std::string>& GetPreloadSet() override;
};

static class EmptyMissionClass : AiMissionClass {
public:
	EmptyMissionClass(const char *name) : AiMissionClass(name)
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

const std::set<std::string>& EmptyMission::GetPreloadSet()
{
	static std::set<std::string> retval = {};
	return retval;
}
