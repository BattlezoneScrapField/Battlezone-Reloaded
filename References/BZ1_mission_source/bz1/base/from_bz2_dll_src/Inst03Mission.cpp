#include "GameCommon.h"
#include "..\fun3d\GameObjectHandle.h"
#include "..\fun3d\SpawnPoint.h"
#include "..\fun3d\ScriptUtils.h"
#include "..\fun3d\UserProcess.h"

struct prup {
	int powerup;
	float time;
	float dt;
	char str[20];
	char odf[10];
	bool waiting;
};

class PlayEvent;

class Inst03Mission : public AiMission {
	DECLARE_RTIME(Inst03Mission)
public:
	Inst03Mission(void);
	~Inst03Mission();
	bool Load(file fp);
	bool Save(file fp);
	virtual void Init(void);
	virtual void Update(void);
	PlayEvent *playEvent;
};

#define INIT	0
#define RUN		1

class PlayEvent : public AiProcess {
	DECLARE_RTIME(PlayEvent)
public:
	PlayEvent(void);
	PlayEvent(AiMission *mission);
	void Execute(void);
private:
	int state;
	struct prup pup[100];
	int number;
};

IMPLEMENT_RTIME(PlayEvent)

PlayEvent::PlayEvent(void)
{
	_ASSERTE(false);
}

PlayEvent::PlayEvent(AiMission *mission): AiProcess(mission, NULL)
{
	state = INIT;

	AiPathList::iterator i;
	for (number = 0, i = AiPath::pathList.begin(); number < sizeof(pup) / sizeof(pup[0]) &&
		i != AiPath::pathList.end(); i++)
	{
		AiPath &curPath = **i;
		if (curPath.label == NULL)
			continue;
		strcpy(pup[number].str, curPath.label);
		strcpy(pup[number].odf, curPath.label);
		char *ptr = strchr(pup[number].odf, '_');
		if (ptr) *ptr = 0;
		ptr++;
		char tmp[20];
		strcpy(tmp, ptr);
		ptr = strchr(tmp, '_');
		if (ptr) *ptr = 0;
		int v = atoi(tmp);
		if (v > 0)
			pup[number].dt = (float) v;
		else
			pup[number].dt = 10.0f;
		number++;
	}
}

void PlayEvent::Execute(void)
{
	if (state == INIT)
	{
		state = RUN;
		for (int i = 0; i < number; i++)
		{
			GameObject *g;
			pup[i].powerup = BuildObject(pup[i].odf, 0, pup[i].str);
			g = GameObjectHandle::GetObj(pup[i].powerup);
			pup[i].waiting = false;
		}
	}
	else
	{
		for (int i = 0; i < number; i++)
		{
			if (0 == GameObjectHandle::GetObj(pup[i].powerup) && false == pup[i].waiting)
			{
				pup[i].waiting = true;
				pup[i].time = Get_Time() + pup[i].dt;
			}
			if (pup[i].waiting && Get_Time() > pup[i].time)
			{
				GameObject *g;
				pup[i].powerup = BuildObject(pup[i].odf, 0, pup[i].str);
				g = GameObjectHandle::GetObj(pup[i].powerup);
				pup[i].waiting = false;
			}
		}
	}
}

static class Inst03MissionClass : AiMissionClass {
public:
	Inst03MissionClass(char *name) : AiMissionClass(name)
	{
	}
	int Matches(char *matches)
	{
		if (strnicmp(matches, name, strlen(name)) == 0)
			return TRUE;
		if (strnicmp(matches, "play", strlen("play")) == 0)
			return TRUE;
		return FALSE;
	}
	AiMission *Build(void)
	{
		return new Inst03Mission;
	}
} Inst03MissionClass("play");

IMPLEMENT_RTIME(Inst03Mission)

Inst03Mission::Inst03Mission(void)
{
	playEvent = 0;
}


void Inst03Mission::Init(void)
{
}

Inst03Mission::~Inst03Mission()
{
}

bool Inst03Mission::Load(file fp)
{
	return AiMission::Load(fp);
}

bool Inst03Mission::Save(file fp)
{
	return AiMission::Save(fp);
}

void Inst03Mission::Update(void)
{
	if (0 == playEvent)
		playEvent = new PlayEvent(this);
	AiMission::Update();
}