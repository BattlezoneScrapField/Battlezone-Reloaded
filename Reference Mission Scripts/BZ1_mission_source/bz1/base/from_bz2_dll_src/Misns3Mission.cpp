#include "GameCommon.h"

#include "..\fun3d\AiMission.h"
#include "..\fun3d\ScriptUtils.h"

/*
	Misns3Mission
*/

class Misns3Mission : public AiMission {
	DECLARE_RTIME(Misns3Mission)
public:
	Misns3Mission(void);
	~Misns3Mission();

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
				economy1, economy2, economy3, economy4, unit1spawned, unit2spawned,
				unit3spawned, newobjective, unit4spawned, bdspawned2, 
				missionstart, missionwon, missionfail, bdspawned, recyclerdestroyed,
				warn1, warn2, plea1, plea2, plea3,
				mark1, play,
				minefield1, minefield2, minefield3, patrolspawned,
				b_last;
		};
		bool b_array[26];
	};

	// floats
	union {
		struct {
			float
				withdraw, help1, help2, help3,
				f_last;
		};
		float f_array[4];
	};

	// handles
	union {
		struct {
			Handle
				bd1, bd2, bd3, bd4, bd5, bd6, bd7, bd8, bd9, bd10, bd11, bd12,
				bd50, bd60, bd70, bd80, bd51, bd52, bd61, bd62, bd71, bd72, bd81, bd82,
				avrec, player, bomb1, bomb2, bomb3, bomb4, 
				pat1, pat2, Enemy1, Enemy2, cam1, cam2,
				h_last;
		};
		Handle h_array[36];
	};

	// integers
	union {
		struct {
			int
				audmsg, Checkdist, Checkdist2, Checkalive,
				aud1, aud2, aud50,
				i_last;
		};
		int i_array[7];
	};
};

void Misns3Mission::Setup(void)
{
	/*
	Here's where you
	set the values
	at the start.  
	*/
	bd1 = 0; 
		bd2 = 0;
		bd3 = 0; 
		bd4 = 0; 
		bd5 = 0; 
		bd6 = 0; 
		bd7 = 0; 
		bd8 = 0; 
		bd9 = 0; 
		bd10 = 0;
		bd11 = 0;
		bd12 = 0;
		bd50 = 0;
		bd51 = 0;
		bd52 = 0;
		bd60 = 0;
		bd61 = 0;
		bd62 = 0;
		bd70 = 0;
		bd71 = 0;
		bd72 = 0;
		bd80 = 0;
		bd81 = 0;
		bd82 = 0;
		avrec = 0;
		player = 0;
		aud50 = 0;
		Checkdist = 9999999999999.0f;
		Checkdist2 = 999999999999999.0f;
		bomb1 = 0;
		bomb2 = 0;
		bomb3 = 0;
		bomb4 = 0;
		Enemy1 = 0;
		Enemy2 = 0;
		pat1 = 0;
		pat2 = 0;
		aud1 = 0;
		aud2 = 0;
		mark1 = false;
		play = false;
		patrolspawned = false;
		bdspawned2 = false;
	missionstart = false;
	minefield1 = false;
	minefield2 = false;
	minefield3 = false;
	economy1 = false;
	economy2 = false;
	economy3 = false;
	economy4 = false;
	bdspawned = false;
	plea1 = false;
	plea2 = false;
	plea3 = false;
	unit1spawned = false;
	unit2spawned = false;
	unit3spawned = false;
	unit4spawned = false;
	newobjective = false;
	missionwon = false;
	missionfail = false;
	recyclerdestroyed = false;
	warn1 = false;
	warn2 = false;
	withdraw = 99999.0f;
	help1 = 9999999.0f;
	help2 = 9999999.0f;
	help3 = 9999999.0f;
	Checkalive = 9999999999.0f;
}

void Misns3Mission::AddObject(Handle h)
{
}

void Misns3Mission::Execute(void)
{
	/*
		Here is where you 
		put what happens 
		every frame.  
	*/

	if
		(missionstart == false)
	{
		AudioMessage("misns301.wav");
		newobjective = true;
		missionstart = true;
		avrec = GetHandle ("avrecy1_recycler");
		player = GetPlayerHandle ();
		withdraw = GetTime() + 600.0f;
		help1 = GetTime () + 120.0f;
		help2 = GetTime () + 280.0f;
		help3 = GetTime () + 380.0f;
		Checkdist = GetTime() + 5.0f;
		Checkdist2 = GetTime() + 5.0f;
		Checkalive = GetTime() + 15.0f;
		bomb1 = GetHandle("bomb1");
		bomb2 = GetHandle("bomb2");
		bomb3 = GetHandle("bomb3");
		bomb4 = GetHandle("bomb4");
		cam1 = GetHandle("basenav");
		cam2 = GetHandle("avrecy");
		GameObjectHandle :: GetObj(cam1) ->SetName ("Home Base");
		GameObjectHandle :: GetObj(cam2) ->SetName ("Black Dog Outpost");
	}
	player = GetPlayerHandle();

	if
		(newobjective == true)
	{
		ClearObjectives();
		if
			(recyclerdestroyed == true)
		{
			
			AddObjective("misns302.otf", WHITE);
			AddObjective("misns301.otf", GREEN);
		}
		if
			(recyclerdestroyed == false)
		{
			AddObjective("misns301.otf", WHITE);
		}
		if
			(missionwon == true)
		{
			AddObjective("misns302.otf", GREEN);
		}
		newobjective = false;
	}
	if
		(
		(help1 < GetTime()) && (plea1 == false)
		&& (recyclerdestroyed == false)
		)
	{
		AudioMessage("misns307.wav");
		plea1 = true;
	}
	if
		(
		(help2 < GetTime()) && (plea2 == false)
		&& (recyclerdestroyed == false)
		)
	{
		AudioMessage("misns308.wav");
		plea2 = true;
	}
	if
		(
		(help3 < GetTime()) && (plea3 == false)
		&& (recyclerdestroyed == false)
		)
	{
		AudioMessage("misns309.wav");
		plea3 = true;
	}

	if 
		(
		(IsAlive(avrec)) && (GetDistance (player, "bdspawntrig") < 200.0f)
		&& (bdspawned == false)
		)
	{
		bd1 = BuildObject ("avtank", 2, "bdspawn1");
		bd2 = BuildObject ("avtank", 2, "bdspawn1");
		bd3 = BuildObject ("avtank", 2, "bdspawn1");
		bd4 = BuildObject ("avfigh", 2, "bdspawn1");
		bd5 = BuildObject ("avfigh", 2, "bdspawn1");
		Attack(bd1, player);
		Attack(bd2, player);
		Attack(bd3, player);
		Attack(bd4, player);
		Attack(bd5, player);
		bdspawned = true;
		AudioMessage("misns310.wav");
	}

	if
		(bdspawned == true)
	{
		IsAlive(bd1);
		IsAlive(bd1);
		IsAlive(bd1);
		IsAlive(bd1);
		IsAlive(bd1);
	}

	if
		(
		(bdspawned == true) && (Checkalive < GetTime())
		)
	{
		if
			(IsAlive(bd1))
		{
			Attack(bd1, player);
		}
		if
			(IsAlive(bd2))
		{
			Attack(bd2, player);
		}
		if
			(IsAlive(bd3))
		{
			Attack(bd3, player);
		}
		if
			(IsAlive(bd4))
		{
			Attack(bd4, player);
		}
		if
			(IsAlive(bd5))
		{
			Attack(bd5, player);
		}
		if
			(
			(!IsAlive(bd1)) &&
			(!IsAlive(bd2)) &&
			(!IsAlive(bd3)) &&
			(!IsAlive(bd4)) &&
			(!IsAlive(bd5))
			)
		{
		bd1 = BuildObject ("avtank", 2, "bdspawn1");
		bd2 = BuildObject ("avtank", 2, "bdspawn1");
		bd3 = BuildObject ("avtank", 2, "bdspawn1");
		bd4 = BuildObject ("avfigh", 2, "bdspawn1");
		bd5 = BuildObject ("avfigh", 2, "bdspawn1");
		}
		Checkalive = GetTime() + 8.0f;
	}
		

	if
		(
		(!IsAlive(avrec)) && (recyclerdestroyed == false)
		)
	{
		AudioMessage("misns302.wav");
		if
			(bdspawned2 == false)
		{
		bd50= BuildObject ("avtank", 2, "bdspawn1");
		bd60 = BuildObject ("avfigh", 2, "bdspawn1");
		bd70 = BuildObject ("avfigh", 2, "bdspawn1");
		bd80 = BuildObject ("avtank", 2, "bdspawn1");
		Goto (bd50, "bdpath1");
		Goto (bd60, "bdpath2");
		Goto (bd70, "bdpath3");
		Goto (bd80, "bdpath4");
		bdspawned2 = true;
		bdspawned = false;
		}
		economy1 = true;
		economy2 = true;
		economy3 = true;
		economy4 = true;
		recyclerdestroyed = true;
		newobjective = true;
	}

	if
		(
		(economy1 == true) && (GetDistance(player, bd50) < 410.0f)
		&& (unit1spawned == false)
		)
	{
		bd51 = BuildObject ("avtank", 2, bd50);
		bd52 = BuildObject ("avtank", 2, bd50);
		Follow (bd51, bd50);
		Follow (bd52, bd50);
		unit1spawned = true;
	}

	if
		(
		(economy2 == true) && (GetDistance(player, bd60) < 410.0f)
		&& (unit2spawned == false)
		)
	{
		bd61 = BuildObject ("avfigh", 2, bd60);
		bd62 = BuildObject ("avfigh", 2, bd60);
		Follow (bd61, bd60);
		Follow (bd62, bd60);
		unit2spawned = true;
	}

	if
		(
		(economy3 == true) && (GetDistance(player, bd70) < 410.0f)
		&& (unit3spawned == false)
		)
	{
		bd71 = BuildObject ("avfigh", 2, bd70);
		bd72 = BuildObject ("avtank", 2, bd70);
		Follow (bd71, bd70);
		Follow (bd72, bd70);
		unit3spawned = true;
	}

	if
		(
		(economy4 == true) && (GetDistance(player, bd80) < 410.0f)
		&& (unit4spawned == false)
		)
	{
		bd81 = BuildObject ("avtank", 2, bd80);
		bd82 = BuildObject ("avtank", 2, bd80);
		Follow (bd81, bd80);
		Follow (bd82, bd80);
		unit4spawned = true;
	}


	if
		(
		(GetDistance(player, "homesweethome") < 200.0f) && 
		(missionwon == false) && 
		(recyclerdestroyed == true)
		)
	{
		aud50 = AudioMessage ("misns303.wav");
		missionwon = true;
	}

	if
		(
		(missionwon == true) && 
		(IsAudioMessageDone(aud50))
		)
	{
		SucceedMission (GetTime() + 0.0f, "misns3w1.des");
	}

	if
		(
		(withdraw < GetTime()) && 
		(recyclerdestroyed == false) &&
		(missionfail == false)
		)
	{
		aud2 = AudioMessage("misns304.wav");
		missionfail = true;
	}
	if
		(
		(missionfail == true) && (IsAudioMessageDone(aud2))
		)
	{
		FailMission (GetTime(), "misns3l1.des");
	}


	if 
		(
		(GetDistance (player, "don'tgohere") < 50.0f) &&
		(warn1 == false) && (recyclerdestroyed == false)
		)
	{
		AudioMessage ("misns305.wav");
		warn1 = true;
	}

	if
		(
		(GetDistance (player, "iwarnedyou") < 50.0f) &&
		(warn2 == false) && (recyclerdestroyed == false)
		)
	{
		aud1 = AudioMessage ("misns306.wav");
		warn2 = true;
	}

	if
		(
		(warn2 == true) && (IsAudioMessageDone(aud1))
		)
	{
		FailMission (GetTime(), "misns3l2.des");
	}


	if
		(patrolspawned == false)
	{

		if
			(
			(bdspawned == false) && (IsAlive(avrec))
			)
		{
			if
				(Checkdist < GetTime())
			{
					if
						(
						(GetDistance (bomb1, "patroltrig1") < 100.0f) ||
						(GetDistance (bomb2, "patroltrig1") < 100.0f) ||
						(GetDistance (bomb3, "patroltrig1") < 100.0f) ||
						(GetDistance (bomb4, "patroltrig1") < 100.0f) ||
						(GetDistance (player, "patroltrig1") < 100.0f)
						)
					{
						pat1 = BuildObject("bvraz", 2, "patrolspawn1");
						pat2 = BuildObject("bvraz", 2, "patrolspawn1");
						AudioMessage("misns219.wav");
						Goto(pat1, "patrolpath1");
						Goto(pat2, "patrolpath1");
						SetIndependence(pat1, 0);
						SetIndependence(pat2, 0);
						patrolspawned = true;
					}
					if
						(
						(GetDistance (bomb1, "patroltrig2") < 100.0f) ||
						(GetDistance (bomb2, "patroltrig2") < 100.0f) ||
						(GetDistance (bomb3, "patroltrig2") < 100.0f) ||
						(GetDistance (bomb4, "patroltrig2") < 100.0f) ||
						(GetDistance (player, "patroltrig2") < 100.0f)
						)
					{
						pat1 = BuildObject("bvraz", 2, "patrolspawn2");
						pat2 = BuildObject("bvraz", 2, "patrolspawn2");
						AudioMessage("misns219.wav");
						Goto(pat1, "patrolpath2");
						Goto(pat2, "patrolpath2");
						SetIndependence(pat1, 0);
						SetIndependence(pat2, 0);
						patrolspawned = true;
					}
					Checkdist = GetTime() + 3.0f;
			}
		}
	}

	if
		(
		(mark1 == false) &&
		(patrolspawned == true) && (bdspawned == false)
		)
	{
		Enemy1 = GetNearestEnemy(pat1);
		Enemy2 = GetNearestEnemy(pat2);
		if
			(Checkdist2 < GetTime())
		{
			if

				(GetDistance(pat1, Enemy1) < 180.0f)
			{
				bdspawned = true;
				Attack(pat1, Enemy1);
				Attack(pat2, Enemy1);
				play = true;
			}
			if
				(GetDistance(pat2, Enemy2) < 180.0f)
			{
				bdspawned = true;
				Attack(pat2, Enemy2);
				Attack(pat1, Enemy2);
				play = true;
			}
			Checkdist2 = GetTime() + 3.0f;
			if
				(
				(play == true) && (mark1 == false)
				)
			{
				AudioMessage("misns220.wav");
				mark1 = true;
			}
		}
	}

	if
		(
		(minefield1 == false)  &&
		(
		(GetDistance(player, "minetrig1") < 200.0f) ||
		(GetDistance(player, "minetrig1b") < 200.0f)
		)
		)
	{
		BuildObject("proxmine", 2, "path_1");
		BuildObject("proxmine", 2, "path_2");
		BuildObject("proxmine", 2, "path_3");
		BuildObject("proxmine", 2, "path_4");
		BuildObject("proxmine", 2, "path_5");
		BuildObject("proxmine", 2, "path_6");
		BuildObject("proxmine", 2, "path_7");
		BuildObject("proxmine", 2, "path_8");
		BuildObject("proxmine", 2, "path_9");
		BuildObject("proxmine", 2, "path_10");
		BuildObject("proxmine", 2, "path_11");
		minefield1 = true;
	}
	if
		(
		(minefield2 == false)  &&
		(
		(GetDistance(player, "minetrig2") < 200.0f) ||
		(GetDistance(player, "minetrig2b") < 200.0f)
		)
		)
	{
		BuildObject("proxmine", 2, "path_12");
		BuildObject("proxmine", 2, "path_13");
		BuildObject("proxmine", 2, "path_14");
		BuildObject("proxmine", 2, "path_15");
		BuildObject("proxmine", 2, "path_16");
		BuildObject("proxmine", 2, "path_17");
		BuildObject("proxmine", 2, "path_18");
		BuildObject("proxmine", 2, "path_19");
		BuildObject("proxmine", 2, "path_20");
		BuildObject("proxmine", 2, "path_21");
		BuildObject("proxmine", 2, "path_22");
		minefield2 = true;
	}
	if
		(
		(minefield3 == false)  &&
		(
		(GetDistance(player, "minetrig3") < 200.0f) ||
		(GetDistance(player, "minetrig3b") < 200.0f)
		)
		)
	{
		BuildObject("proxmine", 2, "path_23");
		BuildObject("proxmine", 2, "path_24");
		BuildObject("proxmine", 2, "path_25");
		BuildObject("proxmine", 2, "path_26");
		BuildObject("proxmine", 2, "path_27");
		BuildObject("proxmine", 2, "path_28");
		BuildObject("proxmine", 2, "path_29");
		BuildObject("proxmine", 2, "path_30");
		BuildObject("proxmine", 2, "path_31");
		BuildObject("proxmine", 2, "path_32");
		BuildObject("proxmine", 2, "path_33");
		BuildObject("proxmine", 2, "path_34");
		minefield3 = true;
	}



		
}

IMPLEMENT_RTIME(Misns3Mission)

Misns3Mission::Misns3Mission(void)
{
}

Misns3Mission::~Misns3Mission()
{
}

void Misns3Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

bool Misns3Mission::Load(file fp)
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

bool Misns3Mission::PostLoad(void)
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

bool Misns3Mission::Save(file fp)
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

void Misns3Mission::Update(void)
{
	AiMission::Update();
	Execute();
}
