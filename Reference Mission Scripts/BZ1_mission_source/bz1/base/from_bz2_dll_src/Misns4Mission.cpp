#include "GameCommon.h"

#include "..\fun3d\AiMission.h"
#include "..\fun3d\ScriptUtils.h"

/*
	Misns4Mission
*/

class Misns4Mission : public AiMission {
	DECLARE_RTIME(Misns4Mission)
public:
	Misns4Mission(void);
	~Misns4Mission();

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
				counter,first,first_bridge,warning,bridge_clear,won,lost,
				start_done,north_bridge,convoy_alive[10],safe[10],
				b_last;
		};
		bool b_array[29];
	};

	// floats
	union {
		struct {
			float
				wakeup_time,convoy_time,attack_time,raider_time,army_time,
				counter_time,
				f_last;
		};
		float f_array[6];
	};

	// handles
	union {
		struct {
			Handle
				convoy_handle[10],cam1,t1,t2,b1,b2,h1,h2,
				counter1,counter2,counter3,counter4,
				h_last;
		};
		Handle h_array[21];
	};

	// integers
	union {
		struct {
			int
				convoy_total,convoy_count,convoy_dead,win_count,
				i_last;
		};
		int i_array[4];
	};
};

void Misns4Mission::Setup(void)
{
	counter=false;
	warning=false;
	first_bridge=false;
	first=false;
	start_done=false;
	won=false;
	lost=false;
	north_bridge=false;
	bridge_clear=false;
	wakeup_time=99999.0f;
	raider_time=99999.0f;
	convoy_time=99999.0f;
	attack_time=99999.0f;
	counter_time=99999.0f;
	convoy_count=0;
	convoy_dead=0;
	convoy_total=5;
	counter1=NULL;
	counter2=NULL;
	counter3=NULL;
	counter4=NULL;
	win_count=0;
	int count;
	for (count=0;count<convoy_total;count++)
	{
		convoy_alive[count]=true;
		safe[count]=false;
		convoy_handle[count]=NULL;
	}
}

void Misns4Mission::AddObject(Handle h)
{
	if ((GetTeamNum(h) == 1) &&
		(IsOdf(h, "svhaul")))
	{
		convoy_handle[convoy_count]=h;
		convoy_count++;
		Goto(h,"escort");
	}

}

void Misns4Mission::Execute(void)
{
	Handle player=GetPlayerHandle();
	int count;
	/*
		Notes
		'escort' is the path you need to escort 
		things down
		'spawn1' is where they start
		'spawn2' is where enemy artillery starts
		'spawn3' is where enemy tanks, etc. start
	*/
	
	if (!start_done)
	{
		start_done=true;
		convoy_time=GetTime()+420.0f;
		wakeup_time=GetTime()+30.0f;
		BuildObject("avartl",2,"spawn2");
		cam1=BuildObject("spcamr",1,"camerapt");
		raider_time=GetTime()+30.0f;
		army_time=GetTime()+100.0f;
		AddScrap(1,50);
		SetPilot(1,30);
		SetPilot(2,30);
		ClearObjectives();
		AddObjective("misns4.otf",WHITE);
		AudioMessage("misns401.wav");
		AudioMessage("misns410.wav");
		StartCockpitTimer(420,300,0);	
		GameObjectHandle::GetObj(cam1)->SetName("Bridge");
		BuildObject("abtowe",2,"tower1");
		BuildObject("abtowe",2,"tower2");
		BuildObject("ablpow",2,"power1");
		BuildObject("ablpow",2,"power2");
		BuildObject("svcnst",1,"svcnst");
	}
	if (GetTime()>wakeup_time)
	{
		Handle h=BuildObject("avfigh",2,"spawn4");
		Goto(h,"wakeup"); // a little reminder
		wakeup_time=99999.0f;
	}
	if (GetTime()>convoy_time)
	{
		if (!first)
		{
			AudioMessage("misns402.wav");
			StopCockpitTimer();
			HideCockpitTimer();
			first=true;
		}
		Handle hauler=BuildObject("svhaul",1,"spawn1");
		SetObjectiveOn(hauler);
		if (convoy_count<convoy_total)
		{
			convoy_time=GetTime()+45.0f;
		}
		else
			convoy_time=99999.0f;
	}
	if (GetTime()>raider_time)
	{
		BuildObject("avfigh",2,"spawn4");
		BuildObject("avfigh",2,"spawn4");
	//	BuildObject("avltnk",2,"spawn4");
		raider_time=99999.0f;
	}
	if (GetTime()>army_time)
	{
		t1=BuildObject("avtank",2,"sbridge");
		t2=BuildObject("avtank",2,"sbridge");
		b1=BuildObject("avhraz",2,"sbridge");
	//	b2=BuildObject("avhraz",2,"sbridge");
		army_time=99999.0f;
	}

	/*
		At some point later
		add more forces north
		of the bridge
		at spawn3
	*/
	if ((!north_bridge) &&
		(GetDistance(player,"sbridge")<200.0f))
	{
		north_bridge=true;
	//	BuildObject("avtank",2,"spawn3");
		BuildObject("avltnk",2,"spawn3");
		BuildObject("avturr",2,"spawn3");
		BuildObject("avscav",2,"spawn3");
		BuildObject("avrecy",2,"spawn3");
		/*
			Now load an AIP.
		*/
	}
	if ((!bridge_clear) &&
		(north_bridge) &&
		(!IsAlive(t1)) && (!IsAlive(t2)) 
		&& (!IsAlive(b1)))
	{
		AudioMessage("misns405.wav");  // wrong message..
		bridge_clear=true;
		SetAIP("misns4.aip");
		counter_time=GetTime()+150.0f;  // counter attack in 2 1/2 minutes
	}
	if ((!warning) && 
		(GetDistance(player,"warn1")<200.0f))
	{
		AudioMessage("misns409.wav");
		warning=true;
	}
	if ((IsAlive(convoy_handle[2])) 
		&& (!counter) &&
		((GetTime()>counter_time) || 
		(GetDistance(convoy_handle[2],"warn1")<200.0f))
		)

	{
		counter1=BuildObject("avrckt",2,"counter");
		counter2=BuildObject("avrckt",2,"counter");
		counter3=BuildObject("avrckt",2,"counter");
		counter4=BuildObject("avrckt",2,"counter");
		Goto(counter1,"sbridge");
		Goto(counter2,"sbridge");
		Goto(counter3,"sbridge");
		Goto(counter4,"sbridge");
		counter=true;
		counter_time=99999.0f;
	}
	for (count=0;count<convoy_total;count++)
	{
		if (convoy_handle[count]!=NULL)
		{
			if ((!IsAlive(convoy_handle[count]))
				&& (convoy_alive[count]))
			{
				/*
					Another one bites the dust
					AudioMessage("transport dead..")
				*/
				AudioMessage("misns403.wav");
				convoy_alive[count]=false;
				convoy_dead++;
				if (convoy_dead>convoy_total/3)
				{
					/*
						That's it
						AudioMessage()
					*/
					FailMission(GetTime()+15.0f,"misns4l1.des");
					/*
						Cineractive 
						on neareset guy to
						the dying guy
					*/
				}


			}
		}
		if ((GetDistance(convoy_handle[count],"goal")<100.0f) && (!safe[count]))
		{
			safe[count]=true;
			win_count++;
		}

	}
	if ((win_count==convoy_total-1) && (!won))
	{
		SucceedMission(GetTime()+10.0f,"misns4w1.des");
		won=true;
	}

}

IMPLEMENT_RTIME(Misns4Mission)

Misns4Mission::Misns4Mission(void)
{
}

Misns4Mission::~Misns4Mission()
{
}

void Misns4Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

bool Misns4Mission::Load(file fp)
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

bool Misns4Mission::PostLoad(void)
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

bool Misns4Mission::Save(file fp)
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

void Misns4Mission::Update(void)
{
	AiMission::Update();
	Execute();
}
