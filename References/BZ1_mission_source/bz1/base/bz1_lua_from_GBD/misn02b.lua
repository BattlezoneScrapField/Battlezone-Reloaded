-- Single M.player NSDF Mission 1 Lua conversion, created by General BlackDragon. 

-- Single Table for all our save/load variables. This SP mission has too many variables to function with them independently. ("main function has > 200 local variables", or "Load having > 197 variables in assignment")
local M = {

-- bools
	camera1 = false,
	camera2 = false,
	camera3 = false,
	found = false,
	found2 = false,
	start_done = false,
	patrol1 = false,
	message1 = false,
	message2 = false,
	message3 = false,
	message4 = false,
	message5 = false,
	--message6 = false,
	--message7 = false,
	--message8 = false,
	--message9 = false,
	--message10 = false,
	--message11 = false,
	--message12 = false,
	--message13 = false,
	--message14 = false,
	--message15 = false,
	mission_won = false,
	mission_lost = false,
	--jump_start = false,
-- Floats (really doubles in Lua)
	last_wave_time = 0,
	wave_timer = 0,
	--repeat_time = 0,
	camera_delay = 0,
	dramatic_pause = 0,
	cam_time = 0,
	NextSecond = 0,
-- Handles
	player = nil,
	--target1 = nil,
	--target2 = nil,
	recycler = nil,
	--muf = nil,
	camera = nil,
	wing = nil,
	bhandle = nil,
	bhome = nil,
	bscav = nil,
	scav2 = nil,
	bplayer = nil,
	bgoal = nil,
	bscout = nil,
	lander = nil,
	dummy = nil, -- the base
	bhandle2 = nil,
-- Ints
	--num_reps = 0,
	--on_point = 0,
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

	M.last_wave_time = 99999.0;
	M.dramatic_pause = 99999.0;
	M.NextSecond = 99999.0;

end

function AddObject(h)

	if (
		(GetTeamNum(h) == 1)  and 
		(IsOdf(h, "avscav"))
		 and  (M.bscav == nil)
		)
	then
		M.found = true;
		M.bscav = h;
		SetCritical(M.bscav, true);
	end
	if (
		(GetTeamNum(h) == 2)  and 
		(IsOdf(h, "svfigh"))
		)
	then
		if ( not M.found2)
		then
			M.found2 = true;
			M.bscout = h;
			Goto(M.bscout,"M.patrol1",0);
			SetObjectiveOn(M.bscout);
		--end
		else
			if (GetDistance(M.bscav,M.bgoal)<200.0)
			then
				Attack(h,M.bscav);
			--end
			else
				Goto(h,"patrol2",0);  -- attack scrap field
			end
		end
	end

end

function Update()

-- START OF SCRIPT

	M.bplayer = GetPlayerHandle();
	if ( not M.start_done)
	then
		SetPilot(1,2);
		SetScrap(1,5);
		local team = 2;  -- hard wired, hope this doesn't change
		SetAIP("misn02.aip");
		--[[
			misn0224
			Commander, we've discovered a deposit of bio metal..
			stay close to the scavenger.  
		--]] 
		M.dummy = GetHandle("fake_player");
		M.lander = GetHandle("avland0_wingman");
		M.bhandle = GetHandle("sscr_171_scrap");
		M.bhome = GetHandle("abcomm1_i76building");
		M.recycler = GetHandle("avrecy-1_recycler");
		--	M.bplayer = GetHandle("M.player-1_hover");
		M.bgoal = GetHandle("apscrap-1_camerapod");
		M.bhandle2 = GetHandle("sscr_176_scrap");
		SetUserTarget(M.bgoal);
		M.start_done = true;
		M.camera1 = true;
		M.cam_time = GetTime()+30.0;
		CameraReady();
		M.audmsg = AudioMessage("misn0230.wav");
	end
	if (M.camera1)
	then
	
		if (CameraPath("fixcam",1200,250,M.lander)  or 
			CameraCancelled() --[[ or  IsAudioMessageDone(M.audmsg)--]])
			--(GetTime()>M.cam_time)))
		then
			M.camera1 = false;	
			M.cam_time = GetTime()+10.0;
			M.camera2 = true;
		end
	end
	if (M.camera2)
	then
			M.camera2 = false;
			M.camera3 = true;
			Goto(M.dummy,"player_path");
			M.cam_time = GetTime()+25.0;
		-- Final actor audio has both tracks in one place
		--	StopAudioMessage(M.audmsg);
	--		M.audmsg = AudioMessage("misn0232.wav");
	end
	if (M.camera3) 
	then	
		if (CameraPath("zoomcam",1200,800,M.dummy) 
			 or  GetTime() > M.cam_time --[[IsAudioMessageDone(M.audmsg)--]]
			 or  CameraCancelled() )
		then
			M.camera3 = false;
			M.cam_time = 99999.0;
			CameraFinish();
			RemoveObject(M.dummy);
			StopAudioMessage(M.audmsg);
			M.audmsg = 0;
			AudioMessage("misn0224.wav");
			M.wave_timer = GetTime()+30.0;
			AddObjective("misn02b1.otf", "WHITE");
		end
	end
	if (		
		( not M.patrol1) and (M.found)
		 and  (GetDistance(M.bhandle,M.bscav)<75.0)

		)
	then
		--VECTOR_3D ted;	
		--ted = GameObjectHandle::GetObj(M.bhandle)->GetPosition();
		BuildObject("svfigh", 2, "spawn1");
		AudioMessage("misn0233.wav");
		M.message1 = true;
		M.patrol1 = true;

		if (( not M.message4) and (M.found2))
		then
			--M.bscout = GetHandle("svfigh-1_M.wingman");
			M.message4 = true;
		end
	end
	if (( not M.message4) and (M.found2))
	then
		-- this is in case the AddObject is called in 
		-- a different frame then the BuildObject() above
		M.message4 = true;
	end
	if ((M.message4) and ( not M.message5) and (GetDistance(M.bscav,M.bhandle2)<200.0))  -- was M.bgoal
	then
		BuildObject("svfigh",2,"spawn2");
--		if (M.bscout ~= nil) Attack(M.bscout,M.bscav,1);
		M.message5 = true;
		M.wave_timer = GetTime()+30.0;
	end
	if ((M.message5) and (GetTime()>M.wave_timer))
	then
		BuildObject("svfigh",2,"spawn2");
		M.wave_timer = GetTime()+45.0;
	end
	if ((M.message1) and (M.message5) and ( not M.message2)  and 
		(
			(M.bscav == nil)  or 
			(GetLastEnemyShot(M.bscav)>0)
		))
	then
		if (M.bscav ~= nil)
		then
			-- send the scav home
			-- M.bscav to bbase
			Follow(M.bscav, M.bhome, 0);
		end

		ClearObjectives();
		AddObjective("misn02b2.otf", "WHITE");
		--[[
			misn0225
			Commander our insturments show that you are heavily
			ounumbered..
		--]]
		AudioMessage("misn0225.wav");
		local bbase = GetHandle("apbase-1_camerapod");
		SetUserTarget(bbase);
		M.message2 = true;
	end
	if (((M.bscav ~= nil) and  -- was M.message2, so we know a scav was built
		(( not IsAlive(M.bplayer))  or  
		( not IsAlive(M.bscav))  or  
		((M.message3) and ( not IsAlive(M.scav2))))
		 or  ( not IsAlive(M.bhome)) 
		 or  ( not IsAlive(M.recycler))
		) 
		 and 
		( not M.mission_lost))
	then
		--[[
			You or the scav is dead
			--]]
		ClearObjectives();
		AddObjective("misn02b4.otf","RED");
		--[[
			misn0227
			Eagle's Nest 1 is being overrun.  
			Our forces are surrendering..
		--]]
		M.audmsg = AudioMessage("misn0227.wav");
		M.mission_lost = true;
	end
	if ((M.mission_lost) and (IsAudioMessageDone(M.audmsg)))
	then
		FailMission(GetTime(),"misn02l1.des");
	end
	if ((IsAlive(M.bplayer))  and 
		((M.message1) and (M.message4)) and 
		(GetDistance(M.bhome,M.bscav)<300.0)
		 and  ( not M.message3))
	then
		--[[
			Now rescue the second
			scavenger
		--]]
		Follow(M.bscav,M.bhome);
		M.wave_timer = GetTime()+45.0;
		M.scav2 = BuildObject("avscav",1,"spawn3");
		SetCritical(M.scav2, true);
		Retreat(M.scav2,"retreat");
		SetObjectiveOn(M.scav2);
		AudioMessage("misn0228.wav");
		M.last_wave_time = GetTime()+10.0;
		M.NextSecond = GetTime()+1.0;
		M.message3 = true;
	end
	if ((IsAlive(M.bscav)) and (M.message3) and (GetTime()>M.NextSecond))
	then
		AddHealth(M.bscav, 200.0);
		M.NextSecond = GetTime()+1.0;
	end
	if (M.last_wave_time<GetTime())
	then
		local sid = BuildObject("svfigh",2,"spawn4");
		Attack(sid,M.scav2);
		M.last_wave_time = 99999.0;
	end
	if	((GetDistance(M.bhome,M.scav2)<200.0)  and 
	(M.message3) and  ( not M.mission_won))
	then
		ClearObjectives();
		AddObjective("misn02b3.otf", "GREEN");
		AddHealth(M.bscav, 1000.0);
		AddHealth(M.scav2, 1000.0);

		--[[
			misn0226
			Good work.  I know you wanted to engage..
		--]]
	--	AudioMessage("misn0226.wav");
		M.audmsg = AudioMessage("misn0234.wav");
		M.mission_won = true;

	end
	if ((M.mission_won) and (IsAudioMessageDone(M.audmsg)))
	then
		SucceedMission(GetTime(),"misn02w1.des");
	end

-- END OF SCRIPT
	
end