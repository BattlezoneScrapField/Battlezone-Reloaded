
#include <string.h>
#include "PowerUp.h"
#include "Recycler.h"
#include "Targeting.h"
#include "ScriptUtils.h"
#include "AiMission.h"
#include "AudioMessage.h"
#include "running.h"
#include "touchbutton.h"
#include "ControlPanel.h"


/*
	Tran04Mission
*/

class Tran04Mission : public AiMission {
	DECLARE_RTIME(Tran04Mission)
public:
	Tran04Mission(void);
	~Tran04Mission();
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
	// bools
	union {
		struct {
			bool
				found1,
				found2,
				start_done,
				message1,
				message2,
				message3,
				message4,
				message5,
				message6,
				message7,
				message8,
				message9,
				message10,
				message11,
				message12,
				message13,
				message14,
				message15,
				message16,
				press7,
				attacked,
				jump_start,
				b_last;
		};
		bool b_array[22];
	};
	// floats
	union {
		struct {
				float
					repeat_time,
					camera_delay,
					f_last;
		};
		float f_array[2];
	};
	// handles
	union {
		struct {
			BZHandle
				player,
				target1,
				target2,
				recycler,
				muf,
				camera,
				wing,
				recy,
				h_last;
		};
		BZHandle h_array[8];
	};
	// path pointers
	union {
		struct {
			AiPath
				*p_I,
				*p_will,
				*p_never,
				*p_cut,
				*p_and,
				*p_paste,
				*p_variabls,
				*p_again,
				*p_last;
		};
		AiPath *p_array[8];
	};

	// integers
	union {
		struct {
			int32_t
				num_reps,
				on_point,
				i_last;
		};
		int32_t i_array[2];
	};
				
};




void Tran04Mission::Setup(void)
{
	start_done=BZFALSE;
	found1=false;
	found2=false;
	press7=false;
	message1=false;
	message2=false;
	message3=false;
	message4=false;
	message5=false;
	message6=false;
	message7=false;
	message8=false;
	message9=false;
	message10=false;
	message11=false;
	message12=false;
	message13=false;
	message14=false;
	message15=false;
	message16=false;
	attacked=false;
	repeat_time=0.0f;
	num_reps=0;
}

// this is the BZHandle thing brad made for me
void Tran04Mission::AddObject(BZHandle h)
{
	if (
		(GetTeamNum(h) == 1) &&
		(IsOdf(h, "avmuf"))
		)
	{
		found1 = true;
		muf= h;
	}
	if (
		(GetTeamNum(h) == 1) &&
		(IsOdf(h, "avfigh"))
		)
	{
		found2 = true;
		wing= h;
		ClearObjectives();
		AddObjective("tran0401.otf", GREEN);
		AddObjective("tran0402.otf", WHITE);
	}

}

void Tran04Mission::Execute(void)
{
	bool test = false;
	if (!start_done)
	{
		buttonSystem.TapNotifyOnControlPanel(4); //recycler

		target1=GetHandle("avturr12_turrettank");
		SetPilotClass(target1, "");
		target2=GetHandle("avturr-1_turrettank");
		SetPilotClass(target2, "");
		recycler=GetHandle("avrecy-1_recycler");
		camera=GetHandle("apcamr-1_camerapod");
		player=GetHandle("player-1_hover");
		Recycler *myRecycler = (Recycler *) GameObjectHandle::GetObj(recycler);
		SetScrap(1,30);	
		if (InfoDisplay_ShouldShowTutorialText() == BZTRUE)
			InfoDisplay_Tutorial(IOS_TUT_0401);
		AudioMessage("tran0401.wav");
		AudioMessage("tran0402.wav");


		if (InfoDisplay_ShouldShowTutorialText())
		{
			InfoDisplay_Tutorial(IOS_TUT_COMM_RECYCLER);
			//AudioMessage("trai0424.wav");
		}
		else
		{
			AudioMessage("tran0424.wav");
		}



	//	AudioMessage("tran0424.wav");
		ClearObjectives();
		AddObjective("tran0401.otf",WHITE);
		AddObjective("tran0402.otf", WHITE);
		start_done=true;
	}
	if ((!message1) && (IsAlive(recycler)) &&
		(IsSelected(recycler)))
	{
		buttonSystem.TapNotifyOnControlPanel(2); //goto geyser

		if (InfoDisplay_ShouldShowTutorialText())
		{
			InfoDisplay_Tutorial(IOS_TUT_GOTO_GEYSER);
			//AudioMessage("trai0425.wav");
		}
		else
		{
			AudioMessage("tran0425.wav");
		}

		message1=true;
	}
	if ((message1) &&
		(!message2) && (IsAlive(recycler))
		)
	{
		if (IsDeployed(recycler))
		{
			buttonSystem.TapNotifyOnControlPanel(4); //recycler

			if (InfoDisplay_ShouldShowTutorialText())
			{
				InfoDisplay_Tutorial(IOS_TUT_COMM_RECYCLER);
				//AudioMessage("trai0424.wav");
			}
			else
			{
				AudioMessage("tran0424.wav");
			}

			message2=true;
		}
		// added to skip muf stage
	}

	/* 
		press 7 to have the recyler build a factory
	*/

	if ((message2) && (IsAlive(recycler)) &&
		(IsSelected(recycler))
		&& (!press7))
	{

		buttonSystem.TapNotifyOnControlPanel(0); //build scout

		if (InfoDisplay_ShouldShowTutorialText())
		{
			InfoDisplay_Tutorial(IOS_TUT_SCOUT);
			//AudioMessage("trai0406.wav");
		}
		else
		{
			AudioMessage("tran0406.wav");
		}

		press7=true;
		message6=true;
	}
	if ((message6) &&
		(!message7) &&  (IsAlive(recycler)) &&
		(!IsSelected(recycler)) && (IsBusy(recycler))) // was muf selected
	{
		if (InfoDisplay_ShouldShowTutorialText() == BZTRUE)
			InfoDisplay_Tutorial(IOS_TUT_0407);
		AudioMessage("tran0407.wav");
		camera_delay=Get_Time()+5.0f;
		message7=true;
	}

	if ((message7) 
		&& (!message8))
	{

		if (Get_Time() > camera_delay)
		{
			buttonSystem.TapNotifyOnControlPanel(3); //nav becon

			if (InfoDisplay_ShouldShowTutorialText())
			{
				InfoDisplay_Tutorial(IOS_TUT_NAV_BECAON);
				//AudioMessage("trai0408.wav");
			}
			else
			{
				AudioMessage("tran0408.wav");
			}

			camera_delay = 99999.0f;
		}

		else if (controlPanel.GetCurrentItem() == 4 && buttonSystem.IsTapActive() == false) // if we're showing the nav panel and the tap is not active
		{
			buttonSystem.TapNotifyOnControlPanel(0); //nav 1
		}
	}

	if ((message7) &&
		(!message8) &&
		(GetUserTarget() == camera))

	{

		if (InfoDisplay_ShouldShowTutorialText())
		{
			InfoDisplay_Tutorial(IOS_TUT_SPY_CAMERA);
			//AudioMessage("trai0409.wav");
		}
		else
		{
			AudioMessage("tran0409.wav");
		}

		message8=true;
		camera_delay=Get_Time()+3.0f;		
	}
	if ((message8) 
		&& (!message9) 
		&& (found2))
	{
		
		if (Get_Time() > camera_delay)
		{
			buttonSystem.TapNotifyOnControlPanel(0); //offsense

			if (InfoDisplay_ShouldShowTutorialText())
			{
				InfoDisplay_Tutorial(IOS_TUT_OFFENSE);
				//AudioMessage("trai0410.wav");
			}
			else
			{
				AudioMessage("tran0410.wav");
			}

			// wing=GetHandle("avtank-1_wingman");
			message9 = true;
			camera_delay = 99999.0f;
		}
	}

	if ((message7) && (message8) && (found2) && (!IsAlive(wing)) && (!message16))
	{
		FailMission(GetTime()+5.0f,"tran04l1.des");
		message16=true;

	}



 	if ((message9) 
		&& (!message10) 
		&& (IsAlive(wing)))
	{

		if (IsSelected(wing))
		{
			buttonSystem.TapNotifyOnControlPanel(1); // goto nav

			if (InfoDisplay_ShouldShowTutorialText())
			{
				InfoDisplay_Tutorial(IOS_TUT_NAV_WINGMAN);
			}
			else
			{
				AudioMessage("tran0411.wav");
			}

			message10 = true;
		}

		else if (buttonSystem.IsTapActive() == false && controlPanel.GetCurrentItem() == 1)
		{
			buttonSystem.TapNotifyOnControlPanel(0); //scout
		}
	}

	if ((message10) &&
		(!message11) && (IsAlive(wing)) &&
		(IsSelected(wing)) &&
		(camera_delay == 99999.0f))
	{
		if (buttonSystem.IsTapActive() == false && controlPanel.GetCurrentItem() == 4)
		{
			buttonSystem.TapNotifyOnControlPanel(0); //nav 1
		}
	}

	if ((message10) &&
		(!message11) &&		(IsAlive(wing)) &&
		(!IsSelected(wing)) &&
		(camera_delay==99999.0f))
	{
		camera_delay=Get_Time()+10.0f;
		ClearObjectives();
		AddObjective("tran0401.otf", GREEN);
		AddObjective("tran0402.otf", GREEN);
	}

	if ((message10) &&
		(!message11) &&
		(camera_delay<Get_Time()))
	{
		if (InfoDisplay_ShouldShowTutorialText() == BZTRUE)
			InfoDisplay_Tutorial(IOS_TUT_0412);
		AudioMessage("tran0412.wav");
		message11=true;
		camera_delay=99999.0f;
	}
	if ((message10) &&
		(!attacked) &&
		IsAlive(wing) &&
		(GameObjectHandle::GetObj(wing)->GetLastEnemyShot()>0))
	{
		if (InfoDisplay_ShouldShowTutorialText() == BZTRUE)
			InfoDisplay_Tutorial(IOS_TUT_0413);
		AudioMessage("tran0413.wav");
		attacked=true;
	}


	if ((!IsAlive(target1))
		&& (!message12))
	{
		if (InfoDisplay_ShouldShowTutorialText() == BZTRUE)
			InfoDisplay_Tutorial(IOS_TUT_0415);
		AudioMessage("tran0415.wav");
		if (IsAlive(target2))
		{
			SetObjectiveOn(target2);
			SetObjectiveName(target2, "Drone 2");
		}
		message12=true;
	}
	if ((GameObjectHandle::GetObj(player)!=NULL)
		&& (GameObjectHandle::GetObj(target2)!=NULL))
	if ((message12) &&
		(GetDistance(player,target2)<300.0f) &&
		(!message13))
	{
		if (InfoDisplay_ShouldShowTutorialText() == BZTRUE)
			InfoDisplay_Tutorial(IOS_TUT_0416);
		AudioMessage("tran0416.wav");
		message13=true;
		if (InfoDisplay_ShouldShowTutorialText())
		{
			InfoDisplay_Tutorial(IOS_TUT_TARGET_DRONE);
			//AudioMessage("trai0418.wav");
		}
		else
		{
			AudioMessage("tran0418.wav");
		}

		message13=true;
	}
	if ((message13) &&
		(GetUserTarget() == target2)
			&& (!message14))
	{
		AudioMessage("tran0410.wav");
		message14=true;
	}
	if ((message14) &&
		(!message15) &&
		(IsSelected(wing)))
	{
		if (InfoDisplay_ShouldShowTutorialText())
		{
			InfoDisplay_Tutorial(IOS_TUT_ATTACK_DRONE);
			//AudioMessage("trai0420.wav");
		}
		else
		{
			AudioMessage("tran0420.wav");
		}

		message15=true;
	}
	if ((message6) &&
		(!IsAlive(target1)) &&
		(!IsAlive(target2))
		&& (!message16))
	{
		if (InfoDisplay_ShouldShowTutorialText() == BZTRUE)
			InfoDisplay_Tutorial(IOS_TUT_0421);
		AudioMessage("tran0421.wav");
		SucceedMission(GetTime()+10,"tran04w1.des");
		message16=true;
	}
	if	((!message6) &&
		((!IsAlive(target1)) || (!IsAlive(target2)))
			&& (!message16))		
	{
		message16=true;
		FailMission(GetTime()+5.0f,"tran04l1.des");
	}
}

IMPLEMENT_RTIME(Tran04Mission)

Tran04Mission::Tran04Mission(void)
{
	intptr_t p_count = &p_last - p_array;
	for (intptr_t i = 0; i < p_count; i++)
		p_array[i] = nullptr;
}

Tran04Mission::~Tran04Mission()
{
}

void Tran04Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);

}

bool Tran04Mission::Load(file fp)
{
	if (missionSave) {
		int h_count = &h_last - h_array;
		for (int i = 0; i < h_count; i++)
			h_array[i] = 0;
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
		ret = ret && in_ptr(fp, (void **)&p_array[i], sizeof(p_array[0]), "Tran04Mission::p_array", this);

	// ints
	int i_count = &i_last - i_array;
	assert(i_count == SIZEOF(i_array));
	ret = ret && in(fp, i_array, sizeof(i_array));

	ret = ret && AiMission::Load(fp);
	return ret;
}

bool Tran04Mission::PostLoad(void)
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

bool Tran04Mission::Save(file fp)
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

void Tran04Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

const std::set<std::string>& Tran04Mission::GetPreloadSet()
{
	static std::set<std::string> retval
	{ "abbarr", "abcomm", "abhang", "abhqcp", "ablpad", "ablpow", "abmbld",
	"abshld", "absilo", "abspow", "abstor", "abtowe", "abwpow", "apammo",
	"aprepa", "avcnst", "avfigh", "avmuf", "avrecy", "avscav", "avslf",
	"avtank", "avturr", "avturr_c", "eggeizr1", "gatst00", "ghartl00",
	"nparr", "npscr1", "npscr2", "npscr3", "sbbarr", "sbcafe", "sbcomm",
	"sbhang", "sbhqcp", "sblpad", "sblpow", "sbshld", "sbsilo", "sbspow",
	"sbtowe", "sbwpow", "sscr_1" };
	if (retval.empty()) return AiMission::GetPreloadSet();
	return retval;
}
