#ifndef _MultDMMission_
#define _MultDMMission_

#include "LuaMission.h"
#include "AiProcess.h"

class MultDMEvent;
class PathSpawn;

class MultDMMission : public LuaMissionMP {
	DECLARE_RTIME(MultDMMission)
public:
	MultDMMission(void);
	~MultDMMission();
	virtual bool Load(file fp) override;
	virtual bool Save(file fp) override;
	virtual void Respawn(void) override;
	virtual void Init(void) override;
	virtual bool EjectCraftCreate(void) override;
	virtual void SetMostRecentKilled(int killedHandle) override;
	virtual void Update(void) override;
	virtual void AddObject(GameObject *gameObj) override;
	virtual const std::set<std::string>& GetPreloadSet() override;
	virtual const std::set<PrjID>& GetPreloadGameObjects() override;
	MultDMEvent *multEvent;
	PathSpawn *pathSpawn;
	int killed;
	bool recently_killed;
	bool camera;
	AiPath *aipath;
	int height;
	int speed;
	VECTOR_3D pos;
};

#endif
