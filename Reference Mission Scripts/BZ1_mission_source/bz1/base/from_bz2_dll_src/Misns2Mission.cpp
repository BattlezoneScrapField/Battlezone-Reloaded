#include "GameCommon.h"

#include "..\fun3d\AiMission.h"
#include "..\fun3d\ScriptUtils.h"

/*
	Misns2Mission
*/

class Misns2Mission : public AiMission {
	DECLARE_RTIME(Misns2Mission)
public:
	Misns2Mission(void);
	~Misns2Mission();
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
				cintimeset, missionstart, missionwon, nicetry, missionfail, wave1gone, wave2gone, wave3gone,
				wave4gone, wave5gone, bdplatoonspawned, navpoint1reached, navpoint2reached, navpoint3reached,
				navpoint4reached, navpoint5reached, sneaktimeset, 
				camnet1found, camnet2found, navpoint6reached, navpoint7reached,
				navpoint8reached, artwarning, patrolsent, playerfound, 
				platooncamdone, t1arrive, t2arrive, t3arrive, newobjective, surrender,
				cam1done, cam2done, cam3done, cam4done,
				openingcindone, bdcindone,
				b_last;
		};
		bool b_array[37];
	};

	// floats
	union {
		struct {
			float
				wave1start, platooncam, sneaktime, alerttime, cintime,
				cam1t, cam2t, cam3t, cam4t,
				f_last;
		};
		float f_array[9];
	};

	// handles
	union {
		struct {
			Handle
				player, lu, e1a, e1b, e2a, e2b, e3a, e3b, t1, t2, t3,
				bd1, bd2, bd3, bd4, bd5, bd6, bd7, bd8, bd9, bd10, bd11,
				bd12, bd13, bd14, bd15, bd16, bd17, bd18, bd19, bd20, bd21,
				bd22, bd23, bd24, bd25, bd26, bd27, bd100, bd101, bd102, bd103, 
				bd104, bd105, bd106, bd107, bd108, bd109, bd110,
				dummy, bdcam1,bdcam2,bdcam3,bdcam4,bdcam5,bdcam6,bdcam7,bdcam8,
				bdcam9,bdcam10,bdcam11,bdcam12,bdcam13,bdcam14, launchpad, 
				enemy1, enemy2, enemy3, cutoff, cam1,
				nav1, nav2, nav3, nav4, nav5, nav6, nav7, nav8, nav9, nav10, nav11,
				nav12, nav13, nav14, nav1route, navmine,
				cutoff1, cutoff2, cutoff3, cutoff4, cutoff5, cutoff6,
				pat1, pat2, one, two, three, four, five, six, seven, eight, nine, ten,
				h_last;
		};
		Handle h_array[104];
	};

	// integers
	union {
		struct {
			int
				audmsg, aud1, aud2, aud3, aud4, aud10,
				aud51, aud52, aud50,
				i_last;
		};
		int i_array[9];
	};
};

void Misns2Mission::Setup(void)
{
	/*
	Here's where you
	set the values
	at the start.  
	*/
	player = 0; 
		lu = 0; 
		aud50 = 0;
		aud51 = 0;
		aud52 = 0;
		e1a = 0;
		e1b = 0; 
		e2a = 0; 
		e2b = 0; 
		e3a = 0;
		e3b = 0; 
		t1 = 0; 
		t2 = 0; 
		t3 = 0;
		bd1 = 0; 
		bd2 = 0; 
		bd3 = 0;
		bd4 = 0;
		bd5 = 0;
		bd6 = 0; 
		bd7 = 0; 
		bd8 = 0; 
		bd9 = 0; 
		bd10 = 0;
		bd11 = 0;
		bd12 = 0; 
		bd13 = 0; 
		bd14 = 0; 
		bd15 = 0; 
		bd16 = 0; 
		bd17 = 0; 
		bd18 = 0; 
		bd19 = 0;
		bd20 = 0; 
		bd21 = 0;
		bd22 = 0; 
		bd23 = 0; 
		bd24 = 0; 
		bd25 = 0; 
		bd26 = 0; 
		bd27 = 0; 
		bd100 = 0;
		bd101 = 0; 
		bd102 = 0; 
		bd103 = 0; 
		bd104 = 0;
		bd105 = 0; 
		bd106 = 0; 
		bd107 = 0; 
		bd108 = 0;
		bd109 = 0; 
		bd110 = 0;
		aud10 = 0;
		dummy = 0; 
		bdcam1 = 0;
		bdcam2 = 0;
		bdcam3 = 0;
		bdcam4 = 0;
		bdcam5 = 0;
		bdcam6 = 0;
		bdcam7 = 0;
		bdcam8 = 0;
		bdcam9 = 0;
		bdcam10 = 0;
		bdcam11 = 0;
		bdcam12 = 0;
		bdcam13 = 0;
		bdcam14 = 0; 
		launchpad = 0; 
		enemy1 = 0; 
		enemy2 = 0; 
		enemy3 = 0;
		cutoff = 0;
		nav1 = 0; 
		nav2 = 0; 
		nav3 = 0; 
		nav4 = 0; 
		nav5 = 0; 
		nav6 = 0; 
		nav7 = 0; 
		nav8 = 0; 
		nav9 = 0;
		navmine = 0;
		nav10 = 0;
		nav11 = 0;
		nav12 = 0;
		nav13 = 0;
		nav14 = 0; 
		nav1route = 0;
		cutoff1 = 0; 
		cutoff2 = 0; 
		cutoff3 = 0; 
		cutoff4 = 0; 
		cutoff5 = 0; 
		cutoff6 = 0;
		aud1 = 0;
		pat1 = 0; 
		pat2 = 0; 
		one = 0; 
		two = 0; 
		three = 0;
		four = 0; 
		five = 0; 
		six = 0; 
		seven = 0;
		eight = 0;
		nine = 0; 
		ten = 0;
	missionstart = false;
	missionwon = false;
	missionfail = false;
	patrolsent = false;
	playerfound = false;
	sneaktimeset = false;
	wave1gone = false;
	wave2gone = false;
	wave3gone = false;
	wave4gone = false;
	wave5gone = false;
	surrender = false;
	openingcindone = false;
	cam1 = 0;
	bdcindone = false;
	aud2 = 0;
	aud3 = 0;
	aud4 = 0;
	camnet1found = false;
	camnet2found = false;
	nicetry = false;
	artwarning = false;
	bdplatoonspawned = false;
	navpoint1reached = false;
	navpoint2reached = false;
	navpoint3reached = false;
	navpoint4reached = false;
	navpoint5reached = false;
	navpoint6reached = false;
	navpoint7reached = false;
	navpoint8reached = false;
	platooncamdone = false;
	cam1done = false;
	cam2done = false;
	cam3done = false;
	cam4done = false;
	t1arrive = false;
	t2arrive = false;
	t3arrive = false;
	newobjective = false;
	cintimeset = false;
	cintime = 999999999.0f;
	wave1start = 99999999.0f;
	platooncam = 99999999.0f;
	sneaktime = 9999999999.0f;
	alerttime = 99999999999.0f;
	cam1t = 99999999999.0f;
	cam2t = 99999999999.0f;
	cam3t = 99999999999.0f;
	cam4t = 99999999999.0f;
	
}

void Misns2Mission::AddObject(Handle h)
{
}

void Misns2Mission::Execute(void)
{
	/*
		Here is where you 
		put what happens 
		every frame.  
	*/

	if
		(missionstart == false)
	{
		aud1 = AudioMessage ("misns200.wav");
		//AudioMessage ("misns202.wav");
		launchpad = GetHandle ("sblpad59_i76building");
		player = GetHandle ("svtank0_wingman");
		lu = GetHandle ("svfigh2_wingman");
		nav1route = GetHandle ("apcamr5_camerapod");
		//navmine = GetHandle("navmine");
		e1a = GetHandle ("svfigh3_wingman");
		e2b = GetHandle ("svfigh5_wingman");
		e3a = GetHandle ("svfigh6_wingman");
		e2a = GetHandle ("svtank5_wingman");
		e1b = GetHandle ("svtank4_wingman");
		e3b = GetHandle ("svtank12_wingman");
		t1 = GetHandle ("svapc0_apc");
		t2 = GetHandle ("svapc1_apc");
		t3 = GetHandle ("svapc2_apc");
		wave1start = GetTime () + 10.0f;
		missionstart = true;
		AddObjective ("misns201.otf", WHITE);
		AddObjective ("misns202.otf", WHITE);
		AddObjective ("misns203.otf", WHITE);
		CameraReady();
		cam1 = GetHandle("cam1");
		cam1t = GetTime() + 9.0f;
		cam2t = GetTime() + 9.01f;
		cam3t = GetTime() + 24.0f;
		cam4t = GetTime() + 34.0f;
		GameObjectHandle :: GetObj(cam1) ->SetName ("Launch Pad");
	}

	if
		(openingcindone == false) 
	{
		CameraPath("cinpath1", 500, 200, t1);
		if
			(
			(IsAudioMessageDone(aud1)) || (CameraCancelled())
			)
		{
			openingcindone = true;
			CameraFinish();
			StopAudioMessage(aud1);
			AudioMessage ("misns202.wav");
		}
	}

	/*if
		(
		(cam1t > GetTime()) && (cam1done == false)
		)
	{
		CameraPath("cinpath1", 500, 800, t1);
	}
	if
		(
		(cam2t < GetTime()) && (cam2done == false)
		)
	{
		CameraPath("cinpath2", 600, 7000, nav1route);
		cam1done = true;
	}
	if
		(
		(cam3t < GetTime()) && (cam3done == false)
		)
	{
		CameraPath("cinpath4", 400, 4000, launchpad);
		cam2done = true;
	}
	if
		(
		(cam4t < GetTime()) && (cam4done == false)
		)
	{
		CameraFinish();
		cam3done = true;
		cam4done = true;
	}*/

	if 
		(newobjective == true)
	{
		ClearObjectives();
		if
			(!IsAlive(t1))
		{
			AddObjective ("misns201.otf", RED);
		}
		if
			(!IsAlive(t2))
		{
			AddObjective ("misns202.otf", RED);
		}
		if
			(!IsAlive(t3))
		{
			AddObjective ("misns203.otf", RED);
		}
		if
			(
			(IsAlive(t1)) && (t1arrive == false)
			)
		{
			AddObjective ("misns201.otf", WHITE);
		}
		if
			(
			(IsAlive(t1)) && (t1arrive == true)
			)
		{
			AddObjective ("misns201.otf", GREEN);
		}
		if
			(
			(IsAlive(t2)) && (t2arrive == true)
			)
		{
			AddObjective ("misns202.otf", GREEN);
		}
		if
			(
			(IsAlive(t2)) && (t2arrive == false)
			)
		{
			AddObjective ("misns202.otf", WHITE);
		}
		if
			(
			(IsAlive(t3)) && (t3arrive == true)
			)
		{
			AddObjective ("misns203.otf", GREEN);
		}
		if
			(
			(IsAlive(t3)) && (t3arrive == false)
			)
		{
			AddObjective ("misns203.otf", WHITE);
		}
		newobjective = false;
	}

	if 
		(
		(wave1start < GetTime()) && (wave1gone == false)
		)
	{
		bd1 = BuildObject ("bvtank", 2, "bdsp1");
		bd2 = BuildObject ("bvraz", 2, "bdsp1");
		//bd3 = BuildObject ("bvraz", 2, "bdsp1");
		//bd4 = BuildObject ("bvraz", 2, "bdsp1");
		Attack (bd1, t1, 1);
		Attack (bd2, t3, 1);
		//Attack (bd3, t3, 1);
		//Attack (bd4, t3, 1);
		SetIndependence (bd1, 1);
		SetIndependence (bd2, 1);
		//SetIndependence (bd3, 1);
		//SetIndependence (bd4, 1);
		wave1gone = true;
		wave1start = 999999999999.0f;
	}

	if
		(
		(wave1gone == true) && 
		(!IsAlive(bd1)) &&
		(!IsAlive(bd2)) &&
		(cintimeset == false)
		)
	{
		AudioMessage("misns203.wav");
		cintime = GetTime() +3.0f;
		cintimeset = true;
	}

	if 
		(
		(!IsAlive(bd1)) &&
		(!IsAlive(bd2)) &&
		(surrender == false) &&
		(wave1gone == true) && (cintime < GetTime())
		)
	{
		aud2 = AudioMessage("misns204.wav");
		aud3 = AudioMessage("misns205.wav");
		surrender = true;
		CameraReady();
		platooncam = GetTime () + 20.0f;
		bd100 = BuildObject("bvtank", 2, "100");
		bd101 = BuildObject("bvtank", 2, "101");
		bd102 = BuildObject("bvtank", 2, "102");
		bd103 = BuildObject("bvtank", 2, "103");
		bd104 = BuildObject("bvtank", 2, "104");
		bd105 = BuildObject("bvtank", 2, "105");
		bd106 = BuildObject("bvtank", 2, "106");
		bd107 = BuildObject("bvtank", 2, "107");
		bd108 = BuildObject("bvtank", 2, "108");
		bd109 = BuildObject("bvtank", 2, "109");
		bd110 = BuildObject("bvtank", 2, "110");
	}

	if
		(bdcindone == false)
	{
		if
			(surrender == true)
		{
			CameraPath("platooncam", 1000, 600, bd100);
			if
				(
				(
				(IsAudioMessageDone(aud2)) &&
				(IsAudioMessageDone(aud3))
				) || (CameraCancelled())
				)
			{
				CameraFinish();
				StopAudioMessage(aud2);
				StopAudioMessage(aud3);
				aud4 = AudioMessage("misns206.wav");
				platooncamdone = true;
				Attack (bd103, t3);
				Attack (bd104, t2);
				RemoveObject(bd100);
				RemoveObject(bd101);
				RemoveObject(bd102);
				RemoveObject(bd105);
				RemoveObject(bd106);
				RemoveObject(bd107);
				RemoveObject(bd108);
				RemoveObject(bd109);
				RemoveObject(bd110);
				bdcindone = true;
			}
		}
	}


/*	if 
		(
		(surrender == true) && (platooncam > GetTime())
		)

	{
		CameraPath("platooncam", 1000, 600, bd100);
	}

	if 
		(
		(platooncam < GetTime()) && (platooncamdone == false)
		)
	{
		CameraFinish();
		platooncamdone = true;
		Attack (bd103, t3);
		Attack (bd104, t2);
		RemoveObject(bd100);
		RemoveObject(bd101);
		RemoveObject(bd102);
		RemoveObject(bd105);
		RemoveObject(bd106);
		RemoveObject(bd107);
		RemoveObject(bd108);
		RemoveObject(bd109);
		RemoveObject(bd110);
	}*/

	if 
		(wave2gone == false)
	{
		enemy3 = GetNearestVehicle("bdsp2", 1);
	}

	if 
		(
		(wave2gone == false) && (GetDistance(enemy3, "bdsp2") < 420.0f)
		)
	{
		bd5 = BuildObject ("bvraz", 2, "bdsp2");
		bd6 = BuildObject ("bvraz", 2, "bdsp2");
		bd7 = BuildObject ("bvraz", 2, "bdsp2");
		bd8 = BuildObject ("bvtank", 2, "bdsp2");
		Attack (bd5, t3, 1);
		Attack (bd6, t1, 1);
		Attack (bd7, t3, 1);
		Attack (bd8, t2, 1);
		SetIndependence (bd5, 1);
		SetIndependence (bd6, 1);
		SetIndependence (bd7, 1);
		SetIndependence (bd8, 1);
		wave2gone = true;
	}

	if 
		(
		(
		(GetDistance (t1, "nav1") < 200.0f) ||
		(GetDistance (t2, "nav1") < 200.0f) ||
		(GetDistance (t3, "nav1") < 200.0f)
		)
		&& (wave2gone == false)
		)
	{
		bd5 = BuildObject ("bvraz", 2, "bdsp2");
		bd6 = BuildObject ("bvraz", 2, "bdsp2");
		bd7 = BuildObject ("bvraz", 2, "bdsp2");
		bd8 = BuildObject ("bvtank", 2, "bdsp2");
		Attack (bd5, t1, 1);
		Attack (bd6, t2, 1);
		Attack (bd7, t2, 1);
		Attack (bd8, t3, 1);
		SetIndependence (bd5, 1);
		SetIndependence (bd6, 1);
		SetIndependence (bd7, 1);
		SetIndependence (bd8, 1);
		wave2gone = true;

	}

	if 
		(wave3gone == false)
	{
		enemy1 = GetNearestVehicle("bdsp3", 1);
	}

	if
		(
		(wave3gone == false) && (GetDistance (enemy1, "bdsp3") < 450.0f)
		&& (GetTeamNum(enemy1) == 1)
		)
	{
		bd9 = BuildObject ("bvartl", 2, "bdsp3");
		bd10 = BuildObject ("bvartl", 2, "bdsp3");
		bd11 = BuildObject ("bvtank", 2, "bdsp3");
		SetIndependence(bd11, 1);
		wave3gone = true;
	}

	if 
		(
		(wave3gone == false) && 
			(
			(GetDistance (t1, "nav3") < 400.0f) ||
			(GetDistance (t2, "nav3") < 400.0f) ||
			(GetDistance (t3, "nav3") < 400.0f)
			)
		)
	{
		bd9 = BuildObject ("bvartl", 2, "bdsp3");
		bd10 = BuildObject ("bvartl", 2, "bdsp3");
		bd11 = BuildObject ("bvtank", 2, "bdsp3");
		//bdcutoff1 = BuildObject("bvraz", 2, "nav5");
		//bdcutoff2 = BuildObject("bvraz", 2, "nav5");
		//bdcutoff3 = BuildObject("bvraz", 2, "nav5");
		//Attack(bdcutoff1, t1);
		//Attack(bdcutoff2, t2);
		//Attack(bdcut0ff2, t3);
		BuildObject ("proxmine", 2, "mine1");
		BuildObject ("proxmine", 2, "mine2");
		BuildObject ("proxmine", 2, "mine3");
		BuildObject ("proxmine", 2, "mine4");
		BuildObject ("proxmine", 2, "mine5");
		BuildObject ("proxmine", 2, "mine6");
		BuildObject ("proxmine", 2, "mine7");
		BuildObject ("proxmine", 2, "mine8");
		BuildObject ("proxmine", 2, "mine9");
		BuildObject ("proxmine", 2, "mine10");
		BuildObject ("proxmine", 2, "mine11");
		BuildObject ("proxmine", 2, "mine12");
		BuildObject ("proxmine", 2, "mine13");
		BuildObject ("proxmine", 2, "mine14");
		BuildObject ("proxmine", 2, "mine15");
		BuildObject ("proxmine", 2, "mine16");
		BuildObject ("proxmine", 2, "mine17");
		BuildObject ("proxmine", 2, "mine18");
		BuildObject ("proxmine", 2, "mine19");
		Attack(bd9, t3);
		Attack(bd10, t2);
		Follow(bd11, bd9);
		SetIndependence(bd11, 1);
		wave3gone = true;
		alerttime = GetTime () + 15.0f;
	}
	

	if
		(
		(alerttime < GetTime()) && (artwarning == false)
		)
	{
		SetObjectiveOn(bd9);
		SetObjectiveOn(bd10);
		AudioMessage ("misns210.wav");
		SetObjectiveOn(bd12);
		SetObjectiveOn(bd13);
		artwarning = true;
	}

	if 
		(wave4gone == false)
	{
		enemy2 = GetNearestVehicle("bdsp4", 1);
	}

	if
		(
		(wave4gone == false) && (GetDistance (enemy2, "bdsp4") < 450.0f)
		&& (GetTeamNum(enemy2) == 1)
		)
	{
		bd12 = BuildObject ("bvartl", 2, "bdsp4");
		bd13 = BuildObject ("bvtank", 2, "bdsp4");
		bd14 = BuildObject ("bvtank", 2, "bdsp4");
		SetIndependence(bd14, 1);
		wave4gone = true;
	}

	if 
		(
		(wave4gone == false) &&
		(
		(GetDistance (t1, "nav3") < 200.0f) ||
		(GetDistance (t2, "nav3") < 200.0f) ||
		(GetDistance (t3, "nav3") < 200.0f)
		)
		)
	{
		bd12 = BuildObject ("bvartl", 2, "bdsp4");
		bd13 = BuildObject ("bvartl", 2, "bdsp4");
		bd14 = BuildObject ("bvtank", 2, "bdsp4");
		Attack(bd12, t1);
		Attack(bd13, t2);
		Follow(bd14, bd12);
		SetIndependence(bd14, 1);
		wave4gone = true;
	}

	if 
		(
		(wave4gone == true) && (wave3gone == true) && 
		(bdplatoonspawned == false) && (!IsAlive(bd9)) &&
		(!IsAlive(bd10)) && (!IsAlive(bd12)) &&
		(!IsAlive(bd13))
		)
	{
		bd15 = BuildObject ("bvtank", 2, "bdspmain");
		bd16 = BuildObject ("bvtank", 2, "bdspmain");
		bd17 = BuildObject ("bvtank", 2, "bdspmain");
		bd18 = BuildObject ("bvtank", 2, "bdspmain");
		bdplatoonspawned = true;
		Attack (bd15, t1);
		Attack (bd16, t1);
		Attack (bd17, t2);
		Attack (bd18, t2);
	}


	if 
		(
		(wave5gone == false) && 
		((GetDistance(player, launchpad) < 550.0f)
		|| (GetDistance(t1, launchpad) < 550.0f) ||
		(GetDistance(t2, launchpad) < 550.0f) ||
		(GetDistance(t3, launchpad) < 550.0f)
		)
		)
	{
		bd22 = BuildObject ("bvraz", 2, "bdsp5");
		bd23 = BuildObject ("bvraz", 2, "bdsp5");
		bd24 = BuildObject ("bvraz", 2, "bdsp5");
		//bd25 = BuildObject ("bvtank", 2, "bdsp5");
		//bd26 = BuildObject ("bvtank", 2, "bdsp5");
		Attack (bd22, t1);
		Attack (bd23, t2);
		Attack (bd24, t3);
		wave5gone = true;
	}


	if 
		(bdplatoonspawned == false)
	{
		dummy = GetNearestVehicle("bdspmain", 1);
	}

	if 
		(
		(GetDistance (dummy, "bdspmain") < 420.0f) &&
		(bdplatoonspawned == false) && (GetTeamNum (dummy) == 1)
		)
	{
		bd15 = BuildObject ("bvtank", 2, "bdspmain");
		bd16 = BuildObject ("bvtank", 2, "bdspmain");
		bd17 = BuildObject ("bvtank", 2, "bdspmain");
		bd18 = BuildObject ("bvtank", 2, "bdspmain");
		bd19 = BuildObject ("bvraz", 2, "bdspmain");
		bd20 = BuildObject ("bvraz", 2, "bdspmain");
		bd21 = BuildObject ("bvraz", 2, "bdspmain");
		bdplatoonspawned = true;
	}

	if
		(
		(GetDistance(player, "bdnet4") < 550.0f) && (camnet1found == false)
		)
	{
		/*nav1 = BuildObject ("apcamr", 2, "bdnet1");
		nav2 = BuildObject ("apcamr", 2, "bdnet2");
		nav3 = BuildObject ("apcamr", 2, "bdnet3");
		nav4 = BuildObject ("apcamr", 2, "bdnet4");
		nav5 = BuildObject ("apcamr", 2, "bdnet5");
		nav6 = BuildObject ("apcamr", 2, "bdnet6");*/

		cutoff1 = BuildObject ("bvtank", 2, "bdnet4");
		cutoff2 = BuildObject ("bvtank", 2, "bdnet4");
		cutoff3 = BuildObject ("bvraz", 2, "bdnet4");
		cutoff4 = BuildObject ("bvraz", 2, "bdnet4");
		cutoff5 = BuildObject ("bvraz", 2, "bdnet4");
		cutoff6 = BuildObject ("bvraz", 2, "bdnet4");
		Attack (cutoff1, t1);
		SetIndependence (cutoff1, 1);
		Attack (cutoff2, t1);
		SetIndependence (cutoff2, 1);
		Attack (cutoff3, t2);
		SetIndependence (cutoff3, 1);
		Attack (cutoff4, t2);
		SetIndependence (cutoff4, 1);
		Attack (cutoff5, t3);
		SetIndependence (cutoff5, 1);
		Attack (cutoff6, t3);
		SetIndependence (cutoff6, 1);
		camnet1found = true;
		bd12 = BuildObject ("bvartl", 2, "bdsp4");
		bd13 = BuildObject ("bvartl", 2, "bdsp4");
		bd14 = BuildObject ("bvtank", 2, "bdsp4");
		wave3gone = true;
		Attack(bd12, t3);
		Follow(bd13, bd12);
		Follow(bd14, bd12);
	}

	if
		(
		(camnet1found == true) && (nicetry == false)
		)
	{
		cutoff = GetNearestEnemy(cutoff1);
	}

	if
		(
		(GetDistance (cutoff, cutoff1) < 400.0f) && (nicetry == false)
		)
	{
		AudioMessage("misns209.wav");
		nicetry = true;
	}

	if
		(
		(
		(GetDistance(player, "bdnet9") < 410.0f) ||
		(GetDistance(player, "bdnet12") < 410.0f)
		)
		&& (camnet2found == false)
		)
	{
		nav7 = BuildObject ("apcamr", 2, "bdnet7");
		nav8 = BuildObject ("apcamr", 2, "bdnet8");
		nav9 = BuildObject ("apcamr", 2, "bdnet9");
		nav10 = BuildObject ("apcamr", 2, "bdnet10");
		nav11 = BuildObject ("apcamr", 2, "bdnet11");
		nav12 = BuildObject ("apcamr", 2, "bdnet12");
		nav13 = BuildObject ("apcamr", 2, "bdnet13");
		nav14 = BuildObject ("apcamr", 2, "bdnet14");
		camnet2found = true;
		AudioMessage ("misns207.wav");
	}

	if
		(camnet2found == true)
	{
		one = GetNearestVehicle("bdnet7",1);
		two = GetNearestVehicle("bdnet8",1);
		three = GetNearestVehicle("bdnet9",1);
		four = GetNearestVehicle("bdnet10",1);
		five = GetNearestVehicle("bdnet11",1);
		six = GetNearestVehicle("bdnet12",1);
		seven = GetNearestVehicle("bdnet13",1);
		eight = GetNearestVehicle("bdnet14",1);
		if
			(
				((GetDistance (one, "bdnet7") < 20.0f) ||
				(GetDistance (two, "bdnet8") < 20.0f) ||
				(GetDistance (three, "bdnet9") < 20.0f) ||
				(GetDistance (four, "bdnet10") < 20.0f) ||
				(GetDistance (five, "bdnet11") < 20.0f) ||
				(GetDistance (six, "bdnet12") < 20.0f) ||
				(GetDistance (seven, "bdnet13") < 20.0f) ||
				(GetDistance (eight, "bdnet14") < 20.0f)) 
				&& (wave3gone == false)
			)
		{
			bd9 = BuildObject ("bvartl", 2, "bdsp3");
			bd10 = BuildObject ("bvartl", 2, "bdsp3");
			bd11 = BuildObject ("bvtank", 2, "bdsp3");
			Attack(bd9, t3);
			Attack(bd10, t2);
			Follow(bd11, bd9);
			wave3gone = true;
		}
	}

	if
		(
		(camnet2found == true) && 
		(
		(!IsAlive(nav7)) ||
		(!IsAlive(nav8)) ||
		(!IsAlive(nav9)) ||
		(!IsAlive(nav10)) ||
		(!IsAlive(nav11)) ||
		(!IsAlive(nav12)) ||
		(!IsAlive(nav13)) ||
		(!IsAlive(nav14)) 
		) && (sneaktimeset == false)
		)
	{
		sneaktime = GetTime () + 45.0f;
		sneaktimeset = true;
		AudioMessage ("misns208.wav");
	}

	if
		(
		(sneaktime < GetTime()) && (patrolsent == false)
		)
	{
		pat1 = BuildObject ("svfigh", 2, "bdspmain");
		pat2 = BuildObject ("svfigh", 2, "bdspmain");
		patrolsent = true;
		Goto (pat1, "bdnet9");
		Goto (pat2, "bdnet12");
	}

	if
		(
		(patrolsent == true) && (playerfound == false)
		)
	{
		ten = GetNearestEnemy (pat1);
		nine = GetNearestEnemy (pat2);
	if
		(
		(GetDistance (nine, pat1) < 50.0f) && (wave3gone == false)
		)
		{
		if
			(wave3gone == false)
			{
		bd9 = BuildObject ("bvartl", 2, "bdsp3");
			bd10 = BuildObject ("bvartl", 2, "bdsp3");
			bd11 = BuildObject ("bvtank", 2, "bdsp3");
			Attack(bd9, t3);
			Attack(bd10, t2);
			Follow(bd11, bd9);
			wave3gone = true;
			}

		if
			(wave3gone == true)
				{
			if
				(IsAlive(bd9))
					{
				Attack(bd9, nine);
					}
			if
				(IsAlive(bd10))
					{
				Attack(bd10, nine);
					}
			if
				(IsAlive(bd11))
					{
				Follow(bd11,bd9);
					}
			wave3gone = true;
				}
	}
		if
		(
		(GetDistance (nine, pat1) < 50.0f) && (wave3gone == false)
		)
	{
		if
			(wave3gone == false)
		{
		bd9 = BuildObject ("bvartl", 2, "bdsp3");
			bd10 = BuildObject ("bvartl", 2, "bdsp3");
			bd11 = BuildObject ("bvtank", 2, "bdsp3");
			Attack(bd9, ten);
			Attack(bd10, ten);
			Follow(bd11, bd9);
			wave3gone = true;
		}

		if
			(wave3gone == true)
			{
			if
				(IsAlive(bd9))
				{
				Attack(bd9, ten);
				}
			if
				(IsAlive(bd10))
				{
				Attack(bd10, ten);
				}
			if
				(IsAlive(bd11))
				{
				Follow(bd11,ten);
				}
			}
		wave3gone = true;
		}

	}

	if
		(
		(patrolsent == true) && (playerfound == false) &&
		(
		(GetDistance (pat1, "bdnet9") < 20.0f) ||
		(GetDistance (pat2, "bdnet12") < 20.0f)
		) && (bdplatoonspawned == false)
		)
	{
		bd15 = BuildObject ("bvtank", 2, "bdspmain");
		bd16 = BuildObject ("bvtank", 2, "bdspmain");
		bd17 = BuildObject ("bvtank", 2, "bdspmain");
		bd18 = BuildObject ("bvtank", 2, "bdspmain");
		bd19 = BuildObject ("bvraz", 2, "bdspmain");
		bd20 = BuildObject ("bvraz", 2, "bdspmain");
		bd21 = BuildObject ("bvraz", 2, "bdspmain");
		bdplatoonspawned = true;
		Attack (bd15, t1);
		SetIndependence (bd15, 1);
		Attack (bd16, t1);
		SetIndependence (bd16, 1);
		Attack (bd17, t2);
		SetIndependence (bd17, 1);
		Attack (bd18, t2);
		SetIndependence (bd18, 1);
		Attack (bd19, t3);
		SetIndependence (bd19, 1);
		Attack (bd20, t3);
		SetIndependence (bd20, 1);
		Attack (bd21, t1);
		SetIndependence (bd21, 1);
	}

	if
		(
		(patrolsent == true) && (playerfound == false) &&
		(
		(GetDistance (pat1, "bdnet9") < 20.0f) ||
		(GetDistance (pat2, "bdnet12") < 20.0f)
		)
		)
	{
		if
			(wave3gone == false)
				{
				bd9 = BuildObject ("bvartl", 2, "bdsp3");
				bd10 = BuildObject ("bvartl", 2, "bdsp3");
				bd11 = BuildObject ("bvtank", 2, "bdsp3");
				Attack(bd9, t3);
				Attack(bd10, t2);
				Follow(bd11, bd9);
				wave3gone = true;
				}
		if
			(wave3gone == true)
		{
			if
				(IsAlive(bd9))
			{
				Attack(bd9, t3);
			}
			if
				(IsAlive(bd10))
			{
				Attack(bd10, t2);
			}
			if
				(IsAlive(bd11))
			{
				Follow(bd11, bd9);
			}
		}
		wave3gone = true;
	}


		
			

	

		







	//victory points

	if 
		(
		(!IsAlive (t1)) && (missionfail == false)
		)
	{
		aud10 = AudioMessage ("misns212.wav");
		missionfail = true;
		newobjective = true;
	}

	if 
		(
		(!IsAlive (t2)) && (missionfail == false)
		)
	{
		aud10 = AudioMessage ("misns212.wav");
		missionfail = true;
		newobjective = true;
	}

	if 
		(
		(!IsAlive (t3)) && (missionfail == false)
		)
	{
		aud10 = AudioMessage ("misns212.wav");
		missionfail = true;
		newobjective = true;
	}

	if
		(
		(missionfail == true) && (IsAudioMessageDone(aud10))
		)
	{
		FailMission(GetTime(), "misns2l1.des");
	}

	if 
		(
		(GetDistance (t1, launchpad) < 100.0f) &&
		(t1arrive == false)
		)
	{
		AudioMessage ("misns216.wav");
		t1arrive = true;
		newobjective = true;
	}

	if 
		(
		(GetDistance (t2, launchpad) < 100.0f) &&
		(t2arrive == false)
		)
	{
		AudioMessage ("misns217.wav");
		t2arrive = true;
		newobjective = true;
	}

	if 
		(
		(GetDistance (t3, launchpad) < 100.0f) &&
		(t3arrive == false)
		)
	{
		AudioMessage ("misns218.wav");
		t3arrive = true;
		newobjective = true;
	}
	if 
		(
		(missionwon == false) && (t1arrive == true) &&
		(t2arrive == true) && (t3arrive == true)
		)
	{
		missionwon = true;
		aud50 = AudioMessage("misns213.wav");
		aud51 = AudioMessage("misns214.wav");
		aud52 = AudioMessage("misns215.wav");

		if
			(IsAlive(bd3))
		{
			Retreat(bd3, "bdspmain", 1000);
		}
		if
			(IsAlive(bd4))
		{
			Retreat(bd4, "bdspmain", 1000);
		}
		if
			(IsAlive(bd5))
		{
			Retreat(bd5, "bdspmain", 1000);
		}
		if
			(IsAlive(bd6))
		{
			Retreat(bd6, "bdspmain", 1000);
		}
		if
			(IsAlive(bd7))
		{
			Retreat(bd7, "bdspmain", 1000);
		}
		if
			(IsAlive(bd8))
		{
			Retreat(bd8, "bdspmain", 1000);
		}
		if
			(IsAlive(bd9))
		{
			Retreat(bd9, "bdspmain", 1000);
		}
		if
			(IsAlive(bd10))
		{
			Retreat(bd10, "bdspmain", 1000);
		}
		if
			(IsAlive(bd11))
		{
			Retreat(bd11, "bdspmain", 1000);
		}
		if
			(IsAlive(bd12))
		{
			Retreat(bd12, "bdspmain", 1000);
		}
		if
			(IsAlive(bd13))
		{
			Retreat(bd13, "bdspmain", 1000);
		}
		if
			(IsAlive(bd14))
		{
			Retreat(bd14, "bdspmain", 1000);
		}
		if
			(IsAlive(bd15))
		{
			Retreat(bd15, "bdspmain", 1000);
		}
		if
			(IsAlive(bd16))
		{
			Retreat(bd16, "bdspmain", 1000);
		}
		if
			(IsAlive(bd17))
		{
			Retreat(bd17, "bdspmain", 1000);
		}
		if
			(IsAlive(bd18))
		{
			Retreat(bd18, "bdspmain", 1000);
		}
		if
			(IsAlive(bd19))
		{
			Retreat(bd19, "bdspmain", 1000);
		}
		if
			(IsAlive(bd20))
		{
			Retreat(bd20, "bdspmain", 1000);
		}
		if
			(IsAlive(bd21))
		{
			Retreat(bd21, "bdspmain", 1000);
		}
		if
			(IsAlive(bd22))
		{
			Retreat(bd22, "bdspmain", 1000);
		}
		if
			(IsAlive(bd23))
		{
			Retreat(bd23, "bdspmain", 1000);
		}
		if
			(IsAlive(bd24))
		{
			Retreat(bd24, "bdspmain", 1000);
		}
		if
			(IsAlive(bd25))
		{
			Retreat(bd25, "bdspmain", 1000);
		}
		if
			(IsAlive(bd26))
		{
			Retreat(bd26, "bdspmain", 1000);
		}
		if
			(IsAlive(bd27))
		{
			Retreat(bd27, "bdspmain", 1000);
		}
		if
			(IsAlive(bd100))
		{
			Retreat(bd100, "bdspmain", 1000);
		}
		if
			(IsAlive(bd101))
		{
			Retreat(bd101, "bdspmain", 1000);
		}
		if
			(IsAlive(bd102))
		{
			Retreat(bd102, "bdspmain", 1000);
		}
		if
			(IsAlive(bd103))
		{
			Retreat(bd103, "bdspmain", 1000);
		}
		if
			(IsAlive(bd104))
		{
			Retreat(bd104, "bdspmain", 1000);
		}
		if
			(IsAlive(bd105))
		{
			Retreat(bd105, "bdspmain", 1000);
		}
		if
			(IsAlive(bd106))
		{
			Retreat(bd106, "bdspmain", 1000);
		}
		if
			(IsAlive(bd107))
		{
			Retreat(bd107, "bdspmain", 1000);
		}
		if
			(IsAlive(bd108))
		{
			Retreat(bd108, "bdspmain", 1000);
		}
		if
			(IsAlive(bd109))
		{
			Retreat(bd109, "bdspmain", 1000);
		}
		if
			(IsAlive(bd110))
		{
			Retreat(bd110, "bdspmain", 1000);
		}
		if
			(IsAlive(cutoff1))
		{
			Retreat(cutoff1, "bdspmain", 1000);
		}
		if
			(IsAlive(cutoff2))
		{
			Retreat(cutoff2, "bdspmain", 1000);
		}
		if
			(IsAlive(cutoff3))
		{
			Retreat(cutoff3, "bdspmain", 1000);
		}
		if
			(IsAlive(cutoff4))
		{
			Retreat(cutoff4, "bdspmain", 1000);
		}
		if
			(IsAlive(cutoff5))
		{
			Retreat(cutoff5, "bdspmain", 1000);
		}
		if
			(IsAlive(cutoff6))
		{
			Retreat(cutoff6, "bdspmain", 1000);
		}
		if
			(IsAlive(pat1))
		{
			Retreat(pat1, "bdspmain", 1000);
		}
		if
			(IsAlive(pat2))
		{
			Retreat(pat2, "bdspmain", 1000);
		}


	}

	if
		(
		(missionwon == true) && (IsAudioMessageDone(aud50)) &&
		(IsAudioMessageDone(aud51)) &&
		(IsAudioMessageDone(aud52)) 
		)
	{
		SucceedMission(GetTime () + 0.0f, "misns2w1.des");
	}

	



	





	

}

IMPLEMENT_RTIME(Misns2Mission)

Misns2Mission::Misns2Mission(void)
{
}

Misns2Mission::~Misns2Mission()
{
}

void Misns2Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

bool Misns2Mission::Load(file fp)
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

bool Misns2Mission::PostLoad(void)
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

bool Misns2Mission::Save(file fp)
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

void Misns2Mission::Update(void)
{
	AiMission::Update();
	Execute();
}
