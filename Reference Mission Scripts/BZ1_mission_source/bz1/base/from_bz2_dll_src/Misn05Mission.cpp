#include "GameCommon.h"

#include "..\fun3d\AiMission.h"
#include "..\fun3d\PowerUp.h"
#include "..\fun3d\ScriptUtils.h"

/*
	Misn05Mission Event
*/

class Misn05Mission : public AiMission {
	DECLARE_RTIME(Misn05Mission)
public:
	Misn05Mission(void);
	~Misn05Mission();

	virtual bool Load(file fp);
	virtual bool PostLoad(void);
	virtual bool Save(file fp);

	virtual void Update(void);

private:
	void Setup(void);
	void Execute(void);

	// bools
	union {
		struct {
			bool
				game_start, reconfactory, lemnossecure, missionwon, missionfail,
				neworders, ob1, ob2, ob3, ob4, basewave, attacktimeset, failmission,
				sent1Done, sent2Done, sent3Done, sent4Done, go, shuffle, notfound, 
				attackstatement, mine1built, mine2built, mine3built, mine4built, 
				mine5built, mine6built, mine7built, mine8built, mine9built, 
				mine10built, mine11built, mine12built, mine13built, mine14built, 
				mine15built, mine16built, mine17built, mine18built, mine19built, 
				mine20built, mine21built, mine22built, mine23built, attackcmd, 
				check1, check2, check3, check4, aw1sent, aw2sent, aw3sent, aw4sent,
				aw1aattack,aw2aattack,aw3aattack,aw4aattack,aw5aattack,
				aw6aattack,aw7aattack,aw8aattack,aw9aattack, possiblewin, takeoutfactory,
				lemcin1, lemcin2, reconed, needtospawn, newobjective,
				b_last;
		};
		bool b_array[69];
	};

	// floats
	union {
		struct {
			float
				processtime, sendTime[4], platoonhere, mine1, mine2 ,mine3,
				mine4, mine5, mine6, mine7, mine8, mine9, mine10, mine11, mine12,
				mine13, mine14, mine15, mine16, mine17, mine18, mine19, mine20,
				mine21, mine22, mine23, bombtime, lemcinstart, lemcinend,
				aw1t, aw2t, start, aw3t, aw4t, readtime, randomwave,
				f_last;
		};
		float f_array[39];
	};

	// handles
	union {
		struct {
			Handle
				lemnos, player, svrec, avrec, wBu1, wBu2, wBu3,
				w1u1,w1u2,w1u3,w1u4,
				w2u1,w2u2,w2u3,w2u4,
				w3u1,w3u2,w3u3,w3u4,
				w4u1,w4u2,w4u3,w4u4,
				rand1, rand2, rand3,
				MINE1, MINE2, MINE3, MINE4, MINE5, MINE6, MINE7, MINE8,
				MINE9,MINE10, MINE11, MINE12, MINE13, MINE14, MINE15, MINE16, MINE17, 
				MINE18, MINE19, MINE20, MINE21, MINE22, MINE23,
				aw1, aw2, aw3, aw4, aw5, cam1,
				aw1a, aw2a, aw3a, aw4a, aw5a, aw6a, aw7a, aw8a, aw9a,
				h_last;
		};
		Handle h_array[64];
	};

	// integers
	union {
		struct {
			int
				attacksent,
				i_last;
		};
		int i_array[1];
	};
};

void Misn05Mission::Setup(void)
{
	game_start = false;
	reconfactory = false;
	missionwon = false;
	lemnossecure = false;
	missionfail = false;
	neworders = false;
	basewave = false;
	sent1Done = false;
	sent2Done = false;
	sent3Done = false;
	sent4Done = false;
	shuffle = false;
	notfound = false;
	ob1 = false;
	ob2 = false;
	ob3 = false;
	ob4 = false;
	go = false;
	check1 = false;
	check2 = false;
	check3 = false;
	check4 = false;
	newobjective = false;
	possiblewin = false;
	mine1built = false;
	mine2built = false;
	mine3built = false;
	mine4built = false;
	mine5built = false;
	mine6built = false;
	mine7built = false;
	mine8built = false;
	mine9built = false;
	mine10built = false;
	mine11built = false;
	mine12built = false;
	mine13built = false;
	mine14built = false;
	mine15built = false;
	mine16built = false;
	mine17built = false;
	mine18built = false;
	mine19built = false;
	mine20built = false;
	mine21built = false;
	mine22built = false;
	mine23built = false;
	takeoutfactory = false;
	attacktimeset = false;
	aw1aattack = false;
	aw2aattack = false;
	aw3aattack = false;
	aw4aattack = false;
	aw5aattack = false;
	aw6aattack = false;
	aw7aattack = false;
	aw8aattack = false;
	aw9aattack = false;
	aw1sent = false;
	aw2sent = false;
	aw3sent = false;
	aw4sent = false;
	lemcin1 = false;
	lemcin2 = false;
	reconed = false;
	lemnos = 0; 
	player = 0; 
	svrec = 0; 
	avrec = 0; 
	wBu1 = 0; 
	wBu2 = 0; 
	wBu3 = 0;
	w1u1 = 0;
	w1u2 = 0;
	w1u3 = 0;
	w1u4 = 0;
	w2u1 = 0;	
	w2u2 = 0;	
	w2u3 = 0;	
	w2u4 = 0;	
	w3u1 = 0;
	w3u2 = 0;
	w3u3 = 0;
	w3u4 = 0;
	w4u1 = 0;
	w4u2 = 0;
	w4u3 = 0;
	w4u4 = 0;
	MINE1 = 0; 
	MINE2 = 0; 
	MINE3 = 0; 
	MINE4 = 0; 
	MINE5 = 0; 
	MINE6 = 0; 
	MINE7 = 0; 
	MINE8 = 0;
	MINE9 = 0;
	MINE10 = 0; 
	MINE11 = 0; 
	MINE12 = 0; 
	MINE13 = 0; 
	MINE14 = 0; 
	MINE15 = 0; 
	MINE16 = 0; 
	MINE17 = 0; 
	MINE18 = 0; 
	MINE19 = 0; 
	MINE20 = 0; 
	MINE21 = 0; 
	MINE22 = 0; 
	MINE23 = 0;
	aw1 = 0; 
	aw2 = 0; 
	aw3 = 0; 
	aw4 = 0; 
	aw5 = 0;
	aw1a = 0; 
	aw2a = 0; 
	aw3a = 0; 
	aw4a = 0; 
	aw5a = 0; 
	aw6a = 0; 
	aw7a = 0; 
	aw8a = 0; 
	aw9a = 0;
	rand1 = 0;
	rand2 = 0;
	rand3 = 0;
	start = 99999999999999.0f;
	needtospawn = true;
	randomwave = 99999999.0f;
	readtime = 99999999999.0f;
	aw1 = 0;
	aw2 = 0;
	aw3 = 0;
	aw4 = 0;
	aw5 = 0;
	aw1t = 99999999999.0f;
	aw2t = 99999999999.0f;
	aw3t = 99999999999.0f;
	aw4t = 99999999999.0f;
	platoonhere = 99999999999999.0f;
	sendTime[0] = 99999999.0f;
	sendTime[1] = 99999999.0f;
	sendTime[2] = 99999999.0f;
	sendTime[3] = 99999999.0f;
	lemcinstart = 99999999.0f;
	lemcinend = 999999999.0f;
	
	

	/*
	Here's where you
	set the values
	at the start.  
	*/
}

static void NoEscorts(void);

#if 0 && defined(_DEBUG)
static void CheckPriority(Handle h)
{
	GameObject *o = GameObjectHandle::GetObj(h);
	if (o == NULL)
		return;
	if (
		(o->curCmd.priority != 0) ||
		(o->nextCmd.priority != 0)
		)
		return;
	Trace("object with bad priority\n");
}
#else
#define CheckPriority(h)
#endif

void Misn05Mission::Execute(void)
{
	int i;

	/*
		Here is where you 
		put what happens 
		every frame.  
	*/
	if (!game_start)
	{
		SetScrap(1,20);
		SetScrap(2,20);
		lemnos = GetHandle ("oblema110_i76building");
		svrec = GetHandle ("svrecy-1_recycler");
		avrec = GetHandle ("avrecy-1_recycler");
		SetAIP("misn05.aip");
		AudioMessage ("misn0501.wav");
		game_start=true;
		mine1 = GetTime() + 2.0f;
		mine2 = GetTime() + 2.0f;
		mine3 = GetTime() + 2.0f;
		mine4 = GetTime() + 2.0f;
		mine5 = GetTime() + 2.0f;
		mine6 = GetTime() + 2.0f;
		mine7 = GetTime() + 2.0f;
		mine8 = GetTime() + 2.0f;
		mine9 = GetTime() + 2.0f;
		mine10 = GetTime() + 2.0f;
		mine11 = GetTime() + 2.0f;
		mine12 = GetTime() + 2.0f;
		mine13 = GetTime() + 2.0f;
		mine14 = GetTime() + 2.0f;
		mine15 = GetTime() + 2.0f;
		mine17 = GetTime() + 2.0f;
		mine18 = GetTime() + 2.0f;
		mine19 = GetTime() + 2.0f;
		mine20 = GetTime() + 2.0f;
		mine21 = GetTime() + 2.0f;
		mine22 = GetTime() + 2.0f;
		mine23 = GetTime() + 2.0f;
		randomwave = GetTime() + 1.0f;
		cam1 = GetHandle("cam1");
		GameObjectHandle :: GetObj(cam1) ->SetName ("Volcano");
		newobjective = true;
	}
	player = GetPlayerHandle();
	NoEscorts();

	if
		(newobjective == true)
	{
		ClearObjectives();
		if
			(missionwon == true)
		{
			AddObjective("misn0502.otf", GREEN);
		}
		if
			(
			(neworders == true) && (missionwon == false)
			)
		{
			AddObjective("misn0502.otf", WHITE);
		}
		if
			(neworders == true)
		{
			AddObjective("misn0503.otf", GREEN);
		}
		if
			(
			(reconfactory == true) && (neworders == false)
			)
		{
			AddObjective("misn0503.otf", WHITE);
		}

		if
			(reconfactory == true)
		{
			AddObjective("misn0501.otf", GREEN);
		}
		if
			(reconfactory == false)
		{
			AddObjective("misn0501.otf", WHITE);
		}
		newobjective = false;
	}
			

	if
		(reconed == false)
	{
	if
		(needtospawn == true)
	{
		if
			(
			(randomwave < GetTime()) && (IsAlive(svrec))
			)
		{
			rand1 = BuildObject("svfigh",2,svrec);
			rand2 = BuildObject("svfigh",2,svrec);
			//rand3 = BuildObject("svfigh",2,svrec);
			Attack (rand1, avrec);
			Attack (rand2, avrec);
			//Attack (rand3, avrec);
			SetIndependence(rand1, 1);
			SetIndependence(rand2, 1);
			//SetIndependence(rand3, 1);
			needtospawn = false;
		}
	}

	if
		(needtospawn == false)
	{
		if
			(
			(!IsAlive(rand1)) &&
			(!IsAlive(rand2)) //&&
			//(!IsAlive(rand3)) 
			)
		{
			needtospawn = true;
		}
	}
	}

	if (mine1built)
	{
		Handle meat = GetNearestVehicle ("path_1" ,1);
		if (GetDistance(meat, "path_1") > 400.0f)
		{
			mine1 = GetTime() + 3.0f;
			mine1built = false;
			RemoveObject (MINE1);
		}
	}
	else
	{
		if (mine1 < GetTime()) {
			Handle meat = GetNearestVehicle ("path_1" ,1);
			if (GetDistance(meat, "path_1") < 400.0f)
			{
				MINE1 = BuildObject ("boltmine", 3, "path_1");
				mine1built = true;
			}
		}
	}
	if (mine2built)
	{
		Handle meat = GetNearestVehicle ("path_2" ,1);
		if (GetDistance(meat, "path_2") > 400.0f)
		{
			mine2 = GetTime() + 3.0f;
			mine2built = false;
			RemoveObject (MINE2);
		}
	}
	else
	{
		if (mine2 < GetTime()) {
			Handle meat = GetNearestVehicle ("path_2" ,1);
			if (GetDistance(meat, "path_2") < 400.0f)
			{
				MINE2 = BuildObject ("boltmine", 3, "path_2");
				mine2built = true;
			}
		}
	}
	if (mine3built)
	{
		Handle meat = GetNearestVehicle ("path_3" ,1);
		if (GetDistance(meat, "path_3") > 400.0f)
		{
			mine3 = GetTime() + 3.0f;
			mine3built = false;
			RemoveObject (MINE3);
		}
	}
	else
	{
		if (mine3 < GetTime()) {
			Handle meat = GetNearestVehicle ("path_3" ,1);
			if (GetDistance(meat, "path_3") < 400.0f)
			{
				MINE3 = BuildObject ("boltmine", 3, "path_3");
				mine3built = true;
			}
		}
	}

	if (mine4built)
	{
		Handle meat = GetNearestVehicle ("path_4" ,1);
		if (GetDistance(meat, "path_4") > 400.0f)
		{
			mine4 = GetTime() + 3.0f;
			mine4built = false;
			RemoveObject (MINE4);
		}
	}
	else
	{
		if (mine4 < GetTime()) {
			Handle meat = GetNearestVehicle ("path_4" ,1);
			if (GetDistance(meat, "path_4") < 400.0f)
			{
				MINE4 = BuildObject ("boltmine", 3, "path_4");
				mine4built = true;
			}
		}
	}
	if (mine5built)
	{
		Handle meat = GetNearestVehicle ("path_5" ,1);
		if (GetDistance(meat, "path_5") > 400.0f)
		{
			mine5 = GetTime() + 3.0f;
			mine5built = false;
			RemoveObject (MINE5);
		}
	}
	else
	{
		if (mine5 < GetTime()) {
			Handle meat = GetNearestVehicle ("path_5" ,1);
			if (GetDistance(meat, "path_5") < 400.0f)
			{
				MINE5 = BuildObject ("boltmine", 3, "path_5");
				mine5built = true;
			}
		}
	}

	if (mine6built)
	{
		Handle meat = GetNearestVehicle ("path_6" ,1);
		if (GetDistance(meat, "path_6") > 400.0f)
		{
			mine6 = GetTime() + 3.0f;
			mine6built = false;
			RemoveObject (MINE6);
		}
	}
	else
	{
		if (mine6 < GetTime()) {
			Handle meat = GetNearestVehicle ("path_6" ,1);
			if (GetDistance(meat, "path_6") < 400.0f)
			{
				MINE6 = BuildObject ("boltmine", 3, "path_6");
				mine6built = true;
			}
		}
	}

	if (mine7built)
	{
		Handle meat = GetNearestVehicle ("path_7" ,1);
		if (GetDistance(meat, "path_7") > 400.0f)
		{
			mine7 = GetTime() + 3.0f;
			mine7built = false;
			RemoveObject (MINE7);
		}
	}
	else
	{
		if (mine7 < GetTime()) {
			Handle meat = GetNearestVehicle ("path_7" ,1);
			if (GetDistance(meat, "path_7") < 400.0f)
			{
				MINE7 = BuildObject ("boltmine", 3, "path_7");
				mine7built = true;
			}
		}
	}

	if (mine8built)
	{
		Handle meat = GetNearestVehicle ("path_8" ,1);
		if (GetDistance(meat, "path_8") > 400.0f)
		{
			mine8 = GetTime() + 3.0f;
			mine8built = false;
			RemoveObject (MINE8);
		}
	}
	else
	{
		if (mine8 < GetTime()) {
			Handle meat = GetNearestVehicle ("path_8" ,1);
			if (GetDistance(meat, "path_8") < 400.0f)
			{
				MINE8 = BuildObject ("boltmine", 3, "path_8");
				mine8built = true;
			}
		}
	}

	if (mine9built)
	{
		Handle meat = GetNearestVehicle ("path_9" ,1);
		if (GetDistance(meat, "path_9") > 400.0f)
		{
			mine9 = GetTime() + 3.0f;
			mine9built = false;
			RemoveObject (MINE9);
		}
	}
	else
	{
		if (mine9 < GetTime()) {
			Handle meat = GetNearestVehicle ("path_9" ,1);
			if (GetDistance(meat, "path_9") < 400.0f)
			{
				MINE9 = BuildObject ("boltmine", 3, "path_9");
				mine9built = true;
			}
		}
	}

	if (mine10built)
	{
		Handle meat = GetNearestVehicle ("path_10" ,1);
		if (GetDistance(meat, "path_10") > 400.0f)
		{
			mine10 = GetTime() + 3.0f;
			mine10built = false;
			RemoveObject (MINE10);
		}
	}
	else
	{
		if (mine10 < GetTime()) {
			Handle meat = GetNearestVehicle ("path_10" ,1);
			if (GetDistance(meat, "path_10") < 400.0f)
			{
				MINE10 = BuildObject ("boltmine", 3, "path_10");
				mine10built = true;
			}
		}
	}

	if (mine11built)
	{
		Handle meat = GetNearestVehicle ("path_11" ,1);
		if (GetDistance(meat, "path_11") > 400.0f)
		{
			mine11 = GetTime() + 3.0f;
			mine11built = false;
			RemoveObject (MINE11);
		}
	}
	else
	{
		if (mine11 < GetTime()) {
			Handle meat = GetNearestVehicle ("path_11" ,1);
			if (GetDistance(meat, "path_11") < 400.0f)
			{
				MINE11 = BuildObject ("boltmine", 3, "path_11");
				mine11built = true;
			}
		}
	}

	if (mine12built)
	{
		Handle meat = GetNearestVehicle ("path_12" ,1);
		if (GetDistance(meat, "path_12") > 400.0f)
		{
			mine12 = GetTime() + 3.0f;
			mine12built = false;
			RemoveObject (MINE12);
		}
	}
	else
	{
		if (mine12 < GetTime()) {
			Handle meat = GetNearestVehicle ("path_12" ,1);
			if (GetDistance(meat, "path_12") < 400.0f)
			{
				MINE12 = BuildObject ("boltmine", 3, "path_12");
				mine12built = true;
			}
		}
	}

	if (mine13built)
	{
		Handle meat = GetNearestVehicle ("path_13" ,1);
		if (GetDistance(meat, "path_13") > 400.0f)
		{
			mine13 = GetTime() + 3.0f;
			mine13built = false;
			RemoveObject (MINE13);
		}
	}
	else
	{
		if (mine13 < GetTime()) {
			Handle meat = GetNearestVehicle ("path_13" ,1);
			if (GetDistance(meat, "path_13") < 400.0f)
			{
				MINE13 = BuildObject ("boltmine", 3, "path_13");
				mine13built = true;
			}
		}
	}

	if (mine14built)
	{
		Handle meat = GetNearestVehicle ("path_14" ,1);
		if (GetDistance(meat, "path_14") > 400.0f)
		{
			mine14 = GetTime() + 3.0f;
			mine14built = false;
			RemoveObject (MINE14);
		}
	}
	else
	{
		if (mine14 < GetTime()) {
			Handle meat = GetNearestVehicle ("path_14" ,1);
			if (GetDistance(meat, "path_14") < 400.0f)
			{
				MINE14 = BuildObject ("boltmine", 3, "path_14");
				mine14built = true;
			}
		}
	}

	if (mine15built)
	{
		Handle meat = GetNearestVehicle ("path_15" ,1);
		if (GetDistance(meat, "path_15") > 400.0f)
		{
			mine15 = GetTime() + 3.0f;
			mine15built = false;
			RemoveObject (MINE15);
		}
	}
	else
	{
		if (mine15 < GetTime()) {
			Handle meat = GetNearestVehicle ("path_15" ,1);
			if (GetDistance(meat, "path_15") < 400.0f)
			{
				MINE15 = BuildObject ("boltmine", 3, "path_15");
				mine15built = true;
			}
		}
	}

	if (mine16built)
	{
		Handle meat = GetNearestVehicle ("path_16" ,1);
		if (GetDistance(meat, "path_16") > 400.0f)
		{
			mine16 = GetTime() + 3.0f;
			mine16built = false;
			RemoveObject (MINE16);
		}
	}
	else
	{
		if (mine16 < GetTime()) {
			Handle meat = GetNearestVehicle ("path_16" ,1);
			if (GetDistance(meat, "path_16") < 400.0f)
			{
				MINE16 = BuildObject ("boltmine", 3, "path_16");
				mine16built = true;
			}
		}
	}

	if (mine17built)
	{
		Handle meat = GetNearestVehicle ("path_17" ,1);
		if (GetDistance(meat, "path_17") > 400.0f)
		{
			mine17 = GetTime() + 3.0f;
			mine17built = false;
			RemoveObject (MINE17);
		}
	}
	else
	{
		if (mine17 < GetTime()) {
			Handle meat = GetNearestVehicle ("path_17" ,1);
			if (GetDistance(meat, "path_17") < 400.0f)
			{
				MINE17 = BuildObject ("boltmine", 3, "path_17");
				mine17built = true;
			}
		}
	}

	if (mine18built)
	{
		Handle meat = GetNearestVehicle ("path_18" ,1);
		if (GetDistance(meat, "path_18") > 400.0f)
		{
			mine18 = GetTime() + 3.0f;
			mine18built = false;
			RemoveObject (MINE18);
		}
	}
	else
	{
		if (mine18 < GetTime()) {
			Handle meat = GetNearestVehicle ("path_18" ,1);
			if (GetDistance(meat, "path_18") < 400.0f)
			{
				MINE18 = BuildObject ("boltmine", 3, "path_18");
				mine18built = true;
			}
		}
	}

	if (mine19built)
	{
		Handle meat = GetNearestVehicle ("path_19" ,1);
		if (GetDistance(meat, "path_19") > 400.0f)
		{
			mine19 = GetTime() + 3.0f;
			mine19built = false;
			RemoveObject (MINE19);
		}
	}
	else
	{
		if (mine19 < GetTime()) {
			Handle meat = GetNearestVehicle ("path_19" ,1);
			if (GetDistance(meat, "path_19") < 400.0f)
			{
				MINE19 = BuildObject ("boltmine", 3, "path_19");
				mine19built = true;
			}
		}
	}

	if (mine20built)
	{
		Handle meat = GetNearestVehicle ("path_20" ,1);
		if (GetDistance(meat, "path_20") > 400.0f)
		{
			mine20 = GetTime() + 3.0f;
			mine20built = false;
			RemoveObject (MINE20);
		}
	}
	else
	{
		if (mine20 < GetTime()) {
			Handle meat = GetNearestVehicle ("path_20" ,1);
			if (GetDistance(meat, "path_20") < 400.0f)
			{
				MINE20 = BuildObject ("boltmine", 3, "path_20");
				mine20built = true;
			}
		}
	}

		if (mine21built)
	{
		Handle meat = GetNearestVehicle ("path_21" ,1);
		if (GetDistance(meat, "path_21") > 400.0f)
		{
			mine21 = GetTime() + 3.0f;
			mine21built = false;
			RemoveObject (MINE21);
		}
	}
	else
	{
		if (mine21 < GetTime()) {
			Handle meat = GetNearestVehicle ("path_21" ,1);
			if (GetDistance(meat, "path_21") < 400.0f)
			{
				MINE21 = BuildObject ("boltmine", 3, "path_21");
				mine21built = true;
			}
		}
	}

		if (mine22built)
	{
		Handle meat = GetNearestVehicle ("path_22" ,1);
		if (GetDistance(meat, "path_22") > 400.0f)
		{
			mine22 = GetTime() + 3.0f;
			mine22built = false;
			RemoveObject (MINE22);
		}
	}
	else
	{
		if (mine22 < GetTime()) {
			Handle meat = GetNearestVehicle ("path_22" ,1);
			if (GetDistance(meat, "path_22") < 400.0f)
			{
				MINE22 = BuildObject ("boltmine", 3, "path_22");
				mine22built = true;
			}
		}
	}

		if (mine23built)
	{
		Handle meat = GetNearestVehicle ("path_23" ,1);
		if (GetDistance(meat, "path_23") > 400.0f)
		{
			mine23 = GetTime() + 3.0f;
			mine23built = false;
			RemoveObject (MINE23);
		}
	}
	else
	{
		if (mine23 < GetTime()) {
			Handle meat = GetNearestVehicle ("path_23" ,1);
			if (GetDistance(meat, "path_23") < 400.0f)
			{
				MINE23 = BuildObject ("boltmine", 3, "path_23");
				mine23built = true;
			}
		}
	}

	

	if 
		(
		(notfound == true) && (shuffle == false)
		)
	{
		sendTime [0] = GetTime() + 10.0f;
		sendTime [1] = GetTime() + 90.0f;
		sendTime [2] = GetTime() + 130.0f;
		sendTime [3] = GetTime() + 190.0f;
		for (i=0; i < 10; i++)
		{
			int j = rand() % 4;
			int k = rand() % 4;
			float temp = sendTime[j];
			sendTime[j] = sendTime[k];
			sendTime[k] = temp;
		}
		for (i = 0; i < 4; i++)
		{
			printf("%f\n", sendTime[i]);
		}
		shuffle = true;
	}

	if
		(
		(sendTime[0] < GetTime()) && (sent1Done == false)
		)
	{
		w1u1 = BuildObject ("svfigh",2,svrec);
		w1u2 = BuildObject ("svfigh",2,svrec);
		w1u3 = BuildObject ("svturr",2,svrec);
		w1u4 = BuildObject ("svturr",2,svrec);
		sent1Done = true;
		Follow (w1u1, w1u3);
		Follow (w1u2, w1u4);
		SetIndependence(w1u1, 1);
		SetIndependence(w1u2, 1);
		Goto (w1u3, "defendrim2");
		Goto (w1u4, "defendrim1");
		check1 = true;
		check2 = true;
		check3 = true;
		check4 = true;
	}

	if (
		IsAlive(w1u3) &&
		(check1 == false) &&
		(GetCurrentCommand(w1u3) == CMD_NONE)
		)
	{
		Defend(w1u3, 1000);
	}
	
	if (
			(check1 == true) &&
			(
				!IsAlive(w1u3) ||
				(GetDistance(w1u3, "defendrim2") < 20.0f)
			)
		)
	{
		if (IsAlive(w1u3))
			Stop(w1u3, 1000);
		Patrol(w1u1, "attackpatrol1", 2);
		check1 = false;
	}

	if (
		IsAlive(w1u4) &&
		(check2 == false) &&
		(GetCurrentCommand(w1u4) == CMD_NONE)
		)
	{
		Defend(w1u4, 1000);
	}

	if (
			(check2 == true) &&
			(
				!IsAlive(w1u4) ||
				(GetDistance(w1u4, "defendrim1") < 20.0f)
			)
		)
	{
		if (IsAlive(w1u4))
			Stop(w1u4, 1000);
		Patrol(w1u2, "attackpatrol1", 2);
		check2 = false;
	}

	if (
		IsAlive(w2u3) &&
		(check3 == false) &&
		(GetCurrentCommand(w2u3) == CMD_NONE)
		)
	{
		Defend(w2u3, 1000);
	}

	if (
			(check3 == true) &&
			(
				!IsAlive(w2u3) ||
				(GetDistance(w2u3, "defendrim3") < 20.0f)
			)
		)
	{
		if (IsAlive(w2u3))
			Stop(w2u3, 1000);
		Patrol(w2u1, "attackpatrol1", 2);
		check3 = false;
	}

	if (
		IsAlive(w2u4) &&
		(check4 == false) &&
		(GetCurrentCommand(w2u4) == CMD_NONE)
		)
	{
		Defend(w2u4, 1000);
	}

	if (
			(check4 == true) &&
			(
				!IsAlive(w2u4) ||
				(GetDistance(w2u4, "defendrim4") < 20.0f)
			)
		)
	{
		if (IsAlive(w2u4))
			Stop(w2u4, 1000);
		Patrol(w2u2, "attackpatrol1", 2);
		check4 = false;
	}

	if
		(
		(sendTime[1] < GetTime()) && (sent2Done == false)
		)
	{
		w2u1 = BuildObject ("svtank",2,svrec);
		w2u2 = BuildObject ("svtank",2,svrec);
		w2u3 = BuildObject ("svturr",2,svrec);
		w2u4 = BuildObject ("svturr",2,svrec);
		sent2Done = true;
		Follow (w2u1, w2u3);
		Follow (w2u2, w2u4);
		SetIndependence(w2u1, 1);
		SetIndependence(w2u2, 1);
		Goto (w2u3, "defendrim3");
		Goto (w2u4, "defendrim4");
	}
	if
		(
		(sendTime[2] < GetTime()) && (sent3Done == false)
		)
	{
		//w3u1 = BuildObject ("svfigh",2,svrec);
		//w3u2 = BuildObject ("svfigh",2,svrec);
		w3u3 = BuildObject ("svfigh",2,svrec);
		w3u4 = BuildObject ("svfigh",2,svrec);
		sent3Done = true;
		//Patrol (w3u1, "attackpatrol1",1);
		//Patrol (w3u2, "attackpatrol1",1);
		Patrol (w3u3, "attackpatrol1",2);
		Patrol (w3u4, "attackpatrol1",2);
	}

	if
		(
		(sendTime[3] < GetTime()) && (sent4Done == false)
		)
	{
		//w4u1 = BuildObject ("svfigh",2,svrec);
		//w4u2 = BuildObject ("svfigh",2,svrec);
		w4u3 = BuildObject ("svfigh",2,svrec);
		w4u4 = BuildObject ("svfigh",2,svrec);
		sent4Done = true;
		//Patrol (w4u1, "attackpatrol1",1);
		//Patrol (w4u2, "attackpatrol1",1);
		Patrol (w4u3, "attackpatrol1",2);
		Patrol (w4u4, "attackpatrol1",2);
	}

	if
		(
		(reconfactory == false) && (GetDistance (player, lemnos) < 600.0f)
		&& (notfound == false)
		)
	{
		AudioMessage ("misn0502.wav");
		notfound = true;
	}

	if
		(
		(reconfactory == false) && (GetDistance (player, lemnos) < 230.0f) 
		)
	{
		AudioMessage ("misn0503.wav");
		AudioMessage ("misn0504.wav");
		reconfactory = true;
		newobjective = true;
		start = GetTime() + 90.0f;
		//lemcinstart = GetTime() - 1.0f;
		//lemcinend = GetTime() + 3.0f;
	}

	/*if
		(
		(lemcin1 == false) && (lemcinstart < GetTime())
		)
	{
		CameraReady();
		lemcin1 = true;
	}

	if
		(
		(lemcin2 == false) && (lemcinend > GetTime())
		)
	{
		CameraObject(player, 0, 5000, - 5000, lemnos);
	}

	if
		(
		(lemcin2 == false) && (lemcinend < GetTime())
		)
	{
		CameraFinish();
		lemcin2 = true;
	}*/
	

	


	if 
		(
		(reconfactory == true) &&
		(reconed == false) &&
		(
		(IsInfo("oblema")) ||
		(start < GetTime())
		)
		)

	{
		//AudioMessage ("misn0515.wav");
		readtime = GetTime() + 5.0f;
		reconed = true;
	}
	if
		(
		(neworders == false) && (readtime < GetTime()) 
		)
	{
		neworders = true;
		AudioMessage ("misn0506.wav");
		newobjective = true;
	}
	if
		(
		(IsAlive(svrec)) && (basewave == false) &&
		(reconfactory == true)
		)
	{
		wBu1 = BuildObject ("svtank",2,svrec);
		wBu2 = BuildObject ("svfigh",2,svrec);
		wBu3 = BuildObject ("svfigh",2,svrec);
		Attack (wBu1, avrec);
		Attack (wBu2, avrec);
		Attack (wBu3, avrec);
		SetIndependence(wBu1, 1);
		SetIndependence(wBu2, 1);
		SetIndependence(wBu3, 1);
		basewave = true;
	}

	// make sure dead things stay 
	if (sent1Done)
	{
		IsAlive(w1u1);
		IsAlive(w1u2);
		IsAlive(w1u3);
		IsAlive(w1u4);
	}
	if (sent2Done)
	{
		IsAlive(w2u1);
		IsAlive(w2u2);
		IsAlive(w2u3);
		IsAlive(w2u4);
	}
	if (sent3Done)
	{
		IsAlive(w3u1);
		IsAlive(w3u2);
		IsAlive(w3u3);
		IsAlive(w3u4);
	}
	if (sent4Done)
	{
		IsAlive(w4u1);
		IsAlive(w4u2);
		IsAlive(w4u3);
		IsAlive(w4u4);
	}

	if
		(
		(sent1Done == true) &&
		(sent2Done == true) &&
		(sent3Done == true) &&
		(sent4Done == true) &&
		(!IsAlive (w1u1)) &&
		(!IsAlive (w1u2)) &&
		(!IsAlive (w1u3)) &&
		(!IsAlive (w1u4)) &&
		(!IsAlive (w2u1)) &&
		(!IsAlive (w2u2)) &&
		(!IsAlive (w2u3)) &&
		(!IsAlive (w2u4)) &&
		(!IsAlive (w3u1)) &&
		(!IsAlive (w3u2)) &&
		(!IsAlive (w3u3)) &&
		(!IsAlive (w3u4)) &&
		(!IsAlive (w4u1)) &&
		(!IsAlive (w4u2)) &&
		(!IsAlive (w4u3)) &&
		(!IsAlive (w4u4)) && 
		(attacktimeset == false)
		)
	{
		AudioMessage ("misn0507.wav");
		platoonhere = GetTime()+45.0f;//600.0f
		attacktimeset = true;
		go = true;
	}

	if 
		(
		(!IsAlive(aw1)) &&
		(!IsAlive(aw2)) &&
		(!IsAlive(aw3)) &&
		(!IsAlive(aw4)) &&
		(!IsAlive(aw5)) &&
		(platoonhere > GetTime()) &&
		(go == true) && (IsAlive(svrec))
		)
	{
		AudioMessage("misn0508.wav");
		AudioMessage("misn0509.wav");
		attacksent = rand() %4;
		attackstatement = false;
		switch (attacksent)
		{
		case 0:
		aw1 = BuildObject ("svhraz", 2, svrec);
		aw2 = BuildObject ("svhraz", 2, svrec);
		aw3 = BuildObject ("svhraz", 2, svrec);
		//aw4 = BuildObject ("svhraz", 2, svrec);
		//aw5 = BuildObject ("svhraz", 2, svrec);
		Goto (aw1, "destroy1");
		Goto (aw2, "destroy1");
		Goto (aw3, "destroy1");
		//Goto (aw4, "destroy1");
		//Goto (aw5, "destroy1");
		break;
		case 1:
		aw1 = BuildObject ("svhraz", 2, svrec);
		aw2 = BuildObject ("svhraz", 2, svrec);
		aw3 = BuildObject ("svhraz", 2, svrec);
		//aw4 = BuildObject ("svhraz", 2, svrec);
		//aw5 = BuildObject ("svhraz", 2, svrec);
		Goto (aw1, "destroy2");
		Goto (aw2, "destroy2");
		Goto (aw3, "destroy2");
		//Goto (aw4, "destroy2");
		//Goto (aw5, "destroy2");
		break;
		case 2:
		aw1 = BuildObject ("svhraz", 2, svrec);
		aw2 = BuildObject ("svhraz", 2, svrec);
		aw3 = BuildObject ("svhraz", 2, svrec);
		//aw4 = BuildObject ("svhraz", 2, svrec);
		//aw5 = BuildObject ("svhraz", 2, svrec);
		Goto (aw1, "destroy3");
		Goto (aw2, "destroy3");
		Goto (aw3, "destroy3");
		//Goto (aw4, "destroy3");
		//Goto (aw5, "destroy3");
		break;
		case 3:
		aw1 = BuildObject ("svhraz", 2, svrec);
		aw2 = BuildObject ("svhraz", 2, svrec);
		aw3 = BuildObject ("svhraz", 2, svrec);
		//aw4 = BuildObject ("svhraz", 2, svrec);
		//aw5 = BuildObject ("svhraz", 2, svrec);
		Goto (aw1, "destroy4");
		Goto (aw2, "destroy4");
		Goto (aw3, "destroy4");
		//Goto (aw4, "destroy4");
		//Goto (aw5, "destroy4");
		break;
		}
		bombtime = GetTime () + 10.0f;
		attackcmd = false;
		aw1t = GetTime() + 10.0f;
		aw2t = GetTime() + 50.0f;
		aw3t = GetTime() + 100.0f;
		aw4t = GetTime() + 140.0f;
	}
	if
		(
		(attackcmd == false) && (bombtime < GetTime())
		)
	{
		if
			(
			(GetDistance(aw1, "dest1") < 30.0f) ||
			(GetDistance(aw1, "dest2") < 30.0f)
			)
		{
			Attack(aw1, lemnos);
			SetIndependence(aw1, 1);
			attackcmd = true;
		}
		if
			(
			(GetDistance(aw2, "dest1") < 30.0f) ||
			(GetDistance(aw2, "dest2") < 30.0f)
			)
		{
			Attack(aw2, lemnos);
			SetIndependence(aw2, 1);
			attackcmd = true;
		}
		if
			(
			(GetDistance(aw3, "dest1") < 30.0f) ||
			(GetDistance(aw3, "dest2") < 30.0f)
			)
		{
			Attack(aw3, lemnos);
			SetIndependence(aw3, 1);
			attackcmd = true;
		}
		if
			(
			(GetDistance(aw4, "dest1") < 30.0f) ||
			(GetDistance(aw4, "dest2") < 30.0f)
			)
		{
			Attack(aw4, lemnos);
			SetIndependence(aw4, 1);
			attackcmd = true;
		}
		if
			(
			(GetDistance(aw5, "dest1") < 30.0f) ||
			(GetDistance(aw5, "dest2") < 30.0f)
			)
		{
			Attack(aw5, lemnos);
			SetIndependence(aw5, 1);
			attackcmd = true;
		}
		bombtime = GetTime() + 3.0f;
	}
		

		/*if
			(
			(platoonhere < GetTime()) && 
			(!IsAlive(aw1)) &&
			(!IsAlive(aw2)) &&
			(!IsAlive(aw3)) &&
			(!IsAlive(aw4)) &&
			(!IsAlive(aw5)) &&
			(missionwon == false)
			)
		{
			missionwon = true;
			AudioMessage ("misn0511.wav");
			AudioMessage ("misn0512.wav");
			SucceedMission (GetTime() + 15.0f);
		}*/

		if 
			(
			(!IsAlive(avrec)) && (missionfail == false)
			)
		{
			FailMission (GetTime()+15.0f, "misn05l1.des");
			AudioMessage ("misn0513.wav");
			missionfail = true;
		}

		if 
			(
			(!IsAlive(lemnos)) && (missionfail == false)
			)
		{
			FailMission (GetTime()+15.0f, "misn05l2.des");
			AudioMessage ("misn0514.wav");
			missionfail = true;
		}

		if
			(
			(
			(GetDistance(aw1, lemnos) < 500.0f) ||
			(GetDistance(aw2, lemnos) < 500.0f) ||
			(GetDistance(aw3, lemnos) < 500.0f) ||
			(GetDistance(aw4, lemnos) < 500.0f) ||
			(GetDistance(aw5, lemnos) < 500.0f) 
			)
			&& (attackstatement == false)
			)
		{
			AudioMessage ("misn0510.wav");
			attackstatement = true;
		}
	



	if 
		(
		(aw1t < GetTime()) && 
		(aw1sent == false) && 
		(IsAlive(svrec))
		)
	{
		//aw1a = BuildObject ("svfigh", 2, svrec);
		aw2a = BuildObject ("svfigh", 2, svrec);
		//Goto (aw1a, lemnos);
		Attack (aw2a, lemnos);
		SetIndependence(aw2a, 1);
		aw1sent = true;
	}

	if 
		(
		(aw2t < GetTime()) && 
		(aw2sent == false) && 
		(IsAlive(svrec))
		)
	{
		//aw3a = BuildObject ("svtank", 2, svrec);
		aw4a = BuildObject ("svtank", 2, svrec);
		//Goto (aw3a, lemnos);
		Attack (aw4a, lemnos);
		SetIndependence(aw4a, 1);
		aw2sent = true;
	}

	if 
		(
		(aw3t < GetTime()) && 
		(aw3sent == false) &&
		(IsAlive(svrec))
		)
	{
		aw5a = BuildObject ("svfigh", 2, svrec);
		aw6a = BuildObject ("svfigh", 2, svrec);
		//aw7a = BuildObject ("svfigh", 2, svrec);
		Attack (aw5a, lemnos);
		Attack (aw6a, lemnos);
		SetIndependence(aw5a, 1);
		SetIndependence(aw6a, 1);
		//Goto (aw7a, lemnos);
		aw3sent = true;
	}

	if 
		(
		(aw4t < GetTime()) && 
		(aw4sent == false) &&
		(IsAlive(svrec))
		)
	{
		aw8a = BuildObject ("svfigh", 2, svrec);
		aw9a = BuildObject ("svtank", 2, svrec);
		Attack (aw8a, lemnos);
		Attack (aw9a, lemnos);
		SetIndependence(aw8a, 1);
		SetIndependence(aw9a, 1);
		aw4sent = true;
	}

	if
		(
		(aw1sent == true) &&
		(IsAlive(aw1a)) && (aw1aattack == false)
		)
	{
		if
			(GetDistance(aw1a, lemnos) < 300.0f)
		{
			Attack(aw1a, lemnos);
			SetIndependence(aw1a, 1);
			aw1aattack = true;
		}
	}
	if
		(
		(aw1sent == true) &&
		(IsAlive(aw2a)) && (aw2aattack == false)
		)
	{
		if
			(GetDistance(aw2a, lemnos) < 300.0f)
		{
			Attack(aw2a, lemnos);
			SetIndependence(aw2a, 1);
			aw2aattack = true;
		}
	}
	if
		(
		(aw1sent == true) &&
		(IsAlive(aw3a)) && (aw3aattack == false)
		)
	{
		if
			(GetDistance(aw3a, lemnos) < 300.0f)
		{
			Attack(aw3a, lemnos);
			SetIndependence(aw3a, 1);
			aw3aattack = true;
		}
	}
	if
		(
		(aw1sent == true) &&
		(IsAlive(aw4a)) && (aw4aattack == false)
		)
	{
		if
			(GetDistance(aw4a, lemnos) < 300.0f)
		{
			Attack(aw4a, lemnos);
			SetIndependence(aw4a, 1);
			aw4aattack = true;
		}
	}
	if
		(
		(aw1sent == true) &&
		(IsAlive(aw9a)) && (aw9aattack == false)
		)
	{
		if
			(GetDistance(aw9a, lemnos) < 300.0f)
		{
			Attack(aw9a, lemnos);
			SetIndependence(aw9a, 1);
			aw9aattack = true;
		}
	}
	if
		(
		(!IsAlive(svrec)) && (possiblewin == false)
		)
	{
		possiblewin = true;
		AudioMessage("misn0516.wav");
		aw1aattack = true;
		aw2aattack = true;
		aw3aattack = true;
		aw4aattack = true;
		aw5aattack = true;
		aw6aattack = true;
		aw7aattack = true;
		aw8aattack = true;
		aw9aattack = true;
		sent1Done = true;
		sent2Done = true;
		sent3Done = true;
		sent4Done = true;

		if
			(
			(IsAlive(aw1)) ||
			(IsAlive(aw2)) ||
			(IsAlive(aw3)) ||
			(IsAlive(aw4)) ||
			(IsAlive(aw5)) ||
			(IsAlive(aw1a)) ||
			(IsAlive(aw2a)) ||
			(IsAlive(aw3a)) ||
			(IsAlive(aw4a)) ||
			(IsAlive(aw5a)) ||
			(IsAlive(aw6a)) ||
			(IsAlive(aw7a)) ||
			(IsAlive(aw8a)) ||
			(IsAlive(aw9a)) 
			)
		{
			AudioMessage("misn0517.wav");
		}
	}


//
	CheckPriority(aw1);
	CheckPriority(aw2);
	CheckPriority(aw3);
	CheckPriority(aw4);
	CheckPriority(aw5);
	CheckPriority(aw1a);
	CheckPriority(aw2a);
	CheckPriority(aw3a);
	CheckPriority(aw4a);
	CheckPriority(aw5a);
	CheckPriority(aw6a);
	CheckPriority(aw7a);
	CheckPriority(aw8a);
	CheckPriority(aw9a);
	CheckPriority(w1u1);
	CheckPriority(w1u2);
	CheckPriority(w1u3);
	CheckPriority(w1u4);
	CheckPriority(w2u1);
	CheckPriority(w2u2);
	CheckPriority(w2u3);
	CheckPriority(w2u4);
	CheckPriority(w3u1);
	CheckPriority(w3u2);
	CheckPriority(w3u3);
	CheckPriority(w3u4);
	CheckPriority(w4u1);
	CheckPriority(w4u2);
	CheckPriority(w4u3);
	CheckPriority(w4u4);
//

	if
		(
		(aw1sent == true) &&
		(aw2sent == true) &&
		(aw3sent == true) &&
		(aw4sent == true) &&
		(sent1Done == true) &&
		(sent2Done == true) &&
		(sent3Done == true) &&
		(sent4Done == true) &&
		(missionwon == false)
		)
	{
		if
			(
			(!IsAlive(aw1)) &&
			(!IsAlive(aw2)) &&
			(!IsAlive(aw3)) &&
			(!IsAlive(aw4)) &&
			(!IsAlive(aw5)) &&
			(!IsAlive(aw1a)) &&
			(!IsAlive(aw2a)) &&
			(!IsAlive(aw3a)) &&
			(!IsAlive(aw4a)) &&
			(!IsAlive(aw5a)) &&
			(!IsAlive(aw6a)) &&
			(!IsAlive(aw7a)) &&
			(!IsAlive(aw8a)) &&
			(!IsAlive(aw9a)) &&
			(!IsAlive (w1u1)) &&
			(!IsAlive (w1u2)) &&
			(!IsAlive (w1u3)) &&
			(!IsAlive (w1u4)) &&
			(!IsAlive (w2u1)) &&
			(!IsAlive (w2u2)) &&
			(!IsAlive (w2u3)) &&
			(!IsAlive (w2u4)) &&
			(!IsAlive (w3u1)) &&
			(!IsAlive (w3u2)) &&
			(!IsAlive (w3u3)) &&
			(!IsAlive (w3u4)) &&
			(!IsAlive (w4u1)) &&
			(!IsAlive (w4u2)) &&
			(!IsAlive (w4u3)) &&
			(!IsAlive (w4u4))
			)
		{
			missionwon = true;
			newobjective = true;
			AudioMessage ("misn0511.wav");
			AudioMessage ("misn0512.wav");
			SucceedMission (GetTime() + 15.0f, "misn05w1.des");
		}
	}

	if
		(
		(!IsAlive(svrec)) && (takeoutfactory == false)
		)
	{
		Attack(w1u1, lemnos);
		Attack(w1u2, lemnos);
		Attack(w1u3, lemnos);
		Attack(w1u4, lemnos);
		Attack(w2u1, lemnos);
		Attack(w2u2, lemnos);
		Attack(w2u3, lemnos);
		Attack(w2u4, lemnos);
		Attack(w3u1, lemnos);
		Attack(w3u2, lemnos);
		Attack(w3u3, lemnos);
		Attack(w3u4, lemnos);
		Attack(w4u1, lemnos);
		Attack(w4u2, lemnos);
		Attack(w4u3, lemnos);
		Attack(w4u4, lemnos);
		takeoutfactory = true;
	}

	

	

	


}

IMPLEMENT_RTIME(Misn05Mission)

Misn05Mission::Misn05Mission(void)
{
}

Misn05Mission::~Misn05Mission()
{
}

bool Misn05Mission::Load(file fp)
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

bool Misn05Mission::PostLoad(void)
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

bool Misn05Mission::Save(file fp)
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

void Misn05Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

#if 0
// this is broken right now
#undef PI
#include "..\schedule\Ai.h"
#include "..\schedule\team.h"
#include "..\schedule\Goal.h"
#include "..\schedule\Mapgrid_Goal.h"

static void NoEscorts(void)
{
	if (AI_map == NULL)
		return;
	if (AI_map->team[2] == NULL)
		return;
	AIP_struct *aip = AI_map->team[2]->AIP;
	if (aip == NULL)
		return;
	aip->escort_priority = 0;
	aip->min_escort_force = 100;
	aip->max_escort_force = 100;

	aip->perimeter_priority = 0;
	aip->min_perimeter_force = 100;
	aip->max_perimeter_force = 100;

	aip->defend_buildings_priority = 0;
	aip->min_building_defense_force = 100;
	aip->max_building_defense_force = 100;
}

#else
static void NoEscorts(void)
{
	_ASSERTE(FALSE);
}
#endif
