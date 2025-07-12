#include "GameCommon.h"

#include "..\fun3d\AiMission.h"
#include "..\fun3d\PowerUp.h"
#include "..\fun3d\ScriptUtils.h"

/*
	Misn10Mission
*/

class Misn10Mission : public AiMission {
	DECLARE_RTIME(Misn10Mission)
public:
	Misn10Mission(void);
	~Misn10Mission();

	virtual bool Load(file fp);
	virtual bool PostLoad(void);
	virtual bool Save(file fp);

	virtual void Update(void);

	virtual void AddObject(GameObject *gameObj);

private:
	void Setup(void);
	void AddObject(Handle h);
	void Execute(void);

	union {
		struct {
			// bool declarations
			bool start_done,
				 sav_moved,
				 base_dead, 
				 build_tug,
				 making_another_tug,
				 made_another_tug,
				 position1, position2, position3, position4, position5, position6, position7,
				 sav_seized, sav_free, sav_secure,
				 tug_underway1, tug_underway2, tug_underway3, tug_underway4, tug_underway5, tug_underway6, tug_underway7,
				 tug_wait_center, tug_wait2, tug_wait3, tug_wait4, tug_wait5, tug_wait6, tug_wait7, tug_wait_base,
				 return_to_base,
				 tug_after_sav,
				 objective_on,
				 tug_at_wait_center,
				 relic_free,
				 new_aipa, new_aipb,
				 fighters_underway, sav_protected,
				 turret1_underway, turret2_underway, turret3_underway,
				 turret1_stop, turret2_stop,
				 artil1_stop, artil2_stop, artil3_stop,
				 artil1_underway, artil2_underway, artil3_underway,
				 got_position,
				 fighter1_underway, fighter2_underway,
				 tank1_follow, tank2_follow,
				 tank1_stop, tank2_stop,
				 plan_a, plan_b,
				 new_sav_built,//temp
				 game_over,
				 chase_tug,
				 sav_warning,
				 player_dead,
				 quake,
				 b_last;
		};
		bool b_array[66];
	};

	union {
		struct {
			// float declarations
			float gech_warning_message,
				  relic_check,

				  build_sav_time,//temp
				  quake_time,
				  build_another_tug_time,
				  fighter_time,
				  artil1_check, artil2_check, artil3_check,
				  turret1_check, turret2_check, next_second, geys1check,
				  f_last;
		};
		float f_array[13];
	};
	
	union {
		struct {
			// Handle declarations
			Handle  user,
					ccatug, 
					tugger,
					sav,
					nav1, nav2, nav3,
					ccaartil1, ccaartil2, ccaartil3,
					ccaturret1, ccaturret2, ccaturret3,
					ccarecycle, ccamuf,
					nsdfrecycle,
					ccafighter1, ccafighter2,
					ccatank1, ccatank2,
					post1_geyser, post3_geyser,
					geys1, geys2, geys3, geys4, geys5, geys6, geys7,
					svartil1, svartil2,
					h_last;
		};
		Handle h_array[31];
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

IMPLEMENT_RTIME(Misn10Mission)

Misn10Mission::Misn10Mission(void)
{
}

Misn10Mission::~Misn10Mission()
{
}

void Misn10Mission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

bool Misn10Mission::Load(file fp)
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

bool Misn10Mission::PostLoad(void)
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

bool Misn10Mission::Save(file fp)
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

void Misn10Mission::Update(void)
{
	AiMission::Update();
	Execute();
}

void Misn10Mission::Setup(void)
{
/*
Here's where you set the values at the start.  
*/
	start_done = false;
	sav_moved = false;
	base_dead = false;
	player_dead = false;
	making_another_tug = false;
	made_another_tug = false;
	build_tug = false;
	position1 = false;
	position2 = false;
	position3 = false;
	position4 = false;
	position5 = false;
	position6 = false;
	position7 = false;
	tug_underway1 = false;
	tug_underway2 = false;
	tug_underway3 = false;
	tug_underway4 = false;
	tug_underway5 = false;
	tug_underway6 = false;
	tug_underway7 = false;
	tug_after_sav = false;
	sav_seized = false;
	sav_free = true;
	sav_secure = false;
	return_to_base = false;
	tug_wait_center = false;
	tug_wait2 = false;
	tug_wait3 = false;
	tug_wait4 = false;
	tug_wait5 = false;
	tug_wait6 = false;
	tug_wait7 = false;
	tug_wait_base = false;
	tug_at_wait_center = false;
	objective_on = false;
	new_aipa = false;
	new_aipb = false;
	relic_free = true;
	fighters_underway = false;
	sav_protected = false;
	turret1_underway = false;
	turret2_underway = false;
	turret3_underway = false;
	turret1_stop = false;
	turret2_stop = false;
	artil1_stop = false;
	artil2_stop = false;
	artil3_stop = false;
	got_position = false;
	fighter1_underway = false;
	fighter2_underway = false;
	tank1_follow = false;
	tank2_follow = false;
	tank1_stop = false;
	tank2_stop = false;
	plan_a = false;
	plan_b = false;
	artil1_underway = false;
	artil2_underway = false;
	artil3_underway = false;
	game_over = false;
	chase_tug = false;
	sav_warning = false;
	quake = false;
	new_sav_built = false;//temp

	gech_warning_message = 99999.0f;

	build_sav_time = 99999.0f;//temp

	build_another_tug_time = 99999.0f;
	relic_check = 99999.0f;
	fighter_time = 99999.0f;
	turret1_check = 99999.0f;
	turret2_check = 99999.0f;
	artil1_check = 99999.0f;
	artil2_check = 99999.0f;
	artil3_check = 99999.0f;
	geys1check = 180.0f;
	quake_time = 4.0f;
	next_second = 0;

	sav = GetHandle("relic");
	nav1 = GetHandle("cam1");
	nav2 = GetHandle("cam2");
	nav3 = GetHandle("cam3");
	ccarecycle = GetHandle("svrecycler");
	nsdfrecycle = GetHandle("avrecycler");
	post1_geyser = GetHandle("post1_geyser");
	post3_geyser = GetHandle("post3_geyser");
	geys1 = GetHandle("geyser1");
	geys2 = GetHandle("geyser2");
	geys3 = GetHandle("geyser3");
	geys4 = GetHandle("geyser4");
	geys5 = GetHandle("geyser5");
	geys6 = GetHandle("geyser6");
	geys7 = GetHandle("geyser7");
	svartil1 = GetHandle("svartil1");
	svartil2 = GetHandle("svartil2");
	ccatug = NULL;
	ccaartil1 = NULL;
	ccaartil2 = NULL;
	ccaartil3 = NULL;
	ccaturret1 = NULL;
	ccaturret2 = NULL;
	ccaturret3 = NULL;
	ccafighter1 = NULL;
	ccafighter2 = NULL;
	ccatank1 = NULL;
	ccatank2 = NULL;
	ccamuf = GetHandle("svmuf");
	tugger = NULL;
}

void Misn10Mission::AddObject(Handle h)
{
	if ((ccatug == NULL) && (IsOdf(h,"svhaul")))
	{
			ccatug = h;
	}
	else
	{
		if ((ccaartil1 == NULL) && (IsOdf(h,"svartl")))
		{
			ccaartil1 = h;
		}
		else
		{
			if ((ccaartil2 == NULL) && (IsOdf(h,"svartl")))
			{
				ccaartil2 = h;
			}
			else
			{
				if ((ccaartil3 == NULL) && (IsOdf(h,"svartl")))
				{
					ccaartil3 = h;
				}
				else
				{
					if ((ccaturret1 == NULL) && (IsOdf(h,"svturr")))
					{
						ccaturret1 = h;
					}
					else
					{
						if ((ccaturret2 == NULL) && (IsOdf(h,"svturr")))
						{
							ccaturret2 = h;
						}
						else
						{
							if ((ccaturret3 == NULL) && (IsOdf(h,"svturr")))
							{
								ccaturret3 = h;
							}
							else
							{
								if ((ccafighter1 == NULL) && (IsOdf(h,"svfigh")))
								{
									ccafighter1 = h;
								}
								else
								{
									if ((ccafighter2 == NULL) && (IsOdf(h,"svfigh")))
									{
										ccafighter2 = h;
									}
									else
									{
										if ((ccatank1 == NULL) && (IsOdf(h,"svltnk")))
										{
											ccatank1 = h;
										}
										else
										{
											if ((ccatank2 == NULL) && (IsOdf(h,"svltnk")))
											{
												ccatank2 = h;
											}
											else
											{
												if ((ccamuf == NULL) && (IsOdf(h,"svmuf")))
												{
													ccamuf = h;
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

void Misn10Mission::Execute(void)
{
/*
Here is where you put what happens every frame.  
*/

	if ((sav_free) && (IsAlive(sav)))
	{
		tugger = GetTug(sav);

		if (IsAlive(tugger))
		{
			if (GetTeamNum(tugger) == 1)
			{
				sav_free = false;
				sav_secure = true;
			}
			else
			{
				sav_free = false;
				sav_seized = true;
				tugger = ccatug;
			}
		}
	}

	if ((sav_secure) && (!IsAlive(tugger)))
	{
		if (!sav_seized)
		{
			sav_free = true;
			chase_tug = false;
			got_position = false;
			sav_secure = false;
			fighter1_underway = false;
			fighter2_underway = false;
		}
	}


	
/*	if (IsAlive(sav))
	{
		if (IsAlive(ccatug))
		{
			if (HasCargo(ccatug))
			{
				sav_free = false;
				sav_seized = true;
			}
			else
			{
				if (!sav_secure)
				{
					sav_free = true;
					sav_seized = false;
				}
			}
		}

		if (!sav_seized)
		{
			tugger = GetTug(sav);

			if (tugger !=0)
			{
				if (GetTeamNum(tugger) == 1)
				{
					sav_free = false;
					sav_secure = true;
				}
				else
				{
					sav_free = false;
					sav_seized = true;
					tugger = ccatug;
				}
			}
		}

		if ((sav_secure) && (!IsAlive(tugger)))
		{
			if (!sav_seized)
			{
				sav_free = true;
				chase_tug = false;
				got_position = false;
				sav_secure = false;
				fighter1_underway = false;
				fighter2_underway = false;
			}
		}
	}
*/
	if ((sav_seized) && (!IsAlive(ccatug)))
	{
		if ((IsAlive(ccatank1)) && (IsAlive(sav)))
		{
			Goto(ccatank1, sav);
		}
		if ((IsAlive(ccatank2)) && (IsAlive(sav)))
		{
			Goto(ccatank2, sav);
		}
		sav_seized = false;
		got_position = false;
		sav_free = true;
	}
	
	if (!IsAlive(ccatug))
	{
		//////////////////////////
		tug_underway1 = false;	
		tug_underway2 = false;	
		tug_underway3 = false;	
		tug_underway4 = false;	
		tug_underway5 = false;	 
		tug_underway6 = false;	
		tug_underway7 = false;	
		tug_after_sav = false;	//all tug settings reset because the last tug was destroyed
		return_to_base = false;	
		tug_wait_center = false;
		tug_wait2 = false;		
		tug_wait3 = false;		
		tug_wait4 = false;		
		tug_wait5 = false;		
		tug_wait6 = false;		
		tug_wait7 = false;		
		tug_wait_base = false;	
		tug_at_wait_center = false;
		got_position = false;
		sav_warning = false;
		//////////////////////////
	}
	
	if ((sav_seized) && (!sav_warning))
	{
		AudioMessage("misn1005.wav"); // the sav is being taken sir
		sav_warning = true;
	}
	
	user = GetPlayerHandle(); //assigns the player a handle every frame

// constant variables

	if (!IsAlive(ccaturret1))
	{
		turret1_underway = false;
		turret1_stop = false;
	}
	if (!IsAlive(ccaturret2))
	{
		turret2_underway = false;
		turret2_stop = false;
	}
	if (!IsAlive(ccaartil1))
	{
		artil1_stop = false;
		artil1_underway = false;
	}
	if (!IsAlive(ccaartil2))
	{
		artil2_stop = false;
		artil2_underway = false;
	}
	if (!IsAlive(ccaartil3))
	{
		artil3_stop = false;
		artil3_underway = false;
	}
	if (!IsAlive(ccafighter1))
	{
		fighter1_underway = false;
		chase_tug = false;
	}
	if (!IsAlive(ccafighter2))
	{
		fighter2_underway = false;
		chase_tug = false;
	}
	if (!IsAlive(ccatank1))
	{
		tank1_follow = false;
		tank1_stop = false;
		chase_tug = false;
	}
	if (!IsAlive(ccatank2))
	{
		tank2_follow = false;
		tank2_stop = false;
		chase_tug = false;
	}

// the first thing I want to do is get the position of the sav
	if ((IsAlive(ccatug)) && (sav_free) && (!got_position))
	{
		if (((GetDistance(sav, geys1)) < (GetDistance(sav, geys2))) && ((GetDistance(sav, geys1)) < (GetDistance(sav, geys3))) && ((GetDistance(sav, geys1)) < (GetDistance(sav, geys4)))
			&& ((GetDistance(sav, geys1)) < (GetDistance(sav, geys5))) && ((GetDistance(sav, geys1)) < (GetDistance(sav, geys6))) && ((GetDistance(sav, geys1)) < (GetDistance(sav, geys7))))
		{
			position1 = true; //
			position2 = false;//
			position3 = false;// this code gets the position of the relic so I can determine 
			position4 = false;// which path to send the cca tug down and back
			position5 = false;//
			position6 = false;//
			position7 = false;//
		}
		else
		{
			if (((GetDistance(sav, geys2)) < (GetDistance(sav, geys1))) && ((GetDistance(sav, geys2)) < (GetDistance(sav, geys3))) && ((GetDistance(sav, geys2)) < (GetDistance(sav, geys4)))
				&& ((GetDistance(sav, geys2)) < (GetDistance(sav, geys5))) && ((GetDistance(sav, geys2)) < (GetDistance(sav, geys6))) && ((GetDistance(sav, geys2)) < (GetDistance(sav, geys7))))
			{
				position1 = false;//
				position2 = true; //
				position3 = false;// this code gets the position of the relic so I can determine 
				position4 = false;// which path to send the cca tug down and back
				position5 = false;//
				position6 = false;//
				position7 = false;//
			}
			else
			{
				if (((GetDistance(sav, geys3)) < (GetDistance(sav, geys1))) && ((GetDistance(sav, geys3)) < (GetDistance(sav, geys2))) && ((GetDistance(sav, geys3)) < (GetDistance(sav, geys4)))
					&& ((GetDistance(sav, geys3)) < (GetDistance(sav, geys5))) && ((GetDistance(sav, geys3)) < (GetDistance(sav, geys6))) && ((GetDistance(sav, geys3)) < (GetDistance(sav, geys7))))
				{
					position1 = false;//
					position2 = false;//
					position3 = true; // this code gets the position of the relic so I can determine 
					position4 = false;// which path to send the cca tug down and back
					position5 = false;//
					position6 = false;//
					position7 = false;//
				}
				else
				{
					if ((!sav_seized) && ((GetDistance(sav, geys4)) < (GetDistance(sav, geys1))) && ((GetDistance(sav, geys4)) < (GetDistance(sav, geys2))) && ((GetDistance(sav, geys4)) < (GetDistance(sav, geys3)))
						&& ((GetDistance(sav, geys4)) < (GetDistance(sav, geys5))) && ((GetDistance(sav, geys4)) < (GetDistance(sav, geys6))) && ((GetDistance(sav, geys4)) < (GetDistance(sav, geys7))))
					{
						position1 = false;//
						position2 = false;//
						position3 = false;// this code gets the position of the relic so I can determine 
						position4 = true; // which path to send the cca tug down and back
						position5 = false;//
						position6 = false;//
						position7 = false;//
					}
					else
					{
						if (((GetDistance(sav, geys5)) < (GetDistance(sav, geys1))) && ((GetDistance(sav, geys5)) < (GetDistance(sav, geys2))) && ((GetDistance(sav, geys5)) < (GetDistance(sav, geys3)))
							&& ((GetDistance(sav, geys5)) < (GetDistance(sav, geys4))) && ((GetDistance(sav, geys5)) < (GetDistance(sav, geys6))) && ((GetDistance(sav, geys5)) < (GetDistance(sav, geys7))))
						{
							position1 = false;//
							position2 = false;//
							position3 = false;//
							position4 = false;// this code gets the position of the relic so I can determine 
							position5 = true; // which path to send the cca tug down and back
							position6 = false;//
							position7 = false;//
						}
						else
						{
							if (((GetDistance(sav, geys6)) < (GetDistance(sav, geys1))) && ((GetDistance(sav, geys6)) < (GetDistance(sav, geys2))) && ((GetDistance(sav, geys6)) < (GetDistance(sav, geys3)))
								&& ((GetDistance(sav, geys6)) < (GetDistance(sav, geys4))) && ((GetDistance(sav, geys6)) < (GetDistance(sav, geys5))) && ((GetDistance(sav, geys6)) < (GetDistance(sav, geys7))))
							{
								position1 = false;//
								position2 = false;//
								position3 = false;// this code gets the position of the relic so I can determine 
								position4 = false;// which path to send the cca tug down and back
								position5 = false;//
								position6 = true; //
								position7 = false;//
							}
							else
							{
								if (((GetDistance(sav, geys7)) < (GetDistance(sav, geys1))) && ((GetDistance(sav, geys7)) < (GetDistance(sav, geys2))) && ((GetDistance(sav, geys7)) < (GetDistance(sav, geys3)))
									&& ((GetDistance(sav, geys7)) < (GetDistance(sav, geys4))) && ((GetDistance(sav, geys7)) < (GetDistance(sav, geys5))) && ((GetDistance(sav, geys7)) < (GetDistance(sav, geys6))))
								{
									position1 = false;//
									position2 = false;//
									position3 = false;// this code gets the position of the relic so I can determine 
									position4 = false;// which path to send the cca tug down and back
									position5 = false;//
									position6 = false;//
									position7 = true; //
								}
							}
						}
					}
				}
			}
		}

		got_position = true;
	}

// now I'll start the mission
	if (!start_done)
	{
		AudioMessage("misn1000.wav"); // player briefing
		ClearObjectives();
		AddObjective("misn1000.otf", WHITE);
		SetIndependence(svartil1, 1);
		SetIndependence(svartil2, 1);
		SetScrap(1, 30);
		SetPilot(1, 10);
		SetScrap(2, 40);
		SetPilot(2, 40);
		SetAIP("misn10.aip"); // this sets the soviets into action
//		build_sav_time = Get_Time() + 120.0f;//temp
//		relic_check = Get_Time() + 5.0f;
		turret1_check = Get_Time() + 19.0f;
		turret2_check = Get_Time() + 20.0f;
		artil1_check = Get_Time() + 21.0f;
		artil2_check = Get_Time() + 22.0f;
		artil3_check = Get_Time() + 23.0f;
		if (nav1!=NULL) GameObjectHandle::GetObj(nav1)->SetName("Relic Site");
		if (nav2!=NULL) GameObjectHandle::GetObj(nav2)->SetName("CCA Base");
		if (nav3!=NULL) GameObjectHandle::GetObj(nav3)->SetName("Drop Zone");
		relic_free = true;
		start_done = true;		
	}

	if ((GetDistance(user, sav) < 100.0f) && (!objective_on))
	{
		SetObjectiveOn(sav);
		SetObjectiveName(sav, "Alien Relic");
		objective_on = true;
	}

/*	if ((!quake) && (quake_time < Get_Time()))
	{
		quake_time = Get_Time() + 10.0f;
		StartEarthquake(2.0f);
		quake = true;
	}

	if ((quake) && (quake_time < Get_Time()))
	{
		StopEarthquake();
		quake_time = Get_Time() + 120.0f;
		quake = false;
	}
*/

// The first thing the soviets do is secure the sav with fighters
	
	if ((relic_free) && (IsAlive(ccafighter1)) && (!fighter1_underway))
	{
		Follow(ccafighter1, sav);
		fighter1_underway = true;
	}

	if ((relic_free) && (IsAlive(ccafighter2)) && (!fighter2_underway))
	{
		Follow(ccafighter2, sav);
		fighter2_underway = true;
	}

// now that fighters are protecting the sav the soviets position turrets to assist
	if ((IsAlive(ccaturret1)) && (!turret1_underway))
	{
		Goto(ccaturret1, "relic_path1");
		turret1_underway = true;
	}

	if ((IsAlive(ccaturret2)) && (!turret2_underway))
	{
		Goto(ccaturret2, "relic_path1");
		turret2_underway = true;
	}

	if ((IsAlive(ccaturret3)) && (!turret3_underway))
	{
		if ((IsAlive(ccarecycle)) && (GetDistance(ccaturret3, ccarecycle) > 30.0f))
		{
			Defend(ccaturret3);
			turret3_underway = true;
		}
	}

// gets the turrets to stop
	if ((turret1_underway) && (turret1_check < Get_Time()))
	{
		turret1_check = Get_Time() + 3.0f;

		if ((IsAlive(ccaturret1)) && (!turret1_stop) && (GetDistance(ccaturret1, geys1) < 50.0f))
		{
			Defend(ccaturret1);
			turret1_stop = true;
		}
	}

	if ((turret2_underway) && (turret2_check < Get_Time()))
	{
		turret2_check = Get_Time() + 3.0f;

		if ((IsAlive(ccaturret2)) && (!turret2_stop) && (GetDistance(ccaturret2, geys2) < 50.0f))
		{
			Defend(ccaturret2);
			turret2_stop = true;
		}
	}

// now the soviets will check to see if they can change their first aip

	if ((IsAlive(ccafighter1)) && (IsAlive(ccafighter2)) 
		&& (IsAlive(ccaturret1)) && (IsAlive(ccaturret2)) && (!plan_a))
	{
		if (GetScrap(2) > 15.0f)
		{
			SetAIP("misn10a.aip");
			plan_a = true;
		}
	}

/*	if ((IsAlive(ccatank1)) && (!IsAlive(ccatug)) && (!tank1_stop))
	{
		Stop(ccatank1);
		tank1_stop = true;
	}

	if ((IsAlive(ccatank2)) && (!IsAlive(ccatug)) && (!tank2_stop))
	{
		Stop(ccatank2);
		tank2_stop = true;
	}
*/

// now they check to see if they can load their next aip
//	if ((IsAlive(ccatug)) && (IsAlive(ccatank1)) 
//		&& (IsAlive(ccatank2)) && (!plan_b))
//	{
//		SetScrap(2, 40);
//		SetAIP("misn10b.aip");
//		plan_b = true;
//	}

// this sets the artillery into motion

	if ((IsAlive(ccaartil1)) && (!artil1_underway))
	{
		Goto(ccaartil1, "artil1_path", 1);
		artil1_underway = true;
	}

	if ((IsAlive(ccaartil2)) && (!artil2_underway))
	{
		Goto(ccaartil2, "artil2_path", 1);
		artil2_underway = true;
	}

	if ((IsAlive(ccaartil3)) && (!artil3_underway))
	{
		Goto(ccaartil3, "relic_path1");
		artil3_underway = true;
	}
// this is checking to see if the soviet artil has reached it's spot
		if (artil1_check < Get_Time())
		{
			artil1_check = Get_Time() + 3.0f;

			if ((IsAlive(ccaartil1)) && (!artil1_stop) && (GetDistance(ccaartil1, post1_geyser) < 20.0f))
			{
				Defend(ccaartil1);
				artil1_stop = true;
			}
		}

		if (artil2_check < Get_Time())
		{
			artil2_check = Get_Time() + 3.0f;

			if ((IsAlive(ccaartil2)) && (!artil2_stop) && (GetDistance(ccaartil2, post3_geyser) < 20.0f))
			{
				Defend(ccaartil2);
				artil2_stop = true;
			}
		}

		if (artil3_check < Get_Time())
		{
			artil3_check = Get_Time() + 3.0f;

			if ((IsAlive(ccaartil3)) && (!artil3_stop) && (GetDistance(ccaartil3, geys2) < 50.0f))
			{
				Defend(ccaartil3);
				artil3_stop = true;
			}
		}
			
/*
	if ((build_sav_time < Get_Time()) && (!new_sav_built)) //this will be replaced by "sav_free"
	{
		sav = BuildObject ("abstor", 1, geys7);

		tug_underway1 = false;
		tug_underway2 = false;
		tug_underway3 = false;
		tug_underway4 = false;
		tug_underway5 = false;
		tug_underway6 = false;
		tug_underway7 = false;
		tug_after_sav = false;
		tug_wait_center = false;
		tug_wait2 = false;
		tug_wait3 = false;
		tug_wait4 = false;
		tug_wait5 = false;
		tug_wait6 = false;
		tug_wait7 = false;
		tug_wait_base = false;		
		sav_seized = false;
		new_sav_built = true;
	}
*/

// hopefully, the following code will build a cca tug every 30 seconds after the last cca tug is destoyed
/*
		if ((!build_tug) && (IsAlive(ccarecycle)))
		{
			ccatug = BuildObject("svhaul", 2, ccarecycle);
			build_tug = true;
		}
		
		if ((build_tug) && (!IsAlive(ccatug)) && (!making_another_tug))
		{
			build_another_tug_time = Get_Time() + 30.0f;
			//////////////////////////
			tug_underway1 = false;	//
			tug_underway2 = false;	//
			tug_underway3 = false;	//
			tug_underway4 = false;	//
			tug_underway5 = false;	// 
			tug_underway6 = false;	//
			tug_underway7 = false;	//
			tug_after_sav = false;	//all tug settings reset because the last tug was destroyed
			return_to_base = false;	//
			tug_wait_center = false;//
			tug_wait2 = false;		//
			tug_wait3 = false;		//
			tug_wait4 = false;		//
			tug_wait5 = false;		//
			tug_wait6 = false;		//
			tug_wait7 = false;		//
			tug_wait_base = false;	//
			tug_at_wait_center = false;
			//////////////////////////
			making_another_tug = true;
		}

		if ((making_another_tug) && (build_another_tug_time < Get_Time()) && (build_tug))
		{
			making_another_tug = false;
			build_tug = false;
		}
*/
// now I'm attempting to send the cca tug to the relic in the smartest path /////////////////////////////////////////////////////////////////////////////////////////////////////////
// first I determine where the relic on the map by dertermining which geyser its closest to /////////////////////////////////////////////////////////////////////////////////////////


// now that I know which geyser the relic closest to I'll send the cca tug down the appropriate path (to keep it out of the lava fields as much as possible //////////////////////////////
if ((IsAlive(ccatug)) && (got_position))
{
				if ((IsAlive(ccatank1)) && (!tank1_follow))
				{
					Follow(ccatank1, ccatug, 1);
					tank1_follow = true;
				}

				if ((IsAlive(ccatank2)) && (!tank2_follow))
				{
					Follow(ccatank2, ccatug, 1);
					tank2_follow = true;
				}

	if ((!tug_underway1) && (sav_free) && (position1) && (!tug_after_sav))
	{
		Goto(ccatug, "relic_path1", 1);
		tug_underway1 = true;
	}

	if ((tug_underway1) && (sav_free) && (GetDistance(ccatug, sav) < GetDistance(ccatug, geys1)) && 
		(GetDistance(ccatug, sav) < 100.0f) && (!tug_after_sav))
	{
		Pickup(ccatug, sav, 1);
		if (IsAlive(ccatank1))
		{
			Follow(ccatank1, ccatug, 0);
		}
		if (IsAlive(ccatank2))
		{
			Follow(ccatank2, ccatug, 0);
		}
		tug_after_sav = true;
	}

	if ((tug_underway1) && (sav_free) && (GetDistance(ccatug, geys1) < 100.0f) && (!tug_after_sav))
	{
		Pickup(ccatug, sav, 1);
		tug_after_sav = true;
	}

		if ((sav_free) && (position2) && (!tug_underway2) && (!tug_after_sav))
		{
			Goto(ccatug, "relic_path1", 1);
			tug_underway2 = true;
		}

		if ((tug_underway2) && (sav_free) && (GetDistance(ccatug, sav) < GetDistance(ccatug, geys2)) &&
			(GetDistance(ccatug, sav) < 100.0f) && (!tug_after_sav))
		{
			Pickup(ccatug, sav, 1);
			tug_after_sav = true;
		}

		if ((tug_underway2) && (sav_free) && (GetDistance(ccatug, geys2) < 100.0f) && (!tug_after_sav))
		{
			Pickup(ccatug, sav, 1);
			tug_after_sav = true;
		}

	if ((sav_free) && (position3) && (!tug_underway3) && (!tug_after_sav))
	{
		Goto(ccatug, "attack_path_central", 1);
		tug_underway3 = true;
	}

	if ((tug_underway3) && (sav_free) && (GetDistance(ccatug, sav) < GetDistance(ccatug, geys3)) &&
		(GetDistance(ccatug, sav) < 100.0f) && (!tug_after_sav))
	{
		Pickup(ccatug, sav, 1);
		tug_after_sav = true;
	}

	if ((tug_underway3) && (sav_free) && (GetDistance(ccatug, geys3) < 100.0f) && (!tug_after_sav))
	{
		Pickup(ccatug, sav, 1);
		tug_after_sav = true;
	}

		if ((sav_free) && (position4) && (!tug_underway4) && (!tug_after_sav))
		{
			Goto(ccatug, "attack_path_central", 1);
			tug_underway4 = true;
		}

		if ((tug_underway4) && (sav_free) && (GetDistance(ccatug, sav) < GetDistance(ccatug, geys4)) &&
			(GetDistance(ccatug, sav) < 100.0f) && (!tug_after_sav))
		{
			Pickup(ccatug, sav, 1);
			tug_after_sav = true;
		}

		if ((tug_underway4) && (sav_free) && (GetDistance(ccatug, geys4) < 100.0f) && (!tug_after_sav))
		{
			Pickup(ccatug, sav, 1);
			tug_after_sav = true;
		}

	if ((sav_free) && (position5) && (!tug_underway5) && (!tug_after_sav))
	{
		Goto(ccatug, "attack_path_south", 1);
		tug_underway5 = true;
	}

	if ((tug_underway5) && (sav_free) && (GetDistance(ccatug, sav) < GetDistance(ccatug, geys5)) &&
		(GetDistance(ccatug, sav) < 100.0f) && (!tug_after_sav))
	{
		Pickup(ccatug, sav, 1);
		tug_after_sav = true;
	}

	if ((tug_underway5) && (sav_free) && (GetDistance(ccatug, geys5) < 100.0f) && (!tug_after_sav))
	{
		Pickup(ccatug, sav, 1);
		tug_after_sav = true;
	}

		if ((sav_free) && (position6) && (!tug_underway6) && (!tug_after_sav))
		{
			Goto(ccatug, "attack_path_north", 1);
			tug_underway6 = true;
		}

		if ((tug_underway6) && (sav_free) && (GetDistance(ccatug, sav) < GetDistance(ccatug, geys6)) && 
			(GetDistance(ccatug, sav) < 100.0f) && (!tug_after_sav))
		{
			Pickup(ccatug, sav, 1);
			tug_after_sav = true;
		}

		if ((tug_underway6) && (sav_free) && (GetDistance(ccatug, geys6) < 100.0f) && (!tug_after_sav))
		{
			Pickup(ccatug, sav, 1);
			tug_after_sav = true;
		}

	if ((sav_free) && (position7) && (!tug_underway7) && (!tug_after_sav))
	{
		Goto(ccatug, "attack_path_south", 1);
		tug_underway7 = true;
	}

	if ((tug_underway7) && (sav_free) && (GetDistance(ccatug, sav) < GetDistance(ccatug, geys7)) && 
		(GetDistance(ccatug, sav) < 100.0f) && (!tug_after_sav))
	{
		Pickup(ccatug, sav, 1);
		tug_after_sav = true;
	}

	if ((tug_underway7) && (sav_free) && (GetDistance(ccatug, geys7) < 100.0f) && (!tug_after_sav))
	{
		Pickup(ccatug, sav, 1);
		tug_after_sav = true;
	}

// now that the tug has picked the correct path I'll have the tug pick up the sav and pick a path home //////////////////////////////////

	if ((tug_after_sav) && (tug_underway1) && (sav_seized) && (!return_to_base))
	{
		Goto(ccatug, "main_return_path", 1);
		return_to_base = true;
	}

	if ((tug_after_sav) && (tug_underway2) && (sav_seized) && (!return_to_base))
	{
		Goto(ccatug, ccarecycle, 1);
		return_to_base = true;
	}

	if ((tug_after_sav) && (tug_underway3) && (sav_seized) && (!return_to_base))
	{
		Goto(ccatug, "lsouth_return_path", 1);
		return_to_base = true;
	}

	if ((tug_after_sav) && (tug_underway4) && (sav_seized) && (!return_to_base))
	{
		Goto(ccatug, "main_return_path", 1);
		return_to_base = true;
	}

	if ((tug_after_sav) && (tug_underway5) && (sav_seized) && (!return_to_base))
	{
		Goto(ccatug, "ssouth_return_path", 1);
		return_to_base = true;
	}

	if ((tug_after_sav) && (tug_underway6) && (sav_seized) && (!return_to_base))
	{
		Goto(ccatug, "main_return_path", 1);
		return_to_base = true;
	}

	if ((tug_after_sav) && (tug_underway7) && (sav_seized) && (!return_to_base))
	{
		Goto(ccatug, "msouth_return_path", 1);
		return_to_base = true;
	}
}

// this is what happens if the player aquires the relic before the cca and a cca tug exits //////////////////

	if (!IsAlive(sav))
	{
		if ((sav_secure) && (!tug_underway1))
		{
			tug_wait_base = true;
		}	
		
		if ((sav_secure) && (tug_underway1))
		{
			tug_underway1 = false;
			tug_wait_center = true;
		}

		if ((sav_secure) && (!tug_underway2))
		{
			tug_wait_base = true;
		}	
	}

		if ((sav_secure) && (tug_underway2) && (GetDistance (ccatug, geys2) < 50.0f) && (!tug_wait2))
		{
			Goto(ccatug, geys2, 1);
			tug_underway2 = false;
			tug_wait2 = true;
		}

		if ((sav_secure) && (tug_underway2) && (tug_after_sav) && (!tug_wait2))
		{
			Goto(ccatug, geys2, 1);
			tug_underway2 = false;
			tug_after_sav = false;
			tug_wait2 = true;
		}

	if ((!IsAlive(sav)) && (sav_secure) && (!tug_underway3))
	{
		tug_wait_base = true;
	}	

		if ((sav_secure) && (tug_underway3) && (GetDistance (ccatug, geys3) < 50.0f) && (!tug_wait3))
		{
			Goto(ccatug, geys3, 1);
			tug_underway3 = false;	
			tug_wait3 = true;
		}

		if ((sav_secure) && (tug_underway3) && (tug_after_sav) && (!tug_wait3))
		{
			Goto(ccatug, geys3, 1);
			tug_underway3 = false;	
			tug_after_sav = false;
			tug_wait3 = true;
		}

	if ((!IsAlive(sav)) && (sav_secure) && (!tug_underway4))
	{
		tug_wait_base = true;
	}	

		if ((sav_secure) && (tug_underway4) && (GetDistance (ccatug, geys4) < 50.0f) && (!tug_wait4))
		{
			Goto(ccatug, geys4, 1);
			tug_underway4 = false;
			tug_wait4 = true;
		}

		if ((sav_secure) && (tug_underway4) && (tug_after_sav) && (!tug_wait4))
		{
			Goto(ccatug, geys4, 1);
			tug_underway4 = false;
			tug_after_sav = false;
			tug_wait4 = true;
		}

	if ((!IsAlive(sav)) && (sav_secure) && (!tug_underway5))
	{
		tug_wait_base = true;
	}	

		if ((sav_secure) && (tug_underway5) && (GetDistance (ccatug, geys5) < 50.0f) && (!tug_wait5))
		{
			Goto(ccatug, geys5, 1);
			tug_underway5 = false;
			tug_wait5 = true;
		}

		if ((sav_secure) && (tug_underway5) && (tug_after_sav) && (!tug_wait5))
		{
			Goto(ccatug, geys5, 1);
			tug_underway5 = false;
			tug_after_sav = false;
			tug_wait5 = true;
		}

	if ((!IsAlive(sav)) && (sav_secure) && (!tug_underway6))
	{
		tug_wait_base = true;
	}	
	
		if ((sav_secure) && (tug_underway6) && (GetDistance (ccatug, geys6) < 50.0f) && (!tug_wait6))
		{
			Goto(ccatug, geys6, 1);
			tug_underway6 = false;			
			tug_wait6 = true;
		}

		if ((sav_secure) && (tug_underway6) && (tug_after_sav) && (!tug_wait6))
		{
			Goto(ccatug, geys6, 1);
			tug_underway6 = false;
			tug_after_sav = false;
			tug_wait6 = true;
		}

	if ((!IsAlive(sav)) && (sav_secure) && (!tug_underway7))
	{
		sav_seized = true;
		tug_wait_base = true;
	}	

		if ((sav_secure) && (tug_underway7) && (GetDistance (ccatug, geys7) < 50.0f) && (!tug_wait7))
		{
			Goto(ccatug, geys7, 1);
			tug_underway7 = false;
			tug_wait7 = true;
		}

		if ((sav_secure) && (tug_underway7) && (tug_after_sav) && (!tug_wait7))
		{
			Goto(ccatug, geys7, 1);
			tug_underway7 = false;
			tug_after_sav = false;
			tug_wait7 = true;
		}

// this is going to make the cca go after the american tug

		if ((tugger != 0) && (!chase_tug))
		{
			if (IsAlive(ccafighter1))
			{
				Attack(ccafighter1, tugger, 1);
			}
			if (IsAlive(ccafighter2))
			{
				Attack(ccafighter2, tugger, 1);
			}
			if (IsAlive(ccatank1))
			{
				Attack(ccatank1, tugger, 1);
			}
			if (IsAlive(ccatank2))
			{
				Attack(ccatank2, tugger, 1);
			}
			if (IsAlive(svartil1))
			{
				Attack(svartil1, tugger, 1);
			}
			if (IsAlive(svartil2))
			{
				Attack(svartil2, tugger, 1);
			}
			if (IsAlive(ccaartil1))
			{
				Attack(ccaartil1, tugger, 1);
			}
			if (IsAlive(ccaartil2))
			{
				Attack(ccaartil2, tugger, 1);
			}
			if (IsAlive(ccaartil3))
			{
				Attack(ccaartil3, tugger, 1);
			}

			chase_tug = true;
		}

// this make the artil sheel the relic

	if ((geys1check < Get_Time()) && (!chase_tug))
	{
		geys1check = Get_Time() + 150.0f;

		if (GetDistance(user, geys1) < 200.0f)
		{
			if (IsAlive(svartil1))
			{
				Attack(svartil1, user);
			}
			if (IsAlive(svartil2))
			{
				Attack(svartil2, user);
			}
		}
		else
		{
			if (IsAlive(svartil1))
			{
				Attack(svartil1, geys1);
			}
			if (IsAlive(svartil2))
			{
				Attack(svartil2, geys1);
			}
		}
	}

// this is making sure the sav doesn't die
	if (IsAlive(sav))
	{
		if (GetTime()>next_second)
		{
			GameObjectHandle::GetObj(sav)->AddHealth(100.0f);
			next_second = GetTime() + 1.0f;
		}
	}

		
// win/victory conditions ////////////////////////////////////////////

	if ((sav_secure) && (GetDistance (sav, nsdfrecycle) < 100.0f) && (!game_over))
	{
		AudioMessage("misn1001.wav");//well done
		SucceedMission(Get_Time() + 15.0f, "misn10w1.des");
		game_over = true;
	}

	if ((sav_seized) && (!game_over) && (GetDistance (sav, ccarecycle) < 100.0f))
	{
		AudioMessage("misn1002.wav");// you lost
		FailMission(Get_Time() + 15.0f, "misn10f1.des");
		game_over = true;
	}

	if ((!IsAlive(sav)) && (!game_over))
	{
		AudioMessage("misn1003.wav");// we lost the sav
		FailMission(Get_Time() + 15.0f, "misn10f2.des");
		game_over = true;
	}
	

	if ((!IsAlive(nsdfrecycle)) && (!game_over))
	{
		AudioMessage("misn1004.wav");// we lost the Utah
		FailMission(Get_Time() + 15.0f, "misn10f3.des");
		game_over = true;
	}

// END OF SCRIPT


}
