#include "GameCommon.h"

#include "..\fun3d\AiMission.h"
#include "..\fun3d\ScriptUtils.h"

/*
	Misn17Mission
*/

static void GetRidOfSomeScrap(void);

class Misn17Mission : public AiMission {
	DECLARE_RTIME(Misn17Mission)
public:
	Misn17Mission(void);
	~Misn17Mission();

	virtual bool Load(file fp);
	virtual bool PostLoad(void);
	virtual bool Save(file fp);

	virtual void Update(void);

	virtual void AddObject(GameObject *gameObj);

private:
	void Setup(void);
	void AddObject(Handle h);
	void Execute(void);

	// bools
	union {
		struct {
			bool
				missionstart, raw1there, raw2there, raw3there, raw4there, raw5there,
				prothere, inprocess, minesmade, openingcin, camera1, camera2, camera3, 
				camera4, camera5, camera6, camera7,
				dispatch, dispatch2, cineractive1, cineractive2, openingcindone, 
				crysswitched, factorydestroyed, attackwavesent, firsttimecrysreplaced,
				newobjective, checktug, crystalhint1, crystalhint2, crystalhint3, 
				said1, procrysgone, missionfail, missionwon, defenders, 
				minecin, minesdestroyed, towersdestroyed,
				tower1spawn, tower2spawn, tower3spawn, tower4spawn, 
				tower5spawn, tower6spawn, tower7spawn, 
				tower1dead, tower2dead, tower3dead, tower4dead, tower5dead, 
				tower6dead, tower7dead, minecinstart, factorypart1dead,
				factorypart2dead, factorypart3dead, sf2gone, sf3gone, sf4gone,
				fact1gone, fact2gone, fact3gone, critstatement,
				b_last;
		};
		bool b_array[64];
	};

	// floats
	union {
		struct {
			float
				discheck, minedistancecheck, waveattacks,spawntime1, 
				spawntime2, spawntime3, spawntime4,
				tower1check,  tower2check, tower3check, tower4check,
				tower5check, tower6check, tower7check, sf2blow, sf3blow, sf4blow,
				procrysdes, rawcrys1des, rawcrys2des, rawcrys3des, rawcrys4des,
				rawcrys5des, procrysreplace, rawcrys1replace, rawcrys2replace,
				rawcrys3replace, camdone, rawcrys4replace, rawcrys5replace, op1replace, op2replace, op3replace, op4replace,
				f_last;
		};
		float f_array[34];
	};

	// handles
	union {
		struct {
			Handle
				savfactory1, savfactory2, savfactory3, savfactory4,
				deftow1a, deftow1b, deftow2a, deftow2b,
				factorynav, basenav, badman1, badman2, badman3,
				badman4, badman5, badman6, badman7, badman8,
				badman9, badman10, badman11, badman12,
				badman13, badman14,
				deftow3a, deftow3b, deftow4a, deftow4b,
				deftow5a, deftow5b, deftow6a, deftow6b, aud1,
				trig1, trig2, trig3, trig4, trig5, trig6, trig7,
				deftow7a, deftow7b, factorypart1, factorypart2, factorypart3,
				procrys, rawcrys1, rawcrys2, rawcrys3, rawcrys4, rawcrys5, miner,
				avrec, prey1, ip1, ip2, ip3, ip4,
				cam1, cam2, cam3, cam4, cam5, cam6, aw1, aw2, aw3, aw4, tug,
				MINE[53], mineaudio, cinscrap, art1, art2, art3, 
				art4, art5, desart1, desart2, desart3, desart4, desart5, 
				tower1, tower2, tower3, tower4, tower5, tower6, tower7,
				h_last;
		};
		Handle h_array[141];
	};

	// integers
	union {
		struct {
			int
				hint, minecount, crit,
				i_last;
		};
		int i_array[3];
	};
};

void Misn17Mission::Setup(void)
{
	/*
		Initialize variables
	*/
	camdone = 9999999999.0f;
	discheck = 9999999999.0f;
	savfactory1 = 0; 
	savfactory2 = 0; 
	savfactory3 = 0; 
	savfactory4 = 0;
	procrys = 0; 
	rawcrys1 = 0; 
	rawcrys2 = 0; 
	rawcrys3 = 0; 
	rawcrys4 = 0; 
	rawcrys5 = 0; 
	miner = 0;
	avrec = 0; 
	prey1 = 0;
	factorypart1 = 0;
	factorypart2 = 0;
	factorypart3 = 0;
	aud1 = 0;
	missionwon = false;
	cinscrap = 0;
	badman1 = 0;
	badman2 = 0;
	badman3 = 0;
	badman4 = 0;
	badman5 = 0;
	badman6 = 0;
	badman7 = 0;
	badman8 = 0;
	badman9 = 0;
	badman10 = 0;
	badman11 = 0;
	badman12 = 0;
	badman13 = 0;
	badman14 = 0;
	ip1 = 0; 
	ip2 = 0; 
	ip3 = 0; 
	ip4 = 0;
	cam1 = 0; 
	cam2 = 0; 
	cam3 = 0; 
	cam4 = 0; 
	cam5 = 0; 
	cam6 = 0; 
	aw1 = 0; 
	aw2 = 0; 
	aw3 = 0; 
	aw4 = 0; 
	tug = 0;
	factorynav = 0;
	basenav = 0;
	sf2gone = false;
	sf3gone = false;
	sf4gone = false;
	sf2blow = 99999999999.0f;
	sf3blow = 99999999999.0f;
	sf4blow = 99999999999.0f;
	deftow1a = 0;
	deftow1b = 0;
	deftow2a = 0;
	deftow2b = 0;
	deftow3a = 0;
	deftow3b = 0;
	deftow4a = 0;
	deftow4b = 0;
	deftow5a = 0;
	deftow5b = 0;
	deftow6a = 0;
	deftow6b = 0;
	deftow7a = 0;
	deftow7b = 0;
	MINE[53] = 0; 
	mineaudio = 0;
	tower1 = 0; 
	tower2 = 0; 
	tower3 = 0; 
	tower4 = 0; 
	tower5 = 0; 
	tower6 = 0; 
	tower7 = 0;
	towersdestroyed = false;
	minecin = false;
	defenders = false;
	said1 = false;
	missionstart = false;
	dispatch2 = false;
	inprocess = false;
	minecinstart = false;
	checktug = false;
	newobjective = false;
	crysswitched = false;
	factorydestroyed = false;
	attackwavesent = false;
	firsttimecrysreplaced = false;
	dispatch = false;
	missionfail = false;
	openingcin = false;
	factorypart1dead = false;
	factorypart2dead = false;
	factorypart3dead = false;
	openingcin = false;
	camera1 = true;
	camera2 = false;
	camera3 = false;
	camera4 = false;
	camera5 = false;
	camera6 = false;
	camera7 = false;
	openingcindone = false;
	trig1 = 0;
	trig2 = 0;
	trig3 = 0;
	trig4 = 0;
	trig5 = 0;
	trig6 = 0;
	trig7 = 0;
	hint = 0;
	spawntime1 = 999999999.0f;
	spawntime2 = 999999999.0f;
	spawntime3 = 999999999.0f;
	spawntime4 = 999999999.0f;
	minedistancecheck = 999999999.0f;
	crit = 0;
	fact1gone = false;
	fact2gone = false;
	fact3gone = false;
	critstatement = false;
	minesmade = false;
	tower1dead = false;
	tower2dead = false;
	tower3dead = false;
	tower4dead = false;
	tower5dead = false;
	tower6dead = false;
	tower7dead = false;
	tower1check = 9999999999.0f;
	tower2check = 9999999999.0f;
	tower3check = 9999999999.0f;
	tower4check = 9999999999.0f;
	tower5check = 9999999999.0f;
	tower6check = 9999999999.0f;
	tower7check = 9999999999.0f;
	tower1spawn = false;
	tower2spawn = false;
	tower3spawn = false;
	tower4spawn = false;
	tower5spawn = false;
	tower6spawn = false;
	tower7spawn = false;
	desart1 = 0;
	desart2 = 0;
	desart3 = 0;
	desart4 = 0;
	desart5 = 0;
	art1 = 0;
	art2 = 0;
	art3 = 0;
	art4 = 0;
	art5 = 0;
}

void Misn17Mission::AddObject(Handle h)
{
	if ((art1 == NULL) && (IsOdf(h,"avartl")))
	{
		art1 = h;
	}
	else if ((art2 == NULL) && (IsOdf(h,"avartl")))
	{
		art2 = h;
	}		
	else if ((art3 == NULL) && (IsOdf(h,"avartl")))
	{
		art3 = h;
	}
	else if ((art4 == NULL) && (IsOdf(h,"avartl")))
	{
		art4 = h;
	}
	else if ((art5 == NULL) && (IsOdf(h,"avartl")))
	{
		art5 = h;
	}
}

void Misn17Mission::Execute(void)
{
#if 0
	/*
	   Event loop.
	*/
	if
		(missionstart == false)
	{
		minedistancecheck = GetTime() + 10.0f;
		aud1 = AudioMessage ("misn1701.wav");
		avrec = GetHandle ("avrecy18_recycler");
		savfactory1 = GetHandle ("savfactory1");
		savfactory2 = GetHandle ("savfactory2");
		savfactory3 = GetHandle ("savfactory3");
		savfactory4 = GetHandle ("savfactory4");
		factorypart1 = GetHandle("factorypart1");
		factorypart2 = GetHandle("factorypart2");
		factorypart3 = GetHandle("factorypart3");
		factorynav = GetHandle("factorynav");
		basenav = GetHandle("basenav");
		tower1 = BuildObject("hbptow", 2, "geizer1");
		tower2 = BuildObject("hbptow", 2, "geizer2");
		tower3 = BuildObject("hbptow", 2, "geizer3");
		tower4 = BuildObject("hbptow", 2, "geizer4");
		tower5 = BuildObject("hbptow", 2, "geizer5");
		tower6 = BuildObject("hbptow", 2, "geizer6");
		tower7 = BuildObject("hbptow", 2, "geizer7");
		SetObjectiveOn(tower1);
		SetObjectiveOn(tower2);
		SetObjectiveOn(tower3);
		SetObjectiveOn(tower4);
		SetObjectiveOn(tower5);
		SetObjectiveOn(tower6);
		SetObjectiveOn(tower7);
		SetObjectiveName(tower1, "Tower 1");
		SetObjectiveName(tower2, "Tower 2");
		SetObjectiveName(tower3, "Tower 3");
		SetObjectiveName(tower4, "Tower 4");
		SetObjectiveName(tower5, "Tower 5");
		SetObjectiveName(tower6, "Tower 6");
		SetObjectiveName(tower7, "Tower 7");
		GameObjectHandle :: GetObj(factorynav) ->SetName ("Furies Factory");
		GameObjectHandle :: GetObj(basenav) ->SetName ("Home Base");
		missionstart = true;
		waveattacks = GetTime()+1800.0f;
		newobjective = true;
		camdone = GetTime() +35.0f;
		SetScrap (1, 40);
		spawntime1 = GetTime () + 10.0f;
		spawntime2 = GetTime () + 100.0f;
		spawntime3 = GetTime () + 220.0f;
		spawntime4 = GetTime () + 340.0f;
		SetAIP ("misn17.aip");
		discheck = GetTime() + 30.0f;
		tower1check = GetTime() + 3.0f;
		tower2check = GetTime() + 3.0f;
		tower3check = GetTime() + 3.0f;
		tower4check = GetTime() + 3.0f;
		tower5check = GetTime() + 3.0f;
		tower6check = GetTime() + 3.0f;
		tower7check = GetTime() + 3.0f;
		CameraReady();
	}

	if
		(
		(IsAlive(art1)) && (!IsAlive(desart1))
		)
	{
		desart1 = BuildObject("hvsav", 2, "counter");
		Attack(desart1, art1);
	}
if
		(
		(IsAlive(art2)) && (!IsAlive(desart2))
		)
	{
		desart2 = BuildObject("hvsav", 2, "counter");
		Attack(desart2, art2);
	}
if
		(
		(IsAlive(art3)) && (!IsAlive(desart3))
		)
	{
		desart3 = BuildObject("hvsav", 2, "counter");
		Attack(desart3, art3);
	}
if
		(
		(IsAlive(art4)) && (!IsAlive(desart4))
		)
	{
		desart4 = BuildObject("hvsav", 2, "counter");
		Attack(desart4, art4);
	}
if
		(
		(IsAlive(art5)) && (!IsAlive(desart5))
		)
	{
		desart5 = BuildObject("hvsav", 2, "counter");
		Attack(desart5, art5);
	}
	if 
		(openingcin == false)
	{
		CameraReady ();
		camera1 = true;
		openingcin = true;
	}

	if 
		(camera2 == true)
	{
		if (CameraPath ("cineractive2", 500, 2000, tower1))
			 
			//	(PanDone())
			{
				camera2 = false;
				camera3 = true;
			}
	}

	if 
		(camera3 == true)
	{
		if (CameraPath("cineractive3", 1000, 2000, tower6))
		
//				(PanDone())
			{
				camera3 = false;
				camera4 = true;
			}
	}

	if 
		(camera4 == true)
	{
		if (CameraPath("cineractive5", 1000, 2000, tower3))
		
//				(PanDone())
			{
				camera4 = false;
				camera5 = true;
			}
	}
	if 
		(camera5 == true)
	{
		if (CameraPath("cineractive6", 1000, 2000, tower4))
		
//				(PanDone())
			{
				camera5 = false;
				camera6 = true;
			}
	}

	if 
		(camera6 == true)
	{
		if (CameraPath("cineractive4", 1000, 2000, tower5))
		
//				(PanDone())
			{
				camera6 = false;
				camera7 = true;
			}
	}

	if 
		(camera7 == true)
	{
		if (CameraPath("cineractive7", 1000, 1700, tower7))
		
//				(PanDone())
			{
				camera7 = false;
				CameraFinish();
			}
	}
	if
		(camera1 == true)
	{
			if
				(CameraPath("cineractive1", 1000, 2000, savfactory1))
//				(PanDone())
			{
				camera1 = false;
				camera2 = true;
				
			}
	}
	if
		(openingcindone == false)
	{
		if
		(
		 (IsAudioMessageDone(aud1)) || (CameraCancelled())
		)
	{
		CameraFinish();
		StopAudioMessage(aud1);
		openingcindone = true;
		camera1 = false;
		camera2 = false;
		camera3 = false;
		camera4 = false;
		camera5 = false;
		camera6 = false;
		camera7 = false;
		CameraFinish();
	}
	}

	/*if
		(cineractive1 == false)
	{
		CameraPath("cineractive1", 1000, 2000, savfactory1);
		cineractive2 = true;
	}

	if
		(
		(cineractive2 == true) && (PanDone())
		)
	{
		CameraPath("cineractive2", 200, 2000, tower1);
		cineractive1 = true;
	}

	if
		(
		(cineractive1 == true) && (PanDone())
		)
	{
		CameraFinish();
	}*/

	if
		(
		(factorypart1dead == false) &&
		(!IsAlive(factorypart1))
		)
	{
		BuildObject("eggiezr1", 3, "part1geizer");
		factorypart1dead = true;
	}

	if
		(
		(factorypart2dead == false) &&
		(!IsAlive(factorypart2))
		)
	{
		BuildObject("eggiezr1", 3, "part2geizer");
		factorypart2dead = true;
	}

	if
		(
		(factorypart3dead == false) &&
		(!IsAlive(factorypart3))
		)
	{
		BuildObject("eggiezr1", 3, "part3geizer");
		factorypart3dead = true;
	}

	if
		(
		(minesmade == false) && (minedistancecheck < GetTime())
		)
	{
		miner = GetNearestEnemy(savfactory2);
		if
			(
		(GetDistance(miner, "pt1") < 610.0f) ||
		(GetDistance(miner, "pt2") < 610.0f) ||
		(GetDistance(miner, "pt3") < 610.0f) 
		)

		{
		MINE[1] = BuildObject("boltmine2", 2, "mine1");
		MINE[2] = BuildObject("boltmine2", 2, "mine2");
		MINE[3] = BuildObject("boltmine2", 2, "mine3");
		MINE[4] = BuildObject("boltmine2", 2, "mine4");
		MINE[5] = BuildObject("boltmine2", 2, "mine5");
		MINE[6] = BuildObject("boltmine2", 2, "mine6");
		MINE[7] = BuildObject("boltmine2", 2, "mine7");
		MINE[8] = BuildObject("boltmine2", 2, "mine8");
		MINE[9] = BuildObject("boltmine2", 2, "mine9");
		MINE[10] = BuildObject("boltmine2", 2," mine10");
		MINE[11] = BuildObject("boltmine2", 2, "mine11");
		MINE[12] = BuildObject("boltmine2", 2, "mine12");
		MINE[13] = BuildObject("boltmine2", 2, "mine13");
		MINE[14] = BuildObject("boltmine2", 2, "mine14");
		MINE[15] = BuildObject("boltmine2", 2, "mine15");
		MINE[16] = BuildObject("boltmine2", 2, "mine16");
		MINE[17] = BuildObject("boltmine2", 2, "mine17");
		MINE[18] = BuildObject("boltmine2", 2, "mine18");
		MINE[19] = BuildObject("boltmine2", 2, "mine19");
		MINE[20] = BuildObject("boltmine2", 2, "mine20");
		MINE[21] = BuildObject("boltmine2", 2, "mine21");
		MINE[22] = BuildObject("boltmine2", 2, "mine22");
		MINE[23] = BuildObject("boltmine2", 2, "mine23");
		MINE[24] = BuildObject("boltmine2", 2, "mine24");
		MINE[25] = BuildObject("boltmine2", 2, "mine25");
		MINE[26] = BuildObject("boltmine2", 2, "mine26");
		MINE[27] = BuildObject("boltmine2", 2, "mine27");
		MINE[28] = BuildObject("boltmine2", 2, "mine28");
		MINE[29] = BuildObject("boltmine2", 2, "mine29");
		MINE[30] = BuildObject("boltmine2", 2, "mine30");
		MINE[31] = BuildObject("boltmine2", 2, "mine31");
		MINE[32] = BuildObject("boltmine2", 2, "mine32");
		MINE[33] = BuildObject("boltmine2", 2, "mine33");
		MINE[34] = BuildObject("boltmine2", 2, "mine34");
		MINE[35] = BuildObject("boltmine2", 2, "mine35");
		MINE[36] = BuildObject("boltmine2", 2, "mine36");
		MINE[37] = BuildObject("boltmine2", 2, "mine37");
		MINE[38] = BuildObject("boltmine2", 2, "mine38");
		MINE[39] = BuildObject("boltmine2", 2, "mine39");
		MINE[40] = BuildObject("boltmine2", 2, "mine40");
		MINE[41] = BuildObject("boltmine2", 2, "mine41");
		MINE[42] = BuildObject("boltmine2", 2, "mine42");
		MINE[43] = BuildObject("boltmine2", 2, "mine43");
		MINE[44] = BuildObject("boltmine2", 2, "mine44");
		MINE[45] = BuildObject("boltmine2", 2, "mine45");
		MINE[46] = BuildObject("boltmine2", 2, "mine46");
		MINE[47] = BuildObject("boltmine2", 2, "mine47");
		MINE[48] = BuildObject("boltmine2", 2, "mine48");
		MINE[49] = BuildObject("boltmine2", 2, "mine49");
		MINE[50] = BuildObject("boltmine2", 2, "mine50");
		MINE[51] = BuildObject("boltmine2", 2, "mine51");
		MINE[52] = BuildObject("boltmine2", 2, "mine52");
		MINE[53] = BuildObject("boltmine2", 2, "mine53");
		minesmade = true;
		}
		minedistancecheck = GetTime() + 3.0f;
	}
	if
		(
		(IsAlive(tower1)) &&
		(tower1spawn == false) && (tower1check < GetTime())
		)
	{
		trig1 = GetNearestEnemy(tower1);
		if
			(GetDistance(tower1, trig1) < 400.0f)
		{
			deftow1a = BuildObject("hvsat", 2, tower1);
			deftow1b = BuildObject("hvsat", 2, tower1);
			Defend2(deftow1a, tower1, 1000);
			Defend2(deftow1b, tower1, 1000);
			tower1spawn = true;
		}

		tower1check = GetTime() + 2.0f;
		trig1 = 0;
	}

	if
		(
		(IsAlive(deftow1a)) && (GetCurrentCommand(deftow1a) == CMD_DEFEND)
		)
	{
		if
			(GameObjectHandle::GetObj(deftow1a) -> GetLastEnemyShot() > 0)
		{
			badman1 = GameObjectHandle::GetObj(deftow1a) -> GetWhoTheHellShotMe();
			Attack (deftow1a, badman1, 1);
		}
	}
	if
		(
		(IsAlive(deftow1b)) && (GetCurrentCommand(deftow1b) == CMD_DEFEND)
		)
	{
		if
			(GameObjectHandle::GetObj(deftow1b) -> GetLastEnemyShot() > 0)
		{
			badman2 = GameObjectHandle::GetObj(deftow1b) -> GetWhoTheHellShotMe();
			Attack (deftow1b, badman2, 1);
		}
	}
	if
		(
		(IsAlive(deftow2a)) && (GetCurrentCommand(deftow2a) == CMD_DEFEND)
		)
	{
		if
			(GameObjectHandle::GetObj(deftow2a) -> GetLastEnemyShot() > 0)
		{
				badman3 = GameObjectHandle::GetObj(deftow2a) -> GetWhoTheHellShotMe();
			Attack (deftow2a, badman3, 1);
		}
	}
	if
		(
		(IsAlive(deftow2b)) && (GetCurrentCommand(deftow2b) == CMD_DEFEND)
		)
	{
		if
			(GameObjectHandle::GetObj(deftow2b) -> GetLastEnemyShot() > 0)
		{
			badman4 = GameObjectHandle::GetObj(deftow2b) -> GetWhoTheHellShotMe();
			Attack (deftow2b, badman4, 1);
		}
	}

	if
		(
		(IsAlive(deftow3a)) && (GetCurrentCommand(deftow3a) == CMD_DEFEND)
		)
	{
		if
			(GameObjectHandle::GetObj(deftow3a) -> GetLastEnemyShot() > 0)
		{
			badman5 = GameObjectHandle::GetObj(deftow3a) -> GetWhoTheHellShotMe();
			Attack (deftow3a, badman5, 1);
		}
	}

	if
		(
		(IsAlive(deftow3b)) && (GetCurrentCommand(deftow3b) == CMD_DEFEND)
		)
	{
		if
			(GameObjectHandle::GetObj(deftow3b) -> GetLastEnemyShot() > 0)
		{
			badman6 = GameObjectHandle::GetObj(deftow3b) -> GetWhoTheHellShotMe();
			Attack (deftow3b, badman6, 1);
		}
	}

	if
		(
		(IsAlive(deftow4a)) && (GetCurrentCommand(deftow4a) == CMD_DEFEND)
		)
	{
		if
			(GameObjectHandle::GetObj(deftow4a) -> GetLastEnemyShot() > 0)
		{
			badman7 = GameObjectHandle::GetObj(deftow4a) -> GetWhoTheHellShotMe();
			Attack (deftow4a, badman7, 1);
		}
	}
	if
		(
		(IsAlive(deftow4b)) && (GetCurrentCommand(deftow4b) == CMD_DEFEND)
		)
	{
		if
			(GameObjectHandle::GetObj(deftow4b) -> GetLastEnemyShot() > 0)
		{
			badman8 = GameObjectHandle::GetObj(deftow4b) -> GetWhoTheHellShotMe();
			Attack (deftow4b, badman8, 1);
		}
	}

	if
		(
		(IsAlive(deftow5a)) && (GetCurrentCommand(deftow5a) == CMD_DEFEND)
		)
	{
		if
			(GameObjectHandle::GetObj(deftow5a) -> GetLastEnemyShot() > 0)
		{
			badman9 = GameObjectHandle::GetObj(deftow5a) -> GetWhoTheHellShotMe();
			Attack (deftow5a, badman9, 1);
		}
	}
	if
		(
		(IsAlive(deftow5b)) && (GetCurrentCommand(deftow5b) == CMD_DEFEND)
		)
	{
		if
			(GameObjectHandle::GetObj(deftow5b) -> GetLastEnemyShot() > 0)
		{
			badman10 = GameObjectHandle::GetObj(deftow5b) -> GetWhoTheHellShotMe();
			Attack (deftow5b, badman10, 1);
		}
	}

	if
		(
		(IsAlive(deftow6a)) && (GetCurrentCommand(deftow6a) == CMD_DEFEND)
		)
	{
		if
			(GameObjectHandle::GetObj(deftow6a) -> GetLastEnemyShot() > 0)
		{
			badman11 = GameObjectHandle::GetObj(deftow6a) -> GetWhoTheHellShotMe();
			Attack (deftow6a, badman11, 1);
		}
	}
	if
		(
		(IsAlive(deftow6b)) && (GetCurrentCommand(deftow6b) == CMD_DEFEND)
		)
	{
		if
			(GameObjectHandle::GetObj(deftow6b) -> GetLastEnemyShot() > 0)
		{
			badman12 = GameObjectHandle::GetObj(deftow6b) -> GetWhoTheHellShotMe();
			Attack (deftow6b, badman12, 1);
		}
	}

	if
		(
		(IsAlive(deftow7a)) && (GetCurrentCommand(deftow7a) == CMD_DEFEND)
		)
	{
		if
			(GameObjectHandle::GetObj(deftow7a) -> GetLastEnemyShot() > 0)
		{
			badman13 = GameObjectHandle::GetObj(deftow7a) -> GetWhoTheHellShotMe();
			Attack (deftow7a, badman14, 1);
		}
	}
	if
		(
		(IsAlive(deftow7b)) && (GetCurrentCommand(deftow7b) == CMD_DEFEND)
		)
	{
		if
			(GameObjectHandle::GetObj(deftow7b) -> GetLastEnemyShot() > 0)
		{
			badman14 = GameObjectHandle::GetObj(deftow7b) -> GetWhoTheHellShotMe();
			Attack (deftow7b, badman14, 1);
		}
	}

	if
		(
		(IsAlive(tower2)) &&
		(tower2spawn == false) && (tower2check < GetTime())
		)
	{
		trig2 = GetNearestEnemy(tower2);

		if
			(GetDistance(tower2, trig2) < 400.0f)
		{
			deftow2a = BuildObject("hvsat", 2, tower2);
			deftow2b = BuildObject("hvsat", 2, tower2);
			Defend2(deftow2a, tower2, 1000);
			Defend2(deftow2b, tower2, 1000);
			tower2spawn = true;
		}
		trig2 = 0;

		tower2check = GetTime() + 2.0f;
	}
	if
		(
		(IsAlive(tower3)) &&
		(tower3spawn == false) && (tower3check < GetTime())
		)
	{
		trig3 = GetNearestEnemy(tower3);
		if
			(GetDistance(tower3, trig3) < 400.0f)
		{
			deftow3a = BuildObject("hvsat", 2, tower3);
			deftow3b = BuildObject("hvsat", 2, tower3);
			Defend2(deftow3a, tower3, 1000);
			Defend2(deftow3b, tower3, 1000);
			tower3spawn = true;
		}
		trig3 = 0;

		tower3check = GetTime() + 2.0f;
	}

	if
		(
		(IsAlive(tower4)) &&
		(tower4spawn == false) && (tower4check < GetTime())
		)
	{
		trig4 = GetNearestEnemy(tower4);
		if
			(GetDistance(tower4, trig4) < 400.0f)
		{
			deftow4a = BuildObject("hvsat", 2, tower4);
			deftow4b = BuildObject("hvsat", 2, tower4);
			Defend2(deftow4a, tower4, 1000);
			Defend2(deftow4b, tower4, 1000);
			tower4spawn = true;
		}
		trig4 = 0;
		tower4check = GetTime() + 2.0f;
	}

	if
		(
		(IsAlive(tower5)) &&
		(tower5spawn == false) && (tower5check < GetTime())
		)
	{
		trig5 = GetNearestEnemy(tower5);
		if
			(GetDistance(tower5, trig5) < 400.0f)
		{
			deftow5a = BuildObject("hvsat", 2, tower5);
			deftow5b = BuildObject("hvsat", 2, tower5);
			Defend2(deftow5a, tower5, 1000);
			Defend2(deftow5b, tower5, 1000);
			tower5spawn = true;
		}
		trig5 = 0;
		tower5check = GetTime() + 2.0f;
	}

	if
		(
		(IsAlive(tower6)) &&
		(tower6spawn == false) && (tower6check < GetTime())
		)
	{
		trig6 = GetNearestEnemy(tower6);
		if
			(GetDistance(tower6, trig6) < 400.0f)
		{
			deftow6a = BuildObject("hvsat", 2, tower6);
			deftow6b = BuildObject("hvsat", 2, tower6);
			Defend2(deftow6a, tower6, 1000);
			Defend2(deftow6b, tower6, 1000);
			tower6spawn = true;
		}
		trig6 = 0;
		tower6check = GetTime() + 2.0f;
	}

	if
		(
		(IsAlive(tower7)) &&
		(tower7spawn == false) && (tower7check < GetTime())
		)
	{
		trig7 = GetNearestEnemy(tower7);
		if
			(GetDistance(tower7, trig7) < 400.0f)
		{
			deftow7a = BuildObject("hvsat", 2, tower7);
			deftow7b = BuildObject("hvsat", 2, tower7);
			Defend2(deftow7a, tower7, 1000);
			Defend2(deftow7b, tower7, 1000);
			tower7spawn = true;
		}
		trig7 = 0;
		tower7check = GetTime() + 2.0f;
	}

	if
		(
		(!IsAlive(tower1)) && (tower1dead == false)
		)
	{
		BuildObject("eggeizr1", 0, "geizer1");
		tower1dead = true;
	}
	if
		(
		(!IsAlive(tower2)) && (tower2dead == false)
		)
	{
		BuildObject("eggeizr1", 0, "geizer2");
		tower2dead = true;
	}
	if
		(
		(!IsAlive(tower3)) && (tower3dead == false)
		)
	{
		BuildObject("eggeizr1", 0, "geizer3");
		tower3dead = true;
	}
	if
		(
		(!IsAlive(tower4)) && (tower4dead == false)
		)
	{
		BuildObject("eggeizr1", 0, "geizer4");
		tower4dead = true;
	}
	if
		(
		(!IsAlive(tower5)) && (tower5dead == false)
		)
	{
		BuildObject("eggeizr1", 0, "geizer5");
		tower5dead = true;
	}
	if
		(
		(!IsAlive(tower6)) && (tower6dead == false)
		)
	{
		BuildObject("eggeizr1", 0, "geizer6");
		tower6dead = true;
	}
	if
		(
		(!IsAlive(tower7)) && (tower7dead == false)
		)
	{
		BuildObject("eggeizr1", 0, "geizer7");
		tower7dead = true;
	}
	if 
		(newobjective == true)
	{
		ClearObjectives();

		if
			(towersdestroyed == false)
		{
			AddObjective ("misn1701.otf", WHITE);
		}

		if
			(
			(towersdestroyed == true) && (missionwon == false)
			)
		{
			AddObjective ("misn1701.otf", GREEN);
			AddObjective ("misn1702.otf", WHITE);
		}

		if
			(missionwon == true)
		{
			AddObjective ("misn1701.otf", GREEN);
			AddObjective ("misn1702.otf", GREEN);
		}

		newobjective = false;
	}
	if
		(spawntime1 < GetTime())
	{
		BuildObject("hvsat", 2, savfactory1);
		spawntime1 = GetTime () + 400.0f;
	}
	if
		(spawntime2 < GetTime())
	{
		BuildObject("hvsav", 2, savfactory2);
		spawntime2 = GetTime () + 400.0f;
	}
	if
		(spawntime3 < GetTime())
	{
		BuildObject("hvsat", 2, savfactory3);
		spawntime3 = GetTime () + 400.0f;
	}
	if
		(spawntime4 < GetTime())
	{
		BuildObject("hvsat", 2, savfactory4);
		spawntime4 = GetTime () + 400.0f;
	}

	if
		(
		(discheck < GetTime()) && (defenders == false)
		)
	{
		prey1 = GetNearestEnemy(savfactory1);
		if
		(GetDistance(prey1, "savspawn", 1) < 450.0f) 
		{
			ip1 = BuildObject("hvsat", 2, savfactory2);
			ip2 = BuildObject("hvsat", 2, savfactory3);
			ip3 = BuildObject("hvsav", 2, savfactory4);
			ip4 = BuildObject("hvsav", 2, savfactory1);
			defenders = true;
			Defend2(ip1, savfactory2);
			Defend2(ip2, savfactory3);
			Defend2(ip3, savfactory4);
			Defend2(ip4, savfactory1);
		}
		discheck = GetTime() + 5.0f;
	}

	if
		(
		(!IsAlive(avrec)) && (missionfail == false)
		)
	{
		FailMission(GetTime()+20.0f, "misn17l1.des");
		AudioMessage("misn1704.wav");
		
		missionfail = true;
	}

	if
	(
	(tower1dead == true) &&
	(tower2dead == true) &&
	(tower3dead == true) &&
	(tower4dead == true) &&
	(tower5dead == true) &&
	(tower6dead == true) &&
	(tower7dead == true) &&
	(towersdestroyed == false)
	)
		{
		if
			(minesmade == false)
		{
			GetRidOfSomeScrap();

		MINE[1] = BuildObject("boltmine2", 2, "mine1");
		MINE[2] = BuildObject("boltmine2", 2, "mine2");
		MINE[3] = BuildObject("boltmine2", 2, "mine3");
		MINE[4] = BuildObject("boltmine2", 2, "mine4");
		MINE[5] = BuildObject("boltmine2", 2, "mine5");
		MINE[6] = BuildObject("boltmine2", 2, "mine6");
		MINE[7] = BuildObject("boltmine2", 2, "mine7");
		MINE[8] = BuildObject("boltmine2", 2, "mine8");
		MINE[9] = BuildObject("boltmine2", 2, "mine9");
		MINE[10] = BuildObject("boltmine2", 2," mine10");
		MINE[11] = BuildObject("boltmine2", 2, "mine11");
		MINE[12] = BuildObject("boltmine2", 2, "mine12");
		MINE[13] = BuildObject("boltmine2", 2, "mine13");
		MINE[14] = BuildObject("boltmine2", 2, "mine14");
		MINE[15] = BuildObject("boltmine2", 2, "mine15");
		MINE[16] = BuildObject("boltmine2", 2, "mine16");
		MINE[17] = BuildObject("boltmine2", 2, "mine17");
		MINE[18] = BuildObject("boltmine2", 2, "mine18");
		MINE[19] = BuildObject("boltmine2", 2, "mine19");
		MINE[20] = BuildObject("boltmine2", 2, "mine20");
		MINE[21] = BuildObject("boltmine2", 2, "mine21");
		MINE[22] = BuildObject("boltmine2", 2, "mine22");
		MINE[23] = BuildObject("boltmine2", 2, "mine23");
		MINE[24] = BuildObject("boltmine2", 2, "mine24");
		MINE[25] = BuildObject("boltmine2", 2, "mine25");
		MINE[26] = BuildObject("boltmine2", 2, "mine26");
		MINE[27] = BuildObject("boltmine2", 2, "mine27");
		MINE[28] = BuildObject("boltmine2", 2, "mine28");
		MINE[29] = BuildObject("boltmine2", 2, "mine29");
		MINE[30] = BuildObject("boltmine2", 2, "mine30");
		MINE[31] = BuildObject("boltmine2", 2, "mine31");
		MINE[32] = BuildObject("boltmine2", 2, "mine32");
		MINE[33] = BuildObject("boltmine2", 2, "mine33");
		MINE[34] = BuildObject("boltmine2", 2, "mine34");
		MINE[35] = BuildObject("boltmine2", 2, "mine35");
		MINE[36] = BuildObject("boltmine2", 2, "mine36");
		MINE[37] = BuildObject("boltmine2", 2, "mine37");
		MINE[38] = BuildObject("boltmine2", 2, "mine38");
		MINE[39] = BuildObject("boltmine2", 2, "mine39");
		MINE[40] = BuildObject("boltmine2", 2, "mine40");
		MINE[41] = BuildObject("boltmine2", 2, "mine41");
		MINE[42] = BuildObject("boltmine2", 2, "mine42");
		MINE[43] = BuildObject("boltmine2", 2, "mine43");
		MINE[44] = BuildObject("boltmine2", 2, "mine44");
		MINE[45] = BuildObject("boltmine2", 2, "mine45");
		MINE[46] = BuildObject("boltmine2", 2, "mine46");
		MINE[47] = BuildObject("boltmine2", 2, "mine47");
		MINE[48] = BuildObject("boltmine2", 2, "mine48");
		MINE[49] = BuildObject("boltmine2", 2, "mine49");
		MINE[50] = BuildObject("boltmine2", 2, "mine50");
		MINE[51] = BuildObject("boltmine2", 2, "mine51");
		MINE[52] = BuildObject("boltmine2", 2, "mine52");
		MINE[53] = BuildObject("boltmine2", 2, "mine53");
		minesmade = true;
		}
		CameraReady();
		newobjective = true;
		towersdestroyed = true;
		minesdestroyed = true;
		minecinstart = true;
		minecount = 0;
		mineaudio = AudioMessage("misn1730.wav");
		}

	if
		(
		(minesdestroyed == true) && (minesmade == true)
		)
		{
		Damage(MINE[minecount], 10000);
		minecount++;
			if
				(minecount > 53)
			{
			minesdestroyed = false;
			}
		}

	if
		(
		(minesdestroyed == true) && (minecin == false)
		)
			{
			CameraPath("minecin", 1000, 500, savfactory2);
			}

	if
		(minecinstart == true) 
	{
	if
		(
		(IsAudioMessageDone(mineaudio)) || (CameraCancelled())
		)
			{
			CameraFinish();
			minecin =true;
			StopAudioMessage(mineaudio);
			minecinstart = false;
			}
	}

	if
		(
		(missionwon == false) &&
		(!IsAlive(factorypart1)) &&
		(!IsAlive(factorypart2)) &&
		(!IsAlive(factorypart3))
		)
	{
		AudioMessage("misn1703.wav");
		missionwon = true;
		SucceedMission(GetTime() + 4.0f, "misn17w1.des");
		CameraReady();
		cinscrap = BuildObject("eggeizr1", 3, "cinscrap");
		CameraObject(cinscrap, 1000, 8000, 1000, savfactory1);
		sf2blow = GetTime() + 1.0f;
		sf4blow = GetTime() + 2.5f;
		sf3blow = GetTime() + 3.2f;
	}


	if
		(missionwon == true)
	{
		if
			(
			 (sf2gone == false) && (sf2blow < GetTime())
			 )
		{
			Damage(savfactory2, 200000);
			sf2gone = true;
		}
		if
			(
			 (sf3gone == false) && (sf3blow < GetTime())
			 )
		{
			Damage(savfactory3, 200000);
			sf3gone = true;
		}
		if
			(
			 (sf4gone == false) && (sf4blow < GetTime())
			 )
		{
			Damage(savfactory4, 200000);
			sf4gone = true;
		}
	}
#endif
}


IMPLEMENT_RTIME(Misn17Mission)

Misn17Mission::Misn17Mission(void)
{
}

Misn17Mission::~Misn17Mission()
{
}

void Misn17Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

bool Misn17Mission::Load(file fp)
{
	if (missionSave) {
		int i;

		// init bools
		int b_count = &b_last - b_array;
		_ASSERTE(b_count == SIZEOF(b_array));
		for (i = 0; i < b_count; i++)
			b_array[i] = false;

		// init floats
		int f_count = &f_last - f_array;
		_ASSERTE(f_count == SIZEOF(f_array));
		for (i = 0; i < f_count; i++)
			f_array[i] = 99999.0f;

		// init handles
		int h_count = &h_last - h_array;
		_ASSERTE(h_count == SIZEOF(h_array));
		for (i = 0; i < h_count; i++)
			h_array[i] = 0;

		// init ints
		int i_count = &i_last - i_array;
		_ASSERTE(i_count == SIZEOF(i_array));
		for (i = 0; i < i_count; i++)
			i_array[i] = 0;

		Setup();
		return AiMission::Load(fp);
	}

	bool ret = true;

	// bools
	int b_count = &b_last - b_array;
	_ASSERTE(b_count == SIZEOF(b_array));
	ret = ret && in(fp, b_array, sizeof(b_array));

	// floats
	int f_count = &f_last - f_array;
	_ASSERTE(f_count == SIZEOF(f_array));
	ret = ret && in(fp, f_array, sizeof(f_array));

	// Handles
	int h_count = &h_last - h_array;
	_ASSERTE(h_count == SIZEOF(h_array));
	ret = ret && in(fp, h_array, sizeof(h_array));

	// ints
	int i_count = &i_last - i_array;
	_ASSERTE(i_count == SIZEOF(i_array));
	ret = ret && in(fp, i_array, sizeof(i_array));

	ret = ret && AiMission::Load(fp);
	return ret;
}

bool Misn17Mission::PostLoad(void)
{
	if (missionSave)
		return AiMission::PostLoad();

	bool ret = true;

	int h_count = &h_last - h_array;
	for (int i = 0; i < h_count; i++)
		h_array[i] = ConvertHandle(h_array[i]);

	ret = ret && AiMission::PostLoad();

	return ret;
}

bool Misn17Mission::Save(file fp)
{
	if (missionSave)
		return AiMission::Save(fp);

	bool ret = true;

	// bools
	int b_count = &b_last - b_array;
	_ASSERTE(b_count == SIZEOF(b_array));
	ret = ret && out(fp, b_array, sizeof(b_array), "b_array");

	// floats
	int f_count = &f_last - f_array;
	_ASSERTE(f_count == SIZEOF(f_array));
	ret = ret && out(fp, f_array, sizeof(f_array), "f_array");

	// Handles
	int h_count = &h_last - h_array;
	_ASSERTE(h_count == SIZEOF(h_array));
	ret = ret && out(fp, h_array, sizeof(h_array), "h_array");

	// ints
	int i_count = &i_last - i_array;
	_ASSERTE(i_count == SIZEOF(i_array));
	ret = ret && out(fp, i_array, sizeof(i_array), "i_array");

	ret = ret && AiMission::Save(fp);
	return ret;
}

void Misn17Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

// the generic scrap/mine removal code in gameobject doesn't take
// into account the fact that 512 is also the limit on entities
// and there are more entities than game objects
// it also doesn't delete more than one scrap and one entity per
// frame, so if you build alot of stuff in one frame it doesn't make
// rooom

static void GetRidOfSomeScrap(void)
{
	while (true)
	{
		int scrapCount = 0;
		GameObject *scrap = NULL;
		OBJHANDLE h;
		h.handle = -1;
		unsigned scrapSeqNo = h.seqNo;
		ObjectList &list = *GameObject::objectList;
		ObjectList::iterator i;
		for (i = list.begin(); i != list.end(); i++)
		{
			GameObject *o = *i;
			if (o->GetClass()->sig == 'SCRP') {
				scrapCount++;
				if (o->GetSeqNo() < scrapSeqNo) {
					scrapSeqNo = o->GetSeqNo();
					scrap = o;
				}
				continue;
			}
		}
		if (scrapCount < 300)
			break;
		scrap->Remove();
	}
}
