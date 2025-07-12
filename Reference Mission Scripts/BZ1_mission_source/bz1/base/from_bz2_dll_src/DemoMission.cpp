#include "GameCommon.h"

#include "..\fun3d\PowerUp.h"
#include "..\fun3d\ScriptUtils.h"

#include "..\terrain\terrain.h"


extern void QuickExit(void);

/*
DemoMission
*/

// used by (misn01.bzn) as first training mission

#include "..\fun3d\AiMission.h"

class DemoMission : public AiMission {
	DECLARE_RTIME(DemoMission)
public:
	DemoMission(void);
	~DemoMission();
	
	virtual bool Load(file fp);
	virtual bool PostLoad(void);
	virtual bool Save(file fp);
	
	virtual void Update(void);
	
	void Setup(void);
	void Execute(void);
	
private:
	// bools
	union {
		struct {
			bool
				camera1,
				camera2,
				start_done,
				hop_in,
				first_objective,
				second_objective,
				third_objecitve,
				combat_start,
				combat_start2,
				start_path1,
				start_path2,
				start_path3,
				start_path4,
				hint1,
				hint2,
				done_message,
				jump_start,
				lost,
				first_start,
				b_last;
		};
		bool b_array[19];
	};
	
	// floats
	union {
		struct {
			float
				camera_time,
				repeat_time,
				forgiveness,
				jump_done,
				time,
				cycle_time,
				f_last;
		};
		float f_array[5];
	};
	
	// object handles
	union {
		struct {
			Handle
				get_in_me,
				target,
				target2,
				foe1,
				foe2,
				foe3,
				foe4,
				friend1,
				art1,
				build1,
				build2,
				build3,
				build4,
				build5,
				build6,
				build7,
				build8,
				h_last;
		};
		Handle h_array[12];
	};
	
	// path pointers
	union {
		struct {
			AiPath
				*p1,
				*p2,
				*p3,
				*p4,
				*p_last;
		};
		AiPath *p_array[4];
	};
	
	// integers
	union {
		struct {
			int
				cycle_count,
				frame_count,
				angle,
				aud,
				num_reps,
				on_point,
				i_last;
		};
		int i_array[5];
	};
};

IMPLEMENT_RTIME(DemoMission)

static class DemoMissionClass : AiMissionClass {
public:
	DemoMissionClass(char *name) : AiMissionClass(name)
	{
	}
	int Matches(char *matches)
	{
		if (strcmp(matches, name) == 0)
			return TRUE;
		if (strcmp(matches, "demo") == 0)
			return TRUE;
		return FALSE;
	}
	AiMission *Build(void)
	{
		return new DemoMission;
	}
} DemoMissionClass("demo01");

DemoMission::DemoMission(void)
{
}

DemoMission::~DemoMission()
{	
}

bool DemoMission::Load(file fp)
{
	if (missionSave) {
		Setup();
		return AiMission::Load(fp);
	}
	
	bool ret = true;
	
	// bools
	int b_count = &b_last - b_array;
	_ASSERTE(b_count == SIZEOF(b_array));
	ret = ret && in(fp, b_array, sizeof(b_array));
	
	// floats
	int f_count = &f_last - f_array;
	_ASSERTE(f_count == SIZEOF(f_array));
	ret = ret && in(fp, f_array, sizeof(f_array));
	
	// Handles
	int h_count = &h_last - h_array;
	_ASSERTE(h_count == SIZEOF(h_array));
	ret = ret && in(fp, h_array, sizeof(h_array));
	
	// path pointers
	int p_count = &p_last - p_array;
	_ASSERTE(p_count == SIZEOF(p_array));
	for (int i = 0; i < p_count; i++)
		ret = ret && in_ptr(fp, (void **)&p_array[i], sizeof(p_array[0]), "p_array", this);
	
	// ints
	int i_count = &i_last - i_array;
	_ASSERTE(i_count == SIZEOF(i_array));
	ret = ret && in(fp, i_array, sizeof(i_array));
	
	ret = ret && AiMission::Load(fp);
	return ret;
}

bool DemoMission::PostLoad(void)
{
	if (missionSave)
		return AiMission::PostLoad();
	
	bool ret = true;
	
	int h_count = &h_last - h_array;
	for (int i = 0; i < h_count; i++)
		h_array[i] = ConvertHandle(h_array[i]);
	
	ret = ret && AiMission::PostLoad();
	
	return ret;
}

bool DemoMission::Save(file fp)
{
	if (missionSave)
		return AiMission::Save(fp);
	
	bool ret = true;
	
	// bools
	int b_count = &b_last - b_array;
	_ASSERTE(b_count == SIZEOF(b_array));
	ret = ret && out(fp, b_array, sizeof(b_array), "b_array");
	
	// floats
	int f_count = &f_last - f_array;
	_ASSERTE(f_count == SIZEOF(f_array));
	ret = ret && out(fp, f_array, sizeof(f_array), "f_array");
	
	// Handles
	int h_count = &h_last - h_array;
	_ASSERTE(h_count == SIZEOF(h_array));
	ret = ret && out(fp, h_array, sizeof(h_array), "h_array");
	
	// path pointers
	int p_count = &p_last - p_array;
	_ASSERTE(p_count == SIZEOF(p_array));
	for (int i = 0; i < p_count; i++)
		ret = ret && out_ptr(fp, (void **)&p_array[i], sizeof(p_array[0]), "p_array");
	
	// ints
	int i_count = &i_last - i_array;
	_ASSERTE(i_count == SIZEOF(i_array));
	ret = ret && out(fp, i_array, sizeof(i_array), "i_array");
	
	ret = ret && AiMission::Save(fp);
	return ret;
}

void DemoMission::Update(void)
{
	AiMission::Update();
	Execute();
}

void DemoMission::Setup(void)
{
	camera1=false;
	camera2=false;
	angle=3;
	camera_time=-99999.0f;
	lost=false;
	first_start=false;
	
	cycle_count=0;
	start_done=false;
	frame_count=0;
}

#define MOVE_TOP 98568.0f
#define MOVE_LEFT 4142.0f
#define MOVE_RIGHT 4989.0f
#define MOVE_BOTTOM 97327.0f

static float moveX = MOVE_LEFT;
static float moveZ = MOVE_TOP;

static void MoveObject(GameObject *o)
{
	float height;
	Terrain_GetHeightAndNormal(moveX, moveZ, &height, NULL);
	VECTOR_3D pos = { moveX, height + 10.0f, moveZ };
	o->SetOrigin(pos);
	o->SetTeam(3);
	switch (o->GetClass()->class_id) {
	case CLASS_ID_PERSON:
	case CLASS_ID_VEHICLE:
	case CLASS_ID_HELICOPTER:
		{
			AiProcess *process = o->GetAIProcess();
			delete process;
		}
		break;
	}
	moveX += (MOVE_RIGHT - MOVE_LEFT) / 50.0f;
	if (moveX > MOVE_RIGHT) {
		moveX = MOVE_LEFT;
		moveZ += (MOVE_BOTTOM - MOVE_TOP) / 50.0f;
	}
}

static bool MovedObject(GameObject *o)
{
	return (o->GetTeam() == 3);
}

static void KillStuff(void)
{
	GameObject *user = GameObject::GetUser();
	ObjectList::iterator i;
	ObjectList &list = *GameObject::objectList;
	for (i = list.begin(); i != list.end(); i++)
	{
		GameObject *o = *i;
		if (o == user)
			continue;
		if (o == NULL)
			continue;
		if (o->flags & OBJ_GAMEFLAG_DESTROYED)
			continue;
		switch (o->GetSeqNo()) {
		case 5:
		case 6:
		case 7:
		case 8:
			continue;
		}
		if (!MovedObject(o))
		{
			o->SetTeam(3);
			o->Remove();
			i = list.begin();
		}
	}
}

void DemoMission::Execute(void)
{
	
	frame_count++;
	GameObject *userObj = GameObject::GetUser();
	// spawn_point go_path
	
	if (!start_done)
	{
		
		int flags = 0;
		cycle_time=GetTime();
		if (!first_start)
		{
			first_start=true;
			time=GetTime();
			CameraReady();
		}
		StartProfiler(flags);
		target=BuildObject("avdemo",1,"spawn_point");
		Goto(target,"go_path");
		start_done=true;
		camera1=true;
		foe1=BuildObject("svhraz",2,"foe1");  // foe1 foe2 foe3
		foe2=BuildObject("svltnk",2,"foe2");
		foe3=BuildObject("svltnk",2,"foe2");
		foe4=BuildObject("svrckt",2,"foe2");
		friend1=BuildObject("avhraz",1,"friend1");
		art1=BuildObject("avartl",1,"art1");
		build1=BuildObject("sbcomm",2,"build1");
		build2=BuildObject("sbspow",2,"build2");
		build3=BuildObject("sbhang",2,"build3");
		build4=BuildObject("sblpow",2,"build4");
		build5=BuildObject("sbhqcp",2,"build5");
		build6=BuildObject("sbwpow",2,"build6");
		build7=BuildObject("sbwpow",2,"build7");
		build8=BuildObject("sbwpow",2,"build8");
		Goto(foe1,build1);
		Goto(foe2,build1);
		Goto(foe3,build1);
		Goto(foe4,build1);
		Follow(friend1,target);
		
	}
	if (camera1)
	{
		GameObject *targetObj=GameObjectHandle::GetObj(target);
		VECTOR_3D userPos = userObj->GetPosition();
		VECTOR_3D targetPos = targetObj->GetPosition();
		switch (angle) {
		case 0:
			CameraObject(target,0,800,-1500,target);
			break;
		case 1:
			CameraObject(target,-1500,800,0,target);
			break;
		case 2:
			CameraObject(target,0,800,1500,target);
			break;
		}
		if (GetTime()>camera_time)
		{
			camera_time=GetTime()+7.0f;
			angle=angle+1;
			if (angle>2)
			{
				angle=0;
			}
		}
		
		
		if (GetDistance(foe1,target)<200.0f)
		{
			camera1=false;
			camera2=true;
			Attack(art1,foe1);
		}
		if (GetTime()>camera_time)
		{
			camera_time=GetTime()+7.0f;
			angle=angle+1;
			if (angle>2)
			{
				angle=0;
			}
		}
	}
	if (camera2)
	{
		if (IsAlive(build2)) {
			Damage(build2,50);
		}
		switch (angle)
		{
		case 0:
			CameraPath("camera1",1000,0,target);
			break;
		case 1:
			if (IsAlive(foe1))
			{	
				CameraObject(target,-600,400,0,foe1);
			}	
			else
				if (IsAlive(foe2)) CameraObject(target,-600,400,0,foe2);
				break;
		}
		if (GetTime()>camera_time)
		{
			camera_time=GetTime()+7.0f;
			angle=angle+1;
			if (angle>1)
			{
				angle=0;
			}
		}
		
	}
	if ((!IsAlive(target)) || (GetTime()>cycle_time+55.0f))
	{
		cycle_count++;
		if  (cycle_count>4) //(!EndProfiler(flags))
		{
			if (!lost)
			{
				FILE *fd=fopen("addon\\bzbench.des","w+");
				fprintf(fd,"Battlezone Benchmark Test \n\n");
				float tottime=GetTime()-time;
				fprintf(fd,"Total time : %f \n",tottime);
				fprintf(fd,"Average frame rate : %f \n\n",frame_count/tottime);
				fprintf(fd,"This benchmark was created by George Collins.\n");
				fclose(fd);
				// SucceedMission(GetTime()+1.0f,"bzbench.des");
				lost=true;
				QuickExit();
			}	
		}
		else 
		{
			// kill everything and restart
#if 1
			KillStuff();
#else
			if (IsAlive(foe1))	RemoveObject(foe1);
			if (IsAlive(foe2)) RemoveObject(foe2);
			if (IsAlive(foe3)) RemoveObject(foe3);
			if (IsAlive(foe4)) RemoveObject(foe4);
			if (IsAlive(build1)) RemoveObject(build1);
			if (IsAlive(build2)) RemoveObject(build2);
			if (IsAlive(build3)) RemoveObject(build3);
			if (IsAlive(build4)) RemoveObject(build4);
			if (IsAlive(build5)) RemoveObject(build5);
			if (IsAlive(build6)) RemoveObject(build6);
			if (IsAlive(build7)) RemoveObject(build7);
			if (IsAlive(build8)) RemoveObject(build8);
			if (IsAlive(art1)) RemoveObject(art1);
#endif
			start_done=false;
			camera1=false;
			camera2=false;
		}
		
	}
	
 }
 
