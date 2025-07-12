#include "GameCommon.h"
#include "..\fun3d\Mult02Mission.h"
#include "..\fun3d\Net.h"
#include "..\fun3d\NetPlayers.h"
#include "..\fun3d\SpawnPoint.h"
#include "..\fun3d\UserProcess.h"

#include "..\gamelgc\running.h"

static class Mult02MissionClass : AiMissionClass {
public:
	Mult02MissionClass(char *name) : AiMissionClass(name)
	{
	}
	int Matches(char *matches)
	{
		if (strcmp(matches, name) == 0)
			return TRUE;
		if (strncmp(matches, "mult02", 6) == 0)
			return TRUE;
		return FALSE;
	}
	AiMission *Build(void)
	{
		return new Mult02Mission;
	}
} Mult02MissionClass("mult02");

IMPLEMENT_RTIME(Mult02Mission)

Mult02Mission::Mult02Mission(void)
{
}

void Mult02Mission::Init(void)
{
	_ASSERTE(theNet);

	Net::SetDeathMatch(false);

	GameObjectClass *gameObjectClass;
	PrjID config = 0;

	memcpy((char *) &config, Net::odfName, strlen(Net::odfName));
	
	gameObjectClass = GameObjectClass::Find(config);
	_ASSERTE(gameObjectClass);

	if (Net::GetHosting())
	{
		// We are hosting so give yourself a spawn point.
		SpawnPoint *spawnPoint = SpawnPoint::GetSafest();
		_ASSERTE(spawnPoint);
		
		theNet->SetStartLocation(spawnPoint->GetLocation());
		NetPlayer *netPlayer = NetPlayer::Find(theNet->GetMyPlayerID());
		_ASSERTE(netPlayer);
		netPlayer->SetWaitingForSpawnPoint(false);
	}
	MAT_3D mat = Identity_Matrix;
	mat.posit = theNet->GetStartLocation();;

	GameObject *gameObject = gameObjectClass->Build(mat,Net::Team, true);
//	GameObject *gameObject = gameObjectClass->Build(mat,1, true);
	gameObject->SetLocal();

//	SetupUserProcess(gameObject->GetOBJ76());

	new UserProcess(this, gameObject);

	config = 0;
	if (Net::odfName[0] == 'a')
		memcpy((char *) &config, "avrecy", 6);
	else
		memcpy((char *) &config, "svrecy", 6);
	
	gameObjectClass = GameObjectClass::Find(config);
	_ASSERTE(gameObjectClass);
	
	mat.posit.x += 50.0f;
	mat.posit.z += 50.0f;
	mat.posit.y = Terrain_FindFloor(mat.posit.x, mat.posit.z) + 2.0f;
	
	gameObject = gameObjectClass->Build(mat, Net::Team, false);
//	gameObject = gameObjectClass->Build(mat, 1, false);
	_ASSERTE(gameObject);
	gameObject->GetTeamList()->AddScrap(20);
	gameObject->SetLocal();
//	gameObject->hasPilot = true;

	this->AddObject(gameObject);
}

Mult02Mission::~Mult02Mission()
{
}

bool Mult02Mission::Load(file fp)
{
	return AiMission::Load(fp);
}

bool Mult02Mission::Save(file fp)
{
	return AiMission::Save(fp);
}

int Mult02Mission::GetTeam(int team)
{
	return team;
}

void Mult02Mission::Respawn(void)
{
	SetRunning(RUN_WAS_FAILURE);
	/*
	_ASSERTE(theNet);
	GameObjectClass *gameObjectClass;
	PrjID config = 0;
	memcpy((char *) &config, Net::odfName, strlen(Net::odfName));
	gameObjectClass = GameObjectClass::Find(config);
	_ASSERTE(gameObjectClass);
	VECTOR_3D pos = theNet->GetStartLocation();
	MAT_3D mat = Identity_Matrix;
	mat.posit_x = pos.x;
	mat.posit_y = pos.y;
	mat.posit_z = pos.z;
	GameObject *gameObject = gameObjectClass->Build(mat, Net::Team, true);
	gameObject->SetLocal();
	new UserProcess(this, gameObject);
	*/
}

bool Mult02Mission::EjectCraftCreate(void)
{
	return false;
}