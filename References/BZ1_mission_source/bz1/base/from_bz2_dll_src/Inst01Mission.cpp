#include "GameCommon.h"

#include "..\fun3d\Inst01Mission.h"
#include "..\fun3d\ScriptUtils.h"
#include "..\utility\SimCut.h"

class Inst01Event : public AiProcess {
	DECLARE_RTIME(Inst01Event)
public:
	Inst01Event(void);
	Inst01Event(AiMission *mission);
	virtual bool Load(file fp);
	virtual bool Save(file fp);
	void Execute(void);
private:
	/*
		Put your variable
		definitions here.
	*/
	AiPath *path;
	Handle pointa,pointb,player,base_handle;
	bool game_start,camera_start1,camera_start2;
};

IMPLEMENT_RTIME(Inst01Event)

Inst01Event::Inst01Event(void)
{
	_ASSERTE(false);
}

Inst01Event::Inst01Event(AiMission *mission): AiProcess(mission, NULL)
{
	bDontSave = true;
	game_start=false;		
	camera_start1=false;
	camera_start2=false;
}

bool Inst01Event::Load(file fp)
{
	return AiProcess::Load(fp);
}

bool Inst01Event::Save(file fp)
{
	return AiProcess::Save(fp);
}

void Inst01Event::Execute(void)
{
	if (!game_start)
	{
		SetScrap(1,5);
		SetScrap(2,40);
		SetAIP("inst01.aip");
		pointa=GetHandle("apdrop196_camerapod");
		pointb=GetHandle("apcamr-1_camerapod");
		player=GetHandle("player-1_hover");
		base_handle=GetHandle("eggeizr139_geyser");
		path=AiPath::Find("camera1");
		game_start=true;
		camera_start1=true;

		if (camera_start1)	fsm_push_camera();
//		AudioMessage("inst0101.wav");
	}

	
	if (camera_start1)
	{
		int height=3500;
		OBJ76 *target=GameObjectHandle::GetObj(player)->GetOBJ76();
		int speed=500;
		fsm_camera_trans_obj(path,&height,&speed,target);
		if (cameraIsArrived())
		{
			camera_start1=false;
			path=AiPath::Find("camera2");
			camera_start2=true;
		}
	}
	if (camera_start2)
	{

		int height=3500;
		OBJ76 *base=GameObjectHandle::GetObj(pointa)->GetOBJ76();
		OBJ76 *target=GameObjectHandle::GetObj(base_handle)->GetOBJ76();
		int i,j,k;
		i=0;  // right, x
		j=100; // height, y
		k=0;  // forward, z
		int speed=5000;
		fsm_camera_trans_obj(path,&height,&speed,target);
		if (cameraIsArrived())
		{
			camera_start2=false;
			fsm_pop_camera();
		}
	//	fsm_camera_obj_obj(target,&i,&j,&k,target);

	//	fsm_camera_pos_obj(path,&height,GameObjectHandle::GetObj(pointb)->GetOBJ76());
	//	fsm_push_camera();
	}

}
/*
	Inst01Mission
*/


static class Inst01MissionClass : AiMissionClass {
public:
	Inst01MissionClass(char *name) : AiMissionClass(name)
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
		return FALSE;
	}
	AiMission *Build(void)
	{
		return new Inst01Mission;
	}
} Inst01MissionClass("inst01");

IMPLEMENT_RTIME(Inst01Mission)

Inst01Mission::Inst01Mission(void)
{
		new Inst01Event(this);	
}

Inst01Mission::~Inst01Mission()
{

}

bool Inst01Mission::Load(file fp)
{
	return AiMission::Load(fp);
}

bool Inst01Mission::Save(file fp)
{
	return AiMission::Save(fp);
}
