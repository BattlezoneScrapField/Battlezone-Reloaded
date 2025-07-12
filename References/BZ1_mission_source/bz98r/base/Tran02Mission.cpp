#include "AiMission.h"
#include "GameObjectHandle.h"
#include "PowerUp.h"
#include "ScriptUtils.h"
#include "ControlPanel.h"
#include "AudioMessage.h"
#include "touchbutton.h"

/*
	Tran02Mission
*/

class Tran02Mission : public AiMission {
	DECLARE_RTIME(Tran02Mission)
public:
	Tran02Mission(void);
	~Tran02Mission();

	virtual bool Load(file fp) override;
	virtual bool PostLoad(void) override;
	virtual bool Save(file fp) override;

	virtual void Update(void) override;

	virtual void AddObject(GameObject *gameObj) override;

	virtual const std::set<std::string>& GetPreloadSet() override;
private:
	void Setup(void);
	void AddObject(BZHandle h);
	void Execute(void);

	float PlayReminder(float time,int message);

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
			BZHandle
				turret,
				pointer,
				haul1,
				haul2,
				h_last;
		};
		BZHandle h_array[4];
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
				num_reps,
				message,
				aud,
				i_last;
		};
		int32_t i_array[3];
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
	SetPilotClass(haul1, "");
	haul2=GetHandle("avhaul19_tug");
	SetPilotClass(haul2, "");
	repeat_time=0.0f;
	num_reps=0;
	hint_delay=99999.0f;
	repeat_time=99999.0f;
	message=0;
}

// this is the BZHandle thing brad made for me
void Tran02Mission::AddObject(BZHandle h)
{
}

float Tran02Mission::PlayReminder(float time,int message)
{
	float new_time=time;
	if (Get_Time()>time)
	{		
		new_time=Get_Time()+15.0f;
		if (InfoDisplay_ShouldShowTutorialText())
		{
			switch (message)
			{

			case 1: InfoDisplay_Tutorial(IOS_TUT_OPEN_A_COMM); //aud = AudioMessage("trai0202.wav");
					break;

			case 2: aud = AudioMessage("tran0203.wav");
					InfoDisplay_Tutorial(IOS_TUT_0203);
					break;
			case 3: InfoDisplay_Tutorial(IOS_TUT_OPEN_A_COMM); //aud = AudioMessage("trai0204.wav");
					break;
			case 4: InfoDisplay_Tutorial(IOS_TUT_SELECT_TURRET); //aud = AudioMessage("tran0211.wav");
					break;
			case 5: InfoDisplay_Tutorial(IOS_TUT_ORDER_TURRET); //aud = AudioMessage("trai0206.wav");
					break;
			case 6: InfoDisplay_Tutorial(IOS_TUT_0109);
					aud = AudioMessage("misn0109.wav");
					break;
			case 7: InfoDisplay_Tutorial(IOS_TUT_COMM_TURRET); //aud = AudioMessage("trai0207.wav");
					break;
			case 8: InfoDisplay_Tutorial(IOS_TUT_DEPLOY_TURRET); //aud = AudioMessage("trai0208.wav");
						new_time=99999.0f;  // we're done
					break;
			}
		}
		else
		{
			switch (message)
			{

				case 1: aud = AudioMessage("tran0202.wav");
					break;
				case 2: aud = AudioMessage("tran0203.wav");
					break;
				case 3: aud = AudioMessage("tran0202.wav");
					break;
				case 4: aud = AudioMessage("tran0211.wav");
					break;
				case 5: aud = AudioMessage("tran0206.wav");
					break;
				case 6: aud = AudioMessage("misn0109.wav");
					break;
				case 7: aud = AudioMessage("tran0207.wav");
					break;
				case 8: aud = AudioMessage("tran0208.wav");
					new_time=99999.0f;  // we're done
					break;
			}
		}


	}
	return new_time;
}

void Tran02Mission::Execute(void)
{
	// check if the turret is alive and the drone is alive before the last stage
	if (IsAlive(turret) && (fifth_selection || IsAlive(haul1)))
	{
		repeat_time=PlayReminder(repeat_time,message);
		if (!start_done)
		{
			SetObjectiveOn(turret);
			SetObjectiveName(turret, "Turret");
			if (InfoDisplay_ShouldShowTutorialText())
				InfoDisplay_Tutorial(IOS_TUT_0201);
			aud = AudioMessage("tran0201.wav");
			hint_delay=Get_Time()+10.0f;
			ClearObjectives();
			AddObjective("tran0201.otf",WHITE);
			start_done=true;

		}
		if (!second_selection && IsAudioMessageDone(aud))
		{
			if(GetRunningPlatform()==PLATFORM_IOS)
			{
					InfoDisplay_Tutorial(IOS_TUT_OPEN_A_COMM);
			}
			else
			{
				aud = AudioMessage("tran0202.wav");
			}
			hint_delay=99999.0f;
			repeat_time=Get_Time()+30.0f;
			message=3;  // was 1
			// new 
			second_selection=true;
			buttonSystem.TapNotifyOnControlPanel(1); //Defense


		}
		if ((!thirda_selection) &&
			(second_selection) &&
			(controlPanel.GetCurrentItem()==2))
		{
			StopAudioMessage(aud);
			buttonSystem.TapNotifyOnControlPanel(0); //Turret

			if (InfoDisplay_ShouldShowTutorialText())
			{
				InfoDisplay_Tutorial(IOS_TUT_GREEN_LINE);
				//aud = AudioMessage("trai0205.wav");
			}
			else
			{
				aud = AudioMessage("tran0205.wav");
			}

			thirda_selection=true;
			repeat_time=Get_Time()+30.0f;
			message=4;
		}
	
		if ((!third_selection) &&
			(second_selection) &&
			(GameObjectHandle::GetObj(turret)->IsSelected()))
		{
			buttonSystem.TapNotifyOnControlPanel(0); //follow me

			StopAudioMessage(aud);
			if (InfoDisplay_ShouldShowTutorialText())
			{
				InfoDisplay_Tutorial(IOS_TUT_ORDER_TURRET);
				//aud = AudioMessage("trai0206.wav");
			}
			else
			{
				aud = AudioMessage("tran0206.wav");
			}

			SetObjectiveOff(turret);
			SetObjectiveOn(pointer);
			SetObjectiveName(pointer, "Target Range");
			third_selection=true;
			repeat_time=Get_Time()+30.0f;
			message=5;


		}
		if ((third_selection) && (!go_reminder) &&
			(!GameObjectHandle::GetObj(turret)->IsSelected()))
		{
			StopAudioMessage(aud);
			if (InfoDisplay_ShouldShowTutorialText() == BZTRUE)
				InfoDisplay_Tutorial(IOS_TUT_0109);
			aud = AudioMessage("misn0109.wav"); // good job now head for the target range
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

			if (InfoDisplay_ShouldShowTutorialText())
			{
				InfoDisplay_Tutorial(IOS_TUT_COMM_TURRET);
				//aud = AudioMessage("trai0207.wav");
				//aud = AudioMessage("trai0212.wav"); // press defense
			}
			else
			{
				/*if (InfoDisplay_ShouldShowTutorialText())
					InfoDisplay_Tutorial(IOS_TUT_0212); //select defensive units*/
				aud = AudioMessage("tran0207.wav");
				aud = AudioMessage("tran0212.wav"); // press 2
			}

					hint1=true;
			repeat_time=Get_Time()+30.0f;
			message=7;
			buttonSystem.TapNotifyOnControlPanel(1); //Defense
		}
		if ((hint1) && (!hint2) &&
				(controlPanel.GetCurrentItem()==2))
		{
			hint2=true;
			StopAudioMessage(aud);
			if (InfoDisplay_ShouldShowTutorialText())
			{
				InfoDisplay_Tutorial(IOS_TUT_SELECT_TURRET);
				//aud = AudioMessage("trai0211.wav");
			}
			else
			{
				aud = AudioMessage("tran0211.wav");
			}
			buttonSystem.TapNotifyOnControlPanel(0); //turret
			repeat_time=Get_Time()+20.0f;
			message=4;
		}
		if ((hint1) &&
			(!fourth_selection) &&
			(GameObjectHandle::GetObj(turret)->IsSelected()))
		{
			StopAudioMessage(aud);
			if (InfoDisplay_ShouldShowTutorialText())
			{
				InfoDisplay_Tutorial(IOS_TUT_DEPLOY_TURRET);
				//aud = AudioMessage("trai0208.wav");
			}
			else
			{
				aud = AudioMessage("tran0208.wav");
			}
			buttonSystem.TapNotifyOnControlPanel(10); //go to
			fourth_selection=true;
			repeat_time=Get_Time()+30.0f;
			message=8;
		}
		if ((fourth_selection) &&
			(!fifth_selection) &&
			(GetCurrentCommand(turret)==CMD_GO))
		{
			repeat_time=99999.0f; // we're done repeating
			StopAudioMessage(aud);
			if (InfoDisplay_ShouldShowTutorialText())
				InfoDisplay_Tutorial(IOS_TUT_0209);
			aud = AudioMessage("tran0209.wav");
			SetObjectiveOff(pointer);
			Goto(haul1, turret, 1);
			SetObjectiveOn(haul1);
			SetObjectiveName(haul1, "Target Drone");
			fifth_selection = true;
		}
		if ((fifth_selection) &&
			(!end_message) &&
			(GameObjectHandle::GetObj(haul1)==NULL))
		{
			UpdateObjective("tran0201.otf",GREEN);
			StopAudioMessage(aud);
			if (InfoDisplay_ShouldShowTutorialText())
				InfoDisplay_Tutorial(IOS_TUT_0210);
			aud = AudioMessage("tran0210.wav");
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
	intptr_t p_count = &p_last - p_array;
	for (intptr_t i = 0; i < p_count; i++)
		p_array[i] = nullptr;
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
	assert(b_count == SIZEOF(b_array));
	ret = ret && in(fp, b_array, sizeof(b_array));

	// floats
	int f_count = &f_last - f_array;
	assert(f_count == SIZEOF(f_array));
	ret = ret && in(fp, f_array, sizeof(f_array));

	// Handles
	int h_count = &h_last - h_array;
	assert(h_count == SIZEOF(h_array));
	ret = ret && in(fp, h_array, sizeof(h_array));

	// path pointers
	int p_count = &p_last - p_array;
	assert(p_count == SIZEOF(p_array));
	for (int i = 0; i < p_count; i++)
		ret = ret && in_ptr(fp, (void **)&p_array[i], sizeof(p_array[0]), "Tran02Mission::p_array", this);

	// ints
	int i_count = &i_last - i_array;
	assert(i_count == SIZEOF(i_array));
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
	assert(b_count == SIZEOF(b_array));
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

void Tran02Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

const std::set<std::string>& Tran02Mission::GetPreloadSet()
{
	static std::set<std::string> retval = 
		{ "aspilo", "aspilo_fp", "avhaul", "avtank", "avturr", "avturr_c",
		"gatst00", "ghartl00", "nparr", "npscr2", "npscr3" };
	if (retval.empty()) return AiMission::GetPreloadSet();
	return retval;
}
