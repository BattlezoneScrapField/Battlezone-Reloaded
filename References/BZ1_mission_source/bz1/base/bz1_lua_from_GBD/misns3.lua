-- Single Player CCA Mission 3 Lua conversion, created by General BlackDragon. 

-- Single Table for all our save/load variables. This SP mission has too many variables to function with them independently. ("main function has > 200 local variables", or "Load having > 197 variables in assignment")
local M = {

-- bools
	economy1 = false,
	economy2 = false,
	economy3 = false,
	economy4 = false,
	unit1spawned = false,
	unit2spawned = false,
	unit3spawned = false,
	newobjective = false,
	unit4spawned = false,
	bdspawned2 = false,
	missionstart = false,
	missionwon = false,
	missionfail = false,
	bdspawned = false,
	recyclerdestroyed = false,
	warn1 = false,
	warn2 = false,
	plea1 = false,
	plea2 = false,
	plea3 = false,
	mark1 = false,
	play = false,
	minefield1 = false,
	minefield2 = false,
	minefield3 = false,
	patrolspawned = false,
-- Floats (really doubles in Lua)
	withdraw = 0,
	help1 = 0,
	help2 = 0,
	help3 = 0,
	Checkdist = 0,
	Checkdist2 = 0,
	Checkalive = 0,
-- Handles
	bd1 = nil,
	bd2 = nil,
	bd3 = nil,
	bd4 = nil,
	bd5 = nil,
	--bd6 = nil,
	--bd7 = nil,
	--bd8 = nil,
	--bd9 = nil,
	--bd10 = nil,
	--bd11 = nil,
	--bd12 = nil,
	bd50 = nil,
	bd60 = nil,
	bd70 = nil,
	bd80 = nil,
	bd51 = nil,
	bd52 = nil,
	bd61 = nil,
	bd62 = nil,
	bd71 = nil,
	bd72 = nil,
	bd81 = nil,
	bd82 = nil,
	avrec = nil,
	player = nil,
	bomb1 = nil,
	bomb2 = nil,
	bomb3 = nil,
	bomb4 = nil,
	pat1 = nil,
	pat2 = nil,
	Enemy1 = nil,
	Enemy2 = nil,
	cam1 = nil,
	cam2 = nil,
-- Ints
	--audmsg = 0,
	aud1 = 0,
	aud2 = 0,
	aud50 = 0
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

	M.withdraw = 99999.0;
	M.help1 = 9999999.0;
	M.help2 = 9999999.0;
	M.help3 = 9999999.0;
	M.Checkdist = 9999999999999.0;
	M.Checkdist2 = 999999999999999.0;
	M.Checkalive = 9999999999.0;

end

function AddObject(h)


end

function Update()

-- START OF SCRIPT

	if
		(M.missionstart == false)
	then
		AudioMessage("misns301.wav");
		M.newobjective = true;
		M.missionstart = true;
		M.avrec = GetHandle("avrecy1_recycler");
		M.player = GetPlayerHandle();
		M.withdraw = GetTime() + 600.0;
		M.help1 = GetTime () + 120.0;
		M.help2 = GetTime () + 280.0;
		M.help3 = GetTime () + 380.0;
		M.Checkdist = GetTime() + 5.0;
		M.Checkdist2 = GetTime() + 5.0;
		M.Checkalive = GetTime() + 15.0;
		M.bomb1 = GetHandle("bomb1");
		M.bomb2 = GetHandle("bomb2");
		M.bomb3 = GetHandle("bomb3");
		M.bomb4 = GetHandle("bomb4");
		M.cam1 = GetHandle("basenav");
		M.cam2 = GetHandle("avrecy");
		SetObjectiveName(M.cam1, "Home Base");
		SetObjectiveName(M.cam2, "Black Dog Outpost");
	end
	M.player = GetPlayerHandle();

	if
		(M.newobjective == true)
	then
		ClearObjectives();
		if
			(M.recyclerdestroyed == true)
		then
			
			AddObjective("misns302.otf", "WHITE");
			AddObjective("misns301.otf", "GREEN");
		end
		if
			(M.recyclerdestroyed == false)
		then
			AddObjective("misns301.otf", "WHITE");
		end
		if
			(M.missionwon == true)
		then
			AddObjective("misns302.otf", "GREEN");
		end
		M.newobjective = false;
	end
	if
		(
		(M.help1 < GetTime()) and (M.plea1 == false)
		 and  (M.recyclerdestroyed == false)
		)
	then
		AudioMessage("misns307.wav");
		M.plea1 = true;
	end
	if
		(
		(M.help2 < GetTime()) and (M.plea2 == false)
		 and  (M.recyclerdestroyed == false)
		)
	then
		AudioMessage("misns308.wav");
		M.plea2 = true;
	end
	if
		(
		(M.help3 < GetTime()) and (M.plea3 == false)
		 and  (M.recyclerdestroyed == false)
		)
	then
		AudioMessage("misns309.wav");
		M.plea3 = true;
	end

	if 
		(
		(IsAlive(M.avrec)) and (GetDistance (M.player, "bdspawntrig") < 200.0)
		 and  (M.bdspawned == false)
		)
	then
		M.bd1 = BuildObject ("avtank", 2, "bdspawn1");
		M.bd2 = BuildObject ("avtank", 2, "bdspawn1");
		M.bd3 = BuildObject ("avtank", 2, "bdspawn1");
		M.bd4 = BuildObject ("avfigh", 2, "bdspawn1");
		M.bd5 = BuildObject ("avfigh", 2, "bdspawn1");
		Attack(M.bd1, M.player);
		Attack(M.bd2, M.player);
		Attack(M.bd3, M.player);
		Attack(M.bd4, M.player);
		Attack(M.bd5, M.player);
		M.bdspawned = true;
		AudioMessage("misns310.wav");
	end

	if
		(M.bdspawned == true)
	then
		IsAlive(M.bd1);
		IsAlive(M.bd1);
		IsAlive(M.bd1);
		IsAlive(M.bd1);
		IsAlive(M.bd1);
	end

	if
		(
		(M.bdspawned == true) and (M.Checkalive < GetTime())
		)
	then
		if
			(IsAlive(M.bd1))
		then
			Attack(M.bd1, M.player);
		end
		if
			(IsAlive(M.bd2))
		then
			Attack(M.bd2, M.player);
		end
		if
			(IsAlive(M.bd3))
		then
			Attack(M.bd3, M.player);
		end
		if
			(IsAlive(M.bd4))
		then
			Attack(M.bd4, M.player);
		end
		if
			(IsAlive(M.bd5))
		then
			Attack(M.bd5, M.player);
		end
		if
			(
			( not IsAlive(M.bd1))  and 
			( not IsAlive(M.bd2))  and 
			( not IsAlive(M.bd3))  and 
			( not IsAlive(M.bd4))  and 
			( not IsAlive(M.bd5))
			)
		then
		M.bd1 = BuildObject ("avtank", 2, "bdspawn1");
		M.bd2 = BuildObject ("avtank", 2, "bdspawn1");
		M.bd3 = BuildObject ("avtank", 2, "bdspawn1");
		M.bd4 = BuildObject ("avfigh", 2, "bdspawn1");
		M.bd5 = BuildObject ("avfigh", 2, "bdspawn1");
		end
		M.Checkalive = GetTime() + 8.0;
	end
		

	if
		(
		( not IsAlive(M.avrec)) and (M.recyclerdestroyed == false)
		)
	then
		AudioMessage("misns302.wav");
		if
			(M.bdspawned2 == false)
		then
		M.bd50 =  BuildObject ("avtank", 2, "bdspawn1");
		M.bd60 = BuildObject ("avfigh", 2, "bdspawn1");
		M.bd70 = BuildObject ("avfigh", 2, "bdspawn1");
		M.bd80 = BuildObject ("avtank", 2, "bdspawn1");
		Goto (M.bd50, "bdpath1");
		Goto (M.bd60, "bdpath2");
		Goto (M.bd70, "bdpath3");
		Goto (M.bd80, "bdpath4");
		M.bdspawned2 = true;
		M.bdspawned = false;
		end
		M.economy1 = true;
		M.economy2 = true;
		M.economy3 = true;
		M.economy4 = true;
		M.recyclerdestroyed = true;
		M.newobjective = true;
	end

	if
		(
		(M.economy1 == true) and (GetDistance(M.player, M.bd50) < 410.0)
		 and  (M.unit1spawned == false)
		)
	then
		M.bd51 = BuildObject ("avtank", 2, M.bd50);
		M.bd52 = BuildObject ("avtank", 2, M.bd50);
		Follow (M.bd51, M.bd50);
		Follow (M.bd52, M.bd50);
		M.unit1spawned = true;
	end

	if
		(
		(M.economy2 == true) and (GetDistance(M.player, M.bd60) < 410.0)
		 and  (M.unit2spawned == false)
		)
	then
		M.bd61 = BuildObject ("avfigh", 2, M.bd60);
		M.bd62 = BuildObject ("avfigh", 2, M.bd60);
		Follow (M.bd61, M.bd60);
		Follow (M.bd62, M.bd60);
		M.unit2spawned = true;
	end

	if
		(
		(M.economy3 == true) and (GetDistance(M.player, M.bd70) < 410.0)
		 and  (M.unit3spawned == false)
		)
	then
		M.bd71 = BuildObject ("avfigh", 2, M.bd70);
		M.bd72 = BuildObject ("avtank", 2, M.bd70);
		Follow (M.bd71, M.bd70);
		Follow (M.bd72, M.bd70);
		M.unit3spawned = true;
	end

	if
		(
		(M.economy4 == true) and (GetDistance(M.player, M.bd80) < 410.0)
		 and  (M.unit4spawned == false)
		)
	then
		M.bd81 = BuildObject ("avtank", 2, M.bd80);
		M.bd82 = BuildObject ("avtank", 2, M.bd80);
		Follow (M.bd81, M.bd80);
		Follow (M.bd82, M.bd80);
		M.unit4spawned = true;
	end


	if
		(
		(GetDistance(M.player, "homesweethome") < 200.0) and 
		(M.missionwon == false) and 
		(M.recyclerdestroyed == true)
		)
	then
		M.aud50 = AudioMessage ("misns303.wav");
		M.missionwon = true;
	end

	if
		(
		(M.missionwon == true) and 
		(IsAudioMessageDone(M.aud50))
		)
	then
		SucceedMission (GetTime() + 0.0, "misns3w1.des");
	end

	if
		(
		(M.withdraw < GetTime()) and 
		(M.recyclerdestroyed == false)  and 
		(M.missionfail == false)
		)
	then
		M.aud2 = AudioMessage("misns304.wav");
		M.missionfail = true;
	end
	if
		(
		(M.missionfail == true) and (IsAudioMessageDone(M.aud2))
		)
	then
		FailMission (GetTime(), "misns3l1.des");
	end


	if 
		(
		(GetDistance (M.player, "don'tgohere") < 50.0)  and 
		(M.warn1 == false) and (M.recyclerdestroyed == false)
		)
	then
		AudioMessage ("misns305.wav");
		M.warn1 = true;
	end

	if
		(
		(GetDistance (M.player, "iwarnedyou") < 50.0)  and 
		(M.warn2 == false) and (M.recyclerdestroyed == false)
		)
	then
		M.aud1 = AudioMessage ("misns306.wav");
		M.warn2 = true;
	end

	if
		(
		(M.warn2 == true) and (IsAudioMessageDone(M.aud1))
		)
	then
		FailMission (GetTime(), "misns3l2.des");
	end


	if
		(M.patrolspawned == false)
	then

		if
			(
			(M.bdspawned == false) and (IsAlive(M.avrec))
			)
		then
			if
				(M.Checkdist < GetTime())
			then
					if
						(
						(GetDistance (M.bomb1, "patroltrig1") < 100.0)  or 
						(GetDistance (M.bomb2, "patroltrig1") < 100.0)  or 
						(GetDistance (M.bomb3, "patroltrig1") < 100.0)  or 
						(GetDistance (M.bomb4, "patroltrig1") < 100.0)  or 
						(GetDistance (M.player, "patroltrig1") < 100.0)
						)
					then
						M.pat1 = BuildObject("bvraz", 2, "patrolspawn1");
						M.pat2 = BuildObject("bvraz", 2, "patrolspawn1");
						AudioMessage("misns219.wav");
						Goto(M.pat1, "patrolpath1");
						Goto(M.pat2, "patrolpath1");
						SetIndependence(M.pat1, 0);
						SetIndependence(M.pat2, 0);
						M.patrolspawned = true;
					end
					if
						(
						(GetDistance (M.bomb1, "patroltrig2") < 100.0)  or 
						(GetDistance (M.bomb2, "patroltrig2") < 100.0)  or 
						(GetDistance (M.bomb3, "patroltrig2") < 100.0)  or 
						(GetDistance (M.bomb4, "patroltrig2") < 100.0)  or 
						(GetDistance (M.player, "patroltrig2") < 100.0)
						)
					then
						M.pat1 = BuildObject("bvraz", 2, "patrolspawn2");
						M.pat2 = BuildObject("bvraz", 2, "patrolspawn2");
						AudioMessage("misns219.wav");
						Goto(M.pat1, "patrolpath2");
						Goto(M.pat2, "patrolpath2");
						SetIndependence(M.pat1, 0);
						SetIndependence(M.pat2, 0);
						M.patrolspawned = true;
					end
					M.Checkdist = GetTime() + 3.0;
			end
		end
	end

	if
		(
		(M.mark1 == false)  and 
		(M.patrolspawned == true) and (M.bdspawned == false)
		)
	then
		M.Enemy1 = GetNearestEnemy(M.pat1);
		M.Enemy2 = GetNearestEnemy(M.pat2);
		if
			(M.Checkdist2 < GetTime())
		then
			if

				(GetDistance(M.pat1, M.Enemy1) < 180.0)
			then
				M.bdspawned = true;
				Attack(M.pat1, M.Enemy1);
				Attack(M.pat2, M.Enemy1);
				M.play = true;
			end
			if
				(GetDistance(M.pat2, M.Enemy2) < 180.0)
			then
				M.bdspawned = true;
				Attack(M.pat2, M.Enemy2);
				Attack(M.pat1, M.Enemy2);
				M.play = true;
			end
			M.Checkdist2 = GetTime() + 3.0;
			if
				(
				(M.play == true) and (M.mark1 == false)
				)
			then
				AudioMessage("misns220.wav");
				M.mark1 = true;
			end
		end
	end

	if
		(
		(M.minefield1 == false)   and 
		(
		(GetDistance(M.player, "minetrig1") < 200.0)  or 
		(GetDistance(M.player, "minetrig1b") < 200.0)
		)
		)
	then
		BuildObject("proxmine", 2, "path_1");
		BuildObject("proxmine", 2, "path_2");
		BuildObject("proxmine", 2, "path_3");
		BuildObject("proxmine", 2, "path_4");
		BuildObject("proxmine", 2, "path_5");
		BuildObject("proxmine", 2, "path_6");
		BuildObject("proxmine", 2, "path_7");
		BuildObject("proxmine", 2, "path_8");
		BuildObject("proxmine", 2, "path_9");
		BuildObject("proxmine", 2, "path_10");
		BuildObject("proxmine", 2, "path_11");
		M.minefield1 = true;
	end
	if
		(
		(M.minefield2 == false)   and 
		(
		(GetDistance(M.player, "minetrig2") < 200.0)  or 
		(GetDistance(M.player, "minetrig2b") < 200.0)
		)
		)
	then
		BuildObject("proxmine", 2, "path_12");
		BuildObject("proxmine", 2, "path_13");
		BuildObject("proxmine", 2, "path_14");
		BuildObject("proxmine", 2, "path_15");
		BuildObject("proxmine", 2, "path_16");
		BuildObject("proxmine", 2, "path_17");
		BuildObject("proxmine", 2, "path_18");
		BuildObject("proxmine", 2, "path_19");
		BuildObject("proxmine", 2, "path_20");
		BuildObject("proxmine", 2, "path_21");
		BuildObject("proxmine", 2, "path_22");
		M.minefield2 = true;
	end
	if
		(
		(M.minefield3 == false)   and 
		(
		(GetDistance(M.player, "minetrig3") < 200.0)  or 
		(GetDistance(M.player, "minetrig3b") < 200.0)
		)
		)
	then
		BuildObject("proxmine", 2, "path_23");
		BuildObject("proxmine", 2, "path_24");
		BuildObject("proxmine", 2, "path_25");
		BuildObject("proxmine", 2, "path_26");
		BuildObject("proxmine", 2, "path_27");
		BuildObject("proxmine", 2, "path_28");
		BuildObject("proxmine", 2, "path_29");
		BuildObject("proxmine", 2, "path_30");
		BuildObject("proxmine", 2, "path_31");
		BuildObject("proxmine", 2, "path_32");
		BuildObject("proxmine", 2, "path_33");
		BuildObject("proxmine", 2, "path_34");
		M.minefield3 = true;
	end


-- END OF SCRIPT
	
end