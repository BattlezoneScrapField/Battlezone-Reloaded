#include "ScriptUtils.h"

#include <crtdbg.h>

/*
	Misn03Mission
*/


class Misn03Mission {
public:
	Misn03Mission(void);
	~Misn03Mission();

	bool Load(void);
	bool PostLoad(void);
	bool Save(void);

	void Update(void);

	void AddObject(Handle h);

private:
	void Setup(void);
	void Execute(void);

	// bools
	union {
		struct {
			bool
				first_wave_done,
				second_wave_done,
				third_wave_done,
				fourth_wave_done,
				fifth_wave_done,
				turret_move_done,
				rescue_move_done,
				help_spawn,
				help_arrive,
				end_game,
				trans_underway,
				ambush_message,
				start_done,
				first_objective,
				second_objective,
				third_objective,
				final_objective,
				special_objective,
				start_retreat,
				done_retreat,
				new_message_start,
				dead1,
				dead2,
				dead3,
				camera_on,
				camera_off,
				help_stop1, help_stop2,
				recycle_stop,
				message1, scavhunt, scavhunt2,
				lost, // since there are many ways you can loose we will make loosing a boolean
				camera_ready, start_movie, movie_over, remove_props, more_show,
				tanks_go, camera_2, show_tank_attack, tower_dead, climax1, climax2,
				clear_debis, last_blown, end_shot, clean_sweep, startfinishingmovie, turrets_set, speach2,
				second_warning, last_warning,
				b_last;
		};
		bool b_array[53];
	};

	// floats
	union {
		struct {
			float
				next_second,
				retreat_timer, 
				next_wave, 
				second_wave_time, 
				ambush_message_time, 
				new_message_time, 
				apc_spawn_time, 
				pull_out_time,
				third_wave_time, 
				fourth_wave_time, 
				fifth_wave_time, 
				turret_move_time,
				wave3_time, 
				wave4_time, 
				camera_off_time,
				support_time,
				movie_time,
				new_unit_time,
				next_shot,
				kill_tower,
				clear_debis_time,
				unit_check,
				clean_sweep_time,
				final_check,
				f_last;
		};
		float f_array[24];
	};

	// handles
	union {
		struct {
			Handle
				user,
				avrecycler,
				geyser, cam_geyser, shot_geyser,
				scav1, scav2, scav3, scav4, scav5, scav6, crate1, crate2, crate3,
				rescue1, rescue2, rescue3,
				wave1_1, wave1_2, wave1_3,
				wave2_1, wave2_2, wave2_3,
				wave3_1, wave3_2, wave3_3,
				wave4_1, wave4_2, wave4_3,
				wave5_1, wave5_2, wave5_3,
				wave6_1, wave6_2, wave6_3,
				wave7_1, wave7_2, wave7_3, wave7_4, wave7_5, wave7_6,
				turret1, turret2, turret3, turret4,
				spawn_point1, spawn_point2,
				launch, nest, solar1, solar2, solar3, solar4,
				help1, help2,
				build1, build2, build3, build4, build5, hanger,
				prop1, prop2, prop3, prop4, prop5, prop6, prop7, prop8, prop9, prop0,
				guy1, guy2, guy3, guy4, box1, sucker,
				avturret1, avturret2, avturret3, avturret4, avturret5, avturret6, avturret7, avturret8, avturret9, avturret10, 
				h_last;
		};
		Handle h_array[87];
	};

	// integers
	union {
		struct {
			int
				x, z, y,
				audmsg,
				i_last;
		};
		int i_array[4];
	};
};

bool missionSave;
Misn03Mission *mission;

void Misn03Mission::Setup(void)
{
/*
Here's where you set the values at the start.  
*/
	x = 4000;
	z = 1;
	y = 1;

	first_wave_done = false;
	second_wave_done = false;	
	third_wave_done = false;	
	fourth_wave_done = false;
	fifth_wave_done = false;
	turret_move_done = false;
	new_message_start = false;
	rescue_move_done = false;
	trans_underway = false;
	ambush_message = false;
	start_done = false;
	first_objective = false;
	second_objective = false;
	third_objective = false;
	special_objective = false;
	final_objective = false;
	end_game = false;
	help_spawn = false;
	help_arrive = false;
	start_retreat = false;
	done_retreat = false;
	dead1 = false;
	dead2 = false;
	dead3 = false;
	camera_on = false;
	camera_off = false;
	lost = false;
	help_stop1 = false;
	help_stop2 = false;
	recycle_stop = false;
	message1 = false;
	scavhunt = false;
	scavhunt2 = false;
	camera_ready = false;
	start_movie = false;
	movie_over = false;
	remove_props = false;
	more_show = false;
	tanks_go = false;
	camera_2 = false;
	show_tank_attack = false;
	tower_dead = false;
	climax1 = false;
	climax2 = false;
	clear_debis = false;
	last_blown = false;
	end_shot = false;
	clean_sweep = false;
	startfinishingmovie = false;
	turrets_set = false;
	speach2 = false;
	second_warning = false;
	last_warning = false;

	second_wave_time = 99999.0f;
	third_wave_time = 99999.0f;
	fourth_wave_time = 99999.0f;
	fifth_wave_time = 99999.0f;
	turret_move_time = 99999.0f;
	next_wave = 99999.0f;
	new_message_time = 99999.0f;
	apc_spawn_time = 99999.0f;
	pull_out_time = 99999.0f;
	ambush_message_time = 99999.0f;
	camera_off_time = 99999.0f;
	support_time = 99999.0f;
	movie_time = 99999.0f;
	new_unit_time = 99999.0f;
	next_shot = 99999.0f;
	kill_tower = 99999.0f;
	clear_debis_time = 99999.0f;
	unit_check = 99999.0f;
	clean_sweep_time = 99999.0f;
	final_check = 99999.0f;

	user = 0;
	avrecycler = GetHandle ("avrec3-1_recycler");
	scav1 = GetHandle ("scav1");
	scav2 = GetHandle ("scav2");
	wave1_1 = GetHandle ("svfigh1");
	wave1_2 = GetHandle ("svfigh2");	
//	wave1_3 = GetHandle ("svfigh3");	
	wave1_3 = 0;
	turret1 = GetHandle ("enemyturret_1");
	turret2 = GetHandle ("enemyturret_2");
	turret3 = GetHandle ("enemyturret_3");
	turret4 = GetHandle ("enemyturret_4");
	geyser = GetHandle ("geyser1");
	solar1 = GetHandle ("solar1");
	solar2 = GetHandle ("solar2");
	solar3 = GetHandle ("solar3");
	solar4 = GetHandle ("solar4");
	launch = GetHandle ("launch_pad");
	build1 = GetHandle ("build1");
//	build2 = GetHandle ("build2");
	build3 = GetHandle ("build3");
	build4 = GetHandle ("build4");
	build5 = GetHandle ("build5");
	hanger = GetHandle ("hanger");
	cam_geyser = GetHandle ("cam_geyser");
	shot_geyser = GetHandle ("shot_geyser");
	box1 = GetHandle ("box1");
	crate1 = GetHandle ("crate1");
	crate2 = GetHandle ("crate2");
	crate3 = GetHandle ("crate3");
	guy1 = NULL;
	guy2 = NULL;
	audmsg = 0;
	scav3 = NULL;
	scav4 = NULL;
	scav5 = NULL;
	scav6 = NULL;
	rescue1 = NULL;
	rescue2 = NULL;
	rescue3 = NULL;
	wave2_1 = NULL;
	wave2_2 = NULL;
	wave2_3 = NULL;
	wave3_1 = NULL;
	wave3_2 = NULL;
	wave3_3 = NULL;
	wave4_1 = NULL;
	wave4_2 = NULL;
	wave4_3 = NULL;
	wave5_1 = NULL;
	wave5_2 = NULL;
	wave5_3 = NULL;
	wave6_1 = NULL;
	wave6_2 = NULL;
	wave6_3 = NULL;
	wave7_1 = NULL;
	wave7_2 = NULL;
	wave7_3 = NULL;
	wave7_4 = NULL;
	wave7_5 = NULL;
	wave7_6 = NULL;
	help1 = NULL;
	help2 = NULL;
	prop1 = NULL;
	prop2 = NULL;
	prop3 = NULL;
	prop4 = NULL;
	prop5 = NULL;
	prop6 = NULL;
	prop7 = NULL;
	prop8 = NULL;
	prop9 = NULL;
	prop0 = NULL;
	sucker = NULL;
	avturret1 = NULL;
	avturret2 = NULL;
	avturret3 = NULL;
	avturret4 = NULL;
	avturret5 = NULL;
	avturret6 = NULL;
	avturret7 = NULL;
	avturret8 = NULL;
	avturret9 = NULL;
	avturret10 = NULL;
	guy3 = NULL;
	guy4 = NULL;
	spawn_point1 = 0;
	spawn_point2 = 0;
	nest = 0;
}

void Misn03Mission::AddObject(Handle h)
{
	if ((avturret1 == NULL) && (IsOdf(h,"avturr")))
	{
		avturret1 = h;
	}
	else
	{
		if ((avturret2 == NULL) && (IsOdf(h,"avturr")))
		{
			avturret2 = h;
		}
		else
		{
			if ((avturret3 == NULL) && (IsOdf(h,"avturr")))
			{
				avturret3 = h;
			}
			else
			{
				if ((avturret4 == NULL) && (IsOdf(h,"avturr")))
				{
					avturret4 = h;
				}
				else
				{
					if ((avturret5 == NULL) && (IsOdf(h,"avturr")))
					{
						avturret5 = h;
					}
					else
					{
						if ((avturret6 == NULL) && (IsOdf(h,"avturr")))
						{
							avturret6 = h;
						}
						else
						{
							if ((avturret7 == NULL) && (IsOdf(h,"avturr")))
							{
								avturret7 = h;
							}
							else
							{
								if ((avturret8 == NULL) && (IsOdf(h,"avturr")))
								{
									avturret8 = h;
								}
								else
								{
									if ((scav3 == NULL) && (IsOdf(h,"avscav")))
									{
										scav3 = h;
									}
									else
									{
										if ((avturret9 == NULL) && (IsOdf(h,"avturr")))
										{
											avturret9 = h;
										}
										else
										{
											if ((avturret10 == NULL) && (IsOdf(h,"avturr")))
											{
												avturret10 = h;
											}
											else
											{
												if ((scav4 == NULL) && (IsOdf(h,"avscav")))
												{
													scav4 = h;
												}
												else
												{
													if ((scav5 == NULL) && (IsOdf(h,"avscav")))
													{
														scav5 = h;
													}
													else
													{
														if ((scav6 == NULL) && (IsOdf(h,"avscav")))
														{
															scav6 = h;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void Misn03Mission::Execute(void)
{

	user = GetPlayerHandle(); //assigns the player a handle every frame

	if (!start_done)
	{	
		SetScrap (1, 8);
		SetPilot(1, 10);

		SetObjectiveOn(solar1);
		SetObjectiveName(solar1, "Command Tower");

		SetObjectiveOn(solar2);
		SetObjectiveName(solar2, "Solar Array");

		Goto(avrecycler, "recycle_point");
		ClearObjectives();
		AddObjective("misn0301.otf", WHITE);		
		second_wave_time = Get_Time() + 200.0f;
		third_wave_time = Get_Time() + 310.0f;
		fourth_wave_time = Get_Time() + 430.0f;
		apc_spawn_time = Get_Time() + 530.0f;
		support_time = Get_Time() + 430.0f;
		next_second = GetTime() + 1.0f;
		unit_check = Get_Time() + 60.0f;
		start_done = true;
	}
	
	if ((IsAlive(solar1)) && (!show_tank_attack))
		{
			if (GetTime()>next_second)
			{
				AddHealth(solar1, 50);
				next_second=GetTime()+1.0f;
			}
		}

	if ((!message1) && (start_done))
	{
		audmsg = AudioMessage("misn0311.wav");
		message1 = true;
	}

	if ((start_done) && (GetDistance(avrecycler, "recycle_point") < 50.0f) && (!recycle_stop))
	{
		Stop(avrecycler, 0);
		recycle_stop = true;
	}

	
	if (!first_wave_done)
	{
		Attack(wave1_1, solar1, 1);
		Attack(wave1_2, solar1, 1);
//		Attack(wave1_3, solar1);
		
		first_wave_done = true;
	}

// this sends the first wave retreating after one of them is destroyed
	if ((first_wave_done) && (!start_retreat))
	{
		if (!IsAlive(wave1_1))
		{
			Retreat(wave1_2,"retreat_path", 1);
//			Retreat(wave1_3, "retreat_path2", 1);
			new_message_time = Get_Time() + 13.0f;
			start_retreat = true;
		}
		else
		{
			if (!IsAlive(wave1_2))
			{
				Retreat(wave1_1,"retreat_path", 1);
//				Retreat(wave1_3, "retreat_path2", 1);
				new_message_time = Get_Time() + 10.0f;
				start_retreat = true;
			}
//			else
//			{
//				if (!IsAlive(wave1_3))
//				{
//					Retreat(wave1_1,"retreat_path", 1);
//					Retreat(wave1_2, "retreat_path2", 1);
//					new_message_time = Get_Time() + 10.0f;
//					start_retreat = true;
//				}
//			}
		}
	}

	if ((start_retreat) && (new_message_time < Get_Time()) && (!done_retreat))
	{
		AudioMessage("misn0312.wav");
		ClearObjectives();
		AddObjective("misn0302.otf", WHITE);
		AddObjective("misn0301.otf", WHITE);
		done_retreat = true;
	}

	if ((!turrets_set) && (IsAlive(solar1)) && (unit_check < Get_Time()))
	{
		unit_check = Get_Time() + 5.0f;
		z = CountUnitsNearObject(solar1, 200.0f, 1, "avturr");

		if (z > 3)
		{
			ClearObjectives();
			AddObjective("misn0302.otf", GREEN);
			AddObjective("misn0301.otf", WHITE);
			turrets_set = true;
		}
	}

	if ((!second_wave_done) && (second_wave_time < Get_Time()))
	{
		wave2_1 = BuildObject("svfigh",2,"spawn_scrap1");
		wave2_2 = BuildObject("svfigh",2,"spawn_scrap1");
//		wave2_3 = BuildObject("svfigh",2,"spawn_scrap1");	

		Attack(wave2_1, solar1);
		Goto(wave2_2, solar1);
//		Goto(wave2_3, solar1);

		second_wave_done = true;
	}

	if ((!third_wave_done) && (third_wave_time < Get_Time()))
	{
		wave3_1 = BuildObject("svfigh",2,"spawn_scrap1");
		wave3_2 = BuildObject("svfigh",2,"spawn_scrap1");
//		wave3_3 = BuildObject("svfigh",2,"spawn_scrap1");
			
		Attack(wave3_1, solar1, 1);
		Attack(wave3_2, solar1, 1);
//		Goto(wave3_3, solar1, 1);
			
		third_wave_done = true;
	}

	if ((!scavhunt) && (third_wave_done))
	{
		if (IsAlive(wave1_1))
		{
			Attack(wave1_1, scav1, 1);
		}

		if (IsAlive(wave1_2))
		{
			Attack(wave1_2, scav1, 1);
		}

//		if (IsAlive(wave1_3))
//		{
//			Attack(wave1_3, scav1, 1);
//		}

		scavhunt = true;
	}

	if ((!fourth_wave_done) && (fourth_wave_time < Get_Time()))
	{
		wave4_1 = BuildObject("svapc",2,"spawn_scrap1");
		wave4_2 = BuildObject("svtank",2,"spawn_scrap1");
//		wave4_3 = BuildObject("svtank",2,"spawn_scrap1");
		wave5_1 = BuildObject("svfigh",2,"spawn_scrap1");

		if (IsAlive(avrecycler))
		{
			Attack(wave4_1, avrecycler, 1);
		}
		else
		{
			if (IsAlive(solar3))
			{
				Attack(wave4_1, solar3, 1);
			}
			else
			{
				if (IsAlive(solar4))
				{
					Attack(wave4_1, solar4, 1);
				}
			}
		}
		

		Attack(wave4_2, solar2, 1);
//		Goto(wave4_3, solar2, 1);
			
		fourth_wave_done = true;
	}

	if ((!scavhunt2) && (fourth_wave_done) && (IsAlive(wave5_1)))
	{
		if (IsAlive(scav1))
		{
			Attack(wave5_1, scav1, 1);
		}
		else
		{
			if (!IsAlive(scav2))
			{
				Attack(wave5_1, scav2, 1);
			}
		}
		scavhunt2 = true;
	}
	
	if ((!help_spawn) && (support_time < Get_Time()))
	{
		help1 = BuildObject("avfigh",1,"spawn_scrap2");
		help2 = BuildObject("avtank",1,"spawn_scrap2");
		AudioMessage("misn0314.wav");
		Goto(help1, solar2, 0);
		Goto(help2, solar2, 0);
		help_spawn = true;
	}

		if ((help_spawn) && (IsAlive(help1)) && (IsAlive(solar2)) && (!help_stop1))
		{
			if (GetDistance(help1, solar2) < 75.0f)
			{
				Stop(help1, 0);
				help_stop1 = true;
			}
		}

		if ((help_spawn) && (IsAlive(help2)) && (IsAlive(solar2)) && (!help_stop2))
		{
			if (GetDistance(help2, solar2) < 75.0f)
			{
				Stop(help2, 0);
				help_stop2 = true;
			}
		}

	if ((help_spawn) && (!help_arrive) && (GetDistance(help1,user) < 50.0f))
	{
//		AudioMessage("misn0313.wav");
		Goto(help1, solar2, 0);
		help_arrive = true;
	}
	if ((help_spawn) && (!help_arrive) && (GetDistance(help2,user) < 50.0f))
	{
//		AudioMessage("misn0313.wav");
		Goto(help2, solar2, 0);
		help_arrive = true;
	}

//  Time to evacuate the base


// soviet movie

	if ((!second_objective) && (apc_spawn_time < Get_Time()))
	{
		apc_spawn_time = Get_Time() + 1.0f;
		z = CountUnitsNearObject(user, 500.0f, 2, "svtank");
		y = CountUnitsNearObject(user, 500.0f, 2, "svfigh");

		if ((z == 0) && (y == 0))
		{
			audmsg = AudioMessage("misn0305.wav");
			second_objective = true;
		}
	}

	if ((!camera_ready) && (second_objective))
	{
		CameraReady();
		movie_time = Get_Time() + 14.5f;
		new_unit_time = Get_Time() + 7.5f;
		prop1 = BuildObject("svrecy", 2, "recy_spawn");
		prop2 = BuildObject("svmuf", 2, "muf_spawn");
		prop3 = BuildObject("svtank", 2, "tank1_spawn");
		prop4 = BuildObject("svtank", 2, "tank2_spawn");
		prop5 = BuildObject("svfigh", 2, "fighter1_spawn");
//		prop6 = BuildObject("svtank", 2, "fighter2_spawn");
//		prop7 = BuildObject("svtank", 2, "fighter3_spawn");
		guy1 = BuildObject("sssold",2,"guy1_spawn");
		guy2 = BuildObject("sssold",2,"guy2_spawn");
		guy3 = BuildObject("sssold",2,"guy1_spawn");
		guy4 = BuildObject("sssold",2,"guy2_spawn");

		Defend(prop1, 1);
//		Defend(prop6, 1);
//		Defend(prop7, 1);
		Goto(prop2, "tank1_spawn", 1);
		Goto(prop3, "that_path", 1);
		Goto(prop4, "cool_path", 1);
		Goto(prop5, "cool_path", 1);
		Goto(guy1, "guy_spot", 1);
		Goto(guy2, "guy_spot", 1);
		Goto(guy3, "guy_spot", 1);
		Goto(guy4, "guy_spot", 1);
		camera_ready = true;
	}

	if ((camera_ready) && (!movie_over))
	{
		CameraPath("movie_path", 175, 850, prop1);
		Defend(prop1, 1);
 		start_movie = true;
	}

	if ((camera_ready) && (!more_show) && (!movie_over))
	{
		if (new_unit_time < Get_Time())
		{
			prop8 = BuildObject("svfigh", 2, "muf_spawn");
			prop9 = BuildObject("svfigh", 2, "muf_spawn");
//			Goto(prop6, "cool_path2", 1);
//			Goto(prop7, "cool_path2", 1);
			Goto(prop8, "tank2_spawn", 1);
			Goto(prop9, "fighter1_spawn", 1);
			more_show = true;
		}
		else
		{
//			Defend(prop6);
//			Defend(prop7);
		}

	}

	if ((start_movie) && (!movie_over) && ((CameraCancelled()) || (movie_time < Get_Time())))
	{
		CameraFinish();
		StopAudioMessage(audmsg);
		rescue1 = BuildObject("avapc",1, "apc1_spawn");
		rescue2 = BuildObject("avapc",1, "apc2_spawn");

		pull_out_time = Get_Time() + 28.0f;
		turret_move_time = Get_Time() + 30.0f;

		SetObjectiveOff(solar1);
		SetObjectiveOff(solar2);

		SetObjectiveOn(rescue1);
		SetObjectiveName(rescue1, "Transport 1");
		SetObjectiveOn(rescue2);
		SetObjectiveName(rescue2, "Transport 2");
		SetObjectiveOn(launch);
		SetObjectiveName(launch, "Launch Pad");

		ClearObjectives();
		AddObjective("misn0311.otf", GREEN);
		AddObjective("misn0312.otf", GREEN); 
		AddObjective("misn0303.otf", WHITE);

		movie_over = true;
	}

	if ((movie_over) && (!remove_props))
	{
		audmsg = AudioMessage("misn0306.wav");
		RemoveObject(prop1);
		RemoveObject(prop2);
		RemoveObject(prop3);
		RemoveObject(prop4);
		RemoveObject(prop5);
//		RemoveObject(prop6);
//		RemoveObject(prop7);
		if (IsAlive(prop8))
		{
			RemoveObject(prop8);
		}
		if (IsAlive(prop9))
		{
			RemoveObject(prop9);
		}
		if (IsAlive(guy1))
		{
			RemoveObject(guy1);
		}
		if (IsAlive(guy2))
		{
			RemoveObject(guy2);
		}
		if (IsAlive(guy3))
		{
			RemoveObject(guy3);
		}
		if (IsAlive(guy4))
		{
			RemoveObject(guy4);
		}

		remove_props = true;
	}

	if (remove_props)
	{
		if ((!trans_underway) && (pull_out_time < Get_Time()))
		{
			Retreat (rescue1,"rescue_path");
			Retreat (rescue2,"rescue_path");
			ambush_message_time = Get_Time()+ 15.0f;
			trans_underway = true;
			rescue_move_done = true;
		}
	}
	if (remove_props)
	{
		if ((!turret_move_done) && (turret_move_time < Get_Time()))
		{
			Retreat (turret1,"turret_path1");
			Retreat (turret2,"turret_path2");
			Retreat (turret3,"turret_path3");
			Retreat (turret4, "base");		
			turret_move_done = true;
		}
		if (IsAlive (wave1_1))
		{
			Attack(wave1_1, rescue1 , 1);
		}
		if (IsAlive (wave1_2))
		{
			Attack(wave1_2, rescue1, 1);
		}
//		if (IsAlive (wave1_3))
//		{
//			Attack(wave1_3, rescue2, 1);
//		}
		if (IsAlive (wave5_1))
		{
			Attack(wave5_1, rescue2, 1);
		}
		if (IsAlive (wave5_2))
		{
			Attack(wave5_2, rescue1, 1);
		}
		if (IsAlive (wave5_3))
		{
			Attack(wave5_3, rescue2, 1);
		}
	}
	if ((trans_underway) && (ambush_message_time < Get_Time()) && (!ambush_message))
	{
		AudioMessage("misn0315.wav");
		wave6_1 = BuildObject("svfigh",2,"spawn_scrap1");
		wave6_2 = BuildObject("svtank",2,"spawn_scrap1");
		wave6_3 = BuildObject("svtank",2,"spawn_scrap1");
		Attack (wave6_1, solar2, 1);
		Attack (wave6_2, solar1, 1);
		Goto (wave6_3, "base", 1);
		ambush_message = true;
	}
	if ((remove_props) && (!lost) && (!third_objective) 
		&& (GetDistance(rescue1,launch) < 100.0f) && (GetDistance(rescue2,launch) < 100.0f))
		 // I removed this for andrew:(GetDistance(rescue3,launch) < 100.0f)
	{
		AudioMessage("misn0310.wav");
		if (IsAlive(rescue1))
		{
			SetObjectiveOff(rescue1);
		}
		if (IsAlive(rescue1))
		{
			SetObjectiveOff(rescue2);
		}
		ClearObjectives();
		AddObjective("misn0313.otf", GREEN);
		AddObjective("misn0304.otf", WHITE);
		wave7_1 = BuildObject("svtank",2,"spawn_scrap1");
		wave7_2 = BuildObject("svtank",2,"spawn_scrap1");
		wave7_3 = BuildObject("svtank",2,"spawn_scrap1");
		Goto (wave7_1, "base", 1);
		Goto (wave7_2, "base", 1);
		Goto (wave7_3, "base", 1);	
		final_check = Get_Time() + 120.0f;
		third_objective = true;
	}

	if ((!final_objective) && (!second_warning) && (final_check < Get_Time()))
	{
		final_check = Get_Time() + 120.0f;
		ClearObjectives();
		AddObjective("misn0313.otf", GREEN);
		AddObjective("misn0304.otf", WHITE);
		AudioMessage("misn0310.wav");
		second_warning = true;
	}

	if ((!final_objective) && (second_warning) && (!last_warning) && (final_check < Get_Time()))
	{
		final_check = Get_Time() + 120.0f;
		ClearObjectives();
		AddObjective("misn0313.otf", GREEN);
		AddObjective("misn0304.otf", WHITE);
		AudioMessage("misn0310.wav");
		last_warning = true;
	}

	if ((!final_objective) && (third_objective) && (!final_objective) && (CountUnitsNearObject(geyser, 5000.0f, 2, "svtank")) < 5.0f)
	{
		wave7_4 = BuildObject("svtank",2,"spawn_scrap1");
		wave7_5 = BuildObject("svtank",2,"spawn_scrap1");
		Goto (wave7_4, "base", 1);
		Goto (wave7_5, "base", 1);
	}


// win/loose conditions	taken out for movie testing


	if ((third_objective) && (GetDistance(user,launch) < 100.0f)  
		&& (!lost) && (!final_objective))
	{
		final_objective = true;
	}

	if ((!startfinishingmovie) && (final_objective))
		{
		if (IsAlive(avrecycler))
		{
			RemoveObject(avrecycler);
		}
		if (IsAlive(scav1))
		{
			RemoveObject(scav1);
		}
		if (IsAlive(scav2))
		{
			RemoveObject(scav2);
		}	
		if (IsAlive(scav3))
		{
			RemoveObject(scav3);
		}
		if (IsAlive(scav4))
		{
			RemoveObject(scav4);
		}
		if (IsAlive(scav5))
		{
			RemoveObject(scav5);
		}
		if (IsAlive(scav6))
		{
			RemoveObject(scav6);
		}
		if (IsAlive(avturret1))
		{
			RemoveObject(avturret1);
		}
		if (IsAlive(avturret2))
		{
			RemoveObject(avturret2);
		}
		if (IsAlive(avturret3))
		{
			RemoveObject(avturret3);
		}
		if (IsAlive(avturret4))
		{
			RemoveObject(avturret4);
		}
		if (IsAlive(avturret5))
		{
			RemoveObject(avturret5);
		}
		if (IsAlive(avturret6))
		{
			RemoveObject(avturret6);
		}
		if (IsAlive(avturret7))
		{
			RemoveObject(avturret7);
		}
		if (IsAlive(avturret8))
		{
			RemoveObject(avturret8);
		}
		if (IsAlive(avturret9))
		{
			RemoveObject(avturret9);
		}
		if (IsAlive(avturret10))
		{
			RemoveObject(avturret10);
		}
		if (IsAlive(help1))
		{
			RemoveObject(help1);
		}
		if (IsAlive(help2))
		{
			RemoveObject(help2);
		}

		if (IsAlive(wave4_1))
		{
			RemoveObject(wave4_1);
		}
		if (IsAlive(wave4_2))
		{
			RemoveObject(wave4_2);
		}
		if (IsAlive(wave6_1))
		{
			RemoveObject(wave6_1);
		}
		if (IsAlive(wave6_2))
		{
			RemoveObject(wave6_2);
		}
		if (IsAlive(wave6_3))
		{
			RemoveObject(wave6_3);
		}
		if (IsAlive(wave7_1))
		{
			RemoveObject(wave7_1);
		}
		if (IsAlive(wave7_2))
		{
			RemoveObject(wave7_2);
		}
		if (IsAlive(wave7_3))
		{
			RemoveObject(wave7_3);
		}
		if (IsAlive(wave7_4))
		{
			RemoveObject(wave7_4);
		}
		if (IsAlive(wave7_5))
		{
			RemoveObject(wave7_5);
		}
		if (IsAlive(turret1))
		{
			RemoveObject(turret1);
		}
		if (IsAlive(turret2))
		{
			RemoveObject(turret2);
		}
		if (IsAlive(turret3))
		{
			RemoveObject(turret3);
		}
		if (IsAlive(turret4))
		{
			RemoveObject(turret4);
		}
		if (IsAlive(wave4_1))
		{
			RemoveObject(wave4_1);
		}
		
		clean_sweep_time = Get_Time() + 14.0f;
		next_shot = Get_Time() + 18.5f;
		new_unit_time = Get_Time() + 2.0f;
		audmsg = AudioMessage("misn0316.wav");
		prop1 = BuildObject("svtank", 2, "spawna");
		prop2 = BuildObject("svtank", 2, "spawnb");
		prop3 = BuildObject("svtank", 2, "spawnc");
		CameraReady();
		startfinishingmovie = true;
	}

	if ((startfinishingmovie) && (!camera_2))
	{
		/*
		  Camera canceled
		  could be called and this would
		  still play
		*/
		CameraPath("camera_path", x, 3500, cam_geyser);
		x = x - 15;
		camera_on = true;
	}

	if ((startfinishingmovie) && (!tanks_go))
	{
		if (new_unit_time < Get_Time())
		{
			Goto(prop1, "line1", 1);
			Goto(prop2, "line2", 1);
			Goto(prop3, "line3", 1);

			tanks_go = true;
		}
		else
		{
			Defend(prop1);
			Defend(prop2);
			Defend(prop3);
		}
	}

	if ((startfinishingmovie) && (clean_sweep_time < Get_Time()) && (!clean_sweep))
	{
		clean_sweep = true;
	}

	if ((startfinishingmovie) && (next_shot < Get_Time()) && (!camera_off))
	{
		CameraPath("inbase_path", 160, 90, prop1);
		camera_2 = true;
	}

	if ((camera_2) && (!speach2))
	{
		audmsg = AudioMessage("misn0317.wav");
		speach2 = true;
	}

	if ((camera_2) && (!show_tank_attack))
	{
		if (GetDistance(prop1, shot_geyser) < 20.0f)
		{ 
			if (IsAlive(solar1))
			{
				Attack(prop1, solar1);
				Attack(prop2, solar1);
				if (IsAlive(solar2))
				{
					Damage(solar2, 20000);
				}
				if (IsAlive(solar3))
				{
					Damage(solar3, 20000);
				}
				if (IsAlive(solar4))
				{
					Damage(solar4, 20000);
				}
				kill_tower = Get_Time() + 7.0f;
				show_tank_attack = true;
			}
		}
	}

	if ((show_tank_attack) && (!tower_dead) && (kill_tower < Get_Time()))
	{
		if (IsAlive(solar1))
		{
			Damage(solar1, 25000);
			tower_dead = true;
		}
	}

	if ((tower_dead) && (!climax1))
	{
		Retreat(prop1, "climax_path1", 1);
		Retreat(prop2, "spawn_scrap1", 1);
		Retreat(prop3, "spawn_scrap1", 1);
		clear_debis_time = Get_Time() + 6.0f;
		audmsg = AudioMessage("misn0318.wav");
		climax1 = true;
	}

	if ((climax1) && (!clear_debis) && (clear_debis_time < Get_Time()))
	{
//		if (IsAlive(build2))
//		{
//			Damage(build2, 20000);
//		}
		if (IsAlive(build3))
		{
			Damage(build3, 20000);
		}
//		if (IsAlive(build2))
//		{
//			RemoveObject(build2);
//		}
		prop8 = BuildObject("svtank", 2, cam_geyser);
		Retreat(prop8, "climax_path2", 1);
		clear_debis = true;
	}

	if ((climax1) && (!climax2))
	{
		if (GetDistance(prop1, cam_geyser) < 100.0f)
		{
			Retreat(prop1, "climax_path2", 1);
			prop9 = BuildObject("svfigh", 2, "solar_spot");
			prop0 = BuildObject("svfigh", 2, "solar_spot");
			Retreat(prop9, "camera_pass", 1);
			Retreat(prop0, "camera_pass", 1);
			if (IsAlive(hanger))
			{
				Damage(hanger, 20000);
			}
			clear_debis_time = Get_Time() + 3.0f;
			climax2 = true;
		}
	}

	if ((climax2) && (!last_blown) && (clear_debis_time < Get_Time())) 
	{
		if (IsAlive(box1))
		{
			Damage(box1, 20000);
		}
		if (IsAlive(build1))
		{
			Damage(build1, 20000);
		}
		if (IsAlive(crate1))
		{
			Damage(crate1, 20000);
		}
		if (IsAlive(crate2))
		{
			Damage(crate2, 20000);
		}
		if (IsAlive(crate3))
		{
			Damage(crate3, 20000);
		}

		Retreat(prop2, "solar_spot");
		Retreat(prop8, "spawn_scrap1", 1);
		sucker = BuildObject("abwpow", 1, "sucker_spot");
//		clear_debis_time = Get_Time() + 6.0f;
		last_blown = true;
	}

	if ((last_blown) && (!end_shot) && (GetDistance(prop1, sucker) < 65.0f))
	{
		Attack(prop1, sucker, 1);
		camera_off_time = Get_Time() + 1.5f;
		end_shot = true;
	}

	if ((camera_on) && (!camera_off) && ((CameraCancelled()) || (camera_off_time < Get_Time())))
	{
		startfinishingmovie=false;
		CameraFinish();
		StopAudioMessage(audmsg);
		SucceedMission(0.1f, "misn03w1.des");
		camera_off = true;
	}


// win/loose conditions

	if ((last_warning) && (final_check < Get_Time()) && (!final_objective) && (!lost))
	{
		FailMission(Get_Time() + 1.0f, "misn03f5.des"); // you didn't reach the launch pad in time
		lost = true;
	}
	
	if ((!dead1) && (!show_tank_attack) && (!second_objective) && (!IsAlive(solar1))) //new
	{
		AudioMessage("misn0302.wav");
		ClearObjectives();
		AddObjective("misn0311.otf", RED);
		AddObjective("misn0312.otf", WHITE); 
		lost = true;
		dead1 = true;
		if (!turrets_set)
		{
			FailMission(Get_Time() + 10.0f, "misn03f1.des"); // com tower dead - you didn't build enough turrets
		}
		else
		{
			FailMission(Get_Time() + 10.0f, "misn03f2.des"); // com tower dead
		}
	}

	if ((!dead2) && (!tanks_go) && (!IsAlive(solar2)) && (!second_objective)) //new
	{
		AudioMessage("misn0303.wav");
		ClearObjectives();
		AddObjective("misn0311.otf", RED);
		AddObjective("misn0312.otf", WHITE); 
		lost = true;
		dead2 = true;
		if (!turrets_set)
		{
			FailMission(Get_Time() + 10.0f, "misn03f3.des"); /// solar arrays dead - you didn't build enough turrets
		}
		else
		{
			FailMission(Get_Time() + 10.0f, "misn03f3.des"); /// solar arrays dead
		}
	}

	if ((movie_over) && (!dead3) && (!IsAlive(rescue1)) && (!third_objective))
	{
		AudioMessage("misn0304.wav");
		ClearObjectives();
		AddObjective("misn0311.otf", GREEN);
		AddObjective("misn0312.otf", GREEN); 
		AddObjective("misn0303.otf", RED);
		lost = true;
		dead3 = true;
		FailMission(Get_Time() + 10.0f, "misn03f4.des"); // transport dead
	}
	if ((movie_over) && (!dead3) && (!IsAlive(rescue2)) && (!third_objective))
	{
		AudioMessage("misn0304.wav");
		ClearObjectives();
		AddObjective("misn0311.otf", GREEN);
		AddObjective("misn0312.otf", GREEN); 
		AddObjective("misn0303.otf", RED);
		lost = true;
		dead3 = true;
		FailMission(Get_Time() + 10.0f, "misn03f4.des"); // transport dead
	}

	if ((!IsAlive(launch)) && (!lost))
	{
		FailMission(Get_Time() + 1.0f); // lost your launch pad no des
		lost = true;
	}
}

Misn03Mission::Misn03Mission(void)
{
}

Misn03Mission::~Misn03Mission()
{
}

bool Misn03Mission::Load(void)
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
		return true;
	}

	bool ret = true;

	// bools
	int b_count = &b_last - b_array;
	_ASSERTE(b_count == SIZEOF(b_array));
	ret = ret && in(b_array, sizeof(b_array));

	// floats
	int f_count = &f_last - f_array;
	_ASSERTE(f_count == SIZEOF(f_array));
	ret = ret && in(f_array, sizeof(f_array));

	// Handles
	int h_count = &h_last - h_array;
	_ASSERTE(h_count == SIZEOF(h_array));
	ret = ret && in(h_array, sizeof(h_array));

	// ints
	int i_count = &i_last - i_array;
	_ASSERTE(i_count == SIZEOF(i_array));
	ret = ret && in(i_array, sizeof(i_array));

	return ret;
}

bool Misn03Mission::PostLoad(void)
{
	if (missionSave)
		return true;

	bool ret = true;

	int h_count = &h_last - h_array;
	for (int i = 0; i < h_count; i++)
		h_array[i] = ConvertHandle(h_array[i]);

	return ret;
}

bool Misn03Mission::Save(void)
{
	if (missionSave)
		return true;

	bool ret = true;

	// bools
	int b_count = &b_last - b_array;
	_ASSERTE(b_count == SIZEOF(b_array));
	ret = ret && out(b_array, sizeof(b_array), "b_array");

	// floats
	int f_count = &f_last - f_array;
	_ASSERTE(f_count == SIZEOF(f_array));
	ret = ret && out(f_array, sizeof(f_array), "f_array");

	// Handles
	int h_count = &h_last - h_array;
	_ASSERTE(h_count == SIZEOF(h_array));
	ret = ret && out(h_array, sizeof(h_array), "h_array");

	// ints
	int i_count = &i_last - i_array;
	_ASSERTE(i_count == SIZEOF(i_array));
	ret = ret && out(i_array, sizeof(i_array), "i_array");

	return ret;
}

void Misn03Mission::Update(void)
{
	Execute();
}

bool Save(bool misnSave)
{
	missionSave = misnSave;
	return mission->Save();
}

bool Load(bool misnSave)
{
	mission = new Misn03Mission();
	missionSave = misnSave;
	return mission->Load();
}

bool PostLoad(bool misnSave)
{
	missionSave = misnSave;
	return mission->PostLoad();
}

void AddObject(Handle h)
{
	mission->AddObject(h);
}

void Update(void)
{
	mission->Update();
}

void PostRun(void)
{
	delete mission;
}

static MisnExport misnExport;
MisnImport misnImport;

MisnExport * __cdecl GetMisnAPI(MisnImport *import)
{
	misnImport = *import;
	misnExport.misnImport = &misnImport;
	misnExport.Save = Save;
	misnExport.Load = Load;
	misnExport.PostLoad = PostLoad;
	misnExport.AddObject = AddObject;
	misnExport.Update = Update;
	misnExport.PostRun = PostRun;
	return &misnExport;
}
