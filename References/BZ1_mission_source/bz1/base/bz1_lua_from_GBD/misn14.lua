-- Single Player NSDF Mission 13 Lua conversion, created by General BlackDragon. 

-- Single Table for all our save/load variables. This SP mission has too many variables to function with them independently. ("main function has > 200 local variables", or "Load having > 197 variables in assignment")
local M = {

-- bools
	start_done = false,
	camera1 = false,
	camera2 = false,
	camera3 = false,
	alien_warning = false,
	alien_attack = false,
	cca_surrender = false,
	gen_message = false,
	rescue_message = false,
	rescue_start = false,
	rescue_reminder = false,
	found = false,
	pick_up = false,
	won = false,
	lost = false,
	finishcam1 = false,
	--finishcam2 = false,
	--finishcam3 = false,
	rescuecam1 = false,
	--rescuecam2 = false,
	--rescuecam3 = false,
	rescue1 = false,
	rescue2 = false,
	rescue3 = false,
-- Floats (really doubles in Lua)
	camera_time = 0,
	alien_time = 0,
	pick_up_time = 0,
	beacon_time1 = 0,
	beacon_time2 = 0,
	beacon_time3 = 0,
	rescue_finish1 = 0,
	rescue_finish2 = 0,
	rescue_finish3 = 0,
	next_second = 0,
-- Handles
	beacon1 = nil,
	beacon2 = nil,
	beacon3 = nil,
	audmsg = nil,
	player = nil,
	recy = nil,
	cam1 = nil,
	cam2 = nil,
	cam3 = nil,
	cam4 = nil,
	erecy = nil,
	base = nil,
	apc = nil,
	guy1 = nil,
	guy2 = nil,
	guy3 = nil,
	tow1 = nil,
	tow2 = nil,
	tow3 = nil,
	tow4 = nil,
	pow1 = nil,
	pow2 = nil,
-- Ints
	wave_count = 0
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

	M.alien_time = 99999.0;
	M.pick_up_time = 99999.0;
	M.beacon_time1 = 99999.0;
	M.beacon_time2 = 99999.0;
	M.beacon_time3 = 99999.0;
	M.rescue_finish1 = 99999.0;
	M.rescue_finish2 = 99999.0;
	M.rescue_finish3 = 99999.0;

end

function AddObject(h)

	if (
		(IsOdf(h, "avapc"))  and 
		(GetTeamNum(h) == 1) 
		)
	then
		M.found = true;
		M.apc =  h;
	end

end

function Update()

-- START OF SCRIPT

	M.player = GetPlayerHandle();
	if ( not M.start_done)
	then
		M.recy = GetHandle("avrecy-1_recycler");
		M.erecy = GetHandle("svrecy-1_recycler");
		M.base = GetHandle("sbbarr0_i76building");
		SetAIP("misn14.aip");
		--AddPilot(1,10);
		AddPilot(2,30);
		SetScrap(1,30);
		SetScrap(2,45);
		M.cam1 = GetHandle("apcamr0_camerapod");
		M.cam2 = GetHandle("apcamr1_camerapod");
		M.cam3 = GetHandle("apcamr2_camerapod");
		M.cam4 = GetHandle("apcamr3_camerapod");
		M.tow1 = GetHandle("sbtowe0_turret");
		M.tow2 = GetHandle("sbtowe1_turret");
		M.tow3 = GetHandle("sbtowe55_turret");
		M.tow4 = GetHandle("sbtowe56_turret");
		M.pow1 = GetHandle("sblpow1_powerplant");
		M.pow2 = GetHandle("sblpow55_powerplant");
		SetObjectiveName(M.cam1, "Foothill Geysers");
		SetObjectiveName(M.cam2, "Canyon Geysers");
		SetObjectiveName(M.cam3, "CCA Base");
		SetObjectiveName(M.cam4, "Plateau Geysers");
		M.start_done = true;
		M.next_second = GetTime()+1.0;
		M.camera1 = true;
		CameraReady();
		M.camera_time = GetTime()+12.0;
		M.audmsg = AudioMessage("misn1401.wav");
		if (IsAlive(M.base))
		then
			SetMaxHealth(M.base, 100000.0);
			M.next_second = GetTime()+1.0;

		end


	end	
	if (M.camera1)
	then
		CameraPath("cam_path1",2000,1000,M.recy);
	end
	if ((M.camera1) and ((GetTime()>M.camera_time)  or  CameraCancelled()))
	then
	--	StopAudioMessage(M.audmsg); 
	-- Now the message is longer and see below
		M.camera1 = false;
		M.camera2 = true;
		M.camera_time = GetTime()+15.0;
	--	M.audmsg = AudioMessage("misn1402.wav");
	-- The above message is part of the first..
	end
	if (M.camera2)
	then
		CameraPath("cam_path2",2000,500,M.recy);
	end
	if ((M.camera2) and ((GetTime()>M.camera_time)  or  CameraCancelled()))
	then
		StopAudioMessage(M.audmsg);
		M.camera2 = false;
		CameraFinish();
		ClearObjectives();
		AddObjective("misn1401.otf","WHITE");
		M.alien_time = GetTime()+720.0;  -- six minutes to alien arrival
		M.beacon_time1 = GetTime()+15.0;
	end
	--[[
		Rescue the
		NSDF
	--]]	
	if (GetTime()>M.beacon_time1)
	then
		AudioMessage("misn1416.wav");
		M.beacon_time1 = 99999.0;
		M.beacon1 = exu.BuildAsyncObject("apcamr",1,"rescue1");
		M.guy1 = exu.BuildAsyncObject("aspilo",1,"help1");
		M.guy2 = exu.BuildAsyncObject("aspilo",1,"help2");
		M.guy3 = exu.BuildAsyncObject("aspilo",1,"help3");
		SetIndependence(M.guy1, 0);
		SetIndependence(M.guy2, 0);
		SetIndependence(M.guy3, 0);
		Defend(M.guy1);
		Defend(M.guy2);
		Defend(M.guy3);
		SetObjectiveName(M.beacon1,"Rescue 1");
		SetObjectiveOn(M.beacon1);
	end
	if ((M.beacon1 ~= nil) 
		 and  (GetDistance(M.player,M.beacon1)<200.0)
		 and  ( not M.rescue_reminder) and (GetDistance(M.apc,M.beacon1)>300.0))
	then
		--[[
			Bring in an APC to 
			rescue the survivors.
		--]]
		AudioMessage("misn1415.wav");
		M.rescue_reminder = true;
	end
	if (
		( not M.lost)  and 
		(M.beacon1 ~= nil) and ( not M.rescue1)  and 
		(( not IsAlive(M.guy1))  or  ( not IsAlive(M.guy2))  or  ( not IsAlive(M.guy3)))
		)
	then
		AudioMessage("misn1421.wav");
		FailMission(GetTime()+15.0,"misn14l2.des");
		M.lost = true;
	end


	if ((M.beacon1 ~= nil) and (M.apc ~= nil) and ( not M.rescue1)
		 and  (GetDistance(M.apc,M.beacon1)<100.0))
	then
		M.rescue1 = true;
		Goto(M.guy1,M.beacon1);
		Goto(M.guy2,M.beacon1);
		Goto(M.guy3,M.beacon1);
		M.rescue_finish1 = GetTime()+25.0;
		AudioMessage("misn1409.wav");
		M.camera_time = GetTime()+3.0;
		CameraReady();
		M.rescuecam1 = true;
	end
	if (M.rescuecam1)
	then
		CameraObject(M.apc,1000,1000,1000,M.apc);
		if (CameraCancelled()  or  (GetTime()>M.camera_time))
		then
			CameraFinish();
			M.rescuecam1 = false;
		end
	end
	if ((M.beacon1 ~= nil) and (M.rescue1)
		 and  (M.rescue_finish1<GetTime()))
	then
		--[[
			We're done here
		--]]
		if (IsAlive(M.guy1)) then
			RemoveObject(M.guy1);
		end
		if (IsAlive(M.guy2)) then 
			RemoveObject(M.guy2);
		end
		if (IsAlive(M.guy3)) then 
			RemoveObject(M.guy3);
		end
		if (IsAlive(M.beacon1)) then 
			RemoveObject(M.beacon1);
		end
		M.beacon_time2 = GetTime()+10.0;
		CameraReady();
		AudioMessage("misn1417.wav");
		M.finishcam1 = true;
		M.rescue_finish1 = 99999.0;
		M.camera_time = GetTime()+3.0;
	end
	if (M.finishcam1)
	then
		CameraObject(M.apc,1000,1000,1000,M.apc);
		if (CameraCancelled()  or  (GetTime()>M.camera_time))
		then
			CameraFinish();
			M.finishcam1 = false;
		end
	end
	if (GetTime()>M.beacon_time2)
	then
		M.beacon_time2 = 99999.0;
		M.beacon2 = exu.BuildAsyncObject("apcamr",1,"rescue2");
		M.guy1 = exu.BuildAsyncObject("aspilo",1,"help4");
		M.guy2 = exu.BuildAsyncObject("aspilo",1,"help5");
		M.guy3 = exu.BuildAsyncObject("aspilo",1,"help6");
		SetIndependence(M.guy1, 0);
		SetIndependence(M.guy2, 0);
		SetIndependence(M.guy3, 0);
		Defend(M.guy1);
		Defend(M.guy2);
		Defend(M.guy3);
		SetObjectiveName(M.beacon2,"Rescue 2");
		SetObjectiveOn(M.beacon2);
	end
	if (
		( not M.lost)  and 
		(M.beacon2 ~= nil) and ( not M.rescue2)  and 
		(( not IsAlive(M.guy1))  or  ( not IsAlive(M.guy2))  or  ( not IsAlive(M.guy3)))
		)
	then
		M.lost = true;
		AudioMessage("misn1421.wav");
		FailMission(GetTime()+15.0,"misn14l2.des");
	end
	if ((M.beacon2 ~= nil) and (M.apc ~= nil) and ( not M.rescue2)
		 and  (GetDistance(M.apc,M.beacon2)<100.0))
	then
		M.rescue2 = true;
		Goto(M.guy1,M.beacon2);
		Goto(M.guy2,M.beacon2);
		Goto(M.guy3,M.beacon2);
		M.rescue_finish2 = GetTime()+25.0;
		AudioMessage("misn1409.wav");
	end
	if ((M.beacon2 ~= nil) and (M.rescue2)
		 and  (M.rescue_finish2<GetTime()))
	then
		--[[
			We're done here
		--]]
		if (IsAlive(M.guy1)) then 
			RemoveObject(M.guy1);
		end
		if (IsAlive(M.guy2)) then 
			RemoveObject(M.guy2);
		end
		if (IsAlive(M.guy3)) then
			RemoveObject(M.guy3);
		end
		if (IsAlive(M.beacon2)) then 
			RemoveObject(M.beacon2);
		end
		AudioMessage("misn1418.wav");
		M.rescue_finish2 = 99999.0;

		M.beacon_time3 = GetTime()+10.0;
	end
	if (GetTime()>M.beacon_time3)
	then
		M.beacon_time3 = 99999.0;
		M.beacon3 = exu.BuildAsyncObject("apcamr",1,"rescue3");
		M.guy1 = exu.BuildAsyncObject("aspilo",1,"help7");
		M.guy2 = exu.BuildAsyncObject("aspilo",1,"help8");
		M.guy3 = exu.BuildAsyncObject("aspilo",1,"help9");
		SetIndependence(M.guy1, 0);
		SetIndependence(M.guy2, 0);
		SetIndependence(M.guy3, 0);
		Defend(M.guy1);
		Defend(M.guy2);
		Defend(M.guy3);
		SetObjectiveName(M.beacon3,"Rescue 3");
		SetObjectiveOn(M.beacon3);
	end
		if (
			( not M.lost)  and 
		(M.beacon3 ~= nil) and ( not M.rescue3)  and 
		(( not IsAlive(M.guy1))  or  ( not IsAlive(M.guy2))  or  ( not IsAlive(M.guy3)))
		)
	then
		M.lost = true;
		AudioMessage("misn1421.wav");
		FailMission(GetTime()+15.0,"misn14l2.des");
	end

	if ((M.beacon3 ~= nil) and (M.apc ~= nil) and ( not M.rescue3)
		 and  (GetDistance(M.apc,M.beacon3)<100.0))
	then
		M.rescue3 = true;
		Goto(M.guy1,M.beacon3);
		Goto(M.guy2,M.beacon3);
		Goto(M.guy3,M.beacon3);
		M.rescue_finish3 = GetTime()+25.0;
		AudioMessage("misn1409.wav");
	end

	if ((M.beacon3 ~= nil) and (M.rescue3)
		 and  (M.rescue_finish3<GetTime()))
	then
		--[[
			We're done here
		--]]
		if (IsAlive(M.guy1)) then 
			RemoveObject(M.guy1);
		end
		if (IsAlive(M.guy2)) then 
			RemoveObject(M.guy2);
		end
		if (IsAlive(M.guy3)) then 
			RemoveObject(M.guy3);
		end
		if (IsAlive(M.beacon3)) then 
			RemoveObject(M.beacon3);
		end
		AudioMessage("misn1419.wav");
		M.rescue_finish3 = 99999.0;
	end
	--[[
		We need to keep the M.base
		alive so the game can finish.
	--]]
	if (IsAlive(M.base))
	then
		if (GetTime()>M.next_second)
		then
			AddHealth(M.base, 5000.0);
			M.next_second = GetTime()+1.0;
		end
	end


	--[[
		The aliens are on
		the way and ready to
		give us grief.
	--]]
	if (GetTime()>M.alien_time)
	then
		M.alien_attack = true;
		M.wave_count = M.wave_count + 1;
		local x = math.random(0, 2); --rand()%3;
		if (x == 0) then
			exu.BuildAsyncObject("hvsav",3,"alien1");
			exu.BuildAsyncObject("hvsav",3,"alien2");
			exu.BuildAsyncObject("hvsav",3,"alien5");
		elseif (x == 1) then
			exu.BuildAsyncObject("hvsav",3,"alien3");
			exu.BuildAsyncObject("hvsav",3,"alien4");
			exu.BuildAsyncObject("hvsav",3,"alien1");
		elseif (x == 2) then
			exu.BuildAsyncObject("hvsav",3,"alien5");
			exu.BuildAsyncObject("hvsav",3,"alien6");
			exu.BuildAsyncObject("hvsav",3,"alien3");
		end
		M.alien_time = GetTime()+180.0;  -- was 70.0, now we explore
	end
	if ((M.alien_attack) and ( not M.alien_warning))
	then
		AudioMessage("misn1403.wav");
		M.alien_warning = true;
	end

	if ((M.wave_count>2) and ( not M.cca_surrender))
	then
		AudioMessage("misn1404.wav");
		AudioMessage("misn1405.wav");  -- it's a trick not 
		M.cca_surrender = true;
		--[[
			Here is where we should
			switch sides or destroy people.
		--]]
		--ObjectList &list = *GameObject::objectList;
		--for (ObjectList::iterator i = list.begin(); i ~= list.end(); i++) 
		--then
		--	local h;
		--	GameObject *o = *i;
		--	h = GameObjectHandle::Find(o);
		--	OBJ76 *obj76 = o->GetOBJ76();
		for h in AllCraft() do
			--if ((IsCraft(obj76)) and (o->GetTeam() == 2))
			if (GetTeamNum(h) == 2)
			then
				SetTeamNum(h, 0); --o->SetTeam(0);  -- crazy not  not   team 0 now
				if ((IsOdf(h,"svtank")) 
					 or  (IsOdf(h,"svturr"))
					 or  (IsOdf(h,"svfigh")))
				then
					Retreat(h,"escape",1);  --run away
				end
			end			
		end
		--[[
			Convert the russian M.base
		--]]
		if (IsAlive(M.base))
		then
			SetTeamNum(M.base, 1);
		end
		if (IsAlive(M.pow1))
		then
			SetTeamNum(M.pow1, 1);
		end
		if (IsAlive(M.pow2))
		then
			SetTeamNum(M.pow2, 1);
		end
		if (IsAlive(M.tow1))
		then
			SetTeamNum(M.tow1, 1);
		end
		if (IsAlive(M.tow2))
		then
			SetTeamNum(M.tow2, 1);
		end
		if (IsAlive(M.tow3))
		then
			SetTeamNum(M.tow3, 1);
		end
		if (IsAlive(M.tow4))
		then
			SetTeamNum(M.tow4, 1);
		end

	end
	if ((M.wave_count>3) and ( not M.gen_message) and (M.rescue3))
	then
		SetScrap(2,0);
		M.audmsg = AudioMessage("misn1406.wav");
		M.gen_message = true;
		local foe =  GetNearestEnemy(M.player);
		if (GetDistance(M.player,foe)>150.0) 
		then
			M.camera3 = true;
			M.camera_time = GetTime()+20.0;
			CameraReady();
		else 
			M.camera3 = false;
		end
	end
	if (M.camera3)
	then
		CameraPath("camera_path",2500,300,M.base);
	end
	if ((M.camera3) and ((GetTime()>M.camera_time)   or  CameraCancelled()))
	then
		StopAudioMessage(M.audmsg);
		M.camera3 = false;
		CameraFinish();
	end
	--[[
		Now we need you 
		to rescue CCA personel
	--]]
	if ((M.wave_count>4) and ( not M.rescue_message) and (M.rescue3))
	then
		SetScrap(2,0);
		AudioMessage("misn1407.wav");
		M.rescue_message = true;
		if (IsAlive(M.base))
		then
			SetObjectiveOn(M.base);
			SetObjectiveName(M.base,"Rescue CCA");
		else
			-- just in case its not there
			FailMission(5.0,"misn14l.des");
		end
	end

	if ((M.wave_count>4) and (M.found) and ( not M.rescue_start) and (M.rescue3))
	then
		--[[
			Now that you've built 
			an APC, get it to the 
			M.base to rescue the soviet scientists
			AudioMessage
		--]]
		AudioMessage("misn1408.wav");
		M.rescue_start = true;
	end
	if (( not M.pick_up) and (M.rescue_start) and (GetDistance(M.apc,M.base)<200.0))
	then
		--[[ 
			AudioMessage ..
			We're picking up the 
			key personel..
		--]]
		M.pick_up = true;
		M.pick_up_time = GetTime()+15.0;
		AudioMessage("misn1409.wav");
	end
	if ((M.pick_up) and (GetTime()>M.pick_up_time))
	then
		--[[
			Audio Message
			Ready to go.  
		--]]
		
		M.pick_up_time = 99999.0;
		AudioMessage("misn1410.wav");
	end
	if (( not M.lost) and (M.pick_up) and ( not IsAlive(M.apc)))
	then
		--[[
			Lost the APC with the 
			Russian scientists-- you 
			lose.  
			--]]
		AudioMessage("misn1412.wav");
		AudioMessage("misn1413.wav");
		FailMission(GetTime()+10.0,"misn14l3.des");
		M.lost = true;

	end
	if (( not M.won) and (M.pick_up) and (GetDistance(M.recy,M.apc)<300.0))
	then
		--[[
			You M.won..
		--]]
		M.won = true;
		SucceedMission(GetTime()+10.0,"misn14w1.des");

		AudioMessage("misn1411.wav");
	end
	if (( not M.lost) and ( not IsAlive(M.recy)))
	then
		AudioMessage("misn1414.wav");
		FailMission(GetTime()+10.0,"misn14l1.des");
		M.lost = true;
	end

-- END OF SCRIPT
	
end