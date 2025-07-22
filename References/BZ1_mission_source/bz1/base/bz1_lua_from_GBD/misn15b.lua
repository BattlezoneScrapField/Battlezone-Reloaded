-- Single Player NSDF Mission 14 Lua conversion, created by General BlackDragon. 

-- Single Table for all our save/load variables. This SP mission has too many variables to function with them independently. ("main function has > 200 local variables", or "Load having > 197 variables in assignment")
local M = {

-- bools
	found_group1 = false,
	found_group2 = false,
	got_dough = false,
	start_done = false,
	cca_here = false,
	found = false,
	won = false,
	lost = false,
	camera1 = false,
	camera2 = false,
	camera3 = false,
	--alien3 = false,
	misn15b = false,
	silo_built = false,
	tartarus = false,
-- Floats (really doubles in Lua)
	camera_time = 0,
	second_message = 0,
	sav_timer = 0,
	rendezvous1 = 0,
	rendezvous2 = 0,
	rcam1 = 0,
	rcam2 = 0,
	deny_time1 = 0,
	deny_time2 = 0,
	--misl_time = 0,
	check_time = 0, -- not to be confused with miller time!
-- Handles
	tart = nil,
	player = nil,
	scav1 = nil,
	scav2 = nil,
	scav3 = nil,
	muf1 = nil,
	tur1 = nil,
	art1 = nil,
	scavcam = nil,
	hov1 = nil,
	audmsg = nil,
	sat1 = nil,
	sat2 = nil,
	--sat3 = nil,
	--sat4 = nil,
	--sat5 = nil,
	--sat6 = nil,
	--goal = nil,
	--tank = nil,
	recy = nil,
	cam1 = nil,
	cam2 = nil,
	cam3 = nil,
	cam4 = nil,
	cam5 = nil,
	cam6 = nil,
	tank1 = nil,
	tank2 = nil,
	scav_du_jour = nil,
	savlist = { }, --[100] = nil,
-- Ints
	savcount = 0,
	silocount = 0
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

	M.second_message = 99999.0;
	M.sav_timer = 99999.0;
	M.rcam1 = 99999.0;
	M.rcam2 = 99999.0;

end

function AddObject(h)

	--[[
		This has M.lost its relevence
		if it works at all.  
	--]]
	if (GetTeamNum(h) == 1) 
	then
		if (IsOdf(h, "avscav"))
		then
			M.found = true;
			M.scav_du_jour =  h;
		else
			if (IsOdf(h,"absilo"))
			then
				M.silocount = M.silocount + 1;
			end
		end
	end

end

function showStuff()
	ClearObjectives();
	if (M.cca_here)
	then
		AddObjective("misn1501.otf","GREEN");
	else 
		AddObjective("misn1501.otf","WHITE");
	end
	
	if (M.found_group1)
	then
		AddObjective("misn1502.otf","GREEN");
	else 
		AddObjective("misn1502.otf","WHITE");
	end
	
	if (M.silo_built)
	then
		AddObjective("misn1503.otf","GREEN");
	else 
		AddObjective("misn1503.otf","WHITE");
	end
	
	if (M.won)
	then
		AddObjective("misn1504.otf","GREEN");
	else 
		AddObjective("misn1504.otf","WHITE");
	end
end

function Update()

-- START OF SCRIPT

	M.player = GetPlayerHandle();
	if ( not M.start_done)
	then
	--	SetAIP("misn15.aip");
		AddScrap(1,10);
		showStuff();
		if (GetHandle("misn15b") ~= nil ) 
		then	
			M.misn15b = true;
		else 
			M.misn15b = false;  -- is this that map.
		end
		M.tart = GetHandle("ubtart0_i76building");
		M.recy = GetHandle("avrecy0_recycler");
		M.cam1 = GetHandle("apcamr0_camerapod");
		M.cam2 = GetHandle("apcamr1_camerapod");
		M.cam3 = GetHandle("apcamr2_camerapod");
		M.cam4 = GetHandle("apcamr3_camerapod");
		M.cam5 = GetHandle("apcamr4_camerapod");
		M.cam6 = GetHandle("apcamr5_camerapod");
		M.tank1 = GetHandle("svtank0_wingman");
		M.tank2 = GetHandle("svtank1_wingman");
		M.hov1 = GetHandle("svapc0_apc");
		--M.goal = GetHandle("eggeizr15_geyser");
		M.rendezvous1 = GetTime()+180.0;
		M.rendezvous2 = GetTime()+240.0;
		M.deny_time1 = GetTime()+300.0;
		M.deny_time2 = GetTime()+400.0;
		M.check_time = GetTime()+5.0;
		--[[
			local misl = BuildObject("waspmsl",2,M.cam1);
			VECTOR_3D from_vec,to_vec;
			from_vec = GetOrigin(misl, );
			to_vec = GetOrigin(M.player, );
			VECTOR_3D dir = SubVectors(to_vec,from_vec);
			SetFrontVector(misl, dir);
		--]]
		--[[ 
			All the units below
			start frozen
			until you go to 
			them.  
		--]]
		--[[
			M.scav1 = GetHandle("avscav6_scavenger");
			M.scav2 = GetHandle("avscav7_scavenger");
			M.scav3 = GetHandle("avscav8_scavenger");
			M.muf1 = GetHandle("avmuf0_factory");
			M.art1 = GetHandle("avartl0_howitzer");
			M.tur1 = GetHandle("avturr0_turrettank");
		--]]
		SetObjectiveName(M.cam1, "Geyser Site");
		SetObjectiveName(M.cam2, "NW Geyser");
		SetObjectiveName(M.cam3, "NE Geyser");
		SetObjectiveName(M.cam4, "Geyser Site");
		SetObjectiveName(M.cam5, "Supply");
		SetObjectiveName(M.cam6, "Nav Bravo");
		Goto(M.tank1,"tank_path",0);
		Goto(M.tank2,"tank_path",0);
		Goto(M.hov1,"tank_path",0);
		M.audmsg = AudioMessage("misn1501.wav");
		M.second_message = GetTime()+2.0; -- was 20.0
		M.sav_timer = GetTime()+120.0;
		--M.misl_time = 40.0;
		-- so that missiles always have a target
		M.scav_du_jour = M.recy;
		M.start_done = true;
		if (M.cam6 ~= nil) then
			SetUserTarget(M.cam6);
		end
	end
	if ((IsAudioMessageDone(M.audmsg))
		 and  (GetTime()>M.second_message))
	then
		--[[
			The workers tank
			battalion will help you out. 
		--]]
		AudioMessage("misn1502.wav");
		CameraReady();
		M.camera_time = GetTime()+8.0;
		M.second_message = 99999.0;
		M.camera1 = true;
	end
	if (M.camera1)
	then
		CameraObject(M.tank1,800,600,1200,M.tank1);
	end
	if ((M.camera1) and ((GetTime()>M.camera_time)  or  CameraCancelled()))
	then
		M.camera1 = false;
		CameraFinish();
	end
	if (( not M.cca_here) and 
		((GetDistance(M.cam6,M.tank1)<100.0)  or 
		(GetDistance(M.cam4,M.tank1)<100.0)))
	then
		M.cca_here = true;
		AudioMessage("misn1503.wav");
		showStuff();
	end
	if (( not M.found_group1) and (GetTime()>M.rendezvous1))
	then
		SetUserTarget(M.cam2);
		AudioMessage("misn1511.wav");
		M.rendezvous1 = 99999.0;
	end

	
	if (( not M.found_group1) and (GetDistance(M.cam2,M.player)<150.0))  -- was 200.0
	then
		--[[
			Play a wave that you
			got reinforcements
		--]]
	
		AudioMessage("misn1518.wav");
		M.scavcam = exu.BuildAsyncObject("avscav",1,"scav3here");
		exu.BuildAsyncObject("avapc",1,"mufhere");
		exu.BuildAsyncObject("avturr",1,"turhere");
		M.found_group1 = true;
		showStuff();
		M.camera2 = true;
		M.rcam1 = GetTime()+3.0;
		CameraReady();
	end
	if (M.camera2)
	then
		CameraPath("rescue_cam1",1000,0,M.scavcam);
	end
	
	if ((M.found_group1) and (GetTime()>M.rcam1))
	then
		M.camera2 = false;
		M.rcam1 = 99999.0;
		CameraFinish();
	end
	--[[
	if (( not M.found_group2) and (GetTime()>M.rendezvous2))
	then
		SetUserTarget(M.cam3);
		AudioMessage("misn1512.wav");
		M.rendezvous2 = 99999.0;
	end
	if (( not M.found_group2) and (GetDistance(M.cam3,M.player)<150.0)) -- was 200.0
	then
		
		--	Play a wave that you
		--	got reinforcements
		
		AudioMessage("misn1514.wav");
		M.scavcam = BuildObject("avscav",1,"scav1here");
		BuildObject("avscav",1,"scav2here");
		BuildObject("avartl",1,"arthere");
		M.found_group2 = true;
		M.camera3 = true;
		M.rcam2 = GetTime()+3.0;
		CameraReady();
	end
	if (M.camera3)
	then
		CameraPath("rescue_cam2",1000,0,M.scavcam);
	end
	
	if ((M.found_group2) and (GetTime()>M.rcam2))
	then
		M.camera3 = false;
		M.rcam2 = 99999.0;
		CameraFinish();
	end
	--]]
	--[[
		if titan relic found
		and NOT played warning
		AudioMessage("misn1513.wav");
	--]]
	if (( not M.tartarus) and (GetDistance(M.player,M.tart)<150.0))
	then
		M.tartarus = true;
		AudioMessage("misn1513.wav");
		AudioMessage("misn1514.wav");
	end
	if ((GetTime()>M.sav_timer) and (M.savcount<50))  -- 50 is the max in case
	then
		
		local sav = nil;
		if ((math.random(0 1)) == 1)
		then
			sav = exu.BuildAsyncObject("hvsav",2,"alien1");
			Attack(sav,M.scav_du_jour);
		else
			sav = exu.BuildAsyncObject("hvsav",2,"alien2");
			Attack(sav,M.scav_du_jour);
		end
		M.sav_timer = GetTime()+240.0;  -- was (rand()%5+9)*10.0;
		M.savcount = M.savcount + 1;
		M.savlist[M.savcount] = sav;
	end
	--[[
		My scheduler
		All the features of the
		Dark Rein AI
		at a fraction of the CPU
		cost.
	--]]
	if (GetTime()>M.check_time)
	then
		local count = nil;
		for count = 1, M.savcount do
			if ((IsAlive(M.savlist[count]))
				 and  (GetCurrentCommand(M.savlist[count]) == AiCommand.NONE))
			then
				Goto(M.savlist[count],"alien_path");
			end
		end
		M.check_time = GetTime()+5.0;
	end
	--[[
		Deny the main scrap
		fields to the 
		enemy.
	--]]
	if ((M.misn15b) and (GetTime()>M.deny_time1))
	then
		M.sat1 = exu.BuildAsyncObject("hvsat",2,"alien1");
		M.sat2 = exu.BuildAsyncObject("hvsat",2,"alien1");
		Goto(M.sat1,"deny1");
		Goto(M.sat2,"deny1");
		M.deny_time1 = 99999.0;
	end
	--[[
		Deny the main scrap
		fields to the 
		enemy.
	--]]
	if ((M.misn15b) and (GetTime()>M.deny_time2))
	then
		M.sat1 = exu.BuildAsyncObject("hvsat",2,"alien2");
		M.sat2 = exu.BuildAsyncObject("hvsat",2,"alien2");
		Goto(M.sat1,"deny2");
		Goto(M.sat2,"deny2");
		M.deny_time2 = 99999.0;
	end

	if (( not M.lost) and ( not IsAlive(M.recy)))
	then
		--[[
			Message:
			Without the resources,
			Titan is M.lost.
		--]]

		AudioMessage("misn1414.wav");
		M.lost = true;
		FailMission(GetTime()+10.0,"misn15l1.des");
	end

	if ((M.silocount>1) and ( not M.silo_built))
	then
		M.silo_built = true;
		showStuff();
	end
	if (( not M.got_dough) and (GetScrap(1)>74))
	then
		ClearObjectives();
		AddObjective("misn1501.otf","GREEN");
		AddObjective("misn1502.otf","GREEN");
		AddObjective("misn1503.otf","GREEN");
		AddObjective("misn1504.otf","GREEN");
		M.got_dough = true;
		AudioMessage("misn1510.wav");
			--[[
				Congratulations
			--]]
		SucceedMission(GetTime() +10.0,"misn15w1.des");
	end

-- END OF SCRIPT
	
end