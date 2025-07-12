-- Single Player CCA Mission 5 Lua conversion, created by General BlackDragon. 

-- Single Table for all our save/load variables. This SP mission has too many variables to function with them independently. ("main function has > 200 local variables", or "Load having > 197 variables in assignment")
local M = {

-- bools
	camera1 = false,
	start_done = false,
	defender = false,
	com_dead = false,
	last_phase = false,
	third_attack = false,
	fourth_attack = false,
	won = false,
	lost = false,
	second_message = false,
	third_message = false,
	art_dead = false,
	apc_here = false,
-- Floats (really doubles in Lua)
	add_defender = 0,
	wave = 0,
	chaff = 0,
	camera_time = 0,
	apc_wave = 0,
-- Handles
	a1 = nil,
	a2 = nil,
	t1 = nil,
	t2 = nil,
	t3 = nil,
	t4 = nil,
	h1 = nil,
	h2 = nil,
	geyser1 = nil,
	geyser2 = nil,
	recy = nil,
	muf = nil,
	commander = nil,
	--cam1 = nil,
	killme = nil,
-- Ints
	wave_count = 0,
	wave_type = 0,
	aud = 0
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

	M.camera_time = 99999.0;
	M.add_defender = 99999.0;
	M.apc_wave = 99999.0;
	M.wave = 99999.0;
	M.chaff = 99999.0;
	
end

function AddObject(h)

	if (GetTeamNum(h) == 2)
	then
		if (IsOdf(h, "avwalk"))
		then
			M.commander = h;
			--[[
				The first walker is
					"the M.commander"
			--]]
		end
		if ((IsOdf(h,"bvltnk"))  or 
			(IsOdf(h,"bvhraz"))  or 
			(IsOdf(h,"avfigh")))
		then
			Goto(h,M.recy);
		end

	end

end

function Update()

-- START OF SCRIPT

	if ( not M.start_done)
	then
		M.recy = GetHandle("svrecy0_recycler");
		AddScrap(1,10);
		M.camera1 = true;
		M.camera_time = GetTime()+17.0;
		M.apc_wave = GetTime()+70.0;
		M.start_done = true;
		M.t4 = GetHandle("sbhang0_repairdepot");
		M.a1 = BuildObject("avartl",2,"spawn1");
		M.a2 = BuildObject("avartl",2,"spawn2");
		CameraReady();
		M.aud = AudioMessage("misns501.wav");
	end
	if (M.camera1)
	then
		CameraPath("campath",5000,2500,M.t4);
		if ((IsAudioMessageDone(M.aud)) and ( not M.second_message))
		then
			M.aud = AudioMessage("misns503.wav");
			M.second_message = true;
		end
--[[		if ((M.second_message) and (IsAudioMessageDone(M.aud))
			 and  ( not M.third_message))
		then
			M.aud = AudioMessage("misns503.wav");
			M.third_message = true;
		end
--]]
		if ((CameraCancelled())  or   (IsAudioMessageDone(M.aud)))--(GetTime()>M.camera_time))
		then
			M.chaff = GetTime()+180.0;
			M.t1 = GetHandle("sblpow2_powerplant");
			M.t2 = GetHandle("sblpow3_powerplant");
			M.t3 = GetHandle("sblpow4_powerplant");
			M.recy = GetHandle("svrecy0_recycler");
			M.muf = GetHandle("svmuf0_factory");
			M.geyser1 = GetHandle("eggeizr11_geyser");
			M.geyser2 = GetHandle("eggeizr12_geyser");
			Goto(M.recy,M.geyser1);
			Goto(M.muf,M.geyser2);
			Attack(M.a1,M.t1);
			Attack(M.a2,M.t2);
			M.add_defender = GetTime()+10.0;
			CameraFinish();	
			ClearObjectives();
			AddObjective("misns501.otf","WHITE");
			StopAudioMessage(M.aud);
			M.camera1 = false;
		end
	end
	if ((M.defender) and ( not M.third_attack) and ( not IsAlive(M.t1)))
	then
		Attack(M.a1,M.t3);
		M.third_attack = true;
	end
	if ((M.defender) and ( not M.fourth_attack) and ( not IsAlive(M.t2)))
	then
		Attack(M.a2,M.t4);
		M.fourth_attack = true;
	end
	if (GetTime()>M.add_defender)
	then
		BuildObject("avwalk",2,"spawn3");
		-- BuildObject("avtank",2,"spawn3");
		M.add_defender = 99999.0;
		SetPilot(2,30);  -- in case we load AIP
		M.defender = true;
	end
	if ((M.defender) and ( not M.art_dead) and ( not IsAlive(M.a1)) and ( not IsAlive(M.a2)))
	then
		AudioMessage("misns504.wav");
		M.art_dead = true;
	end
	if ((M.defender)  and (M.h1 ~= nil) and ( not M.apc_here)  and 
		(GetDistance(M.h1,M.muf)<100.0)) 
	then
		M.apc_here = true;
		AudioMessage("misns505.wav");
	end
	if (GetTime()>M.chaff)
	then
		M.chaff = GetTime()+50.0 + math.random(0, 3) * 10.0;
		BuildObject("avfigh",2,"spawn5");
	end
	if (GetTime()>M.apc_wave)
	then
		M.h1 = BuildObject("avapc",2,"spawn6");
		M.h2 = BuildObject("avapc",2,"spawn6");
		M.killme = BuildObject("avrecy",2,"spawn7");
		local protect = BuildObject("bvtank",2,"spawn7");
		Defend(protect,M.killme);
		protect = BuildObject("bvtank",2,"spawn7");
		Defend(protect,M.killme);
		Attack(M.h1,M.muf);
		Attack(M.h2,M.muf);
		M.apc_wave = 99999.0;
	end
	if ((M.defender) and ( not IsAlive(M.commander))
		 and  ( not M.com_dead))
	then
		M.wave = GetTime()+120.0;
		M.com_dead = true;
	end
	if (GetTime()>M.wave)
	then
		M.wave_count = M.wave_count + 1;
		M.wave = GetTime()+180.0;
		--M.wave_type = rand()%2
		AudioMessage("misns505.wav");
		if (M.wave_count ~= 1)
		then
			BuildObject("bvltnk",2,"spawn5");
			BuildObject("bvltnk",2,"spawn5");
			BuildObject("bvltnk",2,"spawn5");
		else
			BuildObject("bvhraz",2,"spawn6");
			BuildObject("bvhraz",2,"spawn6");
			BuildObject("bvhraz",2,"spawn6");
		end
		if (M.wave_count == 3)
		then
			--[[
				Build a recycler
				at spawn7 avrecy
				
			--]]
			M.last_phase = true;
--			M.killme = BuildObject("avrecy",2,"spawn7");
			BuildObject("avscav",2,"spawn7");
			BuildObject("avscav",2,"spawn7");
			local sam = BuildObject("spcamr",1,"camera1");
			SetObjectiveOn(M.killme);  -- should be sam
			AddObjective("misns502.otf","WHITE");
			AudioMessage("misns506.wav");
			--[[
				Now LoadAIP.
			--]]
			SetAIP("misns5.aip");
			--[[
				Our intelligence.   
			--]]
		end
	end
	if ((M.last_phase) and ( not IsAlive(M.killme))
		 and  ( not M.won) and ( not M.lost))
	then
		M.won = true;
		AudioMessage("misns508.wav");
		SucceedMission(GetTime()+10.0,"misns5w1.des");
	end
	if (( not IsAlive(M.recy)) and ( not M.lost) and ( not M.won))
	then
		M.lost = true;
		AudioMessage("misns507.wav");
		FailMission(GetTime()+10.0,"misns5l1.des");
	end

-- END OF SCRIPT
	
end