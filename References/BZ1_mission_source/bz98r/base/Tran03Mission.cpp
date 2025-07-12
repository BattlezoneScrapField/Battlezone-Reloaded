#include "AiMission.h"
#include "PowerUp.h"
#include "Recycler.h"
#include "ScriptUtils.h"
#include "TeamSlots.h"
#include "AudioMessage.h"
#include "running.h"
#include "touchbutton.h"
#include "controlpanel.h"
/*
	Tran03Mission
*/

class Tran03Mission : public AiMission {
	DECLARE_RTIME(Tran03Mission)
public:
	Tran03Mission(void);
	~Tran03Mission();

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
				found, 
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
				first_message,
				second_message,
				third_message,
				fourth_message,
				fifth_message,
				fifthb_message,
				sixth_message,
				seventh_message,
				eighth_message,
				scav_died,
				jump_start,
				b_last;
		};
		bool b_array[24];
	};

	// floats
	union {
		struct {
			float
				delay_message,
				f_last;
		};
		float f_array[1];
	};

	// handles
	union {
		struct {
			BZHandle
				scav,
				attacker,
				geyser,
				recycler,
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
				aud,
				i_last;
		};
		int32_t i_array[1];
	};
};

// this is the BZHandle thing brad made for me
void Tran03Mission::AddObject(BZHandle h)
{
	if (
		(GetTeamNum(h) == 1) &&
		(IsOdf(h, "avscav"))
		)
	{
		found = true;
		scav = h;
	}

}

void Tran03Mission::Setup(void)
{
	start_done=false;
	found=false;
	first_message=false;
	second_message=false;
	third_message=false;
	fourth_message=false;
	fifth_message=false;
	fifthb_message=false;
	sixth_message=false;
	seventh_message=false;
	eighth_message=false;
	scav_died=false;
	delay_message=99999.0f;
}

void Tran03Mission::Execute(void)
{
	if (!start_done)
	{
		if (InfoDisplay_ShouldShowTutorialText())
			InfoDisplay_Tutorial(IOS_TUT_0301);
		AudioMessage("tran0301.wav");

		if (InfoDisplay_ShouldShowTutorialText())
		{
			InfoDisplay_Tutorial(IOS_TUT_RECYCLER);
			//aud = AudioMessage("trai0302.wav");
		}
		else
		{
			aud = AudioMessage("tran0302.wav");
		}



		geyser=GetHandle("eggeizr111_geyser");
		recycler=GetHandle("avrecy-1_recycler");
		attacker=GetHandle("avfigh-1_wingman");
		SetPilotClass(attacker, "");
		SetIndependence(attacker, 0);
		SetObjectiveOn(recycler);
		SetObjectiveName(recycler,"recycler");
		Recycler *myRecycler = (Recycler *) GameObjectHandle::GetObj(recycler);
		SetScrap(1,7);
		ClearObjectives();
		AddObjective("tran0301.otf",WHITE);
		AddObjective("tran0302.otf",WHITE);
		buttonSystem.TapNotifyOnControlPanel(4); //recycler
		start_done=true;
	}
	
	if ((start_done) &&
		(!first_message)	&& 
		IsAlive(recycler) &&
	(GameObjectHandle::GetObj(recycler)->IsSelected()))
	{
		StopAudioMessage(aud);
		buttonSystem.TapNotifyOnControlPanel(9); //pack up

		if (InfoDisplay_ShouldShowTutorialText())
		{
			InfoDisplay_Tutorial(IOS_TUT_PACK_RECYCLER);
			//aud = AudioMessage("trai0303.wav");
		}
		else
		{
			aud = AudioMessage("tran0303.wav");
		}

		/*
			Switch objective 
		*/
		SetObjectiveOff(recycler);
		SetObjectiveOn(geyser);
		SetObjectiveName(geyser, "Check Point 1");
		first_message=true;
	}

	if ((first_message) &&
		(!second_message) && (IsAlive(recycler)))
	{
		if (!IsDeployed(recycler))
		{
			buttonSystem.TapNotifyOnControlPanel(4); //recycler

			StopAudioMessage(aud);
			if (InfoDisplay_ShouldShowTutorialText())
				InfoDisplay_Tutorial(IOS_TUT_0304);
			aud = AudioMessage("tran0304.wav");
			second_message=true;
		}
	}


	BZHandle player = GetPlayerHandle();

	if (
		(second_message)
		&& (!third_message)
		&& (IsAlive(recycler))
		&& (IsSelected(recycler))
		&& (!IsDeploying(recycler))
		&& (!IsDeployed(recycler))
		&& (!isFollowing(recycler, player))
		&& (IsUnDeployed(recycler))
		)

	{
		buttonSystem.TapNotifyOnControlPanel(0); //follow me
	}

	if ((second_message)
		&& (!third_message) && (IsAlive(recycler))
		&& 	(Dist3D_Squared(GameObjectHandle::GetObj(geyser)->GetPosition(),
			GameObjectHandle::GetObj(recycler)->GetPosition())
			< 200.0f * 200.0f))
	{
		StopAudioMessage(aud);
		if (InfoDisplay_ShouldShowTutorialText())
			InfoDisplay_Tutorial(IOS_TUT_0305);
		aud = AudioMessage("tran0305.wav");
		third_message=true;

		buttonSystem.TapNotifyOnControlPanel(4); //recycler

	}
		if ((third_message) &&
		(!fourth_message) && (IsAlive(recycler)) &&
		(GameObjectHandle::GetObj(recycler)->IsSelected()))
	{

		buttonSystem.TapNotifyOnControlPanel(10); //go to

		StopAudioMessage(aud);
		if (InfoDisplay_ShouldShowTutorialText())
		{
			InfoDisplay_Tutorial(IOS_TUT_GEYSER);
			//aud = AudioMessage("trai0306.wav");
		}
		else
		{
			aud = AudioMessage("tran0306.wav");
		}
		fourth_message=true;
	}

	if ((third_message) &&
		(!fifth_message) && (IsAlive(recycler)))
	{
		if (IsDeployed(recycler))
		{
			buttonSystem.TapNotifyOnControlPanel(4); //recycler

			SetObjectiveOff(geyser);
			ClearObjectives();
			AddObjective("tran0301.otf",GREEN);
			AddObjective("tran0302.otf",WHITE);

			StopAudioMessage(aud);
			if (InfoDisplay_ShouldShowTutorialText())
				InfoDisplay_Tutorial(IOS_TUT_0307);
			aud = AudioMessage("tran0307.wav");
			fifth_message=true;
		}
	}
	if ((fifth_message) && (!fifthb_message) &&
		(GameObjectHandle::GetObj(recycler)->IsSelected()))
	{
		buttonSystem.TapNotifyOnControlPanel(0); //build scavenger

		StopAudioMessage(aud);
		if (InfoDisplay_ShouldShowTutorialText())
		{
			InfoDisplay_Tutorial(IOS_TUT_SCAVENGER);
			//aud = AudioMessage("trai0309.wav");
		}
		else
		{
			aud = AudioMessage("tran0309.wav");
		}

		fifthb_message=true;
	}
	if ((IsAlive(attacker)) && (!sixth_message))
	{
		AddHealth(attacker, 50.0f);
	}


	if ((fifth_message) && (!sixth_message) && (found))
	{
		StopAudioMessage(aud);
		if (InfoDisplay_ShouldShowTutorialText())
			InfoDisplay_Tutorial(IOS_TUT_0310);
		aud = AudioMessage("tran0310.wav");
		sixth_message=true;
		delay_message=Get_Time()+30.0f;
	}
	if ((!scav_died) && 
		(
		(!IsAlive(recycler)) || 
		((sixth_message) && (!IsAlive(scav))) )
		)
	{
		scav_died=true;
		StopAudioMessage(aud);
		if (InfoDisplay_ShouldShowTutorialText())
			InfoDisplay_Tutorial(IOS_TUT_0313);
		aud = AudioMessage("tran0313.wav");
		FailMission(GetTime()+10.0f,"tran03l1.des");
	}
	if (Get_Time()>delay_message)
	{
		// "protect the scavenger"
		if (IsAlive(attacker))
		{
			if (InfoDisplay_ShouldShowTutorialText())
				InfoDisplay_Tutorial(IOS_TUT_0308);
			AudioMessage("tran0308.wav");
			Attack(attacker, scav, 1);
		}
		delay_message=99999.0f;
	}
	if ((sixth_message) && (!seventh_message)
		&& (!IsAlive(attacker)))
	{
		// you killed him
		if (InfoDisplay_ShouldShowTutorialText())
			InfoDisplay_Tutorial(IOS_TUT_0314);
		AudioMessage("tran0314.wav");
		seventh_message=true;
		ClearObjectives();
		AddObjective("tran0301.otf",GREEN);
		AddObjective("tran0302.otf",GREEN);
	}
	if ((seventh_message) && (!eighth_message))
	{
		Recycler *myRecycler = (Recycler *) GameObjectHandle::GetObj(recycler);
		int money=myRecycler->GetTeamList()->GetScrap();		
		if (money>=9)
		{
			if (InfoDisplay_ShouldShowTutorialText())
				InfoDisplay_Tutorial(IOS_TUT_0315);
			AudioMessage("tran0315.wav");
			eighth_message=true;
			SucceedMission(GetTime()+10.0f,"tran03w1.des");
		}
	}



	
}

IMPLEMENT_RTIME(Tran03Mission)

Tran03Mission::Tran03Mission(void)
{
	intptr_t p_count = &p_last - p_array;
	for (intptr_t i = 0; i < p_count; i++)
		p_array[i] = nullptr;
}

Tran03Mission::~Tran03Mission()
{
}

void Tran03Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

bool Tran03Mission::Load(file fp)
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
		ret = ret && in_ptr(fp, (void **)&p_array[i], sizeof(p_array[0]), "Tran03Mission::p_array", this);

	// ints
	int i_count = &i_last - i_array;
	assert(i_count == SIZEOF(i_array));
	ret = ret && in(fp, i_array, sizeof(i_array));

	ret = ret && AiMission::Load(fp);
	return ret;
}

bool Tran03Mission::PostLoad(void)
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

bool Tran03Mission::Save(file fp)
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

void Tran03Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

const std::set<std::string>& Tran03Mission::GetPreloadSet()
{
	static std::set<std::string> retval =
		{ "aspilo", "aspilo_fp", "avfigh", "avrecy", "avscav", "avtank",
		"eggeizr1", "gatst00", "ghartl00", "npscr1", "npscr2", "npscr3",
		"sscr_1" };
	if (retval.empty()) return AiMission::GetPreloadSet();
	return retval;
}
