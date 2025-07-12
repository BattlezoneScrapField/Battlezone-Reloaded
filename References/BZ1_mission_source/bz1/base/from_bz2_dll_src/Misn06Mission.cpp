#include "ScriptUtils.h"

#include <crtdbg.h>
#include <stdlib.h>

/*
	Misn06Mission Event
*/

class Misn06Mission {
public:
	Misn06Mission(void);
	~Misn06Mission();

	bool Load(void);
	bool PostLoad(void);
	bool Save(void);

	void Update(void);

	void Setup(void);
	void AddObject(Handle h);
	void Execute(void);

	// bools
	union {
		struct {
			bool
				missionstart,starportdisc,star1recon,star2recon,star3recon, star,
				star4recon,star5recon,star6recon,star7recon,star8recon,star9recon,
				star10recon,star11recon,missionfail,starportreconed,surveystarport,
				relicmissing,haephestusdisc,blockadefound,ccabasedisc,relicgone, missionfail1,
				missionwon,newobjective,reconheaphestus,recoverrelic,neworders, safebreak,
				ccaattack,hidob2,buildcam,ccapullout,transarrive,touchdown, lprecon,
				fifteenmin,economyccaplatoon,tenmin,threemin,fivemin,twomin,platoonhere,
				corbettalive,lincolndes,loopbreak1,opencamdone,cam1done,cam3done,
				patrol1set,patrol2set,patrol3set,startpat1,startpat2,startpat3,startpat4,
				wave1start,wave2start,wave3start,launchpadreconed,patrol1spawned, breakme,
				patrol2spawned,patrol3spawned,transgone,bugout,pickupset,pickupreached,
				hephikey,reminder,dustoff, fail3, trigger1,ob1,ob2,ob3,ob4,timergone,timerset, respawn,
				simcam, removal, breakout1, attack, breaker, death, fifthplatoon, breaker19, bustout,
				doneaud1,doneaud2,endme,doneaud3,missionfail3,missionfail4,doneaud4,doneaud5, loopbreaker,  // doneauds created by GEC for cineractive control
				b_last;
		};
		bool b_array[98];
	};

	// floats
	union {
		struct {
			float
				transportgone, searchtime, processtime, transportarrive,
				oneminstrans, transaway, platoonarrive, fifteenminsplatoon, tenminsplatoon, 
				threeminsplatoon, fiveminsplatoon, check1, time1,
				twominsplatoon, opencamtime, cam1time, cam3time, wave1, wave2, wave3,
				lincolndestroyed, patrol1time, patrol2time, patrol3time, deathtime,
				hephdisctime, identtime, discstar, removetimer, timerstart, start1, spfail,
				reconsptime, end,
				f_last;
		};
		float f_array[34];
	};

	// handles
	union {
		struct {
			Handle
				haephestus, sim1, sim2, sim3, sim4, sim5, sim6, sim7, sim8, sim9, sim10,
				simaud1, simaud2, simaud3, simaud4, simaud5, heph1, heph2,
				enemy, aud500,//handle for haephestus 
				relic,
				spawnme,
				starport, //handle for starport that triggers starportdisc bool
				player, //duh! 
				nav1, 
				rendezvous,  //handle for cam where 5th platoon is supposed to be 
				blockade1, //handle of soviet turret in scrap field
				avrec,//duh again!
				svrec,//yet another duh
				launchpad,//where player nust go to get information on where database was taken 
				starportcam,// handle of navbeacon at starport 
				dustoffcam,//handle of camera where player must go to finish mission 
				art1,
				//these handles are for the waves that attack the player
				w1u1, w1u2, w1u3, aud1, aud2, aud3, aud4, aud5, aud6, aud7, aud8, aud9, 
				w2u1, w2u2, w2u3, 
				w3u1, w3u2, w3u3, 
				wAu1, wAu2, wAu3, p5u1,
				turret, trigger,
				//these are the handles of the starport buildings the player recons
				star1, star2, star3, star4, star5, star6, star7, 
				star8, star9, star10, star11,
				//these are the handles of the fifth platoon used in the opening cineractive
				p5u2, p5u3, p5u4, p5u5, p5u6, p5u7, p5u8, 
				p5u9, p5u10, p5u11, p5u12,
				aud20, aud21,
				//these are the handles for the units that patrol the canyons
				pu1p1, pu2p1, pu3p1, pu4p1,
				pu1p2, pu2p2, pu3p2, pu4p2,
				pu1p3, pu2p3, pu3p3, pu4p3,
				pu1p4, pu2p4, pu3p4, aud15, aud16, aud54,
				svu1, svu2, svu3, svu4, bogey,
				//these are the handles for the cca platoon created at the end of the mission
				ccap1, ccap2, ccap3, ccap4, ccap5, ccap6, ccap7, ccap8,
				ccap9, ccap10, ccap11, ccap12, ccap13, ccap14, ccap15,
				h_last;
		};
		Handle h_array[119];
	};

	// integers
	union {
		struct {
			int
				cam1hgt, patrol1start, patrol2start, patrol3start, extractpoint,
				hephwarn, ident, stardisc, aud100, aud101, aud102, aud103, aud104, aud105,
				audmsg,
				i_last;
		};
		int i_array[15];
	};
};

bool missionSave;
Misn06Mission *mission;

void Misn06Mission::Setup(void)
{
	/*
	Here's where you
	set the values
	at the start.  
	*/
	p5u1=NULL;
	stardisc = 0;
	discstar = 99999999999.0f;
	ident = 0;
	missionstart = true;
	respawn = false;
	lprecon = false;
		starportdisc = false;
		star1recon = false;
		star2recon = false;
		star3recon = false;
		star4recon = false;
		star5recon = false;
		star6recon = false;
		star7recon = false;
		star8recon = false;
		star9recon = false;
		star10recon = false;
		star11recon = false;
		relicmissing = false;
		haephestusdisc = false;
		breakme = false;
		svu1 = 0;
		svu2 = 0;
		svu3 = 0;
		svu4 = 0;
		end = 999999999999.0f;
		timergone = false;
		economyccaplatoon = false;
		blockadefound = false;
		ccabasedisc = false;
		ccaattack = false;
		relicgone = false;
		missionwon = false;
		newobjective = false;
		reconheaphestus = false;
		recoverrelic = false;
		starportreconed = false;
		surveystarport = false;
		neworders = false;
		hidob2 = false;
		buildcam = false;
		ccapullout = false;
		transarrive = false;
		hephikey = false;
		touchdown = false;
		fifteenmin = false;
		tenmin = false;
		threemin = false;
		twomin = false;
		platoonhere = false;
		corbettalive = true;
		loopbreak1 = false;
		opencamdone = false;
		cam1done = false;
		cam3done = false;
		patrol1spawned = false;
		patrol2spawned = false;
		patrol3spawned = false;
		patrol3set = false;
		patrol2set = false;
		patrol1set = false;
		safebreak = false;
		startpat1 = false;
		startpat2 = false;
		startpat3 = false;
		startpat4 = false;
		wave1start = false;
		wave2start = false;
		wave3start = false;
		reminder = false;
		transgone = false;
		loopbreaker = false;
		breaker = false;
		dustoff = false;
		lincolndes = false;
		trigger1 = false;
		missionfail = false;
		launchpadreconed = false;
		attack = false;
		breakout1 = false;
		removal = false;
		simcam = false;
		bugout = false;
		bustout = false;
		bogey = 0;
		ob1 = false;
		ob2 = false;
		ob3 = false;
		ob4 = false;
		doneaud1=false;
		doneaud2=false;
		doneaud3=false;
		doneaud4=false;
		doneaud5=false;
		star = false;
		fifthplatoon = true;
		haephestus = 0;
		missionfail1 = false;
		aud20 = 0;
		aud21 = 0;
		sim1 = 0; 
		sim2 = 0; 
		sim3 = 0; 
		sim4 = 0; 
		sim5 = 0; 
		sim6 = 0; 
		sim7 = 0; 
		sim8 = 0; 
		sim9 = 0; 
		sim10 = 0;
		simaud1 = 0; 
		simaud2 = 0; 
		simaud3 = 0;
		simaud4 = 0;
		simaud5 = 0;
		heph1 = 0; 
		heph2 = 0;
		enemy = 0;
		relic = 0;
		spawnme = 0;
		starport = 0; 
		player = 0; 
		nav1 = 0; 
		rendezvous = 0; 
		blockade1 = 0;
		avrec = 0;
		svrec = 0;
		launchpad = 0;
		starportcam = 0;
		dustoffcam = 0;
		art1 = 0;
		w1u1 = 0;
		w1u2 = 0; 
		w1u3 = 0; 
		aud1 = 0; 
		aud2 = 0;
		aud3 = 0;
		aud4 = 0;
		aud5 = 0; 
		aud6 = 0;
		aud7 = 0; 
		aud8 = 0; 
		aud9 = 0; 
		w2u1 = 0;
		w2u2 = 0;
		w2u3 = 0; 
		w3u1 = 0; 
		w3u2 = 0;
		w3u3 = 0; 
		wAu1 = 0; 
		wAu2 = 0; 
		wAu3 = 0; 
		p5u1 = 0;
		aud500 = 0;
		star1 = 0;
		star2 = 0;
		star3 = 0;
		star4 = 0;
		star5 = 0;
		star6 = 0; 
		star7 = 0; 
		star8 = 0;
		star9 = 0;
		star10 = 0;
		star11 = 0;
		p5u2 = 0; 
		p5u3 = 0; 
		p5u4 = 0; 
		p5u5 = 0; 
		p5u6 = 0; 
		p5u7 = 0; 
		p5u8 = 0; 
		p5u9 = 0; 
		p5u10 = 0; 
		p5u11 = 0; 
		p5u12 = 0;
		pu1p1 = 0; 
		pu2p1 = 0; 
		pu3p1 = 0; 
		pu4p1 = 0;
		pu1p2 = 0; 
		pu2p2 = 0; 
		pu3p2 = 0; 
		pu4p2 = 0;
		pu1p3 = 0;
		pu2p3 = 0;
		pu3p3 = 0;
		pu4p3 = 0;
		pu1p4 = 0;
		pu2p4 = 0;
		pu3p4 = 0;
		ccap1 = 0; 
		ccap2 = 0;
		ccap3 = 0;
		ccap4 = 0;
		ccap5 = 0; 
		ccap6 = 0; 
		ccap7 = 0; 
		ccap8 = 0;
		ccap9 = 0; 
		ccap10 = 0;
		ccap11 = 0;
		ccap12 = 0; 
		ccap13 = 0; 
		ccap14 = 0; 
		ccap15 = 0;
		aud54 = 0;
		fail3 = false;
		reconsptime = 9999999999999999.0f;
		spfail = 0;
		removetimer = 99999999.0f;
		processtime = 999999.0f;
		searchtime = 999999.0f;
		transportarrive = 99999.0f;
		oneminstrans = 999999.0f;
		transaway = 999999.0f;
		turret = 0;
		trigger = 0;
		missionfail3 = false;
		missionfail4 = false;
		endme = false;
		aud100 = 0;
		aud101 = 0;
		aud102 = 0;
		aud103 = 0;
		aud104 = 0;
		aud105 = 0;
		platoonarrive = 999999.0f;
		fifteenminsplatoon = 999999.0f;
		tenminsplatoon = 999999.0f;
		threeminsplatoon = 999999.0f;
		twominsplatoon = 999999.0f;
		fiveminsplatoon = 999999.0f;
		opencamtime = 999999.0f;
		cam1time = 999999.0f;
		cam3time = 999999.0f;
		cam1hgt = 800;
		starportcam = 0;
		breaker19 = false;
		wave1 = 999999.0f;
		wave2 = 999999.0f;
		wave3 = 999999.0f;
		start1 = 999999999.0f;
		lincolndestroyed = 999999.0f;
		patrol1start = rand() % 4;
		patrol2start = rand() % 4;
		patrol3start = rand() % 4;
		extractpoint = rand() % 4;
		patrol1time = 99999999.0f;
		patrol2time = 99999999.0f;
		patrol3time = 99999999.0f;
		check1 = 99999999.0f;
		time1 = 999999999.0f;
		hephdisctime = 9999999999.0f;
		identtime = 999999999.0f;
		timerstart = 999999999.0f;
		deathtime = 999999999999.0f;
		death = false;
		timerset = false;
		audmsg = 0;
		hephwarn = 0;

	
}

void Misn06Mission::AddObject(Handle h)
{
}

void Misn06Mission::Execute(void)
{
	/*
		Here is where you 
		put what happens 
		every frame.  
	*/

	if 
		(missionstart == true)

	{
		audmsg = AudioMessage("misn0601.wav");
		missionstart = false;
		player = GetPlayerHandle();
		rendezvous = GetHandle ("eggeizr1-1_geyser");
		SetObjectiveName (rendezvous, "5th Platoon");
		haephestus = GetHandle ("obheph0_i76building");
		avrec = GetHandle ("avrecy-1_recycler");
		svrec = GetHandle ("svrecy-1_recycler");
		launchpad = GetHandle ("sblpad0_i76building");
		wAu1 = GetHandle ("svfigh568_wingman");
		wAu2 = GetHandle ("svfigh566_wingman");
		turret = GetHandle("turret");
		//wAu3 = GetHandle ("svfigh567_wingman");
		//star1 = GetHandle ("obstp34_i76building");
		star2 = GetHandle ("obstp25_i76building");
		//star4 = GetHandle ("obstp11_i76building");
		//star5 = GetHandle ("obstp21_i76building");
		star6 = GetHandle ("obstp10_i76building");
		//star7 = GetHandle ("obstp23_i76building");
		star8 = GetHandle ("obstp33_i76building");
		//star9 = GetHandle ("obstp35_i76building");
		blockade1 = GetHandle ("svturr649_turrettank");
		svu1 = GetHandle ("svu1");
		svu2 = GetHandle ("svu2");
		svu3 = GetHandle ("svu3");
		svu4 = GetHandle ("svu4");
		p5u3 = GetHandle ("avtank13_wingman");
		p5u4 = GetHandle ("avtank11_wingman");
		p5u6 = GetHandle ("avtank12_wingman");
		p5u9 = GetHandle ("avfigh7_wingman");
		p5u12 = GetHandle ("avfigh10_wingman");
		patrol1time = GetTime() + 30.0f;
		patrol2time = GetTime() + 30.0f;
		patrol3time = GetTime() + 30.0f;
		SetObjectiveOn(rendezvous);
		AddObjective("misn0600.otf", WHITE);
		CameraReady();
		opencamtime = GetTime() + 28.0f;
		opencamdone = true;
		newobjective = true;
		SetScrap(1,5);
		art1 = GetHandle ("svartl648_howitzer");
		Defend (art1, 1);
		check1 = GetTime() + 20.0f;
	


	}
	player = GetPlayerHandle();
	AddHealth(star2, 1000);
	AddHealth(star6, 1000);
	AddHealth(star8, 1000);

	if
		(trigger1 == false)
	{
		trigger = GetNearestEnemy(turret);
		if
			(
			(GetDistance(trigger, turret) < 200.0f) || (!IsAlive(turret))
			)
		{
	if
		(patrol1set == false)
	{
		switch (patrol1start)
		{
		case 0:
			pu1p1 = BuildObject ("svfigh",2, "pat1sp1");
			break;
		case 1:
			pu1p1 = BuildObject ("svfigh",2, "pat1sp2");
			break;
		case 2:
			pu1p1 = BuildObject ("svtank",2, "pat1sp3");
			break;
		case 3:
			pu1p1 = BuildObject ("svfigh",2, "pat1sp4");
		}
		patrol1set = true;
	}

	if
		(patrol2set == false)
	{
		switch (patrol2start)
		{
		case 0:
			pu1p2 = BuildObject ("svfigh",2, "pat2sp1");
			break;
		case 1:
			pu1p2 = BuildObject ("svfigh",2, "pat2sp2");
			break;
		case 2:
			pu1p2 = BuildObject ("svtank",2, "pat2sp3");
			break;
		case 3:
			pu1p2 = BuildObject ("svfigh",2, "pat2sp4");
		}
		patrol2set = true;
	}

	if
		(patrol3set == false)
	{
		switch (patrol3start)
		{
		case 0:
			pu1p3 = BuildObject ("svfigh",2, "pat3sp1");
			break;
		case 1:
			pu1p3 = BuildObject ("svfigh",2, "pat3sp2");
			break;
		case 2:
			pu1p3 = BuildObject ("svtank",2, "pat3sp3");
			break;
		case 3:
			pu1p3 = BuildObject ("svfigh",2, "pat3sp4");
		}
		patrol3set = true;
	}
	
	if 
		(
		(patrol1set == true) && (startpat1 == false)
		)
	{
		Patrol (pu1p1, "patrol1");
		startpat1 = true;
	}

	if
		(
		(patrol2set == true) && (startpat2 == false)
		)
	{
		Patrol (pu1p2, "patrol2");

		startpat2 = true;
	}

	if
		(
		(patrol3set == true) && (startpat3 == false)
		)
	{
		Patrol (pu1p3, "patrol3");
		startpat3 = true;
	}

	if
		(startpat4 == false)
	{
		Patrol (pu1p4, "patrol4");
		Patrol (pu2p4, "patrol4");
		Patrol (pu3p4, "patrol4");
		startpat4 = true;
	}
	trigger1 = true;
			}
		}

	if
		(trigger1 == true)
	{
		if
			(
			(patrol1time < GetTime()) && (patrol1spawned == false)
			)
		{
			patrol1time = GetTime () + 2.0f;

			if ((IsAlive(pu1p1)) &&
				(GetNearestEnemy (pu1p1) < 450.0f))
			{
				pu2p1 = BuildObject ("svtank",2, pu1p1);
				//pu3p1 = BuildObject ("svtank",2, pu1p1);
				//pu4p1 = BuildObject ("svtank",2, pu1p1);
				patrol1spawned = true;
				Patrol(pu2p1, "patrol1");
				//Patrol(pu3p1, "patrol1");
				//Patrol(pu4p1, "patrol1");
			}
		}

		if
			(
			(patrol2time < GetTime()) && (patrol2spawned == false)
			)
		{
			patrol2time = GetTime () + 2.0f;

			if ((IsAlive(pu1p2)) &&               // added GEC, sometimes this guy is dead
				(GetNearestEnemy (pu1p2) < 450.0f)) 
			{
				pu2p2 = BuildObject ("svfigh",2, pu1p2);
				//pu3p2 = BuildObject ("svtank",2, pu1p2);
				//pu4p2 = BuildObject ("svtank",2, pu1p2);
				patrol2spawned = true;
				Patrol(pu2p2, "patrol2");
				//Patrol(pu3p2, "patrol2");
				//Patrol(pu4p2, "patrol2");
			}
		}

		if
			(
			(patrol3time < GetTime()) && (patrol3spawned == false)
			)
		{
			patrol3time = GetTime () + 2.0f;

			if
				(GetNearestEnemy (pu1p3) < 450.0f)
			{
				pu2p3 = BuildObject ("svfigh",2, pu1p3);
				//pu3p3 = BuildObject ("svtank",2, pu1p3);
				//pu4p3 = BuildObject ("svtank",2, pu1p3);
				patrol3spawned = true;
				Patrol(pu2p3, "patrol3");
				//Patrol(pu3p3, "patrol3");
				//Patrol(pu4p3, "patrol3");
			}
		}
	}

	if
		(
		(!IsAlive(avrec)) && (missionfail1 == false)
		)
	{
		aud20 = AudioMessage("misn0653.wav");
		aud21 = AudioMessage("misn0651.wav");
		missionfail1 = true;
	}

	if
		(missionfail1 == true)
	{
		if
			(
			(IsAudioMessageDone(aud20)) &&
			(IsAudioMessageDone(aud21))
			)
		{
			FailMission(GetTime(), "misn06l5.des");
		}
	}

	if 
		(opencamdone == true)
	{
		CameraPath ("openingcampath", 1000, 500, p5u3);
		AddHealth(p5u3, 50);
		AddHealth(p5u4, 50);
		AddHealth(p5u6, 50);
		AddHealth(p5u9, 50);
		AddHealth(p5u12, 50);
	}

	if
		(
		(opencamdone == true) && ((opencamtime < GetTime()) || CameraCancelled())
		)
	{
		StopAudioMessage(audmsg);
		audmsg = 0;
		CameraFinish();
		opencamdone = false;
		if
			(IsAlive(svu1))
		{RemoveObject (svu1);}
		if
			(IsAlive(svu2))
		{RemoveObject (svu2);}
		if
			(IsAlive(svu3))
		{RemoveObject (svu3);}
		if
			(IsAlive(svu4))
		{RemoveObject (svu4);}
		if
			(IsAlive (p5u1))
		{RemoveObject (p5u1);}
		if
			(IsAlive (p5u2))
		{RemoveObject (p5u2);}
		if
			(IsAlive (p5u3))
		{RemoveObject (p5u3);}
		if
			(IsAlive (p5u4))
		{RemoveObject (p5u4);}
		if
			(IsAlive (p5u5))
		{RemoveObject (p5u5);}
		if
			(IsAlive (p5u6))
		{RemoveObject (p5u6);}
		if
			(IsAlive (p5u7))
		{RemoveObject (p5u7);}
		if
			(IsAlive (p5u8))
		{RemoveObject (p5u8);}
		if
			(IsAlive (p5u9))
		{RemoveObject (p5u9);}
		if
			(IsAlive (p5u10))
		{RemoveObject (p5u10);}
		if
			(IsAlive (p5u11))
		{RemoveObject (p5u11);}
		if
			(IsAlive (p5u12))
		{RemoveObject (p5u12);}
	}

	if 
		(newobjective == true)
	{
		ClearObjectives();


	if
		(
		(bugout == true) && (missionwon == true)
		)
	{
		AddObjective("misn0606.otf", GREEN);
		AddObjective("misn0605.otf", GREEN);
		AddObjective("misn0604.otf", GREEN);
		//AddObjective("misn0603.otf", GREEN);
		//AddObjective("misn0602.otf", GREEN);
		//AddObjective("misn0601.otf", GREEN);
	}

	if
		(
		(bugout == true) && (missionwon == false)
		)
	{
		AddObjective("misn0606.otf", WHITE);
		AddObjective("misn0605.otf", GREEN);
		AddObjective("misn0604.otf", GREEN);
		//AddObjective("misn0603.otf", GREEN);
		//AddObjective("misn0602.otf", GREEN);
		//AddObjective("misn0601.otf", GREEN);
	}


	if
		(
		(lprecon == true) && (bugout == false)
		)
	{
		AddObjective("misn0605.otf", WHITE);
		AddObjective("misn0604.otf", GREEN);
		//AddObjective("misn0603.otf", GREEN);
		//AddObjective("misn0602.otf", GREEN);
		//AddObjective("misn0601.otf", GREEN);
	}

	/*if
		(
		(transarrive == true) && (lprecon == false)
		)
	{
		AddObjective("misn0607.otf", WHITE);
		AddObjective("misn0604.otf", GREEN);
		//AddObjective("misn0603.otf", GREEN);
		//AddObjective("misn0602.otf", GREEN);
		//AddObjective("misn0601.otf", GREEN);
	}*/





	if
		(
		(starportreconed == true) && (transarrive == false) && (safebreak == false)
		)
	{
		AddObjective("misn0604.otf", WHITE);
		//AddObjective("misn0603.otf", GREEN);
		//AddObjective("misn0602.otf", GREEN);
		//AddObjective("misn0601.otf", GREEN);
	}


	if
		(
		(neworders == true) && (starportreconed == false)
		)
	{
		AddObjective("misn0603.otf", WHITE);
		AddObjective("misn0602.otf", GREEN);
		AddObjective("misn0601.otf", GREEN);
	}


	if
		(
		(reconheaphestus == true) && (neworders == false)
		)
	{
		AddObjective("misn0602.otf", WHITE);
		AddObjective("misn0601.otf", GREEN);
	}

	if
		(
		(haephestusdisc == true) && (reconheaphestus == false) && (hephikey == false)
		)
	{
		AddObjective("misn0601.otf", WHITE);
	}

	if
		(fifthplatoon == true)
	{
		AddObjective("misn0600.otf", WHITE);
	}
	newobjective = false;
	}


	
		

	if 
		(
		(haephestusdisc == false) && (GetDistance (haephestus, player) < 1000.0f)
		)

	{
		aud1 = AudioMessage ("misn0602.wav");
		haephestusdisc = true;
		hephdisctime = GetTime() + 60.0f;
	}

	if
		(
		(loopbreaker == false) &&
		(haephestusdisc == true) && (IsAudioMessageDone(aud1))
		)
	{
		SetObjectiveOn (haephestus);
		SetObjectiveName (haephestus, "Object");
		newobjective = true;
		loopbreaker = true;
	}

	if
		(
		(haephestusdisc == true) && (reconheaphestus == false) && (hephikey == false)
		&& (hephdisctime < GetTime()) && (hephwarn < 2)
		)
	{
		AudioMessage("misn0690.wav");
		hephdisctime = GetTime() + 20.0f;
		hephwarn = hephwarn + 1;
	}

	if 
		(
		(hephwarn == 2) && (missionfail4 == false) && (hephdisctime < GetTime())
		)
	{
		aud105 = AudioMessage("misn0694.wav");
		missionfail4 = true;
	}

	if
		(
		(missionfail4 == true) && (IsAudioMessageDone(aud105))
		)
	{
		FailMission(GetTime() + 0.0f, "misn06l1.des");
	}





	if 
		(
		(reconheaphestus == false) && (GetDistance (player, haephestus) < 125.0f) &&
		(hephikey == false)
		)
	{
		heph1 = AudioMessage ("misn0603.wav");
		heph2 = AudioMessage ("misn0604.wav");
		reconheaphestus = true;
		SetObjectiveOff (haephestus);
		CameraReady ();
		cam1time = GetTime() + 12.0f;
		cam1done = true;
		identtime = GetTime() + 20.0f;
	}



	if
		(
		(identtime < GetTime()) && (hephikey == false)
		 && (ident < 2)
		 )
	{
		AudioMessage("misn0691.wav");
		ident = ident + 1;
		identtime = GetTime() + 10.0f;
	}

	if
		(
		(ident == 2) && (identtime < GetTime()) &&
		(hephikey == false) && (missionfail == false)
		)
	{
		aud100 = AudioMessage("misn0694.wav");
		missionfail = true;
	}

	if
		(
		(missionfail == true) && (IsAudioMessageDone(aud100))
		)
	{
		FailMission(GetTime() + 0.0f, "misn06l2.des");
	}


	if
		(
		(IsInfo("obheph") == true) && (hephikey == false)
		)
	{
		processtime = GetTime() + 5.0f;
		hephikey = true;
		reconheaphestus = true;
		SetObjectiveOff (haephestus);
		newobjective = true;
	}

	if 
		(
		(neworders == false) && (processtime < GetTime())
		)
	{
		aud2 = AudioMessage ("misn0605.wav");
		//AudioMessage ("misn0606.wav");
		//AudioMessage ("misn0607.wav");
		fifthplatoon = false;
		neworders = true;
		buildcam = true;
		discstar = GetTime() + 80.0f;
	}

	if 
		(
		(buildcam == true) && (IsAudioMessageDone(aud2))
		)
	{
		SetObjectiveOff (rendezvous);
		starportcam = BuildObject ("apcamr",1,"cam1spawn");
		SetObjectiveName (starportcam, "Starport");
		buildcam = false;
		newobjective = true;
	}

	if 
		(
		(GetDistance (player, blockade1) < 420.0f) && (blockadefound == false)
		)
	{
		AudioMessage ("misn0636.wav");
		blockadefound = true;
	}

	if
		(
		(IsInfo("obstp1") == true) && (star1recon == false)
		)
	{
		star1recon = true;
	}
	if
		(
		(IsInfo("obstp8") == true) && (star4recon == false)
		)
	{
		star4recon = true;
	}
	if
		(
		(IsInfo("obstp3") == true) && (star6recon == false)
		)
	{
		star6recon = true;
	}

	if
		(
		(fail3 == false) && (spfail == 4)
		)
	{
		fail3 = true;
		aud54 = AudioMessage("misn0694.wav");
	}

	if
		(fail3 == true)
	{
		if
			(IsAudioMessageDone(aud54))
		{
			FailMission(GetTime()+0.0f, "misn06l6.des");
		}
	}

	if
		(
		(starportreconed == false) && (reconsptime < GetTime()) && 
		(fail3 == false) && (spfail < 4)
		)
	{
		AudioMessage("misn0654.wav");
		reconsptime = GetTime() + 15.0f;
		spfail = spfail + 1;
	}

	if 
		(
		(star1recon == true) &&
		(star4recon == true) &&
		(star6recon == true) &&
		(starportreconed == false)
		)
	{
		aud3 = AudioMessage ("misn0650.wav");
		aud4 = AudioMessage ("misn0606.wav");
		aud5 = AudioMessage ("misn0607.wav");
		starportreconed = true;
		start1 = GetTime () + 15.0f;
	}

	if
		(
		(star == false) &&
		(starportreconed == true) && (IsAudioMessageDone(aud3)) &&
		(IsAudioMessageDone(aud4)) &&  (IsAudioMessageDone(aud5)) 
		
		)
	{
		newobjective = true;
		star = true;
	}




	if 
		(
		(starportdisc == false)  && (GetDistance (star8, player) < 200.0f)
		)
	{
		AudioMessage ("misn0608.wav");
		searchtime = GetTime( ) + 15.0f;
		starportdisc = true;
		reconsptime = GetTime() + 20.0f;
	}

	if
		(
		(neworders == true) && (starportdisc == false) && (discstar < GetTime())
		&& (stardisc < 3)
		)
	{
		AudioMessage("misn0695.wav");
		discstar = GetTime() + 40.0f;
		stardisc = stardisc + 1;
	}

	if
		(
		(stardisc == 3) && (discstar < GetTime()) && (missionfail3 == false)
		)
	{
		missionfail3 = true;
		aud101 = AudioMessage("misn0694.wav");
	}

	if
		(
		(missionfail3 == true) && (IsAudioMessageDone(aud101))
		)
	{
		FailMission(GetTime() + 0.0f, "misn06l3.des");
	}
	if
		(
		(ccaattack == false) && (check1 < GetTime())
		)
	{
		enemy = GetNearestEnemy(wAu1);
		if
			(GetDistance(enemy, wAu1) < 410.0f)
		{
			Attack (wAu1, enemy);
			Attack (wAu2, enemy);
			//Attack (wAu3, enemy);
			SetIndependence(wAu2, 1);
			//SetIndependence(wAu3, 1);
			ccaattack = true;
			start1 = GetTime() - 1;
		}
		check1 = GetTime() + 1.5f;
	}


	if
		(
		(starportreconed == true) && (ccaattack == false)
		)
	{
		Attack (wAu1, player);
		Attack (wAu2, player);
		//Attack (wAu3, player);
		SetIndependence(wAu1, 1);
		SetIndependence(wAu2, 1);
		//SetIndependence(wAu3, 1);
		ccaattack = true;
	}

	if 
		(
		(
		(GetDistance (wAu1, "cam1spawn") < 400.0f) ||
		(GetDistance (wAu2, "cam1spawn") < 400.0f) //||
		//(GetDistance (wAu3, "cam1spawn") < 400.0f)
		) && (ccaattack == true) && (loopbreak1 == false)
		&& (start1 < GetTime()) && (IsAudioMessageDone(aud5))
		)
	{
		aud500 = AudioMessage("misn0611.wav");
		CameraReady();
		cam3time = GetTime () + 5.0f;
		cam3done = true;
		ccaattack = false;
		loopbreak1 = true;
	}

	if
		(cam1done == true)
	{
		CameraPath("cam1path", cam1hgt, 1000, haephestus);
		cam1hgt = cam1hgt + 15;
	}
	if
		(cam1done == true)
		{
		if
		
		(
		
			(
				(IsAudioMessageDone(heph1)) && (IsAudioMessageDone(heph2))
			)
				|| (CameraCancelled())
		)
		
			
			{
				CameraFinish();
				cam1done = false;
				StopAudioMessage(heph1);
				StopAudioMessage(heph2);
				newobjective = true;
			}
		}

	if 
		(cam3done == true)
	{
		CameraObject (wAu1, 300, 100, -900, wAu1);
	}
	if 
		(
		((cam3done == true) && (IsAudioMessageDone(aud500))) ||
		(CameraCancelled())
		)
	{
		CameraFinish();
		cam3done = false;
	}
	if
		(ccapullout == false)
	{
		IsAlive(wAu1);
		IsAlive(wAu1);
	}

	if 
		(
		(!IsAlive (wAu1)) && (!IsAlive (wAu2)) //&& (!IsAlive (wAu3))
		&& (ccapullout == false) && (starportreconed == true)
		)
	{
		aud15 = AudioMessage ("misn0612.wav");
		aud16 = AudioMessage ("misn0613.wav");
		transportarrive = GetTime () + 50.0f;
		transarrive = true;
		safebreak = true;
		ccapullout = true;
		wave1 = GetTime() + 60.0f;
		wave2 = GetTime() + 180.0f;
		wave3 = GetTime() + 300.0f;
	}

	if
		(
		(breaker19 == false) && (ccapullout == true) && 
		(IsAudioMessageDone(aud15)) &&
		(IsAudioMessageDone(aud16)) 
		)
	{
		//newobjective = true;
		breaker19 = true;
	}

	if
		(
		(wave1 < GetTime()) && (wave1start == false) && (IsAlive (svrec))
		)
	{
		w1u1 = BuildObject ("svfigh",2, svrec);
		w1u2 = BuildObject ("svtank",2, svrec);
		w1u3 = BuildObject ("svfigh",2, svrec);
		Attack (w1u1, avrec);
		Attack (w1u2, avrec);
		Attack (w1u3, avrec);
		SetIndependence (w1u1, 1);
		SetIndependence (w1u2, 1);
		SetIndependence (w1u3, 1);
		wave1start = true;
	}
	if
		(
		(wave2 < GetTime()) && (wave2start == false) && (IsAlive (svrec))
		)
	{
		w2u1 = BuildObject ("svfigh",2, svrec);
		w2u2 = BuildObject ("svtank",2, svrec);
		w2u3 = BuildObject ("svfigh",2, svrec);
		Attack (w2u1, avrec);
		Attack (w2u2, avrec);
		Attack (w2u3, avrec);
		SetIndependence (w2u1, 1);
		SetIndependence (w2u2, 1);
		SetIndependence (w2u3, 1);
		wave2start = true;
	}
	if
		(
		(wave3 < GetTime()) && (wave3start == false) && (IsAlive (svrec))
		)
	{
		w3u1 = BuildObject ("svfigh",2, svrec);
		w3u2 = BuildObject ("svtank",2, svrec);
		w3u3 = BuildObject ("svfigh",2, svrec);
		Attack (w3u1, avrec);
		Attack (w3u2, avrec);
		Attack (w3u3, avrec);
		SetIndependence (w3u1, 1);
		SetIndependence (w3u2, 1);
		SetIndependence (w3u3, 1);
		wave3start = true;
	}


		

	if 
		((transportarrive < GetTime()) && (transarrive == true))

	{
		aud6 = AudioMessage ("misn0614.wav");
		aud7 = AudioMessage ("misn0628.wav");
		lincolndestroyed = GetTime () + 60.0f;
		oneminstrans = GetTime () + 60.0f;
		transaway = GetTime () + 90.0f;
		platoonarrive = GetTime () + 1410.0f;
		threeminsplatoon = GetTime () + 390.0f;
		tenminsplatoon = GetTime () + 810.0f;
		fiveminsplatoon = GetTime () + 1110.0f;
		twominsplatoon = GetTime () + 1260.0f;
		transarrive = false;
		touchdown = true;
		threemin = true;
		tenmin = true;
		fivemin = true;
		twomin = true;
		platoonhere = true;
		newobjective = true;
		timerstart = GetTime() + 27.42f;
		lincolndes = true;
	}

	/*if 
		(
		(lincolndestroyed < GetTime()) && (lincolndes == false)
		)
	{
		aud8 = AudioMessage ("misn0626.wav");
		aud9 = AudioMessage ("misn0628.wav");
		lincolndes = true;
	}*/

	if
		(
		(lprecon == false) && (lincolndes == true)
		)
	{
		if
			(
			(IsAudioMessageDone(aud6)) && (IsAudioMessageDone(aud7))
			)
		{
			lprecon = true;
			StartCockpitTimer(540.0f, 362.0f, 180.0f);
			SetObjectiveOn(launchpad);
			newobjective = true;
		}
	}



	if 
		(
		(threeminsplatoon < GetTime ()) && 
		(threemin == true) && 
		(launchpadreconed == false)
		)
	{
		bogey = GetNearestEnemy(player);
		if
			(GetDistance(bogey, player) > 400.0f)
		{

		sim1 = BuildObject("avtank", 3, "sim1");
		sim2 = BuildObject("avtank", 3, "sim2");
		sim3 = BuildObject("avtank", 3, "sim3");
		sim4 = BuildObject("avtank", 3, "sim4");
		sim5 = BuildObject("avtank", 3, "sim5");
		sim6 = BuildObject("avfigh", 3, "sim6");
		sim7 = BuildObject("avfigh", 3, "sim7");
		sim8 = BuildObject("avfigh", 3, "sim8");
		sim9 = BuildObject("avfigh", 3, "sim9");
		sim10 = BuildObject("avfigh", 3, "sim10");
		/*
			Jens
			this cineractive now
			works except that there is
			no path point called
			sim5spot
			So they don't move.
		*/
		Goto(sim1, "simpoint5");
		Goto(sim2, "simpoint5");
		Goto(sim3, "simpoint5");
		Goto(sim4, "simpoint5");
		Goto(sim5, "simpoint5");
		Goto(sim6, "simpoint5");
		Goto(sim7, "simpoint5");
		Goto(sim8, "simpoint5");
		Goto(sim9, "simpoint5");
		Goto(sim10, "simpoint5");
		CameraReady();
		simaud1 = AudioMessage ("misn0631.wav");
		simaud2 = AudioMessage ("misn0642.wav");
		simaud3 = AudioMessage ("misn0643.wav");
		simaud4 = AudioMessage ("misn0644.wav");
		simaud5 = AudioMessage ("misn0645.wav");
		simcam = true;
		threemin = false;
		HideCockpitTimer();
		}

	}

	if
		(simcam == true)
	{
		CameraObject(sim5, 0, 1000, -4000, sim5);
		if
		(
		(attack == false) && (IsAudioMessageDone(simaud4))
		)
	{
		Goto(sim1, "simpoint1");
		Goto(sim2, "simpoint1");
		Goto(sim4, "simpoint1");
		Goto(sim7, "simpoint1");
		Goto(sim3, "simpoint3");
		Goto(sim6, "simpoint3");
		Goto(sim10, "simpoint3");
		Goto(sim5, "simpoint5");
		Goto(sim8, "simpoint5");
		Goto(sim9, "simpoint5");
		attack = true;
	}

	}

	if
		(
		(simcam == true) && (breakout1 == false)
		)
	{
		if (IsAudioMessageDone(simaud1)) doneaud1=true;
		if (IsAudioMessageDone(simaud2)) doneaud2=true;
		if (IsAudioMessageDone(simaud3)) doneaud3=true;
		if (IsAudioMessageDone(simaud4)) doneaud4=true;
		if (IsAudioMessageDone(simaud5)) doneaud5=true;
		if
			(
				(
				(doneaud1) &&
				(doneaud2) &&
				(doneaud3) &&
				(doneaud4) &&
				(doneaud5)
				)  || 
				(CameraCancelled())
			)
		{
			CameraFinish();
			breakout1 = true;
			simcam = false;
			StopAudioMessage(simaud1);
			StopAudioMessage(simaud2);
			StopAudioMessage(simaud3);
			StopAudioMessage(simaud4);
			StopAudioMessage(simaud5);
		}
	}
	// this used to be breakout =, changed it to == so cineractive wouldn't last eternity
	if
		(
		(breakout1== true) && (removal == false)
		)
	{
		RemoveObject(sim1);
		RemoveObject(sim2);
		RemoveObject(sim3);
		RemoveObject(sim4);
		RemoveObject(sim5);
		RemoveObject(sim6);
		RemoveObject(sim7);
		RemoveObject(sim8);
		RemoveObject(sim9);
		RemoveObject(sim10);
		removal=true;
		StopCockpitTimer();
		HideCockpitTimer();
	}

	



	/*if
		(
		(removal == true) && (timergone == false)
		)
	{
		StopCockpitTimer();
		timergone = true;
	}*/

	if
		(
		(tenminsplatoon < GetTime ()) && 
		(tenmin == true) && 
		(launchpadreconed == false) && (reminder == false)
		)
	{
		AudioMessage ("misn0632.wav");
		tenmin = false;
	}

	if
		(
		(fiveminsplatoon < GetTime ()) && 
		(fivemin == true) &&
		(launchpadreconed == false) && (reminder == false)
		)
	{
		AudioMessage ("misn0633.wav");
		fivemin = false;
	}

	if
		(
		(twominsplatoon < GetTime ()) && 
		(twomin == true) &&
		(launchpadreconed == false) && (reminder == false)
		)
	{
		AudioMessage ("misn0634.wav");
		twomin = false;
	}

	if
		(
		(GetDistance (player, svrec) < 250.0f) && 
		(reminder == false) && (launchpadreconed == false)
		)
	{
		AudioMessage ("misn0638.wav");
		reminder = true;
		end = GetTime() + 120.0f;
	}

	if
		(
		(reminder == true) && (GetDistance(player, launchpad) > 400.0f) &&
		(launchpadreconed == false) && (end < GetTime()) && (breaker == false)
		)
	{
		aud102 = AudioMessage ("misn0635.wav");
		aud103 = AudioMessage ("misn0646.wav");
		aud104 = AudioMessage ("misn0651.wav");
		platoonhere = false;
		endme = true;
		breaker = true;
	}

	if
		(
		(IsInfo("sblpad") == true)  &&
		(launchpadreconed == false)
		)
	{
		time1 = GetTime() + 2.0f;
		bugout = true;
		launchpadreconed = true;
		HideCockpitTimer();
		SetObjectiveOff(launchpad);
		//newobjective = true;
	}

	if
		(
		(bugout == true) &&  
		(corbettalive == true) && (time1 < GetTime()) &&
		(threemin == true) && (bustout == false)
		)
	{
		AudioMessage ("misn0629.wav");
		AudioMessage ("misn0630.wav");
		AudioMessage ("misn0647.wav");
		ccap1 = BuildObject ("svfigh",2,"ccaplatoonspawn");
		Attack (ccap1, avrec);
		SetIndependence (ccap1, 1);
		//bugout = false;
		platoonhere = false;
		pickupset = true;
		platoonarrive = 999999999999.0f;
		twominsplatoon = 999999999999.0f;
		tenminsplatoon = 999999999999.0f;
		fiveminsplatoon = 999999999999.0f;
		newobjective = true;
		bustout = true;
	}

	if
		(
		(bugout == true) &&  
		(corbettalive == true) && (time1 < GetTime()) &&
		(threemin == false) && (bustout == false)
		)
	{
		AudioMessage ("misn0629.wav");
		AudioMessage ("misn0630.wav");
		//AudioMessage ("misn0647.wav");
		ccap1 = BuildObject ("svfigh",2,"ccaplatoonspawn");
		Attack (ccap1, avrec);
		SetIndependence (ccap1, 1);
		//bugout = false;
		platoonhere = false;
		pickupset = true;
		platoonarrive = 999999999999.0f;
		twominsplatoon = 999999999999.0f;
		tenminsplatoon = 999999999999.0f;
		fiveminsplatoon = 999999999999.0f;
		newobjective = true;
		bustout = true;
	}
	if
		(
		(breakme == false) && (bugout == true) &&  
		(corbettalive == false) && (time1 < GetTime())
		)
	{
		AudioMessage ("misn0629.wav");
		AudioMessage ("misn0630.wav");
		SetIndependence (ccap1, 1);
		platoonhere = false;
		breakme = true;
		pickupset = true;
		platoonarrive = 999999999999.0f;
		twominsplatoon = 999999999999.0f;
		tenminsplatoon = 999999999999.0f;
		fiveminsplatoon = 999999999999.0f;
		newobjective = true;
		deathtime = GetTime() + 30.0f;
	}

	if
		(
		(deathtime < GetTime()) && (death == false)
		)
	{
		death = true;
		deathtime = 99999999999999.0f;
		AudioMessage ("misn0635.wav");
		ccap1 = BuildObject ("svfigh",2,"ccaplatoonspawn");
		Attack (ccap1, avrec);
	}

	if
		(pickupset == true) 
	{
		switch (extractpoint)
		{
		case 0:
			dustoffcam = BuildObject ("apcamr", 1, "bugout1");
			break;
		case 1:
			dustoffcam = BuildObject ("apcamr", 1, "bugout2");
			break;
		case 2:
			dustoffcam = BuildObject ("apcamr", 1, "bugout3");
			break;
		case 3:
			dustoffcam = BuildObject ("apcamr", 1, "bugout4");
			break;
		}
		SetObjectiveName (dustoffcam, "Dust Off");
		pickupset = false;
		pickupreached = true;
		SetObjectiveOff(launchpad);
	}

	if
		(
		(bustout == true) && (!IsAlive(dustoffcam))
		)
	{
		pickupset = true;
	}

	if
		(
		(GetDistance (avrec, dustoffcam) < 100.0f) && 
		(GetDistance (player, dustoffcam) < 100.0f) &&
		(pickupreached == true)
		)
	{
		AudioMessage ("misn0649.wav");
		SucceedMission (GetTime() + 5.0f, "misn06w1.des");
		pickupreached = false;
		dustoff = true;
		newobjective = true;
	}


	if
		(
		(platoonarrive <  GetTime()) && (platoonhere == true)
		&& (reminder == true) && (time1 < GetTime())
		)
	{
		AudioMessage ("misn0635.wav");
		AudioMessage ("misn0648.wav");
		ccap1 = BuildObject ("svfigh",2,"ccaplatoonspawn");
		Attack (ccap1, avrec);
		SetIndependence (ccap1, 1);
		platoonhere = false;
		twominsplatoon = 999999999999.0f;
		corbettalive = false;
	}

	if
		(IsAlive(ccap1))
	{
		spawnme = GetNearestEnemy(ccap1);
	}

	if
		(
		(GetDistance(ccap1, spawnme) < 410) && (economyccaplatoon == false)
		)
	{
		ccap2 = BuildObject ("svfigh",2,ccap1);
		ccap3 = BuildObject ("svfigh",2,ccap1);
		ccap4 = BuildObject ("svfigh",2,ccap1);
		ccap5 = BuildObject ("svfigh",2,ccap1);
		ccap6 = BuildObject ("svtank",2,ccap1);
		ccap7 = BuildObject ("svtank",2,ccap1);
		ccap8 = BuildObject ("svtank",2,ccap1);
		ccap9 = BuildObject ("svtank",2,ccap1);
		//ccap10 = BuildObject ("svtank",2,ccap1);
		//ccap11 = BuildObject ("svtank",2,ccap1);
		//ccap12 = BuildObject ("svturr",2,ccap1);
		//ccap13 = BuildObject ("svturr",2,ccap1);
		//ccap14 = BuildObject ("svartl",2,ccap1);
		//ccap15 = BuildObject ("svartl",2,ccap1);
		Attack (ccap2, avrec);
		Attack (ccap3, avrec);
		Attack (ccap4, avrec);
		Attack (ccap5, avrec);
		Attack (ccap6, avrec);
		Attack (ccap7, avrec);
		Attack (ccap8, avrec);
		Attack (ccap9, avrec);
		//Attack (ccap10, avrec);
		//Attack (ccap11, avrec);
		//Attack (ccap12, avrec);
		//Attack (ccap13, avrec);
		//Attack (ccap14, avrec);
		//Attack (ccap15, avrec);
		SetIndependence (ccap2, 1);
		SetIndependence (ccap3, 1);
		SetIndependence (ccap4, 1);
		SetIndependence (ccap5, 1);
		SetIndependence (ccap6, 1);
		SetIndependence (ccap7, 1);
		SetIndependence (ccap8, 1);
		SetIndependence (ccap9, 1);
		//SetIndependence (ccap10, 1);
		//SetIndependence (ccap11, 1);
		//SetIndependence (ccap12, 1);
		//SetIndependence (ccap13, 1);
		//SetIndependence (ccap14, 1);
		//SetIndependence (ccap15, 1);
		economyccaplatoon = true;
	}

	/*
		Jens platoonarrive is a floating point number.
		Here you test to see if it is 'true', like a boolean.
		This will compile but probably never evaluate
		correctly.  
		For arcane reasons platoonarrive is probaly 'true'
		50 % of the time, completely at random unless you 
		set it to zero somewhere, which will make it false.
	*/

	if
		(
		(platoonhere == true) && (respawn == false)
		)
	{
		if
			(
			(!IsAlive(ccap1)) &&
			(!IsAlive(ccap2)) &&
			(!IsAlive(ccap3)) &&
			(!IsAlive(ccap4)) &&
			(!IsAlive(ccap5)) &&
			(!IsAlive(ccap6)) &&
			(!IsAlive(ccap7)) &&
			(!IsAlive(ccap8)) &&
			(!IsAlive(ccap9))
			)
		{
			ccap1 = BuildObject("svfigh", 2, "ccaplatoonspawn");
			respawn = true;
			economyccaplatoon = false;
		}
	}


	if
		(
		(twominsplatoon < GetTime()) && (corbettalive == true)
		)
	{
		corbettalive = false;
	}


	if
		(
		(platoonarrive < GetTime ()) && (platoonhere == true)
		&& (reminder == false)
		)
	{
		aud102 = AudioMessage ("misn0635.wav");
		aud103 = AudioMessage ("misn0646.wav");
		aud104 = AudioMessage ("misn0651.wav");
		platoonhere = false;
		endme = true;
	}

	if
		(
		(endme == true) && (IsAudioMessageDone(aud102)) &&
		(IsAudioMessageDone(aud103)) &&
		(IsAudioMessageDone(aud104)) 
		)
	{
		FailMission(GetTime() + 0.0f, "misn06l4.des");
	}

}	

Misn06Mission::Misn06Mission(void)
{
}

Misn06Mission::~Misn06Mission()
{
}

bool Misn06Mission::Load(void)
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
		return true;
	}

	bool ret = true;

	_ASSERTE(0);

	return ret;
}

bool Misn06Mission::PostLoad(void)
{
	if (missionSave)
		return true;

	bool ret = true;

	int h_count = &h_last - h_array;
	for (int i = 0; i < h_count; i++)
		h_array[i] = ConvertHandle(h_array[i]);

	return ret;
}

bool Misn06Mission::Save(void)
{
	if (missionSave)
		return true;

	bool ret = true;

	_ASSERTE(0);

	return ret;
}

void Misn06Mission::Update(void)
{
	Execute();
}

bool Save(bool misnSave)
{
	missionSave = misnSave;
	return mission->Save();
}

bool Load(bool misnSave)
{
	mission = new Misn06Mission();
	missionSave = misnSave;
	return mission->Load();
}

bool PostLoad(bool misnSave)
{
	missionSave = misnSave;
	return mission->PostLoad();
}

void AddObject(Handle h)
{
	mission->AddObject(h);
}

void Update(void)
{
	mission->Update();
}

void PostRun(void)
{
	delete mission;
}

static MisnExport misnExport;
MisnImport misnImport;

MisnExport * __cdecl GetMisnAPI(MisnImport *import)
{
	misnImport = *import;
	misnExport.misnImport = &misnImport;
	misnExport.Save = Save;
	misnExport.Load = Load;
	misnExport.PostLoad = PostLoad;
	misnExport.AddObject = AddObject;
	misnExport.Update = Update;
	misnExport.PostRun = PostRun;
	return &misnExport;
}
