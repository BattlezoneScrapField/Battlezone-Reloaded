#include "PowerUp.h"
#include "ScriptUtils.h"
#include "AudioMessage.h"
#include "touchbutton.h"

/*
	Misn01Mission
*/

// used by (misn01.bzn) as first training mission

#include "AiMission.h"

class Misn01Mission : public AiMission {
	DECLARE_RTIME(Misn01Mission)
public:
	Misn01Mission(void);
	~Misn01Mission();

	virtual bool Load(file fp) override;
	virtual bool PostLoad(void) override;
	virtual bool Save(file fp) override;

	virtual void Update(void) override;

	void Setup(void);
	void Execute(void);

	virtual const std::set<std::string>& GetPreloadSet() override;
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
			BZHandle
				get_in_me,
				target,
				target2,
				h_last;
		};
		BZHandle h_array[3];
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
			int32_t
				aud,
				num_reps,
				on_point,
				i_last;
		};
		int32_t i_array[3];
	};
};

IMPLEMENT_RTIME(Misn01Mission)

Misn01Mission::Misn01Mission(void)
{
	intptr_t p_count = &p_last - p_array;
	for (intptr_t i = 0; i < p_count; i++)
		p_array[i] = nullptr;
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
	ret = ret && in(fp, b_array, sizeof(b_array));

	// floats
	ret = ret && in(fp, f_array, sizeof(f_array));

	// Handles
	ret = ret && in(fp, h_array, sizeof(h_array));

	// path pointers
	size_t p_count = &p_last - p_array;
	for (size_t i = 0; i < p_count; i++)
		ret = ret && in_ptr(fp, (void **)&p_array[i], sizeof(p_array[0]), "Misn01Mission::p_array", this);

	// ints
	ret = ret && in(fp, i_array, sizeof(i_array));

	ret = ret && AiMission::Load(fp);
	return ret;
}

bool Misn01Mission::PostLoad(void)
{
	if (missionSave)
		return AiMission::PostLoad();

	bool ret = true;

	size_t h_count = &h_last - h_array;
	for (size_t i = 0; i < h_count; i++)
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
	ret = ret && out(fp, b_array, sizeof(b_array), "b_array");

	// floats
	int f_count = &f_last - f_array;
	assert(f_count == SIZEOF(f_array));
	ret = ret && out(fp, f_array, sizeof(f_array), "f_array");

	// Handles
	int h_count = &h_last - h_array;
	assert(h_count == SIZEOF(h_array));
	ret = ret && out(fp, h_array, sizeof(h_array), "h_array");

	// path pointers
	int p_count = &p_last - p_array;
	assert(p_count == SIZEOF(p_array));
	for (int i = 0; i < p_count; i++)
		ret = ret && out_ptr(fp, (void **)&p_array[i], sizeof(p_array[0]), "p_array");

	// ints
	int i_count = &i_last - i_array;
	assert(i_count == SIZEOF(i_array));
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
	BZHandle player_handle=GetPlayerHandle();
	VECTOR_2D player2d;
	if (IsAlive(player_handle)) player2d = Vec2D_From3D(player->GetPosition());
	if (!start_done)
	{
//		start_done=BZTRUE;
		get_in_me=GetHandle("avfigh0_wingman");
		float objDispTime=8.0f;
		if(InfoDisplay_ShouldShowTutorialText() == BZTRUE)
		{
			// We are asking user to hit brief, so don't show
			// it unless the user does so.  That way hitting brief
			// is SHOW and not HIDE
			objDispTime=0.0f;
			//aud=AudioMessage("misi0101.wav");
			InfoDisplay_Tutorial(IOS_TUT_WELCOME);
		}
		else
		{
			aud=AudioMessage("misn0101.wav");
		}
		p1=AiPath::Find("path_1");
		p2=AiPath::Find("path_2");
		p3=AiPath::Find("path_3");
		p4=AiPath::Find("path_5");
		target=GetHandle("svturr0_turrettank");
		SetPilotClass(target, "");
		target2=GetHandle("svturr1_turrettank");
		SetPilotClass(target2, "");
		start_done=BZTRUE;
		repeat_time=Get_Time()+30.0f;
		ClearObjectives();
		AddObjective("misn0101.otf",WHITE, objDispTime);
		AddObjective("misn0103.otf",WHITE, objDispTime);
		buttonSystem.TapNotifyOn("TOGGLE_OBJECTIVES_DISPLAY");

		num_reps=0;
	}

	GameObject *first = GameObjectHandle::GetObj(target);
	if ((!start_path1) && (Get_Time()>repeat_time))
	{
		repeat_time=Get_Time()+20.0f;
		UpdateObjective("misn0101.otf",first_objective?GREEN:WHITE);
		UpdateObjective("misn0103.otf",WHITE);
		num_reps++;
	}
	if (!start_path1)		
	{
		// how far are we from the start..
		VECTOR_2D diff= Vec2D_Subtract(p1->points[0],player2d);
		float dist = Vec2D_Len(diff);
		if (dist<forgiveness)
		{
			// we've started
			if ((player_handle!=get_in_me)
				&& (!hop_in))
			{
				hop_in=true;
				StopAudioMessage(aud);
				if (InfoDisplay_ShouldShowTutorialText() == BZTRUE)
					InfoDisplay_Tutorial(IOS_TUT_0122);
				AudioMessage("misn0122.wav");
			}
			else if (player_handle==get_in_me)
			{
				if (!!first_objective)
				{
					ClearObjectives();
					first_objective = true;
					AddObjective("misn0101.otf",GREEN);
					AddObjective("misn0103.otf",WHITE);
			//		AddObjective("misn0105.otf",WHITE);
				}
				StartCockpitTimerUp(0,300,240);
				
				repeat_time=0.0f;
				num_reps=0;
				start_path1=BZTRUE;
				on_point=0;
			}
		}
		else if (player_handle==get_in_me && !first_objective)
		{
			ClearObjectives();
			first_objective = true;
			AddObjective("misn0101.otf",GREEN);
			AddObjective("misn0103.otf",WHITE);
			//		AddObjective("misn0105.otf",WHITE);
		}
	}
	if ((start_path1) && (!start_path2) && (player_handle==get_in_me))
	{
		// are we out of range of current point?
		VECTOR_2D diff=Vec2D_Subtract(p1->points[on_point],player2d);
		if ((Vec2D_Len(diff)>forgiveness) && (Get_Time()>repeat_time))
		{
			// tell player to get back where he was before
			if (InfoDisplay_ShouldShowTutorialText() == BZTRUE)
				InfoDisplay_Tutorial(IOS_TUT_0103);
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
				start_path2=BZTRUE;
				on_point=0;
			}
		}
	}
	if ((start_path2) && (!start_path3))
	{
		// are we out of range of current point?
		VECTOR_2D diff=Vec2D_Subtract(p2->points[on_point],player2d);
		if ((Vec2D_Len(diff)>forgiveness) && (Get_Time()>repeat_time))
		{
			// tell player to get back where he was before
			if (InfoDisplay_ShouldShowTutorialText() == BZTRUE)
				InfoDisplay_Tutorial(IOS_TUT_0103);
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
				start_path3=BZTRUE;

				if (InfoDisplay_ShouldShowTutorialText())
				{
					InfoDisplay_Tutorial(IOS_TUT_GOOD_JOB);
					//aud=AudioMessage("misi0104.wav");
				}
				else
				{
					aud=AudioMessage("misn0104.wav");
				}

				buttonSystem.TapNotifyOn("jump");

				on_point=0;
			}
		}
		
	}
	if ((start_path3) && (!jump_start))
	{
		// are we out of range of current point?
		VECTOR_2D diff=Vec2D_Subtract(p3->points[on_point],player2d);
		if ((Vec2D_Len(diff)>forgiveness) && (Get_Time()>repeat_time))
		{
			// tell player to get back where he was before
			if (InfoDisplay_ShouldShowTutorialText() == BZTRUE)
				InfoDisplay_Tutorial(IOS_TUT_0103);
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
				jump_start=BZTRUE;
				jump_done=Get_Time()+8.0f;
			}
		}
		
	}
	if ((jump_start) && (!hint1) && (Get_Time()>jump_done))
	{

		repeat_time=Get_Time()+45.0f;  // grace period to continue
		if (InfoDisplay_ShouldShowTutorialText() == BZTRUE)
			InfoDisplay_Tutorial(IOS_TUT_0105);
		AudioMessage("misn0105.wav");
		forgiveness=forgiveness*1.5f;  // for the jumps you'll need it
		AudioMessage("misn0107.wav");
		hint1=BZTRUE;
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
			start_path4=BZTRUE;
			on_point=0;
			/*
				In case the player is
				developmentally 
				disabled.
			*/
			if (player_handle!=get_in_me)
			{
				if (InfoDisplay_ShouldShowTutorialText() == BZTRUE)
					InfoDisplay_Tutorial(IOS_TUT_0122);
					AudioMessage("misn0122.wav");
			}
		}

	}
	if ((start_path4) && (!combat_start))
	{
		// are we out of range of current point?
		VECTOR_2D diff=Vec2D_Subtract(p4->points[on_point],player2d);
		if ((Vec2D_Len(diff)>forgiveness) && (Get_Time()>repeat_time))
		{
			// tell player to get back where he was before
			if (InfoDisplay_ShouldShowTutorialText() == BZTRUE)
				InfoDisplay_Tutorial(IOS_TUT_0108);
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
				combat_start=BZTRUE;
				SetObjectiveOn(target);
				SetObjectiveName(target, "Combat Training");
				if (InfoDisplay_ShouldShowTutorialText() == BZTRUE)
					InfoDisplay_Tutorial(IOS_TUT_0109);
				AudioMessage("misn0109.wav");

				ClearObjectives();
				AddObjective("misn0101.otf",GREEN);
				AddObjective("misn0103.otf",GREEN);
				AddObjective("misn0105.otf",WHITE);

			}
		}
		
	}
	if ((combat_start) && (!hint2) && (IsAlive(target)))
	if  		
			(Dist3D_Squared(first->GetPosition(), player->GetPosition())
			< 100.0f * 100.0f)

	{
		HideCockpitTimer();
		if (InfoDisplay_ShouldShowTutorialText() == BZTRUE)
			InfoDisplay_Tutorial(IOS_TUT_0111);
		aud=AudioMessage("misn0111.wav");

		buttonSystem.TapNotifyOn("weapon_fire_auto"); //tut text says strafe, but nothing ever tells you to fire
		hint2=BZTRUE;
	}
		

	if ((!combat_start2) && 
		(!IsAlive(target)) && (IsAlive(target2)))
	{
		SetObjectiveOn(target2);
		SetObjectiveName(target2, "Combat Training 2");
		if (InfoDisplay_ShouldShowTutorialText() == BZTRUE)
			InfoDisplay_Tutorial(IOS_TUT_0113);
		AudioMessage("misn0113.wav");
		combat_start2=BZTRUE;
	}

	if ((!done_message) &&
		(!IsAlive(target))
		&& (!IsAlive(target2)))
	{
		UpdateObjective("misn0101.otf",GREEN);
		UpdateObjective("misn0103.otf",GREEN);
		UpdateObjective("misn0105.otf",GREEN);
		if (InfoDisplay_ShouldShowTutorialText() == BZTRUE)
			InfoDisplay_Tutorial(IOS_TUT_0121);
		AudioMessage("misn0121.wav");
		done_message=true;
		SucceedMission(GetTime()+10,"misn01w1.des");
	}
	if ((num_reps>4) && (!lost))
	{
		repeat_time=99999.0f;
		ClearObjectives();
		AddObjective("misn0102.otf",RED);
		if (InfoDisplay_ShouldShowTutorialText() == BZTRUE)
			InfoDisplay_Tutorial(IOS_TUT_0123);
		AudioMessage("misn0123.wav");
		FailMission(GetTime()+10,"misn01l1.des");
		num_reps=0;
	}
}

const std::set<std::string>& Misn01Mission::GetPreloadSet()
{
	static std::set<std::string> retval = 
	{ "apammo", "aspilo", "aspilo_fp", "avfigh", "avtest", "nparr",
		"npscr1", "npscr2", "npscr3" };
	if (retval.empty()) return AiMission::GetPreloadSet();
	return retval;
}
