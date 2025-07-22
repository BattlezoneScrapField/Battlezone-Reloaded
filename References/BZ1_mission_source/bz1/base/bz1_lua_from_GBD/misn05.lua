-- Single Player NSDF Mission 4 Lua conversion, created by General BlackDragon. 

-- Single Table for all our save/load variables. This SP mission has too many variables to function with them independently. ("main function has > 200 local variables", or "Load having > 197 variables in assignment")
local M = {

-- bools
	game_start = false,
	reconfactory = false,
	lemnossecure = false,
	missionwon = false,
	missionfail = false,
	neworders = false,
	--ob1 = false,
	--ob2 = false,
	--ob3 = false,
	--ob4 = false,
	basewave = false,
	attacktimeset = false,
	--failmission = false,
	sent1Done = false,
	sent2Done = false,
	sent3Done = false,
	sent4Done = false,
	go = false,
	shuffle = false,
	notfound = false,
	attackstatement = false,
	mine1built = false,
	mine2built = false,
	mine3built = false,
	mine4built = false,
	mine5built = false,
	mine6built = false,
	mine7built = false,
	mine8built = false,
	mine9built = false,
	mine10built = false,
	mine11built = false,
	mine12built = false,
	mine13built = false,
	mine14built = false,
	mine15built = false,
	mine16built = false,
	mine17built = false,
	mine18built = false,
	mine19built = false,
	mine20built = false,
	mine21built = false,
	mine22built = false,
	mine23built = false,
	mine24built = false,
	attackcmd = false,
	check1 = false,
	check2 = false,
	check3 = false,
	check4 = false,
	aw1sent = false,
	aw2sent = false,
	aw3sent = false,
	aw4sent = false,
	aw1aattack = false,
	aw2aattack = false,
	aw3aattack = false,
	aw4aattack = false,
	aw5aattack = false,
	aw6aattack = false,
	aw7aattack = false,
	aw8aattack = false,
	aw9aattack = false,
	possiblewin = false,
	takeoutfactory = false,
	lemcin1 = false,
	lemcin2 = false,
	reconed = false,
	needtospawn = false,
	newobjective = false,
-- Floats (really doubles in Lua)
	--processtime = 0,
	sendTime = { }, --[4] = 0,
	platoonhere = 0,
	mine1 = 0,
	mine2 = 0,
	mine3 = 0,
	mine4 = 0,
	mine5 = 0,
	mine6 = 0,
	mine7 = 0,
	mine8 = 0,
	mine9 = 0,
	mine10 = 0,
	mine11 = 0,
	mine12 = 0,
	mine13 = 0,
	mine14 = 0,
	mine15 = 0,
	mine16 = 0,
	mine17 = 0,
	mine18 = 0,
	mine19 = 0,
	mine20 = 0,
	mine21 = 0,
	mine22 = 0,
	mine23 = 0,
	mine24 = 0,
	bombtime = 0,
	lemcinstart = 0,
	lemcinend = 0,
	aw1t = 0,
	aw2t = 0,
	start = 0,
	aw3t = 0,
	aw4t = 0,
	readtime = 0,
	randomwave = 0,
-- Handles
	lemnos = nil,
	player = nil,
	svrec = nil,
	avrec = nil,
	wBu1 = nil,
	wBu2 = nil,
	wBu3 = nil,
	w1u1 = nil,
	w1u2 = nil,
	w1u3 = nil,
	w1u4 = nil,
	w2u1 = nil,
	w2u2 = nil,
	w2u3 = nil,
	w2u4 = nil,
	w3u1 = nil,
	w3u2 = nil,
	w3u3 = nil,
	w3u4 = nil,
	w4u1 = nil,
	w4u2 = nil,
	w4u3 = nil,
	w4u4 = nil,
	rand1 = nil,
	rand2 = nil,
	rand3 = nil,
	MINE1 = nil,
	MINE2 = nil,
	MINE3 = nil,
	MINE4 = nil,
	MINE5 = nil,
	MINE6 = nil,
	MINE7 = nil,
	MINE8 = nil,
	MINE9 = nil,
	MINE10 = nil,
	MINE11 = nil,
	MINE12 = nil,
	MINE13 = nil,
	MINE14 = nil,
	MINE15 = nil,
	MINE16 = nil,
	MINE17 = nil,
	MINE18 = nil,
	MINE19 = nil,
	MINE20 = nil,
	MINE21 = nil,
	MINE22 = nil,
	MINE23 = nil,
	MINE24 = nil,
	aw1 = nil,
	aw2 = nil,
	aw3 = nil,
	aw4 = nil,
	aw5 = nil,
	cam1 = nil,
	aw1a = nil,
	aw2a = nil,
	aw3a = nil,
	aw4a = nil,
	aw5a = nil,
	aw6a = nil,
	aw7a = nil,
	aw8a = nil,
	aw9a = nil,
-- Ints
	attacksent = 0
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

	M.start = 99999999999999.0;
	M.needtospawn = true;
	M.randomwave = 99999999.0;
	M.readtime = 99999999999.0;
	M.aw1t = 99999999999.0;
	M.aw2t = 99999999999.0;
	M.aw3t = 99999999999.0;
	M.aw4t = 99999999999.0;
	M.platoonhere = 99999999999999.0;
	M.sendTime[0] = 99999999.0;
	M.sendTime[1] = 99999999.0;
	M.sendTime[2] = 99999999.0;
	M.sendTime[3] = 99999999.0;
	M.lemcinstart = 99999999.0;
	M.lemcinend = 999999999.0;

end

function AddObject(h)


end

function Update()

-- START OF SCRIPT

	local i;

	--[[
		Here is where you 
		put what happens 
		every frame.  
	--]]
	if ( not M.game_start)
	then
		SetScrap(1,20);
		SetScrap(2,20);
		M.lemnos = GetHandle("oblema110_i76building");
		M.svrec = GetHandle("svrecy-1_recycler");
		M.avrec = GetHandle("avrecy-1_recycler");
		SetAIP("misn05.aip");
		AudioMessage ("misn0501.wav");
		M.game_start = true;
		M.mine1 = GetTime() + 2.0;
		M.mine2 = GetTime() + 2.0;
		M.mine3 = GetTime() + 2.0;
		M.mine4 = GetTime() + 2.0;
		M.mine5 = GetTime() + 2.0;
		M.mine6 = GetTime() + 2.0;
		M.mine7 = GetTime() + 2.0;
		M.mine8 = GetTime() + 2.0;
		M.mine9 = GetTime() + 2.0;
		M.mine10 = GetTime() + 2.0;
		M.mine11 = GetTime() + 2.0;
		M.mine12 = GetTime() + 2.0;
		M.mine13 = GetTime() + 2.0;
		M.mine14 = GetTime() + 2.0;
		M.mine15 = GetTime() + 2.0;
		M.mine16 = GetTime() + 2.0;
		M.mine17 = GetTime() + 2.0;
		M.mine18 = GetTime() + 2.0;
		M.mine19 = GetTime() + 2.0;
		M.mine20 = GetTime() + 2.0;
		M.mine21 = GetTime() + 2.0;
		M.mine22 = GetTime() + 2.0;
		M.mine23 = GetTime() + 2.0;
		M.mine24 = GetTime() + 2.0;
		M.randomwave = GetTime() + 1.0;
		M.cam1 = GetHandle("cam1");
		SetObjectiveName(M.cam1, "Volcano");
		M.newobjective = true;
	end
	M.player = GetPlayerHandle();
	--NoEscorts();

	if
		(M.newobjective == true)
	then
		ClearObjectives();
		if
			(M.missionwon == true)
		then
			AddObjective("misn0502.otf", "GREEN");
		end
		if
			(
			(M.neworders == true) and (M.missionwon == false)
			)
		then
			AddObjective("misn0502.otf", "WHITE");
		end
		if
			(M.neworders == true)
		then
			AddObjective("misn0503.otf", "GREEN");
		end
		if
			(
			(M.reconfactory == true) and (M.neworders == false)
			)
		then
			AddObjective("misn0503.otf", "WHITE");
		end

		if
			(M.reconfactory == true)
		then
			AddObjective("misn0501.otf", "GREEN");
		end
		if
			(M.reconfactory == false)
		then
			AddObjective("misn0501.otf", "WHITE");
		end
		M.newobjective = false;
	end
			

	if
		(M.reconed == false)
	then
	if
		(M.needtospawn == true)
	then
		if
			(
			(M.randomwave < GetTime()) and (IsAlive(M.svrec))
			)
		then
			M.rand1 = exu.BuildAsyncObject("svfigh",2,M.svrec);
			M.rand2 = exu.BuildAsyncObject("svfigh",2,M.svrec);
			--M.rand3 = BuildObject("svfigh",2,M.svrec);
			Attack (M.rand1, M.avrec);
			Attack (M.rand2, M.avrec);
			--Attack (M.rand3, M.avrec);
			SetIndependence(M.rand1, 1);
			SetIndependence(M.rand2, 1);
			--SetIndependence(M.rand3, 1);
			M.needtospawn = false;
		end
	end

	if
		(M.needtospawn == false)
	then
		if
			(
			( not IsAlive(M.rand1))  and 
			( not IsAlive(M.rand2)) -- and 
			--( not IsAlive(M.rand3)) 
			)
		then
			M.needtospawn = true;
		end
	end
	end

	if (M.mine1built)
	then
		local meat = GetNearestVehicle ("path_1" ,1);
		if (GetDistance(meat, "path_1") > 400.0)
		then
			M.mine1 = GetTime() + 3.0;
			M.mine1built = false;
			RemoveObject (M.MINE1);
		end
	else
		if (M.mine1 < GetTime()) then
			local meat = GetNearestVehicle ("path_1" ,1);
			if (GetDistance(meat, "path_1") < 400.0)
			then
				M.MINE1 = exu.BuildAsyncObject ("boltM.mine", 2, "path_1");
				M.mine1built = true;
			end
		end
	end
	if (M.mine2built)
	then
		local meat = GetNearestVehicle ("path_2" ,1);
		if (GetDistance(meat, "path_2") > 400.0)
		then
			M.mine2 = GetTime() + 3.0;
			M.mine2built = false;
			RemoveObject (M.MINE2);
		end
	else
		if (M.mine2 < GetTime()) then
			local meat = GetNearestVehicle ("path_2" ,1);
			if (GetDistance(meat, "path_2") < 400.0)
			then
				M.MINE2 = exu.BuildAsyncObject ("boltM.mine", 2, "path_2");
				M.mine2built = true;
			end
		end
	end
	if (M.mine3built)
	then
		local meat = GetNearestVehicle ("path_3" ,1);
		if (GetDistance(meat, "path_3") > 400.0)
		then
			M.mine3 = GetTime() + 3.0;
			M.mine3built = false;
			RemoveObject (M.MINE3);
		end
	else
		if (M.mine3 < GetTime()) then
			local meat = GetNearestVehicle ("path_3" ,1);
			if (GetDistance(meat, "path_3") < 400.0)
			then
				M.MINE3 = exu.BuildAsyncObject ("boltM.mine", 2, "path_3");
				M.mine3built = true;
			end
		end
	end

	if (M.mine4built)
	then
		local meat = GetNearestVehicle ("path_4" ,1);
		if (GetDistance(meat, "path_4") > 400.0)
		then
			M.mine4 = GetTime() + 3.0;
			M.mine4built = false;
			RemoveObject (M.MINE4);
		end
	else
		if (M.mine4 < GetTime()) then
			local meat = GetNearestVehicle ("path_4" ,1);
			if (GetDistance(meat, "path_4") < 400.0)
			then
				M.MINE4 = exu.BuildAsyncObject ("boltM.mine", 2, "path_4");
				M.mine4built = true;
			end
		end
	end
	if (M.mine5built)
	then
		local meat = GetNearestVehicle ("path_5" ,1);
		if (GetDistance(meat, "path_5") > 400.0)
		then
			M.mine5 = GetTime() + 3.0;
			M.mine5built = false;
			RemoveObject (M.MINE5);
		end
	else
		if (M.mine5 < GetTime()) then
			local meat = GetNearestVehicle ("path_5" ,1);
			if (GetDistance(meat, "path_5") < 400.0)
			then
				M.MINE5 = exu.BuildAsyncObject ("boltM.mine", 2, "path_5");
				M.mine5built = true;
			end
		end
	end

	if (M.mine6built)
	then
		local meat = GetNearestVehicle ("path_6" ,1);
		if (GetDistance(meat, "path_6") > 400.0)
		then
			M.mine6 = GetTime() + 3.0;
			M.mine6built = false;
			RemoveObject (M.MINE6);
		end
	else
		if (M.mine6 < GetTime()) then
			local meat = GetNearestVehicle ("path_6" ,1);
			if (GetDistance(meat, "path_6") < 400.0)
			then
				M.MINE6 = exu.BuildAsyncObject ("boltM.mine", 2, "path_6");
				M.mine6built = true;
			end
		end
	end

	if (M.mine7built)
	then
		local meat = GetNearestVehicle ("path_7" ,1);
		if (GetDistance(meat, "path_7") > 400.0)
		then
			M.mine7 = GetTime() + 3.0;
			M.mine7built = false;
			RemoveObject (M.MINE7);
		end
	else
		if (M.mine7 < GetTime()) then
			local meat = GetNearestVehicle ("path_7" ,1);
			if (GetDistance(meat, "path_7") < 400.0)
			then
				M.MINE7 = exu.BuildAsyncObject ("boltM.mine", 2, "path_7");
				M.mine7built = true;
			end
		end
	end

	if (M.mine8built)
	then
		local meat = GetNearestVehicle ("path_8" ,1);
		if (GetDistance(meat, "path_8") > 400.0)
		then
			M.mine8 = GetTime() + 3.0;
			M.mine8built = false;
			RemoveObject (M.MINE8);
		end
	else
		if (M.mine8 < GetTime()) then
			local meat = GetNearestVehicle ("path_8" ,1);
			if (GetDistance(meat, "path_8") < 400.0)
			then
				M.MINE8 = exu.BuildAsyncObject ("boltM.mine", 2, "path_8");
				M.mine8built = true;
			end
		end
	end

	if (M.mine9built)
	then
		local meat = GetNearestVehicle ("path_9" ,1);
		if (GetDistance(meat, "path_9") > 400.0)
		then
			M.mine9 = GetTime() + 3.0;
			M.mine9built = false;
			RemoveObject (M.MINE9);
		end
	else
		if (M.mine9 < GetTime()) then
			local meat = GetNearestVehicle ("path_9" ,1);
			if (GetDistance(meat, "path_9") < 400.0)
			then
				M.MINE9 = exu.BuildAsyncObject ("boltM.mine", 2, "path_9");
				M.mine9built = true;
			end
		end
	end

	if (M.mine10built)
	then
		local meat = GetNearestVehicle ("path_10" ,1);
		if (GetDistance(meat, "path_10") > 400.0)
		then
			M.mine10 = GetTime() + 3.0;
			M.mine10built = false;
			RemoveObject (M.MINE10);
		end
	else
		if (M.mine10 < GetTime()) then
			local meat = GetNearestVehicle ("path_10" ,1);
			if (GetDistance(meat, "path_10") < 400.0)
			then
				M.MINE10 = exu.BuildAsyncObject ("boltM.mine", 2, "path_10");
				M.mine10built = true;
			end
		end
	end

	if (M.mine11built)
	then
		local meat = GetNearestVehicle ("path_11" ,1);
		if (GetDistance(meat, "path_11") > 400.0)
		then
			M.mine11 = GetTime() + 3.0;
			M.mine11built = false;
			RemoveObject (M.MINE11);
		end
	else
		if (M.mine11 < GetTime()) then
			local meat = GetNearestVehicle ("path_11" ,1);
			if (GetDistance(meat, "path_11") < 400.0)
			then
				M.MINE11 = exu.BuildAsyncObject ("boltM.mine", 2, "path_11");
				M.mine11built = true;
			end
		end
	end

	if (M.mine12built)
	then
		local meat = GetNearestVehicle ("path_12" ,1);
		if (GetDistance(meat, "path_12") > 400.0)
		then
			M.mine12 = GetTime() + 3.0;
			M.mine12built = false;
			RemoveObject (M.MINE12);
		end
	else
		if (M.mine12 < GetTime()) then
			local meat = GetNearestVehicle ("path_12" ,1);
			if (GetDistance(meat, "path_12") < 400.0)
			then
				M.MINE12 = exu.BuildAsyncObject ("boltM.mine", 2, "path_12");
				M.mine12built = true;
			end
		end
	end

	if (M.mine13built)
	then
		local meat = GetNearestVehicle ("path_13" ,1);
		if (GetDistance(meat, "path_13") > 400.0)
		then
			M.mine13 = GetTime() + 3.0;
			M.mine13built = false;
			RemoveObject (M.MINE13);
		end
	else
		if (M.mine13 < GetTime()) then
			local meat = GetNearestVehicle ("path_13" ,1);
			if (GetDistance(meat, "path_13") < 400.0)
			then
				M.MINE13 = exu.BuildAsyncObject ("boltM.mine", 2, "path_13");
				M.mine13built = true;
			end
		end
	end

	if (M.mine14built)
	then
		local meat = GetNearestVehicle ("path_14" ,1);
		if (GetDistance(meat, "path_14") > 400.0)
		then
			M.mine14 = GetTime() + 3.0;
			M.mine14built = false;
			RemoveObject (M.MINE14);
		end
	else
		if (M.mine14 < GetTime()) then
			local meat = GetNearestVehicle ("path_14" ,1);
			if (GetDistance(meat, "path_14") < 400.0)
			then
				M.MINE14 = exu.BuildAsyncObject ("boltM.mine", 2, "path_14");
				M.mine14built = true;
			end
		end
	end

	if (M.mine15built)
	then
		local meat = GetNearestVehicle ("path_15" ,1);
		if (GetDistance(meat, "path_15") > 400.0)
		then
			M.mine15 = GetTime() + 3.0;
			M.mine15built = false;
			RemoveObject (M.MINE15);
		end
	else
		if (M.mine15 < GetTime()) then
			local meat = GetNearestVehicle ("path_15" ,1);
			if (GetDistance(meat, "path_15") < 400.0)
			then
				M.MINE15 = exu.BuildAsyncObject ("boltM.mine", 2, "path_15");
				M.mine15built = true;
			end
		end
	end

	if (M.mine16built)
	then
		local meat = GetNearestVehicle ("path_16" ,1);
		if (GetDistance(meat, "path_16") > 400.0)
		then
			M.mine16 = GetTime() + 3.0;
			M.mine16built = false;
			RemoveObject (M.MINE16);
		end
	else
		if (M.mine16 < GetTime()) then
			local meat = GetNearestVehicle ("path_16" ,1);
			if (GetDistance(meat, "path_16") < 400.0)
			then
				M.MINE16 = exu.BuildAsyncObject ("boltM.mine", 2, "path_16");
				M.mine16built = true;
			end
		end
	end

	if (M.mine17built)
	then
		local meat = GetNearestVehicle ("path_17" ,1);
		if (GetDistance(meat, "path_17") > 400.0)
		then
			M.mine17 = GetTime() + 3.0;
			M.mine17built = false;
			RemoveObject (M.MINE17);
		end
	else
		if (M.mine17 < GetTime()) then
			local meat = GetNearestVehicle ("path_17" ,1);
			if (GetDistance(meat, "path_17") < 400.0)
			then
				M.MINE17 = exu.BuildAsyncObject ("boltM.mine", 2, "path_17");
				M.mine17built = true;
			end
		end
	end

	if (M.mine18built)
	then
		local meat = GetNearestVehicle ("path_18" ,1);
		if (GetDistance(meat, "path_18") > 400.0)
		then
			M.mine18 = GetTime() + 3.0;
			M.mine18built = false;
			RemoveObject (M.MINE18);
		end
	else
		if (M.mine18 < GetTime()) then
			local meat = GetNearestVehicle ("path_18" ,1);
			if (GetDistance(meat, "path_18") < 400.0)
			then
				M.MINE18 = exu.BuildAsyncObject ("boltM.mine", 2, "path_18");
				M.mine18built = true;
			end
		end
	end

	if (M.mine19built)
	then
		local meat = GetNearestVehicle ("path_19" ,1);
		if (GetDistance(meat, "path_19") > 400.0)
		then
			M.mine19 = GetTime() + 3.0;
			M.mine19built = false;
			RemoveObject (M.MINE19);
		end
	else
		if (M.mine19 < GetTime()) then
			local meat = GetNearestVehicle ("path_19" ,1);
			if (GetDistance(meat, "path_19") < 400.0)
			then
				M.MINE19 = exu.BuildAsyncObject ("boltM.mine", 2, "path_19");
				M.mine19built = true;
			end
		end
	end

	if (M.mine20built)
	then
		local meat = GetNearestVehicle ("path_20" ,1);
		if (GetDistance(meat, "path_20") > 400.0)
		then
			M.mine20 = GetTime() + 3.0;
			M.mine20built = false;
			RemoveObject (M.MINE20);
		end
	else
		if (M.mine20 < GetTime()) then
			local meat = GetNearestVehicle ("path_20" ,1);
			if (GetDistance(meat, "path_20") < 400.0)
			then
				M.MINE20 = exu.BuildAsyncObject ("boltM.mine", 2, "path_20");
				M.mine20built = true;
			end
		end
	end

	if (M.mine21built)
	then
		local meat = GetNearestVehicle ("path_21" ,1);
		if (GetDistance(meat, "path_21") > 400.0)
		then
			M.mine21 = GetTime() + 3.0;
			M.mine21built = false;
			RemoveObject (M.MINE21);
		end
	else
		if (M.mine21 < GetTime()) then
			local meat = GetNearestVehicle ("path_21" ,1);
			if (GetDistance(meat, "path_21") < 400.0)
			then
				M.MINE21 = exu.BuildAsyncObject ("boltM.mine", 2, "path_21");
				M.mine21built = true;
			end
		end
	end

	if (M.mine22built)
	then
		local meat = GetNearestVehicle ("path_22" ,1);
		if (GetDistance(meat, "path_22") > 400.0)
		then
			M.mine22 = GetTime() + 3.0;
			M.mine22built = false;
			RemoveObject (M.MINE22);
		end
	else
		if (M.mine22 < GetTime()) then
			local meat = GetNearestVehicle ("path_22" ,1);
			if (GetDistance(meat, "path_22") < 400.0)
			then
				M.MINE22 = exu.BuildAsyncObject ("boltM.mine", 2, "path_22");
				M.mine22built = true;
			end
		end
	end

	if (M.mine23built)
	then
		local meat = GetNearestVehicle ("path_23" ,1);
		if (GetDistance(meat, "path_23") > 400.0)
		then
			M.mine23 = GetTime() + 3.0;
			M.mine23built = false;
			RemoveObject (M.MINE23);
		end
	else
		if (M.mine23 < GetTime()) then
			local meat = GetNearestVehicle ("path_23" ,1);
			if (GetDistance(meat, "path_23") < 400.0)
			then
				M.MINE23 = exu.BuildAsyncObject ("boltM.mine", 2, "path_23");
				M.mine23built = true;
			end
		end
	end

	if (M.mine24built)
	then
		local meat = GetNearestVehicle ("path_24" ,1);
		if (GetDistance(meat, "path_24") > 400.0)
		then
			M.mine24 = GetTime() + 3.0;
			M.mine24built = false;
			RemoveObject (M.MINE24);
		end
	else
		if (M.mine24 < GetTime()) then
			local meat = GetNearestVehicle ("path_24" ,1);
			if (GetDistance(meat, "path_24") < 400.0)
			then
				M.MINE24 = exu.BuildAsyncObject ("boltM.mine", 2, "path_24");
				M.mine24built = true;
			end
		end
	end

	

	if 
		(
		(M.notfound == true) and (M.shuffle == false)
		)
	then
		M.sendTime [1] = GetTime() + 10.0;
		M.sendTime [2] = GetTime() + 90.0;
		M.sendTime [3] = GetTime() + 130.0;
		M.sendTime [4] = GetTime() + 190.0;
		for i = 1, 11 do
			local j = math.random(0, 3); --rand() % 4;
			local k = math.random(0, 3); --rand() % 4;
			local temp = M.sendTime[j];
			M.sendTime[j] = M.sendTime[k];
			M.sendTime[k] = temp;
		end
		for i = 1, 5 do
			print("%f\n", M.sendTime[i]);
		end
		M.shuffle = true;
	end

	if
		(
		(M.sendTime[0] < GetTime()) and (M.sent1Done == false)
		)
	then
		M.w1u1 = exu.BuildAsyncObject ("svfigh",2,M.svrec);
		M.w1u2 = exu.BuildAsyncObject ("svfigh",2,M.svrec);
		M.w1u3 = exu.BuildAsyncObject ("svturr",2,M.svrec);
		M.w1u4 = exu.BuildAsyncObject ("svturr",2,M.svrec);
		M.sent1Done = true;
		Follow (M.w1u1, M.w1u3);
		Follow (M.w1u2, M.w1u4);
		SetIndependence(M.w1u1, 1);
		SetIndependence(M.w1u2, 1);
		Goto (M.w1u3, "defendrim2");
		Goto (M.w1u4, "defendrim1");
		M.check1 = true;
		M.check2 = true;
		M.check3 = true;
		M.check4 = true;
	end

	if (
		IsAlive(M.w1u3)  and 
		(M.check1 == false)  and 
		(GetCurrentCommand(M.w1u3) == AiCommand.NONE)
		)
	then
		Defend(M.w1u3, 1000);
	end
	
	if (
			(M.check1 == true)  and 
			(
				 not IsAlive(M.w1u3)  or 
				(GetDistance(M.w1u3, "defendrim2") < 20.0)
			)
		)
	then
		if (IsAlive(M.w1u3)) then
			Stop(M.w1u3, 1000);
		end
		Patrol(M.w1u1, "attackpatrol1", 2);
		M.check1 = false;
	end

	if (
		IsAlive(M.w1u4)  and 
		(M.check2 == false)  and 
		(GetCurrentCommand(M.w1u4) == AiCommand.NONE)
		)
	then
		Defend(M.w1u4, 1000);
	end

	if (
			(M.check2 == true)  and 
			(
				 not IsAlive(M.w1u4)  or 
				(GetDistance(M.w1u4, "defendrim1") < 20.0)
			)
		)
	then
		if (IsAlive(M.w1u4)) then 
			Stop(M.w1u4, 1000);
		end
		Patrol(M.w1u2, "attackpatrol1", 2);
		M.check2 = false;
	end

	if (
		IsAlive(M.w2u3)  and 
		(M.check3 == false)  and 
		(GetCurrentCommand(M.w2u3) == AiCommand.NONE)
		)
	then
		Defend(M.w2u3, 1000);
	end

	if (
			(M.check3 == true)  and 
			(
				 not IsAlive(M.w2u3)  or 
				(GetDistance(M.w2u3, "defendrim3") < 20.0)
			)
		)
	then
		if (IsAlive(M.w2u3)) then 
			Stop(M.w2u3, 1000);
		end
		Patrol(M.w2u1, "attackpatrol1", 2);
		M.check3 = false;
	end

	if (
		IsAlive(M.w2u4)  and 
		(M.check4 == false)  and 
		(GetCurrentCommand(M.w2u4) == AiCommand.NONE)
		)
	then
		Defend(M.w2u4, 1000);
	end

	if (
			(M.check4 == true)  and 
			(
				 not IsAlive(M.w2u4)  or 
				(GetDistance(M.w2u4, "defendrim4") < 20.0)
			)
		)
	then
		if (IsAlive(M.w2u4)) then 
			Stop(M.w2u4, 1000);
		end
		Patrol(M.w2u2, "attackpatrol1", 2);
		M.check4 = false;
	end

	if
		(
		(M.sendTime[1] < GetTime()) and (M.sent2Done == false)
		)
	then
		M.w2u1 = exu.BuildAsyncObject ("svtank",2,M.svrec);
		M.w2u2 = exu.BuildAsyncObject ("svtank",2,M.svrec);
		M.w2u3 = exu.BuildAsyncObject ("svturr",2,M.svrec);
		M.w2u4 = exu.BuildAsyncObject ("svturr",2,M.svrec);
		M.sent2Done = true;
		Follow (M.w2u1, M.w2u3);
		Follow (M.w2u2, M.w2u4);
		SetIndependence(M.w2u1, 1);
		SetIndependence(M.w2u2, 1);
		Goto (M.w2u3, "defendrim3");
		Goto (M.w2u4, "defendrim4");
	end
	if
		(
		(M.sendTime[2] < GetTime()) and (M.sent3Done == false)
		)
	then
		--M.w3u1 = BuildObject ("svfigh",2,M.svrec);
		--M.w3u2 = BuildObject ("svfigh",2,M.svrec);
		M.w3u3 = exu.BuildAsyncObject ("svfigh",2,M.svrec);
		M.w3u4 = exu.BuildAsyncObject ("svfigh",2,M.svrec);
		M.sent3Done = true;
		--Patrol (M.w3u1, "attackpatrol1",1);
		--Patrol (M.w3u2, "attackpatrol1",1);
		Patrol (M.w3u3, "attackpatrol1",2);
		Patrol (M.w3u4, "attackpatrol1",2);
	end

	if
		(
		(M.sendTime[3] < GetTime()) and (M.sent4Done == false)
		)
	then
		--M.w4u1 = BuildObject ("svfigh",2,M.svrec);
		--M.w4u2 = BuildObject ("svfigh",2,M.svrec);
		M.w4u3 = exu.BuildAsyncObject ("svfigh",2,M.svrec);
		M.w4u4 = exu.BuildAsyncObject ("svfigh",2,M.svrec);
		M.sent4Done = true;
		--Patrol (M.w4u1, "attackpatrol1",1);
		--Patrol (M.w4u2, "attackpatrol1",1);
		Patrol (M.w4u3, "attackpatrol1",2);
		Patrol (M.w4u4, "attackpatrol1",2);
	end

	if
		(
		(M.reconfactory == false) and (GetDistance (M.player, M.lemnos) < 600.0)
		 and  (M.notfound == false)
		)
	then
		AudioMessage ("misn0502.wav");
		M.notfound = true;
	end

	if
		(
		(M.reconfactory == false) and (GetDistance (M.player, M.lemnos) < 230.0) 
		)
	then
		AudioMessage ("misn0503.wav");
		AudioMessage ("misn0504.wav");
		M.reconfactory = true;
		M.newobjective = true;
		M.start = GetTime() + 90.0;
		--M.lemcinstart = GetTime() - 1.0;
		--M.lemcinend = GetTime() + 3.0;
	end

	--[[if
		(
		(M.lemcin1 == false) and (M.lemcinstart < GetTime())
		)
	then
		CameraReady();
		M.lemcin1 = true;
	end

	if
		(
		(M.lemcin2 == false) and (M.lemcinend > GetTime())
		)
	then
		CameraObject(M.player, 0, 5000, - 5000, M.lemnos);
	end

	if
		(
		(M.lemcin2 == false) and (M.lemcinend < GetTime())
		)
	then
		CameraFinish();
		M.lemcin2 = true;
	end--]]
	

	


	if 
		(
		(M.reconfactory == true)  and 
		(M.reconed == false)  and 
		(
		(IsInfo("oblema"))  or 
		(M.start < GetTime())
		)
		)

	then
		--AudioMessage ("misn0515.wav");
		M.readtime = GetTime() + 5.0;
		M.reconed = true;
	end
	if
		(
		(M.neworders == false) and (M.readtime < GetTime()) 
		)
	then
		M.neworders = true;
		AudioMessage ("misn0506.wav");
		SetObjectiveOn(M.lemnos);
		M.newobjective = true;
	end
	if
		(
		(IsAlive(M.svrec)) and (M.basewave == false)  and 
		(M.reconfactory == true)
		)
	then
		M.wBu1 = exu.BuildAsyncObject ("svtank",2,M.svrec);
		M.wBu2 = exu.BuildAsyncObject ("svfigh",2,M.svrec);
		M.wBu3 = exu.BuildAsyncObject ("svfigh",2,M.svrec);
		Attack (M.wBu1, M.avrec);
		Attack (M.wBu2, M.avrec);
		Attack (M.wBu3, M.avrec);
		SetIndependence(M.wBu1, 1);
		SetIndependence(M.wBu2, 1);
		SetIndependence(M.wBu3, 1);
		M.basewave = true;
	end

	-- make sure dead things stay 
	if (M.sent1Done)
	then
		IsAlive(M.w1u1);
		IsAlive(M.w1u2);
		IsAlive(M.w1u3);
		IsAlive(M.w1u4);
	end
	if (M.sent2Done)
	then
		IsAlive(M.w2u1);
		IsAlive(M.w2u2);
		IsAlive(M.w2u3);
		IsAlive(M.w2u4);
	end
	if (M.sent3Done)
	then
		IsAlive(M.w3u1);
		IsAlive(M.w3u2);
		IsAlive(M.w3u3);
		IsAlive(M.w3u4);
	end
	if (M.sent4Done)
	then
		IsAlive(M.w4u1);
		IsAlive(M.w4u2);
		IsAlive(M.w4u3);
		IsAlive(M.w4u4);
	end

	if
		(
		(M.sent1Done == true)  and 
		(M.sent2Done == true)  and 
		(M.sent3Done == true)  and 
		(M.sent4Done == true)  and 
		( not IsAlive (M.w1u1))  and 
		( not IsAlive (M.w1u2))  and 
		( not IsAlive (M.w1u3))  and 
		( not IsAlive (M.w1u4))  and 
		( not IsAlive (M.w2u1))  and 
		( not IsAlive (M.w2u2))  and 
		( not IsAlive (M.w2u3))  and 
		( not IsAlive (M.w2u4))  and 
		( not IsAlive (M.w3u1))  and 
		( not IsAlive (M.w3u2))  and 
		( not IsAlive (M.w3u3))  and 
		( not IsAlive (M.w3u4))  and 
		( not IsAlive (M.w4u1))  and 
		( not IsAlive (M.w4u2))  and 
		( not IsAlive (M.w4u3))  and 
		( not IsAlive (M.w4u4)) and 
		(M.attacktimeset == false)
		)
	then
		AudioMessage ("misn0507.wav");
		M.platoonhere = GetTime()+45.0;--600.0
		M.attacktimeset = true;
		M.go = true;
	end

	if 
		(
		( not IsAlive(M.aw1))  and 
		( not IsAlive(M.aw2))  and 
		( not IsAlive(M.aw3))  and 
		( not IsAlive(M.aw4))  and 
		( not IsAlive(M.aw5))  and 
		(M.platoonhere > GetTime())  and 
		(M.go == true) and (IsAlive(M.svrec))
		)
	then
		AudioMessage("misn0508.wav");
		AudioMessage("misn0509.wav");
		M.attacksent = math.random(0, 3); --rand() %4;
		M.attackstatement = false;
		
	--	switch (M.attacksent)
		if M.attacksent == 0 then
		--	case 0:
			M.aw1 = exu.BuildAsyncObject ("svhraz", 2, M.svrec);
			M.aw2 = exu.BuildAsyncObject ("svhraz", 2, M.svrec);
			M.aw3 = exu.BuildAsyncObject ("svhraz", 2, M.svrec);
			--M.aw4 = BuildObject ("svhraz", 2, M.svrec);
			--M.aw5 = BuildObject ("svhraz", 2, M.svrec);
			Goto (M.aw1, "destroy1");
			Goto (M.aw2, "destroy1");
			Goto (M.aw3, "destroy1");
			--Goto (M.aw4, "destroy1");
			--Goto (M.aw5, "destroy1");
		elseif M.attacksent == 1 then
		--	break;
		--	case 1:
			M.aw1 = exu.BuildAsyncObject ("svhraz", 2, M.svrec);
			M.aw2 = exu.BuildAsyncObject ("svhraz", 2, M.svrec);
			M.aw3 = exu.BuildAsyncObject ("svhraz", 2, M.svrec);
			--M.aw4 = BuildObject ("svhraz", 2, M.svrec);
			--M.aw5 = BuildObject ("svhraz", 2, M.svrec);
			Goto (M.aw1, "destroy2");
			Goto (M.aw2, "destroy2");
			Goto (M.aw3, "destroy2");
			--Goto (M.aw4, "destroy2");
			--Goto (M.aw5, "destroy2");
		elseif M.attacksent == 2 then
		--	break;
		--	case 2:
			M.aw1 = exu.BuildAsyncObject ("svhraz", 2, M.svrec);
			M.aw2 = exu.BuildAsyncObject ("svhraz", 2, M.svrec);
			M.aw3 = exu.BuildAsyncObject ("svhraz", 2, M.svrec);
			--M.aw4 = BuildObject ("svhraz", 2, M.svrec);
			--M.aw5 = BuildObject ("svhraz", 2, M.svrec);
			Goto (M.aw1, "destroy3");
			Goto (M.aw2, "destroy3");
			Goto (M.aw3, "destroy3");
			--Goto (M.aw4, "destroy3");
			--Goto (M.aw5, "destroy3");
		elseif M.attacksent == 3 then
		--	break;
		--	case 3:
			M.aw1 = exu.BuildAsyncObject ("svhraz", 2, M.svrec);
			M.aw2 = exu.BuildAsyncObject ("svhraz", 2, M.svrec);
			M.aw3 = exu.BuildAsyncObject ("svhraz", 2, M.svrec);
			--M.aw4 = BuildObject ("svhraz", 2, M.svrec);
			--M.aw5 = BuildObject ("svhraz", 2, M.svrec);
			Goto (M.aw1, "destroy4");
			Goto (M.aw2, "destroy4");
			Goto (M.aw3, "destroy4");
			--Goto (M.aw4, "destroy4");
			--Goto (M.aw5, "destroy4");
			--break;
		end
		M.bombtime = GetTime () + 10.0;
		M.attackcmd = false;
		M.aw1t = GetTime() + 10.0;
		M.aw2t = GetTime() + 50.0;
		M.aw3t = GetTime() + 100.0;
		M.aw4t = GetTime() + 140.0;
	end
	if
		(
		(M.attackcmd == false) and (M.bombtime < GetTime())
		)
	then
		if
			(
			(GetDistance(M.aw1, "dest1") < 30.0)  or 
			(GetDistance(M.aw1, "dest2") < 30.0)
			)
		then
			Attack(M.aw1, M.lemnos);
			SetIndependence(M.aw1, 1);
			M.attackcmd = true;
		end
		if
			(
			(GetDistance(M.aw2, "dest1") < 30.0)  or 
			(GetDistance(M.aw2, "dest2") < 30.0)
			)
		then
			Attack(M.aw2, M.lemnos);
			SetIndependence(M.aw2, 1);
			M.attackcmd = true;
		end
		if
			(
			(GetDistance(M.aw3, "dest1") < 30.0)  or 
			(GetDistance(M.aw3, "dest2") < 30.0)
			)
		then
			Attack(M.aw3, M.lemnos);
			SetIndependence(M.aw3, 1);
			M.attackcmd = true;
		end
		if
			(
			(GetDistance(M.aw4, "dest1") < 30.0)  or 
			(GetDistance(M.aw4, "dest2") < 30.0)
			)
		then
			Attack(M.aw4, M.lemnos);
			SetIndependence(M.aw4, 1);
			M.attackcmd = true;
		end
		if
			(
			(GetDistance(M.aw5, "dest1") < 30.0)  or 
			(GetDistance(M.aw5, "dest2") < 30.0)
			)
		then
			Attack(M.aw5, M.lemnos);
			SetIndependence(M.aw5, 1);
			M.attackcmd = true;
		end
		M.bombtime = GetTime() + 3.0;
	end
		

		--[[if
			(
			(M.platoonhere < GetTime()) and 
			( not IsAlive(M.aw1))  and 
			( not IsAlive(M.aw2))  and 
			( not IsAlive(M.aw3))  and 
			( not IsAlive(M.aw4))  and 
			( not IsAlive(M.aw5))  and 
			(M.missionwon == false)
			)
		then
			M.missionwon = true;
			AudioMessage ("misn0511.wav");
			AudioMessage ("misn0512.wav");
			SucceedMission (GetTime() + 15.0);
		end--]]

		if 
			(
			( not IsAlive(M.avrec)) and (M.missionfail == false)
			)
		then
			FailMission (GetTime()+15.0, "misn05l1.des");
			AudioMessage ("misn0513.wav");
			M.missionfail = true;
		end

		if 
			(
			( not IsAlive(M.lemnos)) and (M.missionfail == false)
			)
		then
			FailMission (GetTime()+15.0, "misn05l2.des");
			AudioMessage ("misn0514.wav");
			M.missionfail = true;
		end

		if
			(
			(
			(GetDistance(M.aw1, M.lemnos) < 500.0)  or 
			(GetDistance(M.aw2, M.lemnos) < 500.0)  or 
			(GetDistance(M.aw3, M.lemnos) < 500.0)  or 
			(GetDistance(M.aw4, M.lemnos) < 500.0)  or 
			(GetDistance(M.aw5, M.lemnos) < 500.0) 
			)
			 and  (M.attackstatement == false)
			)
		then
			AudioMessage ("misn0510.wav");
			M.attackstatement = true;
		end
	



	if 
		(
		(M.aw1t < GetTime()) and 
		(M.aw1sent == false) and 
		(IsAlive(M.svrec))
		)
	then
		--M.aw1a = BuildObject ("svfigh", 2, M.svrec);
		M.aw2a = exu.BuildAsyncObject ("svfigh", 2, M.svrec);
		--Goto (M.aw1a, M.lemnos);
		Attack (M.aw2a, M.lemnos);
		SetIndependence(M.aw2a, 1);
		M.aw1sent = true;
	end

	if 
		(
		(M.aw2t < GetTime()) and 
		(M.aw2sent == false) and 
		(IsAlive(M.svrec))
		)
	then
		--M.aw3a = BuildObject ("svtank", 2, M.svrec);
		M.aw4a = exu.BuildAsyncObject ("svtank", 2, M.svrec);
		--Goto (M.aw3a, M.lemnos);
		Attack (M.aw4a, M.lemnos);
		SetIndependence(M.aw4a, 1);
		M.aw2sent = true;
	end

	if 
		(
		(M.aw3t < GetTime()) and 
		(M.aw3sent == false)  and 
		(IsAlive(M.svrec))
		)
	then
		M.aw5a = exu.BuildAsyncObject ("svfigh", 2, M.svrec);
		M.aw6a = exu.BuildAsyncObject ("svfigh", 2, M.svrec);
		--M.aw7a = BuildObject ("svfigh", 2, M.svrec);
		Attack (M.aw5a, M.lemnos);
		Attack (M.aw6a, M.lemnos);
		SetIndependence(M.aw5a, 1);
		SetIndependence(M.aw6a, 1);
		--Goto (M.aw7a, M.lemnos);
		M.aw3sent = true;
	end

	if 
		(
		(M.aw4t < GetTime()) and 
		(M.aw4sent == false)  and 
		(IsAlive(M.svrec))
		)
	then
		M.aw8a = exu.BuildAsyncObject ("svfigh", 2, M.svrec);
		M.aw9a = exu.BuildAsyncObject ("svtank", 2, M.svrec);
		Attack (M.aw8a, M.lemnos);
		Attack (M.aw9a, M.lemnos);
		SetIndependence(M.aw8a, 1);
		SetIndependence(M.aw9a, 1);
		M.aw4sent = true;
	end

	if
		(
		(M.aw1sent == true)  and 
		(IsAlive(M.aw1a)) and (M.aw1aattack == false)
		)
	then
		if
			(GetDistance(M.aw1a, M.lemnos) < 300.0)
		then
			Attack(M.aw1a, M.lemnos);
			SetIndependence(M.aw1a, 1);
			M.aw1aattack = true;
		end
	end
	if
		(
		(M.aw1sent == true)  and 
		(IsAlive(M.aw2a)) and (M.aw2aattack == false)
		)
	then
		if
			(GetDistance(M.aw2a, M.lemnos) < 300.0)
		then
			Attack(M.aw2a, M.lemnos);
			SetIndependence(M.aw2a, 1);
			M.aw2aattack = true;
		end
	end
	if
		(
		(M.aw1sent == true)  and 
		(IsAlive(M.aw3a)) and (M.aw3aattack == false)
		)
	then
		if
			(GetDistance(M.aw3a, M.lemnos) < 300.0)
		then
			Attack(M.aw3a, M.lemnos);
			SetIndependence(M.aw3a, 1);
			M.aw3aattack = true;
		end
	end
	if
		(
		(M.aw1sent == true)  and 
		(IsAlive(M.aw4a)) and (M.aw4aattack == false)
		)
	then
		if
			(GetDistance(M.aw4a, M.lemnos) < 300.0)
		then
			Attack(M.aw4a, M.lemnos);
			SetIndependence(M.aw4a, 1);
			M.aw4aattack = true;
		end
	end
	if
		(
		(M.aw1sent == true)  and 
		(IsAlive(M.aw9a)) and (M.aw9aattack == false)
		)
	then
		if
			(GetDistance(M.aw9a, M.lemnos) < 300.0)
		then
			Attack(M.aw9a, M.lemnos);
			SetIndependence(M.aw9a, 1);
			M.aw9aattack = true;
		end
	end
	if
		(
		( not IsAlive(M.svrec)) and (M.possiblewin == false)
		)
	then
		M.possiblewin = true;
		AudioMessage("misn0516.wav");
		M.aw1aattack = true;
		M.aw2aattack = true;
		M.aw3aattack = true;
		M.aw4aattack = true;
		M.aw5aattack = true;
		M.aw6aattack = true;
		M.aw7aattack = true;
		M.aw8aattack = true;
		M.aw9aattack = true;
		M.sent1Done = true;
		M.sent2Done = true;
		M.sent3Done = true;
		M.sent4Done = true;

		if
			(
			(IsAlive(M.aw1))  or 
			(IsAlive(M.aw2))  or 
			(IsAlive(M.aw3))  or 
			(IsAlive(M.aw4))  or 
			(IsAlive(M.aw5))  or 
			(IsAlive(M.aw1a))  or 
			(IsAlive(M.aw2a))  or 
			(IsAlive(M.aw3a))  or 
			(IsAlive(M.aw4a))  or 
			(IsAlive(M.aw5a))  or 
			(IsAlive(M.aw6a))  or 
			(IsAlive(M.aw7a))  or 
			(IsAlive(M.aw8a))  or 
			(IsAlive(M.aw9a)) 
			)
		then
			AudioMessage("misn0517.wav");
		end
	end


--[[	CheckPriority(M.aw1);
	CheckPriority(M.aw2);
	CheckPriority(M.aw3);
	CheckPriority(M.aw4);
	CheckPriority(M.aw5);
	CheckPriority(M.aw1a);
	CheckPriority(M.aw2a);
	CheckPriority(M.aw3a);
	CheckPriority(M.aw4a);
	CheckPriority(M.aw5a);
	CheckPriority(M.aw6a);
	CheckPriority(M.aw7a);
	CheckPriority(M.aw8a);
	CheckPriority(M.aw9a);
	CheckPriority(M.w1u1);
	CheckPriority(M.w1u2);
	CheckPriority(M.w1u3);
	CheckPriority(M.w1u4);
	CheckPriority(M.w2u1);
	CheckPriority(M.w2u2);
	CheckPriority(M.w2u3);
	CheckPriority(M.w2u4);
	CheckPriority(M.w3u1);
	CheckPriority(M.w3u2);
	CheckPriority(M.w3u3);
	CheckPriority(M.w3u4);
	CheckPriority(M.w4u1);
	CheckPriority(M.w4u2);
	CheckPriority(M.w4u3);
	CheckPriority(M.w4u4);
--]]

	if
		(
		(M.aw1sent == true)  and 
		(M.aw2sent == true)  and 
		(M.aw3sent == true)  and 
		(M.aw4sent == true)  and 
		(M.sent1Done == true)  and 
		(M.sent2Done == true)  and 
		(M.sent3Done == true)  and 
		(M.sent4Done == true)  and 
		(M.missionwon == false)
		)
	then
		if
			(
			( not IsAlive(M.aw1))  and 
			( not IsAlive(M.aw2))  and 
			( not IsAlive(M.aw3))  and 
			( not IsAlive(M.aw4))  and 
			( not IsAlive(M.aw5))  and 
			( not IsAlive(M.aw1a))  and 
			( not IsAlive(M.aw2a))  and 
			( not IsAlive(M.aw3a))  and 
			( not IsAlive(M.aw4a))  and 
			( not IsAlive(M.aw5a))  and 
			( not IsAlive(M.aw6a))  and 
			( not IsAlive(M.aw7a))  and 
			( not IsAlive(M.aw8a))  and 
			( not IsAlive(M.aw9a))  and 
			( not IsAlive (M.w1u1))  and 
			( not IsAlive (M.w1u2))  and 
			( not IsAlive (M.w1u3))  and 
			( not IsAlive (M.w1u4))  and 
			( not IsAlive (M.w2u1))  and 
			( not IsAlive (M.w2u2))  and 
			( not IsAlive (M.w2u3))  and 
			( not IsAlive (M.w2u4))  and 
			( not IsAlive (M.w3u1))  and 
			( not IsAlive (M.w3u2))  and 
			( not IsAlive (M.w3u3))  and 
			( not IsAlive (M.w3u4))  and 
			( not IsAlive (M.w4u1))  and 
			( not IsAlive (M.w4u2))  and 
			( not IsAlive (M.w4u3))  and 
			( not IsAlive (M.w4u4))
			)
		then
			M.missionwon = true;
			M.newobjective = true;
			AudioMessage ("misn0511.wav");
			AudioMessage ("misn0512.wav");
			SucceedMission (GetTime() + 15.0, "misn05w1.des");
		end
	end

	if
		(
		( not IsAlive(M.svrec)) and (M.takeoutfactory == false)
		)
	then
		Attack(M.w1u1, M.lemnos);
		Attack(M.w1u2, M.lemnos);
		Attack(M.w1u3, M.lemnos);
		Attack(M.w1u4, M.lemnos);
		Attack(M.w2u1, M.lemnos);
		Attack(M.w2u2, M.lemnos);
		Attack(M.w2u3, M.lemnos);
		Attack(M.w2u4, M.lemnos);
		Attack(M.w3u1, M.lemnos);
		Attack(M.w3u2, M.lemnos);
		Attack(M.w3u3, M.lemnos);
		Attack(M.w3u4, M.lemnos);
		Attack(M.w4u1, M.lemnos);
		Attack(M.w4u2, M.lemnos);
		Attack(M.w4u3, M.lemnos);
		Attack(M.w4u4, M.lemnos);
		M.takeoutfactory = true;
	end


-- END OF SCRIPT
	
end