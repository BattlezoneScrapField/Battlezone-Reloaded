-- Single Player NSDF Mission 11 Lua conversion, created by General BlackDragon. 

-- Single Table for all our save/load variables. This SP mission has too many variables to function with them independently. ("main function has > 200 local variables", or "Load having > 197 variables in assignment")
local M = {

-- bools
	start_done = false,
	--check_point1_done = false,
	check_point2_done = false,
	check_point3_done = false,
	check_point4_done = false,
	check_point5_done = false,
	--check1 = false,
	check2 = false,
	check3 = false,
	check4 = false,
	--objective1 = false,
	--out_of_order1 = false,
	--out_of_order2 = false,
	--out_of_order3 = false,
	--out_of_order4 = false,
	--out_of_order5 = false,
	interface_connect = false,
	--link_broken = false,
	interface_complete = false,
	warning_message = false,
	--cca_message1 = false,
	--cca_message2 = false,
	--cca_message3 = false,
	--cca_message4 = false,
	identify_message = false,
	cca_warning_message = false,
	better_message = false,
	real_bad = false,
	--enter_base = false,
	did_it_right = false,
	straight_to_5 = false,
	discovered = false,
	noise = false,
	camera_on = false,
	camera_off = false,
	camera1 = false,
	camera2 = false,
	camera3 = false,
	camera4 = false,
	--camera5 = false,
	key_captured = false,
	over = false,
	checked_in = false,
	going_again = false,
	--key_gone = false,
	game_blown = false,
	final_warned = false,
	last_warned = false,
	follow_spawn = false,
	good1 = false,
	good2 = false,
	good3 = false,
	good1_off = false,
	good2_off = false,
	good3_off = false,
	dead_meat = false,
	patrol1_create = false,
	--patrol2_create = false,
	--patrol3_create = false,
	--patrol4_create = false,
	patrol1_moved1 = false,
	patrol2_moved1 = false,
	patrol3_moved1 = false,
	--patrol4_moved1 = false,
	patrol1_moved2 = false,
	--patrol2_moved2 = false,
	patrol3_moved2 = false,
	patrol4_moved2 = false,
	--patrol1_1_gone = false,
	--patrol1_2_gone = false,
	--patrol2_1_gone = false,
	--patrol2_2_gone = false,
	--patrol3_1_gone = false,
	--patrol3_2_gone = false,
	--patrol4_1_gone = false,
	--patrol4_2_gone = false,
	p1_1center = false,
	p2_1center = false,
	p2_2center = false,
	p3_1center = false,
	p3_2center = false,
	p4_1center = false,
	p4_2center = false,
	win = false,
	game_over = false,
	camera_swap1 = false,
	camera_swap2 = false,
	camera_swap_back = false,
	out_of_ship = false,
	camera_noise = false,
	blown_otf = false,
	grump = false,
-- Floats (really doubles in Lua)
	--countdown_time = 0,
	interface_time = 0,
	warning_repeat_time = 0,
	next_message_time = 0,
	next_noise_time = 0,
	camera_time = 0,
	--camera_on_time = 0,
	win_check_time = 0,
	--start_patrol = 0,
	key_check = 0,
	wait_time = 0,
	key_remove = 0,
	death_spawn = 0,
	final_warning = 0,
	last_warning = 0,
	--remove_patrol1_2 = 0,
	patrol1_1_time = 0,
	--patrol1_2_time = 0,
	patrol2_1_time = 0,
	patrol2_2_time = 0,
	patrol3_1_time = 0,
	patrol3_2_time = 0,
	patrol4_1_time = 0,
	patrol4_2_time = 0,
	swap_check = 0,
	next_second = 0,
	grump_time = 0,
-- Handles
	user = nil,
	user_tank = nil,
	center = nil,
	center_cam = nil,
	start_cam = nil,
	check2_cam = nil,
	check3_cam = nil,
	check4_cam = nil,
	goal_cam = nil,
	nav1 = nil,
	key_ship = nil,
	spawn_geyser = nil,
	choke_geyser = nil,
	check2_geyser = nil,
	center_geyser = nil,
	checkpoint1 = nil,
	checkpoint2 = nil,
	checkpoint3 = nil,
	checkpoint4 = nil,
	ccacom_tower = nil,
	--ccasilo1 = nil,
	--ccasilo2 = nil,
	--ccasilo3 = nil,
	--ccasilo4 = nil,
	guard1 = nil,
	guard2 = nil,
	guard3 = nil,
	guard4 = nil,
	spawn_point1 = nil,
	spawn_point2 = nil,
	--guard_fighter = nil,
	--parked_fighter = nil,
	parked_tank1 = nil,
	parked_tank2 = nil,
	--guard_turret = nil,
	pturret1 = nil,
	--pturret2 = nil,
	--pturret3 = nil,
	--pturret4 = nil,
	--pturret5 = nil,
	pturret6 = nil,
	patrol1_1 = nil,
	patrol1_2 = nil,
	patrol2_1 = nil,
	patrol2_2 = nil,
	patrol3_1 = nil,
	patrol3_2 = nil,
	patrol4_1 = nil,
	patrol4_2 = nil,
	guard_tank1 = nil,
	guard_tank2 = nil,
	death_squad1 = nil,
	death_squad2 = nil,
	death_squad3 = nil,
	death_squad4 = nil,
	follower = nil,
	ccamuf = nil,
-- Ints
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

	M.warning_repeat_time = 99999.0;
	--M.countdown_time = 99999.0;
	--M.camera_on_time = 99999.0;
	M.interface_time = 99999.0;
	M.next_noise_time = 99999.0;
	M.camera_time = 99999.0;
	M.next_message_time = 99999.0;
	M.win_check_time = 99999.0;
	--M.start_patrol = 99999.0;
	M.key_check = 99999.0;
	M.wait_time = 99999.0;
	M.key_remove = 99999.0;
	M.death_spawn = 99999.0;
	M.final_warning = 99999.0;
	M.last_warning = 99999.0;
	--M.remove_patrol1_2 = 99999.0;
	M.patrol1_1_time = 99999.0;
	--M.patrol1_2_time = 99999.0;
	M.patrol2_1_time = 99999.0;
	M.patrol2_2_time = 99999.0;
	M.patrol3_1_time = 99999.0;
	M.patrol3_2_time = 99999.0;
	M.patrol4_1_time = 99999.0;
	M.patrol4_2_time = 99999.0;
	M.swap_check = 99999.0;
	M.grump_time = 99999.0;

	M.checkpoint1 = GetHandle("checktower1");
	M.checkpoint2 = GetHandle("svguntower2");
	M.checkpoint3 = GetHandle("svmuf");
	M.checkpoint4 = GetHandle("svsilo1");
	M.center = GetHandle("center");
--	M.ccasilo1 = GetHandle("svsilo1");
	--M.ccasilo2 = GetHandle("svsilo2");
	--M.ccasilo3 = GetHandle("svsilo3");
	--M.ccasilo4 = GetHandle("svsilo4");
	M.ccamuf = GetHandle("svmuf");
	M.ccacom_tower = GetHandle("svcom_tower");
	M.spawn_point1 = GetHandle("spawn_geyser1");
	M.spawn_point2 = GetHandle("spawn_geyser2");
	M.nav1 = GetHandle("apcamr20_camerapod");
	M.spawn_geyser = GetHandle("spawn_geyser");
	M.choke_geyser = GetHandle("choke_geyser");
	M.check2_geyser = GetHandle("check2_geyser");
	M.center_geyser = GetHandle("center_geyser");
	--M.guard_fighter = GetHandle("pfighter2");
	--M.parked_fighter = GetHandle("pfighter1");
	M.parked_tank2 = GetHandle("ptank2");
	M.parked_tank1 = GetHandle("ptank1");
	--M.guard_turret = GetHandle("turret6");
	M.pturret1 = GetHandle("turret1");
	--M.pturret2 = GetHandle("turret2");
	--M.pturret3 = GetHandle("turret3");
	--M.pturret4 = GetHandle("turret4");
	--M.pturret5 = GetHandle("turret5");
	M.pturret6 = GetHandle("turret6");
	M.patrol1_1 = GetHandle("svfigh1_1");
	M.patrol1_2 = GetHandle("svfigh1_2");
	M.patrol2_1 = GetHandle("svfigh2_1");
	M.patrol2_2 = GetHandle("svfigh2_2");
	M.patrol3_1 = GetHandle("svfigh3_1");
	M.patrol3_2 = GetHandle("svfigh3_2");
	M.patrol4_1 = GetHandle("svfigh4_1");
	M.patrol4_2 = GetHandle("svfigh4_2");
	M.guard_tank1 = GetHandle("gtank1");
	M.guard_tank2 = GetHandle("gtank2");
	
end

function AddObject(h)


end

function Update()

-- START OF SCRIPT

	M.user = GetPlayerHandle(); --assigns the player a handle every frame

	if ( not M.start_done)
	then
		AudioMessage("misn1200.wav"); 
		M.user_tank = GetPlayerHandle(); -- this assigns the tank a handle
--		Defend(M.key_ship);
		Defend(M.guard_tank1);
		Defend(M.guard_tank2);
		Defend(M.patrol1_1);
		Defend(M.patrol1_2);
		Defend(M.patrol2_1);
		Defend(M.patrol2_2);
		Defend(M.patrol3_1);
		Defend(M.patrol3_2);
		Defend(M.patrol4_1);
		Defend(M.patrol4_2);
		StartCockpitTimer(1200, 300, 120);

		SetObjectiveOn(M.checkpoint1);
		SetObjectiveName(M.checkpoint1, "Check Point");

		M.center_cam = BuildObject ("apcamr", 3, "center_cam");
		M.start_cam = BuildObject ("apcamr", 3, "start_cam");
		M.check2_cam = BuildObject ("apcamr", 3, "check2_cam");
		M.check3_cam = BuildObject ("apcamr", 3, "check3_cam");
		M.check4_cam = BuildObject ("apcamr", 3, "check4_cam");
		M.goal_cam = BuildObject ("apcamr", 3, "goal_cam");

		M.key_ship = BuildObject("svfi12", 2, M.spawn_geyser);
		SetWeaponMask(M.key_ship, 3);
		Goto(M.key_ship, "first_path"); -- gets the patrol ship to move towards M.checkpoint1
		M.key_check = GetTime() + 2.0;

		CameraReady();
		M.camera_time = GetTime() + 12.0;

		SetObjectiveName(M.nav1, "Drop Zone");
		SetMaxHealth(M.nav1, 0);
		M.start_done = true;
	end


	if (IsAlive(M.ccacom_tower))
	then
		if (GetTime()>M.next_second)
		then
			AddHealth(M.ccacom_tower, 200.0);
			M.next_second = GetTime() + 1.0;
		end
	end


-- this what happens if the player is M.discovered before taking M.over the ship

	if (( not M.game_blown) and ( not M.key_captured))
	then 
		if ((IsAlive(M.user_tank)) and (GetHealth(M.user_tank)< 0.90))
		then
			AudioMessage("misn1213.wav");
			M.death_spawn = GetTime() + 5.0;
			M.game_blown = true;
		end
	end

	if (IsValid(M.key_ship))
	then
		if (( not M.game_blown) and ( not M.key_captured) and (GetHealth(M.key_ship)< 0.50))
		then
			AudioMessage("misn1228.wav");
			M.death_spawn = GetTime() + 5.0;
			M.game_blown = true;
		end
	end

-- this is what happens is the player tries to get in with his tank

	if ((IsAlive(M.user_tank)) and (GetDistance(M.user_tank, M.checkpoint1) < 75.0) and ( not M.key_captured) and ( not M.game_blown))
	then
		AudioMessage("misn1213.wav");
		M.death_spawn = GetTime() + 5.0;
		ClearObjectives();
		AddObjective("misn1200.otf", "RED");
		M.game_blown = true;
	end

	-- this is M.game_blown code
	if ((M.game_blown) and (M.death_spawn < GetTime()))
	then
		M.death_spawn = GetTime() + 120.0;
		M.death_squad1 = BuildObject("svfigh", 2, M.spawn_geyser);
		M.death_squad2 = BuildObject("svfigh", 2, M.spawn_geyser);
		M.death_squad3 = BuildObject("svltnk", 2, M.spawn_geyser);
		M.death_squad4 = BuildObject("svltnk", 2, M.spawn_geyser);
		Attack(M.death_squad1, M.user);
		Attack(M.death_squad2, M.user);
		Attack(M.death_squad3, M.user);
		Attack(M.death_squad4, M.user);
	end

	if ((M.game_blown) and ( not IsAlive(M.user_tank)) and ( not M.dead_meat))
	then
		SetPerceivedTeam(M.user, 1);
		M.dead_meat = true;
	end


-- this is the start of the camera during the players briefing

	if ((M.start_done) and ( not M.camera4))
	then
		CameraPath("start_camera_path", 4000, 900, M.ccacom_tower);
	end

	if (((CameraCancelled())  or 
		(M.camera_time < GetTime())) and ( not M.camera4))
	then
		CameraFinish();
		ClearObjectives();
		AddObjective("misn1200.otf", "WHITE");
		M.camera4 = true;
	end

-- this is the start of patroling the cca ships

	if ((M.camera_off) and ( not M.patrol1_create)) -- change M.start_done to M.key_captured
	then
		Goto(M.patrol1_1, "path1_to");
		Goto(M.patrol1_2, "path1_to");
		M.patrol1_create = true;
	end

	if ((M.patrol1_create) and (IsAlive(M.patrol1_1)) 
		 and  (GetDistance(M.patrol1_1, M.checkpoint1) < 50.0) and ( not M.patrol1_moved1))
	then
		if ((IsAlive(M.patrol1_2) and (GetDistance(M.patrol1_2, M.checkpoint1) < 70.0)))
		then
			Goto(M.patrol1_1, "path1_from");
			Goto(M.patrol1_2, "path1_from");
			M.patrol1_moved1 = true;
		end
	end

	if ((M.patrol1_moved1) and (IsAlive(M.patrol1_1))
		 and  (GetDistance(M.patrol1_1, M.center_geyser) < 50.0) and ( not M.patrol1_moved2))
	then
		if ((IsAlive(M.patrol1_2) and (GetDistance(M.patrol1_2, M.center_geyser) < 50.0)))
		then
			Goto(M.patrol1_1, "path2");
			Patrol(M.patrol1_2, "path5");
			Goto(M.patrol2_1, "path3");
			M.patrol2_1_time = GetTime() + 15.0;
			M.patrol1_moved2 = true;
		end
	end


-- move 2_2
	if ((M.patrol1_moved2) and (IsAlive(M.patrol1_1)) 
		 and  (GetDistance(M.patrol1_1, M.check2_geyser) < 400.0) and ( not M.patrol2_moved1))
	then
		Goto(M.patrol2_2, "path2");
		Goto(M.patrol4_1, "path4");
		M.p4_1center = true;
		M.patrol2_2_time = GetTime() + 11.0;
		M.patrol1_1_time = GetTime() + 10.0;
		M.patrol4_1_time = GetTime() + 12.0;
		M.patrol2_moved1 = true;
	end


-- send 3_1 on route
	
	if ((IsAlive(M.patrol2_1)) and (GetDistance(M.patrol2_1, M.ccamuf) < 400.0) and ( not M.patrol3_moved1))
	then
		Goto(M.patrol3_1, "path4");
		M.patrol3_1_time = GetTime() + 5.0;
		M.p3_1center = true;
		M.patrol3_moved1 = true;
	end

-- send 3_2 on route

	if ((IsAlive(M.patrol2_2)) and (GetDistance(M.patrol2_2, M.ccamuf) < 400.0) and ( not M.patrol3_moved2))
	then
		Goto(M.patrol3_2, "path4");
		M.p3_2center = true;
		M.patrol3_2_time = GetTime() + 10.0;
		M.patrol3_moved2 = true;
	end
-- send 4_2
	if ((IsAlive(M.patrol3_1)) and (GetDistance(M.patrol3_1, M.checkpoint4) < 400.0) and ( not M.patrol4_moved2))
	then
		Goto(M.patrol4_2, "path4");
		M.patrol4_2_time = GetTime() + 5.0;
		M.p4_2center = true;
		M.patrol4_moved2 = true;
	end


-- check patrols
if (( not M.real_bad)  or  ( not M.game_blown))
then
	-- 1_1
	if ((IsAlive(M.patrol1_1)) and (M.patrol1_1_time < GetTime()))
	then
		M.patrol1_1_time = GetTime() + 10.0;
			
		if (( not M.p1_1center) and (GetDistance(M.patrol1_1, M.center_geyser) < 50.0))
		then
			Goto(M.patrol1_1, "path3");
			M.p1_1center = true;
		else
			if (GetDistance(M.patrol1_1, M.center_geyser) < 50.0)
			then
				Goto(M.patrol1_1, "path2");
				M.p1_1center = false;
			else
				if (GetDistance(M.patrol1_1, M.ccamuf) < 70.0)
				then
					Goto(M.patrol1_1, "path4");
				end
			end	
		end
	end
	-- 2_1
	if ((IsAlive(M.patrol2_1)) and (M.patrol2_1_time < GetTime()))
	then
		M.patrol2_1_time = GetTime() + 10.0;
			
		if (( not M.p2_1center) and (GetDistance(M.patrol2_1, M.center_geyser) < 50.0))
		then
			Goto(M.patrol1_1, "path3");
			M.p2_1center = true;
		else
			if (GetDistance(M.patrol2_1, M.center_geyser) < 50.0)
			then
				Goto(M.patrol2_1, "path2");
				M.p2_1center = false;
			else
				if (GetDistance(M.patrol2_1, M.ccamuf) < 70.0)
				then
					Goto(M.patrol2_1, "path4");
				end
			end	
		end
	end
	-- 2_2
	if ((IsAlive(M.patrol2_2)) and (M.patrol2_2_time < GetTime()))
	then
		M.patrol2_2_time = GetTime() + 10.0;
			
		if (( not M.p2_2center) and (GetDistance(M.patrol2_2, M.center_geyser) < 50.0))
		then
			Goto(M.patrol2_2, "path3");
			M.p2_2center = true;
		else
			if (GetDistance(M.patrol2_2, M.center_geyser) < 50.0)
			then
				Goto(M.patrol2_2, "path2");
				M.p2_2center = false;
			else
				if (GetDistance(M.patrol2_2, M.ccamuf) < 70.0)
				then
					Goto(M.patrol2_2, "path4");
				end
			end	
		end
	end
	--3_1
	if ((IsAlive(M.patrol3_1)) and (M.patrol3_1_time < GetTime()))
	then
		M.patrol3_1_time = GetTime() + 10.0;
			
		if (( not M.p3_1center) and (GetDistance(M.patrol3_1, M.center_geyser) < 50.0))
		then
			Goto(M.patrol3_1, "path3");
			M.p3_1center = true;
		else
			if (GetDistance(M.patrol3_1, M.center_geyser) < 50.0)
			then
				Goto(M.patrol3_1, "path2");
				M.p3_1center = false;
			else
				if (GetDistance(M.patrol3_1, M.ccamuf) < 70.0)
				then
					Goto(M.patrol3_1, "path4");
				end
			end	
		end
	end
	--3_2
	if ((IsAlive(M.patrol3_2)) and (M.patrol3_2_time < GetTime()))
	then
		M.patrol3_2_time = GetTime() + 10.0;
			
		if (( not M.p3_2center) and (GetDistance(M.patrol3_2, M.center_geyser) < 50.0))
		then
			Goto(M.patrol3_2, "path3");
			M.p3_2center = true;
		else
			if (GetDistance(M.patrol3_2, M.center_geyser) < 50.0)
			then
				Goto(M.patrol3_2, "path2");
				M.p3_2center = false;
			else
				if (GetDistance(M.patrol3_2, M.ccamuf) < 70.0)
				then
					Goto(M.patrol3_2, "path4");
				end
			end	
		end
	end
	--4_1
	if ((IsAlive(M.patrol4_1)) and (M.patrol4_1_time < GetTime()))
	then
		M.patrol4_1_time = GetTime() + 10.0;
			
		if (( not M.p4_1center) and (GetDistance(M.patrol4_1, M.center_geyser) < 50.0))
		then
			Goto(M.patrol4_1, "path3");
			M.p4_1center = true;
		else
			if (GetDistance(M.patrol4_1, M.center_geyser) < 50.0)
			then
				Goto(M.patrol4_1, "path2");
				M.p4_1center = false;
			else
				if (GetDistance(M.patrol4_1, M.ccamuf) < 70.0)
				then
					Goto(M.patrol4_1, "path4");
				end
			end	
		end
	end
	--4_2
	if ((IsAlive(M.patrol4_2)) and (M.patrol4_2_time < GetTime()))
	then
		M.patrol4_2_time = GetTime() + 10.0;
			
		if (( not M.p4_2center) and (GetDistance(M.patrol4_2, M.center_geyser) < 50.0))
		then
			Goto(M.patrol4_2, "path3");
			M.p4_2center = true;
		else
			if (GetDistance(M.patrol4_2, M.center_geyser) < 50.0)
			then
				Goto(M.patrol4_2, "path2");
				M.p4_2center = false;
			else
				if (GetDistance(M.patrol4_2, M.ccamuf) < 70.0)
				then
					Goto(M.patrol4_2, "path4");
				end
			end	
		end
	end
end
-------------- THIS ALL FALLS UNDER GAME BLOWN ------------------------------------/
if ( not M.game_blown)
then
-- this makes the M.key_ship stop at M.checkpoint1

	if ((M.start_done) and ( not M.key_captured) and ( not M.checked_in))
	then
		if (IsValid(M.key_ship))
		then
			if ((GetDistance(M.key_ship, M.checkpoint1) < 80.0))
			then
				Stop(M.key_ship, 1);
				M.wait_time = GetTime() + 20.0;
				M.checked_in = true;
			end
		end
	end

	if ((M.checked_in) and (M.wait_time < GetTime()) and ( not M.going_again) and ( not M.key_captured))
	then
		Goto(M.key_ship, "first_path");
		M.key_remove = GetTime() + 10.0;
		M.going_again = true;
	end

	if ((M.going_again) and (M.key_remove < GetTime()) and ( not M.key_captured))
	then
		M.key_remove = GetTime() + 3.0;
		
		if (GetDistance(M.key_ship, M.spawn_geyser) < 100.0)
		then
			RemoveObject(M.key_ship);
			M.key_ship = BuildObject("svfi12", 2, M.spawn_geyser);
			SetWeaponMask(M.key_ship, 3);
			Goto(M.key_ship, "first_path");
			M.checked_in = false;
			M.going_again = false;
		end
	end

-- this will indicate when the player has taken M.over the cca fighter

	if ((IsOdf(M.user, "svfi12")) and ( not M.key_captured))
	then
		if (IsAlive(M.user))
		then
			AddAmmo(M.user, 2000);
		end
		ClearObjectives();
		AddObjective("misn1200.otf", "GREEN");
		AddObjective("misn1201.otf", "WHITE");
		AddObjective("misn1202.otf", "WHITE");
		AddObjective("misn1203.otf", "WHITE");
		AddObjective("misn1204.otf", "WHITE");
		AudioMessage("misn1217.wav");
		M.camera_time = GetTime() + 10.0;

		if (IsAlive(M.checkpoint1))
		then
			SetObjectiveOff(M.checkpoint1);
		end

		M.key_captured = true;
	end

	if ((M.key_captured) and ((IsOdf(M.user, "svfigh"))  or  (IsOdf(M.user, "svtank"))) and ( not M.out_of_ship))
	then
		M.out_of_ship = true;
	end

	if ((M.out_of_ship) and ( not M.grump))
	then
		if (IsAlive(M.patrol1_1))
		then
			Attack(M.patrol1_1, M.user);
		end
		if (IsAlive(M.patrol1_2))
		then
			Attack(M.patrol1_2, M.user);
		end
		if (IsAlive(M.patrol2_1))
		then
			Attack(M.patrol2_1, M.user);
		end
		if (IsAlive(M.patrol2_2))
		then
			Attack(M.patrol2_2, M.user);
		end
		if (IsAlive(M.patrol3_1))
		then
			Attack(M.patrol3_1, M.user);
		end
		if (IsAlive(M.patrol3_2))
		then
			Attack(M.patrol3_2, M.user);
		end
		if (IsAlive(M.patrol4_1))
		then
			Attack(M.patrol4_1, M.user);
		end
		if (IsAlive(M.patrol4_2))
		then
			Attack(M.patrol4_2, M.user);
		end
		if (IsAlive(M.guard_tank1))
		then
			Attack(M.guard_tank1, M.user);
		end
		if (IsAlive(M.guard_tank2))
		then
			Attack(M.guard_tank2, M.user);
		end
		if (( not M.interface_complete) and ( not M.blown_otf))
		then
			ClearObjectives();
			AddObjective("misn1206.otf", "WHITE");
			M.blown_otf = true;
		end

		M.grump_time = GetTime() + 180.0;
		M.grump = true;
	end

	if (M.grump_time < GetTime())
	then
		M.grump = false;
	end
-- heres where we start the big movie


	if ((M.key_captured) and (M.camera_time < GetTime()) and ( not M.camera_on) and ( not M.camera_off))
	then
		CameraReady();
		M.camera_on = true;
	end

	if ((M.camera_on) and ( not M.camera1) and ( not M.camera2) and ( not M.camera3) and ( not M.camera_off))
	then
		CameraObject (M.checkpoint2, 0, 1000, 6000, M.checkpoint2);
		M.audmsg = AudioMessage("misn1218.wav");
		M.camera_time = GetTime() + 6.0;
		M.camera1 = true;
	end

	if (((M.camera1) and ( not M.camera2) and ( not M.camera3) and ( not M.camera_off)) 
		 and  ((M.camera_time < GetTime())  or  (CameraCancelled())))
	then
		StopAudioMessage(M.audmsg);
		CameraObject (M.checkpoint3, 3000, 3000, 3000, M.checkpoint3);
		M.audmsg = AudioMessage("misn1219.wav");
		M.camera_time = GetTime() + 6.0;
		M.camera2 = true;
	end

	if (((M.camera2) and ( not M.camera3) and ( not M.camera_off))
		 and  ((M.camera_time < GetTime())  or  (CameraCancelled())))
	then
		StopAudioMessage(M.audmsg);
		CameraObject (M.checkpoint4, -1000, 1500, 4000, M.checkpoint4);
		M.audmsg = AudioMessage("misn1220.wav");
		M.camera_time = GetTime() + 6.0;
		M.camera3 = true;
	end

	if (((M.camera3) and ( not M.camera_off))
		 and  ((M.camera_time < GetTime())  or  (CameraCancelled())))
	then
		StopAudioMessage(M.audmsg);
		AudioMessage("misn1221.wav");
		AudioMessage("misn1222.wav");
		CameraFinish();
		M.camera_off = true;
	end


-- this is where I script the how the player must check in at each check point

--	if ( not M.check2)
--	then
		if (GetDistance(M.user, M.checkpoint2) < 150.0)
		then
			M.check_point2_done = true;
		end

		if ((M.check_point2_done) and (GetDistance(M.user, M.checkpoint2) > 150.0))
		then
			M.check_point2_done = false;
		end
--	end
	
--	if ( not M.check3)
--	then
		if (GetDistance(M.user, M.checkpoint3) < 150.0)
		then
			M.check_point3_done = true;
		end

		if ((M.check_point3_done) and (GetDistance(M.user, M.checkpoint3) > 150.0))
		then
			M.check_point3_done = false;
		end
--	end

--	if ( not M.check4)
--	then
		if (GetDistance(M.user, M.checkpoint4) < 150.0)
		then
			M.check_point4_done = true;
		end

		if ((M.check_point4_done) and (GetDistance(M.user, M.checkpoint4) > 150.0))
		then
			M.check_point4_done = false;
		end
--	end

	if (GetDistance(M.user, M.ccacom_tower) < 150.0)
	then
		M.check_point5_done = true;
	end

	if ((M.check_point5_done) and (GetDistance(M.user, M.ccacom_tower) > 150.0))
	then
		M.check_point5_done = false;
	end

-- the following is if the player does it right
	
	if ( not M.interface_complete)
	then
		if ((GetDistance(M.user, M.checkpoint2) < 70.0) and ( not M.cca_warning_message) 
			 and  ( not M.identify_message) and ( not M.check2))			
		then
			CameraReady();
			M.good1 = true;

			if (M.good1)
			then
				SetVelocity(M.user, ScaleVector(0.2, GetVelocity(M.user)));
				CameraObject(M.user, 0, 700, -1500, M.user);
				M.camera_time = GetTime() + 5.0;
				AudioMessage("misn1207.wav"); -- soviet voice that is calm
				ClearObjectives();
				AddObjective("misn1200.otf", "GREEN");
				AddObjective("misn1201.otf", "GREEN");
				AddObjective("misn1202.otf", "WHITE");
				AddObjective("misn1203.otf", "WHITE");
				AddObjective("misn1204.otf", "WHITE");
				M.check2 = true;
			end
		end

		if ((M.good1) and (M.camera_time < GetTime()) and  ( not M.good1_off))
		then
			CameraFinish();
			M.good1_off = true;
		end


		if ((M.check2) and (GetDistance(M.user, M.checkpoint3) < 70.0) and ( not M.cca_warning_message) 
			 and  ( not M.identify_message) and ( not M.check3))
		then
			CameraReady();
			M.good2 = true;

			if (M.good2)
			then
				SetVelocity(M.user, ScaleVector(0.2, GetVelocity(M.user)));
				CameraObject(M.user, 0, 700, -1500, M.user);
				M.camera_time = GetTime() + 6.0;
				AudioMessage("misn1208.wav"); -- soviet voice that is calm
				ClearObjectives();
				AddObjective("misn1200.otf", "GREEN");
				AddObjective("misn1201.otf", "GREEN");
				AddObjective("misn1202.otf", "GREEN");
				AddObjective("misn1203.otf", "WHITE");
				AddObjective("misn1204.otf", "WHITE");
				M.check3 = true;
			end
		end

		if ((M.good2) and (M.camera_time < GetTime()) and  ( not M.good2_off))
		then
			CameraFinish();
			M.good2_off = true;
		end


		if ((GetDistance(M.user, M.checkpoint4) < 70.0) and (M.check3) and ( not M.check4) 
			 and  ( not M.cca_warning_message) and ( not M.identify_message))
		then
			CameraReady();
			M.good3 = true;

			if (M.good3)
			then
				SetVelocity(M.user, ScaleVector(0.2, GetVelocity(M.user)));
				CameraObject(M.user, 0, 700, -1500, M.user);
				M.camera_time = GetTime() + 6.0;
				AudioMessage("misn1209.wav"); -- soviet voice that is calm
				ClearObjectives();
				AddObjective("misn1200.otf", "GREEN");
				AddObjective("misn1201.otf", "GREEN");
				AddObjective("misn1202.otf", "GREEN");
				AddObjective("misn1203.otf", "GREEN");
				AddObjective("misn1204.otf", "WHITE");
				M.check4 = true;
			end
		end

		if ((M.good3) and (M.camera_time < GetTime()) and  ( not M.good3_off))
		then
			CameraFinish();
			M.good3_off = true;
		end
	end

--------------------------------------------------------------------------------------/
-- the TWOS

	-- if he goes to 2 and then straight to 4
	if ((M.check2) and ( not M.check3) and (M.check_point4_done) and ( not M.cca_warning_message)  and 
		( not M.identify_message) and ( not M.real_bad))
	then
		AudioMessage("misn1205.wav"); -- your out of order scout - return to you posts
		ClearObjectives();
		AddObjective("misn1200.otf", "GREEN");
		AddObjective("misn1201.otf", "GREEN");
		AddObjective("misn1202.otf", "WHITE");
		AddObjective("misn1203.otf", "YELLOW");
		AddObjective("misn1204.otf", "WHITE");
		M.cca_warning_message = true;
	end

		-- if he goes to 2 and then 4 and then back to 3 (recovers)
		if ((M.check2) and (M.cca_warning_message) and (GetDistance(M.user, M.checkpoint3) < 70.0) 
			 and  ( not M.identify_message) and ( not M.real_bad) and ( not M.check4))
		then
			CameraReady();
			M.good2 = true;

			if (M.good2)
			then
				SetVelocity(M.user, ScaleVector(0.2, GetVelocity(M.user)));
				CameraObject(M.user, 0, 700, -1500, M.user);
				M.camera_time = GetTime() + 6.0;
				AudioMessage("misn1210.wav");  -- soviet guy should laugh "you better now"
				ClearObjectives();
				AddObjective("misn1200.otf", "GREEN");
				AddObjective("misn1201.otf", "GREEN");
				AddObjective("misn1202.otf", "GREEN");
				AddObjective("misn1203.otf", "GREEN");
				AddObjective("misn1204.otf", "WHITE");
				M.better_message = true;
				M.check4 = true;
			end
		end

		-- if he goes to 2 and then 4 and then back to 2
		if ((M.check2) and (M.cca_warning_message) and ( not M.check4) and (M.check_point2_done) 
			 and  ( not M.identify_message) and ( not M.real_bad))
		then
			AudioMessage("misn1206.wav"); -- identify yourself not 
			M.next_message_time = GetTime() + 20.0;
			ClearObjectives();
			AddObjective("misn1200.otf", "GREEN");
			AddObjective("misn1201.otf", "GREEN");
			AddObjective("misn1202.otf", "WHITE");
			AddObjective("misn1203.otf", "RED");
			AddObjective("misn1204.otf", "WHITE");
			M.identify_message = true;
		end


		-- this is when he goes to 2 and then 4 and then 5
		if ((M.check2) and (M.cca_warning_message) and ( not M.check4) and (M.check_point5_done)
			 and  ( not M.identify_message) and ( not M.real_bad) and ( not M.check4))
		then
			AudioMessage("misn1206.wav"); -- identify yourself not 
			M.next_message_time = GetTime() + 20.0;
			ClearObjectives();
			AddObjective("misn1200.otf", "GREEN");
			AddObjective("misn1201.otf", "GREEN");
			AddObjective("misn1202.otf", "WHITE");
			AddObjective("misn1203.otf", "YELLOW");
			AddObjective("misn1204.otf", "RED");
			M.identify_message = true;
		end

	-- if he goes to 2 and then straigh to 5
	if ((M.check2) and (M.check_point5_done) and ( not M.check3) and ( not M.cca_warning_message) 
		 and  ( not M.identify_message) and ( not M.real_bad))
	then
		AudioMessage("misn1206.wav"); -- identify yourself not 
		M.next_message_time = GetTime() + 20.0;
		ClearObjectives();
		AddObjective("misn1200.otf", "GREEN");
		AddObjective("misn1201.otf", "GREEN");
		AddObjective("misn1202.otf", "WHITE");
		AddObjective("misn1203.otf", "WHITE");
		AddObjective("misn1204.otf", "YELLOW");
		M.identify_message = true;
	end

	-- if he goes to 2 and then 3 and then 5
	if ((M.check3) and ( not M.check4) and (M.check_point5_done) and ( not M.cca_warning_message) 
		 and  ( not M.identify_message) and ( not M.real_bad))
	then
		AudioMessage("misn1206.wav"); -- identify yourself not 
		M.next_message_time = GetTime() + 20.0;
		ClearObjectives();
		AddObjective("misn1200.otf", "GREEN");
		AddObjective("misn1201.otf", "GREEN");
		AddObjective("misn1202.otf", "GREEN");
		AddObjective("misn1203.otf", "WHITE");
		AddObjective("misn1204.otf", "YELLOW");
		M.identify_message = true;
	end

--/ the THREES


	-- if he goes to 3 before going to 2
	if ((M.check_point3_done) and ( not M.check2) and ( not M.cca_warning_message) and 
		( not M.identify_message) and ( not M.better_message) and ( not M.real_bad))
	then
		AudioMessage("misn1205.wav"); -- your out of order scout - return to you posts
		ClearObjectives();
		AddObjective("misn1200.otf", "GREEN");
		AddObjective("misn1201.otf", "WHITE");
		AddObjective("misn1202.otf", "YELLOW");
		AddObjective("misn1203.otf", "WHITE");
		AddObjective("misn1204.otf", "WHITE");
		M.cca_warning_message = true;
	end

		-- if he goes to 3 and then goes back to 2 (recovers)	
		if (( not M.check2) and (M.cca_warning_message) and ( not M.identify_message) and (GetDistance(M.user, M.checkpoint2) < 70.0) 
			 and  ( not M.better_message)) -- doing better 
		then
			CameraReady();
			M.good1 = true;

			if (M.good1)
			then
				SetVelocity(M.user, ScaleVector(0.2, GetVelocity(M.user)));
				CameraObject(M.user, 0, 700, -1500, M.user);
				M.camera_time = GetTime() + 7.0;
				AudioMessage("misn1210.wav"); -- soviet guy should laugh "you better now"
				ClearObjectives();
				AddObjective("misn1200.otf", "GREEN");
				AddObjective("misn1201.otf", "GREEN");
				AddObjective("misn1202.otf", "GREEN");
				AddObjective("misn1203.otf", "WHITE");
				AddObjective("misn1204.otf", "WHITE");
				M.better_message = true;
			end
		end

		-- if he goes to 3 and then recovers to 2 then goes back to 3
		if ((M.better_message) and ( not M.check4) and (M.check_point3_done) and ( not M.identify_message) and ( not M.real_bad))
		then
			AudioMessage("misn1206.wav"); -- identify yourself not 
			M.next_message_time = GetTime() + 20.0;
			ClearObjectives();
			AddObjective("misn1200.otf", "GREEN");
			AddObjective("misn1201.otf", "GREEN");
			AddObjective("misn1202.otf", "RED");
			AddObjective("misn1203.otf", "WHITE");
			AddObjective("misn1204.otf", "WHITE");
			M.identify_message = true;
		end

		-- if he goes to 3 and then recovers to 2 then goes to 5
		if ((M.better_message) and (M.check_point5_done) and ( not M.check4) 
			 and  ( not M.identify_message) and ( not M.real_bad))
		then
			AudioMessage("misn1206.wav"); -- identify yourself not 
			M.next_message_time = GetTime() + 20.0;
			ClearObjectives();
			AddObjective("misn1200.otf", "GREEN");
			AddObjective("misn1201.otf", "GREEN");
			AddObjective("misn1202.otf", "GREEN");
			AddObjective("misn1203.otf", "WHITE");
			AddObjective("misn1204.otf", "YELLOW");
			M.identify_message = true;
		end


	-- if her goes to 3 and then to 4 without recovering
	if (( not M.check2) and (M.check_point4_done)  and (M.cca_warning_message) and ( not M.better_message) and 
		( not M.identify_message) and ( not M.real_bad))
	then
		ClearObjectives();
		AddObjective("misn1200.otf", "GREEN");
		AddObjective("misn1201.otf", "WHITE");
		AddObjective("misn1202.otf", "YELLOW");
		AddObjective("misn1203.otf", "RED");
		AddObjective("misn1204.otf", "WHITE");
		M.real_bad = true;
	end

	-- if her goes to 3 and then to 5 without recovering
	if ((M.check_point5_done)  and (M.cca_warning_message) and ( not M.better_message) and 
		( not M.identify_message) and ( not M.real_bad) and ( not M.check4))
	then
		ClearObjectives();
		AddObjective("misn1200.otf", "GREEN");
		AddObjective("misn1201.otf", "WHITE");
		AddObjective("misn1202.otf", "YELLOW");
		AddObjective("misn1203.otf", "WHITE");
		AddObjective("misn1204.otf", "RED");
		M.real_bad = true;
	end

	-- if he goes to 3 and then recovers and then goes to 4
	if ((M.better_message) and (GetDistance(M.user, M.checkpoint4) < 70.0) 
		 and  ( not M.identify_message) and ( not M.real_bad) and ( not M.check4))
	then
		CameraReady();
		M.good3 = true;

		if (M.good3)
		then
			SetVelocity(M.user, ScaleVector(0.2, GetVelocity(M.user)));
			CameraObject(M.user, 0, 700, -1500, M.user);
			M.camera_time = GetTime() + 6.0;
			AudioMessage("misn1209.wav"); -- soviet voice that is calm
			ClearObjectives();
			AddObjective("misn1200.otf", "GREEN");
			AddObjective("misn1201.otf", "GREEN");
			AddObjective("misn1202.otf", "GREEN");
			AddObjective("misn1203.otf", "GREEN");
			AddObjective("misn1204.otf", "WHITE");
			M.check4 = true;
		end		
	end


-- the FOURS

	--if he goes straight to 4
	if ((M.check_point4_done) and ( not M.check2) and ( not M.cca_warning_message) 
		 and  ( not M.identify_message) and ( not M.real_bad))
	then
		AudioMessage("misn1206.wav"); -- identify yourself not 
		M.next_message_time = GetTime() + 20.0;
		ClearObjectives();
		AddObjective("misn1200.otf", "GREEN");
		AddObjective("misn1201.otf", "WHITE");
		AddObjective("misn1202.otf", "WHITE");
		AddObjective("misn1203.otf", "YELLOW");
		AddObjective("misn1204.otf", "WHITE");
		M.identify_message = true;
	end

-- the FIVES

-- new line for M.ccacom_tower - this is what happens when the player reaches the ccacomtower

		
	--if he goes straight to 5
	if ((M.check_point5_done) and ( not M.cca_warning_message) and ( not M.check2) 
		 and  ( not M.identify_message) and ( not M.real_bad) and ( not M.straight_to_5))
	then
		AudioMessage("misn1206.wav"); -- identify yourself not 
		M.next_message_time = GetTime() + 15.0;
		ClearObjectives();
		AddObjective("misn1200.otf", "GREEN");
		AddObjective("misn1201.otf", "WHITE");
		AddObjective("misn1202.otf", "WHITE");
		AddObjective("misn1203.otf", "WHITE");
		AddObjective("misn1204.otf", "YELLOW");
		M.identify_message = true;
		M.straight_to_5 = true;
	end

-- if he goes to 5 with some slip ups

	if ((M.check_point5_done) and (M.cca_warning_message) and (M.check4)
		 and  ( not M.identify_message) and ( not M.real_bad) and ( not M.final_warned))
	then
		AudioMessage("misn1214.wav"); -- explain yourself not 
		M.final_warning = GetTime() + 20.0;
		ClearObjectives();
		AddObjective("misn1200.otf", "GREEN");
		AddObjective("misn1201.otf", "GREEN");
		AddObjective("misn1202.otf", "GREEN");
		AddObjective("misn1203.otf", "GREEN");
		AddObjective("misn1204.otf", "YELLOW");
		M.final_warned = true;
	end
	
-- if he does it exactly right	
	
	if ((M.check_point5_done) and (M.check4) and ( not M.cca_warning_message)
		 and  ( not M.identify_message) and ( not M.real_bad) and ( not M.did_it_right))
	then
		AudioMessage("misn1205.wav"); -- can we help you scout
		M.last_warning = GetTime() + 30.0;
		ClearObjectives();
		AddObjective("misn1200.otf", "GREEN");
		AddObjective("misn1201.otf", "GREEN");
		AddObjective("misn1202.otf", "GREEN");
		AddObjective("misn1203.otf", "GREEN");
		AddObjective("misn1204.otf", "GREEN");
		M.did_it_right = true;
	end

	if ((M.did_it_right) and (M.last_warning < GetTime()) and ( not M.final_warned))
	then
		AudioMessage("misn1214.wav"); -- explain yourself not 
		M.final_warning = GetTime() + 20.0;
		M.final_warned = true;
	end

	

-- these are constants ----------------------------------------------------------------/

	-- this defines what happens under "cca_warning_message" conditions (if he goes out of order and then dilly-dallys)

	if ((M.cca_warning_message) and ( not M.better_message) and ( not M.check4) and ( not M.identify_message) and ( not M.last_warned))
	then
		M.last_warning = GetTime() + 100.0;
		M.last_warned = true;
	end

	if ((M.last_warned) and (M.last_warning < GetTime()) and ( not M.better_message) 
		 and  ( not M.check4) and ( not M.final_warned))
	then
		AudioMessage("misn1214.wav"); -- explain yourself not 
		M.final_warning = GetTime() + 40.0;
		M.final_warned = true;
	end

	if ((M.final_warned) and (M.final_warning < GetTime()) and ( not M.identify_message))
	then
		AudioMessage("misn1206.wav"); -- identify yourself not 
		M.next_message_time = GetTime() + 10.0;
		M.identify_message = true;
	end

	-- this defines what happens under "identify_message" conditions (if he is warned and does not recover in time)

	if ((M.identify_message) and (M.next_message_time < GetTime()) 
		 and  ( not M.real_bad))
	then
		M.real_bad = true;
	end

	if ((M.identify_message) and ( not M.real_bad))
	then
		if (M.check_point5_done)
		then
			Follow(M.guard_tank1, M.user);
			Follow(M.guard_tank2, M.user);
		else
			Goto(M.guard_tank1, M.ccacom_tower);
			Goto(M.guard_tank2, M.ccacom_tower);
		end
	end

	-- this defines what happens under "real_bad" conditions

	if ((M.real_bad) and ( not M.discovered))
	then
		AudioMessage("misn1211.wav");
		if ( not M.interface_connect)
		then
			ClearObjectives();
			AddObjective("misn1206.otf", "WHITE");
		end
		SetPerceivedTeam(M.user, 1);
		M.guard1 = BuildObject("svtank", 2, M.spawn_point1);
		M.guard2 = BuildObject("svtank", 2, M.spawn_point1);
		M.guard3 = BuildObject("svtank", 2, M.spawn_point2);
		M.guard4 = BuildObject("svtank", 2, M.spawn_point2);
		Goto(M.parked_tank2, M.ccacom_tower);
		Goto(M.parked_tank1, M.ccacom_tower);
		Attack (M.guard1, M.user, 1);
		Attack (M.guard2, M.user, 1);
		Attack (M.guard3, M.user, 1);
		Attack (M.guard4, M.user, 1);
		Attack (M.patrol1_1, M.user, 1);
		Attack (M.patrol1_2, M.user, 1);
		Attack (M.patrol2_1, M.user, 1);
		Attack (M.patrol2_2, M.user, 1);
--		Attack (M.patrol3_1, M.user, 1);
--		Attack (M.patrol3_2, M.user, 1);
		M.discovered = true;
	end


	if ((M.discovered) and ( not IsAlive(M.guard1)) and ( not IsAlive(M.guard2)) and ( not IsAlive(M.guard3)))
	then
		M.guard1 = BuildObject("svtank", 2, M.spawn_point1);
		M.guard2 = BuildObject("svtank", 2, M.spawn_point1);
		M.guard3 = BuildObject("svtank", 2, M.spawn_point2);
		M.guard4 = BuildObject("svtank", 2, M.spawn_point2);
		Attack (M.guard1, M.user, 1);
		Attack (M.guard2, M.user, 1);
		Attack (M.guard3, M.user, 1);
		Attack (M.guard4, M.user, 1);
		if ( not M.follow_spawn)
		then
			if (IsAlive(M.pturret1))
			then
				Goto(M.pturret1, "turret1_path");
			end
			if (IsAlive(M.pturret6))
			then
				Goto(M.pturret6, "turret2_path");
			end
		end
	end

-- this is what happens when the player gets a warning message

	if ((M.cca_warning_message) and ( not M.follow_spawn))
	then
		
		Goto(M.pturret1, "turret1_path");
		Goto(M.pturret6, "turret2_path");

		if ((GetDistance(M.user, M.checkpoint4)) > (GetDistance(M.user, M.checkpoint3))) -- he's at 3
		then
			M.follower = BuildObject("svfigh", 2, "3spawn");
			Follow(M.follower, M.user);
		else
			M.follower = BuildObject("svfigh", 2, "4spawn");
			Follow(M.follower, M.user);
		end

		M.follow_spawn = true;
	end


-- this is what happens when the player interfaces with the ccacomtower

		if ((GetDistance(M.user, M.ccacom_tower) < 60.0) and ( not M.interface_connect) and ( not M.interface_complete))
		then
			AudioMessage("misn1201.wav"); --uplink sound
			M.interface_connect = true;
			M.interface_time = GetTime () + 45.0;
		end

		if ((GetDistance(M.user, M.ccacom_tower) > 75.0) and (M.interface_connect) 
			 and  ( not M.interface_complete) and ( not M.warning_message))
		then
			AudioMessage("misn1202.wav"); -- loosing data uplink
			M.warning_repeat_time = GetTime () + 5.0;
			M.warning_message = true;
		end

		if ((M.warning_message) and (GetDistance(M.user, M.ccacom_tower) > 75.0) and 
			(M.warning_repeat_time < GetTime()) and (M.interface_connect))
		then
			M.warning_message = false;
		end

		if ((M.warning_message) and (GetDistance(M.user, M.ccacom_tower) < 75.0) and (M.interface_connect))
		then
			M.warning_message = false;
		end

		if ((M.interface_connect) and (GetDistance(M.user, M.ccacom_tower) > 85.0) and ( not M.interface_complete))
		then
			AudioMessage("misn1203.wav"); -- interface broken
			M.interface_connect = false;
		end

		if ((M.interface_connect) and (M.interface_time < GetTime()) and ( not M.interface_complete))
		then
			AudioMessage("misn1204.wav"); -- interface complete
			ClearObjectives();
			AddObjective("misn1205.otf", "WHITE");
			M.win_check_time = GetTime() + 120.0;
			StopCockpitTimer();
			HideCockpitTimer();
			AudioMessage("misn1223.wav"); -- get back to nav 1
			M.interface_complete = true;
		end

	if ((M.interface_complete) and ( not M.discovered))
	then
		if (IsAlive(M.patrol1_1))
		then
			Attack(M.patrol1_1, M.user);
		end
		if (IsAlive(M.patrol1_2))
		then
			Attack(M.patrol1_2, M.user);
		end
		if (IsAlive(M.patrol2_1))
		then
			Attack(M.patrol2_1, M.user);
		end
		if (IsAlive(M.patrol2_2))
		then
			Attack(M.patrol2_2, M.user);
		end
		if (IsAlive(M.patrol3_1))
		then
			Attack(M.patrol3_1, M.user);
		end
		if (IsAlive(M.patrol3_2))
		then
			Attack(M.patrol3_2, M.user);
		end
		if (IsAlive(M.patrol4_1))
		then
			Attack(M.patrol4_1, M.user);
		end
		if (IsAlive(M.patrol4_2))
		then
			Attack(M.patrol4_2, M.user);
		end
		if (IsAlive(M.guard_tank1))
		then
			Attack(M.guard_tank1, M.user);
		end
		if (IsAlive(M.guard_tank2))
		then
			Attack(M.guard_tank2, M.user);
		end

		M.discovered = true;
	end

	if ((M.interface_connect) and ( not M.interface_complete) and ( not M.noise))
	then
		AudioMessage("misn1212.wav");
		M.next_noise_time = GetTime() + 3.0;
		M.noise = true;
	end

	if ((M.interface_connect) and ( not M.interface_complete) and (M.noise) 
		 and  (M.next_noise_time < GetTime()))
	then
		M.noise = false;
	end

-- this is the Nav camera code

	if (M.key_captured)
	then
		if (((IsInfo("sbhqt1") == true)  or  (IsInfo("sbhqt2") == true)) and (( not M.camera_swap1)  or  ( not M.camera_swap2)))
		then
			if ((GetDistance(M.user, M.center) < 100.0))
			then
	--			if (IsAlive(M.center_cam))
	--			then
	--				RemoveObject(M.center_cam);
	--			end
				if (IsAlive(M.start_cam))
				then
					SetTeamNum(M.start_cam, 1);
--					RemoveObject(M.start_cam);
				end
				if (IsAlive(M.check2_cam))
				then
					SetTeamNum(M.check2_cam, 1);
--					RemoveObject(M.check2_cam);
				end
				if (IsAlive(M.check3_cam))
				then
					SetTeamNum(M.check3_cam, 1);
--					RemoveObject(M.check3_cam);
				end
				if (IsAlive(M.check4_cam))
				then
					SetTeamNum(M.check4_cam, 1);
--					RemoveObject(M.check4_cam);
				end
				if (IsAlive(M.goal_cam))
				then
					SetTeamNum(M.goal_cam, 1);
--					RemoveObject(M.goal_cam);
				end
	--			M.center_cam = BuildObject ("apcamr", 1, "center_cam");
--				M.start_cam = BuildObject ("apcamr", 1, "start_cam");
				SetObjectiveName(M.start_cam, "Check Point");
--				M.check2_cam = BuildObject ("apcamr", 1, "check2_cam");
				SetObjectiveName(M.check2_cam, "Check Point");
--				M.check3_cam = BuildObject ("apcamr", 1, "check3_cam");
				SetObjectiveName(M.check3_cam, "Check Point");
--				M.check4_cam = BuildObject ("apcamr", 1, "check4_cam");
				SetObjectiveName(M.check4_cam, "Check Point");
--				M.goal_cam = BuildObject ("apcamr", 1, "goal_cam");
				M.swap_check = GetTime() + 1.0;
				M.camera_swap1 = true;
				M.camera_swap_back = false;
			end

			if ((GetDistance(M.user, M.checkpoint1) < 100.0))
			then

				if (IsAlive(M.center_cam))
				then
					SetTeamNum(M.center_cam, 1);
--					RemoveObject(M.center_cam);
				end
	--			if (IsAlive(M.start_cam))
	--			then
	--				RemoveObject(M.start_cam);
	--			end
	--[[			if (IsAlive(M.check2_cam))
				then
					RemoveObject(M.check2_cam);
				end
				if (IsAlive(M.check3_cam))
				then
					RemoveObject(M.check3_cam);
				end
				if (IsAlive(M.check4_cam))
				then
					RemoveObject(M.check4_cam);
				end
				if (IsAlive(M.goal_cam))
				then
					RemoveObject(M.goal_cam);
				end
	--]]
--				M.center_cam = BuildObject ("apcamr", 1, "center_cam");
	--			M.start_cam = BuildObject ("apcamr", 1, "start_cam");
	--			M.check2_cam = BuildObject ("apcamr", 1, "check2_cam");
	--			M.check3_cam = BuildObject ("apcamr", 1, "check3_cam");
	--			M.check4_cam = BuildObject ("apcamr", 1, "check4_cam");
	--			M.goal_cam = BuildObject ("apcamr", 1, "goal_cam");
				M.swap_check = GetTime() + 1.0;
				M.camera_swap2 = true;
				M.camera_swap_back = false;
			end
		end
	end

	if (((M.camera_swap1)  or  (M.camera_swap2)) and ( not M.camera_noise))
	then
		AudioMessage("misn1229.wav");
		M.camera_noise = true;
	end

	if (( not M.camera_swap_back) and (M.swap_check < GetTime()) and ((M.camera_swap1)  or  (M.camera_swap2)))
	then
		M.swap_check = GetTime() + 1.0;

		if ((M.camera_swap1) and (GetDistance(M.user, M.center) > 300.0))
		then
			AudioMessage("misn1230.wav");
--			if (IsAlive(M.center_cam))
--			then
--				RemoveObject(M.center_cam);
--			end
			if (IsAlive(M.start_cam))
			then
				SetTeamNum(M.start_cam, 3);
--				RemoveObject(M.start_cam);
			end
			if (IsAlive(M.check2_cam))
			then
				SetTeamNum(M.check2_cam, 3);
--				RemoveObject(M.check2_cam);
			end
			if (IsAlive(M.check3_cam))
			then
				SetTeamNum(M.check3_cam, 3);
--				RemoveObject(M.check3_cam);
			end
			if (IsAlive(M.check4_cam))
			then
				SetTeamNum(M.check4_cam, 3);
--				RemoveObject(M.check4_cam);
			end
			if (IsAlive(M.goal_cam))
			then
				SetTeamNum(M.goal_cam, 3);
--				RemoveObject(M.goal_cam);
			end
--			M.center_cam = BuildObject ("apcamr", 3, "center_cam");
--			M.start_cam = BuildObject ("apcamr", 3, "start_cam");
--			M.check2_cam = BuildObject ("apcamr", 3, "check2_cam");
--			M.check3_cam = BuildObject ("apcamr", 3, "check3_cam");
--			M.check4_cam = BuildObject ("apcamr", 3, "check4_cam");
--			M.goal_cam = BuildObject ("apcamr", 3, "goal_cam");
			M.swap_check = 99999.0;
			M.camera_swap1 = false;
			M.camera_noise = false;
			M.camera_swap_back = true;
		end

		if ((M.camera_swap2) and (GetDistance(M.user, M.checkpoint1) > 300.0))
		then
			AudioMessage("misn1230.wav");

			if (IsAlive(M.center_cam))
			then
				SetTeamNum(M.center_cam, 3);
--				RemoveObject(M.center_cam);
			end
--			if (IsAlive(M.start_cam))
--			then
--				RemoveObject(M.start_cam);
--			end
--			if (IsAlive(M.check2_cam))
--[[			then
				RemoveObject(M.check2_cam);
			end
			if (IsAlive(M.check3_cam))
			then
				RemoveObject(M.check3_cam);
			end
			if (IsAlive(M.check4_cam))
			then
				RemoveObject(M.check4_cam);
			end
			if (IsAlive(M.goal_cam))
			then
				RemoveObject(M.goal_cam);
			end
--]]
--			M.center_cam = BuildObject ("apcamr", 3, "center_cam");
--			M.start_cam = BuildObject ("apcamr", 3, "start_cam");
--			M.check2_cam = BuildObject ("apcamr", 3, "check2_cam");
--			M.check3_cam = BuildObject ("apcamr", 3, "check3_cam");
--			M.check4_cam = BuildObject ("apcamr", 3, "check4_cam");
--			M.goal_cam = BuildObject ("apcamr", 3, "goal_cam");
			M.swap_check = 99999.0;
			M.camera_swap2 = false;
			M.camera_noise = false;
			M.camera_swap_back = true;
		end
	end
end

--------------------/ THIS MARKS THE END OF GAME BLOWN --------------------------------------
-- M.win condition

	if ((M.game_blown) and ( not M.game_over))
	then
		FailMission(GetTime() + 10.0);
		M.game_over = true;
	end

	if ((M.interface_complete) and (M.win_check_time < GetTime()))
	then
		M.win_check_time = GetTime() + 5.0;

		if ((GetDistance(M.user, M.nav1) < 75.0) and ( not M.win))
		then
			AudioMessage("misn1216.wav");
			SucceedMission(GetTime() + 7.0, "misn12w1.des");
			M.win = true;
		end
	end

	if (( not M.interface_complete) and (GetCockpitTimer() == 0) and ( not M.game_over))
	then
		AudioMessage("misn1215.wav");
		FailMission(GetTime() + 15.0, "misn12f1.des");
		M.game_over = true;
	end

-- END OF SCRIPT
	
end