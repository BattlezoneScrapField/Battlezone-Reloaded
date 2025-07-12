#include "GameCommon.h"

#include "..\fun3d\PowerUp.h"
#include "..\fun3d\ScriptUtils.h"

/*
	Misn01Mission
*/

// used by (misn01.bzn) as first training mission

#include "..\fun3d\AiMission.h"

class Misn01Mission : public AiMission {
	DECLARE_RTIME(Misn01Mission)
public:
	Misn01Mission(void);
	~Misn01Mission();

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
				b_last;
		};
		bool b_array[16];
	};

	// floats
	union {
		struct {
			float
				repeat_time,
				forgiveness,
				jump_done,
				f_last;
		};
		float f_array[3];
	};

	// object handles
	union {
		struct {
			Handle
				get_in_me,
				target,
				target2,
				h_last;
		};
		Handle h_array[3];
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
				aud,
				num_reps,
				on_point,
				i_last;
		};
		int i_array[3];
	};
};

IMPLEMENT_RTIME(Misn01Mission)

Misn01Mission::Misn01Mission(void)
{
}

Misn01Mission::~Misn01Mission()
{	
}

bool Misn01Mission::Load(file fp)
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

bool Misn01Mission::PostLoad(void)
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

bool Misn01Mission::Save(file fp)
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

void Misn01Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

void Misn01Mission::Setup(void)
{
	start_done=false;
	lost=false;
	first_objective=false;
	second_objective=false;
	third_objecitve=false;
	start_path1=false;
	start_path2=false;
	start_path3=false;
	start_path4=false;
	jump_start=false;
	hop_in=false;
	combat_start=false;
	combat_start2=false;
	hint1=false;
	hint2=false;
	done_message=false;
	repeat_time=0.0f;
	num_reps=0;
	forgiveness=40.0f;
}

void Misn01Mission::Execute(void)
{
	GameObject *player = GameObject::GetUser();
	Handle player_handle=GetPlayerHandle();
	VECTOR_2D player2d;
	if (IsAlive(player_handle)) player2d = Vec2D_From3D(player->GetPosition());
	if (!start_done)
	{
//		start_done=TRUE;
		get_in_me=GetHandle("avfigh0_wingman");
		aud=AudioMessage("misn0101.wav");
		p1=AiPath::Find("path_1");
		p2=AiPath::Find("path_2");
		p3=AiPath::Find("path_3");
		p4=AiPath::Find("path_5");
		target=GetHandle("svturr0_turrettank");
		target2=GetHandle("svturr1_turrettank");
		start_done=TRUE;
		repeat_time=Get_Time()+30.0f;
		ClearObjectives();
		AddObjective("misn0101.otf",WHITE);
		AddObjective("misn0103.otf",WHITE);
		num_reps=0;
	}

	GameObject *first = GameObjectHandle::GetObj(target);
	if ((!start_path1) && (Get_Time()>repeat_time))
	{
		repeat_time=Get_Time()+20.0f;
		ClearObjectives();
		AddObjective("misn0101.otf",GREEN);

		//		aud=AudioMessage("misn0101.wav");
		num_reps++;
	}
	if (!start_path1)		
	{
		// how far are we from the start..
		VECTOR_2D diff= Vec2D_Subtract(p1->points[0],player2d);
		if (Vec2D_Len(diff)<forgiveness)
		{
			// we've started
			if ((player_handle!=get_in_me)
				&& (!hop_in))
			{
				hop_in=true;
				StopAudioMessage(aud);
				AudioMessage("misn0122.wav");
			}
			else
			{
				ClearObjectives();
				AddObjective("misn0101.otf",GREEN);
				AddObjective("misn0103.otf",WHITE);

			}
			StartCockpitTimerUp(0,300,240);
			repeat_time=0.0f;
			num_reps=0;
			start_path1=TRUE;
			on_point=0;
		}
	}
	if ((start_path1) && (!start_path2) && (player_handle==get_in_me))
	{
		// are we out of range of current point?
		VECTOR_2D diff=Vec2D_Subtract(p1->points[on_point],player2d);
		float x=Vec2D_Len(diff);
		if ((Vec2D_Len(diff)>forgiveness) && (Get_Time()>repeat_time))
		{
			// tell player to get back where he was before
			AudioMessage("misn0103.wav");
			if ((!IsAlive(target)) &&
				(!IsAlive(target2)) && (!lost))
			{
				lost=true;
				FailMission(GetTime()+5.0f,"misn01l1.des");
			}
			repeat_time=Get_Time()+15.0f;
			num_reps++;
		}
		VECTOR_2D diff2=Vec2D_Subtract(p1->points[on_point+1],player2d);
		if (Vec2D_Len(diff2)<Vec2D_Len(diff))
		{
			// time to switch where we are on the path
			on_point++;
			if (on_point==p1->pointCount-1)
			{
				start_path2=TRUE;
				on_point=0;
			}
		}
	}
	if ((start_path2) && (!start_path3))
	{
		// are we out of range of current point?
		VECTOR_2D diff=Vec2D_Subtract(p2->points[on_point],player2d);
		float x=Vec2D_Len(diff);
		if ((Vec2D_Len(diff)>forgiveness) && (Get_Time()>repeat_time))
		{
			// tell player to get back where he was before
			AudioMessage("misn0103.wav");
			if ((!IsAlive(target)) &&
				(!IsAlive(target2)) && (!lost))
			{
				lost=true;
				FailMission(GetTime()+5.0f,"misn01l1.des");
			}
			repeat_time=Get_Time()+15.0f;
			num_reps++;
		}
		VECTOR_2D diff2=Vec2D_Subtract(p2->points[on_point+1],player2d);
		if (Vec2D_Len(diff2)<Vec2D_Len(diff))
		{
			// time to switch where we are on the path
			on_point++;
			if (on_point==p2->pointCount-1)
			{
				start_path3=TRUE;
				AudioMessage("misn0104.wav");
				on_point=0;
			}
		}
		
	}
	if ((start_path3) && (!jump_start))
	{
		// are we out of range of current point?
		VECTOR_2D diff=Vec2D_Subtract(p3->points[on_point],player2d);
		float x=Vec2D_Len(diff);
		if ((Vec2D_Len(diff)>forgiveness) && (Get_Time()>repeat_time))
		{
			// tell player to get back where he was before
			AudioMessage("misn0103.wav");
			if ((!IsAlive(target)) &&
				(!IsAlive(target2)) && (!lost))
			{
				lost=true;
				FailMission(GetTime()+5.0f,"misn01l1.des");
			}
			repeat_time=Get_Time()+15.0f;
			num_reps++;
		}
		VECTOR_2D diff2=Vec2D_Subtract(p3->points[on_point+1],player2d);
		if (Vec2D_Len(diff2)<Vec2D_Len(diff))
		{
			// time to switch where we are on the path
			on_point++;
			if (on_point==p3->pointCount-1)
			{
				jump_start=TRUE;
				jump_done=Get_Time()+8.0f;
			}
		}
		
	}
	if ((jump_start) && (!hint1) && (Get_Time()>jump_done))
	{

		repeat_time=Get_Time()+45.0f;  // grace period to continue
		AudioMessage("misn0105.wav");
		forgiveness=forgiveness*1.5f;  // for the jumps you'll need it
		AudioMessage("misn0107.wav");
		hint1=TRUE;
	}
	if (!start_path4)		
	{
		// how far are we from the start..
		VECTOR_2D diff= Vec2D_Subtract(p4->points[0],player2d);
		if (Vec2D_Len(diff)<forgiveness)
		{
			// we've started
			repeat_time=0.0f;
			num_reps=0;
			start_path4=TRUE;
			on_point=0;
			/*
				In case the player is
				developmentally 
				disabled.
			*/
			if (player_handle!=get_in_me)
			{
					AudioMessage("misn0122.wav");
			}
		}

	}
	if ((start_path4) && (!combat_start))
	{
		// are we out of range of current point?
		VECTOR_2D diff=Vec2D_Subtract(p4->points[on_point],player2d);
		float x=Vec2D_Len(diff);
		if ((Vec2D_Len(diff)>forgiveness) && (Get_Time()>repeat_time))
		{
			// tell player to get back where he was before
			AudioMessage("misn0108.wav");
			repeat_time=Get_Time()+15.0f;
			num_reps++;
		}
		VECTOR_2D diff2=Vec2D_Subtract(p4->points[on_point+1],player2d);
		if (Vec2D_Len(diff2)<Vec2D_Len(diff))
		{
			// time to switch where we are on the path
			on_point++;
			if (on_point==p4->pointCount-1)
			{
				StopCockpitTimer();
				combat_start=TRUE;
				GameObject *second_obj=GameObjectHandle::GetObj(target);  
				second_obj->SetObjective(TRUE);
				second_obj->SetName("Combat Training");
				AudioMessage("misn0109.wav");
			}
		}
		
	}
	if ((combat_start) && (!hint2) && (IsAlive(target)))
	if  		
			(Dist3D_Squared(first->GetPosition(), player->GetPosition())
			< 100.0f * 100.0f)

	{
		HideCockpitTimer();
		AudioMessage("misn0111.wav");
		hint2=TRUE;
	}
		

	if ((!combat_start2) && 
		(!IsAlive(target)) && (IsAlive(target2)))
	{
		GameObject *second_obj=GameObjectHandle::GetObj(target2);  
		second_obj->SetObjective(TRUE);
		second_obj->SetName("Combat Training 2");
		AudioMessage("misn0113.wav");
		combat_start2=TRUE;
	}

	if ((!done_message) &&
		(!IsAlive(target))
		&& (!IsAlive(target2)))
	{
		AudioMessage("misn0121.wav");
		done_message=true;
		SucceedMission(GetTime()+10,"misn01w1.des");
	}
	if ((num_reps>4) && (!lost))
	{
		repeat_time=99999.0f;
		ClearObjectives();
		AddObjective("misn0102.otf",RED);
		AudioMessage("misn0123.wav");
		FailMission(GetTime()+10,"misn01l1.des");
		num_reps=0;
	}
}
