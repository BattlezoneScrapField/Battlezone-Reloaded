#include "GameCommon.h"
#include <string.h>
#include "..\fun3d\PowerUp.h"
#include "..\fun3d\Recycler.h"
#include "..\fun3d\Factory.h"
#include "..\fun3d\Targeting.h"
#include "..\fun3d\ScriptUtils.h"

/*
	Tran04Mission
*/

#include "..\fun3d\AiMission.h"
#include "..\fun3d\AiProcess.h"

class Tran04Mission : public AiMission {
	DECLARE_RTIME(Tran04Mission)
public:
	Tran04Mission(void);
	~Tran04Mission();
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
			Handle
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
		Handle h_array[8];
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
			int 
				num_reps,
				on_point,
				i_last;
		};
		int i_array[2];
	};
				
};




void Tran04Mission::Setup(void)
{
	start_done=FALSE;
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

// this is the handle thing brad made for me
void Tran04Mission::AddObject(Handle h)
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
	}

}

void Tran04Mission::Execute(void)
{
	bool test = false;
	if (!start_done)
	{
		target1=GetHandle("avturr12_turrettank");
		target2=GetHandle("avturr-1_turrettank");
		recycler=GetHandle("avrecy-1_recycler");
		camera=GetHandle("apcamr-1_camerapod");
		player=GetHandle("player-1_hover");
		Recycler *myRecycler = (Recycler *) GameObjectHandle::GetObj(recycler);
		SetScrap(1,30);		
		AudioMessage("tran0401.wav");
		AudioMessage("tran0402.wav");
		AudioMessage("tran0424.wav");
		ClearObjectives();
		AddObjective("tran0401.otf",WHITE);
		start_done=true;
	}
	if ((!message1) && (IsAlive(recycler)) &&
		(GameObjectHandle::GetObj(recycler)->IsSelected()))
	{
		AudioMessage("tran0425.wav");
		message1=true;
	}
	if ((message1) &&
		(!message2) && (IsAlive(recycler))
		)
	{
		bool test=((Recycler *) GameObjectHandle::GetObj(recycler))->IsDeployed();
		if (test)
		{
			AudioMessage("tran0424.wav");  // select the recycler
			message2=true;
		}
		// added to skip muf stage
	}

	/* 
		press 7 to have the recyler build a factory
	*/

	if ((message2) && (IsAlive(recycler)) &&
		(GameObjectHandle::GetObj(recycler))->IsSelected()
		&& (!press7))
	{
		// was
		// AudioMessage("tran0403.wav");
		AudioMessage("tran0406.wav");
		press7=true;
		message6=true;
	}
	/*
	if ((message2) &&
		(!message3))
	{
		int money = ((Recycler *) GameObjectHandle::GetObj(recycler))->GetTeamList()->GetScrap();
		if ((money<30) && (found1))
		{
			// found1 is set but we don't test for it
			//muf=GetHandle("avmuf-1_factory");
			if (muf!=NULL)
			{
				AudioMessage("tran0404.wav");
				AudioMessage("tran0405.wav");
				message3=true;			
			}
			else
			{
				message2=false; // so you don't repeat this
				FailAll(10);  // you built the wrong thing
			}
		}
	}

	if ((message3)
		&& (!message4)
				&& (GameObjectHandle::GetObj(muf)->IsSelected()))
	{
		AudioMessage("tran0423.wav");
		message4=true;
	}

		if ((message4)
		&& (!message5))

	{ 
		test=((Factory *) GameObjectHandle::GetObj(muf))->IsDeployed();
		if (test)
		{
			AudioMessage("tran0405.wav");
			message5=true;
		}
	}
	 if ((message5) &&
		(!message6) &&
		(GameObjectHandle::GetObj(muf)->IsSelected()))
	{
		AudioMessage("tran0406.wav");
		message6=true;
	}
	*/
	if ((message6) &&
		(!message7) &&  (IsAlive(recycler)) &&
		(!GameObjectHandle::GetObj(recycler)->IsSelected())) // was muf selected
	{
		AudioMessage("tran0407.wav");
		camera_delay=Get_Time()+5.0f;
		message7=true;
	}
	if ((message7) 
		&& (!message8)
		&& (Get_Time()>camera_delay))
	{
		AudioMessage("tran0408.wav");
		camera_delay=99999.0f;
	}

	if ((message7) &&
		(!message8) &&
		(GetUserTarget() == camera))

	{
		AudioMessage("tran0409.wav");
		message8=true;
		camera_delay=Get_Time()+3.0f;		
	}
	if ((message8) &&
		(!message9) &&
		(Get_Time()>camera_delay) && (found2))
	{
		AudioMessage("tran0410.wav");
		// wing=GetHandle("avtank-1_wingman");
		message9=true;
		camera_delay=99999.0f;
	}
	if ((message8) && (!IsAlive(wing)) && (!message16))
	{
		FailMission(GetTime()+5.0f,"tran04l1.des");
		message16=true;

	}
 	if ((message9) &&
		(!message10) && (IsAlive(wing)) &&
		(GameObjectHandle::GetObj(wing)->IsSelected()))
	{
		AudioMessage("tran0411.wav");
		message10=true;
	}

	if ((message10) &&
		(!message11) &&		(IsAlive(wing)) &&
		(!GameObjectHandle::GetObj(wing)->IsSelected()) &&
		(camera_delay==99999.0f))
	{
		camera_delay=Get_Time()+10.0f;

	}
	if ((message10) &&
		(!message11) &&
		(camera_delay<Get_Time()))
	{
		AudioMessage("tran0412.wav");
		message11=true;
		camera_delay=99999.0f;
	}
	if ((message10) &&
		(!attacked) &&
		IsAlive(wing) &&
		(GameObjectHandle::GetObj(wing)->GetLastEnemyShot()>0))
	{
		AudioMessage("tran0413.wav");
		attacked=true;
	}


	if ((!IsAlive(target1))
		&& (!message12))
	{
		AudioMessage("tran0415.wav");
		if (IsAlive(target2))
		{
			GameObject *second_obj=GameObjectHandle::GetObj(target2);  
			second_obj->SetObjective(TRUE);
			second_obj->SetName("Drone 2");
		}
		message12=true;
	}
	if ((GameObjectHandle::GetObj(player)!=NULL)
		&& (GameObjectHandle::GetObj(target2)!=NULL))
	if ((message12) &&
		(GetDistance(player,target2)<300.0f) &&
		(!message13))
	{
		AudioMessage("tran0416.wav");
		message13=true;
		AudioMessage("tran0418.wav");
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
		(GameObjectHandle::GetObj(wing)->IsSelected()))
	{
		AudioMessage("tran0420.wav");
		message15=true;
	}
	if ((message6) &&
		(!IsAlive(target1)) &&
		(!IsAlive(target2))
		&& (!message16))
	{
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

void Tran04Mission::Update(void)
{
	AiMission::Update();
	Execute();
}
