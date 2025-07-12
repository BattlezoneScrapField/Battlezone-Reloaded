#include "GameCommon.h"
#include "..\fun3d\Factory.h"
#include "..\fun3d\AiMission.h"
#include "..\fun3d\PowerUp.h"
#include "..\fun3d\ScriptUtils.h"

/*
	Misn07Mission
*/

class Misn07Mission : public AiMission {
	DECLARE_RTIME(Misn07Mission)
public:
	Misn07Mission(void);
	~Misn07Mission();

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
				test, utah_found,
				start_done, 
				out_of_car, 
				alarm_on,
				start_evac,
				ccaguntower1_down, ccaguntower2_down,
				radar_dead, 
				player_dead, 
				over_wall, 
				guntower_attacked,
				fence_off,
				rendezvous,
				recon_message1, recon_message2,
				build_scouts,
				jump_cam_spawned,
				rookie_moved,
				becon_build,
				free1,
				free2,
				p1_retreat, p2_retreat, p3_retreat, p4_retreat,
				retreat_message_done,
				first_objective, second_objective,
				turret_move,
				next_mission,
				rookie_lost,
				mine_pathed,
				detected, getum,
				patrola1, patrola2, patrolb1, patrolb2, patrolc1, patrolc2,
				retreat_success,
				detected_message,
				fighter_moved,
				unit_spawn,
				vehicle_stolen,
				trigger1,
				alarm_special,
				m_on[111],
				m_dead[111],
				alarm_sound,
				rookie_removed,
				forces_enroute,
				test_tank_built,
				camera1_on, camera2_on, camera3_on, camera4_on, camera_off,
				camera2_oned, camera3_oned, 
				camera_ready,
				tank_switch,
				sound_started,
				test_found,
				game_over,
				first_camera_ready, first_camera_off,
				cute_camera_ready, cute_camera_off,
				radar_camera_off, next_camera_on, rookie_jumped, tower_warning,
				rookie_found, opening_vo, shot1, shot2,
				b_last;
		};
		bool b_array[298];
	};

	// floats
	union {
		struct {
			float
				unit_spawn_time,
				recon_message_time,
				becon_build_time,
				rookie_rendezvous_time,
				getaway_message_time,
				patrol2_move_time,
				rookie_move_time,
				alarm_time,
				alarm_timer,
				rendezous_check,
				alarm_check,
				rookie_remove_time,
				runner_check,
				check_jump_geyser,
				reach_mine_time,
				check_range,
				change_angle, change_angle1, change_angle2, change_angle3,
				switch_tank,
				start_sound,
				recon_message2_time,
				first_camera_time,
				radar_camera_time,
				next_mission_time,
				cute_camera_time,
				next_shot_time,
				tower_check,
				f_last;
		};
		float f_array[29];
	};

	// handles
	union {
		struct {
			Handle
				user, nsdfrecycle, nsdfmuf,
				rookie,
				jump_cam,
				jump_geyz,
				remove_geyz,
				mine_geyz,
				pilot1, pilot2, pilot3, pilot4, pilot5,
				ccaguntower1, ccaguntower2,
				ccacomtower,
				powrplnt1, powrplnt2, 
				parkedtank1, parkedtank2, parkedtank3, parkedtank4,
				barrack1, barrack2,

				nav1, nav2, nav3, nav4/*is becon5*/, nav5/*is becon6*/, nav6, nav7,
				becon1, becon2, becon3, becon4, 

				wingman1, wingman2, 
				wingtank1, wingtank2, wingtank3,
				wingturret1, wingturret2,
				nsdfarmory, svapc,

				m[111],

				ccarecycle, ccamuf, ccaslf,
				basepowrplnt1, pbaseowrplnt2,
				ccabaseguntower1, ccabaseguntower2,
				guard_tank1, guard_tank2, guard_tank3, test_tank,
				patrol1_1, patrol1_2, patrol1_3,
				svpatrol1_1, svpatrol1_2, svpatrol1_3,
				svpatrol2_1, svpatrol2_2, svpatrol2_3,
				svpatrol3_1, svpatrol3_2, svpatrol3_3,
				svpatrol4_1, svpatrol4_2,
				guard_turret1, guard_turret2,
				spawn_turret1, spawn_turret2,
				parked1, parked2,parked3,
				parkturret1, parkturret2,
				spawn_point,
				fence,
				test_turret,
				tank_spawn,
				power1_geyser, power2_geyser,
				radar_geyser, camera_geyser, show_geyser,
				new_tank1, new_tank2,
				h_last;
		};
		Handle h_array[200];
	};

	// path pointers
	union {
		struct {
			AiPath
				*turret1_spot, *mine[111],
				*p_last;
		};
		AiPath *p_array[112];
	};

	// integers
	union {
		struct {
			int
				count,mine_check, x, units,
				audmsg, 
				i_last;
		};
		int i_array[5];
	};
};

IMPLEMENT_RTIME(Misn07Mission)

Misn07Mission::Misn07Mission(void)
{
}

Misn07Mission::~Misn07Mission()
{
}

void Misn07Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

bool Misn07Mission::Load(file fp)
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

		// path pointers
		int p_count = &p_last - p_array;
		_ASSERTE(p_count == SIZEOF(p_array));
		for (i = 0; i < p_count; i++)
			p_array[i] = 0;

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

	// path pointers
	int p_count = &p_last - p_array;
	_ASSERTE(p_count == SIZEOF(p_array));
	for (int i = 0; i < p_count; i++)
		ret = ret && in_ptr(fp, (void **)&p_array[i], sizeof(p_array[0]), "p_array", this);

	// ints
	int i_count = &i_last - i_array;
	_ASSERTE(i_count == SIZEOF(i_array));
	ret = ret && in(fp, i_array, sizeof(i_array));

	ret = ret && AiMission::Load(fp);
	return ret;
}

bool Misn07Mission::PostLoad(void)
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

bool Misn07Mission::Save(file fp)
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

	// path pointers
	int p_count = &p_last - p_array;
	_ASSERTE(p_count == SIZEOF(p_array));
	for (int i = 0; i < p_count; i++)
		ret = ret && out_ptr(fp, (void **)&p_array[i], sizeof(p_array[0]), "p_array");

	// ints
	int i_count = &i_last - i_array;
	_ASSERTE(i_count == SIZEOF(i_array));
	ret = ret && out(fp, i_array, sizeof(i_array), "i_array");

	ret = ret && AiMission::Save(fp);
	return ret;
}

void Misn07Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

void Misn07Mission::Setup(void)
{
// Here's where you set the values at the start.  

	mine_check = 1;
	x = 6000;
	units = 1;
	
	start_done = false; 
	out_of_car = false; 
	alarm_on = false; 
	start_evac = false;
	ccaguntower1_down = false;
	ccaguntower2_down = false;
	radar_dead = false;
	player_dead = false; 
	over_wall = false; 
	guntower_attacked = false;
	fence_off = false;
	unit_spawn = false;
	recon_message1 = false;
	recon_message2 = false;
	build_scouts = false;
	jump_cam_spawned = false;
	rookie_moved = false;
	rendezvous = false;
	free1 = false;
	free2 = false;
	becon_build = false;
	p1_retreat = false;
	p2_retreat = false;
	p3_retreat = false;
	p4_retreat = false;
	first_objective = false;
	second_objective = false;
	retreat_message_done = false;
	turret_move = false;
	next_mission = false;
	rookie_lost = false;
	mine_pathed = false;
	getum = false;
	detected = false;
	patrola1 = false;
	patrola2 = false;
	patrolb1 = false;
	patrolb2 = false;
	patrolc1 = false;
	patrolc2 = false;
	retreat_success = false;
	detected_message = false;
	fighter_moved = false;
	vehicle_stolen = false;
	trigger1 = false;
	alarm_special = false;
	alarm_sound = false;
	rookie_removed = false;
	forces_enroute = false;
	test_tank_built = false;
	camera_ready = false;
	camera1_on = false;
	camera2_on = false;
	camera3_on = false;
	camera4_on = false;
	camera_off = false;
	camera2_oned = false;
	camera3_oned = false;
	tank_switch = false;
	sound_started = false;
	test_found = false;
	game_over = false;
	first_camera_ready = false;
	first_camera_off = false;
	cute_camera_ready = false;
	cute_camera_off = false;
	radar_camera_off = false;
	next_camera_on = false;
	rookie_jumped = false;
	tower_warning = false;
	rookie_found = false;
	opening_vo = false;
	test = false;
	utah_found = false;
	shot1 = false;
	shot2 = false;

	for (count=0; count<111; count = count+1)
	{
		mine[count] = NULL;
		m_on[count] = false;
		m_dead[count] = false;
	}

	unit_spawn_time = 99999.0f;
	recon_message_time = 99999.0f;
	becon_build_time = 99999.0f;
	rookie_move_time = 99999.0f;
	getaway_message_time = 99999.0f;
	rookie_rendezvous_time = 99999.0f;
	patrol2_move_time = 99999.0f;
	alarm_time = 99999.0f;
	alarm_timer = 99999.0f;
	rendezous_check = 99999.0f;
	alarm_check = 99999.0f;
	rookie_remove_time = 99999.0f;
	runner_check = 99999.0f;
	check_jump_geyser = 99999.0f;
	reach_mine_time = 99999.0f;
	check_range = 99999.0f;
	change_angle = 99999.0f;
	change_angle1 = 99999.0f;
	change_angle2 = 99999.0f;
	change_angle3 = 99999.0f;
	switch_tank = 99999.0f;
	start_sound = 99999.0f;
	recon_message2_time = 99999.0f;
	first_camera_time = 99999.0f;
	cute_camera_time = 99999.0f;
	radar_camera_time = 99999.0f;
	next_mission_time = 99999.0f;
	next_shot_time = 99999.0f;
	tower_check = 99999.0f;

	turret1_spot = NULL;

	jump_geyz = GetHandle ("volcano_geyz1");
	remove_geyz = GetHandle ("volcano_geyz2");
	ccaguntower1 = GetHandle ("sgtower1");
	ccaguntower2 = GetHandle ("sgtower2");
	ccacomtower = GetHandle ("radar_array");
	powrplnt1 = GetHandle ("power1");
//	powrplnt2 = GetHandle ("power2");
	barrack1 = GetHandle ("hut1");
	barrack2 = GetHandle ("hut2");

	nav1 = NULL;
	nav2 = NULL;
	nav3 = GetHandle ("cam3");

	wingman1 = GetHandle ("avfigh1");
	wingman2 = 0;
	wingtank1 = GetHandle ("avtank1");
	wingtank2 = GetHandle ("avtank2");
	wingtank3 = GetHandle ("avtank3");
	wingturret1 = GetHandle ("avturret1");
	wingturret2 = GetHandle ("avturret2");
	nsdfarmory = GetHandle ("avslf");

	ccarecycle = GetHandle ("svrecycler");
	ccamuf = GetHandle ("svmuf");
	basepowrplnt1 = GetHandle ("svbasepower1");
	pbaseowrplnt2 = GetHandle ("svbasepower2");
//	ccabaseguntower1 = GetHandle ("svbasetower1");
//	ccabaseguntower2 = GetHandle ("svbasetower2");
//	guard_tank1 = GetHandle ("svtank1");
//	guard_tank2 = GetHandle ("svtank2");
	patrol1_1 = GetHandle ("svfigh1");
	patrol1_2 = GetHandle ("svfigh2");

	svpatrol1_1 = GetHandle ("svpatrol1_1");
	svpatrol1_2 = GetHandle ("svpatrol1_2");
	svpatrol2_1 = GetHandle ("svpatrol2_1");
	svpatrol2_2 = GetHandle ("svpatrol2_2");
	svpatrol3_1 = GetHandle ("svpatrol3_1");
	svpatrol3_2 = GetHandle ("svpatrol3_2");
	svpatrol4_1 = GetHandle ("svpatrol4_1");
	svpatrol4_2 = GetHandle ("svpatrol4_2");
//	test_tank = GetHandle ("test_tank");
	guard_turret1 = GetHandle("svturret1");
	guard_turret2 = GetHandle("svturret2");
	parked1 = GetHandle ("parked1");
	parked2 = GetHandle ("parked2");
	parked3 = GetHandle ("parked3");
	parkturret1 = GetHandle("pturret1");
	parkturret2 = GetHandle("pturret2");
	svapc = GetHandle("parked_svapc");
	spawn_point = GetHandle ("recycle_spawn_geyz");
//	test_turret = GetHandle ("test_turret");
//	mine_geyz = GetHandle("");
//	tank_spawn = GetHandle ("test_tank_spawn");
	radar_geyser = GetHandle ("radar_geyser");
	camera_geyser = GetHandle ("camera_geyser");
	show_geyser = GetHandle ("show_geyser");
	nsdfrecycle = NULL;
	nsdfmuf = NULL;
	jump_cam = NULL;
	rookie = NULL;
	nav4 = NULL;
	nav5 = NULL;
	nav6 = NULL;
	nav7 = NULL;
	audmsg = NULL;
	pilot1 = NULL;
	pilot2 = NULL;
	pilot3 = NULL;
	pilot4 = NULL;
	pilot5 = NULL;
	spawn_turret1 = NULL;
	spawn_turret2 = NULL;
	becon1 = NULL;
	becon2 = NULL;
	becon3 = NULL;
	becon4 = NULL;
	new_tank1 = NULL;
	new_tank2 = NULL;

}

void Misn07Mission::AddObject(Handle h)
{
}

inline bool AliveButDamaged(Handle h)
{
	GameObject *o = GameObjectHandle::GetObj(h);
	if (o == NULL)
		return false;
	if (o->GetHealth()>=0.95f)
		return false;
	return true;
}

void Misn07Mission::Execute(void)
{
// START OF SCRIPT

// Here is where you put what happens  every frame.  

	user = GetPlayerHandle(); //assigns the player a handle every frame

	mine_check = mine_check + 10;

	if (mine_check > 110)
	{
		mine_check = 1;
	}

/*	if (!first_camera_ready)
	{
		CameraReady();
		audmsg = AudioMessage("misn0700.wav"); // General "mission breifing"
		first_camera_time = Get_Time() + 10.0f;
		first_camera_ready = true;
	}

	if ((first_camera_ready) && (!first_camera_off))
	{
		CameraPath("start_camera", x, 950, user);
		x = x - 100;
	}

	if ((first_camera_ready) && (!first_camera_off) && ((CameraCancelled()) || (first_camera_time < Get_Time())))
	{
		CameraFinish();
		first_camera_off = true;
	}

	if (CameraCancelled())
	{
		StopAudioMessage(audmsg);
	}
*/
	if (!start_done)
	{ 

		if (nav3!=NULL) GameObjectHandle::GetObj(nav3)->SetName("Rendezvous Point");

		SetScrap(1, 10);

		SetObjectiveOff(ccacomtower);
		Patrol(patrol1_1, "patrol_path3");	//
		Patrol(patrol1_2, "patrol_path3");	//
//		Patrol(guard_tank1, "guard_path");	//
//		Patrol(guard_tank2, "guard_path");	// sets enemy units to their patrol routes
		Patrol(svpatrol3_1, "patrol_path1");//
		Patrol(svpatrol3_2, "patrol_path1");//
		Patrol(svpatrol4_1, "patrol_path2");//
		Patrol(svpatrol4_2, "patrol_path2");//

		SetIndependence(wingtank2, 0);
		Stop(wingtank2);
		SetPerceivedTeam(wingtank2, 1);
		SetIndependence(wingtank3, 0);
		Stop(wingtank3);
		SetPerceivedTeam(wingtank3, 1);

		Stop(svpatrol2_1, 1);
		Stop(svpatrol2_2, 1);

		rendezous_check = Get_Time() + 9.0f;
		patrol2_move_time = Get_Time () + 121.0f;
		alarm_check = Get_Time() + 27.0f;

		turret1_spot = AiPath::Find("turret1_spot");
		for (count = 0; count < 111; count++)
		{
			char name[10];
			sprintf(name, "m%0.3d", count);
			mine[count] = AiPath::Find(name);
		}

		start_done = true;
	}

//	if (CameraCancelled())
//	{
//		StopAudioMessage(audmsg);
//	}

	if ((!opening_vo) && (start_done) && (rendezous_check < Get_Time()))
	{
		rendezous_check = Get_Time() + 15.0f;
		AudioMessage("misn0700.wav"); // General "mission breifing"
		ClearObjectives();
		AddObjective("misn0700.otf", WHITE);
		opening_vo = true;
	}

	if ((start_done) && (patrol2_move_time < Get_Time () && (!rendezvous)) 
		&& (IsAlive(svpatrol2_1))  && (IsAlive(svpatrol2_2)) && (!fighter_moved))
//		&& (GameObjectHandle::GetObj(svpatrol2_1)->GetHealth()<0.98f) // (GameObjectHandle::GetObj(svpatrol2_1)->GetLastEnemyShot()<0)
//		&& (GameObjectHandle::GetObj(svpatrol2_2)->GetHealth()<0.98f)) //(GameObjectHandle::GetObj(svpatrol2_2)->GetLastEnemyShot()<0)) 
	{
		Patrol(svpatrol2_1, "patrol_path1");// sets enemy units to their patrol routes 
		Patrol(svpatrol2_2, "patrol_path1");// sets enemy units to their patrol routes
		fighter_moved = true;
	}

// this is when the player rendezvous with the other tanks 
if (!first_objective)
{																							
	if ((rendezous_check < Get_Time()) && (!rendezvous) && (!alarm_on))
	{
		rendezous_check = Get_Time() + 3.0f;

		if ((IsAlive(wingtank2)) && (GetDistance(user,wingtank2) < 150.0f) && (!rendezvous) ||
			((IsAlive(wingtank3)) && (GetDistance(user,wingtank3) < 150.0f) && (!rendezvous)))		
		{																					
			audmsg = AudioMessage("misn0701.wav"); // greetings comander "standby"
			if (IsAlive(wingtank2))
			{
				new_tank1 = BuildObject("avtank", 1, wingtank2);
				RemoveObject(wingtank2);
			}
			if (IsAlive(wingtank3))
			{
				new_tank2 = BuildObject("avtank", 1, wingtank3);
				RemoveObject(wingtank3);
			}
			ClearObjectives();																
			AddObjective("misn0700.otf", GREEN);											
			AddObjective("misn0701.otf", WHITE);										
			recon_message_time = Get_Time() + 240.0f;
			runner_check = Get_Time() + 6.0f; 
			patrol2_move_time = Get_Time () + 60.0f;
			nav1 = BuildObject ("apcamr", 1, "cam1_spawn"); //outpost cam
			if (nav1!=NULL) GameObjectHandle::GetObj(nav1)->SetName("CCA Outpost");
			tower_check = Get_Time() + 10.0f;
			rendezvous = true;														
		}	
	}
	
	if ((rendezvous) && (patrol2_move_time < Get_Time()) && (!fighter_moved))
	{
		if (svpatrol2_1!=NULL)
		{
			Attack(svpatrol2_1, user);
		}
		if (svpatrol2_2!=NULL)
		{
			Attack(svpatrol2_2, user);
		}

		fighter_moved = true;
	}
															
/*	if ((rendezvous) && (IsAlive (wingtank3)) && (!free1))				
	{																		
		Stop(wingtank3, 0);												
		free1 = true;														
	}																			
																							
	if ((rendezvous) && (IsAlive (wingtank2)) && (!free2))									
	{																					
		Stop(wingtank2, 0);															
		free2 = true;																		
	}
*/
	if ((IsAlive(nav1)) && (tower_check < Get_Time()) && (!tower_warning))
	{
		tower_check = Get_Time() + 4.0f;

		if (GetDistance(user, nav1) < 90.0f)
		{
			AudioMessage("misn0716.wav");
			tower_warning = true;
		}
	}
}

// this is when the rookie tells the player about the overlook into the base and lays down a camera
//////////////////////////////ROOKIE SCRIPT 1 HE JUMPS IN FRONT OF PLAYER ////////////////////////////	
/*																										
if ((!first_objective) && (!alarm_on) && (!out_of_car))
{
	if ((rendezvous) && (!jump_cam_spawned) && (recon_message_time < Get_Time()))
	{
		recon_message_time = Get_Time() + 20.0f;

	    if ((GetDistance(user, jump_geyz) > 400.0f) && (GetDistance(user, ccacomtower) > 150.0f))
		{																											
//			AudioMessage("misn0702.wav"); // Rookie "I found an overlook"										
			AudioMessage("win.wav"); // Rookie trasmits a broken message saying he's found a way in and screams YAAAAAAAHHHHHHOOOOOO!
			jump_cam = BuildObject ("apcamr", 1, "jump_cam_spawn"); //Rookie drops camera			
			rookie = BuildObject ("avfigh", 1, jump_geyz);// spawn in rookie										
			Goto (rookie, jump_cam);//rookie goes to jump-cam to get in picture
			rookie_move_time = Get_Time() + 20.0f; // sets time to move rookie to secret spot
			recon_message2_time = Get_Time() + 480.0f;
			jump_cam_spawned = true;																				
		}																											
	}																																																						//
	
	if ((jump_cam_spawned) && (jump_cam!=NULL))
	{
		GameObjectHandle::GetObj(jump_cam)->SetName("Volcano Peak");
	}
	
	if ((jump_cam_spawned) && (rookie_move_time < Get_Time()) && (!rookie_moved))								
	{																											
		Defend(rookie, 1); 
		rookie_remove_time = Get_Time() + 15.0f;
		rookie_moved = true;																					
	}																							
	
	if ((rookie_moved) && (rookie_remove_time < Get_Time()) && (!rookie_removed))
	{
		rookie_remove_time = Get_Time() + 5.0f;

		if (IsAlive(rookie))
		{
			Defend(rookie, 1);

			if (GetDistance(user, rookie) < 70.0f)
			{
				audmsg = AudioMessage("win.wav");
				rookie_removed = true;
			}
		}
	}

	if ((rookie_removed) && (IsAudioMessageDone(audmsg)) && (!rookie_jumped))
	{
		Damage(rookie, 5000);
		rookie_jumped = true;
	}

//	if ((rookie_moved) && (rookie_remove_time < Get_Time()) && (!rookie_removed)) // rookie reaches secret spot
//	{																								
//		RemoveObject(rookie);// I take rookie away so that he is safe
//		rookie_removed = true;
//	}
}
*/
//////////////////////////////ROOKIE SCRIPT 2 HE JUMPS ON CAMERA ////////////////////////////
if ((!first_objective) && (!alarm_on) && (!out_of_car))
{
	if ((rendezvous) && (!jump_cam_spawned) && ((recon_message_time < Get_Time()) || (tower_warning)))
	{
		recon_message_time = Get_Time() + 5.0f;
		units = CountUnitsNearObject(user, 200.0f, 2, "svfigh");

	    if ((GetDistance(user, jump_geyz) > 400.0f) && (units == 0))
		{
			AudioMessage("misn0702.wav"); // Rookie trasmits a broken message saying player should look at camera
			jump_cam = BuildObject ("apcamr", 1, "jump_cam_spawn");
			rookie = BuildObject ("avfigh", 1, jump_geyz);
			Follow (rookie, jump_geyz);
			rookie_move_time = Get_Time() + 10.0f;
//			recon_message2_time = Get_Time() + 480.0f;
			jump_cam_spawned = true;
		}
	}

	if ((jump_cam_spawned) && (jump_cam!=NULL))
	{
		GameObjectHandle::GetObj(jump_cam)->SetName("Volcano Peak");
	}
	
	if ((jump_cam_spawned) && (rookie_move_time < Get_Time()) && (!rookie_moved))								
	{
//		if (IsAlive(rookie))
//		{
//			Defend(rookie, 1);
//		}
		rookie_remove_time = Get_Time() + 10.0f;
		rookie_moved = true;
	}

	if ((rookie_moved) && (rookie_remove_time < Get_Time()) && (!rookie_found))
	{
		rookie_remove_time = Get_Time() + 3.0f;	
		
		if (IsAlive(rookie))
		{
//			Defend(rookie);

			if (GetDistance(user, rookie) < 70.0f)
			{
				Defend(rookie, 1);
				AudioMessage("misn0718.wav"); // rookie sends broken message he's found a way inside base
				rookie_remove_time = Get_Time() + 10.0f;
				rookie_found = true;
			}
		}
	}
	
	if ((rookie_found) && (rookie_remove_time < Get_Time()) && (!rookie_removed))
	{
		if (IsAlive(rookie))
		{
			AudioMessage("misn0715.wav");// screams YAAAAAAAHHHHHHOOOOOO!
			EjectPilot(rookie);
			rookie_removed = true;
		}
	}
}
																							
// end rookie at overlook - he heads off to mine field //////////////////////////////////





// this is when the player tries to go into the radar array base w/out jumping in (in his tank) 

	if ((alarm_check < Get_Time()) && (!alarm_on))
	{

		alarm_check = Get_Time() + 5.0f;

/*		if ((!alarm_on) && (!out_of_car) && (GetDistance(user, turret1_spot) < 90.0f))// this is if the player attacks the gun towers around the solar array
		{
			AudioMessage("misn0710.wav");// you've tripped the alarm
			SetObjectiveOn(ccacomtower);
			SetObjectiveName(ccacomtower, "Radar Array");
			alarm_on = true;
		}
*/
		if ((!alarm_on) && (!out_of_car) && (GetDistance(user, turret1_spot) < 70.0f))// this is if the player attacks the gun towers around the solar array
		{
			AudioMessage("misn0710.wav");// you've tripped the alarm
			SetObjectiveOn(ccacomtower);
			SetObjectiveName(ccacomtower, "Radar Array");
			alarm_on = true;
		}

	}

// end of player trying to enter radar base in tank 
// now that the alarm is on the task will be more difficult
if (!first_objective)
{
	if (alarm_on)
	{
		// this code makes the alarm sound
		if ((ccacomtower!=NULL) && (GetDistance(user, ccacomtower) < 170.0f) && (!alarm_sound))
		{
			AudioMessage("misn0708.wav"); // this is the alarm sound		
			alarm_timer = Get_Time() + 6.0f;
			alarm_sound = true;
		}

		if ((alarm_sound) && (alarm_timer < Get_Time()))
		{
			alarm_sound = false;
		}

		if (!turret_move)
		{
			SetObjectiveOn(ccacomtower);
			SetObjectiveName(ccacomtower, "Radar Array");
			Retreat (guard_turret1, ccacomtower, 1);
			Retreat (guard_turret2, ccacomtower, 1);
			turret_move = true;
		}

		if (!start_evac) //starts clock to spawn cca soldiers
		{
			unit_spawn_time = Get_Time() + 20.0f;
			start_evac = true;
		}

		if ((start_evac) && (unit_spawn_time < Get_Time()) && (!unit_spawn) && (!alarm_special))// spawns cca soldiers and tells them to go to their tanks
		{
			pilot1 = BuildObject("sspilo",2,"hut2_spawn");
			pilot2 = BuildObject("sspilo",2,"hut2_spawn");
			pilot3 = BuildObject("sspilo",2,"hut2_spawn");
			pilot4 = BuildObject("sspilo",2,"hut1_spawn");
			pilot5 = BuildObject("sspilo",2,"hut1_spawn");
			if (parkturret1 != user) {
				spawn_turret1 = BuildObject("svturr", 2, parkturret1);
				Defend(spawn_turret1);
				RemoveObject(parkturret1);
			}
			if (parkturret2 != user) {
				spawn_turret2 = BuildObject("svturr", 2, parkturret2);
				Defend(spawn_turret2);
				RemoveObject(parkturret2);
			}
			// these lines tell the soviet pilots to get to their ships
			if (parked1!=NULL)
			{
				Retreat(pilot1, parked1, 1);
			}
			
			if (parked2!=NULL)
			{
				Retreat(pilot2, parked2, 1);
			}

			if (parked3!=NULL)
			{
				Retreat(pilot3, parked3, 1);
			}
		
			unit_spawn = true;
		}
		// this is what happens when the player is in the base and sets off the alarm while out of a vehcile
		if ((start_evac) && (alarm_special) && (unit_spawn_time < Get_Time()) && (!unit_spawn))// spawns cca soldiers and tells them to go to their tanks
		{
			pilot1 = BuildObject("sspilo",2,"hut2_spawn");
			pilot2 = BuildObject("sspilo",2,"hut2_spawn");
			pilot3 = BuildObject("sssold",2,"hut2_spawn");
			pilot4 = BuildObject("sspilo",2,"hut1_spawn");
			pilot5 = BuildObject("sssold",2,"hut1_spawn");
			Attack(pilot3, user);
			Attack(pilot5, user);
			// these lines tell the soviet pilots to get to their ships
			if (parked1!=NULL)
			{
				Retreat(pilot1, parked1, 1);
			}
			
			if (parked2!=NULL)
			{
				Retreat(pilot2, parked2, 1);
			}

			if (parked3!=NULL)
			{
				Retreat(pilot4, parkturret1, 1);
			}

			unit_spawn = true;
		}

		// this is an attempt to find out if a pilot has gotten to his ship and then give them orders

		if ((unit_spawn) && (!alarm_special))
		{
			if ((!IsAlive(pilot1)) && (parked1!=NULL))
			{
				Attack(parked1, user);
			}
			if ((!IsAlive(pilot2)) && (parked2!=NULL))
			{
				Attack(parked2, user);
			}
			if ((!IsAlive(pilot3)) && (parked3!=NULL))
			{
				Attack(parked3, user);
			}

/*			if ((!IsAlive(pilot4)) && (parkturret1!=NULL))
			{
				Retreat(parkturret1, turret1_spot);		
			}
			if ((!IsAlive(pilot5)) && (parkturret2!=NULL))
			{
				Retreat(parkturret2, "turret2_spot");
			}
*/	
		}

		if ((unit_spawn) && (alarm_special))
		{
			if ((!IsAlive(pilot1)) && (parked1!=NULL))
			{
				Goto(parked1, ccacomtower);
			}
			if ((!IsAlive(pilot2)) && (parked2!=NULL))
			{
				Goto(parked2, ccacomtower);
			}
			if ((!IsAlive(pilot4)) && (parkturret1!=NULL))
			{
				Retreat(parkturret1, "turret1_spot");
			}
		}

//		if (((!alarm_special) && (!IsAlive(ccaguntower1)) && (!forces_enroute)) || 
//			((!alarm_special) && (!IsAlive(ccaguntower2)) && (!forces_enroute)))
		if ((IsAlive(ccacomtower)) && (GameObjectHandle::GetObj(ccacomtower)->GetHealth()<0.50f) && (!forces_enroute))
		{
//			if (IsAlive(svpatrol1_1))
//			{
//				Goto(svpatrol1_1, ccacomtower, 1);
//			}
			if (IsAlive(svpatrol1_2))
			{
				Goto(svpatrol1_2, ccacomtower, 1);
			}
//			if (IsAlive(svpatrol2_1))
//			{
//				Goto(svpatrol2_1, ccacomtower, 1);
//			}
//			if (IsAlive(svpatrol2_2))
//			{
//				Goto(svpatrol2_2, ccacomtower, 1);
//			}
			if (IsAlive(svpatrol3_1))
			{
				Goto(svpatrol3_1, ccacomtower, 1);
			}
//			if (IsAlive(svpatrol3_2))
//			{
//				Goto(svpatrol3_2, ccacomtower, 1);
//			}
			if (IsAlive(svpatrol4_1))
			{
				Goto(svpatrol4_1, ccacomtower, 1);
			}
//			if (IsAlive(svpatrol4_2))
//			{
//				Goto(svpatrol4_2, ccacomtower, 1);
//			}

			forces_enroute = true;
		}
	}
}

// this is what happens when the player parachutes into the base
if (!first_objective)
{
	if ((!alarm_on) && (!out_of_car) && (GetDistance(user, camera_geyser) < 160.0f))// this indicates that the player has parachuted into the solar array
	{
		SetObjectiveOn(ccacomtower);
		SetObjectiveName(ccacomtower, "Radar Array");		
//		cute_camera_time = Get_Time() + 5.0f;
		out_of_car = true;
	}

/*	// this will start the camera on the player
	if ((out_of_car) && (!cute_camera_ready) && (cute_camera_time < Get_Time()))
	{
		CameraReady();
		cute_camera_time = Get_Time() + 5.0f;
		cute_camera_ready = true;
	}

	if ((cute_camera_ready) && (!cute_camera_off))
	{
		CameraObject(user, 800, 800, 10, user);	
	}

	if ((cute_camera_ready) && (!cute_camera_off))
	{
		if (cute_camera_time < Get_Time())
		{
			CameraFinish();
			cute_camera_off = true;
		}
	}
*/
// this indicates when the player has taken over a vehicle
	if (((out_of_car) && (IsOdf(user, "svtank"))) || ((out_of_car) && (IsOdf(user, "svfigh"))) ||
		((out_of_car) && (IsOdf(user, "svturr"))) && (!vehicle_stolen))
	{
//		alarm_time = Get_Time() + 20.0f;
		vehicle_stolen = true;
	}
	// this simply means that if the player fires on anything while in the base he will set off an alarm
	if (!trigger1 && out_of_car)
	{
		if (
			AliveButDamaged(ccaguntower1) ||
			AliveButDamaged(ccaguntower2) ||
			AliveButDamaged(ccacomtower) ||
			AliveButDamaged(powrplnt1) ||
			// AliveButDamaged(powrplnt2) ||
			AliveButDamaged(barrack1) ||
			AliveButDamaged(barrack2) ||
			AliveButDamaged(parked1) ||
			AliveButDamaged(parked2) ||
			AliveButDamaged(parked3) ||
			AliveButDamaged(parkturret1) ||
			AliveButDamaged(parkturret2)
			)
		{
			trigger1 = true;
		}
	}

	if ((trigger1) && (vehicle_stolen) && (!alarm_on))
	{
		alarm_on = true;
	}
	if ((trigger1) && (!vehicle_stolen) && (!alarm_on))
	{
		alarm_on = true;
		alarm_special = true;
	}
}
// end parachute into base
// the following code triggers the solar array alarm if the player orders ANY of his units to attack the gun towers protecting it
if (!first_objective)
{		
		if ((!alarm_on) && (!out_of_car) && (GetDistance(wingman1, turret1_spot) < 100.0f))
		{
			AudioMessage("misn0709.wav"); //I've tripped the alarm sir
			alarm_on = true;
		}

		if ((!alarm_on) && (!out_of_car) && (GetDistance(wingman2, turret1_spot) < 100.0f))
		{
			AudioMessage("misn0709.wav"); //I've tripped the alarm sir
			alarm_on = true;
		}

		if ((!alarm_on) && (!out_of_car) && (GetDistance(wingtank1, turret1_spot) < 100.0f))
		{
			AudioMessage("misn0709.wav"); //I've tripped the alarm sir
			alarm_on = true;
		}

		if ((!alarm_on) && (!out_of_car) && (GetDistance(new_tank1, turret1_spot) < 100.0f))
		{
			AudioMessage("misn0709.wav"); //I've tripped the alarm sir
			alarm_on = true;
		}

		if ((!alarm_on) && (!out_of_car) && (GetDistance(new_tank2, turret1_spot) < 100.0f))
		{
			AudioMessage("misn0709.wav"); //I've tripped the alarm sir
			alarm_on = true;
		}

/*		if ((!alarm_on) && (!out_of_car) && (GetDistance(wingturret1, turret1_spot) < 100.0f))
		{
			AudioMessage("misn0709.wav"); //I've tripped the alarm sir
			alarm_on = true;
		}

		if ((!alarm_on) && (!out_of_car) && (GetDistance(wingturret2, turret1_spot) < 100.0f))
		{
			AudioMessage("misn0709.wav"); //I've tripped the alarm sir
			alarm_on = true;
		}

*/
}
// end of alarm trigger for other vehicles //////////////////////////////////////////////////////////
// this is an attempt to make the soviets retreat ///////////////////////////////////////////////////
if (!first_objective)
{
	if (!retreat_success)
	{
		if (IsAlive(svpatrol1_2))
		{
			if ((!IsAlive (svpatrol1_1)) && (rendezvous) && (IsAlive(ccarecycle)) && (!first_objective) 
				&& (!mine_pathed) && (!alarm_on) && (GetDistance(user,svpatrol1_2) < 50.0f)  && (!p1_retreat)
				&& (!p2_retreat) && (!p3_retreat))
			{
				Retreat(svpatrol1_2, ccarecycle);
				SetObjectiveOn(svpatrol1_2);
				SetObjectiveName(svpatrol1_2, "Runner");
				getaway_message_time = Get_Time() + 3.0f;
				p1_retreat = true;
			}
		}

		if (IsAlive(svpatrol1_1))
		{
			if ((!IsAlive (svpatrol1_2)) && (rendezvous) && (IsAlive(ccarecycle)) && (!first_objective) 
				&& (!mine_pathed) && (!alarm_on) && (GetDistance(user,svpatrol1_1) < 50.0f)  && (!p1_retreat)
				&& (!p2_retreat) && (!p3_retreat))
			{
				Retreat(svpatrol1_1, ccarecycle);
				SetObjectiveOn(svpatrol1_1);
				SetObjectiveName(svpatrol1_1, "Runner");
				getaway_message_time = Get_Time() + 3.0f;
				p1_retreat = true;
			}
		}

/*		if ((!IsAlive (svpatrol2_1)) && (rendezvous) && (IsAlive(ccarecycle)) && (!first_objective) 
			&& (!mine_pathed) && (!alarm_on) && (GetDistance(user,svpatrol2_2) < 50.0f)  && (!p2_retreat)
			&& (!p1_retreat) && (!p3_retreat))
		{
			Retreat(svpatrol2_2, ccarecycle);
			SetObjectiveOn(svpatrol2_2);
			SetObjectiveName(svpatrol2_2, "Runner");
			getaway_message_time = Get_Time() + 3.0f;
			p2_retreat = true;
		}

		if ((!IsAlive (svpatrol2_2)) && (rendezvous) && (IsAlive(ccarecycle)) && (!first_objective) 
			&& (!mine_pathed) && (!alarm_on) && (GetDistance(user,svpatrol2_1) < 50.0f)  && (!p2_retreat)
			&& (!p1_retreat) && (!p3_retreat))
		{
			Retreat(svpatrol2_1, ccarecycle);
			SetObjectiveOn(svpatrol2_1);
			SetObjectiveName(svpatrol2_1, "Runner");
			getaway_message_time = Get_Time() + 3.0f;
			p2_retreat = true;
		}
*/
		if (IsAlive(svpatrol3_2))
		{
			if ((!IsAlive (svpatrol3_1)) && (rendezvous) && (IsAlive(ccarecycle)) && (!first_objective) 
				&& (!mine_pathed) && (!alarm_on) && (GetDistance(user,svpatrol3_2) < 50.0f)  && (!p2_retreat)
				&& (!p1_retreat) && (!p3_retreat))
			{
				Retreat(svpatrol3_2, ccarecycle);
				SetObjectiveOn(svpatrol3_2);
				SetObjectiveName(svpatrol3_2, "Runner");
				getaway_message_time = Get_Time() + 3.0f;
				p3_retreat = true;
			}
		}

		if (IsAlive(svpatrol3_1))
		{
			if ((!IsAlive (svpatrol3_2)) && (rendezvous) && (IsAlive(ccarecycle)) && (!first_objective) 
				&& (!mine_pathed) && (!alarm_on) && (GetDistance(user,svpatrol3_1) < 50.0f)  && (!p2_retreat)
				&& (!p1_retreat) && (!p3_retreat))
			{
				Retreat(svpatrol3_1, ccarecycle);
				SetObjectiveOn(svpatrol3_1);
				SetObjectiveName(svpatrol3_1, "Runner");
				getaway_message_time = Get_Time() + 3.0f;
				p3_retreat = true;
			}
		}

	// this is the player being warned when one is getting away.
if ((!retreat_success) && (!getum))
{
		if (((p1_retreat) && (getaway_message_time < Get_Time()) 
			&& (IsAlive(new_tank1)) && (!getum)) || 
			((p1_retreat) && (getaway_message_time < Get_Time()) 
			&& (IsAlive(new_tank2)) && (!getum)))
		{
			AudioMessage("misn0705.wav");// one of'ms making a break for it!
			getum = true;
		}

		if (((p2_retreat) && (getaway_message_time < Get_Time()) 
			&& (IsAlive(new_tank1)) && (!getum)) || 
			((p2_retreat) && (getaway_message_time < Get_Time()) 
			&& (IsAlive(new_tank2)) && (!getum)))
		{
			AudioMessage("misn0705.wav");// one of'ms making a break for it!
			getum = true;
		}
		
		if (((p3_retreat) && (getaway_message_time < Get_Time()) 
			&& (IsAlive(new_tank1)) && (!getum)) ||
			((p3_retreat) && (getaway_message_time < Get_Time()) 
			&& (IsAlive(new_tank2)) && (!getum)))
		{
			AudioMessage("misn0705.wav");// one of'ms making a break for it!
			getum = true;
		}
}

	// this is to set up the "that's gotum" message

		if ((p1_retreat) && (IsAlive(svpatrol1_1)))
		{
			patrola1 = true;
		}

		if ((p1_retreat) && (IsAlive(svpatrol1_2)))
		{
			patrola2 = true;
		}

		if ((p2_retreat) && (IsAlive(svpatrol2_1)))
		{
			patrolb1 = true;
		}

		if ((p2_retreat) && (IsAlive(svpatrol2_2)))
		{
			patrolb2 = true;
		}

		if ((p3_retreat) && (IsAlive(svpatrol3_1)))
		{
			patrolc1 = true;
		}

		if ((p3_retreat) && (IsAlive(svpatrol3_2)))
		{
			patrolc2 = true;
		}

		if (((p1_retreat) && (patrola1) && (!IsAlive(svpatrol1_1)) && (IsAlive(new_tank1))) ||
			((p1_retreat) && (patrola1) && (!IsAlive(svpatrol1_1)) && (IsAlive(new_tank2))))
		{
			AudioMessage("misn0706.wav"); // that got'um!
//			SetObjectiveOff(svpatrol1_1);
			p1_retreat = false;
			patrola1 = false;
			getum = false;
		}

		if (((p1_retreat) && (patrola2) && (!IsAlive(svpatrol1_2)) && (IsAlive(new_tank1))) ||
			((p1_retreat) && (patrola2) && (!IsAlive(svpatrol1_2)) && (IsAlive(new_tank2))))
		{
			AudioMessage("misn0706.wav"); // that got'um!
//			SetObjectiveOff(svpatrol1_2);
			p1_retreat = false;
			patrola2 = false;
			getum = false;
		}

		if (((p2_retreat) && (patrolb1) && (!IsAlive(svpatrol2_1)) && (IsAlive(new_tank1))) ||
			((p2_retreat) && (patrolb1) && (!IsAlive(svpatrol2_1)) && (IsAlive(new_tank2))))
		{
			AudioMessage("misn0706.wav"); // that got'um!
//			SetObjectiveOff(svpatrol2_1);
			p2_retreat = false;
			patrolb1 = false;
			getum = false;
		}

		if (((p2_retreat) && (patrolb2) && (!IsAlive(svpatrol2_2)) && (IsAlive(new_tank1))) ||
			((p2_retreat) && (patrolb2) && (!IsAlive(svpatrol2_2)) && (IsAlive(new_tank2))))
		{
			AudioMessage("misn0706.wav"); // that got'um!
//			SetObjectiveOff(svpatrol2_2);
			p2_retreat = false;
			patrolb2 = false;
			getum = false;
		}

		if (((p3_retreat) && (patrolc1) && (!IsAlive(svpatrol3_1)) && (IsAlive(new_tank1))) ||
			((p3_retreat) && (patrolc1) && (!IsAlive(svpatrol3_1)) && (IsAlive(new_tank2))))
		{
			AudioMessage("misn0706.wav"); // that got'um!
//			SetObjectiveOff(svpatrol3_1);
			p3_retreat = false;
			patrolc1 = false;
			getum = false;
		}

		if (((p3_retreat) && (patrolc2) && (!IsAlive(svpatrol3_2)) && (IsAlive(new_tank1))) ||
			((p3_retreat) && (patrolc2) && (!IsAlive(svpatrol3_2)) && (IsAlive(new_tank2))))
		{
			AudioMessage("misn0706.wav"); // that got'um!
//			SetObjectiveOff(svpatrol3_2);
			p3_retreat = false;
			patrolc2 = false;
			getum = false;
		}

	}

	// this is what happens if an enemy unit gets away - tanks will come out

		if ((patrola1) && (!retreat_success) && (!alarm_on)
			&& (GetDistance(svpatrol1_1, ccarecycle) < 100.0f)
			&& (ccarecycle!=NULL) && (IsAlive(ccarecycle)))
		{
			SetObjectiveOff(svpatrol1_1);		
			retreat_success = true;
		}

		if ((patrola2) && (!retreat_success) && (!alarm_on) 
			&& (GetDistance(svpatrol1_2, ccarecycle) < 100.0f)
			&& (ccarecycle!=NULL) && (IsAlive(ccarecycle)))
		{
			SetObjectiveOff(svpatrol1_2);
			retreat_success = true;
		}

		if ((patrolb1) && (!retreat_success) && (!alarm_on) 
			&& (GetDistance(svpatrol2_1, ccarecycle) < 100.0f)
			&& (ccarecycle!=NULL) && (IsAlive(ccarecycle)))
		{
			SetObjectiveOff(svpatrol2_1);
			retreat_success = true;
		}

		if ((patrolb2) && (!retreat_success) && (!alarm_on) 
			&& (GetDistance(svpatrol2_2, ccarecycle) < 100.0f)
			&& (ccarecycle!=NULL) && (IsAlive(ccarecycle)))
		{
			SetObjectiveOff(svpatrol2_2);
			retreat_success = true;
		}

		if ((patrolc1) && (!retreat_success) && (!alarm_on) 
			&& (GetDistance(svpatrol3_1, ccarecycle) < 100.0f)
			&& (ccarecycle!=NULL) && (IsAlive(ccarecycle)))
		{
			SetObjectiveOff(svpatrol3_1);
			retreat_success = true;
		}

		if ((patrolc2) && (!retreat_success) && (!alarm_on) 
			&& (GetDistance(svpatrol3_2, ccarecycle) < 100.0f)
			&& (ccarecycle!=NULL) && (IsAlive(ccarecycle)))
		{
			SetObjectiveOff(svpatrol3_2);
			retreat_success = true;
		}

	// this is the message that they were detected
		if (((retreat_success) && (IsAlive(new_tank1)) && (!detected_message)) ||
			((retreat_success) && (IsAlive(new_tank2)) && (!detected_message)))
		{
			AudioMessage("misn0707.wav");// one of the runers has made it back
			detected_message = true;
		}
			// now that the player is detetected the soviets will send tanks out to scout
			if ((retreat_success) && (!IsAlive(svpatrol1_1)) 
				&& (!IsAlive(svpatrol1_2)) && (!IsAlive(svpatrol1_3)) && (IsAlive(ccarecycle)))
			{																			
				svpatrol1_1 = BuildObject("svtank", 2, ccarecycle);
				svpatrol1_2 = BuildObject("svtank", 2, ccarecycle);
//				svpatrol1_3 = BuildObject("svtank", 2, ccarecycle);
				Patrol(svpatrol1_1, "patrol_path1");
				Patrol(svpatrol1_2, "patrol_path1");
//				Patrol(svpatrol1_3, "patrol_path1");
			}																				
																						
/*			if ((retreat_success) && (!IsAlive(svpatrol2_1)) && 
				(!IsAlive(svpatrol2_2)) && (!IsAlive(svpatrol2_3)) && (IsAlive(ccarecycle)))

			{																					
				svpatrol2_1 = BuildObject("svtank", 2, ccarecycle);
				svpatrol2_2 = BuildObject("svtank", 2, ccarecycle);
				svpatrol2_3 = BuildObject("svtank", 2, ccarecycle);
				Patrol(svpatrol2_1, "patrol_path1");	
				Patrol(svpatrol2_2, "patrol_path1");
				Patrol(svpatrol2_3, "patrol_path1");
			}																					
*/																							
			if ((retreat_success) && (!IsAlive(svpatrol3_1)) 
				&& (!IsAlive(svpatrol3_2)) && (!IsAlive(svpatrol3_3)) && (IsAlive(ccarecycle)))
			{																					
				svpatrol3_1 = BuildObject("svtank", 2, ccarecycle);
				svpatrol3_2 = BuildObject("svtank", 2, ccarecycle);
//				svpatrol3_3 = BuildObject("svtank", 2, ccarecycle);
				Patrol(svpatrol3_1, "patrol_path1");
				Patrol(svpatrol3_2, "patrol_path1");
//				Patrol(svpatrol3_3, "patrol_path1");
			}																					
																								
//			if ((retreat_success) && (!IsAlive(svpatrol4_1)) && 
//				(!IsAlive(svpatrol4_2)) && (IsAlive(ccarecycle)))	
//			{																				
//				svpatrol4_1 = BuildObject("svtank", 2, ccarecycle);								
//				svpatrol4_2 = BuildObject("svtank", 2, ccarecycle);								
//				Patrol(svpatrol4_1, "patrol_path2");											
//				Patrol(svpatrol4_2, "patrol_path2");											
//			}
}
		
// end of retreat code /////////////////////////////////////////
// building more patrol ships if patrol ships are lost /////////////////////////////////////
if (!first_objective)
{																							
	if ((!IsAlive(svpatrol1_1)) && (!IsAlive(svpatrol1_2)) && (IsAlive(ccarecycle)) && (!detected))   
	{																				
		svpatrol1_1 = BuildObject("svfigh", 2, ccarecycle);							
		svpatrol1_2 = BuildObject("svfigh", 2, ccarecycle);						
		Patrol(svpatrol1_1, "patrol_path1");									
		Patrol(svpatrol1_2, "patrol_path1");									
		p1_retreat = false;	
		getum = false;
		patrola1 = false;
		patrola2 = false;
	}																				
																				
/*	if ((!IsAlive(svpatrol2_1)) && (!IsAlive(svpatrol2_2)) && (IsAlive(ccarecycle)) && (!detected))	
	{																					
		svpatrol2_1 = BuildObject("svfigh", 2, ccarecycle);								
		svpatrol2_2 = BuildObject("svfigh", 2, ccarecycle);						
		Patrol(svpatrol2_1, "patrol_path1");										
		Patrol(svpatrol2_2, "patrol_path1");
		p2_retreat = false;
		getum = false;
		patrolb1 = false;
		patrolb2 = false;
	}																					
*/																					
	if ((!IsAlive(svpatrol3_1)) && (!IsAlive(svpatrol3_2)) && (IsAlive(ccarecycle)) && (!detected))
	{																					
		svpatrol3_1 = BuildObject("svfigh", 2, ccarecycle);								
		svpatrol3_2 = BuildObject("svfigh", 2, ccarecycle);								
		Patrol(svpatrol3_1, "patrol_path1");											
		Patrol(svpatrol3_2, "patrol_path1");
		p3_retreat = false;	
		getum = false;	
		patrolc1 = false;
		patrolc2 = false;
	}																					
																						
	if ((!IsAlive(svpatrol4_1)) && (!IsAlive(svpatrol4_2)) && (IsAlive(ccarecycle)))	
	{																				
		svpatrol4_1 = BuildObject("svfigh", 2, ccarecycle);								
		svpatrol4_2 = BuildObject("svfigh", 2, ccarecycle);								
		Patrol(svpatrol4_1, "patrol_path2");											
		Patrol(svpatrol4_2, "patrol_path2");											
	}
}
																							
// end of scout building code ////////////////////////////////////////////////////////////////
// this is what happens when the player reaches the jump overlook - the rookie tells him about the test range
/*
	if ((recon_message2_time < Get_Time()) && (!recon_message2))
	{
		recon_message2_time = Get_Time() + 20.0f;
		
		if ((!test_found) && (!recon_message2))
		{
			AudioMessage("misn0703.wav"); // rookie "I found a soviet test range
			becon_build_time = Get_Time() + 15.0f;
			check_range = Get_Time() + 20.0f;
			recon_message2 = true;
		}
	}
				
	if ((recon_message2) && (becon_build_time < Get_Time()) && (!becon_build))//rookie lays path through mines
	{
		nav4 = BuildObject ("apcamr", 1, "cam_spawn6");
		rookie_rendezvous_time = Get_Time() + 120.0f;
		becon_build = true;
	}

	if ((becon_build) && (nav4!=NULL))
	{
		GameObjectHandle::GetObj(nav4)->SetName("Testing Range");
	}

// this is how the rookie tells the player he's under attack

	if ((becon_build) && (rookie_rendezvous_time < Get_Time()) && (!rookie_lost))
	{
		rookie_rendezvous_time = Get_Time()	+ 21.0f;	

		if ((GetDistance (user, mine_geyz) > 400.0f) && (!rookie_lost))
		{
			AudioMessage("misn0704.wav"); // I'm under attack - I'll drop the a camera - goto to activate mine path
			nav5 = BuildObject ("apcamr", 1, "cam_spawn1");
			reach_mine_time = Get_Time() + 10.0f;
			rookie_lost = true;
		}
	}

	if ((rookie_lost) && (nav5!=NULL))
	{
		GameObjectHandle::GetObj(nav5)->SetName("Mine Field");
	}

	if ((rookie_lost) && (reach_mine_time < Get_Time()) && (!mine_pathed))
	{
		reach_mine_time = Get_Time() + 10.0f;
			
		if ((GetDistance(user, nav5) < 70.0f) && (!mine_pathed))
		{
			becon1 = BuildObject ("apcamr", 1, "cam_spawn2");
			becon2 = BuildObject ("apcamr", 1, "cam_spawn3");
			becon3 = BuildObject ("apcamr", 1, "cam_spawn4");
			becon4 = BuildObject ("apcamr", 1, "cam_spawn5");
			mine_pathed = true;
		}
	}

		if ((mine_pathed) && (becon1!=NULL))
		{
			GameObjectHandle::GetObj(becon1)->SetName("Mine Path 1");
		}
		if ((mine_pathed) && (becon2!=NULL))
		{
			GameObjectHandle::GetObj(becon2)->SetName("Mine Path 2");
		}
		if ((mine_pathed) && (becon3!=NULL))
		{
			GameObjectHandle::GetObj(becon3)->SetName("Mine Path 3");
		}
		if ((mine_pathed) && (becon4!=NULL))
		{
			GameObjectHandle::GetObj(becon4)->SetName("Mine Path 4");
		}

*/
// end of rookie message about soviet test range /////////
// when the radar array is destroyed /////////////////////
														
	if ((!IsAlive(ccacomtower)) && (!first_objective))	
	{													
		audmsg = AudioMessage ("misn0714.wav");						
		radar_camera_time = Get_Time() + 10.0f;
//		next_shot_time = Get_Time() + 20.0f;
		next_mission_time = Get_Time() + 7.5f;
//		CameraReady();
//		shot1 = true;
		first_objective = true;							
	}
	
/*	if (shot1)
	{
		CameraPath("radar_path", 4000, 1000, radar_geyser);
	}

	if ((shot1) && (radar_camera_time < Get_Time()))
	{
//		StopAudioMessage(audmsg);
//		audmsg = AudioMessage ("misn0714.wav");	
		shot1 = false;
		shot2 = true;
	}

	if (shot2)
	{
		CameraPath("movie_cam_spawn", 160, 0, show_geyser);
	}

	if ((!radar_camera_off) && (shot2) && (next_shot_time < Get_Time()))
	{
//		StopAudioMessage(audmsg);
		CameraFinish();
		shot2 = false;
		radar_camera_off = true;
	}

	if (((shot1) || (shot2)) && (!radar_camera_off))
	{
		if (CameraCancelled())
		{
			shot1 = false;
			shot2 = false;
//			StopAudioMessage(audmsg);
			CameraFinish();
			radar_camera_off = true;
		}
	}
*/
	if ((first_objective) && (!next_mission) && (next_mission_time < Get_Time()))
	{
		nsdfrecycle = BuildObject("avrec7", 1, "recycle_spawn");
		nsdfmuf = BuildObject("avmu7", 1, "muf_spawn");
		Goto(nsdfrecycle, "recycle_path", 0);
		Goto(nsdfmuf, "muf_path", 0);
		nav6 = BuildObject ("apcamr", 1, "recycle_cam_spawn");	
		nav7 = BuildObject ("apcamr", 1, "recy_cam_spawn"); 
		if (nav6!=NULL) GameObjectHandle::GetObj(nav6)->SetName("Utah Rendezvous");
		if (nav7!=NULL) GameObjectHandle::GetObj(nav7)->SetName("CCA BASE");
		AddScrap(1, 30);
		SetPilot(1, 20);
		AddScrap(2, 60);
		SetPilot(2, 40);
		SetAIP("misn07.aip");
//		SetObjectiveOn(recycler);
//		SetObjectiveName(recycler, "Utah");
		ccabaseguntower1 = BuildObject("sbtowe", 2, "base_tower1_spawn");
//		ccabaseguntower2 = BuildObject("sbtowe", 2, "base_tower2_spawn");
		ClearObjectives();
		AddObjective("misn0701.otf", GREEN);
		AddObjective("misn0703.otf", WHITE);
		AddObjective("misn0702.otf", WHITE);
		next_mission = true;
	}

	if ((next_mission) && (!IsAlive(ccarecycle)))
	{
		second_objective = true;
	}

	if ((next_mission) && (!utah_found))
	{
		if (IsAlive(nsdfrecycle))
		{
			bool test=((Factory *) GameObjectHandle::GetObj(nsdfrecycle))->IsDeployed();
			if (test)
			{
				ClearObjectives();
				AddObjective("misn0703.otf", GREEN);
				AddObjective("misn0702.otf", WHITE);
				utah_found = true;
			}
		}
	}

// here is an attempt at the mine code ////////////
/*
	for (count = mine_check; count < mine_check + 10; count = count + 1)
	{
		if (GetDistance(user, mine[count]) < 400.0f)
		{
			if ((!m_on[count]) && (!m_dead[count]))
			{
				m[count] = BuildObject ("proxmine", 2, mine[count]);
				m_on[count] = true;
			}
			if ((m_on[count]) && (!IsAlive(m[count])))
			{
				m_dead[count] = true;
			}
		}
		else
		{
			if ((m_on[count]) && (!m_dead[count]))
			{
				RemoveObject(m[count]);
				m_on[count] = false;
			}
		}
	}
*/
// this is the code that operates the MAG cannon and camera when the player encounters it
/*
	if ((recon_message2) && (GetDistance(user, test_tank) < 65.0f) 
		&& (!camera_ready))
	{															
		CameraReady();
		GameObjectHandle:: GetObj(test_turret)->AddHealth(-950.0f); 
		camera_ready = true;									
	}															
																
	if ((camera_ready) && (!camera1_on))
	{															
		CameraObject(test_tank, 2000, 800, 500, user);
		AudioMessage("misn0711.wav");
		start_sound = Get_Time() + 8.0f;
		change_angle = Get_Time() + 6.0f;
		camera1_on = true;
	}

	if ((camera1_on) && (change_angle < Get_Time()) && (!camera3_on))
	{
		CameraPath("camera_path1", 250,  250, test_tank);
		camera2_on = true;
	}

	if ((camera2_on) && (!camera2_oned))
	{
		change_angle1 = Get_Time() + 8.0f;
		camera2_oned = true;
	}

	if ((change_angle1 < Get_Time()) && (!camera4_on))
	{
		CameraPath("camera_path2", 310, 500, test_turret);
		camera3_on = true;
	}

	if ((camera3_on) && (!camera3_oned))
	{
		change_angle2 = Get_Time() + 6.0f;
		switch_tank = Get_Time() + 5.0f;
		camera3_oned = true;
	}

	if ((switch_tank < Get_Time()) && (!tank_switch))
	{
		RemoveObject(test_tank);
		test_tank = BuildObject("svtnk7", 2, "test_tank_spawn");
		Attack(test_tank, test_turret);
		tank_switch = true;
	}
	
//	if ((change_angle2 < Get_Time()) && (!camera4_on))
//	{
//		CameraObject(test_tank, -300, 400,-750, test_turret);
//		change_angle3 = Get_Time() + 10.0f;
//		camera4_on = true;
//	}
	
	if ((change_angle2 < Get_Time()) && (!camera4_on))
	{
		CameraObject(test_turret, 1000, 300, 4700, test_turret);
		change_angle3 = Get_Time() + 10.0f;
		camera4_on = true;
	}

	if ((camera4_on) && (change_angle3 < Get_Time()) && (!camera_off))
	{
		CameraFinish();											
		camera_off = true;
	}
*/

// win/loose conditions ///////////////////

	if ((next_mission) && (!IsAlive(nsdfrecycle)) && (!game_over))
	{
		AudioMessage("misn0712.wav");
		if (!utah_found)
		{
			ClearObjectives();
			AddObjective("misn0701.otf", GREEN);
			AddObjective("misn0703.otf", RED);
			AddObjective("misn0702.otf", WHITE);
		}
		FailMission(Get_Time() + 15.0f, "misn07f1.des");
		game_over = true;
	}
											
	if ((next_mission) && (!IsAlive(ccarecycle)))
	{
		second_objective = true;
	}
	
	if ((first_objective) && (second_objective) && (!game_over))
	{
		AudioMessage("misn0713.wav");
		SucceedMission(Get_Time() + 15.0f, "misn07w1.des");
		game_over = true;
	}
	
//////////////////////////////////////////////////////////
// END OF SCRIPT
}
