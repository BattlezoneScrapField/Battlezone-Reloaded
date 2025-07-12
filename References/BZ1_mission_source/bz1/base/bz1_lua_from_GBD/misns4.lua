-- Single Player CCA Mission 4 Lua conversion, created by General BlackDragon. 

-- Single Table for all our save/load variables. This SP mission has too many variables to function with them independently. ("main function has > 200 local variables", or "Load having > 197 variables in assignment")
local M = {

-- bools
	counter = false,
	first = false,
	--first_bridge = false,
	warning = false,
	bridge_clear = false,
	won = false,
	--lost = false,
	start_done = false,
	north_bridge = false,
	convoy_alive = { }, --[10] = false,
	safe = { }, --[10] = false,
-- Floats (really doubles in Lua)
	wakeup_time = 0,
	convoy_time = 0,
	--attack_time = 0,
	raider_time = 0,
	army_time = 0,
	counter_time = 0,
-- Handles
	convoy_handle = { }, --[10] = nil,
	cam1 = nil,
	t1 = nil,
	t2 = nil,
	b1 = nil,
	--b2 = nil,
	--h1 = nil,
	--h2 = nil,
	counter1 = nil,
	counter2 = nil,
	counter3 = nil,
	counter4 = nil,
-- Ints
	convoy_total = 0,
	convoy_count = 0,
	convoy_dead = 0,
	win_count = 0
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

	M.wakeup_time = 99999.0;
	M.raider_time = 99999.0;
	M.convoy_time = 99999.0;
	--M.attack_time = 99999.0;
	M.counter_time = 99999.0;
	M.convoy_total = 5;

	--local count;
	for count = 1, M.convoy_total do
		M.convoy_alive[count] = true;
	end

end

function AddObject(h)


end

function Update()

-- START OF SCRIPT

	local player = GetPlayerHandle();
	local count;
	--[[
		Notes
		'escort' is the path you need to escort 
		things down
		'spawn1' is where they start
		'spawn2' is where enemy artillery starts
		'spawn3' is where enemy tanks, etc. start
	--]]
	
	if ( not M.start_done)
	then
		M.start_done = true;
		M.convoy_time = GetTime()+420.0;
		M.wakeup_time = GetTime()+30.0;
		BuildObject("avartl",2,"spawn2");
		M.cam1 = BuildObject("spcamr",1,"camerapt");
		M.raider_time = GetTime()+30.0;
		M.army_time = GetTime()+100.0;
		AddScrap(1,50);
		SetPilot(1,30);
		SetPilot(2,30);
		ClearObjectives();
		AddObjective("misns4.otf","WHITE");
		AudioMessage("misns401.wav");
		StartCockpitTimer(420,300,0);	
		SetObjectiveName(M.cam1, "Bridge");
		BuildObject("abtowe",2,"tower1");
		BuildObject("abtowe",2,"tower2");
		BuildObject("ablpow",2,"power1");
		BuildObject("ablpow",2,"power2");
		BuildObject("svcnst",1,"svcnst");
	end
	if (GetTime()>M.wakeup_time)
	then
		local h = BuildObject("avfigh",2,"spawn4");
		Goto(h,"wakeup"); -- a little reminder
		M.wakeup_time = 99999.0;
	end
	if (GetTime()>M.convoy_time)
	then
		if ( not M.first)
		then
			AudioMessage("misns402.wav");
			StopCockpitTimer();
			HideCockpitTimer();
			M.first = true;
		end
		local hauler = BuildObject("svhaul",1,"spawn1");
		M.convoy_count = M.convoy_count + 1;
		M.convoy_handle[M.convoy_count] = hauler;
		Goto(hauler,"escort");
		SetObjectiveOn(hauler);
		SetCritical(hauler, true);
		if (M.convoy_count<M.convoy_total)
		then
			M.convoy_time = GetTime()+45.0;
		else
			M.convoy_time = 99999.0;
		end
	end
	if (GetTime()>M.raider_time)
	then
		BuildObject("avfigh",2,"spawn4");
		BuildObject("avfigh",2,"spawn4");
	--	BuildObject("avltnk",2,"spawn4");
		M.raider_time = 99999.0;
	end
	if (GetTime()>M.army_time)
	then
		M.t1 = BuildObject("avtank",2,"sbridge");
		M.t2 = BuildObject("avtank",2,"sbridge");
		M.b1 = BuildObject("avhraz",2,"sbridge");
	--	M.b2 = BuildObject("avhraz",2,"sbridge");
		M.army_time = 99999.0;
	end

	--[[
		At some point later
		add more forces north
		of the bridge
		at spawn3
	--]]
	if (( not M.north_bridge)  and 
		(GetDistance(player,"sbridge")<200.0))
	then
		M.north_bridge = true;
	--	BuildObject("avtank",2,"spawn3");
		BuildObject("avltnk",2,"spawn3");
		BuildObject("avturr",2,"spawn3");
		BuildObject("avscav",2,"spawn3");
		BuildObject("avrecy",2,"spawn3");
		--[[
			Now load an AIP.
		--]]
	end
	if (( not M.bridge_clear)  and 
		(M.north_bridge)  and 
		( not IsAlive(M.t1)) and ( not IsAlive(M.t2)) 
		 and  ( not IsAlive(M.b1)))
	then
		AudioMessage("misns405.wav");  -- wrong message..
		M.bridge_clear = true;
		SetAIP("misns4.aip");
		M.counter_time = GetTime()+150.0;  -- M.counter attack in 2 1/2 minutes
	end
	if (( not M.warning) and 
		(GetDistance(player,"warn1")<200.0))
	then
		AudioMessage("misns409.wav");
		M.warning = true;
	end
	if ((IsAlive(M.convoy_handle[2])) 
		 and  ( not M.counter)  and 
		((GetTime()>M.counter_time)  or  
		(GetDistance(M.convoy_handle[2],"warn1")<200.0))
		)

	then
		M.counter1 = BuildObject("avrckt",2,"counter");
		M.counter2 = BuildObject("avrckt",2,"counter");
		M.counter3 = BuildObject("avrckt",2,"counter");
		M.counter4 = BuildObject("avrckt",2,"counter");
		Goto(M.counter1,"sbridge");
		Goto(M.counter2,"sbridge");
		Goto(M.counter3,"sbridge");
		Goto(M.counter4,"sbridge");
		M.counter = true;
		M.counter_time = 99999.0;
	end
	for count = 1, M.convoy_total do
		if (M.convoy_handle[count] ~= nil)
		then
			if (( not IsAlive(M.convoy_handle[count]))
				 and  (M.convoy_alive[count]))
			then
				--[[
					Another one bites the dust
					AudioMessage("transport dead..")
				--]]
				AudioMessage("misns403.wav");
				M.convoy_alive[count] = false;
				M.convoy_dead = M.convoy_dead + 1;
				if (M.convoy_dead>M.convoy_total/3)
				then
					--[[
						That's it
						AudioMessage()
					--]]
					FailMission(GetTime()+15.0,"misns4l1.des");
					--[[
						Cineractive 
						on neareset guy to
						the dying guy
					--]]
				end


			end
		end
		if ((GetDistance(M.convoy_handle[count],"goal")<100.0) and ( not M.safe[count]))
		then
			M.safe[count] = true;
			M.win_count = M.win_count + 1;
		end

	end
	if ((M.win_count == M.convoy_total-1) and ( not M.won))
	then
		SucceedMission(GetTime()+10.0,"misns4w1.des");
		M.won = true;
	end

-- END OF SCRIPT
	
end