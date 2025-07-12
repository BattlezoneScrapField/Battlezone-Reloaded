#ifndef _Mult01Mission_
#define _Mult01Mission_

#include "..\fun3d\AiMission.h"
#include "..\fun3d\AiProcess.h"

class Mult01Mission : public AiMission {
	DECLARE_RTIME(Mult01Mission)
public:
	Mult01Mission(void);
	~Mult01Mission();
	bool Load(file fp);
	bool Save(file fp);
	virtual int GetTeam(int team);
	virtual void Respawn(void);
	virtual void Init(void);
	virtual bool EjectCraftCreate(void);
};



#endif
