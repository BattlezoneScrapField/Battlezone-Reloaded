-- Single Player NSDF Mission 7 Lua conversion, created by General BlackDragon. 

-- Single Table for all our save/load variables. This SP mission has too many variables to function with them independently. ("main function has > 200 local variables", or "Load having > 197 variables in assignment")
local M = {

-- bools
	start_done = false,
	gech_found = false,
	gech_found1 = false,
	gech_found2 = false,
	base_dead = false,
	won_mission = false,
	lost_mission = false,
	gech_at_nav = false,
	gech_at_nav2 = false,
	gech_at_nav3 = false,
	player_warned_ofgech = false,
	colorado_under_attack = false,
	colorado_destroyed = false,
	followup_message = false,
	colorado_message2 = false,
	colorado_message3 = false,
	colorado_message4 = false,
	second_gech_warning = false,
	run_into_other_gech = false,
	too_close_message = false,
	bad_news = false,
	bump_into_gech = false,
	ccarecycle_spawned = false,
	gech_started = false,
	gech3_move = false,
	first_wave = false,
	--second_wave = false,
	--next_wave = false,
	gech1_at_base = false,
	gech2_at_base = false,
	gech3_at_base = false,
	gech1_blossom = false,
	gech2_blossom = false,
	gech3_blossom = false,
	fresh_meat = false,
	fighter_message = false,
	apc_attack = false,
	base_set = false,
	game_over = false,
	cerb_found = false,
	relic_message = false,
	kill_colorado = false,
	gen_message = false,
-- Floats (really doubles in Lua)
	--unit_spawn_time = 0,
	followup_message_time = 0,
	colorado_message2_time = 0,
	colorado_message3_time = 0,
	colorado_message4_time = 0,
	bad_news_time = 0,
	gech_warning_message = 0,
	remove_nav5_time = 0,
	gech_spawn_time = 0,
	gech_check = 0,
	gech_check2 = 0,
	stumble1_check = 0,
	stumble2_check = 0,
	trigger_check = 0,
	no_stumble_check = 0,
	time_waist = 0,
	start_gech_time = 0,
	gech_check_time = 0,
	first_wave_time = 0,
	--second_wave_time = 0,
	--next_wave_time = 0,
	gech1_there_time = 0,
	gech2_there_time = 0,
	gech3_there_time = 0,
	new_aip_time = 0,
	fresh_meat_time = 0,
	fighter_message_time = 0,
	player_nosey_time = 0,
	pull_out_message = 0,
	base_check = 0,
	cerb_check = 0,
	next_second = 0,
	next_second2 = 0,
-- Handles
	user = nil,
	death_scrap = nil,
	death_scrap2 = nil,
	death_scrap3 = nil,
	nav1 = nil,
	nav2 = nil,
	nav3 = nil,
	nav4 = nil,
	nav5 = nil,
	ccagech1 = nil,
	ccagech2 = nil,
	ccagech3 = nil,
	colorado = nil,
	drop = nil,
	ccarecycle = nil,
	ccamuf = nil,
	--ccaarmor = nil,
	gech_trigger2 = nil,
	gech_trigger3 = nil,
	nsdfrecycle = nil,
	nsdfmuf = nil,
	--attack_geys = nil,
	ccarecycle_geyser = nil,
	stop_geyser1 = nil,
	stop_geyser2 = nil,
	stop_geyser3 = nil,
	svpatrol1_1 = nil,
	svpatrol1_2 = nil,
	svpatrol1_3 = nil,
	svpatrol2_1 = nil,
	svpatrol2_2 = nil,
	svpatrol2_3 = nil,
	cannon_fodder1 = nil,
	cannon_fodder2 = nil,
	cannon_fodder3 = nil,
	ccaapc = nil,
	guntower1 = nil,
	guntower2 = nil,
	--relic1 = nil,
	--relic2 = nil,
	main_relic = nil,
-- Ints
	units1 = 0,
	units2 = 0
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
		
	M.followup_message_time = 99999.0;
	M.gech_warning_message = 99999.0;
	M.colorado_message2_time = 99999.0;
	M.colorado_message3_time = 99999.0;
	M.colorado_message4_time = 99999.0;
	M.bad_news_time = 99999.0;
	M.remove_nav5_time = 99999.0;
	M.gech_spawn_time = 99999.0;
	M.gech_check = 99999.0;
	M.gech_check2 = 99999.0;
	M.stumble2_check = 99999.0;
	M.stumble1_check = 99999.0;
	M.trigger_check = 99999.0;
	M.no_stumble_check = 99999.0;
	M.time_waist = 99999.0;
	M.start_gech_time = 99999.0;
	M.gech_check_time = 10.0;
	M.first_wave_time = 99999.0;
	--M.second_wave_time = 99999.0;
	--M.next_wave_time = 99999.0;
	M.gech1_there_time = 99999.0;
	M.gech2_there_time = 99999.0;
	M.gech3_there_time = 99999.0;
	M.new_aip_time = 99999.0;
	M.fresh_meat_time = 99999.0;
	M.fighter_message_time = 200.0;
	M.player_nosey_time = 45.0;
	M.pull_out_message = 99999.0;
	M.base_check = 99999.0;
	M.cerb_check = 30.0;
	M.next_second = 99999.0;
	M.next_second2 = 99999.0;
	
	M.death_scrap = GetHandle("death_scrap");
	M.death_scrap2 = GetHandle("death_scrap2");
	M.death_scrap3 = GetHandle("death_scrap3");
	M.nsdfrecycle = GetHandle("avrecycle");
	M.ccarecycle = GetHandle("svrecycle");
	M.ccamuf = GetHandle("svmuf");
	M.ccagech1 = GetHandle("sovgech1");
	M.ccagech2 = GetHandle("sovgech2");
	M.nav1 = GetHandle("cam1");
	M.nav4 = GetHandle("cam2");
	M.nav5 = GetHandle("cam5");
	M.gech_trigger2 = GetHandle("giez_spawn2");
	M.gech_trigger3 = GetHandle("giez_spawn3");
	M.colorado = GetHandle("colorado");
--	M.drop = GetHandle("dropoff57_dropoff");
	--M.attack_geys = GetHandle("attack_geyser");
	M.ccarecycle_geyser = GetHandle("ccarecycle_geyser");
	M.stop_geyser1 = GetHandle("stop_geyser1");
	M.stop_geyser2 = GetHandle("stop_geyser2");
	M.stop_geyser3 = GetHandle("stop_geyser3");
	M.svpatrol1_1 = GetHandle("svpatrol1_1");
	M.svpatrol1_2 = GetHandle("svpatrol1_2");
	M.svpatrol1_3 = GetHandle("svpatrol1_3");
	M.svpatrol2_1 = GetHandle("svpatrol2_1");
	M.svpatrol2_2 = GetHandle("svpatrol2_2");
	M.svpatrol2_3 = GetHandle("svpatrol2_3");
	--M.relic1 = GetHandle("hbblde1_i76building");
	--M.relic2 = GetHandle("hbbldf1_i76building");
	M.main_relic = GetHandle("hbcerb1_i76building");

end

function AddObject(h)

	if ((M.nsdfmuf == nil) and (IsOdf(h,"avmu8")))
	then
		M.nsdfmuf = h;
	else
		if ((M.ccaapc == nil) and (IsOdf(h,"svapc")))
		then
			M.ccaapc = h;
		else
			if ((M.guntower1 == nil) and (IsOdf(h,"abtowe")))
			then
				M.guntower1 = h;
			else
				if ((M.guntower2 == nil) and (IsOdf(h,"abtowe")))
				then
					M.guntower2 = h;
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
		AudioMessage("misn0800.wav"); --starts opeing V.O.
		ClearObjectives();
		AddObjective("misn0800.otf", "WHITE");
		AddObjective("misn0801.otf", "WHITE");
--		SetPilot(1, 30);
		SetScrap(1,30);
		Defend(M.ccagech1);
		Defend(M.ccagech2);
		M.start_gech_time = GetTime() + 329.0; -- starts the gechs towards the base
		M.gech_spawn_time = GetTime() + 280.0; -- starts attack on M.colorado
		M.trigger_check = GetTime() + 285.0;
		M.fresh_meat_time = 100.0; -- build more units to send after player
		M.gech_check = GetTime() + 61.0; -- searches to see if the player encounters a gech
		M.first_wave_time = GetTime() + 20.0; -- starts the first wave of fighters
		SetWeaponMask(M.ccagech1, 1);
		SetWeaponMask(M.ccagech2, 1);
		SetObjectiveName(M.nav1, "Drop Zone");
		SetObjectiveName(M.nav5, "Colorado Base");
		SetObjectiveName(M.nav4, "CCA Main Base");
		M.base_check = GetTime() + 5.0;
		M.start_done = true;
	end

	if ((M.start_done) and (M.start_gech_time < GetTime()) and ( not M.gech_started)) --sets gechs into motion
	then
		Goto(M.ccagech1, "gech_path1"); 
		Goto(M.ccagech2, "gech_path2");
		M.gech_started = true;
	end
	-- this sends the first soviets into the M.user's base
	if ((M.first_wave_time < GetTime()) and ( not M.first_wave))
	then
		Goto(M.svpatrol2_2, M.nsdfrecycle);
		Goto(M.svpatrol2_3, M.nsdfrecycle);
		M.first_wave = true;
	end

	if ((M.fresh_meat_time < GetTime()) and ( not M.colorado_under_attack) and ( not M.fresh_meat))
	then
		M.cannon_fodder1 = exu.BuildAsyncObject("svfigh", 2, M.ccarecycle);
		M.cannon_fodder2 = exu.BuildAsyncObject("svfigh", 2, M.ccarecycle);
		M.cannon_fodder3 = exu.BuildAsyncObject("svfigh", 2, M.ccarecycle);
		Goto(M.cannon_fodder1, "gech_path2");
		Goto(M.cannon_fodder2, "gech_path2");
		Goto(M.cannon_fodder3, "gech_path2");
		M.fresh_meat = true;
	end

	if ((M.fighter_message_time < GetTime()) and ( not M.colorado_under_attack) and ( not M.fighter_message))
	then
		AudioMessage("misn0817.wav"); -- M.colorado: we're experiencing a lot of fighters - they know we're here - wonder what the main forces is waiting for
		M.fighter_message = true;
	end


-- M.colorado gets attacked by gech --------------------------------------------------------------------------

	if ((M.gech_spawn_time < GetTime()) and ( not M.colorado_under_attack))--gech attacks M.colorado
	then
		M.gech_spawn_time = GetTime() + 10.0;

		if (GetDistance(M.user, M.nav5) > 400.0)
		then
			M.svpatrol2_2 = exu.BuildAsyncObject("svfigh", 2, M.ccarecycle);
			M.svpatrol2_2 = exu.BuildAsyncObject("svltnk", 2, M.ccarecycle);
			M.ccagech3 = exu.BuildAsyncObject("svwalk", 2, "gech_spawn");
			SetWeaponMask(M.ccagech3, 1);
			Attack(M.ccagech3, M.colorado, 1);
			AudioMessage("misn0801.wav");-- player gets message that M.colorado is encountering hostiles "standby"
			M.colorado_message2_time = GetTime() + 10.0;

			if (IsAlive(M.svpatrol2_1))
			then
				Goto(M.svpatrol2_1, M.nav1);
			end
			if (IsAlive(M.svpatrol2_2))
			then
				Goto(M.svpatrol2_2, M.nav1);
			end
			if (IsAlive(M.svpatrol2_3))
			then
				Goto(M.svpatrol2_3, M.nav1);
			end

			M.colorado_under_attack = true;
		end
	end
	
	-- this is what happens if the player tries to get to the M.colorado before the attack - it speeds things up
	if ((M.player_nosey_time < GetTime()) and ( not M.colorado_under_attack))
	then
		M.player_nosey_time = GetTime() + 32.0;

		if (GetDistance(M.user, M.nav5) < 700.0)
		then
			M.gech_spawn_time = GetTime() + 10.0;

			if (IsAlive(M.svpatrol1_1))
			then
				Attack(M.svpatrol1_1, M.user);
			end
			if (IsAlive(M.svpatrol1_2))
			then
				Attack(M.svpatrol1_2, M.user);
			end
			if (IsAlive(M.svpatrol1_3))
			then
				Attack(M.svpatrol1_3, M.user);
			end
			if (IsAlive(M.svpatrol2_1))
			then
				Attack(M.svpatrol2_1, M.nsdfrecycle);
			end
			if (IsAlive(M.svpatrol2_2))
			then
				Attack(M.svpatrol2_2, M.nsdfrecycle);
			end
			if (IsAlive(M.svpatrol2_3))
			then
				Attack(M.svpatrol2_3, M.nsdfrecycle);
			end
		end
	end

	if ((M.colorado_under_attack) and IsAlive(M.ccagech3))
	then
		SetCurAmmo(M.ccagech3, GetMaxAmmo(M.ccagech3));	-- keep ammunition topped off so it doesn't run out
	end

	if ((M.colorado_under_attack) and (M.colorado_message2_time < GetTime()) and ( not M.colorado_message2))
	then

		AudioMessage("misn0803.wav");--second message from M.colorado
		M.colorado_message3_time = GetTime() + 7.0;
		M.colorado_message2 = true;
	end	

	if ((M.colorado_message2) and (M.colorado_message3_time < GetTime()) and ( not M.colorado_message3))
	then

		AudioMessage("misn0802.wav");--third message from M.colorado
		AudioMessage("misn0804.wav");--final message from M.colorado
		M.colorado_message4_time = GetTime() + 10.0;
		M.colorado_message3 = true;
	end

	if ((M.colorado_message4_time < GetTime()) and ( not M.kill_colorado) and  not IsAudioMessagePlaying())
	then
		M.kill_colorado = true;
	end

	if ((IsAlive(M.colorado)) and ( not M.kill_colorado))
	then
		if (GetTime()>M.next_second)
		then
			SetCurHealth(M.colorado, GetMaxHealth(M.colorado)); --prevent M.colorado from dying too early
			M.next_second = GetTime() + 1.0;
		end
	end

	if ((M.colorado_message3) and (M.kill_colorado) and ( not M.colorado_message4))
	then
		if (IsAlive(M.colorado))
		then
			Damage(M.colorado, 20000);
		end
		M.remove_nav5_time = GetTime() + 3.0;
		M.colorado_message4 = true;
	end

	if ((M.colorado_message4) and (M.remove_nav5_time < GetTime()) and ( not M.colorado_destroyed))
	then
--		RemoveObject (M.colorado);
		if (IsAlive(M.ccagech3))
		then
			Attack(M.ccagech3, M.nav5, 1);
		else
			RemoveObject (M.nav5);
		end
--		RemoveObject (M.drop);
		M.bad_news_time = GetTime() + 5.0;
		M.colorado_destroyed = true;
	end

	if ((M.colorado_destroyed) and ( not M.bad_news) and (M.bad_news_time < GetTime()))
	then
		AudioMessage("misn0805.wav");--Corbett give player news of M.colorado fate
		M.bad_news_time = GetTime() + 30.0;
		M.bad_news = true;
	end

	if ((M.bad_news) and (M.bad_news_time < GetTime()) and ( not M.gen_message))
	then
		AudioMessage("misn0810.wav");--Gen Collins give player news of M.colorado fate
		M.gen_message = true;
	end

-- end soviet attack on M.colorado ------------------------------------------------------------------------------/


-- this is going to give the soviets a recycler and start them attacking

	if ((M.bad_news) and ( not M.ccarecycle_spawned))
	then
		SetAIP("misn08.aip");		
		SetScrap(2, 40);
		SetPilot(2, 40);
		M.new_aip_time = GetTime() + 420.0;
		if (IsAlive(M.ccagech3))
		then
			Goto(M.ccagech3, "gech_path2");
		end

		if (IsAlive(M.svpatrol1_1))
		then
			Goto(M.svpatrol1_1, "cam3_spawn");
		end
		if (IsAlive(M.svpatrol1_2))
		then
			Goto(M.svpatrol1_2, "cam3_spawn");
		end
		if (IsAlive(M.svpatrol1_3))
		then
			Goto(M.svpatrol1_3, "cam3_spawn");
		end

		M.ccarecycle_spawned = true;
	end

	-- this is sending the third gech down the gech path when it gets to a certain point
--[[	if ((M.ccarecycle_spawned) and ( not M.gech3_move) and (M.gech_check_time < GetTime()))
	then
		if (GetDistance(M.ccagech3, M.stop_geyser2) < 30.0)
		then
			Goto(M.ccagech3, "gech_path2");
			M.gech3_there_time = GetTime() + 97.0;
			M.gech3_move = true;
		end
	end

--]]	

-- this is what happens when the player encounters the gech before it reaches the nav point --------------------

	if ((M.gech_check < GetTime()) and ( not M.gech_found) and ( not M.gech_at_nav))
	then
		M.gech_check = GetTime() + 6.0;

		if ((GetDistance(M.user,M.ccagech1) < 400.0) and ( not M.gech_found1) and ( not M.gech_found) and ( not M.gech_at_nav)) --if player reaches gech before gech reaches nav
		then
			AudioMessage("misn0806.wav"); -- "we're picking up something big on your radar, you may want to check it out"
			M.followup_message_time = GetTime() + 20.0; -- setting up follow up message about cca gech
			M.stumble2_check = GetTime() + 10.0;
			M.no_stumble_check = GetTime() + 13.0;
			M.gech1_there_time = 100.0;
			M.gech2_there_time = 105.0;
			M.gech_found1 = true;
			M.gech_found = true;
		end

		if ((GetDistance(M.user,M.ccagech2) < 400.0) and ( not M.gech_found) and ( not M.gech_found2) and ( not M.gech_at_nav)) --if player reaches gech before gech reaches nav
		then
			AudioMessage("misn0806.wav"); -- "we're picking up something big on your radar, you may want to check it out"
			M.followup_message_time = GetTime() + 5.0; -- setting up follow up message about cca gech
			M.stumble2_check = GetTime() + 60.0;
			M.no_stumble_check = GetTime() + 13.0;
			M.gech1_there_time = 100.0;
			M.gech2_there_time = 105.0;
			M.gech_found2 = true;
			M.gech_found = true;
		end
	end

	if ((M.gech_found) and (M.followup_message_time < GetTime()) and ( not M.followup_message))
	then
		AudioMessage("misn0807.wav"); -- "what the hell is that thing - approach with caution not "
		M.followup_message = true;
	end


	if ((M.base_check < GetTime()) and ( not M.base_set))
	then
		M.base_check = GetTime() + 2.0;

		if (IsAlive(M.nsdfmuf))
		then
			if (IsDeployed(M.nsdfmuf))
			then
				ClearObjectives();
				AddObjective("misn0800.otf", "GREEN");
				AddObjective("misn0801.otf", "WHITE");
				M.base_set = true;
			end
		end
	end


	
	-- this is what happens when the player goes and sees the gech after the first nav is dropped 

	if ((M.gech_found) and (M.stumble2_check < GetTime()) and ( not M.second_gech_warning) and ( not M.run_into_other_gech))
	then
		M.stumble2_check = GetTime() + 21.0;
		
		if ((M.gech_found1) and (GetDistance(M.user,M.ccagech2) < 100.0) and ( not M.run_into_other_gech))
		then
			AudioMessage("misn0813.wav"); --Oh no not  Looks like you've found another one not 
			M.run_into_other_gech = true;
		end

		if ((M.gech_found2) and (GetDistance(M.user,M.ccagech1) < 100.0) and ( not M.run_into_other_gech))
		then
			AudioMessage("misn0813.wav"); --Oh no not  Looks like you've found another one not 
			M.run_into_other_gech = true;
		end
	end

	-- this is when the player runs into one gech but the other gech gets half-way to base before being discovered

	if ((M.gech_found) and (M.no_stumble_check < GetTime()) and ( not M.run_into_other_gech) and ( not M.second_gech_warning))
	then
		M.no_stumble_check = GetTime() + 9.0;

		if ((M.gech_found1) and (GetDistance(M.gech_trigger2, M.ccagech2) < 100.0) and ( not M.second_gech_warning))
		then
			AudioMessage("misn0815.wav"); --V.O. looks like we've got another one coming out of the west
			M.nav2 = exu.BuildAsyncObject ("apcamr", 1, "cam2_spawn"); -- builds camera near gech
			SetObjectiveName(M.nav2, "Nav Alpha 1");
			M.second_gech_warning = true;
		end

		if ((M.gech_found2) and (GetDistance(M.gech_trigger3,M.ccagech1) < 100.0) and ( not M.second_gech_warning))
		then
			AudioMessage("misn0814.wav"); --V.O. warns player of second gech
			M.nav3 = exu.BuildAsyncObject ("apcamr", 1, "cam3_spawn"); -- builds camera near gech
			SetObjectiveName(M.nav3, "Nav Alpha 2");
			M.second_gech_warning = true;
		end
	end


-- the following occurs when the approaching gechs get half-way to the player's base

	if ((M.colorado_under_attack) and (M.trigger_check < GetTime()) and ( not M.gech_at_nav) and ( not M.gech_found))
	then
		M.trigger_check = GetTime() + 19.0;
		
		if (( not M.gech_found) and (GetDistance(M.gech_trigger2, M.ccagech2) < 100.0) and ( not M.gech_at_nav)) --if gech reaches nav before player reaches gech
		then
			AudioMessage("misn0809.wav"); -- "We've detected something strange on approach from the east - standby"
			M.gech_warning_message = GetTime() + 20.0;
			M.gech1_there_time = 100.0;
			M.gech2_there_time = 105.0;
			M.gech_at_nav = true;
			M.gech_at_nav2 = true;
		end	

		if (( not M.gech_found) and (GetDistance(M.gech_trigger3,M.ccagech1) < 100.0) and ( not M.gech_at_nav)) --if gech reaches nav before player reaches gech	
		then
			AudioMessage("misn0808.wav"); -- "We've detected something strange on approach from the west - standby"
			M.gech_warning_message = GetTime() + 20.0;
			M.gech1_there_time = 100.0;
			M.gech2_there_time = 105.0;
			M.gech_at_nav = true;
			M.gech_at_nav3 = true;
		end
	end

	if ((M.gech_at_nav2) and (M.gech_warning_message < GetTime()) and ( not M.player_warned_ofgech)) --if player ignores M.gech_at_nav message
	then
		AudioMessage("misn0814.wav"); -- Check it out - we're dropping a nav camera there now
		M.nav2 = exu.BuildAsyncObject ("apcamr", 1, "cam2_spawn"); -- builds camera near gech
		SetObjectiveName(M.nav2, "Nav Alpha 1");
		M.time_waist = GetTime() + 14.0;
		M.stumble1_check = GetTime() + 100.0;
		M.player_warned_ofgech = true;
	end

	if ((M.gech_at_nav3) and (M.gech_warning_message < GetTime()) and ( not M.player_warned_ofgech)) --if player ignores M.gech_at_nav message
	then
		AudioMessage("misn0815.wav"); -- Check it out - we're dropping a nav camera there now
		M.nav3 = exu.BuildAsyncObject ("apcamr", 1, "cam3_spawn"); -- builds camera near gech
		SetObjectiveName(M.nav3, "Nav Alpha 2");
		M.time_waist = GetTime() + 14.0;
		M.stumble1_check = GetTime() + 100.0;
		M.player_warned_ofgech = true;
	end

	-- this is the player getting warned of the second gech if he hasn't gone to see the first one yet ------------------

	if ((M.player_warned_ofgech) and (M.time_waist < GetTime()) and ( not M.second_gech_warning) and ( not M.bump_into_gech))
	then
		M.time_waist = GetTime() + 14.0;

		if ((M.gech_at_nav2) and (GetDistance(M.gech_trigger3,M.ccagech1) < 75.0) and ( not M.second_gech_warning)) --second gech found
		then
			AudioMessage("misn0812.wav");  --looks like we've got another one coming out of the east
			M.nav3 = exu.BuildAsyncObject ("apcamr", 1, "cam3_spawn"); -- builds camera near gech
			SetObjectiveName(M.nav3, "Nav Alpha 2");
			M.second_gech_warning = true;
		end

		if ((M.gech_at_nav3) and (GetDistance(M.gech_trigger2, M.ccagech2) < 75.0) and ( not M.second_gech_warning)) --second gech found
		then
			AudioMessage("misn0811.wav"); --looks like we've got another one coming out of the west
			M.nav2 = exu.BuildAsyncObject ("apcamr", 1, "cam2_spawn"); -- builds camera near gech
			SetObjectiveName(M.nav2, "Nav Alpha 1");
			M.second_gech_warning = true;
		end
	end

	-- this is what happens when the player goes and sees the gech after the first nav is dropped 

	if ((M.player_warned_ofgech) and (M.stumble1_check < GetTime()) and ( not M.second_gech_warning) and ( not M.bump_into_gech))
	then
		M.stumble1_check = GetTime() + 23.0;
		
		if ((M.gech_at_nav2) and (GetDistance(M.user,M.ccagech1) < 100.0) and ( not M.bump_into_gech))
		then
			AudioMessage("misn0813.wav"); --Oh no not  Looks like you've found another one not 
			M.bump_into_gech = true;
		end

		if ((M.gech_at_nav3) and (GetDistance(M.user,M.ccagech2) < 100.0) and ( not M.bump_into_gech))
		then
			AudioMessage("misn0813.wav"); --Oh no not  Looks like you've found another one not 
			M.bump_into_gech = true;
		end
	end


-- this makes the gechs attack the player's base when they get close enough

	if ((M.gech_found)  or  (M.gech_at_nav))
	then
		if ((M.gech1_there_time < GetTime()) and ( not M.gech1_at_base))
		then
			M.gech1_there_time = GetTime() + 30.0;
			
			if ((IsAlive(M.ccagech1)) and (GetDistance(M.ccagech1, M.stop_geyser3) < 100.0))
			then
				if (IsAlive(M.nsdfrecycle))
				then
					Attack(M.ccagech1, M.nsdfrecycle);
					if (M.gech1_blossom)
					then
						SetWeaponMask(M.ccagech1, 5);
					end
					M.gech1_at_base = true;
				else
					if (IsAlive(M.nsdfmuf))
					then
						Attack(M.ccagech1, M.nsdfmuf);
						if (M.gech1_blossom)
						then
							SetWeaponMask(M.ccagech1, 5);
						end
						M.gech1_at_base = true;
					end
				end
			end
		end

		if ((M.gech2_there_time < GetTime()) and ( not M.gech2_at_base))
		then
			M.gech2_there_time = GetTime() + 30.0;
			
			if ((IsAlive(M.ccagech2)) and (GetDistance(M.ccagech2, M.stop_geyser3) < 100.0))
			then
				if (IsAlive(M.nsdfrecycle))
				then
					Attack(M.ccagech2, M.nsdfrecycle);
					if (M.gech2_blossom)
					then
						SetWeaponMask(M.ccagech2, 5);
					end
					M.gech2_at_base = true;
				else
					if (IsAlive(M.nsdfmuf))
					then
						Attack(M.ccagech2, M.nsdfmuf);
						if (M.gech2_blossom)
						then
							SetWeaponMask(M.ccagech2, 5);
						end
						M.gech2_at_base = true;
					end
				end
			end
		end

		if ((M.gech3_there_time < GetTime()) and ( not M.gech3_at_base))
		then
			M.gech3_there_time = GetTime() + 30.0;
			
			if ((IsAlive(M.ccagech3)) and (GetDistance(M.ccagech3, M.stop_geyser3) < 100.0))
			then
				if (IsAlive(M.nsdfrecycle))
				then
					Attack(M.ccagech3, M.nsdfrecycle);
					if (M.gech3_blossom)
					then
						SetWeaponMask(M.ccagech3, 5);
					end
					M.gech3_at_base = true;
				else
					if (IsAlive(M.nsdfmuf))
					then
						Attack(M.ccagech3, M.nsdfmuf);
						if (M.gech3_blossom)
						then
							SetWeaponMask(M.ccagech3, 5);
						end
						M.gech3_at_base = true;
					end
				end
			end
		end

	end

-- now I'm loading the new attack aips if the correct amount of time has passed

	if (M.new_aip_time < GetTime())
	then
		M.new_aip_time = GetTime() + 420.0;
		
		M.units1 = CountUnitsNearObject(M.stop_geyser2, 5000.0, 1, "avfigh");
		M.units2 = CountUnitsNearObject(M.stop_geyser2, 5000.0, 1, "avtank");

		if(M.units1 > M.units2)
		then
			SetAIP("misn08b.aip");
		else
			SetAIP("misn08a.aip");
		end
	end

-- this is apc code

	if ((IsAlive(M.ccaapc)) and ( not M.apc_attack))
	then
		if (IsAlive(M.guntower1))
		then
			Attack(M.ccaapc, M.guntower1);
		else
			if (IsAlive(M.guntower2))
			then
				Attack(M.ccaapc, M.guntower2);
			else
				if (IsAlive(M.nsdfmuf))
				then
					Attack(M.ccaapc, M.nsdfmuf);
				else
					if (IsAlive(M.nsdfrecycle))
					then
						Attack(M.ccaapc, M.nsdfrecycle);
					end
				end
			end
		end

		M.apc_attack = true;
	end

	if ((M.apc_attack) and ( not IsAlive(M.ccaapc)))
	then
		M.apc_attack = false;
	end


--This is another radar comment when the player gets extrememly close to the gech
--[[	if ((M.gech_found) and ( not M.too_close_message)  or  (M.gech_at_nav) and ( not M.too_close_message))
	then
		if ((GetDistance(M.user, M.ccagech1) < 75.0) and ( not M.too_close_message))
		then
			AudioMessage("misn0816.wav"); -- pull out not  not  what the hell is that not 
			M.too_close_message = true;
		end

		if ((GetDistance(M.user, M.ccagech2) < 75.0) and ( not M.too_close_message))
		then
			AudioMessage("misn0816.wav"); -- pull out not  not  what the hell is that not 
			M.too_close_message = true;
		end
	end
--]]

	if ((M.pull_out_message < GetTime()) and ( not M.too_close_message))
	then
		AudioMessage("misn0816.wav"); -- pull out not  not  what the hell is that not 
		M.too_close_message = true;
	end


-- this will make the gechs use the popper

	if ((IsAlive(M.ccagech1)) and ( not M.gech1_blossom) and (GetHealth(M.ccagech1) < 0.25))
	then
		SetWeaponMask(M.ccagech1, 4);
		M.pull_out_message = GetTime() + 6.0;
		M.gech1_blossom = true;
	end
	
	if ((IsAlive(M.ccagech2)) and ( not M.gech2_blossom) and (GetHealth(M.ccagech2) < 0.25))
	then
		SetWeaponMask(M.ccagech2, 4);
		M.pull_out_message = GetTime() + 6.0;
		M.gech2_blossom = true;
	end
	
	if ((IsAlive(M.ccagech3)) and ( not M.gech3_blossom) and (GetHealth(M.ccagech3) < 0.25))
	then
		SetWeaponMask(M.ccagech3, 4);
		M.pull_out_message = GetTime() + 6.0;
		M.gech3_blossom = true;
	end

-- audio messages started below will have started playing by the time we get here
-- (there's a one-frame delay between calling AudioMessage and IsAudioMessagePlaying returning true)

	-- check if relic found and base destroyed
	if ( not M.won_mission and M.cerb_found and M.base_dead and  not IsAudioMessagePlaying())
	then
		SucceedMission(GetTime() + 3.0, "misn08w1.des"); --well done
		M.won_mission = true;
	end

	-- check if recycler destroyed
	if ( not M.lost_mission and M.game_over and  not IsAudioMessagePlaying())
	then
		FailMission(GetTime() + 3.0, "misn08f1.des"); --lost recycler
		M.lost_mission = true;
	end

-- this is the relic code

	if (( not M.cerb_found) and ( not M.relic_message) and ((IsInfo("hbblde") == true)  or  (IsInfo("hbbldf") == true)))
	then
		if (M.base_dead)
		then
			AudioMessage("misn0821.wav"); -- that's not it, the ruins will be much larger
			M.relic_message = true;
		else
			AudioMessage("misn0822.wav"); -- this area is crawling with relics recon as many as possible
			M.relic_message = true;
		end
	end

	if (( not M.cerb_found) and (M.cerb_check < GetTime()))
	then
		M.cerb_check = GetTime() + 3.0;

		if (GetDistance(M.user, M.main_relic) < 70.0)
		then
			if (M.base_dead)
			then
				AudioMessage("misn0818.wav"); -- well done
				AudioMessage("misn0826.wav");
				--SucceedMission(GetTime() + 30.0, "misn08w1.des"); --well done
				M.cerb_found = true;
			else
				AudioMessage("misn0819.wav"); -- this must be how they built gechs - find base
				M.cerb_found = true;
			end
		end
	end

	if (IsAlive(M.main_relic))
	then
		if (GetTime()>M.next_second2)
		then
			AddHealth(M.main_relic, 500.0);
			M.next_second2 = GetTime() + 1.0;
		end
	end


-- win/loose conditions ----------------------------/
	
	if (( not IsAlive(M.ccarecycle)) and ( not IsAlive(M.ccamuf)) and ( not M.base_dead))
	then
		if (M.cerb_found)
		then
			AudioMessage("misn0818.wav");
			AudioMessage("misn0826.wav");
			--SucceedMission(GetTime() + 30.0, "misn08w1.des"); --well done
			M.base_dead = true;
		else
			ClearObjectives();
			AddObjective("misn0801.otf", "GREEN");
			AddObjective("misn0802.otf", "WHITE");
			AudioMessage("misn0820.wav"); -- find cerbeus
			SetObjectiveOn(M.main_relic);
			SetObjectiveName(M.main_relic, "Relic Site");
			M.base_dead = true;
		end
	end

	if (( not IsAlive(M.nsdfrecycle)) and ( not M.game_over))
	then
		AudioMessage("misn0421.wav");
		M.game_over = true;
	end

-- END OF SCRIPT
	
end