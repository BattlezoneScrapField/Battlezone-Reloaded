#include "GameCommon.h"

#include "..\fun3d\ScriptUtils.h"

/*
	Misns7Mission
*/

#include "..\fun3d\AiMission.h"

class Misns7Mission : public AiMission {
	DECLARE_RTIME(Misns7Mission)
public:
	Misns7Mission(void);
	~Misns7Mission();

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
			bool start_done,
				get_recycle,
				camera_on_recycle,
				camera_off_recycle,
				svrecycle_unit_spawn,
				svrecycle_on,
				jail_unit_spawn,
				jail_camera_on,
				jail_camera_off,
				mission_fail,
				con_pickup,
				con_camera_on,
				con_camera_off,
				jail_dead,
				con1_in_apc, con2_in_apc, con3_in_apc,
				fully_loaded, two_loaded, one_loaded, apc_empty,
				going_to_recycle,
				get_muf,
				camera_on_muf,
				svmuf_unit_spawn,
				svmuf_on,
				camera_off_muf,
				get_supply,
				camera_on_supply,
				supply_unit_spawn,
				supply_on,
				camera_off_supply,
				supply_message,
				con1_safe, con2_safe, con3_safe,
				con1_dead, con2_dead, con3_dead,
				first_message_done,
				down_to_two, down_to_one,
				game_over,
				supplies_spawned,
				build_scav,
				fight1_built, fight2_built, fight3_built, fight4_built,
				nsdf_adjust,
				avmuf_built,
				pick_up,
				supply_first,
				jail_found,
				turret_move1, build_turret, closer_message, muf_message,
				in_base, plan_a, plan_b, plan_c, plan_d,
				muf_found, gech_sent, muf_located, gech_adjust,
				rig_underway1, build_tower1, build_power1, build_tower2,
				muf_deployed, muf_redirect,
				new_rig, rig_show, rig_show2, rig_show3, rig_stop1, rig_stop2, main_off, main_on, main_build, last_tower,
				turret4_defend, maint_off, maint_on, maint_build,
				new_muf, silo_message, silo_message2, turret_message, supply2_message,
				blah, apc_panic_message, muf_message2,
				b_last;
		};
		bool b_array[95];
	};

	// floats
	union {
		struct {
			float unit_spawn_time1,
				  con_spawn_time,
				  camera_off_time,
				  con_camera_time,
				  supply_spawn_time,
				  con1_pickup_time, con2_pickup_time, con3_pickup_time,
				  supply_message_time,
				  avfigh1_time, avfigh2_time, avfigh3_time, avfigh4_time,
				  build_scav_time,
				  adjust_timer,
				  muf_message_time,
				  muf_scan_time,
				  tower1_timer,
				  rig_check,
				  turret_check,
				  bm_time, b1_time, b2_time, b3_time, b4_time, b5_time, b6_time, b7_time,
				  check_a, check_b, check_c, silo_check,
				  muf_build_time, goo_time, bturret_time,
				f_last;
		};
		float f_array[35];
	};

	// handles
	union {
		struct {
			Handle  user, temp,
				fed_up_scrap,
				svrecycle, svmuf, apc, svsilo, guntower1, guntower2,
				avrecycle, avmuf, avscav1, avscav2, avsilo, hanger, avtower1, avtower2, avtower3, avbarrack,
				main_tower, main_power,
				geyser1, geyser2, geyser3, field_geyser1,
				jail, 
				supply,
				avpower1, avpower2,
				con1, con2, con3,
				boxes, svsilo2,
				supply1, supply2, supply3, supply4, supply5, supply6, supply7, supply8, supply9,
				avfight1, avfight2, avfight3, avfight4,
				avtank1, avtank2, avltnk1, avltnk2, avgech, avturr1, avturr2, avturr3, avturr4,
				avrig, b1, b2, b3, b4, b5, b6, b7, b8, b9, b0,
				newmuf, engineer, con_geyser, bturret1, bturret2, bturret3, bturret4,
				bvrig, bvrecycle,
				h_last;
		};
		Handle h_array[76];
	};

	// integers
	union {
		struct {
			int
				stuff, stuff2, stuff4, scrap,
				i_last;
		};
		int i_array[4];
	};
};

void Misns7Mission::Setup(void)
{
	stuff = 10;
	stuff2 = 0;
	stuff4 = 10;
	scrap = 0;

	main_on = true;
	maint_on = true;

//	svrecycle = GetHandle ("svrecycle");
//	svmuf = GetHandle ("svmuf");
	camera_off_supply = NULL;
	apc = GetHandle ("svapc");
	avrecycle = GetHandle ("avrecycle");
	jail = GetHandle ("jail");
	supply = GetHandle ("supply");
	geyser1 = GetHandle("geyser1");
	geyser2 = GetHandle("geyser2");
	geyser3 = GetHandle("geyser3");
	boxes = GetHandle("boxes");
	fed_up_scrap = GetHandle("getum_started");
	svsilo = GetHandle("svsilo");
	guntower1 = GetHandle("guntower1");
	guntower2 = GetHandle("guntower2");
	field_geyser1 = GetHandle("field_geyser1");
	avsilo = GetHandle("avsilo");
	hanger = GetHandle ("hanger");
	avrig = GetHandle ("rig");
	main_power = GetHandle ("wind_power1");
	con_geyser = GetHandle("con_geyser");
	bturret1 = GetHandle("bturret1");
	bturret2 = GetHandle("bturret2");
	svrecycle = GetHandle("svrecycle");
	svmuf = GetHandle("svmuf");
	main_tower = GetHandle("main_tower");
	avmuf = NULL;
	bturret3 = NULL;
	bturret4 = NULL;
	bvrig = NULL;
	bvrecycle = NULL;
}

void Misns7Mission::AddObject(Handle h)
{
	if ((avscav1 == NULL) && (IsOdf(h,"bvscav")))
	{
		avscav1 = h;
	}
	else
	{
		if ((avscav2 == NULL) && (IsOdf(h,"bvscav")))		
		{
			avscav2 = h;
		}
		else
		{
			if ((avfight1 == NULL) && (IsOdf(h,"bvraz")))		
			{
				avfight1 = h;
			}
			else
			{
				if ((avfight2 == NULL) && (IsOdf(h,"bvraz")))		
				{
					avfight2 = h;
				}
				else
				{
					if ((avtank1 == NULL) && (IsOdf(h,"bvtank")))		
					{
						avtank1 = h;
					}
					else
					{
						if ((avtank2 == NULL) && (IsOdf(h,"bvtank")))		
						{
							avtank2 = h;
						}
						else
						{
							if ((avltnk1 == NULL) && (IsOdf(h,"bvltnk")))		
							{
								avltnk1 = h;
							}
							else
							{
								if ((avltnk2 == NULL) && (IsOdf(h,"bvltnk")))		
								{
									avltnk2 = h;
								}
								else
								{
									if ((avgech == NULL) && (IsOdf(h,"bvwalk")))		
									{
										avgech = h;
									}
									else
									{
										if ((avturr1 == NULL) && (IsOdf(h,"bvturr")))		
										{
											avturr1 = h;
										}
										else
										{
											if ((avturr2 == NULL) && (IsOdf(h,"bvturr")))		
											{
												avturr2 = h;
											}
											else
											{
												if ((main_tower == NULL) && (IsOdf(h,"abtowe")))		
												{
													main_tower = h;
												}
												else
												{
													if ((avtower1 == NULL) && (IsOdf(h,"abtowe")))		
													{
														avtower1 = h;
													}
													else
													{
														if ((avtower2 == NULL) && (IsOdf(h,"abtowe")))		
														{
															avtower2 = h;
														}
														else
														{
															if ((main_power == NULL) && (IsOdf(h,"abwpow")))		
															{
																main_power = h;
															}
															else
															{
																if ((avpower1 == NULL) && (IsOdf(h,"abwpow")))		
																{
																	avpower1 = h;
																}
																else
																{
																	if ((avpower2 == NULL) && (IsOdf(h,"abwpow")))		
																	{
																		avpower2 = h;
																	}
																	else
																	{
																		if ((IsAlive(svmuf)) && (newmuf == NULL) && (IsOdf(h,"svmuf")))		
																		{
																			newmuf = h;
																		}
																		else
																		{
																			if ((!IsAlive(avmuf)) && (IsOdf(h,"bvmuf")))
																			{
																				avmuf = h;
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
				}
			}
		}
	}
}

void Misns7Mission::Execute(void)
{

// START OF SCRIPT

	user = GetPlayerHandle(); //assigns the player a handle every frame
//	scrap = GetScrap(2);// gets the american's scrap
	
//	if ((scrap < 19) && (IsAlive(avrig)))
//	{
//		SetScrap(2, 20);
//	}

	if (!start_done)
	{ 
		SetPilot(1, 8);
		SetScrap(2, 40);
		SetPilot(2, 40);

		SetObjectiveOn(jail);
		SetObjectiveName(jail, "Military Prison");

		AudioMessage("misns700.wav"); // General "mission breifing"
		ClearObjectives();
		AddObjective("misns700.otf", WHITE);
		build_scav_time = Get_Time() + 8.0f;

		Defend(svmuf);
		Defend(avrig);
		Defend(bturret1);
		Defend(bturret2);		
		bturret_time = Get_Time() + 60.0f;
		SetPerceivedTeam(guntower1, 2);
		SetPerceivedTeam(guntower2, 2);
		SetPerceivedTeam(svrecycle, 2);
		muf_scan_time = Get_Time() + 240.0f;
		Build(avrig, "abtowe");
		start_done = true;
	}

	if (bturret_time < Get_Time())
	{
		bturret_time = Get_Time() + 180.0f;

		if (IsAlive(bturret1))
		{
			Defend(bturret1);
		}
		if (IsAlive(bturret2))
		{
			Defend(bturret2);
		}
	}

	if ((start_done) && (GetDistance(user, jail) < 150.0f) && (!jail_found))
	{
		AudioMessage("misns722.wav");
		adjust_timer = Get_Time() + 120.0f;
		jail_found = true;
	}

	if ((start_done) && (build_scav_time < Get_Time()) && (!build_scav))
	{
		avscav1 = BuildObject("bvscav", 2, "muf_point");
		avscav2 = BuildObject("bvscav", 2, "muf_point");
//		main_tower = BuildObject("abtowe", 2, "main_tower");
		Goto(avscav1, fed_up_scrap, 0);
		Goto(avscav2, fed_up_scrap, 0);
		silo_check = Get_Time() + 10.0f;
		build_scav = true;
	}

// this is what happens if the player attacks the american scavengers right away

	if (!jail_dead)
	{
		if ((((IsAlive(avscav1)) && (GameObjectHandle::GetObj(avscav1)->GetHealth()<0.91f))
			||
			((IsAlive(avscav2)) && (GameObjectHandle::GetObj(avscav2)->GetHealth()<0.91f))
			||
			((IsAlive(main_power)) && (GameObjectHandle::GetObj(main_power)->GetHealth()<0.95f))
			||
			((IsAlive(avrecycle)) && (GameObjectHandle::GetObj(avrecycle)->GetHealth()<0.95f))
			||
			((IsAlive(avrig)) && (GameObjectHandle::GetObj(avrig)->GetHealth()<0.95f)))	&& (!nsdf_adjust))
		{
			nsdf_adjust = true;
		}
	}

	if ((IsAlive(jail)) && (!in_base) && (GameObjectHandle::GetObj(jail)->GetHealth() < 0.50f))
	{ 
		in_base = true;
	}

	if ((jail_found) && (adjust_timer < Get_Time()) && (!nsdf_adjust) && (!jail_dead))
	{
		nsdf_adjust = true;
	}

	// the nsdf adjusts by building fighters and sending them after the player
	if ((nsdf_adjust) && (!fight1_built))
	{
		avfight1 = BuildObject("bvraz", 2, "muf_point");
		Attack(avfight1, user);
		avfigh2_time = Get_Time() + 20.0f;
		fight1_built = true;
	}

	if ((nsdf_adjust) && (fight1_built) && (avfigh2_time < Get_Time()) && (!fight2_built))
	{
		avfight2 = BuildObject ("bvraz", 2, "muf_point");
		Attack(avfight2, user);
		avfigh3_time = Get_Time() + 20.0f;
		fight2_built = true;
	}

	if ((nsdf_adjust) && (fight2_built) && (avfigh3_time < Get_Time()) && (!fight3_built))
	{
		avfight3 = BuildObject ("bvraz", 2, "muf_point");
			// this is going to send the third fighter after the apc if the 
			// second fighter is still alive and the apc is within radar range
			if (IsAlive(avfight2))
			{
				Attack(avfight3, apc);
			}
			else
			{
				Attack(avfight3, user);
			}
		
		SetScrap(2, 40);
		fight3_built = true;
	}

	if ((nsdf_adjust) && (IsAlive(avfight3)) && (!jail_dead) && (!build_turret))
	{
		avturr1 = BuildObject("bvturr", 2, "muf_point");
		build_turret = true;
	}

// this is when the player destroys the jail
	
	if ((!IsAlive(jail)) && (!jail_dead)) 
	{
		CameraReady();
		con_spawn_time = Get_Time() + 1.5f;
		jail_dead = true;
	}

	if ((jail_dead) && (!jail_camera_on))
	{
		CameraObject(geyser1, -1500, 1000, -5000, boxes);
		camera_off_time = Get_Time() + 3.5f;
		jail_camera_on = true;
	}

	if ((jail_dead) && (con_spawn_time < Get_Time()) && (!jail_unit_spawn))
	{
		con1 = BuildObject("sssold",1, "con1_spot");
		con2 = BuildObject("sssold",1, "con2_spot");
		con3 = BuildObject("sssold",1, "con3_spot");
		SetIndependence(con1, 0);
		SetIndependence(con2, 0);
		SetIndependence(con3, 0);
		GetIn(con1, apc, 1);
		GetIn(con2, apc, 1);
		GetIn(con3, apc, 1);
		jail_unit_spawn = true;	
	}

	if ((jail_camera_on) && (camera_off_time < Get_Time()) && (!jail_camera_off))
	{
		CameraFinish();
		muf_build_time = Get_Time() + 5.0f;
		jail_camera_off = true;
	}

	// tells the player to move the apc in if it is too far away
	if ((jail_camera_off) && (!closer_message))
	{
		if (GetDistance(apc, boxes) > 70.0f)
		{
			AudioMessage("misns710.wav"); 
			closer_message = true;
		}
		else
		{
			closer_message = true;
		}
	}

// this is the apc telling the player to get him out of there

	if ((jail_camera_off) && (IsAlive(apc)) && (avfigh2_time < Get_Time()) && (!fully_loaded)
		&& (GameObjectHandle::GetObj(apc)->GetHealth()<0.80f) && (!apc_panic_message))
	{
		AudioMessage("misns723.wav");
		apc_panic_message = true;
	}

// now that the jail is down the nsdf builds its muf

	if ((jail_camera_off) && (muf_build_time < Get_Time()) && (!avmuf_built))
	{
		avmuf = BuildObject("bvmuf", 2, "muf_point");
		Defend(avmuf);
		Goto(avmuf, geyser1);
		avfigh1_time = Get_Time() + 30.0f;
		avmuf_built = true;
	}

	// this is just seeing if the avmuf is deployed
	if (IsAlive(avtank1))
	{
		muf_deployed = true;
	}

	// if the muf is attacked it will redirect
/*	if ((avmuf_built) && (IsAlive(avmuf)) && (GameObjectHandle::GetObj(avmuf)->GetHealth()<0.50f) 
		&& (!muf_redirect) && (!muf_deployed))
	{
		Goto(avmuf, geyser3);
		muf_redirect = true;
	}
*/
	// now that the nsdf has built an muf it will start building fighters
	if ((avmuf_built) && (avfigh1_time < Get_Time()) && (!fight1_built))
	{
		avfight1 = BuildObject("bvraz", 2, "muf_point");
		SetPerceivedTeam(guntower1, 2);
		SetPerceivedTeam(guntower2, 2);
		SetPerceivedTeam(svrecycle, 2);
		avfigh2_time = Get_Time() + 30.0f;
		fight1_built = true;
	}

	if ((avmuf_built) && (fight1_built) && (avfigh2_time < Get_Time()) && (!fight2_built))
	{
		avfight2 = BuildObject ("bvraz", 2, "muf_point");
		// this is going to send the second fighter after the apc if the first fighter is still alive and the apc is within radar range 
		if ((IsAlive(avfight1)) && (GetDistance(apc, boxes) < 200.0f))
		{
			Attack(avfight2, apc);
		}

		SetAIP("misns7.aip");
		SetPerceivedTeam(guntower1, 2);
		SetPerceivedTeam(guntower2, 2);
		SetPerceivedTeam(svrecycle, 2);
		AddScrap(2, 40);	
		fight2_built = true;
	}

	if ((IsAlive(avturr1)) && (!turret_move1))
	{
		Goto(avturr1, "turret_spot");
		turret_move1 = true;
	}

// this what happens if the muf is destroyed

	if ((avmuf_built) && (!IsAlive(avmuf)) && (!plan_b))
	{
		AddScrap(2, 20);
		SetAIP("misns7c.aip");
		SetPerceivedTeam(guntower1, 2);
		SetPerceivedTeam(guntower2, 2);
		SetPerceivedTeam(svrecycle, 2);
		plan_c = false;
		plan_b = true;
	}

	if ((plan_b) && (IsAlive(avmuf)) && (!plan_c))
	{
		if (plan_a)// if the player has already gotten his muf
		{
			SetAIP("misns7a.aip");// this has scavs
			SetPerceivedTeam(guntower1, 2);
			SetPerceivedTeam(guntower2, 2);
			SetPerceivedTeam(svrecycle, 2);
		}
		else
		{
			SetAIP("misns7.aip");
			SetPerceivedTeam(guntower1, 2);
			SetPerceivedTeam(guntower2, 2);
			SetPerceivedTeam(svrecycle, 2);
		}
		
//		AddScrap(2, 20);
		Goto(avmuf, geyser1);
		plan_b = false;
		plan_c = true;
	}


// this determines if the cons are killed BEFORE they get into the apc (since getting into an apc techincally "kills" them

	if ((jail_unit_spawn) && (!IsAlive(con1)) && (!con1_in_apc))
	{
		con1_dead = true;
	}

	if ((jail_unit_spawn) && (!IsAlive(con2)) && (!con2_in_apc))
	{
		con2_dead = true;
	}

	if ((jail_unit_spawn) && (!IsAlive(con3)) && (!con3_in_apc))
	{
		con3_dead = true;
	}

	// now that the cons are free the player has to pick them up

//	if ((jail_unit_spawn) && (!con_pickup) && (GetDistance(apc,boxes) < 30.0f))
//	{
////	Stop(apc, 0);
////	CameraReady();
//		Retreat(con1, apc);
//		Retreat(con2, apc);
//		Retreat(con3, apc);
//		con_pickup = true;
//	}
	
// this is instructing the apc to stop when in close proximity to a con
/*	
		if ((jail_unit_spawn) && (con1!= NULL) && (GetDistance(con1, apc) < 25.0f) && (!pick_up))
		{
			Stop(apc, 0);
			pick_up = true;
		}

		if((jail_unit_spawn) && (con2!= NULL) && (GetDistance(con2, apc) < 25.0f) && (!pick_up))
		{
			Stop(apc, 0);
			pick_up = true;
		}

		if((jail_unit_spawn) && (con3!= NULL) && (GetDistance(con3, apc) < 25.0f) && (!pick_up))
		{
			Stop(apc, 0);
			pick_up = true;
		}
		
		if ((pick_up) && (con1!= NULL) && (GetDistance(con1, apc) < 50.0f))
		{
			pick_up = false;
		}

		if ((pick_up) && (con2!= NULL) && (GetDistance(con2, apc) < 50.0f))
		{
			pick_up = false;
		}

		if ((pick_up) && (con3!= NULL) && (GetDistance(con3, apc) < 50.0f))
		{
			pick_up = false;
		}
*/
//	if ((con_pickup) && (!con_camera_on))
//	{
//		CameraObject(geyser1, -2000, 2000, -4000, boxes);
//		con_camera_time = Get_Time() + 7.0f;
//		con_camera_on = true;
//	}

	if ((jail_unit_spawn) && (GetDistance(con1, apc) < 20.0f) && (!con1_dead) && (!con1_in_apc))
	{
		con1_pickup_time = Get_Time() + 0.2f;
		con1_in_apc = true;
	}

		if ((con1_in_apc) && (con1_pickup_time < Get_Time()) && (!con1_safe))
		{
			RemoveObject(con1);
			AddPilot(1, 1);
			AudioMessage("misns702.wav"); // con 1 on board sir! 726
			goo_time = Get_Time() + 5.0f;
			pick_up = true;
			con1_safe = true;
		}

	if ((jail_unit_spawn) && (GetDistance(con2, apc) < 20.0f) && (!con2_dead) && (!con2_in_apc))
	{
		con2_pickup_time = Get_Time() + 0.2f;
		con2_in_apc = true;
	}

		if ((con2_in_apc) && (con2_pickup_time < Get_Time()) && (!con2_safe))
		{
			RemoveObject(con2);
			AddPilot(1, 1);
			AudioMessage("misns702.wav"); // con 2 on board sir! 726
			goo_time = Get_Time() + 5.0f;
			pick_up = true;
			con2_safe = true;
		}

	if ((jail_unit_spawn) && (GetDistance(con3, apc) < 20.0f) && (!con3_dead) && (!con3_in_apc))
	{
		con3_pickup_time = Get_Time() + 0.2f;
		con3_in_apc = true;
	}

		if ((con3_in_apc) && (con3_pickup_time < Get_Time()) && (!con3_safe))
		{
			RemoveObject(con3);
			AddPilot(1, 1);
			AudioMessage("misns702.wav"); // con 3 on board sir! 726
			goo_time = Get_Time() + 5.0f;
			pick_up = true;
			con3_safe = true;
		}

// here is where I set the "loaded" apc parameters (depending on how many cons get into the apc

	if ((con1_safe) && (con2_safe) && (con3_safe) && (!fully_loaded)
		&& (!first_message_done) && (!get_recycle) && (!get_muf) && (!get_supply))
	{
		AudioMessage("misns704.wav"); 
		fully_loaded = true;
		muf_message_time = Get_Time() + 3.0f;
		check_a = Get_Time() + 1.0f;
		check_b = Get_Time() + 2.0f;
		check_c = Get_Time() + 3.0f;
		first_message_done = true;
	}

	if (((con1_safe) && (con2_safe) && (con3_dead) && (!two_loaded)) ||
		((con1_safe) && (con2_dead) && (con3_safe) && (!two_loaded)) ||
		((con1_dead) && (con2_safe) && (con3_safe) && (!two_loaded))
		&& (!first_message_done) && (!get_recycle) && (!get_muf) && (!get_supply))
	{
		AudioMessage("misns705.wav"); // only two of us made it sir lets get the fuck outta here
		two_loaded = true;
		muf_message_time = Get_Time() + 3.0f;
		check_a = Get_Time() + 1.0f;
		check_b = Get_Time() + 2.0f;
		check_c = Get_Time() + 3.0f;
		first_message_done = true;
	}

	if (((con1_safe) && (con2_dead) && (con3_dead) && (!one_loaded)) ||
		((con1_dead) && (con2_safe) && (con3_dead) && (!one_loaded)) ||
		((con1_dead) && (con2_dead) && (con3_safe) && (!one_loaded))
		&& (!first_message_done) && (!get_recycle) && (!get_muf) && (!get_supply))
	{
		AudioMessage("misns706.wav"); // only one of us made it sir lets get the fuck outta here
		one_loaded = true;
		muf_message_time = Get_Time() + 3.0f;
		check_a = Get_Time() + 1.0f;
		check_b = Get_Time() + 2.0f;
		check_c = Get_Time() + 3.0f;
		first_message_done = true;
	}

// this is where the apc pilot tells the player about the muf

	if ((IsAlive(apc)) && (pick_up) && (goo_time < Get_Time()) && (!first_message_done))
	{
		goo_time = Get_Time() + 5.0f;
		stuff = CountUnitsNearObject(apc, 200.0f, 2, NULL);
		if (stuff == 0)
		{
			if (IsAlive(con1))
			{
				RemoveObject(con1);
			}
			if (IsAlive(con2))
			{
				RemoveObject(con2);
			}
			if (IsAlive(con3))
			{
				RemoveObject(con3);
			}
		}
	}

	if ((IsAlive(apc)) && (first_message_done) && (muf_message_time < Get_Time()) && (!muf_message))
	{
		muf_message_time = Get_Time() + 3.0f;
		stuff4 = CountUnitsNearObject(apc, 200.0f, 2, NULL);
		if (stuff4 == 0)
		{
			if (fully_loaded)
			{
				AudioMessage("misns724.wav");
				AudioMessage("misns717.wav");
				muf_message_time = Get_Time() + 30.0f;
			}
			else
			{
				if (two_loaded)
				{
					AudioMessage("misns725.wav");
					AudioMessage("misns718.wav");
					muf_message_time = Get_Time() + 30.0f;
				}
				else
				{
					if (one_loaded)
					{
						AudioMessage("misns725.wav");
						AudioMessage("misns708.wav");
						muf_message_time = Get_Time() + 30.0f;
					}
				}
			}

			ClearObjectives();					
			AddObjective("misns703.otf", GREEN);	
			AddObjective("misns701.otf", WHITE);
//			AddObjective("misns702.otf", WHITE);
			muf_message = true;
		}
	}

	if ((!muf_message2) && (muf_message) && (muf_message_time < Get_Time()))
	{
		ClearObjectives();					
		AddObjective("misns703.otf", GREEN);	
		AddObjective("misns701.otf", WHITE);
		AddObjective("misns702.otf", WHITE);
		muf_message2 = true;
	}

//	if ((con_camera_on) && (cons_loaded) && (!con_camera_off))
//	{
//		CameraFinish();
//		con_camera_off = true;
//	}


// this is the apc dropping off the engineer at the svrecycler

if ((first_message_done) && (!get_recycle) 
	&& (check_a < Get_Time()) && (GetDistance(apc, svrecycle) < 50.0f))
{
	check_a = Get_Time() + 3.0f;

	if ((!apc_empty) && (fully_loaded) && (!get_recycle)  
		&& (!down_to_two)/* && (GetDistance(apc, svrecycle) < 50.0f)*/)
	{
		get_recycle = true;
		CameraReady();
		Stop(apc, 0);
		unit_spawn_time1 = Get_Time() + 2.0f;
		down_to_two = true;
	}

		if ((!apc_empty) && (two_loaded) && (!get_recycle)
			 && (!down_to_one)/* && (GetDistance(apc, svrecycle) < 50.0f)*/)
		{
			get_recycle = true;
			CameraReady();
			Stop(apc, 0);
			unit_spawn_time1 = Get_Time() + 2.0f;
			down_to_one = true;
		}

		if ((!apc_empty) && (one_loaded) && (!get_recycle) 
			/* && (GetDistance(apc, svrecycle) < 50.0f)*/)
		{
			get_recycle = true;
			CameraReady();
			Stop(apc, 0);
			unit_spawn_time1 = Get_Time() + 2.0f;
			apc_empty = true;
		}

	if ((!apc_empty) && (down_to_two) && (!get_recycle)
		 && (!down_to_one)/* && (GetDistance(apc, svrecycle) < 50.0f)*/)
	{
		get_recycle = true;
		CameraReady();
		Stop(apc, 0);
		unit_spawn_time1 = Get_Time() + 2.0f;
		down_to_one = true;
	}

	if ((!apc_empty) && (down_to_one) && (!get_recycle)
		 /* && (GetDistance(apc, svrecycle) < 50.0f)*/)
	{
		get_recycle = true;
		CameraReady();
		Stop(apc, 0);
		unit_spawn_time1 = Get_Time() + 2.0f;
		apc_empty = true;
	}
}

		if ((get_recycle) && (!camera_off_recycle))
		{
			CameraObject(svrecycle, -4000, 1000, 2000, svrecycle);
//			camera_off_time = Get_Time + 8.0f;
			camera_on_recycle = true;		
		}

		if ((camera_on_recycle) && (unit_spawn_time1 < Get_Time()) && (!svrecycle_unit_spawn))
		{
			engineer = BuildObject("sssold",1,apc);
			Retreat (engineer, svrecycle, 1);
			AddPilot(1, -1);
			svrecycle_unit_spawn = true;
		}

		if ((svrecycle_unit_spawn) && (!svrecycle_on) && (GetDistance(engineer, svrecycle) < 25.0f))
		{
			RemoveObject(engineer);
			svrecycle_on = true;
		}

		if ((svrecycle_unit_spawn) && (!camera_off_recycle) && ((svrecycle_on) || (CameraCancelled())))
		{
			CameraFinish();
			if (IsAlive(engineer))
			{
				RemoveObject(engineer);
			}
			temp = BuildObject("svmine", 0, svrecycle);
			Defend(temp);
			RemoveObject(svrecycle);
			svrecycle = BuildObject("svrecy", 1, temp);
			RemoveObject(temp);
//			if (IsAlive(guntower1))
//			{
//				SetPerceivedTeam(guntower1, 1);
//			}
//			if (IsAlive(guntower2))
//			{
//				SetPerceivedTeam(guntower2, 1);
//			}

			if ((!camera_off_muf) && (!camera_off_supply))
			{
				ClearObjectives();					
				AddObjective("misns708.otf", WHITE);
			}
			else
			{
				if ((camera_off_muf) && (!camera_off_supply))
				{
					ClearObjectives();					
					AddObjective("misns708.otf", WHITE);
					AddObjective("misns704.otf", GREEN);
					AddObjective("misns705.otf", WHITE);
				}
				else
				{
					if ((camera_off_muf) && (camera_off_supply))
					{
						ClearObjectives();					
						AddObjective("misns708.otf", WHITE);
						AddObjective("misns704.otf", GREEN);
						AddObjective("misns706.otf", GREEN);
					}
				}
			}

			AudioMessage("misns727.wav");
			AddScrap(1, 20);
			SetAIP("misns7a.aip");
			SetPerceivedTeam(guntower1, 2);
			SetPerceivedTeam(guntower2, 2);
			SetPerceivedTeam(svrecycle, 2);
			camera_off_recycle = true;
		}

// this is when the player retakes his muf
if (!new_muf)
{
	if ((first_message_done) && (!get_muf) 
		&& (check_b < Get_Time()) && (GetDistance(apc, svmuf) < 40.0f))
	{
		check_b = Get_Time() + 3.0f;

		if ((!apc_empty) && (fully_loaded) && (!get_muf) 
			 && (!down_to_two)/* && (GetDistance(apc, svmuf) < 50.0f)*/)
		{
			get_muf = true;
			CameraReady();
			Stop(apc, 0);
			unit_spawn_time1 = Get_Time() + 2.0f;
			down_to_two = true;
		}

			if ((!apc_empty)  && (two_loaded) && (!get_muf)
				 && (!down_to_one)/* && (GetDistance(apc, svmuf) < 50.0f)*/)
			{
				get_muf = true;
				CameraReady();
				Stop(apc, 0);
				unit_spawn_time1 = Get_Time() + 2.0f;
				down_to_one = true;
			}

			if ((!apc_empty) && (one_loaded) && (!get_muf)
				 /* && (GetDistance(apc, svmuf) < 50.0f)*/)
			{
				get_muf = true;
				CameraReady();
				Stop(apc, 0);
				unit_spawn_time1 = Get_Time() + 2.0f;
				apc_empty = true;
			}

		if ((!apc_empty) && (down_to_two) && (!get_muf)
			 && (!down_to_one)/* && (GetDistance(apc, svmuf) < 50.0f)*/)
		{
			get_muf = true;
			CameraReady();
			Stop(apc, 0);
			unit_spawn_time1 = Get_Time() + 2.0f;
			down_to_one = true;
		}

		if ((!apc_empty) && (down_to_one) && (!get_muf)
			 /* && (GetDistance(apc, svmuf) < 50.0f)*/)
		{
			get_muf = true;
			CameraReady();
			Stop(apc, 0);
			unit_spawn_time1 = Get_Time() + 2.0f;
			apc_empty = true;
		}
	}

			if ((get_muf) && (!camera_off_muf))
			{
				CameraObject(svmuf, -3000, 1000, 4000, svmuf);
				camera_on_muf = true;		
			}

			if ((camera_on_muf) && (unit_spawn_time1 < Get_Time()) && (!svmuf_unit_spawn))
			{
				engineer = BuildObject("sssold",1,apc);
				Retreat (engineer, svmuf, 1);
				AddPilot(1, -1);
				svmuf_unit_spawn = true;
			}

			if ((svmuf_unit_spawn) && (!svmuf_on) && (GetDistance(engineer, svmuf) < 20.0f))
			{
				RemoveObject(engineer);
				svmuf_on = true;
			}

			if ((svmuf_unit_spawn) && (!camera_off_muf) && ((svmuf_on) || (CameraCancelled())))
			{
				if (IsAlive(engineer))
				{
					RemoveObject(engineer);
				}
				temp = BuildObject("svmine", 0, svmuf);
				Defend(temp);
				RemoveObject(svmuf);
				svmuf = BuildObject("svmuf", 1, temp);
				RemoveObject(temp);
				AddScrap(1, 20);
				CameraFinish();
				camera_off_muf = true;
			}
		// this is the message from the muf
		if ((camera_off_muf) && (!supply_message))
		{
			if (supply_first)
			{
				AudioMessage("misns709.wav");// found the key to open the lock to the silo
			}

			if (!supply_first)
			{
				AudioMessage("misns714.wav");// found a key and map to the "devil's crown in north
			}

			if (!camera_off_recycle)
			{
				ClearObjectives();	
				AddObjective("misns703.otf", GREEN);
				AddObjective("misns701.otf", WHITE);
				AddObjective("misns704.otf", GREEN);
				AddObjective("misns705.otf", WHITE);
			}

			supply_message = true;
		}
}

// this is when the player reaches the supply hut

if (camera_off_muf)
{
	if ((first_message_done) && (!get_supply) 
		&& (check_c < Get_Time()) && (GetDistance(apc, supply) < 70.0f))
	{
		check_c = Get_Time() + 3.0f;

		if ((!apc_empty) && (fully_loaded) && (!get_supply)
			 && (!down_to_two)/* && (GetDistance(apc, supply) < 50.0f)*/)
		{
			get_supply = true;
			CameraReady();
			Stop(apc, 0);
			unit_spawn_time1 = Get_Time() + 2.0f;
			down_to_two = true;
		}

			if ((!apc_empty) && (two_loaded) && (!get_supply)
				 && (!down_to_one)/* && (GetDistance(apc, supply) < 50.0f)*/)
			{
				get_supply = true;
				CameraReady();
				Stop(apc, 0);
				unit_spawn_time1 = Get_Time() + 2.0f;
				down_to_one = true;
			}

			if ((!apc_empty) && (one_loaded) && (!get_supply)
				 /* && (GetDistance(apc, supply) < 50.0f)*/)
			{
				get_supply = true;
				CameraReady();
				Stop(apc, 0);
				unit_spawn_time1 = Get_Time() + 2.0f;
				apc_empty = true;
			}

		if ((!apc_empty) && (down_to_two) && (!get_supply)
			 && (!down_to_one)/* && (GetDistance(apc, supply) < 50.0f)*/)
		{
			get_supply = true;
			CameraReady();
			Stop(apc, 0);
			unit_spawn_time1 = Get_Time() + 2.0f;
			down_to_one = true;
		}

		if ((!apc_empty) && (down_to_one) && (!get_supply)
			 /* && (GetDistance(apc, supply) < 50.0f)*/)
		{
			get_supply = true;
			CameraReady();
			Stop(apc, 0);
			unit_spawn_time1 = Get_Time() + 2.0f;
			apc_empty = true;
		}
	}

		if ((get_supply) && (!camera_off_supply))
		{
			CameraObject(supply, 1000, 1000, 8000, supply);
			camera_on_supply = true;		
		}

		if ((camera_on_supply) && (unit_spawn_time1 < Get_Time()) && (!supply_unit_spawn))
		{
			engineer = BuildObject("sssold",1,apc);
			Retreat (engineer, "con_path", 1);
			AddPilot(1, -1);
			supply_unit_spawn = true;
		}

		if ((supply_unit_spawn) && (IsAlive(engineer)) 
			&& (!supply_on) && (GetDistance(engineer, con_geyser) < 30.0f))
		{
			RemoveObject(engineer);
//			supply_message_time = Get_Time() + 3.0f;
			supply_on = true;
		}

		if ((supply_unit_spawn) && (!camera_off_supply) && ((supply_on) || (CameraCancelled())))
		{
			if (IsAlive(engineer))
			{
				RemoveObject(engineer);
			}

			if (!camera_off_recycle)
			{
				ClearObjectives();					
				AddObjective("misns703.otf", GREEN);
				AddObjective("misns701.otf", WHITE);
				AddObjective("misns704.otf", GREEN);
				AddObjective("misns706.otf", GREEN);
			}
			else
			{
				ClearObjectives();	
				AddObjective("misns708.otf", WHITE);
				AddObjective("misns704.otf", GREEN);
				AddObjective("misns706.otf", GREEN);
			}

			camera_off_supply = true;
			CameraFinish();
		}
		
		// now that the player has an engineer in the supply shed he willl be given the goods

		if ((camera_off_supply) && /*(supply_message_time < Get_Time()) && */(!supply2_message))
		{
			AudioMessage("misns707.wav"); // I found some supplies in here
			supply_spawn_time = Get_Time() + 15.0f;
			supply2_message = true;
		}

		if ((supply_message) && (supply_spawn_time < Get_Time()) && (!supplies_spawned))
		{
			supply1 = BuildObject("svscav", 1, "supply1");
			supply2 = BuildObject("svturr", 1, "supply2");
			supply3 = BuildObject("svturr", 1, "supply3");
			supply4 = BuildObject("svscav", 1, "supply4");
			supply5 = BuildObject("spammo", 1, "supply5");
			supply6 = BuildObject("spammo", 1, "supply6");
			supply7 = BuildObject("spammo", 1, "supply7");
			supply8 = BuildObject("sprepa", 1, "supply8");
			supply9 = BuildObject("sprepa", 1, "supply9");
			Stop(supply1, 0);
			Stop(supply4, 0);
			supplies_spawned = true;
		}

		if ((supplies_spawned) && (!turret_message))
		{
			AudioMessage("misns721.wav");
			Stop(supply1, 0);
			Stop(supply4, 0);
			turret_message = true;
		}
}

	if ((IsAlive(supply)) && (!camera_off_muf) 
		&& (GetDistance(user, supply) < 70.0f) && (!supply_first))
	{
		AudioMessage("misns715.wav"); // tells the player that the hut is locked
		supply_first = true;
	}

// this is sending the nsdf scavengers to their silo

	if (((supply_first) || (camera_off_muf)) && (!plan_a))
	{
		if (IsAlive(avsilo))
		{
			if (IsAlive(avscav1))
			{
				Goto(avscav1, avsilo);
			}
			if (IsAlive(avscav2))
			{
				Goto(avscav2, avsilo);
			}
			if (IsAlive(avturr1))
			{
				Goto(avturr1, "avsilo_spot1", 1);
			}
			if (IsAlive(avturr2))
			{
				Goto(avturr2, "avsilo_spot2", 1);
			}
			if (IsAlive(avfight1))
			{
				Goto(avfight1, avsilo, 0);
			}
			if (IsAlive(avfight2))
			{
				Goto(avfight2, avsilo, 0);
			}
		}

		SetAIP("misns7b.aip");// this has scavs
		SetPerceivedTeam(guntower1, 2);
		SetPerceivedTeam(guntower2, 2);
		SetPerceivedTeam(svrecycle, 2);

		if (IsAlive(avrig))
		{
			Defend(avrig);
		}

		plan_a = true;
	}

//	if ((plan_a) && (!IsAlive(avrig)) && (!plan_d))
//	{
//		SetAIP("misns7a.aip");// this has scavs
//
//		if ((!IsAlive(avscav1)) && (!IsAlive(avscav2)))
//		{
//			AddScrap(2, 20);
//		}
//
//		plan_d = true;
//	}

// this is checking to see if a gech is build and what to do with it

	if ((muf_scan_time < Get_Time()) && (!muf_located))
	{
		muf_scan_time = Get_Time() + 3.0f;
		if (IsAlive(svmuf))
		{
			stuff2 = CountUnitsNearObject(svmuf, 200.0f, 2, NULL);
			if (stuff2 > 0)
			{
				muf_located = true;
			}
		}
	}

	if ((IsAlive(avgech)) && (!gech_sent))
	{
		if (muf_located)
		{
			if (IsAlive(svmuf))
			{
				Attack(avgech, svmuf);
			}
		}
		else
		{
			if(IsAlive(avsilo))
			{
				Goto(avgech, avsilo, 0);
			}
		}

		gech_sent = true;
	}

	if ((gech_sent) && (muf_located) && (!gech_adjust))
	{
		if ((IsAlive(avgech)) && (IsAlive(svmuf)))
		{
			Attack(avgech, svmuf);
			gech_adjust = true;
		}
	}

// this is the script that tells the rig to build a base

	// this sends the rig to build the first guntower
	if ((in_base) && (!build_tower1))
	{
		if (IsAlive(avrig))
		{
			Dropoff(avrig, "tower1_spot");
			build_tower1 = true;
		}
	}

	// this sends the rig to build the third powerplant
	if ((build_tower1) && (IsAlive(avtower1)) && (!b1))
	{
		if (IsAlive(avrig))
		{
			Build(avrig, "abwpow");// this is avpower1
			b1_time = Get_Time() + 5.0f;
			b1 = true;
		}
	}

	if ((b1) && (b1_time < Get_Time()) && (!build_power1))
	{
		if (IsAlive(avrig))
		{	
			AddScrap(2, 20);
			Dropoff(avrig, "power1_spot");
			b2_time = Get_Time() + 5.0f;
			build_power1 = true;
		}
	}
	// this sends the rig to build the next guntower
	if ((build_power1) && (!main_off) && (!maint_off) && (IsAlive(avpower1)) && (!b2))
	{
		if ((b2_time < Get_Time()) && (IsAlive(avrig)))
		{
			Build(avrig, "abtowe");// this is avtower2
			b3_time = Get_Time() + 5.0f;
			b2 = true;
		}
	}

	if ((b2) && (b3_time < Get_Time()) && (!build_tower2))
	{
		if (IsAlive(avrig))
		{
			Dropoff(avrig, "tower2_spot");
			b4_time = Get_Time() + 5.0f;
			build_tower2 = true;
		}
	}
	// this removes the rig and builds it again at the barracks spot
	if ((IsAlive(avtower2)) && (IsAlive(avrig)) && (!new_rig) 
		&& (GetDistance(user, avrig) > 400.0f) && (b4_time < Get_Time()))
	{
		RemoveObject(avrig);
//		avrig = BuildObject("avcnst", 2, "barrack_spot");
//		Defend(avrig);
//		Build(avrig, "abbarr");
		rig_check = Get_Time() + 10.0f;
//		bm_time = Get_Time() + 5.0f;
		new_rig = true;
	}
	// this waits until the player is close and then builds a barracks, a turret and moves the rig
if (rig_show)
{
	// this has the rig trying to maintain the main power and guntower
	if ((IsAlive(avrig)) && (!IsAlive(main_power)) && (!main_off)/* && (bm_time < Get_Time())*/)
	{
		Build(avrig, "abwpow");
		bm_time = Get_Time() + 10.0f;
//		main_on = false;
		main_off = true;
	}
		
		if ((main_off) && (bm_time < Get_Time()) && (!main_build))
		{
			if (IsAlive(avrig))
			{
				Dropoff(avrig, "main_power");
//				bm_time = Get_Time() + 5.0f;
				main_build = true;
			}
		}

		if ((main_build) && (IsAlive(main_power)))
		{
//			bm_time = Get_Time() + 5.0f;
			main_build = false;
			main_off = false;
		}

	if ((IsAlive(avrig)) && (!IsAlive(main_tower)) && (!main_off)
		&& (!maint_off))
	{
		Build(avrig, "abtowe");
		bm_time = Get_Time() + 10.0f;
//		maint_on = false;
		maint_off = true;
	}
		
		if ((maint_off) && (!maint_build) && (bm_time < Get_Time()))
		{
			if (IsAlive(avrig))
			{
//				bm_time = Get_Time() + 5.0f;
				Dropoff(avrig, "main_tower");
				maint_build = true;
			}
		}

		if ((maint_build) && (IsAlive(main_tower)))
		{
//			bm_time = Get_Time() + 5.0f;
//			maint_on = true;
			maint_build = false;
			maint_off = false;
		}
}

	// this happens immediately after the player returns to the american base
	if ((!rig_show) && (rig_check < Get_Time()))
	{
		rig_check = Get_Time() + 5.0f;

		if (GetDistance(user, avrecycle) < 400.0f)
		{
			avrig = BuildObject("avcns7", 2, "barrack_spot");
			Defend(avrig);
			Build(avrig, "abbarr");
			rig_check = Get_Time() + 20.0f;
			rig_show = true;
		}
	}

	if ((rig_show) && (IsAlive(avrig)) && (rig_check < Get_Time()) && (!blah))
	{
		Dropoff(avrig, "barrack_spot"); // this is avbarrack
		avturr4 = BuildObject("bvturr", 2, "muf_point");
		Goto(avturr4, "base_turret_spot1", 1);
		turret_check = Get_Time() + 60.0f;
		blah = true;
	}


	// this stops the turret when its at its post
	if ((IsAlive(avturr4)) && (turret_check < Get_Time()) && (!turret4_defend))
	{
		Defend(avturr4, 1);

		if (IsAlive(avrig))
		{
			Defend(avrig, 1);
		}

		turret4_defend = true;
	}

/*	// this tells the rig to build the power plant in the center of the base
	if ((camera_off_recycle) && (IsAlive(avrig)) && (!main_off) && (!maint_off) && (!b3))
	{
		Build(avrig, "abwpow");// this is avpower2
		b5_time = Get_Time() + 5.0f;
		b3 = true;
	}

	if ((b3) && (!rig_show2) && (b5_time < Get_Time()))
	{
		if (IsAlive(avrig))
		{
			Dropoff(avrig, "power2_spot");
			b6_time = Get_Time() + 5.0f;
			rig_show2 = true;
		}
	}

	// this tells the rig to build the last guntower
	if ((rig_show2) && (IsAlive(avrig)) && ((IsAlive(avpower2)) || (IsAlive(avpower1)))
		&& (!main_off) && (!maint_off) && (!b4) && (b6_time < Get_Time()))
	{
		Build(avrig, "abtowe");// this is nothing
		b7_time = Get_Time() + 5.0f;
		b4 = true;
	}

	if ((b4) && (!rig_show3) && (b7_time < Get_Time()))
	{
		if (IsAlive(avrig))
		{
			Dropoff(avrig, "tower3_spot");
			rig_show3 = true;
		}
	}
*/

// this is determining if the player has got the the recycler before the muf
	
	if ((camera_off_recycle) && (!camera_off_muf) && (IsAlive(newmuf)) && (!new_muf))
	{
		new_muf = true;
	}

/// this is the message when the player reaches his silo

	if ((!silo_message) && (IsAlive(svsilo)) && (silo_check < Get_Time()))
	{
		silo_check = Get_Time() + 5.0f;

		if (GetDistance(user, svsilo) < 90.0f)
		{
			AudioMessage("misns720.wav"); // looks like one of ours
			silo_message = true;
		}
	}

// win/loose conditions

	if ((!IsAlive(avrecycle)) && (!game_over))
	{
		AudioMessage("misns712.wav"); // congradulations
		SucceedMission(Get_Time() + 10.0f, "misns7w1.des");
		game_over = true;
	}

	if ((((con1_dead) && (con2_dead) && (con3_dead) && (!fully_loaded)) ||
		((con1_dead) && (con2_dead) && (con3_dead) && (!two_loaded)) ||
		((con1_dead) && (con2_dead) && (con3_dead) && (!one_loaded))) && (!game_over))
	{															
		AudioMessage("misns711.wav"); // our comrades are dead
		FailMission(Get_Time() + 10.0f, "misns7f1.des");
		game_over = true;
	}															
																	
	if ((!IsAlive(apc)) && (!camera_off_recycle) && (!camera_off_muf) && (!game_over))
	{
		AudioMessage("misns716.wav"); // you lost the apc
		FailMission(Get_Time() + 10.0f, "misns7f2.des");
		game_over = true;
	}


// END OF SCRIPT
}

IMPLEMENT_RTIME(Misns7Mission)

Misns7Mission::Misns7Mission(void)
{
}

Misns7Mission::~Misns7Mission()
{
}

void Misns7Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

bool Misns7Mission::Load(file fp)
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

bool Misns7Mission::PostLoad(void)
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

bool Misns7Mission::Save(file fp)
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

void Misns7Mission::Update(void)
{
	AiMission::Update();
	Execute();
}
