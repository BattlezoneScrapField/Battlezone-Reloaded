-- Single Player Training Mission 1 Lua conversion, created by General BlackDragon.  --Special Thanks to Mario for help with the p# arrays.

-- Single Table for all our save/load variables. This SP mission has too many variables to function with them independently. ("main function has > 200 local variables", or "Load having > 197 variables in assignment")
local M = {

-- bools
	start_done = false,
	hop_in = false,
	--first_objective = false,
	--second_objective = false,
	--third_objecitve = false,
	combat_start = false,
	combat_start2 = false,
	start_path1 = false,
	start_path2 = false,
	start_path3 = false,
	start_path4 = false,
	hint1 = false,
	hint2 = false,
	done_message = false,
	jump_start = false,
	lost = false,
-- Floats (really doubles in Lua)
	repeat_time = 0,
	forgiveness = 0,
	jump_done = 0,
-- Handles
	get_in_me = nil,
	target = nil,
	target2 = nil,
-- AiPaths
	p1 = { },
	p2 = { },
	p3 = { },
	p4 = { },
-- Ints
	aud = 0,
	num_reps = 0,
	on_point = 0,
	
	p1count = 0,
	p2count = 0,
	p3count = 0,
	p4count = 0
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

	M.forgiveness=40.0;

end

function AddObject(h)


end

function Update()

-- START OF SCRIPT

	--GameObject *player = GameObject::GetUser();
	--local player_handle = GetPlayerHandle();
	--VECTOR_2D player2d;
	local player_handle = GetPlayerHandle();
	local player2d;
	
	if (IsAlive(player_handle)) then 
		player2d = GetPosition(player_handle);
	end
	
	if (not M.start_done)
	then
--		M.start_done = true;
		M.get_in_me = GetHandle("avfigh0_wingman");
		M.aud = AudioMessage("misn0101.wav");
		--p1 = AiPath::Find("path_1");
		--p2 = AiPath::Find("path_2");
		--p3 = AiPath::Find("path_3");
		--p4 = AiPath::Find("path_5");
		M.p1count = GetPathPointCount("path_1")
		for i = 0, M.p1count-1 do M.p1[i+1] = GetPosition("path_1", i) end
		M.p2count = GetPathPointCount("path_2")
		for i = 0, M.p2count-1 do M.p2[i+1] = GetPosition("path_2", i) end
		M.p3count = GetPathPointCount("path_3")
		for i = 0, M.p3count-1 do M.p3[i+1] = GetPosition("path_3", i) end
		M.p4count = GetPathPointCount("path_5")
		for i = 0, M.p4count-1 do M.p4[i+1] = GetPosition("path_5", i) end
		M.target = GetHandle("svturr0_turrettank");
		SetPilotClass(M.target, "");
		M.target2 = GetHandle("svturr1_turrettank");
		SetPilotClass(M.target2, "");
		M.start_done = true;
		M.repeat_time = GetTime()+30.0;
		ClearObjectives();
		AddObjective("misn0101.otf","WHITE");
		AddObjective("misn0103.otf","WHITE");
		M.num_reps = 0;
	end

	local first = M.target;
	if ((not M.start_path1) and (GetTime()>M.repeat_time))
	then
		M.repeat_time = GetTime()+20.0;
		ClearObjectives();
		AddObjective("misn0101.otf","GREEN");

		--		M.aud = AudioMessage("misn0101.wav");
		M.num_reps = M.num_reps + 1;
	end
	if (not M.start_path1)		
	then
		-- how far are we from the start..
		--VECTOR_2D diff =  Vec2D_Subtract(p1->points[0],player2d);
		local diff = (M.p1[1] - player2d);
		diff.y = 0;
		if (Length(diff)<M.forgiveness)
		then
			-- we've started
			if ((player_handle ~= M.get_in_me)
				 and  (not M.hop_in))
			then
				M.hop_in = true;
				StopAudioMessage(M.aud);
				AudioMessage("misn0122.wav");
			else
				ClearObjectives();
				AddObjective("misn0101.otf","GREEN");
				AddObjective("misn0103.otf","WHITE");

			end
			StartCockpitTimerUp(0,300,240);
			M.repeat_time = 0.0;
			M.num_reps = 0;
			M.start_path1 = true;
			M.on_point = 1;
		end
	end
	if ((M.start_path1) and (not M.start_path2) and (player_handle == M.get_in_me))
	then
		-- are we out of range of current point?
		local diff = (M.p1[M.on_point] - player2d);
		diff.y = 0;
		local x = Length (diff);
		if ((Length(diff)>M.forgiveness) and (GetTime()>M.repeat_time))
		then
			-- tell player to get back where he was before
			AudioMessage("misn0103.wav");
			if ((not IsAlive(M.target))  and 
				(not IsAlive(M.target2)) and (not M.lost))
			then
				M.lost = true;
				FailMission(GetTime()+5.0,"misn01l1.des");
			end
			M.repeat_time = GetTime()+15.0;
			M.num_reps = M.num_reps + 1;
		end
		local diff2 = (M.p1[M.on_point+1] - player2d);
		diff2.y = 0;
		if (Length(diff2)<Length(diff))
		then
			-- time to switch where we are on the path
			M.on_point = M.on_point + 1;
			if (M.on_point == M.p1count)
			then
				M.start_path2 = true;
				M.on_point = 1;
			end
		end
	end
	if ((M.start_path2) and (not M.start_path3))
	then
		-- are we out of range of current point?
		local diff = (M.p2[M.on_point] - player2d);
		diff.y = 0;
		local x = Length(diff);
		if ((Length(diff)>M.forgiveness) and (GetTime()>M.repeat_time))
		then
			-- tell player to get back where he was before
			AudioMessage("misn0103.wav");
			if ((not IsAlive(M.target))  and 
				(not IsAlive(M.target2)) and (not M.lost))
			then
				M.lost = true;
				FailMission(GetTime()+5.0,"misn01l1.des");
			end
			M.repeat_time = GetTime()+15.0;
			M.num_reps = M.num_reps + 1;
		end
		local diff2 = (M.p2[M.on_point+1] - player2d);
		diff2.y = 0;
		if (Length (diff2)<Length(diff))
		then
			-- time to switch where we are on the path
			M.on_point = M.on_point + 1;
			if (M.on_point == M.p2count)
			then
				M.start_path3 = true;
				AudioMessage("misn0104.wav");
				M.on_point = 1;
			end
		end
		
	end
	if ((M.start_path3) and (not M.jump_start))
	then
		-- are we out of range of current point?
		--VECTOR_2D diff = Vec2D_Subtract(p3->points[M.on_point],player2d);
		local diff = (M.p3[M.on_point] - player2d);
		diff.y = 0;
		local x = Length(diff);
		if ((Length(diff)>M.forgiveness) and (GetTime()>M.repeat_time))
		then
			-- tell player to get back where he was before
			AudioMessage("misn0103.wav");
			if ((not IsAlive(M.target))  and 
				(not IsAlive(M.target2)) and (not M.lost))
			then
				M.lost = true;
				FailMission(GetTime()+5.0,"misn01l1.des");
			end
			M.repeat_time = GetTime()+15.0;
			M.num_reps = M.num_reps + 1;
		end
		--VECTOR_2D diff2 = Vec2D_Subtract(p3->points[M.on_point+1],player2d);
		local diff2 = (M.p3[M.on_point+1] - player2d);
		diff2.y = 0;
		if (Length(diff2)<Length(diff))
		then
			-- time to switch where we are on the path
			M.on_point = M.on_point + 1;
			if (M.on_point == M.p3count)
			then
				M.jump_start = true;
				M.jump_done = GetTime()+8.0;
			end
		end
		
	end
	if ((M.jump_start) and (not M.hint1) and (GetTime()>M.jump_done))
	then

		M.repeat_time = GetTime()+45.0;  -- grace period to continue
		AudioMessage("misn0105.wav");
		M.forgiveness = M.forgiveness * 1.5;  -- for the jumps you'll need it
		AudioMessage("misn0107.wav");
		M.hint1 = true;
	end
	if (not M.start_path4)		
	then
		-- how far are we from the start..
		--VECTOR_2D diff =  Vec2D_Subtract(p4->points[0],player2d);
		local diff = (M.p4[1] - player2d);
		diff.y = 0;
		if (Length(diff)<M.forgiveness)
		then
			-- we've started
			M.repeat_time = 0.0;
			M.num_reps = 0;
			M.start_path4 = true;
			M.on_point = 1;
			--[[
				In case the player is
				developmentally 
				disabled.
			--]]
			if (player_handle ~= M.get_in_me)
			then
					AudioMessage("misn0122.wav");
			end
		end

	end
	if ((M.start_path4) and (not M.combat_start))
	then
		-- are we out of range of current point?
		--VECTOR_2D diff = Vec2D_Subtract(p4->points[M.on_point],player2d);
		local diff = (M.p4[M.on_point] - player2d);
		diff.y = 0;
		local x = Length(diff);
		if ((Length(diff)>M.forgiveness) and (GetTime()>M.repeat_time))
		then
			-- tell player to get back where he was before
			AudioMessage("misn0108.wav");
			M.repeat_time = GetTime()+15.0;
			M.num_reps = M.num_reps + 1;
		end
		--VECTOR_2D diff2 = Vec2D_Subtract(p4->points[M.on_point+1],player2d);
		local diff2 = (M.p4[M.on_point+1] - player2d);
		if (Length(diff2)<Length(diff))
		then
			-- time to switch where we are on the path
			M.on_point = M.on_point + 1;
			if (M.on_point == M.p4count)
			then
				StopCockpitTimer();
				M.combat_start = true;
				SetObjectiveOn(M.target);
				SetObjectiveName(M.target, "Combat Training");
				AudioMessage("misn0109.wav");
			end
		end
		
	end
	if ((M.combat_start) and (not M.hint2) and (IsAlive(M.target))) 
	then 
		if  
			(Distance3DSquared(GetPosition(first), GetPosition(player))
			< 100.0 * 100.0)
		then
			HideCockpitTimer();
			AudioMessage("misn0111.wav");
			M.hint2 = true;
		end
	end

	if ((not M.combat_start2) and 
		(not IsAlive(M.target)) and (IsAlive(M.target2)))
	then
		SetObjectiveOn(M.target2);
		SetObjectiveName(M.target2, "Combat Training 2");
		AudioMessage("misn0113.wav");
		M.combat_start2 = true;
	end

	if ((not M.done_message)  and 
		(not IsAlive(M.target))
		 and  (not IsAlive(M.target2)))
	then
		AudioMessage("misn0121.wav");
		M.done_message = true;
		SucceedMission(GetTime()+10,"misn01w1.des");
	end
	if ((M.num_reps>4) and (not M.lost))
	then
		M.repeat_time = 99999.0;
		ClearObjectives();
		AddObjective("misn0102.otf","RED");
		AudioMessage("misn0123.wav");
		FailMission(GetTime()+10,"misn01l1.des");
		M.num_reps = 0;
	end

-- END OF SCRIPT
	
end