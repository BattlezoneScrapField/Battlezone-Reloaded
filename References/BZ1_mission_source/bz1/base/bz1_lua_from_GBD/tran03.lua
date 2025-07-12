-- Single Player Training Mission 3 Lua conversion, created by General BlackDragon. 

-- Single Table for all our save/load variables. This SP mission has too many variables to function with them independently. ("main function has > 200 local variables", or "Load having > 197 variables in assignment")
local M = {

-- bools
	found = false,
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
	--hint1 = false,
	--hint2 = false,
	first_message = false,
	second_message = false,
	third_message = false,
	fourth_message = false,
	fifth_message = false,
	fifthb_message = false,
	sixth_message = false,
	seventh_message = false,
	eighth_message = false,
	scav_died = false,
	--jump_start = false,
-- Floats (really doubles in Lua)
	delay_message = 0,
-- Handles
	scav = nil,
	attacker = nil,
	geyser = nil,
	recycler = nil,
-- Ints
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

	M.delay_message = 99999.0;

end

function AddObject(h)

	if (
		(GetTeamNum(h) == 1) and
		(IsOdf(h, "avscav"))
		)
	then
		M.found = true;
		M.scav = h;
	end

end

function Update()

-- START OF SCRIPT

	if ( not M.start_done)
	then
		AudioMessage("tran0301.wav");
		M.aud = AudioMessage("tran0302.wav");
		M.geyser = GetHandle("eggeizr111_geyser");
		M.recycler = GetHandle("avrecy-1_recycler");
		M.attacker = GetHandle("avfigh-1_wingman");
		SetPilotClass(M.attacker, "");
		SetIndependence(M.attacker, 0);
		SetObjectiveOn(M.recycler);
		SetObjectiveName(M.recycler,"recycler");
		SetScrap(1,7);
		ClearObjectives();
		AddObjective("tran0301.otf","WHITE");
		AddObjective("tran0302.otf","WHITE");

		M.start_done = true;
	end
	
	if ((M.start_done)  and 
		( not M.first_message)	 and  
		IsAlive(M.recycler)  and 
	(IsSelected(M.recycler)))
	then
		StopAudioMessage(M.aud);
		M.aud = AudioMessage("tran0303.wav");
		--[[
			Switch objective 
		--]]
		SetObjectiveOff(M.recycler);
		SetObjectiveOn(M.geyser);
		SetObjectiveName(M.geyser, "Check Point 1");
		M.first_message = true;
	end

	if ((M.first_message)  and 
		( not M.second_message) and (IsAlive(M.recycler)))
	then
		if ( not IsDeployed(M.recycler))
		then
			StopAudioMessage(M.aud);
			M.aud = AudioMessage("tran0304.wav");
			M.second_message = true;
		end
	end

	if ((M.second_message)
		 and  ( not M.third_message) and (IsAlive(M.recycler))
		 and  (GetDistance(m.geyser, M.recycler) < 200.0)) --(Dist3D_Squared(GameObjectHandle::GetObj(M.geyser)->GetPosition(), GameObjectHandle::GetObj(M.recycler)->GetPosition()) < 200.0 * 200.0))
	then
	--	ClearObjectives();
	--	AddObjective("tran0301.otf","GREEN");
		StopAudioMessage(M.aud);
		M.aud = AudioMessage("tran0305.wav");
		M.third_message = true;
	end
	if ((M.third_message)  and 
		( not M.fourth_message) and (IsAlive(M.recycler))  and 
		(IsSelected(M.recycler)))
	then
		StopAudioMessage(M.aud);
		M.aud = AudioMessage("tran0306.wav");
		M.fourth_message = true;
	end

	if ((M.third_message)  and 
		( not M.fifth_message) and (IsAlive(M.recycler)))
	then
		if (IsDeployed(M.recycler))
		then
			SetObjectiveOff(M.geyser);
			ClearObjectives();
			AddObjective("tran0301.otf","GREEN");
			AddObjective("tran0302.otf","WHITE");

			StopAudioMessage(M.aud);
			M.aud = AudioMessage("tran0307.wav");
			M.fifth_message = true;
		end
	end
	if ((M.fifth_message) and ( not M.fifthb_message)  and 
		(IsSelected(M.recycler)))
	then
		StopAudioMessage(M.aud);
		M.aud = AudioMessage("tran0309.wav");
		M.fifthb_message = true;
	end
	if ((IsAlive(M.attacker)) and ( not M.sixth_message))
	then
		AddHealth(M.attacker, 50.0);
	end


	if ((M.fifth_message) and ( not M.sixth_message) and (M.found))
	then
		StopAudioMessage(M.aud);
		M.aud = AudioMessage("tran0310.wav");
		M.sixth_message = true;
		M.delay_message = GetTime()+30.0;
	end
	if (( not M.scav_died) and 
		(
		( not IsAlive(M.recycler))  or  
		((M.sixth_message) and ( not IsAlive(M.scav))) )
		)
	then
		M.scav_died = true;
		StopAudioMessage(M.aud);
		M.aud = AudioMessage("tran0313.wav");
		FailMission(GetTime()+10.0,"tran03l1.des");
	end
	if (GetTime()>M.delay_message)
	then
		-- "protect the scavenger"
	--	AudioMessage("tran0311.wav");
		if (IsAlive(M.attacker))
		then
			AudioMessage("tran0308.wav");
			Attack(M.attacker, M.scav, 1);
		end
		M.delay_message = 99999.0;
	end
	if ((M.sixth_message) and ( not M.seventh_message)
		 and  ( not IsAlive(M.attacker)))
	then
		-- you killed him
		AudioMessage("tran0314.wav");
		M.seventh_message = true;
		ClearObjectives();
		AddObjective("tran0301.otf","GREEN");
		AddObjective("tran0302.otf","GREEN");
	end
	if ((M.seventh_message) and ( not M.eighth_message))
	then
		--Recycler *myRecycler = (Recycler *) GameObjectHandle::GetObj(M.recycler);
		local money = GetScrap(1); --myRecycler->GetTeamList()->GetScrap();		
		if (money >= 9)
		then
			AudioMessage("tran0315.wav");
			M.eighth_message = true;
			SucceedMission(GetTime()+10.0,"tran03w1.des");
		end
	end

-- END OF SCRIPT
	
end