#include "GameCommon.h"

#include "..\fun3d\AiMission.h"
#include "..\fun3d\ScriptUtils.h"

/*
	Misns1Mission
*/

class Misns1Mission : public AiMission {
	DECLARE_RTIME(Misns1Mission)
public:
	Misns1Mission(void);
	~Misns1Mission();

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
				coloradoescapes, halfwaywarn, coloradodestroyed, silodestroyed, mufdestroyed, retreat,
				missionstart, missionwon, enterwarning, trapset, coloradosafe, missionfail, beginassault, convoyseen, convoyintrap,
				pickpath, cav1pathwarn1, cav1pathwarn2, cav2pathwarn1, cav2pathwarn2, 
				cav3pathwarn1, cav3pathwarn2, cav4pathwarn1, cav4pathwarn2,
				finish, cavalry, cavsent, cavpath1, cavpath2, cavpath3, cavpath4,
				coloradoreachedsafepoint, possible1, possible2, newobjective, escortretreat,
				cindone, cindone05, cindone1, cindone2, cindone3, cindone4, cindone5, 
				cindone6, cindone7, cindone8, cindone08, cindone9, cindone10, 
				cindone11, retreatpathset, blockaderun,
				aw1amade, aw1bmade, aw1cmade, aw2amade, aw2bmade, aw2cmade, aw3amade, aw3bmade, aw3cmade,
				du1amade, du1bmade, safety1,
				b_last;
		};
		bool b_array[64];
	};

	// floats
	union {
		struct {
			float
				startconvoy, wave1, cintime, cintime05, cintime2, cintime3, cintime4, 
				cintime5, cintime6, cintime7, cintime8, cintime9, cintime09, 
				cintime10, cintime11, cintime12,
				aw1at, aw1bt, aw1ct, aw2at, aw2bt, aw2ct, aw3at, aw3bt, aw3ct, du1at, du1bt,
				f_last;
		};
		float f_array[27];
	};

	// handles
	union {
		struct {
			Handle
				colorado, ef1, ef2, ef3, et1, et2, et3, et4, silo, 
				muf, svrec, player, geyser, geyser2, guntower, walker1, walker2, walker3,
				walkcam1, walkcam2, walkcam3, hidcam1, hidcam2, hidcam3, basecam,
				cav1, cav2, cav3, cav4, cav5, scav1, scav2,
				aw1a, aw1b, aw1c, aw2a, aw2b, aw2c, aw3a, 
				aw3b, aw3c, du1a, du1b, hostile, ambase,
				h_last;
		};
		Handle h_array[45];
	};

	// integers
	union {
		struct {
			int
				path, cav, aud20, aud21, aud22, aud23, aud1,
				i_last;
		};
		int i_array[7];
	};
};

void Misns1Mission::Setup(void)
{
	/*
	Here's where you
	set the values
	at the start.  
	*/
	startconvoy = 9999999999.0f;
	colorado = 0; 
		ef1 = 0; 
		safety1 = false;
		ef2 = 0; 
		ef3 = 0; 
		et1 = 0; 
		et2 = 0; 
		et3 = 0; 
		et4 = 0; 
		silo = 0; 
		muf = 0; 
		svrec = 0; 
		player = 0; 
		geyser = 0; 
		geyser2 = 0; 
		guntower = 0; 
		walker1 = 0; 
		walker2 = 0; 
		walker3 = 0;
		walkcam1 = 0; 
		walkcam2 = 0; 
		walkcam3 = 0; 
		hidcam1 = 0; 
		hidcam2 = 0; 
		hidcam3 = 0; 
		basecam = 0;
		cav1 = 0; 
		cav2 = 0; 
		cav3 = 0; 
		cav4 = 0; 
		cav5 = 0; 
		scav1 = 0; 
		scav2 = 0;
		aw1a = 0; 
		aw1b = 0; 
		aw1c = 0; 
		aw2a = 0; 
		aw2b = 0; 
		aw2c = 0; 
		aw3a = 0; 
		aw3b = 0; 
		aw3c = 0; 
		du1a = 0; 
		du1b = 0;
	coloradoescapes = false;
	coloradodestroyed = false;
	trapset = false;
	coloradosafe = false;
	silodestroyed = false;
	mufdestroyed = false;
	retreat = false;
	mufdestroyed = false;
	silodestroyed = false;
	halfwaywarn = false;
	escortretreat = false;
	missionstart = false;
	missionwon = false;
	missionfail = false;
	beginassault = false;
	convoyseen = false;
	convoyintrap = false;
	pickpath = false;
	finish = false;
	newobjective = false;
	enterwarning = false;
	cavalry = false;
	cavsent = false;
	cavpath1 = false;
	cavpath2 = false;
	cavpath3 = false;
	cavpath4 = false;
	coloradoreachedsafepoint = false;
	possible1 = false;
	possible2 = false;
	cindone = false;
	cindone05 = false;
	cindone1 = false;
	cindone2 = false;
	cindone3 = false;
	cindone4 = false;
	cindone5 = false;
	cindone6 = false;
	cindone7 = false;
	cindone8 = false;
	cindone08 = false;
	cindone9 = false;
	cindone10 = false;
	cindone11 = false;
	blockaderun = false;
	cav1pathwarn1 = false;
	cav1pathwarn2 = false;
	cav2pathwarn1 = false;
	cav2pathwarn2 = false;
	cav3pathwarn1 = false;
	cav3pathwarn2 = false;
	cav4pathwarn1 = false;
	cav4pathwarn2 = false;
	retreatpathset = false;
	aw1amade = false;
	aw1bmade = false;
	aw1cmade = false;
	aw2amade = false;
	aw2bmade = false;
	aw2cmade = false;
	aw3amade = false;
	aw3bmade = false;
	aw3cmade = false;
	du1amade = false;
	du1bmade = false;
	aud1 = 0;
	aud20 = 0;
	aud21 = 0;
	aud22 = 0;
	aud23 = 0;
	wave1 = 999999999.0f;
	cintime = 9999999999.0f;
	cintime05 = 99999999.0f;
	cintime2 = 9999999999.0f;
	cintime3 = 9999999999.0f;
	cintime4 = 9999999999.0f;
	cintime5 = 9999999999.0f;
	cintime6 = 9999999999.0f;
	cintime7 = 9999999999.0f;
	cintime8 = 9999999999.0f;
	cintime9 = 9999999999.0f;
	cintime09 = 999999999999.0f;
	cintime10 = 9999999999.0f;
	cintime11 = 9999999999.0f;
	hostile = 0;
	aw1at = 99999999999.0f;
	aw1bt = 99999999999.0f;
	aw1ct = 99999999999.0f;
	aw2at = 99999999999.0f;
	aw2bt = 99999999999.0f;
	aw2ct = 99999999999.0f;
	aw3at = 99999999999.0f;
	aw3bt = 99999999999.0f;
	aw3ct = 99999999999.0f;
	du1at = 99999999999.0f;
	du1bt = 99999999999.0f;


}

void Misns1Mission::AddObject(Handle h)
{
}

void Misns1Mission::Execute(void)
{
	/*
		Here is where you 
		put what happens 
		every frame.  
	*/
	if 
		(missionstart == false)
	{
		AudioMessage("misns101.wav");
		geyser = GetHandle ("eggeizr10_geyser");
		muf = GetHandle ("avmuf1_factory");
		silo = GetHandle ("absilo1_i76building");
		colorado = GetHandle ("avrecy1_recycler");
		svrec = GetHandle ("svrecy2_recycler");
		SetScrap (2, 50);
		SetScrap (1,20);
		//geyser2 = GetHandle ("geyser2");
		ef1 = GetHandle ("avfigh3_wingman");
		ef2 = GetHandle ("avfigh4_wingman");
		ef3 = GetHandle ("avfigh5_wingman");
		et1 = GetHandle ("avtank5_wingman");
		et2 = GetHandle ("avtank6_wingman");
		et3 = GetHandle ("avtank7_wingman");
		et4 = GetHandle ("avtank8_wingman");
		ambase = GetHandle("ambase");
		// temporary 
		walker1 = BuildObject ("svwalk", 1, "spawnwalker1"); 
		//walker2 = BuildObject ("svwalk", 1, "spawnwalker2"); 
		//walker3 = BuildObject ("svwalk", 1, "walkstart3"); 
		walkcam1 = BuildObject ("apcamr", 1, "walkcam1");
		//walkcam2 = BuildObject ("apcamr", 1, "walkcam2");
		//walkcam3 = BuildObject ("apcamr", 1, "walkcam3");
		hidcam1 = BuildObject ("apcamr", 1, "hidcamupper");
		hidcam2 = BuildObject ("apcamr", 1, "hidcammiddle");
		hidcam3 = BuildObject ("apcamr", 1, "hidcamlower");
		basecam = GetHandle ("apcamr0_camerapod");
		GameObjectHandle :: GetObj(walkcam1) ->SetName ("Walker Cut Off");
		//GameObjectHandle :: GetObj(walkcam2) ->SetName ("Middle Pass Exit");
		GameObjectHandle :: GetObj(ambase) ->SetName ("American Outpost");
		GameObjectHandle :: GetObj(hidcam1) ->SetName ("Upper Pass Exit");
		GameObjectHandle :: GetObj(hidcam2) ->SetName ("Middle Pass Exit");
		GameObjectHandle :: GetObj(hidcam3) ->SetName ("Lower Pass Exit");
		GameObjectHandle :: GetObj(basecam) ->SetName ("Home Base");
		//Goto (walker1, "spawnwalker1");
		//Goto (walker2, "spawnwalker2");
		//Goto (walker3, "spawnwalker3");
		//RemoveObject (ef2);
		//RemoveObject (ef3);
		//RemoveObject (et1);
		//RemoveObject (et2);
		RemoveObject (et3);
		RemoveObject (et4);
		BuildObject("svtank", 1, "tank1");
		BuildObject("svtank", 1, "tank2");
		BuildObject("svfigh", 1, "figh1");
		BuildObject("svturr", 1, "turr1");
		BuildObject("svturr", 1, "turr2");
		startconvoy = GetTime () + 180.0f;
		missionstart = true;
		SetScrap (1, 20);
		SetScrap (2, 50);
		path = rand () % 3;
		cav = rand () % 4;
		newobjective = true;
		//CameraReady();
		cintime = GetTime () + 11.0f;//11
		cintime05 = GetTime () + 11.1;//11
		cintime2 = GetTime () + 20.0f;
		cintime3 = GetTime () + 27.0f;
		cintime4 = GetTime () + 29.0f;
		cintime5 = GetTime () + 31.0f;
		cintime6 = GetTime () + 33.0f;
		cintime7 = GetTime () + 44.0f;
		cintime8 = GetTime () + 46.0f;
		cintime9 = GetTime () + 48.0f;
		cintime09 = GetTime () + 50.0f;
		cintime10 = GetTime () + 60.0f;
		cintime11 = GetTime () + 66.0f;
	}
	IsAlive(colorado);

	/*if
		(
		(cindone == false) && (cintime > GetTime())
		)
	{
		CameraPath("cinpath3", 200, 600, svrec);
	}
	if
		(
		(cindone05 == false) && (cintime05 < GetTime())
		)
	{
		CameraPath("cinpath4", 300, 500, colorado);
		cindone = true;
	}
	if
		(
		(cindone1 == false) && (cintime2 < GetTime())
		)
	{
		//CameraObject(geyser2, 3000, 600, 3000, geyser2);
		CameraPath("geyserpath", 500, 5000, geyser2);
		cindone05 = true;
	}
	//CameraObject(walker1, -1200, 1500, -1100, walker2);
	if
		(
		(cintime3 < GetTime()) && (cindone2 == false)
		)
	{
		CameraObject(hidcam1, 1100, 300, 200, hidcam1);
		cindone1 = true;
	}
	if
		(
		(cintime4 < GetTime()) && (cindone3 == false)
		)
	{
		CameraObject(hidcam2, 300, 200, 1500, hidcam2);
		cindone2 = true;
	}
	if
		(
		(cintime5 < GetTime()) && (cindone4 == false)
		)
	{
		CameraObject(hidcam3, 600, 1000, 300, hidcam3);
		cindone3 = true;
	}
	if
		(
		(cintime6 < GetTime()) && (cindone5 == false)
		)
	{
		CameraObject(walker1, -1200, 1500, 1100, walker2);
		cindone4 = true;
	}
	if
		(
		(cintime7 < GetTime()) && (cindone6 == false)
		)
	{
		CameraObject(walkcam1, 500, 300, 1200, walkcam1);
		cindone5 = true;
	}
	if
		(
		(cintime8 < GetTime()) && (cindone7 == false)
		)
	{
		CameraObject(walkcam2, 1300, 200, 500, walkcam2);
		cindone6 = true;
	}
	if
		(
		(cintime9 < GetTime()) && (cindone8 == false)
		)
	{
		CameraObject(walkcam3, 600, 400, 1300, walkcam3);
		cindone7 = true;
	}
	if
		(
		(cindone08 == false) && (cintime09 < GetTime())
		)
	{
		CameraPath("approach", 400, 5000, hidcam3);
		cindone8 = true;
	}
	if
		(
		(cindone9 == false) && (cintime10 < GetTime())
		)
	{
		CameraPath("cinpath1", 300, 500, muf);
		cindone08 = true;
	}
	if
		(
		(cintime11 < GetTime()) && (cindone10 == false)
		)
	{
		CameraFinish();
		cindone9 = true;
		cindone10 = true;
	}*/



	if
		(newobjective == true)
	{
		ClearObjectives();
		if
			(
			(IsAlive(colorado)) && (coloradosafe == false)
			)
		{
			AddObjective ("misns101.otf", WHITE);
		}
		if
			(
			(!IsAlive(colorado)) && (coloradosafe == false)
			)
		{
			AddObjective ("misns101.otf", GREEN);
		}
		if
			(coloradoreachedsafepoint == true)
		{
			AddObjective ("misns101.otf", RED);
		}
		if
			(coloradosafe == false)
		{
			if
			(
			(IsAlive(muf)) || (IsAlive(silo))
			)
		{
			AddObjective ("misns102.otf", WHITE);
		}
		}
		if
			(coloradosafe == true)
		{
			if
			(
			(IsAlive(muf)) || (IsAlive(silo)) || (IsAlive(colorado))
			)
		{
			AddObjective ("misns102.otf", WHITE);
		}
		}
		if
			(coloradosafe == false)
		{
		if
			(
			(!IsAlive(muf)) && (!IsAlive(silo))
			)
		{
			AddObjective ("misns102.otf", GREEN);
		}
		}
		if
			(coloradosafe == true)
		{
		if
			(
			(!IsAlive(muf)) && (!IsAlive(silo)) && (!IsAlive(colorado))
			)
		{
			AddObjective ("misns102.otf", GREEN);
		}
		}
		if
			(
			(IsAlive(svrec)) && (missionwon == false)
			)
		{
			AddObjective ("misns103.otf", WHITE);
		}
		if
			(!IsAlive(svrec))
		{
			AddObjective ("misns103.otf", RED);
		}
		if
			(missionwon == true)
		{
			AddObjective ("misn103.otf", GREEN);
		}
		if
			(
			(coloradosafe == true) && (missionwon == false)
			)
		{
			AddObjective ("misns101.otf", RED);
		}
		newobjective = false;
	}

			

	if
		(
		(pickpath == false) && (startconvoy < GetTime ())
		)
	{
		switch (path)
		{
		case 0:
			Follow (ef1, colorado);
			Follow (ef2, colorado);
			Follow (ef3, colorado);
			Goto (colorado, "upperpath");
			Follow (et1, colorado, 1);
			Follow (et2, colorado, 1);
			//Follow (et3, colorado, 1);
			//Follow (et4, colorado, 1);
			break;
		case 1:
			Follow (ef1, colorado);
			Follow (ef2, colorado);
			Follow (ef3, colorado);
			Goto (colorado, "midpath");
			Follow (et1, colorado, 1);
			Follow (et2, colorado, 1);
			//Follow (et3, colorado, 1);
			//Follow (et4, colorado, 1);
			break;
		case 2:
			Follow (ef1, colorado);
			Follow (ef2, colorado);
			Follow (ef3, colorado);
			Goto (colorado, "lowerpath");
			Follow (et1, colorado, 1);
			Follow (et2, colorado, 1);
			//Follow (et3, colorado, 1);
			//Follow (et4, colorado, 1);
			break;
		}
		SetIndependence(ef1, 1);
		SetIndependence(ef2, 1);
		SetIndependence(ef3, 1);
		SetIndependence(et1, 1);
		SetIndependence(et2, 1);
		//SetIndependence(et3, 1);
		//SetIndependence(et4, 1);
		pickpath = true;
		AudioMessage("misns125.wav");
	}

	if 
		(
		(
		(GetDistance(walker1, walkcam1) < 50.0f) //||
		//(GetDistance(walker2, walkcam1) < 50.0f) ||
		//(GetDistance(walker3, walkcam1) < 50.0f)
		) && (trapset == false) && (blockaderun == false) && 
		(IsAlive(colorado))
		)
	{
		trapset = true;
		AudioMessage("misns123.wav");
	}

	/*if 
		(
		(
		(GetDistance(walker1, walkcam2) < 50.0f) ||
		(GetDistance(walker2, walkcam2) < 50.0f) //||
		//(GetDistance(walker3, walkcam2) < 50.0f)
		) && (trapset == false) && (blockaderun == false)
		)
	{
		trapset = true;
		AudioMessage("misns123.wav");
	}

	if 
		(
		(
		(GetDistance(walker1, walkcam3) < 50.0f) ||
		(GetDistance(walker2, walkcam3) < 50.0f) //||
		//(GetDistance(walker3, walkcam3) < 50.0f)
		) && (trapset == false) && (blockaderun == false)
		)
	{
		trapset = true;
		AudioMessage("misns123.wav");
	}*/

	if
		(
		(halfwaywarn == true) && (blockaderun == false)
		)
	{
		if	
			(
			(path == 0) && (GetDistance(colorado, hidcam1) < 70.0f)
			)
		{
			blockaderun = true;
			AudioMessage("misns124.wav");
		}
		if	
			(
			(path == 1) && (GetDistance(colorado, hidcam2) < 70.0f)
			)
		{
			blockaderun = true;
			AudioMessage("misns124.wav");
		}
		if	
			(
			(path == 2) && (GetDistance(colorado, hidcam3) < 70.0f)
			)
		{
			blockaderun = true;
			AudioMessage("misns124.wav");
		}
	}
	if 
		(
		(retreat == false) && (blockaderun == false)
		)
	{
		hostile = GetNearestEnemy(colorado);
		if
		(GetDistance(hostile, colorado) < 200.0f)
		{
		//Attack (walker1, colorado);
		//Attack (walker2, ef2);
		//Attack (walker3, ef1);
		//SetIndependence (walker1, 1);
		//SetIndependence (walker2, 1);
		//SetIndependence (walker3, 1);
		retreat = true;
		AudioMessage ("misns114.wav");
		}
	}

	if
		(
		(retreatpathset == false) && (retreat == true) 
		)
	{
		
			Goto(colorado, "retreat1");
			Attack(ef1, hostile);
			Follow(ef2, ef1);
			Follow(et3, ef1);
			SetIndependence(ef1, 1);
			SetIndependence(ef2, 1);
			SetIndependence(et3, 1);
			retreatpathset = true;
	}

	if 
		(
		(retreat == true) && (GetDistance (colorado, geyser) < 50.0f) &&
		(coloradosafe == false)
		)
	{
		coloradosafe = true;
		SetAIP ("misn09.aip");
		SetObjectiveOn(colorado);
		SetObjectiveOn(silo);
		SetObjectiveOn(muf);
		AudioMessage ("misns106.wav");
		aw1at = GetTime() + 25.0f;
		aw1bt = GetTime() + 30.0f;
		aw1ct = GetTime() + 35.0f;
		aw2at = GetTime() + 90.0f;
		aw2bt = GetTime() + 95.0f;
		aw2ct = GetTime() + 100.0f;
		aw3at = GetTime() + 190.0f;
		aw3bt = GetTime() + 195.0f;
		aw3ct = GetTime() + 200.0f;
		du1at = GetTime() + 60.0f;
		du1bt = GetTime() + 75.0f;
		newobjective = true;
	}

	if
		(
		(!IsAlive(colorado)) && (escortretreat == false)
		)
	{
		Goto(ef1, muf, 1000);
		Goto(ef2, muf, 1000);
		Goto(ef3, muf, 1000);
		//Goto(et1, muf, 1000);
		escortretreat = true;
	}

	if 
		(
		(safety1 == false) &&
		(coloradosafe == false) && (!IsAlive(colorado))
		)
	{
		SetAIP ("misn14.aip");
		scav1 = BuildObject ("avscav", 2, muf);
		scav2 = BuildObject ("avscav", 2, muf);
		SetObjectiveOn(silo);
		SetObjectiveOn(muf);
		//coloradosafe = true;
		safety1 = true;
		AudioMessage ("misns105.wav");
		aw1at = GetTime() + 25.0f;
		aw1bt = GetTime() + 35.0f;
		aw1ct = GetTime() + 40.0f;
		aw2at = GetTime() + 90.0f;
		aw2bt = GetTime() + 95.0f;
		aw2ct = GetTime() + 100.0f;
		aw3at = GetTime() + 190.0f;
		aw3bt = GetTime() + 195.0f;
		aw3ct = GetTime() + 200.0f;
		du1at = GetTime() + 60.0f;
		du1bt = GetTime() + 75.0f;
		newobjective = true;
	}
	if
		(
		(aw1at < GetTime()) && (aw1amade == false) && (IsAlive(muf))
		)
	{
		BuildObject ("avtank", 2, muf);
		aw1amade = true;
	}
	if
		(
		(aw1bt < GetTime()) && (aw1bmade == false) && (IsAlive(muf))
		)
	{
		BuildObject ("avfigh", 2, muf);
		aw1bmade = true;
	}
	if
		(
		(aw1ct < GetTime()) && (aw1cmade == false) && (IsAlive(muf))
		)
	{
		BuildObject ("avfigh", 2, muf);
		aw1cmade = true;
	}
	if
		(
		(aw2at < GetTime()) && (aw2amade == false) && (IsAlive(muf))
		)
	{
		BuildObject ("avtank", 2, muf);
		aw2amade = true;
	}
	if
		(
		(aw2bt < GetTime()) && (aw2bmade == false) && (IsAlive(muf))
		)
	{
		BuildObject ("avfigh", 2, muf);
		aw2bmade = true;
	}
	if
		(
		(aw2ct < GetTime()) && (aw2cmade == false) && (IsAlive(muf))
		)
	{
		BuildObject ("avtank", 2, muf);
		aw2cmade = true;
	}
	if
		(
		(aw3at < GetTime()) && (aw3amade == false) && 
		(IsAlive(muf)) && (IsAlive(silo))
		)
	{
		BuildObject ("avtank", 2, muf);
		aw3amade = true;
	}
	if
		(
		(aw3bt < GetTime()) && (aw3bmade == false) && 
		(IsAlive(muf)) && (IsAlive(silo))
		)
	{
		BuildObject ("avtank", 2, muf);
		aw3bmade = true;
	}
	if
		(
		(aw3ct < GetTime()) && (aw3cmade == false) && 
		(IsAlive(muf)) && (IsAlive(silo))
		)
	{
		BuildObject ("avfigh", 2, muf);
		aw3cmade = true;
	}
	if
		(
		(du1at < GetTime()) && (du1amade == false)
		)
	{
		BuildObject ("avturr", 2, muf);
		du1amade = true;
	}
	if
		(
		(du1bt < GetTime()) && (du1bmade == false)
		)
	{
		BuildObject ("avturr", 2, muf);
		du1bmade = true;
	}
	/*if
		(
		(aw1sent == false) && (aw1amade == true) &&
		(aw1bmade == true) && (aw1cmade == true)
		)
	{
		Attack(aw1a, svrec);
		Attack(aw1b, svrec);
		Attack(aw1c, svrec);
		SetIndependence(aw1a, 1);
		SetIndependence(aw1b, 1);
		SetIndependence(aw1c, 1);
		aw1sent = true;
	}
	if
		(
		(aw2sent == false) && (aw2amade == true) &&
		(aw2bmade == true) && (aw2cmade == true)
		)
	{
		Attack(aw2a, svrec);
		Attack(aw2b, svrec);
		Attack(aw2c, svrec);
		SetIndependence(aw2a, 1);
		SetIndependence(aw2b, 1);
		SetIndependence(aw2c, 1);
		aw2sent = true;
	}
	if
		(
		(aw3sent == false) && (aw3amade == true) &&
		(aw3bmade == true) && (aw3cmade == true)
		)
	{
		Attack(aw3a, svrec);
		Attack(aw3b, svrec);
		Attack(aw3c, svrec);
		SetIndependence(aw3a, 1);
		SetIndependence(aw3b, 1);
		SetIndependence(aw3c, 1);
		aw3sent = true;
	}*/

	if
		(
		(!IsAlive(colorado)) && (coloradodestroyed == false)
		)
	{
		coloradodestroyed = true;
		wave1 = GetTime() + 180.0f;
	}

	if
		(
		(!IsAlive(muf)) && (mufdestroyed == false)
		)
	{
		AudioMessage ("misns108.wav");
		mufdestroyed = true;
		possible1 = true;
	}

	if
		(
		(!IsAlive (silo)) && (silodestroyed == false)
		)
	{
		possible2 = true;
		AudioMessage ("misns107.wav");
		silodestroyed = true;
	}

	if 
		(
		(possible1 == true) && (possible2 == true)
		)
	{
		newobjective = true;
	}

	if
		(
		(mufdestroyed == true) && (silodestroyed == true) && 
		(coloradodestroyed == true) && (missionwon == false)
		)
	{
		newobjective = true;
		missionwon = true;
	}

	if 
		(
		(missionwon == true) && (finish == false)
		)
	{
		aud1 = AudioMessage("misns110.wav");
		finish = true;
	}

	if 
		(
		(finish == true) && (IsAudioMessageDone(aud1))
		)
	{
		SucceedMission(GetTime(), "misns1w1.des");
	}


	if
		(
		(enterwarning == false) && 
		(GetDistance (colorado, walkcam1) < 70.0f) 
		)
	{
		if
			(path == 0)
		{
		AudioMessage ("misns117.wav");
		enterwarning = true;
		}
		if
			(path == 1)
		{
			AudioMessage ("misns116.wav");
		enterwarning = true;
		}
		if
			(path == 2)
		{
			AudioMessage ("misns115.wav");
		enterwarning = true;
		}
	}

	if 
		(
		(GetDistance (colorado, "halfwayupper") < 100.0f) &&
		(halfwaywarn == false)
		)
	{
		halfwaywarn = true;
		AudioMessage ("misns102.wav");
	}

	if 
		(
		(GetDistance (colorado, "halfwaymid") < 100.0f) &&
		(halfwaywarn == false)
		)
	{
		halfwaywarn = true;
		AudioMessage ("misns103.wav");
	}
	if 
		(
		(GetDistance (colorado, "halfwaylower") < 100.0f) &&
		(halfwaywarn == false)
		)
	{
		halfwaywarn = true;
		AudioMessage ("misns104.wav");
	}

	if 
		(
		(blockaderun == true) &&
		(GetDistance (colorado, "safepoint") < 60.0f) &&  // I know succeds is not the correct spelling but it was easier to leave it then to change it.  I'm not dumb.  I'm just lazy. hehe
		(coloradoreachedsafepoint == false)
		)
	{
		aud20 = AudioMessage ("misns109.wav");
		aud21 = AudioMessage ("misns111.wav");
		coloradoreachedsafepoint = true;
		newobjective = true;
		CameraReady();
		CameraObject(geyser2, 1200, 500, 1200, colorado);
	}

	if
		(
		(coloradoreachedsafepoint == true) && (IsAudioMessageDone(aud20)) &&
		(IsAudioMessageDone(aud21))
		)
	{
		FailMission(GetTime(), "misns1l1.des");
	}

	if
		(
		(!IsAlive(svrec)) && (missionfail == false)
		)
	{
		aud22 = AudioMessage("misns112.wav");
		aud23 = AudioMessage("misns113.wav");
		missionfail = true;
		newobjective = true;
	}

	if
		(
		(missionfail == true) && (IsAudioMessageDone(aud22)) &&
		(IsAudioMessageDone(aud23))
		)
	{
		FailMission(GetTime(), "misns1l2.des");
	}

	if
		(
		(wave1 < GetTime()) && (cavalry == false)
		)
	{
		wave1 = 99999999999.0f;
		cavalry = true;
		cav1 = BuildObject ("avfigh", 2, "cavspawn");
		cav2 = BuildObject ("avtank", 2, "cavspawn");
		cav3 = BuildObject ("avfigh", 2, "cavspawn");
		//cav4 = BuildObject ("avtank", 2, "cavspawn");
		//cav5 = BuildObject ("avtank", 2, "cavspawn");
		AudioMessage ("misns122.wav");
	}

	if 
		(
		(cavalry == true) &&
		(cavsent == false)
		)
	{
		switch (cav)
		{
		case 0:
			Goto (cav1, "cavpath1");
			Goto (cav2, "cavpath1");
			Goto (cav3, "cavpath1");
			//Goto (cav4, "cavpath1");
			//Goto (cav5, "cavpath1");
			cavpath1 = true;
			break;
		case 1:
			Goto (cav1, "cavpath2");
			Goto (cav2, "cavpath2");
			Goto (cav3, "cavpath2");
			//Goto (cav4, "cavpath2");
			//Goto (cav5, "cavpath2");
			cavpath2 = true;
			break;
		case 2:
			Goto (cav1, "cavpath1");
			Goto (cav2, "cavpath1");
			Goto (cav3, "cavpath1");
			//Goto (cav4, "cavpath1");
			//Goto (cav5, "cavpath1");
			cavpath1 = true;
			break;
		case 3:
			Goto (cav1, "cavpath2");
			Goto (cav2, "cavpath2");
			Goto (cav3, "cavpath2");
			//Goto (cav4, "cavpath2");
			//Goto (cav5, "cavpath2");
			cavpath2 = true;
			break;
		}
		cavsent = true;
	}

	if 
		(
		(cavpath1 == true) && 
		(
		(GetDistance (cav1, walkcam1) < 200.0f) ||
		(GetDistance (cav2, walkcam1) < 200.0f) ||
		(GetDistance (cav3, walkcam1) < 200.0f) //||
		//(GetDistance (cav4, walkcam1) < 200.0f) ||
		//(GetDistance (cav5, walkcam1) < 200.0f)
		) && (cav1pathwarn1 == false)
		)
	{
		AudioMessage("misns118.wav");
		cav1pathwarn1 = true;
	}

	if 
		(
		(cavpath2 == true) && 
		(
		(GetDistance (cav1, walkcam2) < 50.0f) ||
		(GetDistance (cav2, walkcam2) < 50.0f) ||
		(GetDistance (cav3, walkcam2) < 50.0f) //||
		//(GetDistance (cav4, walkcam2) < 50.0f) ||
		//(GetDistance (cav5, walkcam2) < 50.0f)
		) && (cav2pathwarn1 == false)
		)
	{
		AudioMessage("misns119.wav");
		cav2pathwarn1 = true;
	}

	/*if 
		(
		(cavpath3 == true) && 
		(
		(GetDistance (cav1, walkcam1) < 200.0f) ||
		(GetDistance (cav2, walkcam1) < 200.0f) ||
		(GetDistance (cav3, walkcam1) < 200.0f) ||
		(GetDistance (cav4, walkcam1) < 200.0f) ||
		(GetDistance (cav5, walkcam1) < 200.0f)
		) && (cav3pathwarn1 == false)
		)
	{
		AudioMessage("misns118.wav");
		cav3pathwarn1 = true;
	}

	if 
		(
		(cavpath3 == true) && 
		(
		(GetDistance (cav1, hidcam2) < 60.0f) ||
		(GetDistance (cav2, hidcam2) < 60.0f) ||
		(GetDistance (cav3, hidcam2) < 60.0f) ||
		(GetDistance (cav4, hidcam2) < 60.0f) ||
		(GetDistance (cav5, hidcam2) < 60.0f)
		) && (cav3pathwarn2 == false)
		)
	{
		AudioMessage("misns120.wav");
		cav3pathwarn2 = true;
	}
	
	if 
		(
		(cavpath4 == true) && 
		(
		(GetDistance (cav1, walkcam2) < 50.0f) ||
		(GetDistance (cav2, walkcam2) < 50.0f) ||
		(GetDistance (cav3, walkcam2) < 50.0f) ||
		(GetDistance (cav4, walkcam2) < 50.0f) ||
		(GetDistance (cav5, walkcam2) < 50.0f)
		) && (cav4pathwarn1 == false)
		)
	{
		AudioMessage("misns119.wav");
		cav4pathwarn1 = true;
	}

	if 
		(
		(cavpath4 == true) && 
		(
		(GetDistance (cav1, hidcam1) < 100.0f) ||
		(GetDistance (cav2, hidcam1) < 100.0f) ||
		(GetDistance (cav3, hidcam1) < 100.0f) ||
		(GetDistance (cav4, hidcam1) < 100.0f) ||
		(GetDistance (cav5, hidcam1) < 100.0f)
		) && (cav4pathwarn2 == false)
		)
	{
		AudioMessage("misns121.wav");
		cav4pathwarn2 = true;
	}*/

			

	


	
	








}

IMPLEMENT_RTIME(Misns1Mission)

Misns1Mission::Misns1Mission(void)
{
}

Misns1Mission::~Misns1Mission()
{
}

void Misns1Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

bool Misns1Mission::Load(file fp)
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

bool Misns1Mission::PostLoad(void)
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

bool Misns1Mission::Save(file fp)
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

void Misns1Mission::Update(void)
{
	AiMission::Update();
	Execute();
}
