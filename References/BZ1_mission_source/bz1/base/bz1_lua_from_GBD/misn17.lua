-- Single Player NSDF Mission 16 Lua conversion, created by General BlackDragon. 

-- Single Table for all our save/load variables. This SP mission has too many variables to function with them independently. ("main function has > 200 local variables", or "Load having > 197 variables in assignment")
local M = {

-- bools
	missionstart = false,
	--raw1there = false,
	--raw2there = false,
	--raw3there = false,
	--raw4there = false,
	--raw5there = false,
	--prothere = false,
	--inprocess = false,
	minesmade = false,
	openingcin = false,
	camera1 = false,
	camera2 = false,
	camera3 = false,
	camera4 = false,
	camera5 = false,
	camera6 = false,
	camera7 = false,
	--dispatch = false,
	--dispatch2 = false,
	cineractive1 = false,
	cineractive2 = false,
	openingcindone = false,
	--crysswitched = false,
	--factorydestroyed = false,
	--attackwavesent = false,
	--firsttimecrysreplaced = false,
	newobjective = false,
	--checktug = false,
	--crystalhint1 = false,
	--crystalhint2 = false,
	--crystalhint3 = false,
	--said1 = false,
	--procrysgone = false,
	missionfail = false,
	missionwon = false,
	defenders = false,
	minecin = false,
	minesdestroyed = false,
	towersdestroyed = false,
	tower1spawn = false,
	tower2spawn = false,
	tower3spawn = false,
	tower4spawn = false,
	tower5spawn = false,
	tower6spawn = false,
	tower7spawn = false,
	tower1dead = false,
	tower2dead = false,
	tower3dead = false,
	tower4dead = false,
	tower5dead = false,
	tower6dead = false,
	tower7dead = false,
	minecinstart = false,
	factorypart1dead = false,
	factorypart2dead = false,
	factorypart3dead = false,
	sf2gone = false,
	sf3gone = false,
	sf4gone = false,
	--fact1gone = false,
	--fact2gone = false,
	--fact3gone = false,
	--critstatement = false,
-- Floats (really doubles in Lua)
	discheck = 0,
	minedistancecheck = 0,
	--waveattacks = 0,
	spawntime1 = 0,
	spawntime2 = 0,
	spawntime3 = 0,
	spawntime4 = 0,
	tower1check = 0,
	tower2check = 0,
	tower3check = 0,
	tower4check = 0,
	tower5check = 0,
	tower6check = 0,
	tower7check = 0,
	sf2blow = 0,
	sf3blow = 0,
	sf4blow = 0,
	--procrysdes = 0,
	--rawcrys1des = 0,
	--rawcrys2des = 0,
	--rawcrys3des = 0,
	--rawcrys4des = 0,
	--rawcrys5des = 0,
	--procrysreplace = 0,
	--rawcrys1replace = 0,
	--rawcrys2replace = 0,
	--rawcrys3replace = 0,
	camdone = 0,
	--rawcrys4replace = 0,
	--rawcrys5replace = 0,
	--op1replace = 0,
	--op2replace = 0,
	--op3replace = 0,
	--op4replace = 0,
-- Handles
	savfactory1 = nil,
	savfactory2 = nil,
	savfactory3 = nil,
	savfactory4 = nil,
	deftow1a = nil,
	deftow1b = nil,
	deftow2a = nil,
	deftow2b = nil,
	factorynav = nil,
	basenav = nil,
	badman1 = nil,
	badman2 = nil,
	badman3 = nil,
	badman4 = nil,
	badman5 = nil,
	badman6 = nil,
	badman7 = nil,
	badman8 = nil,
	badman9 = nil,
	badman10 = nil,
	badman11 = nil,
	badman12 = nil,
	badman13 = nil,
	badman14 = nil,
	deftow3a = nil,
	deftow3b = nil,
	deftow4a = nil,
	deftow4b = nil,
	deftow5a = nil,
	deftow5b = nil,
	deftow6a = nil,
	deftow6b = nil,
	aud1 = nil,
	trig1 = nil,
	trig2 = nil,
	trig3 = nil,
	trig4 = nil,
	trig5 = nil,
	trig6 = nil,
	trig7 = nil,
	deftow7a = nil,
	deftow7b = nil,
	factorypart1 = nil,
	factorypart2 = nil,
	factorypart3 = nil,
	--procrys = nil,
	--rawcrys1 = nil,
	--rawcrys2 = nil,
	--rawcrys3 = nil,
	--rawcrys4 = nil,
	--rawcrys5 = nil,
	miner = nil,
	avrec = nil,
	prey1 = nil,
	ip1 = nil,
	ip2 = nil,
	ip3 = nil,
	ip4 = nil,
	--cam1 = nil,
	--cam2 = nil,
	--cam3 = nil,
	--cam4 = nil,
	--cam5 = nil,
	--cam6 = nil,
	--aw1 = nil,
	--aw2 = nil,
	--aw3 = nil,
	--aw4 = nil,
	--tug = nil,
	MINE = { }, --[54] = nil,
	mineaudio = nil,
	cinscrap = nil,
	art1 = nil,
	art2 = nil,
	art3 = nil,
	art4 = nil,
	art5 = nil,
	desart1 = nil,
	desart2 = nil,
	desart3 = nil,
	desart4 = nil,
	desart5 = nil,
	tower1 = nil,
	tower2 = nil,
	tower3 = nil,
	tower4 = nil,
	tower5 = nil,
	tower6 = nil,
	tower7 = nil,
-- Ints
	--hint = 0,
	minecount = 0
	--crit = 0
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

	M.camdone = 9999999999.0;
	M.discheck = 9999999999.0;
	
	M.sf2blow = 99999999999.0;
	M.sf3blow = 99999999999.0;
	M.sf4blow = 99999999999.0;
	
	M.camera1 = true;
	
	M.spawntime1 = 999999999.0;
	M.spawntime2 = 999999999.0;
	M.spawntime3 = 999999999.0;
	M.spawntime4 = 999999999.0;
	M.minedistancecheck = 999999999.0;
	
	M.tower1check = 9999999999.0;
	M.tower2check = 9999999999.0;
	M.tower3check = 9999999999.0;
	M.tower4check = 9999999999.0;
	M.tower5check = 9999999999.0;
	M.tower6check = 9999999999.0;
	M.tower7check = 9999999999.0;

end

function AddObject(h)

	if ((M.art1 == nil) and (IsOdf(h,"avartl")))
	then
		M.art1 = h;
	elseif ((M.art2 == nil) and (IsOdf(h,"avartl")))
	then
		M.art2 = h;
	elseif ((M.art3 == nil) and (IsOdf(h,"avartl")))
	then
		M.art3 = h;
	elseif ((M.art4 == nil) and (IsOdf(h,"avartl")))
	then
		M.art4 = h;
	elseif ((M.art5 == nil) and (IsOdf(h,"avartl")))
	then
		M.art5 = h;
	end

end

function Update()

-- START OF SCRIPT

	if
		(M.missionstart == false)
	then
		M.minedistancecheck = GetTime() + 10.0;
		M.aud1 = AudioMessage ("misn1701.wav");
		M.avrec = GetHandle("avrecy18_recycler");
		M.savfactory1 = GetHandle("savfactory1");
		M.savfactory2 = GetHandle("savfactory2");
		M.savfactory3 = GetHandle("savfactory3");
		M.savfactory4 = GetHandle("savfactory4");
		M.factorypart1 = GetHandle("factorypart1");
		M.factorypart2 = GetHandle("factorypart2");
		M.factorypart3 = GetHandle("factorypart3");
		M.factorynav = GetHandle("factorynav");
		M.basenav = GetHandle("basenav");
		M.tower1 = exu.BuildAsyncObject("hbptow", 2, "geizer1");
		M.tower2 = exu.BuildAsyncObject("hbptow", 2, "geizer2");
		M.tower3 = exu.BuildAsyncObject("hbptow", 2, "geizer3");
		M.tower4 = exu.BuildAsyncObject("hbptow", 2, "geizer4");
		M.tower5 = exu.BuildAsyncObject("hbptow", 2, "geizer5");
		M.tower6 = exu.BuildAsyncObject("hbptow", 2, "geizer6");
		M.tower7 = exu.BuildAsyncObject("hbptow", 2, "geizer7");
		SetObjectiveOn(M.tower1);
		SetObjectiveOn(M.tower2);
		SetObjectiveOn(M.tower3);
		SetObjectiveOn(M.tower4);
		SetObjectiveOn(M.tower5);
		SetObjectiveOn(M.tower6);
		SetObjectiveOn(M.tower7);
		SetObjectiveName(M.tower1, "Tower 1");
		SetObjectiveName(M.tower2, "Tower 2");
		SetObjectiveName(M.tower3, "Tower 3");
		SetObjectiveName(M.tower4, "Tower 4");
		SetObjectiveName(M.tower5, "Tower 5");
		SetObjectiveName(M.tower6, "Tower 6");
		SetObjectiveName(M.tower7, "Tower 7 "); -- needs fixed in sprite table
		SetObjectiveName(M.factorynav, "Furies Factory");
		SetObjectiveName(M.basenav, "Home Base");
		M.missionstart = true;
--		M.waveattacks = GetTime()+1800.0; -- not used
		M.newobjective = true;
		M.camdone = GetTime() +35.0;
		SetScrap (1, 40);
		M.spawntime1 = GetTime () + 10.0;
		M.spawntime2 = GetTime () + 100.0;
		M.spawntime3 = GetTime () + 220.0;
		M.spawntime4 = GetTime () + 340.0;
		SetAIP ("misn17.aip");
		M.discheck = GetTime() + 30.0;
		M.tower1check = GetTime() + 3.0;
		M.tower2check = GetTime() + 3.0;
		M.tower3check = GetTime() + 3.0;
		M.tower4check = GetTime() + 3.0;
		M.tower5check = GetTime() + 3.0;
		M.tower6check = GetTime() + 3.0;
		M.tower7check = GetTime() + 3.0;
	end

	if
		(
		(IsAlive(M.art1)) and ( not IsAlive(M.desart1))
		)
	then
		M.desart1 = exu.BuildAsyncObject("hvsav", 2, "counter");
		Attack(M.desart1, M.art1);
	end
if
		(
		(IsAlive(M.art2)) and ( not IsAlive(M.desart2))
		)
	then
		M.desart2 = exu.BuildAsyncObject("hvsav", 2, "counter");
		Attack(M.desart2, M.art2);
	end
if
		(
		(IsAlive(M.art3)) and ( not IsAlive(M.desart3))
		)
	then
		M.desart3 = exu.BuildAsyncObject("hvsav", 2, "counter");
		Attack(M.desart3, M.art3);
	end
if
		(
		(IsAlive(M.art4)) and ( not IsAlive(M.desart4))
		)
	then
		M.desart4 = exu.BuildAsyncObject("hvsav", 2, "counter");
		Attack(M.desart4, M.art4);
	end
if
		(
		(IsAlive(M.art5)) and ( not IsAlive(M.desart5))
		)
	then
		M.desart5 = exu.BuildAsyncObject("hvsav", 2, "counter");
		Attack(M.desart5, M.art5);
	end
	if 
		(M.openingcin == false)
	then
		CameraReady ();
		M.camera1 = true;
		M.openingcin = true;
	end

	if 
		(M.camera2 == true)
	then
		if (CameraPath ("cineractive2", 500, 2000, M.tower1))
			 
			--	(PanDone())
			then
				M.camera2 = false;
				M.camera3 = true;
			end
	end

	if 
		(M.camera3 == true)
	then
		if (CameraPath("cineractive3", 1000, 2000, M.tower6))
		
--				(PanDone())
			then
				M.camera3 = false;
				M.camera4 = true;
			end
	end

	if 
		(M.camera4 == true)
	then
		if (CameraPath("cineractive5", 1000, 2000, M.tower3))
		
--				(PanDone())
			then
				M.camera4 = false;
				M.camera5 = true;
			end
	end
	if 
		(M.camera5 == true)
	then
		if (CameraPath("cineractive6", 1000, 2000, M.tower4))
		
--				(PanDone())
			then
				M.camera5 = false;
				M.camera6 = true;
			end
	end

	if 
		(M.camera6 == true)
	then
		if (CameraPath("cineractive4", 1000, 2000, M.tower5))
		
--				(PanDone())
			then
				M.camera6 = false;
				M.camera7 = true;
			end
	end

	if 
		(M.camera7 == true)
	then
		if (CameraPath("cineractive7", 1000, 1700, M.tower7))
		
--				(PanDone())
			then
				M.camera7 = false;
				CameraFinish();
			end
	end
	if
		(M.camera1 == true)
	then
			if
				(CameraPath("cineractive1", 1000, 2000, M.savfactory1))
--				(PanDone())
			then
				M.camera1 = false;
				M.camera2 = true;
				
			end
	end
	if
		(M.openingcindone == false)
	then
		if
		(
		 (IsAudioMessageDone(M.aud1))  or  (CameraCancelled())
		)
	then
		CameraFinish();
		StopAudioMessage(M.aud1);
		M.openingcindone = true;
		M.camera1 = false;
		M.camera2 = false;
		M.camera3 = false;
		M.camera4 = false;
		M.camera5 = false;
		M.camera6 = false;
		M.camera7 = false;
	end
	end

	--[[if
		(M.cineractive1 == false)
	then
		CameraPath("cineractive1", 1000, 2000, M.savfactory1);
		M.cineractive2 = true;
	end

	if
		(
		(M.cineractive2 == true) and (PanDone())
		)
	then
		CameraPath("cineractive2", 200, 2000, M.tower1);
		M.cineractive1 = true;
	end

	if
		(
		(M.cineractive1 == true) and (PanDone())
		)
	then
		CameraFinish();
	end--]]

	if
		(
		(M.factorypart1dead == false)  and 
		( not IsAlive(M.factorypart1))
		)
	then
		exu.BuildAsyncObject("eggeizr1", 0, "part1geizer");
		M.factorypart1dead = true;
	end

	if
		(
		(M.factorypart2dead == false)  and 
		( not IsAlive(M.factorypart2))
		)
	then
		exu.BuildAsyncObject("eggeizr1", 0, "part2geizer");
		M.factorypart2dead = true;
	end

	if
		(
		(M.factorypart3dead == false)  and 
		( not IsAlive(M.factorypart3))
		)
	then
		exu.BuildAsyncObject("eggeizr1", 0, "part3geizer");
		M.factorypart3dead = true;
	end

	if
		(
		(M.minesmade == false) and (M.minedistancecheck < GetTime())
		)
	then
		M.miner = GetNearestEnemy(M.savfactory2);
		if
			(
		(GetDistance(M.miner, "pt1") < 610.0)  or 
		(GetDistance(M.miner, "pt2") < 610.0)  or 
		(GetDistance(M.miner, "pt3") < 610.0) 
		)

		then
		M.MINE[1] = exu.BuildAsyncObject("boltmine2", 2, "mine54"); -- needs fixed in bzn
		M.MINE[2] = exu.BuildAsyncObject("boltmine2", 2, "mine1");
		M.MINE[3] = exu.BuildAsyncObject("boltmine2", 2, "mine2");
		M.MINE[4] = exu.BuildAsyncObject("boltmine2", 2, "mine3");
		M.MINE[5] = exu.BuildAsyncObject("boltmine2", 2, "mine4");
		M.MINE[6] = exu.BuildAsyncObject("boltmine2", 2, "mine5");
		M.MINE[7] = exu.BuildAsyncObject("boltmine2", 2, "mine6");
		M.MINE[8] = exu.BuildAsyncObject("boltmine2", 2, "mine7");
		M.MINE[9] = exu.BuildAsyncObject("boltmine2", 2, "mine8");
		M.MINE[10] = exu.BuildAsyncObject("boltmine2", 2, "mine9");
		M.MINE[11] = exu.BuildAsyncObject("boltmine2", 2, "mine10");
		M.MINE[12] = exu.BuildAsyncObject("boltmine2", 2, "mine11");
		M.MINE[13] = exu.BuildAsyncObject("boltmine2", 2, "mine12");
		M.MINE[14] = exu.BuildAsyncObject("boltmine2", 2, "mine13");
		M.MINE[15] = exu.BuildAsyncObject("boltmine2", 2, "mine14");
		M.MINE[16] = exu.BuildAsyncObject("boltmine2", 2, "mine15");
		M.MINE[17] = exu.BuildAsyncObject("boltmine2", 2, "mine16");
		M.MINE[18] = exu.BuildAsyncObject("boltmine2", 2, "mine17");
		M.MINE[19] = exu.BuildAsyncObject("boltmine2", 2, "mine18");
		M.MINE[20] = exu.BuildAsyncObject("boltmine2", 2, "mine19");
		M.MINE[21] = exu.BuildAsyncObject("boltmine2", 2, "mine20");
		M.MINE[22] = exu.BuildAsyncObject("boltmine2", 2, "mine21");
		M.MINE[23] = exu.BuildAsyncObject("boltmine2", 2, "mine22");
		M.MINE[24] = exu.BuildAsyncObject("boltmine2", 2, "mine23");
		M.MINE[25] = exu.BuildAsyncObject("boltmine2", 2, "mine24");
		M.MINE[26] = exu.BuildAsyncObject("boltmine2", 2, "mine25");
		M.MINE[27] = exu.BuildAsyncObject("boltmine2", 2, "mine26");
		M.MINE[28] = exu.BuildAsyncObject("boltmine2", 2, "mine27");
		M.MINE[29] = exu.BuildAsyncObject("boltmine2", 2, "mine28");
		M.MINE[30] = exu.BuildAsyncObject("boltmine2", 2, "mine29");
		M.MINE[31] = exu.BuildAsyncObject("boltmine2", 2, "mine30");
		M.MINE[32] = exu.BuildAsyncObject("boltmine2", 2, "mine31");
		M.MINE[33] = exu.BuildAsyncObject("boltmine2", 2, "mine32");
		M.MINE[34] = exu.BuildAsyncObject("boltmine2", 2, "mine33");
		M.MINE[35] = exu.BuildAsyncObject("boltmine2", 2, "mine34");
		M.MINE[36] = exu.BuildAsyncObject("boltmine2", 2, "mine35");
		M.MINE[37] = exu.BuildAsyncObject("boltmine2", 2, "mine36");
		M.MINE[38] = exu.BuildAsyncObject("boltmine2", 2, "mine37");
		M.MINE[39] = exu.BuildAsyncObject("boltmine2", 2, "mine38");
		M.MINE[40] = exu.BuildAsyncObject("boltmine2", 2, "mine39");
		M.MINE[41] = exu.BuildAsyncObject("boltmine2", 2, "mine40");
		M.MINE[42] = exu.BuildAsyncObject("boltmine2", 2, "mine41");
		M.MINE[43] = exu.BuildAsyncObject("boltmine2", 2, "mine42");
		M.MINE[44] = exu.BuildAsyncObject("boltmine2", 2, "mine43");
		M.MINE[45] = exu.BuildAsyncObject("boltmine2", 2, "mine44");
		M.MINE[46] = exu.BuildAsyncObject("boltmine2", 2, "mine45");
		M.MINE[47] = exu.BuildAsyncObject("boltmine2", 2, "mine46");
		M.MINE[48] = exu.BuildAsyncObject("boltmine2", 2, "mine47");
		M.MINE[49] = exu.BuildAsyncObject("boltmine2", 2, "mine48");
		M.MINE[50] = exu.BuildAsyncObject("boltmine2", 2, "mine49");
		M.MINE[51] = exu.BuildAsyncObject("boltmine2", 2, "mine55"); -- needs fixed in bzn
		M.MINE[52] = exu.BuildAsyncObject("boltmine2", 2, "mine56"); -- needs fixed in bzn
		M.MINE[53] = exu.BuildAsyncObject("boltmine2", 2, "mine52");
		M.MINE[54] = exu.BuildAsyncObject("boltmine2", 2, "mine53");
		M.minesmade = true;
		end
		M.minedistancecheck = GetTime() + 3.0;
	end
	if
		(
		(IsAlive(M.tower1))  and 
		(M.tower1spawn == false) and (M.tower1check < GetTime())
		)
	then
		M.trig1 = GetNearestEnemy(M.tower1);
		if
			(GetDistance(M.tower1, M.trig1) < 400.0)
		then
			M.deftow1a = exu.BuildAsyncObject("hvsat", 2, M.tower1);
			M.deftow1b = exu.BuildAsyncObject("hvsat", 2, M.tower1);
			Defend2(M.deftow1a, M.tower1, 1000);
			Defend2(M.deftow1b, M.tower1, 1000);
			M.tower1spawn = true;
		end

		M.tower1check = GetTime() + 2.0;
		M.trig1 = 0;
	end

	if
		(
		(IsAlive(M.deftow1a)) and (GetCurrentCommand(M.deftow1a) == AiCommand.DEFEND)
		)
	then
		if
			(GetLastEnemyShot(M.deftow1a) > 0)
		then
			M.badman1 = GetWhoShotMe(M.deftow1a);
			Attack (M.deftow1a, M.badman1, 1);
		end
	end
	if
		(
		(IsAlive(M.deftow1b)) and (GetCurrentCommand(M.deftow1b) == AiCommand.DEFEND)
		)
	then
		if
			(GetLastEnemyShot(M.deftow1b) > 0)
		then
			M.badman2 = GetWhoShotMe(M.deftow1b);
			Attack (M.deftow1b, M.badman2, 1);
		end
	end
	if
		(
		(IsAlive(M.deftow2a)) and (GetCurrentCommand(M.deftow2a) == AiCommand.DEFEND)
		)
	then
		if
			(GetLastEnemyShot(M.deftow2a) > 0)
		then
			M.badman3 = GetWhoShotMe(M.deftow2a);
			Attack (M.deftow2a, M.badman3, 1);
		end
	end
	if
		(
		(IsAlive(M.deftow2b)) and (GetCurrentCommand(M.deftow2b) == AiCommand.DEFEND)
		)
	then
		if
			(GetLastEnemyShot(M.deftow2b) > 0)
		then
			M.badman4 = GetWhoShotMe(M.deftow2b);
			Attack (M.deftow2b, M.badman4, 1);
		end
	end

	if
		(
		(IsAlive(M.deftow3a)) and (GetCurrentCommand(M.deftow3a) == AiCommand.DEFEND)
		)
	then
		if
			(GetLastEnemyShot(M.deftow3a) > 0)
		then
			M.badman5 = GetWhoShotMe(M.deftow3a);
			Attack (M.deftow3a, M.badman5, 1);
		end
	end

	if
		(
		(IsAlive(M.deftow3b)) and (GetCurrentCommand(M.deftow3b) == AiCommand.DEFEND)
		)
	then
		if
			(GetLastEnemyShot(M.deftow3b) > 0)
		then
			M.badman6 = GetWhoShotMe(M.deftow3b);
			Attack (M.deftow3b, M.badman6, 1);
		end
	end

	if
		(
		(IsAlive(M.deftow4a)) and (GetCurrentCommand(M.deftow4a) == AiCommand.DEFEND)
		)
	then
		if
			(GetLastEnemyShot(M.deftow4a) > 0)
		then
			M.badman7 = GetWhoShotMe(M.deftow4a);
			Attack (M.deftow4a, M.badman7, 1);
		end
	end
	if
		(
		(IsAlive(M.deftow4b)) and (GetCurrentCommand(M.deftow4b) == AiCommand.DEFEND)
		)
	then
		if
			(GetLastEnemyShot(M.deftow4b) > 0)
		then
			M.badman8 = GetWhoShotMe(M.deftow4b);
			Attack (M.deftow4b, M.badman8, 1);
		end
	end

	if
		(
		(IsAlive(M.deftow5a)) and (GetCurrentCommand(M.deftow5a) == AiCommand.DEFEND)
		)
	then
		if
			(GetLastEnemyShot(M.deftow5a) > 0)
		then
			M.badman9 = GetWhoShotMe(M.deftow5a);
			Attack (M.deftow5a, M.badman9, 1);
		end
	end
	if
		(
		(IsAlive(M.deftow5b)) and (GetCurrentCommand(M.deftow5b) == AiCommand.DEFEND)
		)
	then
		if
			(GetLastEnemyShot(M.deftow5b) > 0)
		then
			M.badman10 = GetWhoShotMe(M.deftow5b);
			Attack (M.deftow5b, M.badman10, 1);
		end
	end

	if
		(
		(IsAlive(M.deftow6a)) and (GetCurrentCommand(M.deftow6a) == AiCommand.DEFEND)
		)
	then
		if
			(GetLastEnemyShot(M.deftow6a) > 0)
		then
			M.badman11 = GetWhoShotMe(M.deftow6a);
			Attack (M.deftow6a, M.badman11, 1);
		end
	end
	if
		(
		(IsAlive(M.deftow6b)) and (GetCurrentCommand(M.deftow6b) == AiCommand.DEFEND)
		)
	then
		if
			(GetLastEnemyShot(M.deftow6b) > 0)
		then
			M.badman12 = GetWhoShotMe(M.deftow6b);
			Attack (M.deftow6b, M.badman12, 1);
		end
	end

	if
		(
		(IsAlive(M.deftow7a)) and (GetCurrentCommand(M.deftow7a) == AiCommand.DEFEND)
		)
	then
		if
			(GetLastEnemyShot(M.deftow7a) > 0)
		then
			M.badman13 = GetWhoShotMe(M.deftow7a);
			Attack (M.deftow7a, M.badman14, 1);
		end
	end
	if
		(
		(IsAlive(M.deftow7b)) and (GetCurrentCommand(M.deftow7b) == AiCommand.DEFEND)
		)
	then
		if
			(GetLastEnemyShot(M.deftow7b) > 0)
		then
			M.badman14 = GetWhoShotMe(M.deftow7b);
			Attack (M.deftow7b, M.badman14, 1);
		end
	end

	if
		(
		(IsAlive(M.tower2))  and 
		(M.tower2spawn == false) and (M.tower2check < GetTime())
		)
	then
		M.trig2 = GetNearestEnemy(M.tower2);

		if
			(GetDistance(M.tower2, M.trig2) < 400.0)
		then
			M.deftow2a = exu.BuildAsyncObject("hvsat", 2, M.tower2);
			M.deftow2b = exu.BuildAsyncObject("hvsat", 2, M.tower2);
			Defend2(M.deftow2a, M.tower2, 1000);
			Defend2(M.deftow2b, M.tower2, 1000);
			M.tower2spawn = true;
		end
		M.trig2 = 0;

		M.tower2check = GetTime() + 2.0;
	end
	if
		(
		(IsAlive(M.tower3))  and 
		(M.tower3spawn == false) and (M.tower3check < GetTime())
		)
	then
		M.trig3 = GetNearestEnemy(M.tower3);
		if
			(GetDistance(M.tower3, M.trig3) < 400.0)
		then
			M.deftow3a = exu.BuildAsyncObject("hvsat", 2, M.tower3);
			M.deftow3b = exu.BuildAsyncObject("hvsat", 2, M.tower3);
			Defend2(M.deftow3a, M.tower3, 1000);
			Defend2(M.deftow3b, M.tower3, 1000);
			M.tower3spawn = true;
		end
		M.trig3 = 0;

		M.tower3check = GetTime() + 2.0;
	end

	if
		(
		(IsAlive(M.tower4))  and 
		(M.tower4spawn == false) and (M.tower4check < GetTime())
		)
	then
		M.trig4 = GetNearestEnemy(M.tower4);
		if
			(GetDistance(M.tower4, M.trig4) < 400.0)
		then
			M.deftow4a = exu.BuildAsyncObject("hvsat", 2, M.tower4);
			M.deftow4b = exu.BuildAsyncObject("hvsat", 2, M.tower4);
			Defend2(M.deftow4a, M.tower4, 1000);
			Defend2(M.deftow4b, M.tower4, 1000);
			M.tower4spawn = true;
		end
		M.trig4 = 0;
		M.tower4check = GetTime() + 2.0;
	end

	if
		(
		(IsAlive(M.tower5))  and 
		(M.tower5spawn == false) and (M.tower5check < GetTime())
		)
	then
		M.trig5 = GetNearestEnemy(M.tower5);
		if
			(GetDistance(M.tower5, M.trig5) < 400.0)
		then
			M.deftow5a = exu.BuildAsyncObject("hvsat", 2, M.tower5);
			M.deftow5b = exu.BuildAsyncObject("hvsat", 2, M.tower5);
			Defend2(M.deftow5a, M.tower5, 1000);
			Defend2(M.deftow5b, M.tower5, 1000);
			M.tower5spawn = true;
		end
		M.trig5 = 0;
		M.tower5check = GetTime() + 2.0;
	end

	if
		(
		(IsAlive(M.tower6))  and 
		(M.tower6spawn == false) and (M.tower6check < GetTime())
		)
	then
		M.trig6 = GetNearestEnemy(M.tower6);
		if
			(GetDistance(M.tower6, M.trig6) < 400.0)
		then
			M.deftow6a = exu.BuildAsyncObject("hvsat", 2, M.tower6);
			M.deftow6b = exu.BuildAsyncObject("hvsat", 2, M.tower6);
			Defend2(M.deftow6a, M.tower6, 1000);
			Defend2(M.deftow6b, M.tower6, 1000);
			M.tower6spawn = true;
		end
		M.trig6 = 0;
		M.tower6check = GetTime() + 2.0;
	end

	if
		(
		(IsAlive(M.tower7))  and 
		(M.tower7spawn == false) and (M.tower7check < GetTime())
		)
	then
		M.trig7 = GetNearestEnemy(M.tower7);
		if
			(GetDistance(M.tower7, M.trig7) < 400.0)
		then
			M.deftow7a = exu.BuildAsyncObject("hvsat", 2, M.tower7);
			M.deftow7b = exu.BuildAsyncObject("hvsat", 2, M.tower7);
			Defend2(M.deftow7a, M.tower7, 1000);
			Defend2(M.deftow7b, M.tower7, 1000);
			M.tower7spawn = true;
		end
		M.trig7 = 0;
		M.tower7check = GetTime() + 2.0;
	end

	if
		(
		( not IsAlive(M.tower1)) and (M.tower1dead == false)
		)
	then
		exu.BuildAsyncObject("eggeizr1", 0, "geizer1");
		M.tower1dead = true;
	end
	if
		(
		( not IsAlive(M.tower2)) and (M.tower2dead == false)
		)
	then
		exu.BuildAsyncObject("eggeizr1", 0, "geizer2");
		M.tower2dead = true;
	end
	if
		(
		( not IsAlive(M.tower3)) and (M.tower3dead == false)
		)
	then
		exu.BuildAsyncObject("eggeizr1", 0, "geizer3");
		M.tower3dead = true;
	end
	if
		(
		( not IsAlive(M.tower4)) and (M.tower4dead == false)
		)
	then
		exu.BuildAsyncObject("eggeizr1", 0, "geizer4");
		M.tower4dead = true;
	end
	if
		(
		( not IsAlive(M.tower5)) and (M.tower5dead == false)
		)
	then
		exu.BuildAsyncObject("eggeizr1", 0, "geizer5");
		M.tower5dead = true;
	end
	if
		(
		( not IsAlive(M.tower6)) and (M.tower6dead == false)
		)
	then
		exu.BuildAsyncObject("eggeizr1", 0, "geizer6");
		M.tower6dead = true;
	end
	if
		(
		( not IsAlive(M.tower7)) and (M.tower7dead == false)
		)
	then
		exu.BuildAsyncObject("eggeizr1", 0, "geizer7");
		M.tower7dead = true;
	end
	if 
		(M.newobjective == true)
	then
		ClearObjectives();

		if
			(M.towersdestroyed == false)
		then
			AddObjective ("misn1701.otf", "WHITE");
		end

		if
			(
			(M.towersdestroyed == true) and (M.missionwon == false)
			)
		then
			AddObjective ("misn1701.otf", "GREEN");
			AddObjective ("misn1702.otf", "WHITE");
		end

		if
			(M.missionwon == true)
		then
			AddObjective ("misn1701.otf", "GREEN");
			AddObjective ("misn1702.otf", "GREEN");
		end

		M.newobjective = false;
	end
	if
		(M.spawntime1 < GetTime())
	then
		exu.BuildAsyncObject("hvsat", 2, M.savfactory1);
		M.spawntime1 = GetTime () + 400.0;
	end
	if
		(M.spawntime2 < GetTime())
	then
		exu.BuildAsyncObject("hvsav", 2, M.savfactory2);
		M.spawntime2 = GetTime () + 400.0;
	end
	if
		(M.spawntime3 < GetTime())
	then
		exu.BuildAsyncObject("hvsat", 2, M.savfactory3);
		M.spawntime3 = GetTime () + 400.0;
	end
	if
		(M.spawntime4 < GetTime())
	then
		exu.BuildAsyncObject("hvsat", 2, M.savfactory4);
		M.spawntime4 = GetTime () + 400.0;
	end

	if
		(
		(M.discheck < GetTime()) and (M.defenders == false)
		)
	then
		M.prey1 = GetNearestEnemy(M.savfactory1);
		if
		(GetDistance(M.prey1, "savspawn", 1) < 450.0) 
		then
			M.ip1 = exu.BuildAsyncObject("hvsav", 2, M.savfactory1);
			M.ip2 = exu.BuildAsyncObject("hvsat", 2, M.savfactory2);
			M.ip3 = exu.BuildAsyncObject("hvsat", 2, M.savfactory3);
			M.ip4 = exu.BuildAsyncObject("hvsav", 2, M.savfactory4);
			M.defenders = true;
			Defend2(M.ip1, M.savfactory1);
			Defend2(M.ip2, M.savfactory2);
			Defend2(M.ip3, M.savfactory3);
			Defend2(M.ip4, M.savfactory4);
			M.badman1 = 0;
			M.badman2 = 0;
			M.badman3 = 0;
			M.badman4 = 0;
			M.discheck = 0.0;
		else
			M.discheck = GetTime() + 5.0;
		end
	end

	if (M.defenders)
	then
		local time = GetTime();

		-- keep track of who shot each sav factory recently
		--local shot1 = IsAlive(M.savfactory1) and time < GetLastEnemyShot(M.savfactory1) + 20.0 ? GetWhoShotMe(M.savfactory1) : 0;
		local shot1 = IsAlive(M.savfactory1) and time < GetLastEnemyShot(M.savfactory1) + 20.0 and GetWhoShotMe(M.savfactory1) or 0;
		local shot2 = IsAlive(M.savfactory2) and time < GetLastEnemyShot(M.savfactory2) + 20.0 and GetWhoShotMe(M.savfactory2) or 0;
		local shot3 = IsAlive(M.savfactory3) and time < GetLastEnemyShot(M.savfactory3) + 20.0 and GetWhoShotMe(M.savfactory3) or 0;
		local shot4 = IsAlive(M.savfactory4) and time < GetLastEnemyShot(M.savfactory4) + 20.0 and GetWhoShotMe(M.savfactory4) or 0;

		-- keep track of who shot each factory part recently
		local shotp1 = IsAlive(M.factorypart1) and time < GetLastEnemyShot(M.factorypart1) + 20.0 and GetWhoShotMe(M.factorypart1) or 0;
		local shotp2 = IsAlive(M.factorypart2) and time < GetLastEnemyShot(M.factorypart2) + 20.0 and GetWhoShotMe(M.factorypart2) or 0;
		local shotp3 = IsAlive(M.factorypart3) and time < GetLastEnemyShot(M.factorypart3) + 20.0 and GetWhoShotMe(M.factorypart3) or 0;

	


		if (IsAlive(M.ip1))
		then
			-- target assignment for defender 1
			local shot = M.badman1;
			if (shot1) then
				shot = shot1;
			elseif (shot2) then
				shot = shot2;
			elseif (shot3) then
				shot = shot3;
			elseif (shot4) then
				shot = shot4;
			elseif (shotp1) then
				shot = shotp1;
			elseif (shotp2) then
				shot = shotp2;
			elseif (shotp3) then
				shot = shotp3;
			end
			if ( M.badman1 ~= shot )
			then
				M.badman1 = shot;
				Attack(M.ip1, M.badman1);
			end
		end

		if (IsAlive(M.ip2))
		then
			-- target assignment for defender 2
			local shot = M.badman2;
			if (shot2) then
				shot = shot2;
			elseif (shot1) then
				shot = shot1;
			elseif (shot3) then
				shot = shot3;
			elseif (shot4) then
				shot = shot4;
			elseif (shotp1) then
				shot = shotp1;
			elseif (shotp2) then
				shot = shotp2;
			elseif (shotp3) then
				shot = shotp3;
			end
			if (M.badman2 ~= shot)
			then
				M.badman2 = shot;
				Attack(M.ip2, M.badman2);
			end
		end

		if (IsAlive(M.ip3))
		then
			-- target assignment for defender 3
			local shot = M.badman3;
			if (shot3) then
				shot = shot3;
			elseif (shot4) then
				shot = shot4;
			elseif (shot2) then
				shot = shot2;
			elseif (shot1) then
				shot = shot1;
			elseif (shotp3) then
				shot = shotp3;
			elseif (shotp2) then
				shot = shotp2;
			elseif (shotp1) then
				shot = shotp1;
			end
			if (M.badman3 ~= shot)
			then
				M.badman3 = shot;
				Attack(M.ip3, M.badman3);
			end
		end

		if (IsAlive(M.ip4))
		then
			-- target assignment for defender 4
			local shot = M.badman4;
			if (shot4) then
				shot = shot4;
			elseif (shot3) then
				shot = shot3;
			elseif (shot2) then
				shot = shot2;
			elseif (shot1) then
				shot = shot1;
			elseif (shotp3) then
				shot = shotp3;
			elseif (shotp2) then
				shot = shotp2;
			elseif (shotp1) then
				shot = shotp1;
			end
			if (M.badman4 ~= shot)
			then
				M.badman4 = shot;
				Attack(M.ip4, M.badman4);
			end
		end
	end

	if
		(
		( not IsAlive(M.avrec)) and (M.missionfail == false)
		)
	then
		FailMission(GetTime()+20.0, "misn17l1.des");
		AudioMessage("misn1704.wav");
		
		M.missionfail = true;
	end

	if
	(
	(M.tower1dead == true)  and 
	(M.tower2dead == true)  and 
	(M.tower3dead == true)  and 
	(M.tower4dead == true)  and 
	(M.tower5dead == true)  and 
	(M.tower6dead == true)  and 
	(M.tower7dead == true)  and 
	(M.towersdestroyed == false)
	)
		then
		if
			(M.minesmade == false)
		then
			GetRidOfSomeScrap();

		M.MINE[1] = exu.BuildAsyncObject("boltmine2", 2, "mine54"); -- needs fixed in bzn
		M.MINE[2] = exu.BuildAsyncObject("boltmine2", 2, "mine1");
		M.MINE[3] = exu.BuildAsyncObject("boltmine2", 2, "mine2");
		M.MINE[4] = exu.BuildAsyncObject("boltmine2", 2, "mine3");
		M.MINE[5] = exu.BuildAsyncObject("boltmine2", 2, "mine4");
		M.MINE[6] = exu.BuildAsyncObject("boltmine2", 2, "mine5");
		M.MINE[7] = exu.BuildAsyncObject("boltmine2", 2, "mine6");
		M.MINE[8] = exu.BuildAsyncObject("boltmine2", 2, "mine7");
		M.MINE[9] = exu.BuildAsyncObject("boltmine2", 2, "mine8");
		M.MINE[10] = exu.BuildAsyncObject("boltmine2", 2, "mine9");
		M.MINE[11] = exu.BuildAsyncObject("boltmine2", 2, "mine10");
		M.MINE[12] = exu.BuildAsyncObject("boltmine2", 2, "mine11");
		M.MINE[13] = exu.BuildAsyncObject("boltmine2", 2, "mine12");
		M.MINE[14] = exu.BuildAsyncObject("boltmine2", 2, "mine13");
		M.MINE[15] = exu.BuildAsyncObject("boltmine2", 2, "mine14");
		M.MINE[16] = exu.BuildAsyncObject("boltmine2", 2, "mine15");
		M.MINE[17] = exu.BuildAsyncObject("boltmine2", 2, "mine16");
		M.MINE[18] = exu.BuildAsyncObject("boltmine2", 2, "mine17");
		M.MINE[19] = exu.BuildAsyncObject("boltmine2", 2, "mine18");
		M.MINE[20] = exu.BuildAsyncObject("boltmine2", 2, "mine19");
		M.MINE[21] = exu.BuildAsyncObject("boltmine2", 2, "mine20");
		M.MINE[22] = exu.BuildAsyncObject("boltmine2", 2, "mine21");
		M.MINE[23] = exu.BuildAsyncObject("boltmine2", 2, "mine22");
		M.MINE[24] = exu.BuildAsyncObject("boltmine2", 2, "mine23");
		M.MINE[25] = exu.BuildAsyncObject("boltmine2", 2, "mine24");
		M.MINE[26] = exu.BuildAsyncObject("boltmine2", 2, "mine25");
		M.MINE[27] = exu.BuildAsyncObject("boltmine2", 2, "mine26");
		M.MINE[28] = exu.BuildAsyncObject("boltmine2", 2, "mine27");
		M.MINE[29] = exu.BuildAsyncObject("boltmine2", 2, "mine28");
		M.MINE[30] = exu.BuildAsyncObject("boltmine2", 2, "mine29");
		M.MINE[31] = exu.BuildAsyncObject("boltmine2", 2, "mine30");
		M.MINE[32] = exu.BuildAsyncObject("boltmine2", 2, "mine31");
		M.MINE[33] = exu.BuildAsyncObject("boltmine2", 2, "mine32");
		M.MINE[34] = exu.BuildAsyncObject("boltmine2", 2, "mine33");
		M.MINE[35] = exu.BuildAsyncObject("boltmine2", 2, "mine34");
		M.MINE[36] = exu.BuildAsyncObject("boltmine2", 2, "mine35");
		M.MINE[37] = exu.BuildAsyncObject("boltmine2", 2, "mine36");
		M.MINE[38] = exu.BuildAsyncObject("boltmine2", 2, "mine37");
		M.MINE[39] = exu.BuildAsyncObject("boltmine2", 2, "mine38");
		M.MINE[40] = exu.BuildAsyncObject("boltmine2", 2, "mine39");
		M.MINE[41] = exu.BuildAsyncObject("boltmine2", 2, "mine40");
		M.MINE[42] = exu.BuildAsyncObject("boltmine2", 2, "mine41");
		M.MINE[43] = exu.BuildAsyncObject("boltmine2", 2, "mine42");
		M.MINE[44] = exu.BuildAsyncObject("boltmine2", 2, "mine43");
		M.MINE[45] = exu.BuildAsyncObject("boltmine2", 2, "mine44");
		M.MINE[46] = exu.BuildAsyncObject("boltmine2", 2, "mine45");
		M.MINE[47] = exu.BuildAsyncObject("boltmine2", 2, "mine46");
		M.MINE[48] = exu.BuildAsyncObject("boltmine2", 2, "mine47");
		M.MINE[49] = exu.BuildAsyncObject("boltmine2", 2, "mine48");
		M.MINE[50] = exu.BuildAsyncObject("boltmine2", 2, "mine49");
		M.MINE[51] = exu.BuildAsyncObject("boltmine2", 2, "mine55"); -- needs fixed in bzn
		M.MINE[52] = exu.BuildAsyncObject("boltmine2", 2, "mine56"); -- needs fixed in bzn
		M.MINE[53] = exu.BuildAsyncObject("boltmine2", 2, "mine52");
		M.MINE[54] = exu.BuildAsyncObject("boltmine2", 2, "mine53");
		M.minesmade = true;
		end
		CameraReady();
		M.newobjective = true;
		M.towersdestroyed = true;
		M.minesdestroyed = true;
		M.minecinstart = true;
		M.minecount = 0;
		M.mineaudio = AudioMessage("misn1730.wav");
		end

	if
		(
		(M.minesdestroyed == true) and (M.minesmade == true)
		)
		then
		Damage(M.MINE[M.minecount], 10000);
		M.minecount = M.minecount + 1;
			if
				(M.minecount > 53)
			then
			M.minesdestroyed = false;
			end
		end

	if
		(
		(M.minesdestroyed == true) and (M.minecin == false)
		)
			then
			CameraPath("minecin", 1000, 500, M.savfactory2);
			end

	if
		(M.minecinstart == true) 
	then
	if
		(
		(IsAudioMessageDone(M.mineaudio))  or  (CameraCancelled())
		)
			then
			CameraFinish();
			M.minecin  = true;
			StopAudioMessage(M.mineaudio);
			M.minecinstart = false;
			end
	end

	if
		(
		(M.missionwon == false)  and 
		( not IsAlive(M.factorypart1))  and 
		( not IsAlive(M.factorypart2))  and 
		( not IsAlive(M.factorypart3))
		)
	then
		AudioMessage("misn1703.wav");
		M.missionwon = true;
		SucceedMission(GetTime() + 7.0, "misn17w1.des");
		CameraReady();
		M.cinscrap = exu.BuildAsyncObject("eggeizr1", 3, "cinscrap");
		if ( not M.savfactory1)
		then
			local EndScenePos = SetVector(2990, 64, 101376);   --forcing this because if you have a save game where you blew up the M.savfactory1 its position is not retrievable hence this nasty hack.
			M.savfactory1 = exu.BuildAsyncObject("eggeizr1", 3, EndScenePos);		--if we killed the factory put a geyser where it used to be.
		end
		--		CameraObject(M.cinscrap, 1000, 8000, 1000, M.savfactory1);
		CameraObject(M.cinscrap, 1000, 8000, 1000, M.savfactory1);
		M.sf2blow = GetTime() + 1.0;
		M.sf4blow = GetTime() + 2.5;
		M.sf3blow = GetTime() + 3.2;
	end


	if
		(M.missionwon == true)
	then
		if
			(
			 (M.sf2gone == false) and (M.sf2blow < GetTime())
			 )
		then
			Damage(M.savfactory2, 200000);
			M.sf2gone = true;
		end
		if
			(
			 (M.sf3gone == false) and (M.sf3blow < GetTime())
			 )
		then
			Damage(M.savfactory3, 200000);
			M.sf3gone = true;
		end
		if
			(
			 (M.sf4gone == false) and (M.sf4blow < GetTime())
			 )
		then
			Damage(M.savfactory1, 200000);
			Damage(M.savfactory4, 200000);
			M.sf4gone = true;
		end
	end


-- END OF SCRIPT
	
end
--[[
function GetRidOfSomeScrap(void)
then
	while (true)
	then
		local scrapCount = 0;
		GameObject *scrap = nil;
		Objectlocalh;
		h.handle = -1;
		unsigned scrapSeqNo = h.seqNo;
		ObjectList &list = *GameObject::objectList;
		ObjectList::iterator i;
		for (i = list.begin(); i ~= list.end(); i++)
		then
			GameObject *o = *i;
			if (o->GetClass()->sig == 'SCRP') then
				scrapCount++;
				if (o->GetSeqNo() < scrapSeqNo) then
					scrapSeqNo = o->GetSeqNo();
					scrap = o;
				end
				continue;
			end
		end
		if (scrapCount < 300)
			break;
		scrap->Remove();
	end
end
--]]

