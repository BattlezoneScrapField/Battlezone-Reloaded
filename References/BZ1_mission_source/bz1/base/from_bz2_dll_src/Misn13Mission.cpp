#include "GameCommon.h"

#include "..\fun3d\AiMission.h"
#include "..\fun3d\PowerUp.h"
#include "..\fun3d\ScriptUtils.h"

/*
	Misn13Mission
*/

class Misn13Mission : public AiMission {
	DECLARE_RTIME(Misn13Mission)
public:
	Misn13Mission(void);
	~Misn13Mission();

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
				start_done,
				silos_gone,
				turret_move,
				first_wave,
				second_wave,
				turret1_set,
				turret2_set,
				artil_move, artil_move2,
				artil_set,
				wave2, wave2_done, wave2_move,
				wave3, wave3_done, wave3_move,
				wave4, wave4_done, wave4_move,
				a, b, c, d,
				silo1_lost, silo2_lost, silo3_lost, silo4_lost,
				make_bomber,
				bomber_attack,
				new_target, bomber_retreat,
				sv1_wait, sv4_wait, sv3_wait,
				sv1_reload, sv2_reload, sv3_reload, sv4_reload,
				set_aip, hold_aip,
				bomber_reload,
				assign_tank1, assign_tank2, assign_tank3, assign_tank4, 
				silos_attacked, silo_defend,
				muf_attacked, muf_safe,
				turret1_muf, turret2_muf, turret5_muf, turret6_muf,
				player_center,
				apc_sent,
				artil_lost,
				game_over,
				scav_swap, artil_message,
				b_last;
		};
		bool b_array[59];
	};

	// floats
	union {
		struct {
			float
				first_wave_time, 
				second_wave_time,
				next_wave_time,
				artil_move_time,
				artil_set_time,
				set_aip_time,
				bomber_retreat_time,
				turret_move_time,
				new_orders_time,
				safe_time_check,
				scrap_check,
				f_last;
		};
		float f_array[11];
	};

	// handles
	union {
		struct {
			Handle
				user,
				nsdfrecycle, nsdfmuf,
				nav1,
				checkpoint1, checkpoint2, checkpoint3, checkpoint4,
				ccacom_tower,
				ccasilo1, ccasilo2, ccasilo3, ccasilo4,
				spawn_point1, spawn_point2,
				check1, check2, check3,
				ccamuf, ccaslf, ccaapc,
				turret1, turret2, turret3, turret4, turret5, turret6, 
				artil1, artil2, artil3, artil4,
				fighter1, fighter2, fighter3, fighter4, fighter5, fighter6, 
				sv1, sv2, sv3, sv4, sv5, sv6, sv7, sv8, sv9, sv0,
				tank1, tank2, tank3, tank4, tank5, tank6, tank7, tank8,
				key_geyser1, key_geyser2, split_geyser, center_geyser,
				choke_bridged,
				guntower1, controltower,
				center, svscav1, svscav2, svscav3, svscav4, svscav5, svscav6, svscav7, svscav8,
				escort_tank, nsdfrig, avscav1, avscav2, avscav3,
				h_last;
		};
		Handle h_array[76];
	};

	// integers
	union {
		struct {
			int
				check, scrap, shot_by,
				i_last;
		};
		int i_array[3];
	};
};

void Misn13Mission::Setup(void)
{
/* Here's where you set the values at the start. */

	check = 0;
	scrap = 100;
	shot_by = 0;
	
	start_done = false;
	silos_gone = false;
	turret_move = false;
	first_wave = false;
	second_wave = false;
	artil_move = false;
	artil_move2 = false;
	turret1_set = false;
	turret2_set = false;
	artil_set = false;
	wave2 = false;
	wave2_done = false;
	wave2_move = false;
	wave3 = false;
	wave3_done = false;
	wave3_move = false;
	wave4 = false;
	wave4_done = false;
	wave4_move = false;
	a = false;
	b = false;
	c = false;
	d = false;
	silo1_lost = false;
	silo2_lost = false;
	silo3_lost = false;
	silo4_lost = false;
	make_bomber = false;
	bomber_attack = false;
	new_target = false;
	bomber_retreat = false;
	set_aip = false;
	sv1_wait = false;
	sv4_wait = false;
	sv3_wait = false;
	sv1_reload = false;
	sv2_reload = false;
	sv3_reload = false;
	sv4_reload = false;
	bomber_reload = false;
	hold_aip = false;
	assign_tank1 = false;
	assign_tank2 = false;
	assign_tank3 = false;
	assign_tank4 = false;
	silos_attacked = false;
	silo_defend = false;
	muf_attacked = false;
	muf_safe = false;
	turret1_muf = false;
	turret2_muf = false;
	turret5_muf = false;
	turret6_muf = false;
	choke_bridged = false;
	artil_lost = true;
	apc_sent = false;
	game_over = false;
	scav_swap = false;
	artil_message = false;

	first_wave_time = 99999.0f;
	second_wave_time = 99999.0f;
	next_wave_time = 99999.0f;
	artil_move_time = 99999.0f;
	artil_set_time = 99999.0f;
	set_aip_time = 99999.0f;
	bomber_retreat_time = 99999.0f;
	turret_move_time = 99999.0f;
	new_orders_time = 99999.0f;
	safe_time_check = 99999.0f;
	scrap_check = 60.0f;


	checkpoint1 = GetHandle("svguntower1");
//	checkpoint2 = GetHandle("svcontroltower");
	checkpoint3 = GetHandle("svmuf");
	checkpoint4 = GetHandle("svsilo1");
	ccasilo1 = GetHandle ("svsilo1");
	ccasilo2 = GetHandle ("svsilo2");
	ccasilo3 = GetHandle ("svsilo3");
	ccasilo4 = GetHandle ("svsilo4");
	ccamuf = GetHandle("svmuf");
	ccaslf = GetHandle("svslf");
	ccacom_tower = GetHandle("svcom_tower");
	spawn_point1 = GetHandle("spawn_geyser1");
	spawn_point2 = GetHandle("spawn_geyser2");
	nav1 = GetHandle("apcamr20_camerapod");
	turret1 = GetHandle("turret1");
	turret2 = GetHandle("turret2");
	turret3 = GetHandle("turret3");
	turret4 = GetHandle("turret4");
	turret5 = GetHandle("turret5");
	turret6 = GetHandle("turret6");
	artil1 = GetHandle("artil1");
	artil2 = GetHandle("artil2");
	artil3 = GetHandle("artil3");
	artil4 = GetHandle("artil4");
	fighter1 = GetHandle("fighter1");
	fighter2 = GetHandle("fighter2");
	fighter3 = GetHandle("fighter3");
	fighter4 = GetHandle("fighter4");
	fighter5 = GetHandle("fighter5");
	fighter6 = GetHandle("fighter6");
	tank1 = GetHandle("tank1");
	tank2 = GetHandle("tank2");
	tank3 = GetHandle("tank3");
	tank4 = GetHandle("tank4");
	key_geyser1 = GetHandle("key_geyser1");
	key_geyser2 = GetHandle("key_geyser2");
	center_geyser = GetHandle("center_geyser");
	split_geyser = GetHandle("split_geyser");
	nsdfrecycle = GetHandle("avrecycle");
//	ccaapc = GetHandle("svapc");
	svscav1 = GetHandle("svscav1"); 
	svscav2 = GetHandle("svscav2"); 
	svscav3 = GetHandle("svscav3"); 
	svscav4 = GetHandle("svscav4"); 
	svscav5 = NULL;
	svscav6 = NULL;
	svscav7 = NULL;
	svscav8 = NULL;
	sv1 = NULL;
	sv2 = NULL;
	sv3 = NULL;
	sv4 = NULL;
	guntower1 = NULL;
	controltower = NULL;
	tank5 = NULL;
	tank6 = NULL;
	tank7 = NULL;
	tank8 = NULL;
	nsdfmuf = NULL;
	nsdfrig = NULL;
	avscav1 = NULL;
	avscav2 = NULL;
	avscav3 = NULL;
	center = GetHandle ("center");


}

// this is the handle thing brad made for me
void Misn13Mission::AddObject(Handle h)
{
	if ((sv1 == NULL) && (IsOdf(h,"svapc13")))
	{
		sv1 = h;
	}
	else if ((sv2 == NULL) && (IsOdf(h,"svapc13")))
	{
		sv2 = h;
	}		
	else if ((sv3 == NULL) && (IsOdf(h,"svhr13")))
	{
		sv3 = h;
	}
	else if ((sv4 == NULL) && (IsOdf(h,"svhr13")))
	{
		sv4 = h;
	}
	else if (IsOdf(h,"abtowe"))
	{
		guntower1 = h;
	}
	else if ((controltower == NULL) && (IsOdf(h,"abcomm")))
	{
		controltower = h;
	}
	else if ((tank5 == NULL) && (IsOdf(h,"svtk13")))
	{
		tank5 = h;
	}
	else if ((tank6 == NULL) && (IsOdf(h,"svtk13")))
	{
		tank6 = h;
	}
	else if ((tank7 == NULL) && (IsOdf(h,"svtk13")))
	{
		tank7 = h;
	}
	else if ((tank8 == NULL) && (IsOdf(h,"svtk13")))
	{
		tank8 = h;
	}
	else if ((nsdfmuf == NULL) && (IsOdf(h,"avmuf")))
	{
		nsdfmuf = h;
	}
	else if ((nsdfrig == NULL) && (IsOdf(h,"avcnst")))
	{
		nsdfrig = h;
	}
	else if ((avscav1 == NULL) && (IsOdf(h,"avscav")))
	{
		avscav1 = h;
	}
	else if ((avscav2 == NULL) && (IsOdf(h,"avscav")))
	{
		avscav2 = h;
	}
	else if ((avscav3 == NULL) && (IsOdf(h,"avscav")))
	{
		avscav3 = h;
	}
}

void Misn13Mission::Execute(void)
{

// START OF SCRIPT

	user = GetPlayerHandle(); //assigns the player a handle every frame

// these are constants
	if (bomber_attack)
	{
		if (!IsAlive(sv1))
		{
			sv1_wait = false;
		}
		if (!IsAlive(sv4))
		{
			sv4_wait = false;
		}
		if (!IsAlive(sv3))
		{
			sv3_wait = false;
		}
		if ((!IsAlive(sv3)) && (!IsAlive(sv4)))
		{
			make_bomber = false;
			bomber_attack = false;
			new_target = false;
			bomber_retreat = false;
			bomber_retreat_time = 99999.0f;
			bomber_reload = false;
//			sv1_reload = false;
//			sv2_reload = false;
//			sv3_reload = false;
//			sv4_reload = false;

		}
	}

	if (!IsAlive(tank1))
	{
		assign_tank1 = false;
	}
	if (!IsAlive(tank2))
	{
		assign_tank2 = false;
	}
	if (!IsAlive(tank3))
	{
		assign_tank3 = false;
	}
	if (!IsAlive(tank4))
	{
		assign_tank4 = false;
	}

// end of constants ///////////////////////////////////////////////////////////////////
	
	if (!start_done)
	{
		AudioMessage("misn1300.wav");
		ClearObjectives();
		AddObjective("misn1300.otf", WHITE);
		SetPilot(1, 10);
		SetPilot(2, 40);
		SetScrap(1,40);
		SetScrap(2, 200);
		Defend(tank1);
		Defend(tank2);
		Defend(artil1);
		Defend(artil2);
		Defend(artil3);
		Defend(artil4);
//		Defend(ccaapc);
		escort_tank = BuildObject("svtank", 2, artil1);
		if (nav1!=NULL) GameObjectHandle::GetObj(nav1)->SetName("Drop Zone");
		Defend(escort_tank);
		first_wave_time = Get_Time()+5.0f;
		next_wave_time = Get_Time()+300.0f;

		artil_move_time = Get_Time()+ 900.0f; // this may move

		start_done = true;
	}

// this is going to subtract scrap from the soviets if the silos are destroyed

	if ((!IsAlive(ccasilo1)) && (GetScrap(2) > 150) && (!silo1_lost))
	{
		SetScrap(2,150);
		silo1_lost = true; 
	}

	if ((!IsAlive(ccasilo2)) && (GetScrap(2) > 150) && (!silo1_lost))
	{
		SetScrap(2,150);
		silo1_lost = true; 
	}

	if ((!IsAlive(ccasilo3)) && (GetScrap(2) > 150) && (!silo1_lost))
	{
		SetScrap(2,150);
		silo1_lost = true; 
	}

	if ((!IsAlive(ccasilo4)) && (GetScrap(2) > 150) && (!silo1_lost))
	{
		SetScrap(2,150);
		silo1_lost = true; 
	}

	if ((!IsAlive(ccasilo1)) && (!IsAlive(ccasilo2)) && (GetScrap(2) > 100) && (!silo2_lost))
	{
		SetScrap(2,100);
		silo2_lost = true; 
	}

	if ((!IsAlive(ccasilo1)) && (!IsAlive(ccasilo3)) && (GetScrap(2) > 100) && (!silo2_lost))
	{
		SetScrap(2,100);
		silo2_lost = true; 
	}

	if ((!IsAlive(ccasilo1)) && (!IsAlive(ccasilo4)) && (GetScrap(2) > 100) && (!silo2_lost))
	{
		SetScrap(2,100);
		silo2_lost = true; 
	}

	if ((!IsAlive(ccasilo2)) && (!IsAlive(ccasilo3)) && (GetScrap(2) > 100) && (!silo2_lost))
	{
		SetScrap(2,100);
		silo2_lost = true; 
	}

	if ((!IsAlive(ccasilo2)) && (!IsAlive(ccasilo4)) && (GetScrap(2) > 100) && (!silo2_lost))
	{
		SetScrap(2,100);
		silo2_lost = true; 
	}

	if ((!IsAlive(ccasilo3)) && (!IsAlive(ccasilo4)) && (GetScrap(2) > 100) && (!silo2_lost))
	{
		SetScrap(2,100);
		silo2_lost = true; 
	}

	if ((!IsAlive(ccasilo1)) && (!IsAlive(ccasilo2)) && (!IsAlive(ccasilo3))
		&& (GetScrap(2) > 50) && (!silo3_lost))
	{
		SetScrap(2,50);
		silo3_lost = true; 
	}

	if ((!IsAlive(ccasilo1)) && (!IsAlive(ccasilo2)) && (!IsAlive(ccasilo4))
		&& (GetScrap(2) > 50) && (!silo3_lost))
	{
		SetScrap(2,50);
		silo3_lost = true; 
	}

	if ((!IsAlive(ccasilo1)) && (!IsAlive(ccasilo3)) && (!IsAlive(ccasilo4))
		&& (GetScrap(2) > 50) && (!silo3_lost))
	{
		SetScrap(2,50);
		silo3_lost = true; 
	}

	if ((!IsAlive(ccasilo2)) && (!IsAlive(ccasilo3)) && (!IsAlive(ccasilo4))
		&& (GetScrap(2) > 50) && (!silo3_lost))
	{
		SetScrap(2,50);
		silo3_lost = true; 
	}

	if ((!IsAlive(ccasilo1)) && (!IsAlive(ccasilo2)) && (!IsAlive(ccasilo3))
		 && (!IsAlive(ccasilo4)) && (GetScrap(2) > 0) && (!silos_gone))
	{
		silos_gone = true;
		SetScrap(2,0);
	}

// now I'm going to start the battle by sending the turrets to smart locations
	// this immediately sends turrets to key locations
	
	if ((start_done) && (!turret_move))
	{
		Retreat(turret1, "turret_path1");	// a scrap field vital to americans
		Retreat(turret2, "turret_path1");	// a scrap field vital to americans
		Defend(turret3);					// the main choke point where americans must come through
		Defend(turret4);					// the main choke point where americans must come through
		Retreat(turret5, "turret_path2");	// the scrap silos
		Retreat(turret6, "turret_path2");	// the scrap silos
		Goto(ccaslf, "slf_path");
		turret_move_time = Get_Time() + 120.0f;
		turret_move = true;
	}

	if ((turret_move) && (turret_move_time < Get_Time()) && (!silo_defend))
	{
		turret_move_time = Get_Time() + 3.0f;

		if ((GetDistance(turret5, ccasilo1) < 60.0f) && (GetDistance(turret6, ccasilo1) < 60.0f))
		{
			Defend(turret5);
			Defend(turret6);
			silo_defend = true;
		}
	}

	if ((turret_move) && (turret_move_time < Get_Time()) && (!turret1_set))
	{
		if (GetDistance(turret1, key_geyser1) < 100.0f)
		{
			Goto(turret1, key_geyser1);
			turret1_set = true;
		}
	}

	if ((turret_move) && (turret_move_time < Get_Time()) && (!turret2_set))
	{
		if (GetDistance(turret2, key_geyser1) < 100.0f)
		{
			Goto(turret2, key_geyser2);
			turret2_set = true;
		}
	}

// sending the tanks that would have been following the player in for the first attack
	if ((start_done) && (first_wave_time < Get_Time()) && (!first_wave))
	{
		Attack(tank3, nsdfrecycle, 1);
		Attack(tank4, nsdfrecycle, 1);
		Attack(fighter5, nsdfrecycle, 1);
		Attack(fighter6, nsdfrecycle, 1);
		second_wave_time = Get_Time()+ 5.0f;
		first_wave = true;
	}

	if ((first_wave) && (second_wave_time < Get_Time()) && (!second_wave))
	{
		Goto(fighter1, "choke_point1");
		Goto(fighter2, "choke_point1");
		Goto(fighter3, key_geyser1);
		Goto(fighter4, key_geyser2);

		set_aip_time = Get_Time() + 60.0f;
		second_wave = true;
	}

	if ((!set_aip) && (set_aip_time < Get_Time()) && (!hold_aip) && (!muf_attacked))
	{
		set_aip_time = Get_Time() + 240.0f;
 		SetAIP("misn13.aip");
//		set_aip = true;
	}

//	if (set_aip)
//	{
//		set_aip = false;
//	}

// tank code

	if ((IsAlive(tank1)) && (!assign_tank1))
	{
		Follow(tank1, ccamuf);
		assign_tank1 = true;
	}

	if ((IsAlive(tank2)) && (!assign_tank2))
	{
		Follow(tank2, ccamuf);
		assign_tank2 = true;
	}

	if ((IsAlive(tank3)) && (!assign_tank3))
	{
		Follow(tank3, center);
		assign_tank3 = true;
	}

	if ((IsAlive(tank4)) && (!assign_tank4))
	{
		Follow(tank4, center);
		assign_tank4 = true;
	}

// this sends the first apc after the player's comtower

//	if ((IsAlive(controltower)) && (!apc_sent))
//	{
//		Attack(ccaapc, controltower, 1);
//		apc_sent = true;
//	}
	
// this is bomber code ////////////////////////////////////////////////////////////////////////////


	if (((IsAlive(guntower1)) || (IsAlive(controltower))) && (!make_bomber) && (!muf_attacked))
	{
		SetAIP("misn13a.aip");
		hold_aip = true;
		make_bomber = true;
	}

	if ((make_bomber) && (!bomber_attack))
	{
		if ((IsAlive(sv4)) && (!sv4_wait))
		{
			if (IsAlive(guntower1))
			{
				Attack(sv4, guntower1);
			}
			else
			{
				if (IsAlive(nsdfmuf))
				{
					Attack(sv4, nsdfmuf);
				}
				else
				{
					if (IsAlive(controltower))
					{
						Attack(sv4, controltower);
					}
				}

				if (IsAlive(tank5))
				{
					Follow(tank5, sv4);
				}	
			}

			sv4_wait = true;
		}
			

		if ((IsAlive(sv1)) &&(!sv1_wait))
		{
			if (IsAlive(controltower))
			{
				Attack(sv1, controltower);
			}
			else
			{
				if (IsAlive(guntower1))
				{
					Attack(sv1, guntower1);
				}
				else
				{
					if (IsAlive(nsdfmuf))
					{
						Attack(sv1, nsdfmuf);
					}
				}		
			}

			if (IsAlive(tank6))
			{
				Follow(tank6, sv1);
			}

			sv1_wait = true;
		}

		if ((IsAlive(sv3)) && (!sv3_wait))
		{
			if (IsAlive(guntower1))
			{
				Attack(sv3, guntower1);
			}
			else
			{
				if (IsAlive(nsdfmuf))
				{
					Attack(sv3, nsdfmuf);
				}
				else
				{
					if (IsAlive(controltower))
					{
						Attack(sv3, controltower);
					}
				}

				if (IsAlive(tank7))
				{
					Follow(tank7, sv3);
				}
			}

			sv3_wait = true;
		}
	}

	if ((sv1_wait) && (sv3_wait) && (sv4_wait) && (!bomber_attack))
	{
		hold_aip = false;
//		bomber_reload = false;
		bomber_attack = true;
	}
	

	if ((bomber_attack) && (!IsAlive(guntower1)) && (!new_target))
	{
		if (IsAlive(controltower))
		{
			if(IsAlive(sv1))
			{
				Attack(sv1, controltower);
			}
			if(IsAlive(sv3))
			{
				Attack(sv3, controltower);
			}
			if(IsAlive(sv4))
			{
				Attack(sv4, controltower);
			}
			
			new_target = true;
		}
		else
		{
			if (IsAlive(nsdfmuf))
			{
				if(IsAlive(sv1))
				{
					Attack(sv1, nsdfmuf);
				}
				if(IsAlive(sv3))
				{
					Attack(sv3, nsdfmuf);
				}
				if(IsAlive(sv4))
				{
					Attack(sv4, nsdfmuf);
				}
				
				new_target = true;
			}
		}
/*			else
			{
				if (IsAlive(sv1))
				{
					Retreat(sv1, ccamuf);
				}
				if (IsAlive(sv3))
				{
					Retreat(sv3, ccamuf);
				}
				if (IsAlive(sv4))
				{
					Retreat(sv4, ccamuf);
				}
			}
*/
//		bomber_retreat_time = Get_Time() + 15.0f;
//		bomber_retreat = true;
	}


/*
	if ((new_target) && ((!IsAlive(controltower)) || (!IsAlive(nsdfmuf))) && (!bomber_retreat))
	{
		if(IsAlive(sv1))
		{
			Retreat(sv1, ccamuf);
		}
//		if(IsAlive(sv2))
//		{
//			Retreat(sv2, ccamuf);
//		}
		if(IsAlive(sv3))
		{
			Retreat(sv3, ccamuf);
		}
		if(IsAlive(sv4))
		{
			Retreat(sv4, ccamuf);
		}
		
		bomber_retreat_time = Get_Time() + 15.0f;
		bomber_retreat = true;
	}

*/
/*
	if ((bomber_retreat) && (bomber_retreat_time < Get_Time()) && (!bomber_reload))
	{
		bomber_retreat_time = Get_Time() + 15.0f;

		if (GetDistance(user, ccamuf) > 500.0f)
		{
			if ((IsAlive(sv1)) && (GetDistance(sv1, ccamuf) < 100.0f) && (!sv1_reload))
			{
				RemoveObject(sv1);
				sv1 = BuildObject("avhraz", 2, ccamuf);
				AddScrap(2, -2);
				sv1_reload = true;
			}
//			if ((IsAlive(sv2)) && (GetDistance(sv2, ccamuf) < 50.0f) && (!sv2_reload))
//			{
//				RemoveObject(sv2);
//				sv2 = BuildObject("avhraz", 2, ccamuf);
//				AddScrap(2, -2);
//				sv2_reload = true;
//			}
			if ((IsAlive(sv3)) && (GetDistance(sv3, ccamuf) < 100.0f) && (!sv3_reload))
			{
				RemoveObject(sv3);
				sv3 = BuildObject("avhraz", 2, ccamuf);
				AddScrap(2, -2);
				sv3_reload = true;
			}
			if ((IsAlive(sv4)) && (GetDistance(sv4, ccamuf) < 100.0f) && (!sv4_reload))
			{
				RemoveObject(sv4);
				sv4 = BuildObject("avhraz", 2, ccamuf);
				AddScrap(2, -2);
				sv4_reload = true;
			}
		}
*/

//		if (((sv1_reload) && /*(sv2_reload) && */(sv3_reload) && (sv4_reload)) ||
//			((!IsAlive(sv1)) && /*(sv2_reload) && */(sv3_reload) && (sv4_reload)) ||
//			(/*(!IsAlive(sv2)) && */(sv1_reload) && (sv3_reload) && (sv4_reload)) ||
//			((!IsAlive(sv3)) && (sv1_reload) && /*(sv2_reload) && */(sv4_reload)) ||
//			((!IsAlive(sv4)) && (sv1_reload) && /*(sv2_reload) && */(sv3_reload)) ||
//			((!IsAlive(sv1)) && /*(!IsAlive(sv2)) && */(sv3_reload) && (sv4_reload)) ||
//			((!IsAlive(sv1)) && (!IsAlive(sv3)) && /*(sv2_reload) && */(sv4_reload)) ||
//			((!IsAlive(sv1)) && (!IsAlive(sv4)) && /*(sv2_reload) && */(sv3_reload)) ||
//			(/*(!IsAlive(sv2)) && */(!IsAlive(sv3)) && (sv1_reload) && (sv4_reload)) ||
//			(/*(!IsAlive(sv2)) && */(!IsAlive(sv4)) && (sv1_reload) && (sv3_reload)) ||
//			((!IsAlive(sv3)) && (!IsAlive(sv4)) && (sv1_reload)/* && (sv2_reload) */) ||
//			((!IsAlive(sv1)) && /*(!IsAlive(sv2)) && */(!IsAlive(sv3)) && (sv4_reload)) ||
//			((!IsAlive(sv1)) && /*(!IsAlive(sv2)) && */(!IsAlive(sv4)) && (sv3_reload)) ||
//			((!IsAlive(sv1)) && (!IsAlive(sv3)) && (!IsAlive(sv4))/* && (sv2_reload) */) ||
//			(/*(!IsAlive(sv2)) && */(!IsAlive(sv3)) && (!IsAlive(sv4)) && (sv1_reload)))
//		{
/*(			if (!IsAlive(sv1))
			{
				Defend(sv1);
			}
			if (!IsAlive(sv2))
			{
				Defend(sv2);
			}
			if (!IsAlive(sv3))
			{
				Defend(sv3);
			}
			if (!IsAlive(sv4))
			{
				Defend(sv4);
			}
*/
//			make_bomber = false;
//			bomber_attack = false;
//			sv1_wait = false;
//			sv3_wait = false;
//			sv4_wait = false;
//			new_target = false;
//			bomber_retreat = false;
//			bomber_retreat_time = 99999.0f;
//			sv1_reload = false;
//			sv2_reload = false;
//			sv3_reload = false;
//			sv4_reload = false;
//			bomber_reload = true;
//		}
//	}



// end bomber code ////////////////////////////////////////////////////////////////////////////
// this is what happens if the silos get attacked

	if ((IsAlive(ccasilo1)) && (!silos_attacked) && (GameObjectHandle::GetObj(ccasilo1)->GetHealth() < 0.95f))
	{
		new_orders_time = Get_Time() + 2.0f;
		silos_attacked = true;
	}
	if ((IsAlive(ccasilo2)) && (!silos_attacked) && (GameObjectHandle::GetObj(ccasilo2)->GetHealth() < 0.95f))
	{
		new_orders_time = Get_Time() + 2.0f;
		silos_attacked = true;
	}
	if ((IsAlive(ccasilo3)) && (!silos_attacked) && (GameObjectHandle::GetObj(ccasilo3)->GetHealth() < 0.95f))
	{
		new_orders_time = Get_Time() + 2.0f;
		silos_attacked = true;
	}
	if ((IsAlive(ccasilo4)) && (!silos_attacked) && (GameObjectHandle::GetObj(ccasilo4)->GetHealth() < 0.95f))
	{
		new_orders_time = Get_Time() + 2.0f;
		silos_attacked = true;
	}

	if ((silos_attacked) && (new_orders_time < Get_Time()))
	{
		new_orders_time = Get_Time() + 120.0f;

		if (IsAlive(tank1))
		{
			Goto(tank1, "silo_spot");
		}
		if (IsAlive(tank2))
		{
			Goto(tank2, "silo_spot");
		}
		if (IsAlive(tank3))
		{
			Goto(tank3, "silo_spot");
		}
		if (IsAlive(tank4))
		{
			Goto(tank4, "silo_spot");
		}
		if (IsAlive(turret1))
		{
			Goto(turret1, "silo_spot");
		}
		if (IsAlive(turret2))
		{
			Goto(turret2, "silo_spot");
		}
		if (IsAlive(turret5))
		{
			Goto(turret5, "silo_spot");
		}
		if (IsAlive(turret6))
		{
			Goto(turret6, "silo_spot");
		}
		if (IsAlive(tank4))
		{
			Goto(tank4, "silo_spot");
		}
		if ((bomber_reload) || (bomber_attack))
		{
			if (IsAlive(sv1))
			{
				Goto(sv1, "silo_spot");
			}
//			if (IsAlive(sv2))
//			{
//				Goto(sv2, "silo_spot");
//			}
			if (IsAlive(sv3))
			{
				Goto(sv3, "silo_spot");
			}
			if (IsAlive(sv4))
			{
				Goto(sv4, "silo_spot");
			}
		}
	}

// this is what happens if the muf is under attack

	if ((IsAlive(ccamuf)) && (!muf_attacked) 
		&& (GameObjectHandle::GetObj(ccamuf)->GetHealth() < 0.90f) && (!muf_safe))
	{
		if (IsAlive(turret1))
		{
			Goto(turret1, ccamuf);
		}
		if (IsAlive(turret2))
		{
			Goto(turret2, ccamuf);
		}
		if (IsAlive(turret5))
		{
			Goto(turret5, ccamuf);
		}
		if (IsAlive(turret6))
		{
			Goto(turret6, ccamuf);
		}
		
		AddScrap(2, 40);
		safe_time_check = Get_Time() + 120.0f;
		SetAIP("misn13c.aip");
		muf_attacked = true;
	}

	if ((muf_attacked) && (IsAlive(turret1)) && (!turret1_muf) && GetDistance(turret1, ccamuf) < 60.0f)
	{
		Defend(turret1);
		turret1_muf = true;
	}
	if ((muf_attacked) && (IsAlive(turret2)) && (!turret2_muf) && GetDistance(turret2, ccamuf) < 60.0f)
	{
		Defend(turret2);
		turret2_muf = true;
	}
	if ((muf_attacked) && (IsAlive(turret5)) && (!turret5_muf) && GetDistance(turret5, ccamuf) < 60.0f)
	{
		Defend(turret5);
		turret5_muf = true;
	}
	if ((muf_attacked) && (IsAlive(turret6)) && (!turret6_muf) && GetDistance(turret6, ccamuf) < 60.0f)
	{
		Defend(turret6);
		turret6_muf = true;
	}

	// this checks to see of the coast is clear after the muf is attacked
	if ((!game_over) && (muf_attacked) && (safe_time_check < Get_Time()) && (!muf_safe))
	{
		safe_time_check < Get_Time() + 60.0f;
		check = CountUnitsNearObject(ccamuf, 400.0f, 1, NULL);		
		if (check < 2.0f)
		{
			muf_safe = true;
			muf_attacked = false;
		}

	}

// this checks to see if the player has broken through the main chokepoint

	if ((!choke_bridged) && (!IsAlive(turret3)) && (!IsAlive(turret4)))
	{
		choke_bridged = true;
	}

// this is the section that moves the first wave of soviet artillery units
	if ((artil_move_time < Get_Time()) && (!artil_move))
	{
		artil_move_time = Get_Time() + 10.0f;

		if (IsAlive(artil1))
		{
			Retreat(artil1, "artil_path1");
		}
		if (IsAlive(artil2))
		{	
			Retreat(artil2, "artil_path1");
		}
		if (IsAlive(artil3))
		{
			Retreat(artil3, "artil_path1");
		}
		if (IsAlive(artil4))
		{
			Retreat(artil4, "artil_path1");
		}
		if (IsAlive(escort_tank))
		{
			Retreat(escort_tank, "artil_path1");
		}

		artil_move = true;
	}

	if ((artil_move) && (artil_move_time < Get_Time()) && (!artil_move2))
	{
		artil_move_time = Get_Time() + 5.0f;
		if (GetDistance(artil4, split_geyser) < 20.0f)
		{
			if (IsAlive(artil1))
			{
				Goto(artil1, "artil_point1");
				SetIndependence(artil1, 1);
			}
			if (IsAlive(artil2))
			{
				Goto(artil2, "artil_point2");
				SetIndependence(artil2, 1);
			}
			if (IsAlive(artil3))
			{
				Goto(artil3, "artil_point3");
				SetIndependence(artil3, 1);
			}
			if (IsAlive(artil4))
			{
				Goto(artil4, "artil_point4");
				SetIndependence(artil4, 1);
			}
			if (IsAlive(escort_tank))
			{
				Follow(escort_tank, artil1);
			}
			
			artil_set_time = Get_Time() + 120.0;
			artil_move2 = true;
		}
	}

	if ((artil_set_time < Get_Time()) && (!artil_set))
	{
		if (IsAlive(artil1))
		{
			if (IsAlive(avscav1))
			{
				Attack(artil1, avscav1);
			}
			else if (IsAlive(avscav2))
			{
				Attack(artil1, avscav2);
			}
			else if (IsAlive(avscav3))
			{
				Attack(artil1, avscav3);
			}
		}
		if (IsAlive(artil2))
		{	
			if (IsAlive(avscav3))
			{
				Attack(artil2, avscav3);
			}
			else if (IsAlive(avscav2))
			{
				Attack(artil2, avscav2);
			}
			else if (IsAlive(avscav1))
			{
				Attack(artil2, avscav1);
			}
		}

		artil_set = true;
	}

	if ((!IsAlive(artil1)) && (!IsAlive(artil2)) && (!IsAlive(artil3)) && (!IsAlive(artil4)))
	{
		artil_lost = true;
	}

	if ((artil_move2) && (!artil_message))
	{
		if (IsAlive(nsdfrecycle))
		{
			shot_by = GameObjectHandle::GetObj(nsdfrecycle)->GetWhoTheHellShotMe();

			if (shot_by != 0)
			{
				if ((artil1 == shot_by) ||
					(artil2 == shot_by) ||
					(artil3 == shot_by) ||
					(artil4 == shot_by))
				{
					AudioMessage("misn1302.wav"); 
					artil_message = true;
				}
			}
		}

		if ((IsAlive(nsdfmuf)) && (!artil_message))
		{
			shot_by = GameObjectHandle::GetObj(nsdfmuf)->GetWhoTheHellShotMe();

			if (shot_by != 0)
			{
				if ((artil1 == shot_by) ||
					(artil2 == shot_by) ||
					(artil3 == shot_by) ||
					(artil4 == shot_by))
				{
					AudioMessage("misn1302.wav"); 
					artil_message = true;
				}
			}
		}

		if ((IsAlive(avscav1)) && (!artil_message))
		{
			shot_by = GameObjectHandle::GetObj(avscav1)->GetWhoTheHellShotMe();

			if (shot_by != 0)
			{
				if ((artil1 == shot_by) ||
					(artil2 == shot_by) ||
					(artil3 == shot_by) ||
					(artil4 == shot_by))
				{
					AudioMessage("misn1302.wav"); 
					artil_message = true;
				}
			}
		}

		if ((IsAlive(avscav2)) && (!artil_message))
		{
			shot_by = GameObjectHandle::GetObj(avscav2)->GetWhoTheHellShotMe();

			if (shot_by != 0)
			{
				if ((artil1 == shot_by) ||
					(artil2 == shot_by) ||
					(artil3 == shot_by) ||
					(artil4 == shot_by))
				{
					AudioMessage("misn1302.wav"); 
					artil_message = true;
				}
			}
		}

		if ((IsAlive(avscav3)) && (!artil_message))
		{
			shot_by = GameObjectHandle::GetObj(avscav3)->GetWhoTheHellShotMe();

			if (shot_by != 0)
			{
				if ((artil1 == shot_by) ||
					(artil2 == shot_by) ||
					(artil3 == shot_by) ||
					(artil4 == shot_by))
				{
					AudioMessage("misn1302.wav"); 
					artil_message = true;
				}
			}
		}
	}

// this wakes up the scavengers

	if ((scrap_check < Get_Time()) && (!scav_swap))
	{
		scrap_check = Get_Time() + 60.0f;
		scrap = GetScrap(2);

		if (scrap < 40)
		{
			if (svscav1 != NULL)
			{
				svscav5 = BuildObject("svscav", 2, svscav1);
				RemoveObject(svscav1);
				Goto(svscav5, center_geyser);
			}
			if (svscav2 != NULL)
			{
				svscav6 = BuildObject("svscav", 2, svscav2);
				RemoveObject(svscav2);
				Goto(svscav6, center_geyser);
			}
			if (svscav3 != NULL)
			{
				svscav7 = BuildObject("svscav", 2, svscav3);
				RemoveObject(svscav3);
				Goto(svscav7, center_geyser);
			}
			if (svscav4 != NULL)
			{
				svscav8 = BuildObject("svscav", 2, svscav4);
				RemoveObject(svscav4);
				Goto(svscav8, center_geyser);
			}
			scav_swap = true;
		}
	}

// win/loose conditions

	if ((!IsAlive(nsdfrecycle)) && (!game_over))
	{
		AudioMessage("misn1304.wav");
		FailMission(Get_Time() + 15.0f, "misn13f1.des");
		game_over = true;
	}

	if ((!IsAlive(ccamuf)) && (!game_over))
	{
		AudioMessage("misn1303.wav");
		SucceedMission(Get_Time() + 15.0f, "misn13w1.des");
		game_over = true;
	}



// end of scrap reduction

// END OF SCRIPT

}																	

IMPLEMENT_RTIME(Misn13Mission)

Misn13Mission::Misn13Mission(void)
{
}

Misn13Mission::~Misn13Mission()
{
}

void Misn13Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

bool Misn13Mission::Load(file fp)
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

bool Misn13Mission::PostLoad(void)
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

bool Misn13Mission::Save(file fp)
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

void Misn13Mission::Update(void)
{
	AiMission::Update();
	Execute();
}
