#include "GameCommon.h"

#include "..\fun3d\AiMission.h"
#include "..\fun3d\ScriptUtils.h"
#include "..\fun3d\Factory.h"

/*
	Misns8Mission
*/

class Misns8Mission : public AiMission {
	DECLARE_RTIME(Misns8Mission)
public:
	Misns8Mission(void);
	~Misns8Mission();

	virtual bool Load(file fp);
	virtual bool PostLoad(void);
	virtual bool Save(file fp);

	virtual void Update(void);

	virtual void AddObject(GameObject *gameObj);

private:
	void AddObject(Handle h);
	void Setup(void);
	void Execute(void);

	// bools
	union {
		struct {
			bool
				start_done,
				convoy_start,
				convoy_over,
				nsdf_adjust,
				base_build,
				new_muf_built, muf_deployed,
				plan_a, plan_b, plan_c,
				gech1_set, gechs_built,
				turret_move, turret1_set, turret2_set, turret3_set, turret4_set,
				rig_movea, rig_prep, rig_prepa, rigs_ordered, rig_wait,
				rigsabuildn,
				rigs_at_last, build_last, prep_silo, build_silo,
				t1down, t2down, t3down, new_turret_orders,
				silo_center_prep, silo1_build, prep_center_towers, welldone_rig,
				recycle_move, recy_goto_geyser, recy_deployed,
				at_geyser, artil_build, muf_pack,
				start_attack, recycle_pack, scav_sent,
				rebuild1_prep, rebuild2_prep, rebuild3_prep,
				rebuilding1, rebuilding2, rebuilding3,
				rebuild4_prep, rebuild5_prep, rebuild6_prep,
				rebuilding4, rebuilding5, rebuilding6,
				warning, tanks_built, tanks_follow, bomb_attack, apc_attack, walker_attack,
				build_muf, back_in_business, game_over, recycle_message, new_muf,
				escort1_build, escort2_build, escort3_build,
				silo_lost, maintain, rig_there, rigs_reordered,
				general_spawn, key_open,
				sav1_lost, sav2_lost, sav3_lost, sav4_lost, sav5_lost, sav6_lost,
				sav1_togeneral, sav2_togeneral, sav3_togeneral, sav4_togeneral, sav5_togeneral, sav6_togeneral,
				savs_alive, general_dead,
				general_message1, general_message2, general_message3, general_message4, general_message5, general_message6,
				sav1_attack, sav2_attack, sav3_attack, sav4_attack, sav5_attack, sav6_attack,
				player_payback, sav_payback, general_scream, danger_message,
				sav1_swap, sav2_swap, sav3_swap, sav4_swap, sav5_swap, sav6_swap,
				sav_attack,
				b_last;
		};
		bool b_array[113];
	};

	// floats
	union {
		struct {
			float
				unit_spawn_time,
				new_muf_time,
				convoy_check,
				turret_check,
				rig_check,
				rig_check2,
				rig_move,
				base_build_time,
				silo_prep,
				turret1_set_time, turret2_set_time, turret3_set_time, turret4_set_time,
				recy_time, muf_timer, rebuild_time, rebuild_time2,
				muf_warning, tank_check, escort_time, defense_check,
				center_check, alt_check, next_second, next_second2, go_to_alt,
				pay_off, sav_check, damage_time, help_me_check,
				f_last;
		};
		float f_array[30];
	};

	// handles
	union {
		struct {
			Handle
				user, cam1, cam2, cam3, cam4,
				avrig1, avrig2,
				avmuf, avrecycle, 
				
				avmuftemp, avrecycletemp,
				
				ccarecycle, ccamuf, avturret1, avturret2, avturret3, avturret4,
				center_geyser, first_geyser, last_geyser, sv_geyser, av_geyser, temp_geyser, turret_geyser,
				dis_geyser1, dis_geyser2, avmuf_geyser,
				avscav1, avscav2, avscav3, avbomb1, avbomb2, avapc1, avapc2, avgech1, avtank1, avtank2, avtank3,
				avgech2, avtower1, avtower2, avpower1, avpower2, avtower3,
				avtower4, avpower3, avpower4, avsilo1, avsilo2, screwtower, screwpower, 
				svpower1, svpower2,
				sav1, sav2, sav3, sav4, sav5, sav6, avfighter1, avfighter2, avwalker,
				escort1, escort2, escort3,
				powerplant1, powerplant2, basetower1, basetower2,
				screwu1, screwu2, key_tank,
				badsav1, badsav2, badsav3, badsav4, badsav5, badsav6,
				popartil, nark,
				h_last;
		};
		Handle h_array[80];
	};

	// integers
	union {
		struct {
			int
				units, scrap, check, check2, tanks, defense1, defense2,
				silo1, tower1, power1, silo2, tower2, power2,
				i_last;
		};
		int i_array[13];
	};
};

IMPLEMENT_RTIME(Misns8Mission)

Misns8Mission::Misns8Mission(void)
{
}

Misns8Mission::~Misns8Mission()
{
}

void Misns8Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

bool Misns8Mission::Load(file fp)
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

bool Misns8Mission::PostLoad(void)
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

bool Misns8Mission::Save(file fp)
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

void Misns8Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

void Misns8Mission::Setup(void)
{

	units = 1;
	scrap = 0;
	check = 1;
	check2 = 1;
	tanks = 0;
	defense1 = 3;
	defense2 = 3;
	silo1 = 1;
	tower1 = 1;
	power1 = 1;
	silo2 = 1;
	tower2 = 1;
	power2 = 1;

	start_done = false;
	convoy_start = false;
	convoy_over = false;
	nsdf_adjust = false;
	new_muf_built = false;
	plan_a = false;
	plan_b = false;
	plan_c = false;
	gech1_set = false;
	gechs_built = false;
	turret_move = false;
	turret1_set = false;
	turret2_set = false;
	turret3_set = false;
	turret4_set = false;
	rig_movea = false;
	rig_prep = false;
	rig_prepa = false;
	rigs_ordered = false;
	rig_wait = false;
	new_muf_built = false;
	muf_deployed = false;
	base_build = false;
	rigsabuildn = false;
	rigs_at_last = false;
	build_last = false;
	prep_silo = false;
	build_silo = false;
	t1down = false;
	t2down = false;
	t3down = false;
	new_turret_orders = false;
	silo_center_prep = false;
	silo1_build = false;
	prep_center_towers = false;
	welldone_rig = false;
	recycle_move = false;
	recy_goto_geyser = false;
	recy_deployed = false;
	at_geyser = false;
	artil_build = false;
	muf_pack = false;
	recycle_pack = false;
	start_attack = false;
	scav_sent = false;
	rebuild1_prep = false;
	rebuild2_prep = false;
	rebuild3_prep = false;
	rebuilding1 = false;
	rebuilding2 = false;
	rebuilding3 = false;
	rebuild4_prep = false;
	rebuild5_prep = false;
	rebuild6_prep = false;
	rebuilding4 = false;
	rebuilding5 = false;
	rebuilding6 = false;
	warning = false;
	tanks_follow = false;
	bomb_attack = false;
	apc_attack = false;
	walker_attack = false;
	tanks_built = false;
	build_muf = false;
	back_in_business = false;
	game_over = false;
	recycle_message = false;
	new_muf = false;
	escort1_build = false;
	escort2_build = false;
	escort3_build = false;
	silo_lost = false;
	maintain = false;
	rig_there = false;
	rigs_reordered = false;
	general_spawn = false;
	key_open = false;
	sav1_lost = false;
	sav2_lost = false;
	sav3_lost = false;
	sav4_lost = false;
	sav5_lost = false;
	sav6_lost = false;
	savs_alive = false;
	general_dead = false;
	sav1_togeneral = false;
	sav2_togeneral = false;
	sav3_togeneral = false;
	sav4_togeneral = false;
	sav5_togeneral = false;
	sav6_togeneral = false;
	general_message1 = false;
	general_message2 = false;
	general_message3 = false;
	general_message4 = false;
	general_message5 = false;
	general_message6 = false;
	player_payback = false;
	sav_payback = false;
	sav1_attack = false;
	sav2_attack = false;
	sav3_attack = false;
	sav4_attack = false;
	sav5_attack = false;
	sav6_attack = false;
	general_scream = false;
	danger_message = false;
	sav1_swap = false;
	sav2_swap = false;
	sav3_swap = false;
	sav4_swap = false;
	sav5_swap = false;
	sav6_swap = false;
	sav_attack = false;


	next_second = 0;
	next_second2 = 0;
	unit_spawn_time = 99999.0f;
	new_muf_time = 99999.0f;
	convoy_check = 99999.0f;
	turret_check = 99999.0f;
	rig_check = 99999.0f;
	rig_check2 = 99999.0f;
	rig_move = 99999.0f;
	base_build_time = 99999.0f;
	silo_prep = 99999.0f;
	turret1_set_time = 99999.0f;
	turret2_set_time = 99999.0f;
	turret3_set_time = 99999.0f;
	turret4_set_time = 99999.0f;
	recy_time = 99999.0f;
	muf_timer = 99999.0f;
	rebuild_time = 99999.0f;
	rebuild_time2 = 99999.0f;
	muf_warning = 99999.0f;
	tank_check = 99999.0f;
	escort_time = 99999.0f;
	defense_check = 99999.0f;
	center_check = 99999.0f;
	alt_check = 99999.0f;
	go_to_alt = 99999.0f;
	pay_off = 99999.0f;
	sav_check = 99999.0f;
	damage_time = 99999.0f;
	help_me_check = 99999.0f;

	avmuf = GetHandle ("avmuf");
	avrecycle = GetHandle ("avrecycle");
	ccarecycle = GetHandle ("svrecycle");
	ccamuf = GetHandle ("svmuf");
	center_geyser = GetHandle ("center_geyser");
	first_geyser = GetHandle ("first_geyser");
	last_geyser = GetHandle ("last_geyser");
	sv_geyser = GetHandle ("sv_geyser");
	av_geyser = GetHandle ("av_geyser");
	temp_geyser = GetHandle("temp_geyser");
	turret_geyser = GetHandle("turret_geyser");
	dis_geyser1 = GetHandle("dis_geyser1");
	dis_geyser2 = GetHandle("dis_geyser2");
	cam1 = GetHandle("cam");
	cam2 = GetHandle("basecam");
	powerplant1 = GetHandle("powerplant1");
	powerplant2 = GetHandle("powerplant2");
	basetower1 = GetHandle("basetower1");
	basetower2 = GetHandle("basetower2");
	avmuf_geyser = GetHandle("avmuf_geyser");
	cam3 = NULL;
	cam4 = NULL;
	avrig1 = NULL;
	avrig2 = NULL;
	avscav1 = NULL;
	avscav2 = NULL;
	avscav3 = NULL;
	avbomb1 = NULL;
	avbomb2 = NULL;
	avapc1 = NULL;
	avapc2 = NULL;
	avgech1 = NULL;
	avgech2 = NULL;
	avtower1 = NULL;
	avtower2 = NULL;
	avpower1 = NULL;
	avpower2 = NULL;
	avtower3 = NULL;
	avtower4 = NULL;
	avpower3 = NULL;
	avpower4 = NULL;
	avsilo1 = NULL;
	avsilo2 = NULL;
	avtank1 = NULL;
	avtank2 = NULL;
	avtank3 = NULL;
	screwtower = NULL;
	screwpower = NULL;
	svpower1 = NULL;
	svpower2 = NULL;
	avturret1 = NULL;
	avturret2 = NULL;
	sav1 = NULL;
	sav2 = NULL;
	sav3 = NULL;
	sav4 = NULL;
	sav5 = NULL;
	sav6 = NULL;
	avfighter1 = NULL;
	avfighter2 = NULL;
	avwalker = NULL;
	escort1 = NULL;
	escort2 = NULL;
	escort3 = NULL;
	screwu1 = NULL;
	screwu2 = NULL;
	key_tank = NULL;
	badsav1 = NULL;
	badsav2 = NULL;
	badsav3 = NULL;
	badsav4 = NULL;
	badsav5 = NULL;
	badsav6 = NULL;
	popartil = NULL;
	nark = NULL;
}


void Misns8Mission::AddObject(Handle h)
{
	if ((avturret1 == NULL) && (IsOdf(h,"bvtur8")))
	{
		avturret1 = h;
	}
	else if ((avturret2 == NULL) && (IsOdf(h,"bvtur8")))			
	{
		avturret2 = h;
	}
	else if ((avfighter1 == NULL) && (IsOdf(h,"bvra8")))
	{
		avfighter1 = h;
	}
	else if ((avfighter2 == NULL) && (IsOdf(h,"bvra8")))
	{
		avfighter2 = h;
	}
	else if ((avrig1 == NULL) && (IsOdf(h,"avcns8")))		
	{
		avrig1 = h;
	}
	else if ((avrig2 == NULL) && (IsOdf(h,"avcns8")))		
	{
		avrig2 = h;
	}
	else if ((avtank1 == NULL) && (IsOdf(h,"bvtavk")))		
	{
		avtank1 = h;
	}
	else if ((avtank2 == NULL) && (IsOdf(h,"bvtavk")))		
	{
		avtank2 = h;
	}
	else if ((avtank3 == NULL) && (IsOdf(h,"bvtavk")))
	{
		avtank3 = h;
	}
	else if ((avtower1 == NULL) && (IsOdf(h,"abtowe")))		
	{
		avtower1 = h;
	}
	else if ((avtower2 == NULL) && (IsOdf(h,"abtowe")))		
	{
		avtower2 = h;
	}
	else if ((avpower1 == NULL) && (IsOdf(h,"abwpow")))		
	{
		avpower1 = h;
	}
	else if ((avpower2 == NULL) && (IsOdf(h,"abwpow")))		
	{
		avpower2 = h;
	}
	else if ((avtower3 == NULL) && (IsOdf(h,"abtowe")))		
	{
		avtower3 = h;
	}
	else if ((avtower4 == NULL) && (IsOdf(h,"abtowe")))		
	{
		avtower4 = h;
	}
	else if ((avpower3 == NULL) && (IsOdf(h,"abwpow")))		
	{
		avpower3 = h;
	}
	else if ((avpower4 == NULL) && (IsOdf(h,"abwpow")))		
	{
		avpower4 = h;
	}
	else if ((avsilo1 == NULL) && (IsOdf(h,"absilo")))		
	{
		avsilo1 = h;
	}
	else if ((avsilo2 == NULL) && (IsOdf(h,"absilo")))		
	{
		avsilo2 = h;
	}
	else if ((screwtower == NULL) && (IsOdf(h,"abtowe")))		
	{
		screwtower = h;
	}
	else if ((screwpower == NULL) && (IsOdf(h,"abwpow")))		
	{
		screwpower = h;
	}
	else if ((svpower1 == NULL) && (IsOdf(h,"sbwpow")))		
	{
		svpower1 = h;
	}
	else if ((svpower2 == NULL) && (IsOdf(h,"sbwpow")))		
	{
		svpower2 = h;
	}
	else if ((avturret3 == NULL) && (IsOdf(h,"bvtur8")))
	{
		avturret3 = h;
	}
	else if ((avturret4 == NULL) && (IsOdf(h,"bvtur8")))	
	{
		avturret4 = h;
	}
	else if ((avbomb1 == NULL) && (IsOdf(h,"bvhraz")))					
	{
		avbomb1 = h;
	}
	else if ((avapc1 == NULL) && (IsOdf(h,"bvapc")))		
	{
		avapc1 = h;
	}
	else if ((sav1 == NULL) && (IsOdf(h,"savtnk")))	
	{
		sav1 = h;
	}
	else if ((sav2 == NULL) && (IsOdf(h,"savtnk")))	
	{
		sav2 = h;
	}
	else if ((sav3 == NULL) && (IsOdf(h,"savtnk")))	
	{
		sav3 = h;
	}
	else if ((sav4 == NULL) && (IsOdf(h,"savtnk")))	
	{
		sav4 = h;
	}
	else if ((sav5 == NULL) && (IsOdf(h,"savtnk")))
	{
		sav5 = h;
	}
	else if ((sav6 == NULL) && (IsOdf(h,"savtnk")))
	{
		sav6 = h;
	}
	else if ((avwalker == NULL) && (IsOdf(h,"bvwalk")))
	{
		avwalker = h;
	}
}


void Misns8Mission::Execute(void)
{

// START OF SCRIPT

	user = GetPlayerHandle(); //assigns the player a handle every frame


	if (!IsAlive(sav1))
	{
		sav1_swap = false;
	}
	if (!IsAlive(sav2))
	{
		sav2_swap = false;
	}
	if (!IsAlive(sav3))
	{
		sav3_swap = false;
	}
	if (!IsAlive(sav4))
	{
		sav4_swap = false;
	}
	if (!IsAlive(sav5))
	{
		sav5_swap = false;
	}
	if (!IsAlive(sav6))
	{
		sav6_swap = false;
	}

	if (!IsAlive(avbomb1))
	{
		bomb_attack = false;
	}

	if (!IsAlive(avapc1))
	{
		apc_attack = false;
	}

	if (!IsAlive(avwalker))
	{
		walker_attack = false;
	}

	if ((IsAlive(avrecycle)) && (!recycle_move))
	{
		if (GetTime() > next_second)
		{
			GameObjectHandle::GetObj(avrecycle)->AddHealth(200.0f);
			next_second = GetTime() + 1.0f;
		}				
	}

	if (!start_done)
	{ 
		SetScrap(1, 25);
		SetScrap(2, 40);
		SetPilot(1, 10);
		SetPilot(2, 60);
		AudioMessage("misns800.wav"); // General "mission breifing"
		ClearObjectives();
		AddObjective("misns800.otf", WHITE);
//		AddObjective("misns800.otf", WHITE);
		avscav1 = BuildObject("bvsca8", 2, "american_spawn");
		avscav2 = BuildObject("bvsca8", 2, "american_spawn");
		avscav3 = BuildObject("bvsca8", 2, "american_spawn");
		nark = BuildObject("bvra8", 2, "american_spawn");
		if (cam1!=NULL) GameObjectHandle::GetObj(cam1)->SetName("Black Dog Base");
		if (cam2!=NULL) GameObjectHandle::GetObj(cam2)->SetName("Drop Zone");
		defense_check = Get_Time() + 60.0f;
		SetAIP("misns8.aip");

		start_done = true;
		plan_a = true;
	}



// this is the start of PLAN A - take the center
if (plan_a)
{

// first I build the turrets and then the rigs
/*	if ((IsAlive(avturret3)) && (!turret_move))
	{
		Goto(avturret3, "center_path3");

		if (IsAlive(avturret1))
		{
			Goto(avturret1, "center_path");
		}

		if (IsAlive(avturret2))
		{
			Retreat(avturret2, "center_path2", 1);
		}

		if ((IsAlive(nark)) && (IsAlive(ccarecycle)))
		{
			Attack(nark, ccarecycle, 1);
		}
		
		turret_check = Get_Time() + 10.0f;
		turret_move = true;
	}

	if ((turret_move) && (turret_check < Get_Time()))
	{
		if ((IsAlive(avturret1)) && (!turret1_set) && (GetDistance(avturret1, turret_geyser) < 100.0f))
		{
			Defend(avturret1);
			turret1_set_time = Get_Time() + 10.0f;
			turret1_set = true;
		}

		if ((IsAlive(avturret2)) && (!turret2_set) && (GetDistance(avturret2, turret_geyser) < 100.0f))
		{
			Defend(avturret2);
//			RemoveObject(temp_geyser);
			turret2_set_time = Get_Time() + 11.0f;
			turret2_set = true;
		}

		if ((IsAlive(avturret3)) && (!turret3_set) && (GetDistance(avturret3, turret_geyser) < 100.0f))
		{
			Defend(avturret3);
			turret3_set_time = Get_Time() + 12.0f;
			turret3_set = true;
		}

		if ((IsAlive(popartil)) && (!turret4_set) && (GetDistance(popartil, temp_geyser) < 20.0f))
		{
			Defend(popartil);
			turret4_set_time = Get_Time() + 12.0f;
			turret4_set = true;
		}

		turret_check = Get_Time() + 6.0f;
	}

	if (!new_turret_orders)
	{
		if ((turret1_set) && (turret1_set_time < Get_Time()))
		{
			if (IsAlive(avturret1))
			{
				turret1_set_time = Get_Time() + 20.0f;
				Defend(avturret1);
			}
		}

		if ((turret2_set) && (turret2_set_time < Get_Time()))
		{
			if (IsAlive(avturret2))
			{
				turret2_set_time = Get_Time() + 20.0f;
				Defend(avturret2);
			}
		}

		if ((turret3_set) && (turret3_set_time < Get_Time()))
		{
			if (IsAlive(avturret3))
			{
				turret3_set_time = Get_Time() + 20.0f;
				Defend(avturret3);
			}
		}

		if ((turret4_set) && (turret4_set_time < Get_Time()))
		{
			if (IsAlive(popartil))
			{
				turret4_set_time = Get_Time() + 180.0f;
				Defend(popartil);
			}
		}
	}

/*	if ((turret1_set) && (turret1_set_time < Get_Time()))
	{
		if ((IsAlive(avturret1)) && (!t1down))
		{
			Defend(avturret1, 1);
			t1down = true;
		}
	}

	if ((turret2_set) && (turret2_set_time < Get_Time()))
	{
		if ((IsAlive(avturret2)) && (!t2down))
		{
			Defend(avturret2, 1);
			t2down = true;
		}
	}

	if ((turret3_set) && (turret3_set_time < Get_Time()))
	{
		if ((IsAlive(avturret3)) && (!t3down))
			{
				Defend(avturret3, 1);
				t3down = true;
			}
	}
*/
}

// this is telling the construction rigs to build gun towers at their base
	if ((IsAlive(avrig1)) && (IsAlive(avrig2)) && (!rig_prep))
	{
		Build(avrig1, "abwpow");
		Build(avrig2, "abtowe");
		base_build_time = Get_Time() + 10.0f;
		SetAIP("misns8a.aip"); // this buld another turret and HAVE 3 fighters (have 4 scavs)
		rig_prep = true;
	}

	if ((rig_prep) && (!base_build) && (base_build_time < Get_Time()))
	{
		AddScrap(2, 60);

		if (IsAlive(avrig1))
		{
			Dropoff(avrig1, "rpower1");
		}
		if (IsAlive(avrig2))
		{
			Dropoff(avrig2, "rtower1");
		}

		base_build = true;
	}

// this is sending the construction rigs to the scrap field
	if ((base_build) && (IsAlive(avtower1)) && (IsAlive(avpower1)) && (!rig_movea))
	{
		if (IsAlive(avrig1))
		{
			Goto(avrig1, "center_path", 1);
		}

		if (IsAlive(avrig2))
		{
			Goto(avrig2, "center_path", 1);
		}
		
		rig_check = Get_Time() + 90.0f;
		rig_movea = true;
	}

// building artil w/poppers
	if ((!artil_build) && (rig_movea))
	{
		popartil = BuildObject("avart8", 2, "american_spawn");
		artil_build = true;
	}

	if ((!at_geyser) && (IsAlive(popartil)))
	{
		Goto(popartil, temp_geyser, 1);
		at_geyser = true;
	}

// first I build a silo
	if ((!silo_center_prep) && (rig_check < Get_Time()))
	{
		rig_check2 = Get_Time() + 5.0f;

		if (IsAlive(avrig1))
		{
			Build(avrig1, "absilo");
		}

		if (IsAlive(avrig2))
		{
			Build(avrig2, "absilo");
		}		

		silo_center_prep = true;
	}

	if ((silo_center_prep) && (!silo1_build) && (rig_check2 < Get_Time()))
	{
		rig_check2 = Get_Time() + 5.0f;
		scrap = GetScrap(2);

		if (IsAlive(avrig1))
		{
			check2 = GetDistance(avrig1, temp_geyser);
		}
		else
		{
			if (IsAlive(avrig2))
			{
				check2 = GetDistance(avrig2, temp_geyser);
			}
		}
	
		if (scrap > 8.0f) 
		{
			if (IsAlive(avrig1))
			{
				Dropoff(avrig1, "center_silo");

				if (IsAlive(avrig2))
				{
					Goto(avrig2, "center_silo");

				}

				silo1_build = true;
			}
			else
			{
				if (IsAlive(avrig2))
				{
					Dropoff(avrig2, "center_silo");
					silo1_build = true;
				}
			}
		}
		else
		{
			if (check2 < 100.0f)
			{
				if (IsAlive(avrig1))
				{
					Defend(avrig1);
				}

				if (IsAlive(avrig2))
				{
					Defend(avrig2);
				}
			}
			else
			{
				if (IsAlive(avrig1))
				{
					Goto(avrig1, temp_geyser, 1);
				}

				if (IsAlive(avrig2))
				{
					Goto(avrig2, temp_geyser, 1);
				}
			}
		}
	}

	if ((silo1_build) && (!prep_center_towers) && (IsAlive(avsilo1)))
	{
		if (IsAlive(avrig1))
		{
			Build(avrig1, "abwpow");
		}

		if (IsAlive(avrig2))
		{
			Build(avrig2, "abtowe");
		}
		
		SetAIP("misns8b.aip"); // this builds another fighter (have 3) (have 4 scavs)
		rig_check = Get_Time() + 10.0f;
		muf_timer = Get_Time() + 10.0f; // BE CAREFUL - carries over into plan_b 
		prep_center_towers = true;
	}

// this is making the rigs build a gun tower and powerplant in the center
	if ((prep_center_towers) && (!rigs_ordered) && (rig_check < Get_Time()))
	{
		rig_check = Get_Time() + 5.0f;
		scrap = GetScrap(2);

		if (scrap > 14.0f) 
		{
			SetAIP("misns8g.aip"); // this stops building vehicles while the rigs build towers

			if (IsAlive(avrig1))
			{
				Dropoff(avrig1, "main_field2");
			}

			if (IsAlive(avrig2))
			{
				Dropoff(avrig2, "main_field1");
			}

			rigs_ordered = true;
		}
		else
		{
			if ((IsAlive(avrig1)) && (GetDistance(avrig1, temp_geyser) < 200.0f))
			{
				Defend(avrig1);

				if (IsAlive(avrig2))
				{
					Defend(avrig2);
				}
			}
			else
			{
				if ((IsAlive(avrig2)) && (GetDistance(avrig2, temp_geyser) < 200.0f))
				{
					Defend(avrig2);
				}
			}

			AddScrap(2, 2);
		}
	}

/*	if ((rigs_ordered) && (!rigsabuildn) && (rig_check < Get_Time()))
	{
		rig_check = Get_Time() + 10.0f;
		scrap = GetScrap(2);

		if (scrap > 18.0f) 
		{
			if (IsAlive(avrig1))
			{
				Dropoff(avrig1, "main_field2");
			}

			if (IsAlive(avrig2))
			{
				Dropoff(avrig2, "main_field1");
			}

			rigsabuildn = true;
		}
	}
*/
	if ((IsAlive(avtower2)) && (IsAlive(avpower2)) && (!welldone_rig))
	{
		go_to_alt = Get_Time() + 20.0f;
		SetAIP("misns8b.aip"); // this builds another fighter (have 3) (have 4 scavs)		
		center_check = Get_Time() + 5.0f;
		alt_check = Get_Time() + 60.0f;
		new_turret_orders = true; // releases the original 3 turrets if they are still alive
		welldone_rig = true;
	}

// this is checking to see if the muf has tank support
	if ((IsAlive(avtank2)) && (!tanks_follow))
	{
		if (IsAlive (avmuf))
		{
			Follow(avtank2, avmuf);

			if (IsAlive(avtank1))
			{
				Follow(avtank1, avmuf);
			}

			tank_check = Get_Time() + 30.0f;
			tanks_follow = true;
		}
	}

	if ((tanks_follow) && (tank_check < Get_Time()) && (!tanks_built))
	{
		tank_check = Get_Time() + 30.0f;

		if (IsAlive(avtank3))
		{
//			tanks = CountUnitsNearObject(avmuf, 4000, 2, "bvtavk");
//
//			if (tanks > 3)
//			{
				tanks_built = true;
//			}
		}
	}

	if ((tanks_built) && (welldone_rig) && (plan_a))
	{
		plan_a = false;
		plan_b = true;
	}







// this is the start of PLAN B "move muf"
if (plan_b)
{

// carry-over form plan_a
/*	if ((turret1_set) && (turret1_set_time < Get_Time()))
	{
		if (IsAlive(avturret1))
		{
			turret1_set_time = Get_Time() + 20.0f;
			Defend(avturret1);
		}
	}

	if ((turret2_set) && (turret2_set_time < Get_Time()))
	{
		if (IsAlive(avturret2))
		{
			turret2_set_time = Get_Time() + 20.0f;
			Defend(avturret2);
		}
	}

	if ((turret3_set) && (turret3_set_time < Get_Time()))
	{
		if (IsAlive(avturret3))
		{
			turret3_set_time = Get_Time() + 20.0f;
			Defend(avturret3);
		}
	}
*/
	if ((turret4_set) && (turret4_set_time < Get_Time()))
	{
		if (IsAlive(popartil))
		{
			turret4_set_time = Get_Time() + 180.0f;
			Defend(popartil);
		}
	}


// this makes the muf move

	if ((!muf_pack) && (IsAlive(avmuf)) && (muf_timer < Get_Time()))
	{
		muf_timer = Get_Time() + 10.0f;
		scrap = GetScrap(2);

		if (scrap > 11)
		{
			Pickup(avmuf, 0, 1);
			muf_timer = Get_Time() + 10.0f;
			muf_pack = true;
		}
	}

	if ((!convoy_start) && (muf_pack) && (IsAlive(avmuf)) && (muf_timer < Get_Time()))
	{
		Goto(avmuf, "convoy_path", 1);
		SetAIP("misns8d.aip"); // povides fighter support
		muf_timer = Get_Time() + 60.0f;
		muf_warning = Get_Time() + 10.0f;

		if (IsAlive(avfighter1))
		{
			Follow(avfighter1, avmuf);
		}
		if (IsAlive(avfighter2))
		{
			Follow(avfighter2, avmuf);
		}

		convoy_start = true;
	}

	if ((!warning) && (convoy_start) && (IsAlive(avmuf)) && (muf_warning < Get_Time()))
	{
		muf_warning = Get_Time() + 6.0f;

		if (GetDistance(user, avmuf) < 100.0f)
		{
			warning = true;
		}
		else
		{
			if (GetDistance(avmuf, dis_geyser1) < 100.0f)
			{
				AudioMessage("misns801.wav");
				cam3 = BuildObject ("apcamr", 1, "cam_spawn");
				if (cam3!=NULL) GameObjectHandle::GetObj(cam3)->SetName("Choke Point");
				ClearObjectives();
				AddObjective("misns800.otf", WHITE);
				AddObjective("misns801.otf", WHITE);
				warning = true;
			}
		}
	}

	if ((!convoy_over) && (convoy_start) && (IsAlive(avmuf)) && (muf_timer < Get_Time()))
	{
		muf_timer = Get_Time() + 5.0f;

		if (GetDistance(avmuf, center_geyser) < 100.0f)
		{
			Goto(avmuf, center_geyser, 1);
			convoy_over = true;
		}
	}

	if ((convoy_over) && (!muf_deployed))
	{
		if (IsAlive(avmuf))
		{
			bool test=((Factory *) GameObjectHandle::GetObj(avmuf))->IsDeployed();

			if (test)
			{
				muf_deployed = true;
			}
		}
	}

// this is what happens when the muf is destroyed

	if ((convoy_start) && (!IsAlive(avmuf)) && (!new_muf))
	{
		screwu1 = BuildObject("bvtavk", 2, "t1post");
		screwu2 = BuildObject("bvtavk", 2, "t1post");
		if (IsAlive(ccarecycle))
		{
			Attack(screwu1, ccarecycle);
			Attack(screwu2, ccarecycle);
		}
		avmuf = BuildObject("bvmuf", 2, "american_spawn");
		Goto(avmuf, avmuf_geyser);
		muf_deployed = false;
		new_muf = true;
	}

	if ((!start_attack) && (muf_deployed))
	{
		SetAIP("misns8c.aip"); // starts to produce tanks + bombers and gechs (have 4 scavs)
//		plan_b = false;
//		plan_c = true;
		start_attack = true;
	}

	if ((IsAlive(avbomb1)) && (!bomb_attack))
	{
		if (IsAlive(ccarecycle))
		{
			Attack(avbomb1, ccarecycle, 1);
		}

		bomb_attack = true;
	}

	if ((IsAlive(avapc1)) && (!apc_attack))
	{
		if (IsAlive(ccarecycle))
		{
			Attack(avapc1, ccarecycle, 1);
		}

		apc_attack = true;
	}

	if ((IsAlive(avwalker)) && (!walker_attack))
	{
		if (IsAlive(ccarecycle))
		{
			Attack(avwalker, ccarecycle, 0);
		}

		walker_attack = true;
	}
}





// this constitutes the situation where plan_c happens
	if ((!plan_c) && (IsAlive(avrecycle)) && (defense_check < Get_Time()))
	{
		defense_check = Get_Time() + 5.0f;
		defense1 = CountUnitsNearObject(avrecycle, 200.0f, 2, "abtowe");
		defense2 = CountUnitsNearObject(avrecycle, 200.0f, 2, "abwpow");
		scrap = GetScrap(2);

		if ((/*((defense1 == 1) && (defense2 == 1)) || */(defense1 == 0) || (defense2 == 0)) && (scrap < 10.0f))
		{
			plan_a = false;
			plan_b = false;
			plan_c = true;
		}
	}





// this is the start of PLAN C "move Recycler"

if (plan_c)
{
/*	if ((!escort1_build) && (IsAlive(avrecycle)) && (escort_time < Get_Time()))
	{ 
		escort1 = BuildObject("bvraz", 2, "american_spawn");
		Follow(escort1, avrecycle);
		escort_time = Get_Time() + 10.0f;
		escort1_build = true;
	}

	if ((!escort2_build) && (IsAlive(avrecycle)) && (escort1_build) &&  (escort_time < Get_Time()))
	{ 
		escort2 = BuildObject("bvraz", 2, "american_spawn");
		Follow(escort2, avrecycle);
		escort_time = Get_Time() + 10.0f;
		escort2_build = true;
	}

	if ((!escort3_build) && (IsAlive(avrecycle)) && (escort2_build) && (escort_time < Get_Time()))
	{ 
		escort3 = BuildObject("bvraz", 2, "american_spawn");
		Follow(escort3, avrecycle);
		escort3_build = true;
	}

*/
	if (/*escort3_build) && */ ((general_message1) || (sav_payback)) && (!recycle_pack) && (IsAlive(avrecycle)))
	{
		AddScrap(2, 20);
		SetAIP("misns8c.aip");
		Pickup(avrecycle, 0, 1);
		recy_time = Get_Time() + 10.0f;
		recycle_pack = true;
	}

	if ((!recycle_move) && (recycle_pack) && (IsAlive(avrecycle)) && (recy_time < Get_Time()))
	{
		Goto(avrecycle, "escape_route", 1);
		recy_time = Get_Time() + 60.0;

/*			if (IsAlive(escort1))
		{
			Follow(escort1, avrecycle);
		}

		if (IsAlive(escort2))
		{
			Follow(escort2, avrecycle);
		}

		if (IsAlive(escort3))
		{
			Follow(escort3, avrecycle);
		}
*/
		SetPerceivedTeam(avrecycle, 1);

		if (IsAlive(basetower1))
		{
			SetPerceivedTeam(basetower1, 1);
		}
		if (IsAlive(basetower2))
		{
			SetPerceivedTeam(basetower2, 1);
		}
		if (IsAlive(avtower1))
		{
			SetPerceivedTeam(avtower1, 1);
		}
		if (IsAlive(powerplant1))
		{
			SetPerceivedTeam(powerplant1, 1);
		}
		if (IsAlive(powerplant2))
		{
			SetPerceivedTeam(powerplant2, 1);
		}
		if (IsAlive(avpower1))
		{
			SetPerceivedTeam(avpower1, 1);
		}
		if (IsAlive(avmuf))
		{
			SetPerceivedTeam(avmuf, 1);
		}
	
		recycle_move = true;
	}

	if ((recycle_move) && (IsAlive(avrecycle)) && (recy_time < Get_Time()))
	{
		recy_time = Get_Time() + 10.0f;
/*
		if ((GetDistance(avrecycle, dis_geyser2) < 100.0f) && (!recycle_message))
		{
			AudioMessage("misns802.wav");
			cam4 = BuildObject ("apcamr", 1, "last_nav_spawn");
			if (cam4!=NULL) GameObjectHandle::GetObj(cam4)->SetName("Choke Point");
			recycle_message = true;
		}
*/
		if ((GetDistance(avrecycle, last_geyser) < 100.0f) && (!recy_goto_geyser))
		{
			Goto(avrecycle, last_geyser, 1);
			SetPerceivedTeam(avrecycle, 2);
			recy_goto_geyser = true;
		}
	}

	if ((recy_goto_geyser) && (!recy_deployed) && (IsAlive(avrecycle)) && (recy_time < Get_Time()))
	{
		recy_time = Get_Time() + 5.0f;
		bool test=((Factory *) GameObjectHandle::GetObj(avrecycle))->IsDeployed();

		if (test)
		{
			SetAIP("misns8a.aip");
			recy_deployed = true;
		}
	}

	if ((recy_deployed) && (!back_in_business))
	{
		if ((IsAlive(avturret1)) && (IsAlive(avturret2)))
		{
			SetAIP("misns8f.aip");
			back_in_business = true;
		}
	}
}





 // this makes sure rig1 keep up the center

 if ((welldone_rig) && (go_to_alt < Get_Time()) && (!rigs_reordered))
 {
 	if (IsAlive(avsilo1))
	{
		if (IsAlive(avrig1))
		{
//			SetIndependence(avrig1, 1);
			Follow(avrig1, avsilo1);
		}

		if (IsAlive(avrig2))
		{
//			SetIndependence(avrig2, 1);
			Goto(avrig2, "go_path");
		}
	}
	else
	{
		if (IsAlive(avrig1))
		{
//			SetIndependence(avrig2, 1);
			Build(avrig1, "absilo");
		}

		if (IsAlive(avrig2))
		{
//			SetIndependence(avrig2, 1);
			Goto(avrig2, "go_path");
		}
	}

	rigs_reordered = true;
 }

 if ((rigs_reordered) && (IsAlive(avrig1)) && (center_check < Get_Time()))
 {
	if ((!rebuild1_prep) && (!rebuild2_prep) && (!rebuild3_prep))
	{
		center_check = Get_Time() + 10.0f;
		silo1 = CountUnitsNearObject(temp_geyser, 900, 2, "absilo");
		power1 = CountUnitsNearObject(temp_geyser, 900, 2, "abwpow");
		tower1 = CountUnitsNearObject(temp_geyser, 900, 2, "abtowe");

		if (silo1 == 0)
		{
			Build(avrig1, "absilo");
			rebuild_time = Get_Time() + 5.0f;
			rebuild1_prep = true;
		}
		else
		{
			if (power1 == 0)
			{
				Build(avrig1, "abwpow");
				rebuild_time = Get_Time() + 5.0f;
				rebuild2_prep = true;
			}
			else
			{
				if (tower1 == 0)
				{
					Build(avrig1, "abtowe");
					rebuild_time = Get_Time() + 5.0f;
					rebuild3_prep = true;
				}
				else
				{
					Defend(avrig1);
				}
			}
		}
	}

	if ((rebuild1_prep) && (!rebuilding1) && (rebuild_time < Get_Time()))
	{
		rebuild_time = Get_Time() + 5.0f;
		scrap = GetScrap(2);
		if (scrap > 8)
		{
			Dropoff(avrig1, "center_silo");
			rebuilding1 = true;
		}
	}

	if ((rebuild2_prep) && (!rebuilding2) && (rebuild_time < Get_Time()))
	{
		rebuild_time = Get_Time() + 5.0f;
		scrap = GetScrap(2);
		if (scrap > 10)
		{
			Dropoff(avrig1, "main_field2");
			rebuilding2 = true;
		}
	}

	if ((rebuild3_prep) && (!rebuilding3) && (rebuild_time < Get_Time()))
	{
		rebuild_time = Get_Time() + 5.0f;
		scrap = GetScrap(2);
		if (scrap > 10)
		{
			Dropoff(avrig1, "main_field1");
			rebuilding3 = true;
		}
	}

	if ((rebuilding1) && (center_check < Get_Time()))
	{
		center_check = Get_Time() + 10.0f;
		silo1 = CountUnitsNearObject(temp_geyser, 900, 2, "absilo");
		if (silo1 == 1)
		{
			rebuild1_prep = false;
			rebuilding1 = false;
		}
	}

	if ((rebuilding2) && (center_check < Get_Time()))
	{
		center_check = Get_Time() + 10.0f;
		power1 = CountUnitsNearObject(temp_geyser, 900, 2, "abwpow");
		if (power1 == 1)
		{
			rebuild2_prep = false;
			rebuilding2 = false;
		}
	}

	if ((rebuilding3) && (center_check < Get_Time()))
	{
		center_check = Get_Time() + 10.0f;
		tower1 = CountUnitsNearObject(temp_geyser, 900, 2, "abtowe");
		if (tower1 == 1)
		{
			rebuild3_prep = false;
			rebuilding3 = false;
		}
	}
 }

 // this is rig2 code

 if ((welldone_rig) && (IsAlive(avrig2)))
 {
	if (!maintain)
	{
		Build(avrig2, "absilo");
		maintain = true;
	}

	if ((alt_check < Get_Time()) && (!rig_there))
	{
		alt_check = Get_Time() + 10.0f;

		if (GetDistance(avrig2, last_geyser) < 300.0f)
		{
			rebuild_time2 = Get_Time() + 5.0f;
			rig_there = true;
		}
	}

	if ((rig_there) && (alt_check < Get_Time()))
	{
		if ((!rebuild4_prep) && (!rebuild5_prep) && (!rebuild6_prep))
		{
			alt_check = Get_Time() + 10.0f;
			silo2 = CountUnitsNearObject(last_geyser, 400, 2, "absilo");
			power2 = CountUnitsNearObject(last_geyser, 400, 2, "abwpow");
			tower2 = CountUnitsNearObject(last_geyser, 400, 2, "abtowe");

			if (silo2 == 0)
			{
				Build(avrig2, "absilo");
				rebuild_time2 = Get_Time() + 5.0f;
				rebuild4_prep = true;
			}
			else
			{
				if (power2 == 0)
				{
					Build(avrig2, "abwpow");
					rebuild_time2 = Get_Time() + 5.0f;
					rebuild5_prep = true;
				}
				else
				{
					if (tower2 == 0)
					{
						Build(avrig2, "abtowe");
						rebuild_time2 = Get_Time() + 5.0f;
						rebuild6_prep = true;
					}
					else
					{
						Defend(avrig2);
						if (!scav_sent)
						{
							if (IsAlive(avscav1))
							{
								Goto(avscav1, "go_path");
							}
							scav_sent = true;
						}
					}
				}
			}
		}

		if ((rebuild4_prep) && (!rebuilding4) && (rebuild_time2 < Get_Time()))
		{
			rebuild_time2 = Get_Time() + 5.0f;
			scrap = GetScrap(2);
			if (scrap > 8)
			{
				Dropoff(avrig2, "alt_silo");
				rebuilding4 = true;
			}
		}

		if ((rebuild5_prep) && (!rebuilding5) && (rebuild_time2 < Get_Time()))
		{
			rebuild_time2 = Get_Time() + 5.0f;
			scrap = GetScrap(2);
			if (scrap > 10)
			{
				Dropoff(avrig2, "alt_power");
				rebuilding5 = true;
			}
		}

		if ((rebuild6_prep) && (!rebuilding6) && (rebuild_time2 < Get_Time()))
		{
			rebuild_time2 = Get_Time() + 5.0f;
			scrap = GetScrap(2);
			if (scrap > 10)
			{
				Dropoff(avrig2, "alt_tower");
				rebuilding6 = true;
			}
		}

		if ((rebuilding4) && (alt_check < Get_Time()))
		{
			alt_check = Get_Time() + 10.0f;
			silo2 = CountUnitsNearObject(last_geyser, 400, 2, "absilo");
			if (silo2 == 1)
			{
				rebuild4_prep = false;
				rebuilding4 = false;
			}
		}

		if ((rebuilding5) && (alt_check < Get_Time()))
		{
			alt_check = Get_Time() + 10.0f;
			power2 = CountUnitsNearObject(last_geyser, 400, 2, "abwpow");
			if (power2 == 1)
			{
				rebuild5_prep = false;
				rebuilding5 = false;
			}
		}

		if ((rebuilding6) && (alt_check < Get_Time()))
		{
			alt_check = Get_Time() + 10.0f;
			tower2 = CountUnitsNearObject(last_geyser, 400, 2, "abtowe");
			if (tower2 == 1)
			{
				rebuild6_prep = false;
				rebuilding6 = false;
			}
		}
	}
 }


 // this is the attemp at the tank encounter

	if ((plan_c) && (!recycle_message))
	{
		if ((IsAlive(sav1)) || (IsAlive(sav2)) || (IsAlive(sav3)) || (IsAlive(sav4)) || (IsAlive(sav5)) || (IsAlive(sav6)))
		{
			AudioMessage("misns816.wav");
			savs_alive = true;
			recycle_message = true;
		}
		else
		{
			AudioMessage("misns815.wav");
			recycle_message = true;
		}
	}

	if ((plan_c) && (!general_spawn))	
	{
		key_tank = BuildObject ("svtank", 1, "romeski_spawn");

		if (IsAlive(avrecycle))
		{
			SetPerceivedTeam(avrecycle, 1);
			Follow(key_tank, sv_geyser, 1);
		}

		if (IsAlive(basetower1))
		{
			SetPerceivedTeam(basetower1, 1);
		}
		if (IsAlive(basetower2))
		{
			SetPerceivedTeam(basetower2, 1);
		}
		if (IsAlive(avtower1))
		{
			SetPerceivedTeam(avtower1, 1);
		}
		if (IsAlive(powerplant1))
		{
			SetPerceivedTeam(powerplant1, 1);
		}
		if (IsAlive(powerplant2))
		{
			SetPerceivedTeam(powerplant2, 1);
		}
		if (IsAlive(avpower1))
		{
			SetPerceivedTeam(avpower1, 1);
		}
			if (IsAlive(avmuf))
		{
			SetPerceivedTeam(avmuf, 1);
		}	

		pay_off = Get_Time() + 5.0f; // for big finish
		sav_check = Get_Time() + 10.0f;
		general_spawn = true;
	}

	if ((general_spawn) && (!general_message1) && (pay_off < Get_Time()))
	{
		pay_off = Get_Time() + 2.0f;

		if ((IsAlive(key_tank)) && (GetDistance(user, key_tank) < 150.0f))
		{
			SetObjectiveOn(key_tank);
			SetObjectiveName(key_tank, "Romeski");
			
			if (!sav_payback)
			{
//				AudioMessage("win.wav"); //glad you could make it commander now watch as I destroy the recycler
				Attack(key_tank, avrecycle, 1);
			}

			general_message1 = true;
		}
	}

/*
	// this sends savs to recycler when there is no romeski
	if ((recycle_message) && (IsAlive(avrecycle)) && (!general_spawn))
	{
		if ((!sav1_lost) && (IsAlive(sav1)))
		{
			Follow(sav1, avrecycle, 1);
			sav1_lost = true;
			if ((!savs_alive) && (!general_dead))
			{
				AudioMessage("misns807.wav");
				savs_alive = true;
			}
		}
		if ((!sav2_lost) && (IsAlive(sav2)))
		{
			Follow(sav2, avrecycle, 1);
			sav2_lost = true;
			if ((!savs_alive) && (!general_dead))
			{
				AudioMessage("misns807.wav");
				savs_alive = true;
			}
		}
		if ((!sav3_lost) && (IsAlive(sav3)))
		{
			Follow(sav3, avrecycle, 1);
			sav3_lost = true;
			if ((!savs_alive) && (!general_dead))
			{
				AudioMessage("misns807.wav");
				savs_alive = true;
			}
		}
		if ((!sav4_lost) && (IsAlive(sav4)))
		{
			Follow(sav4, avrecycle, 1);
			sav4_lost = true;
			if ((!savs_alive) && (!general_dead))
			{
				AudioMessage("misns807.wav");
				savs_alive = true;
			}
		}
		if ((!sav5_lost) && (IsAlive(sav5)))
		{
			Follow(sav5, avrecycle, 1);
			sav5_lost = true;
			if ((!savs_alive) && (!general_dead))
			{
				AudioMessage("misns807.wav");
				savs_alive = true;
			}
		}
		if ((!sav6_lost) && (IsAlive(sav6)))
		{
			Follow(sav6, avrecycle, 1);
			sav6_lost = true;
			if ((!savs_alive) && (!general_dead))
			{
				AudioMessage("misns807.wav");
				savs_alive = true;
			}
		}
	}
*/
	if ((general_spawn) && (IsAlive(key_tank)))
	{
		if ((!sav1_togeneral) && (IsAlive(sav1)))
		{
			Follow(sav1, key_tank, 1);
			sav1_togeneral = true;

			if ((!savs_alive) && (!general_dead))
			{
				AudioMessage("misns807.wav");
				savs_alive = true;
			}
		}
		if ((!sav2_togeneral) && (IsAlive(sav2)))
		{
			Follow(sav2, key_tank, 1);
			sav2_togeneral = true;

			if ((!savs_alive) && (!general_dead))
			{
				AudioMessage("misns807.wav");
				savs_alive = true;
			}
		}
		if ((!sav3_togeneral) && (IsAlive(sav3)))
		{
			Follow(sav3, key_tank, 1);
			sav3_togeneral = true;

			if ((!savs_alive) && (!general_dead))
			{
				AudioMessage("misns807.wav");
				savs_alive = true;
			}
		}
		if ((!sav4_togeneral) && (IsAlive(sav4)))
		{
			Follow(sav4, key_tank, 1);
			sav4_togeneral = true;

			if ((!savs_alive) && (!general_dead))
			{
				AudioMessage("misns807.wav");
				savs_alive = true;
			}
		}
		if ((!sav5_togeneral) && (IsAlive(sav5)))
		{
			Follow(sav5, key_tank, 1);
			sav5_togeneral = true;

			if ((!savs_alive) && (!general_dead))
			{
				AudioMessage("misns807.wav");
				savs_alive = true;
			}
		}
		if ((!sav6_togeneral) && (IsAlive(sav6)))
		{
			Follow(sav6, key_tank, 1);
			sav6_togeneral = true;

			if ((!savs_alive) && (!general_dead))
			{
				AudioMessage("misns807.wav");
				savs_alive = true;
			}
		}
	}


	if (sav_check < Get_Time())
	{
		sav_check = Get_Time() + 10.0f;

		if ((IsAlive(sav1)) && (sav1_togeneral) && (!sav1_attack))
		{
			if ((IsAlive(key_tank)) && (GetDistance(sav1, key_tank) < 200.0f))
			{
//				Defend(key_tank);
				Attack(sav1, key_tank, 1);
				sav_attack = true;
				sav1_attack = true;
			}
		}
		if ((IsAlive(sav2)) && (sav2_togeneral) && (!sav2_attack))
		{
			if ((IsAlive(key_tank)) && (GetDistance(sav2, key_tank) < 200.0f))
			{
//				Defend(key_tank);
				Attack(sav2, key_tank, 1);
				sav_attack = true;
				sav2_attack = true;
			}
		}
		if ((IsAlive(sav3)) && (sav3_togeneral) && (!sav3_attack))
		{
			if ((IsAlive(key_tank)) && (GetDistance(sav3, key_tank) < 200.0f))
			{
//				Defend(key_tank);
				Attack(sav3, key_tank, 1);
				sav_attack = true;
				sav3_attack = true;
			}
		}
		if ((IsAlive(sav4)) && (sav4_togeneral) && (!sav4_attack))
		{
			if ((IsAlive(key_tank)) && (GetDistance(sav4, key_tank) < 200.0f))
			{
//				Defend(key_tank);
				Attack(sav4, key_tank, 1);
				sav_attack = true;
				sav4_attack = true;
			}
		}
		if ((IsAlive(sav5)) && (sav5_togeneral) && (!sav5_attack))
		{
			if ((IsAlive(key_tank)) && (GetDistance(sav5, key_tank) < 200.0f))
			{
//				Defend(key_tank);
				Attack(sav5, key_tank, 1);
				sav_attack = true;
				sav5_attack = true;
			}
		}
		if ((IsAlive(sav6)) && (sav6_togeneral) && (!sav6_attack))
		{
			if ((IsAlive(key_tank)) && (GetDistance(sav6, key_tank) < 200.0f))
			{
//				Defend(key_tank);
				Attack(sav6, key_tank, 1);
				sav_attack = true;
				sav6_attack = true;
			}
		}
	}

	if (((sav1_togeneral) || (sav2_togeneral) || (sav3_togeneral) ||
		(sav4_togeneral) || (sav5_togeneral) || (sav6_togeneral)) && (!danger_message))
	{
		AudioMessage("misns805.wav");
		AudioMessage("misns818.wav");
		danger_message = true;
	}




// this gives romeski health
	if ((IsAlive(key_tank)) && (!key_open))
	{
		if (GetTime() > next_second2)
		{
			GameObjectHandle::GetObj(key_tank)->AddHealth(300.0f);
			next_second2 = GetTime() + 1.0f;
		}				
	}


// this determines who shot him

	// if the decision hasn't been made...
	if ((!player_payback) && (!sav_payback))
	{
		// the player
		if (IsAlive(key_tank))
		{
			// who shot this vehicle?
			int shot_by = GameObjectHandle::GetObj(key_tank)->GetWhoTheHellShotMe();

			if (shot_by != 0)
			{
				// if the player shot him...
				if (user == shot_by)
				{
					// "want to attack me huh?! We'll see."
					AudioMessage("misns819.wav"); 
					Attack(key_tank, user, 1);
					key_open = true;
					player_payback = true;
				}
				else
				// did an SAV shoot it?
				if (
					(badsav1 == shot_by) ||
					(badsav2 == shot_by) ||
					(badsav3 == shot_by) ||
					(badsav4 == shot_by) ||
					(badsav5 == shot_by) ||
					(badsav6 == shot_by))
				{
					// "help me!"
	//				AudioMessage("misns817.wav");
					help_me_check = GetTime() + 5.0f;
					key_open = true;
					sav_payback = true;
				}
			}
		}
	}

	if ((sav_payback) && (!general_message3) && (IsAlive(key_tank)) && 
		(GameObjectHandle::GetObj(key_tank)->GetHealth() < 0.80f) && (!general_message2))
	{
		AudioMessage("misns817.wav");
		general_message3 = true;
	}
	
// romeski is attacked by savs and them gets close to player he asks for help
	if ((sav_payback) && (!general_message2) && (help_me_check < GetTime()))
	{
		help_me_check = GetTime() + 3.0f;

		if ((IsAlive(key_tank)) && (GetDistance(key_tank, user) < 130.0f))
		{
			Follow(key_tank, user, 1);
			AudioMessage("misns810.wav");
			general_message2 = true;
		}
	}


// this is killing Romeski
	if ((IsAlive(key_tank)) && (!general_scream))
	{
		if ((GameObjectHandle::GetObj(key_tank)->GetHealth() < 0.10f))
		{
			AudioMessage("misns812.wav");
			damage_time = Get_Time() + 3.0f;
			general_scream = true;				
		}
	}

	if ((general_scream) && (damage_time < Get_Time()) && (!general_dead))
	{
		if (IsAlive(key_tank))
		{
			Damage(key_tank, 1000);
			general_dead = true;
		}
		else
		{
			general_dead = true;
		}
	}



	if ((general_spawn) && ((!IsAlive(key_tank)) || (sav_attack)))
	{
		if ((!sav1_swap) && (IsAlive(sav1)))
		{
			badsav1 = BuildObject("savs8", 2, sav1);
			SetIndependence(badsav1, 1);
			RemoveObject(sav1);

			if (IsAlive(key_tank))
			{
				Attack(badsav1, key_tank, 1);
			}

			if (!danger_message)
			{
				AudioMessage("misns805.wav");
				danger_message = true;
			}

			sav1_swap = true;
		}

		if ((!sav2_swap) && (IsAlive(sav2)))
		{
			badsav2 = BuildObject("savs8", 2, sav2);
			SetIndependence(badsav2, 1);
			RemoveObject(sav2);

			if (IsAlive(key_tank))
			{
				Attack(badsav2, key_tank, 1);
			}

			if (!danger_message)
			{
				AudioMessage("misns805.wav");
				danger_message = true;
			}

			sav2_swap = true;
		}

		if ((!sav3_swap) && (IsAlive(sav3)))
		{
			badsav3 = BuildObject("savs8", 2, sav3);
			SetIndependence(badsav3, 1);
			RemoveObject(sav3);

			if (IsAlive(key_tank))
			{
				Attack(badsav3, key_tank, 1);
			}

			if (!danger_message)
			{
				AudioMessage("misns805.wav");
				danger_message = true;
			}

			sav3_swap = true;
		}

		if ((!sav4_swap) && (IsAlive(sav4)))
		{
			badsav4 = BuildObject("savs8", 2, sav4);
			SetIndependence(badsav4, 1);
			RemoveObject(sav4);

			if (IsAlive(key_tank))
			{
				Attack(badsav4, key_tank, 1);
			}

			if (!danger_message)
			{
				AudioMessage("misns805.wav");
				danger_message = true;
			}

			sav4_swap = true;
		}

		if ((!sav5_swap) && (IsAlive(sav5)))
		{
			badsav5 = BuildObject("savs8", 2, sav5);
			SetIndependence(badsav5, 1);
			RemoveObject(sav5);

			if (IsAlive(key_tank))
			{
				Attack(badsav5, key_tank, 1);
			}

			if (!danger_message)
			{
				AudioMessage("misns805.wav");
				danger_message = true;
			}

			sav5_swap = true;
		}

		if ((!sav6_swap) && (IsAlive(sav6)))
		{
			badsav6 = BuildObject("savs8", 2, sav6);
			SetIndependence(badsav6, 1);
			RemoveObject(sav6);

			if (IsAlive(key_tank))
			{
				Attack(badsav6, key_tank, 1);
			}

			if (!danger_message)
			{
				AudioMessage("misns805.wav");
				danger_message = true;
			}

			sav6_swap = true;
		}
	}


// win/ loose conditions

	if ((!IsAlive(avrecycle)) && (!game_over))
	{
		if (IsAlive(badsav1))
		{
			Goto(badsav1, first_geyser, 1);
		}
		if (IsAlive(badsav2))
		{
			Goto(badsav2, first_geyser, 1);
		}
		if (IsAlive(badsav3))
		{
			Goto(badsav3, first_geyser, 1);
		}
		if (IsAlive(badsav4))
		{
			Goto(badsav4, first_geyser, 1);
		}
		if (IsAlive(badsav5))
		{
			Goto(badsav5, first_geyser, 1);
		}
		if (IsAlive(badsav6))
		{
			Goto(badsav6, first_geyser, 1);
		}
		if (IsAlive(key_tank))
		{
			AudioMessage("misns803.wav"); // congradulations
			AudioMessage("misns808.wav");
			SucceedMission(Get_Time() + 35.0f, "misns8w1.des");
			game_over = true;
		}
		else
		{
			AudioMessage("misns814.wav");
			SucceedMission(Get_Time() + 25.0f, "misns8w1.des");
			game_over = true;
		}
	}
}
