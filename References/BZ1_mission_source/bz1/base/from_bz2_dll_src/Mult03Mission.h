#ifndef _Mult03Mission_
#define _Mult03Mission_

#include "..\fun3d\AiMission.h"
#include "..\fun3d\AiProcess.h"

class Mult03Mission : public AiMission {
	DECLARE_RTIME(Mult03Mission)
public:
	Mult03Mission(void);
	~Mult03Mission();

	bool Load(file fp);
	bool Save(file fp);
	virtual int GetTeam(int team);
	virtual void Respawn(void);
	virtual void Init(void);
	virtual bool EjectCraftCreate(void);
};

#endif