#include "GameCommon.h"

#include "..\fun3d\AiMission.h"
#include "..\fun3d\ScriptUtils.h"
#include "..\fun3d\UnitProcess.h"

/*
	Misns6Mission
*/


class Misns6Mission : public AiMission {
	DECLARE_RTIME(Misns6Mission)
public:
	Misns6Mission(void);
	~Misns6Mission();

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
				won,lost,last_objective,
				start_done,won_message,lost_message,warning,
				base_suggestion,art_found,
				counter1,counter2,counter3,counter4,counter5,
				counter_attack,
				b_last;
		};
		bool b_array[15];
	};

	// floats
	union {
		struct {
			float
				check_time,check1,check2,check3,check4,aip_time,
				f_last;
		};
		float f_array[6];
	};

	// handles
	union {
		struct {
			Handle
				beacon,goal,art1,art2,tur1,tur2,tur3,tur4,
				far_silo,recy,
				miners[6],
				h_last;
		};
		Handle h_array[16];
	};

	// integers
	union {
		struct {
			int
				next_target,
				audmsg,
				i_last;
		};
		int i_array[2];
	};
};

void Misns6Mission::Setup(void)
{
	aip_time=99999.0f;
	last_objective=false;
	start_done=false;
	counter1=false;
	counter2=false;
	counter3=false;
	counter4=false;
	counter5=false;
	counter_attack=false;
	base_suggestion=false;
	art_found=false;
	warning=false;
	won=false;
	lost=false;
	won_message=false;
	lost_message=false;
}

void Misns6Mission::AddObject(Handle h)
{
	int closest;
	if (
		(GetTeamNum(h) == 2) &&
		(IsOdf(h, "avmine"))
		)
	{
		float min_dist=99999.0f;
		float temp;
		if ((temp=GetDistance(h,"m1",1))<min_dist)
		{
			closest=0;
			min_dist=temp;
			Goto(h,"s1",1);
		}
		if ((temp=GetDistance(h,"m2",1))<min_dist)
		{
			closest=1;
			min_dist=temp;
			Goto(h,"s2",1);
		}
		if ((temp=GetDistance(h,"m3",1))<min_dist)
		{
			closest=2;
			min_dist=temp;
			Goto(h,"s3",1);
		}
		
		miners[closest]=h;
		next_target=closest;
	}
}

void Misns6Mission::Execute(void)
{
	int count;
	Handle player=GetPlayerHandle();
	if (!start_done)
	{
		next_target=0;
//		BuildObject("svrecy",1,"spawn1");
		aip_time=GetTime()+120.0f;
		BuildObject("avmine",2,"m1");
		BuildObject("avmine",2,"m2");
		BuildObject("avmine",2,"m3");
		goal=GetHandle("abcafe8_i76building");
		art1=GetHandle("avartl3_howitzer");
		art2=GetHandle("avartl4_howitzer");
		tur1=GetHandle("avturr0_turrettank");
		tur2=GetHandle("avturr1_turrettank");
		tur3=GetHandle("defender1");
		tur4=GetHandle("defender2");
		recy=GetHandle("svrecy0_recycler");
		far_silo=GetHandle("absilo0_scrapsilo");
		Defend(art1,1);
		Defend(art2,1);
		Defend(tur3,1);
		Defend(tur4,1);
		Defend(tur1,1);
		Defend(tur2,1);
		SetScrap(1,20);
		check_time=GetTime()+10.0f;
		AudioMessage("misns601.wav");
		ClearObjectives();
		AddObjective("misns601.otf",WHITE);
		AddObjective("misns602.otf",WHITE);
		start_done=true;
	}
	if ((!warning) &&
		((GetDistance(player,"m1",1)<250) 
		|| (GetDistance(player,"m2",1)<250) 
		|| (GetDistance(player,"m3",1)<250)))
	{
		AudioMessage("misns602.wav");
		warning=true;
	}
	if (GetTime()>aip_time)
	{
		SetAIP("misns6.aip");
		aip_time=99999.0f;
	}
	if (GetTime()>check_time)
	for (count=0;count<3;count++)
	{
		// if (what == CMD_NONE)
		//   Attack(friend1, enemy1);
		if (IsAlive(miners[count]))
		{
			
			GameObject *meObj = GameObjectHandle::GetObj(miners[count]);
			if ((meObj->GetLastEnemyShot()>0) && (!counter1))
			{
				counter1=true;
				Handle a1=BuildObject("bvraz",2,"counter1");
				Handle a2=BuildObject("bvraz",2,"counter2");
				Attack(a1,player);
				Attack(a2,player);
			}

#if 0
			AiProcess *p=meObj->GetAIProcess();
			bool test=((MineLayerProcess *) p)->laying;
#else
			UnitProcess *p = (UnitProcess *)meObj->GetAIProcess();
			bool test = p->curState == UnitProcess::USTATE1;
#endif
			AiCommand what=GetCurrentCommand(miners[count]);
			if ((what==CMD_NONE) && (!test))
			//	(meObj->((MineLayerProcess *) GetAIProcess())->laying))
				//((MineLayerProcess *) aiProcess)->laying))
			{
				switch (next_target)
				{
					case 0:
						Mine(miners[count],"s1",1);
						break;
					case 1:
						Mine(miners[count],"s2",1);
						break;
					case 2:
						Mine(miners[count],"s3",1);
						break;
					case 3:
						Mine(miners[count],"m1",1);
						break;
					case 4:
						Mine(miners[count],"m2",1);
						break;
					case 5:
						Mine(miners[count],"m3",1);
						break;
				}
				next_target++;
				if (next_target>5) next_target=0;
			}
		}
		check_time=GetTime()+3.0f;

	}
	if ((!counter2) && (GetTime()>check1))
	{
		if (GetDistance(player,"counter2")<400.0f)
		{
			BuildObject("bvtank",2,"counter2");
			BuildObject("bvtank",2,"counter2");
			BuildObject("bvturr",2,"counter2");
			check1=check1+300.0f;
		}
		else check1=GetTime()+3.0f;
	}
	if ((!counter3) && (GetTime()>check2))
	{
		if (GetDistance(player,"counter3")<400.0f)
		{
			BuildObject("bvtank",2,"counter3");
			BuildObject("bvtank",2,"counter3");
			BuildObject("bvturr",2,"counter3");
			check2=check2+300.0f;
		}
		else check2=GetTime()+3.0f;
	}
	if ((!counter4) && (GetTime()>check3))
	{
		if (GetDistance(player,"counter4")<200.0f)
		{
			BuildObject("bvtank",2,"counter4");
			BuildObject("bvtank",2,"counter4");
			BuildObject("bvturr",2,"counter4");
			check3=GetTime()+300.0f;
		}
		else check3=GetTime()+3.0f;
	}
	if ((!counter5) && (GetTime()>check4))
	{
		if (GetDistance(player,"counter5")<200.0f)
		{
			BuildObject("bvtank",2,"counter5");
			BuildObject("bvtank",2,"counter5");
			BuildObject("bvturr",2,"counter5");
			check4=GetTime()+300.0f;
		}
		else check4=GetTime()+3.0f;
	}
	if ((!art_found) && 
		 ((GetDistance(player,art1)<200.0f) || 
		  (GetDistance(player,art2)<200.0f)))
	{
		art_found=true;
		AudioMessage("misns605.wav");
	}
	if ((!counter_attack) && (GetDistance(far_silo,player)<400.0f))
	{
		Handle temp=BuildObject("bvltnk",2,"counter_attack");
		Goto(temp,"counter_attack_path",1);
		temp=BuildObject("bvltnk",2,"counter_attack");
		Goto(temp,"counter_attack_path",1);
		temp=BuildObject("bvtank",2,"counter_attack");
		Goto(temp,"counter_attack_path",1);
		temp=BuildObject("bvtank",2,"counter_attack");
		Goto(temp,"counter_attack_path",1);
		temp=BuildObject("bvrckt",2,"counter_attack");
		Goto(temp,"counter_attack_path",1);
		AudioMessage("misns603.wav");
		counter_attack=true;
	}
	/*
		If the player
		is close to the last objective
		make it the 
		objective.
	*/
	if ((!last_objective) && (GetDistance(player,goal)<300.0f))
	{
		ClearObjectives();
		AddObjective("misns601.otf",GREEN);
		AddObjective("misns602.otf",WHITE);
		last_objective=true;
		SetObjectiveOn(goal);
	}
	if ((!won) && (!IsAlive(goal)))
	{
		audmsg=AudioMessage("misns609.wav");
		won_message=true;
		won=true;
	}
	if ((won) && (IsAudioMessageDone(audmsg)))
	{
		SucceedMission(GetTime()+0.0f,"misns6w1.des");
		won=false;
	}
	if ((!won) && (!lost) && (!IsAlive(recy)))
	{
		lost=true;
		FailMission(GetTime()+2.0f,"misns6l1.des");
	}
}

IMPLEMENT_RTIME(Misns6Mission)

Misns6Mission::Misns6Mission(void)
{
}

Misns6Mission::~Misns6Mission()
{
}

void Misns6Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

bool Misns6Mission::Load(file fp)
{
	if (missionSave) {
		int i;

		// init bools
		int b_count = &b_last - b_array;
		_ASSERTE(b_count == SIZEOF(b_array));
		for (i = 0; i < b_count; i++)
			b_array[i] = false;

		// init floats
		int f_count = &f_last - f_array;
		_ASSERTE(f_count == SIZEOF(f_array));
		for (i = 0; i < f_count; i++)
			f_array[i] = 99999.0f;

		// init handles
		int h_count = &h_last - h_array;
		_ASSERTE(h_count == SIZEOF(h_array));
		for (i = 0; i < h_count; i++)
			h_array[i] = 0;

		// init ints
		int i_count = &i_last - i_array;
		_ASSERTE(i_count == SIZEOF(i_array));
		for (i = 0; i < i_count; i++)
			i_array[i] = 0;

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

	// ints
	int i_count = &i_last - i_array;
	_ASSERTE(i_count == SIZEOF(i_array));
	ret = ret && in(fp, i_array, sizeof(i_array));

	ret = ret && AiMission::Load(fp);
	return ret;
}

bool Misns6Mission::PostLoad(void)
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

bool Misns6Mission::Save(file fp)
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

	// ints
	int i_count = &i_last - i_array;
	_ASSERTE(i_count == SIZEOF(i_array));
	ret = ret && out(fp, i_array, sizeof(i_array), "i_array");

	ret = ret && AiMission::Save(fp);
	return ret;
}

void Misns6Mission::Update(void)
{
	AiMission::Update();
	Execute();
}
