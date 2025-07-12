#include "GameCommon.h"
#include "AiCommon.h"
#include "AiMission.h"
#include "AiProcess.h"
#include "PowerUp.h"
#include "ScriptUtils.h"


#define MAXATTACKERSPERSPAWN		20
#define MAXCURRENTATTACKERS			(7 * MAXATTACKERSPERSPAWN)

extern "C"
{
BOOL CheckCheater(LONG playOptions);
}


struct {
	float wait;
	int invehicleWait, nowait, numunits, onlyone;
	char *spawnPrefix;
	char *attacker;

} attackRounds[] = 
{
	{ 5.0,  0, 0, 3, 0, "pilot_%d",  "cspilo" },
	{ 0.0,  0, 0, 3, 0, "sold_%d",   "cssolda" },
	{ 0.0,  0, 0, 3, 0, "sniper_%d", "cssold" },
	{ 30.0, 1, 0, 3, 0, "spawn_%d",  "cvfigh" },
	{ 10.0, 0, 0, 3, 0, "spawn_%d",  "cvltnk" },
	{ 10.0, 0, 0, 3, 0, "spawn_%d",  "cvtnk" },
	{ 10.0, 0, 0, 3, 0, "spawn_%d",  "cvhraz" },
	{ 10.0, 0, 0, 3, 0, "spawn_%d",  "cvwalk" },
	{ 10.0, 0, 0, 3, 0, "spawn_%d",  "cvhtnk" }
};

#define MAXROUNDS	(sizeof(attackRounds) / sizeof(attackRounds[0]))
#define RESTARTROUND		3



struct {
	float wait;
	int   initround;
	int   attackplayer;
	char *spawnpoint;
	char *item;
}
spawnitems[] = 
{
	{ 30.0, 0, 0, "repair",   "aprepaa" },
	{ 30.0, 0, 0, "ammo",		  "apammoa" },
	{ 30.0, 0, 0, "apmini_1", "apmini" },
	{ 30.0, 0, 0, "apmini_2", "apmini" },
	{ 30.0, 0, 0, "apstab_1", "apstab" },
	{ 30.0, 0, 0, "apstab_2", "apstab" },
	{ 30.0, 0, 0, "apsstb_1", "apsstb" },
	{ 30.0, 0, 0, "apsstb_2", "apsstb" },
	{ 30.0, 0, 0, "apflsh_1", "apflsh" },
	{ 30.0, 0, 0, "apflsh_2", "apflsh" },
	{ 30.0, 0, 0, "aptagg_1", "apbolt" },
	{ 30.0, 0, 0, "aptagg_2", "apbolt" },
	{ 30.0, 4, 1, "cover_1",  "csuserb" },
	{ 30.0, 4, 1, "cover_2",  "csuserb" },
	{ 30.0, 4, 1, "cover_3",  "csuserb" },
	{ 30.0, 4, 1, "cover_4",  "csuserb" },
};


#define MAXITEMS	(sizeof(spawnitems) / sizeof(spawnitems[0]))



/*
	EvolveMission
*/

class EvolveMission : public AiMission {
	DECLARE_RTIME(EvolveMission)
public:
	EvolveMission();
	~EvolveMission();

	virtual bool Load(file fp);
	virtual bool PostLoad(void);
	virtual bool Save(file fp);

	void createAttackerRound(void);

	virtual void Update(void);

	virtual void AddObject(GameObject *gameObj);

private:
	void Setup();
	void Execute();
	void AddObject(Handle h);

	// bools
	union {
		struct {
			bool
				// have we lost?
				lost, 
				
				b_last;
		};
		bool b_array[1];
	};

	// floats
	union {
		struct {
			float
				stateTimer,  // timer to say when the next state starts
				itemTimer[MAXITEMS],
				deadTimer,

				f_last;
		};
		float f_array[2 + MAXITEMS];
	};

	// handles
	union {
		struct {
			Handle
				// the user
				user,
				olduser,

				currentAttackers[MAXCURRENTATTACKERS],

				item[MAXITEMS],

				// place holder
				h_last;
		};
		Handle h_array[2 + MAXCURRENTATTACKERS + MAXITEMS];
	};

	// integers
	union {
		struct {
			int
				startup,
				diedAttackers[MAXCURRENTATTACKERS],
				numOfCurrentAttackers,
				score,
				round,
				maxroundattackers,
				invehicle,
				bestscore,
				orgbestscore,
				orgbesttime,

				i_last;
		};
		int i_array[9 + MAXCURRENTATTACKERS];
	};
};

IMPLEMENT_RTIME(EvolveMission)

EvolveMission::EvolveMission()
{
}

EvolveMission::~EvolveMission()
{
}

bool EvolveMission::Load(file fp)
{
	if (missionSave) 
	{
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

bool EvolveMission::PostLoad(void)
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

bool EvolveMission::Save(file fp)
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

void EvolveMission::AddObject(GameObject *gameObj)
{
	AddObject(gameObj->GetHandle());
	AiMission::AddObject(gameObj);
}

void EvolveMission::AddObject(Handle h)
{
}

void EvolveMission::Update(void)
{
	AiMission::Update();
	Execute();
}








void EvolveMission::Setup()
{
	startup = 1;
	numOfCurrentAttackers = 0;


	FILE *bscorefile;

	bestscore = orgbestscore = orgbesttime = 0;

	bscorefile = fopen("emission.bst", "rb");
	if(bscorefile)
	{
		fread(&bestscore, sizeof(bestscore), 1, bscorefile);
		orgbestscore = bestscore;

		fread(&orgbesttime, sizeof(orgbesttime), 1, bscorefile);

		fclose(bscorefile);
	}
}

void EvolveMission::Execute()
{
	int i = 0;

	user = GetPlayerHandle(); //assigns the player a handle every frame

	if(!lost && !IsAlive(user))
	{
		if(deadTimer)
		{
			if(deadTimer < GetTime())
			{
				int currenttime = GetCockpitTimer();
				int bestmin, bestsec, currentmin, currentsec;

				int values[6];

				bestmin = orgbesttime / 60;
				bestsec = orgbesttime % 60;
				currentmin = currenttime / 60;
				currentsec = currenttime % 60;

				if(!CheckCheater(UserProfile.playOption) && (orgbestscore < score || (orgbestscore == score && currenttime < orgbesttime)))
				{
					FILE *bscorefile;

					// save emission.bst file
					bscorefile = fopen("emission.bst", "wb");
					if(bscorefile)
					{
						fwrite(&score, sizeof(score), 1, bscorefile);
						fwrite(&currenttime, sizeof(currenttime), 1, bscorefile);
						fclose(bscorefile);
					}

					values[0] = score;
					values[1] = currentmin;
					values[2] = currentsec;
					values[3] = orgbestscore;
					values[4] = bestmin;
					values[5] = bestsec;

					SucceedMission(GetTime() + 2.0, "sammywin.des", values);
				}
				else
				{
					values[0] = score;
					values[1] = currentmin;
					values[2] = currentsec;
					values[3] = orgbestscore;
					values[4] = bestmin;
					values[5] = bestsec;

					SucceedMission(GetTime() + 2.0, "sammylse.des", values);
				}

				lost = TRUE;
				return;
			}
		}
		else
		{
			deadTimer = GetTime() + 2;
		}
	}
	else if(lost)
	{
		return;
	}
	else
	{
		deadTimer = 0;
	}

	if(startup)
	{
		SetScrap(1,0);
		SetPilot(1,10);

		SetMaxScrap(1, bestscore);

		StartCockpitTimerUp(0);
		olduser = user;

		score = 0;
		startup = 0;

		invehicle = 0;

		round = 0;
		stateTimer = 0;
		maxroundattackers = 1;

		for(i = 0; i < MAXITEMS; i++)
		{
			item[i] = 0;

			if(spawnitems[i].initround <= round)
			{
				itemTimer[i] = 1;
			}
			else
			{
				itemTimer[i] = 0;
			}
		}

		createAttackerRound();
	}
	else if(stateTimer)
	{
		if(stateTimer == 1 && attackRounds[round].invehicleWait)
		{
			if(invehicle)
			{
				stateTimer = GetTime() + attackRounds[round].wait;
			}
		}
		else if(stateTimer < GetTime())
		{
			createAttackerRound();
			stateTimer = 0;
		}
	}
	else
	{
		int alldead = 1;

		if(numOfCurrentAttackers && user != olduser && user != 0)
		{
			for(i = 0; i < numOfCurrentAttackers; i++)
			{
				Attack(currentAttackers[i], user);
			}
		}

		if(user != olduser && user != 0)
		{
			for(i = 0; i < MAXITEMS; i++)
			{
				if(spawnitems[i].attackplayer && item[i] && IsAlive(item[i]))
				{
					Attack(item[i], user);
				}
			}
		}


		for(i = 0; i < numOfCurrentAttackers; i++)
		{
			if(!diedAttackers[i])
			{
				if(!IsAlive(currentAttackers[i]))
				{
					RemoveObject(currentAttackers[i]);

					diedAttackers[i] = 1;
					score++;

					if(score > bestscore)
					{
						bestscore = score;
						SetMaxScrap(1, bestscore);
					}

					SetScrap(1, score);
				}
				else
				{
					alldead = 0;
				}
			}
		}


		for(i = 0; i < MAXITEMS; i++)
		{
			if(spawnitems[i].attackplayer && item[i] && !IsAlive(item[i]))
			{
				RemoveObject(item[i]);
				item[i] = 0;
				score++;

				if(score > bestscore)
				{
					bestscore = score;
					SetMaxScrap(1, bestscore);
				}

				SetScrap(1, score);
			}
		}

		if(alldead)
		{
			round++;
			
			if(round >= MAXROUNDS)
			{
				round = RESTARTROUND;

				if(maxroundattackers < MAXATTACKERSPERSPAWN)
				{
					maxroundattackers++;
				}
			}

			if(attackRounds[round].invehicleWait)
			{
				stateTimer = 1;
			}
			else if(attackRounds[round].wait)
			{
				stateTimer = GetTime() + attackRounds[round].wait;
			}
			else
			{
				createAttackerRound();
			}
		}
	}

	for(i = 0; i < MAXITEMS; i++)
	{
		if(itemTimer[i] == 0)
		{
			if(!item[i] || !IsAlive(item[i]))
			{
				if(spawnitems[i].initround <= round)
				{
					spawnitems[i].initround = 0;
					itemTimer[i] = GetTime() + spawnitems[i].wait;
				}
			}
		}
		else if(itemTimer[i] < GetTime())
		{
			itemTimer[i] = 0;
			item[i] = BuildObject(spawnitems[i].item, spawnitems[i].attackplayer ? 2 : 1, spawnitems[i].spawnpoint);

			if(spawnitems[i].attackplayer)
			{
				Attack(item[i], user);
			}
		}
	}

	bool done = FALSE;

	while(!done)
	{
		ObjectList &list = *GameObject::objectList;

		done = TRUE;

		// remove scrap
		for (ObjectList::iterator oi = list.begin(); oi != list.end(); oi++) 
		{
			GameObject *o = *oi;
			if(memcmp(&o->GetClass()->cfg, "npscr", 5) == 0)
			{
				RemoveObject(GameObjectHandle::Find(o));
				done = FALSE;
				break;
			}
		}
	}

	if(user != olduser)
	{
		olduser = user;
		invehicle = 1;
	}
}



void EvolveMission::createAttackerRound(void)
{
	int i, j, idx, roundmax;
	char buffer[30];

	numOfCurrentAttackers = 0;

	while(1)
	{
		if(attackRounds[round].onlyone)
		{
			roundmax = 1;
		}
		else
		{
			roundmax = maxroundattackers;
		}
		

		for(i = 0, idx = numOfCurrentAttackers; i < attackRounds[round].numunits; i++)
		{
			sprintf(buffer, attackRounds[round].spawnPrefix, i + 1);

			for(j = 0; j < roundmax; j++, idx++)
			{
				diedAttackers[idx] = 0;
				currentAttackers[idx] = BuildObject(attackRounds[round].attacker, 2, buffer);
				Attack(currentAttackers[idx], user);
			}
		}
		
		numOfCurrentAttackers += (attackRounds[round].numunits * roundmax);

		if(attackRounds[round].nowait)
		{
			round++;
		}
		else
		{
			break;
		}
	}
}
