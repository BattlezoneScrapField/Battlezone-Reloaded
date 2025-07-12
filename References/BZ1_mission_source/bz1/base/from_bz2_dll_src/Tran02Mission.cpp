#include "GameCommon.h"

#include "..\fun3d\AiMission.h"
#include "..\fun3d\GameObjectHandle.h"
#include "..\fun3d\AiUtil.h"
#include "..\fun3d\PowerUp.h"
#include "..\fun3d\ScriptUtils.h"
#include "..\fun3d\ControlPanel.h"

/*
	Tran02Mission
*/

class Tran02Mission : public AiMission {
	DECLARE_RTIME(Tran02Mission)
public:
	Tran02Mission(void);
	~Tran02Mission();

	virtual bool Load(file fp);
	virtual bool PostLoad(void);
	virtual bool Save(file fp);

	virtual void Update(void);

	virtual void AddObject(GameObject *gameObj);

private:
	void Setup(void);
	void AddObject(Handle h);
	void Execute(void);

	// bools
	union {
		struct {
			bool
				lost,
				go_reminder,
				start_done,
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
				first_selection,
				second_selection,
				third_selection,
				thirda_selection,
				fourth_selection,
				fifth_selection,
				end_message,
				jump_start,
				b_last;
		};
		bool b_array[22];
	};

	// floats
	union {
		struct {
			float
				hint_delay,
				repeat_time,
				f_last;
		};
		float f_array[2];
	};

	// handles
	union {
		struct {
			Handle
				turret,
				pointer,
				haul1,
				haul2,
				h_last;
		};
		Handle h_array[4];
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
				num_reps,
				message,
				on_point,
				i_last;
		};
		int i_array[3];
	};
};


void Tran02Mission::Setup(void)
{
	lost=false;
	start_done=false;
	first_selection=false;
	second_selection=false;
	third_selection=false;
	fourth_selection=false;
	fifth_selection=false;
	first_objective=false;
	second_objective=false;
	third_objecitve=false;
	thirda_selection=false;
	start_path1=false;
	start_path2=false;
	start_path3=false;
	start_path4=false;
	jump_start=false;
	combat_start=false;
	combat_start2=false;
	end_message=false;
	go_reminder=false;
	hint1=false;
	hint2=false;
	turret=GetHandle("avturr-1_turrettank");
	pointer=GetHandle("nparr-1_i76building");
	haul1=GetHandle("avhaul-1_tug");
	haul2=GetHandle("avhaul19_tug");
	repeat_time=0.0f;
	num_reps=0;
	hint_delay=99999.0f;
	repeat_time=99999.0f;
	message=0;
}

// this is the handle thing brad made for me
void Tran02Mission::AddObject(Handle h)
{
}

float PlayReminder(float time,int message)
{
	float new_time=time;
	if (Get_Time()>time)
	{		
		new_time=Get_Time()+15.0f;
		switch (message)
		{
			case 1: AudioMessage("tran0202.wav");
				break;
			case 2: AudioMessage("tran0203.wav");
				break;
			case 3: AudioMessage("tran0204.wav");
				break;
			case 4: AudioMessage("tran0211.wav");
				break;
			case 5: AudioMessage("tran0206.wav");
				break;
			case 6: AudioMessage("misn0109.wav");
				break;
			case 7: AudioMessage("tran0207.wav");
				break;
			case 8: AudioMessage("tran0208.wav");
					new_time=99999.0f;  // we're done
				break;
		}
	}
	return new_time;
}

void Tran02Mission::Execute(void)
{
	if (IsAlive(turret))
	{
		repeat_time=PlayReminder(repeat_time,message);
		if (!start_done)
		{
			GameObject *second_obj=GameObjectHandle::GetObj(turret);  
			second_obj->SetObjective(TRUE);
			second_obj->SetName("Turret");
			AudioMessage("tran0201.wav");
			hint_delay=Get_Time()+1.0f;
			ClearObjectives();
			AddObjective("tran0201.otf",GREEN);
			start_done=true;
		}
		if (Get_Time()>hint_delay)
		{
			// was
			// AudioMessage("tran0202.wav");
			AudioMessage("tran0204.wav"); 
			hint_delay=99999.0f;
			repeat_time=Get_Time()+30.0f;
			message=3;  // was 1
			// new 
			second_selection=true;
		}
		if ((!thirda_selection) &&
			(second_selection) &&
			(ControlPanel::GetCurrentItem()==2))
		{
			AudioMessage("tran0205.wav");
		//	AudioMessage("tran0211.wav");
			thirda_selection=true;
			repeat_time=Get_Time()+30.0f;
			message=4;
		}
	
		if ((!third_selection) &&
			(second_selection) &&
			(GameObjectHandle::GetObj(turret)->IsSelected()))
		{
			AudioMessage("tran0206.wav");
			GameObject *second_obj=GameObjectHandle::GetObj(turret);  
			second_obj->SetObjective(false);
			second_obj=GameObjectHandle::GetObj(pointer);  
			second_obj->SetObjective(true);
			second_obj->SetName("Target Range");
			third_selection=true;
			repeat_time=Get_Time()+30.0f;
			message=5;	
		}
		if ((third_selection) && (!go_reminder) &&
			(!GameObjectHandle::GetObj(turret)->IsSelected()))
		{
			AudioMessage("misn0109.wav"); // good job now head for the target range
			go_reminder=true;
			repeat_time=GetTime()+30.0f;
			message=6;
		}
		if ((third_selection) && 
			(!hint1) &&
			(Dist3D_Squared(GameObjectHandle::GetObj(pointer)->GetPosition(),
				GameObjectHandle::GetObj(turret)->GetPosition())
				< 100.0f * 100.0f))
		{
			AudioMessage("tran0207.wav");
			AudioMessage("tran0212.wav"); // press 2
			hint1=true;
			repeat_time=Get_Time()+30.0f;
			message=7;
		}
		if ((hint1) && (!hint2) &&
			(ControlPanel::GetCurrentItem()==2))
		{
			hint2=true;
			AudioMessage("tran0211.wav");  // press 1
			repeat_time=Get_Time()+20.0f;
			message=4;
		}
		if ((hint1) &&
			(!fourth_selection) &&
			(GameObjectHandle::GetObj(turret)->IsSelected()))
		{
			AudioMessage("tran0208.wav");
			fourth_selection=true;
			repeat_time=Get_Time()+30.0f;
			message=8;
		}
		if ((fourth_selection) &&
			(!fifth_selection) &&
			(GetCurrentCommand(turret)==CMD_GO))
		{
			repeat_time=99999.0f; // we're done repeating
			AudioMessage("tran0209.wav");	
			if (IsAlive(haul1))
			{
				AiCmdInfo info;
				info.what=CMD_GO;
				info.priority=1;  // so the computer doesn't interupt
				info.where=new AiPath(GameObjectHandle::GetObj(haul1)->GetPosition(),GameObjectHandle::GetObj(turret)->GetPosition());
			
				GameObjectHandle::GetObj(haul1)->SetCommand(info);
				GameObject *second_obj=GameObjectHandle::GetObj(pointer);  
				second_obj->SetObjective(false);
				second_obj=GameObjectHandle::GetObj(haul1);  
				second_obj->SetObjective(TRUE);
				second_obj->SetName("Target Drone");
			}
			else FailMission(GetTime()+2.0f,"tran02l1.des");
			fifth_selection=true;
		}
		if ((IsAlive(haul1)) && (GetCurrentCommand(haul1)==CMD_NONE))
		{
			AiCmdInfo info;
			info.what=CMD_GO;
			info.priority=1;  // so the computer doesn't interupt
			info.where=new AiPath(GameObjectHandle::GetObj(haul1)->GetPosition(),GameObjectHandle::GetObj(turret)->GetPosition());	
		}
		if ((fifth_selection) &&
			(!end_message) &&
			(GameObjectHandle::GetObj(haul1)==NULL))
		{
			AudioMessage("tran0210.wav");
			end_message=true;
			SucceedMission(GetTime()+10.0f,"tran02w1.des");
		}
	}
	else
	{
		if (!lost)
		{
			lost=true;
			FailMission(GetTime()+5.0f,"tran02l1.des");
		}
	}
}

IMPLEMENT_RTIME(Tran02Mission)

Tran02Mission::Tran02Mission(void)
{
}

Tran02Mission::~Tran02Mission()
{
}

void Tran02Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

bool Tran02Mission::Load(file fp)
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

bool Tran02Mission::PostLoad(void)
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

bool Tran02Mission::Save(file fp)
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

void Tran02Mission::Update(void)
{
	AiMission::Update();
	Execute();
}
