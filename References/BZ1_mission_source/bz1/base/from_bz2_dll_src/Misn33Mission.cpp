#include "GameCommon.h"

#include "Misn33Mission.h"
#include "ScavengerFriend.h"
#include "..\fun3d\ScriptUtils.h"

/*
	Misn33Mission
*/


class Misn33Event : public AiProcess {
	DECLARE_RTIME(Misn33Event)
public:
	Misn33Event(void);
	Misn33Event(AiMission *mission);
	void Execute(void);
	void AddObject(Handle h);
		
private:

};

IMPLEMENT_RTIME(Misn33Event)

Misn33Event::Misn33Event(void)
{
	_ASSERTE(false);
}

Misn33Event::Misn33Event(AiMission *mission) : AiProcess(mission,NULL)
{

	bDontSave=true;
}

// this is the handle thing brad made for me
void Misn33Event::AddObject(Handle h)
{

}

void Misn33Event::Execute(void)
{
}

static class Misn33MissionClass : AiMissionClass {
public:
	Misn33MissionClass(char *name) : AiMissionClass(name)
	{
	}
	int Matches(char *matches)
	{
		if (strcmp(matches, name) == 0)
			return TRUE;
		if (strcmp(matches, "Misn33a") == 0)
			return TRUE;
		if (strcmp(matches, "Misn33b") == 0)
			return TRUE;
		if (strcmp(matches, "Misn33c") == 0)
			return TRUE;
		if (strcmp(matches, "Misn33d") == 0)
			return TRUE;
		if (strcmp(matches, "Misn33e") == 0)
			return TRUE;
		if (strcmp(matches, "Misn33f") == 0)
			return TRUE;
		if (strcmp(matches, "Misn33g") == 0)
			return TRUE;
		return FALSE;
	}
	AiMission *Build(void)
	{
		return new Misn33Mission;
	}
} Misn33MissionClass("Misn33");

IMPLEMENT_RTIME(Misn33Mission)

Misn33Mission::Misn33Mission(void)
{
	event=new Misn33Event(this);
}

Misn33Mission::~Misn33Mission()
{
	
}

void Misn33Mission::AddObject(GameObject *gameObj)
{
	int objHandle = GameObjectHandle::Find(gameObj);
	((Misn33Event *)event)->AddObject(objHandle);
	AiMission::AddObject(gameObj);
}

bool Misn33Mission::Load(file fp)
{
	return AiMission::Load(fp);
}

bool Misn33Mission::Save(file fp)
{
	return AiMission::Save(fp);
}
