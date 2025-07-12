#include "GameCommon.h"

#include "..\fun3d\AiMission.h"
#include "..\fun3d\ScriptUtils.h"

/*
	Misns5Mission
*/

class Misns5Mission : public AiMission {
	DECLARE_RTIME(Misns5Mission)
public:
	Misns5Mission(void);
	~Misns5Mission();

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
				camera1,start_done,defender,com_dead,last_phase,
				third_attack,fourth_attack,won,lost,
				second_message,third_message,
				art_dead,apc_here,
				b_last;
		};
		bool b_array[13];
	};

	// floats
	union {
		struct {
			float
				add_defender,wave,chaff,camera_time,
				apc_wave,
				f_last;
		};
		float f_array[5];
	};

	// handles
	union {
		struct {
			Handle
				a1,a2,t1,t2,t3,t4,h1,h2,geyser1,geyser2,
				recy,muf,commander,cam1,killme,
				h_last;
		};
		Handle h_array[15];
	};

	// integers
	union {
		struct {
			int
				wave_count,wave_type,
				aud,
				i_last;
		};
		int i_array[3];
	};
};

void Misns5Mission::Setup(void)
{
	h1=NULL;
	h2=NULL;
	third_attack=false;
	fourth_attack=false;
	art_dead=false;
	apc_here=false;
	killme=NULL;
	camera1=false;
	camera_time=99999.0f;
	wave_count=0;
	add_defender=99999.0f;
	apc_wave=99999.0f;
	wave=99999.0f;
	chaff=99999.0f;
	start_done=false;
	second_message=false;
	third_message=false;
	defender=false;
	com_dead=false;
	last_phase=false;
	won=false;
	lost=false;
}

void Misns5Mission::AddObject(Handle h)
{
	if (GetTeamNum(h) == 2)
	{
		if (IsOdf(h, "avwalk"))
		{
			commander=h;
			/*
				The first walker is
					"the commander"
			*/
		}
		if ((IsOdf(h,"bvltnk")) ||
			(IsOdf(h,"bvhraz")) ||
			(IsOdf(h,"avfigh")))
		{
			Goto(h,recy);
		}

	}


}

void Misns5Mission::Execute(void)
{
	if (!start_done)
	{
		recy=GetHandle("svrecy0_recycler");
		AddScrap(1,10);
		camera1=true;
		camera_time=GetTime()+17.0f;
		apc_wave=GetTime()+70.0f;
		start_done=true;
		t4=GetHandle("sbhang0_repairdepot");
		a1=BuildObject("avartl",2,"spawn1");
		a2=BuildObject("avartl",2,"spawn2");
		CameraReady();
		aud=AudioMessage("misns501.wav");
	}
	if (camera1)
	{
		CameraPath("campath",5000,2500,t4);
		if ((IsAudioMessageDone(aud)) && (!second_message))
		{
			aud=AudioMessage("misns503.wav");
			second_message=true;
		}
/*		if ((second_message) && (IsAudioMessageDone(aud))
			&& (!third_message))
		{
			aud=AudioMessage("misns503.wav");
			third_message=true;
		}
*/
		if ((CameraCancelled()) ||  (IsAudioMessageDone(aud)))//(GetTime()>camera_time))
		{
			chaff=GetTime()+180.0f;
			t1=GetHandle("sblpow2_powerplant");
			t2=GetHandle("sblpow3_powerplant");
			t3=GetHandle("sblpow4_powerplant");
			recy=GetHandle("svrecy0_recycler");
			muf=GetHandle("svmuf0_factory");
			geyser1=GetHandle("eggeizr11_geyser");
			geyser2=GetHandle("eggeizr12_geyser");
			Goto(recy,geyser1);
			Goto(muf,geyser2);
			Attack(a1,t1);
			Attack(a2,t2);
			add_defender=GetTime()+10.0f;
			CameraFinish();	
			ClearObjectives();
			AddObjective("misns501.otf",WHITE);
			StopAudioMessage(aud);
			camera1=false;
		}
	}
	if ((defender) && (!third_attack) && (!IsAlive(t1)))
	{
		Attack(a1,t3);
		third_attack=true;
	}
	if ((defender) && (!fourth_attack) && (!IsAlive(t2)))
	{
		Attack(a2,t4);
		fourth_attack=true;
	}
	if (GetTime()>add_defender)
	{
		BuildObject("avwalk",2,"spawn3");
		// BuildObject("avtank",2,"spawn3");
		add_defender=99999.0f;
		SetPilot(2,30);  // in case we load AIP
		defender=true;
	}
	if ((defender) && (!art_dead) && (!IsAlive(a1)) && (!IsAlive(a2)))
	{
		AudioMessage("misns504.wav");
		art_dead=true;
	}
	if ((defender)  && (h1!=NULL) && (!apc_here) &&
		(GetDistance(h1,muf)<100.0f)) 
	{
		apc_here=true;
		AudioMessage("misns505.wav");
	}
	if (GetTime()>chaff)
	{
		chaff=GetTime()+50.0f+rand()%4*10.0f;
		BuildObject("avfigh",2,"spawn5");
	}
	if (GetTime()>apc_wave)
	{
		h1=BuildObject("avapc",2,"spawn6");
		h2=BuildObject("avapc",2,"spawn6");
		killme=BuildObject("avrecy",2,"spawn7");
		Handle protect=BuildObject("bvtank",2,"spawn7");
		Defend(protect,killme);
		protect=BuildObject("bvtank",2,"spawn7");
		Defend(protect,killme);
		Attack(h1,muf);
		Attack(h2,muf);
		apc_wave=99999.0f;
	}
	if ((defender) && (!IsAlive(commander))
		&& (!com_dead))
	{
		wave=GetTime()+120.0f;
		com_dead=true;
	}
	if (GetTime()>wave)
	{
		wave_count++;
		wave=GetTime()+180.0f;
		//wave_type=rand()%2
		AudioMessage("misns505.wav");
		if (wave_count!=1)
		{
			BuildObject("bvltnk",2,"spawn5");
			BuildObject("bvltnk",2,"spawn5");
			BuildObject("bvltnk",2,"spawn5");
		}
		else
		{
			BuildObject("bvhraz",2,"spawn6");
			BuildObject("bvhraz",2,"spawn6");
			BuildObject("bvhraz",2,"spawn6");
		}
		if (wave_count==3)
		{
			/*
				Build a recycler
				at spawn7 avrecy
				
			*/
			last_phase=true;
//			killme=BuildObject("avrecy",2,"spawn7");
			BuildObject("avscav",2,"spawn7");
			BuildObject("avscav",2,"spawn7");
			Handle sam=BuildObject("spcamr",1,"camera1");
			SetObjectiveOn(killme);  // should be sam
			AddObjective("misns502.otf",WHITE);
			AudioMessage("misns506.wav");
			/*
				Now LoadAIP.
			*/
			SetAIP("misns5.aip");
			/*
				Our intelligence.   
			*/
		}
	}
	if ((last_phase) && (!IsAlive(killme))
		&& (!won) && (!lost))
	{
		won=true;
		AudioMessage("misns508.wav");
		SucceedMission(GetTime()+10.0f,"misns5w1.des");
	}
	if ((!IsAlive(recy)) && (!lost) && (!won))
	{
		lost=true;
		AudioMessage("misns507.wav");
		FailMission(GetTime()+10.0f,"misns5l1.des");
	}
}

IMPLEMENT_RTIME(Misns5Mission)

Misns5Mission::Misns5Mission(void)
{
}

Misns5Mission::~Misns5Mission()
{
}

void Misns5Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

bool Misns5Mission::Load(file fp)
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

bool Misns5Mission::PostLoad(void)
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

bool Misns5Mission::Save(file fp)
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

void Misns5Mission::Update(void)
{
	AiMission::Update();
	Execute();
}
