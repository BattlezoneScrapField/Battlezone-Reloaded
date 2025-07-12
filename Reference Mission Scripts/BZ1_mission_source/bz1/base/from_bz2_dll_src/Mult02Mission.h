#ifndef _Mult02Mission_
#define _Mult02Mission_

#include "..\fun3d\AiMission.h"
#include "..\fun3d\AiProcess.h"

class Mult02Mission : public AiMission {
	DECLARE_RTIME(Mult02Mission)
public:
	Mult02Mission(void);
	~Mult02Mission();

//	virtual void Update(void);

	bool Load(file fp);
	bool Save(file fp);
	virtual int GetTeam(int team);
	virtual void Respawn(void);
	virtual void Init(void);
	virtual bool EjectCraftCreate(void);
};

#endif