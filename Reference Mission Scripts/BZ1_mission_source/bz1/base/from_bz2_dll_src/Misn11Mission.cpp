#include "GameCommon.h"

#include "..\fun3d\AiMission.h"
#include "..\fun3d\Targeting.h"
#include "..\fun3d\PowerUp.h"
#include "..\fun3d\ScriptUtils.h"


/*
	Misn11Mission
*/


class Misn11Mission : public AiMission {
	DECLARE_RTIME(Misn11Mission)
public:
	Misn11Mission(void);
	~Misn11Mission();

	virtual bool Load(file fp);
	virtual bool PostLoad(void);
	virtual bool Save(file fp);

	virtual void Update(void);

private:
	void Setup(void);
	void Execute(void);

	// bools
	union {
		struct {
			bool
				won,lost,
				launch_gone,escape_start,last_wave,
				got_there1,got_there2,got_there3,
				escape_path,start_done,betrayal,pursuit_warning,betrayal_message,
				check1,check2,restart,launch_attack,
				b_last;
		};
		bool b_array[17];
	};

	// floats
	union {
		struct {
			float
				escape_time,last_wave_time,
				camera_time,betrayal_time,start_delay,
				f_last;
		};
		float f_array[5];
	};

	// handles
	union {
		struct {
			Handle
				player,recy,cam1,cam2,cam3,cam4,tug1,tug2,
				turr1,turr2,turr3,openh,launch,launch2,tank1,tank2,
				h_last;
		};
		Handle h_array[16];
	};

	// integers
	union {
		struct {
			int
				audmsg,
				i_last;
		};
		int i_array[1];
	};
};

void Misn11Mission::Setup(void)
{
	tank1=NULL;
	tank2=NULL;
	escape_start=false;
	last_wave=false;
	start_done=false;
	betrayal=false;
	check1=false;
	check2=false;
	restart=false;
	betrayal_message=false;
	pursuit_warning=false;
	launch_attack=false;
	escape_path=false;
	launch_gone=false;
	lost=false;
	won=false;
	betrayal_time=99999.0f;
	start_delay=99999.0f;
	escape_time=99999.0f;
	last_wave_time=99999.0f;
	got_there1=false;
	got_there2=false;
	got_there3=false;
}

void Misn11Mission::Execute(void)
{
	player=GetPlayerHandle();
	if (!start_done)
	{
		/*
			-paths
			base
			openheimer
			escape
			units
			avhaul0_tug
			avhaul1_tug
			avhaul2_tug
			-camera
			apcamr3_camerapod
			apcamr4_camerapod
			apcamr5_camerapod
		*/
		/*
			misn1501.wav
			Now that we've captured the SAV relics
			we need to ransport this key technology
			off of Io.  This could win the war for us.
		*/
		tug1=GetHandle("avhaul0_tug");
		tug2=GetHandle("avhaul1_tug");
		openh=GetHandle("avhaul2_tug");
		turr1=GetHandle("svturr2_turrettank");
		turr2=GetHandle("second_blockade");
		turr3=GetHandle("svturr3_turrettank");
		cam1=GetHandle("apcamr3_camerapod");
		cam2=GetHandle("apcamr4_camerapod");
		cam3=GetHandle("apcamr5_camerapod");
		launch=GetHandle("launch_pad");
		launch2=GetHandle("launch_pad2");
		GameObjectHandle::GetObj(cam1)->SetName("Waypoint 1");
		GameObjectHandle::GetObj(cam2)->SetName("Waypoint 2");
		GameObjectHandle::GetObj(cam3)->SetName("Launch Pad");
		GameObject *tug_obj = GameObjectHandle::GetObj(tug1);
		tug_obj->SetObjective(TRUE); 
		tug_obj->SetName("Transport 1"); 
		tug_obj = GameObjectHandle::GetObj(tug2);
		tug_obj->SetObjective(TRUE); 
		tug_obj->SetName("Transport 2"); 
		tug_obj = GameObjectHandle::GetObj(openh);
		tug_obj->SetObjective(TRUE); 
		tug_obj->SetName("Transport 3"); 
	
		SetUserTarget(cam1);
		SetScrap(1,50);
		AudioMessage("misn1101.wav");
		ClearObjectives();
		AddObjective("misn1101.otf",WHITE);
		start_delay=Get_Time()+15.0f;
		start_done=true;
	}
	/*
		Mad Dr. Openheimer 
		has magic shields that
		prevent him from being killer.  
	*/
	if (IsAlive(openh))GameObjectHandle::GetObj(openh)->AddHealth(300.0f);

	if (Get_Time()>start_delay)
	{
		/*
			Moving out!
		*/
		AudioMessage("misn1102.wav");
		start_delay=99999.0f;
		Goto(tug1,"base1",1);
		Goto(tug2,"base1",1);
		Goto(openh,"base1",0);
	}
	/*
		if (isDamaged(tug1) || is damaged(tug2)
		AudioMessage(misn1402)
		get your ass up here and help us out, etc.
	*/
	if ((!betrayal) && (GetDistance(cam1,openh)<50.0f))
	{
		betrayal_time=GetTime()+15.0f;  // when we announce it
		Goto(openh,"openheimer",1);
		betrayal=true;
	}
	if (Get_Time()>betrayal_time)
	{
		betrayal_time=99999.0f;
		AudioMessage("misn1103.wav");  // transport 3 seems to be braking off
		AudioMessage("misn1104.wav");  // farewell capitalist pigs!!
		GameObjectHandle::GetObj(openh)->SetTeam(2);
		Defend(turr1,0);
		Defend(turr3,0);
		AudioMessage("misn1105.wav");
		BuildObject("svfigh",2,"strike1");		
		ObjectList &list = *GameObject::objectList;
		for (ObjectList::iterator i = list.begin(); i != list.end(); i++) 
		{
			GameObject *o=*i;
			Handle h=GameObjectHandle::Find(o);
			if (IsOdf(h,"svfigh"))
			{
				Goto(h,"strike_path1",0);
			}
			
		}
		betrayal_message=true;
		ClearObjectives();
		AddObjective("misn1102.otf",WHITE);
	}
	if ((betrayal_message) && (!pursuit_warning)
		&& (IsAlive(turr1)) && (GetDistance(turr1,player)))
	{
		AudioMessage("misn1106.wav");  // do not pursue..
		pursuit_warning=true;
	}
	if (((GetDistance(cam1,tug1)<50.0f) ||
		(GetDistance(cam1,player)<50.0f))
		&& (!check1))
	{
		check1=true;
		SetUserTarget(cam2);
	}
	if ((GetDistance(tug1,"check2",1)<50.0f)  // was cam2
		&& (!check2))
	{
		/*
			At this point openheimer
			has escaped..
		*/
		GameObject *tug_obj = GameObjectHandle::GetObj(openh);
		if (tug_obj!=NULL)
			tug_obj->SetObjective(FALSE); 
		check2=true;
		SetUserTarget(cam3);
		AudioMessage("misn1107.wav");
		/*
			 Now send another enemy
		*/
		BuildObject("svfigh",2,"strike2");		
		ObjectList &list = *GameObject::objectList;
		for (ObjectList::iterator i = list.begin(); i != list.end(); i++) 
		{
			GameObject *o=*i;
			Handle h=GameObjectHandle::Find(o);
			if (IsOdf(h,"svfigh"))
			{
				Goto(h,"strike_path2",0);
			}
		}
	}
	if ((check2) && (!restart) && (!IsAlive(turr2)))
	{
		AudioMessage("misn1102.wav");
		Goto(tug1,"base2",1);
		Goto(tug2,"base2",1);
		restart=true;
	}
	if ((restart) && (!launch_attack) &&
		(
			(GetDistance(launch,player)<450.0f)
			||
			(GetDistance(launch,tug1)<450.0f))
		)
	{
		tank1=BuildObject("svtank",2,"launch_attack");
		tank2=BuildObject("svtank",2,"launch_attack");
		GameObjectHandle::GetObj(launch)->AddHealth(-0.90f);
		AudioMessage("misn1108.wav");
		Attack(tank1,launch,1);
		Attack(tank2,launch,1);
		/*
		ObjectList &list = *GameObject::objectList;
		for (ObjectList::iterator i = list.begin(); i != list.end(); i++) 
		{
			GameObject *o=*i;
			Handle h=GameObjectHandle::Find(o);
			if (IsOdf(h,"svtank"))
			{
				Attack(h,launch,1); // attack the launch pad
			}
			
		}
		*/
		launch_attack=true;
	}
	if ((launch_attack) && (!IsAlive(launch))
		 && (!launch_gone))
	{
		AudioMessage("misn1109.wav");
		launch_gone=true;
		escape_time=GetTime()+40.0f;
	}
	/*
		If both tanks die
		and somehow
		the launch pad is ok..
		It's not!
	*/
	if ((launch_attack) && (!IsAlive(tank1)) && (!IsAlive(tank2)) 
		&& (IsAlive(launch)))
	{
		RemoveObject(launch);
		launch_gone=true;
		escape_time=GetTime()+10.0f;
	}
	if ((launch_gone) && (GetTime()>escape_time))
	{
		Goto(tug1,"escape");
		Goto(tug2,"escape");
		AudioMessage("misn1110.wav");
		SetObjectiveOn(launch2);
		ClearObjectives();
		AddObjective("misn1103.otf",WHITE);
		SetObjectiveName(launch2,"Launch Pad 2");
		escape_time=99999.0f;
	}
	if ((launch_gone) && ((GetDistance(tug2,cam3)<50.0f) || (!IsAlive(cam3))) // in case cam3 is shot
		&& (!escape_start))
	{
 		escape_start=true;
		last_wave_time=GetTime()+15.0f;
		launch_gone=true;
	}
	if ((!last_wave) && (last_wave_time<GetTime()))
	{
		BuildObject("svfigh",2,"strike2");
		BuildObject("svfigh",2,"strike2");
		ObjectList &list = *GameObject::objectList;
		for (ObjectList::iterator i = list.begin(); i != list.end(); i++) 
		{
			GameObject *o=*i;
			Handle h=GameObjectHandle::Find(o);
			if (IsOdf(h,"svfigh"))
			{
				Attack(h,tug2,1); // attack the launch pad
			}
			
		}
		// we put this one in later
		// cuz we want it to wait
		Handle last_guy=BuildObject("svfigh",2,launch2);
		Attack(last_guy,player);
		BuildObject("avcamr",1,"last_camera");
		last_wave=true;
		last_wave_time=99999.0f;
	}
	if ((!lost) && 
		(
			((!IsAlive(tug1)) || (!IsAlive(tug2)))
			|| 
			((!betrayal) && (!IsAlive(openh)))
		 )
		)
	{
		if (betrayal)
		{
			ClearObjectives();
			AddObjective("misn1102.otf",WHITE);
		}
		AudioMessage("misn1111.wav");
		AudioMessage("misn1112.wav");
		lost=true;
		FailMission(GetTime()+15,"misn11l1.des");
			
	}
	if ((last_wave) && (!got_there1) && 
		(GetDistance(player,launch2)<200.0f))
	{
		got_there1=true;
		// we do each check seperately in case
		// the vehicles get to safety & leave
	}
	if ((last_wave) && (!got_there2) &&
		(GetDistance(tug1,launch2)<200.0f))
	{
		got_there2=true;
	}
	if ((last_wave) && (!got_there3) &&
		(GetDistance(tug2,launch2)<200.0f))
	{
		got_there3=true;
	}
	if ((!won) && (last_wave) 
		&& (IsAlive(tug1)) && (IsAlive(tug2)) &&
		(got_there1) && (got_there2) && (got_there3))
	{
		AudioMessage("misn1113.wav");
		won=true;
		SucceedMission(GetTime()+15,"misn11w1.des");
	}
}

IMPLEMENT_RTIME(Misn11Mission)

Misn11Mission::Misn11Mission(void)
{
}

Misn11Mission::~Misn11Mission()
{
}

bool Misn11Mission::Load(file fp)
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

bool Misn11Mission::PostLoad(void)
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

bool Misn11Mission::Save(file fp)
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

void Misn11Mission::Update(void)
{
	AiMission::Update();
	Execute();
}
