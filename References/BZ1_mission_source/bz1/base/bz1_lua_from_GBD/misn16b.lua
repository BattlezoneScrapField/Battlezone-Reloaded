-- Single Player NSDF Mission 15 Lua conversion, created by General BlackDragon. 

-- Single Table for all our save/load variables. This SP mission has too many variables to function with them independently. ("main function has > 200 local variables", or "Load having > 197 variables in assignment")
local M = {

-- bools
	counter = false,
	start_done = false,
	rcam = false,
	won = false,
	lost = false,
	camera1 = false,
-- Floats (really doubles in Lua)
	next_reinforcement = 0,
	rcam_time = 0,
	start_time = 0,
	alien_wave = 0,
	counter_strike2 = 0,
	wave_gap = 0,
	cam_time1 = 0,
	alien_wave1 = 0,
	--finish_cam = 0,
-- Handles
	base1 = nil,
	base2 = nil,
	--reinfo1 = nil,
	--reinfo2 = nil,
	newbie = nil,
	recy = nil,
	muf = nil,
	audmsg1 = nil,
	audmsg2 = nil,
	cam1 = nil,
	cam2 = nil,
	cam3 = nil,
	cam4 = nil,
	--cam5 = nil,
	sat1 = nil,
	sat2 = nil,
	sat3 = nil,
	tow1 = nil,
	tow2 = nil,
	tow3 = nil,
	tow4 = nil,
-- Ints
	rtype = 0,
	rcount = 0 -- type of reinforcement, count 
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

	M.next_reinforcement = 99999.0;
	M.start_time = 99999.0;
	M.rcam_time = 99999.0;
	M.alien_wave = 99999.0;
	--M.finish_cam = 99999.0;
	M.alien_wave1 = 99999.0;
	M.wave_gap = 150.0;  -- two & a half minutes
	M.counter_strike2 = 999999.0;
    M.cam_time1 = 99999.0;
	
end

function AddObject(h)

	--[[
		Whenever a new soviet unit
		is added, that unit storms
		toward the alien base.  
	--]]
	if 	(GetTeamNum(h) == 1) 
	then
		if
			(
				(IsOdf(h, "svtank"))  or 
				(IsOdf(h,"svturr"))  or 
				(IsOdf(h,"svfigh"))  or 
				(IsOdf(h,"svwalk"))
			)
		then

			if (math.random(0, 1) == 0)
			then
				Attack(h,M.base1,0);
			else 
				Attack(h,M.base2,0);
			end
			M.newbie = h;  -- so we always have one to key on
		else 
			if ((IsOdf(h,"svscav"))  or 	
				(IsOdf(h,"svhaul")))
			then
				if (math.random(0, 1) == 0)
				then
					Goto(h,M.base1,0);
				else 
					Goto(h,M.base2,0);
				end
				M.newbie = h;  -- so we always have one to key on
			end
		end
	end

end

function Update()

-- START OF SCRIPT

	local player = GetPlayerHandle();
	if ( not M.start_done)
	then
		M.audmsg1 = AudioMessage("misn1601.wav");
		M.audmsg2 = AudioMessage("misn1602.wav");
		M.recy = GetHandle("avrecy0_recycler");
		M.rtype = math.random(0, 1) + 1; --rand()%2+1;  -- wimpy reinforcements, type 1 or 0
		M.start_done = true;
		M.base1 = GetHandle("alien_hq");
		M.base2 = GetHandle("alien_hangar");
		SetScrap(1,50);
		SetAIP("misn16.aip");
		ClearObjectives();
		AddObjective("misn1601.otf", "WHITE");
		M.cam1 = GetHandle("apcamr12_camerapod");
		M.cam2 = GetHandle("apcamr15_camerapod");
		M.cam3 = GetHandle("apcamr13_camerapod");
		M.cam4 = GetHandle("apcamr11_camerapod");
		if (M.cam1 ~= nil) then
			SetObjectiveName(M.cam1,"NW Geyser");
		end
		if (M.cam2 ~= nil) then
			SetObjectiveName(M.cam2,"Foothill Geysers");
		end
		if (M.cam3 ~= nil) then 
			SetObjectiveName(M.cam3,"Geyser Site");
		end
		if (M.cam4 ~= nil) then 
			SetObjectiveName(M.cam4,"Alien HQ");
		end
		M.tow1 = GetHandle("sbtowe0_turret");
		M.tow2 = GetHandle("sbtowe1_turret");
		M.tow3 = GetHandle("sbtowe2_turret");
		M.tow4 = GetHandle("sbtowe3_turret");
		M.sat1 = GetHandle("hvsat0_wingman");
		M.sat2 = GetHandle("hvsat1_wingman");
		M.sat3 = GetHandle("hvsat2_wingman");
		if (M.sat1 ~= nil) then
			Defend(M.sat1,1);
		end
		if (M.sat2 ~= nil) then 
			Defend(M.sat2,1);
		end
		if (M.sat3 ~= nil) then
			Defend(M.sat3,1);
		end
		local sav1 = GetHandle("hvsav47_sav");
		if (sav1 ~= nil) then 
			Defend(sav1, 1);
		end

		M.muf = GetHandle("avmuf26_factory");
        M.camera1 = true;
		M.cam_time1 = GetTime()+20.0;
        CameraReady();
	end
    if (M.camera1)
	then
		CameraPath("camera_path1",4000,500,M.base2);
	end
	if ((M.camera1) and (CameraCancelled()  or 
		(GetTime()>M.cam_time1)  or  IsAudioMessageDone(M.audmsg2)))
	then
		M.camera1 = false;
		CameraFinish();

		-- set event times now that the opening cutscene is over
		M.alien_wave = GetTime()+60.0;
		M.alien_wave1 = GetTime()+90.0;
		M.next_reinforcement = GetTime()+120.0;  --should be 120

		-- release the sav
		local sav1 = GetHandle("hvsav47_sav");
		if (sav1 ~= nil) then 
			Stop(sav1, 0);
		end
	end
	if (GetTime()>M.next_reinforcement)
	then
		M.rcount = M.rcount + 1;
		if (M.rcount<10)
		then
			if (M.rtype == 1)
			then
				--[[
					The thriteenth workers 
					hauling battilion
				--]]
				AudioMessage("misn1603.wav");
				BuildObject("svfigh",1,"starta");
				BuildObject("svhaul",1,"starta2");
				BuildObject("svhaul",1,"starta3");
			elseif (M.rtype == 2)
			then
				--[[
					Eighth scrap auxilliries
				--]]
				AudioMessage("misn1604.wav");
				BuildObject("svscav",1,"startb");
				BuildObject("svscav",1,"startb2");
				BuildObject("svfigh",1,"startb3");
			elseif (M.rtype == 3)
			then
				--[[
					Remenants of various units
				--]]
				AudioMessage("misn1605.wav");
				BuildObject("svscav",1,"starta");
				BuildObject("svturr",1,"starta2");
				BuildObject("svfigh",1,"starta3");
			elseif (M.rtype == 4)
			then
				--[[
					A scout unit
				--]]
				AudioMessage("misn1606.wav");
				BuildObject("svfigh",1,"startb");
				BuildObject("svfigh",1,"startb2");
			elseif (M.rtype == 5)
			then
				--[[
					A light armor unit
				--]]
				AudioMessage("misn1607.wav");
				BuildObject("svfigh",1,"starta");
				BuildObject("svfigh",1,"starta2");
				BuildObject("svtank",1,"starta3");
			elseif (M.rtype == 6)
			then
				--[[ 
					A strike wing
				--]]
				AudioMessage("misn1607.wav");
				BuildObject("svtank",1,"startb");
				BuildObject("svtank",1,"startb2");
				BuildObject("svtank",1,"startb3");
			--	BuildObject("svfigh",1,"reinforce24");
			elseif (M.rtype == 7)
			then
				--[[
					Heavy armor
				--]]
				AudioMessage("misn1608.wav");
				BuildObject("svwalk",1,"starta");
				BuildObject("svwalk",1,"starta2");
				BuildObject("svwalk",1,"starta3");
			--	BuildObject("svtank",1,"reinforce14");
			end

			-- all times after the first its random
			M.rtype = math.random(0, 6) + 1; --rand()%7+1;
			M.next_reinforcement = GetTime()+180.0;
			M.start_time = GetTime()+2.0;  -- give time for units to exist
	--	end
	--	else 
	--	then
			--AudioMessage("misn1614.wav");
		end
	end
	if (GetTime()>M.start_time)
	then
		if (IsAlive(player))   -- better safe then sorry
		then
			local enemy = GetNearestEnemy(player);
			if (GetDistance(player,enemy)>150.0)  -- if safe do cineractive
			then
				M.rcam = true;
				M.rcam_time = GetTime()+4.0;
				CameraReady();
			end
		end
		M.start_time = 99999.0;
	end
	if (M.rcam)
	then
		CameraObject(M.newbie,0,2000,3000,M.newbie);
	end
	if (M.rcam and ((M.rcam_time<GetTime())  or  CameraCancelled()))
	then
		M.rcam = false;
		CameraFinish();
		M.rcam_time = 99999.0;
	end

	if (GetTime()>M.alien_wave)
	then
		BuildObject("hvsav",2,M.base2);
		M.alien_wave = GetTime()+M.wave_gap;
		if (M.wave_gap>60.0) then 
			M.wave_gap = M.wave_gap-5.0;
		end
	end
	if (GetTime()>M.alien_wave1)
	then
		local sat = BuildObject("hvsat",2,"sat1");
		Goto(sat,"strike1");
		sat = BuildObject("hvsat",2,"sat2");
		Goto(sat,"strike2");
		M.alien_wave1 = M.alien_wave+90.0;
	end
	--[[	
		If the user
		is winning turn up
		the heat.
	--]]
	if (( not M.won) and ( not M.lost) and ( not M.counter)  and 

		(
		(( not IsAlive(M.tow1)) and ( not IsAlive(M.tow2)))
			 or 
		(( not IsAlive(M.tow3)) and ( not IsAlive(M.tow4)))
			 or  
		( not IsAlive(M.base1))  or  ( not IsAlive(M.base2)))

		)
	then
		--[[
			That means one of the
			entrances is open.
			Counter attack not  not 
		--]]
		local sav1 = BuildObject("hvsav",2,M.base2);
		local sav2 = BuildObject("hvsav",2,M.base2);
--		local sav3 = BuildObject("hvsav",2,M.base2);
		Attack(sav1,M.muf,1);
		Attack(sav2,M.muf,1);
--		Attack(sav3,M.muf,1);
		M.counter = true;
		M.counter_strike2 = GetTime()+120.0;  -- another killer attack
	end
	if (GetTime()>M.counter_strike2)
	then
		local sav1 = BuildObject("hvsav",2,M.base2);
		local sav2 = BuildObject("hvsav",2,M.base2);
--		local sav3 = BuildObject("hvsav",2,M.base2);
		Attack(sav1,M.recy,1);
		Attack(sav2,M.recy,1);
--		Attack(sav1,M.recy,1);
		M.counter_strike2 = 99999.0;
	end
	if (( not M.won) and ( not IsAlive(M.base1)) 
		 and  ( not IsAlive(M.base2)))
	then
		--[[
			We've destroyed the 
			alien building facillity
		--]]

		AudioMessage("misn1613.wav");
		M.won = true;
		SucceedMission(GetTime()+15.0,"misn16w1.des");
	end

	if (( not M.lost) and ( not IsAlive(M.recy)))
	then

		--[[
			We've M.lost the
			utah.  The soviets
			are withdrawing
		--]]

		AudioMessage("misn1612.wav");
		M.lost = true;
		FailMission(GetTime()+15.0,"misn16l1.des");
	end

-- END OF SCRIPT
	
end