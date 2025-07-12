-- Single Player NSDF Mission 3 Lua conversion, created by General BlackDragon. 

-- Single Table for all our save/load variables. This SP mission has too many variables to function with them independently. ("main function has > 200 local variables", or "Load having > 197 variables in assignment")
local M = {

-- bools
	missionstart = false,
	basesecure = false,
	relicsecure = false,
	--ob1 = false,
	--ob2 = false,
	--ob3 = false,
	--ob4 = false,
	--ob5 = false,
	--ob6 = false,
	--ob7 = false,
	--ob8 = false,
	missionfail2 = false,
	done = false,
	--firstwave = false,
	found = false,
	ccahasrelic = false,
	build2 = false,
	build3 = false,
	build4 = false,
	build5 = false,
	--secondwave = false,
	doneaud20 = false,
	doneaud21 = false,
	doneaud22 = false,
	doneaud23 = false,
	--thirdwave = false,
	--fourthwave = false,
	secureloopbreak = false,
	chewedout = false,
	--fifthwave = false,
	possiblewin = false,
	attackccabase = false,
	endmission = false,
	--fifthwavedestroyed = false,
	--ccabasedestroyed = false,
	surveysent = false,
	reconsent = false,
	--discrelic = false,
	--missionend = false,
	loopbreak = false,
	loopbreak2 = false,
	halfway = false,
	ccatugsent = false,
	cin1done = false,
	wave1arrive = false,
	wave2arrive = false,
	wave3arrive = false,
	wave4arrive = false,
	wave5arrive = false,
	obset = false,
	discoverrelic = false,
	newobjective = false,
	relicmoved = false,
	cheater = false,
	relicseen = false,
	retreat = false,
	missionwon = false,
	missionfail = false,
	wave1dead = false,
	wave2dead = false,
	wave3dead = false,
	wave4dead = false,
	wave5dead = false,
	--endcinfinish = false,
	tur1sent = false,
	tur2sent = false,
	tur3sent = false,
	tur4sent = false,
-- Floats (really doubles in Lua)
	wave1 = 0,
	wave2 = 0,
	wave3 = 0,
	wave4 = 0,
	wave5 = 0,
	fetch = 0,
	reconcca = 0,
	--startendcin = 0,
	--endcindone = 0,
	notfound = 0,
	ccatug = 0,
	cintime1 = 0,
	tur1 = 0,
	tur2 = 0,
	tur3 = 0,
	tur4 = 0,
	investigate = 0,
-- Handles
	svrec = nil,
	pu1 = nil,
	pu2 = nil,
	pu3 = nil,
	pu4 = nil,
	pu5 = nil,
	pu6 = nil,
	pu7 = nil,
	pu8 = nil,
	--navbeacon = nil,
	cheat1 = nil,
	cheat2 = nil,
	cheat3 = nil,
	cheat4 = nil,
	cheat5 = nil,
	cheat6 = nil,
	cheat7 = nil,
	cheat8 = nil,
	cheat9 = nil,
	cheat10 = nil,
	tug = nil,
	svtug = nil,
	tuge1 = nil,
	tuge2 = nil,
	player = nil,
	surv1 = nil,
	surv2 = nil,
	surv3 = nil,
	surv4 = nil,
	cam1 = nil,
	cam2 = nil,
	cam3 = nil,
	basecam = nil,
	reliccam = nil,
	avrec = nil,
	w1u1 = nil,
	w1u2 = nil,
	safety = nil,
	w2u1 = nil,
	w2u2 = nil,
	w2u3 = nil,
	w3u1 = nil,
	w3u2 = nil,
	w3u3 = nil,
	w3u4 = nil,
	w4u1 = nil,
	w4u2 = nil,
	w4u3 = nil,
	w4u4 = nil,
	w4u5 = nil,
	w5u1 = nil,
	w5u2 = nil,
	w5u3 = nil,
	w5u4 = nil,
	w5u5 = nil,
	w5u6 = nil,
	spawn1 = nil,
	spawn2 = nil,
	spawn3 = nil,
	relic = nil,
	calipso = nil,
	turret1 = nil,
	turret2 = nil,
	turret3 = nil,
	turret4 = nil,
-- Ints
	--height = 0,
	relicstartpos = 0,
	wavenumber = 0,
	investigator = 0,
	warn = 0,
	--aud1 = 0,
	aud2 = 0,
	aud3 = 0,
	aud4 = 0,
	aud10 = 0,
	aud11 = 0,
	aud12 = 0,
	aud13 = 0,
	aud14 = 0,
	aud20 = 0,
	aud21 = 0,
	aud22 = 0,
	aud23 = 0
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

	M.wavenumber = 1;
	SetScrap (1, 20);
	
	M.wave2 = 99999.0;
	M.wave3 = 99999.0;
	M.wave4 = 99999.0;
	M.wave5 = 99999.0;
	--M.endcindone = 999999.0;
	--M.startendcin = 999999.0;
	M.ccatug = 999999999999.0;
	M.notfound = 999999999999999.0;
	M.investigate = 999999999.0;
	M.tur1 = 999999999.0;
	M.tur2 = 999999999.0;
	M.tur3 = 999999999.0;
	M.tur4 = 999999999.0;
	--M.height = 500;
	M.cintime1 = 9999999999.0;

end

function AddObject(h)

	if (
		(GetTeamNum(h) == 1)  and 
		(IsOdf(h, "avhaul"))
		)
	then
		M.found = true;
		M.tug = h;
	end

end

function Update()

-- START OF SCRIPT

	-- get this every frame in case the user changes vehicles
	M.player = GetPlayerHandle();

	if
		(M.missionstart == false)
	then
		M.wave1 = GetTime( ) + 30.0;
		M.fetch = GetTime( ) + 240.0;--change to 350.0
		AudioMessage ("misn0401.wav");
		M.cam1 = GetHandle("apcamr352_camerapod");
		M.cam2 = GetHandle("apcamr350_camerapod");
		M.cam3 = GetHandle("apcamr351_camerapod");
		M.basecam = GetHandle("apcamr-1_camerapod");
		M.svrec = GetHandle("svrecy-1_recycler");
		M.avrec = GetHandle("avrecy-1_recycler");
		M.relic = BuildObject("obdata", 0, "relicstart1");
		M.pu1 = GetHandle("svfigh-1_wingman");
		--M.pu2 = GetHandle("svfigh281_wingman");
		M.pu3 = GetHandle("svfigh282_wingman");
		--M.pu4 = GetHandle("svfigh280_wingman");
		--M.pu5 = GetHandle("svfigh276_wingman");
		M.pu6 = GetHandle("svfigh279_wingman");
		--M.pu7 = GetHandle("svfigh277_wingman");
		M.pu8 = GetHandle("svfigh278_wingman");
		SetObjectiveName(M.cam1, "SW Geyser");
		SetObjectiveName(M.cam2, "NW Geyser");
		SetObjectiveName(M.cam3, "NE Geyser");
		SetObjectiveName(M.basecam, "CCA Base");
		Patrol (M.pu1, "innerpatrol");
		--Patrol (M.pu2, "innerpatrol");
		Patrol (M.pu3, "innerpatrol");
		--Patrol (M.pu4, "innerpatrol");
		--Patrol (M.pu5, "outerpatrol");
		Patrol (M.pu6, "outerpatrol");
		--Patrol (M.pu7, "scouting");
		Patrol (M.pu8, "scouting");
		AddObjective ("misn0401.otf", "WHITE");
		AddObjective ("misn0400.otf", "WHITE");
		M.missionstart = true;
		M.cheater = false;
		M.relicstartpos = math.random(0, 3); --rand() % 4;
		M.tur1 = GetTime() + 30.0;
		M.tur2 = GetTime() + 45.0;
		M.tur3 = GetTime() + 60.0;
		M.tur4 = GetTime() + 75.0;
		M.investigate = GetTime () + 3.0;
		end
	M.player = GetPlayerHandle();
	
	if
		(IsAlive(M.cam1))
	then
		AddHealth(M.cam1, 100.0);
	end
	if
		(IsAlive(M.cam2))
	then
		AddHealth(M.cam2, 100.0);
	end
	if
		(IsAlive(M.cam3))
	then
		AddHealth(M.cam3, 100.0);
	end

	if
		(M.relicmoved == false)
	then
		if M.relicstartpos == 0 then
			SetPosition (M.relic, "relicstart1");
		elseif M.relicstartpos == 1 then
			SetPosition (M.relic, "relicstart2");
		elseif M.relicstartpos == 2 then
			SetPosition (M.relic, "relicstart3");
		elseif M.relicstartpos == 3 then
			SetPosition (M.relic, "relicstart4");
		end
		M.relicmoved = true;
	end

	if
		(
		(M.reconsent == false) and 
		(M.cheater == false)  and 
		(GetDistance (M.player, M.relic) < 600.0)
		)
	then
			M.cheat1 = BuildObject ("svfigh",2,M.relic);
			M.cheat2 = BuildObject ("svfigh",2,M.relic);
			M.cheat3 = BuildObject ("svfigh",2,M.relic);
			M.cheat4 = BuildObject ("svfigh",2,M.relic);
			M.cheat5 = BuildObject ("svfigh",2,M.relic);
			M.cheat6 = BuildObject ("svfigh",2,M.relic);
			if
				(M.relicstartpos == 0)
			then
				Patrol(M.cheat1, "relicpatrolpath1a");
				Patrol(M.cheat2, "relicpatrolpath1a");
				Patrol(M.cheat3, "relicpatrolpath1a");
				Patrol(M.cheat4, "relicpatrolpath1b");
				Patrol(M.cheat5, "relicpatrolpath1b");
				Patrol(M.cheat6, "relicpatrolpath1b");
				SetIndependence(M.cheat1, 1);
				SetIndependence(M.cheat2, 1);
				SetIndependence(M.cheat3, 1);
				SetIndependence(M.cheat4, 1);
				SetIndependence(M.cheat5, 1);
				SetIndependence(M.cheat6, 1);
			end
			if
				(M.relicstartpos == 1)
			then
				Patrol(M.cheat1, "relicpatrolpath2a");
				Patrol(M.cheat2, "relicpatrolpath2a");
				Patrol(M.cheat3, "relicpatrolpath2a");
				Patrol(M.cheat4, "relicpatrolpath2b");
				Patrol(M.cheat5, "relicpatrolpath2b");
				Patrol(M.cheat6, "relicpatrolpath2b");
				SetIndependence(M.cheat1, 1);
				SetIndependence(M.cheat2, 1);
				SetIndependence(M.cheat3, 1);
				SetIndependence(M.cheat4, 1);
				SetIndependence(M.cheat5, 1);
				SetIndependence(M.cheat6, 1);
			end
			if
				(M.relicstartpos == 2)
			then
				Patrol(M.cheat1, "relicpatrolpath3a");
				Patrol(M.cheat2, "relicpatrolpath3a");
				Patrol(M.cheat3, "relicpatrolpath3a");
				Patrol(M.cheat4, "relicpatrolpath3b");
				Patrol(M.cheat5, "relicpatrolpath3b");
				Patrol(M.cheat6, "relicpatrolpath3b");
				SetIndependence(M.cheat1, 1);
				SetIndependence(M.cheat2, 1);
				SetIndependence(M.cheat3, 1);
				SetIndependence(M.cheat4, 1);
				SetIndependence(M.cheat5, 1);
				SetIndependence(M.cheat6, 1);
			end
			if
				(M.relicstartpos == 3)
			then
				Patrol(M.cheat1, "relicpatrolpath4a");
				Patrol(M.cheat2, "relicpatrolpath4a");
				Patrol(M.cheat3, "relicpatrolpath4a");
				Patrol(M.cheat4, "relicpatrolpath4b");
				Patrol(M.cheat5, "relicpatrolpath4b");
				Patrol(M.cheat6, "relicpatrolpath4b");
				SetIndependence(M.cheat1, 1);
				SetIndependence(M.cheat2, 1);
				SetIndependence(M.cheat3, 1);
				SetIndependence(M.cheat4, 1);
				SetIndependence(M.cheat5, 1);
				SetIndependence(M.cheat6, 1);
			end
			--M.cheat7 = BuildObject ("svfigh",2,M.relic);
			--M.cheat8 = BuildObject ("svfigh",2,M.relic);
			--M.cheat9 = BuildObject ("svfigh",2,M.relic);
			--M.cheat10 = BuildObject ("svfigh",2,M.relic);
			M.surveysent = true;
			M.cheater = true;
			M.reconcca = GetTime();
	end

	
	--[[if 
		
		(M.discoverrelic == false)
	then	
		M.calipso = GetNearestVehicle (M.relic);
		GetTeamNum (M.calipso);
			if
				(
					(GetTeamNum (M.calipso) == 1) and 
					(GetDistance (M.relic, M.calipso) < =  500.0)  and 
					(M.calipso ~= M.player)
				)
					then
						AudioMessage ("misn0407.wav");
						M.discoverrelic = true;
						M.newobjective = true;
						M.reconsent = false;
						SetObjectiveOn (M.relic);
						SetObjectiveName (M.relic, "OBJECT");
					end
	end--]]

	if
		(
		(M.fetch < GetTime ()) and (M.surveysent == false)
		)
	then
		M.surv1 = BuildObject ("svfigh",2,M.relic);
		M.surv2 = BuildObject ("svfigh",2,M.relic);
		--M.surv3 = BuildObject ("svfigh",2,M.relic);
		--M.surv4 = BuildObject ("svfigh",2,M.relic);
		if
			(M.relicstartpos == 0)
		then
			Patrol(M.surv1, "relicpatrolpath1a");
			Patrol(M.surv2, "relicpatrolpath1b");
			SetIndependence(M.surv1, 1);
			SetIndependence(M.surv2, 1);
		end
		if
			(M.relicstartpos == 1)
		then
			Patrol(M.surv1, "relicpatrolpath2a");
			Patrol(M.surv2, "relicpatrolpath2b");
			SetIndependence(M.surv1, 1);
			SetIndependence(M.surv2, 1);
		end
		if
			(M.relicstartpos == 2)
		then
			Patrol(M.surv1, "relicpatrolpath3a");
			Patrol(M.surv2, "relicpatrolpath3b");
			SetIndependence(M.surv1, 1);
			SetIndependence(M.surv2, 1);
		end
		if
			(M.relicstartpos == 3)
		then
			Patrol(M.surv1, "relicpatrolpath4a");
			Patrol(M.surv2, "relicpatrolpath4b");
			SetIndependence(M.surv1, 1);
			SetIndependence(M.surv2, 1);
		end
		--Goto(M.surv3, M.relic);
		--Goto(M.surv4, M.relic);
		M.surveysent = true;
		--M.newobjective = true;
		M.reconcca = GetTime () + 60;
	end

	if
		(
		(M.tur1sent == false) and (M.tur1 < GetTime()) and (IsAlive(M.svrec))
		)
	then
		M.turret1 = BuildObject ("svturr", 2, M.svrec);
		Goto (M.turret1, "turret1");
		M.tur1sent = true;
	end
	if
		(
		(M.tur2sent == false) and (M.tur2 < GetTime()) and (IsAlive(M.svrec))
		)
	then
		M.turret2 = BuildObject ("svturr", 2, M.svrec);
		Goto (M.turret2, "turret2");
		M.tur2sent = true;
	end
	if
		(
		(M.tur3sent == false) and (M.tur3 < GetTime()) and (IsAlive(M.svrec))
		)
	then
		M.turret3 = BuildObject ("svturr", 2, M.svrec);
		Goto (M.turret3, "turret3");
		M.tur3sent = true;
	end
	if
		(
		(M.tur4sent == false) and (M.tur4 < GetTime()) and (IsAlive(M.svrec))
		)
	then
		M.turret4 = BuildObject ("svturr", 2, M.svrec);
		Goto (M.turret4, "turret4");
		M.tur4sent = true;
	end

	if 
		(
		(M.reconcca < GetTime ()) and (M.reconsent == false) and (M.surveysent == true)
		
		
		)
	then
		M.aud4 = AudioMessage ("misn0406.wav");
		M.reliccam = BuildObject ("apcamr", 1, ("reliccam%d"):format(M.relicstartpos + 1));
	--[[	-- Ugly code made simplier by Mario. -GBD
	--	switch (M.relicstartpos)
	--	then
	--	case 0:
		if M.relicstartpos == 0 then
			M.reliccam = BuildObject ("apcamr",1,"reliccam1");
	--		break;
		elseif M.relicstartpos == 1 then
	--	case 1:
			M.reliccam = BuildObject ("apcamr",1,"reliccam2");
	--		break;
		elseif M.relicstartpos == 2 then
	--	case 2:
			M.reliccam = BuildObject ("apcamr",1,"reliccam3");
	--		break;
		elseif M.relicstartpos == 3 then
	--	case 3:
			M.reliccam = BuildObject ("apcamr",1,"reliccam4");
	--		break;
		end
		--]]
		
		
		M.reconsent = true;
		M.obset = true;
		M.notfound = GetTime() + 90.0;
	end

	if
		(
		(M.obset == true) and (IsAudioMessageDone(M.aud4)) 
		)
	then
		SetObjectiveName(M.reliccam, "Investigate CCA");
		M.newobjective = true;
		M.obset = false;
	end


	if 
		(
		(M.found == true) and (M.halfway == false)
		)
	then
		if
		(HasCargo(M.tug))
			then
				AudioMessage ("misn0419.wav");
				M.halfway = true;
				SetObjectiveOff (M.relic);
				if
					(IsAlive(M.tuge1))
				then
					Attack(M.tuge1, M.tug);
				end
				if
					(IsAlive(M.tuge2))
				then
					Attack(M.tuge2, M.tug);
				end
			end
	end

	if 
		(M.reconsent == true)
	then
		if
		(
		(GetDistance (M.relic, M.avrec) < 100.0) and (M.relicsecure == false)
		)

		then
			M.aud23 = AudioMessage ("misn0420.wav");
			M.relicsecure = true;
			M.newobjective = true;
		end
	end

	if 
		(
		(M.ccatug < GetTime()) and (M.ccatugsent == false) and (IsAlive(M.svrec))
		)
	then
		M.svtug = BuildObject ("svhaul", 2, M.svrec);
		M.tuge1 = BuildObject ("svfigh", 2, M.svrec);
		M.tuge2 = BuildObject ("svfigh", 2, M.svrec);
		Pickup (M.svtug, M.relic);
		Follow (M.tuge1, M.svtug);
		Follow (M.tuge2, M.svtug);
		M.ccatugsent = true;
	end

	if
		(
		(M.ccatugsent == true) and (M.ccahasrelic == false)
		)
	then
		if
			
			(IsAlive(M.svtug))
		then
			if
				(
				(HasCargo(M.svtug)) and ( not HasCargo(M.tug))
				)
		then
			M.ccahasrelic = true;
			Goto (M.svtug, "dropoff");
			AudioMessage ("misn0427.wav");
			SetObjectiveOn(M.svtug);
			SetObjectiveName(M.svtug, "CCA Tug");
		end
		end
	end

	
	if
		(
		(M.ccahasrelic == true) and (GetDistance(M.svtug, M.svrec) < 60.0)  and 
		(M.missionfail2 == false)
		)
	then
		M.aud10 = AudioMessage("misn0431.wav");
		M.aud11 = AudioMessage("misn0432.wav");
		M.aud12 = AudioMessage("misn0433.wav");
		M.aud13 = AudioMessage("misn0434.wav");
		M.missionfail2 = true;
		CameraReady();
	end

	if
		(
		(M.missionfail2 == true) and (M.done == false)
		)
	then
		CameraPath("ccareliccam", 3000, 1000, M.svtug);
		if
			(
			(
			(IsAudioMessageDone(M.aud10)) and 
			(IsAudioMessageDone(M.aud11)) and 
			(IsAudioMessageDone(M.aud12)) and 
			(IsAudioMessageDone(M.aud13))
			)  or  CameraCancelled()
			)
		then
			CameraFinish();
			StopAudioMessage(M.aud10);
			StopAudioMessage(M.aud11);
			StopAudioMessage(M.aud12);
			StopAudioMessage(M.aud13);
			FailMission(GetTime(), "misn04l1.des");
			M.done = true;
		end
	end

	if

		(
		(M.discoverrelic == false) and (M.reconsent == true)
		 and  (M.notfound < GetTime()) and (M.ccahasrelic == false) and (M.warn < 4)
		)
	then
		AudioMessage ("misn0429.wav");
		M.notfound = GetTime() + 85.0;
		M.warn = M.warn + 1;
	end

	if
		(
		(M.warn == 4) and (M.notfound < GetTime()) and (M.missionfail == false)
		)
	then
		M.aud14 = AudioMessage("misn0694.wav");
		M.missionfail = true;
	end
		if
			(M.missionfail == true) 
		then
			if
				(
				(M.warn == 4)  and 
				(IsAudioMessageDone(M.aud14))
				)
			then
				FailMission(GetTime(), "misn04l4.des");
				M.warn = 0;
			end
		end

	if
		(M.discoverrelic == false)  
	
	then
		if
			(M.investigate < GetTime())
		then
			M.investigator = CountUnitsNearObject(M.relic, 400.0, 1, nil);
			if (IsAlive(M.reliccam))
			then
				M.investigator = M.investigator - 1;
			end
		end

		if 
			(M.investigator >= 1)
		then
			M.aud2 = AudioMessage ("misn0408.wav");
			M.aud3 = AudioMessage ("misn0409.wav");
			M.relicseen = true;
			M.newobjective = true;
			M.ccatug = GetTime()+200.0;--change to 240.0
			M.discoverrelic = true;
			CameraReady();
			M.cintime1 = GetTime() + 23.0;
		end
	end

	if
		(
		(M.discoverrelic == true) and (M.cin1done == false)
		)
	then
		if
		(
		(
		(M.discoverrelic == true) and 
		(IsAudioMessageDone(M.aud2)) and  (IsAudioMessageDone(M.aud3))
		)  or  (CameraCancelled())
		)
		then
		CameraFinish();
		StopAudioMessage(M.aud2);
		StopAudioMessage(M.aud3);
		M.cin1done = true;
		end
	end


	--[[if
		(
		(M.cintime1 < GetTime()) and (M.cin1done == false)
		)

	then
		CameraFinish();
		M.cin1done = true;
	end--]]

	if
		(
		(M.discoverrelic == true) and (M.cintime1 > GetTime())  and 
		(M.cin1done == false)
		)
	then
		if
			(M.relicstartpos == 0)
		then
			CameraPath("reliccin1", 500, 400, M.relic);
		end
		if
			(M.relicstartpos == 1)
		then
			CameraPath("reliccin2", 500, 400, M.relic);
		end
		if
			(M.relicstartpos == 2)
		then
			CameraPath("reliccin3", 500, 400, M.relic);
		end
		if
			(M.relicstartpos == 3)
		then
			CameraPath("reliccin4", 500, 400, M.relic);
		end
	end

	if 
		(M.newobjective == true)

	then
		ClearObjectives ();
		if
			(M.basesecure == false)
		then
			AddObjective ("misn0401.otf", "WHITE");
		end
		if
			(M.basesecure == true)
		then
			AddObjective ("misn0401.otf", "GREEN");
		end

		if
			(
			(M.relicsecure == false) and (M.relicseen == true)
			)
		then
			AddObjective ("misn0403.otf", "WHITE");
		end
		if
			(M.relicsecure == true)
		then
			AddObjective ("misn0403.otf", "GREEN");
		end
		if
			(
			(M.reconsent == true) and (M.discoverrelic == false)
			)
		then
			AddObjective ("misn0405.otf", "WHITE");
		end
		if
			(
			(M.discoverrelic == true)
			)
		then
			AddObjective ("misn0405.otf", "GREEN");
		end
		--[[if
			(
			(M.discoverrelic == true) and (M.relicseen == false)
			)
		then
			AddObjective ("misn0402.otf", "WHITE");
		end
		if
			(M.relicseen == true)
		then
			AddObjective ("misn0402.otf", "GREEN");
		end--]]
		
		M.newobjective = false;
	end
	if
		(M.wavenumber == 1)
	then
		IsAlive(M.w1u1);
		IsAlive(M.w1u2);
	end

	if
		(
		(M.wavenumber == 1) and (GetTime( ) > M.wave1)
		)
	then
		M.w1u1 = BuildObject ("svfigh",2,"wave1");
		M.w1u2 = BuildObject ("svfigh",2,"wave1");
		Attack (M.w1u1, M.avrec,1);
		Attack (M.w1u2, M.avrec,1);
		SetIndependence (M.w1u1, 1);
		SetIndependence (M.w1u2, 1);

		M.wavenumber = 2;
		M.wave1arrive = false;
	end

	if
		(M.wavenumber == 2)
	then
		IsAlive(M.w1u1);
		IsAlive(M.w1u2);
	end
	
	if
		(
		(M.wavenumber == 2) and 
		( not IsAlive (M.w1u1))  and 
		( not IsAlive (M.w1u2))  and 
		(M.build2 == false)  
		)

	
			then
				M.wave2 = GetTime ( ) + 60.0;
				M.build2 = true;
				M.wave1dead = true;
			end
			
	if 
		(
		(M.wave2 < GetTime ( )) and (IsAlive(M.svrec))
		)
	then
		M.w2u1 = BuildObject ("svtank",2,"spawn2new");
		M.w2u2 = BuildObject ("svfigh",2,"spawn2new");
		--M.w2u3 = BuildObject ("svtank",2,"spawn2new");
		Goto(M.w2u1, M.avrec,1);
		Goto(M.w2u2, M.avrec,1);
		--Goto(M.w2u3, M.avrec,1);
		SetIndependence (M.w2u1, 1);
		SetIndependence (M.w2u2, 1);
		--SetIndependence (M.w2u3, 1);
		M.wavenumber = 3;
		M.wave2arrive = false;
		M.wave2 = 99999.0;
	end
	if
	(M.wavenumber == 3)
	then
		IsAlive(M.w2u1);
		IsAlive(M.w2u2);
	end
	
	if
		(
		(M.wavenumber == 3) and 
		( not IsAlive (M.w2u1))  and 
		( not IsAlive (M.w2u2))  and 
		--( not IsAlive (M.w2u3))  and 
		(M.build3 == false)    
		)
			then
				M.wave3 = GetTime ( ) + 74.0;
				M.build3 = true;
				M.wave2dead = true;
			end
	if
		(
		(M.wave3 < GetTime ( )) and (IsAlive(M.svrec))
		)
	then
		
		M.w3u1 = BuildObject ("svfigh",2,M.svrec);
		M.w3u2 = BuildObject ("svfigh",2,M.svrec);
		M.w3u3 = BuildObject ("svfigh",2,M.svrec);
		--M.w3u4 = BuildObject ("svfigh",2,M.svrec);
		Goto(M.w3u1, M.avrec,1);
		Goto(M.w3u2, M.avrec,1);
		Goto(M.w3u3, M.avrec,1);
		--Goto(M.w3u4, M.avrec,1);
		SetIndependence (M.w3u1, 1);
		SetIndependence (M.w3u2, 1);
		SetIndependence (M.w3u3, 1);
		--SetIndependence (M.w3u4, 1);
		M.wavenumber = 4;
		M.wave3arrive = false;
		M.wave3 = 99999.0;
	end

	if
		(M.wavenumber == 4)
	then
		IsAlive(M.w3u1);
		IsAlive(M.w3u2);
		IsAlive(M.w3u3);
	end
	
	if
		(
		(M.wavenumber == 4) and 
		( not IsAlive (M.w3u1))  and 
		( not IsAlive (M.w3u2))  and 
		( not IsAlive (M.w3u3))  and 
		--( not IsAlive (M.w3u4))  and 
		(M.build4 == false)
		)
	then
		M.wave4 = GetTime ( ) + 60.0;
		M.build4 = true;
		M.wave3dead = true;
	end
	if
		(
		(M.wave4 < GetTime ( )) and (IsAlive(M.svrec))
		)
	then
		
		M.w4u1 = BuildObject ("svtank",2,"spawnotherside");
		M.w4u2 = BuildObject ("svfigh",2,"spawnotherside");
		M.w4u3 = BuildObject ("svfigh",2,"spawnotherside");
		--M.w4u4 = BuildObject ("svfigh",2,"spawnotherside");
		--M.w4u5 = BuildObject ("svtank",2,"spawnotherside");
		Goto(M.w4u1, M.avrec,1);
		Goto(M.w4u2, M.avrec,1);
		Goto(M.w4u3, M.avrec,1);
		--Goto(M.w4u4, M.avrec,1);
		--Goto(M.w4u5, M.avrec,1);
		SetIndependence (M.w4u1, 1);
		SetIndependence (M.w4u2, 1);
		SetIndependence (M.w4u3, 1);
		--SetIndependence (M.w4u4, 1);
		--SetIndependence (M.w4u5, 1);
		M.wavenumber = 5;
		M.wave4arrive = false;
		M.wave4 = 99999.0;
	end

	if
		(M.wavenumber == 5)
	then
		IsAlive(M.w4u1);
		IsAlive(M.w4u2);
		IsAlive(M.w4u3);
	end

	
	if
		(
		(M.wavenumber == 5) and 
		( not IsAlive (M.w4u1))  and 
		( not IsAlive (M.w4u2))  and 
		( not IsAlive (M.w4u3))  and 
		--( not IsAlive (M.w4u4))  and 
		--( not IsAlive (M.w4u5))  and 
		(M.build5 == false)
		)
	then
		M.wave5 = GetTime ( ) + 30.0;
		M.build5 = true;
		M.wave4dead = true;
	end

	if
		(
		(M.wave5 < GetTime ( )) and (IsAlive(M.svrec))
		)
	then
		
		M.w5u1 = BuildObject ("svtank",2,M.svrec);
		M.w5u2 = BuildObject ("svfigh",2,M.svrec);
		M.w5u3 = BuildObject ("svfigh",2,M.svrec);
		M.w5u4 = BuildObject ("svfigh",2,M.svrec);
		--M.w5u5 = BuildObject ("svtank",2,M.svrec);
		--M.w5u6 = BuildObject ("svfigh",2,M.svrec);
		Goto(M.w5u1, M.avrec,1);
		Goto(M.w5u2, M.avrec,1);
		Goto(M.w5u3, M.avrec,1);
		Goto(M.w5u4, M.avrec,1);
		--Goto(M.w5u5, M.avrec,1);
		--Goto(M.w5u6, M.avrec,1);
		SetIndependence (M.w5u1, 1);
		SetIndependence (M.w5u2, 1);
		SetIndependence (M.w5u3, 1);
		SetIndependence (M.w5u4, 1);
		--SetIndependence (M.w5u5, 1);
		--SetIndependence (M.w5u6, 1);
		M.wavenumber = 6;
		M.wave5arrive = false;
		M.wave5 = 99999.0;
	end
	
	
	if
		(
		(M.wave1arrive == false) and (IsAlive (M.avrec))
		)
	then
		
		
		if 
			
			(
			(GetDistance (M.avrec, M.w1u1)< 300.0)  or 
			(GetDistance (M.avrec, M.w1u2)< 300.0)
			)
			
			
			
		then
			AudioMessage ("misn0402.wav");
			M.wave1arrive = true;
			M.wave1dead = true;
		end
	end
	
	if
		(
		(M.wave2arrive == false) and (IsAlive (M.avrec))
		)
	then
		if
			
			(
			(GetDistance (M.avrec, M.w2u1) < 300.0)  or 
			(GetDistance (M.avrec, M.w2u2) < 300.0) 
--			 or  (GetDistance (M.avrec, M.w2u3) < 300.0)
			)
			
			
		then
			AudioMessage ("misn0404.wav");
			M.wave2arrive = true;
		end
	end
	if
		(
		(M.wave3arrive == false) and (IsAlive (M.avrec))
		)
	then
		if
			
			(
			(GetDistance (M.avrec, M.w3u1)< 300.0)  or 
			(GetDistance (M.avrec, M.w3u2)< 300.0)  or 
			(GetDistance (M.avrec, M.w3u3)< 300.0) 
--			 or  (GetDistance (M.avrec, M.w3u4)< 300.0)
			)
			
			
		then
			AudioMessage ("misn0410.wav");
			M.wave3arrive = true;
		end
	end
	if
		(
		(M.wave4arrive == false) and (IsAlive (M.avrec))
		)
	then
		if
			
			(
			(GetDistance (M.avrec, M.w4u1)< 300.0)  or  
			(GetDistance (M.avrec, M.w4u2)< 300.0)  or 
			(GetDistance (M.avrec, M.w4u3)< 300.0) -- or 
			--(GetDistance (M.avrec, M.w4u4)< 300.0) 
--			 or  (GetDistance (M.avrec, M.w4u5)< 300.0)
			)
			
			
		then
			AudioMessage ("misn0412.wav");
			M.wave4arrive = true;
		end
	end
	if
		(
		(M.wave5arrive == false) and (IsAlive (M.avrec))
		)
	then
		if
			
			(
			(GetDistance (M.avrec, M.w5u1)< 300.0)  or 
			(GetDistance (M.avrec, M.w5u2)< 300.0)  or 
			(GetDistance (M.avrec, M.w5u3)< 300.0)  or 
			(GetDistance (M.avrec, M.w5u4)< 300.0) -- or 
			--(GetDistance (M.avrec, M.w5u5)< 300.0)  or 
			--(GetDistance (M.avrec, M.w5u6)< 300.0)
			)
			
			
		then
			AudioMessage ("misn0414.wav");
			M.wave5arrive = true;
		end
	end
	
	if (
		(M.attackccabase == false)  and 
		(GetDistance (M.player, M.svrec) < 300.0) )
	then
		AudioMessage ("misn0423.wav");
		M.attackccabase = true;
	end
	
	if
		(
		(M.wave1dead == true)  and 
		( not IsAlive (M.w1u1))  and 
		( not IsAlive (M.w1u2))
		 
		)
	then
		AudioMessage ("misn0403.wav");
		M.wave1dead = false;
	end
	
	if
		(M.wave2dead == true)
	then
		AudioMessage ("misn0405.wav");
		M.wave2dead = false;
	end
	if
		(M.wave3dead == true)
	then
		AudioMessage ("misn0411.wav");
		M.wave3dead = false;
	end
	if
		(M.wave4dead == true)
	then
		AudioMessage ("misn0413.wav");
		M.wave4dead = false;
	end
	
	
	if
		(
		(M.loopbreak == false)  and 
		(M.possiblewin == false) and 
		(M.missionwon == false) and 
		( not IsAlive (M.svrec))
		)
	then
		AudioMessage ("misn0417.wav");
		M.possiblewin = true;
		M.chewedout = true;
		if 
		(

		( not IsAlive (M.svrec))  and 
		(
		(IsAlive (M.w1u1))  or 
		(IsAlive (M.w1u2))  or 
		(IsAlive (M.w2u1))  or 
		(IsAlive (M.w2u2))  or 
--		(IsAlive (M.w2u3))  or 
		(IsAlive (M.w3u1))  or 
		(IsAlive (M.w3u2))  or 
		(IsAlive (M.w3u3))  or 
--		(IsAlive (M.w3u4))  or 
		(IsAlive (M.w4u1))  or 
		(IsAlive (M.w4u2))  or 
		(IsAlive (M.w4u3))  or 
		--(IsAlive (M.w4u4))  or 
--		(IsAlive (M.w4u5))  or 
		(IsAlive (M.w5u1))  or 
		(IsAlive (M.w5u2))  or 
		(IsAlive (M.w5u3))  or 
		(IsAlive (M.w5u4)) -- or 
		--(IsAlive (M.w5u5))  or 
		--(IsAlive (M.w5u6))
		)
		)
		then
			AudioMessage ("misn0418.wav");
		--	M.possiblewin = false;
			M.loopbreak = true;
		end
	end
	if
		(
		(M.basesecure == false)  and 
		( not IsAlive (M.svrec))  and 
		( not IsAlive (M.w1u1))  and 
		( not IsAlive (M.w1u2))  and 
		( not IsAlive (M.w2u1))  and 
		( not IsAlive (M.w2u2))  and 
--		( not IsAlive (M.w2u3))  and 
		( not IsAlive (M.w3u1))  and 
		( not IsAlive (M.w3u2))  and 
		( not IsAlive (M.w3u3))  and 
--		( not IsAlive (M.w3u4))  and 
		( not IsAlive (M.w4u1))  and 
		( not IsAlive (M.w4u2))  and 
		( not IsAlive (M.w4u3))  and 
		--( not IsAlive (M.w4u4))  and 
--		( not IsAlive (M.w4u5))  and 
		( not IsAlive (M.w5u1))  and 
		( not IsAlive (M.w5u2))  and 
		( not IsAlive (M.w5u3))  and 
		( not IsAlive (M.w5u4)) -- and 
		--( not IsAlive (M.w5u5))  and 
		--( not IsAlive (M.w5u6))
		
		)
		
	then
		M.basesecure = true;
		M.newobjective = true;
	end
	
	if
		(
		(M.relicsecure == true) and (M.basesecure == true)
		)

	then
		M.missionwon = true;
	end

	if 
		(
		(M.missionwon == true) and (M.endmission == false)
		)
	then
		if
			(
			--[[(M.doneaud20 == true) and 
			(M.doneaud21 == true)  and 
			(M.doneaud22 == true)  and 
			(M.doneaud23 == true)--]] 
			(IsAudioMessageDone(M.aud20))  and 
			(IsAudioMessageDone(M.aud21))  and 
			(IsAudioMessageDone(M.aud22))  and 
			(IsAudioMessageDone(M.aud23)) 
			)
		then	
		SucceedMission (GetTime(), "misn04w1.des"); 
		end
	end

	--[[if
		(
		(M.doneaud20 == false) and (IsAudioMessageDone(M.aud20))
		)
	then
		M.doneaud20 = true;
	end

	if
		(
		(M.doneaud21 == false) and (IsAudioMessageDone(M.aud21))
		)
	then
		M.doneaud21 = true;
	end

	if
		(
		(M.doneaud22 == false) and (IsAudioMessageDone(M.aud22))
		)
	then
		M.doneaud22 = true;
	end

	if
		(
		(M.doneaud23 == false) and (IsAudioMessageDone(M.aud23))
		)
	then
		M.doneaud23 = true;
	end--]]


	if
		(
		(M.missionwon == false) and 
		( not IsAlive (M.avrec))  and 
		(M.missionfail == false)
		)
	then
		AudioMessage ("misn0421.wav");
		AudioMessage ("misn0422.wav");
		M.missionfail = true;
		FailMission (GetTime( ) + 20.0, "misn04l3.des");
	end
	if
		((M.basesecure == false)  and 
		(M.secureloopbreak == false)  and 
		(M.wavenumber == 6) 
		 and  ( not IsAlive (M.w5u1)) 
		 and  ( not IsAlive (M.w5u2)) 
		 and  ( not IsAlive (M.w5u3))
		 and  ( not IsAlive (M.w5u4))
		-- and  ( not IsAlive (M.w5u5))
		-- and  ( not IsAlive (M.w5u6))
		 and  (IsAlive (M.svrec))
		
		)
	then
		if
			(M.retreat == false)
		then
			if
				(IsAlive(M.tuge1))
			then
			Retreat(M.tuge1, "retreatpoint");
			end
			if
				(IsAlive(M.tuge2))
			then
			Retreat(M.tuge2, "retreatpoint28");
			end
			if
				(IsAlive(M.pu1))
			then
			Retreat(M.pu1, "retreatpoint27");
			end
			if
				(IsAlive(M.pu2))
			then
			Retreat(M.pu2, "retreatpoint26");
			end
			if
				(IsAlive(M.pu3))
			then
			Retreat(M.pu3, "retreatpoint25");
			end
			if
				(IsAlive(M.pu4))
			then
			Retreat(M.pu4, "retreatpoint24");
			end
			if
				(IsAlive(M.pu5))
			then
			Retreat(M.pu5, "retreatpoint23");
			end
			if
				(IsAlive(M.pu6))
			then
			Retreat(M.pu6, "retreatpoint22");
			end
			if
				(IsAlive(M.pu7))
			then
			Retreat(M.pu7, "retreatpoint21");
			end
			if
				(IsAlive(M.pu8))
			then
			Retreat(M.pu8, "retreatpoint20");
			end
			if
				(IsAlive(M.cheat1))
			then
			Retreat(M.cheat1, "retreatpoint19");
			end
			if
				(IsAlive(M.cheat2))
			then
			Retreat(M.cheat2, "retreatpoint18");
			end
			if
				(IsAlive(M.cheat3))
			then
			Retreat(M.cheat3, "retreatpoint17");
			end
			if
				(IsAlive(M.cheat4))
			then
			Retreat(M.cheat4, "retreatpoint16");
			end
			if
				(IsAlive(M.cheat5))
			then
			Retreat(M.cheat5, "retreatpoint15");
			end
			if
				(IsAlive(M.cheat6))
			then
			Retreat(M.cheat6, "retreatpoint14");
			end
			if
				(IsAlive(M.cheat7))
			then
			Retreat(M.cheat7, "retreatpoint13");
			end
			if
				(IsAlive(M.cheat8))
			then
			Retreat(M.cheat8, "retreatpoint12");
			end
			if
				(IsAlive(M.cheat9))
			then
			Retreat(M.cheat9, "retreatpoint11");
			end
			if
				(IsAlive(M.cheat10))
			then
			Retreat(M.cheat10, "retreatpoint10");
			end
			if
				(IsAlive(M.surv1))
			then
			Retreat(M.surv1, "retreatpoint9");
			end
			if
				(IsAlive(M.surv2))
			then
			Retreat(M.surv2, "retreatpoint8");
			end
			if
				(IsAlive(M.surv3))
			then
			Retreat(M.surv3, "retreatpoint7");
			end
			if
				(IsAlive(M.surv4))
			then
			Retreat(M.surv4, "retreatpoint6");
			end
			if
				(IsAlive(M.turret1))
			then
			Retreat(M.turret1, "retreatpoint2");
			end
			if
				(IsAlive(M.turret2))
			then
			Retreat(M.turret2, "retreatpoint3");
			end
			if
				(IsAlive(M.turret3))
			then
			Retreat(M.turret3, "retreatpoint4");
			end
			if
				(IsAlive(M.turret4))
			then
			Retreat(M.turret4, "retreatpoint5");
			end
			M.retreat = true;
		end

		--[[M.safety = GetNearestEnemy(M.player);
		if
			(GetDistance(M.safety, M.player) > 400.0)
		then--]]
		M.aud21 = AudioMessage ("misn0415.wav");
		M.aud22 = AudioMessage ("misn0416.wav");
		M.basesecure = true;
		M.newobjective = true;
		M.secureloopbreak = true;
		--end

	end

	if
		(
		( not IsAlive(M.relic)) and (M.missionfail == false)
		)
	then
		FailMission(GetTime() + 20.0, "misn04l2.des");
		AudioMessage("misn0431.wav");
		AudioMessage("misn0432.wav");
		AudioMessage("misn0433.wav");
		AudioMessage("misn0434.wav");
		M.missionfail = true;
	end

	if
		(M.wavenumber == 6)
	then
		IsAlive(M.w5u1);
		IsAlive(M.w5u2);
		IsAlive(M.w5u3);
		IsAlive(M.w5u4);
	end

	if
		((M.basesecure == false)  and 
		(M.secureloopbreak == false)  and 
		(M.wavenumber == 6) 
		 and  ( not IsAlive (M.w5u1)) 
		 and  ( not IsAlive (M.w5u2)) 
		 and  ( not IsAlive (M.w5u3))
		 and  ( not IsAlive (M.w5u4))
		-- and  ( not IsAlive (M.w5u5))
		-- and  ( not IsAlive (M.w5u6))
		 and  ( not IsAlive (M.svrec))
		 and  (M.chewedout == true)
		)

	then
		M.aud20 = AudioMessage ("misn0425.wav");
		M.basesecure = true;
		M.newobjective = true;
		M.secureloopbreak = true;
	end

-- END OF SCRIPT
	
end