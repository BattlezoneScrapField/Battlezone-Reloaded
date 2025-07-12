-- Single Player Training Mission 2 Lua conversion, created by General BlackDragon. 

-- Single Table for all our save/load variables. This SP mission has too many variables to function with them independently. ("main function has > 200 local variables", or "Load having > 197 variables in assignment")
local M = {

-- bools
	lost = false,
	go_reminder = false,
	start_done = false,
	--first_objective = false,
	--second_objective = false,
	--third_objecitve = false,
	--combat_start = false,
	--combat_start2 = false,
	--start_path1 = false,
	--start_path2 = false,
	--start_path3 = false,
	--start_path4 = false,
	hint1 = false,
	hint2 = false,
	--first_selection = false,
	second_selection = false,
	third_selection = false,
	thirda_selection = false,
	fourth_selection = false,
	fifth_selection = false,
	end_message = false,
	--jump_start = false,
-- Floats (really doubles in Lua)
	hint_delay = 0,
	repeat_time = 0,
-- Handles
	turret = nil,
	pointer = nil,
	haul1 = nil,
	haul2 = nil,
-- Ints
	--num_reps = 0,
	message = 0,
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
	
	
	M.turret = GetHandle("avturr-1_turrettank");
	M.pointer = GetHandle("nparr-1_i76building");
	M.haul1 = GetHandle("avhaul-1_tug");
	SetPilotClass(M.haul1, "");
	M.haul2 = GetHandle("avhaul19_tug");
	SetPilotClass(M.haul2, "");
	
	M.hint_delay = 99999.0;
	M.repeat_time = 99999.0;

end

function PlayReminder(time, message)

	local new_time = time;
	if (GetTime()>time)
	then		
		new_time = GetTime()+15.0;
		if (M.message == 1) then
			M.aud = AudioMessage("tran0202.wav");
		elseif (M.message == 2) then
			M.aud = AudioMessage("tran0203.wav");
		elseif (M.message == 3) then
			M.aud = AudioMessage("tran0204.wav");
		elseif (M.message == 4) then
			M.aud = AudioMessage("tran0211.wav");
		elseif (M.message == 5) then
			M.aud = AudioMessage("tran0206.wav");
		elseif (M.message == 6) then
			M.aud = AudioMessage("misn0109.wav");
		elseif (M.message == 7) then
			M.aud = AudioMessage("tran0207.wav");
		elseif (M.message == 8) then 
			M.aud = AudioMessage("tran0208.wav");
			new_time = 99999.0;  -- we're done
		end
	end
	return new_time;
end

function AddObject(h)


end

function Update()

-- START OF SCRIPT

	if (IsAlive(M.turret))
	then
		M.repeat_time = PlayReminder(M.repeat_time,M.message);
		if ( not M.start_done)
		then
			SetObjectiveOn(M.turret);
			SetObjectiveName(M.turret, "Turret");
			M.aud = AudioMessage("tran0201.wav");
			M.hint_delay = GetTime()+10.0;
			ClearObjectives();
			AddObjective("tran0201.otf","GREEN");
			M.start_done = true;
		end
		if ( not M.second_selection and IsAudioMessageDone(M.aud))
		then
			-- was
			-- AudioMessage("tran0202.wav");
			M.aud = AudioMessage("tran0204.wav"); 
			M.hint_delay = 99999.0;
			M.repeat_time = GetTime()+30.0;
			M.message = 3;  -- was 1
			-- new 
			M.second_selection = true;
		end
		if (( not M.thirda_selection)  and 
			(M.second_selection)  and 
			(LastGameKey == "2")) --(controlPanel.GetCurrentItem() == 2)) -- No Lua access to controlPanel activation detection :( Read if they pressed 2 last. -GBD 
		then
			StopAudioMessage(M.aud);
			M.aud = AudioMessage("tran0205.wav");
		--	AudioMessage("tran0211.wav");
			M.thirda_selection = true;
			M.repeat_time = GetTime()+30.0;
			M.message = 4;
		end
	
		if (( not M.third_selection)  and 
			(M.second_selection)  and 
			(IsSelected(M.turret)))
		then
			StopAudioMessage(M.aud);
			M.aud = AudioMessage("tran0206.wav");
			SetObjectiveOff(M.turret);
			SetObjectiveOn(M.pointer);
			SetObjectiveName(M.pointer, "Target Range");
			M.third_selection = true;
			M.repeat_time = GetTime()+30.0;
			M.message = 5;	
		end
		if ((M.third_selection) and ( not M.go_reminder)  and 
			( not IsSelected(M.turret)))
		then
			StopAudioMessage(M.aud);
			M.aud = AudioMessage("misn0109.wav"); -- good job now head for the target range
			M.go_reminder = true;
			M.repeat_time = GetTime()+30.0;
			M.message = 6;
		end
		if ((M.third_selection) and 
			( not M.hint1)  and 
			(GetDistance(M.pointer, M.turret) < 100.0)) --(Dist3D_Squared(GameObjectHandle::GetObj(M.pointer)->GetPosition(), GameObjectHandle::GetObj(M.turret)->GetPosition()) < 100.0 * 100.0))
		then
			AudioMessage("tran0207.wav");
			M.aud = AudioMessage("tran0212.wav"); -- press 2
			M.hint1 = true;
			M.repeat_time = GetTime()+30.0;
			M.message = 7;
		end
		if ((M.hint1) and ( not M.hint2)  and 
				(LastGameKey == "2")) --(controlPanel.GetCurrentItem() == 2)) -- No Lua access to controlPanel activation detection :( Read if they pressed 2 last. -GBD 
		then
			M.hint2 = true;
			StopAudioMessage(M.aud);
			M.aud = AudioMessage("tran0211.wav");  -- press 1
			M.repeat_time = GetTime()+20.0;
			M.message = 4;
		end
		if ((M.hint1)  and 
			( not M.fourth_selection)  and 
			(IsSelected(M.turret)))
		then
			StopAudioMessage(M.aud);
			M.aud = AudioMessage("tran0208.wav");
			M.fourth_selection = true;
			M.repeat_time = GetTime()+30.0;
			M.message = 8;
		end
		if ((M.fourth_selection)  and 
			( not M.fifth_selection)  and 
			(GetCurrentCommand(M.turret) == AiCommand.GO))
		then
			M.repeat_time = 99999.0; -- we're done repeating
			StopAudioMessage(M.aud);
			M.aud = AudioMessage("tran0209.wav");	
			if (IsAlive(M.haul1))
			then
				SetObjectiveOff(M.pointer);
				Goto(M.haul1, M.turret, 1);
				SetObjectiveOn(M.haul1);
				SetObjectiveName(M.haul1, "Target Drone");
			else 
				FailMission(GetTime()+2.0,"tran02l1.des");
			end
			M.fifth_selection = true;
		end
		if ((M.fifth_selection)  and 
			( not M.end_message)  and 
			(not IsAlive(M.haul1))) --(M.haul1 == nil)) -- Lua IsAlive doesn't zero out the handle.
		then
			StopAudioMessage(M.aud);
			M.aud = AudioMessage("tran0210.wav");
			M.end_message = true;
			SucceedMission(GetTime()+10.0,"tran02w1.des");
		end
	else
		if ( not M.lost)
		then
			M.lost = true;
			FailMission(GetTime()+5.0,"tran02l1.des");
		end
	end

-- END OF SCRIPT
	
end