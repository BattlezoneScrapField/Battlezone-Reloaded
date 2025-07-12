-- Single Player NSDF Mission 12 Lua conversion, created by General BlackDragon. 

-- Single Table for all our save/load variables. This SP mission has too many variables to function with them independently. ("main function has > 200 local variables", or "Load having > 197 variables in assignment")
local M = {

-- bools
	start_done = false,
	silos_gone = false,
	turret_move = false,
	first_wave = false,
	second_wave = false,
	turret1_set = false,
	turret2_set = false,
	artil_move = false,
	artil_move2 = false,
	artil_set = false,
	--wave2 = false,
	--wave2_done = false,
	--wave2_move = false,
	--wave3 = false,
	--wave3_done = false,
	--wave3_move = false,
	--wave4 = false,
	--wave4_done = false,
	--wave4_move = false,
	a = false,
	--b = false,
	--c = false,
	--d = false,
	silo1_lost = false,
	silo2_lost = false,
	silo3_lost = false,
	--silo4_lost = false,
	make_bomber = false,
	bomber_attack = false,
	new_target = false,
	bomber_retreat = false,
	sv1_wait = false,
	sv4_wait = false,
	sv3_wait = false,
	sv1_reload = false,
	sv2_reload = false,
	sv3_reload = false,
	sv4_reload = false,
	set_aip = false,
	hold_aip = false,
	bomber_reload = false,
	assign_tank1 = false,
	assign_tank2 = false,
	assign_tank3 = false,
	assign_tank4 = false,
	silos_attacked = false,
	silo_defend = false,
	muf_attacked = false,
	muf_safe = false,
	turret1_muf = false,
	turret2_muf = false,
	turret5_muf = false,
	turret6_muf = false,
	--player_center = false,
	apc_sent = false,
	artil_lost = false,
	game_over = false,
	scav_swap = false,
	artil_message = false,
-- Floats (really doubles in Lua)
	first_wave_time = 0,
	second_wave_time = 0,
	next_wave_time = 0,
	artil_move_time = 0,
	artil_set_time = 0,
	set_aip_time = 0,
	bomber_retreat_time = 0,
	turret_move_time = 0,
	new_orders_time = 0,
	safe_time_check = 0,
	scrap_check = 0,
-- Handles
	user = nil,
	nsdfrecycle = nil,
	nsdfmuf = nil,
	nav1 = nil,
	--checkpoint1 = nil,
	--checkpoint2 = nil,
	--checkpoint3 = nil,
	--checkpoint4 = nil,
	--ccacom_tower = nil,
	ccasilo1 = nil,
	ccasilo2 = nil,
	ccasilo3 = nil,
	ccasilo4 = nil,
	--spawn_point1 = nil,
	--spawn_point2 = nil,
	--check1 = nil,
	--check2 = nil,
	--check3 = nil,
	ccamuf = nil,
	ccaslf = nil,
	ccaapc = nil,
	turret1 = nil,
	turret2 = nil,
	turret3 = nil,
	turret4 = nil,
	turret5 = nil,
	turret6 = nil,
	artil1 = nil,
	artil2 = nil,
	artil3 = nil,
	artil4 = nil,
	fighter1 = nil,
	fighter2 = nil,
	fighter3 = nil,
	fighter4 = nil,
	fighter5 = nil,
	fighter6 = nil,
	sv1 = nil,
	sv2 = nil,
	sv3 = nil,
	sv4 = nil,
	--sv5 = nil,
	--sv6 = nil,
	--sv7 = nil,
	--sv8 = nil,
	--sv9 = nil,
	--sv0 = nil,
	tank1 = nil,
	tank2 = nil,
	tank3 = nil,
	tank4 = nil,
	tank5 = nil,
	tank6 = nil,
	tank7 = nil,
	tank8 = nil,
	key_geyser1 = nil,
	key_geyser2 = nil,
	split_geyser = nil,
	center_geyser = nil,
	choke_bridged = nil,
	guntower1 = nil,
	controltower = nil,
	center = nil,
	svscav1 = nil,
	svscav2 = nil,
	svscav3 = nil,
	svscav4 = nil,
	svscav5 = nil,
	svscav6 = nil,
	svscav7 = nil,
	svscav8 = nil,
	escort_tank = nil,
	nsdfrig = nil,
	avscav1 = nil,
	avscav2 = nil,
	avscav3 = nil,
-- Ints
	check = 0,
	scrap = 0,
	shot_by = 0
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

	M.scrap = 100;
	
	M.first_wave_time = 99999.0;
	M.second_wave_time = 99999.0;
	M.next_wave_time = 99999.0;
	M.artil_move_time = 99999.0;
	M.artil_set_time = 99999.0;
	M.set_aip_time = 99999.0;
	M.bomber_retreat_time = 99999.0;
	M.turret_move_time = 99999.0;
	M.new_orders_time = 99999.0;
	M.safe_time_check = 99999.0;
	M.scrap_check = 60.0;


	--M.checkpoint1 = GetHandle("svguntower1");
--	M.checkpoint2 = GetHandle("svcontroltower");
	--M.checkpoint3 = GetHandle("svmuf");
	--M.checkpoint4 = GetHandle("svsilo1");
	M.ccasilo1 = GetHandle("svsilo1");
	M.ccasilo2 = GetHandle("svsilo2");
	M.ccasilo3 = GetHandle("svsilo3");
	M.ccasilo4 = GetHandle("svsilo4");
	M.ccamuf = GetHandle("svmuf");
	M.ccaslf = GetHandle("svslf");
	--M.ccacom_tower = GetHandle("svcom_tower");
	--M.spawn_point1 = GetHandle("spawn_geyser1");
	--M.spawn_point2 = GetHandle("spawn_geyser2");
	M.nav1 = GetHandle("apcamr20_camerapod");
	M.turret1 = GetHandle("turret1");
	M.turret2 = GetHandle("turret2");
	M.turret3 = GetHandle("turret3");
	M.turret4 = GetHandle("turret4");
	M.turret5 = GetHandle("turret5");
	M.turret6 = GetHandle("turret6");
	M.artil1 = GetHandle("artil1");
	M.artil2 = GetHandle("artil2");
	M.artil3 = GetHandle("artil3");
	M.artil4 = GetHandle("artil4");
	M.fighter1 = GetHandle("fighter1");
	M.fighter2 = GetHandle("fighter2");
	M.fighter3 = GetHandle("fighter3");
	M.fighter4 = GetHandle("fighter4");
	M.fighter5 = GetHandle("fighter5");
	M.fighter6 = GetHandle("fighter6");
	M.tank1 = GetHandle("tank1");
	M.tank2 = GetHandle("tank2");
	M.tank3 = GetHandle("tank3");
	M.tank4 = GetHandle("tank4");
	M.key_geyser1 = GetHandle("key_geyser1");
	M.key_geyser2 = GetHandle("key_geyser2");
	M.center_geyser = GetHandle("center_geyser");
	M.split_geyser = GetHandle("split_geyser");
	M.nsdfrecycle = GetHandle("avrecycle");
--	M.ccaapc = GetHandle("svapc");
	M.svscav1 = GetHandle("svscav1"); 
	M.svscav2 = GetHandle("svscav2"); 
	M.svscav3 = GetHandle("svscav3"); 
	M.svscav4 = GetHandle("svscav4"); 

	M.center = GetHandle("center");

end

function AddObject(h)

	if ((M.sv1 == nil) and (IsOdf(h,"svapc13")))
	then
		M.sv1 = h;
	elseif ((M.sv2 == nil) and (IsOdf(h,"svapc13")))
	then
		M.sv2 = h;
	elseif ((M.sv3 == nil) and (IsOdf(h,"svhr13")))
	then
		M.sv3 = h;
	elseif ((M.sv4 == nil) and (IsOdf(h,"svhr13")))
	then
		M.sv4 = h;
	elseif (IsOdf(h,"abtowe"))
	then
		M.guntower1 = h;
	elseif ((M.controltower == nil) and (IsOdf(h,"abcomm")))
	then
		M.controltower = h;
	elseif ((M.tank5 == nil) and (IsOdf(h,"svtk13")))
	then
		M.tank5 = h;
	elseif ((M.tank6 == nil) and (IsOdf(h,"svtk13")))
	then
		M.tank6 = h;
	elseif ((M.tank7 == nil) and (IsOdf(h,"svtk13")))
	then
		M.tank7 = h;
	elseif ((M.tank8 == nil) and (IsOdf(h,"svtk13")))
	then
		M.tank8 = h;
	elseif ((M.nsdfmuf == nil) and (IsOdf(h,"avmuf")))
	then
		M.nsdfmuf = h;
	elseif ((M.nsdfrig == nil) and (IsOdf(h,"avcnst")))
	then
		M.nsdfrig = h;
	elseif ((M.avscav1 == nil) and (IsOdf(h,"avscav")))
	then
		M.avscav1 = h;
	elseif ((M.avscav2 == nil) and (IsOdf(h,"avscav")))
	then
		M.avscav2 = h;
	elseif ((M.avscav3 == nil) and (IsOdf(h,"avscav")))
	then
		M.avscav3 = h;
	end

end

function Update()

-- START OF SCRIPT

	M.user = GetPlayerHandle(); --assigns the player M.a handle every frame

-- these are constants
	if (M.bomber_attack)
	then
		if ( not IsAlive(M.sv1))
		then
			M.sv1_wait = false;
		end
		if ( not IsAlive(M.sv4))
		then
			M.sv4_wait = false;
		end
		if ( not IsAlive(M.sv3))
		then
			M.sv3_wait = false;
		end
		if (( not IsAlive(M.sv3)) and ( not IsAlive(M.sv4)))
		then
			M.make_bomber = false;
			M.bomber_attack = false;
			M.new_target = false;
			M.bomber_retreat = false;
			M.bomber_retreat_time = 99999.0;
			M.bomber_reload = false;
--			M.sv1_reload = false;
--			M.sv2_reload = false;
--			M.sv3_reload = false;
--			M.sv4_reload = false;

		end
	end

	if ( not IsAlive(M.tank1))
	then
		M.assign_tank1 = false;
	end
	if ( not IsAlive(M.tank2))
	then
		M.assign_tank2 = false;
	end
	if ( not IsAlive(M.tank3))
	then
		M.assign_tank3 = false;
	end
	if ( not IsAlive(M.tank4))
	then
		M.assign_tank4 = false;
	end

-- end of constants ------------------------------------------------------------------/
	
	if ( not M.start_done)
	then
		AudioMessage("misn1300.wav");
		ClearObjectives();
		AddObjective("misn1300.otf", "WHITE");
		SetPilot(1, 10);
		SetPilot(2, 40);
		SetScrap(1,40);
		SetScrap(2, 200);
		Defend(M.tank1);
		Defend(M.tank2);
		Defend(M.artil1);
		Defend(M.artil2);
		Defend(M.artil3);
		Defend(M.artil4);
--		Defend(M.ccaapc);
		M.escort_tank = BuildObject("svtank", 2, M.artil1);
		SetObjectiveName(M.nav1, "Drop Zone");
		Defend(M.escort_tank);
		M.first_wave_time = GetTime()+5.0;
		M.next_wave_time = GetTime()+300.0;

		M.artil_move_time = GetTime()+ 900.0; -- this may move

		M.start_done = true;
	end

-- this is going to subtract M.scrap from the soviets if the silos are destroyed

	if (( not IsAlive(M.ccasilo1)) and (GetScrap(2) > 150) and ( not M.silo1_lost))
	then
		SetScrap(2,150);
		M.silo1_lost = true; 
	end

	if (( not IsAlive(M.ccasilo2)) and (GetScrap(2) > 150) and ( not M.silo1_lost))
	then
		SetScrap(2,150);
		M.silo1_lost = true; 
	end

	if (( not IsAlive(M.ccasilo3)) and (GetScrap(2) > 150) and ( not M.silo1_lost))
	then
		SetScrap(2,150);
		M.silo1_lost = true; 
	end

	if (( not IsAlive(M.ccasilo4)) and (GetScrap(2) > 150) and ( not M.silo1_lost))
	then
		SetScrap(2,150);
		M.silo1_lost = true; 
	end

	if (( not IsAlive(M.ccasilo1)) and ( not IsAlive(M.ccasilo2)) and (GetScrap(2) > 100) and ( not M.silo2_lost))
	then
		SetScrap(2,100);
		M.silo2_lost = true; 
	end

	if (( not IsAlive(M.ccasilo1)) and ( not IsAlive(M.ccasilo3)) and (GetScrap(2) > 100) and ( not M.silo2_lost))
	then
		SetScrap(2,100);
		M.silo2_lost = true; 
	end

	if (( not IsAlive(M.ccasilo1)) and ( not IsAlive(M.ccasilo4)) and (GetScrap(2) > 100) and ( not M.silo2_lost))
	then
		SetScrap(2,100);
		M.silo2_lost = true; 
	end

	if (( not IsAlive(M.ccasilo2)) and ( not IsAlive(M.ccasilo3)) and (GetScrap(2) > 100) and ( not M.silo2_lost))
	then
		SetScrap(2,100);
		M.silo2_lost = true; 
	end

	if (( not IsAlive(M.ccasilo2)) and ( not IsAlive(M.ccasilo4)) and (GetScrap(2) > 100) and ( not M.silo2_lost))
	then
		SetScrap(2,100);
		M.silo2_lost = true; 
	end

	if (( not IsAlive(M.ccasilo3)) and ( not IsAlive(M.ccasilo4)) and (GetScrap(2) > 100) and ( not M.silo2_lost))
	then
		SetScrap(2,100);
		M.silo2_lost = true; 
	end

	if (( not IsAlive(M.ccasilo1)) and ( not IsAlive(M.ccasilo2)) and ( not IsAlive(M.ccasilo3))
		 and  (GetScrap(2) > 50) and ( not M.silo3_lost))
	then
		SetScrap(2,50);
		M.silo3_lost = true; 
	end

	if (( not IsAlive(M.ccasilo1)) and ( not IsAlive(M.ccasilo2)) and ( not IsAlive(M.ccasilo4))
		 and  (GetScrap(2) > 50) and ( not M.silo3_lost))
	then
		SetScrap(2,50);
		M.silo3_lost = true; 
	end

	if (( not IsAlive(M.ccasilo1)) and ( not IsAlive(M.ccasilo3)) and ( not IsAlive(M.ccasilo4))
		 and  (GetScrap(2) > 50) and ( not M.silo3_lost))
	then
		SetScrap(2,50);
		M.silo3_lost = true; 
	end

	if (( not IsAlive(M.ccasilo2)) and ( not IsAlive(M.ccasilo3)) and ( not IsAlive(M.ccasilo4))
		 and  (GetScrap(2) > 50) and ( not M.silo3_lost))
	then
		SetScrap(2,50);
		M.silo3_lost = true; 
	end

	if (( not IsAlive(M.ccasilo1)) and ( not IsAlive(M.ccasilo2)) and ( not IsAlive(M.ccasilo3))
		 and ( not IsAlive(M.ccasilo4)) and (GetScrap(2) > 0) and ( not M.silos_gone))
	then
		M.silos_gone = true;
		SetScrap(2,0);
	end

-- now I'm going to start the battle by sending the turrets to smart locations
	-- this immediately sends turrets to key locations
	
	if ((M.start_done) and ( not M.turret_move))
	then
		Retreat(M.turret1, "turret_path1");	-- M.a M.scrap field vital to americans
		Retreat(M.turret2, "turret_path1");	-- M.a M.scrap field vital to americans
		Defend(M.turret3);					-- the main choke point where americans must come through
		Defend(M.turret4);					-- the main choke point where americans must come through
		Retreat(M.turret5, "turret_path2");	-- the M.scrap silos
		Retreat(M.turret6, "turret_path2");	-- the M.scrap silos
		Goto(M.ccaslf, "slf_path");
		M.turret_move_time = GetTime() + 120.0;
		M.turret_move = true;
	end

	if ((M.turret_move) and (M.turret_move_time < GetTime()) and ( not M.silo_defend))
	then
		M.turret_move_time = GetTime() + 3.0;

		if ((GetDistance(M.turret5, M.ccasilo1) < 60.0) and (GetDistance(M.turret6, M.ccasilo1) < 60.0))
		then
			Defend(M.turret5);
			Defend(M.turret6);
			M.silo_defend = true;
		end
	end

	if ((M.turret_move) and (M.turret_move_time < GetTime()) and ( not M.turret1_set))
	then
		if (GetDistance(M.turret1, M.key_geyser1) < 100.0)
		then
			Goto(M.turret1, M.key_geyser1);
			M.turret1_set = true;
		end
	end

	if ((M.turret_move) and (M.turret_move_time < GetTime()) and ( not M.turret2_set))
	then
		if (GetDistance(M.turret2, M.key_geyser1) < 100.0)
		then
			Goto(M.turret2, M.key_geyser2);
			M.turret2_set = true;
		end
	end

-- sending the tanks that would have been following the player in for the first attack
	if ((M.start_done) and (M.first_wave_time < GetTime()) and ( not M.first_wave))
	then
		Attack(M.tank3, M.nsdfrecycle, 1);
		Attack(M.tank4, M.nsdfrecycle, 1);
		Attack(M.fighter5, M.nsdfrecycle, 1);
		Attack(M.fighter6, M.nsdfrecycle, 1);
		M.second_wave_time = GetTime()+ 5.0;
		M.first_wave = true;
	end

	if ((M.first_wave) and (M.second_wave_time < GetTime()) and ( not M.second_wave))
	then
		Goto(M.fighter1, "choke_point1");
		Goto(M.fighter2, "choke_point1");
		Goto(M.fighter3, M.key_geyser1);
		Goto(M.fighter4, M.key_geyser2);

		M.set_aip_time = GetTime() + 60.0;
		M.second_wave = true;
	end

	if (( not M.set_aip) and (M.set_aip_time < GetTime()) and ( not M.hold_aip) and ( not M.muf_attacked))
	then
		M.set_aip_time = GetTime() + 240.0;
 		SetAIP("misn13.aip");
--		M.set_aip = true;
	end

--	if (M.set_aip)
--	then
--		M.set_aip = false;
--	end

-- tank code

	if ((IsAlive(M.tank1)) and ( not M.assign_tank1))
	then
		Follow(M.tank1, M.ccamuf);
		M.assign_tank1 = true;
	end

	if ((IsAlive(M.tank2)) and ( not M.assign_tank2))
	then
		Follow(M.tank2, M.ccamuf);
		M.assign_tank2 = true;
	end

	if ((IsAlive(M.tank3)) and ( not M.assign_tank3))
	then
		Follow(M.tank3, M.center);
		M.assign_tank3 = true;
	end

	if ((IsAlive(M.tank4)) and ( not M.assign_tank4))
	then
		Follow(M.tank4, M.center);
		M.assign_tank4 = true;
	end

-- this sends the first apc after the player's comtower

--	if ((IsAlive(M.controltower)) and ( not M.apc_sent))
--	then
--		Attack(M.ccaapc, M.controltower, 1);
--		M.apc_sent = true;
--	end
	
-- this is bomber code ----------------------------------------------------------------------------


	if (((IsAlive(M.guntower1))  or  (IsAlive(M.controltower))) and ( not M.make_bomber) and ( not M.muf_attacked))
	then
		SetAIP("misn13a.aip");
		M.hold_aip = true;
		M.make_bomber = true;
	end

	if ((M.make_bomber) and ( not M.bomber_attack))
	then
		if ((IsAlive(M.sv4)) and ( not M.sv4_wait))
		then
			if (IsAlive(M.guntower1))
			then
				Attack(M.sv4, M.guntower1);
			else
				if (IsAlive(M.nsdfmuf))
				then
					Attack(M.sv4, M.nsdfmuf);
				else
					if (IsAlive(M.controltower))
					then
						Attack(M.sv4, M.controltower);
					end
				end

				if (IsAlive(M.tank5))
				then
					Follow(M.tank5, M.sv4);
				end	
			end

			M.sv4_wait = true;
		end
			

		if ((IsAlive(M.sv1))  and ( not M.sv1_wait))
		then
			if (IsAlive(M.controltower))
			then
				Attack(M.sv1, M.controltower);
			else
				if (IsAlive(M.guntower1))
				then
					Attack(M.sv1, M.guntower1);
				else
					if (IsAlive(M.nsdfmuf))
					then
						Attack(M.sv1, M.nsdfmuf);
					end
				end		
			end

			if (IsAlive(M.tank6))
			then
				Follow(M.tank6, M.sv1);
			end

			M.sv1_wait = true;
		end

		if ((IsAlive(M.sv3)) and ( not M.sv3_wait))
		then
			if (IsAlive(M.guntower1))
			then
				Attack(M.sv3, M.guntower1);
			else
				if (IsAlive(M.nsdfmuf))
				then
					Attack(M.sv3, M.nsdfmuf);
				else
					if (IsAlive(M.controltower))
					then
						Attack(M.sv3, M.controltower);
					end
				end

				if (IsAlive(M.tank7))
				then
					Follow(M.tank7, M.sv3);
				end
			end

			M.sv3_wait = true;
		end
	end

	if ((M.sv1_wait) and (M.sv3_wait) and (M.sv4_wait) and ( not M.bomber_attack))
	then
		M.hold_aip = false;
--		M.bomber_reload = false;
		M.bomber_attack = true;
	end
	

	if ((M.bomber_attack) and ( not IsAlive(M.guntower1)) and ( not M.new_target))
	then
		if (IsAlive(M.controltower))
		then
			if(IsAlive(M.sv1))
			then
				Attack(M.sv1, M.controltower);
			end
			if(IsAlive(M.sv3))
			then
				Attack(M.sv3, M.controltower);
			end
			if(IsAlive(M.sv4))
			then
				Attack(M.sv4, M.controltower);
			end
			
			M.new_target = true;
		else
			if (IsAlive(M.nsdfmuf))
			then
				if(IsAlive(M.sv1))
				then
					Attack(M.sv1, M.nsdfmuf);
				end
				if(IsAlive(M.sv3))
				then
					Attack(M.sv3, M.nsdfmuf);
				end
				if(IsAlive(M.sv4))
				then
					Attack(M.sv4, M.nsdfmuf);
				end
				
				M.new_target = true;
			end
		end
--[[			else
			then
				if (IsAlive(M.sv1))
				then
					Retreat(M.sv1, M.ccamuf);
				end
				if (IsAlive(M.sv3))
				then
					Retreat(M.sv3, M.ccamuf);
				end
				if (IsAlive(M.sv4))
				then
					Retreat(M.sv4, M.ccamuf);
				end
			end
--]]
--		M.bomber_retreat_time = GetTime() + 15.0;
--		M.bomber_retreat = true;
	end


--[[
	if ((M.new_target) and (( not IsAlive(M.controltower))  or  ( not IsAlive(M.nsdfmuf))) and ( not M.bomber_retreat))
	then
		if(IsAlive(M.sv1))
		then
			Retreat(M.sv1, M.ccamuf);
		end
--		if(IsAlive(M.sv2))
--		then
--			Retreat(M.sv2, M.ccamuf);
--		end
		if(IsAlive(M.sv3))
		then
			Retreat(M.sv3, M.ccamuf);
		end
		if(IsAlive(M.sv4))
		then
			Retreat(M.sv4, M.ccamuf);
		end
		
		M.bomber_retreat_time = GetTime() + 15.0;
		M.bomber_retreat = true;
	end

--]]
--[[
	if ((M.bomber_retreat) and (M.bomber_retreat_time < GetTime()) and ( not M.bomber_reload))
	then
		M.bomber_retreat_time = GetTime() + 15.0;

		if (GetDistance(M.user, M.ccamuf) > 500.0)
		then
			if ((IsAlive(M.sv1)) and (GetDistance(M.sv1, M.ccamuf) < 100.0) and ( not M.sv1_reload))
			then
				RemoveObject(M.sv1);
				M.sv1 = BuildObject("avhraz", 2, M.ccamuf);
				AddScrap(2, -2);
				M.sv1_reload = true;
			end
--			if ((IsAlive(M.sv2)) and (GetDistance(M.sv2, M.ccamuf) < 50.0) and ( not M.sv2_reload))
--			then
--				RemoveObject(M.sv2);
--				M.sv2 = BuildObject("avhraz", 2, M.ccamuf);
--				AddScrap(2, -2);
--				M.sv2_reload = true;
--			end
			if ((IsAlive(M.sv3)) and (GetDistance(M.sv3, M.ccamuf) < 100.0) and ( not M.sv3_reload))
			then
				RemoveObject(M.sv3);
				M.sv3 = BuildObject("avhraz", 2, M.ccamuf);
				AddScrap(2, -2);
				M.sv3_reload = true;
			end
			if ((IsAlive(M.sv4)) and (GetDistance(M.sv4, M.ccamuf) < 100.0) and ( not M.sv4_reload))
			then
				RemoveObject(M.sv4);
				M.sv4 = BuildObject("avhraz", 2, M.ccamuf);
				AddScrap(2, -2);
				M.sv4_reload = true;
			end
		end
--]]

--		if (((M.sv1_reload) and --[[(M.sv2_reload) and --]](M.sv3_reload) and (M.sv4_reload))  or 
--			(( not IsAlive(M.sv1)) and --[[(M.sv2_reload) and --]](M.sv3_reload) and (M.sv4_reload))  or 
--			(--[[( not IsAlive(M.sv2)) and --]](M.sv1_reload) and (M.sv3_reload) and (M.sv4_reload))  or 
--			(( not IsAlive(M.sv3)) and (M.sv1_reload) and --[[(M.sv2_reload) and --]](M.sv4_reload))  or 
--			(( not IsAlive(M.sv4)) and (M.sv1_reload) and --[[(M.sv2_reload) and --]](M.sv3_reload))  or 
--			(( not IsAlive(M.sv1)) and --[[( not IsAlive(M.sv2)) and --]](M.sv3_reload) and (M.sv4_reload))  or 
--			(( not IsAlive(M.sv1)) and ( not IsAlive(M.sv3)) and --[[(M.sv2_reload) and --]](M.sv4_reload))  or 
--			(( not IsAlive(M.sv1)) and ( not IsAlive(M.sv4)) and --[[(M.sv2_reload) and --]](M.sv3_reload))  or 
--			(--[[( not IsAlive(M.sv2)) and --]]( not IsAlive(M.sv3)) and (M.sv1_reload) and (M.sv4_reload))  or 
--			(--[[( not IsAlive(M.sv2)) and --]]( not IsAlive(M.sv4)) and (M.sv1_reload) and (M.sv3_reload))  or 
--			(( not IsAlive(M.sv3)) and ( not IsAlive(M.sv4)) and (M.sv1_reload)--[[ and (M.sv2_reload) --]])  or 
--			(( not IsAlive(M.sv1)) and --[[( not IsAlive(M.sv2)) and --]]( not IsAlive(M.sv3)) and (M.sv4_reload))  or 
--			(( not IsAlive(M.sv1)) and --[[( not IsAlive(M.sv2)) and --]]( not IsAlive(M.sv4)) and (M.sv3_reload))  or 
--			(( not IsAlive(M.sv1)) and ( not IsAlive(M.sv3)) and ( not IsAlive(M.sv4))--[[ and (M.sv2_reload) --]])  or 
--			(--[[( not IsAlive(M.sv2)) and --]]( not IsAlive(M.sv3)) and ( not IsAlive(M.sv4)) and (M.sv1_reload)))
--		then
--[[(			if ( not IsAlive(M.sv1))
			then
				Defend(M.sv1);
			end
			if ( not IsAlive(M.sv2))
			then
				Defend(M.sv2);
			end
			if ( not IsAlive(M.sv3))
			then
				Defend(M.sv3);
			end
			if ( not IsAlive(M.sv4))
			then
				Defend(M.sv4);
			end
--]]
--			M.make_bomber = false;
--			M.bomber_attack = false;
--			M.sv1_wait = false;
--			M.sv3_wait = false;
--			M.sv4_wait = false;
--			M.new_target = false;
--			M.bomber_retreat = false;
--			M.bomber_retreat_time = 99999.0;
--			M.sv1_reload = false;
--			M.sv2_reload = false;
--			M.sv3_reload = false;
--			M.sv4_reload = false;
--			M.bomber_reload = true;
--		end
--	end



-- end bomber code ----------------------------------------------------------------------------
-- this is what happens if the silos get attacked

	if ((IsAlive(M.ccasilo1)) and ( not M.silos_attacked) and (GetHealth(M.ccasilo1) < 0.95))
	then
		M.new_orders_time = GetTime() + 2.0;
		M.silos_attacked = true;
	end
	if ((IsAlive(M.ccasilo2)) and ( not M.silos_attacked) and (GetHealth(M.ccasilo2) < 0.95))
	then
		M.new_orders_time = GetTime() + 2.0;
		M.silos_attacked = true;
	end
	if ((IsAlive(M.ccasilo3)) and ( not M.silos_attacked) and (GetHealth(M.ccasilo3) < 0.95))
	then
		M.new_orders_time = GetTime() + 2.0;
		M.silos_attacked = true;
	end
	if ((IsAlive(M.ccasilo4)) and ( not M.silos_attacked) and (GetHealth(M.ccasilo4) < 0.95))
	then
		M.new_orders_time = GetTime() + 2.0;
		M.silos_attacked = true;
	end

	if ((M.silos_attacked) and (M.new_orders_time < GetTime()))
	then
		M.new_orders_time = GetTime() + 120.0;

		if (IsAlive(M.tank1))
		then
			Goto(M.tank1, "silo_spot");
		end
		if (IsAlive(M.tank2))
		then
			Goto(M.tank2, "silo_spot");
		end
		if (IsAlive(M.tank3))
		then
			Goto(M.tank3, "silo_spot");
		end
		if (IsAlive(M.tank4))
		then
			Goto(M.tank4, "silo_spot");
		end
		if (IsAlive(M.turret1))
		then
			Goto(M.turret1, "silo_spot");
		end
		if (IsAlive(M.turret2))
		then
			Goto(M.turret2, "silo_spot");
		end
		if (IsAlive(M.turret5))
		then
			Goto(M.turret5, "silo_spot");
		end
		if (IsAlive(M.turret6))
		then
			Goto(M.turret6, "silo_spot");
		end
		if (IsAlive(M.tank4))
		then
			Goto(M.tank4, "silo_spot");
		end
		if ((M.bomber_reload)  or  (M.bomber_attack))
		then
			if (IsAlive(M.sv1))
			then
				Goto(M.sv1, "silo_spot");
			end
--			if (IsAlive(M.sv2))
--			then
--				Goto(M.sv2, "silo_spot");
--			end
			if (IsAlive(M.sv3))
			then
				Goto(M.sv3, "silo_spot");
			end
			if (IsAlive(M.sv4))
			then
				Goto(M.sv4, "silo_spot");
			end
		end
	end

-- this is what happens if the muf is under attack

	if ((IsAlive(M.ccamuf)) and ( not M.muf_attacked) 
		 and  (GetHealth(M.ccamuf) < 0.90) and ( not M.muf_safe))
	then
		if (IsAlive(M.turret1))
		then
			Goto(M.turret1, M.ccamuf);
		end
		if (IsAlive(M.turret2))
		then
			Goto(M.turret2, M.ccamuf);
		end
		if (IsAlive(M.turret5))
		then
			Goto(M.turret5, M.ccamuf);
		end
		if (IsAlive(M.turret6))
		then
			Goto(M.turret6, M.ccamuf);
		end
		
		AddScrap(2, 40);
		M.safe_time_check = GetTime() + 120.0;
		SetAIP("misn13c.aip");
		M.muf_attacked = true;
	end

	if ((M.muf_attacked) and (IsAlive(M.turret1)) and ( not M.turret1_muf) and GetDistance(M.turret1, M.ccamuf) < 60.0)
	then
		Defend(M.turret1);
		M.turret1_muf = true;
	end
	if ((M.muf_attacked) and (IsAlive(M.turret2)) and ( not M.turret2_muf) and GetDistance(M.turret2, M.ccamuf) < 60.0)
	then
		Defend(M.turret2);
		M.turret2_muf = true;
	end
	if ((M.muf_attacked) and (IsAlive(M.turret5)) and ( not M.turret5_muf) and GetDistance(M.turret5, M.ccamuf) < 60.0)
	then
		Defend(M.turret5);
		M.turret5_muf = true;
	end
	if ((M.muf_attacked) and (IsAlive(M.turret6)) and ( not M.turret6_muf) and GetDistance(M.turret6, M.ccamuf) < 60.0)
	then
		Defend(M.turret6);
		M.turret6_muf = true;
	end

	-- this checks to see of the coast is clear after the muf is attacked
	if (( not M.game_over) and (M.muf_attacked) and (M.safe_time_check < GetTime()) and ( not M.muf_safe))
	then
		M.safe_time_check = GetTime() + 60.0;
		M.check = CountUnitsNearObject(M.ccamuf, 400.0, 1, nil);		
		if (M.check < 2.0)
		then
			M.muf_safe = true;
			M.muf_attacked = false;
		end

	end

-- this checks to see if the player has broken through the main chokepoint

	if (( not M.choke_bridged) and ( not IsAlive(M.turret3)) and ( not IsAlive(M.turret4)))
	then
		M.choke_bridged = true;
	end

-- this is the section that moves the first wave of soviet artillery units
	if ((M.artil_move_time < GetTime()) and ( not M.artil_move))
	then
		M.artil_move_time = GetTime() + 10.0;

		if (IsAlive(M.artil1))
		then
			Retreat(M.artil1, "artil_path1");
		end
		if (IsAlive(M.artil2))
		then	
			Retreat(M.artil2, "artil_path1");
		end
		if (IsAlive(M.artil3))
		then
			Retreat(M.artil3, "artil_path1");
		end
		if (IsAlive(M.artil4))
		then
			Retreat(M.artil4, "artil_path1");
		end
		if (IsAlive(M.escort_tank))
		then
			Retreat(M.escort_tank, "artil_path1");
		end

		M.artil_move = true;
	end

	if ((M.artil_move) and (M.artil_move_time < GetTime()) and ( not M.artil_move2))
	then
		M.artil_move_time = GetTime() + 5.0;
		if (GetDistance(M.artil4, M.split_geyser) < 20.0)
		then
			if (IsAlive(M.artil1))
			then
				Goto(M.artil1, "artil_point1");
				SetIndependence(M.artil1, 1);
			end
			if (IsAlive(M.artil2))
			then
				Goto(M.artil2, "artil_point2");
				SetIndependence(M.artil2, 1);
			end
			if (IsAlive(M.artil3))
			then
				Goto(M.artil3, "artil_point3");
				SetIndependence(M.artil3, 1);
			end
			if (IsAlive(M.artil4))
			then
				Goto(M.artil4, "artil_point4");
				SetIndependence(M.artil4, 1);
			end
			if (IsAlive(M.escort_tank))
			then
				Follow(M.escort_tank, M.artil1);
			end
			
			M.artil_set_time = GetTime() + 120.0;
			M.artil_move2 = true;
		end
	end

	if ((M.artil_set_time < GetTime()) and ( not M.artil_set))
	then
		if (IsAlive(M.artil1))
		then
			if (IsAlive(M.avscav1))
			then
				Attack(M.artil1, M.avscav1);
			elseif (IsAlive(M.avscav2))
			then
				Attack(M.artil1, M.avscav2);
			elseif (IsAlive(M.avscav3))
			then
				Attack(M.artil1, M.avscav3);
			end
		end
		if (IsAlive(M.artil2))
		then	
			if (IsAlive(M.avscav3))
			then
				Attack(M.artil2, M.avscav3);
			elseif (IsAlive(M.avscav2))
			then
				Attack(M.artil2, M.avscav2);
			elseif (IsAlive(M.avscav1))
			then
				Attack(M.artil2, M.avscav1);
			end
		end

		M.artil_set = true;
	end

	if (( not IsAlive(M.artil1)) and ( not IsAlive(M.artil2)) and ( not IsAlive(M.artil3)) and ( not IsAlive(M.artil4)))
	then
		M.artil_lost = true;
	end

	if ((M.artil_move2) and ( not M.artil_message))
	then
		if (IsAlive(M.nsdfrecycle))
		then
			M.shot_by = GetWhoShotMe(M.nsdfrecycle);

			if (M.shot_by ~= 0)
			then
				if ((M.artil1 == M.shot_by)  or 
					(M.artil2 == M.shot_by)  or 
					(M.artil3 == M.shot_by)  or 
					(M.artil4 == M.shot_by))
				then
					AudioMessage("misn1302.wav"); 
					M.artil_message = true;
				end
			end
		end

		if ((IsAlive(M.nsdfmuf)) and ( not M.artil_message))
		then
			M.shot_by = GetWhoShotMe(M.nsdfmuf);

			if (M.shot_by ~= 0)
			then
				if ((M.artil1 == M.shot_by)  or 
					(M.artil2 == M.shot_by)  or 
					(M.artil3 == M.shot_by)  or 
					(M.artil4 == M.shot_by))
				then
					AudioMessage("misn1302.wav"); 
					M.artil_message = true;
				end
			end
		end

		if ((IsAlive(M.avscav1)) and ( not M.artil_message))
		then
			M.shot_by = GetWhoShotMe(M.avscav1);

			if (M.shot_by ~= 0)
			then
				if ((M.artil1 == M.shot_by)  or 
					(M.artil2 == M.shot_by)  or 
					(M.artil3 == M.shot_by)  or 
					(M.artil4 == M.shot_by))
				then
					AudioMessage("misn1302.wav"); 
					M.artil_message = true;
				end
			end
		end

		if ((IsAlive(M.avscav2)) and ( not M.artil_message))
		then
			M.shot_by = GetWhoShotMe(M.avscav2);

			if (M.shot_by ~= 0)
			then
				if ((M.artil1 == M.shot_by)  or 
					(M.artil2 == M.shot_by)  or 
					(M.artil3 == M.shot_by)  or 
					(M.artil4 == M.shot_by))
				then
					AudioMessage("misn1302.wav"); 
					M.artil_message = true;
				end
			end
		end

		if ((IsAlive(M.avscav3)) and ( not M.artil_message))
		then
			M.shot_by = GetWhoShotMe(M.avscav3);

			if (M.shot_by ~= 0)
			then
				if ((M.artil1 == M.shot_by)  or 
					(M.artil2 == M.shot_by)  or 
					(M.artil3 == M.shot_by)  or 
					(M.artil4 == M.shot_by))
				then
					AudioMessage("misn1302.wav"); 
					M.artil_message = true;
				end
			end
		end
	end

-- this wakes up the scavengers

	if ((M.scrap_check < GetTime()) and ( not M.scav_swap))
	then
		M.scrap_check = GetTime() + 60.0;
		M.scrap = GetScrap(2);

		if (M.scrap < 40)
		then
			if (M.svscav1 ~= nil)
			then
				M.svscav5 = BuildObject("svscav", 2, M.svscav1);
				RemoveObject(M.svscav1);
				Goto(M.svscav5, M.center_geyser);
			end
			if (M.svscav2 ~= nil)
			then
				M.svscav6 = BuildObject("svscav", 2, M.svscav2);
				RemoveObject(M.svscav2);
				Goto(M.svscav6, M.center_geyser);
			end
			if (M.svscav3 ~= nil)
			then
				M.svscav7 = BuildObject("svscav", 2, M.svscav3);
				RemoveObject(M.svscav3);
				Goto(M.svscav7, M.center_geyser);
			end
			if (M.svscav4 ~= nil)
			then
				M.svscav8 = BuildObject("svscav", 2, M.svscav4);
				RemoveObject(M.svscav4);
				Goto(M.svscav8, M.center_geyser);
			end
			M.scav_swap = true;
		end
	end

-- win/loose conditions

	if (( not IsAlive(M.nsdfrecycle)) and ( not M.game_over))
	then
		AudioMessage("misn1304.wav");
		FailMission(GetTime() + 15.0, "misn13f1.des");
		M.game_over = true;
	end

	if (( not IsAlive(M.ccamuf)) and ( not M.game_over))
	then
		AudioMessage("misn1303.wav");
		SucceedMission(GetTime() + 15.0, "misn13w1.des");
		M.game_over = true;
	end

-- END OF SCRIPT
	
end