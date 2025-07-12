#include "GameCommon.h"

#include "..\fun3d\AiMission.h"
#include "..\fun3d\PowerUp.h"
#include "..\fun3d\Recycler.h"
#include "..\fun3d\ScriptUtils.h"

/*
	Tran03Mission
*/

class Tran03Mission : public AiMission {
	DECLARE_RTIME(Tran03Mission)
public:
	Tran03Mission(void);
	~Tran03Mission();

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
			Handle
				scav,
				attacker,
				geyser,
				recycler,
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
				dummy,
				i_last;
		};
		int i_array[1];
	};
};

// this is the handle thing brad made for me
void Tran03Mission::AddObject(Handle h)
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
	bool test;
	if (!start_done)
	{
		AudioMessage("tran0301.wav");
		AudioMessage("tran0302.wav");
		geyser=GetHandle("eggeizr111_geyser");
		recycler=GetHandle("avrecy-1_recycler");
		attacker=GetHandle("svfigh-1_wingman");
		SetObjectiveOn(recycler);
		SetObjectiveName(recycler,"recycler");
		Recycler *myRecycler = (Recycler *) GameObjectHandle::GetObj(recycler);
		SetScrap(1,7);
		ClearObjectives();
		AddObjective("tran0301.otf",WHITE);
		AddObjective("tran0302.otf",WHITE);

		start_done=true;
	}
	
	if ((start_done) &&
		(!first_message)	&& 
		IsAlive(recycler) &&
	(GameObjectHandle::GetObj(recycler)->IsSelected()))
	{
		AudioMessage("tran0303.wav");
		/*
			Switch objective 
		*/
		SetObjectiveOff(recycler);
		GameObject *second_obj=GameObjectHandle::GetObj(geyser);  
		second_obj->SetObjective(TRUE);
		second_obj->SetName("Check Point 1");
		first_message=true;
	}

	if ((first_message) &&
		(!second_message) && (IsAlive(recycler)))
	{
		test = ((Recycler *) GameObjectHandle::GetObj(recycler))->IsDeployed();
		if	(!test)
		{
			AudioMessage("tran0304.wav");
			second_message=true;
		}
	}

	if ((second_message)
		&& (!third_message) && (IsAlive(recycler))
		&& 	(Dist3D_Squared(GameObjectHandle::GetObj(geyser)->GetPosition(),
			GameObjectHandle::GetObj(recycler)->GetPosition())
			< 200.0f * 200.0f))
	{
	//	ClearObjectives();
	//	AddObjective("tran0301.otf",GREEN);
		AudioMessage("tran0305.wav");
		third_message=true;
	}
	if ((third_message) &&
		(!fourth_message) && (IsAlive(recycler)) &&
		(GameObjectHandle::GetObj(recycler)->IsSelected()))
	{
		AudioMessage("tran0306.wav");
		fourth_message=true;
	}

	if ((third_message) &&
		(!fifth_message) && (IsAlive(recycler)))
	{
		test = ((Recycler *) GameObjectHandle::GetObj(recycler))->IsDeployed();
		if	(test)
		{
			SetObjectiveOff(geyser);
			ClearObjectives();
			AddObjective("tran0301.otf",GREEN);
			AddObjective("tran0302.otf",WHITE);

			AudioMessage("tran0307.wav");
			fifth_message=true;
		}
	}
	if ((fifth_message) && (!fifthb_message) &&
		(GameObjectHandle::GetObj(recycler)->IsSelected()))
	{
		AudioMessage("tran0309.wav");
		fifthb_message=true;
	}
	if ((IsAlive(attacker)) && (!sixth_message))
	{
				GameObjectHandle::GetObj(attacker)->AddHealth(50.0f);
	}


	if ((fifth_message) && (!sixth_message))
	{
		Recycler *myRecycler = (Recycler *) GameObjectHandle::GetObj(recycler);
		int money=myRecycler->GetTeamList()->GetScrap();		
		if ((money<5) && (found))
		{
			AudioMessage("tran0308.wav");
			// scav=GetHandle("avscav-1_scavenger");
			sixth_message=true;
			delay_message=Get_Time()+5.0f;
			AiCmdInfo info;
			info.what=CMD_ATTACK;
			info.priority=1;  // so the computer doesn't interupt
			info.where=NULL;  // just in case
			info.who=scav;
			GameObjectHandle::GetObj(attacker)->SetCommand(info);
		}
	}
	if ((!scav_died) && 
		(
		(!IsAlive(recycler)) || 
		((sixth_message) && (!IsAlive(scav))) )
		)
	{
		scav_died=true;
		AudioMessage("tran0313.wav");
		FailMission(GetTime()+10.0f,"tran03l1.des");
	}
	if (Get_Time()>delay_message)
	{
		// "protect the scavenger"
	//	AudioMessage("tran0311.wav");
		delay_message=99999.0f;
	}
	if ((sixth_message) && (!seventh_message)
		&& (!IsAlive(attacker)))
	{
		// you killed him
		AudioMessage("tran0314.wav");
		seventh_message=true;
	}
	if ((seventh_message) && (!eighth_message))
	{
		Recycler *myRecycler = (Recycler *) GameObjectHandle::GetObj(recycler);
		int money=myRecycler->GetTeamList()->GetScrap();		
		if (money>1)
		{
			AudioMessage("tran0310.wav");
			AudioMessage("tran0315.wav");
			eighth_message=true;
			SucceedMission(GetTime()+20.0,"tran03w1.des");

		}
	}



	
}

IMPLEMENT_RTIME(Tran03Mission)

Tran03Mission::Tran03Mission(void)
{
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

void Tran03Mission::Update(void)
{
	AiMission::Update();
	Execute();
}
