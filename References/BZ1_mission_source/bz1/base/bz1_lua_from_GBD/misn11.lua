-- Single Player NSDF Mission 10 Lua conversion, created by General BlackDragon. 

-- Single Table for all our save/load variables. This SP mission has too many variables to function with them independently. ("main function has > 200 local variables", or "Load having > 197 variables in assignment")
local M = {

-- bools
	won = false,
	lost = false,
	launch_gone = false,
	--escape_start = false,
	last_wave = false,
	got_there1 = false,
	got_there2 = false,
	got_there3 = false,
	--escape_path = false,
	start_done = false,
	betrayal = false,
	pursuit_warning = false,
	betrayal_message = false,
	check1 = false,
	check2 = false,
	restart = false,
	launch_attack = false,
-- Floats (really doubles in Lua)
	escape_time = 0,
	last_wave_time = 0,
	--camera_time = 0,
	betrayal_time = 0,
	start_delay = 0,
-- Handles
	player = nil,
	--recy = nil,
	cam1 = nil,
	cam2 = nil,
	cam3 = nil,
	--cam4 = nil,
	tug1 = nil,
	tug2 = nil,
	turr1 = nil,
	turr2 = nil,
	turr3 = nil,
	openh = nil,
	launch = nil,
	launch2 = nil,
	tank1 = nil,
	tank2 = nil
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

	M.betrayal_time = 99999.0;
	M.start_delay = 99999.0;
	M.escape_time = 99999.0;
	M.last_wave_time = 99999.0;

end

function AddObject(h)


end

function Update()

-- START OF SCRIPT

	M.player = GetPlayerHandle();
	if ( not M.start_done)
	then
		--[[
			-paths
			base
			openheimer
			escape
			units
			avhaul0_tug
			avhaul1_tug
			avhaul2_tug
			-camera
			apcamr3_camerapod
			apcamr4_camerapod
			apcamr5_camerapod
		--]]
		--[[
			misn1501.wav
			Now that we've captured the SAV relics
			we need to ransport this key technology
			off of Io.  This could win the war for us.
		--]]
		M.tug1 = GetHandle("avhaul0_tug");
		M.tug2 = GetHandle("avhaul1_tug");
		M.openh = GetHandle("avhaul2_tug");
		M.turr1 = GetHandle("svturr2_turrettank");
		M.turr2 = GetHandle("second_blockade");
		M.turr3 = GetHandle("svturr3_turrettank");
		M.cam1 = GetHandle("apcamr3_camerapod");
		M.cam2 = GetHandle("apcamr4_camerapod");
		M.cam3 = GetHandle("apcamr5_camerapod");
		M.launch = GetHandle("launch_pad");
		M.launch2 = GetHandle("launch_pad2");
		SetObjectiveName(M.cam1, "Waypoint 1");
		SetObjectiveName(M.cam2, "Waypoint 2");
		SetObjectiveName(M.cam3, "Launch Pad");
		SetObjectiveOn(M.tug1); 
		SetObjectiveName(M.tug1, "Transport 1"); 
		Stop(M.tug1, 1);
		SetCritical(M.tug1, true);
		SetObjectiveOn(M.tug2); 
		SetObjectiveName(M.tug2, "Transport 2"); 
		Stop(M.tug2, 1);
		SetCritical(M.tug2, true);
		SetObjectiveOn(M.openh);
		SetObjectiveName(M.openh, "Transport 3"); 
		Stop(M.openh, 1);
		SetCritical(M.openh, true);

		SetUserTarget(M.cam1);
		SetScrap(1,50);
		AudioMessage("misn1101.wav");
		ClearObjectives();
		AddObjective("misn1101.otf","WHITE");
		M.start_delay = GetTime()+15.0;
		M.start_done = true;
	end
	--[[
		Mad Dr. Openheimer 
		has magic shields that
		prevent him from being killer.  
	--]]
	if (IsAlive(M.openh)) then 
		AddHealth(M.openh, 300.0);
	end

	if (GetTime()>M.start_delay)
	then
		--[[
			Moving out not 
		--]]
		AudioMessage("misn1102.wav");
		M.start_delay = 99999.0;
		Goto(M.tug1,"base1",1);
		Goto(M.tug2,"base1",1);
		Goto(M.openh,"base1",1);	-- was originally 0
	end
	--[[
		if (isDamaged(M.tug1)  or  is damaged(M.tug2)
		AudioMessage(misn1402)
		get your ass up here and help us out, etc.
	--]]
	if (( not M.betrayal) and (GetDistance(M.cam1,M.openh)<50.0))
	then
		M.betrayal_time = GetTime()+15.0;  -- when we announce it
		Goto(M.openh,"openheimer",1);
		M.betrayal = true;
	end
	if (GetTime()>M.betrayal_time)
	then
		M.betrayal_time = 99999.0;
		AudioMessage("misn1103.wav");  -- transport 3 seems to be braking off
		AudioMessage("misn1104.wav");  -- farewell capitalist pigs not  not 
		SetTeamNum(M.openh, 2);
		Defend(M.turr1,0);
		Defend(M.turr3,0);
		AudioMessage("misn1105.wav");
		exu.BuildAsyncObject("svfigh",2,"strike1");
		--ObjectList &list = *GameObject::objectList;
		--for (ObjectList::iterator i = list.begin(); i ~= list.end(); i++) 
		--then
		for h in AllCraft() do
			--GameObject *o = *i;
			--local h = GameObjectHandle::Find(o);
			if (IsOdf(h,"svfigh"))
			then
				Goto(h,"strike_path1",0);
			end
			
		end
		M.betrayal_message = true;
		ClearObjectives();
		AddObjective("misn1102.otf","WHITE");
	end
	if ((M.betrayal_message) and ( not M.pursuit_warning)
		 and  (IsAlive(M.turr1)) and (GetDistance(M.turr1,M.player)))
	then
		AudioMessage("misn1106.wav");  -- do not pursue..
		M.pursuit_warning = true;
	end
	if (((GetDistance(M.cam1,M.tug1)<50.0)  or 
		(GetDistance(M.cam1,M.player)<50.0))
		 and  ( not M.check1))
	then
		M.check1 = true;
		SetUserTarget(M.cam2);
	end
	if ((GetDistance(M.tug1,"check2",1)<50.0)  -- was M.cam2
		 and  ( not M.check2))
	then
		--[[
			At this point openheimer
			has escaped..
		--]]
		SetObjectiveOff(M.openh);
		M.check2 = true;
		SetUserTarget(M.cam3);
		AudioMessage("misn1107.wav");
		--[[
			 Now send another enemy
		--]]
		exu.BuildAsyncObject("svfigh",2,"strike2");		
		--ObjectList &list = *GameObject::objectList;
		--for (ObjectList::iterator i = list.begin(); i ~= list.end(); i++) 
		--then
		for h in AllCraft() do
			--GameObject *o = *i;
			--local h = GameObjectHandle::Find(o);
			if (IsOdf(h,"svfigh"))
			then
				Goto(h,"strike_path2",0);
			end
		end
	end
	if ((M.check2) and ( not M.restart) and ( not IsAlive(M.turr2)))
	then
		AudioMessage("misn1102.wav");
		Goto(M.tug1,"base2",1);
		Goto(M.tug2,"base2",1);
		M.restart = true;
	end
	if ((M.restart) and ( not M.launch_attack)  and 
		(
			(GetDistance(M.launch,M.player)<450.0)
			 or 
			(GetDistance(M.launch,M.tug1)<450.0))
		)
	then
		M.tank1 = exu.BuildAsyncObject("svtank",2,"launch_attack");
		M.tank2 = exu.BuildAsyncObject("svtank",2,"launch_attack");
		AddHealth(M.launch, -0.90);
		AudioMessage("misn1108.wav");
		Attack(M.tank1,M.launch,1);
		Attack(M.tank2,M.launch,1);
		--[[
		ObjectList &list = *GameObject::objectList;
		for (ObjectList::iterator i = list.begin(); i ~= list.end(); i++) 
		then
			GameObject *o = *i;
			local h = GameObjectHandle::Find(o);
			if (IsOdf(h,"svtank"))
			then
				Attack(h,M.launch,1); -- attack the M.launch pad
			end
			
		end
		--]]
		M.launch_attack = true;
	end
	if ((M.launch_attack) and ( not IsAlive(M.launch))
		 and ( not M.launch_gone))
	then
		AudioMessage("misn1109.wav");
		M.launch_gone = true;
		M.escape_time = GetTime()+40.0;
	end
	--[[
		If both tanks die
		and somehow
		the M.launch pad is ok..
		It's not not 
	--]]
	if ((M.launch_attack) and ( not IsAlive(M.tank1)) and ( not IsAlive(M.tank2)) 
		 and  (IsAlive(M.launch)))
	then
		RemoveObject(M.launch);
		M.launch_gone = true;
		M.escape_time = GetTime()+10.0;
	end
	if ((M.launch_gone) and (GetTime()>M.escape_time))
	then
		Goto(M.tug1,"escape");
		Goto(M.tug2,"escape");
		AudioMessage("misn1110.wav");
		SetObjectiveOn(M.launch2);
		ClearObjectives();
		AddObjective("misn1103.otf","WHITE");
		SetObjectiveName(M.launch2,"Launch Pad 2");
		M.escape_time = 99999.0;
 		--M.escape_start = true;
		M.last_wave_time = GetTime()+15.0;
	end
	if (( not M.last_wave) and (M.last_wave_time<GetTime()))
	then
		exu.BuildAsyncObject("svfigh",2,"strike2");
		exu.BuildAsyncObject("svfigh",2,"strike2");
		--ObjectList &list = *GameObject::objectList;
		--for (ObjectList::iterator i = list.begin(); i ~= list.end(); i++) 
		--then
		for h in AllCraft() do
			--GameObject *o = *i;
			--local h = GameObjectHandle::Find(o);
			if (IsOdf(h,"svfigh"))
			then
				Attack(h,M.tug2,1); -- attack the M.launch pad
			end
			
		end
		-- we put this one in later
		-- cuz we want it to wait
		local last_guy = exu.BuildAsyncObject("svfigh",2,M.launch2);
		Attack(last_guy,M.player);
		exu.BuildAsyncObject("apcamr",1,"last_camera");
		M.last_wave = true;
		M.last_wave_time = 99999.0;
	end
	if (( not M.lost) and 
		(
			(( not IsAlive(M.tug1))  or  ( not IsAlive(M.tug2)))
			 or  
			(( not M.betrayal) and ( not IsAlive(M.openh)))
		 )
		)
	then
		if (M.betrayal)
		then
			ClearObjectives();
			AddObjective("misn1102.otf","WHITE");
		end
		AudioMessage("misn1111.wav");
		AudioMessage("misn1112.wav");
		M.lost = true;
		FailMission(GetTime()+15,"misn11l1.des");
			
	end
	if ((M.last_wave) and ( not M.got_there1) and 
		(GetDistance(M.player,M.launch2)<200.0))
	then
		M.got_there1 = true;
		-- we do each check seperately in case
		-- the vehicles get to safety & leave
	end
	if ((M.last_wave) and ( not M.got_there2)  and 
		(GetDistance(M.tug1,M.launch2)<200.0))
	then
		M.got_there2 = true;
	end
	if ((M.last_wave) and ( not M.got_there3)  and 
		(GetDistance(M.tug2,M.launch2)<200.0))
	then
		M.got_there3 = true;
	end
	if (( not M.won) and (M.last_wave) 
		 and  (IsAlive(M.tug1)) and (IsAlive(M.tug2))  and 
		(M.got_there1) and (M.got_there2) and (M.got_there3))
	then
		AudioMessage("misn1113.wav");
		M.won = true;
		SucceedMission(GetTime()+15,"misn11w1.des");
	end

-- END OF SCRIPT
	
end