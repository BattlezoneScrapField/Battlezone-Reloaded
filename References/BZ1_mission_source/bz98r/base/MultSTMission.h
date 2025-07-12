#ifndef _MultSTMission_
#define _MultSTMission_

#include "LuaMission.h"
#include "AiProcess.h"

class PathSpawn;

class MultSTMission : public LuaMissionMP {
	DECLARE_RTIME(MultSTMission)
public:
	MultSTMission(void);
	~MultSTMission();

	virtual void Init(void) override;
	virtual bool Load(file fp) override;
	virtual bool Save(file fp) override;
	virtual void Respawn(void) override;
	virtual bool EjectCraftCreate(void) override;
	virtual void SetMostRecentKilled(int killedHandle) override;
	virtual void Update(void) override;
	virtual const std::set<std::string>& GetPreloadSet() override;
	virtual const std::set<PrjID>& GetPreloadGameObjects() override;
	PathSpawn *pathSpawn;
	int killed;
	bool recently_killed;
	bool camera;
	AiPath *aipath;
	int height;
	int speed;
	VECTOR_3D pos;
	uint32_t dwLastTime;
};

#endif
