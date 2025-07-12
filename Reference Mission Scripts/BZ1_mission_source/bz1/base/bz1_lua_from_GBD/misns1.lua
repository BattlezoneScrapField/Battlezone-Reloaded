-- Single Player CCA Mission 1 Lua conversion, created by General BlackDragon. 

-- Single Table for all our save/load variables. This SP mission has too many variables to function with them independently. ("main function has > 200 local variables", or "Load having > 197 variables in assignment")
local M = {

-- bools
	--coloradoescapes = false,
	halfwaywarn = false,
	coloradodestroyed = false,
	silodestroyed = false,
	mufdestroyed = false,
	retreat = false,
	missionstart = false,
	missionwon = false,
	enterwarning = false,
	trapset = false,
	coloradosafe = false,
	missionfail = false,
	--beginassault = false,
	--convoyseen = false,
	--convoyintrap = false,
	pickpath = false,
	cav1pathwarn1 = false,
	--cav1pathwarn2 = false,
	cav2pathwarn1 = false,
	--cav2pathwarn2 = false,
	cav3pathwarn1 = false,
	cav3pathwarn2 = false,
	cav4pathwarn1 = false,
	cav4pathwarn2 = false,
	finish = false,
	cavalry = false,
	cavsent = false,
	cavpath1 = false,
	cavpath2 = false,
	cavpath3 = false,
	cavpath4 = false,
	coloradoreachedsafepoint = false,
	possible1 = false,
	possible2 = false,
	newobjective = false,
	escortretreat = false,
	cindone = false,
	cindone05 = false,
	cindone1 = false,
	cindone2 = false,
	cindone3 = false,
	cindone4 = false,
	cindone5 = false,
	cindone6 = false,
	cindone7 = false,
	cindone8 = false,
	cindone08 = false,
	cindone9 = false,
	cindone10 = false,
	--cindone11 = false,
	retreatpathset = false,
	blockaderun = false,
	aw1amade = false,
	aw1bmade = false,
	aw1cmade = false,
	aw2amade = false,
	aw2bmade = false,
	aw2cmade = false,
	aw3amade = false,
	aw3bmade = false,
	aw3cmade = false,
	du1amade = false,
	du1bmade = false,
	safety1 = false,
-- Floats (really doubles in Lua)
	startconvoy = 0,
	wave1 = 0,
	cintime = 0,
	cintime05 = 0,
	cintime2 = 0,
	cintime3 = 0,
	cintime4 = 0,
	cintime5 = 0,
	cintime6 = 0,
	cintime7 = 0,
	cintime8 = 0,
	cintime9 = 0,
	cintime09 = 0,
	cintime10 = 0,
	cintime11 = 0,
	--cintime12 = 0,
	aw1at = 0,
	aw1bt = 0,
	aw1ct = 0,
	aw2at = 0,
	aw2bt = 0,
	aw2ct = 0,
	aw3at = 0,
	aw3bt = 0,
	aw3ct = 0,
	du1at = 0,
	du1bt = 0,
-- Handles
	colorado = nil,
	ef1 = nil,
	ef2 = nil,
	ef3 = nil,
	et1 = nil,
	et2 = nil,
	et3 = nil,
	et4 = nil,
	silo = nil,
	muf = nil,
	svrec = nil,
	--player = nil,
	geyser = nil,
	geyser2 = nil,
	--guntower = nil,
	walker1 = nil,
	walker2 = nil,
	walker3 = nil,
	walkcam1 = nil,
	walkcam2 = nil,
	walkcam3 = nil,
	hidcam1 = nil,
	hidcam2 = nil,
	hidcam3 = nil,
	basecam = nil,
	cav1 = nil,
	cav2 = nil,
	cav3 = nil,
	cav4 = nil,
	cav5 = nil,
	scav1 = nil,
	scav2 = nil,
	aw1a = nil,
	aw1b = nil,
	aw1c = nil,
	aw2a = nil,
	aw2b = nil,
	aw2c = nil,
	aw3a = nil,
	aw3b = nil,
	aw3c = nil,
	--du1a = nil,
	--du1b = nil,
	hostile = nil,
	ambase = nil,
-- Ints
	path = 0,
	cav = 0,
	aud20 = 0,
	aud21 = 0,
	aud22 = 0,
	aud23 = 0,
	aud1 = 0
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

	M.startconvoy = 9999999999.0;
	
	M.wave1 = 999999999.0;
	M.cintime = 9999999999.0;
	M.cintime05 = 99999999.0;
	M.cintime2 = 9999999999.0;
	M.cintime3 = 9999999999.0;
	M.cintime4 = 9999999999.0;
	M.cintime5 = 9999999999.0;
	M.cintime6 = 9999999999.0;
	M.cintime7 = 9999999999.0;
	M.cintime8 = 9999999999.0;
	M.cintime9 = 9999999999.0;
	M.cintime09 = 999999999999.0;
	M.cintime10 = 9999999999.0;
	M.cintime11 = 9999999999.0;
	M.aw1at = 99999999999.0;
	M.aw1bt = 99999999999.0;
	M.aw1ct = 99999999999.0;
	M.aw2at = 99999999999.0;
	M.aw2bt = 99999999999.0;
	M.aw2ct = 99999999999.0;
	M.aw3at = 99999999999.0;
	M.aw3bt = 99999999999.0;
	M.aw3ct = 99999999999.0;
	M.du1at = 99999999999.0;
	M.du1bt = 99999999999.0;

end

function AddObject(h)


end

function Update()

-- START OF SCRIPT

	if 
		(M.missionstart == false)
	then
		AudioMessage("misns101.wav");
		M.geyser = GetHandle("eggeizr10_geyser");
		M.muf = GetHandle("avmuf1_factory");
		M.silo = GetHandle("absilo1_i76building");
		M.colorado = GetHandle("avrecy1_recycler");
		M.svrec = GetHandle("svrecy2_recycler");
		SetScrap (2, 50);
		SetScrap (1,20);
		--M.geyser2 = GetHandle("geyser2");
		M.ef1 = GetHandle("avfigh3_wingman");
		M.ef2 = GetHandle("avfigh4_wingman");
		M.ef3 = GetHandle("avfigh5_wingman");
		M.et1 = GetHandle("avtank5_wingman");
		M.et2 = GetHandle("avtank6_wingman");
		M.et3 = GetHandle("avtank7_wingman");
		M.et4 = GetHandle("avtank8_wingman");
		M.ambase = GetHandle("ambase");
		-- temporary 
		M.walker1 = BuildObject ("svwalk", 1, "spawnwalker1"); 
		--M.walker2 = BuildObject ("svwalk", 1, "spawnwalker2"); 
		--M.walker3 = BuildObject ("svwalk", 1, "walkstart3"); 
		M.walkcam1 = BuildObject ("apcamr", 1, "walkcam1");
		--M.walkcam2 = BuildObject ("apcamr", 1, "walkcam2");
		--M.walkcam3 = BuildObject ("apcamr", 1, "walkcam3");
		M.hidcam1 = BuildObject ("apcamr", 1, "hidcamupper");
		M.hidcam2 = BuildObject ("apcamr", 1, "hidcammiddle");
		M.hidcam3 = BuildObject ("apcamr", 1, "hidcamlower");
		M.basecam = GetHandle("apcamr0_camerapod");
		SetObjectiveName(M.walkcam1, "Walker Cut Off");
		--SetObjectiveName(M.walkcam2, "Middle Pass Exit");
		SetObjectiveName(M.ambase, "American Outpost");
		SetObjectiveName(M.hidcam1, "Upper Pass Exit");
		SetObjectiveName(M.hidcam2, "Middle Pass Exit");
		SetObjectiveName(M.hidcam3, "Lower Pass Exit");
		SetObjectiveName(M.basecam, "Home Base");
		--Goto (M.walker1, "spawnwalker1");
		--Goto (M.walker2, "spawnwalker2");
		--Goto (M.walker3, "spawnwalker3");
		--RemoveObject (M.ef2);
		--RemoveObject (M.ef3);
		--RemoveObject (M.et1);
		--RemoveObject (M.et2);
		RemoveObject (M.et3);
		RemoveObject (M.et4);
		BuildObject("svtank", 1, "tank1");
		BuildObject("svtank", 1, "tank2");
		BuildObject("svfigh", 1, "figh1");
		BuildObject("svturr", 1, "turr1");
		BuildObject("svturr", 1, "turr2");
		M.startconvoy = GetTime () + 180.0;
		M.missionstart = true;
		SetScrap (1, 20);
		SetScrap (2, 50);
		M.path = math.random(0, 2); --rand () % 3;
		M.cav = math.random(0, 3); --rand () % 4;
		M.newobjective = true;
		--CameraReady();
		M.cintime = GetTime () + 11.0;--11
		M.cintime05 = GetTime () + 11.1;--11
		M.cintime2 = GetTime () + 20.0;
		M.cintime3 = GetTime () + 27.0;
		M.cintime4 = GetTime () + 29.0;
		M.cintime5 = GetTime () + 31.0;
		M.cintime6 = GetTime () + 33.0;
		M.cintime7 = GetTime () + 44.0;
		M.cintime8 = GetTime () + 46.0;
		M.cintime9 = GetTime () + 48.0;
		M.cintime09 = GetTime () + 50.0;
		M.cintime10 = GetTime () + 60.0;
		M.cintime11 = GetTime () + 66.0;
	end
	IsAlive(M.colorado);

	--[[if
		(
		(M.cindone == false) and (M.cintime > GetTime())
		)
	then
		CameraPath("cinpath3", 200, 600, M.svrec);
	end
	if
		(
		(M.cindone05 == false) and (M.cintime05 < GetTime())
		)
	then
		CameraPath("cinpath4", 300, 500, M.colorado);
		M.cindone = true;
	end
	if
		(
		(M.cindone1 == false) and (M.cintime2 < GetTime())
		)
	then
		--CameraObject(M.geyser2, 3000, 600, 3000, M.geyser2);
		CameraPath("geyserpath", 500, 5000, M.geyser2);
		M.cindone05 = true;
	end
	--CameraObject(M.walker1, -1200, 1500, -1100, M.walker2);
	if
		(
		(M.cintime3 < GetTime()) and (M.cindone2 == false)
		)
	then
		CameraObject(M.hidcam1, 1100, 300, 200, M.hidcam1);
		M.cindone1 = true;
	end
	if
		(
		(M.cintime4 < GetTime()) and (M.cindone3 == false)
		)
	then
		CameraObject(M.hidcam2, 300, 200, 1500, M.hidcam2);
		M.cindone2 = true;
	end
	if
		(
		(M.cintime5 < GetTime()) and (M.cindone4 == false)
		)
	then
		CameraObject(M.hidcam3, 600, 1000, 300, M.hidcam3);
		M.cindone3 = true;
	end
	if
		(
		(M.cintime6 < GetTime()) and (M.cindone5 == false)
		)
	then
		CameraObject(M.walker1, -1200, 1500, 1100, M.walker2);
		M.cindone4 = true;
	end
	if
		(
		(M.cintime7 < GetTime()) and (M.cindone6 == false)
		)
	then
		CameraObject(M.walkcam1, 500, 300, 1200, M.walkcam1);
		M.cindone5 = true;
	end
	if
		(
		(M.cintime8 < GetTime()) and (M.cindone7 == false)
		)
	then
		CameraObject(M.walkcam2, 1300, 200, 500, M.walkcam2);
		M.cindone6 = true;
	end
	if
		(
		(M.cintime9 < GetTime()) and (M.cindone8 == false)
		)
	then
		CameraObject(M.walkcam3, 600, 400, 1300, M.walkcam3);
		M.cindone7 = true;
	end
	if
		(
		(M.cindone08 == false) and (M.cintime09 < GetTime())
		)
	then
		CameraPath("approach", 400, 5000, M.hidcam3);
		M.cindone8 = true;
	end
	if
		(
		(M.cindone9 == false) and (M.cintime10 < GetTime())
		)
	then
		CameraPath("cinpath1", 300, 500, M.muf);
		M.cindone08 = true;
	end
	if
		(
		(M.cintime11 < GetTime()) and (M.cindone10 == false)
		)
	then
		CameraFinish();
		M.cindone9 = true;
		M.cindone10 = true;
	end--]]



	if
		(M.newobjective == true)
	then
		ClearObjectives();
		if
			(
			(IsAlive(M.colorado)) and (M.coloradosafe == false)
			)
		then
			AddObjective ("misns101.otf", "WHITE");
		end
		if
			(
			( not IsAlive(M.colorado)) and (M.coloradosafe == false)
			)
		then
			AddObjective ("misns101.otf", "GREEN");
		end
		if
			(M.coloradoreachedsafepoint == true)
		then
			AddObjective ("misns101.otf", "RED");
		end
		if
			(M.coloradosafe == false)
		then
			if
			(
			(IsAlive(M.muf))  or  (IsAlive(M.silo))
			)
		then
			AddObjective ("misns102.otf", "WHITE");
		end
		end
		if
			(M.coloradosafe == true)
		then
			if
			(
			(IsAlive(M.muf))  or  (IsAlive(M.silo))  or  (IsAlive(M.colorado))
			)
		then
			AddObjective ("misns102.otf", "WHITE");
		end
		end
		if
			(M.coloradosafe == false)
		then
		if
			(
			( not IsAlive(M.muf)) and ( not IsAlive(M.silo))
			)
		then
			AddObjective ("misns102.otf", "GREEN");
		end
		end
		if
			(M.coloradosafe == true)
		then
		if
			(
			( not IsAlive(M.muf)) and ( not IsAlive(M.silo)) and ( not IsAlive(M.colorado))
			)
		then
			AddObjective ("misns102.otf", "GREEN");
		end
		end
		if
			(
			(IsAlive(M.svrec)) and (M.missionwon == false)
			)
		then
			AddObjective ("misns103.otf", "WHITE");
		end
		if
			( not IsAlive(M.svrec))
		then
			AddObjective ("misns103.otf", "RED");
		end
		if
			(M.missionwon == true)
		then
			AddObjective ("misns103.otf", "GREEN");
		end
		if
			(
			(M.coloradosafe == true) and (M.missionwon == false)
			)
		then
			AddObjective ("misns101.otf", "RED");
		end
		M.newobjective = false;
	end

			

	if
		(
		(M.pickpath == false) and (M.startconvoy < GetTime ())
		)
	then
		if (M.path == 0) then
			Follow (M.ef1, M.colorado);
			Follow (M.ef2, M.colorado);
			Follow (M.ef3, M.colorado);
			Goto (M.colorado, "upperpath");
			Follow (M.et1, M.colorado, 1);
			Follow (M.et2, M.colorado, 1);
			--Follow (M.et3, M.colorado, 1);
			--Follow (M.et4, M.colorado, 1);
		elseif (M.path == 1) then
			Follow (M.ef1, M.colorado);
			Follow (M.ef2, M.colorado);
			Follow (M.ef3, M.colorado);
			Goto (M.colorado, "midpath");
			Follow (M.et1, M.colorado, 1);
			Follow (M.et2, M.colorado, 1);
			--Follow (M.et3, M.colorado, 1);
			--Follow (M.et4, M.colorado, 1);
		elseif (M.path == 2) then
			Follow (M.ef1, M.colorado);
			Follow (M.ef2, M.colorado);
			Follow (M.ef3, M.colorado);
			Goto (M.colorado, "lowerpath");
			Follow (M.et1, M.colorado, 1);
			Follow (M.et2, M.colorado, 1);
			--Follow (M.et3, M.colorado, 1);
			--Follow (M.et4, M.colorado, 1);
		end
		SetIndependence(M.ef1, 1);
		SetIndependence(M.ef2, 1);
		SetIndependence(M.ef3, 1);
		SetIndependence(M.et1, 1);
		SetIndependence(M.et2, 1);
		--SetIndependence(M.et3, 1);
		--SetIndependence(M.et4, 1);
		M.pickpath = true;
		AudioMessage("misns125.wav");
	end

	if 
		(
		(
		(GetDistance(M.walker1, M.walkcam1) < 50.0) -- or 
		--(GetDistance(M.walker2, M.walkcam1) < 50.0)  or 
		--(GetDistance(M.walker3, M.walkcam1) < 50.0)
		) and (M.trapset == false) and (M.blockaderun == false) and 
		(IsAlive(M.colorado))
		)
	then
		M.trapset = true;
		AudioMessage("misns123.wav");
	end

	--[[if 
		(
		(
		(GetDistance(M.walker1, M.walkcam2) < 50.0)  or 
		(GetDistance(M.walker2, M.walkcam2) < 50.0) -- or 
		--(GetDistance(M.walker3, M.walkcam2) < 50.0)
		) and (M.trapset == false) and (M.blockaderun == false)
		)
	then
		M.trapset = true;
		AudioMessage("misns123.wav");
	end

	if 
		(
		(
		(GetDistance(M.walker1, M.walkcam3) < 50.0)  or 
		(GetDistance(M.walker2, M.walkcam3) < 50.0) -- or 
		--(GetDistance(M.walker3, M.walkcam3) < 50.0)
		) and (M.trapset == false) and (M.blockaderun == false)
		)
	then
		M.trapset = true;
		AudioMessage("misns123.wav");
	end--]]

	if
		(
		(M.halfwaywarn == true) and (M.blockaderun == false)
		)
	then
		if	
			(
			(M.path == 0) and (GetDistance(M.colorado, M.hidcam1) < 70.0)
			)
		then
			M.blockaderun = true;
			AudioMessage("misns124.wav");
		end
		if	
			(
			(M.path == 1) and (GetDistance(M.colorado, M.hidcam2) < 70.0)
			)
		then
			M.blockaderun = true;
			AudioMessage("misns124.wav");
		end
		if	
			(
			(M.path == 2) and (GetDistance(M.colorado, M.hidcam3) < 70.0)
			)
		then
			M.blockaderun = true;
			AudioMessage("misns124.wav");
		end
	end
	if 
		(
		(M.retreat == false) and (M.blockaderun == false)
		)
	then
		M.hostile = GetNearestEnemy(M.colorado);
		if
		(GetDistance(M.hostile, M.colorado) < 200.0)
		then
		--Attack (M.walker1, M.colorado);
		--Attack (M.walker2, M.ef2);
		--Attack (M.walker3, M.ef1);
		--SetIndependence (M.walker1, 1);
		--SetIndependence (M.walker2, 1);
		--SetIndependence (M.walker3, 1);
		M.retreat = true;
		AudioMessage ("misns114.wav");
		end
	end

	if
		(
		(M.retreatpathset == false) and (M.retreat == true) 
		)
	then
		
			Goto(M.colorado, "retreat1");
			Attack(M.ef1, M.hostile);
			Follow(M.ef2, M.ef1);
			Follow(M.et3, M.ef1);
			SetIndependence(M.ef1, 1);
			SetIndependence(M.ef2, 1);
			SetIndependence(M.et3, 1);
			M.retreatpathset = true;
	end

	if 
		(
		(M.retreat == true) and (GetDistance (M.colorado, M.geyser) < 50.0)  and 
		(M.coloradosafe == false)
		)
	then
		M.coloradosafe = true;
		SetAIP ("misn09.aip");
		SetObjectiveOn(M.colorado);
		SetObjectiveOn(M.silo);
		SetObjectiveOn(M.muf);
		AudioMessage ("misns106.wav");
		M.aw1at = GetTime() + 25.0;
		M.aw1bt = GetTime() + 30.0;
		M.aw1ct = GetTime() + 35.0;
		M.aw2at = GetTime() + 90.0;
		M.aw2bt = GetTime() + 95.0;
		M.aw2ct = GetTime() + 100.0;
		M.aw3at = GetTime() + 190.0;
		M.aw3bt = GetTime() + 195.0;
		M.aw3ct = GetTime() + 200.0;
		M.du1at = GetTime() + 60.0;
		M.du1bt = GetTime() + 75.0;
		M.newobjective = true;
	end

	if
		(
		( not IsAlive(M.colorado)) and (M.escortretreat == false)
		)
	then
		Goto(M.ef1, M.muf, 1000);
		Goto(M.ef2, M.muf, 1000);
		Goto(M.ef3, M.muf, 1000);
		--Goto(M.et1, M.muf, 1000);
		M.escortretreat = true;
	end

	if 
		(
		(M.safety1 == false)  and 
		(M.coloradosafe == false) and ( not IsAlive(M.colorado))
		)
	then
		SetAIP ("misn14.aip");
		M.scav1 = BuildObject ("avscav", 2, M.muf);
		M.scav2 = BuildObject ("avscav", 2, M.muf);
		SetObjectiveOn(M.silo);
		SetObjectiveOn(M.muf);
		--M.coloradosafe = true;
		M.safety1 = true;
		AudioMessage ("misns105.wav");
		M.aw1at = GetTime() + 25.0;
		M.aw1bt = GetTime() + 35.0;
		M.aw1ct = GetTime() + 40.0;
		M.aw2at = GetTime() + 90.0;
		M.aw2bt = GetTime() + 95.0;
		M.aw2ct = GetTime() + 100.0;
		M.aw3at = GetTime() + 190.0;
		M.aw3bt = GetTime() + 195.0;
		M.aw3ct = GetTime() + 200.0;
		M.du1at = GetTime() + 60.0;
		M.du1bt = GetTime() + 75.0;
		M.newobjective = true;
	end
	if
		(
		(M.aw1at < GetTime()) and (M.aw1amade == false) and (IsAlive(M.muf))
		)
	then
		BuildObject ("avtank", 2, M.muf);
		M.aw1amade = true;
	end
	if
		(
		(M.aw1bt < GetTime()) and (M.aw1bmade == false) and (IsAlive(M.muf))
		)
	then
		BuildObject ("avfigh", 2, M.muf);
		M.aw1bmade = true;
	end
	if
		(
		(M.aw1ct < GetTime()) and (M.aw1cmade == false) and (IsAlive(M.muf))
		)
	then
		BuildObject ("avfigh", 2, M.muf);
		M.aw1cmade = true;
	end
	if
		(
		(M.aw2at < GetTime()) and (M.aw2amade == false) and (IsAlive(M.muf))
		)
	then
		BuildObject ("avtank", 2, M.muf);
		M.aw2amade = true;
	end
	if
		(
		(M.aw2bt < GetTime()) and (M.aw2bmade == false) and (IsAlive(M.muf))
		)
	then
		BuildObject ("avfigh", 2, M.muf);
		M.aw2bmade = true;
	end
	if
		(
		(M.aw2ct < GetTime()) and (M.aw2cmade == false) and (IsAlive(M.muf))
		)
	then
		BuildObject ("avtank", 2, M.muf);
		M.aw2cmade = true;
	end
	if
		(
		(M.aw3at < GetTime()) and (M.aw3amade == false) and 
		(IsAlive(M.muf)) and (IsAlive(M.silo))
		)
	then
		BuildObject ("avtank", 2, M.muf);
		M.aw3amade = true;
	end
	if
		(
		(M.aw3bt < GetTime()) and (M.aw3bmade == false) and 
		(IsAlive(M.muf)) and (IsAlive(M.silo))
		)
	then
		BuildObject ("avtank", 2, M.muf);
		M.aw3bmade = true;
	end
	if
		(
		(M.aw3ct < GetTime()) and (M.aw3cmade == false) and 
		(IsAlive(M.muf)) and (IsAlive(M.silo))
		)
	then
		BuildObject ("avfigh", 2, M.muf);
		M.aw3cmade = true;
	end
	if
		(
		(M.du1at < GetTime()) and (M.du1amade == false)
		)
	then
		BuildObject ("avturr", 2, M.muf);
		M.du1amade = true;
	end
	if
		(
		(M.du1bt < GetTime()) and (M.du1bmade == false)
		)
	then
		BuildObject ("avturr", 2, M.muf);
		M.du1bmade = true;
	end
	--[[if
		(
		(aw1sent == false) and (M.aw1amade == true)  and 
		(M.aw1bmade == true) and (M.aw1cmade == true)
		)
	then
		Attack(M.aw1a, M.svrec);
		Attack(M.aw1b, M.svrec);
		Attack(M.aw1c, M.svrec);
		SetIndependence(M.aw1a, 1);
		SetIndependence(M.aw1b, 1);
		SetIndependence(M.aw1c, 1);
		aw1sent = true;
	end
	if
		(
		(aw2sent == false) and (M.aw2amade == true)  and 
		(M.aw2bmade == true) and (M.aw2cmade == true)
		)
	then
		Attack(M.aw2a, M.svrec);
		Attack(M.aw2b, M.svrec);
		Attack(M.aw2c, M.svrec);
		SetIndependence(M.aw2a, 1);
		SetIndependence(M.aw2b, 1);
		SetIndependence(M.aw2c, 1);
		aw2sent = true;
	end
	if
		(
		(aw3sent == false) and (M.aw3amade == true)  and 
		(M.aw3bmade == true) and (M.aw3cmade == true)
		)
	then
		Attack(M.aw3a, M.svrec);
		Attack(M.aw3b, M.svrec);
		Attack(M.aw3c, M.svrec);
		SetIndependence(M.aw3a, 1);
		SetIndependence(M.aw3b, 1);
		SetIndependence(M.aw3c, 1);
		aw3sent = true;
	end--]]

	if
		(
		( not IsAlive(M.colorado)) and (M.coloradodestroyed == false)
		)
	then
		M.coloradodestroyed = true;
		M.wave1 = GetTime() + 180.0;
	end

	if
		(
		( not IsAlive(M.muf)) and (M.mufdestroyed == false)
		)
	then
		AudioMessage ("misns108.wav");
		M.mufdestroyed = true;
		M.possible1 = true;
	end

	if
		(
		( not IsAlive (M.silo)) and (M.silodestroyed == false)
		)
	then
		M.possible2 = true;
		AudioMessage ("misns107.wav");
		M.silodestroyed = true;
	end

	if 
		(
		(M.possible1 == true) and (M.possible2 == true)
		)
	then
		M.newobjective = true;
	end

	if
		(
		(M.mufdestroyed == true) and (M.silodestroyed == true) and 
		(M.coloradodestroyed == true) and (M.missionwon == false)
		)
	then
		M.newobjective = true;
		M.missionwon = true;
	end

	if 
		(
		(M.missionwon == true) and (M.finish == false)
		)
	then
		M.aud1 = AudioMessage("misns110.wav");
		M.finish = true;
	end

	if 
		(
		(M.finish == true) and (IsAudioMessageDone(M.aud1))
		)
	then
		SucceedMission(GetTime(), "misns1w1.des");
	end


	if
		(
		(M.enterwarning == false) and 
		(GetDistance (M.colorado, M.walkcam1) < 70.0) 
		)
	then
		if
			(M.path == 0)
		then
		AudioMessage ("misns117.wav");
		M.enterwarning = true;
		end
		if
			(M.path == 1)
		then
			AudioMessage ("misns116.wav");
		M.enterwarning = true;
		end
		if
			(M.path == 2)
		then
			AudioMessage ("misns115.wav");
		M.enterwarning = true;
		end
	end

	if 
		(
		(GetDistance (M.colorado, "halfwayupper") < 100.0)  and 
		(M.halfwaywarn == false)
		)
	then
		M.halfwaywarn = true;
		AudioMessage ("misns102.wav");
	end

	if 
		(
		(GetDistance (M.colorado, "halfwaymid") < 100.0)  and 
		(M.halfwaywarn == false)
		)
	then
		M.halfwaywarn = true;
		AudioMessage ("misns103.wav");
	end
	if 
		(
		(GetDistance (M.colorado, "halfwaylower") < 100.0)  and 
		(M.halfwaywarn == false)
		)
	then
		M.halfwaywarn = true;
		AudioMessage ("misns104.wav");
	end

	if 
		(
		(M.blockaderun == true)  and 
		(GetDistance (M.colorado, "safepoint") < 60.0) and  -- I know succeds is not the correct spelling but it was easier to leave it then to change it.  I'm not dumb.  I'm just lazy. hehe
		(M.coloradoreachedsafepoint == false)
		)
	then
		M.aud20 = AudioMessage ("misns109.wav");
		M.aud21 = AudioMessage ("misns111.wav");
		M.coloradoreachedsafepoint = true;
		M.newobjective = true;
		CameraReady();
		CameraObject(M.geyser2, 1200, 500, 1200, M.colorado);
	end

	if
		(
		(M.coloradoreachedsafepoint == true) and (IsAudioMessageDone(M.aud20))  and 
		(IsAudioMessageDone(M.aud21))
		)
	then
		FailMission(GetTime(), "misns1l1.des");
	end

	if
		(
		( not IsAlive(M.svrec)) and (M.missionfail == false)
		)
	then
		M.aud22 = AudioMessage("misns112.wav");
		M.aud23 = AudioMessage("misns113.wav");
		M.missionfail = true;
		M.newobjective = true;
	end

	if
		(
		(M.missionfail == true) and (IsAudioMessageDone(M.aud22))  and 
		(IsAudioMessageDone(M.aud23))
		)
	then
		FailMission(GetTime(), "misns1l2.des");
	end

	if
		(
		(M.wave1 < GetTime()) and (M.cavalry == false)
		)
	then
		M.wave1 = 99999999999.0;
		M.cavalry = true;
		M.cav1 = BuildObject ("avfigh", 2, "cavspawn");
		M.cav2 = BuildObject ("avtank", 2, "cavspawn");
		M.cav3 = BuildObject ("avfigh", 2, "cavspawn");
		--M.cav4 = BuildObject ("avtank", 2, "cavspawn");
		--M.cav5 = BuildObject ("avtank", 2, "cavspawn");
		AudioMessage ("misns122.wav");
	end

	if 
		(
		(M.cavalry == true)  and 
		(M.cavsent == false)
		)
	then
		if (M.cav == 0) then
			Goto (M.cav1, "cavpath1");
			Goto (M.cav2, "cavpath1");
			Goto (M.cav3, "cavpath1");
			--Goto (M.cav4, "cavpath1");
			--Goto (M.cav5, "cavpath1");
			M.cavpath1 = true;
		elseif (M.cav == 1) then
			Goto (M.cav1, "cavpath2");
			Goto (M.cav2, "cavpath2");
			Goto (M.cav3, "cavpath2");
			--Goto (M.cav4, "cavpath2");
			--Goto (M.cav5, "cavpath2");
			M.cavpath2 = true;
		elseif (M.cav == 2) then
			Goto (M.cav1, "cavpath1");
			Goto (M.cav2, "cavpath1");
			Goto (M.cav3, "cavpath1");
			--Goto (M.cav4, "cavpath1");
			--Goto (M.cav5, "cavpath1");
			M.cavpath1 = true;
		elseif (M.cav == 3) then
			Goto (M.cav1, "cavpath2");
			Goto (M.cav2, "cavpath2");
			Goto (M.cav3, "cavpath2");
			--Goto (M.cav4, "cavpath2");
			--Goto (M.cav5, "cavpath2");
			M.cavpath2 = true;
		end
		M.cavsent = true;
	end

	if 
		(
		(M.cavpath1 == true) and 
		(
		(GetDistance (M.cav1, M.walkcam1) < 200.0)  or 
		(GetDistance (M.cav2, M.walkcam1) < 200.0)  or 
		(GetDistance (M.cav3, M.walkcam1) < 200.0) -- or 
		--(GetDistance (M.cav4, M.walkcam1) < 200.0)  or 
		--(GetDistance (M.cav5, M.walkcam1) < 200.0)
		) and (M.cav1pathwarn1 == false)
		)
	then
		AudioMessage("misns118.wav");
		M.cav1pathwarn1 = true;
	end

	if 
		(
		(M.cavpath2 == true) and 
		(
		(GetDistance (M.cav1, M.walkcam2) < 50.0)  or 
		(GetDistance (M.cav2, M.walkcam2) < 50.0)  or 
		(GetDistance (M.cav3, M.walkcam2) < 50.0) -- or 
		--(GetDistance (M.cav4, M.walkcam2) < 50.0)  or 
		--(GetDistance (M.cav5, M.walkcam2) < 50.0)
		) and (M.cav2pathwarn1 == false)
		)
	then
		AudioMessage("misns119.wav");
		M.cav2pathwarn1 = true;
	end

	--[[if 
		(
		(M.cavpath3 == true) and 
		(
		(GetDistance (M.cav1, M.walkcam1) < 200.0)  or 
		(GetDistance (M.cav2, M.walkcam1) < 200.0)  or 
		(GetDistance (M.cav3, M.walkcam1) < 200.0)  or 
		(GetDistance (M.cav4, M.walkcam1) < 200.0)  or 
		(GetDistance (M.cav5, M.walkcam1) < 200.0)
		) and (M.cav3pathwarn1 == false)
		)
	then
		AudioMessage("misns118.wav");
		M.cav3pathwarn1 = true;
	end

	if 
		(
		(M.cavpath3 == true) and 
		(
		(GetDistance (M.cav1, M.hidcam2) < 60.0)  or 
		(GetDistance (M.cav2, M.hidcam2) < 60.0)  or 
		(GetDistance (M.cav3, M.hidcam2) < 60.0)  or 
		(GetDistance (M.cav4, M.hidcam2) < 60.0)  or 
		(GetDistance (M.cav5, M.hidcam2) < 60.0)
		) and (M.cav3pathwarn2 == false)
		)
	then
		AudioMessage("misns120.wav");
		M.cav3pathwarn2 = true;
	end
	
	if 
		(
		(M.cavpath4 == true) and 
		(
		(GetDistance (M.cav1, M.walkcam2) < 50.0)  or 
		(GetDistance (M.cav2, M.walkcam2) < 50.0)  or 
		(GetDistance (M.cav3, M.walkcam2) < 50.0)  or 
		(GetDistance (M.cav4, M.walkcam2) < 50.0)  or 
		(GetDistance (M.cav5, M.walkcam2) < 50.0)
		) and (M.cav4pathwarn1 == false)
		)
	then
		AudioMessage("misns119.wav");
		M.cav4pathwarn1 = true;
	end

	if 
		(
		(M.cavpath4 == true) and 
		(
		(GetDistance (M.cav1, M.hidcam1) < 100.0)  or 
		(GetDistance (M.cav2, M.hidcam1) < 100.0)  or 
		(GetDistance (M.cav3, M.hidcam1) < 100.0)  or 
		(GetDistance (M.cav4, M.hidcam1) < 100.0)  or 
		(GetDistance (M.cav5, M.hidcam1) < 100.0)
		) and (M.cav4pathwarn2 == false)
		)
	then
		AudioMessage("misns121.wav");
		M.cav4pathwarn2 = true;
	end--]]


-- END OF SCRIPT
	
end