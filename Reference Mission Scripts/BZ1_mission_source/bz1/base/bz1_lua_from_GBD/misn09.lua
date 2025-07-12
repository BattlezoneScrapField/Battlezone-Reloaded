-- Single Player NSDF Mission 8 Lua conversion, created by General BlackDragon. 

-- Single Table for all our save/load variables. This SP mission has too many variables to function with them independently. ("main function has > 200 local variables", or "Load having > 197 variables in assignment")
local M = {

-- bools
	start_done = false,
	convoy_started = false,
	camera_ready = false,
	--camera_artil = false,
	build_new_tug = false,
	tug_done = false,
	objective1 = false,
	first_warning = false,
	second_warning = false,
	third_warning = false,
	--player_dead = false,
	muf_contact = false,
	muf_moving = false,
	--post1 = false,
	--post2 = false,
	--post3 = false,
	--post4 = false,
	--guard1 = false,
	--guard2 = false,
	turret1_set = false,
	turret2_set = false,
	turret3_set = false,
	turret4_set = false,
	--get_relic = false,
	relic_secure = false,
	relic_seized = false,
	relic_free = false,
	tug_underway = false,
	head_4_pad = false,
	game_over = false,
	next_shot = false,
	player_camera_off = false,
	next_shot_message = false,
	cam1_on = false,
	cam2_on = false,
	cam3_on = false,
	cam4_on = false,
	cam5_on = false,
	cam_off = false,
	convoy_cam_ready = false,
	convoy_cam_off = false,
	muf_deployed = false,
	scavs_alive = false,
	charon_found = false,
	charon_build = false,
	start = false,
	opening_vo = false,
	muf_gobaby = false,
	recon_artil = false,
	base_warning = false,
	muf_deployed_good = false,
	ccadead = false,
	start_camera1 = false,
	game_over5 = false,
-- Floats (really doubles in Lua)
	start_convoy_time = 0,
	camera_ready_time = 0,
	build_tug_time = 0,
	first_warning_time = 0,
	second_warning_time = 0,
	third_warning_time = 0,
	--camera_on_time = 0,
	muf_check = 0,
	movie_time = 0,
	unit_check = 0,
	--turret1_time = 0,
	--turret2_time = 0,
	--turret3_time = 0,
	--turret4_time = 0,
	win_check = 0,
	atril_check = 0,
	player_camera_time = 0,
	next_shot_time = 0,
	cam1_time = 0,
	cam2_time = 0,
	cam3_time = 0,
	cam4_time = 0,
	cam5_time = 0,
	convoy_cam_time = 0,
	deploy_check = 0,
	charon_check = 0,
	start_time = 0,
	recon_message_time = 0,
-- Handles
	user = nil,
	relic = nil,
	nav1 = nil,
	charon = nil,
	avsilo = nil,
	key_scrap = nil,
	ccatug = nil,
	nsdftug = nil,
	convoy_geyser = nil,
	cut_off_geyser = nil,
	ccaturret1 = nil,
	ccaturret2 = nil,
	ccaturret3 = nil,
	ccaturret4 = nil,
	ccaturret5 = nil,
	ccaturret6 = nil,
	ccarecycle = nil,
	ccamuf = nil,
	--ccaarmor = nil,
	ccalaunch = nil,
	cca1 = nil,
	cca2 = nil,
	cca3 = nil,
	cca4 = nil,
	cca5 = nil,
	cca6 = nil,
	cca7 = nil,
	cca8 = nil,
	cca9 = nil,
	cca0 = nil,
	scav1 = nil,
	scav2 = nil,
	scav3 = nil,
	--nsdfrecycle = nil,
	nsdfmuf = nil,
	avscav1 = nil,
	avscav2 = nil,
	avscav3 = nil,
	nsdfgech1 = nil,
	--construct = nil,
	nsdfslf = nil,
	nsdfrig = nil,
	tugger = nil,
	convoy1 = nil,
	convoy2 = nil,
	convoy3 = nil,
	convoy4 = nil,
	convoy5 = nil,
	convoy6 = nil,
	convoy7 = nil,
	convoy8 = nil,
	convoy9 = nil,
	convoy0 = nil,
	charon_nav = nil,
-- Ints
	stuff = 0,
	x = 0,
	y = 0,
	scrap = 0,
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

	M.x = 950;
	M.y = 3000;
	M.scrap = 100;
	
	M.start_convoy_time = 99999.0;
	M.camera_ready_time = 99999.0;
	M.build_tug_time = 99999.0;
	--M.camera_on_time = 99999.0;
	M.first_warning_time = 99999.0;
	M.second_warning_time = 99999.0;
	M.third_warning_time = 99999.0;
	M.muf_check = 99999.0;
	M.movie_time = 99999.0;
	--M.turret1_time = 99999.0;
	--M.turret2_time = 99999.0;
	--M.turret3_time = 99999.0;
	--M.turret4_time = 99999.0;
	M.unit_check = 99999.0;
	M.win_check = 99999.0;
	M.atril_check = 99999.0;
	M.player_camera_time = 99999.0;
	M.next_shot_time = 99999.0;
	M.cam1_time = 99999.0;
	M.cam2_time = 99999.0;
	M.cam3_time = 99999.0;
	M.cam4_time = 99999.0;
	M.cam5_time = 99999.0;
	M.convoy_cam_time = 99999.0;
	M.deploy_check = 99999.0;
	M.charon_check = 99999.0;
	M.start_time = 20.0;
	M.recon_message_time = 99999.0;

	M.ccaturret1 = GetHandle("artil1");
	M.ccaturret2 = GetHandle("artil2");
	M.ccaturret3 = GetHandle("artil3");
	M.ccaturret4 = GetHandle("artil4");
	M.ccaturret5 = GetHandle("artil5");
	M.ccaturret6 = GetHandle("artil6");
	M.ccarecycle = GetHandle("svrecycle");
	M.avscav1 = GetHandle("scav1");
	M.avscav2 = GetHandle("scav2");
	M.avscav3 = GetHandle("scav3");
	M.nsdfrig = GetHandle("rig");
	M.nsdfslf = GetHandle("avslf");
	M.ccamuf = GetHandle("svmuf");
	M.nsdfmuf = GetHandle("avmuf");
	M.convoy_geyser = GetHandle("convoy_geyser");
	M.ccalaunch = GetHandle("launchpad");
	M.nav1 = GetHandle("cam1");
	M.charon = GetHandle("hbchar0_i76building");
	M.cut_off_geyser = GetHandle("cut_off_geyser");
	M.key_scrap = GetHandle("key_scrap");
	
end

function AddObject(h)

	if ((M.cca1 == nil) and (IsOdf(h,"svturr")))
	then
		M.cca1 = h;
	else
		if ((M.cca2 == nil) and (IsOdf(h,"svturr")))
		then
			M.cca2 = h;
		else
			if ((M.cca3 == nil) and (IsOdf(h,"svturr")))
			then
				M.cca3 = h;
			else
				if ((M.cca4 == nil) and (IsOdf(h,"svturr")))
				then
					M.cca4 = h;
				else
					if ((M.cca5 == nil) and (IsOdf(h,"svfigh")))
					then
						M.cca5 = h;
					else
						if ((M.cca6 == nil) and (IsOdf(h,"svfigh")))
						then
							M.cca6 = h;
						else
							if ((M.cca7 == nil) and (IsOdf(h,"svfigh")))
							then
								M.cca7 = h;
							else
								if ((M.cca8 == nil) and (IsOdf(h,"svfigh")))
								then
									M.cca8 = h;
								else
									if ((M.cca9 == nil) and (IsOdf(h,"svtank")))
									then
										M.cca9 = h;
									else
										if ((M.cca0 == nil) and (IsOdf(h,"svtank")))
										then
											M.cca0 = h;
										else
											if ((M.scav1 == nil) and (IsOdf(h,"svscav")))
											then
												M.scav1 = h;
											else
												if ((M.scav2 == nil) and (IsOdf(h,"svscav")))
												then
													M.scav2 = h;
												else
													if ((M.scav3 == nil) and (IsOdf(h,"svscav")))
													then
														M.scav3 = h;
													else
														if ((M.nsdfgech1 == nil) and (IsOdf(h,"avwalk")))
														then
															M.nsdfgech1 = h;
														else
															if ((M.ccatug == nil) and (IsOdf(h,"svhaul")))
															then
																M.ccatug = h;
															else
																if ((M.avsilo == nil) and (IsOdf(h,"absilo")))
																then
																	M.avsilo = h;
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
	end

end

function Update()

-- START OF SCRIPT

	if ((M.relic_free) and (IsAlive(M.relic)))
	then
		M.tugger = GetTug(M.relic);

		if (IsAlive(M.tugger))
		then
			if (GetTeamNum(M.tugger) == 1)
			then
				M.relic_free = false;
				M.relic_secure = true;
			else
				M.relic_free = false;
				M.relic_seized = true;
				M.tugger = M.ccatug;
			end
		end
	end

	if ((M.relic_secure) and ( not IsAlive(M.tugger)))
	then
		M.relic_free = true;
		M.relic_secure = false;
	end

	if ((M.relic_seized) and ( not IsAlive(M.ccatug)))
	then
		M.relic_free = true;
		M.relic_seized = false;
	end

	if (IsAlive(M.relic))
	then
		if ((IsAlive(M.ccatug)) and (M.relic_free) and ( not M.tug_underway))
		then
			Pickup(M.ccatug, M.relic);
			M.tug_underway = true;
		end

		if ((M.relic_seized) and ( not M.head_4_pad))
		then
			Dropoff(M.ccatug, "soviet_path", 1);
			M.head_4_pad = true;
		end
	end

	if ( not IsAlive(M.ccatug))
	then
		M.tug_underway = false;
		M.head_4_pad = false;
	end


--[[	if (IsAlive(M.nsdftug))
	then
		if (HasCargo(M.nsdftug))
		then
			M.relic_free = false;
			M.relic_secure = true;
		else
			if ( not M.relic_seized)
			then
				M.relic_free = true;
				M.relic_secure = false;
			end
		end
	end

--]]
	M.user = GetPlayerHandle(); --assigns the player a handle every frame

--	if ((M.start_time < GetTime()) and ( not M.start))
--	then
--		M.start = true;
--	end

	if ( not M.start_done)
	then
		CameraReady();
		Defend(M.nsdfmuf);
		SetScrap(2,40);
		SetPilot(2, 40);
	    Follow(M.nsdfrig, M.nsdfmuf, 1);
		Follow(M.avscav1, M.nsdfmuf, 1);
		Follow(M.avscav2, M.nsdfmuf, 1);
		Follow(M.avscav3, M.nsdfmuf, 1);
		Follow(M.nsdfslf, M.nsdfrig, 0);
		Defend(M.ccaturret1);
		Defend(M.ccaturret2);
		Defend(M.ccaturret3);
		Defend(M.ccaturret4);
		Defend(M.ccaturret5);
		Defend(M.ccaturret6);
--		M.start_convoy_time = GetTime() + 900.0;		
		M.camera_ready_time = GetTime() + 6.0;
		M.muf_check = GetTime() + 3.0;
		M.first_warning_time = GetTime() + 700.0;
		M.second_warning_time = GetTime() + 1000.0;
		M.third_warning_time = GetTime() + 1300.0; -- was 900.0
		M.unit_check = GetTime() + 1360.0;
		M.atril_check = GetTime() + 15.0;
		M.player_camera_time = GetTime() + 11.0;
		M.deploy_check = GetTime() + 6.0;
		M.charon_check = GetTime() + 30.0;
		M.next_shot_time = GetTime() + 22.0;
		SetObjectiveName(M.nav1, "Choke Point");
		M.start_camera1 = true;
		M.start_done = true;
	end

	if (M.start_camera1)
	then
		CameraPath("camera_circle", 375, 750, M.key_scrap);
	end
--[[
	if (( not M.next_shot_message) and ((M.player_camera_time < GetTime())  or  (CameraCancelled())))
	then
		CameraPath("launch_camera_path", 7000, 1150, M.ccalaunch);

		if (M.x > 6000.0)
		then
			M.x = M.x - 150;
		else
			M.x = M.x + 50;
		end
		M.y = M.y - 20;
--]]		
--[[		M.next_shot = true;
	end

	if (( not M.next_shot_message) and (IsAudioMessageDone(M.audmsg)))
	then
		M.audmsg = AudioMessage("misn0912.wav");
		M.next_shot_time = GetTime() + 6.0;
		M.next_shot_message = true;
	end

	if ((M.next_shot_message) and ( not M.player_camera_off)) 
	then
		CameraPath("choke_cam_path", 375, 450, M.nav1);
	end
--]]
	if (( not M.player_camera_off) and ((M.next_shot_time < GetTime())  or  (CameraCancelled())))
	then
		ClearObjectives();
		AddObjective("misn0900.otf", "WHITE");
		CameraFinish();
		M.start_camera1 = false;
		M.player_camera_off = true;
	end
 
	if (CameraCancelled())
	then
		StopAudioMessage(M.audmsg);
	end

-- this starts the opening voice-over

	if (((M.camera_ready_time < GetTime()) and ( not M.opening_vo)))
	then
		M.audmsg = AudioMessage("misn0900.wav"); --starts opening V.O.5
		M.opening_vo = true;
	end

	if ((M.opening_vo) and ( not M.muf_gobaby) and (IsAudioMessageDone(M.audmsg)))
	then
		ClearObjectives();
		AddObjective("misn0900.otf", "WHITE");
		Goto(M.nsdfmuf, "return_path", 1);
		M.muf_gobaby = true;
	end

-- this tells the muf to stop when the player gets close & plays the artillery message
	if ((M.muf_gobaby) and (M.muf_check < GetTime()) and ( not M.muf_contact))
	then
		M.muf_check = GetTime() + 1.0;

		if (GetDistance(M.user, M.nsdfmuf) < 70.0)
		then
			Stop(M.nsdfmuf, 0);
			Stop(M.nsdfslf, 0);
			Defend(M.nsdfrig, 0);
			SetScrap(1,20);
			SetPilot(1, 7);
			AudioMessage("misn0905.wav"); -- message from muf "we took a beating out there"
			M.movie_time = GetTime() + 7.0;
			M.muf_contact = true;
		end

	end

	if (( not M.objective1) and (M.atril_check < GetTime()))
	then
		M.atril_check = GetTime() + 15.0;

		if (IsAlive(M.ccaturret1))
		then
			Defend(M.ccaturret1);
		end
		if (IsAlive(M.ccaturret2))
		then
			Defend(M.ccaturret2);
		end
		if (IsAlive(M.ccaturret3))
		then
			Defend(M.ccaturret3);
		end
		if (IsAlive(M.ccaturret4))
		then
			Defend(M.ccaturret4);
		end
		if (IsAlive(M.ccaturret5))
		then
			Defend(M.ccaturret5);
		end
		if (IsAlive(M.ccaturret6))
		then
			Defend(M.ccaturret6);
		end
	end

-- this starts the muf towards the player
--[[	if ((M.player_camera_off) and ( not M.muf_moving))
	then
		Goto(M.nsdfmuf, "return_path", 1);
		Follow(M.nsdfrig, M.nsdfmuf, 1);
		Follow(M.avscav1, M.nsdfmuf, 1);
		Follow(M.avscav2, M.nsdfmuf, 1);
		Follow(M.avscav3, M.nsdfmuf, 1);
		Follow(M.nsdfslf, M.nsdfrig, 1);
		M.muf_moving = true;
	end
--]]

-- this checks to see if the muf is deployed

	if ((M.deploy_check < GetTime()) and ( not M.muf_deployed))
	then
		M.deploy_check = GetTime() + 2.0;

		if (IsAlive(M.nsdfmuf))
		then
			if (IsDeployed(M.nsdfmuf))
			then
				M.muf_deployed = true;
			end
		end
	end

	if (((M.muf_deployed)  or  (IsAlive(M.avsilo))) and ( not M.scavs_alive))
	then
		Stop(M.avscav1, 0);
		Stop(M.avscav2, 0);
		Stop(M.avscav3, 0);
		M.scavs_alive = true;
	end

-- This turns the camera over the artilery units on/off --------

	if (IsAlive(M.ccaturret6))
	then
		if ((M.muf_contact) and (M.movie_time < GetTime()) and ( not M.camera_ready))
		then

			CameraReady();
			M.cam5_time = GetTime() + 7.0;
			M.camera_ready = true;
		end
--[[
		if ((M.camera_ready) and ( not M.cam_off))
		then
			CameraPath("camera_path", M.x, 300, M.ccaturret6);
			M.x = M.x + 90;
		end

		if ((M.camera_ready) and (M.cam5_time < GetTime()) and ( not M.cam_off))		
		then															
			CameraFinish();
			ClearObjectives();
			AddObjective("misn0900.otf", "GREEN");
			AddObjective("misn0901.otf", "WHITE");
			Stop(M.nsdfrig, 0);
			SetAIP("misn09.aip");
			M.recon_message_time = GetTime() + 60.0;
			M.cam_off = true;
		end
--]]	end

	if ((M.recon_message_time < GetTime()) and ( not M.recon_artil))
	then
		M.recon_message_time = GetTime() + 1.0;
		AudioMessage("misn0913.wav");
		M.recon_artil = true;
	end

	if ((M.recon_message_time < GetTime()) and ( not M.base_warning))
	then
		M.recon_message_time = GetTime() + 2.0;

		if (((IsAlive(M.nav1)) and (GetDistance(M.user, M.nav1) < 100.0))  or 
			((IsAlive(M.cca5)) and (GetDistance(M.user, M.cca5) < 400.0))  or 
			((IsAlive(M.cca6)) and (GetDistance(M.user, M.cca6) < 400.0)))
		then
			AudioMessage("misn0914.wav");
			M.base_warning = true;
		end
	end

	if ((M.camera_ready) and ( not M.cam2_on))	
	then
		CameraObject(M.ccaturret6, 3000, 3000, 3000, M.ccaturret6);
		if ( not M.cam1_on)
		then
			M.cam1_time = GetTime() + 2.0;
			M.cam1_on = true;
		end
	end

	if ((M.cam1_on) and (M.cam1_time < GetTime()) and ( not M.cam3_on))
	then
		CameraObject(M.ccaturret5, 3000, 3000, 3000, M.ccaturret5);
		if ( not M.cam2_on)
		then
			M.cam2_time = GetTime() + 2.0;
			M.cam2_on = true;
		end
	end

	if ((M.cam2_on) and (M.cam2_time < GetTime()) and ( not M.cam4_on))
	then
		CameraObject(M.ccaturret4, 3000, 3000, 3000, M.ccaturret4);
		if ( not M.cam3_on)
		then
			M.cam3_time = GetTime() + 2.0;
			M.cam3_on = true;
		end
	end

	if ((M.cam3_on) and (M.cam3_time < GetTime()) and ( not M.cam5_on))
	then
		CameraObject(M.ccaturret3, 3000, 3000, 3000, M.ccaturret3);
		if ( not M.cam4_on)
		then
			M.cam4_time = GetTime() + 2.0;
			M.cam4_on = true;
		end
	end

	if ((M.cam4_on) and (M.cam4_time < GetTime()) and ( not M.cam_off))
	then
		CameraObject(M.ccaturret2, 3000, 3000, 3000, M.ccaturret2);
		if ( not M.cam5_on)
		then
			M.cam5_time = GetTime() + 2.0;
			M.cam5_on = true;
		end
	end

	if ((M.cam5_on) and (M.cam5_time < GetTime()) and ( not M.cam_off))		
	then															
		CameraFinish();
		ClearObjectives();
		AddObjective("misn0900.otf", "GREEN");
		AddObjective("misn0901.otf", "WHITE");
		Stop(M.nsdfrig, 0);
		SetAIP("misn09.aip");
		M.cam_off = true;
	end

-- end of camera script for artiliery units --------------------

	-- this is going to set up a fortification of turrets
	if	((IsAlive(M.ccarecycle)) and (M.turret1_set == false))
	then
		M.cca1 = BuildObject("svturr", 2, "post1");
		M.turret1_set = true;
		Defend(M.cca1);
	end
	if	((IsAlive(M.ccarecycle)) and (M.turret2_set == false))
	then
		M.cca2 = BuildObject("svturr", 2, "post2");
		M.turret2_set = true;
		Defend(M.cca2);
	end
	if	((IsAlive(M.ccarecycle)) and (M.turret3_set == false))
	then
		M.cca3 = BuildObject("svturr", 2, "post3");
		M.turret3_set = true;
		Defend(M.cca3);
	end
	if	((IsAlive(M.ccarecycle)) and (M.turret4_set == false))
	then
		M.cca4 = BuildObject("svturr", 2, "post4");
		M.turret4_set = true;
		Defend(M.cca4);
	end

-- this is to insure that the soviets keep trying to get the database M.relic	
--[[																			
	if ((M.convoy_started) and ( not IsAlive (M.ccatug)) and (IsAlive(M.ccarecycle)) and ( not M.build_new_tug))	
	then																		
		M.build_tug_time = GetTime () + 60.0;-- was 60 seconds
		M.tug_done = false;
		M.build_new_tug = true;												
	end																		
																			
	if ((M.build_new_tug) and (M.build_tug_time < GetTime()) and ( not M.tug_done))	
	then																		
		M.ccatug = BuildObject("svhaul", 2, M.ccarecycle);
--		M.convoy_started = false; -- should change this to somthing else
		M.build_new_tug = false;
		M.tug_done = true;
	end																								
--]]	
-- if player destroys all the cca turrets----------------------------------------------/

	if(( not IsAlive (M.ccaturret1)) and ( not IsAlive (M.ccaturret2)) and ( not IsAlive (M.ccaturret3))
		 and  ( not IsAlive (M.ccaturret4)) and ( not IsAlive (M.ccaturret5)) and ( not IsAlive (M.ccaturret6))
		 and  ( not M.objective1))
	then
		AudioMessage("misn0904.wav");--congradulations you killed the turrets
		Stop(M.avscav1, 0);
		Stop(M.avscav2, 0);
		Stop(M.avscav3, 0);
		ClearObjectives();
		AddObjective("misn0901.otf", "GREEN");
		AddObjective("misn0902.otf", "WHITE");
		AddObjective("misn0903.otf", "WHITE");
		if ( not M.third_warning)
		then
			SetAIP("misn09a.aip"); -- causes the soviets to get more aggresive
		end

		M.objective1 = true;
	end

-- this is the general warning of the approaching convoy --------------------------------

	if (( not M.first_warning) and (M.first_warning_time < GetTime()))	
	then
		AudioMessage("misn0901.wav"); -- the soviets convey will be here in less than 10 minutes
		M.first_warning = true;
	end

	if (( not M.second_warning) and (M.second_warning_time < GetTime()))	
	then
		AudioMessage("misn0902.wav"); -- the soviets convey will be here in less than 5 minutes
		M.second_warning = true;
	end

	if (( not M.third_warning) and (M.third_warning_time < GetTime()))	
	then
		M.third_warning_time = GetTime() + 11.0;

		if (GetDistance(M.user, M.convoy_geyser) > 500.0)
		then
			M.relic = BuildObject("obdata", 0, M.convoy_geyser);
			M.ccatug = BuildObject("svhaul", 2, "spawn1");
			M.convoy1 = BuildObject("svfigh", 2, "spawn2");
			M.convoy2 = BuildObject("svfigh", 2, "spawn2");
			M.convoy3 = BuildObject("svfigh", 2, "spawn2");
			M.convoy4 = BuildObject("svfigh", 2, "spawn3");
			M.convoy5 = BuildObject("svtank", 2, "spawn3");
			M.convoy6 = BuildObject("svtank", 2, "spawn3");
			M.convoy7 = BuildObject("svtank", 2, "spawn4");
			M.convoy8 = BuildObject("svtank", 2, "spawn4");
			M.convoy9 = BuildObject("svapc", 2, "spawn4");
			M.convoy0 = BuildObject("svapc", 2, "spawn4");
			Defend(M.convoy1);
			Defend(M.convoy2);
			Defend(M.convoy3);
			Defend(M.convoy4);
			Defend(M.convoy5);
			Defend(M.convoy6);
			Defend(M.convoy7);
			Defend(M.convoy8);
			Defend(M.convoy9);
			Defend(M.convoy0);
--			Pickup(M.ccatug, M.relic); -- should do automatically

			if ( not M.objective1)
			then
				ClearObjectives();
				AddObjective("misn0901.otf", "RED");
				AddObjective("misn0902.otf", "WHITE");
				AddObjective("misn0903.otf", "WHITE");
			end

			M.win_check = GetTime() + 5.0;
			SetAIP("misn09b.aip"); -- causes the soviets to get more reserved
			M.relic_free = true;			
			M.third_warning = true;
		end

	end

-- this starts the convoy towards the launch pad ------------------------------------

	if ((M.third_warning) and (M.relic_seized) and ( not M.convoy_started))		
	then
		SetObjectiveOn(M.relic);
		SetObjectiveName(M.relic, "Alien Relic");
		Goto(M.ccatug, "soviet_path", 1);
		Follow(M.convoy1, M.ccatug);
		Follow(M.convoy2, M.ccatug);
		Follow(M.convoy3, M.ccatug);
		Follow(M.convoy4, M.ccatug);
		Follow(M.convoy5, M.ccatug);
		Follow(M.convoy6, M.ccatug);
		Follow(M.convoy7, M.ccatug);
		Follow(M.convoy8, M.ccatug);
		Follow(M.convoy9, M.ccatug);
		Follow(M.convoy0, M.ccatug);
		M.convoy_cam_time = GetTime() + 7.0;
		M.convoy_started = true;									
	end
	
	if ((M.convoy_started) and ( not M.convoy_cam_ready) and (M.convoy_cam_time < GetTime()))
	then
		AudioMessage("misn0903.wav"); -- the soviets convey is within radar range "I'm picking up the soviet convoy"
		CameraReady();
		M.convoy_cam_time = GetTime() + 18.0;
		M.convoy_cam_ready = true;
	end

	if ((M.convoy_cam_ready) and ( not M.convoy_cam_off))
	then
		CameraPath("convoy_cam_path", M.y, 1150, M.ccatug);
		M.y = M.y - 4;
	end

	if ((M.convoy_cam_ready) and ( not M.convoy_cam_off) and ((M.convoy_cam_time < GetTime())  or  (CameraCancelled())))
	then
		CameraFinish();
		M.convoy_cam_off = true;
	end

-- this is the M.charon code

	if ((IsAlive(M.charon)) and ( not M.charon_found))
	then
		if (M.charon_check < GetTime())
		then
			M.charon_check = GetTime() + 2.0;

			if (GetDistance(M.user, M.charon) < 70.0)
			then
				AudioMessage("misn0915.wav");-- told to check out the M.charon
				M.charon_found = true;
			end
		end
	end

	if ((M.charon_found) and (IsInfo("hbchar") == true) and ( not M.charon_build))
	then
		AudioMessage("misn0916.wav");-- well done, we'll drop a nav camera here to come back to this, this looks like a good spot to go after artils
		M.charon_nav = BuildObject ("apcamr", 1, "charon_spawn"); 
		SetObjectiveName(M.charon_nav, "Alien Relic");
		M.charon_build = true;
	end


-- this is to check and see if the muf is deployed correctly
	if ((M.objective1)  or  (M.third_warning))
	then
		if (( not M.muf_deployed_good) and (M.deploy_check < GetTime()))
		then
			M.deploy_check = GetTime() + 2.0;

			if (IsAlive(M.nsdfmuf))
			then
				if ((IsDeployed(M.nsdfmuf)) and (GetDistance(M.nsdfmuf, M.convoy_geyser) < 1400.0))
				then
					if (M.objective1)
					then
						ClearObjectives();
						AddObjective("misn0901.otf", "GREEN");
						AddObjective("misn0902.otf", "GREEN");
						AddObjective("misn0903.otf", "WHITE");
						M.muf_deployed_good = true;
					else
						ClearObjectives();
						AddObjective("misn0901.otf", "RED");
						AddObjective("misn0902.otf", "GREEN");
						AddObjective("misn0903.otf", "WHITE");
						M.muf_deployed_good = true;
					end
				end
			end
		end
	end

	if (( not IsAlive(M.ccarecycle)) and ( not IsAlive(M.ccamuf)) and ( not M.ccadead))
	then
		AudioMessage("misn0908.wav");-- you've cleared the area of the enemy well done
		M.ccadead = true;		
	end

-- end of general's warings ------------------------------------------------------------/

-- win/victory conditions  

	if ((M.scavs_alive) and ( not IsAlive(M.avscav1)) and ( not IsAlive(M.avscav2)) and ( not IsAlive(M.avscav3)) and ( not M.game_over))
	then
		if (( not M.objective1) and ( not M.first_warning))
		then
			M.scrap = GetScrap(1);

			if (M.scrap < 10)
			then
				FailMission(GetTime() + 6.0, "misn09f4.des");
				M.game_over = true;				
			end
		end
	end

	if ((M.convoy_started) and ( not IsAlive(M.relic)) and ( not M.game_over))
	then
		AudioMessage("misn0906.wav"); -- the M.relic has been destroyed commander
		FailMission(GetTime() + 15.0, "misn09f1.des");
		M.game_over = true;
	end

	if ((M.relic_seized) and (IsAlive(M.ccalaunch)) and (GetDistance(M.ccatug, M.ccalaunch) < 100.0) and ( not M.game_over))
	then
		AudioMessage("misn0907.wav"); -- the tug has reached the launch pad
		FailMission(GetTime() + 15.0, "misn09f2.des");
		M.game_over = true;
	end
	
	if ((M.convoy_started) and (M.unit_check < GetTime()) and ( not M.game_over5))
	then
		M.unit_check = GetTime() + 10.0;
		M.stuff = CountUnitsNearObject(M.convoy_geyser, 5000.0, 2, nil);

		if (M.stuff == 0)
		then
			AudioMessage("misn0908.wav");-- you've cleared the area of the enemy well done
--			SucceedMission(GetTime() + 15.0, "misn09w1.des");
			M.game_over5 = true;
		end
	end

	if ((IsAlive(M.relic)) and ( not M.relic_seized) and (M.win_check < GetTime()) and ( not M.game_over))
	then
		M.win_check = GetTime() + 2.0;

		if ((IsAlive(M.nsdfmuf)) and (GetDistance(M.relic, M.nsdfmuf) < 100.0))
		then
			AudioMessage("misn0909.wav");-- you've won
			SucceedMission(GetTime() + 15.0, "misn09w1.des");
			M.game_over = true;
		end
	end

	if (( not IsAlive(M.nsdfmuf)) and ( not M.game_over))
	then
		AudioMessage("misn0911.wav");-- you've lost your muf
		FailMission(GetTime() + 15.0, "misn09f3.des");
		M.game_over = true;
	end

	if (( not IsAlive(M.ccalaunch)) and ( not M.game_over))
	then
		AudioMessage("misn0918.wav");-- you've destroyed the launchpad
		FailMission(GetTime() + 15.0);
		M.game_over = true;
	end

-- END OF SCRIPT
	
end