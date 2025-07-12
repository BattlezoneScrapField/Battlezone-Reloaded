#ifndef _Mult04Mission_
#define _Mult04Mission_

#include "..\fun3d\AiMission.h"
#include "..\fun3d\AiProcess.h"

class Mult04Mission : public AiMission {
	DECLARE_RTIME(Mult04Mission)
public:
	Mult04Mission(void);
	~Mult04Mission();
	bool Load(file fp);
	bool Save(file fp);
	virtual int GetTeam(int team);
	virtual void Respawn(void);
	virtual bool EjectCraftCreate(void);
};



#endif
