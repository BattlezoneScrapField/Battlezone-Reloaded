-- Single Player NSDF Mission 17 Lua conversion, created by General BlackDragon. 

-- Single Table for all our save/load variables. This SP mission has too many variables to function with them independently. ("main function has > 200 local variables", or "Load having > 197 variables in assignment")
local M = {

-- bools
	openingcin = false,
	camera1 = false,
	camera2 = false,
	camera3 = false,
	wave1start = false,
	wave2start = false,
	wave3start = false,
	--wave4start = false,
	--wave5start = false,
	--wave6start = false,
	missionstart = false,
	--missionfail = false,
	transdestroyed = false,
	transportfound = false,
	returnwave = false,
	missionwon = false,
	--alternateroute = false,
	rand1brk = false,
	rand2brk = false,
	rand3brk = false,
	newobjective = false,
	dontgo = false,
	dg1 = false,
	dg2 = false,
	dg3 = false,
	--builddone = false,
	fail1 = false,
	fail2 = false,
	--win1 = false,
	blastoff = false,
	thrust1 = false,
	thrust2 = false,
	thrust3 = false,
	thrust4 = false,
	fail3 = false,
	openingcindone = false,
	transblownup = false,
	message1 = false,
	message2 = false,
	message3 = false,
	--message4 = false,
	savwaves = false,
-- Floats (really doubles in Lua)
	--explosions = 0,
	rand1 = 0,
	rand2 = 0,
	rand3 = 0,
	gettosavtrans = 0,
	hurry1 = 0,
	hurry2 = 0,
	hurry3 = 0,
	hurry4 = 0,
	savattack = 0,
	quake_check = 0,
	next_second = 0,
	enemycheck = 0,-- quake_check 
-- Handles
	transport = nil,
	avrec = nil,
	player = nil,
	enemy = nil,
	thrusterone = nil,
	thrustertwo = nil,
	thrusterthree = nil,
	thrusterfour = nil,
	w1u1 = nil,
	--w1u2 = nil,
	w1u3 = nil,
	--w1u4 = nil,
	--w2u1 = nil,
	w2u2 = nil,
	--w2u3 = nil,
	w2u4 = nil,
	w3u1 = nil,
	--w3u2 = nil,
	w3u3 = nil,
	--w3u4 = nil,
	--w4u1 = nil,
	--w4u2 = nil,
	--w4u3 = nil,
	--w4u4 = nil,
	--w5u1 = nil,
	--w5u2 = nil,
	--w5u3 = nil,
	--w5u4 = nil,
	--w6u1 = nil,
	--w6u2 = nil,
	--w6u3 = nil,
	--w6u4 = nil,
	aud1 = nil,
	basenav = nil,
	rand1a = nil,
	--rand1b = nil,
	--rand1c = nil,
	rand2a = nil,
	--rand2b = nil,
	--rand2c = nil,
	rand3a = nil,
	--rand3b = nil,
	--rand3c = nil,
	dg1a = nil,
	dg1b = nil,
	--dg1c = nil,
	--dg1d = nil,
	dg2a = nil,
	dg2b = nil,
	--dg2c = nil,
	--dg2d = nil,
	dg3a = nil,
	dg3b = nil,
	--dg3c = nil,
	--dg3d = nil,
	fury1 = nil,
	fury2 = nil,
	fury3 = nil,
	fury4 = nil,
	sav1 = nil,
	sav2 = nil,
	sav3 = nil,
	scrapcam = nil,
	scrapcam2 = nil,
-- Ints
	x = 0,
	y = 0,
	z = 0,
	quake_level = 0,
	quake_count = 0 -- quake_level is for varying quakes
}

function Save()
    return 
		M
end

function Load(...)	
    if select('#', ...) > 0 then
		M
		 =  ...
    end
end


function Start()

	--missionSupportsBZWinner = true;
	--missionSupportsBZLoser = true;
	

	M.enemycheck = 999999999999.0;
	M.next_second = 99999999999.0;
	M.savattack = 99999999999999.0;

	M.x = 6000;
	M.y = 1500;
	M.rand1 = 9999999.0;
	M.rand2 = 9999999.0;
	M.rand3 = 9999999.0;
	M.hurry1 = 999999.0;
	M.hurry2 = 999999.0;
	M.hurry3 = 999999.0;
	M.hurry4 = 999999.0;
	M.gettosavtrans = 9999999.0;

end

function AddObject(h)


end

function Update()

-- START OF SCRIPT

	--[[ -- BZWinner cheat Code reading not supported via Lua. -GBD
	if (missionBZWinner >= 0)
	then
		if (missionBZFired) then
			return;
		end
		AudioMessage("misn1808.wav");
		SucceedMission(GetTime() + 12.0);
		M.fail2 = true;
		M.missionwon = true;
		M.newobjective = true;
		missionBZFired = true;
	end
	if (missionBZLoser >= 0)
	then
		if (missionBZFired) return;
		switch (missionBZLoser)
		then
		case 2:
			FailMission(GetTime() + 5.0, "misn18l1.des");
			AudioMessage("misn1806.wav");
			M.fail1 = true;
		case 1:
			CameraReady();
			FailMission(GetTime() + 7.0, "misn18l2.des");
			AudioMessage("misn1807.wav");
			M.fail2 = true;
			M.blastoff = true;
			break;
		case 0:
		default:
			M.fail3 = true;
			FailMission(GetTime() + 7.0, "misn18l3.des");
			AudioMessage("misn1704.wav");
			break;
		end
		missionBZFired = true;
	end
	--]]

	--[[
		Here is where you 
		put what happens 
		every frame.  
	--]]

	if 
		(M.missionstart == false)
	then

		M.aud1 = AudioMessage ("misn1801.wav");
		M.avrec = GetHandle("avrecy2_recycler");
		SetScrap (1, 80);
		M.scrapcam = GetHandle("scrapcam");
		M.scrapcam2 = GetHandle("scrapcam2");
		M.rand1 = GetTime()+150.0;
		M.rand2 = GetTime()+230.0;
		M.rand3 = GetTime()+310.0;
		M.gettosavtrans = GetTime() + 600.0;
		M.basenav = GetHandle("basenav");
		SetObjectiveName(M.basenav, "Home Base");
		M.missionstart = true;
		M.thrusterone = GetHandle("hbtrn20049_i76building");
		M.thrustertwo = GetHandle("hbtrn20050_i76building");
		M.thrusterthree = GetHandle("hbtrn20051_i76building");
		M.thrusterfour = GetHandle("hbtrn20052_i76building");
		M.transport = GetHandle("hbtran0038_i76building");
		StartEarthquake(2.0);
		M.quake_level = 2;
		M.quake_check = GetTime()+2.0;
		M.newobjective = true;
		SetObjectiveOn(M.transport);
		SetObjectiveName(M.transport, "Fury Transport");
		M.next_second = GetTime() + 5.0;
		M.enemycheck = GetTime() + 3.0;
	end
	M.player = GetPlayerHandle();
	if
		(
		(M.transportfound == false)  and 
		(M.enemycheck < GetTime())
		)
	then

		if
			(IsAlive(M.transport))
		then
		M.enemy = GetNearestEnemy(M.transport);
		M.enemycheck = GetTime() + 3.0;
		end
	end


	if
		(M.newobjective == true)
	then
		ClearObjectives();

		if
			(M.missionwon == true)
		then
			AddObjective("misn1803.otf", "GREEN");
			AddObjective("misn1802.otf", "GREEN");
		end

		if
			(
			(M.transdestroyed == true) and (M.missionwon == false)
			)
		then
			AddObjective("misn1803.otf", "WHITE");
			AddObjective("misn1802.otf", "GREEN");
		end

		if
			(
			(M.transdestroyed == false) and (M.transportfound == true)
			)
		then
			AddObjective("misn1802.otf", "WHITE");
		end

		if
			(M.transportfound == false)
		then
			AddObjective("misn1801.otf", "WHITE");
		end

		M.newobjective = false;

	end

	--[[
		After four seconds the
		quake gets bigger for 
		two seconds.
	--]]
	--[[if (GetTime()>M.quake_check)
	then
		M.quake_count = M.quake_count + 1;
		M.quake_check = GetTime()+3.0;
		if (M.quake_count%4 == 1)
		then
			UpdateEarthQuake(M.quake_level*3.0);
		else 
			UpdateEarthQuake(M.quake_level*0.9);
		end

	end--]]
	if 
		(M.openingcin == false)
	then
		CameraReady ();
		M.camera1 = true;
		M.openingcin = true;
	end

	if 
		(M.camera2 == true)
	then
		if (CameraPath ("opencam1", 1500, 8000, M.scrapcam))
			 
			--	(PanDone())
			then
				M.camera2 = false;
				M.camera3 = true;
			end
	end

	if 
		(M.camera3 == true)
	then
		if (CameraPath("opencam2", 1500, 9000, M.scrapcam2))
		
--				(PanDone())
			then
				M.camera3 = false;
				RemoveObject(M.scrapcam);
				RemoveObject(M.scrapcam2);
			end
	end
	if
		(M.camera1 == true)
	then
		M.x = M.x - (300 * GetTimeStep());
			if
				(CameraPath("opencam3", M.x, 2000, M.transport))
--				(PanDone())
			then
				M.camera1 = false;
				M.camera2 = true;
				
			end
	end

	if
		(M.openingcindone == false)
	then
		if
		(
		 (IsAudioMessageDone(M.aud1))  or  (CameraCancelled())
		)
	then
		StopAudioMessage(M.aud1);
		M.openingcindone = true;
		M.camera1 = false;
		M.camera2 = false;
		M.camera3 = false;
		CameraFinish();
	end
	end

	if
		(M.transdestroyed == false)
	then
		if
			(
			(IsAlive(M.transport)) and (GetTime()>M.next_second)
			)
		then
			AddHealth(M.transport, 100.0);
		end
	end

	if
		(
		(M.transdestroyed == true) and (M.transblownup == false)
		)
	then
		Damage(M.transport, 999999999.0);
		M.transblownup = true;
	end


	if (M.transportfound == false)
		then
			if (GetTime()>M.next_second)
			then
				if
					(IsAlive(M.thrusterone))
				then
					AddHealth(M.thrusterone, 50.0);
				end
				if
					(IsAlive(M.thrustertwo))
				then
					AddHealth(M.thrustertwo, 50.0);
				end
				if
					(IsAlive(M.thrusterthree))
				then
					AddHealth(M.thrusterthree, 50.0);
				end
				if
					(IsAlive(M.thrusterfour))
				then
					AddHealth(M.thrusterfour, 50.0);
				end
				M.next_second = GetTime()+1.0;
			end
		end


	if
		(
		(M.wave1start == false)  and 
			(
			(GetDistance (M.player, "spawn1a") < 100.0)  or 
			(GetDistance (M.player, "spawnalt1a") < 100.0) or 
			(GetDistance (M.player, "cheat1a") < 200.0)  or 
			(GetDistance (M.player, "cheatalt1a") < 200.0)
			)
		)
	then
		M.w1u1 = exu.BuildAsyncObject ("hvsat",2, "spawn1b");
		M.w1u3 = exu.BuildAsyncObject ("hvsat",2, "spawnalt1b");
		Goto (M.w1u1, "transport1");
		Goto (M.w1u3, "transport2");
		SetIndependence (M.w1u1, 1);
		SetIndependence (M.w1u3, 1);
		M.wave1start = true;
	end
	if
		(
		(M.wave2start == false)  and 
			(
			(GetDistance (M.player, "spawn2a") < 100.0)  or 
			(GetDistance (M.player, "spawnalt2a") < 100.0) or 
			(GetDistance (M.player, "cheat2a") < 200.0)  or 
			(GetDistance (M.player, "cheatalt2a") < 200.0)
			)
		
		)
	then
		M.w2u2 = exu.BuildAsyncObject ("hvsat",2, "spawn2b");
		M.w2u4 = exu.BuildAsyncObject ("hvsat",2, "spawnalt2b");
		Goto (M.w2u2, "transport3");
		Goto (M.w2u4, "transport4");
		SetIndependence (M.w2u2, 1);
		SetIndependence (M.w2u4, 1);
		M.wave2start = true;
	end
	if
		(
		    (M.wave3start == false) and 
			(
			(GetDistance (M.player, "spawn3a") < 100.0)  or 
			(GetDistance (M.player, "spawnalt3a") < 100.0)  or 
			(GetDistance (M.player, "cheat3a") < 200.0)  or 
			(GetDistance (M.player, "cheatalt3a") < 200.0)
			)
		)
	then
		M.w3u1 = exu.BuildAsyncObject ("hvsat",2, "spawn3b");
		M.w3u3 = exu.BuildAsyncObject ("hvsat",2, "spawnalt3b");
		Goto (M.w3u1, "transport5");
		Goto (M.w3u3, "transport6");
		SetIndependence (M.w3u1, 1);
		SetIndependence (M.w3u3, 1);
		M.wave3start = true;
	end

	if 
		(
		(M.rand1 < GetTime()) and (M.rand1brk == false)
		)
	then
		M.rand1a = exu.BuildAsyncObject ("hvsav",2, "spawnrand");
		Goto (M.rand1a, "transport7");
		SetIndependence (M.rand1a, 1);
		M.rand1brk = true;
	end
	if 
		(
		(M.rand2 < GetTime()) and (M.rand2brk == false)
		)
	then
		M.rand2a = exu.BuildAsyncObject ("hvsav",2, "spawnrand");
		Goto (M.rand2a, "transport8");
		SetIndependence (M.rand2a, 1);
		M.rand2brk = true;
	end

	if 
		(
		(M.rand3 < GetTime()) and (M.rand3brk == false)
		)
	then
		M.rand3a = exu.BuildAsyncObject ("hvsav",2, "spawnrand");
		Goto (M.rand3a, "transport9");
		SetIndependence (M.rand3a, 1);
		M.rand3brk = true;
	end

	if 
		(
		(M.transdestroyed == true) and 
		(M.dontgo == false)  and 
		(GetDistance (M.player, "dontgo") < 50.0)
		)
	then
		AudioMessage ("misn1805.wav");
		M.dontgo = true;
	end

	if
		(
		(M.dontgo == true)  and 
		(GetDistance (M.player, "dontgo1") < 100.0)  and 
		(M.dg1 == false)
		)
	then
		M.dg1a = exu.BuildAsyncObject ("hvsat",2, "dgs1");
		M.dg1b = exu.BuildAsyncObject ("hvsav",2, "spawn1");
		M.dg1 = true;
	end

	if
		(
		(M.dontgo == true)  and 
		(GetDistance (M.player, "dontgo2") < 100.0)  and 
		(M.dg2 == false)
		)

	then
		M.dg2a = exu.BuildAsyncObject ("hvsat",2, "dgs2");
		M.dg2b = exu.BuildAsyncObject ("hvsav",2, "spawn1");
		M.dg2 = true;
	end

	if
		(
		(M.dontgo == true)  and 
		(GetDistance (M.player, "dontgo3") < 100.0)  and 
		(M.dg3 == false)
		)

	then
		M.dg3a = exu.BuildAsyncObject ("hvsat",2,"dgs3");
		M.dg3b = exu.BuildAsyncObject ("hvsav",2,"spawn1");
		M.dg3 = true;
	end

	if
		(
		( not IsAlive(M.thrusterone)) and 
		( not IsAlive(M.thrustertwo))  and 
		( not IsAlive(M.thrusterthree))  and 
		( not IsAlive(M.thrusterfour))  and 
		(M.transdestroyed == false)
		)
	then
		AudioMessage ("misn1804.wav");
		M.transdestroyed = true;
		M.newobjective = true;
		M.hurry1 = GetTime()+60.0;
		M.hurry2 = GetTime()+85.0;
		M.hurry3 = GetTime()+115.0;
		M.hurry4 = GetTime()+140.0;
		M.quake_level = 6;
		StartCockpitTimer(180, 120, 30);
	end

	if
		(
		(M.hurry1 < GetTime()) and (M.missionwon  == false)
		)
	then
		AudioMessage ("misn1809.wav");
		M.hurry1 = GetTime()+99999999.0;
	end

	if
		(
		(M.hurry2 < GetTime()) and (M.missionwon  == false)
		)
	then
		AudioMessage ("misn1810.wav");
		M.hurry2 = GetTime()+99999999.0;
	end

	if
		(
		(M.hurry3 < GetTime()) and (M.missionwon  == false)
		)
	then
		AudioMessage ("misn1811.wav");
		M.hurry3 = GetTime()+99999999.0;
	end

	if
		(
		(M.hurry4 < GetTime()) and (M.missionwon  == false)
		)
	then
		AudioMessage ("misn1812.wav");
		M.hurry4 = GetTime()+99999999.0;
	end

	if 
		(
		(M.transportfound == false)  and 
		(
			(GetDistance (M.player, "transfound") < 100.0)  or 
			(GetDistance(M.enemy, M.transport) < 200.0)
		)
		)
	then
		AudioMessage("misn1816.wav");
		M.transportfound = true;
		if
			(IsAlive(M.transport))
		then
		SetObjectiveOff(M.transport);
		end
		if
			(IsAlive(M.thrusterone))
		then
		SetObjectiveOn(M.thrusterone);
		end
		if
			(IsAlive(M.thrustertwo))
		then
		SetObjectiveOn(M.thrustertwo);
		end
		if
			(IsAlive(M.thrusterthree))
		then
		SetObjectiveOn(M.thrusterthree);
		end
		if
			(IsAlive(M.thrusterfour))
		then
		SetObjectiveOn(M.thrusterfour);
		end
		M.savattack = GetTime() + 180.0;
		M.newobjective = true;
		if
			(M.wave1start == false)
		then
		M.w1u1 = exu.BuildAsyncObject ("hvsat",2, "spawn1b");
		M.w1u3 = exu.BuildAsyncObject ("hvsat",2, "spawnalt1b");
		Goto (M.w1u1, "transport1");
		Goto (M.w1u3, "transport2");
		SetIndependence (M.w1u1, 1);
		SetIndependence (M.w1u3, 1);
		M.wave1start = true;
		end
		if
			(M.wave2start == false)
		then
		M.w2u2 = exu.BuildAsyncObject ("hvsat",2, "spawn2b");
		M.w2u4 = exu.BuildAsyncObject ("hvsat",2, "spawnalt2b");
		Goto (M.w2u2, "transport3");
		Goto (M.w2u4, "transport4");
		SetIndependence (M.w2u2, 1);
		SetIndependence (M.w2u4, 1);
		M.wave2start = true;
		end
		if
			(M.wave3start == false)
		then
		M.w3u1 = exu.BuildAsyncObject ("hvsat",2, "spawn3b");
		M.w3u3 = exu.BuildAsyncObject ("hvsat",2, "spawnalt3b");
		Goto (M.w3u1, "transport5");
		Goto (M.w3u3, "transport6");
		SetIndependence (M.w3u1, 1);
		SetIndependence (M.w3u3, 1);
		M.wave3start = true;
		end
	end

	if
		(
		(M.transdestroyed == false) and (M.savwaves == false) and (M.savattack < GetTime())
		)
	then
		M.savwaves = true;
		M.fury1 = exu.BuildAsyncObject("hvsav", 2, "spawnrand");
		M.fury2 = exu.BuildAsyncObject("hvsav", 2, "spawnrand");
		M.fury3 = exu.BuildAsyncObject("hvsav", 2, "spawnrand2");
		M.fury4 = exu.BuildAsyncObject("hvsav", 2, "spawnrand2");
		Attack (M.fury1, M.avrec);
		Attack (M.fury2, M.avrec);
		Attack (M.fury3, M.avrec);
		Attack (M.fury4, M.avrec);
	end

	if
		(M.savwaves == true)
	then
		if
			(
			( not IsAlive(M.fury1))  and 
			( not IsAlive(M.fury2))  and 
			( not IsAlive(M.fury3))  and 
			( not IsAlive(M.fury4)) 
			)
		then
			M.fury1 = exu.BuildAsyncObject("hvsav", 2, "spawnrand");
		M.fury2 = exu.BuildAsyncObject("hvsav", 2, "spawnrand");
		M.fury3 = exu.BuildAsyncObject("hvsav", 2, "spawnrand2");
		M.fury4 = exu.BuildAsyncObject("hvsav", 2, "spawnrand2");
		Attack (M.fury1, M.avrec);
		Attack (M.fury2, M.avrec);
		Attack (M.fury3, M.avrec);
		Attack (M.fury4, M.avrec);
		end
	end

	if 
		(
		(M.transportfound == false) and (M.gettosavtrans < GetTime())
		 and  (M.fail1 == false)
		)
	then
		FailMission (GetTime () + 5.0, "misn18l1.des");
		AudioMessage ("misn1806.wav");
		M.fail1 = true;
	end

	if
		(
		(M.transdestroyed == true)  and 
		(GetDistance (M.player, M.avrec) > 400.0)  and 
		(GetCockpitTimer() <= 0)  and 
		(M.fail2 == false)
		)
	then
     	CameraReady();
		FailMission ( GetTime () + 7.0, "misn18l2.des");
		AudioMessage ("misn1807.wav");
		M.fail2 = true;
		M.blastoff = true;
	end

	if
		(
		( not IsAlive(M.avrec)) and (M.fail3 == false)
		)
	then
		M.fail3 = true;
		FailMission(GetTime() + 7.0, "misn18l3.des");
		AudioMessage("misn1704.wav");
	end

	if 
		(M.blastoff == true)
	then
		M.y = M.y + 500;
		CameraObject(M.player, 1, M.y, 1000, M.player);
	end


	if
		(
			(
			(GetDistance (M.player, "return1") < 100.0)  or 
			(GetDistance (M.player, "return2") < 100.0)
			)
		 and  (M.returnwave == false) and (M.transdestroyed == true)
		)
	then
		M.sav1 = exu.BuildAsyncObject ("hvsat",2, "spawnreturn");
		--M.sav2 = BuildObject ("hvsat",2, "spawnreturn");
		--M.sav3 = BuildObject ("hvsav",2, "spawnreturn");
		M.returnwave = true;
	end

	if 
		(
		(GetDistance (M.player, M.avrec) < 200.0)  and 
		(M.transdestroyed == true) and (M.missionwon == false)
		)
	then
		AudioMessage ("misn1808.wav");
		SucceedMission (GetTime () + 12.0);
		M.fail2 = true;
		M.missionwon = true;
		M.newobjective = true;
	end

  if
  (
  ( not IsAlive(M.thrusterone)) and (M.thrust1 == false)
  )
  then
	  M.z = M.z +1;
	 M.thrust1 = true;
  end
  if
  (
  ( not IsAlive(M.thrustertwo)) and (M.thrust2 == false)
  )
  then
	M.z = M.z +1;
	M.thrust2 = true;
  end
  if
  (
  ( not IsAlive(M.thrusterthree)) and (M.thrust3 == false)
  )
  then
	  M.z = M.z +1;
	 M.thrust3 = true;
  end
  if
  (
  ( not IsAlive(M.thrusterfour)) and (M.thrust4 == false)
  )
  then
	  M.z = M.z +1;
	 M.thrust4 = true;
  end

  if
  (
  (M.z == 1) and (M.message1 == false)
  )
  then
	  AudioMessage("misn1813.wav");
	  M.message1 = true;
  end
  if
  (
  (M.z == 2) and (M.message2 == false)
  )
  then
	  AudioMessage("misn1814.wav");	
	  M.message2 = true;
  end
  if
  (
  (M.z == 3) and (M.message3 == false)
  )
  then
  AudioMessage("misn1815.wav");
  M.message3 = true;
  end

-- END OF SCRIPT
	
end