#include "GameCommon.h"

#include "..\fun3d\AiMission.h"
#include "..\fun3d\Recycler.h"
#include "..\fun3d\ScriptUtils.h"

/*
	Misn14Mission
*/

class Misn14Mission : public AiMission {
	DECLARE_RTIME(Misn14Mission)
public:
	Misn14Mission(void);
	~Misn14Mission();

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
				start_done,camera1,camera2,camera3,
				alien_warning,alien_attack,cca_surrender,gen_message,
				rescue_message,rescue_start,rescue_reminder,
				found,pick_up,won,lost,
				finishcam1,finishcam2,finishcam3,
				rescuecam1,rescuecam2,rescuecam3,
				rescue1,rescue2,rescue3,
				b_last;
		};
		bool b_array[24];
	};

	// floats
	union {
		struct {
			float
				camera_time,alien_time,pick_up_time,
				beacon_time1,beacon_time2,beacon_time3,
				rescue_finish1,rescue_finish2,
				rescue_finish3,next_second,
				f_last;
		};
		float f_array[10];
	};

	// handles
	union {
		struct {
			Handle
				beacon1,beacon2,beacon3,audmsg,
				player,recy,cam1,cam2,cam3,cam4,erecy,base,apc,
				guy1,guy2,guy3,tow1,tow2,tow3,tow4,
				h_last;
		};
		Handle h_array[20];
	};

	// integers
	union {
		struct {
			int
				wave_count,
				i_last;
		};
		int i_array[1];
	};
};

void Misn14Mission::Setup(void)
{
	wave_count=0;
	start_done=false;
	camera1=false;
	camera2=false;
	camera3=false;
	alien_attack=false;
	alien_warning=false;
	cca_surrender=false;
	gen_message=false;
	rescue_reminder=false;
	rescue_message=false;
	rescue_start=false;
	found=false;
	beacon1=NULL;
	beacon2=NULL;
	beacon3=NULL;
	rescue1=false;
	rescue2=false;
	rescue3=false;
	won=false;
	lost=false;
	pick_up=false;
	rescuecam1=false;
	rescuecam2=false;
	rescuecam3=false;
	finishcam1=false;
	finishcam2=false;
	finishcam3=false;
	alien_time=99999.0f;
	pick_up_time=99999.0f;
	beacon_time1=99999.0f;
	beacon_time2=99999.0f;
	beacon_time3=99999.0f;
	rescue_finish1=99999.0f;
	rescue_finish2=99999.0f;
	rescue_finish3=99999.0f;

	// Initialize the darned handles
	beacon1 = 0;
	beacon2 = 0;
	beacon3 = 0;
	audmsg = 0;
	player = 0;
	recy = 0;
	cam1 = 0;
	cam2 = 0;
	cam3 = 0;
	cam4 = 0;
	erecy = 0;
	base = 0;
	apc = 0;
	guy1 = 0;
	guy2 = 0;
	guy3 = 0;
	tow1 = 0;
	tow2 = 0;
	tow3 = 0;
	tow4 = 0;
}

void Misn14Mission::AddObject(Handle h)
{
	if (
		(IsOdf(h, "avapc")) &&
		(GetTeamNum(h) == 1) 
		)
	{
		found = true;
		apc= h;
	}

}

void Misn14Mission::Execute(void)
{
	//GameObject *fcycler,*ecycler;
	player=GetPlayerHandle();
	if (!start_done)
	{
		recy=GetHandle("avrecy-1_recycler");
		erecy=GetHandle("svrecy-1_recycler");
		base=GetHandle("sbbarr0_i76building");
		SetAIP("misn14.aip");
		//AddPilot(1,10);
		AddPilot(2,30);
		SetScrap(1,30);
		SetScrap(2,45);
		cam1=GetHandle("apcamr0_camerapod");
		cam2=GetHandle("apcamr1_camerapod");
		cam3=GetHandle("apcamr2_camerapod");
		cam4=GetHandle("apcamr3_camerapod");
		tow1=GetHandle("sbtowe0_turret");
		tow2=GetHandle("sbtowe1_turret");
		tow3=GetHandle("sbtowe55_turret");
		tow4=GetHandle("sbtowe56_turret");
		if (cam1!=NULL) GameObjectHandle::GetObj(cam1)->SetName("Foothill Geysers");
		if (cam2!=NULL) GameObjectHandle::GetObj(cam2)->SetName("Canyon Geysers");
		if (cam3!=NULL) GameObjectHandle::GetObj(cam3)->SetName("CCA Base");
		if (cam4!=NULL) GameObjectHandle::GetObj(cam4)->SetName("Plateau Geysers");
		start_done=true;
		next_second=GetTime()+1.0f;
		camera1=true;
		CameraReady();
		camera_time=GetTime()+12.0f;
		audmsg=AudioMessage("misn1401.wav");
		if (IsAlive(base))
		{
			GameObjectHandle::GetObj(base)->SetMaxHealth(100000.0f);
			next_second=GetTime()+1.0f;

		}


	}	
	if (camera1)
	{
		CameraPath("cam_path1",2000,1000,recy);
	}
	if ((camera1) && ((GetTime()>camera_time) || CameraCancelled()))
	{
	//	StopAudioMessage(audmsg); 
	// Now the message is longer and see below
		camera1=false;
		camera2=true;
		camera_time=GetTime()+15.0f;
	//	audmsg=AudioMessage("misn1402.wav");
	// The above message is part of the first..
	}
	if (camera2)
	{
		CameraPath("cam_path2",2000,500,recy);
	}
	if ((camera2) && ((GetTime()>camera_time) || CameraCancelled()))
	{
		StopAudioMessage(audmsg);
		camera2=false;
		CameraFinish();
		ClearObjectives();
		AddObjective("misn1401.otf",WHITE);
		alien_time=Get_Time()+720.0f;  // six minutes to alien arrival
		beacon_time1=GetTime()+15.0f;
	}
	/*
		Rescue the
		NSDF
	*/	
	if (GetTime()>beacon_time1)
	{
		AudioMessage("misn1416.wav");
		beacon_time1=99999.0f;
		beacon1=BuildObject("apcamr",1,"rescue1");
		guy1=BuildObject("aspilo",1,"help1");
		guy2=BuildObject("aspilo",1,"help2");
		guy3=BuildObject("aspilo",1,"help3");
		Defend(guy1);
		Defend(guy2);
		Defend(guy3);
		SetObjectiveName(beacon1,"Rescue 1");
		SetObjectiveOn(beacon1);
	}
	if ((beacon1!=NULL) 
		&& (GetDistance(player,beacon1)<200.0f)
		&& (!rescue_reminder) && (GetDistance(apc,beacon1)>300.0f))
	{
		/*
			Bring in an APC to 
			rescue the survivors.
		*/
		AudioMessage("misn1415.wav");
		rescue_reminder=true;
	}
	if (
		(!lost) &&
		(beacon1!=NULL) && (!rescue1) &&
		((!IsAlive(guy1)) || (!IsAlive(guy2)) || (!IsAlive(guy3)))
		)
	{
		AudioMessage("misn1421.wav");
		FailMission(GetTime()+15.0f,"misn14l2.des");
		lost=true;
	}


	if ((beacon1!=NULL) && (apc!=NULL) && (!rescue1)
		&& (GetDistance(apc,beacon1)<100.0f))
	{
		rescue1=true;
		Goto(guy1,beacon1);
		Goto(guy2,beacon1);
		Goto(guy3,beacon1);
		rescue_finish1=GetTime()+25.0f;
		AudioMessage("misn1409.wav");
		camera_time=GetTime()+3.0f;
		CameraReady();
		rescuecam1=true;
	}
	if (rescuecam1)
	{
		CameraObject(apc,1000,1000,1000,apc);
		if (CameraCancelled() || (GetTime()>camera_time))
		{
			CameraFinish();
			rescuecam1=false;
		}
	}
	if ((beacon1!=NULL) && (rescue1)
		&& (rescue_finish1<GetTime()))
	{
		/*
			We're done here
		*/
		if (IsAlive(guy1)) 
			RemoveObject(guy1);
		if (IsAlive(guy2)) RemoveObject(guy2);
		if (IsAlive(guy3)) RemoveObject(guy3);
		if (IsAlive(beacon1)) RemoveObject(beacon1);
		beacon_time2=GetTime()+10.0f;
		CameraReady();
		AudioMessage("misn1417.wav");
		finishcam1=true;
		rescue_finish1=99999.0f;
		camera_time=GetTime()+3.0f;
	}
	if (finishcam1)
	{
		CameraObject(apc,1000,1000,1000,apc);
		if (CameraCancelled() || (GetTime()>camera_time))
		{
			CameraFinish();
			finishcam1=false;
		}
	}
	if (GetTime()>beacon_time2)
	{
		beacon_time2=99999.0f;
		beacon2=BuildObject("apcamr",1,"rescue2");
		guy1=BuildObject("aspilo",1,"help4");
		guy2=BuildObject("aspilo",1,"help5");
		guy3=BuildObject("aspilo",1,"help6");
		Defend(guy1);
		Defend(guy2);
		Defend(guy3);
		SetObjectiveName(beacon2,"Rescue 2");
		SetObjectiveOn(beacon2);
	}
	if (
		(!lost) &&
		(beacon2!=NULL) && (!rescue2) &&
		((!IsAlive(guy1)) || (!IsAlive(guy2)) || (!IsAlive(guy3)))
		)
	{
		lost=true;
		AudioMessage("misn1421.wav");
		FailMission(GetTime()+15.0f,"misn14l2.des");
	}
	if ((beacon2!=NULL) && (apc!=NULL) && (!rescue2)
		&& (GetDistance(apc,beacon2)<100.0f))
	{
		rescue2=true;
		Goto(guy1,beacon2);
		Goto(guy2,beacon2);
		Goto(guy3,beacon2);
		rescue_finish2=GetTime()+25.0f;
		AudioMessage("misn1409.wav");
	}
	if ((beacon2!=NULL) && (rescue2)
		&& (rescue_finish2<GetTime()))
	{
		/*
			We're done here
		*/
		if (IsAlive(guy1)) RemoveObject(guy1);
		if (IsAlive(guy2)) RemoveObject(guy2);
		if (IsAlive(guy3)) RemoveObject(guy3);
		if (IsAlive(beacon2)) RemoveObject(beacon2);
		AudioMessage("misn1418.wav");
		rescue_finish2=99999.0f;

		beacon_time3=GetTime()+10.0f;
	}
	if (GetTime()>beacon_time3)
	{
		beacon_time3=99999.0f;
		beacon3=BuildObject("apcamr",1,"rescue3");
		guy1=BuildObject("aspilo",1,"help7");
		guy2=BuildObject("aspilo",1,"help8");
		guy3=BuildObject("aspilo",1,"help9");
		Defend(guy1);
		Defend(guy2);
		Defend(guy3);
		SetObjectiveName(beacon3,"Rescue 3");
		SetObjectiveOn(beacon3);
	}
		if (
			(!lost) &&
		(beacon3!=NULL) && (!rescue3) &&
		((!IsAlive(guy1)) || (!IsAlive(guy2)) || (!IsAlive(guy3)))
		)
	{
		lost=true;
		AudioMessage("misn1421.wav");
		FailMission(GetTime()+15.0f,"misn14l2.des");
	}

	if ((beacon3!=NULL) && (apc!=NULL) && (!rescue3)
		&& (GetDistance(apc,beacon3)<100.0f))
	{
		rescue3=true;
		Goto(guy1,beacon3);
		Goto(guy2,beacon3);
		Goto(guy3,beacon3);
		rescue_finish3=GetTime()+25.0f;
		AudioMessage("misn1409.wav");
	}

	if ((beacon3!=NULL) && (rescue3)
		&& (rescue_finish3<GetTime()))
	{
		/*
			We're done here
		*/
		if (IsAlive(guy1)) RemoveObject(guy1);
		if (IsAlive(guy2)) RemoveObject(guy2);
		if (IsAlive(guy3)) RemoveObject(guy3);
		if (IsAlive(beacon3)) RemoveObject(beacon3);
		AudioMessage("misn1419.wav");
		rescue_finish3=99999.0f;
	}
	/*
		We need to keep the base
		alive so the game can finish.
	*/
	if (IsAlive(base))
	{
		if (GetTime()>next_second)
		{
			GameObjectHandle::GetObj(base)->AddHealth(5000.0f);
			next_second=GetTime()+1.0f;
		}
	}


	/*
		The aliens are on
		the way and ready to
		give us grief.
	*/
	if (Get_Time()>alien_time)
	{
		alien_attack=true;
		wave_count++;
		int x=rand()%3;
		switch (x) {
			case 0:
				BuildObject("hvsav",3,"alien1");
				BuildObject("hvsav",3,"alien2");
				BuildObject("hvsav",3,"alien5");
				break;
			case 1:
				BuildObject("hvsav",3,"alien3");
				BuildObject("hvsav",3,"alien4");
				BuildObject("hvsav",3,"alien1");
				break;
			case 2:
				BuildObject("hvsav",3,"alien5");
				BuildObject("hvsav",3,"alien6");
				BuildObject("hvsav",3,"alien3");
				break;
		}
		alien_time=Get_Time()+180.0f;  // was 70.0, now we explore
	}
	if ((alien_attack) && (!alien_warning))
	{
		AudioMessage("misn1403.wav");
		alien_warning=true;
	}

	if ((wave_count>2) && (!cca_surrender))
	{
		AudioMessage("misn1404.wav");
		AudioMessage("misn1405.wav");  // it's a trick!
		cca_surrender=true;
		/*
			Here is where we should
			switch sides or destroy people.
		*/
		ObjectList &list = *GameObject::objectList;
		for (ObjectList::iterator i = list.begin(); i != list.end(); i++) 
		{
			Handle h;
			GameObject *o = *i;
			h=GameObjectHandle::Find(o);
			OBJ76 *obj76 = o->GetOBJ76();
			if ((IsCraft(obj76)) && (o->GetTeam()==2))
			{
				o->SetTeam(0);  // crazy!!  team 0 now
				if ((IsOdf(h,"svtank")) 
					|| (IsOdf(h,"svturr"))
					|| (IsOdf(h,"svfigh")))
				{
					Retreat(h,"escape",1);  //run away
				}
			}			
		}
		/*
			Convert the russian base
		*/
		GameObject *ob=GameObjectHandle::GetObj(base);
		if (IsAlive(base)) ob->SetTeam(1);
		if (IsAlive(tow1))
		{
			ob=GameObjectHandle::GetObj(tow1);
			ob->SetTeam(1);
		}
		if (IsAlive(tow2))
		{
			ob=GameObjectHandle::GetObj(tow2);
			ob->SetTeam(1);
		}
		if (IsAlive(tow3))
		{
			ob=GameObjectHandle::GetObj(tow3);
			ob->SetTeam(1);
		}
		if (IsAlive(tow4))
		{
			ob=GameObjectHandle::GetObj(tow4);
			ob->SetTeam(1);
		}

	}
	if ((wave_count>3) && (!gen_message) && (rescue3))
	{
		SetScrap(2,0);
		audmsg=AudioMessage("misn1406.wav");
		gen_message=true;
		Handle foe= GetNearestEnemy(player);
		if (GetDistance(player,foe)>150.0f) 
		{
			camera3=true;
			camera_time=Get_Time()+20.0f;
			CameraReady();
		}
		else camera3=false;
	}
	if (camera3)
	{
		CameraPath("camera_path",2500,300,base);
	}
	if ((camera3) && ((Get_Time()>camera_time)  || CameraCancelled()))
	{
		StopAudioMessage(audmsg);
		camera3=false;
		CameraFinish();
	}
	/*
		Now we need you 
		to rescue CCA personel
	*/
	if ((wave_count>4) && (!rescue_message) && (rescue3))
	{
		SetScrap(2,0);
		AudioMessage("misn1407.wav");
		rescue_message=true;
		if (IsAlive(base))
		{
			SetObjectiveOn(base);
			SetObjectiveName(base,"Rescue CCA");
		}
		else
		{
			// just in case its not there
			FailMission(5.0,"misn14l.des");
		}
	}

	if ((wave_count>4) && (found) && (!rescue_start) && (rescue3))
	{
		/*
			Now that you've built 
			an APC, get it to the 
			base to rescue the soviet scientists
			AudioMessage
		*/
		AudioMessage("misn1408.wav");
		rescue_start=true;
	}
	if ((!pick_up) && (rescue_start) && (GetDistance(apc,base)<200.0f))
	{
		/* 
			AudioMessage ..
			We're picking up the 
			key personel..
		*/
		pick_up=true;
		pick_up_time=Get_Time()+15.0f;
		AudioMessage("misn1409.wav");
	}
	if ((pick_up) && (Get_Time()>pick_up_time))
	{
		/*
			Audio Message
			Ready to go.  
		*/
		
		pick_up_time=99999.0f;
		AudioMessage("misn1410.wav");
	}
	if ((!lost) && (pick_up) && (!IsAlive(apc)))
	{
		/*
			Lost the APC with the 
			Russian scientists-- you 
			lose.  
			*/
		AudioMessage("misn1412.wav");
		AudioMessage("misn1413.wav");
		FailMission(GetTime()+10.0f,"misn14l3.des");
		lost=true;

	}
	if ((!won) && (pick_up) && (GetDistance(recy,apc)<300.0f))
	{
		/*
			You won..
		*/
		won=true;
		SucceedMission(GetTime()+10.0f,"misn14w1.des");

		AudioMessage("misn1411.wav");
	}
	if ((!lost) && (!IsAlive(recy)))
	{
		AudioMessage("misn1414.wav");
		FailMission(GetTime()+10.0f,"misn14l1.des");
		lost=true;
	}

}
IMPLEMENT_RTIME(Misn14Mission)

Misn14Mission::Misn14Mission(void)
{
}

Misn14Mission::~Misn14Mission()
{
}

void Misn14Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

bool Misn14Mission::Load(file fp)
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
	for (int i = 0; i < f_count; i++) {
		if (f_array[i] == 9999.0f)
			f_array[i] = 99999.0f;
	}

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

bool Misn14Mission::PostLoad(void)
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

bool Misn14Mission::Save(file fp)
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

void Misn14Mission::Update(void)
{
	AiMission::Update();
	Execute();
}
