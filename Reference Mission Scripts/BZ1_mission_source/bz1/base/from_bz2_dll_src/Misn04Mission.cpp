#include "..\Shared\SPMission.h"

class Misn04Mission : public SPMission {
public:
	Misn04Mission(void)
	{
		b_count = &b_last - &b_first - 1;
		b_array = &b_first + 1;

		f_count = &f_last - &f_first - 1;
		f_array = &f_first + 1;

		h_count = &h_last - &h_first - 1;
		h_array = &h_first + 1;

		i_count = &i_last - &i_first - 1;
		i_array = &i_first + 1;
	}

	void Setup(void);
	void AddObject(Handle h);
	void Execute(void);

	// bools
	bool
		b_first,
		missionstart, basesecure, relicsecure, ob1, ob2, ob3, ob4,
		ob5, ob6, ob7, ob8, missionfail2, done,
		firstwave, found, ccahasrelic,
		build2, build3, build4, build5,
		secondwave, doneaud20, doneaud21, doneaud22, doneaud23,
		thirdwave,
		fourthwave, secureloopbreak, chewedout,
		fifthwave, possiblewin,
		attackccabase, endmission,
		fifthwavedestroyed,
		ccabasedestroyed, surveysent, reconsent,
		discrelic,
		missionend, loopbreak, loopbreak2, halfway, ccatugsent, cin1done,
		wave1arrive, wave2arrive, wave3arrive, wave4arrive, wave5arrive, obset,
		discoverrelic, newobjective, relicmoved, cheater,
		relicseen, retreat,
		missionwon, missionfail, wave1dead, wave2dead, wave3dead, wave4dead, wave5dead,
		endcinfinish, tur1sent, tur2sent, tur3sent, tur4sent,
		b_last;

	// floats
	float
		f_first,
		wave1, wave2, wave3, wave4, wave5, fetch, reconcca, startendcin,
		endcindone, notfound, ccatug, cintime1, 
		tur1, tur2, tur3, tur4, investigate,
		f_last;

	// handles
	Handle
		h_first,
		svrec, pu1, pu2, pu3, pu4, pu5, pu6, pu7, pu8, navbeacon,
		cheat1, cheat2, cheat3, cheat4, 
		cheat5, cheat6, cheat7, cheat8, cheat9, 
		cheat10, tug, svtug, tuge1, tuge2,
		player, surv1, surv2, surv3, surv4, 
		cam1, cam2, cam3, basecam, reliccam,
		avrec, w1u1, w1u2, safety, 
		w2u1, w2u2, w2u3,  
		w3u1, w3u2, w3u3, w3u4, 
		w4u1, w4u2, w4u3, w4u4, w4u5, 
		w5u1, w5u2, w5u3, w5u4, w5u5, w5u6,spawn1,spawn2,spawn3,relic,
		calipso, turret1, turret2, turret3, turret4,
		h_last;

	// integers
	int
		i_first,
		height,
		relicstartpos,
		wavenumber,
		investigator,
		warn,
		aud1, aud2, aud3, aud4, aud10, aud11, aud12, aud13, aud14,
		aud20, aud21, aud22, aud23,
		i_last;
};

SPMission *BuildMission(void)
{
	return new Misn04Mission();
}

void Misn04Mission::Setup(void)
{
	/*
	Here's where you
	set the values
	at the start.  
	*/
	missionstart = false;
	warn = 0;
	aud14 = 0;
	safety = 0;
	retreat = false;
	surveysent = false;
	reconsent = false;
	firstwave = false;
	secondwave = false;
	thirdwave = false;
	fourthwave = false;
	fifthwave = false;
	discrelic = false;
	ccatugsent = false;
	attackccabase = false;
	ccabasedestroyed = false;
	fifthwavedestroyed = false;
	missionend = false;
	wavenumber = 1;
	SetScrap (1, 20);
	missionwon = false;
	wave1dead = false;
	wave2dead = false;
	wave3dead = false;
	wave4dead = false;
	wave5dead = false;
	possiblewin = false;
	loopbreak = false;
	basesecure = false;
	newobjective = false;
	relicsecure = false;
	discoverrelic = false;
	missionfail2 = false;
	aud10 = 0;
	aud11 = 0;
	aud12 = 0;
	aud13 = 0;
	ccahasrelic = false;
	relicseen = false;
	obset = false;
	wave2 = 99999.0f;
	wave3 = 99999.0f;
	wave4 = 99999.0f;
	wave5 = 99999.0f;
	endcindone = 999999.0f;
	startendcin = 999999.0f;
	ccatug = 999999999999.0f;
	notfound = 999999999999999.0f;
	build2 = false;
	build3 = false;
	build4 = false;
	build5 = false;
	halfway = false;
	svrec = 0; 
		pu1 = 0; 
		pu2 = 0; 
		pu3 = 0; 
		pu4 = 0; 
		pu5 = 0; 
		pu6 = 0; 
		pu7 = 0;
		pu8 = 0;
		aud20 = 0;
		aud21 = 0;
		aud22 = 0;
		aud23 = 0;
		navbeacon = 0;
		cheat1 = 0; 
		cheat2 = 0; 
		cheat3 = 0;
		cheat4 = 0; 
		cheat5 = 0; 
		cheat6 = 0; 
		cheat7 = 0; 
		cheat8 = 0; 
		cheat9 = 0; 
		cheat10 = 0;
		aud1 = 0; 
		aud2 = 0; 
		aud3 = 0; 
		tug = 0; 
		svtug = 0; 
		tuge1 = 0; 
		tuge2 = 0;
		player = 0;
		surv1 = 0; 
		surv2 = 0; 
		surv3 = 0; 
		surv4 = 0; 
		aud4 = 0;
	cam1 = 0; 
	cam2 = 0; 
	cam3 = 0; 
	basecam = 0; 
	reliccam = 0;
	 avrec = 0; 
	 w1u1 = 0; 
	 w1u2 = 0; 
		w2u1 = 0; 
		w2u2 = 0; 
		w2u3 = 0;  
		w3u1 = 0;
		w3u2 = 0; 
		w3u3 = 0; 
		w3u4 = 0; 
		w4u1 = 0; 
		w4u2 = 0; 
		w4u3 = 0;
		w4u4 = 0; 
		w4u5 = 0; 
		w5u1 = 0; 
		w5u2 = 0; 
		w5u3 = 0; 
		w5u4 = 0; 
		w5u5 = 0; 
		w5u6 = 0;
		spawn1 = 0;
		spawn2 = 0;
		spawn3 = 0;
		relic = 0;
		doneaud20 = false;
		doneaud21 = false;
		doneaud22 = false;
		doneaud23 = false;
 calipso = 0; 
 turret1 = 0; 
 turret2 = 0; 
 turret3 = 0; 
 turret4 = 0;
 done = false;
	secureloopbreak = false;
	found = false;
	endmission = false;
	endcinfinish = false;
	loopbreak2 = false;
	ob1 = true;
	ob2 = true;
	ob3 = true;
	ob4 = true;
	ob5 = true;
	ob6 = true;
	ob7 = true;
	ob8 = true;
	investigate = 999999999.0f;
	investigator = 0;
	tur1 = 999999999.0f;
	tur2 = 999999999.0f;
	tur3 = 999999999.0f;
	tur4 = 999999999.0f;
	tur1sent = false;
	tur2sent = false;
	tur3sent = false;
	tur4sent = false;
	cin1done = false;
	missionfail = false;
	chewedout = false;
	newobjective = false;
	relicmoved = false;
	height = 500;
	cintime1 = 9999999999.0f;
	w2u3 = 0;

}

void Misn04Mission::AddObject(Handle h)
{
	if (
		(GetTeamNum(h) == 1) &&
		(IsOdf(h, "avhaul"))
		)
	{
		found = true;
		tug = h;
	}
}

void Misn04Mission::Execute(void)
{
/*
Here is where you 
put what happens 
every frame.  
	*/

	// get this every frame in case the user changes vehicles
	player = GetPlayerHandle();

	if
		(missionstart == false)
	{
		//
		Vector myPos = GetPosition(player);
		Vector hisPos = GetPosition(GetHandle("apcamr351_camerapod"));
		AiPath *thePath = FindAiPath(myPos, hisPos);
		FreeAiPath(thePath);
		//
		wave1 = GetTime( ) + 30.0f;
		fetch = GetTime( ) + 240.0f;//change to 350.0f
		AudioMessage ("misn0401.wav");
		cam1 = GetHandle ("apcamr352_camerapod");
		cam2 = GetHandle ("apcamr350_camerapod");
		cam3 = GetHandle ("apcamr351_camerapod");
		basecam = GetHandle ("apcamr-1_camerapod");
		svrec = GetHandle ("svrecy-1_recycler");
		avrec = GetHandle ("avrecy-1_recycler");
		relic = BuildObject("obdata", 0, "relicstart1");
		pu1 = GetHandle ("svfigh-1_wingman");
		//pu2 = GetHandle ("svfigh281_wingman");
		pu3 = GetHandle ("svfigh282_wingman");
		//pu4 = GetHandle ("svfigh280_wingman");
		//pu5 = GetHandle ("svfigh276_wingman");
		pu6 = GetHandle ("svfigh279_wingman");
		//pu7 = GetHandle ("svfigh277_wingman");
		pu8 = GetHandle ("svfigh278_wingman");
		SetObjectiveName (cam1, "SW Geyser");
		SetObjectiveName (cam2, "NW Geyser");
		SetObjectiveName (cam3, "NE Geyser");
		SetObjectiveName (basecam, "CCA Base");
		Patrol (pu1, "innerpatrol");
		//Patrol (pu2, "innerpatrol");
		Patrol (pu3, "innerpatrol");
		//Patrol (pu4, "innerpatrol");
		//Patrol (pu5, "outerpatrol");
		Patrol (pu6, "outerpatrol");
		//Patrol (pu7, "scouting");
		Patrol (pu8, "scouting");
		AddObjective ("misn0401.otf", WHITE);
		AddObjective ("misn0400.otf", WHITE);
		missionstart = true;
		cheater = false;
		relicstartpos = rand() % 4;
		tur1 = GetTime() + 30.0f;
		tur2 = GetTime() + 45.0f;
		tur3 = GetTime() + 60.0f;
		tur4 = GetTime() + 75.0f;
		investigate = GetTime () + 3.0f;
		}
	player = GetPlayerHandle();
	
	AddHealth(cam1, 1000);
	AddHealth(cam2, 1000);
	AddHealth(cam3, 1000);

	if
		(relicmoved == false)
	{
		switch (relicstartpos)
		{
		case 0:
			SetPosition (relic, "relicstart1");
			break;
		case 1:
			SetPosition (relic, "relicstart2");
			break;
		case 2:
			SetPosition (relic, "relicstart3");
			break;
		case 3:
			SetPosition (relic, "relicstart4");
			break;
		}
		relicmoved = true;
	}

	if
		(
		(reconsent == false) && 
		(cheater == false) &&
		(GetDistance (player, relic) < 600.0f)
		)
	{
			cheat1 = BuildObject ("svfigh",2,relic);
			cheat2 = BuildObject ("svfigh",2,relic);
			cheat3 = BuildObject ("svfigh",2,relic);
			cheat4 = BuildObject ("svfigh",2,relic);
			cheat5 = BuildObject ("svfigh",2,relic);
			cheat6 = BuildObject ("svfigh",2,relic);
			if
				(relicstartpos == 0)
			{
				Patrol(cheat1, "relicpatrolpath1a");
				Patrol(cheat2, "relicpatrolpath1a");
				Patrol(cheat3, "relicpatrolpath1a");
				Patrol(cheat4, "relicpatrolpath1b");
				Patrol(cheat5, "relicpatrolpath1b");
				Patrol(cheat6, "relicpatrolpath1b");
				SetIndependence(cheat1, 1);
				SetIndependence(cheat2, 1);
				SetIndependence(cheat3, 1);
				SetIndependence(cheat4, 1);
				SetIndependence(cheat5, 1);
				SetIndependence(cheat6, 1);
			}
			if
				(relicstartpos == 1)
			{
				Patrol(cheat1, "relicpatrolpath2a");
				Patrol(cheat2, "relicpatrolpath2a");
				Patrol(cheat3, "relicpatrolpath2a");
				Patrol(cheat4, "relicpatrolpath2b");
				Patrol(cheat5, "relicpatrolpath2b");
				Patrol(cheat6, "relicpatrolpath2b");
				SetIndependence(cheat1, 1);
				SetIndependence(cheat2, 1);
				SetIndependence(cheat3, 1);
				SetIndependence(cheat4, 1);
				SetIndependence(cheat5, 1);
				SetIndependence(cheat6, 1);
			}
			if
				(relicstartpos == 2)
			{
				Patrol(cheat1, "relicpatrolpath3a");
				Patrol(cheat2, "relicpatrolpath3a");
				Patrol(cheat3, "relicpatrolpath3a");
				Patrol(cheat4, "relicpatrolpath3b");
				Patrol(cheat5, "relicpatrolpath3b");
				Patrol(cheat6, "relicpatrolpath3b");
				SetIndependence(cheat1, 1);
				SetIndependence(cheat2, 1);
				SetIndependence(cheat3, 1);
				SetIndependence(cheat4, 1);
				SetIndependence(cheat5, 1);
				SetIndependence(cheat6, 1);
			}
			if
				(relicstartpos == 3)
			{
				Patrol(cheat1, "relicpatrolpath4a");
				Patrol(cheat2, "relicpatrolpath4a");
				Patrol(cheat3, "relicpatrolpath4a");
				Patrol(cheat4, "relicpatrolpath4b");
				Patrol(cheat5, "relicpatrolpath4b");
				Patrol(cheat6, "relicpatrolpath4b");
				SetIndependence(cheat1, 1);
				SetIndependence(cheat2, 1);
				SetIndependence(cheat3, 1);
				SetIndependence(cheat4, 1);
				SetIndependence(cheat5, 1);
				SetIndependence(cheat6, 1);
			}
			//cheat7 = BuildObject ("svfigh",2,relic);
			//cheat8 = BuildObject ("svfigh",2,relic);
			//cheat9 = BuildObject ("svfigh",2,relic);
			//cheat10 = BuildObject ("svfigh",2,relic);
			surveysent = true;
			cheater = true;
			reconcca = GetTime();
	}

	
	/*if 
		
		(discoverrelic == false)
	{	
		calipso = GetNearestVehicle (relic);
		GetTeamNum (calipso);
			if
				(
					(GetTeamNum (calipso) == 1) && 
					(GetDistance (relic, calipso) <= 500.0f) &&
					(calipso != player)
				)
					{
						AudioMessage ("misn0407.wav");
						discoverrelic = true;
						newobjective = true;
						reconsent = false;
						SetObjectiveOn (relic);
						SetObjectiveName (relic, "OBJECT");
					}
	}*/

	if
		(
		(fetch < GetTime ()) && (surveysent == false)
		)
	{
		surv1 = BuildObject ("svfigh",2,relic);
		surv2 = BuildObject ("svfigh",2,relic);
		//surv3 = BuildObject ("svfigh",2,relic);
		//surv4 = BuildObject ("svfigh",2,relic);
		if
			(relicstartpos == 0)
		{
			Patrol(surv1, "relicpatrolpath1a");
			Patrol(surv2, "relicpatrolpath1b");
			SetIndependence(surv1, 1);
			SetIndependence(surv2, 1);
		}
		if
			(relicstartpos == 1)
		{
			Patrol(surv1, "relicpatrolpath2a");
			Patrol(surv2, "relicpatrolpath2b");
			SetIndependence(surv1, 1);
			SetIndependence(surv2, 1);
		}
		if
			(relicstartpos == 2)
		{
			Patrol(surv1, "relicpatrolpath3a");
			Patrol(surv2, "relicpatrolpath3b");
			SetIndependence(surv1, 1);
			SetIndependence(surv2, 1);
		}
		if
			(relicstartpos == 3)
		{
			Patrol(surv1, "relicpatrolpath4a");
			Patrol(surv2, "relicpatrolpath4b");
			SetIndependence(surv1, 1);
			SetIndependence(surv2, 1);
		}
		//Goto(surv3, relic);
		//Goto(surv4, relic);
		surveysent = true;
		//newobjective = true;
		reconcca = GetTime () + 60;
	}

	if
		(
		(tur1sent == false) && (tur1 < GetTime()) && (IsAlive(svrec))
		)
	{
		turret1 = BuildObject ("svturr", 2, svrec);
		Goto (turret1, "turret1");
		tur1sent = true;
	}
	if
		(
		(tur2sent == false) && (tur2 < GetTime()) && (IsAlive(svrec))
		)
	{
		turret2 = BuildObject ("svturr", 2, svrec);
		Goto (turret2, "turret2");
		tur2sent = true;
	}
	if
		(
		(tur3sent == false) && (tur3 < GetTime()) && (IsAlive(svrec))
		)
	{
		turret3 = BuildObject ("svturr", 2, svrec);
		Goto (turret3, "turret3");
		tur3sent = true;
	}
	if
		(
		(tur4sent == false) && (tur4 < GetTime()) && (IsAlive(svrec))
		)
	{
		turret4 = BuildObject ("svturr", 2, svrec);
		Goto (turret4, "turret4");
		tur4sent = true;
	}

	if 
		(
		(reconcca < GetTime ()) && (reconsent == false) && (surveysent == true)
		
		
		)
	{
		aud4 = AudioMessage ("misn0406.wav");
		switch (relicstartpos)
		{
		case 0:
			reliccam = BuildObject ("apcamr",1,"reliccam1");
			break;
		case 1:
			reliccam = BuildObject ("apcamr",1,"reliccam2");
			break;
		case 2:
			reliccam = BuildObject ("apcamr",1,"reliccam3");
			break;
		case 3:
			reliccam = BuildObject ("apcamr",1,"reliccam4");
			break;
		}
		
		
		reconsent = true;
		obset = true;
		notfound = GetTime() + 90.0f;
	}

	if
		(
		(obset == true) && (IsAudioMessageDone(aud4)) 
		)
	{
		SetObjectiveName(reliccam, "Investigate CCA");
		newobjective = true;
		obset = false;
	}


	if 
		(
		(found == true) && (halfway == false)
		)
	{
		if
		(HasCargo(tug))
			{
				AudioMessage ("misn0419.wav");
				halfway = true;
				SetObjectiveOff (relic);
				if
					(IsAlive(tuge1))
				{
					Attack(tuge1, tug);
				}
				if
					(IsAlive(tuge2))
				{
					Attack(tuge2, tug);
				}
			}
	}

	if 
		(reconsent == true)
	{
		if
		(
		(GetDistance (relic, avrec) < 100.0f) && (relicsecure == false)
		)

		{
			aud23 = AudioMessage ("misn0420.wav");
			relicsecure = true;
			newobjective = true;
		}
	}

	if 
		(
		(ccatug < GetTime()) && (ccatugsent == false) && (IsAlive(svrec))
		)
	{
		svtug = BuildObject ("svhaul", 2, svrec);
		tuge1 = BuildObject ("svfigh", 2, svrec);
		tuge2 = BuildObject ("svfigh", 2, svrec);
		Pickup (svtug, relic);
		Follow (tuge1, svtug);
		Follow (tuge2, svtug);
		ccatugsent = true;
	}

	if
		(
		(ccatugsent == true) && (ccahasrelic == false)
		)
	{
		if
			
			(IsAlive(svtug))
		{
			if
				(
				(HasCargo(svtug)) && (!HasCargo(tug))
				)
		{
			ccahasrelic = true;
			Goto (svtug, "dropoff");
			AudioMessage ("misn0427.wav");
			SetObjectiveOn(svtug);
			SetObjectiveName(svtug, "CCA Tug");
		}
		}
	}

	
	if
		(
		(ccahasrelic == true) && (GetDistance(svtug, svrec) < 60.0f) &&
		(missionfail2 == false)
		)
	{
		aud10 = AudioMessage("misn0431.wav");
		aud11 = AudioMessage("misn0432.wav");
		aud12 = AudioMessage("misn0433.wav");
		aud13 = AudioMessage("misn0434.wav");
		missionfail2 = true;
		CameraReady();
	}

	if
		(
		(missionfail2 == true) && (done == false)
		)
	{
		CameraPath("ccareliccam", 3000, 1000, svtug);
		if
			(
			(
			(IsAudioMessageDone(aud10)) && 
			(IsAudioMessageDone(aud11)) && 
			(IsAudioMessageDone(aud12)) && 
			(IsAudioMessageDone(aud13))
			) || CameraCancelled()
			)
		{
			CameraFinish();
			StopAudioMessage(aud10);
			StopAudioMessage(aud11);
			StopAudioMessage(aud12);
			StopAudioMessage(aud13);
			FailMission(GetTime(), "misn04l1.des");
			done = true;
		}
	}

	if

		(
		(discoverrelic == false) && (reconsent == true)
		&& (notfound < GetTime()) && (ccahasrelic == false) && (warn < 4)
		)
	{
		AudioMessage ("misn0429.wav");
		notfound = GetTime() + 85.0f;
		warn = warn + 1;
	}

	if
		(
		(warn == 4) && (notfound < GetTime()) && (missionfail == false)
		)
	{
		aud14 = AudioMessage("misn0694.wav");
		missionfail = true;
	}
		if
			(missionfail == true) 
		{
			if
				(
				(warn == 4) &&
				(IsAudioMessageDone(aud14))
				)
			{
				FailMission(GetTime(), "misn04l4.des");
				warn = 0;
			}
		}

	if
		(discoverrelic == false)  
	
	{
		if
			(investigate < GetTime())
		{
			investigator = CountUnitsNearObject(relic, 400.0f, 1, NULL);
			if (IsAlive(reliccam))
			{
				investigator = investigator - 1;
			}
		}

		if 
			(investigator >= 1)
		{
			aud2 = AudioMessage ("misn0408.wav");
			aud3 = AudioMessage ("misn0409.wav");
			relicseen = true;
			newobjective = true;
			ccatug = GetTime()+200.0f;//change to 240.0f
			discoverrelic = true;
			CameraReady();
			cintime1 = GetTime() + 23.0f;
		}
	}

	if
		(
		(discoverrelic == true) && (cin1done == false)
		)
	{
		if
		(
		(
		(discoverrelic == true) && 
		(IsAudioMessageDone(aud2)) &&  (IsAudioMessageDone(aud3))
		) || (CameraCancelled())
		)
		{
		CameraFinish();
		StopAudioMessage(aud2);
		StopAudioMessage(aud3);
		cin1done = true;
		}
	}


	/*if
		(
		(cintime1 < GetTime()) && (cin1done == false)
		)

	{
		CameraFinish();
		cin1done = true;
	}*/

	if
		(
		(discoverrelic == true) && (cintime1 > GetTime()) &&
		(cin1done == false)
		)
	{
		if
			(relicstartpos == 0)
		{
			CameraPath("reliccin1", 500, 400, relic);
		}
		if
			(relicstartpos == 1)
		{
			CameraPath("reliccin2", 500, 400, relic);
		}
		if
			(relicstartpos == 2)
		{
			CameraPath("reliccin3", 500, 400, relic);
		}
		if
			(relicstartpos == 3)
		{
			CameraPath("reliccin4", 500, 400, relic);
		}
	}

	if 
		(newobjective == true)

	{
		ClearObjectives ();
		if
			(basesecure == false)
		{
			AddObjective ("misn0401.otf", WHITE);
		}
		if
			(basesecure == true)
		{
			AddObjective ("misn0401.otf", GREEN);
		}

		if
			(
			(relicsecure == false) && (relicseen == true)
			)
		{
			AddObjective ("misn0403.otf", WHITE);
		}
		if
			(relicsecure == true)
		{
			AddObjective ("misn0403.otf", GREEN);
		}
		if
			(
			(reconsent == true) && (discoverrelic == false)
			)
		{
			AddObjective ("misn0405.otf", WHITE);
		}
		if
			(
			(discoverrelic == true)
			)
		{
			AddObjective ("misn0405.otf", GREEN);
		}
		/*if
			(
			(discoverrelic == true) && (relicseen == false)
			)
		{
			AddObjective ("misn0402.otf", WHITE);
		}
		if
			(relicseen == true)
		{
			AddObjective ("misn0402.otf", GREEN);
		}*/
		
		newobjective = false;
	}
	if
		(wavenumber == 1)
	{
		IsAlive(w1u1);
		IsAlive(w1u2);
	}

	if
		(
		(wavenumber == 1) && (GetTime( ) > wave1)
		)
	{
		w1u1 = BuildObject ("svfigh",2,"wave1");
		w1u2 = BuildObject ("svfigh",2,"wave1");
		Attack (w1u1, avrec,1);
		Attack (w1u2, avrec,1);
		SetIndependence (w1u1, 1);
		SetIndependence (w1u2, 1);

		wavenumber = 2;
		wave1arrive = false;
	}

	if
		(wavenumber == 2)
	{
		IsAlive(w1u1);
		IsAlive(w1u2);
	}
	
	if
		(
		(wavenumber == 2) && 
		(!IsAlive (w1u1)) &&
		(!IsAlive (w1u2)) &&
		(build2 == false)  
		)

	
			{
				wave2 = GetTime ( ) + 60.0f;
				build2 = true;
				wave1dead = true;
			}
			
	if 
		(
		(wave2 < GetTime ( )) && (IsAlive(svrec))
		)
	{
		w2u1 = BuildObject ("svtank",2,"spawn2new");
		w2u2 = BuildObject ("svfigh",2,"spawn2new");
		//w2u3 = BuildObject ("svtank",2,"spawn2new");
		Goto(w2u1, avrec,1);
		Goto(w2u2, avrec,1);
		//Goto(w2u3, avrec,1);
		SetIndependence (w2u1, 1);
		SetIndependence (w2u2, 1);
		//SetIndependence (w2u3, 1);
		wavenumber = 3;
		wave2arrive = false;
		wave2 = 99999.0f;
	}
	if
	(wavenumber == 3)
	{
		IsAlive(w2u1);
		IsAlive(w2u2);
	}
	
	if
		(
		(wavenumber == 3) && 
		(!IsAlive (w2u1)) &&
		(!IsAlive (w2u2)) &&
		//(!IsAlive (w2u3)) &&
		(build3 == false)    
		)
			{
				wave3 = GetTime ( ) + 74.0f;
				build3 = true;
				wave2dead = true;
			}
	if
		(
		(wave3 < GetTime ( )) && (IsAlive(svrec))
		)
	{
		
		w3u1 = BuildObject ("svfigh",2,svrec);
		w3u2 = BuildObject ("svfigh",2,svrec);
		w3u3 = BuildObject ("svfigh",2,svrec);
		//w3u4 = BuildObject ("svfigh",2,svrec);
		Goto(w3u1, avrec,1);
		Goto(w3u2, avrec,1);
		Goto(w3u3, avrec,1);
		//Goto(w3u4, avrec,1);
		SetIndependence (w3u1, 1);
		SetIndependence (w3u2, 1);
		SetIndependence (w3u3, 1);
		//SetIndependence (w3u4, 1);
		wavenumber = 4;
		wave3arrive = false;
		wave3 = 99999.0f;
	}

	if
		(wavenumber == 4)
	{
		IsAlive(w3u1);
		IsAlive(w3u2);
		IsAlive(w3u3);
	}
	
	if
		(
		(wavenumber == 4) && 
		(!IsAlive (w3u1)) &&
		(!IsAlive (w3u2)) &&
		(!IsAlive (w3u3)) &&
		//(!IsAlive (w3u4)) &&
		(build4 == false)
		)
	{
		wave4 = GetTime ( ) + 60.0f;
		build4 = true;
		wave3dead = true;
	}
	if
		(
		(wave4 < GetTime ( )) && (IsAlive(svrec))
		)
	{
		
		w4u1 = BuildObject ("svtank",2,"spawnotherside");
		w4u2 = BuildObject ("svfigh",2,"spawnotherside");
		w4u3 = BuildObject ("svfigh",2,"spawnotherside");
		//w4u4 = BuildObject ("svfigh",2,"spawnotherside");
		//w4u5 = BuildObject ("svtank",2,"spawnotherside");
		Goto(w4u1, avrec,1);
		Goto(w4u2, avrec,1);
		Goto(w4u3, avrec,1);
		//Goto(w4u4, avrec,1);
		//Goto(w4u5, avrec,1);
		SetIndependence (w4u1, 1);
		SetIndependence (w4u2, 1);
		SetIndependence (w4u3, 1);
		//SetIndependence (w4u4, 1);
		//SetIndependence (w4u5, 1);
		wavenumber = 5;
		wave4arrive = false;
		wave4 = 99999.0f;
	}

	if
		(wavenumber == 5)
	{
		IsAlive(w4u1);
		IsAlive(w4u2);
		IsAlive(w4u3);
	}

	
	if
		(
		(wavenumber == 5) && 
		(!IsAlive (w4u1)) &&
		(!IsAlive (w4u2)) &&
		(!IsAlive (w4u3)) &&
		//(!IsAlive (w4u4)) &&
		//(!IsAlive (w4u5)) &&
		(build5 == false)
		)
	{
		wave5 = GetTime ( ) + 30.0f;
		build5 = true;
		wave4dead = true;
	}

	if
		(
		(wave5 < GetTime ( )) && (IsAlive(svrec))
		)
	{
		
		w5u1 = BuildObject ("svtank",2,svrec);
		w5u2 = BuildObject ("svfigh",2,svrec);
		w5u3 = BuildObject ("svfigh",2,svrec);
		w5u4 = BuildObject ("svfigh",2,svrec);
		//w5u5 = BuildObject ("svtank",2,svrec);
		//w5u6 = BuildObject ("svfigh",2,svrec);
		Goto(w5u1, avrec,1);
		Goto(w5u2, avrec,1);
		Goto(w5u3, avrec,1);
		Goto(w5u4, avrec,1);
		//Goto(w5u5, avrec,1);
		//Goto(w5u6, avrec,1);
		SetIndependence (w5u1, 1);
		SetIndependence (w5u2, 1);
		SetIndependence (w5u3, 1);
		SetIndependence (w5u4, 1);
		//SetIndependence (w5u5, 1);
		//SetIndependence (w5u6, 1);
		wavenumber = 6;
		wave5arrive = false;
		wave5 = 99999.0f;
	}
	
	
	if
		(
		(wave1arrive == false) && (IsAlive (avrec))
		)
	{
		
		
		if 
			
			(
			(GetDistance (avrec, w1u1)< 300.0f) ||
			(GetDistance (avrec, w1u2)< 300.0f)
			)
			
			
			
		{
			AudioMessage ("misn0402.wav");
			wave1arrive = true;
			wave1dead = true;
		}
	}
	
	if
		(
		(wave2arrive == false) && (IsAlive (avrec))
		)
	{
		if
			
			(
			(GetDistance (avrec, w2u1) < 300.0f) ||
			(GetDistance (avrec, w2u2) < 300.0f) 
//			|| (GetDistance (avrec, w2u3) < 300.0f)
			)
			
			
		{
			AudioMessage ("misn0404.wav");
			wave2arrive = true;
		}
	}
	if
		(
		(wave3arrive == false) && (IsAlive (avrec))
		)
	{
		if
			
			(
			(GetDistance (avrec, w3u1)< 300.0f) ||
			(GetDistance (avrec, w3u2)< 300.0f) ||
			(GetDistance (avrec, w3u3)< 300.0f) 
//			|| (GetDistance (avrec, w3u4)< 300.0f)
			)
			
			
		{
			AudioMessage ("misn0410.wav");
			wave3arrive = true;
		}
	}
	if
		(
		(wave4arrive == false) && (IsAlive (avrec))
		)
	{
		if
			
			(
			(GetDistance (avrec, w4u1)< 300.0f) || 
			(GetDistance (avrec, w4u2)< 300.0f) ||
			(GetDistance (avrec, w4u3)< 300.0f) //||
			//(GetDistance (avrec, w4u4)< 300.0f) 
//			|| (GetDistance (avrec, w4u5)< 300.0f)
			)
			
			
		{
			AudioMessage ("misn0412.wav");
			wave4arrive = true;
		}
	}
	if
		(
		(wave5arrive == false) && (IsAlive (avrec))
		)
	{
		if
			
			(
			(GetDistance (avrec, w5u1)< 300.0f) ||
			(GetDistance (avrec, w5u2)< 300.0f) ||
			(GetDistance (avrec, w5u3)< 300.0f) ||
			(GetDistance (avrec, w5u4)< 300.0f) //||
			//(GetDistance (avrec, w5u5)< 300.0f) ||
			//(GetDistance (avrec, w5u6)< 300.0f)
			)
			
			
		{
			AudioMessage ("misn0414.wav");
			wave5arrive = true;
		}
	}
	
	if (
		(attackccabase == false) &&
		(GetDistance (player, svrec) < 300.0f) )
	{
		AudioMessage ("misn0423.wav");
		attackccabase = true;
	}
	
	if
		(
		(wave1dead == true) &&
		(!IsAlive (w1u1)) &&
		(!IsAlive (w1u2))
		 
		)
	{
		AudioMessage ("misn0403.wav");
		wave1dead = false;
	}
	
	if
		(wave2dead == true)
	{
		AudioMessage ("misn0405.wav");
		wave2dead = false;
	}
	if
		(wave3dead == true)
	{
		AudioMessage ("misn0411.wav");
		wave3dead = false;
	}
	if
		(wave4dead == true)
	{
		AudioMessage ("misn0413.wav");
		wave4dead = false;
	}
	
	
	if
		(
		(loopbreak == false) &&
		(possiblewin == false) && 
		(missionwon == false) && 
		(!IsAlive (svrec))
		)
	{
		AudioMessage ("misn0417.wav");
		possiblewin = true;
		chewedout = true;
		if 
		(

		(!IsAlive (svrec)) &&
		(
		(IsAlive (w1u1)) ||
		(IsAlive (w1u2)) ||
		(IsAlive (w2u1)) ||
		(IsAlive (w2u2)) ||
//		(IsAlive (w2u3)) ||
		(IsAlive (w3u1)) ||
		(IsAlive (w3u2)) ||
		(IsAlive (w3u3)) ||
//		(IsAlive (w3u4)) ||
		(IsAlive (w4u1)) ||
		(IsAlive (w4u2)) ||
		(IsAlive (w4u3)) ||
		//(IsAlive (w4u4)) ||
//		(IsAlive (w4u5)) ||
		(IsAlive (w5u1)) ||
		(IsAlive (w5u2)) ||
		(IsAlive (w5u3)) ||
		(IsAlive (w5u4)) //||
		//(IsAlive (w5u5)) ||
		//(IsAlive (w5u6))
		)
		)
		{
			AudioMessage ("misn0418.wav");
		//	possiblewin = false;
			loopbreak = true;
		}
	}
	if
		(
		(basesecure == false) &&
		(!IsAlive (svrec)) &&
		(!IsAlive (w1u1)) &&
		(!IsAlive (w1u2)) &&
		(!IsAlive (w2u1)) &&
		(!IsAlive (w2u2)) &&
//		(!IsAlive (w2u3)) &&
		(!IsAlive (w3u1)) &&
		(!IsAlive (w3u2)) &&
		(!IsAlive (w3u3)) &&
//		(!IsAlive (w3u4)) &&
		(!IsAlive (w4u1)) &&
		(!IsAlive (w4u2)) &&
		(!IsAlive (w4u3)) &&
		//(!IsAlive (w4u4)) &&
//		(!IsAlive (w4u5)) &&
		(!IsAlive (w5u1)) &&
		(!IsAlive (w5u2)) &&
		(!IsAlive (w5u3)) &&
		(!IsAlive (w5u4)) //&&
		//(!IsAlive (w5u5)) &&
		//(!IsAlive (w5u6))
		
		)
		
	{
		basesecure = true;
		newobjective = true;
	}
	
	if
		(
		(relicsecure == true) && (basesecure == true)
		)

	{
		missionwon = true;
	}

	if 
		(
		(missionwon == true) && (endmission == false)
		)
	{
		if
			(
			/*(doneaud20 == true) && 
			(doneaud21 == true) &&
			(doneaud22 == true) &&
			(doneaud23 == true)*/ 
			(IsAudioMessageDone(aud20)) &&
			(IsAudioMessageDone(aud21)) &&
			(IsAudioMessageDone(aud22)) &&
			(IsAudioMessageDone(aud23)) 
			)
		{	
		SucceedMission (GetTime(), "misn04w1.des"); 
		}
	}

	/*if
		(
		(doneaud20 == false) && (IsAudioMessageDone(aud20))
		)
	{
		doneaud20 = true;
	}

	if
		(
		(doneaud21 == false) && (IsAudioMessageDone(aud21))
		)
	{
		doneaud21 = true;
	}

	if
		(
		(doneaud22 == false) && (IsAudioMessageDone(aud22))
		)
	{
		doneaud22 = true;
	}

	if
		(
		(doneaud23 == false) && (IsAudioMessageDone(aud23))
		)
	{
		doneaud23 = true;
	}*/


	if
		(
		(missionwon == false) && 
		(!IsAlive (avrec)) &&
		(missionfail == false)
		)
	{
		AudioMessage ("misn0421.wav");
		AudioMessage ("misn0422.wav");
		missionfail = true;
		FailMission (GetTime( ) + 20.0f, "misn04l3.des");
	}
	if
		((basesecure == false) &&
		(secureloopbreak == false) &&
		(wavenumber == 6) 
		&& (!IsAlive (w5u1)) 
		&& (!IsAlive (w5u2)) 
		&& (!IsAlive (w5u3))
		&& (!IsAlive (w5u4))
		//&& (!IsAlive (w5u5))
		//&& (!IsAlive (w5u6))
		&& (IsAlive (svrec))
		
		)
	{
		if
			(retreat == false)
		{
			if
				(IsAlive(tuge1))
			{
			Retreat(tuge1, "retreatpoint");
			}
			if
				(IsAlive(tuge2))
			{
			Retreat(tuge2, "retreatpoint28");
			}
			if
				(IsAlive(pu1))
			{
			Retreat(pu1, "retreatpoint27");
			}
			if
				(IsAlive(pu2))
			{
			Retreat(pu2, "retreatpoint26");
			}
			if
				(IsAlive(pu3))
			{
			Retreat(pu3, "retreatpoint25");
			}
			if
				(IsAlive(pu4))
			{
			Retreat(pu4, "retreatpoint24");
			}
			if
				(IsAlive(pu5))
			{
			Retreat(pu5, "retreatpoint23");
			}
			if
				(IsAlive(pu6))
			{
			Retreat(pu6, "retreatpoint22");
			}
			if
				(IsAlive(pu7))
			{
			Retreat(pu7, "retreatpoint21");
			}
			if
				(IsAlive(pu8))
			{
			Retreat(pu8, "retreatpoint20");
			}
			if
				(IsAlive(cheat1))
			{
			Retreat(cheat1, "retreatpoint19");
			}
			if
				(IsAlive(cheat2))
			{
			Retreat(cheat2, "retreatpoint18");
			}
			if
				(IsAlive(cheat3))
			{
			Retreat(cheat3, "retreatpoint17");
			}
			if
				(IsAlive(cheat4))
			{
			Retreat(cheat4, "retreatpoint16");
			}
			if
				(IsAlive(cheat5))
			{
			Retreat(cheat5, "retreatpoint15");
			}
			if
				(IsAlive(cheat6))
			{
			Retreat(cheat6, "retreatpoint14");
			}
			if
				(IsAlive(cheat7))
			{
			Retreat(cheat7, "retreatpoint13");
			}
			if
				(IsAlive(cheat8))
			{
			Retreat(cheat8, "retreatpoint12");
			}
			if
				(IsAlive(cheat9))
			{
			Retreat(cheat9, "retreatpoint11");
			}
			if
				(IsAlive(cheat10))
			{
			Retreat(cheat10, "retreatpoint10");
			}
			if
				(IsAlive(surv1))
			{
			Retreat(surv1, "retreatpoint9");
			}
			if
				(IsAlive(surv2))
			{
			Retreat(surv2, "retreatpoint8");
			}
			if
				(IsAlive(surv3))
			{
			Retreat(surv3, "retreatpoint7");
			}
			if
				(IsAlive(surv4))
			{
			Retreat(surv4, "retreatpoint6");
			}
			if
				(IsAlive(turret1))
			{
			Retreat(turret1, "retreatpoint2");
			}
			if
				(IsAlive(turret2))
			{
			Retreat(turret2, "retreatpoint3");
			}
			if
				(IsAlive(turret3))
			{
			Retreat(turret3, "retreatpoint4");
			}
			if
				(IsAlive(turret4))
			{
			Retreat(turret4, "retreatpoint5");
			}
			retreat = true;
		}

		/*safety = GetNearestEnemy(player);
		if
			(GetDistance(safety, player) > 400.0f)
		{*/
		aud21 = AudioMessage ("misn0415.wav");
		aud22 = AudioMessage ("misn0416.wav");
		basesecure = true;
		newobjective = true;
		secureloopbreak = true;
		//}

	}

	if
		(
		(!IsAlive(relic)) && (missionfail == false)
		)
	{
		FailMission(GetTime() + 20.0f, "misn04l2.des");
		AudioMessage("misn0431.wav");
		AudioMessage("misn0432.wav");
		AudioMessage("misn0433.wav");
		AudioMessage("misn0434.wav");
		missionfail = true;
	}

	if
		(wavenumber == 6)
	{
		IsAlive(w5u1);
		IsAlive(w5u2);
		IsAlive(w5u3);
		IsAlive(w5u4);
	}

	if
		((basesecure == false) &&
		(secureloopbreak == false) &&
		(wavenumber == 6) 
		&& (!IsAlive (w5u1)) 
		&& (!IsAlive (w5u2)) 
		&& (!IsAlive (w5u3))
		&& (!IsAlive (w5u4))
		//&& (!IsAlive (w5u5))
		//&& (!IsAlive (w5u6))
		&& (!IsAlive (svrec))
		&& (chewedout == true)
		)

	{
		aud20 = AudioMessage ("misn0425.wav");
		basesecure = true;
		newobjective = true;
		secureloopbreak = true;
	}
	
	
	
}
