-- Single Player NSDF Mission 5 Lua conversion, created by General BlackDragon. 

-- Single Table for all our save/load variables. This SP mission has too many variables to function with them independently. ("main function has > 200 local variables", or "Load having > 197 variables in assignment")
local M = {

-- bools
	missionstart = false,
	starportdisc = false,
	star1recon = false,
	--star2recon = false,
	--star3recon = false,
	star = false,
	star4recon = false,
	--star5recon = false,
	star6recon = false,
	--star7recon = false,
	--star8recon = false,
	--star9recon = false,
	--star10recon = false,
	--star11recon = false,
	missionfail = false,
	starportreconed = false,
	--surveystarport = false,
	--relicmissing = false,
	haephestusdisc = false,
	blockadefound = false,
	--ccabasedisc = false,
	--relicgone = false,
	missionfail1 = false,
	missionwon = false,
	newobjective = false,
	reconheaphestus = false,
	--recoverrelic = false,
	neworders = false,
	safebreak = false,
	ccaattack = false,
	--hidob2 = false,
	buildcam = false,
	ccapullout = false,
	transarrive = false,
	touchdown = false,
	lprecon = false,
	--fifteenmin = false,
	economyccaplatoon = false,
	tenmin = false,
	threemin = false,
	fivemin = false,
	twomin = false,
	platoonhere = false,
	corbettalive = false,
	lincolndes = false,
	loopbreak1 = false,
	opencamdone = false,
	cam1done = false,
	cam3done = false,
	patrol1set = false,
	patrol2set = false,
	patrol3set = false,
	startpat1 = false,
	startpat2 = false,
	startpat3 = false,
	startpat4 = false,
	wave1start = false,
	wave2start = false,
	wave3start = false,
	launchpadreconed = false,
	patrol1spawned = false,
	breakme = false,
	patrol2spawned = false,
	patrol3spawned = false,
	--transgone = false,
	bugout = false,
	pickupset = false,
	pickupreached = false,
	hephikey = false,
	reminder = false,
	dustoff = false,
	fail3 = false,
	trigger1 = false,
	ob1 = false,
	ob2 = false,
	ob3 = false,
	ob4 = false,
	timergone = false,
	--timerset = false,
	respawn = false,
	simcam = false,
	removal = false,
	breakout1 = false,
	attack = false,
	breaker = false,
	death = false,
	fifthplatoon = false,
	breaker19 = false,
	bustout = false,
	doneaud1 = false,
	doneaud2 = false,
	endme = false,
	doneaud3 = false,
	missionfail3 = false,
	missionfail4 = false,
	doneaud4 = false,
	doneaud5 = false,
	loopbreaker = false, -- doneauds created by GEC for cineractive control
-- Floats (really doubles in Lua)
	--transportgone = 0,
	searchtime = 0,
	processtime = 0,
	transportarrive = 0,
	oneminstrans = 0,
	transaway = 0,
	platoonarrive = 0,
	--fifteenminsplatoon = 0,
	tenminsplatoon = 0,
	threeminsplatoon = 0,
	fiveminsplatoon = 0,
	check1 = 0,
	time1 = 0,
	twominsplatoon = 0,
	opencamtime = 0,
	cam1time = 0,
	cam3time = 0,
	wave1 = 0,
	wave2 = 0,
	wave3 = 0,
	lincolndestroyed = 0,
	patrol1time = 0,
	patrol2time = 0,
	patrol3time = 0,
	deathtime = 0,
	hephdisctime = 0,
	identtime = 0,
	discstar = 0,
	--removetimer = 0,
	timerstart = 0,
	start1 = 0,
	spfail = 0,
	reconsptime = 0,
	endtime = 0,
-- Handles
	haephestus = nil,
	sim1 = nil,
	sim2 = nil,
	sim3 = nil,
	sim4 = nil,
	sim5 = nil,
	sim6 = nil,
	sim7 = nil,
	sim8 = nil,
	sim9 = nil,
	sim10 = nil,
	simaud1 = nil,
	simaud2 = nil,
	simaud3 = nil,
	simaud4 = nil,
	simaud5 = nil,
	heph1 = nil,
	heph2 = nil,
	enemy = nil,
	aud500 = nil, --handle for haephestus 
	--relic = nil,
	spawnme = nil,
	starport = nil, --handle for starport that triggers starportdisc bool
	player = nil, --duh not  
	--nav1 = nil,
	rendezvous = nil, --handle for cam where 5th platoon is supposed to be 
	blockade1 = nil, --handle of soviet turret in scrap field
	avrec = nil, --duh again not 
	svrec = nil, --yet another duh
	launchpad = nil, --where player nust go to get information on where database was taken 
	starportcam = nil, -- handle of navbeacon at starport 
	dustoffcam = nil, --handle of camera where player must go to finish mission 
	art1 = nil,
	--these handles are for the waves that attack the player
	w1u1 = nil,
	w1u2 = nil,
	w1u3 = nil,
	aud1 = nil,
	aud2 = nil,
	aud3 = nil,
	aud4 = nil,
	aud5 = nil,
	aud6 = nil,
	aud7 = nil,
	aud8 = nil,
	aud9 = nil,
	w2u1 = nil,
	w2u2 = nil,
	w2u3 = nil,
	w3u1 = nil,
	w3u2 = nil,
	w3u3 = nil,
	wAu1 = nil,
	wAu2 = nil,
	wAu3 = nil,
	p5u1 = nil,
	turret = nil,
	trigger = nil,
	--these are the handles of the starport buildings the player recons
	--star1 = nil,
	star2 = nil,
	--star3 = nil,
	--star4 = nil,
	--star5 = nil,
	star6 = nil,
	--star7 = nil,
	star8 = nil,
	--star9 = nil,
	--star10 = nil,
	--star11 = nil,
	--these are the handles of the fifth platoon used in the opening cineractive
	p5u2 = nil,
	p5u3 = nil,
	p5u4 = nil,
	p5u5 = nil,
	p5u6 = nil,
	p5u7 = nil,
	p5u8 = nil,
	p5u9 = nil,
	p5u10 = nil,
	p5u11 = nil,
	p5u12 = nil,
	aud20 = nil,
	aud21 = nil,
	--these are the handles for the units that patrol the canyons
	pu1p1 = nil,
	pu2p1 = nil,
	pu3p1 = nil,
	pu4p1 = nil,
	pu1p2 = nil,
	pu2p2 = nil,
	pu3p2 = nil,
	pu4p2 = nil,
	pu1p3 = nil,
	pu2p3 = nil,
	pu3p3 = nil,
	pu4p3 = nil,
	pu1p4 = nil,
	pu2p4 = nil,
	pu3p4 = nil,
	aud15 = nil,
	aud16 = nil,
	aud54 = nil,
	svu1 = nil,
	svu2 = nil,
	svu3 = nil,
	svu4 = nil,
	bogey = nil,
	--these are the handles for the cca platoon created at the end of the mission
	ccap1 = nil,
	ccap2 = nil,
	ccap3 = nil,
	ccap4 = nil,
	ccap5 = nil,
	ccap6 = nil,
	ccap7 = nil,
	ccap8 = nil,
	ccap9 = nil,
	ccap10 = nil,
	ccap11 = nil,
	ccap12 = nil,
	ccap13 = nil,
	ccap14 = nil,
	ccap15 = nil,
-- Ints
	cam1hgt = 0,
	patrol1start = 0,
	patrol2start = 0,
	patrol3start = 0,
	extractpoint = 0,
	hephwarn = 0,
	ident = 0,
	stardisc = 0,
	aud100 = 0,
	aud101 = 0,
	aud102 = 0,
	aud103 = 0,
	aud104 = 0,
	aud105 = 0,
	audmsg = 0
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

	M.discstar = 99999999999.0;
	M.missionstart = true;
	M.endtime = 999999999999.0;
	
	M.fifthplatoon = true;
	
	M.reconsptime = 9999999999999999.0;
	--M.removetimer = 99999999.0;
	M.processtime = 999999.0;
	M.searchtime = 999999.0;
	M.transportarrive = 99999.0;
	M.oneminstrans = 999999.0;
	M.transaway = 999999.0;
	M.platoonarrive = 999999.0;
	--M.fifteenminsplatoon = 999999.0;
	M.tenminsplatoon = 999999.0;
	M.threeminsplatoon = 999999.0;
	M.twominsplatoon = 999999.0;
	M.fiveminsplatoon = 999999.0;
	M.opencamtime = 999999.0;
	M.cam1time = 999999.0;
	M.cam3time = 999999.0;
	M.cam1hgt = 800;
	M.wave1 = 999999.0;
	M.wave2 = 999999.0;
	M.wave3 = 999999.0;
	M.start1 = 999999999.0;
	M.lincolndestroyed = 999999.0;
	M.patrol1start = math.random(0, 3); --rand() % 4;
	M.patrol2start = math.random(0, 3); --rand() % 4;
	M.patrol3start = math.random(0, 3); --rand() % 4;
	M.extractpoint = math.random(0, 3); --rand() % 4;
	M.patrol1time = 99999999.0;
	M.patrol2time = 99999999.0;
	M.patrol3time = 99999999.0;
	M.check1 = 99999999.0;
	M.time1 = 999999999.0;
	M.hephdisctime = 9999999999.0;
	M.identtime = 999999999.0;
	M.timerstart = 999999999.0;
	M.deathtime = 999999999999.0;

end

function AddObject(h)


end

function Update()

-- START OF SCRIPT

	if 
		(M.missionstart == true)

	then
		M.audmsg = AudioMessage("misn0601.wav");
		M.missionstart = false;
		M.player = GetPlayerHandle();
		M.rendezvous = GetHandle("eggeizr1-1_geyser");
		SetObjectiveName(M.rendezvous, "5th Platoon");
		M.haephestus = GetHandle("obheph0_i76building");
		M.avrec = GetHandle("avrecy-1_recycler");
		M.svrec = GetHandle("svrecy-1_recycler");
		M.launchpad = GetHandle("sblpad0_i76building");
		M.wAu1 = GetHandle("svfigh568_wingman");
		M.wAu2 = GetHandle("svfigh566_wingman");
		M.turret = GetHandle("M.turret");
		--M.wAu3 = GetHandle("svfigh567_wingman");
		--M.star1 = GetHandle("obstp34_i76building");
		M.star2 = GetHandle("obstp25_i76building");
		--M.star4 = GetHandle("obstp11_i76building");
		--M.star5 = GetHandle("obstp21_i76building");
		M.star6 = GetHandle("obstp10_i76building");
		--M.star7 = GetHandle("obstp23_i76building");
		M.star8 = GetHandle("obstp33_i76building");
		--M.star9 = GetHandle("obstp35_i76building");
		M.blockade1 = GetHandle("svturr649_turrettank");
		M.svu1 = GetHandle("M.svu1");
		M.svu2 = GetHandle("M.svu2");
		M.svu3 = GetHandle("M.svu3");
		M.svu4 = GetHandle("M.svu4");
		M.p5u3 = GetHandle("avtank13_wingman");
		M.p5u4 = GetHandle("avtank11_wingman");
		M.p5u6 = GetHandle("avtank12_wingman");
		M.p5u9 = GetHandle("avfigh7_wingman");
		M.p5u12 = GetHandle("avfigh10_wingman");
		M.patrol1time = GetTime() + 30.0;
		M.patrol2time = GetTime() + 30.0;
		M.patrol3time = GetTime() + 30.0;
		SetObjectiveOn(M.rendezvous);
		AddObjective("misn0600.otf", "WHITE");
		CameraReady();
		M.opencamtime = GetTime() + 30.0;
		M.opencamdone = true;
		M.newobjective = true;
		SetScrap(1,5);
		M.art1 = GetHandle("svartl648_howitzer");
		Defend (M.art1, 1);
		M.check1 = GetTime() + 20.0;
	


	end
	M.player = GetPlayerHandle();
	if
		(IsAlive(M.star2))
	then
		AddHealth(M.star2, 10000.0);
	end
	if
		(IsAlive(M.star6))
	then
		AddHealth(M.star6, 10000.0);
	end
	if
		(IsAlive(M.star8))
	then
		AddHealth(M.star8, 10000.0);
	end

	if
		(M.trigger1 == false)
	then
		M.trigger = GetNearestEnemy(M.turret);
		if
			(
			(GetDistance(M.trigger, M.turret) < 200.0)  or  ( not IsAlive(M.turret))
			)
		then
	if
		(M.patrol1set == false)
	then
	--	switch (M.patrol1start)
		if M.patrol1start == 0 then
	--	case 0:
			M.pu1p1 = BuildObject ("svfigh",2, "pat1sp1");
		elseif M.patrol1start == 1 then
	--		break;
	--	case 1:
			M.pu1p1 = BuildObject ("svfigh",2, "pat1sp2");
		elseif M.patrol1start == 2 then	
	--		break;
	--	case 2:
			M.pu1p1 = BuildObject ("svtank",2, "pat1sp3");
		elseif M.patrol1start == 3 then
	--		break;
	--	case 3:
			M.pu1p1 = BuildObject ("svfigh",2, "pat1sp4");
		end
		M.patrol1set = true;
	end

	if
		(M.patrol2set == false)
	then
	--	switch (M.patrol2start)
		if M.patrol2start == 0 then
	--	case 0:
			M.pu1p2 = BuildObject ("svfigh",2, "pat2sp1");
		elseif M.patrol2start == 1 then	
	--		break;
	--	case 1:
			M.pu1p2 = BuildObject ("svfigh",2, "pat2sp2");
		elseif M.patrol2start == 2 then
	--		break;
	--	case 2:
			M.pu1p2 = BuildObject ("svtank",2, "pat2sp3");
		elseif M.patrol2start == 3 then
	--		break;
	--	case 3:
			M.pu1p2 = BuildObject ("svfigh",2, "pat2sp4");
		end
		M.patrol2set = true;
	end

	if
		(M.patrol3set == false)
	then
	--	switch (M.patrol3start)
		if M.patrol3start == 0 then
	--	case 0:
			M.pu1p3 = BuildObject ("svfigh",2, "pat3sp1");
		elseif M.patrol3start == 1 then	
	--		break;
	--	case 1:
			M.pu1p3 = BuildObject ("svfigh",2, "pat3sp2");
		elseif M.patrol3start == 2 then
	--		break;
	--	case 2:
			M.pu1p3 = BuildObject ("svtank",2, "pat3sp3");
		elseif M.patrol3start == 3 then	
	--		break;
	--	case 3:
			M.pu1p3 = BuildObject ("svfigh",2, "pat3sp4");
		end
		M.patrol3set = true;
	end
	
	if 
		(
		(M.patrol1set == true) and (M.startpat1 == false)
		)
	then
		Patrol (M.pu1p1, "patrol1");
		M.startpat1 = true;
	end

	if
		(
		(M.patrol2set == true) and (M.startpat2 == false)
		)
	then
		Patrol (M.pu1p2, "patrol2");

		M.startpat2 = true;
	end

	if
		(
		(M.patrol3set == true) and (M.startpat3 == false)
		)
	then
		Patrol (M.pu1p3, "patrol3");
		M.startpat3 = true;
	end

	if
		(M.startpat4 == false)
	then
		Patrol (M.pu1p4, "patrol4");
		Patrol (M.pu2p4, "patrol4");
		Patrol (M.pu3p4, "patrol4");
		M.startpat4 = true;
	end
	M.trigger1 = true;
			end
		end

	if
		(M.trigger1 == true)
	then
		if
			(
			(M.patrol1time < GetTime()) and (M.patrol1spawned == false)
			)
		then
			M.patrol1time = GetTime () + 2.0;

			if ((IsAlive(M.pu1p1))  and 
				(GetNearestEnemy (M.pu1p1) < 450.0))
			then
				M.pu2p1 = BuildObject ("svtank",2, M.pu1p1);
				--M.pu3p1 = BuildObject ("svtank",2, M.pu1p1);
				--M.pu4p1 = BuildObject ("svtank",2, M.pu1p1);
				M.patrol1spawned = true;
				Patrol(M.pu2p1, "patrol1");
				--Patrol(M.pu3p1, "patrol1");
				--Patrol(M.pu4p1, "patrol1");
			end
		end

		if
			(
			(M.patrol2time < GetTime()) and (M.patrol2spawned == false)
			)
		then
			M.patrol2time = GetTime () + 2.0;

			if ((IsAlive(M.pu1p2)) and               -- added GEC, sometimes this guy is dead
				(GetNearestEnemy (M.pu1p2) < 450.0)) 
			then
				M.pu2p2 = BuildObject ("svfigh",2, M.pu1p2);
				--M.pu3p2 = BuildObject ("svtank",2, M.pu1p2);
				--M.pu4p2 = BuildObject ("svtank",2, M.pu1p2);
				M.patrol2spawned = true;
				Patrol(M.pu2p2, "patrol2");
				--Patrol(M.pu3p2, "patrol2");
				--Patrol(M.pu4p2, "patrol2");
			end
		end

		if
			(
			(M.patrol3time < GetTime()) and (M.patrol3spawned == false)
			)
		then
			M.patrol3time = GetTime () + 2.0;

			if
				(GetNearestEnemy (M.pu1p3) < 450.0)
			then
				M.pu2p3 = BuildObject ("svfigh",2, M.pu1p3);
				--M.pu3p3 = BuildObject ("svtank",2, M.pu1p3);
				--M.pu4p3 = BuildObject ("svtank",2, M.pu1p3);
				M.patrol3spawned = true;
				Patrol(M.pu2p3, "patrol3");
				--Patrol(M.pu3p3, "patrol3");
				--Patrol(M.pu4p3, "patrol3");
			end
		end
	end

	if
		(
		( not IsAlive(M.avrec)) and (M.missionfail1 == false)
		)
	then
		M.aud20 = AudioMessage("misn0653.wav");
		M.aud21 = AudioMessage("misn0651.wav");
		M.missionfail1 = true;
	end

	if
		(M.missionfail1 == true)
	then
		if
			(
			(IsAudioMessageDone(M.aud20))  and 
			(IsAudioMessageDone(M.aud21))
			)
		then
			FailMission(GetTime(), "misn06l5.des");
		end
	end

	if 
		(M.opencamdone == true)
	then
		CameraPath ("openingcampath", 1000, 500, M.p5u3);
		AddHealth(M.p5u3, 50.0);
		AddHealth(M.p5u4, 50.0);
		AddHealth(M.p5u6, 50.0);
		AddHealth(M.p5u9, 50.0);
		AddHealth(M.p5u12, 50.0);
	end

	if
		(
		(M.opencamdone == true) and ((M.opencamtime < GetTime() and IsAudioMessageDone(M.audmsg))  or  CameraCancelled())
		)
	then
		StopAudioMessage(M.audmsg);
		M.audmsg = 0;
		CameraFinish();
		M.opencamdone = false;
		if
			(IsAlive(M.svu1))
		then RemoveObject (M.svu1);end
		if
			(IsAlive(M.svu2))
		then RemoveObject (M.svu2);end
		if
			(IsAlive(M.svu3))
		then RemoveObject (M.svu3);end
		if
			(IsAlive(M.svu4))
		then RemoveObject (M.svu4);end
		if
			(IsAlive (M.p5u1))
		then RemoveObject (M.p5u1);end
		if
			(IsAlive (M.p5u2))
		then RemoveObject (M.p5u2);end
		if
			(IsAlive (M.p5u3))
		then RemoveObject (M.p5u3);end
		if
			(IsAlive (M.p5u4))
		then RemoveObject (M.p5u4);end
		if
			(IsAlive (M.p5u5))
		then RemoveObject (M.p5u5);end
		if
			(IsAlive (M.p5u6))
		then RemoveObject (M.p5u6);end
		if
			(IsAlive (M.p5u7))
		then RemoveObject (M.p5u7);end
		if
			(IsAlive (M.p5u8))
		then RemoveObject (M.p5u8);end
		if
			(IsAlive (M.p5u9))
		then RemoveObject (M.p5u9);end
		if
			(IsAlive (M.p5u10))
		then RemoveObject (M.p5u10);end
		if
			(IsAlive (M.p5u11))
		then RemoveObject (M.p5u11);end
		if
			(IsAlive (M.p5u12))
		then RemoveObject (M.p5u12);end
	end

	if 
		(M.newobjective == true)
	then
		ClearObjectives();


	if
		(
		(M.bugout == true) and (M.missionwon == true)
		)
	then
		AddObjective("misn0606.otf", "GREEN");
		AddObjective("misn0605.otf", "GREEN");
		AddObjective("misn0604.otf", "GREEN");
		--AddObjective("misn0603.otf", "GREEN");
		--AddObjective("misn0602.otf", "GREEN");
		--AddObjective("misn0601.otf", "GREEN");
	end

	if
		(
		(M.bugout == true) and (M.missionwon == false)
		)
	then
		AddObjective("misn0606.otf", "WHITE");
		AddObjective("misn0605.otf", "GREEN");
		AddObjective("misn0604.otf", "GREEN");
		--AddObjective("misn0603.otf", "GREEN");
		--AddObjective("misn0602.otf", "GREEN");
		--AddObjective("misn0601.otf", "GREEN");
	end


	if
		(
		(M.lprecon == true) and (M.bugout == false)
		)
	then
		AddObjective("misn0605.otf", "WHITE");
		AddObjective("misn0604.otf", "GREEN");
		--AddObjective("misn0603.otf", "GREEN");
		--AddObjective("misn0602.otf", "GREEN");
		--AddObjective("misn0601.otf", "GREEN");
	end

	--[[if
		(
		(M.transarrive == true) and (M.lprecon == false)
		)
	then
		AddObjective("misn0607.otf", "WHITE");
		AddObjective("misn0604.otf", "GREEN");
		--AddObjective("misn0603.otf", "GREEN");
		--AddObjective("misn0602.otf", "GREEN");
		--AddObjective("misn0601.otf", "GREEN");
	end--]]





	if
		(
		(M.starportreconed == true) and (M.transarrive == false) and (M.safebreak == false)
		)
	then
		AddObjective("misn0604.otf", "WHITE");
		--AddObjective("misn0603.otf", "GREEN");
		--AddObjective("misn0602.otf", "GREEN");
		--AddObjective("misn0601.otf", "GREEN");
	end


	if
		(
		(M.neworders == true) and (M.starportreconed == false)
		)
	then
		AddObjective("misn0603.otf", "WHITE");
		AddObjective("misn0602.otf", "GREEN");
		AddObjective("misn0601.otf", "GREEN");
	end


	if
		(
		(M.reconheaphestus == true) and (M.neworders == false)
		)
	then
		AddObjective("misn0602.otf", "WHITE");
		AddObjective("misn0601.otf", "GREEN");
	end

	if
		(
		(M.haephestusdisc == true) and (M.reconheaphestus == false) and (M.hephikey == false)
		)
	then
		AddObjective("misn0601.otf", "WHITE");
	end

	if
		(M.fifthplatoon == true)
	then
		AddObjective("misn0600.otf", "WHITE");
	end
	M.newobjective = false;
	end


	
		

	if 
		(
		(M.haephestusdisc == false) and (GetDistance (M.haephestus, M.player) < 1000.0)
		)

	then
		M.aud1 = AudioMessage ("misn0602.wav");
		M.haephestusdisc = true;
		--M.hephdisctime = GetTime() + 60.0;
	end

	if
		(
		(M.loopbreaker == false)  and 
		(M.haephestusdisc == true) and (IsAudioMessageDone(M.aud1))
		)
	then
		SetObjectiveOn (M.haephestus);
		SetObjectiveName (M.haephestus, "Object");
		M.newobjective = true;
		M.loopbreaker = true;
		M.hephdisctime = GetTime() + 60.0;
	end

	if
		(
		(M.haephestusdisc == true) and (M.reconheaphestus == false) and (M.hephikey == false)
		 and  (M.hephdisctime < GetTime())
		)
	then
		if (M.hephwarn < 2)
		then
			M.aud105 = AudioMessage("misn0690.wav");
			M.hephdisctime = GetTime() + 20.0;
			M.hephwarn = M.hephwarn + 1;
		elseif (M.missionfail4 == false)
		then
			M.aud105 = AudioMessage("misn0694.wav");
			M.missionfail4 = true;
		end
	end

	if
		(
		(M.missionfail4 == true) and (IsAudioMessageDone(M.aud105))
		)
	then
		FailMission(GetTime() + 0.0, "misn06l1.des");
	end





	if 
		(
		(M.reconheaphestus == false) and (GetDistance (M.player, M.haephestus) < 125.0)  and 
		(M.hephikey == false)
		)
	then
		StopAudioMessage(M.aud105);
		M.heph1 = AudioMessage ("misn0603.wav");
		M.heph2 = AudioMessage ("misn0604.wav");
		M.reconheaphestus = true;
		SetObjectiveOff (M.haephestus);
		CameraReady ();
		M.cam1time = GetTime() + 12.0;
		M.cam1done = true;
		--M.identtime = GetTime() + 20.0;
	end



	if
		(
		(M.identtime < GetTime()) and (M.hephikey == false)
		 )
	then
		if (M.ident < 2)
		then
			M.aud100 = AudioMessage("misn0691.wav");
			M.ident = M.ident + 1;
			M.identtime = GetTime() + 10.0;
		elseif (M.missionfail == false)
		then
			M.aud100 = AudioMessage("misn0694.wav");
			M.missionfail = true;
		end
	end

	if
		(
		(M.missionfail == true) and (IsAudioMessageDone(M.aud100))
		)
	then
		FailMission(GetTime() + 0.0, "misn06l2.des");
	end


	if
		(
		(IsInfo("obheph") == true) and (M.hephikey == false)
		)
	then
		StopAudioMessage(M.aud100);
		M.processtime = GetTime() + 5.0;
		M.hephikey = true;
		M.reconheaphestus = true;
		SetObjectiveOff (M.haephestus);
		M.newobjective = true;
	end

	if 
		(
		(M.neworders == false) and (M.processtime < GetTime())
		)
	then
		M.aud2 = AudioMessage ("misn0605.wav");
		--AudioMessage ("misn0606.wav");
		--AudioMessage ("misn0607.wav");
		M.fifthplatoon = false;
		M.neworders = true;
		M.buildcam = true;
		M.discstar = GetTime() + 80.0;
	end

	if 
		(
		(M.buildcam == true) and (IsAudioMessageDone(M.aud2))
		)
	then
		SetObjectiveOff (M.rendezvous);
		M.starportcam = BuildObject ("apcamr",1,"cam1spawn");
		SetObjectiveName(M.starportcam, "Starport");
		M.buildcam = false;
		M.newobjective = true;
	end

	if 
		(
		(GetDistance (M.player, M.blockade1) < 420.0) and (M.blockadefound == false)
		)
	then
		AudioMessage ("misn0636.wav");
		M.blockadefound = true;
	end

	if
		(
		(IsInfo("obstp1") == true) and (M.star1recon == false)
		)
	then
		M.star1recon = true;
	end
	if
		(
		(IsInfo("obstp8") == true) and (M.star4recon == false)
		)
	then
		M.star4recon = true;
	end
	if
		(
		(IsInfo("obstp3") == true) and (M.star6recon == false)
		)
	then
		M.star6recon = true;
	end

	if
		(
		(M.fail3 == false) and (M.spfail == 4)
		)
	then
		M.fail3 = true;
		M.aud54 = AudioMessage("misn0694.wav");
	end

	if
		(M.fail3 == true)
	then
		if
			(IsAudioMessageDone(M.aud54))
		then
			FailMission(GetTime()+0.0, "misn06l6.des");
		end
	end

	if
		(
		(M.starportreconed == false) and (M.reconsptime < GetTime()) and 
		(M.fail3 == false) and (M.spfail < 4)
		)
	then
		AudioMessage("misn0654.wav");
		M.reconsptime = GetTime() + 15.0;
		M.spfail = M.spfail + 1;
	end

	if 
		(
		(M.star1recon == true)  and 
		(M.star4recon == true)  and 
		(M.star6recon == true)  and 
		(M.starportreconed == false)
		)
	then
		M.aud3 = AudioMessage ("misn0650.wav");
		M.aud4 = AudioMessage ("misn0606.wav");
		M.aud5 = AudioMessage ("misn0607.wav");
		M.starportreconed = true;
		M.start1 = GetTime () + 15.0;
	end

	if
		(
		(M.star == false)  and 
		(M.starportreconed == true) and (IsAudioMessageDone(M.aud3))  and 
		(IsAudioMessageDone(M.aud4)) and  (IsAudioMessageDone(M.aud5)) 
		
		)
	then
		M.newobjective = true;
		M.star = true;
	end




	if 
		(
		(M.starportdisc == false)  and (GetDistance (M.star8, M.player) < 200.0)
		)
	then
		AudioMessage ("misn0608.wav");
		M.searchtime = GetTime( ) + 15.0;
		M.starportdisc = true;
		M.reconsptime = GetTime() + 20.0;
	end

	if
		(
		(M.neworders == true) and (M.starportdisc == false) and (M.discstar < GetTime())
		 and  (M.stardisc < 3)
		)
	then
		AudioMessage("misn0695.wav");
		M.discstar = GetTime() + 40.0;
		M.stardisc = M.stardisc + 1;
	end

	if
		(
		(M.stardisc == 3) and (M.discstar < GetTime()) and (M.missionfail3 == false)
		)
	then
		M.missionfail3 = true;
		M.aud101 = AudioMessage("misn0694.wav");
	end

	if
		(
		(M.missionfail3 == true) and (IsAudioMessageDone(M.aud101))
		)
	then
		FailMission(GetTime() + 0.0, "misn06l3.des");
	end
	if
		(
		(M.ccaattack == false) and (M.check1 < GetTime())
		)
	then
		M.enemy = GetNearestEnemy(M.wAu1);
		if
			(GetDistance(M.enemy, M.wAu1) < 410.0)
		then
			Attack (M.wAu1, M.enemy);
			Attack (M.wAu2, M.enemy);
			--Attack (M.wAu3, M.enemy);
			SetIndependence(M.wAu2, 1);
			--SetIndependence(M.wAu3, 1);
			M.ccaattack = true;
			M.start1 = GetTime() - 1;
		end
		M.check1 = GetTime() + 1.5;
	end


	if
		(
		(M.starportreconed == true) and (M.ccaattack == false)
		)
	then
		Attack (M.wAu1, M.player);
		Attack (M.wAu2, M.player);
		--Attack (M.wAu3, M.player);
		SetIndependence(M.wAu1, 1);
		SetIndependence(M.wAu2, 1);
		--SetIndependence(M.wAu3, 1);
		M.ccaattack = true;
	end

	if 
		(
		(
		(GetDistance (M.wAu1, "cam1spawn") < 400.0)  or 
		(GetDistance (M.wAu2, "cam1spawn") < 400.0) -- or 
		--(GetDistance (M.wAu3, "cam1spawn") < 400.0)
		) and (M.ccaattack == true) and (M.loopbreak1 == false)
		 and  (M.start1 < GetTime()) and (IsAudioMessageDone(M.aud5))
		)
	then
		M.aud500 = AudioMessage("misn0611.wav");
		CameraReady();
		M.cam3time = GetTime () + 5.0;
		M.cam3done = true;
		M.ccaattack = false;
		M.loopbreak1 = true;
	end

	if
		(M.cam1done == true)
	then
		CameraPath("cam1path", M.cam1hgt, 1000, M.haephestus);
		M.cam1hgt = M.cam1hgt + 15;
	end
	if
		(M.cam1done == true)
		then
		if
		
		(
		
			(
				(IsAudioMessageDone(M.heph1)) and (IsAudioMessageDone(M.heph2))
			)
				 or  (CameraCancelled())
		)
		
			
			then
				CameraFinish();
				M.cam1done = false;
				StopAudioMessage(M.heph1);
				StopAudioMessage(M.heph2);
				M.newobjective = true;

				-- start timer when the cutscene ends
				-- (instead of when it begins)
				M.identtime = GetTime() + 20.0;
			end
		end

	if 
		(M.cam3done == true)
	then
		CameraObject (M.wAu1, 300, 100, -900, M.wAu1);
	end
	if 
		(
		((M.cam3done == true) and (IsAudioMessageDone(M.aud500)))  or 
		(CameraCancelled())
		)
	then
		CameraFinish();
		if ( not M.cam3done) then 
			M.simcam = false;
		end
		M.cam3done = false;
	end
	if
		(M.ccapullout == false)
	then
		IsAlive(M.wAu1);
		IsAlive(M.wAu1);
	end

	if 
		(
		( not IsAlive (M.wAu1)) and ( not IsAlive (M.wAu2)) -- and  ( not IsAlive (M.wAu3))
		 and  (M.ccapullout == false) and (M.starportreconed == true)
		)
	then
		M.aud15 = AudioMessage ("misn0612.wav");
		M.aud16 = AudioMessage ("misn0613.wav");
		M.transportarrive = GetTime () + 50.0;
		M.transarrive = true;
		M.safebreak = true;
		M.ccapullout = true;
		M.wave1 = GetTime() + 60.0;
		M.wave2 = GetTime() + 180.0;
		M.wave3 = GetTime() + 300.0;
	end

	if
		(
		(M.breaker19 == false) and (M.ccapullout == true) and 
		(IsAudioMessageDone(M.aud15))  and 
		(IsAudioMessageDone(M.aud16)) 
		)
	then
		--M.newobjective = true;
		M.breaker19 = true;
	end

	if
		(
		(M.wave1 < GetTime()) and (M.wave1start == false) and (IsAlive (M.svrec))
		)
	then
		M.w1u1 = BuildObject ("svfigh",2, M.svrec);
		M.w1u2 = BuildObject ("svtank",2, M.svrec);
		M.w1u3 = BuildObject ("svfigh",2, M.svrec);
		Attack (M.w1u1, M.avrec);
		Attack (M.w1u2, M.avrec);
		Attack (M.w1u3, M.avrec);
		SetIndependence (M.w1u1, 1);
		SetIndependence (M.w1u2, 1);
		SetIndependence (M.w1u3, 1);
		M.wave1start = true;
	end
	if
		(
		(M.wave2 < GetTime()) and (M.wave2start == false) and (IsAlive (M.svrec))
		)
	then
		M.w2u1 = BuildObject ("svfigh",2, M.svrec);
		M.w2u2 = BuildObject ("svtank",2, M.svrec);
		M.w2u3 = BuildObject ("svfigh",2, M.svrec);
		Attack (M.w2u1, M.avrec);
		Attack (M.w2u2, M.avrec);
		Attack (M.w2u3, M.avrec);
		SetIndependence (M.w2u1, 1);
		SetIndependence (M.w2u2, 1);
		SetIndependence (M.w2u3, 1);
		M.wave2start = true;
	end
	if
		(
		(M.wave3 < GetTime()) and (M.wave3start == false) and (IsAlive (M.svrec))
		)
	then
		M.w3u1 = BuildObject ("svfigh",2, M.svrec);
		M.w3u2 = BuildObject ("svtank",2, M.svrec);
		M.w3u3 = BuildObject ("svfigh",2, M.svrec);
		Attack (M.w3u1, M.avrec);
		Attack (M.w3u2, M.avrec);
		Attack (M.w3u3, M.avrec);
		SetIndependence (M.w3u1, 1);
		SetIndependence (M.w3u2, 1);
		SetIndependence (M.w3u3, 1);
		M.wave3start = true;
	end


		

	if 
		((M.transportarrive < GetTime()) and (M.transarrive == true))

	then
		M.aud6 = AudioMessage ("misn0614.wav");
		M.aud7 = AudioMessage ("misn0628.wav");
		M.lincolndestroyed = GetTime () + 60.0;
		M.oneminstrans = GetTime () + 60.0;
		M.transaway = GetTime () + 90.0;
		M.platoonarrive = GetTime () + 1410.0;
		M.threeminsplatoon = GetTime () + 390.0;
		M.tenminsplatoon = GetTime () + 810.0;
		M.fiveminsplatoon = GetTime () + 1110.0;
		M.twominsplatoon = GetTime () + 1260.0;
		M.transarrive = false;
		M.touchdown = true;
		M.threemin = true;
		M.tenmin = true;
		M.fivemin = true;
		M.twomin = true;
		M.platoonhere = true;
		M.newobjective = true;
		M.timerstart = GetTime() + 27.42;
		M.lincolndes = true;
	end

	--[[if 
		(
		(M.lincolndestroyed < GetTime()) and (M.lincolndes == false)
		)
	then
		M.aud8 = AudioMessage ("misn0626.wav");
		M.aud9 = AudioMessage ("misn0628.wav");
		M.lincolndes = true;
	end--]]

	if
		(
		(M.lprecon == false) and (M.lincolndes == true)
		)
	then
		if
			(
			(IsAudioMessageDone(M.aud6)) and (IsAudioMessageDone(M.aud7))
			)
		then
			M.lprecon = true;
			StartCockpitTimer(540, 360, 180);
			SetObjectiveOn(M.launchpad);
			M.newobjective = true;
		end
	end



	if 
		(
		(M.threeminsplatoon < GetTime ()) and 
		(M.threemin == true) and 
		(M.launchpadreconed == false)
		)
	then
		M.bogey = GetNearestEnemy(M.player);
		if
			(GetDistance(M.bogey, M.player) > 400.0)
		then

		M.sim1 = BuildObject("avtank", 3, "M.sim1");
		M.sim2 = BuildObject("avtank", 3, "M.sim2");
		M.sim3 = BuildObject("avtank", 3, "M.sim3");
		M.sim4 = BuildObject("avtank", 3, "M.sim4");
		M.sim5 = BuildObject("avtank", 3, "M.sim5");
		M.sim6 = BuildObject("avfigh", 3, "M.sim6");
		M.sim7 = BuildObject("avfigh", 3, "M.sim7");
		M.sim8 = BuildObject("avfigh", 3, "M.sim8");
		M.sim9 = BuildObject("avfigh", 3, "M.sim9");
		M.sim10 = BuildObject("avfigh", 3, "M.sim10");
		--[[
			Jens
			this cineractive now
			works except that there is
			no path point called
			sim5spot
			So they don't move.
		--]]
		Goto(M.sim1, "simpoint5");
		Goto(M.sim2, "simpoint5");
		Goto(M.sim3, "simpoint5");
		Goto(M.sim4, "simpoint5");
		Goto(M.sim5, "simpoint5");
		Goto(M.sim6, "simpoint5");
		Goto(M.sim7, "simpoint5");
		Goto(M.sim8, "simpoint5");
		Goto(M.sim9, "simpoint5");
		Goto(M.sim10, "simpoint5");
		CameraReady();
		M.simaud1 = AudioMessage ("misn0631.wav");
		M.simaud2 = AudioMessage ("misn0642.wav");
		M.simaud3 = AudioMessage ("misn0643.wav");
		M.simaud4 = AudioMessage ("misn0644.wav");
		M.simaud5 = AudioMessage ("misn0645.wav");
		M.simcam = true;
		M.threemin = false;
		HideCockpitTimer();
		end

	end

	if
		(M.simcam == true)
	then
		CameraObject(M.sim5, 0, 1000, -4000, M.sim5);
		if
		(
		(M.attack == false) and (IsAudioMessageDone(M.simaud4))
		)
	then
		Goto(M.sim1, "simpoint1");
		Goto(M.sim2, "simpoint1");
		Goto(M.sim4, "simpoint1");
		Goto(M.sim7, "simpoint1");
		Goto(M.sim3, "simpoint3");
		Goto(M.sim6, "simpoint3");
		Goto(M.sim10, "simpoint3");
		Goto(M.sim5, "simpoint5");
		Goto(M.sim8, "simpoint5");
		Goto(M.sim9, "simpoint5");
		M.attack = true;
	end

	end

	if
		(
		(M.simcam == true) and (M.breakout1 == false)
		)
	then
		if (IsAudioMessageDone(M.simaud1)) then M.doneaud1 = true; end
		if (IsAudioMessageDone(M.simaud2)) then M.doneaud2 = true; end
		if (IsAudioMessageDone(M.simaud3)) then M.doneaud3 = true; end
		if (IsAudioMessageDone(M.simaud4)) then M.doneaud4 = true; end
		if (IsAudioMessageDone(M.simaud5)) then M.doneaud5 = true; end
		if
			(
				(
				(M.doneaud1)  and 
				(M.doneaud2)  and 
				(M.doneaud3)  and 
				(M.doneaud4)  and 
				(M.doneaud5)
				)   or  
				(CameraCancelled())
			)
		then
			CameraFinish();
			M.breakout1 = true;
			M.simcam = false;
			StopAudioMessage(M.simaud1);
			StopAudioMessage(M.simaud2);
			StopAudioMessage(M.simaud3);
			StopAudioMessage(M.simaud4);
			StopAudioMessage(M.simaud5);
		end
	end
	-- this used to be breakout  = , changed it to == so cineractive wouldn't last eternity
	if
		(
		(M.breakout1 ==  true) and (M.removal == false)
		)
	then
		RemoveObject(M.sim1);
		RemoveObject(M.sim2);
		RemoveObject(M.sim3);
		RemoveObject(M.sim4);
		RemoveObject(M.sim5);
		RemoveObject(M.sim6);
		RemoveObject(M.sim7);
		RemoveObject(M.sim8);
		RemoveObject(M.sim9);
		RemoveObject(M.sim10);
		M.removal = true;
		StopCockpitTimer();
		HideCockpitTimer();
	end

	



	--[[if
		(
		(M.removal == true) and (M.timergone == false)
		)
	then
		StopCockpitTimer();
		M.timergone = true;
	end--]]

	if
		(
		(M.tenminsplatoon < GetTime ()) and 
		(M.tenmin == true) and 
		(M.launchpadreconed == false) and (M.reminder == false)
		)
	then
		AudioMessage ("misn0632.wav");
		M.tenmin = false;
	end

	if
		(
		(M.fiveminsplatoon < GetTime ()) and 
		(M.fivemin == true)  and 
		(M.launchpadreconed == false) and (M.reminder == false)
		)
	then
		AudioMessage ("misn0633.wav");
		M.fivemin = false;
	end

	if
		(
		(M.twominsplatoon < GetTime ()) and 
		(M.twomin == true)  and 
		(M.launchpadreconed == false) and (M.reminder == false)
		)
	then
		AudioMessage ("misn0634.wav");
		M.twomin = false;
	end

	if
		(
		(GetDistance (M.player, M.svrec) < 250.0) and 
		(M.reminder == false) and (M.launchpadreconed == false)
		)
	then
		AudioMessage ("misn0638.wav");
		M.reminder = true;
		M.endtime = GetTime() + 120.0;
	end

	if
		(
		(M.reminder == true) and (GetDistance(M.player, M.launchpad) > 400.0)  and 
		(M.launchpadreconed == false) and (M.endtime < GetTime()) and (M.breaker == false)
		)
	then
		M.aud102 = AudioMessage ("misn0635.wav");
		M.aud103 = AudioMessage ("misn0646.wav");
		M.aud104 = AudioMessage ("misn0651.wav");
		M.platoonhere = false;
		M.endme = true;
		M.breaker = true;
	end

	if
		(
		(IsInfo("sblpad") == true)   and 
		(M.launchpadreconed == false)
		)
	then
		M.time1 = GetTime() + 2.0;
		M.bugout = true;
		M.launchpadreconed = true;
		HideCockpitTimer();
		SetObjectiveOff(M.launchpad);
		--M.newobjective = true;
	end

	if
		(
		(M.bugout == true) and  
		(M.corbettalive == true) and (M.time1 < GetTime())  and 
		(M.threemin == true) and (M.bustout == false)
		)
	then
		AudioMessage ("misn0629.wav");
		AudioMessage ("misn0630.wav");
		AudioMessage ("misn0647.wav");
		M.ccap1 = BuildObject ("svfigh",2,"ccaplatoonspawn");
		Attack (M.ccap1, M.avrec);
		SetIndependence (M.ccap1, 1);
		--M.bugout = false;
		M.platoonhere = false;
		M.pickupset = true;
		M.platoonarrive = 999999999999.0;
		M.twominsplatoon = 999999999999.0;
		M.tenminsplatoon = 999999999999.0;
		M.fiveminsplatoon = 999999999999.0;
		M.newobjective = true;
		M.bustout = true;
	end

	if
		(
		(M.bugout == true) and  
		(M.corbettalive == true) and (M.time1 < GetTime())  and 
		(M.threemin == false) and (M.bustout == false)
		)
	then
		AudioMessage ("misn0629.wav");
		AudioMessage ("misn0630.wav");
		--AudioMessage ("misn0647.wav");
		M.ccap1 = BuildObject ("svfigh",2,"ccaplatoonspawn");
		Attack (M.ccap1, M.avrec);
		SetIndependence (M.ccap1, 1);
		--M.bugout = false;
		M.platoonhere = false;
		M.pickupset = true;
		M.platoonarrive = 999999999999.0;
		M.twominsplatoon = 999999999999.0;
		M.tenminsplatoon = 999999999999.0;
		M.fiveminsplatoon = 999999999999.0;
		M.newobjective = true;
		M.bustout = true;
	end
	if
		(
		(M.breakme == false) and (M.bugout == true) and  
		(M.corbettalive == false) and (M.time1 < GetTime())
		)
	then
		AudioMessage ("misn0629.wav");
		AudioMessage ("misn0630.wav");
		SetIndependence (M.ccap1, 1);
		M.platoonhere = false;
		M.breakme = true;
		M.pickupset = true;
		M.platoonarrive = 999999999999.0;
		M.twominsplatoon = 999999999999.0;
		M.tenminsplatoon = 999999999999.0;
		M.fiveminsplatoon = 999999999999.0;
		M.newobjective = true;
		M.deathtime = GetTime() + 30.0;
	end

	if
		(
		(M.deathtime < GetTime()) and (M.death == false)
		)
	then
		M.death = true;
		M.deathtime = 99999999999999.0;
		AudioMessage ("misn0635.wav");
		M.ccap1 = BuildObject ("svfigh",2,"ccaplatoonspawn");
		Attack (M.ccap1, M.avrec);
	end

	if
		(M.pickupset == true) 
	then
	--	switch (extractpoint)
		if extractpoint == 0 then
	--	case 0:
			M.dustoffcam = BuildObject ("apcamr", 1, "bugout1");
		elseif extractpoint == 1 then
	--		break;
	--	case 1:
			M.dustoffcam = BuildObject ("apcamr", 1, "bugout2");
		elseif extractpoint == 2 then
	--		break;
	--	case 2:
			M.dustoffcam = BuildObject ("apcamr", 1, "bugout3");
		elseif extractpoint == 3 then
	--		break;
	--	case 3:
			M.dustoffcam = BuildObject ("apcamr", 1, "bugout4");
	--	break;
		end
		SetObjectiveName(M.dustoffcam, "Dust Off");
		M.pickupset = false;
		M.pickupreached = true;
		SetObjectiveOff(M.launchpad);
	end

	if
		(
		(M.bustout == true) and ( not IsAlive(M.dustoffcam))
		)
	then
		M.pickupset = true;
	end

	if
		(
		(GetDistance (M.avrec, M.dustoffcam) < 100.0) and 
		(GetDistance (M.player, M.dustoffcam) < 100.0)  and 
		(M.pickupreached == true)
		)
	then
		AudioMessage ("misn0649.wav");
		SucceedMission (GetTime() + 5.0, "misn06w1.des");
		M.pickupreached = false;
		M.dustoff = true;
		M.newobjective = true;
	end


	if
		(
		(M.platoonarrive <  GetTime()) and (M.platoonhere == true)
		 and  (M.reminder == true) and (M.time1 < GetTime())
		)
	then
		AudioMessage ("misn0635.wav");
		AudioMessage ("misn0648.wav");
		M.ccap1 = BuildObject ("svfigh",2,"ccaplatoonspawn");
		Attack (M.ccap1, M.avrec);
		SetIndependence (M.ccap1, 1);
		M.platoonhere = false;
		M.twominsplatoon = 999999999999.0;
		M.corbettalive = false;
	end

	if
		(IsAlive(M.ccap1))
	then
		M.spawnme = GetNearestEnemy(M.ccap1);
	end

	if
		(
		(GetDistance(M.ccap1, M.spawnme) < 410) and (M.economyccaplatoon == false)
		)
	then
		M.ccap2 = BuildObject ("svfigh",2,M.ccap1);
		M.ccap3 = BuildObject ("svfigh",2,M.ccap1);
		M.ccap4 = BuildObject ("svfigh",2,M.ccap1);
		M.ccap5 = BuildObject ("svfigh",2,M.ccap1);
		M.ccap6 = BuildObject ("svtank",2,M.ccap1);
		M.ccap7 = BuildObject ("svtank",2,M.ccap1);
		M.ccap8 = BuildObject ("svtank",2,M.ccap1);
		M.ccap9 = BuildObject ("svtank",2,M.ccap1);
		--M.ccap10 = BuildObject ("svtank",2,M.ccap1);
		--M.ccap11 = BuildObject ("svtank",2,M.ccap1);
		--M.ccap12 = BuildObject ("svturr",2,M.ccap1);
		--M.ccap13 = BuildObject ("svturr",2,M.ccap1);
		--M.ccap14 = BuildObject ("svartl",2,M.ccap1);
		--M.ccap15 = BuildObject ("svartl",2,M.ccap1);
		Attack (M.ccap2, M.avrec);
		Attack (M.ccap3, M.avrec);
		Attack (M.ccap4, M.avrec);
		Attack (M.ccap5, M.avrec);
		Attack (M.ccap6, M.avrec);
		Attack (M.ccap7, M.avrec);
		Attack (M.ccap8, M.avrec);
		Attack (M.ccap9, M.avrec);
		--Attack (M.ccap10, M.avrec);
		--Attack (M.ccap11, M.avrec);
		--Attack (M.ccap12, M.avrec);
		--Attack (M.ccap13, M.avrec);
		--Attack (M.ccap14, M.avrec);
		--Attack (M.ccap15, M.avrec);
		SetIndependence (M.ccap2, 1);
		SetIndependence (M.ccap3, 1);
		SetIndependence (M.ccap4, 1);
		SetIndependence (M.ccap5, 1);
		SetIndependence (M.ccap6, 1);
		SetIndependence (M.ccap7, 1);
		SetIndependence (M.ccap8, 1);
		SetIndependence (M.ccap9, 1);
		--SetIndependence (M.ccap10, 1);
		--SetIndependence (M.ccap11, 1);
		--SetIndependence (M.ccap12, 1);
		--SetIndependence (M.ccap13, 1);
		--SetIndependence (M.ccap14, 1);
		--SetIndependence (M.ccap15, 1);
		M.economyccaplatoon = true;
	end

	--[[
		Jens M.platoonarrive is a floating point number.
		Here you test to see if it is 'true', like a boolean.
		This will compile but probably never evaluate
		correctly.  
		For arcane reasons M.platoonarrive is probaly 'true'
		50 % of the time, completely at random unless you 
		set it to zero somewhere, which will make it false.
	--]]

	if
		(
		(M.platoonhere == true) and (M.respawn == false)
		)
	then
		if
			(
			( not IsAlive(M.ccap1))  and 
			( not IsAlive(M.ccap2))  and 
			( not IsAlive(M.ccap3))  and 
			( not IsAlive(M.ccap4))  and 
			( not IsAlive(M.ccap5))  and 
			( not IsAlive(M.ccap6))  and 
			( not IsAlive(M.ccap7))  and 
			( not IsAlive(M.ccap8))  and 
			( not IsAlive(M.ccap9))
			)
		then
			M.ccap1 = BuildObject("svfigh", 2, "ccaplatoonspawn");
			M.respawn = true;
			M.economyccaplatoon = false;
		end
	end


	if
		(
		(M.twominsplatoon < GetTime()) and (M.corbettalive == true)
		)
	then
		M.corbettalive = false;
	end


	if
		(
		(M.platoonarrive < GetTime ()) and (M.platoonhere == true)
		 and  (M.reminder == false)
		)
	then
		M.aud102 = AudioMessage ("misn0635.wav");
		M.aud103 = AudioMessage ("misn0646.wav");
		M.aud104 = AudioMessage ("misn0651.wav");
		M.platoonhere = false;
		M.endme = true;
	end

	if
		(
		(M.endme == true) and (IsAudioMessageDone(M.aud102))  and 
		(IsAudioMessageDone(M.aud103))  and 
		(IsAudioMessageDone(M.aud104)) 
		)
	then
		FailMission(GetTime() + 0.0, "misn06l4.des");
	end

	-- added to fix crash if M.player died during camera scene
	if ( ( not IsAlive(M.player)) and (IsOdf(M.player, "asuser")) )
	then
		FailMission(GetTime() + 5.0);
	end

-- END OF SCRIPT
	
end