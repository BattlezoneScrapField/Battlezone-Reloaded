#include "GameCommon.h"

#include "..\fun3d\AiMission.h"
#include "..\fun3d\PowerUp.h"
#include "..\fun3d\Factory.h"
#include "..\fun3d\ScriptUtils.h"

/*
	Misn09Mission Event
*/

class Misn09Mission : public AiMission {
	DECLARE_RTIME(Misn09Mission)
public:
	Misn09Mission(void);
	~Misn09Mission();

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
				convoy_started,
				camera_ready,
				camera_artil,
				build_new_tug,
				tug_done,
				objective1,
				first_warning,
				second_warning,
				third_warning,
				player_dead,
				muf_contact, muf_moving,
				post1, post2, post3, post4,
				guard1, guard2,
				turret1_set, turret2_set, turret3_set, turret4_set,
				get_relic, relic_secure, relic_seized, relic_free, tug_underway,
				head_4_pad,
				game_over,
				next_shot, player_camera_off, next_shot_message,
				cam1_on, cam2_on, cam3_on, cam4_on, cam5_on, cam_off,
				convoy_cam_ready, convoy_cam_off, muf_deployed, scavs_alive,
				charon_found, charon_build, start, opening_vo, muf_gobaby,
				recon_artil, base_warning, muf_deployed_good, ccadead, start_camera1,
				game_over5,
				b_last;
		};
		bool b_array[54];
	};

	// floats
	union {
		struct {
			float
				start_convoy_time,
				camera_ready_time,
				build_tug_time,
				first_warning_time,
				second_warning_time,
				third_warning_time,
				camera_on_time,
				muf_check,
				movie_time, unit_check,
				turret1_time, turret2_time, turret3_time, turret4_time,
				win_check, atril_check, player_camera_time, next_shot_time,
				cam1_time, cam2_time, cam3_time, cam4_time, cam5_time,
				convoy_cam_time, deploy_check, charon_check, start_time,
				recon_message_time,
				f_last;
		};
		float f_array[28];
	};

	// handles
	union {
		struct {
			Handle
				user, relic, nav1, charon, avsilo, key_scrap,
				ccatug, nsdftug, convoy_geyser, cut_off_geyser,
				ccaturret1, ccaturret2, ccaturret3, ccaturret4, ccaturret5, ccaturret6,
				ccarecycle, ccamuf, ccaarmor, ccalaunch,
				cca1, cca2, cca3,  cca4,  cca5,  cca6,  cca7,  cca8,  cca9,  cca0,
				scav1, scav2, scav3,
				nsdfrecycle, nsdfmuf, avscav1, avscav2, avscav3, nsdfgech1,
				construct, nsdfslf, nsdfrig, tugger,
				convoy1, convoy2, convoy3, convoy4, convoy5, convoy6, convoy7, convoy8, convoy9, convoy0,
				charon_nav,
				h_last;
		};
		Handle h_array[54];
	};

	// integers
	union {
		struct {
			int
				stuff, x, y, scrap,
				audmsg,
				i_last;
		};
		int i_array[5];
	};
};

IMPLEMENT_RTIME(Misn09Mission)

Misn09Mission::Misn09Mission(void)
{
}

Misn09Mission::~Misn09Mission()
{
}

void Misn09Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

bool Misn09Mission::Load(file fp)
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

bool Misn09Mission::PostLoad(void)
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

bool Misn09Mission::Save(file fp)
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

void Misn09Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

void Misn09Mission::Setup(void)
{
/*
Here's where you set the values at the start.  
*/
	stuff = 0;
	x = 950;
	y = 3000;
	scrap = 100;
	
	start_done = false;
	start_camera1 = false;
	convoy_started = false;
	player_dead = false;
	camera_ready = false;
	build_new_tug = false;
	tug_done = false;
	objective1 = false;
	camera_artil = false;
	first_warning = false;
	second_warning = false;
	third_warning = false;
	muf_contact = false;
	muf_moving = false;
	post1 = false;
	post2 = false;
	post3 = false;
	post4 = false;
	guard1 = false;
	guard2 = false;
	turret1_set = false;
	turret2_set = false;
	turret3_set = false;
	turret4_set = false;
	get_relic = false;
	relic_secure = false;
	relic_seized = false;
	relic_free = false;
	tug_underway =false;
	game_over = false;
	head_4_pad = false;
	next_shot = false;
	player_camera_off = false;
	next_shot_message = false;
	cam1_on = false;
	cam2_on = false;
	cam3_on = false;
	cam4_on = false;
	cam5_on = false;
	cam_off = false;
	convoy_cam_ready = false;
	convoy_cam_off = false;
	muf_deployed = false;
	scavs_alive = false;
	charon_found = false;
	charon_build = false;
	start = false;
	opening_vo = false;
	muf_gobaby = false;
	recon_artil = false;
	base_warning = false;
	muf_deployed_good = false;
	ccadead = false;
	game_over5 = false;

	start_convoy_time = 99999.0f;
	camera_ready_time = 99999.0f;
	build_tug_time = 99999.0f;
	camera_on_time = 99999.0f;
	first_warning_time = 99999.0f;
	second_warning_time = 99999.0f;
	third_warning_time = 99999.0f;
	muf_check = 99999.0f;
	movie_time = 99999.0f;
	turret1_time = 99999.0f;
	turret2_time = 99999.0f;
	turret3_time = 99999.0f;
	turret4_time = 99999.0f;
	unit_check = 99999.0f;
	win_check = 99999.0f;
	atril_check = 99999.0f;
	player_camera_time = 99999.0f;
	next_shot_time = 99999.0f;
	cam1_time = 99999.0f;
	cam2_time = 99999.0f;
	cam3_time = 99999.0f;
	cam4_time = 99999.0f;
	cam5_time = 99999.0f;
	convoy_cam_time = 99999.0f;
	deploy_check = 99999.0f;
	charon_check = 99999.0f;
	start_time = 20.0f;
	recon_message_time = 99999.0f;

	ccatug = NULL;
	ccaturret1 = GetHandle("artil1");
	ccaturret2 = GetHandle("artil2");
	ccaturret3 = GetHandle("artil3");
	ccaturret4 = GetHandle("artil4");
	ccaturret5 = GetHandle("artil5");
	ccaturret6 = GetHandle("artil6");
	ccarecycle = GetHandle("svrecycle");
	avscav1 = GetHandle("scav1");
	avscav2 = GetHandle("scav2");
	avscav3 = GetHandle("scav3");
	nsdfrig = GetHandle("rig");
	nsdfslf = GetHandle("avslf");
	ccamuf = GetHandle("svmuf");
	nsdfmuf = GetHandle("avmuf");
	convoy_geyser = GetHandle("convoy_geyser");
	ccalaunch = GetHandle ("launchpad");
	nav1 = GetHandle("cam1");
	charon = GetHandle("hbchar0_i76building");
	cut_off_geyser = GetHandle ("cut_off_geyser");
	key_scrap = GetHandle("key_scrap");
	cca1 = NULL;
	cca2 = NULL;
	cca3 = NULL;
	cca4 = NULL;
	cca5 = NULL;
	cca6 = NULL;
	cca7 = NULL;
	cca8 = NULL;
	cca9 = NULL;
	cca0 = NULL;
	scav1 = NULL;
	scav2 = NULL;
	scav3 = NULL;
	nsdfgech1 = NULL; 
	nsdftug = NULL;
	convoy1 = NULL;
	convoy2 = NULL;
	convoy3 = NULL;
	convoy4 = NULL;
	convoy5 = NULL;
	convoy6 = NULL;
	convoy7 = NULL;
	convoy8 = NULL;
	convoy9 = NULL;
	convoy0 = NULL;
	relic = NULL;
	tugger = NULL;
	audmsg = NULL;
	avsilo = NULL;
	charon_nav = NULL;

}

void Misn09Mission::AddObject(Handle h)
{
	if ((cca1 == NULL) && (IsOdf(h,"svturr")))
	{
		cca1 = h;
	}
	else
	{
		if ((cca2 == NULL) && (IsOdf(h,"svturr")))
		{
			cca2 = h;
		}
		else
		{
			if ((cca3 == NULL) && (IsOdf(h,"svturr")))
			{
				cca3 = h;
			}
			else
			{
				if ((cca4 == NULL) && (IsOdf(h,"svturr")))
				{
					cca4 = h;
				}
				else
				{
					if ((cca5 == NULL) && (IsOdf(h,"svfigh")))
					{
						cca5 = h;
					}
					else
					{
						if ((cca6 == NULL) && (IsOdf(h,"svfigh")))
						{
							cca6 = h;
						}
						else
						{
							if ((cca7 == NULL) && (IsOdf(h,"svfigh")))
							{
								cca7 = h;
							}
							else
							{
								if ((cca8 == NULL) && (IsOdf(h,"svfigh")))
								{
									cca8 = h;
								}
								else
								{
									if ((cca9 == NULL) && (IsOdf(h,"svtank")))
									{
										cca9 = h;
									}
									else
									{
										if ((cca0 == NULL) && (IsOdf(h,"svtank")))
										{
											cca0 = h;
										}
										else
										{
											if ((scav1 == NULL) && (IsOdf(h,"svscav")))
											{
												scav1 = h;
											}
											else
											{
												if ((scav2 == NULL) && (IsOdf(h,"svscav")))
												{
													scav2 = h;
												}
												else
												{
													if ((scav3 == NULL) && (IsOdf(h,"svscav")))
													{
														scav3 = h;
													}
													else
													{
														if ((nsdfgech1 == NULL) && (IsOdf(h,"avwalk")))
														{
															nsdfgech1 = h;
														}
														else
														{
															if ((ccatug == NULL) && (IsOdf(h,"svhaul")))
															{
																ccatug = h;
															}
															else
															{
																if ((avsilo == NULL) && (IsOdf(h,"absilo")))
																{
																	avsilo = h;
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

void Misn09Mission::Execute(void)
{
/*
Here is where you put what happens every frame.  
*/
// START OF SCRIPT

	if ((relic_free) && (IsAlive(relic)))
	{
		tugger = GetTug(relic);

		if (IsAlive(tugger))
		{
			if (GetTeamNum(tugger) == 1)
			{
				relic_free = false;
				relic_secure = true;
			}
			else
			{
				relic_free = false;
				relic_seized = true;
				tugger = ccatug;
			}
		}
	}

	if ((relic_secure) && (!IsAlive(tugger)))
	{
		relic_free = true;
		relic_secure = false;
	}

	if ((relic_seized) && (!IsAlive(ccatug)))
	{
		relic_free = true;
		relic_seized = false;
	}

	if (IsAlive(relic))
	{
		if ((IsAlive(ccatug)) && (relic_free) && (!tug_underway))
		{
			Pickup(ccatug, relic);
			tug_underway = true;
		}

		if ((relic_seized) && (!head_4_pad))
		{
			Dropoff(ccatug, "soviet_path", 1);
			head_4_pad = true;
		}
	}

	if (!IsAlive(ccatug))
	{
		tug_underway = false;
		head_4_pad = false;
	}


/*	if (IsAlive(nsdftug))
	{
		if (HasCargo(nsdftug))
		{
			relic_free = false;
			relic_secure = true;
		}
		else
		{
			if (!relic_seized)
			{
				relic_free = true;
				relic_secure = false;
			}
		}
	}

*/
	user = GetPlayerHandle(); //assigns the player a handle every frame

//	if ((start_time < Get_Time()) && (!start))
//	{
//		start = true;
//	}

	if (!start_done)
	{
		CameraReady();
		Defend(nsdfmuf);
		SetScrap(2,40);
		SetPilot(2, 40);
	    Follow(nsdfrig, nsdfmuf, 1);
		Follow(avscav1, nsdfmuf, 1);
		Follow(avscav2, nsdfmuf, 1);
		Follow(avscav3, nsdfmuf, 1);
		Follow(nsdfslf, nsdfrig, 0);
		Defend(ccaturret1);
		Defend(ccaturret2);
		Defend(ccaturret3);
		Defend(ccaturret4);
		Defend(ccaturret5);
		Defend(ccaturret6);
//		start_convoy_time = Get_Time() + 900.0f;		
		camera_ready_time = Get_Time() + 6.0f;
		muf_check = Get_Time() + 3.0f;
		first_warning_time = Get_Time() + 700.0f;
		second_warning_time = Get_Time() + 1000.0f;
		third_warning_time = Get_Time() + 1300.0f; // was 900.0f
		unit_check = Get_Time() + 1360.0f;
		atril_check = Get_Time() + 15.0f;
		player_camera_time = Get_Time() + 11.0f;
		deploy_check = Get_Time() + 6.0f;
		charon_check = Get_Time() + 30.0f;
		next_shot_time = Get_Time() + 22.0f;
		if (nav1!=NULL) GameObjectHandle::GetObj(nav1)->SetName("Choke Point");
		start_camera1 = true;
		start_done = true;
	}

	if (start_camera1)
	{
		CameraPath("camera_circle", 375, 750, key_scrap);
	}
/*
	if ((!next_shot_message) && ((player_camera_time < Get_Time()) || (CameraCancelled())))
	{
		CameraPath("launch_camera_path", 7000, 1150, ccalaunch);

		if (x > 6000.0f)
		{
			x = x - 150;
		}
		else
		{
			x = x + 50;
		}
		y = y - 20;
*/		
/*		next_shot = true;
	}

	if ((!next_shot_message) && (IsAudioMessageDone(audmsg)))
	{
		audmsg = AudioMessage("misn0912.wav");
		next_shot_time = Get_Time() + 6.0f;
		next_shot_message = true;
	}

	if ((next_shot_message) && (!player_camera_off)) 
	{
		CameraPath("choke_cam_path", 375, 450, nav1);
	}
*/
	if ((!player_camera_off) && ((next_shot_time < Get_Time()) || (CameraCancelled())))
	{
		CameraFinish();
		start_camera1 = false;
		player_camera_off = true;
	}
 
	if (CameraCancelled())
	{
		StopAudioMessage(audmsg);
	}

// this starts the opening voice-over

	if (((camera_ready_time < Get_Time()) && (!opening_vo)))
	{
		audmsg = AudioMessage("misn0900.wav"); //starts opening V.O.5
		ClearObjectives();
		AddObjective("misn0900.otf", WHITE);
		opening_vo = true;
	}

	if ((opening_vo) && (!muf_gobaby) && (IsAudioMessageDone(audmsg)))
	{
		Goto(nsdfmuf, "return_path", 1);
		muf_gobaby = true;
	}
// this tells the muf to stop when the player gets close & plays the artillery message
	if ((muf_gobaby) && (muf_check < Get_Time()) && (!muf_contact))
	{
		muf_check = Get_Time() + 1.0f;

		if (GetDistance(user, nsdfmuf) < 70.0f)
		{
			Stop(nsdfmuf, 0);
			Stop(nsdfslf, 0);
			Defend(nsdfrig, 0);
			SetScrap(1,20);
			SetPilot(1, 7);
			AudioMessage("misn0905.wav"); // message from muf "we took a beating out there"
			movie_time = Get_Time() + 7.0f;
			muf_contact = true;
		}

	}

	if ((!objective1) && (atril_check < Get_Time()))
	{
		atril_check = Get_Time() + 15.0f;

		if (IsAlive(ccaturret1))
		{
			Defend(ccaturret1);
		}
		if (IsAlive(ccaturret2))
		{
			Defend(ccaturret2);
		}
		if (IsAlive(ccaturret3))
		{
			Defend(ccaturret3);
		}
		if (IsAlive(ccaturret4))
		{
			Defend(ccaturret4);
		}
		if (IsAlive(ccaturret5))
		{
			Defend(ccaturret5);
		}
		if (IsAlive(ccaturret6))
		{
			Defend(ccaturret6);
		}
	}

// this starts the muf towards the player
/*	if ((player_camera_off) && (!muf_moving))
	{
		Goto(nsdfmuf, "return_path", 1);
		Follow(nsdfrig, nsdfmuf, 1);
		Follow(avscav1, nsdfmuf, 1);
		Follow(avscav2, nsdfmuf, 1);
		Follow(avscav3, nsdfmuf, 1);
		Follow(nsdfslf, nsdfrig, 1);
		muf_moving = true;
	}
*/

// this checks to see if the muf is deployed

	if ((deploy_check < Get_Time()) && (!muf_deployed))
	{
		deploy_check = Get_Time() + 2.0f;

		if (IsAlive(nsdfmuf))
		{
			bool test=((Factory *) GameObjectHandle::GetObj(nsdfmuf))->IsDeployed();

			if (test)
			{
				muf_deployed = true;
			}
		}
	}

	if (((muf_deployed) || (IsAlive(avsilo))) && (!scavs_alive))
	{
		Stop(avscav1, 0);
		Stop(avscav2, 0);
		Stop(avscav3, 0);
		scavs_alive = true;
	}

// This turns the camera over the artilery units on/off ////////

	if (IsAlive(ccaturret6))
	{
		if ((muf_contact) && (movie_time < Get_Time()) && (!camera_ready))
		{

			CameraReady();
			cam5_time = Get_Time() + 7.0f;
			camera_ready = true;
		}

		if ((camera_ready) && (!cam_off))
		{
			CameraPath("camera_path", x, 300, ccaturret6);
			x = x + 90;
		}

		if ((camera_ready) && (cam5_time < Get_Time()) && (!cam_off))		
		{															
			CameraFinish();
			ClearObjectives();
			AddObjective("misn0900.otf", GREEN);
			AddObjective("misn0901.otf", WHITE);
			Stop(nsdfrig, 0);
			SetAIP("misn09.aip");
			recon_message_time = Get_Time() + 60.0f;
			cam_off = true;									
		}
	}

	if ((recon_message_time < Get_Time()) && (!recon_artil))
	{
		recon_message_time = Get_Time() + 1.0f;
		AudioMessage("misn0913.wav");
		recon_artil = true;
	}

	if ((recon_message_time < Get_Time()) && (!base_warning))
	{
		recon_message_time = Get_Time() + 2.0f;

		if (((IsAlive(nav1)) && (GetDistance(user, nav1) < 100.0f)) ||
			((IsAlive(cca5)) && (GetDistance(user, cca5) < 400.0f)) ||
			((IsAlive(cca6)) && (GetDistance(user, cca6) < 400.0f)))
		{
			AudioMessage("misn0914.wav");
			base_warning = true;
		}
	}

/*	
	if ((camera_ready) && (!cam2_on))	
	{
		CameraObject(ccaturret6, 650, 650, 650, ccaturret6);
		if (!cam1_on)
		{
			cam1_time = Get_Time() + 2.0f;
			cam1_on = true;
		}
	}

	if ((cam1_on) && (cam1_time < Get_Time()) && (!cam3_on))
	{
		CameraObject(ccaturret5, -650, 350, 300, ccaturret5);
		if (!cam2_on)
		{
			cam2_time = Get_Time() + 2.0f;
			cam2_on = true;
		}
	}

	if ((cam2_on) && (cam2_time < Get_Time()) && (!cam4_on))
	{
		CameraObject(ccaturret4, 1000, 1350, 600, ccaturret4);
		if (!cam3_on)
		{
			cam3_time = Get_Time() + 2.0f;
			cam3_on = true;
		}
	}

	if ((cam3_on) && (cam3_time < Get_Time()) && (!cam5_on))
	{
		CameraObject(ccaturret3, -90, -250, 1000, ccaturret3);
		if (!cam4_on)
		{
			cam4_time = Get_Time() + 2.0f;
			cam4_on = true;
		}
	}

	if ((cam4_on) && (cam4_time < Get_Time()) && (!cam_off))
	{
		CameraObject(ccaturret2, 500, 900, 90, ccaturret2);
		if (!cam5_on)
		{
			cam5_time = Get_Time() + 2.0f;
			cam5_on = true;
		}
	}

	if ((cam5_on) && (cam5_time < Get_Time()) && (!cam_off))		
	{															
		CameraFinish();
		ClearObjectives();
		AddObjective("misn0900.otf", GREEN);
		AddObjective("misn0901.otf", WHITE);
		cam_off = true;									
	}

*/																
// end of camera script for artiliery units ////////////////////

// this is going to set up a fortification of turrets

	if ((IsAlive(cca1)) && (!post1))
	{
		Goto(cca1, "post1", 1);
		turret1_time = Get_Time() + 10.0f;
		post1 = true;
	}

		if ((post1) && (turret1_time < Get_Time()))
		{
			turret1_time = Get_Time() + 15.0f;

			if (IsAlive(cca1))
			{
				Defend(cca1);
			}
		}

	if ((IsAlive(cca2)) && (!post2))
	{
		Goto(cca2, "post2", 1);
		turret2_time = Get_Time() + 10.0f;
		post2 = true;
	}

		if ((post2) && (turret2_time < Get_Time()))
		{
			turret2_time = Get_Time() + 15.0f;

			if (IsAlive(cca2))
			{
				Defend(cca2);
			}
		}

	if ((IsAlive(cca3)) && (!post3))
	{
		Goto(cca3, "post3", 1);
		turret3_time = Get_Time() + 10.0f;
		post1 = true;
	}

		if ((post3) && (turret3_time < Get_Time()))
		{
			turret3_time = Get_Time() + 15.0f;

			if (IsAlive(cca3))
			{
				Defend(cca3);
			}
		}

	if ((IsAlive(cca4)) && (!post4))
	{
		Goto(cca4, "post4", 1);
		turret4_time = Get_Time() + 10.0f;
		post4 = true;
	}

		if ((post4) && (turret4_time < Get_Time()))
		{
			turret4_time = Get_Time() + 15.0f;
			if (IsAlive(cca4))
			{
				Defend(cca4);
			}
		}

// this is to insure that the soviets keep trying to get the database relic	
/*																			
	if ((convoy_started) && (!IsAlive (ccatug)) && (IsAlive(ccarecycle)) && (!build_new_tug))	
	{																		
		build_tug_time = Get_Time () + 60.0f;// was 60 seconds
		tug_done = false;
		build_new_tug = true;												
	}																		
																			
	if ((build_new_tug) && (build_tug_time < Get_Time()) && (!tug_done))	
	{																		
		ccatug = BuildObject("svhaul", 2, ccarecycle);
//		convoy_started = false; // should change this to somthing else
		build_new_tug = false;
		tug_done = true;
	}																								
*/	
// if player destroys all the cca turrets///////////////////////////////////////////////

	if((!IsAlive (ccaturret1)) && (!IsAlive (ccaturret2)) && (!IsAlive (ccaturret3))
		&& (!IsAlive (ccaturret4)) && (!IsAlive (ccaturret5)) && (!IsAlive (ccaturret6))
		&& (!objective1))
	{
		AudioMessage("misn0904.wav");//congradulations you killed the turrets
		Stop(avscav1, 0);
		Stop(avscav2, 0);
		Stop(avscav3, 0);
		ClearObjectives();
		AddObjective("misn0901.otf", GREEN);
		AddObjective("misn0902.otf", WHITE);
		AddObjective("misn0903.otf", WHITE);
		if (!third_warning)
		{
			SetAIP("misn09a.aip"); // causes the soviets to get more aggresive
		}

		objective1 = true;
	}

// this is the general warning of the approaching convoy ////////////////////////////////

	if ((!first_warning) && (first_warning_time < Get_Time()))	
	{
		AudioMessage("misn0901.wav"); // the soviets convey will be here in less than 10 minutes
		first_warning = true;
	}

	if ((!second_warning) && (second_warning_time < Get_Time()))	
	{
		AudioMessage("misn0902.wav"); // the soviets convey will be here in less than 5 minutes
		second_warning = true;
	}

	if ((!third_warning) && (third_warning_time < Get_Time()))	
	{
		third_warning_time = Get_Time() + 11.0f;

		if (GetDistance(user, convoy_geyser) > 500.0f)
		{
			relic = BuildObject("obdata", 3, convoy_geyser);
			ccatug = BuildObject("svhaul", 2, "spawn1");
			convoy1 = BuildObject("svfigh", 2, "spawn2");
			convoy2 = BuildObject("svfigh", 2, "spawn2");
			convoy3 = BuildObject("svfigh", 2, "spawn2");
			convoy4 = BuildObject("svfigh", 2, "spawn3");
			convoy5 = BuildObject("svtank", 2, "spawn3");
			convoy6 = BuildObject("svtank", 2, "spawn3");
			convoy7 = BuildObject("svtank", 2, "spawn4");
			convoy8 = BuildObject("svtank", 2, "spawn4");
			convoy9 = BuildObject("svapc", 2, "spawn4");
			convoy0 = BuildObject("svapc", 2, "spawn4");
			Defend(convoy1);
			Defend(convoy2);
			Defend(convoy3);
			Defend(convoy4);
			Defend(convoy5);
			Defend(convoy6);
			Defend(convoy7);
			Defend(convoy8);
			Defend(convoy9);
			Defend(convoy0);
//			Pickup(ccatug, relic); // should do automatically

			if (!objective1)
			{
				ClearObjectives();
				AddObjective("misn0901.otf", RED);
				AddObjective("misn0902.otf", WHITE);
				AddObjective("misn0903.otf", WHITE);
			}

			win_check = Get_Time() + 5.0f;
			SetAIP("misn09b.aip"); // causes the soviets to get more reserved
			relic_free = true;			
			third_warning = true;
		}

	}

// this starts the convoy towards the launch pad ////////////////////////////////////

	if ((third_warning) && (relic_seized) && (!convoy_started))		
	{
		SetObjectiveOn(relic);
		SetObjectiveName(relic, "Alien Relic");
		Goto(ccatug, "soviet_path", 1);
		Follow(convoy1, ccatug);
		Follow(convoy2, ccatug);
		Follow(convoy3, ccatug);
		Follow(convoy4, ccatug);
		Follow(convoy5, ccatug);
		Follow(convoy6, ccatug);
		Follow(convoy7, ccatug);
		Follow(convoy8, ccatug);
		Follow(convoy9, ccatug);
		Follow(convoy0, ccatug);
		convoy_cam_time = Get_Time() + 7.0f;
		convoy_started = true;									
	}
	
	if ((convoy_started) && (!convoy_cam_ready) && (convoy_cam_time < Get_Time()))
	{
		AudioMessage("misn0903.wav"); // the soviets convey is within radar range "I'm picking up the soviet convoy"
		CameraReady();
		convoy_cam_time = Get_Time() + 18.0f;
		convoy_cam_ready = true;
	}

	if ((convoy_cam_ready) && (!convoy_cam_off))
	{
		CameraPath("convoy_cam_path", y, 1150, ccatug);
		y = y - 10;
	}

	if ((convoy_cam_ready) && (!convoy_cam_off) && ((convoy_cam_time < Get_Time()) || (CameraCancelled)))
	{
		CameraFinish();
		convoy_cam_off = true;
	}

// this is the charon code

	if ((IsAlive(charon)) && (!charon_found))
	{
		if (charon_check < Get_Time())
		{
			charon_check = Get_Time() + 2.0f;

			if (GetDistance(user, charon) < 70.0f)
			{
				AudioMessage("misn0915.wav");// told to check out the charon
				charon_found = true;
			}
		}
	}

	if ((charon_found) && (IsInfo("hbchar") == true) && (!charon_build))
	{
		AudioMessage("misn0916.wav");// well done, we'll drop a nav camera here to come back to this, this looks like a good spot to go after artils
		charon_nav = BuildObject ("apcamr", 1, "charon_spawn"); 
		if (charon_nav!=NULL) GameObjectHandle::GetObj(charon_nav)->SetName("Alien Relic");
		charon_build = true;
	}


// this is to check and see if the muf is deployed correctly
	if ((objective1) || (third_warning))
	{
		if ((!muf_deployed_good) && (deploy_check < Get_Time()))
		{
			deploy_check = Get_Time() + 2.0f;

			if (IsAlive(nsdfmuf))
			{
				bool test1=((Factory *) GameObjectHandle::GetObj(nsdfmuf))->IsDeployed();

				if ((test1) && (GetDistance(nsdfmuf, convoy_geyser) < 400.0f));
				{
					if (objective1)
					{
						ClearObjectives();
						AddObjective("misn0901.otf", GREEN);
						AddObjective("misn0902.otf", GREEN);
						AddObjective("misn0903.otf", WHITE);
						muf_deployed_good = true;
					}
					else
					{
						ClearObjectives();
						AddObjective("misn0901.otf", RED);
						AddObjective("misn0902.otf", GREEN);
						AddObjective("misn0903.otf", WHITE);
						muf_deployed_good = true;
					}
				}
			}
		}
	}

	if ((!IsAlive(ccarecycle)) && (!IsAlive(ccamuf)) && (!ccadead))
	{
		AudioMessage("misn0908.wav");// you've cleared the area of the enemy well done
		ccadead = true;		
	}

// end of general's warings /////////////////////////////////////////////////////////////

// win/victory conditions  

	if ((scavs_alive) && (!IsAlive(avscav1)) && (!IsAlive(avscav2)) && (!IsAlive(avscav3)) && (!game_over))
	{
		if ((!objective1) && (!first_warning))
		{
			scrap = GetScrap(1);

			if (scrap < 10)
			{
				FailMission(Get_Time() + 6.0f, "misn09f4.des");
				game_over = true;				
			}
		}
	}

	if ((convoy_started) && (!IsAlive(relic)) && (!game_over))
	{
		AudioMessage("misn0906.wav"); // the relic has been destroyed commander
		FailMission(Get_Time() + 15.0f, "misn09f1.des");
		game_over = true;
	}

	if ((relic_seized) && (IsAlive(ccalaunch)) && (GetDistance(ccatug, ccalaunch) < 100.0f) && (!game_over))
	{
		AudioMessage("misn0907.wav"); // the tug has reached the launch pad
		FailMission(Get_Time() + 15.0f, "misn09f2.des");
		game_over = true;
	}
	
	if ((convoy_started) && (unit_check < Get_Time()) && (!game_over5))
	{
		unit_check = Get_Time() + 10.0f;
		stuff = CountUnitsNearObject(convoy_geyser, 5000.0f, 2, NULL);

		if (stuff == 0)
		{
			AudioMessage("misn0908.wav");// you've cleared the area of the enemy well done
//			SucceedMission(Get_Time() + 15.0f, "misn09w1.des");
			game_over5 = true;
		}
	}

	if ((IsAlive(relic)) && (!relic_seized) && (win_check < Get_Time()) && (!game_over))
	{
		win_check = Get_Time() + 2.0f;

		if ((IsAlive(nsdfmuf)) && (GetDistance(relic, nsdfmuf) < 100.0f))
		{
			AudioMessage("misn0909.wav");// you've won
			SucceedMission(Get_Time() + 15.0f, "misn09w1.des");
			game_over = true;
		}
	}

	if ((!IsAlive(nsdfmuf)) && (!game_over))
	{
		AudioMessage("misn0911.wav");// you've lost your muf
		FailMission(Get_Time() + 15.0f, "misn09f3.des");
		game_over = true;
	}

	if ((!IsAlive(ccalaunch)) && (!game_over))
	{
		AudioMessage("misn0918.wav");// you've destroyed the launchpad
		FailMission(Get_Time() + 15.0f);
		game_over = true;
	}

// END OF SCRIPT

}																	
