#include "GameCommon.h"

#include "..\fun3d\AiMission.h"
#include "..\fun3d\PowerUp.h"
#include "..\fun3d\Recycler.h"
#include "..\fun3d\Factory.h"
#include "..\fun3d\Targeting.h"
#include "..\fun3d\ScriptUtils.h"
#include "..\fun3d\AiTask.h"
#include "..\fun3d\AiPath.h"
#include "..\utility\SimCut.h"
#include "..\fun3d\ScriptUtils.h"

#include "..\input\input.h"
#include "..\gamelgc\views.h"

/*
	Tran05Mission
*/

// used by (misn02b.bzn) as first american mission

class Tran05Mission : public AiMission {
	DECLARE_RTIME(Tran05Mission)
public:
	Tran05Mission(void);
	~Tran05Mission();

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
				camera1,
				camera2,
				camera3,
				found,
				found2,
				start_done,
				patrol1,
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
				mission_won,
				mission_lost,
				jump_start,
				b_last;
		};
		bool b_array[25];
	};

	// floats
	union {
		struct {
			float
				last_wave_time,
				wave_timer,
				repeat_time,
				camera_delay,
				dramatic_pause,
				cam_time,
				NextSecond,
				f_last;
		};
		float f_array[7];
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
				bhandle,
				bhome,
				bscav,
				scav2,
				bplayer,
				bgoal,
				bscout,
				lander,
				dummy,  // the base
				bhandle2,
				h_last;
		};
		Handle h_array[17];
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
				num_reps,
				on_point,
				audmsg,
				i_last;
		};
		int i_array[3];
	};
};

void Tran05Mission::Setup(void)
{
	start_done=FALSE;
	camera1=false;
	camera2=false;
	camera3=false;
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
	mission_won=false;
	mission_lost=false;
	found=false;
	found2=false;
	patrol1=false;
	repeat_time=0.0f;
	wave_timer=0.0f;
	last_wave_time=99999.0f;
	num_reps=0;
	dramatic_pause=99999.0f;
	audmsg = 0;
	bscav=NULL;
	scav2 = 0;
	NextSecond=99999.0f;
}

// this is the handle thing brad made for me
void Tran05Mission::AddObject(Handle h)
{
	if (
		(GetTeamNum(h) == 1) &&
		(IsOdf(h, "avscav"))
		&& (bscav==NULL)
		)
	{
		found = true;
		bscav=h;
	}
	if (
		(GetTeamNum(h) == 2) &&
		(IsOdf(h, "svfigh"))
		)
	{
		if (!found2)
		{
			found2 = true;
			bscout = h;
			Goto(bscout,"patrol1",0);
			SetObjectiveOn(bscout);
		}
		else
		{
			if (GetDistance(bscav,bgoal)<200.0f)
			{
				Attack(h,bscav);
			}
			else
				Goto(h,"patrol2",0);  // attack scrap field
		}
	}

}

void Tran05Mission::Execute(void)
{
	bplayer=GetPlayerHandle();
	if (!start_done)
	{
		SetPilot(1,2);
		SetScrap(1,5);
		int team=2;  // hard wired, hope this doesn't change
		SetAIP("misn02.aip");
		/*
			misn0224
			Commander, we've discovered a deposit of bio metal..
			stay close to the scavenger.  
		*/ 
		dummy=GetHandle("fake_player");
		lander=GetHandle("avland0_wingman");
		bhandle=GetHandle("sscr_171_scrap");
		bhome=GetHandle("abcomm1_i76building");
		recycler=GetHandle("avrecy-1_recycler");
		//	bplayer=GetHandle("player-1_hover");
		bgoal=GetHandle("apscrap-1_camerapod");
		bhandle2=GetHandle("sscr_176_scrap");
		SetUserTarget(bgoal);
		start_done=true;
		camera1=true;
		cam_time=GetTime()+30.0f;
		CameraReady();
		audmsg = AudioMessage("misn0230.wav");
	}
	if (camera1)
	{
	
		if (CameraPath("fixcam",1200,250,lander) ||
			CameraCancelled() || IsAudioMessageDone(audmsg))
			//(GetTime()>cam_time)))
		{
			camera1=false;	
			cam_time=GetTime()+10.0f;
			camera2=true;
		}
	}
	if (camera2)
	{
			camera2=false;
			camera3=true;
			Goto(dummy,"player_path");
			cam_time=GetTime()+25.0f;
		// Final actor audio has both tracks in one place
		//	StopAudioMessage(audmsg);
	//		audmsg = AudioMessage("misn0232.wav");
	}
	if (camera3) 
	{	
		if (CameraPath("zoomcam",1200,800,dummy) 
			|| IsAudioMessageDone(audmsg)
			|| CameraCancelled() )
		{
			camera3=false;
			cam_time=99999.0f;
			CameraFinish();
			RemoveObject(dummy);
			StopAudioMessage(audmsg);
			audmsg = 0;
			AudioMessage("misn0224.wav");
			wave_timer=Get_Time()+30.0f;
			AddObjective("misn02b1.otf", WHITE);
		}
	}
	if (		
		(!patrol1) && (found)
		&& (GetDistance(bhandle,bscav)<75.0f)

		)
	{
		VECTOR_3D ted;	
		ted=GameObjectHandle::GetObj(bhandle)->GetPosition();
		BuildObject("svfigh", 2, "spawn1");
		AudioMessage("misn0233.wav");
		message1=true;
		patrol1=true;

		if ((!message4) && (found2))
		{
			//bscout=GetHandle("svfigh-1_wingman");
			message4=true;
		}
	}
	if ((!message4) && (found2))
	{
		// this is in case the AddObject is called in 
		// a different frame then the BuildObject() above
		message4=true;
	}
	if ((message4) && (!message5) && (GetDistance(bscav,bhandle2)<200.0f))  // was bgoal
	{
		BuildObject("svfigh",2,"spawn2");
//		if (bscout!=NULL) Attack(bscout,bscav,1);
		message5=true;
		wave_timer=Get_Time()+30.0f;
	}
	if ((message5) && (GetTime()>wave_timer))
	{
		BuildObject("svfigh",2,"spawn2");
		wave_timer=GetTime()+45.0f;
	}
	if ((message1) && (message5) && (!message2) &&

		(GameObjectHandle::GetObj(bscav)->GetLastEnemyShot()>0) 
		)
	{
		AiCmdInfo info;
		// send the scav home
		// bscav to bbase
		info.what=CMD_FOLLOW;
		info.where=new AiPath(GameObjectHandle::GetObj(bscav)->GetPosition(),
								GameObjectHandle::GetObj(bhome)->GetPosition());
		info.who=bhome;
		info.priority=0;
		GameObjectHandle::GetObj(bscav)->SetCommand(info);
		ClearObjectives();
		AddObjective("misn02b2.otf", WHITE);
		/*
			misn0225
			Commander our insturments show that you are heavily
			ounumbered..
		*/
		AudioMessage("misn0225.wav");
		Handle bbase=GetHandle("apbase-1_camerapod");
		SetUserTarget(bbase);
		message2=true;
	}
	if (((bscav!=NULL) &&  // was message2, so we know a scav was built
		((!IsAlive(bplayer)) || 
		(!IsAlive(bscav)) || 
		((message3) && (!IsAlive(scav2))))
		|| (!IsAlive(bhome)) 
		|| (!IsAlive(recycler))
		) 
		&&
		(!mission_lost))
	{
		/*
			You or the scav is dead
			*/
		ClearObjectives();
		AddObjective("misn02b4.otf",RED);
		/*
			misn0227
			Eagle's Nest 1 is being overrun.  
			Our forces are surrendering..
		*/
		audmsg=AudioMessage("misn0227.wav");
		mission_lost=true;
	}
	if ((mission_lost) && (IsAudioMessageDone(audmsg)))
	{
		FailMission(GetTime(),"misn02l1.des");
	}
	if ((IsAlive(bplayer)) &&
		((message1) && (message4)) && 
		(GetDistance(bhome,bscav)<300.0f)
		&& (!message3))
	{
		/*
			Now rescue the second
			scavenger
		*/
		Follow(bscav,bhome);
		wave_timer=Get_Time()+45.0f;
		scav2=BuildObject("avscav",1,"spawn3");
		Retreat(scav2,"retreat");
		SetObjectiveOn(scav2);
		AudioMessage("misn0228.wav");
		last_wave_time=GetTime()+10.0f;
		NextSecond=GetTime()+1.0f;
		message3=true;
	}
	if ((IsAlive(bscav)) && (message3) && (GetTime()>NextSecond))
	{
		GameObjectHandle::GetObj(bscav)->AddHealth(200.0f);
		NextSecond=GetTime()+1.0f;
	}
	if (last_wave_time<GetTime())
	{
		Handle sid=BuildObject("svfigh",2,"spawn4");
		Attack(sid,scav2);
		last_wave_time=99999.0f;
	}
	if	((GetDistance(bhome,scav2)<200.0f) &&
	(message3)	&& (!mission_won))
	{
		ClearObjectives();
		AddObjective("misn02b3.otf", GREEN);
		GameObjectHandle::GetObj(bscav)->AddHealth(1000.0f);
		GameObjectHandle::GetObj(scav2)->AddHealth(1000.0f);

		/*
			misn0226
			Good work.  I know you wanted to engage..
		*/
	//	AudioMessage("misn0226.wav");
		audmsg=AudioMessage("misn0234.wav");
		mission_won=true;

	}
	if ((mission_won) && (IsAudioMessageDone(audmsg)))
	{
		SucceedMission(GetTime(),"misn02w1.des");
	}
}

IMPLEMENT_RTIME(Tran05Mission)

Tran05Mission::Tran05Mission(void)
{
}

Tran05Mission::~Tran05Mission()
{
}

void Tran05Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

bool Tran05Mission::Load(file fp)
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

bool Tran05Mission::PostLoad(void)
{
	// hack path to go around buildings
	AiPath *p = AiPath::Find("player_path");
	if (p != NULL) {
		VECTOR_2D &pt = p->points[7];
		pt.x -= 40.0f;
	}

	if (missionSave)
		return AiMission::PostLoad();

	bool ret = true;

	int h_count = &h_last - h_array;
	for (int i = 0; i < h_count; i++)
		h_array[i] = ConvertHandle(h_array[i]);

	ret = ret && AiMission::PostLoad();

	return ret;
}

bool Tran05Mission::Save(file fp)
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

void Tran05Mission::Update(void)
{
	AiMission::Update();
	Execute();
}
