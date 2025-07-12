#include "GameCommon.h"

#include "..\fun3d\AiMission.h"
#include "..\fun3d\ScriptUtils.h"
#include "..\fun3d\Targeting.h"

/*
	Misn15Mission
*/

class Misn15Mission : public AiMission {
	DECLARE_RTIME(Misn15Mission)
public:
	Misn15Mission(void);
	~Misn15Mission();

	virtual bool Load(file fp);
	virtual bool PostLoad(void);
	virtual bool Save(file fp);

	virtual void Update(void);

	virtual void AddObject(GameObject *gameObj);

private:
	void Setup(void);
	void AddObject(Handle h);
	void Execute(void);
	void showStuff();

	// bools
	union {
		struct {
			bool
				found_group1,found_group2,
				got_dough,start_done,cca_here,found,won,lost,camera1,
				camera2,camera3,alien3,
				misn15b,silo_built,tartarus,
				b_last;
		};
		bool b_array[15];
	};

	// floats
	union {
		struct {
			float
				camera_time,second_message,sav_timer,
				rendezvous1,rendezvous2,rcam1,rcam2,
				deny_time1,deny_time2,
				misl_time,check_time,  // not to be confused with miller time!
				f_last;
		};
		float f_array[11];
	};

	// handles
	union {
		struct {
			Handle
				tart,
				player,scav1,scav2,scav3,muf1,tur1,art1,
				scavcam,hov1,audmsg,sat1,sat2,sat3,sat4,sat5,sat6,
				goal,tank,recy,cam1,cam2,cam3,cam4,cam5,cam6,tank1,tank2,
				scav_du_jour,savlist[100],
				h_last;
		};
		Handle h_array[129];
	};

	// integers
	union {
		struct {
			int
				savcount,
				silocount,
				i_last;
		};
		int i_array[2];
	};
};

void Misn15Mission::Setup(void)
{
	found_group1=false;
	found_group2=false;
	silo_built=false;
	tartarus=false;
	got_dough=false;
	start_done=false;
	won=false;
	lost=false;
	cca_here=false;
	camera1=false;
	camera2=false;
	camera3=false;
	second_message=99999.0f;
	sav_timer=99999.0f;
	scavcam=NULL;
	rcam1=99999.0f;
	rcam2=99999.0f;
	alien3=false;
	savcount=0;
	silocount=0;
}

void Misn15Mission::AddObject(Handle h)
{
	/*
		This has lost its relevence
		if it works at all.  
	*/
	if (GetTeamNum(h) == 1) 
	{
		if 
		(IsOdf(h, "avscav"))
		{
			found = true;
			scav_du_jour= h;
		}
		else
			if (IsOdf(h,"absilo"))
			{
				silocount++;
			}
	}

}

void Misn15Mission::showStuff()
{
	ClearObjectives();
	if (cca_here)
	{
		AddObjective("misn1501.otf",GREEN);
	}
	else AddObjective("misn1501.otf",WHITE);
	if (found_group1)
	{
		AddObjective("misn1502.otf",GREEN);
	}
	else AddObjective("misn1502.otf",WHITE);
	if (silo_built)
	{
		AddObjective("misn1503.otf",GREEN);
	}
	else AddObjective("misn1503.otf",WHITE);
	if (won)
	{
		AddObjective("misn1504.otf",GREEN);
	}
	else AddObjective("misn1504.otf",WHITE);
}

void Misn15Mission::Execute(void)
{
	player=GetPlayerHandle();
	if (!start_done)
	{
	//	SetAIP("misn15.aip");
		AddScrap(1,10);
		showStuff();
		if (GetHandle("misn15b")!=NULL ) 
		{	
			misn15b=true;
		}	else misn15b=false;  // is this that map.
		tart=GetHandle("ubtart0_i76building");
		recy=GetHandle("avrecy0_recycler");
		cam1=GetHandle("apcamr0_camerapod");
		cam2=GetHandle("apcamr1_camerapod");
		cam3=GetHandle("apcamr2_camerapod");
		cam4=GetHandle("apcamr3_camerapod");
		cam5=GetHandle("apcamr4_camerapod");
		cam6=GetHandle("apcamr5_camerapod");
		tank1=GetHandle("svtank0_wingman");
		tank2=GetHandle("svtank1_wingman");
		hov1=GetHandle("svapc0_apc");
		goal=GetHandle("eggeizr15_geyser");
		rendezvous1=GetTime()+180.0f;
		rendezvous2=GetTime()+240.0f;
		deny_time1=GetTime()+300.0f;
		deny_time2=GetTime()+400.0f;
		check_time=GetTime()+5.0f;
		/*
			Handle misl=BuildObject("waspmsl",2,cam1);
			VECTOR_3D from_vec,to_vec;
			from_vec=GameObjectHandle::GetObj(misl)->GetOrigin();
			to_vec=GameObjectHandle::GetObj(player)->GetOrigin();
			VECTOR_3D dir=SubVectors(to_vec,from_vec);
			GameObjectHandle::GetObj(misl)->SetFrontVector(dir);
		*/
		/* 
			All the units below
			start frozen
			until you go to 
			them.  
		*/
		/*
			scav1=GetHandle("avscav6_scavenger");
			scav2=GetHandle("avscav7_scavenger");
			scav3=GetHandle("avscav8_scavenger");
			muf1=GetHandle("avmuf0_factory");
			art1=GetHandle("avartl0_howitzer");
			tur1=GetHandle("avturr0_turrettank");
		*/
		if (cam1!=NULL) GameObjectHandle::GetObj(cam1)->SetName("Geyser Site");
		if (cam2!=NULL) GameObjectHandle::GetObj(cam2)->SetName("NW Geyser");
		if (cam3!=NULL) GameObjectHandle::GetObj(cam3)->SetName("NE Geyser");
		if (cam4!=NULL) GameObjectHandle::GetObj(cam4)->SetName("Geyser Site");
		if (cam5!=NULL) GameObjectHandle::GetObj(cam5)->SetName("Supply");
		if (cam6!=NULL) GameObjectHandle::GetObj(cam6)->SetName("Nav Beta");
		Goto(tank1,"tank_path",0);
		Goto(tank2,"tank_path",0);
		Goto(hov1,"tank_path",0);
		audmsg=AudioMessage("misn1501.wav");
		second_message=Get_Time()+2.0f; // was 20.0f
		sav_timer=Get_Time()+120.0f;
		misl_time=40.0f;
		// so that missiles always have a target
		scav_du_jour=recy;
		start_done=true;
		if (cam6!=NULL) SetUserTarget(cam6);
	}
	if ((IsAudioMessageDone(audmsg))
		&& (Get_Time()>second_message))
	{
		/*
			The workers tank
			battalion will help you out. 
		*/
		AudioMessage("misn1502.wav");
		CameraReady();
		camera_time=GetTime()+8.0f;
		second_message=99999.0f;
		camera1=true;
	}
	if (camera1)
	{
		CameraObject(tank1,800,600,1200,tank1);
	}
	if ((camera1) && ((Get_Time()>camera_time) || CameraCancelled()))
	{
		camera1=false;
		CameraFinish();
	}
	if ((!cca_here) && 
		((GetDistance(cam6,tank1)<100.0f) ||
		(GetDistance(cam4,tank1)<100.0f)))
	{
		cca_here=true;
		AudioMessage("misn1503.wav");
		showStuff();
	}
	if ((!found_group1) && (GetTime()>rendezvous1))
	{
		SetUserTarget(cam2);
		AudioMessage("misn1511.wav");
		rendezvous1=99999.0f;
	}

	
	if ((!found_group1) && (GetDistance(cam2,player)<150.0f))  // was 200.0
	{
		/*
			Play a wave that you
			got reinforcements
		*/
	
		AudioMessage("misn1518.wav");
		scavcam=BuildObject("avscav",1,"scav3here");
		BuildObject("avapc",1,"mufhere");
		BuildObject("avturr",1,"turhere");
		found_group1=true;
		showStuff();
		camera2=true;
		rcam1=GetTime()+3.0f;
		CameraReady();
	}
	if (camera2)
	{
		CameraPath("rescue_cam1",1000,0,scavcam);
	}
	
	if ((found_group1) && (GetTime()>rcam1))
	{
		camera2=false;
		rcam1=99999.0f;
		CameraFinish();
	}
	/*
	if ((!found_group2) && (GetTime()>rendezvous2))
	{
		SetUserTarget(cam3);
		AudioMessage("misn1512.wav");
		rendezvous2=99999.0f;
	}
	if ((!found_group2) && (GetDistance(cam3,player)<150.0f)) // was 200.0
	{
		
		//	Play a wave that you
		//	got reinforcements
		
		AudioMessage("misn1514.wav");
		scavcam=BuildObject("avscav",1,"scav1here");
		BuildObject("avscav",1,"scav2here");
		BuildObject("avartl",1,"arthere");
		found_group2=true;
		camera3=true;
		rcam2=GetTime()+3.0f;
		CameraReady();
	}
	if (camera3)
	{
		CameraPath("rescue_cam2",1000,0,scavcam);
	}
	
	if ((found_group2) && (GetTime()>rcam2))
	{
		camera3=false;
		rcam2=99999.0f;
		CameraFinish();
	}
	*/
	/*
		if titan relic found
		and NOT played warning
		AudioMessage("misn1513.wav");
	*/
	if ((!tartarus) && (GetDistance(player,tart)<150.0f))
	{
		tartarus=true;
		AudioMessage("misn1513.wav");
		AudioMessage("misn1514.wav");
	}
	if ((GetTime()>sav_timer) && (savcount<50))  // 50 is the max in case
	{
		
		Handle sav;
		if ((rand()%2)==1)
		{
			sav=BuildObject("hvsav",2,"alien1");
			Attack(sav,scav_du_jour);
		}
		else
		{
			sav=BuildObject("hvsav",2,"alien2");
			Attack(sav,scav_du_jour);
		}
		sav_timer=GetTime()+240.0f;  // was (rand()%5+9)*10.0f;
		savlist[savcount]=sav;
		savcount++;
	}
	/*
		My scheduler
		All the features of the
		Dark Rein AI
		at a fraction of the CPU
		cost.
	*/
	if (GetTime()>check_time)
	{
		int count;
		for (count=0;count<savcount;count++)
		{
			if ((IsAlive(savlist[count]))
				&& (GetCurrentCommand(savlist[count])==CMD_NONE))
			{
				Goto(savlist[count],"alien_path");
			}
		}
		check_time=GetTime()+5.0f;
	}
	/*
		Deny the main scrap
		fields to the 
		enemy.
	*/
	if ((misn15b) && (GetTime()>deny_time1))
	{
		sat1=BuildObject("hvsat",2,"alien1");
		sat2=BuildObject("hvsat",2,"alien1");
		Goto(sat1,"deny1");
		Goto(sat2,"deny1");
		deny_time1=99999.0f;
	}
	/*
		Deny the main scrap
		fields to the 
		enemy.
	*/
	if ((misn15b) && (GetTime()>deny_time2))
	{
		sat1=BuildObject("hvsat",2,"alien2");
		sat2=BuildObject("hvsat",2,"alien2");
		Goto(sat1,"deny2");
		Goto(sat2,"deny2");
		deny_time2=99999.0f;
	}

	if ((!lost) && (!IsAlive(recy)))
	{
		/*
			Message:
			Without the resources,
			Titan is lost.
		*/

		AudioMessage("misn1414.wav");
		lost=true;
		FailMission(GetTime()+10.0f,"misn15l1.des");
	}

	if ((silocount>1) && (!silo_built))
	{
		silo_built=true;
		showStuff();
	}
	if ((!got_dough) && (GetScrap(1)>74))
	{
		ClearObjectives();
		AddObjective("misn1501.otf",GREEN);
		AddObjective("misn1502.otf",GREEN);
		AddObjective("misn1503.otf",GREEN);
		AddObjective("misn1504.otf",GREEN);
		got_dough=true;
		AudioMessage("misn1510.wav");
			/*
				Congratulations
			*/
		SucceedMission(GetTime() +10.0f,"misn15w1.des");
	}


}

IMPLEMENT_RTIME(Misn15Mission)

Misn15Mission::Misn15Mission(void)
{
}

Misn15Mission::~Misn15Mission()
{
}

void Misn15Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

bool Misn15Mission::Load(file fp)
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

bool Misn15Mission::PostLoad(void)
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

bool Misn15Mission::Save(file fp)
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

void Misn15Mission::Update(void)
{
	AiMission::Update();
	Execute();
}
