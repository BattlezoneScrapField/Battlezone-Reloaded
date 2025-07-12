#ifndef _Inst01Mission_
#define _Inst01Mission_


#include "AiMission.h"
#include "AiProcess.h"

class Inst01Mission : public AiMission {
	DECLARE_RTIME(Inst01Mission)
public:
	Inst01Mission(void);
	~Inst01Mission();
	virtual bool Load(file fp) override;
	virtual bool Save(file fp) override;
	virtual const std::set<std::string>& GetPreloadSet() override;

};



#endif
