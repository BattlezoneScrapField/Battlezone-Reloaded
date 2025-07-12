-- Single Player Training Mission 4 Lua conversion, created by General BlackDragon. 

-- Single Table for all our save/load variables. This SP mission has too many variables to function with them independently. ("main function has > 200 local variables", or "Load having > 197 variables in assignment")
local M = {

-- bools
	found1 = false,
	found2 = false,
	start_done = false,
	message1 = false,
	message2 = false,
	message3 = false,
	message4 = false,
	message5 = false,
	message6 = false,
	message7 = false,
	message8 = false,
	message9 = false,
	message10 = false,
	message11 = false,
	message12 = false,
	message13 = false,
	message14 = false,
	message15 = false,
	message16 = false,
	press7 = false,
	attacked = false,
	--jump_start = false,
-- Floats (really doubles in Lua)
	--repeat_time = 0,
	camera_delay = 0,
-- Handles
	player = nil,
	target1 = nil,
	target2 = nil,
	recycler = nil,
	muf = nil,
	camera = nil,
	wing = nil
	--recy = nil,
--[[ Funny AiPath array
	*p_I,
	*p_will,
	*p_never,
	*p_cut,
	*p_and,
	*p_paste,
	*p_variabls,
	*p_again,
	*p_last;
--]]
-- Ints
	--num_reps = 0,
	--on_point = 0
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

end

function AddObject(h)

	if (
		(GetTeamNum(h) == 1)  and 
		(IsOdf(h, "avmuf"))
		)
	then
		M.found1 = true;
		M.muf =  h;
	end
	if (
		(GetTeamNum(h) == 1)  and 
		(IsOdf(h, "avfigh"))
		)
	then
		M.found2 = true;
		M.wing =  h;
	end

end

function Update()

-- START OF SCRIPT

	local test = false;
	if ( not M.start_done)
	then
		M.target1 = GetHandle("avturr12_turrettank");
		SetPilotClass(M.target1, "");
		M.target2 = GetHandle("avturr-1_turrettank");
		SetPilotClass(M.target2, "");
		M.recycler = GetHandle("avrecy-1_recycler");
		M.camera = GetHandle("apcamr-1_camerapod");
		M.player = GetHandle("player-1_hover");
		SetScrap(1,30);		
		AudioMessage("tran0401.wav");
		AudioMessage("tran0402.wav");
		AudioMessage("tran0424.wav");
		ClearObjectives();
		AddObjective("tran0401.otf","WHITE");
		M.start_done = true;
	end
	if (( not M.message1) and (IsAlive(M.recycler))  and 
		(IsSelected(M.recycler)))
	then
		AudioMessage("tran0425.wav");
		M.message1 = true;
	end
	if ((M.message1)  and 
		( not M.message2) and (IsAlive(M.recycler))
		)
	then
		if (IsDeployed(M.recycler))
		then
			AudioMessage("tran0424.wav");  -- select the M.recycler
			M.message2 = true;
		end
		-- added to skip M.muf stage
	end

	--[[ 
		press 7 to have the recyler build a factory
	--]]

	if ((M.message2) and (IsAlive(M.recycler))  and 
		(IsSelected(M.recycler))
		 and  ( not M.press7))
	then
		-- was
		-- AudioMessage("tran0403.wav");
		AudioMessage("tran0406.wav");
		M.press7 = true;
		M.message6 = true;
	end
	--[[
	if ((M.message2)  and 
		( not M.message3))
	then
		local money = ((Recycler *) GameObjectHandle::GetObj(M.recycler))->GetTeamList()->GetScrap();
		if ((money<30) and (M.found1))
		then
			-- M.found1 is set but we don't test for it
			--M.muf = GetHandle("avmuf-1_factory");
			if (M.muf ~= nil)
			then
				AudioMessage("tran0404.wav");
				AudioMessage("tran0405.wav");
				M.message3 = true;			
			else
				M.message2 = false; -- so you don't repeat this
				FailAll(10);  -- you built the wrong thing
			end
		end
	end

	if ((M.message3)
		 and  ( not M.message4)
				 and  (IsSelected(M.muf)))
	then
		AudioMessage("tran0423.wav");
		M.message4 = true;
	end

		if ((M.message4)
		 and  ( not M.message5))

	then 
		if (IsDeployed(M.muf))
		then
			AudioMessage("tran0405.wav");
			M.message5 = true;
		end
	end
	 if ((M.message5)  and 
		( not M.message6)  and 
		(IsSelected(M.muf)))
	then
		AudioMessage("tran0406.wav");
		M.message6 = true;
	end
	--]]
	if ((M.message6)  and 
		( not M.message7) and  (IsAlive(M.recycler))  and 
		( not IsSelected(M.recycler)) and (IsBusy(M.recycler))) -- was M.muf selected
	then
		AudioMessage("tran0407.wav");
		M.camera_delay = GetTime()+5.0;
		M.message7 = true;
	end
	if ((M.message7) 
		 and  ( not M.message8)
		 and  (GetTime()>M.camera_delay))
	then
		AudioMessage("tran0408.wav");
		M.camera_delay = 99999.0;
	end

	if ((M.message7)  and 
		( not M.message8)  and 
		(GetUserTarget() == M.camera))

	then
		AudioMessage("tran0409.wav");
		M.message8 = true;
		M.camera_delay = GetTime()+3.0;		
	end
	if ((M.message8)  and 
		( not M.message9)  and 
		(GetTime()>M.camera_delay) and (M.found2))
	then
		AudioMessage("tran0410.wav");
		-- M.wing = GetHandle("avtank-1_wingman");
		M.message9 = true;
		M.camera_delay = 99999.0;
	end
	if ((M.message7) and (M.message8) and (M.found2) and ( not IsAlive(M.wing)) and ( not M.message16))
	then
		FailMission(GetTime()+5.0,"tran04l1.des");
		M.message16 = true;

	end
 	if ((M.message9)  and 
		( not M.message10) and (IsAlive(M.wing))  and 
		(IsSelected(M.wing)))
	then
		AudioMessage("tran0411.wav");
		M.message10 = true;
	end

	if ((M.message10)  and 
		( not M.message11)  and 		(IsAlive(M.wing))  and 
		( not IsSelected(M.wing))  and 
		(M.camera_delay == 99999.0))
	then
		M.camera_delay = GetTime()+10.0;

	end
	if ((M.message10)  and 
		( not M.message11)  and 
		(M.camera_delay<GetTime()))
	then
		AudioMessage("tran0412.wav");
		M.message11 = true;
		M.camera_delay = 99999.0;
	end
	if ((M.message10)  and 
		( not M.attacked)  and 
		IsAlive(M.wing)  and 
		(GetLastEnemyShot(M.wing)>0))
	then
		AudioMessage("tran0413.wav");
		M.attacked = true;
	end


	if (( not IsAlive(M.target1))
		 and  ( not M.message12))
	then
		AudioMessage("tran0415.wav");
		if (IsAlive(M.target2))
		then
			SetObjectiveOn(M.target2);
			SetObjectiveName(M.target2, "Drone 2");
		end
		M.message12 = true;
	end
	if (IsValid(M.player) and IsValid(M.target2))
	then
		if ((M.message12)  and 
			(GetDistance(M.player,M.target2)<300.0)  and 
			( not M.message13))
		then
			AudioMessage("tran0416.wav");
			M.message13 = true;
			AudioMessage("tran0418.wav");
			M.message13 = true;
		end
	end
	if ((M.message13)  and 
		(GetUserTarget() == M.target2)
			 and  ( not M.message14))
	then
		AudioMessage("tran0410.wav");
		M.message14 = true;
	end
	if ((M.message14)  and 
		( not M.message15)  and 
		(IsSelected(M.wing)))
	then
		AudioMessage("tran0420.wav");
		M.message15 = true;
	end
	if ((M.message6)  and 
		( not IsAlive(M.target1))  and 
		( not IsAlive(M.target2))
		 and  ( not M.message16))
	then
		AudioMessage("tran0421.wav");
		SucceedMission(GetTime()+10,"tran04w1.des");
		M.message16 = true;
	end
	if	(( not M.message6)  and 
		(( not IsAlive(M.target1))  or  ( not IsAlive(M.target2)))
			 and  ( not M.message16))		
	then
		M.message16 = true;
		FailMission(GetTime()+5.0,"tran04l1.des");
	end

-- END OF SCRIPT
	
end