#ifndef _Inst01Mission_
#define _Inst01Mission_


#include "..\fun3d\AiMission.h"
#include "..\fun3d\AiProcess.h"

class Inst01Mission : public AiMission {
	DECLARE_RTIME(Inst01Mission)
public:
	Inst01Mission(void);
	~Inst01Mission();
	bool Load(file fp);
	bool Save(file fp);

private:
		bool intro_message;  // escort the recycler to ..
		bool build_message;  // now build a wingman
		bool train_message;  // as a training exercise..
		bool attack_message;  // I'm being attacked
		bool save_message;  // get the recycler back to base

};



#endif
