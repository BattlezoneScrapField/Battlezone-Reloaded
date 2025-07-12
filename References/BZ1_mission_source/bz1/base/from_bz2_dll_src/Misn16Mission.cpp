#include "GameCommon.h"
#include "..\fun3d\AiMission.h"
#include "..\fun3d\ScriptUtils.h"

/*
	Misn16Mission
*/



class Misn16Mission : public AiMission {
	DECLARE_RTIME(Misn16Mission)
public:
	Misn16Mission(void);
	~Misn16Mission();

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
				counter,start_done,rcam,won,lost,camera1,
				b_last;
		};
		bool b_array[6];
	};

	// floats
	union {
		struct {
			float
				next_reinforcement,rcam_time,start_time,alien_wave,
				counter_strike2,wave_gap,cam_time1,alien_wave1,finish_cam,
				f_last;
		};
		float f_array[9];
	};

	// handles
	union {
		struct {
			Handle
				base1,base2,reinfo1,reinfo2,newbie,recy,	
				muf,audmsg1,audmsg2,
				cam1,cam2,cam3,cam4,cam5,
				sat1,sat2,sat3,
				tow1,tow2,tow3,tow4,
				h_last;
		};
		Handle h_array[21];
	};

	// integers
	union {
		struct {
			int
				rtype,rcount, // type of reinforcement, count 
				i_last;
		};
		int i_array[2];
	};
};

void Misn16Mission::Setup(void)
{

	rcount=0;
	newbie=NULL;  // if we haven't found one there isn't
					// one
	start_done=false;
	rcam=false;
	start_time=99999.0f;
	rcam_time=99999.0f;
	alien_wave=99999.0f;
	finish_cam=99999.0f;
	alien_wave1=99999.0f;
	wave_gap=150.0f;  // two & a half minutes
	counter_strike2=999999.0f;
    camera1=false;
    cam_time1=99999.0f;
	counter=false;
	won=false;
	lost=false;
}

void Misn16Mission::AddObject(Handle h)
{
	/*
		Whenever a new soviet unit
		is added, that unit storms
		toward the alien base.  
	*/
	if 
			(GetTeamNum(h) == 1) 
	if

			(
				(IsOdf(h, "svtank")) ||
				(IsOdf(h,"svturr")) ||
				(IsOdf(h,"svfigh")) ||
				(IsOdf(h,"svwalk"))
			)
	    
		
	{

		if (rand()%2==0)
		{
			Attack(h,base1,0);
		}
			else Attack(h,base2,0);
		newbie=h;  // so we always have one to key on
	}
	else 
		if ((IsOdf(h,"svscav")) ||	
			(IsOdf(h,"svhaul")))
		{
			if (rand()%2==0)
			{
				Goto(h,base1,0);
			}
			else Goto(h,base2,0);
			newbie=h;  // so we always have one to key on
		}

}

void Misn16Mission::Execute(void)
{
	Handle player=GetPlayerHandle();
	if (!start_done)
	{
		audmsg1=AudioMessage("misn1601.wav");
		audmsg2=AudioMessage("misn1602.wav");
		recy=GetHandle("avrecy0_recycler");
		next_reinforcement=GetTime()+120.0f;  //should be 120
		rtype=rand()%2+1;  // wimpy reinforcements, type 1 or 0
		start_done=true;
		base1=GetHandle("alien_hq");
		base2=GetHandle("alien_hangar");
		SetScrap(1,50);
		SetAIP("misn16.aip");
		ClearObjectives();
		AddObjective("misn1601.otf", WHITE);
		alien_wave=GetTime()+60.0f;
		alien_wave1=GetTime()+90.0f;
		cam1=GetHandle("apcamr12_camerapod");
		cam2=GetHandle("apcamr15_camerapod");
		cam3=GetHandle("apcamr13_camerapod");
		cam4=GetHandle("apcamr11_camerapod");
		if (cam1!=NULL) SetObjectiveName(cam1,"NW Geyser");
		if (cam2!=NULL) SetObjectiveName(cam2,"Foothill Geysers");
		if (cam3!=NULL) SetObjectiveName(cam3,"Geyser Site");
		if (cam4!=NULL) SetObjectiveName(cam4,"Alien HQ");
		tow1=GetHandle("sbtowe0_turret");
		tow2=GetHandle("sbtowe1_turret");
		tow3=GetHandle("sbtowe2_turret");
		tow4=GetHandle("sbtowe3_turret");
		sat1=GetHandle("hvsat0_wingman");
		sat2=GetHandle("hvsat1_wingman");
		sat3=GetHandle("hvsat2_wingman");
		if (sat1!=NULL) Defend(sat1,1);
		if (sat2!=NULL) Defend(sat2,1);
		if (sat3!=NULL) Defend(sat3,1);

		muf=GetHandle("avmuf26_factory");
        camera1=true;
		cam_time1=GetTime()+20.0f;
        CameraReady();
	}
    if (camera1)
	{
		CameraPath("camera_path1",4000,500,base2);
	}
	if ((camera1) && (CameraCancelled() ||
		(GetTime()>cam_time1) || IsAudioMessageDone(audmsg2)))
	{
		camera1=false;
		CameraFinish();
	}
	if (GetTime()>next_reinforcement)
	{
		rcount++;
		if (rcount<10)
		{
			switch (rtype)
			{
			case 1:
				/*
					The thriteenth workers 
					hauling battilion
				*/
				AudioMessage("misn1603.wav");
				BuildObject("svfigh",1,"starta");
				BuildObject("svhaul",1,"starta2");
				BuildObject("svhaul",1,"starta3");
				break;
			case 2:
				/*
					Eighth scrap auxilliries
				*/
				AudioMessage("misn1604.wav");
				BuildObject("svscav",1,"startb");
				BuildObject("svscav",1,"startb2");
				BuildObject("svfigh",1,"startb3");
				break;
			case 3:
				/*
					Remenants of various units
				*/
				AudioMessage("misn1605.wav");
				BuildObject("svscav",1,"starta");
				BuildObject("svturr",1,"starta2");
				BuildObject("svfigh",1,"starta3");
				break;
			case 4:
				/*
					A scout unit
				*/
				AudioMessage("misn1606.wav");
				BuildObject("svfigh",1,"startb");
				BuildObject("svfigh",1,"startb2");
				break;
			case 5:
				/*
					A light armor unit
				*/
				AudioMessage("misn1607.wav");
				BuildObject("svfigh",1,"starta");
				BuildObject("svfigh",1,"starta2");
				BuildObject("svtank",1,"starta3");
			case 6:
				/* 
					A strike wing
				*/
				AudioMessage("misn1607.wav");
				BuildObject("svtank",1,"startb");
				BuildObject("svtank",1,"startb2");
				BuildObject("svtank",1,"startb3");
			//	BuildObject("svfigh",1,"reinforce24");
				break;
			case 7:
				/*
					Heavy armor
				*/
				AudioMessage("misn1608.wav");
				BuildObject("svwalk",1,"starta");
				BuildObject("svwalk",1,"starta2");
				BuildObject("svwalk",1,"starta3");
			//	BuildObject("svtank",1,"reinforce14");
				break;
			}

			// all times after the first its random
			rtype=rand()%7+1;
			next_reinforcement=GetTime()+180.0f;
			start_time=GetTime()+2.0f;  // give time for units to exist
		}
		else 
		{
			//AudioMessage("misn1614.wav");
		}
	}
	if (GetTime()>start_time)
	{
		Handle enemy;
		if (IsAlive(player))   // better safe then sorry
			enemy=GetNearestEnemy(player);
		if (GetDistance(player,enemy)>150.0f)  // if safe do cineractive
		{
			rcam=true;
			rcam_time=GetTime()+4.0f;
			CameraReady();
		}
		start_time=99999.0f;
	}
	if (rcam)
	{
		CameraObject(newbie,0,2000,3000,newbie);
	}
	if (rcam && ((rcam_time<GetTime()) || CameraCancelled()))
	{
		rcam=false;
		CameraFinish();
		rcam_time=99999.0f;
	}

	if (GetTime()>alien_wave)
	{
		BuildObject("hvsav",2,base2);
		alien_wave=GetTime()+wave_gap;
		if (wave_gap>60.0f) wave_gap=wave_gap-5.0f;
	}
	if (GetTime()>alien_wave1)
	{
		Handle sat=BuildObject("hvsat",2,"sat1");
		Goto(sat,"strike1");
		sat=BuildObject("hvsat",2,"sat2");
		Goto(sat,"strike2");
		alien_wave1=alien_wave+90.0f;
	}
	/*	
		If the user
		is winning turn up
		the heat.
	*/
	if ((!won) && (!lost) && (!counter) &&

		(
		((!IsAlive(tow1)) && (!IsAlive(tow2)))
			||
		((!IsAlive(tow3)) && (!IsAlive(tow4)))
			|| 
		(!IsAlive(base1)) || (!IsAlive(base2)))

		)
	{
		/*
			That means one of the
			entrances is open.
			Counter attack!!
		*/
		Handle sav1=BuildObject("hvsav",2,base2);
		Handle sav2=BuildObject("hvsav",2,base2);
//		Handle sav3=BuildObject("hvsav",2,base2);
		Attack(sav1,muf,1);
		Attack(sav2,muf,1);
//		Attack(sav3,muf,1);
		counter=true;
		counter_strike2=GetTime()+120.0f;  // another killer attack
	}
	if (GetTime()>counter_strike2)
	{
		Handle sav1=BuildObject("hvsav",2,base2);
		Handle sav2=BuildObject("hvsav",2,base2);
//		Handle sav3=BuildObject("hvsav",2,base2);
		Attack(sav1,recy,1);
		Attack(sav2,recy,1);
//		Attack(sav1,recy,1);
		counter_strike2=99999.0f;
	}
	if ((!won) && (!IsAlive(base1)) 
		&& (!IsAlive(base2)))
	{
		/*
			We've destroyed the 
			alien building facillity
		*/

		AudioMessage("misn1613.wav");
		won=true;
		SucceedMission(GetTime()+15.0f,"misn16w1.des");
	}

	if ((!lost) && (!IsAlive(recy)))
	{

		/*
			We've lost the
			utah.  The soviets
			are withdrawing
		*/

		AudioMessage("misn1612.wav");
		lost=true;
		FailMission(GetTime()+15.0f,"misn16l1.des");
	}

}

IMPLEMENT_RTIME(Misn16Mission)

void Misn16Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}


Misn16Mission::Misn16Mission(void)
{
}

Misn16Mission::~Misn16Mission()
{
}

bool Misn16Mission::Load(file fp)
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

bool Misn16Mission::PostLoad(void)
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

bool Misn16Mission::Save(file fp)
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

void Misn16Mission::Update(void)
{
	AiMission::Update();
	Execute();
}
