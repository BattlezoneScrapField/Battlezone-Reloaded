#include "GameCommon.h"

#include "..\fun3d\AiMission.h"
#include "..\fun3d\ScriptUtils.h"

/*
	Misn06Mission Event
*/

class Misn18Mission : public AiMission {
	DECLARE_RTIME(Misn18Mission)
public:
	Misn18Mission(void);
	~Misn18Mission();

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
				openingcin, camera1, camera2, camera3, wave1start, wave2start, wave3start, wave4start, wave5start, wave6start,
				missionstart, missionfail, transdestroyed, transportfound, returnwave, 
				missionwon, alternateroute, rand1brk, rand2brk, rand3brk, newobjective,
				dontgo, dg1, dg2, dg3, builddone, fail1, fail2, win1, blastoff,
				thrust1, thrust2, thrust3, thrust4, fail3, openingcindone, transblownup,
				message1, message2, message3, message4, savwaves,
				b_last;
		};
		bool b_array[42];
	};

	// floats
	union {
		struct {
			float
				explosions, rand1, rand2, rand3, 
				gettosavtrans,
				hurry1, hurry2, hurry3, hurry4, savattack,
				quake_check,  next_second, enemycheck,// quake_check 
				f_last;
		};
		float f_array[13];
	};

	// handles
	union {
		struct {
			Handle
				transport, avrec, player, enemy, 
				thrusterone, thrustertwo, thrusterthree, thrusterfour, 
				w1u1,w1u2,w1u3,w1u4,
				w2u1,w2u2,w2u3,w2u4,
				w3u1,w3u2,w3u3,w3u4,
				w4u1,w4u2,w4u3,w4u4,
				w5u1,w5u2,w5u3,w5u4,
				w6u1,w6u2,w6u3,w6u4,
				aud1, basenav,
				rand1a, rand1b, rand1c,
				rand2a, rand2b, rand2c,
				rand3a, rand3b, rand3c,
				dg1a, dg1b, dg1c, dg1d,
				dg2a, dg2b, dg2c, dg2d,
				dg3a, dg3b, dg3c, dg3d, 
				fury1, fury2, fury3, fury4,
				sav1, sav2, sav3, scrapcam, scrapcam2,
				h_last;
		};
		Handle h_array[64];
	};

	// integers
	union {
		struct {
			int
				x, y, z,quake_level,quake_count,  // quake_level is for varying quakes
				i_last;
		};
		int i_array[5];
	};
};

void Misn18Mission::Setup(void)
{
	/*
	Here's where you
	set the values
	at the start.  
	*/
	wave1start = false;
	wave2start = false;
	wave3start = false;
	wave4start = false;
	wave5start = false;
	wave6start = false;
	rand1brk = false;
	rand2brk = false;
	rand3brk = false;
	dontgo = false;
	builddone = false;
	thrust1 = false;
	thrust2 = false;
	thrust3 = false;
	thrust4 = false;
	enemy = 0;
	enemycheck = 999999999999.0f;
	dg1 = false;
	dg2 = false;
	dg3 = false;
	next_second = 99999999999.0f;
	message1 = false;
	message2 = false;
	message3 = false;
	message4 = false;
	missionstart = false;
	missionwon = false;
	missionfail = false;
	transdestroyed = false;
	transportfound = false;
	alternateroute = false;
	transblownup = false;
	returnwave = false;
	camera1 = false;
	camera2 = false;
	camera3 = false;
	openingcin = false;
	fail1 = false;
	fail2 = false;
	win1 = false;
	blastoff = false;
	newobjective = false;
	transport = 0;
	basenav = 0;
	savattack = 99999999999999.0f;
		avrec = 0; 
		player = 0; 
		thrusterone = 0; 
		thrustertwo = 0; 
		thrusterthree = 0; 
		thrusterfour = 0; 
		w1u1 = 0;
		w1u2 = 0;
		w1u3 = 0;
		w1u4 = 0;
		w2u1 = 0;
		w2u2 = 0;
		w2u3 = 0;
		w2u4 = 0;
		w3u1 = 0;
		w3u2 = 0;
		w3u3 = 0;
		w3u4 = 0;
		w4u1 = 0;
		w4u2 = 0;
		w4u3 = 0;
		w4u4 = 0;
		w5u1 = 0;
		w5u2 = 0;
		w5u3 = 0;
		w5u4 = 0;
		w6u1 = 0;
		w6u2 = 0;
		w6u3 = 0;
		w6u4 = 0;
		scrapcam = 0;
		scrapcam2 = 0;
		rand1a = 0; 
		rand1b = 0; 
		rand1c = 0;
		rand2a = 0; 
		rand2b = 0; 
		rand2c = 0;
		rand3a = 0; 
		rand3b = 0; 
		rand3c = 0;
		aud1 = 0;
		dg1a = 0; 
		dg1b = 0; 
		dg1c = 0; 
		dg1d = 0;
		dg2a = 0; 
		dg2b = 0; 
		dg2c = 0; 
		dg2d = 0;
		dg3a = 0; 
		dg3b = 0; 
		dg3c = 0; 
		dg3d = 0;
		sav1 = 0; 
		sav2 = 0; 
		sav3 = 0;
		fail3 = false;
		savwaves = false;
		openingcindone = false;
		fury1 = 0;
		fury2 = 0;
		fury3 = 0;
		fury4 = 0;
	x = 6000;
	y = 1500;
	z = 0;
	rand1 = 9999999.0f;
	rand2 = 9999999.0f;
	rand3 = 9999999.0f;
	hurry1 = 999999.0f;
	hurry2 = 999999.0f;
	hurry3 = 999999.0f;
	hurry4 = 999999.0f;
	gettosavtrans = 9999999.0f;
	/*
		Harmless but unnessecary
		initialization of 
		quake variables.
	*/
	quake_count=0;
	quake_level=0;

}

void Misn18Mission::Execute(void)
{
	/*
		Here is where you 
		put what happens 
		every frame.  
	*/

	if 
		(missionstart == false)
	{

		aud1 = AudioMessage ("misn1801.wav");
		avrec = GetHandle ("avrecy2_recycler");
		SetScrap (1, 80);
		scrapcam = GetHandle("scrapcam");
		scrapcam2 = GetHandle("scrapcam2");
		rand1 = GetTime()+150.0f;
		rand2 = GetTime()+230.0f;
		rand3 = GetTime()+310.0f;
		gettosavtrans = GetTime() + 600.0f;
		basenav = GetHandle("basenav");
		GameObjectHandle :: GetObj(basenav) ->SetName ("Home Base");
		missionstart = true;
		thrusterone = GetHandle("hbtrn20049_i76building");
		thrustertwo = GetHandle("hbtrn20050_i76building");
		thrusterthree = GetHandle("hbtrn20051_i76building");
		thrusterfour = GetHandle("hbtrn20052_i76building");
		transport = GetHandle("hbtran0038_i76building");
		StartEarthquake(2.0f);
		quake_level=2;
		quake_check=GetTime()+2.0f;
		newobjective = true;
		SetObjectiveOn(transport);
		next_second = GetTime() + 5.0f;
		enemycheck = GetTime() + 3.0f;
	}
	player = GetPlayerHandle();
	if
		(
		(transportfound == false) &&
		(enemycheck < GetTime())
		)
	{

		if
			(IsAlive(transport))
		{
		enemy = GetNearestEnemy(transport);
		enemycheck = GetTime() + 3.0f;
		}
	}


	if
		(newobjective == true)
	{
		ClearObjectives();

		if
			(missionwon == true)
		{
			AddObjective("misn1803.otf", GREEN);
			AddObjective("misn1802.otf", GREEN);
		}

		if
			(
			(transdestroyed == true) && (missionwon == false)
			)
		{
			AddObjective("misn1803.otf", WHITE);
			AddObjective("misn1802.otf", GREEN);
		}

		if
			(
			(transdestroyed == false) && (transportfound == true)
			)
		{
			AddObjective("misn1802.otf", WHITE);
		}

		if
			(transportfound == false)
		{
			AddObjective("misn1801.otf", WHITE);
		}

		newobjective = false;

	}

	/*
		After four seconds the
		quake gets bigger for 
		two seconds.
	*/
	/*if (GetTime()>quake_check)
	{
		quake_count++;
		quake_check=GetTime()+3.0f;
		if (quake_count%4==1)
		{
			UpdateEarthQuake(quake_level*3.0f);
		}
		else UpdateEarthQuake(quake_level*0.9f);

	}*/
	if 
		(openingcin == false)
	{
		CameraReady ();
		camera1 = true;
		openingcin = true;
	}

	if 
		(camera2 == true)
	{
		if (CameraPath ("opencam1", 1500, 8000, scrapcam))
			 
			//	(PanDone())
			{
				camera2 = false;
				camera3 = true;
			}
	}

	if 
		(camera3 == true)
	{
		if (CameraPath("opencam2", 1500, 9000, scrapcam2))
		
//				(PanDone())
			{
				camera3 = false;
				RemoveObject(scrapcam);
				RemoveObject(scrapcam2);
			}
	}
	if
		(camera1 == true)
	{
		x = x-20;
			if
				(CameraPath("opencam3", x, 2000, transport))
//				(PanDone())
			{
				camera1 = false;
				camera2 = true;
				
			}
	}

	if
		(openingcindone == false)
	{
		if
		(
		 (IsAudioMessageDone(aud1)) || (CameraCancelled())
		)
	{
		StopAudioMessage(aud1);
		openingcindone = true;
		camera1 = false;
		camera2 = false;
		camera3 = false;
		CameraFinish();
	}
	}

	if
		(transdestroyed == false)
	{
		if
			(
			(IsAlive(transport)) && (GetTime()>next_second)
			)
		{
			GameObjectHandle::GetObj(transport)->AddHealth(100.0f);
		}
	}

	if
		(
		(transdestroyed == true) && (transblownup == false)
		)
	{
		Damage(transport, 999999999.0f);
		transblownup = true;
	}


	if (transportfound == false)
		{
			if (GetTime()>next_second)
			{
				if
					(IsAlive(thrusterone))
				{
				GameObjectHandle::GetObj(thrusterone)->AddHealth(50.0f);
				}
				if
					(IsAlive(thrustertwo))
				{
				GameObjectHandle::GetObj(thrustertwo)->AddHealth(50.0f);
				}
				if
					(IsAlive(thrusterthree))
				{
				GameObjectHandle::GetObj(thrusterthree)->AddHealth(50.0f);
				}
				if
					(IsAlive(thrusterfour))
				{
				GameObjectHandle::GetObj(thrusterfour)->AddHealth(50.0f);
				}
				next_second=GetTime()+1.0f;
			}
		}


	if
		(
		(wave1start == false) &&
			(
			(GetDistance (player, "spawn1a") < 100.0f) ||
			(GetDistance (player, "spawnalt1a") < 100.0f)||
			(GetDistance (player, "cheat1a") < 200.0f) ||
			(GetDistance (player, "cheatalt1a") < 200.0f)
			)
		)
	{
		w1u1 = BuildObject ("hvsat",2, "spawn1b");
		w1u3 = BuildObject ("hvsat",2, "spawnalt1b");
		Goto (w1u1, "transport1");
		Goto (w1u3, "transport2");
		SetIndependence (w1u1, 1);
		SetIndependence (w1u3, 1);
		wave1start = true;
	}
	if
		(
		(wave2start == false) &&
			(
			(GetDistance (player, "spawn2a") < 100.0f) ||
			(GetDistance (player, "spawnalt2a") < 100.0f)||
			(GetDistance (player, "cheat2a") < 200.0f) ||
			(GetDistance (player, "cheatalt2a") < 200.0f)
			)
		
		)
	{
		w2u2 = BuildObject ("hvsat",2, "spawn2b");
		w2u4 = BuildObject ("hvsat",2, "spawnalt2b");
		Goto (w2u2, "transport3");
		Goto (w2u4, "transport4");
		SetIndependence (w2u2, 1);
		SetIndependence (w2u4, 1);
		wave2start = true;
	}
	if
		(
		    (wave3start == false) && 
			(
			(GetDistance (player, "spawn3a") < 100.0f) ||
			(GetDistance (player, "spawnalt3a") < 100.0f) ||
			(GetDistance (player, "cheat3a") < 200.0f) ||
			(GetDistance (player, "cheatalt3a") < 200.0f)
			)
		)
	{
		w3u1 = BuildObject ("hvsat",2, "spawn3b");
		w3u3 = BuildObject ("hvsat",2, "spawnalt3b");
		Goto (w3u1, "transport5");
		Goto (w3u3, "transport6");
		SetIndependence (w3u1, 1);
		SetIndependence (w3u3, 1);
		wave3start = true;
	}

	if 
		(
		(rand1 < GetTime()) && (rand1brk == false)
		)
	{
		rand1a = BuildObject ("hvsav",2, "spawnrand");
		Goto (rand1a, "transport7");
		SetIndependence (rand1a, 1);
		rand1brk = true;
	}
	if 
		(
		(rand2 < GetTime()) && (rand2brk == false)
		)
	{
		rand2a = BuildObject ("hvsav",2, "spawnrand");
		Goto (rand2a, "transport8");
		SetIndependence (rand2a, 1);
		rand2brk = true;
	}

	if 
		(
		(rand3 < GetTime()) && (rand3brk == false)
		)
	{
		rand3a = BuildObject ("hvsav",2, "spawnrand");
		Goto (rand3a, "transport9");
		SetIndependence (rand3a, 1);
		rand3brk = true;
	}

	if 
		(
		(transdestroyed == true) && 
		(dontgo == false) &&
		(GetDistance (player, "dontgo") < 50.0f)
		)
	{
		AudioMessage ("misn1805.wav");
		dontgo = true;
	}

	if
		(
		(dontgo == true) &&
		(GetDistance (player, "dontgo1") < 100.0f) &&
		(dg1 == false)
		)
	{
		dg1a = BuildObject ("hvsat",2, "dgs1");
		dg1b = BuildObject ("hvsav",2, "spawn1");
		dg1 = true;
	}

	if
		(
		(dontgo == true) &&
		(GetDistance (player, "dontgo2") < 100.0f) &&
		(dg2 == false)
		)

	{
		dg2a = BuildObject ("hvsat",2, "dgs2");
		dg2b = BuildObject ("hvsav",2, "spawn1");
		dg2 = true;
	}

	if
		(
		(dontgo == true) &&
		(GetDistance (player, "dontgo3") < 100.0f) &&
		(dg3 == false)
		)

	{
		dg3a = BuildObject ("hvsat",2,"dgs3");
		dg3b = BuildObject ("hvsav",2,"spawn1");
		dg3 = true;
	}

	if
		(
		(!IsAlive(thrusterone)) && 
		(!IsAlive(thrustertwo)) &&
		(!IsAlive(thrusterthree)) &&
		(!IsAlive(thrusterfour)) &&
		(transdestroyed == false)
		)
	{
		AudioMessage ("misn1804.wav");
		transdestroyed = true;
		newobjective = true;
		hurry1 = GetTime()+60.0f;
		hurry2 = GetTime()+85.0f;
		hurry3 = GetTime()+115.0f;
		hurry4 = GetTime()+140.0f;
		quake_level=6;
		StartCockpitTimer(180.0f, 120.0f, 30.0f);
	}

	if
		(
		(hurry1 < GetTime()) && (missionwon ==false)
		)
	{
		AudioMessage ("misn1809.wav");
		hurry1 = GetTime()+99999999.0f;
	}

	if
		(
		(hurry2 < GetTime()) && (missionwon ==false)
		)
	{
		AudioMessage ("misn1810.wav");
		hurry2 = GetTime()+99999999.0f;
	}

	if
		(
		(hurry3 < GetTime()) && (missionwon ==false)
		)
	{
		AudioMessage ("misn1811.wav");
		hurry3 = GetTime()+99999999.0f;
	}

	if
		(
		(hurry4 < GetTime()) && (missionwon ==false)
		)
	{
		AudioMessage ("misn1812.wav");
		hurry4 = GetTime()+99999999.0f;
	}

	if 
		(
		(transportfound == false) &&
		(
			(GetDistance (player, "transfound") < 100.0f) ||
			(GetDistance(enemy, transport) < 200.0f)
		)
		)
	{
		AudioMessage("misn1816.wav");
		transportfound = true;
		if
			(IsAlive(transport))
		{
		SetObjectiveOff(transport);
		}
		if
			(IsAlive(thrusterone))
		{
		SetObjectiveOn(thrusterone);
		}
		if
			(IsAlive(thrustertwo))
		{
		SetObjectiveOn(thrustertwo);
		}
		if
			(IsAlive(thrusterthree))
		{
		SetObjectiveOn(thrusterthree);
		}
		if
			(IsAlive(thrusterfour))
		{
		SetObjectiveOn(thrusterfour);
		}
		savattack = GetTime() + 180.0f;
		newobjective = true;
		if
			(wave1start == false)
		{
		w1u1 = BuildObject ("hvsat",2, "spawn1b");
		w1u3 = BuildObject ("hvsat",2, "spawnalt1b");
		Goto (w1u1, "transport1");
		Goto (w1u3, "transport2");
		SetIndependence (w1u1, 1);
		SetIndependence (w1u3, 1);
		wave1start = true;
		}
		if
			(wave2start == false)
		{
		w2u2 = BuildObject ("hvsat",2, "spawn2b");
		w2u4 = BuildObject ("hvsat",2, "spawnalt2b");
		Goto (w2u2, "transport3");
		Goto (w2u4, "transport4");
		SetIndependence (w2u2, 1);
		SetIndependence (w2u4, 1);
		wave2start = true;
		}
		if
			(wave3start == false)
		{
		w3u1 = BuildObject ("hvsat",2, "spawn3b");
		w3u3 = BuildObject ("hvsat",2, "spawnalt3b");
		Goto (w3u1, "transport5");
		Goto (w3u3, "transport6");
		SetIndependence (w3u1, 1);
		SetIndependence (w3u3, 1);
		wave3start = true;
		}
	}

	if
		(
		(transdestroyed == false) && (savwaves == false) && (savattack < GetTime())
		)
	{
		savwaves = true;
		fury1 = BuildObject("hvsav", 2, "spawnrand");
		fury2 = BuildObject("hvsav", 2, "spawnrand");
		fury3 = BuildObject("hvsav", 2, "spawnrand2");
		fury4 = BuildObject("hvsav", 2, "spawnrand2");
		Attack (fury1, avrec);
		Attack (fury2, avrec);
		Attack (fury3, avrec);
		Attack (fury4, avrec);
	}

	if
		(savwaves == true)
	{
		if
			(
			(!IsAlive(fury1)) &&
			(!IsAlive(fury2)) &&
			(!IsAlive(fury3)) &&
			(!IsAlive(fury4)) 
			)
		{
			fury1 = BuildObject("hvsav", 2, "spawnrand");
		fury2 = BuildObject("hvsav", 2, "spawnrand");
		fury3 = BuildObject("hvsav", 2, "spawnrand2");
		fury4 = BuildObject("hvsav", 2, "spawnrand2");
		Attack (fury1, avrec);
		Attack (fury2, avrec);
		Attack (fury3, avrec);
		Attack (fury4, avrec);
		}
	}

	if 
		(
		(transportfound == false) && (gettosavtrans < GetTime())
		&& (fail1 == false)
		)
	{
		FailMission (GetTime () + 5.0f, "misn18l1.des");
		AudioMessage ("misn1806.wav");
		fail1 = true;
	}

	if
		(
		(transdestroyed == true) &&
		(GetDistance (player, avrec) > 400.0f) &&
		(GetCockpitTimer() <= 0) &&
		(fail2 == false)
		)
	{
     	CameraReady();
		FailMission ( GetTime () + 7.0f, "misn18l2.des");
		AudioMessage ("misn1807.wav");
		fail2 = true;
		blastoff = true;
	}

	if
		(
		(!IsAlive(avrec)) && (fail3 == false)
		)
	{
		fail3 = true;
		FailMission(GetTime() + 7.0f, "misn18l3.des");
		AudioMessage("misn1704.wav");
	}

	if 
		(blastoff == true)
	{
		y = y + 500;
		CameraObject(player, 1, y, 1000, player);
	}


	if
		(
			(
			(GetDistance (player, "return1") < 100.0f) ||
			(GetDistance (player, "return2") < 100.0f)
			)
		&& (returnwave == false) && (transdestroyed == true)
		)
	{
		sav1 = BuildObject ("hvsat",2, "spawnreturn");
		//sav2 = BuildObject ("hvsat",2, "spawnreturn");
		//sav3 = BuildObject ("hvsav",2, "spawnreturn");
		returnwave = true;
	}

	if 
		(
		(GetDistance (player, avrec) < 200.0f) &&
		(transdestroyed == true) && (missionwon == false)
		)
	{
		AudioMessage ("misn1808.wav");
		SucceedMission (GetTime () + 12.0f);
		fail2 = true;
		missionwon = true;
		newobjective = true;
	}

  if
  (
  (!IsAlive(thrusterone)) && (thrust1 == false)
  )
  {
	  z = z +1;
	 thrust1 = true;
  }
  if
  (
  (!IsAlive(thrustertwo)) && (thrust2 == false)
  )
  {
	z = z +1;
	thrust2 = true;
  }
  if
  (
  (!IsAlive(thrusterthree)) && (thrust3 == false)
  )
  {
	  z = z +1;
	 thrust3 = true;
  }
  if
  (
  (!IsAlive(thrusterfour)) && (thrust4 == false)
  )
  {
	  z = z +1;
	 thrust4 = true;
  }

  if
  (
  (z == 1) && (message1 == false)
  )
  {
	  AudioMessage("misn1813.wav");
	  message1 = true;
  }
  if
  (
  (z == 2) && (message2 == false)
  )
  {
	  AudioMessage("misn1814.wav");	
	  message2 = true;
  }
  if
  (
  (z == 3) && (message3 == false)
  )
  {
  AudioMessage("misn1815.wav");
  message3 = true;
  }



}

IMPLEMENT_RTIME(Misn18Mission)

Misn18Mission::Misn18Mission(void)
{
}

Misn18Mission::~Misn18Mission()
{
}

bool Misn18Mission::Load(file fp)
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

bool Misn18Mission::PostLoad(void)
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

bool Misn18Mission::Save(file fp)
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

void Misn18Mission::Update(void)
{
	AiMission::Update();
	Execute();
}
