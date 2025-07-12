#include "GameCommon.h"

#include "..\fun3d\AiMission.h"
#include "..\fun3d\PowerUp.h"
#include "..\fun3d\ScriptUtils.h"

/*
	Misn12Mission
*/

class Misn12Mission : public AiMission {
	DECLARE_RTIME(Misn12Mission)
public:
	Misn12Mission(void);
	~Misn12Mission();

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
				check_point1_done,
				check_point2_done,
				check_point3_done,
				check_point4_done,
				check_point5_done,
				check1,
				check2,
				check3,
				check4,
				objective1,
				out_of_order1,
				out_of_order2,
				out_of_order3,
				out_of_order4,
				out_of_order5,
				interface_connect,
				link_broken,
				interface_complete,
				warning_message,
				cca_message1,
				cca_message2,
				cca_message3,
				cca_message4,
				identify_message,
				cca_warning_message,
				better_message,
				real_bad,
				enter_base,
				did_it_right,
				straight_to_5,
				discovered,
				noise,
				camera_on,
				camera_off,
				camera1,
				camera2,
				camera3,
				camera4,
				camera5,
				key_captured,
				over,
				checked_in, going_again, key_gone,
				game_blown,
				final_warned, last_warned,
				follow_spawn,
				good1, good2, good3,
				good1_off, good2_off, good3_off, dead_meat,
				patrol1_create, patrol2_create, patrol3_create, patrol4_create,
				patrol1_moved1, patrol2_moved1, patrol3_moved1, patrol4_moved1,
				patrol1_moved2, patrol2_moved2, patrol3_moved2, patrol4_moved2,
				patrol1_1_gone, patrol1_2_gone, patrol2_1_gone, patrol2_2_gone,
				patrol3_1_gone, patrol3_2_gone, patrol4_1_gone, patrol4_2_gone,
				p1_1center, p2_1center, p2_2center, p3_1center, p3_2center, p4_1center, p4_2center,
				win, game_over, camera_swap1, camera_swap2, camera_swap_back, out_of_ship,
				camera_noise, blown_otf, grump,
				b_last;
		};
		bool b_array[92];
	};

	// floats
	union {
		struct {
			float
				countdown_time,
				interface_time,
				warning_repeat_time,
				next_message_time,
				next_noise_time,
				camera_time,
				camera_on_time,
				win_check_time,
				start_patrol,
				key_check,
				wait_time,
				key_remove,
				death_spawn,
				final_warning, last_warning,
				remove_patrol1_2,
				patrol1_1_time, patrol1_2_time, patrol2_1_time, patrol2_2_time,
				patrol3_1_time, patrol3_2_time, patrol4_1_time, patrol4_2_time,
				swap_check, next_second, grump_time,
				f_last;
		};
		float f_array[27];
	};

	// handles
	union {
		struct {
			Handle
				user, user_tank, center,
				center_cam, start_cam, check2_cam, check3_cam, check4_cam, goal_cam,
				nav1,
				key_ship,
				spawn_geyser, choke_geyser, check2_geyser, center_geyser,
				checkpoint1, checkpoint2, checkpoint3, checkpoint4,
				ccacom_tower,
				ccasilo1, ccasilo2, ccasilo3, ccasilo4,
				guard1, guard2, guard3, guard4,
				spawn_point1, spawn_point2,
				guard_fighter, parked_fighter,
				parked_tank1, parked_tank2,
				guard_turret, pturret1, pturret2, pturret3, pturret4, pturret5, pturret6,
				patrol1_1, patrol1_2,
				patrol2_1, patrol2_2,
				patrol3_1, patrol3_2,
				patrol4_1, patrol4_2,
				guard_tank1, guard_tank2,
				death_squad1, death_squad2, death_squad3, death_squad4,
				follower,
				ccamuf,
				h_last;
		};
		Handle h_array[57];
	};

	// integers
	union {
		struct {
			int
				audmsg,
				i_last;
		};
		int i_array[1];
	};
};

IMPLEMENT_RTIME(Misn12Mission)

Misn12Mission::Misn12Mission(void)
{
}

Misn12Mission::~Misn12Mission()
{
}

void Misn12Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

bool Misn12Mission::Load(file fp)
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

bool Misn12Mission::PostLoad(void)
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

bool Misn12Mission::Save(file fp)
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

void Misn12Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

void Misn12Mission::Setup(void)
{
/* Here's where you set the values at the start. */

	start_done = false;
	key_captured = false;
	check_point1_done = false;
	check_point2_done = false;
	check_point3_done = false;
	check_point4_done = false;
	check_point5_done = false;
	check1 = false;
	check2 = false;
	check3 = false;
	check4 = false;
	objective1 = false;
	out_of_order1 = false;
	out_of_order2 = false;
	out_of_order3 = false;
	out_of_order4 = false;
	out_of_order5 = false;
	interface_connect = false;
	link_broken = false;
	interface_complete = false;
	warning_message = false;
	cca_message1 = false;
	cca_message2 = false;
	cca_message3 = false;
	cca_message4 = false;
	enter_base = false;
	did_it_right = false;
	discovered = false;
	straight_to_5 = false;
	noise = false;
	camera_on = false;
	camera_off = false;
	camera1 = false;
	camera2 = false;
	camera3 = false;
	camera4 = false;
	camera5 = false;
	win = false;
	checked_in = false;

	identify_message = false;
	cca_warning_message = false;
	better_message = false;
	real_bad = false;
	over = false;
	going_again = false;
	key_gone = false;
	game_blown = false;
	final_warned = false;
	last_warned = false;
	follow_spawn = false;
	good1 = false;
	good2 = false;
	good3 = false;
	good1_off = false;
	good2_off = false;
	good3_off = false;
	dead_meat = false;
	patrol1_create = false;
	patrol2_create = false;
	patrol3_create = false;
	patrol4_create = false;
	patrol1_moved1 = false;
	patrol2_moved1 = false;
	patrol3_moved1 = false;
	patrol4_moved1 = false;
	patrol1_moved2 = false;
	patrol2_moved2 = false;
	patrol3_moved2 = false;
	patrol4_moved2 = false;
	patrol1_1_gone = false;
	patrol1_2_gone = false;
	patrol2_1_gone = false;
	patrol2_2_gone = false;
	patrol3_1_gone = false;
	patrol3_2_gone = false;
	patrol4_1_gone = false;
	patrol4_2_gone = false;
	p1_1center = false;
	p2_1center = false;
	p2_2center = false;
	p3_1center = false;
	p3_2center = false;
	p4_1center = false;
	p4_2center = false;
	game_over = false;
	camera_swap1 = false;
	camera_swap2 = false;
	camera_swap_back = false;
	camera_noise = false;
	out_of_ship = false;
	blown_otf = false;
	grump = false;

	warning_repeat_time = 99999.0f;
	countdown_time = 99999.0f;
	camera_on_time = 99999.0f;
	interface_time = 99999.0f;
	next_noise_time = 99999.0f;
	camera_time = 99999.0f;
	next_message_time = 99999.0f;
	win_check_time = 99999.0f;
	start_patrol = 99999.0f;
	key_check = 99999.0f;
	wait_time = 99999.0f;
	key_remove = 99999.0f;
	death_spawn = 99999.0f;
	final_warning = 99999.0f;
	last_warning = 99999.0f;
	remove_patrol1_2 = 99999.0f;
	patrol1_1_time = 99999.0f;
	patrol1_2_time = 99999.0f;
	patrol2_1_time = 99999.0f;
	patrol2_2_time = 99999.0f;
	patrol3_1_time = 99999.0f;
	patrol3_2_time = 99999.0f;
	patrol4_1_time = 99999.0f;
	patrol4_2_time = 99999.0f;
	swap_check = 99999.0f;
	grump_time = 99999.0f;
	next_second = 0;


	key_ship = NULL;
	checkpoint1 = GetHandle("checktower1");
	checkpoint2 = GetHandle("svguntower2");
	checkpoint3 = GetHandle("svmuf");
	checkpoint4 = GetHandle("svsilo1");
	center = GetHandle("center");
//	ccasilo1 = GetHandle ("svsilo1");
	ccasilo2 = GetHandle ("svsilo2");
	ccasilo3 = GetHandle ("svsilo3");
	ccasilo4 = GetHandle ("svsilo4");
	ccamuf = GetHandle("svmuf");
	ccacom_tower = GetHandle("svcom_tower");
	spawn_point1 = GetHandle("spawn_geyser1");
	spawn_point2 = GetHandle("spawn_geyser2");
	nav1 = GetHandle("apcamr20_camerapod");
	spawn_geyser = GetHandle("spawn_geyser");
	choke_geyser = GetHandle("choke_geyser");
	check2_geyser = GetHandle("check2_geyser");
	center_geyser = GetHandle("center_geyser");
	guard_fighter = GetHandle("pfighter2");
	parked_fighter = GetHandle("pfighter1");
	parked_tank2 = GetHandle("ptank2");
	parked_tank1 = GetHandle("ptank1");
	guard_turret = GetHandle("turret6");
	pturret1 = GetHandle("turret1");
	pturret2 = GetHandle("turret2");
	pturret3 = GetHandle("turret3");
	pturret4 = GetHandle("turret4");
	pturret5 = GetHandle("turret5");
	pturret6 = GetHandle("turret6");
	patrol1_1 = GetHandle("svfigh1_1");
	patrol1_2 = GetHandle("svfigh1_2");
	patrol2_1 = GetHandle("svfigh2_1");
	patrol2_2 = GetHandle("svfigh2_2");
	patrol3_1 = GetHandle("svfigh3_1");
	patrol3_2 = GetHandle("svfigh3_2");
	patrol4_1 = GetHandle("svfigh4_1");
	patrol4_2 = GetHandle("svfigh4_2");
	guard_tank1 = GetHandle("gtank1");
	guard_tank2 = GetHandle("gtank2");
	follower = NULL;
	death_squad1 = NULL;
	death_squad2 = NULL;
	death_squad3 = NULL;
	death_squad4 = NULL;
	guard1 = NULL;
	guard2 = NULL;
	guard3 = NULL;
	guard4 = NULL;
	center_cam = NULL;
	start_cam = NULL;
	check2_cam = NULL;
	check3_cam = NULL;
	check4_cam = NULL;
	goal_cam = NULL;


}

void Misn12Mission::AddObject(Handle h)
{
}

static bool IsVehicleAlive(Handle h)
{
	return GameObjectHandle::GetObj(h) != NULL;
}

void Misn12Mission::Execute(void)
{

// START OF SCRIPT

	user = GetPlayerHandle(); //assigns the player a handle every frame

	if (!start_done)
	{
		AudioMessage("misn1200.wav"); 
		user_tank = GetPlayerHandle(); // this assigns the tank a handle
//		Defend(key_ship);
		ClearObjectives();
		AddObjective("misn1200.otf", WHITE);
		Defend(guard_tank1);
		Defend(guard_tank2);
		Defend(patrol1_1);
		Defend(patrol1_2);
		Defend(patrol2_1);
		Defend(patrol2_2);
		Defend(patrol3_1);
		Defend(patrol3_2);
		Defend(patrol4_1);
		Defend(patrol4_2);
		StartCockpitTimer(1200, 300, 120);

		SetObjectiveOn(checkpoint1);
		SetObjectiveName(checkpoint1, "Check Point");

		center_cam = BuildObject ("apcamr", 3, "center_cam");
		start_cam = BuildObject ("apcamr", 3, "start_cam");
		check2_cam = BuildObject ("apcamr", 3, "check2_cam");
		check3_cam = BuildObject ("apcamr", 3, "check3_cam");
		check4_cam = BuildObject ("apcamr", 3, "check4_cam");
		goal_cam = BuildObject ("apcamr", 3, "goal_cam");

		key_ship = BuildObject("svfi12", 2, spawn_geyser);
		SetWeaponMask(key_ship, 3);
		Goto(key_ship, "first_path"); // gets the patrol ship to move towards checkpoint1
		key_check = Get_Time() + 2.0f;

		CameraReady();
		camera_time = Get_Time() + 12.0f;

		if (nav1!=NULL) GameObjectHandle::GetObj(nav1)->SetName("Drop Zone");
		start_done = true;
	}


	if (IsAlive(ccacom_tower))
	{
		if (GetTime()>next_second)
		{
			GameObjectHandle::GetObj(ccacom_tower)->AddHealth(200.0f);
			next_second = GetTime() + 1.0f;
		}
	}


// this what happens if the player is discovered before taking over the ship

	if ((!game_blown) && (!key_captured))
	{ 
		if ((IsAlive(user_tank)) && (GameObjectHandle::GetObj(user_tank)->GetHealth()< 0.90f))
		{
			AudioMessage("misn1213.wav");
			death_spawn = Get_Time() + 5.0f;
			game_blown = true;
		}
	}

	if (IsVehicleAlive(key_ship))
	{
		if ((!game_blown) && (!key_captured) && (GameObjectHandle::GetObj(key_ship)->GetHealth()< 0.50f))
		{
			AudioMessage("misn1228.wav");
			death_spawn = Get_Time() + 5.0f;
			game_blown = true;
		}
	}

// this is what happens is the player tries to get in with his tank

	if ((IsAlive(user_tank)) && (GetDistance(user_tank, checkpoint1) < 75.0f) && (!key_captured) && (!game_blown))
	{
		AudioMessage("misn1213.wav");
		death_spawn = Get_Time() + 5.0f;
		ClearObjectives();
		AddObjective("misn1200.otf", RED);
		game_blown = true;
	}

	// this is game_blown code
	if ((game_blown) && (death_spawn < Get_Time()))
	{
		death_spawn = Get_Time() + 120.0f;
		death_squad1 = BuildObject("svfigh", 2, spawn_geyser);
		death_squad2 = BuildObject("svfigh", 2, spawn_geyser);
		death_squad3 = BuildObject("svltnk", 2, spawn_geyser);
		death_squad4 = BuildObject("svltnk", 2, spawn_geyser);
		Attack(death_squad1, user);
		Attack(death_squad2, user);
		Attack(death_squad3, user);
		Attack(death_squad4, user);
	}

	if ((game_blown) && (!IsAlive(user_tank)) && (!dead_meat))
	{
		SetPerceivedTeam(user, 1);
		dead_meat = true;
	}


// this is the start of the camera during the players briefing

	if ((start_done) && (!camera4))
	{
		CameraPath("start_camera_path", 4000, 900, ccacom_tower);
	}

	if (((CameraCancelled()) ||
		(camera_time < Get_Time())) && (!camera4))
	{
		CameraFinish();
		camera4 = true;
	}

// this is the start of patroling the cca ships

	if ((camera_off) && (!patrol1_create)) // change start_done to key_captured
	{
		Goto(patrol1_1, "path1_to");
		Goto(patrol1_2, "path1_to");
		patrol1_create = true;
	}

	if ((patrol1_create) && (IsAlive(patrol1_1)) 
		&& (GetDistance(patrol1_1, checkpoint1) < 50.0f) && (!patrol1_moved1))
	{
		if ((IsAlive(patrol1_2) && (GetDistance(patrol1_2, checkpoint1) < 70.0f)))
		{
			Goto(patrol1_1, "path1_from");
			Goto(patrol1_2, "path1_from");
			patrol1_moved1 = true;
		}
	}

	if ((patrol1_moved1) && (IsAlive(patrol1_1))
		&& (GetDistance(patrol1_1, center_geyser) < 50.0f) && (!patrol1_moved2))
	{
		if ((IsAlive(patrol1_2) && (GetDistance(patrol1_2, center_geyser) < 50.0f)))
		{
			Goto(patrol1_1, "path2");
			Patrol(patrol1_2, "path5");
			Goto(patrol2_1, "path3");
			patrol2_1_time = Get_Time() + 15.0f;
			patrol1_moved2 = true;
		}
	}


// move 2_2
	if ((patrol1_moved2) && (IsAlive(patrol1_1)) 
		&& (GetDistance(patrol1_1, check2_geyser) < 400.0f) && (!patrol2_moved1))
	{
		Goto(patrol2_2, "path2");
		Goto(patrol4_1, "path4");
		p4_1center = true;
		patrol2_2_time = Get_Time() + 11.0f;
		patrol1_1_time = Get_Time() + 10.0f;
		patrol4_1_time = Get_Time() + 12.0f;
		patrol2_moved1 = true;
	}


// send 3_1 on route
	
	if ((IsAlive(patrol2_1)) && (GetDistance(patrol2_1, ccamuf) < 400.0f) && (!patrol3_moved1))
	{
		Goto(patrol3_1, "path4");
		patrol3_1_time = Get_Time() + 5.0f;
		p3_1center = true;
		patrol3_moved1 = true;
	}

// send 3_2 on route

	if ((IsAlive(patrol2_2)) && (GetDistance(patrol2_2, ccamuf) < 400.0f) && (!patrol3_moved2))
	{
		Goto(patrol3_2, "path4");
		p3_2center = true;
		patrol3_2_time = Get_Time() + 10.0f;
		patrol3_moved2 = true;
	}
// send 4_2
	if ((IsAlive(patrol3_1)) && (GetDistance(patrol3_1, checkpoint4) < 400.0f) && (!patrol4_moved2))
	{
		Goto(patrol4_2, "path4");
		patrol4_2_time = Get_Time() + 5.0f;
		p4_2center = true;
		patrol4_moved2 = true;
	}


// check patrols
if ((!real_bad) || (!game_blown))
{
	// 1_1
	if ((IsAlive(patrol1_1)) && (patrol1_1_time < Get_Time()))
	{
		patrol1_1_time = Get_Time() + 10.0f;
			
		if ((!p1_1center) && (GetDistance(patrol1_1, center_geyser) < 50.0f))
		{
			Goto(patrol1_1, "path3");
			p1_1center = true;
		}
		else
		{
			if (GetDistance(patrol1_1, center_geyser) < 50.0f)
			{
				Goto(patrol1_1, "path2");
				p1_1center = false;
			}
			else
			{
				if (GetDistance(patrol1_1, ccamuf) < 70.0f)
				{
					Goto(patrol1_1, "path4");
				}
			}	
		}
	}
	// 2_1
	if ((IsAlive(patrol2_1)) && (patrol2_1_time < Get_Time()))
	{
		patrol2_1_time = Get_Time() + 10.0f;
			
		if ((!p2_1center) && (GetDistance(patrol2_1, center_geyser) < 50.0f))
		{
			Goto(patrol1_1, "path3");
			p2_1center = true;
		}
		else
		{
			if (GetDistance(patrol2_1, center_geyser) < 50.0f)
			{
				Goto(patrol2_1, "path2");
				p2_1center = false;
			}
			else
			{
				if (GetDistance(patrol2_1, ccamuf) < 70.0f)
				{
					Goto(patrol2_1, "path4");
				}
			}	
		}
	}
	// 2_2
	if ((IsAlive(patrol2_2)) && (patrol2_2_time < Get_Time()))
	{
		patrol2_2_time = Get_Time() + 10.0f;
			
		if ((!p2_2center) && (GetDistance(patrol2_2, center_geyser) < 50.0f))
		{
			Goto(patrol2_2, "path3");
			p2_2center = true;
		}
		else
		{
			if (GetDistance(patrol2_2, center_geyser) < 50.0f)
			{
				Goto(patrol2_2, "path2");
				p2_2center = false;
			}
			else
			{
				if (GetDistance(patrol2_2, ccamuf) < 70.0f)
				{
					Goto(patrol2_2, "path4");
				}
			}	
		}
	}
	//3_1
	if ((IsAlive(patrol3_1)) && (patrol3_1_time < Get_Time()))
	{
		patrol3_1_time = Get_Time() + 10.0f;
			
		if ((!p3_1center) && (GetDistance(patrol3_1, center_geyser) < 50.0f))
		{
			Goto(patrol3_1, "path3");
			p3_1center = true;
		}
		else
		{
			if (GetDistance(patrol3_1, center_geyser) < 50.0f)
			{
				Goto(patrol3_1, "path2");
				p3_1center = false;
			}
			else
			{
				if (GetDistance(patrol3_1, ccamuf) < 70.0f)
				{
					Goto(patrol3_1, "path4");
				}
			}	
		}
	}
	//3_2
	if ((IsAlive(patrol3_2)) && (patrol3_2_time < Get_Time()))
	{
		patrol3_2_time = Get_Time() + 10.0f;
			
		if ((!p3_2center) && (GetDistance(patrol3_2, center_geyser) < 50.0f))
		{
			Goto(patrol3_2, "path3");
			p3_2center = true;
		}
		else
		{
			if (GetDistance(patrol3_2, center_geyser) < 50.0f)
			{
				Goto(patrol3_2, "path2");
				p3_2center = false;
			}
			else
			{
				if (GetDistance(patrol3_2, ccamuf) < 70.0f)
				{
					Goto(patrol3_2, "path4");
				}
			}	
		}
	}
	//4_1
	if ((IsAlive(patrol4_1)) && (patrol4_1_time < Get_Time()))
	{
		patrol4_1_time = Get_Time() + 10.0f;
			
		if ((!p4_1center) && (GetDistance(patrol4_1, center_geyser) < 50.0f))
		{
			Goto(patrol4_1, "path3");
			p4_1center = true;
		}
		else
		{
			if (GetDistance(patrol4_1, center_geyser) < 50.0f)
			{
				Goto(patrol4_1, "path2");
				p4_1center = false;
			}
			else
			{
				if (GetDistance(patrol4_1, ccamuf) < 70.0f)
				{
					Goto(patrol4_1, "path4");
				}
			}	
		}
	}
	//4_2
	if ((IsAlive(patrol4_2)) && (patrol4_2_time < Get_Time()))
	{
		patrol4_2_time = Get_Time() + 10.0f;
			
		if ((!p4_2center) && (GetDistance(patrol4_2, center_geyser) < 50.0f))
		{
			Goto(patrol4_2, "path3");
			p4_2center = true;
		}
		else
		{
			if (GetDistance(patrol4_2, center_geyser) < 50.0f)
			{
				Goto(patrol4_2, "path2");
				p4_2center = false;
			}
			else
			{
				if (GetDistance(patrol4_2, ccamuf) < 70.0f)
				{
					Goto(patrol4_2, "path4");
				}
			}	
		}
	}
}
////////////// THIS ALL FALLS UNDER GAME BLOWN /////////////////////////////////////
if (!game_blown)
{
// this makes the key_ship stop at checkpoint1

	if ((start_done) && (!key_captured) && (!checked_in))
	{
		if (IsVehicleAlive(key_ship))
		{
			if ((GetDistance(key_ship, checkpoint1) < 80.0f))
			{
				Stop(key_ship, 1);
				wait_time = Get_Time() + 20.0f;
				checked_in = true;
			}
		}
	}

	if ((checked_in) && (wait_time < Get_Time()) && (!going_again) && (!key_captured))
	{
		Goto(key_ship, "first_path");
		key_remove = Get_Time() + 10.0f;
		going_again = true;
	}

	if ((going_again) && (key_remove < Get_Time()) && (!key_captured))
	{
		key_remove = Get_Time() + 3.0f;
		
		if (GetDistance(key_ship, spawn_geyser) < 100.0f)
		{
			RemoveObject(key_ship);
			key_ship = BuildObject("svfi12", 2, spawn_geyser);
			SetWeaponMask(key_ship, 3);
			Goto(key_ship, "first_path");
			checked_in = false;
			going_again = false;
		}
	}

// this will indicate when the player has taken over the cca fighter

	if ((IsOdf(user, "svfi12")) && (!key_captured))
	{
		if (IsAlive(user))
		{
			GameObjectHandle::GetObj(user)->AddAmmo(2000.0f);
		}
		ClearObjectives();
		AddObjective("misn1200.otf", GREEN);
		AddObjective("misn1201.otf", WHITE);
		AddObjective("misn1202.otf", WHITE);
		AddObjective("misn1203.otf", WHITE);
		AddObjective("misn1204.otf", WHITE);
		AudioMessage("misn1217.wav");
		camera_time = Get_Time() + 10.0f;

		if (IsAlive(checkpoint1))
		{
			SetObjectiveOff(checkpoint1);
		}

		key_captured = true;
	}

	if ((key_captured) && ((IsOdf(user, "svfigh")) || (IsOdf(user, "svtank"))) && (!out_of_ship))
	{
		out_of_ship = true;
	}

	if ((out_of_ship) && (!grump))
	{
		if (IsAlive(patrol1_1))
		{
			Attack(patrol1_1, user);
		}
		if (IsAlive(patrol1_2))
		{
			Attack(patrol1_2, user);
		}
		if (IsAlive(patrol2_1))
		{
			Attack(patrol2_1, user);
		}
		if (IsAlive(patrol2_2))
		{
			Attack(patrol2_2, user);
		}
		if (IsAlive(patrol3_1))
		{
			Attack(patrol3_1, user);
		}
		if (IsAlive(patrol3_2))
		{
			Attack(patrol3_2, user);
		}
		if (IsAlive(patrol4_1))
		{
			Attack(patrol4_1, user);
		}
		if (IsAlive(patrol4_2))
		{
			Attack(patrol4_2, user);
		}
		if (IsAlive(guard_tank1))
		{
			Attack(guard_tank1, user);
		}
		if (IsAlive(guard_tank2))
		{
			Attack(guard_tank2, user);
		}
		if ((!interface_complete) && (!blown_otf))
		{
			ClearObjectives();
			AddObjective("misn1206.otf", WHITE);
			blown_otf = true;
		}

		grump_time = Get_Time() + 180.0f;
		grump = true;
	}

	if (grump_time < Get_Time())
	{
		grump = false;
	}
// heres where we start the big movie


	if ((key_captured) && (camera_time < Get_Time()) && (!camera_on) && (!camera_off))
	{
		CameraReady();
		camera_on = true;
	}

	if ((camera_on) && (!camera1) && (!camera2) && (!camera3) && (!camera_off))
	{
		CameraObject (checkpoint2, 0, 1000, 6000, checkpoint2);
		audmsg = AudioMessage("misn1218.wav");
		camera_time = Get_Time() + 6.0f;
		camera1 = true;
	}

	if (((camera1) && (!camera2) && (!camera3) && (!camera_off)) 
		&& ((camera_time < Get_Time()) || (CameraCancelled())))
	{
		StopAudioMessage(audmsg);
		CameraObject (checkpoint3, 3000, 3000, 3000, checkpoint3);
		audmsg = AudioMessage("misn1219.wav");
		camera_time = Get_Time() + 6.0f;
		camera2 = true;
	}

	if (((camera2) && (!camera3) && (!camera_off))
		&& ((camera_time < Get_Time()) || (CameraCancelled())))
	{
		StopAudioMessage(audmsg);
		CameraObject (checkpoint4, -1000, 1500, 4000, checkpoint4);
		audmsg = AudioMessage("misn1220.wav");
		camera_time = Get_Time() + 6.0f;
		camera3 = true;
	}

	if (((camera3) && (!camera_off))
		&& ((camera_time < Get_Time()) || (CameraCancelled())))
	{
		StopAudioMessage(audmsg);
		AudioMessage("misn1221.wav");
		AudioMessage("misn1222.wav");
		CameraFinish();
		camera_off = true;
	}


// this is where I script the how the player must check in at each check point

//	if (!check2)
//	{
		if (GetDistance(user, checkpoint2) < 150.0f)
		{
			check_point2_done = true;
		}

		if ((check_point2_done) && (GetDistance(user, checkpoint2) > 150.0f))
		{
			check_point2_done = false;
		}
//	}
	
//	if (!check3)
//	{
		if (GetDistance(user, checkpoint3) < 150.0f)
		{
			check_point3_done = true;
		}

		if ((check_point3_done) && (GetDistance(user, checkpoint3) > 150.0f))
		{
			check_point3_done = false;
		}
//	}

//	if (!check4)
//	{
		if (GetDistance(user, checkpoint4) < 150.0f)
		{
			check_point4_done = true;
		}

		if ((check_point4_done) && (GetDistance(user, checkpoint4) > 150.0f))
		{
			check_point4_done = false;
		}
//	}

	if (GetDistance(user, ccacom_tower) < 150.0f)
	{
		check_point5_done = true;
	}

	if ((check_point5_done) && (GetDistance(user, ccacom_tower) > 150.0f))
	{
		check_point5_done = false;
	}

// the following is if the player does it right
	
	if (!interface_complete)
	{
		if ((GetDistance(user, checkpoint2) < 70.0f) && (!cca_warning_message) 
			&& (!identify_message) && (!check2))			
		{
			CameraReady();
			good1 = true;

			if (good1)
			{
				CameraObject(user, 0, 700, -1500, user);
				camera_time = Get_Time() + 5.0f;
				AudioMessage("misn1207.wav"); // soviet voice that is calm
				ClearObjectives();
				AddObjective("misn1200.otf", GREEN);
				AddObjective("misn1201.otf", GREEN);
				AddObjective("misn1202.otf", WHITE);
				AddObjective("misn1203.otf", WHITE);
				AddObjective("misn1204.otf", WHITE);
				check2 = true;
			}
		}

		if ((good1) && (camera_time < Get_Time()) &&  (!good1_off))
		{
			CameraFinish();
			good1_off = true;
		}


		if ((check2) && (GetDistance(user, checkpoint3) < 70.0f) && (!cca_warning_message) 
			&& (!identify_message) && (!check3))
		{
			CameraReady();
			good2 = true;

			if (good2)
			{
				CameraObject(user, 0, 700, -1500, user);
				camera_time = Get_Time() + 6.0f;
				AudioMessage("misn1208.wav"); // soviet voice that is calm
				ClearObjectives();
				AddObjective("misn1200.otf", GREEN);
				AddObjective("misn1201.otf", GREEN);
				AddObjective("misn1202.otf", GREEN);
				AddObjective("misn1203.otf", WHITE);
				AddObjective("misn1204.otf", WHITE);
				check3 = true;
			}
		}

		if ((good2) && (camera_time < Get_Time()) &&  (!good2_off))
		{
			CameraFinish();
			good2_off = true;
		}


		if ((GetDistance(user, checkpoint4) < 70.0f) && (check3) && (!check4) 
			&& (!cca_warning_message) && (!identify_message))
		{
			CameraReady();
			good3 = true;

			if (good3)
			{
				CameraObject(user, 0, 700, -1500, user);
				camera_time = Get_Time() + 6.0f;
				AudioMessage("misn1209.wav"); // soviet voice that is calm
				ClearObjectives();
				AddObjective("misn1200.otf", GREEN);
				AddObjective("misn1201.otf", GREEN);
				AddObjective("misn1202.otf", GREEN);
				AddObjective("misn1203.otf", GREEN);
				AddObjective("misn1204.otf", WHITE);
				check4 = true;
			}
		}

		if ((good3) && (camera_time < Get_Time()) &&  (!good3_off))
		{
			CameraFinish();
			good3_off = true;
		}
	}

///////////////////////////////////////////////////////////////////////////////////////
// the TWOS

	// if he goes to 2 and then straight to 4
	if ((check2) && (!check3) && (check_point4_done) && (!cca_warning_message) &&
		(!identify_message) && (!real_bad))
	{
		AudioMessage("misn1205.wav"); // your out of order scout - return to you posts
		ClearObjectives();
		AddObjective("misn1200.otf", GREEN);
		AddObjective("misn1201.otf", GREEN);
		AddObjective("misn1202.otf", WHITE);
		AddObjective("misn1203.otf", YELLOW);
		AddObjective("misn1204.otf", WHITE);
		cca_warning_message = true;
	}

		// if he goes to 2 and then 4 and then back to 3 (recovers)
		if ((check2) && (cca_warning_message) && (GetDistance(user, checkpoint3) < 70.0f) 
			&& (!identify_message) && (!real_bad) && (!check4))
		{
			CameraReady();
			good2 = true;

			if (good2)
			{
				CameraObject(user, 0, 700, -1500, user);
				camera_time = Get_Time() + 6.0f;
				AudioMessage("misn1210.wav");  // soviet guy should laugh "you better now"
				ClearObjectives();
				AddObjective("misn1200.otf", GREEN);
				AddObjective("misn1201.otf", GREEN);
				AddObjective("misn1202.otf", GREEN);
				AddObjective("misn1203.otf", GREEN);
				AddObjective("misn1204.otf", WHITE);
				better_message = true;
				check4 = true;
			}
		}

		// if he goes to 2 and then 4 and then back to 2
		if ((check2) && (cca_warning_message) && (!check4) && (check_point2_done) 
			&& (!identify_message) && (!real_bad))
		{
			AudioMessage("misn1206.wav"); // identify yourself!
			next_message_time = Get_Time() + 20.0f;
			ClearObjectives();
			AddObjective("misn1200.otf", GREEN);
			AddObjective("misn1201.otf", GREEN);
			AddObjective("misn1202.otf", WHITE);
			AddObjective("misn1203.otf", RED);
			AddObjective("misn1204.otf", WHITE);
			identify_message = true;
		}


		// this is when he goes to 2 and then 4 and then 5
		if ((check2) && (cca_warning_message) && (!check4) && (check_point5_done)
			&& (!identify_message) && (!real_bad) && (!check4))
		{
			AudioMessage("misn1206.wav"); // identify yourself!
			next_message_time = Get_Time() + 20.0f;
			ClearObjectives();
			AddObjective("misn1200.otf", GREEN);
			AddObjective("misn1201.otf", GREEN);
			AddObjective("misn1202.otf", WHITE);
			AddObjective("misn1203.otf", YELLOW);
			AddObjective("misn1204.otf", RED);
			identify_message = true;
		}

	// if he goes to 2 and then straigh to 5
	if ((check2) && (check_point5_done) && (!check3) && (!cca_warning_message) 
		&& (!identify_message) && (!real_bad))
	{
		AudioMessage("misn1206.wav"); // identify yourself!
		next_message_time = Get_Time() + 20.0f;
		ClearObjectives();
		AddObjective("misn1200.otf", GREEN);
		AddObjective("misn1201.otf", GREEN);
		AddObjective("misn1202.otf", WHITE);
		AddObjective("misn1203.otf", WHITE);
		AddObjective("misn1204.otf", YELLOW);
		identify_message = true;
	}

	// if he goes to 2 and then 3 and then 5
	if ((check3) && (!check4) && (check_point5_done) && (!cca_warning_message) 
		&& (!identify_message) && (!real_bad))
	{
		AudioMessage("misn1206.wav"); // identify yourself!
		next_message_time = Get_Time() + 20.0f;
		ClearObjectives();
		AddObjective("misn1200.otf", GREEN);
		AddObjective("misn1201.otf", GREEN);
		AddObjective("misn1202.otf", GREEN);
		AddObjective("misn1203.otf", WHITE);
		AddObjective("misn1204.otf", YELLOW);
		identify_message = true;
	}

/// the THREES


	// if he goes to 3 before going to 2
	if ((check_point3_done) && (!check2) && (!cca_warning_message) && 
		(!identify_message) && (!better_message) && (!real_bad))
	{
		AudioMessage("misn1205.wav"); // your out of order scout - return to you posts
		ClearObjectives();
		AddObjective("misn1200.otf", GREEN);
		AddObjective("misn1201.otf", WHITE);
		AddObjective("misn1202.otf", YELLOW);
		AddObjective("misn1203.otf", WHITE);
		AddObjective("misn1204.otf", WHITE);
		cca_warning_message = true;
	}

		// if he goes to 3 and then goes back to 2 (recovers)	
		if ((!check2) && (cca_warning_message) && (!identify_message) && (GetDistance(user, checkpoint2) < 70.0f) 
			&& (!better_message)) // doing better 
		{
			CameraReady();
			good1 = true;

			if (good1)
			{
				CameraObject(user, 0, 700, -1500, user);
				camera_time = Get_Time() + 7.0f;
				AudioMessage("misn1210.wav"); // soviet guy should laugh "you better now"
				ClearObjectives();
				AddObjective("misn1200.otf", GREEN);
				AddObjective("misn1201.otf", GREEN);
				AddObjective("misn1202.otf", GREEN);
				AddObjective("misn1203.otf", WHITE);
				AddObjective("misn1204.otf", WHITE);
				better_message = true;
			}
		}

		// if he goes to 3 and then recovers to 2 then goes back to 3
		if ((better_message) && (!check4) && (check_point3_done) && (!identify_message) && (!real_bad))
		{
			AudioMessage("misn1206.wav"); // identify yourself!
			next_message_time = Get_Time() + 20.0f;
			ClearObjectives();
			AddObjective("misn1200.otf", GREEN);
			AddObjective("misn1201.otf", GREEN);
			AddObjective("misn1202.otf", RED);
			AddObjective("misn1203.otf", WHITE);
			AddObjective("misn1204.otf", WHITE);
			identify_message = true;
		}

		// if he goes to 3 and then recovers to 2 then goes to 5
		if ((better_message) && (check_point5_done) && (!check4) 
			&& (!identify_message) && (!real_bad))
		{
			AudioMessage("misn1206.wav"); // identify yourself!
			next_message_time = Get_Time() + 20.0f;
			ClearObjectives();
			AddObjective("misn1200.otf", GREEN);
			AddObjective("misn1201.otf", GREEN);
			AddObjective("misn1202.otf", GREEN);
			AddObjective("misn1203.otf", WHITE);
			AddObjective("misn1204.otf", YELLOW);
			identify_message = true;
		}


	// if her goes to 3 and then to 4 without recovering
	if ((!check2) && (check_point4_done)  && (cca_warning_message) && (!better_message) && 
		(!identify_message) && (!real_bad))
	{
		ClearObjectives();
		AddObjective("misn1200.otf", GREEN);
		AddObjective("misn1201.otf", WHITE);
		AddObjective("misn1202.otf", YELLOW);
		AddObjective("misn1203.otf", RED);
		AddObjective("misn1204.otf", WHITE);
		real_bad = true;
	}

	// if her goes to 3 and then to 5 without recovering
	if ((check_point5_done)  && (cca_warning_message) && (!better_message) && 
		(!identify_message) && (!real_bad) && (!check4))
	{
		ClearObjectives();
		AddObjective("misn1200.otf", GREEN);
		AddObjective("misn1201.otf", WHITE);
		AddObjective("misn1202.otf", YELLOW);
		AddObjective("misn1203.otf", WHITE);
		AddObjective("misn1204.otf", RED);
		real_bad = true;
	}

	// if he goes to 3 and then recovers and then goes to 4
	if ((better_message) && (GetDistance(user, checkpoint4) < 70.0f) 
		&& (!identify_message) && (!real_bad) && (!check4))
	{
		CameraReady();
		good3 = true;

		if (good3)
		{
			CameraObject(user, 0, 700, -1500, user);
			camera_time = Get_Time() + 6.0f;
			AudioMessage("misn1209.wav"); // soviet voice that is calm
			ClearObjectives();
			AddObjective("misn1200.otf", GREEN);
			AddObjective("misn1201.otf", GREEN);
			AddObjective("misn1202.otf", GREEN);
			AddObjective("misn1203.otf", GREEN);
			AddObjective("misn1204.otf", WHITE);
			check4 = true;
		}		
	}


// the FOURS

	//if he goes straight to 4
	if ((check_point4_done) && (!check2) && (!cca_warning_message) 
		&& (!identify_message) && (!real_bad))
	{
		AudioMessage("misn1206.wav"); // identify yourself!
		next_message_time = Get_Time() + 20.0f;
		ClearObjectives();
		AddObjective("misn1200.otf", GREEN);
		AddObjective("misn1201.otf", WHITE);
		AddObjective("misn1202.otf", WHITE);
		AddObjective("misn1203.otf", YELLOW);
		AddObjective("misn1204.otf", WHITE);
		identify_message = true;
	}

// the FIVES

// new line for ccacom_tower - this is what happens when the player reaches the ccacomtower

		
	//if he goes straight to 5
	if ((check_point5_done) && (!cca_warning_message) && (!check2) 
		&& (!identify_message) && (!real_bad) && (!straight_to_5))
	{
		AudioMessage("misn1206.wav"); // identify yourself!
		next_message_time = Get_Time() + 15.0f;
		ClearObjectives();
		AddObjective("misn1200.otf", GREEN);
		AddObjective("misn1201.otf", WHITE);
		AddObjective("misn1202.otf", WHITE);
		AddObjective("misn1203.otf", WHITE);
		AddObjective("misn1204.otf", YELLOW);
		identify_message = true;
		straight_to_5 = true;
	}

// if he goes to 5 with some slip ups

	if ((check_point5_done) && (cca_warning_message) && (check4)
		&& (!identify_message) && (!real_bad) && (!final_warned))
	{
		AudioMessage("misn1214.wav"); // explain yourself!
		final_warning = Get_Time() + 20.0f;
		ClearObjectives();
		AddObjective("misn1200.otf", GREEN);
		AddObjective("misn1201.otf", GREEN);
		AddObjective("misn1202.otf", GREEN);
		AddObjective("misn1203.otf", GREEN);
		AddObjective("misn1204.otf", YELLOW);
		final_warned = true;
	}
	
// if he does it exactly right	
	
	if ((check_point5_done) && (check4) && (!cca_warning_message)
		&& (!identify_message) && (!real_bad) && (!did_it_right))
	{
		AudioMessage("misn1205.wav"); // can we help you scout
		last_warning = Get_Time() + 30.0f;
		ClearObjectives();
		AddObjective("misn1200.otf", GREEN);
		AddObjective("misn1201.otf", GREEN);
		AddObjective("misn1202.otf", GREEN);
		AddObjective("misn1203.otf", GREEN);
		AddObjective("misn1204.otf", GREEN);
		did_it_right = true;
	}

	if ((did_it_right) && (last_warning < Get_Time()) && (!final_warned))
	{
		AudioMessage("misn1214.wav"); // explain yourself!
		final_warning = Get_Time() + 20.0f;
		final_warned = true;
	}

	

// these are constants /////////////////////////////////////////////////////////////////

	// this defines what happens under "cca_warning_message" conditions (if he goes out of order and then dilly-dallys)

	if ((cca_warning_message) && (!better_message) && (!check4) && (!identify_message) && (!last_warned))
	{
		last_warning = Get_Time() + 100.0f;
		last_warned = true;
	}

	if ((last_warned) && (last_warning < Get_Time()) && (!better_message) 
		&& (!check4) && (!final_warned))
	{
		AudioMessage("misn1214.wav"); // explain yourself!
		final_warning = Get_Time() + 40.0f;
		final_warned = true;
	}

	if ((final_warned) && (final_warning < Get_Time()) && (!identify_message))
	{
		AudioMessage("misn1206.wav"); // identify yourself!
		next_message_time = Get_Time() + 10.0f;
		identify_message = true;
	}

	// this defines what happens under "identify_message" conditions (if he is warned and does not recover in time)

	if ((identify_message) && (next_message_time < Get_Time()) 
		&& (!real_bad))
	{
		real_bad = true;
	}

	if ((identify_message) && (!real_bad))
	{
		if (check_point5_done)
		{
			Follow(guard_tank1, user);
			Follow(guard_tank2, user);
		}
		else
		{
			Goto(guard_tank1, ccacom_tower);
			Goto(guard_tank2, ccacom_tower);
		}
	}

	// this defines what happens under "real_bad" conditions

	if ((real_bad) && (!discovered))
	{
		AudioMessage("misn1211.wav");
		if (!interface_connect)
		{
			ClearObjectives();
			AddObjective("misn1206.otf", WHITE);
		}
		SetPerceivedTeam(user, 1);
		guard1 = BuildObject("svtank", 2, spawn_point1);
		guard2 = BuildObject("svtank", 2, spawn_point1);
		guard3 = BuildObject("svtank", 2, spawn_point2);
		guard4 = BuildObject("svtank", 2, spawn_point2);
		Goto(parked_tank2, ccacom_tower);
		Goto(parked_tank1, ccacom_tower);
		Attack (guard1, user, 1);
		Attack (guard2, user, 1);
		Attack (guard3, user, 1);
		Attack (guard4, user, 1);
		Attack (patrol1_1, user, 1);
		Attack (patrol1_2, user, 1);
		Attack (patrol2_1, user, 1);
		Attack (patrol2_2, user, 1);
//		Attack (patrol3_1, user, 1);
//		Attack (patrol3_2, user, 1);
		discovered = true;
	}


	if ((discovered) && (!IsAlive(guard1)) && (!IsAlive(guard2)) && (!IsAlive(guard3)))
	{
		guard1 = BuildObject("svtank", 2, spawn_point1);
		guard2 = BuildObject("svtank", 2, spawn_point1);
		guard3 = BuildObject("svtank", 2, spawn_point2);
		guard4 = BuildObject("svtank", 2, spawn_point2);
		Attack (guard1, user, 1);
		Attack (guard2, user, 1);
		Attack (guard3, user, 1);
		Attack (guard4, user, 1);
		if (!follow_spawn)
		{
			if (IsAlive(pturret1))
			{
				Goto(pturret1, "turret1_path");
			}
			if (IsAlive(pturret6))
			{
				Goto(pturret6, "turret2_path");
			}
		}
	}

// this is what happens when the player gets a warning message

	if ((cca_warning_message) && (!follow_spawn))
	{
		
		Goto(pturret1, "turret1_path");
		Goto(pturret6, "turret2_path");

		if ((GetDistance(user, checkpoint4)) > (GetDistance(user, checkpoint3))) // he's at 3
		{
			follower = BuildObject("svfigh", 2, "3spawn");
			Follow(follower, user);
		}
		else
		{
			follower = BuildObject("svfigh", 2, "4spawn");
			Follow(follower, user);
		}

		follow_spawn = true;
	}


// this is what happens when the player interfaces with the ccacomtower

		if ((GetDistance(user, ccacom_tower) < 60.0f) && (!interface_connect) && (!interface_complete))
		{
			AudioMessage("misn1201.wav"); //uplink sound
			interface_connect = true;
			interface_time = Get_Time () + 45.0f;
		}

		if ((GetDistance(user, ccacom_tower) > 75.0f) && (interface_connect) 
			&& (!interface_complete) && (!warning_message))
		{
			AudioMessage("misn1202.wav"); // loosing data uplink
			warning_repeat_time = Get_Time () + 5.0f;
			warning_message = true;
		}

		if ((warning_message) && (GetDistance(user, ccacom_tower) > 75.0f) && 
			(warning_repeat_time < Get_Time()) && (interface_connect))
		{
			warning_message = false;
		}

		if ((warning_message) && (GetDistance(user, ccacom_tower) < 75.0f) && (interface_connect))
		{
			warning_message = false;
		}

		if ((interface_connect) && (GetDistance(user, ccacom_tower) > 85.0f) && (!interface_complete))
		{
			AudioMessage("misn1203.wav"); // interface broken
			interface_connect = false;
		}

		if ((interface_connect) && (interface_time < Get_Time()) && (!interface_complete))
		{
			AudioMessage("misn1204.wav"); // interface complete
			ClearObjectives();
			AddObjective("misn1205.otf", WHITE);
			win_check_time = Get_Time() + 120.0f;
			StopCockpitTimer();
			HideCockpitTimer();
			AudioMessage("misn1223.wav"); // get back to nav 1
			interface_complete = true;
		}

	if ((interface_complete) && (!discovered))
	{
		if (IsAlive(patrol1_1))
		{
			Attack(patrol1_1, user);
		}
		if (IsAlive(patrol1_2))
		{
			Attack(patrol1_2, user);
		}
		if (IsAlive(patrol2_1))
		{
			Attack(patrol2_1, user);
		}
		if (IsAlive(patrol2_2))
		{
			Attack(patrol2_2, user);
		}
		if (IsAlive(patrol3_1))
		{
			Attack(patrol3_1, user);
		}
		if (IsAlive(patrol3_2))
		{
			Attack(patrol3_2, user);
		}
		if (IsAlive(patrol4_1))
		{
			Attack(patrol4_1, user);
		}
		if (IsAlive(patrol4_2))
		{
			Attack(patrol4_2, user);
		}
		if (IsAlive(guard_tank1))
		{
			Attack(guard_tank1, user);
		}
		if (IsAlive(guard_tank2))
		{
			Attack(guard_tank2, user);
		}

		discovered = true;
	}

	if ((interface_connect) && (!interface_complete) && (!noise))
	{
		AudioMessage("misn1212.wav");
		next_noise_time = Get_Time() + 3.0f;
		noise = true;
	}

	if ((interface_connect) && (!interface_complete) && (noise) 
		&& (next_noise_time < Get_Time()))
	{
		noise = false;
	}

// this is the Nav camera code

	if (key_captured)
	{
		if (((IsInfo("sbhqt1") == true) || (IsInfo("sbhqt2") == true)) && ((!camera_swap1) || (!camera_swap2)))
		{
			if ((GetDistance(user, center) < 100.0f))
			{
	//			if (IsAlive(center_cam))
	//			{
	//				RemoveObject(center_cam);
	//			}
				if (IsAlive(start_cam))
				{
					GameObjectHandle::GetObj(start_cam)->SetTeam(1);
//					RemoveObject(start_cam);
				}
				if (IsAlive(check2_cam))
				{
					GameObjectHandle::GetObj(check2_cam)->SetTeam(1);
//					RemoveObject(check2_cam);
				}
				if (IsAlive(check3_cam))
				{
					GameObjectHandle::GetObj(check3_cam)->SetTeam(1);
//					RemoveObject(check3_cam);
				}
				if (IsAlive(check4_cam))
				{
					GameObjectHandle::GetObj(check4_cam)->SetTeam(1);
//					RemoveObject(check4_cam);
				}
				if (IsAlive(goal_cam))
				{
					GameObjectHandle::GetObj(goal_cam)->SetTeam(1);
//					RemoveObject(goal_cam);
				}
	//			center_cam = BuildObject ("apcamr", 1, "center_cam");
//				start_cam = BuildObject ("apcamr", 1, "start_cam");
						if (start_cam!=NULL) GameObjectHandle::GetObj(start_cam)->SetName("Check Point");
//				check2_cam = BuildObject ("apcamr", 1, "check2_cam");
						if (check2_cam!=NULL) GameObjectHandle::GetObj(check2_cam)->SetName("Check Point");
//				check3_cam = BuildObject ("apcamr", 1, "check3_cam");
						if (check3_cam!=NULL) GameObjectHandle::GetObj(check3_cam)->SetName("Check Point");
//				check4_cam = BuildObject ("apcamr", 1, "check4_cam");
						if (check4_cam!=NULL) GameObjectHandle::GetObj(check4_cam)->SetName("Check Point");
//				goal_cam = BuildObject ("apcamr", 1, "goal_cam");
				swap_check = Get_Time() + 1.0f;
				camera_swap1 = true;
				camera_swap_back = false;
			}

			if ((GetDistance(user, checkpoint1) < 100.0f))
			{

				if (IsAlive(center_cam))
				{
					GameObjectHandle::GetObj(center_cam)->SetTeam(1);
//					RemoveObject(center_cam);
				}
	//			if (IsAlive(start_cam))
	//			{
	//				RemoveObject(start_cam);
	//			}
	/*			if (IsAlive(check2_cam))
				{
					RemoveObject(check2_cam);
				}
				if (IsAlive(check3_cam))
				{
					RemoveObject(check3_cam);
				}
				if (IsAlive(check4_cam))
				{
					RemoveObject(check4_cam);
				}
				if (IsAlive(goal_cam))
				{
					RemoveObject(goal_cam);
				}
	*/
//				center_cam = BuildObject ("apcamr", 1, "center_cam");
	//			start_cam = BuildObject ("apcamr", 1, "start_cam");
	//			check2_cam = BuildObject ("apcamr", 1, "check2_cam");
	//			check3_cam = BuildObject ("apcamr", 1, "check3_cam");
	//			check4_cam = BuildObject ("apcamr", 1, "check4_cam");
	//			goal_cam = BuildObject ("apcamr", 1, "goal_cam");
				swap_check = Get_Time() + 1.0f;
				camera_swap2 = true;
				camera_swap_back = false;
			}
		}
	}

	if (((camera_swap1) || (camera_swap2)) && (!camera_noise))
	{
		AudioMessage("misn1229.wav");
		camera_noise = true;
	}

	if ((!camera_swap_back) && (swap_check < Get_Time()) && ((camera_swap1) || (camera_swap2)))
	{
		swap_check = Get_Time() + 1.0f;

		if ((camera_swap1) && (GetDistance(user, center) > 300.0f))
		{
			AudioMessage("misn1230.wav");
//			if (IsAlive(center_cam))
//			{
//				RemoveObject(center_cam);
//			}
			if (IsAlive(start_cam))
			{
				GameObjectHandle::GetObj(start_cam)->SetTeam(3);
//				RemoveObject(start_cam);
			}
			if (IsAlive(check2_cam))
			{
				GameObjectHandle::GetObj(check2_cam)->SetTeam(3);
//				RemoveObject(check2_cam);
			}
			if (IsAlive(check3_cam))
			{
				GameObjectHandle::GetObj(check3_cam)->SetTeam(3);
//				RemoveObject(check3_cam);
			}
			if (IsAlive(check4_cam))
			{
				GameObjectHandle::GetObj(check4_cam)->SetTeam(3);
//				RemoveObject(check4_cam);
			}
			if (IsAlive(goal_cam))
			{
				GameObjectHandle::GetObj(goal_cam)->SetTeam(3);
//				RemoveObject(goal_cam);
			}
//			center_cam = BuildObject ("apcamr", 3, "center_cam");
//			start_cam = BuildObject ("apcamr", 3, "start_cam");
//			check2_cam = BuildObject ("apcamr", 3, "check2_cam");
//			check3_cam = BuildObject ("apcamr", 3, "check3_cam");
//			check4_cam = BuildObject ("apcamr", 3, "check4_cam");
//			goal_cam = BuildObject ("apcamr", 3, "goal_cam");
			swap_check = 99999.0f;
			camera_swap1 = false;
			camera_noise = false;
			camera_swap_back = true;
		}

		if ((camera_swap2) && (GetDistance(user, checkpoint1) > 300.0f))
		{
			AudioMessage("misn1230.wav");

			if (IsAlive(center_cam))
			{
				GameObjectHandle::GetObj(center_cam)->SetTeam(3);
//				RemoveObject(center_cam);
			}
//			if (IsAlive(start_cam))
//			{
//				RemoveObject(start_cam);
//			}
//			if (IsAlive(check2_cam))
/*			{
				RemoveObject(check2_cam);
			}
			if (IsAlive(check3_cam))
			{
				RemoveObject(check3_cam);
			}
			if (IsAlive(check4_cam))
			{
				RemoveObject(check4_cam);
			}
			if (IsAlive(goal_cam))
			{
				RemoveObject(goal_cam);
			}
*/
//			center_cam = BuildObject ("apcamr", 3, "center_cam");
//			start_cam = BuildObject ("apcamr", 3, "start_cam");
//			check2_cam = BuildObject ("apcamr", 3, "check2_cam");
//			check3_cam = BuildObject ("apcamr", 3, "check3_cam");
//			check4_cam = BuildObject ("apcamr", 3, "check4_cam");
//			goal_cam = BuildObject ("apcamr", 3, "goal_cam");
			swap_check = 99999.0f;
			camera_swap2 = false;
			camera_noise = false;
			camera_swap_back = true;
		}
	}
}

///////////////////// THIS MARKS THE END OF GAME BLOWN //////////////////////////////////////
// win condition

	if ((game_blown) && (!game_over))
	{
		FailMission(Get_Time() + 10.0f);
		game_over = true;
	}

	if ((interface_complete) && (win_check_time < Get_Time()))
	{
		win_check_time = Get_Time() + 5.0f;

		if ((GetDistance(user, nav1) < 75.0f) && (!win))
		{
			AudioMessage("misn1216.wav");
			SucceedMission(Get_Time() + 7.0f, "misn12w1.des");
			win = true;
		}
	}

	if ((!interface_complete) && (GetCockpitTimer() == 0) && (!game_over))
	{
		AudioMessage("misn1215.wav");
		FailMission(Get_Time() + 15.0f, "misn12f1.des");
		game_over = true;
	}


// END OF SCRIPT

}
																	
