#include "GameCommon.h"
#include "..\fun3d\Factory.h"
#include "..\fun3d\AiMission.h"
#include "..\fun3d\PowerUp.h"
#include "..\fun3d\ScriptUtils.h"


/*
Misn08Mission Event
*/

class Misn08Mission : public AiMission {
	DECLARE_RTIME(Misn08Mission)
public:
	Misn08Mission(void);
	~Misn08Mission();

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
				gech_found, gech_found1, gech_found2, 
				base_dead, 
				player_dead,
				unit_spawn,
				gech_at_nav, gech_at_nav2, gech_at_nav3,
				player_warned_ofgech,
				colorado_under_attack,
				colorado_destroyed,
				followup_message,
				colorado_message2,
				colorado_message3,
				colorado_message4,
				second_gech_warning,
				run_into_other_gech,
				too_close_message,
				bad_news,
				base_exposed,
				bump_into_gech,
				ccarecycle_spawned,
				gech_started,
				gech3_move,
				first_wave, second_wave, next_wave,
				gech1_at_base, gech2_at_base, gech3_at_base,
				gech1_blossom, gech2_blossom, gech3_blossom,
				fresh_meat, fighter_message,
				apc_attack, base_set, game_over, cerb_found, relic_message,
				kill_colorado, gen_message,
				b_last;
		};
		bool b_array[44];
	};

	// floats
	union {
		struct {
			float
				unit_spawn_time,
				followup_message_time,
				colorado_message2_time, colorado_message3_time, colorado_message4_time,
				bad_news_time,
				gech_warning_message,
				remove_nav5_time,
				gech_spawn_time,
				gech_check, gech_check2,
				stumble1_check, stumble2_check, trigger_check, no_stumble_check,
				time_waist,
				start_gech_time,
				gech_check_time,
				first_wave_time,
				second_wave_time,
				next_wave_time,
				gech1_there_time, gech2_there_time, gech3_there_time,
				new_aip_time,
				fresh_meat_time,
				fighter_message_time, player_nosey_time,
				pull_out_message, base_check, cerb_check,
				next_second, next_second2,
				f_last;
		};
		float f_array[33];
	};

	// handles
	union {
		struct {
			Handle
				user, death_scrap, death_scrap2, death_scrap3,
				nav1, nav2, nav3, nav4, nav5,
				ccagech1, ccagech2, ccagech3,
				colorado, drop,
				ccarecycle, ccamuf, ccaarmor,
				gech_trigger2, gech_trigger3,
				nsdfrecycle, nsdfmuf,
				attack_geys,
				ccarecycle_geyser,
				stop_geyser1, stop_geyser2, stop_geyser3,
				svpatrol1_1, svpatrol1_2, svpatrol1_3,
				svpatrol2_1, svpatrol2_2, svpatrol2_3,
				cannon_fodder1, cannon_fodder2, cannon_fodder3,
				ccaapc, guntower1, guntower2, relic1, relic2, main_relic,
				h_last;
		};
		Handle h_array[41];
	};

	// integers
	union {
		struct {
			int
				units1, units2,
				i_last;
		};
		int i_array[2];
	};
};

void Misn08Mission::Setup(void)
{
/*
Here's where you set the values at the start.  
*/
	units1 = 0.0f;
	units2 = 0.0f;
	
	start_done = false;
	gech_found = false;
	gech_found1 = false;
	gech_found2 = false;
	base_dead = false;
	player_dead = false;
	unit_spawn = false;
	gech_at_nav = false;
	gech_at_nav2 = false;
	gech_at_nav3 = false;
	followup_message = false;
	player_warned_ofgech = false;
	colorado_under_attack = false;
	colorado_destroyed = false;
	colorado_message2 = false;
	colorado_message3 = false;
	colorado_message4 = false;
	second_gech_warning = false;
	bad_news = false;
	run_into_other_gech = false;
	too_close_message =false;
	base_exposed = false;
	bump_into_gech = false;
	ccarecycle_spawned = false;
	gech_started = false;
	gech3_move = false;
	first_wave = false;
	second_wave = false;
	next_wave = false;
	gech1_at_base = false;
	gech2_at_base = false;
	gech3_at_base = false;
	fresh_meat = false;
	fighter_message = false;
	gech1_blossom = false;
	gech2_blossom = false;
	gech3_blossom = false;
	apc_attack = false;
	game_over = false;
	base_set = false;
	cerb_found = false;
	relic_message = false;
	kill_colorado = false;
	gen_message = false;


	followup_message_time = 99999.0f;
	gech_warning_message = 99999.0f;
	colorado_message2_time = 99999.0f;
	colorado_message3_time = 99999.0f;
	colorado_message4_time = 99999.0f;
	bad_news_time = 99999.0f;
	remove_nav5_time = 99999.0f;
	gech_spawn_time = 99999.0f;
	gech_check = 99999.0f;
	gech_check2 = 99999.0f;
	stumble2_check = 99999.0f;
	stumble1_check = 99999.0f;
	trigger_check = 99999.0f;
	no_stumble_check = 99999.0f;
	time_waist = 99999.0f;
	start_gech_time = 99999.0f;
	gech_check_time = 10.0f;
	first_wave_time = 99999.0f;
	second_wave_time = 99999.0f;
	next_wave_time = 99999.0f;
	gech1_there_time = 99999.0f;
	gech2_there_time = 99999.0f;
	gech3_there_time = 99999.0f;
	new_aip_time = 99999.0f;
	fresh_meat_time = 99999.0f;
	fighter_message_time = 200.0f;
	player_nosey_time = 45.0f;
	pull_out_message = 99999.0f;
	base_check = 99999.0f;
	cerb_check = 30.0f;
	next_second = 99999.0f;
	next_second2 = 99999.0f;
	
	death_scrap = GetHandle("death_scrap");
	death_scrap2 = GetHandle("death_scrap2");
	death_scrap3 = GetHandle("death_scrap3");
	nsdfrecycle = GetHandle("avrecycle");
	ccarecycle = GetHandle("svrecycle");
	ccamuf = GetHandle("svmuf");
	ccagech1 = GetHandle("sovgech1");
	ccagech2 = GetHandle("sovgech2");
	nav1 = GetHandle("cam1");
	nav4 = GetHandle("cam2");
	nav5 = GetHandle("cam5");
	gech_trigger2 = GetHandle("giez_spawn2");
	gech_trigger3 = GetHandle("giez_spawn3");
	colorado = GetHandle("colorado");
//	drop = GetHandle("dropoff57_dropoff");
	attack_geys = GetHandle("attack_geyser");
	ccarecycle_geyser = GetHandle("ccarecycle_geyser");
	stop_geyser1 = GetHandle("stop_geyser1");
	stop_geyser2 = GetHandle("stop_geyser2");
	stop_geyser3 = GetHandle("stop_geyser3");
	svpatrol1_1 = GetHandle("svpatrol1_1");
	svpatrol1_2 = GetHandle("svpatrol1_2");
	svpatrol1_3 = GetHandle("svpatrol1_3");
	svpatrol2_1 = GetHandle("svpatrol2_1");
	svpatrol2_2 = GetHandle("svpatrol2_2");
	svpatrol2_3 = GetHandle("svpatrol2_3");
	relic1 = GetHandle("hbblde1_i76building");
	relic2 = GetHandle("hbbldf1_i76building");
	main_relic = GetHandle("hbcerb1_i76building");
	nsdfmuf = NULL;
	ccaapc = NULL;
	guntower1 = NULL;
	guntower2 = NULL;
	ccagech3 = 0;
}

void Misn08Mission::AddObject(Handle h)
{
	if ((nsdfmuf == NULL) && (IsOdf(h,"avmu8")))
	{
		nsdfmuf = h;
	}
	else
	{
		if ((ccaapc == NULL) && (IsOdf(h,"svapc")))
		{
			nsdfmuf = h;
		}
		else
		{
			if ((guntower1 == NULL) && (IsOdf(h,"abtowe")))
			{
				guntower1 = h;
			}
			else
			{
				if ((guntower2 == NULL) && (IsOdf(h,"abtowe")))
				{
					guntower1 = h;
				}
			}
		}
	}
}

void Misn08Mission::Execute(void)
{
/*
Here is where you put what happens every frame.  
*/
	user = GetPlayerHandle(); //assigns the player a handle every frame

	if (!start_done)
	{
		AudioMessage("misn0800.wav"); //starts opeing V.O.
		ClearObjectives();
		AddObjective("misn0800.otf", WHITE);
		AddObjective("misn0801.otf", WHITE);
//		SetPilot(1, 30);
		SetScrap(1,30);
		Defend(ccagech1);
		Defend(ccagech2);
		start_gech_time = Get_Time() + 329.0f; // starts the gechs towards the base
		gech_spawn_time = Get_Time() + 280.0f; // starts attack on colorado
		trigger_check = Get_Time() + 285.0f;
		fresh_meat_time = 100.0f; // build more units to send after player
		gech_check = Get_Time() + 61.0f; // searches to see if the player encounters a gech
		first_wave_time = Get_Time() + 20.0f; // starts the first wave of fighters
		SetWeaponMask(ccagech1, 1);
		SetWeaponMask(ccagech2, 1);
		if (nav1!=NULL) GameObjectHandle::GetObj(nav1)->SetName("Drop Zone");
		if (nav5!=NULL) GameObjectHandle::GetObj(nav5)->SetName("Colorado Base");
		if (nav4!=NULL) GameObjectHandle::GetObj(nav4)->SetName("CCA Main Base");
		base_check = Get_Time() + 5.0f;
		start_done = true;
	}

	if ((start_done) && (start_gech_time < Get_Time()) && (!gech_started)) //sets gechs into motion
	{
		Goto(ccagech1, "gech_path1"); 
		Goto(ccagech2, "gech_path2");
		gech_started = true;
	}
	// this sends the first soviets into the user's base
	if ((first_wave_time < Get_Time()) && (!first_wave))
	{
		Goto(svpatrol2_2, nsdfrecycle);
		Goto(svpatrol2_3, nsdfrecycle);
		first_wave = true;
	}

	if ((fresh_meat_time < Get_Time()) && (!colorado_under_attack) && (!fresh_meat))
	{
		cannon_fodder1 = BuildObject("svfigh", 2, ccarecycle);
		cannon_fodder2 = BuildObject("svfigh", 2, ccarecycle);
		cannon_fodder3 = BuildObject("svfigh", 2, ccarecycle);
		Goto(cannon_fodder1, "gech_path2");
		Goto(cannon_fodder2, "gech_path2");
		Goto(cannon_fodder3, "gech_path2");
		fresh_meat = true;
	}

	if ((fighter_message_time < Get_Time()) && (!colorado_under_attack) && (!fighter_message))
	{
		AudioMessage("misn0817.wav"); // colorado: we're experiencing a lot of fighters - they know we're here - wonder what the main forces is waiting for
		fighter_message = true;
	}


// colorado gets attacked by gech //////////////////////////////////////////////////////////////////////////

	if ((gech_spawn_time < Get_Time()) && (!colorado_under_attack))//gech attacks colorado
	{
		gech_spawn_time = Get_Time() + 10.0f;

		if (GetDistance(user, nav5) > 400.0f)
		{
			svpatrol2_2 = BuildObject("svfigh", 2, ccarecycle);
			svpatrol2_2 = BuildObject("svltnk", 2, ccarecycle);
			ccagech3 = BuildObject("svwalk", 2, "gech_spawn");
			SetWeaponMask(ccagech3, 1);
			Attack(ccagech3, colorado, 1);
			AudioMessage("misn0801.wav");// player gets message that colorado is encountering hostiles "standby"
			colorado_message2_time = Get_Time() + 10.0f;

			if (IsAlive(svpatrol2_1))
			{
				Goto(svpatrol2_1, nav1);
			}
			if (IsAlive(svpatrol2_2))
			{
				Goto(svpatrol2_2, nav1);
			}
			if (IsAlive(svpatrol2_3))
			{
				Goto(svpatrol2_3, nav1);
			}

			colorado_under_attack = true;
		}
	}
	
	// this is what happens if the player tries to get to the colorado before the attack - it speeds things up
	if ((player_nosey_time < GetTime()) && (!colorado_under_attack))
	{
		player_nosey_time = GetTime() + 32.0f;

		if (GetDistance(user, nav5) < 700.0f)
		{
			gech_spawn_time = Get_Time() + 10.0f;

			if (IsAlive(svpatrol1_1))
			{
				Attack(svpatrol1_1, user);
			}
			if (IsAlive(svpatrol1_2))
			{
				Attack(svpatrol1_2, user);
			}
			if (IsAlive(svpatrol1_3))
			{
				Attack(svpatrol1_3, user);
			}
			if (IsAlive(svpatrol2_1))
			{
				Attack(svpatrol2_1, nsdfrecycle);
			}
			if (IsAlive(svpatrol2_2))
			{
				Attack(svpatrol2_2, nsdfrecycle);
			}
			if (IsAlive(svpatrol2_3))
			{
				Attack(svpatrol2_3, nsdfrecycle);
			}
		}
	}

	if ((colorado_under_attack) && (colorado_message2_time < Get_Time()) && (!colorado_message2))
	{

		AudioMessage("misn0803.wav");//second message from colorado
		colorado_message3_time = Get_Time() + 7.0f;
		colorado_message2 = true;
	}	

	if ((colorado_message2) && (colorado_message3_time < Get_Time()) && (!colorado_message3))
	{

		AudioMessage("misn0802.wav");//third message from colorado
		AudioMessage("misn0804.wav");//final message from colorado
		colorado_message4_time = Get_Time() + 10.0f;
		colorado_message3 = true;
	}

	if ((colorado_message4_time < Get_Time()) && (!kill_colorado))
	{
		kill_colorado = true;
	}

	if ((IsAlive(colorado)) && (!kill_colorado))
	{
		if (GetTime()>next_second)
		{
			GameObjectHandle::GetObj(colorado)->AddHealth(500.0f);
			next_second = GetTime() + 1.0f;
		}
	}

	if ((colorado_message3) && (kill_colorado) && (!colorado_message4))
	{
		if (IsAlive(colorado))
		{
			Damage(colorado, 20000);
		}
		remove_nav5_time = Get_Time() + 15.0f;
		colorado_message4 = true;
	}

	if ((colorado_message4) && (remove_nav5_time < Get_Time()) && (!colorado_destroyed))
	{
//		RemoveObject (colorado);
		RemoveObject (nav5);
//		RemoveObject (drop);
		bad_news_time = Get_Time() + 5.0f;
		colorado_destroyed = true;
	}

	if ((colorado_destroyed) && (!bad_news) && (bad_news_time < Get_Time()))
	{
		AudioMessage("misn0805.wav");//Corbett give player news of colorado fate
		bad_news_time = Get_Time() + 30.0f;
		bad_news = true;
	}

	if ((bad_news) && (bad_news_time < Get_Time()) && (!gen_message))
	{
		AudioMessage("misn0810.wav");//Gen Collins give player news of colorado fate
		gen_message = true;
	}

// end soviet attack on colorado ///////////////////////////////////////////////////////////////////////////////


// this is going to give the soviets a recycler and start them attacking

	if ((bad_news) && (!ccarecycle_spawned))
	{
		SetAIP("misn08.aip");		
		SetScrap(2, 40);
		SetPilot(2, 40);
		new_aip_time = Get_Time() + 420.0f;
		if (IsAlive(ccagech3))
		{
			Goto(ccagech3, "gech_path2");
		}

		if (IsAlive(svpatrol1_1))
		{
			Goto(svpatrol1_1, "cam3_spawn");
		}
		if (IsAlive(svpatrol1_2))
		{
			Goto(svpatrol1_2, "cam3_spawn");
		}
		if (IsAlive(svpatrol1_3))
		{
			Goto(svpatrol1_3, "cam3_spawn");
		}

		ccarecycle_spawned = true;
	}

	// this is sending the third gech down the gech path when it gets to a certain point
/*	if ((ccarecycle_spawned) && (!gech3_move) && (gech_check_time < Get_Time()))
	{
		if (GetDistance(ccagech3, stop_geyser2) < 30.0f)
		{
			Goto(ccagech3, "gech_path2");
			gech3_there_time = Get_Time() + 97.0f;
			gech3_move = true;
		}
	}

*/	

// this is what happens when the player encounters the gech before it reaches the nav point ////////////////////

	if ((gech_check < Get_Time()) && (!gech_found) && (!gech_at_nav))
	{
		gech_check = Get_Time() + 6.0f;

		if ((GetDistance(user,ccagech1) < 400.0f) && (!gech_found1) && (!gech_found) && (!gech_at_nav)) //if player reaches gech before gech reaches nav
		{
			AudioMessage("misn0806.wav"); // "we're picking up something big on your radar, you may want to check it out"
			followup_message_time = Get_Time() + 20.0f; // setting up follow up message about cca gech
			stumble2_check = Get_Time() + 10.0f;
			no_stumble_check = Get_Time() + 13.0f;
			gech1_there_time = 100.0f;
			gech2_there_time = 105.0f;
			gech_found1 = true;
			gech_found = true;
		}

		if ((GetDistance(user,ccagech2) < 400.0f) && (!gech_found) && (!gech_found2) && (!gech_at_nav)) //if player reaches gech before gech reaches nav
		{
			AudioMessage("misn0806.wav"); // "we're picking up something big on your radar, you may want to check it out"
			followup_message_time = Get_Time() + 5.0f; // setting up follow up message about cca gech
			stumble2_check = Get_Time() + 60.0f;
			no_stumble_check = Get_Time() + 13.0f;
			gech1_there_time = 100.0f;
			gech2_there_time = 105.0f;
			gech_found2 = true;
			gech_found = true;
		}
	}

	if ((gech_found) && (followup_message_time < Get_Time()) && (!followup_message))
	{
		AudioMessage("misn0807.wav"); // "what the hell is that thing - approach with caution!"
		followup_message = true;
	}


	if ((base_check < Get_Time()) && (!base_set))
	{
		base_check = Get_Time() + 2.0f;

		if (IsAlive(nsdfmuf))
		{
			bool test=((Factory *) GameObjectHandle::GetObj(nsdfmuf))->IsDeployed();

			if (test)
			{
				ClearObjectives();
				AddObjective("misn0800.otf", GREEN);
				AddObjective("misn0801.otf", WHITE);
				base_set = true;
			}
		}
	}


	
	// this is what happens when the player goes and sees the gech after the first nav is dropped 

	if ((gech_found) && (stumble2_check < Get_Time()) && (!second_gech_warning) && (!run_into_other_gech))
	{
		stumble2_check = Get_Time() + 21.0f;
		
		if ((gech_found1) && (GetDistance(user,ccagech2) < 100.0f) && (!run_into_other_gech))
		{
			AudioMessage("misn0813.wav"); //Oh no! Looks like you've found another one!
			run_into_other_gech = true;
		}

		if ((gech_found2) && (GetDistance(user,ccagech1) < 100.0f) && (!run_into_other_gech))
		{
			AudioMessage("misn0813.wav"); //Oh no! Looks like you've found another one!
			run_into_other_gech = true;
		}
	}

	// this is when the player runs into one gech but the other gech gets half-way to base before being discovered

	if ((gech_found) && (no_stumble_check < Get_Time()) && (!run_into_other_gech) && (!second_gech_warning))
	{
		no_stumble_check = Get_Time() + 9.0f;

		if ((gech_found1) && (GetDistance(gech_trigger2, ccagech2) < 100.0f) && (!second_gech_warning))
		{
			AudioMessage("misn0815.wav"); //V.O. looks like we've got another one coming out of the west
			nav2 = BuildObject ("apcamr", 1, "cam2_spawn"); // builds camera near gech
			if (nav2!=NULL) GameObjectHandle::GetObj(nav2)->SetName("Nav Alpha 1");
			second_gech_warning = true;
		}

		if ((gech_found2) && (GetDistance(gech_trigger3,ccagech1) < 100.0f) && (!second_gech_warning))
		{
			AudioMessage("misn0814.wav"); //V.O. warns player of second gech
			nav3 = BuildObject ("apcamr", 1, "cam3_spawn"); // builds camera near gech
			if (nav3!=NULL) GameObjectHandle::GetObj(nav3)->SetName("Nav Alpha 2");
			second_gech_warning = true;
		}
	}


// the following occurs when the approaching gechs get half-way to the player's base

	if ((colorado_under_attack) && (trigger_check < Get_Time()) && (!gech_at_nav) && (!gech_found))
	{
		trigger_check = Get_Time() + 19.0f;
		
		if ((!gech_found) && (GetDistance(gech_trigger2, ccagech2) < 100.0f) && (!gech_at_nav)) //if gech reaches nav before player reaches gech
		{
			AudioMessage("misn0809.wav"); // "We've detected something strange on approach from the east - standby"
			gech_warning_message = Get_Time() + 20.0f;
			gech1_there_time = 100.0f;
			gech2_there_time = 105.0f;
			gech_at_nav = true;
			gech_at_nav2 = true;
		}	

		if ((!gech_found) && (GetDistance(gech_trigger3,ccagech1) < 100.0f) && (!gech_at_nav)) //if gech reaches nav before player reaches gech	
		{
			AudioMessage("misn0808.wav"); // "We've detected something strange on approach from the west - standby"
			gech_warning_message = Get_Time() + 20.0f;
			gech1_there_time = 100.0f;
			gech2_there_time = 105.0f;
			gech_at_nav = true;
			gech_at_nav3 = true;
		}
	}

	if ((gech_at_nav2) && (gech_warning_message < Get_Time()) && (!player_warned_ofgech)) //if player ignores gech_at_nav message
	{
		AudioMessage("misn0814.wav"); // Check it out - we're dropping a nav camera there now
		nav2 = BuildObject ("apcamr", 1, "cam2_spawn"); // builds camera near gech
		if (nav2!=NULL) GameObjectHandle::GetObj(nav2)->SetName("Nav Alpha 1");
		time_waist = Get_Time() + 14.0f;
		stumble1_check = Get_Time() + 100.0f;
		player_warned_ofgech = true;
	}

	if ((gech_at_nav3) && (gech_warning_message < Get_Time()) && (!player_warned_ofgech)) //if player ignores gech_at_nav message
	{
		AudioMessage("misn0815.wav"); // Check it out - we're dropping a nav camera there now
		nav3 = BuildObject ("apcamr", 1, "cam3_spawn"); // builds camera near gech
		if (nav3!=NULL) GameObjectHandle::GetObj(nav3)->SetName("Nav Alpha 2");
		time_waist = Get_Time() + 14.0f;
		stumble1_check = Get_Time() + 100.0f;
		player_warned_ofgech = true;
	}

	// this is the player getting warned of the second gech if he hasn't gone to see the first one yet //////////////////

	if ((player_warned_ofgech) && (time_waist < Get_Time()) && (!second_gech_warning) && (!bump_into_gech))
	{
		time_waist = Get_Time() + 14.0f;

		if ((gech_at_nav2) && (GetDistance(gech_trigger3,ccagech1) < 75.0f) && (!second_gech_warning)) //second gech found
		{
			AudioMessage("misn0812.wav");  //looks like we've got another one coming out of the east
			nav3 = BuildObject ("apcamr", 1, "cam3_spawn"); // builds camera near gech
			if (nav3!=NULL) GameObjectHandle::GetObj(nav3)->SetName("Nav Alpha 2");
			second_gech_warning = true;
		}

		if ((gech_at_nav3) && (GetDistance(gech_trigger2, ccagech2) < 75.0f) && (!second_gech_warning)) //second gech found
		{
			AudioMessage("misn0811.wav"); //looks like we've got another one coming out of the west
			nav2 = BuildObject ("apcamr", 1, "cam2_spawn"); // builds camera near gech
			if (nav2!=NULL) GameObjectHandle::GetObj(nav2)->SetName("Nav Alpha 1");
			second_gech_warning = true;
		}
	}

	// this is what happens when the player goes and sees the gech after the first nav is dropped 

	if ((player_warned_ofgech) && (stumble1_check < Get_Time()) && (!second_gech_warning) && (!bump_into_gech))
	{
		stumble1_check = Get_Time() + 23.0f;
		
		if ((gech_at_nav2) && (GetDistance(user,ccagech1) < 100.0f) && (!bump_into_gech))
		{
			AudioMessage("misn0813.wav"); //Oh no! Looks like you've found another one!
			bump_into_gech = true;
		}

		if ((gech_at_nav3) && (GetDistance(user,ccagech2) < 100.0f) && (!bump_into_gech))
		{
			AudioMessage("misn0813.wav"); //Oh no! Looks like you've found another one!
			bump_into_gech = true;
		}
	}


// this makes the gechs attack the player's base when they get close enough

	if ((gech_found) || (gech_at_nav))
	{
		if ((gech1_there_time < Get_Time()) && (!gech1_at_base))
		{
			gech1_there_time = Get_Time() + 30.0f;
			
			if ((IsAlive(ccagech1)) && (GetDistance(ccagech1, stop_geyser3) < 100.0f))
			{
				if (IsAlive(nsdfrecycle))
				{
					Attack(ccagech1, nsdfrecycle);
					if (gech1_blossom)
					{
						SetWeaponMask(ccagech1, 5);
					}
					gech1_at_base = true;
				}
				else
				{
					if (IsAlive(nsdfmuf))
					{
						Attack(ccagech1, nsdfmuf);
						if (gech1_blossom)
						{
							SetWeaponMask(ccagech1, 5);
						}
						gech1_at_base = true;
					}
				}
			}
		}

		if ((gech2_there_time < Get_Time()) && (!gech2_at_base))
		{
			gech2_there_time = Get_Time() + 30.0f;
			
			if ((IsAlive(ccagech2)) && (GetDistance(ccagech2, stop_geyser3) < 100.0f))
			{
				if (IsAlive(nsdfrecycle))
				{
					Attack(ccagech2, nsdfrecycle);
					if (gech2_blossom)
					{
						SetWeaponMask(ccagech2, 5);
					}
					gech2_at_base = true;
				}
				else
				{
					if (IsAlive(nsdfmuf))
					{
						Attack(ccagech2, nsdfmuf);
						if (gech2_blossom)
						{
							SetWeaponMask(ccagech2, 5);
						}
						gech2_at_base = true;
					}
				}
			}
		}

		if ((gech3_there_time < Get_Time()) && (!gech3_at_base))
		{
			gech3_there_time = Get_Time() + 30.0f;
			
			if ((IsAlive(ccagech3)) && (GetDistance(ccagech3, stop_geyser3) < 100.0f))
			{
				if (IsAlive(nsdfrecycle))
				{
					Attack(ccagech3, nsdfrecycle);
					if (gech3_blossom)
					{
						SetWeaponMask(ccagech3, 5);
					}
					gech3_at_base = true;
				}
				else
				{
					if (IsAlive(nsdfmuf))
					{
						Attack(ccagech3, nsdfmuf);
						if (gech3_blossom)
						{
							SetWeaponMask(ccagech3, 5);
						}
						gech3_at_base = true;
					}
				}
			}
		}

	}

// now I'm loading the new attack aips if the correct amount of time has passed

	if (new_aip_time < Get_Time())
	{
		new_aip_time = Get_Time() + 420.0f;
		
		units1 = CountUnitsNearObject(stop_geyser2, 5000.0f, 1, "avfigh");
		units2 = CountUnitsNearObject(stop_geyser2, 5000.0f, 1, "avtank");

		if(units1 > units2)
		{
			SetAIP("misn08b.aip");
		}
		else
		{
			SetAIP("misn08a.aip");
		}
	}

// this is apc code

	if ((IsAlive(ccaapc)) && (!apc_attack))
	{
		if (IsAlive(guntower1))
		{
			Attack(ccaapc, guntower1);
		}
		else
		{
			if (IsAlive(guntower2))
			{
				Attack(ccaapc, guntower2);
			}
			else
			{
				if (IsAlive(nsdfmuf))
				{
					Attack(ccaapc, nsdfmuf);
				}
				else
				{
					if (IsAlive(nsdfrecycle))
					{
						Attack(ccaapc, nsdfrecycle);
					}
				}
			}
		}

		apc_attack = true;
	}

	if ((apc_attack) && (!IsAlive(ccaapc)))
	{
		apc_attack = false;
	}


//This is another radar comment when the player gets extrememly close to the gech
/*	if ((gech_found) && (!too_close_message) || (gech_at_nav) && (!too_close_message))
	{
		if ((GetDistance(user, ccagech1) < 75.0f) && (!too_close_message))
		{
			AudioMessage("misn0816.wav"); // pull out!! what the hell is that!
			too_close_message = true;
		}

		if ((GetDistance(user, ccagech2) < 75.0f) && (!too_close_message))
		{
			AudioMessage("misn0816.wav"); // pull out!! what the hell is that!
			too_close_message = true;
		}
	}
*/

	if ((pull_out_message < Get_Time()) && (!too_close_message))
	{
		AudioMessage("misn0816.wav"); // pull out!! what the hell is that!
		too_close_message = true;
	}


// this will make the gechs use the popper

	if ((IsAlive(ccagech1)) && (!gech1_blossom) && (GameObjectHandle::GetObj(ccagech1)->GetHealth() < 0.25f))
	{
		SetWeaponMask(ccagech1, 4);
		pull_out_message = Get_Time() + 6.0f;
		gech1_blossom = true;
	}
	
	if ((IsAlive(ccagech2)) && (!gech2_blossom) && (GameObjectHandle::GetObj(ccagech2)->GetHealth() < 0.25f))
	{
		SetWeaponMask(ccagech2, 4);
		pull_out_message = Get_Time() + 6.0f;
		gech2_blossom = true;
	}
	
	if ((IsAlive(ccagech3)) && (!gech3_blossom) && (GameObjectHandle::GetObj(ccagech3)->GetHealth() < 0.25f))
	{
		SetWeaponMask(ccagech3, 4);
		pull_out_message = Get_Time() + 6.0f;
		gech3_blossom = true;
	}

// this is the relic code

	if ((!cerb_found) && (!relic_message) && ((IsInfo("hbblde") == true) || (IsInfo("hbbldf") == true)))
	{
		if (base_dead)
		{
			AudioMessage("misn0821.wav"); // that's not it, the ruins will be much larger
			relic_message = true;
		}
		else
		{
			AudioMessage("misn0822.wav"); // this area is crawling with relics recon as many as possible
			relic_message = true;
		}
	}

	if ((!cerb_found) && (cerb_check < Get_Time()))
	{
		cerb_check = Get_Time() + 3.0f;

		if (GetDistance(user, main_relic) < 70.0f)
		{
			if (base_dead)
			{
				AudioMessage("misn0818.wav"); // well done
				AudioMessage("misn0826.wav");
				SucceedMission(Get_Time() + 30.0f, "misn08w1.des"); //well done
				cerb_found = true;
			}
			else
			{
				AudioMessage("misn0819.wav"); // this must be how they built gechs - find base
				cerb_found = true;
			}
		}
	}

	if (IsAlive(main_relic))
	{
		if (GetTime()>next_second2)
		{
			GameObjectHandle::GetObj(main_relic)->AddHealth(500.0f);
			next_second2 = GetTime() + 1.0f;
		}
	}


// win/loose conditions /////////////////////////////
	
	if ((!IsAlive(ccarecycle)) && (!IsAlive(ccamuf)) && (!base_dead))
	{
		if (cerb_found)
		{
			AudioMessage("misn0818.wav");
			AudioMessage("misn0826.wav");
			SucceedMission(Get_Time() + 30.0f, "misn08w1.des"); //well done
			base_dead = true;
		}
		else
		{
			ClearObjectives();
			AddObjective("misn0801.otf", GREEN);
			AddObjective("misn0802.otf", WHITE);
			AudioMessage("misn0820.wav"); // find cerbeus
			SetObjectiveOn(main_relic);
			SetObjectiveName(main_relic, "Relic Site");
			base_dead = true;
		}
	}

	if ((!IsAlive(nsdfrecycle)) && (!game_over))
	{
		AudioMessage("misn0421.wav");
		FailMission(Get_Time() + 15.0f, "misn08f1.des"); //lost recycler
		game_over = true;
	}

}	

IMPLEMENT_RTIME(Misn08Mission)

Misn08Mission::Misn08Mission(void)
{
}

Misn08Mission::~Misn08Mission()
{
}

void Misn08Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

bool Misn08Mission::Load(file fp)
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

bool Misn08Mission::PostLoad(void)
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

bool Misn08Mission::Save(file fp)
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

void Misn08Mission::Update(void)
{
	AiMission::Update();
	Execute();
}
