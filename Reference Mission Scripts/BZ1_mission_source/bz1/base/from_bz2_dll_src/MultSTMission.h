#ifndef _MultSTMission_
#define _MultSTMission_

#include "..\fun3d\AiMission.h"
#include "..\fun3d\AiProcess.h"

class MultSTMission : public AiMission {
	DECLARE_RTIME(MultSTMission)
public:
	MultSTMission(void);
	~MultSTMission();

	virtual void Init(void);
	bool Load(file fp);
	bool Save(file fp);
	virtual int GetTeam(int team);
	virtual void Respawn(void);
	virtual bool EjectCraftCreate(void);
	virtual void SetMostRecentKilled(int killedHandle);
	virtual void Update(void);
	int killed;
	bool recently_killed;
	bool camera;
	AiPath *aipath;
	int height;
	int speed;
	VECTOR_3D pos;
};

#endif