#ifndef _Inst02Mission_
#define _Inst02Mission_


#include "AiMission.h"
#include "AiProcess.h"

class Inst02Mission : public AiMission {
	DECLARE_RTIME(Inst02Mission)
public:
	Inst02Mission(void);
	~Inst02Mission();
	virtual bool Load(file fp) override;
	virtual bool Save(file fp) override;
	virtual const std::set<std::string>& GetPreloadSet() override;

};



#endif
