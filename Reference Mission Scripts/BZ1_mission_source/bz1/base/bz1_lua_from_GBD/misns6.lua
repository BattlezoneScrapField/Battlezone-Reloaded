-- Single Player CCA Mission 6 Lua conversion, created by General BlackDragon. 

-- Single Table for all our save/load variables. This SP mission has too many variables to function with them independently. ("main function has > 200 local variables", or "Load having > 197 variables in assignment")
local M = {

-- bools
	won = false,
	lost = false,
	last_objective = false,
	start_done = false,
	--won_message = false,
	--lost_message = false,
	warning = false,
	--base_suggestion = false,
	art_found = false,
	counter1 = false,
	counter2 = false,
	counter3 = false,
	counter4 = false,
	counter5 = false,
	counter_attack = false,
-- Floats (really doubles in Lua)
	check_time = 0,
	check1 = 0,
	check2 = 0,
	check3 = 0,
	check4 = 0,
	aip_time = 0,
-- Handles
	--beacon = nil,
	goal = nil,
	art1 = nil,
	art2 = nil,
	tur1 = nil,
	tur2 = nil,
	tur3 = nil,
	tur4 = nil,
	far_silo = nil,
	recy = nil,
	miners = { }, --[6] = nil,
-- Ints
	next_target = 0,
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

	M.aip_time = 99999.0;
	
end

function AddObject(h)

	local closest;
	if (
		(GetTeamNum(h) == 2)  and 
		(IsOdf(h, "avmine"))
		)
	then
		local min_dist = 99999.0;
		local temp = GetDistance(h,"m1",1);
		if (temp < min_dist)
		then
			closest = 0;
			min_dist = temp;
			Goto(h,"s1",1);
		end
		temp = GetDistance(h,"m2",1);
		if (temp < min_dist)
		then
			closest = 1;
			min_dist = temp;
			Goto(h,"s2",1);
		end
		temp = GetDistance(h,"m3",1);
		if (temp < min_dist)
		then
			closest = 2;
			min_dist = temp;
			Goto(h,"s3",1);
		end
		
		M.miners[closest] = h;
		M.next_target = closest;
	end

end

function Update()

-- START OF SCRIPT

	--local count;
	local player = GetPlayerHandle();
	if ( not M.start_done)
	then
		M.next_target = 0;
--		BuildObject("svrecy",1,"spawn1");
		local cam1 = GetHandle("spcamr0_camerapod");
		SetObjectiveName(cam1, "Black Dog Base");
		M.aip_time = GetTime()+120.0;
		BuildObject("avmine",2,"m1");
		BuildObject("avmine",2,"m2");
		BuildObject("avmine",2,"m3");
		M.goal = GetHandle("abcafe8_i76building");
		M.art1 = GetHandle("avartl3_howitzer");
		M.art2 = GetHandle("avartl4_howitzer");
		M.tur1 = GetHandle("avturr0_turrettank");
		M.tur2 = GetHandle("avturr1_turrettank");
		M.tur3 = GetHandle("defender1");
		M.tur4 = GetHandle("defender2");
		M.recy = GetHandle("svrecy0_recycler");
		M.far_silo = GetHandle("absilo0_scrapsilo");
		Defend(M.art1,1);
		Defend(M.art2,1);
		Defend(M.tur3,1);
		Defend(M.tur4,1);
		Defend(M.tur1,1);
		Defend(M.tur2,1);
		SetScrap(1,20);
		M.check_time = GetTime()+10.0;
		AudioMessage("misns601.wav");
		ClearObjectives();
		AddObjective("misns601.otf","WHITE");
		AddObjective("misns602.otf","WHITE");
		M.start_done = true;
	end
	if (( not M.warning)  and 
		((GetDistance(player,"m1",1)<250) 
		 or  (GetDistance(player,"m2",1)<250) 
		 or  (GetDistance(player,"m3",1)<250)))
	then
		AudioMessage("misns602.wav");
		M.warning = true;
	end
	if (GetTime()>M.aip_time)
	then
		SetAIP("misns6.aip");
		M.aip_time = 99999.0;
	end
	if (GetTime()>M.check_time) 
	then
		for count = 1, 3 do 
			-- if (what == CMD_NONE)
			--   Attack(friend1, enemy1);
			if (IsAlive(M.miners[count]))
			then
				
				if ((GetLastEnemyShot(M.miners[count])>0) and ( not M.counter1))
				then
					M.counter1 = true;
					local a1 = BuildObject("bvraz",2,"counter1");
					local a2 = BuildObject("bvraz",2,"counter2");
					Attack(a1,player);
					Attack(a2,player);
				end

				local what = GetCurrentCommand(M.miners[count]);
				if (what == AiCommand.NONE)
				then
					if (M.next_target == 0)	then
						Mine(M.miners[count],"s1",1);
					elseif (M.next_target == 1) then
						Mine(M.miners[count],"s2",1);
					elseif (M.next_target == 2) then
						Mine(M.miners[count],"s3",1);
					elseif (M.next_target == 3) then
						Mine(M.miners[count],"m1",1);
					elseif (M.next_target == 4) then
						Mine(M.miners[count],"m2",1);
					elseif (M.next_target == 5) then
						Mine(M.miners[count],"m3",1);
					end
					M.next_target = M.next_target + 1;
					if (M.next_target>5) then 
						M.next_target = 0;
					end
				end
			end
			M.check_time = GetTime()+3.0;

		end
	end
	
	if (( not M.counter2) and (GetTime()>M.check1))
	then
		if (GetDistance(player,"counter2")<400.0)
		then
			BuildObject("bvtank",2,"counter2");
			BuildObject("bvtank",2,"counter2");
			BuildObject("bvturr",2,"counter2");
			M.check1 = M.check1+300.0;
		else 
			M.check1 = GetTime()+3.0;
		end
	end
	if (( not M.counter3) and (GetTime()>M.check2))
	then
		if (GetDistance(player,"counter3")<400.0)
		then
			BuildObject("bvtank",2,"counter3");
			BuildObject("bvtank",2,"counter3");
			BuildObject("bvturr",2,"counter3");
			M.check2 = M.check2+300.0;
		else 
			M.check2 = GetTime()+3.0;
		end
	end
	if (( not M.counter4) and (GetTime()>M.check3))
	then
		if (GetDistance(player,"counter4")<200.0)
		then
			BuildObject("bvtank",2,"counter4");
			BuildObject("bvtank",2,"counter4");
			BuildObject("bvturr",2,"counter4");
			M.check3 = GetTime()+300.0;
		else 
			M.check3 = GetTime()+3.0;
		end
	end
	if (( not M.counter5) and (GetTime()>M.check4))
	then
		if (GetDistance(player,"counter5")<200.0)
		then
			BuildObject("bvtank",2,"counter5");
			BuildObject("bvtank",2,"counter5");
			BuildObject("bvturr",2,"counter5");
			M.check4 = GetTime()+300.0;
		else 
			M.check4 = GetTime()+3.0;
		end
	end
	if (( not M.art_found) and 
		 ((GetDistance(player,M.art1)<200.0)  or  
		  (GetDistance(player,M.art2)<200.0)))
	then
		M.art_found = true;
		AudioMessage("misns605.wav");
	end
	if (( not M.counter_attack) and (GetDistance(M.far_silo,player)<400.0))
	then
		local temp = BuildObject("bvltnk",2,"counter_attack");
		Goto(temp,"counter_attack_path",1);
		temp = BuildObject("bvltnk",2,"counter_attack");
		Goto(temp,"counter_attack_path",1);
		temp = BuildObject("bvtank",2,"counter_attack");
		Goto(temp,"counter_attack_path",1);
		temp = BuildObject("bvtank",2,"counter_attack");
		Goto(temp,"counter_attack_path",1);
		temp = BuildObject("bvrckt",2,"counter_attack");
		Goto(temp,"counter_attack_path",1);
		AudioMessage("misns603.wav");
		M.counter_attack = true;
	end
	--[[
		If the player
		is close to the last objective
		make it the 
		objective.
	--]]
	if (( not M.last_objective) and (GetDistance(player,M.goal)<300.0))
	then
		ClearObjectives();
		AddObjective("misns601.otf","GREEN");
		AddObjective("misns602.otf","WHITE");
		M.last_objective = true;
		SetObjectiveOn(M.goal);
	end
	if (( not M.won) and ( not IsAlive(M.goal)))
	then
		M.audmsg = AudioMessage("misns609.wav");
		--M.won_message = true;
		M.won = true;
	end
	if ((M.won) and (IsAudioMessageDone(M.audmsg)))
	then
		SucceedMission(GetTime()+0.0,"misns6w1.des");
		M.won = false;
	end
	if (( not M.won) and ( not M.lost) and ( not IsAlive(M.recy)))
	then
		M.lost = true;
		FailMission(GetTime()+2.0,"misns6l1.des");
	end

-- END OF SCRIPT
	
end