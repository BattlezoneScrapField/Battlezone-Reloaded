-- Single Player NSDF Mission 6 Lua conversion, created by General BlackDragon. 

-- Single Table for all our save/load variables. This SP mission has too many variables to function with them independently. ("main function has > 200 local variables", or "Load having > 197 variables in assignment")
local M = {

-- bools
	test = false,
	utah_found = false,
	start_done = false,
	out_of_car = false,
	alarm_on = false,
	start_evac = false,
	--ccaguntower1_down = false,
	--ccaguntower2_down = false,
	--radar_dead = false,
	--player_dead = false,
	--over_wall = false,
	--guntower_attacked = false,
	--fence_off = false,
	rendezvous = false,
	--recon_message1 = false,
	recon_message2 = false,
	--build_scouts = false,
	jump_cam_spawned = false,
	rookie_moved = false,
	becon_build = false,
	free1 = false,
	free2 = false,
	p1_retreat = false,
	p2_retreat = false,
	p3_retreat = false,
	p4_retreat = false,
	--retreat_message_done = false,
	first_objective = false,
	second_objective = false,
	turret_move = false,
	next_mission = false,
	rookie_lost = false,
	mine_pathed = false,
	detected = false,
	getum = false,
	patrola1 = false,
	patrola2 = false,
	patrolb1 = false,
	patrolb2 = false,
	patrolc1 = false,
	patrolc2 = false,
	retreat_success = false,
	detected_message = false,
	fighter_moved = false,
	unit_spawn = false,
	vehicle_stolen = false,
	trigger1 = false,
	alarm_special = false,
	m_on = { }, --[111] = false,
	m_dead = { }, --[111] = false,
	alarm_sound = false,
	rookie_removed = false,
	forces_enroute = false,
	--test_tank_built = false,
	camera1_on = false,
	camera2_on = false,
	camera3_on = false,
	camera4_on = false,
	camera_off = false,
	camera2_oned = false,
	camera3_oned = false,
	camera_ready = false,
	tank_switch = false,
	--sound_started = false,
	test_found = false,
	game_over = false,
	first_camera_ready = false,
	first_camera_off = false,
	cute_camera_ready = false,
	cute_camera_off = false,
	radar_camera_off = false,
	--next_camera_on = false,
	rookie_jumped = false,
	tower_warning = false,
	rookie_found = false,
	opening_vo = false,
	shot1 = false,
	shot2 = false,
-- Floats (really doubles in Lua)
	unit_spawn_time = 0,
	recon_message_time = 0,
	becon_build_time = 0,
	rookie_rendezvous_time = 0,
	getaway_message_time = 0,
	patrol2_move_time = 0,
	rookie_move_time = 0,
	alarm_time = 0,
	alarm_timer = 0,
	rendezous_check = 0,
	alarm_check = 0,
	rookie_remove_time = 0,
	runner_check = 0,
	check_jump_geyser = 0,
	reach_mine_time = 0,
	check_range = 0,
	change_angle = 0,
	change_angle1 = 0,
	change_angle2 = 0,
	change_angle3 = 0,
	switch_tank = 0,
	start_sound = 0,
	recon_message2_time = 0,
	first_camera_time = 0,
	radar_camera_time = 0,
	next_mission_time = 0,
	cute_camera_time = 0,
	next_shot_time = 0,
	tower_check = 0,
-- Handles
	user = nil,
	nsdfrecycle = nil,
	nsdfmuf = nil,
	rookie = nil,
	jump_cam = nil,
	jump_geyz = nil,
	remove_geyz = nil,
	mine_geyz = nil,
	pilot1 = nil,
	pilot2 = nil,
	pilot3 = nil,
	pilot4 = nil,
	pilot5 = nil,
	ccaguntower1 = nil,
	ccaguntower2 = nil,
	ccacomtower = nil,
	powrplnt1 = nil,
	powrplnt2 = nil,
	--parkedtank1 = nil,
	--parkedtank2 = nil,
	--parkedtank3 = nil,
	--parkedtank4 = nil,
	barrack1 = nil,
	barrack2 = nil,

	nav1 = nil,
	--nav2 = nil,
	nav3 = nil,
	nav4 = nil, --[[is becon5--]]
	nav5 = nil, --[[is becon6--]]
	nav6 = nil,
	nav7 = nil,
	becon1 = nil,
	becon2 = nil,
	becon3 = nil,
	becon4 = nil,

	wingman1 = nil,
	wingman2 = nil,
	wingtank1 = nil,
	wingtank2 = nil,
	wingtank3 = nil,
	wingturret1 = nil,
	wingturret2 = nil,
	nsdfarmory = nil,
	svapc = nil,

	m = { }, --[111] = nil,

	ccarecycle = nil,
	ccamuf = nil,
	--ccaslf = nil,
	basepowrplnt1 = nil,
	pbaseowrplnt2 = nil,
	ccabaseguntower1 = nil,
	ccabaseguntower2 = nil,
	guard_tank1 = nil,
	guard_tank2 = nil,
	--guard_tank3 = nil,
	test_tank = nil,
	patrol1_1 = nil,
	patrol1_2 = nil,
	--patrol1_3 = nil,
	svpatrol1_1 = nil,
	svpatrol1_2 = nil,
	svpatrol1_3 = nil,
	svpatrol2_1 = nil,
	svpatrol2_2 = nil,
	svpatrol2_3 = nil,
	svpatrol3_1 = nil,
	svpatrol3_2 = nil,
	svpatrol3_3 = nil,
	svpatrol4_1 = nil,
	svpatrol4_2 = nil,
	guard_turret1 = nil,
	guard_turret2 = nil,
	spawn_turret1 = nil,
	spawn_turret2 = nil,
	parked1 = nil,
	parked2 = nil,
	parked3 = nil,
	parkturret1 = nil,
	parkturret2 = nil,
	--spawn_point = nil,
	--fence = nil,
	test_turret = nil,
	tank_spawn = nil,
	--power1_geyser = nil,
	--power2_geyser = nil,
	radar_geyser = nil,
	camera_geyser = nil,
	show_geyser = nil,
	new_tank1 = nil,
	new_tank2 = nil,
-- AiPaths
	turret1_spot = nil, 
	mine = { }, --[111] = nil,
-- Ints
	--count = 0,
	mine_check = 0,
	x = 0,
	units = 0,
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

	M.mine_check = 1;
	M.x = 6000;
	M.units = 1;
	
	for i = 1, 111 do
		M.mine[i] = nil;
		M.m_on[i] = false;
		M.m_dead[i] = false;
	end

	M.unit_spawn_time = 99999.0;
	M.recon_message_time = 99999.0;
	M.becon_build_time = 99999.0;
	M.rookie_move_time = 99999.0;
	M.getaway_message_time = 99999.0;
	M.rookie_rendezvous_time = 99999.0;
	M.patrol2_move_time = 99999.0;
	M.alarm_time = 99999.0;
	M.alarm_timer = 99999.0;
	M.rendezous_check = 99999.0;
	M.alarm_check = 99999.0;
	M.rookie_remove_time = 99999.0;
	M.runner_check = 99999.0;
	M.check_jump_geyser = 99999.0;
	M.reach_mine_time = 99999.0;
	M.check_range = 99999.0;
	M.change_angle = 99999.0;
	M.change_angle1 = 99999.0;
	M.change_angle2 = 99999.0;
	M.change_angle3 = 99999.0;
	M.switch_tank = 99999.0;
	M.start_sound = 99999.0;
	M.recon_message2_time = 99999.0;
	M.first_camera_time = 99999.0;
	M.cute_camera_time = 99999.0;
	M.radar_camera_time = 99999.0;
	M.next_mission_time = 99999.0;
	M.next_shot_time = 99999.0;
	M.tower_check = 99999.0;

	M.jump_geyz = GetHandle("volcano_geyz1");
	M.remove_geyz = GetHandle("volcano_geyz2");
	M.ccaguntower1 = GetHandle("sgtower1");
	M.ccaguntower2 = GetHandle("sgtower2");
	M.ccacomtower = GetHandle("radar_array");
	M.powrplnt1 = GetHandle("power1");
--	M.powrplnt2 = GetHandle("power2");
	M.barrack1 = GetHandle("hut1");
	M.barrack2 = GetHandle("hut2");

	M.nav3 = GetHandle("cam3");

	M.wingman1 = GetHandle("avfigh1");
	M.wingtank1 = GetHandle("avtank1");
	M.wingtank2 = GetHandle("avtank2");
	M.wingtank3 = GetHandle("avtank3");
	M.wingturret1 = GetHandle("avturret1");
	M.wingturret2 = GetHandle("avturret2");
	M.nsdfarmory = GetHandle("avslf");

	M.ccarecycle = GetHandle("svrecycler");
	M.ccamuf = GetHandle("svmuf");
	M.basepowrplnt1 = GetHandle("svbasepower1");
	M.pbaseowrplnt2 = GetHandle("svbasepower2");
--	M.ccabaseguntower1 = GetHandle("svbasetower1");
--	M.ccabaseguntower2 = GetHandle("svbasetower2");
--	M.guard_tank1 = GetHandle("svtank1");
--	M.guard_tank2 = GetHandle("svtank2");
	M.patrol1_1 = GetHandle("svfigh1");
	M.patrol1_2 = GetHandle("svfigh2");

	M.svpatrol1_1 = GetHandle("svpatrol1_1");
	M.svpatrol1_2 = GetHandle("svpatrol1_2");
	M.svpatrol2_1 = GetHandle("svpatrol2_1");
	M.svpatrol2_2 = GetHandle("svpatrol2_2");
	M.svpatrol3_1 = GetHandle("svpatrol3_1");
	M.svpatrol3_2 = GetHandle("svpatrol3_2");
	M.svpatrol4_1 = GetHandle("svpatrol4_1");
	M.svpatrol4_2 = GetHandle("svpatrol4_2");
--	M.test_tank = GetHandle("test_tank");
	M.guard_turret1 = GetHandle("svturret1");
	M.guard_turret2 = GetHandle("svturret2");
	M.parked1 = GetHandle("parked1");
	M.parked2 = GetHandle("parked2");
	M.parked3 = GetHandle("parked3");
	M.parkturret1 = GetHandle("pturret1");
	M.parkturret2 = GetHandle("pturret2");
	M.svapc = GetHandle("parked_svapc");
	--M.spawn_point = GetHandle("recycle_spawn_geyz");
--	M.test_turret = GetHandle("test_turret");
--	M.mine_geyz = GetHandle("");
--	M.tank_spawn = GetHandle("test_tank_spawn");
	M.radar_geyser = GetHandle("radar_geyser");
	M.camera_geyser = GetHandle("camera_geyser");
	M.show_geyser = GetHandle("show_geyser");
	
end

function AddObject(h)


end

function Update()

-- START OF SCRIPT

	-- Here is where you put what happens  every frame.  

	M.user = GetPlayerHandle(); --assigns the player a handle every frame

	M.mine_check = M.mine_check + 10;

	if (M.mine_check > 110)
	then
		M.mine_check = 1;
	end

--[[	if ( not M.first_camera_ready)
	then
		CameraReady();
		M.audmsg = AudioMessage("misn0700.wav"); -- General "mission breifing"
		M.first_camera_time = GetTime() + 10.0;
		M.first_camera_ready = true;
	end

	if ((M.first_camera_ready) and ( not M.first_camera_off))
	then
		CameraPath("start_camera", M.x, 950, M.user);
		M.x = M.x - 100;
	end

	if ((M.first_camera_ready) and ( not M.first_camera_off) and ((CameraCancelled())  or  (M.first_camera_time < GetTime())))
	then
		CameraFinish();
		M.first_camera_off = true;
	end

	if (CameraCancelled())
	then
		StopAudioMessage(M.audmsg);
	end
--]]
	if ( not M.start_done)
	then 

		SetObjectiveName(M.nav3, "Rendezvous Point");

		SetScrap(1, 10);

		SetObjectiveOff(M.ccacomtower);
		Patrol(M.patrol1_1, "patrol_path3");	--
		Patrol(M.patrol1_2, "patrol_path3");	--
--		Patrol(M.guard_tank1, "guard_path");	--
--		Patrol(M.guard_tank2, "guard_path");	-- sets enemy M.units to their patrol routes
		Patrol(M.svpatrol3_1, "patrol_path1");--
		Patrol(M.svpatrol3_2, "patrol_path1");--
		Patrol(M.svpatrol4_1, "patrol_path2");--
		Patrol(M.svpatrol4_2, "patrol_path2");--

		SetIndependence(M.wingtank2, 0);
		Stop(M.wingtank2);
		SetPerceivedTeam(M.wingtank2, 1);
		SetIndependence(M.wingtank3, 0);
		Stop(M.wingtank3);
		SetPerceivedTeam(M.wingtank3, 1);

		Stop(M.svpatrol2_1, 1);
		Stop(M.svpatrol2_2, 1);

		M.rendezous_check = GetTime() + 9.0;
		M.patrol2_move_time = GetTime () + 121.0;
		M.alarm_check = GetTime() + 27.0;

		M.turret1_spot = GetPosition("turret1_spot");
		for i = 1, 111 do
			local name = string.format("m%0.3d", i-1);
			--sprintf(name, "m%0.3d", i);
			M.mine[i] = GetPosition(name);
		end

		M.start_done = true;
	end

--	if (CameraCancelled())
--	then
--		StopAudioMessage(M.audmsg);
--	end

	if (( not M.opening_vo) and (M.start_done) and (M.rendezous_check < GetTime()))
	then
		M.rendezous_check = GetTime() + 15.0;
		AudioMessage("misn0700.wav"); -- General "mission breifing"
		ClearObjectives();
		AddObjective("misn0700.otf", "WHITE");
		M.opening_vo = true;
	end

	if ((M.start_done) and (M.patrol2_move_time < GetTime () and ( not M.rendezvous)) 
		 and  (IsAlive(M.svpatrol2_1))  and (IsAlive(M.svpatrol2_2)) and ( not M.fighter_moved))
--		 and  (GetHealth(M.svpatrol2_1)<0.98f) -- (GetLastEnemyShot(M.svpatrol2_1)<0)
--		 and  (GetHealth(M.svpatrol2_2)<0.98f)) --(GetLastEnemyShot(M.svpatrol2_2)<0)) 
	then
		Patrol(M.svpatrol2_1, "patrol_path1");-- sets enemy M.units to their patrol routes 
		Patrol(M.svpatrol2_2, "patrol_path1");-- sets enemy M.units to their patrol routes
		M.fighter_moved = true;
	end

-- this is when the player M.rendezvous with the other tanks 
if ( not M.first_objective)
then																							
	if ((M.rendezous_check < GetTime()) and ( not M.rendezvous) and ( not M.alarm_on))
	then
		M.rendezous_check = GetTime() + 3.0;

		if ((IsAlive(M.wingtank2)) and (GetDistance(M.user,M.wingtank2) < 150.0) and ( not M.rendezvous)  or 
			((IsAlive(M.wingtank3)) and (GetDistance(M.user,M.wingtank3) < 150.0) and ( not M.rendezvous)))		
		then																					
			M.audmsg = AudioMessage("misn0701.wav"); -- greetings comander "standby"
			if (IsAlive(M.wingtank2))
			then
				local MAT_3D M = GetTransform(M.wingtank2);
				RemoveObject(M.wingtank2);
				M.new_tank1 = exu.BuildAsyncObject("avtank", 1, M);
			end
			if (IsAlive(M.wingtank3))
			then
				local MAT_3D M = GetTransform(M.wingtank3);
				RemoveObject(M.wingtank3);
				M.new_tank2 = exu.BuildAsyncObject("avtank", 1, M);
			end
			ClearObjectives();																
			AddObjective("misn0700.otf", "GREEN");											
			AddObjective("misn0701.otf", "WHITE");										
			M.recon_message_time = GetTime() + 240.0;
			M.runner_check = GetTime() + 6.0; 
			M.patrol2_move_time = GetTime () + 60.0;
			M.nav1 = exu.BuildAsyncObject ("apcamr", 1, "cam1_spawn"); --outpost cam
			SetObjectiveName(M.nav1, "CCA Outpost");
			M.tower_check = GetTime() + 10.0;
			M.rendezvous = true;														
		end	
	end
	
	if ((M.rendezvous) and (M.patrol2_move_time < GetTime()) and ( not M.fighter_moved))
	then
		if (M.svpatrol2_1 ~= nil)
		then
			Attack(M.svpatrol2_1, M.user);
		end
		if (M.svpatrol2_2 ~= nil)
		then
			Attack(M.svpatrol2_2, M.user);
		end

		M.fighter_moved = true;
	end
															
--[[	if ((M.rendezvous) and (IsAlive (M.wingtank3)) and ( not M.free1))				
	then																		
		Stop(M.wingtank3, 0);												
		M.free1 = true;														
	end																			
																							
	if ((M.rendezvous) and (IsAlive (M.wingtank2)) and ( not M.free2))									
	then																					
		Stop(M.wingtank2, 0);															
		M.free2 = true;																		
	end
--]]
	if ((IsAlive(M.nav1)) and (M.tower_check < GetTime()) and ( not M.tower_warning))
	then
		M.tower_check = GetTime() + 4.0;

		if (GetDistance(M.user, M.nav1) < 90.0)
		then
			AudioMessage("misn0716.wav");
			M.tower_warning = true;
		end
	end
end

-- this is when the M.rookie tells the player about the overlook into the base and lays down a camera
------------------------------ROOKIE SCRIPT 1 HE JUMPS IN FRONT OF PLAYER ----------------------------	
--[[																										
if (( not M.first_objective) and ( not M.alarm_on) and ( not M.out_of_car))
then
	if ((M.rendezvous) and ( not M.jump_cam_spawned) and (M.recon_message_time < GetTime()))
	then
		M.recon_message_time = GetTime() + 20.0;

	    if ((GetDistance(M.user, M.jump_geyz) > 400.0) and (GetDistance(M.user, M.ccacomtower) > 150.0))
		then																											
--			AudioMessage("misn0702.wav"); -- Rookie "I found an overlook"										
			AudioMessage("win.wav"); -- Rookie trasmits a broken message saying he's found a way in and screams YAAAAAAAHHHHHHOOOOOO not 
			M.jump_cam = BuildObject ("apcamr", 1, "jump_cam_spawn"); --Rookie drops camera			
			M.rookie = BuildObject ("avfigh", 1, M.jump_geyz);-- spawn in M.rookie										
			Goto (M.rookie, M.jump_cam);--M.rookie goes to jump-cam to get in picture
			M.rookie_move_time = GetTime() + 20.0; -- sets time to move M.rookie to secret spot
			M.recon_message2_time = GetTime() + 480.0;
			M.jump_cam_spawned = true;																				
		end																											
	end																																																						--
	
	if ((M.jump_cam_spawned) and (M.jump_cam ~= nil))
	then
		SetObjectiveName(M.jump_cam, "Volcano Peak");
	end
	
	if ((M.jump_cam_spawned) and (M.rookie_move_time < GetTime()) and ( not M.rookie_moved))								
	then																											
		Defend(M.rookie, 1); 
		M.rookie_remove_time = GetTime() + 15.0;
		M.rookie_moved = true;																					
	end																							
	
	if ((M.rookie_moved) and (M.rookie_remove_time < GetTime()) and ( not M.rookie_removed))
	then
		M.rookie_remove_time = GetTime() + 5.0;

		if (IsAlive(M.rookie))
		then
			Defend(M.rookie, 1);

			if (GetDistance(M.user, M.rookie) < 70.0)
			then
				M.audmsg = AudioMessage("win.wav");
				M.rookie_removed = true;
			end
		end
	end

	if ((M.rookie_removed) and (IsAudioMessageDone(M.audmsg)) and ( not M.rookie_jumped))
	then
		Damage(M.rookie, 5000);
		M.rookie_jumped = true;
	end

--	if ((M.rookie_moved) and (M.rookie_remove_time < GetTime()) and ( not M.rookie_removed)) -- M.rookie reaches secret spot
--	then																								
--		RemoveObject(M.rookie);-- I take M.rookie away so that he is safe
--		M.rookie_removed = true;
--	end
end
--]]
------------------------------ROOKIE SCRIPT 2 HE JUMPS ON CAMERA ----------------------------
if (( not M.first_objective) and ( not M.alarm_on) and ( not M.out_of_car))
then
	if ((M.rendezvous) and ( not M.jump_cam_spawned) and ((M.recon_message_time < GetTime())  or  (M.tower_warning)))
	then
		M.recon_message_time = GetTime() + 5.0;
		M.units = CountUnitsNearObject(M.user, 200.0, 2, "svfigh");

	    if ((GetDistance(M.user, M.jump_geyz) > 400.0) and (M.units == 0))
		then
			AudioMessage("misn0702.wav"); -- Rookie trasmits a broken message saying player should look at camera
			M.jump_cam = exu.BuildAsyncObject ("apcamr", 1, "jump_cam_spawn");
			M.rookie = exu.BuildAsyncObject ("avfigh", 1, M.jump_geyz);
			Follow (M.rookie, M.jump_geyz);
			M.rookie_move_time = GetTime() + 10.0;
--			M.recon_message2_time = GetTime() + 480.0;
			M.jump_cam_spawned = true;
		end
	end

	if ((M.jump_cam_spawned) and (M.jump_cam ~= nil))
	then
		SetObjectiveName(M.jump_cam, "Volcano Peak");
	end
	
	if ((M.jump_cam_spawned) and (M.rookie_move_time < GetTime()) and ( not M.rookie_moved))								
	then
--		if (IsAlive(M.rookie))
--		then
--			Defend(M.rookie, 1);
--		end
		M.rookie_remove_time = GetTime() + 10.0;
		M.rookie_moved = true;
	end

	if ((M.rookie_moved) and (M.rookie_remove_time < GetTime()) and ( not M.rookie_found))
	then
		M.rookie_remove_time = GetTime() + 3.0;	
		
		if (IsAlive(M.rookie))
		then
--			Defend(M.rookie);

			if (GetDistance(M.user, M.rookie) < 70.0)
			then
				Defend(M.rookie, 1);
				AudioMessage("misn0718.wav"); -- M.rookie sends broken message he's found a way inside base
				M.rookie_remove_time = GetTime() + 10.0;
				M.rookie_found = true;
			end
		end
	end
	
	if ((M.rookie_found) and (M.rookie_remove_time < GetTime()) and ( not M.rookie_removed))
	then
		if (IsAlive(M.rookie))
		then
			AudioMessage("misn0715.wav");-- screams YAAAAAAAHHHHHHOOOOOO not 
			EjectPilot(M.rookie);
			M.rookie_removed = true;
		end
	end
end
																							
-- end M.rookie at overlook - he heads off to mine field ----------------------------------





-- this is when the player tries to go into the radar array base w/out jumping in (in his tank) 

	if ((M.alarm_check < GetTime()) and ( not M.alarm_on))
	then

		M.alarm_check = GetTime() + 5.0;

--[[		if (( not M.alarm_on) and ( not M.out_of_car) and (GetDistance(M.user, M.turret1_spot) < 90.0))-- this is if the player attacks the gun towers around the solar array
		then
			AudioMessage("misn0710.wav");-- you've tripped the alarm
			SetObjectiveOn(M.ccacomtower);
			SetObjectiveName(M.ccacomtower, "Radar Array");
			M.alarm_on = true;
		end
--]]
		if (( not M.alarm_on) and ( not M.out_of_car) and (GetDistance(M.user, M.turret1_spot) < 70.0))-- this is if the player attacks the gun towers around the solar array
		then
			AudioMessage("misn0710.wav");-- you've tripped the alarm
			SetObjectiveOn(M.ccacomtower);
			SetObjectiveName(M.ccacomtower, "Radar Array");
			M.alarm_on = true;
		end

	end

-- end of player trying to enter radar base in tank 
-- now that the alarm is on the task will be more difficult
if ( not M.first_objective)
then
	if (M.alarm_on)
	then
		-- this code makes the alarm sound
		if ((M.ccacomtower ~= nil) and (GetDistance(M.user, M.ccacomtower) < 170.0) and ( not M.alarm_sound))
		then
			AudioMessage("misn0708.wav"); -- this is the alarm sound		
			M.alarm_timer = GetTime() + 6.0;
			M.alarm_sound = true;
		end

		if ((M.alarm_sound) and (M.alarm_timer < GetTime()))
		then
			M.alarm_sound = false;
		end

		if ( not M.turret_move)
		then
			SetObjectiveOn(M.ccacomtower);
			SetObjectiveName(M.ccacomtower, "Radar Array");
			Retreat (M.guard_turret1, M.ccacomtower, 1);
			Retreat (M.guard_turret2, M.ccacomtower, 1);
			M.turret_move = true;
		end

		if ( not M.start_evac) --starts clock to spawn cca soldiers
		then
			M.unit_spawn_time = GetTime() + 20.0;
			M.start_evac = true;
		end

		if ((M.start_evac) and (M.unit_spawn_time < GetTime()) and ( not M.unit_spawn) and ( not M.alarm_special))-- spawns cca soldiers and tells them to go to their tanks
		then
			M.pilot1 = exu.BuildAsyncObject("sspilo",2,"hut2_spawn");
			M.pilot2 = exu.BuildAsyncObject("sspilo",2,"hut2_spawn");
			M.pilot3 = exu.BuildAsyncObject("sspilo",2,"hut2_spawn");
			M.pilot4 = exu.BuildAsyncObject("sspilo",2,"hut1_spawn");
			M.pilot5 = exu.BuildAsyncObject("sspilo",2,"hut1_spawn");
			if (M.parkturret1 ~= M.user) then
				local MAT_3D M = GetTransform(M.parkturret1);
				RemoveObject(M.parkturret1);
				M.spawn_turret1 = exu.BuildAsyncObject("svturr", 2, M);
				Defend(M.spawn_turret1);
			end
			if (M.parkturret2 ~= M.user) then
				local MAT_3D M = GetTransform(M.parkturret2);
				RemoveObject(M.parkturret2);
				M.spawn_turret2 = exu.BuildAsyncObject("svturr", 2, M);
				Defend(M.spawn_turret2);
			end
			-- these lines tell the soviet pilots to get to their ships
			if (M.parked1 ~= nil)
			then
				Retreat(M.pilot1, M.parked1, 1);
			end
			
			if (M.parked2 ~= nil)
			then
				Retreat(M.pilot2, M.parked2, 1);
			end

			if (M.parked3 ~= nil)
			then
				Retreat(M.pilot3, M.parked3, 1);
			end
		
			M.unit_spawn = true;
		end
		-- this is what happens when the player is in the base and sets off the alarm while out of a vehcile
		if ((M.start_evac) and (M.alarm_special) and (M.unit_spawn_time < GetTime()) and ( not M.unit_spawn))-- spawns cca soldiers and tells them to go to their tanks
		then
			M.pilot1 = exu.BuildAsyncObject("sspilo",2,"hut2_spawn");
			M.pilot2 = exu.BuildAsyncObject("sspilo",2,"hut2_spawn");
			M.pilot3 = exu.BuildAsyncObject("sssold",2,"hut2_spawn");
			M.pilot4 = exu.BuildAsyncObject("sspilo",2,"hut1_spawn");
			M.pilot5 = exu.BuildAsyncObject("sssold",2,"hut1_spawn");
			Attack(M.pilot3, M.user);
			Attack(M.pilot5, M.user);
			-- these lines tell the soviet pilots to get to their ships
			if (M.parked1 ~= nil)
			then
				Retreat(M.pilot1, M.parked1, 1);
			end
			
			if (M.parked2 ~= nil)
			then
				Retreat(M.pilot2, M.parked2, 1);
			end

			if (M.parked3 ~= nil)
			then
				Retreat(M.pilot4, M.parkturret1, 1);
			end

			M.unit_spawn = true;
		end

		-- this is an attempt to find out if a pilot has gotten to his ship and then give them orders

		if ((M.unit_spawn) and ( not M.alarm_special))
		then
			if (( not IsAlive(M.pilot1)) and (M.parked1 ~= nil))
			then
				Attack(M.parked1, M.user);
			end
			if (( not IsAlive(M.pilot2)) and (M.parked2 ~= nil))
			then
				Attack(M.parked2, M.user);
			end
			if (( not IsAlive(M.pilot3)) and (M.parked3 ~= nil))
			then
				Attack(M.parked3, M.user);
			end

--[[			if (( not IsAlive(M.pilot4)) and (M.parkturret1 ~= nil))
			then
				Retreat(M.parkturret1, M.turret1_spot);		
			end
			if (( not IsAlive(M.pilot5)) and (M.parkturret2 ~= nil))
			then
				Retreat(M.parkturret2, "turret2_spot");
			end
--]]	
		end

		if ((M.unit_spawn) and (M.alarm_special))
		then
			if (( not IsAlive(M.pilot1)) and (M.parked1 ~= nil))
			then
				Goto(M.parked1, M.ccacomtower);
			end
			if (( not IsAlive(M.pilot2)) and (M.parked2 ~= nil))
			then
				Goto(M.parked2, M.ccacomtower);
			end
			if (( not IsAlive(M.pilot4)) and (M.parkturret1 ~= nil))
			then
				Retreat(M.parkturret1, "turret1_spot");
			end
		end

--		if ((( not M.alarm_special) and ( not IsAlive(M.ccaguntower1)) and ( not M.forces_enroute))  or  
--			(( not M.alarm_special) and ( not IsAlive(M.ccaguntower2)) and ( not M.forces_enroute)))
		if ((IsAlive(M.ccacomtower)) and (GetHealth(M.ccacomtower) < 0.50) and ( not M.forces_enroute))
		then
--			if (IsAlive(M.svpatrol1_1))
--			then
--				Goto(M.svpatrol1_1, M.ccacomtower, 1);
--			end
			if (IsAlive(M.svpatrol1_2))
			then
				Goto(M.svpatrol1_2, M.ccacomtower, 1);
			end
--			if (IsAlive(M.svpatrol2_1))
--			then
--				Goto(M.svpatrol2_1, M.ccacomtower, 1);
--			end
--			if (IsAlive(M.svpatrol2_2))
--			then
--				Goto(M.svpatrol2_2, M.ccacomtower, 1);
--			end
			if (IsAlive(M.svpatrol3_1))
			then
				Goto(M.svpatrol3_1, M.ccacomtower, 1);
			end
--			if (IsAlive(M.svpatrol3_2))
--			then
--				Goto(M.svpatrol3_2, M.ccacomtower, 1);
--			end
			if (IsAlive(M.svpatrol4_1))
			then
				Goto(M.svpatrol4_1, M.ccacomtower, 1);
			end
--			if (IsAlive(M.svpatrol4_2))
--			then
--				Goto(M.svpatrol4_2, M.ccacomtower, 1);
--			end

			M.forces_enroute = true;
		end
	end
end

-- this is what happens when the player parachutes into the base
if ( not M.first_objective)
then
	if (( not M.alarm_on) and ( not M.out_of_car) and (GetDistance(M.user, M.camera_geyser) < 160.0))-- this indicates that the player has parachuted into the solar array
	then
		SetObjectiveOn(M.ccacomtower);
		SetObjectiveName(M.ccacomtower, "Radar Array");		
--		M.cute_camera_time = GetTime() + 5.0;
		M.out_of_car = true;
	end

--[[	-- this will start the camera on the player
	if ((M.out_of_car) and ( not M.cute_camera_ready) and (M.cute_camera_time < GetTime()))
	then
		CameraReady();
		M.cute_camera_time = GetTime() + 5.0;
		M.cute_camera_ready = true;
	end

	if ((M.cute_camera_ready) and ( not M.cute_camera_off))
	then
		CameraObject(M.user, 800, 800, 10, M.user);	
	end

	if ((M.cute_camera_ready) and ( not M.cute_camera_off))
	then
		if (M.cute_camera_time < GetTime())
		then
			CameraFinish();
			M.cute_camera_off = true;
		end
	end
--]]
-- this indicates when the player has taken over a vehicle
	if (((M.out_of_car) and (IsOdf(M.user, "svtank")))  or  ((M.out_of_car) and (IsOdf(M.user, "svfigh")))  or 
		((M.out_of_car) and (IsOdf(M.user, "svturr"))) and ( not M.vehicle_stolen))
	then
--		M.alarm_time = GetTime() + 20.0;
		M.vehicle_stolen = true;
	end
	-- this simply means that if the player fires on anything while in the base he will set off an alarm
	if ( not M.trigger1 and M.out_of_car)
	then
		if (
			IsDamaged(M.ccaguntower1)  or 
			IsDamaged(M.ccaguntower2)  or 
			IsDamaged(M.ccacomtower)  or 
			IsDamaged(M.powrplnt1)  or 
			-- IsDamaged(M.powrplnt2)  or 
			IsDamaged(M.barrack1)  or 
			IsDamaged(M.barrack2)  or 
			IsDamaged(M.parked1)  or 
			IsDamaged(M.parked2)  or 
			IsDamaged(M.parked3)  or 
			IsDamaged(M.parkturret1)  or 
			IsDamaged(M.parkturret2)
			)
		then
			M.trigger1 = true;
		end
	end

	if ((M.trigger1) and (M.vehicle_stolen) and ( not M.alarm_on))
	then
		M.alarm_on = true;
	end
	if ((M.trigger1) and ( not M.vehicle_stolen) and ( not M.alarm_on))
	then
		M.alarm_on = true;
		M.alarm_special = true;
	end
end
-- end parachute into base
-- the following code triggers the solar array alarm if the player orders ANY of his M.units to attack the gun towers protecting it
if ( not M.first_objective)
then		
		if (( not M.alarm_on) and ( not M.out_of_car) and (GetDistance(M.wingman1, M.turret1_spot) < 100.0))
		then
			AudioMessage("misn0709.wav"); --I've tripped the alarm sir
			M.alarm_on = true;
		end

		if (( not M.alarm_on) and ( not M.out_of_car) and (GetDistance(M.wingman2, M.turret1_spot) < 100.0))
		then
			AudioMessage("misn0709.wav"); --I've tripped the alarm sir
			M.alarm_on = true;
		end

		if (( not M.alarm_on) and ( not M.out_of_car) and (GetDistance(M.wingtank1, M.turret1_spot) < 100.0))
		then
			AudioMessage("misn0709.wav"); --I've tripped the alarm sir
			M.alarm_on = true;
		end

		if (( not M.alarm_on) and ( not M.out_of_car) and (GetDistance(M.new_tank1, M.turret1_spot) < 100.0))
		then
			AudioMessage("misn0709.wav"); --I've tripped the alarm sir
			M.alarm_on = true;
		end

		if (( not M.alarm_on) and ( not M.out_of_car) and (GetDistance(M.new_tank2, M.turret1_spot) < 100.0))
		then
			AudioMessage("misn0709.wav"); --I've tripped the alarm sir
			M.alarm_on = true;
		end

--[[		if (( not M.alarm_on) and ( not M.out_of_car) and (GetDistance(M.wingturret1, M.turret1_spot) < 100.0))
		then
			AudioMessage("misn0709.wav"); --I've tripped the alarm sir
			M.alarm_on = true;
		end

		if (( not M.alarm_on) and ( not M.out_of_car) and (GetDistance(M.wingturret2, M.turret1_spot) < 100.0))
		then
			AudioMessage("misn0709.wav"); --I've tripped the alarm sir
			M.alarm_on = true;
		end

--]]
end
-- end of alarm trigger for other vehicles ----------------------------------------------------------
-- this is an attempt to make the soviets retreat --------------------------------------------------/
if ( not M.first_objective)
then
	if ( not M.retreat_success)
	then
		if (IsAlive(M.svpatrol1_2))
		then
			if (( not IsAlive (M.svpatrol1_1)) and (M.rendezvous) and (IsAlive(M.ccarecycle)) and ( not M.first_objective) 
				 and  ( not M.mine_pathed) and ( not M.alarm_on) and (GetDistance(M.user,M.svpatrol1_2) < 50.0)  and ( not M.p1_retreat)
				 and  ( not M.p2_retreat) and ( not M.p3_retreat))
			then
				Retreat(M.svpatrol1_2, M.ccarecycle);
				SetObjectiveOn(M.svpatrol1_2);
				SetObjectiveName(M.svpatrol1_2, "Runner");
				M.getaway_message_time = GetTime() + 3.0;
				M.p1_retreat = true;
			end
		end

		if (IsAlive(M.svpatrol1_1))
		then
			if (( not IsAlive (M.svpatrol1_2)) and (M.rendezvous) and (IsAlive(M.ccarecycle)) and ( not M.first_objective) 
				 and  ( not M.mine_pathed) and ( not M.alarm_on) and (GetDistance(M.user,M.svpatrol1_1) < 50.0)  and ( not M.p1_retreat)
				 and  ( not M.p2_retreat) and ( not M.p3_retreat))
			then
				Retreat(M.svpatrol1_1, M.ccarecycle);
				SetObjectiveOn(M.svpatrol1_1);
				SetObjectiveName(M.svpatrol1_1, "Runner");
				M.getaway_message_time = GetTime() + 3.0;
				M.p1_retreat = true;
			end
		end

--[[		if (( not IsAlive (M.svpatrol2_1)) and (M.rendezvous) and (IsAlive(M.ccarecycle)) and ( not M.first_objective) 
			 and  ( not M.mine_pathed) and ( not M.alarm_on) and (GetDistance(M.user,M.svpatrol2_2) < 50.0)  and ( not M.p2_retreat)
			 and  ( not M.p1_retreat) and ( not M.p3_retreat))
		then
			Retreat(M.svpatrol2_2, M.ccarecycle);
			SetObjectiveOn(M.svpatrol2_2);
			SetObjectiveName(M.svpatrol2_2, "Runner");
			M.getaway_message_time = GetTime() + 3.0;
			M.p2_retreat = true;
		end

		if (( not IsAlive (M.svpatrol2_2)) and (M.rendezvous) and (IsAlive(M.ccarecycle)) and ( not M.first_objective) 
			 and  ( not M.mine_pathed) and ( not M.alarm_on) and (GetDistance(M.user,M.svpatrol2_1) < 50.0)  and ( not M.p2_retreat)
			 and  ( not M.p1_retreat) and ( not M.p3_retreat))
		then
			Retreat(M.svpatrol2_1, M.ccarecycle);
			SetObjectiveOn(M.svpatrol2_1);
			SetObjectiveName(M.svpatrol2_1, "Runner");
			M.getaway_message_time = GetTime() + 3.0;
			M.p2_retreat = true;
		end
--]]
		if (IsAlive(M.svpatrol3_2))
		then
			if (( not IsAlive (M.svpatrol3_1)) and (M.rendezvous) and (IsAlive(M.ccarecycle)) and ( not M.first_objective) 
				 and  ( not M.mine_pathed) and ( not M.alarm_on) and (GetDistance(M.user,M.svpatrol3_2) < 50.0)  and ( not M.p2_retreat)
				 and  ( not M.p1_retreat) and ( not M.p3_retreat))
			then
				Retreat(M.svpatrol3_2, M.ccarecycle);
				SetObjectiveOn(M.svpatrol3_2);
				SetObjectiveName(M.svpatrol3_2, "Runner");
				M.getaway_message_time = GetTime() + 3.0;
				M.p3_retreat = true;
			end
		end

		if (IsAlive(M.svpatrol3_1))
		then
			if (( not IsAlive (M.svpatrol3_2)) and (M.rendezvous) and (IsAlive(M.ccarecycle)) and ( not M.first_objective) 
				 and  ( not M.mine_pathed) and ( not M.alarm_on) and (GetDistance(M.user,M.svpatrol3_1) < 50.0)  and ( not M.p2_retreat)
				 and  ( not M.p1_retreat) and ( not M.p3_retreat))
			then
				Retreat(M.svpatrol3_1, M.ccarecycle);
				SetObjectiveOn(M.svpatrol3_1);
				SetObjectiveName(M.svpatrol3_1, "Runner");
				M.getaway_message_time = GetTime() + 3.0;
				M.p3_retreat = true;
			end
		end

	-- this is the player being warned when one is getting away.
if (( not M.retreat_success) and ( not M.getum))
then
		if (((M.p1_retreat) and (M.getaway_message_time < GetTime()) 
			 and  (IsAlive(M.new_tank1)) and ( not M.getum))  or  
			((M.p1_retreat) and (M.getaway_message_time < GetTime()) 
			 and  (IsAlive(M.new_tank2)) and ( not M.getum)))
		then
			AudioMessage("misn0705.wav");-- one of'ms making a break for it not 
			M.getum = true;
		end

		if (((M.p2_retreat) and (M.getaway_message_time < GetTime()) 
			 and  (IsAlive(M.new_tank1)) and ( not M.getum))  or  
			((M.p2_retreat) and (M.getaway_message_time < GetTime()) 
			 and  (IsAlive(M.new_tank2)) and ( not M.getum)))
		then
			AudioMessage("misn0705.wav");-- one of'ms making a break for it not 
			M.getum = true;
		end
		
		if (((M.p3_retreat) and (M.getaway_message_time < GetTime()) 
			 and  (IsAlive(M.new_tank1)) and ( not M.getum))  or 
			((M.p3_retreat) and (M.getaway_message_time < GetTime()) 
			 and  (IsAlive(M.new_tank2)) and ( not M.getum)))
		then
			AudioMessage("misn0705.wav");-- one of'ms making a break for it not 
			M.getum = true;
		end
end

	-- this is to set up the "that's gotum" message

		if ((M.p1_retreat) and (IsAlive(M.svpatrol1_1)))
		then
			M.patrola1 = true;
		end

		if ((M.p1_retreat) and (IsAlive(M.svpatrol1_2)))
		then
			M.patrola2 = true;
		end

		if ((M.p2_retreat) and (IsAlive(M.svpatrol2_1)))
		then
			M.patrolb1 = true;
		end

		if ((M.p2_retreat) and (IsAlive(M.svpatrol2_2)))
		then
			M.patrolb2 = true;
		end

		if ((M.p3_retreat) and (IsAlive(M.svpatrol3_1)))
		then
			M.patrolc1 = true;
		end

		if ((M.p3_retreat) and (IsAlive(M.svpatrol3_2)))
		then
			M.patrolc2 = true;
		end

		if (((M.p1_retreat) and (M.patrola1) and ( not IsAlive(M.svpatrol1_1)) and (IsAlive(M.new_tank1)))  or 
			((M.p1_retreat) and (M.patrola1) and ( not IsAlive(M.svpatrol1_1)) and (IsAlive(M.new_tank2))))
		then
			AudioMessage("misn0706.wav"); -- that got'um not 
--			SetObjectiveOff(M.svpatrol1_1);
			M.p1_retreat = false;
			M.patrola1 = false;
			M.getum = false;
		end

		if (((M.p1_retreat) and (M.patrola2) and ( not IsAlive(M.svpatrol1_2)) and (IsAlive(M.new_tank1)))  or 
			((M.p1_retreat) and (M.patrola2) and ( not IsAlive(M.svpatrol1_2)) and (IsAlive(M.new_tank2))))
		then
			AudioMessage("misn0706.wav"); -- that got'um not 
--			SetObjectiveOff(M.svpatrol1_2);
			M.p1_retreat = false;
			M.patrola2 = false;
			M.getum = false;
		end

		if (((M.p2_retreat) and (M.patrolb1) and ( not IsAlive(M.svpatrol2_1)) and (IsAlive(M.new_tank1)))  or 
			((M.p2_retreat) and (M.patrolb1) and ( not IsAlive(M.svpatrol2_1)) and (IsAlive(M.new_tank2))))
		then
			AudioMessage("misn0706.wav"); -- that got'um not 
--			SetObjectiveOff(M.svpatrol2_1);
			M.p2_retreat = false;
			M.patrolb1 = false;
			M.getum = false;
		end

		if (((M.p2_retreat) and (M.patrolb2) and ( not IsAlive(M.svpatrol2_2)) and (IsAlive(M.new_tank1)))  or 
			((M.p2_retreat) and (M.patrolb2) and ( not IsAlive(M.svpatrol2_2)) and (IsAlive(M.new_tank2))))
		then
			AudioMessage("misn0706.wav"); -- that got'um not 
--			SetObjectiveOff(M.svpatrol2_2);
			M.p2_retreat = false;
			M.patrolb2 = false;
			M.getum = false;
		end

		if (((M.p3_retreat) and (M.patrolc1) and ( not IsAlive(M.svpatrol3_1)) and (IsAlive(M.new_tank1)))  or 
			((M.p3_retreat) and (M.patrolc1) and ( not IsAlive(M.svpatrol3_1)) and (IsAlive(M.new_tank2))))
		then
			AudioMessage("misn0706.wav"); -- that got'um not 
--			SetObjectiveOff(M.svpatrol3_1);
			M.p3_retreat = false;
			M.patrolc1 = false;
			M.getum = false;
		end

		if (((M.p3_retreat) and (M.patrolc2) and ( not IsAlive(M.svpatrol3_2)) and (IsAlive(M.new_tank1)))  or 
			((M.p3_retreat) and (M.patrolc2) and ( not IsAlive(M.svpatrol3_2)) and (IsAlive(M.new_tank2))))
		then
			AudioMessage("misn0706.wav"); -- that got'um not 
--			SetObjectiveOff(M.svpatrol3_2);
			M.p3_retreat = false;
			M.patrolc2 = false;
			M.getum = false;
		end

	end

	-- this is what happens if an enemy unit gets away - tanks will come out

		if ((M.patrola1) and ( not M.retreat_success) and ( not M.alarm_on)
			 and  (GetDistance(M.svpatrol1_1, M.ccarecycle) < 100.0)
			 and  (M.ccarecycle ~= nil) and (IsAlive(M.ccarecycle)))
		then
			SetObjectiveOff(M.svpatrol1_1);		
			M.retreat_success = true;
		end

		if ((M.patrola2) and ( not M.retreat_success) and ( not M.alarm_on) 
			 and  (GetDistance(M.svpatrol1_2, M.ccarecycle) < 100.0)
			 and  (M.ccarecycle ~= nil) and (IsAlive(M.ccarecycle)))
		then
			SetObjectiveOff(M.svpatrol1_2);
			M.retreat_success = true;
		end

		if ((M.patrolb1) and ( not M.retreat_success) and ( not M.alarm_on) 
			 and  (GetDistance(M.svpatrol2_1, M.ccarecycle) < 100.0)
			 and  (M.ccarecycle ~= nil) and (IsAlive(M.ccarecycle)))
		then
			SetObjectiveOff(M.svpatrol2_1);
			M.retreat_success = true;
		end

		if ((M.patrolb2) and ( not M.retreat_success) and ( not M.alarm_on) 
			 and  (GetDistance(M.svpatrol2_2, M.ccarecycle) < 100.0)
			 and  (M.ccarecycle ~= nil) and (IsAlive(M.ccarecycle)))
		then
			SetObjectiveOff(M.svpatrol2_2);
			M.retreat_success = true;
		end

		if ((M.patrolc1) and ( not M.retreat_success) and ( not M.alarm_on) 
			 and  (GetDistance(M.svpatrol3_1, M.ccarecycle) < 100.0)
			 and  (M.ccarecycle ~= nil) and (IsAlive(M.ccarecycle)))
		then
			SetObjectiveOff(M.svpatrol3_1);
			M.retreat_success = true;
		end

		if ((M.patrolc2) and ( not M.retreat_success) and ( not M.alarm_on) 
			 and  (GetDistance(M.svpatrol3_2, M.ccarecycle) < 100.0)
			 and  (M.ccarecycle ~= nil) and (IsAlive(M.ccarecycle)))
		then
			SetObjectiveOff(M.svpatrol3_2);
			M.retreat_success = true;
		end

	-- this is the message that they were M.detected
		if (((M.retreat_success) and (IsAlive(M.new_tank1)) and ( not M.detected_message))  or 
			((M.retreat_success) and (IsAlive(M.new_tank2)) and ( not M.detected_message)))
		then
			AudioMessage("misn0707.wav");-- one of the runers has made it back
			M.detected_message = true;
		end
			-- now that the player is detetected the soviets will send tanks out to scout
			if ((M.retreat_success) and ( not IsAlive(M.svpatrol1_1)) 
				 and  ( not IsAlive(M.svpatrol1_2)) and ( not IsAlive(M.svpatrol1_3)) and (IsAlive(M.ccarecycle)))
			then																			
				M.svpatrol1_1 = exu.BuildAsyncObject("svtank", 2, M.ccarecycle);
				M.svpatrol1_2 = exu.BuildAsyncObject("svtank", 2, M.ccarecycle);
--				M.svpatrol1_3 = BuildObject("svtank", 2, M.ccarecycle);
				Patrol(M.svpatrol1_1, "patrol_path1");
				Patrol(M.svpatrol1_2, "patrol_path1");
--				Patrol(M.svpatrol1_3, "patrol_path1");
			end																				
																						
--[[			if ((M.retreat_success) and ( not IsAlive(M.svpatrol2_1)) and 
				( not IsAlive(M.svpatrol2_2)) and ( not IsAlive(M.svpatrol2_3)) and (IsAlive(M.ccarecycle)))

			then																					
				M.svpatrol2_1 = BuildObject("svtank", 2, M.ccarecycle);
				M.svpatrol2_2 = BuildObject("svtank", 2, M.ccarecycle);
				M.svpatrol2_3 = BuildObject("svtank", 2, M.ccarecycle);
				Patrol(M.svpatrol2_1, "patrol_path1");	
				Patrol(M.svpatrol2_2, "patrol_path1");
				Patrol(M.svpatrol2_3, "patrol_path1");
			end																					
--]]																							
			if ((M.retreat_success) and ( not IsAlive(M.svpatrol3_1)) 
				 and  ( not IsAlive(M.svpatrol3_2)) and ( not IsAlive(M.svpatrol3_3)) and (IsAlive(M.ccarecycle)))
			then																					
				M.svpatrol3_1 = exu.BuildAsyncObject("svtank", 2, M.ccarecycle);
				M.svpatrol3_2 = exu.BuildAsyncObject("svtank", 2, M.ccarecycle);
--				M.svpatrol3_3 = BuildObject("svtank", 2, M.ccarecycle);
				Patrol(M.svpatrol3_1, "patrol_path1");
				Patrol(M.svpatrol3_2, "patrol_path1");
--				Patrol(M.svpatrol3_3, "patrol_path1");
			end																					
																								
--			if ((M.retreat_success) and ( not IsAlive(M.svpatrol4_1)) and 
--				( not IsAlive(M.svpatrol4_2)) and (IsAlive(M.ccarecycle)))	
--			then																				
--				M.svpatrol4_1 = BuildObject("svtank", 2, M.ccarecycle);								
--				M.svpatrol4_2 = BuildObject("svtank", 2, M.ccarecycle);								
--				Patrol(M.svpatrol4_1, "patrol_path2");											
--				Patrol(M.svpatrol4_2, "patrol_path2");											
--			end
end
		
-- end of retreat code ----------------------------------------/
-- building more patrol ships if patrol ships are lost ------------------------------------/
if ( not M.first_objective)
then																							
	if (( not IsAlive(M.svpatrol1_1)) and ( not IsAlive(M.svpatrol1_2)) and (IsAlive(M.ccarecycle)) and ( not M.detected))   
	then																				
		M.svpatrol1_1 = exu.BuildAsyncObject("svfigh", 2, M.ccarecycle);							
		M.svpatrol1_2 = exu.BuildAsyncObject("svfigh", 2, M.ccarecycle);						
		Patrol(M.svpatrol1_1, "patrol_path1");									
		Patrol(M.svpatrol1_2, "patrol_path1");									
		M.p1_retreat = false;	
		M.getum = false;
		M.patrola1 = false;
		M.patrola2 = false;
	end																				
																				
--[[	if (( not IsAlive(M.svpatrol2_1)) and ( not IsAlive(M.svpatrol2_2)) and (IsAlive(M.ccarecycle)) and ( not M.detected))	
	then																					
		M.svpatrol2_1 = BuildObject("svfigh", 2, M.ccarecycle);								
		M.svpatrol2_2 = BuildObject("svfigh", 2, M.ccarecycle);						
		Patrol(M.svpatrol2_1, "patrol_path1");										
		Patrol(M.svpatrol2_2, "patrol_path1");
		M.p2_retreat = false;
		M.getum = false;
		M.patrolb1 = false;
		M.patrolb2 = false;
	end																					
--]]																					
	if (( not IsAlive(M.svpatrol3_1)) and ( not IsAlive(M.svpatrol3_2)) and (IsAlive(M.ccarecycle)) and ( not M.detected))
	then																					
		M.svpatrol3_1 = exu.BuildAsyncObject("svfigh", 2, M.ccarecycle);								
		M.svpatrol3_2 = exu.BuildAsyncObject("svfigh", 2, M.ccarecycle);								
		Patrol(M.svpatrol3_1, "patrol_path1");											
		Patrol(M.svpatrol3_2, "patrol_path1");
		M.p3_retreat = false;	
		M.getum = false;	
		M.patrolc1 = false;
		M.patrolc2 = false;
	end																					
																						
	if (( not IsAlive(M.svpatrol4_1)) and ( not IsAlive(M.svpatrol4_2)) and (IsAlive(M.ccarecycle)))	
	then																				
		M.svpatrol4_1 = exu.BuildAsyncObject("svfigh", 2, M.ccarecycle);								
		M.svpatrol4_2 = exu.BuildAsyncObject("svfigh", 2, M.ccarecycle);								
		Patrol(M.svpatrol4_1, "patrol_path2");											
		Patrol(M.svpatrol4_2, "patrol_path2");											
	end
end
																							
-- end of scout building code ----------------------------------------------------------------
-- this is what happens when the player reaches the jump overlook - the M.rookie tells him about the M.test range
--[[
	if ((M.recon_message2_time < GetTime()) and ( not M.recon_message2))
	then
		M.recon_message2_time = GetTime() + 20.0;
		
		if (( not M.test_found) and ( not M.recon_message2))
		then
			AudioMessage("misn0703.wav"); -- M.rookie "I found a soviet M.test range
			M.becon_build_time = GetTime() + 15.0;
			M.check_range = GetTime() + 20.0;
			M.recon_message2 = true;
		end
	end
				
	if ((M.recon_message2) and (M.becon_build_time < GetTime()) and ( not M.becon_build))--M.rookie lays path through mines
	then
		M.nav4 = BuildObject ("apcamr", 1, "cam_spawn6");
		M.rookie_rendezvous_time = GetTime() + 120.0;
		M.becon_build = true;
	end

	if ((M.becon_build) and (M.nav4 ~= nil))
	then
		SetObjectiveName(M.nav4, "Testing Range");
	end

-- this is how the M.rookie tells the player he's under attack

	if ((M.becon_build) and (M.rookie_rendezvous_time < GetTime()) and ( not M.rookie_lost))
	then
		M.rookie_rendezvous_time = GetTime()	+ 21.0;	

		if ((GetDistance (M.user, M.mine_geyz) > 400.0) and ( not M.rookie_lost))
		then
			AudioMessage("misn0704.wav"); -- I'm under attack - I'll drop the a camera - goto to activate mine path
			M.nav5 = BuildObject ("apcamr", 1, "cam_spawn1");
			M.reach_mine_time = GetTime() + 10.0;
			M.rookie_lost = true;
		end
	end

	if ((M.rookie_lost) and (M.nav5 ~= nil))
	then
		SetObjectiveName(M.nav5, "Mine Field");
	end

	if ((M.rookie_lost) and (M.reach_mine_time < GetTime()) and ( not M.mine_pathed))
	then
		M.reach_mine_time = GetTime() + 10.0;
			
		if ((GetDistance(M.user, M.nav5) < 70.0) and ( not M.mine_pathed))
		then
			M.becon1 = BuildObject ("apcamr", 1, "cam_spawn2");
			M.becon2 = BuildObject ("apcamr", 1, "cam_spawn3");
			M.becon3 = BuildObject ("apcamr", 1, "cam_spawn4");
			M.becon4 = BuildObject ("apcamr", 1, "cam_spawn5");
			M.mine_pathed = true;
		end
	end

		if ((M.mine_pathed) and (M.becon1 ~= nil))
		then
			SetObjectiveName(M.becon1, "Mine Path 1");
		end
		if ((M.mine_pathed) and (M.becon2 ~= nil))
		then
			SetObjectiveName(M.becon2, "Mine Path 2");
		end
		if ((M.mine_pathed) and (M.becon3 ~= nil))
		then
			SetObjectiveName(M.becon3, "Mine Path 3");
		end
		if ((M.mine_pathed) and (M.becon4 ~= nil))
		then
			SetObjectiveName(M.becon4, "Mine Path 4");
		end

--]]
-- end of M.rookie message about soviet M.test range --------/
-- when the radar array is destroyed --------------------/
														
	if (( not IsAlive(M.ccacomtower)) and ( not M.first_objective))	
	then													
		M.audmsg = AudioMessage ("misn0714.wav");						
		M.radar_camera_time = GetTime() + 10.0;
--		M.next_shot_time = GetTime() + 20.0;
		M.next_mission_time = GetTime() + 7.5;
--		CameraReady();
--		M.shot1 = true;
		M.first_objective = true;							
	end
	
--[[	if (M.shot1)
	then
		CameraPath("radar_path", 4000, 1000, M.radar_geyser);
	end

	if ((M.shot1) and (M.radar_camera_time < GetTime()))
	then
--		StopAudioMessage(M.audmsg);
--		M.audmsg = AudioMessage ("misn0714.wav");	
		M.shot1 = false;
		M.shot2 = true;
	end

	if (M.shot2)
	then
		CameraPath("movie_cam_spawn", 160, 0, M.show_geyser);
	end

	if (( not M.radar_camera_off) and (M.shot2) and (M.next_shot_time < GetTime()))
	then
--		StopAudioMessage(M.audmsg);
		CameraFinish();
		M.shot2 = false;
		M.radar_camera_off = true;
	end

	if (((M.shot1)  or  (M.shot2)) and ( not M.radar_camera_off))
	then
		if (CameraCancelled())
		then
			M.shot1 = false;
			M.shot2 = false;
--			StopAudioMessage(M.audmsg);
			CameraFinish();
			M.radar_camera_off = true;
		end
	end
--]]
	if ((M.first_objective) and ( not M.next_mission) and (M.next_mission_time < GetTime()))
	then
		M.nsdfrecycle = exu.BuildAsyncObject("avrec7", 1, "recycle_spawn");
		M.nsdfmuf = exu.BuildAsyncObject("avmu7", 1, "muf_spawn");
		Goto(M.nsdfrecycle, "recycle_path", 0);
		Goto(M.nsdfmuf, "muf_path", 0);
		M.nav6 = exu.BuildAsyncObject ("apcamr", 1, "recycle_cam_spawn");	
		M.nav7 = exu.BuildAsyncObject ("apcamr", 1, "recy_cam_spawn"); 
		SetObjectiveName(M.nav6, "Utah Rendezvous");
		SetObjectiveName(M.nav7, "CCA BASE");
		AddScrap(1, 30);
		SetPilot(1, 20);
		AddScrap(2, 60);
		SetPilot(2, 40);
		SetAIP("misn07.aip");
--		SetObjectiveOn(recycler);
--		SetObjectiveName(recycler, "Utah");
		M.ccabaseguntower1 = exu.BuildAsyncObject("sbtowe", 2, "base_tower1_spawn");
--		M.ccabaseguntower2 = BuildObject("sbtowe", 2, "base_tower2_spawn");
		ClearObjectives();
		AddObjective("misn0701.otf", "GREEN");
		AddObjective("misn0703.otf", "WHITE");
		AddObjective("misn0702.otf", "WHITE");
		M.next_mission = true;
	end

	if ((M.next_mission) and ( not IsAlive(M.ccarecycle)))
	then
		M.second_objective = true;
	end

	if ((M.next_mission) and ( not M.utah_found))
	then
		if (IsAlive(M.nsdfrecycle))
		then
			if (IsDeployed(M.nsdfrecycle))
			then
				ClearObjectives();
				AddObjective("misn0703.otf", "GREEN");
				AddObjective("misn0702.otf", "WHITE");
				M.utah_found = true;
			end
		end
	end

-- here is an attempt at the mine code ------------
--[[
	--for (M.count = M.mine_check; M.count < M.mine_check + 10; M.count = M.count + 1)
	for ( i = 1, M.mine_check+10 do
		if (GetDistance(M.user, M.mine[M.count]) < 400.0)
		then
			if (( not M.m_on[M.count]) and ( not M.m_dead[M.count]))
			then
				M.m[M.count] = BuildObject ("proxmine", 2, M.mine[M.count]);
				M.m_on[M.count] = true;
			end
			if ((M.m_on[M.count]) and ( not IsAlive(M.m[M.count])))
			then
				M.m_dead[M.count] = true;
			end
		else
			if ((M.m_on[M.count]) and ( not M.m_dead[M.count]))
			then
				RemoveObject(M.m[M.count]);
				M.m_on[M.count] = false;
			end
		end
	end
--]]
-- this is the code that operates the MAG cannon and camera when the player encounters it
--[[
	if ((M.recon_message2) and (GetDistance(M.user, M.test_tank) < 65.0) 
		 and  ( not M.camera_ready))
	then															
		CameraReady();
		AddHealth(M.test_turret, -950.0); 
		M.camera_ready = true;									
	end															
																
	if ((M.camera_ready) and ( not M.camera1_on))
	then															
		CameraObject(M.test_tank, 2000, 800, 500, M.user);
		AudioMessage("misn0711.wav");
		M.start_sound = GetTime() + 8.0;
		M.change_angle = GetTime() + 6.0;
		M.camera1_on = true;
	end

	if ((M.camera1_on) and (M.change_angle < GetTime()) and ( not M.camera3_on))
	then
		CameraPath("camera_path1", 250,  250, M.test_tank);
		M.camera2_on = true;
	end

	if ((M.camera2_on) and ( not M.camera2_oned))
	then
		M.change_angle1 = GetTime() + 8.0;
		M.camera2_oned = true;
	end

	if ((M.change_angle1 < GetTime()) and ( not M.camera4_on))
	then
		CameraPath("camera_path2", 310, 500, M.test_turret);
		M.camera3_on = true;
	end

	if ((M.camera3_on) and ( not M.camera3_oned))
	then
		M.change_angle2 = GetTime() + 6.0;
		M.switch_tank = GetTime() + 5.0;
		M.camera3_oned = true;
	end

	if ((M.switch_tank < GetTime()) and ( not M.tank_switch))
	then
		RemoveObject(M.test_tank);
		M.test_tank = BuildObject("svtnk7", 2, "test_tank_spawn");
		Attack(M.test_tank, M.test_turret);
		M.tank_switch = true;
	end
	
--	if ((M.change_angle2 < GetTime()) and ( not M.camera4_on))
--	then
--		CameraObject(M.test_tank, -300, 400,-750, M.test_turret);
--		M.change_angle3 = GetTime() + 10.0;
--		M.camera4_on = true;
--	end
	
	if ((M.change_angle2 < GetTime()) and ( not M.camera4_on))
	then
		CameraObject(M.test_turret, 1000, 300, 4700, M.test_turret);
		M.change_angle3 = GetTime() + 10.0;
		M.camera4_on = true;
	end

	if ((M.camera4_on) and (M.change_angle3 < GetTime()) and ( not M.camera_off))
	then
		CameraFinish();											
		M.camera_off = true;
	end
--]]

-- win/loose conditions ------------------/

	-- added to fix crash if player died during camera scene
	if ( ( not IsAlive(M.user)) and (IsOdf(M.user, "asuser")) )
	then
		FailMission(GetTime() + 5.0);
	end

	if ((M.next_mission) and ( not IsAlive(M.nsdfrecycle)) and ( not M.game_over))
	then
		AudioMessage("misn0712.wav");
		if ( not M.utah_found)
		then
			ClearObjectives();
			AddObjective("misn0701.otf", "GREEN");
			AddObjective("misn0703.otf", "RED");
			AddObjective("misn0702.otf", "WHITE");
		end
		FailMission(GetTime() + 15.0, "misn07f1.des");
		M.game_over = true;
	end
											
	if ((M.next_mission) and ( not IsAlive(M.ccarecycle)))
	then
		M.second_objective = true;
	end
	
	if ((M.first_objective) and (M.second_objective) and ( not M.game_over))
	then
		AudioMessage("misn0713.wav");
		SucceedMission(GetTime() + 15.0, "misn07w1.des");
		M.game_over = true;
	end
	

-- END OF SCRIPT
	
end