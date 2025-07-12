-- Single Player NSDF Mission 9 Lua conversion, created by General BlackDragon. 

-- Single Table for all our save/load variables. This SP mission has too many variables to function with them independently. ("main function has > 200 local variables", or "Load having > 197 variables in assignment")
local M = {

-- bools
	start_done = false,
	--sav_moved = false,
	--base_dead = false,
	build_tug = false,
	making_another_tug = false,
	--made_another_tug = false,
	position1 = false,
	position2 = false,
	position3 = false,
	position4 = false,
	position5 = false,
	position6 = false,
	position7 = false,
	sav_seized = false,
	sav_free = false,
	sav_secure = false,
	tug_underway1 = false,
	tug_underway2 = false,
	tug_underway3 = false,
	tug_underway4 = false,
	tug_underway5 = false,
	tug_underway6 = false,
	tug_underway7 = false,
	tug_wait_center = false,
	tug_wait2 = false,
	tug_wait3 = false,
	tug_wait4 = false,
	tug_wait5 = false,
	tug_wait6 = false,
	tug_wait7 = false,
	tug_wait_base = false,
	return_to_base = false,
	tug_after_sav = false,
	objective_on = false,
	tug_at_wait_center = false,
	relic_free = false,
	--new_aipa = false,
	--new_aipb = false,
	--fighters_underway = false,
	--sav_protected = false,
	turret1_underway = false,
	turret2_underway = false,
	turret3_underway = false,
	turret1_stop = false,
	turret2_stop = false,
	artil1_stop = false,
	artil2_stop = false,
	artil3_stop = false,
	artil1_underway = false,
	artil2_underway = false,
	artil3_underway = false,
	got_position = false,
	fighter1_underway = false,
	fighter2_underway = false,
	tank1_follow = false,
	tank2_follow = false,
	tank1_stop = false,
	tank2_stop = false,
	plan_a = false,
	plan_b = false,
	new_sav_built = false, --temp
	game_over = false,
	chase_tug = false,
	sav_warning = false,
	--player_dead = false,
	quake = false,
-- Floats (really doubles in Lua)
	--gech_warning_message = 0,
	relic_check = 0,
	build_sav_time = 0, --temp
	quake_time = 0,
	build_another_tug_time = 0,
	--fighter_time = 0,
	artil1_check = 0,
	artil2_check = 0,
	artil3_check = 0,
	turret1_check = 0,
	turret2_check = 0,
	next_second = 0,
	geys1check = 0,
-- Handles
	user = nil,
	ccatug = nil,
	tugger = nil,
	sav = nil,
	nav1 = nil,
	nav2 = nil,
	nav3 = nil,
	ccaartil1 = nil,
	ccaartil2 = nil,
	ccaartil3 = nil,
	ccaturret1 = nil,
	ccaturret2 = nil,
	ccaturret3 = nil,
	ccarecycle = nil,
	ccamuf = nil,
	nsdfrecycle = nil,
	ccafighter1 = nil,
	ccafighter2 = nil,
	ccatank1 = nil,
	ccatank2 = nil,
	post1_geyser = nil,
	post3_geyser = nil,
	geys1 = nil,
	geys2 = nil,
	geys3 = nil,
	geys4 = nil,
	geys5 = nil,
	geys6 = nil,
	geys7 = nil,
	svartil1 = nil,
	svartil2 = nil
-- Ints
	--audmsg = 0
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

	M.relic_free = true;
	
	--M.gech_warning_message = 99999.0;

	M.build_sav_time = 99999.0;--temp

	M.build_another_tug_time = 99999.0;
	M.relic_check = 99999.0;
	--M.fighter_time = 99999.0;
	M.turret1_check = 99999.0;
	M.turret2_check = 99999.0;
	M.artil1_check = 99999.0;
	M.artil2_check = 99999.0;
	M.artil3_check = 99999.0;
	M.geys1check = 180.0;
	M.quake_time = 4.0;

	M.sav = GetHandle("relic");
	M.nav1 = GetHandle("cam1");
	M.nav2 = GetHandle("cam2");
	M.nav3 = GetHandle("cam3");
	M.ccarecycle = GetHandle("svrecycler");
	M.nsdfrecycle = GetHandle("avrecycler");
	M.post1_geyser = GetHandle("post1_geyser");
	M.post3_geyser = GetHandle("post3_geyser");
	M.geys1 = GetHandle("geyser1");
	M.geys2 = GetHandle("geyser2");
	M.geys3 = GetHandle("geyser3");
	M.geys4 = GetHandle("geyser4");
	M.geys5 = GetHandle("geyser5");
	M.geys6 = GetHandle("geyser6");
	M.geys7 = GetHandle("geyser7");
	M.svartil1 = GetHandle("svartil1");
	M.svartil2 = GetHandle("svartil2");
	
	M.ccamuf = GetHandle("svmuf");

end

function AddObject(h)

	if ((M.ccatug == nil) and (IsOdf(h,"svhaul")))
	then
			M.ccatug = h;
	else
		if ((M.ccaartil1 == nil) and (IsOdf(h,"svartl")))
		then
			M.ccaartil1 = h;
		else
			if ((M.ccaartil2 == nil) and (IsOdf(h,"svartl")))
			then
				M.ccaartil2 = h;
			else
				if ((M.ccaartil3 == nil) and (IsOdf(h,"svartl")))
				then
					M.ccaartil3 = h;
				else
					if ((M.ccaturret1 == nil) and (IsOdf(h,"svturr")))
					then
						M.ccaturret1 = h;
					else
						if ((M.ccaturret2 == nil) and (IsOdf(h,"svturr")))
						then
							M.ccaturret2 = h;
						else
							if ((M.ccaturret3 == nil) and (IsOdf(h,"svturr")))
							then
								M.ccaturret3 = h;
							else
								if ((M.ccafighter1 == nil) and (IsOdf(h,"svfigh")))
								then
									M.ccafighter1 = h;
								else
									if ((M.ccafighter2 == nil) and (IsOdf(h,"svfigh")))
									then
										M.ccafighter2 = h;
									else
										if ((M.ccatank1 == nil) and (IsOdf(h,"svltnk")))
										then
											M.ccatank1 = h;
										else
											if ((M.ccatank2 == nil) and (IsOdf(h,"svltnk")))
											then
												M.ccatank2 = h;
											else
												if ((M.ccamuf == nil) and (IsOdf(h,"svmuf")))
												then
													M.ccamuf = h;
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

	if ((M.sav_free) and (IsAlive(M.sav)))
	then
		M.tugger = GetTug(M.sav);

		if (IsAlive(M.tugger))
		then
			if (GetTeamNum(M.tugger) == 1)
			then
				M.sav_free = false;
				M.sav_secure = true;
			else
				M.sav_free = false;
				M.sav_seized = true;
				M.tugger = M.ccatug;
			end
		end
	end

	if ((M.sav_secure) and ( not IsAlive(M.tugger)))
	then
		if ( not M.sav_seized)
		then
			M.sav_free = true;
			M.chase_tug = false;
			M.got_position = false;
			M.sav_secure = false;
			M.fighter1_underway = false;
			M.fighter2_underway = false;
		end
	end


	
--[[	if (IsAlive(M.sav))
	then
		if (IsAlive(M.ccatug))
		then
			if (HasCargo(M.ccatug))
			then
				M.sav_free = false;
				M.sav_seized = true;
			else
				if ( not M.sav_secure)
				then
					M.sav_free = true;
					M.sav_seized = false;
				end
			end
		end

		if ( not M.sav_seized)
		then
			M.tugger = GetTug(M.sav);

			if (M.tugger  not  = 0)
			then
				if (GetTeamNum(M.tugger) == 1)
				then
					M.sav_free = false;
					M.sav_secure = true;
				else
					M.sav_free = false;
					M.sav_seized = true;
					M.tugger = M.ccatug;
				end
			end
		end

		if ((M.sav_secure) and ( not IsAlive(M.tugger)))
		then
			if ( not M.sav_seized)
			then
				M.sav_free = true;
				M.chase_tug = false;
				M.got_position = false;
				M.sav_secure = false;
				M.fighter1_underway = false;
				M.fighter2_underway = false;
			end
		end
	end
--]]
	if ((M.sav_seized) and ( not IsAlive(M.ccatug)))
	then
		if ((IsAlive(M.ccatank1)) and (IsAlive(M.sav)))
		then
			Goto(M.ccatank1, M.sav);
		end
		if ((IsAlive(M.ccatank2)) and (IsAlive(M.sav)))
		then
			Goto(M.ccatank2, M.sav);
		end
		M.sav_seized = false;
		M.got_position = false;
		M.sav_free = true;
	end
	
	if ( not IsAlive(M.ccatug))
	then
		--------------------------
		M.tug_underway1 = false;	
		M.tug_underway2 = false;	
		M.tug_underway3 = false;	
		M.tug_underway4 = false;	
		M.tug_underway5 = false;	 
		M.tug_underway6 = false;	
		M.tug_underway7 = false;	
		M.tug_after_sav = false;	--all tug settings reset because the last tug was destroyed
		M.return_to_base = false;	
		M.tug_wait_center = false;
		M.tug_wait2 = false;		
		M.tug_wait3 = false;		
		M.tug_wait4 = false;		
		M.tug_wait5 = false;		
		M.tug_wait6 = false;		
		M.tug_wait7 = false;		
		M.tug_wait_base = false;	
		M.tug_at_wait_center = false;
		M.got_position = false;
		M.sav_warning = false;
		--------------------------
	end
	
	if ((M.sav_seized) and ( not M.sav_warning))
	then
		AudioMessage("misn1005.wav"); -- the M.sav is being taken sir
		M.sav_warning = true;
	end
	
	M.user = GetPlayerHandle(); --assigns the player a handle every frame

-- constant variables

	if ( not IsAlive(M.ccaturret1))
	then
		M.turret1_underway = false;
		M.turret1_stop = false;
	end
	if ( not IsAlive(M.ccaturret2))
	then
		M.turret2_underway = false;
		M.turret2_stop = false;
	end
	if ( not IsAlive(M.ccaartil1))
	then
		M.artil1_stop = false;
		M.artil1_underway = false;
	end
	if ( not IsAlive(M.ccaartil2))
	then
		M.artil2_stop = false;
		M.artil2_underway = false;
	end
	if ( not IsAlive(M.ccaartil3))
	then
		M.artil3_stop = false;
		M.artil3_underway = false;
	end
	if ( not IsAlive(M.ccafighter1))
	then
		M.fighter1_underway = false;
		M.chase_tug = false;
	end
	if ( not IsAlive(M.ccafighter2))
	then
		M.fighter2_underway = false;
		M.chase_tug = false;
	end
	if ( not IsAlive(M.ccatank1))
	then
		M.tank1_follow = false;
		M.tank1_stop = false;
		M.chase_tug = false;
	end
	if ( not IsAlive(M.ccatank2))
	then
		M.tank2_follow = false;
		M.tank2_stop = false;
		M.chase_tug = false;
	end

-- the first thing I want to do is get the position of the M.sav
	if ((IsAlive(M.ccatug)) and (M.sav_free) and ( not M.got_position))
	then
		if (((GetDistance(M.sav, M.geys1)) < (GetDistance(M.sav, M.geys2))) and ((GetDistance(M.sav, M.geys1)) < (GetDistance(M.sav, M.geys3))) and ((GetDistance(M.sav, M.geys1)) < (GetDistance(M.sav, M.geys4)))
			 and  ((GetDistance(M.sav, M.geys1)) < (GetDistance(M.sav, M.geys5))) and ((GetDistance(M.sav, M.geys1)) < (GetDistance(M.sav, M.geys6))) and ((GetDistance(M.sav, M.geys1)) < (GetDistance(M.sav, M.geys7))))
		then
			M.position1 = true; --
			M.position2 = false;--
			M.position3 = false;-- this code gets the position of the relic so I can determine 
			M.position4 = false;-- which path to send the cca tug down and back
			M.position5 = false;--
			M.position6 = false;--
			M.position7 = false;--
		else
			if (((GetDistance(M.sav, M.geys2)) < (GetDistance(M.sav, M.geys1))) and ((GetDistance(M.sav, M.geys2)) < (GetDistance(M.sav, M.geys3))) and ((GetDistance(M.sav, M.geys2)) < (GetDistance(M.sav, M.geys4)))
				 and  ((GetDistance(M.sav, M.geys2)) < (GetDistance(M.sav, M.geys5))) and ((GetDistance(M.sav, M.geys2)) < (GetDistance(M.sav, M.geys6))) and ((GetDistance(M.sav, M.geys2)) < (GetDistance(M.sav, M.geys7))))
			then
				M.position1 = false;--
				M.position2 = true; --
				M.position3 = false;-- this code gets the position of the relic so I can determine 
				M.position4 = false;-- which path to send the cca tug down and back
				M.position5 = false;--
				M.position6 = false;--
				M.position7 = false;--
			else
				if (((GetDistance(M.sav, M.geys3)) < (GetDistance(M.sav, M.geys1))) and ((GetDistance(M.sav, M.geys3)) < (GetDistance(M.sav, M.geys2))) and ((GetDistance(M.sav, M.geys3)) < (GetDistance(M.sav, M.geys4)))
					 and  ((GetDistance(M.sav, M.geys3)) < (GetDistance(M.sav, M.geys5))) and ((GetDistance(M.sav, M.geys3)) < (GetDistance(M.sav, M.geys6))) and ((GetDistance(M.sav, M.geys3)) < (GetDistance(M.sav, M.geys7))))
				then
					M.position1 = false;--
					M.position2 = false;--
					M.position3 = true; -- this code gets the position of the relic so I can determine 
					M.position4 = false;-- which path to send the cca tug down and back
					M.position5 = false;--
					M.position6 = false;--
					M.position7 = false;--
				else
					if (( not M.sav_seized) and ((GetDistance(M.sav, M.geys4)) < (GetDistance(M.sav, M.geys1))) and ((GetDistance(M.sav, M.geys4)) < (GetDistance(M.sav, M.geys2))) and ((GetDistance(M.sav, M.geys4)) < (GetDistance(M.sav, M.geys3)))
						 and  ((GetDistance(M.sav, M.geys4)) < (GetDistance(M.sav, M.geys5))) and ((GetDistance(M.sav, M.geys4)) < (GetDistance(M.sav, M.geys6))) and ((GetDistance(M.sav, M.geys4)) < (GetDistance(M.sav, M.geys7))))
					then
						M.position1 = false;--
						M.position2 = false;--
						M.position3 = false;-- this code gets the position of the relic so I can determine 
						M.position4 = true; -- which path to send the cca tug down and back
						M.position5 = false;--
						M.position6 = false;--
						M.position7 = false;--
					else
						if (((GetDistance(M.sav, M.geys5)) < (GetDistance(M.sav, M.geys1))) and ((GetDistance(M.sav, M.geys5)) < (GetDistance(M.sav, M.geys2))) and ((GetDistance(M.sav, M.geys5)) < (GetDistance(M.sav, M.geys3)))
							 and  ((GetDistance(M.sav, M.geys5)) < (GetDistance(M.sav, M.geys4))) and ((GetDistance(M.sav, M.geys5)) < (GetDistance(M.sav, M.geys6))) and ((GetDistance(M.sav, M.geys5)) < (GetDistance(M.sav, M.geys7))))
						then
							M.position1 = false;--
							M.position2 = false;--
							M.position3 = false;--
							M.position4 = false;-- this code gets the position of the relic so I can determine 
							M.position5 = true; -- which path to send the cca tug down and back
							M.position6 = false;--
							M.position7 = false;--
						else
							if (((GetDistance(M.sav, M.geys6)) < (GetDistance(M.sav, M.geys1))) and ((GetDistance(M.sav, M.geys6)) < (GetDistance(M.sav, M.geys2))) and ((GetDistance(M.sav, M.geys6)) < (GetDistance(M.sav, M.geys3)))
								 and  ((GetDistance(M.sav, M.geys6)) < (GetDistance(M.sav, M.geys4))) and ((GetDistance(M.sav, M.geys6)) < (GetDistance(M.sav, M.geys5))) and ((GetDistance(M.sav, M.geys6)) < (GetDistance(M.sav, M.geys7))))
							then
								M.position1 = false;--
								M.position2 = false;--
								M.position3 = false;-- this code gets the position of the relic so I can determine 
								M.position4 = false;-- which path to send the cca tug down and back
								M.position5 = false;--
								M.position6 = true; --
								M.position7 = false;--
							else
								if (((GetDistance(M.sav, M.geys7)) < (GetDistance(M.sav, M.geys1))) and ((GetDistance(M.sav, M.geys7)) < (GetDistance(M.sav, M.geys2))) and ((GetDistance(M.sav, M.geys7)) < (GetDistance(M.sav, M.geys3)))
									 and  ((GetDistance(M.sav, M.geys7)) < (GetDistance(M.sav, M.geys4))) and ((GetDistance(M.sav, M.geys7)) < (GetDistance(M.sav, M.geys5))) and ((GetDistance(M.sav, M.geys7)) < (GetDistance(M.sav, M.geys6))))
								then
									M.position1 = false;--
									M.position2 = false;--
									M.position3 = false;-- this code gets the position of the relic so I can determine 
									M.position4 = false;-- which path to send the cca tug down and back
									M.position5 = false;--
									M.position6 = false;--
									M.position7 = true; --
								end
							end
						end
					end
				end
			end
		end

		M.got_position = true;
	end

-- now I'll start the mission
	if ( not M.start_done)
	then
		AudioMessage("misn1000.wav"); -- player briefing
		ClearObjectives();
		AddObjective("misn1000.otf", "WHITE");
		SetIndependence(M.svartil1, 1);
		SetIndependence(M.svartil2, 1);
		SetScrap(1, 30);
		SetPilot(1, 10);
		SetScrap(2, 40);
		SetPilot(2, 40);
		SetAIP("misn10.aip"); -- this sets the soviets into action
--		M.build_sav_time = GetTime() + 120.0;--temp
--		M.relic_check = GetTime() + 5.0;
		M.turret1_check = GetTime() + 19.0;
		M.turret2_check = GetTime() + 20.0;
		M.artil1_check = GetTime() + 21.0;
		M.artil2_check = GetTime() + 22.0;
		M.artil3_check = GetTime() + 23.0;
		SetObjectiveName(M.nav1, "Relic Site");
		SetObjectiveName(M.nav2, "CCA Base");
		SetObjectiveName(M.nav3, "Drop Zone");
		SetObjectiveName(M.sav, "Alien Relic");
		M.relic_free = true;
		M.start_done = true;		
	end

	if ((GetDistance(M.user, M.sav) < 100.0) and ( not M.objective_on))
	then
		SetObjectiveOn(M.sav);
		M.objective_on = true;
	end

--[[	if (( not M.quake) and (M.quake_time < GetTime()))
	then
		M.quake_time = GetTime() + 10.0;
		StartEarthquake(2.0);
		M.quake = true;
	end

	if ((M.quake) and (M.quake_time < GetTime()))
	then
		StopEarthquake();
		M.quake_time = GetTime() + 120.0;
		M.quake = false;
	end
--]]

-- The first thing the soviets do is secure the M.sav with fighters
	
	if ((M.relic_free) and (IsAlive(M.ccafighter1)) and ( not M.fighter1_underway))
	then
		Follow(M.ccafighter1, M.sav);
		M.fighter1_underway = true;
	end

	if ((M.relic_free) and (IsAlive(M.ccafighter2)) and ( not M.fighter2_underway))
	then
		Follow(M.ccafighter2, M.sav);
		M.fighter2_underway = true;
	end

-- now that fighters are protecting the M.sav the soviets position turrets to assist
	if ((IsAlive(M.ccaturret1)) and ( not M.turret1_underway))
	then
		Goto(M.ccaturret1, "relic_path1");
		M.turret1_underway = true;
	end

	if ((IsAlive(M.ccaturret2)) and ( not M.turret2_underway))
	then
		Goto(M.ccaturret2, "relic_path1");
		M.turret2_underway = true;
	end

	if ((IsAlive(M.ccaturret3)) and ( not M.turret3_underway))
	then
		if ((IsAlive(M.ccarecycle)) and (GetDistance(M.ccaturret3, M.ccarecycle) > 30.0))
		then
			Defend(M.ccaturret3);
			M.turret3_underway = true;
		end
	end

-- gets the turrets to stop
	if ((M.turret1_underway) and (M.turret1_check < GetTime()))
	then
		M.turret1_check = GetTime() + 3.0;

		if ((IsAlive(M.ccaturret1)) and ( not M.turret1_stop) and (GetDistance(M.ccaturret1, M.geys1) < 50.0))
		then
			Defend(M.ccaturret1);
			M.turret1_stop = true;
		end
	end

	if ((M.turret2_underway) and (M.turret2_check < GetTime()))
	then
		M.turret2_check = GetTime() + 3.0;

		if ((IsAlive(M.ccaturret2)) and ( not M.turret2_stop) and (GetDistance(M.ccaturret2, M.geys2) < 50.0))
		then
			Deploy(M.ccaturret2);
			Defend(M.ccaturret2);
			M.turret2_stop = true;
		end
	end

-- now the soviets will check to see if they can change their first aip

	if ((IsAlive(M.ccafighter1)) and (IsAlive(M.ccafighter2)) 
		 and  (IsAlive(M.ccaturret1)) and (IsAlive(M.ccaturret2)) and ( not M.plan_a))
	then
		if (GetScrap(2) > 15)
		then
			SetAIP("misn10a.aip");
			M.plan_a = true;
		end
	end

--[[	if ((IsAlive(M.ccatank1)) and ( not IsAlive(M.ccatug)) and ( not M.tank1_stop))
	then
		Stop(M.ccatank1);
		M.tank1_stop = true;
	end

	if ((IsAlive(M.ccatank2)) and ( not IsAlive(M.ccatug)) and ( not M.tank2_stop))
	then
		Stop(M.ccatank2);
		M.tank2_stop = true;
	end
--]]

-- now they check to see if they can load their next aip
--	if ((IsAlive(M.ccatug)) and (IsAlive(M.ccatank1)) 
--		 and  (IsAlive(M.ccatank2)) and ( not M.plan_b))
--	then
--		SetScrap(2, 40);
--		SetAIP("misn10b.aip");
--		M.plan_b = true;
--	end

-- this sets the artillery into motion

	if ((IsAlive(M.ccaartil1)) and ( not M.artil1_underway))
	then
		Goto(M.ccaartil1, "artil1_path", 1);
		M.artil1_underway = true;
	end

	if ((IsAlive(M.ccaartil2)) and ( not M.artil2_underway))
	then
		Goto(M.ccaartil2, "artil2_path", 1);
		M.artil2_underway = true;
	end

	if ((IsAlive(M.ccaartil3)) and ( not M.artil3_underway))
	then
		Goto(M.ccaartil3, "relic_path1");
		M.artil3_underway = true;
	end
-- this is checking to see if the soviet artil has reached it's spot
		if (M.artil1_check < GetTime())
		then
			M.artil1_check = GetTime() + 3.0;

			if ((IsAlive(M.ccaartil1)) and ( not M.artil1_stop) and (GetDistance(M.ccaartil1, M.post1_geyser) < 20.0))
			then
				Defend(M.ccaartil1);
				M.artil1_stop = true;
			end
		end

		if (M.artil2_check < GetTime())
		then
			M.artil2_check = GetTime() + 3.0;

			if ((IsAlive(M.ccaartil2)) and ( not M.artil2_stop) and (GetDistance(M.ccaartil2, M.post3_geyser) < 20.0))
			then
				Defend(M.ccaartil2);
				M.artil2_stop = true;
			end
		end

		if (M.artil3_check < GetTime())
		then
			M.artil3_check = GetTime() + 3.0;

			if ((IsAlive(M.ccaartil3)) and ( not M.artil3_stop) and (GetDistance(M.ccaartil3, M.geys2) < 50.0))
			then
				Defend(M.ccaartil3);
				M.artil3_stop = true;
			end
		end
			
--[[
	if ((M.build_sav_time < GetTime()) and ( not M.new_sav_built)) --this will be replaced by "sav_free"
	then
		M.sav = BuildObject ("abstor", 1, M.geys7);

		M.tug_underway1 = false;
		M.tug_underway2 = false;
		M.tug_underway3 = false;
		M.tug_underway4 = false;
		M.tug_underway5 = false;
		M.tug_underway6 = false;
		M.tug_underway7 = false;
		M.tug_after_sav = false;
		M.tug_wait_center = false;
		M.tug_wait2 = false;
		M.tug_wait3 = false;
		M.tug_wait4 = false;
		M.tug_wait5 = false;
		M.tug_wait6 = false;
		M.tug_wait7 = false;
		M.tug_wait_base = false;		
		M.sav_seized = false;
		M.new_sav_built = true;
	end
--]]

-- hopefully, the following code will build a cca tug every 30 seconds after the last cca tug is destoyed
--[[
		if (( not M.build_tug) and (IsAlive(M.ccarecycle)))
		then
			M.ccatug = BuildObject("svhaul", 2, M.ccarecycle);
			M.build_tug = true;
		end
		
		if ((M.build_tug) and ( not IsAlive(M.ccatug)) and ( not M.making_another_tug))
		then
			M.build_another_tug_time = GetTime() + 30.0;
			--------------------------
			M.tug_underway1 = false;	--
			M.tug_underway2 = false;	--
			M.tug_underway3 = false;	--
			M.tug_underway4 = false;	--
			M.tug_underway5 = false;	-- 
			M.tug_underway6 = false;	--
			M.tug_underway7 = false;	--
			M.tug_after_sav = false;	--all tug settings reset because the last tug was destroyed
			M.return_to_base = false;	--
			M.tug_wait_center = false;--
			M.tug_wait2 = false;		--
			M.tug_wait3 = false;		--
			M.tug_wait4 = false;		--
			M.tug_wait5 = false;		--
			M.tug_wait6 = false;		--
			M.tug_wait7 = false;		--
			M.tug_wait_base = false;	--
			M.tug_at_wait_center = false;
			--------------------------
			M.making_another_tug = true;
		end

		if ((M.making_another_tug) and (M.build_another_tug_time < GetTime()) and (M.build_tug))
		then
			M.making_another_tug = false;
			M.build_tug = false;
		end
--]]
-- now I'm attempting to send the cca tug to the relic in the smartest path --------------------------------------------------------------------------------------------------------/
-- first I determine where the relic on the map by dertermining which geyser its closest to ----------------------------------------------------------------------------------------/


-- now that I know which geyser the relic closest to I'll send the cca tug down the appropriate path (to keep it out of the lava fields as much as possible ------------------------------
if ((IsAlive(M.ccatug)) and (M.got_position))
then
				if ((IsAlive(M.ccatank1)) and ( not M.tank1_follow))
				then
					Follow(M.ccatank1, M.ccatug, 1);
					M.tank1_follow = true;
				end

				if ((IsAlive(M.ccatank2)) and ( not M.tank2_follow))
				then
					Follow(M.ccatank2, M.ccatug, 1);
					M.tank2_follow = true;
				end

	if (( not M.tug_underway1) and (M.sav_free) and (M.position1) and ( not M.tug_after_sav))
	then
		Goto(M.ccatug, "relic_path1", 1);
		M.tug_underway1 = true;
	end

	if ((M.tug_underway1) and (M.sav_free) and (GetDistance(M.ccatug, M.sav) < GetDistance(M.ccatug, M.geys1)) and 
		(GetDistance(M.ccatug, M.sav) < 100.0) and ( not M.tug_after_sav))
	then
		Pickup(M.ccatug, M.sav, 1);
		if (IsAlive(M.ccatank1))
		then
			Follow(M.ccatank1, M.ccatug, 0);
		end
		if (IsAlive(M.ccatank2))
		then
			Follow(M.ccatank2, M.ccatug, 0);
		end
		M.tug_after_sav = true;
	end

	if ((M.tug_underway1) and (M.sav_free) and (GetDistance(M.ccatug, M.geys1) < 100.0) and ( not M.tug_after_sav))
	then
		Pickup(M.ccatug, M.sav, 1);
		M.tug_after_sav = true;
	end

		if ((M.sav_free) and (M.position2) and ( not M.tug_underway2) and ( not M.tug_after_sav))
		then
			Goto(M.ccatug, "relic_path1", 1);
			M.tug_underway2 = true;
		end

		if ((M.tug_underway2) and (M.sav_free) and (GetDistance(M.ccatug, M.sav) < GetDistance(M.ccatug, M.geys2))  and 
			(GetDistance(M.ccatug, M.sav) < 100.0) and ( not M.tug_after_sav))
		then
			Pickup(M.ccatug, M.sav, 1);
			M.tug_after_sav = true;
		end

		if ((M.tug_underway2) and (M.sav_free) and (GetDistance(M.ccatug, M.geys2) < 100.0) and ( not M.tug_after_sav))
		then
			Pickup(M.ccatug, M.sav, 1);
			M.tug_after_sav = true;
		end

	if ((M.sav_free) and (M.position3) and ( not M.tug_underway3) and ( not M.tug_after_sav))
	then
		Goto(M.ccatug, "attack_path_central", 1);
		M.tug_underway3 = true;
	end

	if ((M.tug_underway3) and (M.sav_free) and (GetDistance(M.ccatug, M.sav) < GetDistance(M.ccatug, M.geys3))  and 
		(GetDistance(M.ccatug, M.sav) < 100.0) and ( not M.tug_after_sav))
	then
		Pickup(M.ccatug, M.sav, 1);
		M.tug_after_sav = true;
	end

	if ((M.tug_underway3) and (M.sav_free) and (GetDistance(M.ccatug, M.geys3) < 100.0) and ( not M.tug_after_sav))
	then
		Pickup(M.ccatug, M.sav, 1);
		M.tug_after_sav = true;
	end

		if ((M.sav_free) and (M.position4) and ( not M.tug_underway4) and ( not M.tug_after_sav))
		then
			Goto(M.ccatug, "attack_path_central", 1);
			M.tug_underway4 = true;
		end

		if ((M.tug_underway4) and (M.sav_free) and (GetDistance(M.ccatug, M.sav) < GetDistance(M.ccatug, M.geys4))  and 
			(GetDistance(M.ccatug, M.sav) < 100.0) and ( not M.tug_after_sav))
		then
			Pickup(M.ccatug, M.sav, 1);
			M.tug_after_sav = true;
		end

		if ((M.tug_underway4) and (M.sav_free) and (GetDistance(M.ccatug, M.geys4) < 100.0) and ( not M.tug_after_sav))
		then
			Pickup(M.ccatug, M.sav, 1);
			M.tug_after_sav = true;
		end

	if ((M.sav_free) and (M.position5) and ( not M.tug_underway5) and ( not M.tug_after_sav))
	then
		Goto(M.ccatug, "attack_path_south", 1);
		M.tug_underway5 = true;
	end

	if ((M.tug_underway5) and (M.sav_free) and (GetDistance(M.ccatug, M.sav) < GetDistance(M.ccatug, M.geys5))  and 
		(GetDistance(M.ccatug, M.sav) < 100.0) and ( not M.tug_after_sav))
	then
		Pickup(M.ccatug, M.sav, 1);
		M.tug_after_sav = true;
	end

	if ((M.tug_underway5) and (M.sav_free) and (GetDistance(M.ccatug, M.geys5) < 100.0) and ( not M.tug_after_sav))
	then
		Pickup(M.ccatug, M.sav, 1);
		M.tug_after_sav = true;
	end

		if ((M.sav_free) and (M.position6) and ( not M.tug_underway6) and ( not M.tug_after_sav))
		then
			Goto(M.ccatug, "attack_path_north", 1);
			M.tug_underway6 = true;
		end

		if ((M.tug_underway6) and (M.sav_free) and (GetDistance(M.ccatug, M.sav) < GetDistance(M.ccatug, M.geys6)) and 
			(GetDistance(M.ccatug, M.sav) < 100.0) and ( not M.tug_after_sav))
		then
			Pickup(M.ccatug, M.sav, 1);
			M.tug_after_sav = true;
		end

		if ((M.tug_underway6) and (M.sav_free) and (GetDistance(M.ccatug, M.geys6) < 100.0) and ( not M.tug_after_sav))
		then
			Pickup(M.ccatug, M.sav, 1);
			M.tug_after_sav = true;
		end

	if ((M.sav_free) and (M.position7) and ( not M.tug_underway7) and ( not M.tug_after_sav))
	then
		Goto(M.ccatug, "attack_path_south", 1);
		M.tug_underway7 = true;
	end

	if ((M.tug_underway7) and (M.sav_free) and (GetDistance(M.ccatug, M.sav) < GetDistance(M.ccatug, M.geys7)) and 
		(GetDistance(M.ccatug, M.sav) < 100.0) and ( not M.tug_after_sav))
	then
		Pickup(M.ccatug, M.sav, 1);
		M.tug_after_sav = true;
	end

	if ((M.tug_underway7) and (M.sav_free) and (GetDistance(M.ccatug, M.geys7) < 100.0) and ( not M.tug_after_sav))
	then
		Pickup(M.ccatug, M.sav, 1);
		M.tug_after_sav = true;
	end

-- now that the tug has picked the correct path I'll have the tug pick up the M.sav and pick a path home ----------------------------------

	if ((M.tug_after_sav) and (M.tug_underway1) and (M.sav_seized) and ( not M.return_to_base))
	then
		Goto(M.ccatug, "main_return_path", 1);
		M.return_to_base = true;
	end

	if ((M.tug_after_sav) and (M.tug_underway2) and (M.sav_seized) and ( not M.return_to_base))
	then
		Goto(M.ccatug, M.ccarecycle, 1);
		M.return_to_base = true;
	end

	if ((M.tug_after_sav) and (M.tug_underway3) and (M.sav_seized) and ( not M.return_to_base))
	then
		Goto(M.ccatug, "lsouth_return_path", 1);
		M.return_to_base = true;
	end

	if ((M.tug_after_sav) and (M.tug_underway4) and (M.sav_seized) and ( not M.return_to_base))
	then
		Goto(M.ccatug, "main_return_path", 1);
		M.return_to_base = true;
	end

	if ((M.tug_after_sav) and (M.tug_underway5) and (M.sav_seized) and ( not M.return_to_base))
	then
		Goto(M.ccatug, "ssouth_return_path", 1);
		M.return_to_base = true;
	end

	if ((M.tug_after_sav) and (M.tug_underway6) and (M.sav_seized) and ( not M.return_to_base))
	then
		Goto(M.ccatug, "main_return_path", 1);
		M.return_to_base = true;
	end

	if ((M.tug_after_sav) and (M.tug_underway7) and (M.sav_seized) and ( not M.return_to_base))
	then
		Goto(M.ccatug, "msouth_return_path", 1);
		M.return_to_base = true;
	end
end

-- this is what happens if the player aquires the relic before the cca and a cca tug exits ------------------

	if ( not IsAlive(M.sav))
	then
		if ((M.sav_secure) and ( not M.tug_underway1))
		then
			M.tug_wait_base = true;
		end	
		
		if ((M.sav_secure) and (M.tug_underway1))
		then
			M.tug_underway1 = false;
			M.tug_wait_center = true;
		end

		if ((M.sav_secure) and ( not M.tug_underway2))
		then
			M.tug_wait_base = true;
		end	
	end

		if ((M.sav_secure) and (M.tug_underway2) and (GetDistance (M.ccatug, M.geys2) < 50.0) and ( not M.tug_wait2))
		then
			Goto(M.ccatug, M.geys2, 1);
			M.tug_underway2 = false;
			M.tug_wait2 = true;
		end

		if ((M.sav_secure) and (M.tug_underway2) and (M.tug_after_sav) and ( not M.tug_wait2))
		then
			Goto(M.ccatug, M.geys2, 1);
			M.tug_underway2 = false;
			M.tug_after_sav = false;
			M.tug_wait2 = true;
		end

	if (( not IsAlive(M.sav)) and (M.sav_secure) and ( not M.tug_underway3))
	then
		M.tug_wait_base = true;
	end	

		if ((M.sav_secure) and (M.tug_underway3) and (GetDistance (M.ccatug, M.geys3) < 50.0) and ( not M.tug_wait3))
		then
			Goto(M.ccatug, M.geys3, 1);
			M.tug_underway3 = false;	
			M.tug_wait3 = true;
		end

		if ((M.sav_secure) and (M.tug_underway3) and (M.tug_after_sav) and ( not M.tug_wait3))
		then
			Goto(M.ccatug, M.geys3, 1);
			M.tug_underway3 = false;	
			M.tug_after_sav = false;
			M.tug_wait3 = true;
		end

	if (( not IsAlive(M.sav)) and (M.sav_secure) and ( not M.tug_underway4))
	then
		M.tug_wait_base = true;
	end	

		if ((M.sav_secure) and (M.tug_underway4) and (GetDistance (M.ccatug, M.geys4) < 50.0) and ( not M.tug_wait4))
		then
			Goto(M.ccatug, M.geys4, 1);
			M.tug_underway4 = false;
			M.tug_wait4 = true;
		end

		if ((M.sav_secure) and (M.tug_underway4) and (M.tug_after_sav) and ( not M.tug_wait4))
		then
			Goto(M.ccatug, M.geys4, 1);
			M.tug_underway4 = false;
			M.tug_after_sav = false;
			M.tug_wait4 = true;
		end

	if (( not IsAlive(M.sav)) and (M.sav_secure) and ( not M.tug_underway5))
	then
		M.tug_wait_base = true;
	end	

		if ((M.sav_secure) and (M.tug_underway5) and (GetDistance (M.ccatug, M.geys5) < 50.0) and ( not M.tug_wait5))
		then
			Goto(M.ccatug, M.geys5, 1);
			M.tug_underway5 = false;
			M.tug_wait5 = true;
		end

		if ((M.sav_secure) and (M.tug_underway5) and (M.tug_after_sav) and ( not M.tug_wait5))
		then
			Goto(M.ccatug, M.geys5, 1);
			M.tug_underway5 = false;
			M.tug_after_sav = false;
			M.tug_wait5 = true;
		end

	if (( not IsAlive(M.sav)) and (M.sav_secure) and ( not M.tug_underway6))
	then
		M.tug_wait_base = true;
	end	
	
		if ((M.sav_secure) and (M.tug_underway6) and (GetDistance (M.ccatug, M.geys6) < 50.0) and ( not M.tug_wait6))
		then
			Goto(M.ccatug, M.geys6, 1);
			M.tug_underway6 = false;			
			M.tug_wait6 = true;
		end

		if ((M.sav_secure) and (M.tug_underway6) and (M.tug_after_sav) and ( not M.tug_wait6))
		then
			Goto(M.ccatug, M.geys6, 1);
			M.tug_underway6 = false;
			M.tug_after_sav = false;
			M.tug_wait6 = true;
		end

	if (( not IsAlive(M.sav)) and (M.sav_secure) and ( not M.tug_underway7))
	then
		M.sav_seized = true;
		M.tug_wait_base = true;
	end	

		if ((M.sav_secure) and (M.tug_underway7) and (GetDistance (M.ccatug, M.geys7) < 50.0) and ( not M.tug_wait7))
		then
			Goto(M.ccatug, M.geys7, 1);
			M.tug_underway7 = false;
			M.tug_wait7 = true;
		end

		if ((M.sav_secure) and (M.tug_underway7) and (M.tug_after_sav) and ( not M.tug_wait7))
		then
			Goto(M.ccatug, M.geys7, 1);
			M.tug_underway7 = false;
			M.tug_after_sav = false;
			M.tug_wait7 = true;
		end

-- this is going to make the cca go after the american tug

		if ((M.tugger ~= 0) and ( not M.chase_tug))
		then
			if (IsAlive(M.ccafighter1))
			then
				Attack(M.ccafighter1, M.tugger, 1);
			end
			if (IsAlive(M.ccafighter2))
			then
				Attack(M.ccafighter2, M.tugger, 1);
			end
			if (IsAlive(M.ccatank1))
			then
				Attack(M.ccatank1, M.tugger, 1);
			end
			if (IsAlive(M.ccatank2))
			then
				Attack(M.ccatank2, M.tugger, 1);
			end
			if (IsAlive(M.svartil1))
			then
				Attack(M.svartil1, M.tugger, 1);
			end
			if (IsAlive(M.svartil2))
			then
				Attack(M.svartil2, M.tugger, 1);
			end
			if (IsAlive(M.ccaartil1))
			then
				Attack(M.ccaartil1, M.tugger, 1);
			end
			if (IsAlive(M.ccaartil2))
			then
				Attack(M.ccaartil2, M.tugger, 1);
			end
			if (IsAlive(M.ccaartil3))
			then
				Attack(M.ccaartil3, M.tugger, 1);
			end

			M.chase_tug = true;
		end

-- this make the artil sheel the relic

	if ((M.geys1check < GetTime()) and ( not M.chase_tug))
	then
		M.geys1check = GetTime() + 150.0;

		if (GetDistance(M.user, M.geys1) < 200.0)
		then
			if (IsAlive(M.svartil1))
			then
				Attack(M.svartil1, M.user);
			end
			if (IsAlive(M.svartil2))
			then
				Attack(M.svartil2, M.user);
			end
		else
			if (IsAlive(M.svartil1))
			then
				Attack(M.svartil1, M.geys1);
			end
			if (IsAlive(M.svartil2))
			then
				Attack(M.svartil2, M.geys1);
			end
		end
	end

-- this is making sure the M.sav doesn't die
	if (IsAlive(M.sav))
	then
		if (GetTime()>M.next_second)
		then
			AddHealth(M.sav, 100.0);
			M.next_second = GetTime() + 1.0;
		end
	end

		
-- win/victory conditions --------------------------------------------

	if ((M.sav_secure) and (GetDistance (M.sav, M.nsdfrecycle) < 100.0) and ( not M.game_over))
	then
		AudioMessage("misn1001.wav");--well done
		SucceedMission(GetTime() + 15.0, "misn10w1.des");
		M.game_over = true;
	end

	if ((M.sav_seized) and ( not M.game_over) and (GetDistance (M.sav, M.ccarecycle) < 100.0))
	then
		AudioMessage("misn1002.wav");-- you lost
		FailMission(GetTime() + 15.0, "misn10f1.des");
		M.game_over = true;
	end

	if (( not IsAlive(M.sav)) and ( not M.game_over))
	then
		AudioMessage("misn1003.wav");-- we lost the M.sav
		FailMission(GetTime() + 15.0, "misn10f2.des");
		M.game_over = true;
	end
	

	if (( not IsAlive(M.nsdfrecycle)) and ( not M.game_over))
	then
		AudioMessage("misn1004.wav");-- we lost the Utah
		FailMission(GetTime() + 15.0, "misn10f3.des");
		M.game_over = true;
	end

-- END OF SCRIPT
	
end