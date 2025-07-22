-- Single Player NSDF Mission 2 Lua conversion, created by General BlackDragon. 

-- Single Table for all our save/load variables. This SP mission has too many variables to function with them independently. ("main function has > 200 local variables", or "Load having > 197 variables in assignment")
local M = {

-- bools
	first_wave_done = false,
	second_wave_done = false,
	third_wave_done = false,
	fourth_wave_done = false,
	--fifth_wave_done = false,
	turret_move_done = false,
	--rescue_move_done = false,
	help_spawn = false,
	help_arrive = false,
	--end_game = false,
	trans_underway = false,
	ambush_message = false,
	start_done = false,
	--first_objective = false,
	second_objective = false,
	third_objective = false,
	final_objective = false,
	--special_objective = false,
	start_retreat = false,
	done_retreat = false,
	--new_message_start = false,
	dead1 = false,
	dead2 = false,
	dead3 = false,
	camera_on = false,
	camera_off = false,
	help_stop1 = false,
	help_stop2 = false,
	recycle_stop = false,
	message1 = false,
	scavhunt = false,
	scavhunt2 = false,
	lost = false,-- since there are many ways you can loose we will make loosing a boolean
	camera_ready = false,
	start_movie = false,
	movie_over = false,
	remove_props = false,
	more_show = false,
	tanks_go = false,
	camera_2 = false,
	show_tank_attack = false,
	tower_dead = false,
	climax1 = false,
	climax2 = false,
	clear_debis = false,
	last_blown = false,
	end_shot = false,
	clean_sweep = false,
	startfinishingmovie = false,
	turrets_set = false,
	speach2 = false,
	second_warning = false,
	last_warning = false,
-- Floats (really doubles in Lua)
	next_second = 0,
	--retreat_timer = 0,
	--next_wave = 0,
	second_wave_time = 0,
	ambush_message_time = 0,
	new_message_time = 0,
	apc_spawn_time = 0,
	pull_out_time = 0,
	third_wave_time = 0,
	fourth_wave_time = 0,
	--fifth_wave_time = 0,
	turret_move_time = 0,
	--wave3_time = 0,
	--wave4_time = 0,
	camera_off_time = 0,
	support_time = 0,
	movie_time = 0,
	new_unit_time = 0,
	next_shot = 0,
	kill_tower = 0,
	clear_debis_time = 0,
	unit_check = 0,
	clean_sweep_time = 0,
	final_check = 0,
-- Handles
	user = nil,
	avrecycler = nil,
	geyser = nil,
	cam_geyser = nil,
	shot_geyser = nil,
	scav1 = nil,
	scav2 = nil,
	scav3 = nil,
	scav4 = nil,
	scav5 = nil,
	scav6 = nil,
	crate1 = nil,
	crate2 = nil,
	crate3 = nil,
	rescue1 = nil,
	rescue2 = nil,
	rescue3 = nil,
	wave1_1 = nil,
	wave1_2 = nil,
	wave1_3 = nil,
	wave2_1 = nil,
	wave2_2 = nil,
	wave2_3 = nil,
	wave3_1 = nil,
	wave3_2 = nil,
	wave3_3 = nil,
	wave4_1 = nil,
	wave4_2 = nil,
	wave4_3 = nil,
	wave5_1 = nil,
	wave5_2 = nil,
	wave5_3 = nil,
	wave6_1 = nil,
	wave6_2 = nil,
	wave6_3 = nil,
	wave7_1 = nil,
	wave7_2 = nil,
	wave7_3 = nil,
	wave7_4 = nil,
	wave7_5 = nil,
	wave7_6 = nil,
	turret1 = nil,
	turret2 = nil,
	turret3 = nil,
	turret4 = nil,
	--spawn_point1 = nil,
	--spawn_point2 = nil,
	launch = nil,
	nest = nil,
	solar1 = nil,
	solar2 = nil,
	solar3 = nil,
	solar4 = nil,
	help1 = nil,
	help2 = nil,
	build1 = nil,
	build2 = nil,
	build3 = nil,
	build4 = nil,
	build5 = nil,
	hanger = nil,
	prop1 = nil,
	prop2 = nil,
	prop3 = nil,
	prop4 = nil,
	prop5 = nil,
	prop6 = nil,
	prop7 = nil,
	prop8 = nil,
	prop9 = nil,
	prop0 = nil,
	guy1 = nil,
	guy2 = nil,
	guy3 = nil,
	guy4 = nil,
	box1 = nil,
	sucker = nil,
	avturret1 = nil,
	avturret2 = nil,
	avturret3 = nil,
	avturret4 = nil,
	avturret5 = nil,
	avturret6 = nil,
	avturret7 = nil,
	avturret8 = nil,
	avturret9 = nil,
	avturret10 = nil,
-- Ints
	x = 0,
	z = 0,
	y = 0,
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

	M.x = 4000;
	M.z = 1;
	M.y = 1;

	M.second_wave_time = 99999.0;
	M.third_wave_time = 99999.0;
	M.fourth_wave_time = 99999.0;
	--M.fifth_wave_time = 99999.0;
	M.turret_move_time = 99999.0;
	--M.next_wave = 99999.0;
	M.new_message_time = 99999.0;
	M.apc_spawn_time = 99999.0;
	M.pull_out_time = 99999.0;
	M.ambush_message_time = 99999.0;
	M.camera_off_time = 99999.0;
	M.support_time = 99999.0;
	M.movie_time = 99999.0;
	M.new_unit_time = 99999.0;
	M.next_shot = 99999.0;
	M.kill_tower = 99999.0;
	M.clear_debis_time = 99999.0;
	M.unit_check = 99999.0;
	M.clean_sweep_time = 99999.0;
	M.final_check = 99999.0;

	M.avrecycler = GetHandle("avrec3-1_recycler");
	M.scav1 = GetHandle("scav1");
	M.scav2 = GetHandle("scav2");
	M.wave1_1 = GetHandle("svfigh1");
	M.wave1_2 = GetHandle("svfigh2");	
--	M.wave1_3 = GetHandle("svfigh3");	
	M.turret1 = GetHandle("enemyturret_1");
	M.turret2 = GetHandle("enemyturret_2");
	M.turret3 = GetHandle("enemyturret_3");
	M.turret4 = GetHandle("enemyturret_4");
	M.geyser = GetHandle("geyser1");
	M.solar1 = GetHandle("solar1");
	M.solar2 = GetHandle("solar2");
	M.solar3 = GetHandle("solar3");
	M.solar4 = GetHandle("solar4");
	M.launch = GetHandle("launch_pad");
	M.build1 = GetHandle("build1");
--	M.build2 = GetHandle("build2");
	M.build3 = GetHandle("build3");
	M.build4 = GetHandle("build4");
	M.build5 = GetHandle("build5");
	M.hanger = GetHandle("hanger");
	M.cam_geyser = GetHandle("cam_geyser");
	M.shot_geyser = GetHandle("shot_geyser");
	M.box1 = GetHandle("box1");
	M.crate1 = GetHandle("crate1");
	M.crate2 = GetHandle("crate2");
	M.crate3 = GetHandle("crate3");

end

function AddObject(h)

	if ((M.avturret1 == nil) and (IsOdf(h,"avturr")))
	then
		M.avturret1 = h;
	else
		if ((M.avturret2 == nil) and (IsOdf(h,"avturr")))
		then
			M.avturret2 = h;
		else
			if ((M.avturret3 == nil) and (IsOdf(h,"avturr")))
			then
				M.avturret3 = h;
			else
				if ((M.avturret4 == nil) and (IsOdf(h,"avturr")))
				then
					M.avturret4 = h;
				else
					if ((M.avturret5 == nil) and (IsOdf(h,"avturr")))
					then
						M.avturret5 = h;
					else
						if ((M.avturret6 == nil) and (IsOdf(h,"avturr")))
						then
							M.avturret6 = h;
						else
							if ((M.avturret7 == nil) and (IsOdf(h,"avturr")))
							then
								M.avturret7 = h;
							else
								if ((M.avturret8 == nil) and (IsOdf(h,"avturr")))
								then
									M.avturret8 = h;
								else
									if ((M.scav3 == nil) and (IsOdf(h,"avscav")))
									then
										M.scav3 = h;
									else
										if ((M.avturret9 == nil) and (IsOdf(h,"avturr")))
										then
											M.avturret9 = h;
										else
											if ((M.avturret10 == nil) and (IsOdf(h,"avturr")))
											then
												M.avturret10 = h;
											else
												if ((M.scav4 == nil) and (IsOdf(h,"avscav")))
												then
													M.scav4 = h;
												else
													if ((M.scav5 == nil) and (IsOdf(h,"avscav")))
													then
														M.scav5 = h;
													else
														if ((M.scav6 == nil) and (IsOdf(h,"avscav")))
														then
															M.scav6 = h;
														end
													end
												end
											end
										end
									end
								end
							end
						end
					end
				end
			end
		end
	end

end

function Update()

-- START OF SCRIPT

	M.user = GetPlayerHandle(); --assigns the player a handle every frame

	if ( not M.start_done)
	then	
		SetScrap (1, 8);
		SetPilot(1, 10);

		SetObjectiveOn(M.solar1);
		SetObjectiveName(M.solar1, "Command Tower");

		SetObjectiveOn(M.solar2);
		SetObjectiveName(M.solar2, "Solar Array");

		Goto(M.avrecycler, "recycle_point");
		ClearObjectives();
		AddObjective("misn0301.otf", "WHITE");		
		M.second_wave_time = GetTime() + 200.0;
		M.third_wave_time = GetTime() + 310.0;
		M.fourth_wave_time = GetTime() + 430.0;
		M.apc_spawn_time = GetTime() + 530.0;
		M.support_time = GetTime() + 430.0;
		M.next_second = GetTime() + 1.0;
		M.unit_check = GetTime() + 60.0;
		M.start_done = true;
	end
	
	if ((IsAlive(M.solar1)) and ( not M.show_tank_attack))
		then
			if (GetTime()>M.next_second)
			then
				AddHealth(M.solar1, 50.0);
				M.next_second = GetTime()+1.0;
			end
		end

	if (( not M.message1) and (M.start_done))
	then
		M.audmsg = AudioMessage("misn0311.wav");
		M.message1 = true;
	end

	if ((M.start_done) and (GetDistance(M.avrecycler, "recycle_point") < 50.0) and ( not M.recycle_stop))
	then
		Stop(M.avrecycler, 0);
		M.recycle_stop = true;
	end

	
	if ( not M.first_wave_done)
	then
		Attack(M.wave1_1, M.solar1, 1);
		Attack(M.wave1_2, M.solar1, 1);
--		Attack(M.wave1_3, M.solar1);
		
		M.first_wave_done = true;
	end

-- this sends the first wave retreating after one of them is destroyed
	if ((M.first_wave_done) and ( not M.start_retreat))
	then
		if ( not IsAlive(M.wave1_1))
		then
			Retreat(M.wave1_2,"retreat_path", 1);
--			Retreat(M.wave1_3, "retreat_path2", 1);
			M.new_message_time = GetTime() + 13.0;
			M.start_retreat = true;
		else
			if ( not IsAlive(M.wave1_2))
			then
				Retreat(M.wave1_1,"retreat_path", 1);
--				Retreat(M.wave1_3, "retreat_path2", 1);
				M.new_message_time = GetTime() + 10.0;
				M.start_retreat = true;
			end
--			else
--				if ( not IsAlive(M.wave1_3))
--				then
--					Retreat(M.wave1_1,"retreat_path", 1);
--					Retreat(M.wave1_2, "retreat_path2", 1);
--					M.new_message_time = GetTime() + 10.0;
--					M.start_retreat = true;
--				end
--			end
		end
	end

	if ((M.start_retreat) and (M.new_message_time < GetTime()) and ( not M.done_retreat))
	then
		AudioMessage("misn0312.wav");
		ClearObjectives();
		AddObjective("misn0302.otf", "WHITE");
		AddObjective("misn0301.otf", "WHITE");
		M.done_retreat = true;
	end

	if (( not M.turrets_set) and (IsAlive(M.solar1)) and (M.unit_check < GetTime()))
	then
		M.unit_check = GetTime() + 5.0;
		M.z = CountUnitsNearObject(M.solar1, 200.0, 1, "avturr");

		if (M.z > 3)
		then
			ClearObjectives();
			AddObjective("misn0302.otf", "GREEN");
			AddObjective("misn0301.otf", "WHITE");
			M.turrets_set = true;
		end
	end

	if (( not M.second_wave_done) and (M.second_wave_time < GetTime()))
	then
		M.wave2_1 = exu.BuildAsyncObject("svfigh",2,"spawn_scrap1");
		M.wave2_2 = exu.BuildAsyncObject("svfigh",2,"spawn_scrap1");
--		M.wave2_3 = BuildObject("svfigh",2,"spawn_scrap1");	

		Attack(M.wave2_1, M.solar1);
		Goto(M.wave2_2, M.solar1);
--		Goto(M.wave2_3, M.solar1);

		M.second_wave_done = true;
	end

	if (( not M.third_wave_done) and (M.third_wave_time < GetTime()))
	then
		M.wave3_1 = exu.BuildAsyncObject("svfigh",2,"spawn_scrap1");
		M.wave3_2 = exu.BuildAsyncObject("svfigh",2,"spawn_scrap1");
--		M.wave3_3 = BuildObject("svfigh",2,"spawn_scrap1");
			
		Attack(M.wave3_1, M.solar1, 1);
		Attack(M.wave3_2, M.solar1, 1);
--		Goto(M.wave3_3, M.solar1, 1);
			
		M.third_wave_done = true;
	end

	if (( not M.scavhunt) and (M.third_wave_done))
	then
		if (IsAlive(M.wave1_1))
		then
			Attack(M.wave1_1, M.scav1, 1);
		end

		if (IsAlive(M.wave1_2))
		then
			Attack(M.wave1_2, M.scav1, 1);
		end

--		if (IsAlive(M.wave1_3))
--		then
--			Attack(M.wave1_3, M.scav1, 1);
--		end

		M.scavhunt = true;
	end

	if (( not M.fourth_wave_done) and (M.fourth_wave_time < GetTime()))
	then
		M.wave4_1 = exu.BuildAsyncObject("svapc",2,"spawn_scrap1");
		M.wave4_2 = exu.BuildAsyncObject("svtank",2,"spawn_scrap1");
--		M.wave4_3 = BuildObject("svtank",2,"spawn_scrap1");
		M.wave5_1 = exu.BuildAsyncObject("svfigh",2,"spawn_scrap1");

		if (IsAlive(M.avrecycler))
		then
			Attack(M.wave4_1, M.avrecycler, 1);
		else
			if (IsAlive(M.solar3))
			then
				Attack(M.wave4_1, M.solar3, 1);
			else
				if (IsAlive(M.solar4))
				then
					Attack(M.wave4_1, M.solar4, 1);
				end
			end
		end
		

		Attack(M.wave4_2, M.solar2, 1);
--		Goto(M.wave4_3, M.solar2, 1);
			
		M.fourth_wave_done = true;
	end

	if (( not M.scavhunt2) and (M.fourth_wave_done) and (IsAlive(M.wave5_1)))
	then
		if (IsAlive(M.scav1))
		then
			Attack(M.wave5_1, M.scav1, 1);
		else
			if ( not IsAlive(M.scav2))
			then
				Attack(M.wave5_1, M.scav2, 1);
			end
		end
		M.scavhunt2 = true;
	end
	
	if (( not M.help_spawn) and (M.support_time < GetTime()))
	then
		M.help1 = exu.BuildAsyncObject("avfigh",1,"spawn_scrap2");
		M.help2 = exu.BuildAsyncObject("avtank",1,"spawn_scrap2");
		AudioMessage("misn0314.wav");
		Goto(M.help1, M.solar2, 1);
		Goto(M.help2, M.solar2, 1);
		M.help_spawn = true;
	end

		if ((M.help_spawn) and ( not M.help_stop1) and (IsAlive(M.help1)) and (IsAlive(M.solar2)))
		then
			if (GetDistance(M.help1, M.solar2) < 75.0)
			then
				Stop(M.help1, 0);
				M.help_stop1 = true;
			end
		end

		if ((M.help_spawn) and ( not M.help_stop2) and (IsAlive(M.help2)) and (IsAlive(M.solar2)))
		then
			if (GetDistance(M.help2, M.solar2) < 75.0)
			then
				Stop(M.help2, 0);
				M.help_stop2 = true;
			end
		end

	if ((M.help_spawn) and ( not M.help_arrive) and ((GetDistance(M.help1,M.user) < 50.0)  or  (GetDistance(M.help2,M.user) < 50.0)))
	then
--		AudioMessage("misn0313.wav");
		Goto(M.help1, M.solar2, 0);
		Goto(M.help2, M.solar2, 0);
		M.help_arrive = true;
	end

--  Time to evacuate the base


-- soviet movie

	if (( not M.second_objective) and (M.apc_spawn_time < GetTime()))
	then
		M.apc_spawn_time = GetTime() + 1.0;
		M.z = CountUnitsNearObject(M.user, 500.0, 2, "svtank");
		M.y = CountUnitsNearObject(M.user, 500.0, 2, "svfigh");

		if ((M.z == 0) and (M.y == 0))
		then
			M.audmsg = AudioMessage("misn0305.wav");
			M.second_objective = true;
		end
	end

	if (( not M.camera_ready) and (M.second_objective))
	then
		CameraReady();
		M.movie_time = GetTime() + 14.5;
		M.new_unit_time = GetTime() + 7.5;
		M.prop1 = exu.BuildAsyncObject("svrecy", 2, "recy_spawn");
		M.prop2 = exu.BuildAsyncObject("svmuf", 2, "muf_spawn");
		M.prop3 = exu.BuildAsyncObject("svtank", 2, "tank1_spawn");
		M.prop4 = exu.BuildAsyncObject("svtank", 2, "tank2_spawn");
		M.prop5 = exu.BuildAsyncObject("svfigh", 2, "fighter1_spawn");
--		M.prop6 = BuildObject("svtank", 2, "fighter2_spawn");
--		M.prop7 = BuildObject("svtank", 2, "fighter3_spawn");
		M.guy1 = exu.BuildAsyncObject("sssold",2,"guy1_spawn");
		M.guy2 = exu.BuildAsyncObject("sssold",2,"guy2_spawn");
		M.guy3 = exu.BuildAsyncObject("sssold",2,"guy1_spawn");
		M.guy4 = exu.BuildAsyncObject("sssold",2,"guy2_spawn");

		Defend(M.prop1, 1);
--		Defend(M.prop6, 1);
--		Defend(M.prop7, 1);
		Goto(M.prop2, "tank1_spawn", 1);
		Goto(M.prop3, "that_path", 1);
		Goto(M.prop4, "cool_path", 1);
		Goto(M.prop5, "cool_path", 1);
		Goto(M.guy1, "guy_spot", 1);
		Goto(M.guy2, "guy_spot", 1);
		Goto(M.guy3, "guy_spot", 1);
		Goto(M.guy4, "guy_spot", 1);
		M.camera_ready = true;
	end

	if ((M.camera_ready) and ( not M.movie_over))
	then
		CameraPath("movie_path", 175, 850, M.prop1);
		Defend(M.prop1, 1);
 		M.start_movie = true;
	end

	if ((M.camera_ready) and ( not M.more_show) and ( not M.movie_over))
	then
		if (M.new_unit_time < GetTime())
		then
			M.prop8 = exu.BuildAsyncObject("svfigh", 2, "muf_spawn");
			M.prop9 = exu.BuildAsyncObject("svfigh", 2, "muf_spawn");
--			Goto(M.prop6, "cool_path2", 1);
--			Goto(M.prop7, "cool_path2", 1);
			Goto(M.prop8, "tank2_spawn", 1);
			Goto(M.prop9, "fighter1_spawn", 1);
			M.more_show = true;
	--	end
	--	else
	--	then
--			Defend(M.prop6);
--			Defend(M.prop7);
		end

	end

	if ((M.start_movie) and ( not M.movie_over) and ((CameraCancelled())  or  (M.movie_time < GetTime() and IsAudioMessageDone(M.audmsg))))
	then
		CameraFinish();
		StopAudioMessage(M.audmsg);
		M.rescue1 = exu.BuildAsyncObject("avapc",1, "apc1_spawn");
		M.rescue2 = exu.BuildAsyncObject("avapc",1, "apc2_spawn");

		M.pull_out_time = GetTime() + 28.0;
		M.turret_move_time = GetTime() + 30.0;

		SetObjectiveOff(M.solar1);
		SetObjectiveOff(M.solar2);

		SetObjectiveOn(M.rescue1);
		SetObjectiveName(M.rescue1, "Transport 1");
		SetCritical(M.rescue1, true);
		SetObjectiveOn(M.rescue2);
		SetObjectiveName(M.rescue2, "Transport 2");
		SetCritical(M.rescue2, true);
		SetObjectiveOn(M.launch);
		SetObjectiveName(M.launch, "Launch Pad");

		ClearObjectives();
		AddObjective("misn0311.otf", "GREEN");
		AddObjective("misn0312.otf", "GREEN"); 
		AddObjective("misn0303.otf", "WHITE");

		M.movie_over = true;
	end

	if ((M.movie_over) and ( not M.remove_props))
	then
		M.audmsg = AudioMessage("misn0306.wav");
		RemoveObject(M.prop1);
		RemoveObject(M.prop2);
		RemoveObject(M.prop3);
		RemoveObject(M.prop4);
		RemoveObject(M.prop5);
--		RemoveObject(M.prop6);
--		RemoveObject(M.prop7);
		if (IsAlive(M.prop8))
		then
			RemoveObject(M.prop8);
		end
		if (IsAlive(M.prop9))
		then
			RemoveObject(M.prop9);
		end
		if (IsAlive(M.guy1))
		then
			RemoveObject(M.guy1);
		end
		if (IsAlive(M.guy2))
		then
			RemoveObject(M.guy2);
		end
		if (IsAlive(M.guy3))
		then
			RemoveObject(M.guy3);
		end
		if (IsAlive(M.guy4))
		then
			RemoveObject(M.guy4);
		end

		M.remove_props = true;
	end

	if (M.remove_props)
	then
		if (( not M.trans_underway) and (M.pull_out_time < GetTime()))
		then
			Retreat (M.rescue1,"rescue_path");
			Retreat (M.rescue2,"rescue_path");
			M.ambush_message_time = GetTime()+ 15.0;
			M.trans_underway = true;
			--M.rescue_move_done = true;
		end
	end
	if (M.remove_props)
	then
		if (( not M.turret_move_done) and (M.turret_move_time < GetTime()))
		then
			Retreat (M.turret1,"turret_path1");
			Retreat (M.turret2,"turret_path2");
			Retreat (M.turret3,"turret_path3");
			Retreat (M.turret4, "base");		
			M.turret_move_done = true;
		end
		if (IsAlive (M.wave1_1))
		then
			Attack(M.wave1_1, M.rescue1 , 1);
		end
		if (IsAlive (M.wave1_2))
		then
			Attack(M.wave1_2, M.rescue1, 1);
		end
--		if (IsAlive (M.wave1_3))
--		then
--			Attack(M.wave1_3, M.rescue2, 1);
--		end
		if (IsAlive (M.wave5_1))
		then
			Attack(M.wave5_1, M.rescue2, 1);
		end
		if (IsAlive (M.wave5_2))
		then
			Attack(M.wave5_2, M.rescue1, 1);
		end
		if (IsAlive (M.wave5_3))
		then
			Attack(M.wave5_3, M.rescue2, 1);
		end
	end
	if ((M.trans_underway) and (M.ambush_message_time < GetTime()) and ( not M.ambush_message))
	then
		AudioMessage("misn0315.wav");
		M.wave6_1 = exu.BuildAsyncObject("svfigh",2,"spawn_scrap1");
		M.wave6_2 = exu.BuildAsyncObject("svtank",2,"spawn_scrap1");
		M.wave6_3 = exu.BuildAsyncObject("svtank",2,"spawn_scrap1");
		Attack (M.wave6_1, M.solar2, 1);
		Attack (M.wave6_2, M.solar1, 1);
		Goto (M.wave6_3, "base", 1);
		M.ambush_message = true;
	end
	if ((M.remove_props) and ( not M.lost) and ( not M.third_objective) 
		 and  (GetDistance(M.rescue1,M.launch) < 100.0) and (GetDistance(M.rescue2,M.launch) < 100.0))
		 -- I removed this for andrew:(GetDistance(M.rescue3,M.launch) < 100.0)
	then
		AudioMessage("misn0310.wav");
		if (IsAlive(M.rescue1))
		then
			SetObjectiveOff(M.rescue1);
		end
		if (IsAlive(M.rescue1))
		then
			SetObjectiveOff(M.rescue2);
		end
		ClearObjectives();
		AddObjective("misn0313.otf", "GREEN");
		AddObjective("misn0304.otf", "WHITE");
		M.wave7_1 = exu.BuildAsyncObject("svtank",2,"spawn_scrap1");
		M.wave7_2 = exu.BuildAsyncObject("svtank",2,"spawn_scrap1");
		M.wave7_3 = exu.BuildAsyncObject("svtank",2,"spawn_scrap1");
		Goto (M.wave7_1, "base", 1);
		Goto (M.wave7_2, "base", 1);
		Goto (M.wave7_3, "base", 1);	
		M.final_check = GetTime() + 120.0;
		M.third_objective = true;
	end

	if (( not M.final_objective) and ( not M.second_warning) and (M.final_check < GetTime()))
	then
		M.final_check = GetTime() + 120.0;
		ClearObjectives();
		AddObjective("misn0313.otf", "GREEN");
		AddObjective("misn0304.otf", "WHITE");
		AudioMessage("misn0310.wav");
		M.second_warning = true;
	end

	if (( not M.final_objective) and (M.second_warning) and ( not M.last_warning) and (M.final_check < GetTime()))
	then
		M.final_check = GetTime() + 120.0;
		ClearObjectives();
		AddObjective("misn0313.otf", "GREEN");
		AddObjective("misn0304.otf", "WHITE");
		AudioMessage("misn0310.wav");
		M.last_warning = true;
	end

	if (( not M.final_objective) and (M.third_objective) and ( not M.final_objective) and (CountUnitsNearObject(M.geyser, 5000.0, 2, "svtank")) < 5.0)
	then
		M.wave7_4 = exu.BuildAsyncObject("svtank",2,"spawn_scrap1");
		M.wave7_5 = exu.BuildAsyncObject("svtank",2,"spawn_scrap1");
		Goto (M.wave7_4, "base", 1);
		Goto (M.wave7_5, "base", 1);
	end


-- win/loose conditions	taken out for movie testing


	if ((M.third_objective) and (GetDistance(M.user,M.launch) < 100.0)  
		 and  ( not M.lost) and ( not M.final_objective))
	then
		M.final_objective = true;
	end

	if (( not M.startfinishingmovie) and (M.final_objective))
		then
		if (IsAlive(M.avrecycler))
		then
			RemoveObject(M.avrecycler);
		end
		if (IsAlive(M.scav1) and M.scav1 ~= M.user)
		then
			RemoveObject(M.scav1);
		end
		if (IsAlive(M.scav2) and M.scav2 ~= M.user)
		then
			RemoveObject(M.scav2);
		end	
		if (IsAlive(M.scav3) and M.scav3 ~= M.user)
		then
			RemoveObject(M.scav3);
		end
		if (IsAlive(M.scav4) and M.scav4 ~= M.user)
		then
			RemoveObject(M.scav4);
		end
		if (IsAlive(M.scav5) and M.scav5 ~= M.user)
		then
			RemoveObject(M.scav5);
		end
		if (IsAlive(M.scav6) and M.scav6 ~= M.user)
		then
			RemoveObject(M.scav6);
		end
		if (IsAlive(M.avturret1) and M.avturret1 ~= M.user)
		then
			RemoveObject(M.avturret1);
		end
		if (IsAlive(M.avturret2) and M.avturret2 ~= M.user)
		then
			RemoveObject(M.avturret2);
		end
		if (IsAlive(M.avturret3) and M.avturret3 ~= M.user)
		then
			RemoveObject(M.avturret3);
		end
		if (IsAlive(M.avturret4) and M.avturret4 ~= M.user)
		then
			RemoveObject(M.avturret4);
		end
		if (IsAlive(M.avturret5) and M.avturret5 ~= M.user)
		then
			RemoveObject(M.avturret5);
		end
		if (IsAlive(M.avturret6) and M.avturret6 ~= M.user)
		then
			RemoveObject(M.avturret6);
		end
		if (IsAlive(M.avturret7) and M.avturret7 ~= M.user)
		then
			RemoveObject(M.avturret7);
		end
		if (IsAlive(M.avturret8) and M.avturret8 ~= M.user)
		then
			RemoveObject(M.avturret8);
		end
		if (IsAlive(M.avturret9) and M.avturret9 ~= M.user)
		then
			RemoveObject(M.avturret9);
		end
		if (IsAlive(M.avturret10) and M.avturret10 ~= M.user)
		then
			RemoveObject(M.avturret10);
		end
		if (IsAlive(M.help1) and M.help1 ~= M.user)
		then
			RemoveObject(M.help1);
		end
		if (IsAlive(M.help2) and M.help2 ~= M.user)
		then
			RemoveObject(M.help2);
		end

		if (IsAlive(M.wave4_1) and M.wave4_1 ~= M.user)
		then
			RemoveObject(M.wave4_1);
		end
		if (IsAlive(M.wave4_2) and M.wave4_2 ~= M.user)
		then
			RemoveObject(M.wave4_2);
		end
		if (IsAlive(M.wave6_1) and M.wave6_1 ~= M.user)
		then
			RemoveObject(M.wave6_1);
		end
		if (IsAlive(M.wave6_2) and M.wave6_2 ~= M.user)
		then
			RemoveObject(M.wave6_2);
		end
		if (IsAlive(M.wave6_3) and M.wave6_3 ~= M.user)
		then
			RemoveObject(M.wave6_3);
		end
		if (IsAlive(M.wave7_1) and M.wave7_1 ~= M.user)
		then
			RemoveObject(M.wave7_1);
		end
		if (IsAlive(M.wave7_2) and M.wave7_2 ~= M.user)
		then
			RemoveObject(M.wave7_2);
		end
		if (IsAlive(M.wave7_3) and M.wave7_3 ~= M.user)
		then
			RemoveObject(M.wave7_3);
		end
		if (IsAlive(M.wave7_4) and M.wave7_4 ~= M.user)
		then
			RemoveObject(M.wave7_4);
		end
		if (IsAlive(M.wave7_5) and M.wave7_5 ~= M.user)
		then
			RemoveObject(M.wave7_5);
		end
		if (IsAlive(M.turret1) and M.turret1 ~= M.user)
		then
			RemoveObject(M.turret1);
		end
		if (IsAlive(M.turret2) and M.turret2 ~= M.user)
		then
			RemoveObject(M.turret2);
		end
		if (IsAlive(M.turret3) and M.turret3 ~= M.user)
		then
			RemoveObject(M.turret3);
		end
		if (IsAlive(M.turret4) and M.turret4 ~= M.user)
		then
			RemoveObject(M.turret4);
		end
		if (IsAlive(M.wave4_1) and M.wave4_1 ~= M.user)
		then
			RemoveObject(M.wave4_1);
		end
		
		M.clean_sweep_time = GetTime() + 14.0;
		M.next_shot = GetTime() + 18.5;
		M.new_unit_time = GetTime() + 2.0;
		M.audmsg = AudioMessage("misn0316.wav");
		M.prop1 = exu.BuildAsyncObject("svtank", 2, "spawna");
		M.prop2 = exu.BuildAsyncObject("svtank", 2, "spawnb");
		M.prop3 = exu.BuildAsyncObject("svtank", 2, "spawnc");
		CameraReady();
		M.startfinishingmovie = true;
	end

	if ((M.startfinishingmovie) and ( not M.camera_2))
	then
		--[[
		  Camera canceled
		  could be called and this would
		  still play
		--]]
		CameraPath("camera_path", M.x, 3500, M.cam_geyser);
		--x = x - 15;
		M.x = math.max(160, M.x - (240 * GetTimeStep()));
		M.camera_on = true;
	end

	if ((M.startfinishingmovie) and ( not M.tanks_go))
	then
		if (M.new_unit_time < GetTime())
		then
			Goto(M.prop1, "line1", 1);
			Goto(M.prop2, "line2", 1);
			Goto(M.prop3, "line3", 1);

			M.tanks_go = true;
		else
			Defend(M.prop1);
			Defend(M.prop2);
			Defend(M.prop3);
		end
	end

	if ((M.startfinishingmovie) and (M.clean_sweep_time < GetTime()) and ( not M.clean_sweep))
	then
		M.clean_sweep = true;
	end

	if ((M.startfinishingmovie) and (M.next_shot < GetTime()) and ( not M.camera_off))
	then
		CameraPath("inbase_path", 160, 90, M.prop1);
		M.camera_2 = true;
	end

	if ((M.camera_2) and ( not M.speach2))
	then
		M.audmsg = AudioMessage("misn0317.wav");
		M.speach2 = true;
	end

	if ((M.camera_2) and ( not M.show_tank_attack))
	then
		if (GetDistance(M.prop1, M.shot_geyser) < 20.0)
		then 
			if (IsAlive(M.solar1))
			then
				Attack(M.prop1, M.solar1);
				Attack(M.prop2, M.solar1);
				if (IsAlive(M.solar2))
				then
					Damage(M.solar2, 20000);
				end
				if (IsAlive(M.solar3))
				then
					Damage(M.solar3, 20000);
				end
				if (IsAlive(M.solar4))
				then
					Damage(M.solar4, 20000);
				end
				M.kill_tower = GetTime() + 7.0;
				M.show_tank_attack = true;
			end
		end
	end

	if ((M.show_tank_attack) and ( not M.tower_dead) and (M.kill_tower < GetTime()))
	then
		if (IsAlive(M.solar1))
		then
			Damage(M.solar1, 25000);
			M.tower_dead = true;
		end
	end

	if ((M.tower_dead) and ( not M.climax1))
	then
		Retreat(M.prop1, "climax_path1", 1);
		Retreat(M.prop2, "spawn_scrap1", 1);
		Retreat(M.prop3, "spawn_scrap1", 1);
		M.clear_debis_time = GetTime() + 6.0;
		M.audmsg = AudioMessage("misn0318.wav");
		M.climax1 = true;
	end

	if ((M.climax1) and ( not M.clear_debis) and (M.clear_debis_time < GetTime()))
	then
--		if (IsAlive(M.build2))
--		then
--			Damage(M.build2, 20000);
--		end
		if (IsAlive(M.build3))
		then
			Damage(M.build3, 20000);
		end
--		if (IsAlive(M.build2))
--		then
--			RemoveObject(M.build2);
--		end
		M.prop8 = exu.BuildAsyncObject("svtank", 2, M.cam_geyser);
		Retreat(M.prop8, "climax_path2", 1);
		M.clear_debis = true;
	end

	if ((M.climax1) and ( not M.climax2))
	then
		if (GetDistance(M.prop1, M.cam_geyser) < 100.0)
		then
			Retreat(M.prop1, "climax_path2", 1);
			M.prop9 = exu.BuildAsyncObject("svfigh", 2, "solar_spot");
			M.prop0 = exu.BuildAsyncObject("svfigh", 2, "solar_spot");
			Retreat(M.prop9, "camera_pass", 1);
			Retreat(M.prop0, "camera_pass", 1);
			if (IsAlive(M.hanger))
			then
				Damage(M.hanger, 20000);
			end
			M.clear_debis_time = GetTime() + 3.0;
			M.climax2 = true;
		end
	end

	if ((M.climax2) and ( not M.last_blown) and (M.clear_debis_time < GetTime())) 
	then
		if (IsAlive(M.box1))
		then
			Damage(M.box1, 20000);
		end
		if (IsAlive(M.build1))
		then
			Damage(M.build1, 20000);
		end
		if (IsAlive(M.crate1))
		then
			Damage(M.crate1, 20000);
		end
		if (IsAlive(M.crate2))
		then
			Damage(M.crate2, 20000);
		end
		if (IsAlive(M.crate3))
		then
			Damage(M.crate3, 20000);
		end

		Retreat(M.prop2, "solar_spot");
		Retreat(M.prop8, "spawn_scrap1", 1);
		sucker = exu.BuildAsyncObject("abwpow", 1, "sucker_spot");
--		M.clear_debis_time = GetTime() + 6.0;
		M.last_blown = true;
	end

	if ((M.last_blown) and ( not M.end_shot) and (GetDistance(M.prop1, sucker) < 65.0))
	then
		Attack(M.prop1, sucker, 1);
		M.camera_off_time = GetTime() + 1.5;
		M.end_shot = true;
	end

	if ((M.camera_on) and ( not M.camera_off) and ((CameraCancelled())  or  (M.camera_off_time < GetTime())))
	then
		M.startfinishingmovie = false;
		CameraFinish();
		StopAudioMessage(M.audmsg);
		SucceedMission(0.1, "misn03w1.des");
		M.camera_off = true;
	end


-- win/loose conditions

	if ((M.last_warning) and (M.final_check < GetTime()) and ( not M.final_objective) and ( not M.lost))
	then
		FailMission(GetTime() + 1.0, "misn03f5.des"); -- you didn't reach the M.launch pad in time
		M.lost = true;
	end
	
	if (( not M.dead1) and ( not M.show_tank_attack) and ( not M.second_objective) and ( not IsValid(M.solar1))) --new
	then
		AudioMessage("misn0302.wav");
		ClearObjectives();
		AddObjective("misn0311.otf", "RED");
		AddObjective("misn0312.otf", "WHITE"); 
		M.lost = true;
		M.dead1 = true;
		if ( not M.turrets_set)
		then
			FailMission(GetTime() + 10.0, "misn03f1.des"); -- com tower dead - you didn't build enough turrets
		else
			FailMission(GetTime() + 10.0, "misn03f2.des"); -- com tower dead
		end
	end

	if (( not M.dead2) and ( not M.tanks_go) and ( not M.second_objective) and ( not IsValid(M.solar2))) --new
	then
		AudioMessage("misn0303.wav");
		ClearObjectives();
		AddObjective("misn0311.otf", "RED");
		AddObjective("misn0312.otf", "WHITE"); 
		M.lost = true;
		M.dead2 = true;
		if ( not M.turrets_set)
		then
			FailMission(GetTime() + 10.0, "misn03f3.des"); --/ solar arrays dead - you didn't build enough turrets
		else
			FailMission(GetTime() + 10.0, "misn03f3.des"); --/ solar arrays dead
		end
	end

	if ((M.movie_over) and ( not M.dead3) and ( not IsAlive(M.rescue1)) and ( not M.third_objective))
	then
		AudioMessage("misn0304.wav");
		ClearObjectives();
		AddObjective("misn0311.otf", "GREEN");
		AddObjective("misn0312.otf", "GREEN"); 
		AddObjective("misn0303.otf", "RED");
		M.lost = true;
		M.dead3 = true;
		FailMission(GetTime() + 10.0, "misn03f4.des"); -- transport dead
	end
	if ((M.movie_over) and ( not M.dead3) and ( not IsAlive(M.rescue2)) and ( not M.third_objective))
	then
		AudioMessage("misn0304.wav");
		ClearObjectives();
		AddObjective("misn0311.otf", "GREEN");
		AddObjective("misn0312.otf", "GREEN"); 
		AddObjective("misn0303.otf", "RED");
		M.lost = true;
		M.dead3 = true;
		FailMission(GetTime() + 10.0, "misn03f4.des"); -- transport dead
	end

	if (( not IsAlive(M.launch)) and ( not M.lost))
	then
		FailMission(GetTime() + 1.0); -- M.lost your M.launch pad no des
		M.lost = true;
	end

-- END OF SCRIPT
	
end