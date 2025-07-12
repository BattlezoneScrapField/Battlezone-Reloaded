#ifndef __PORTAL_H
#define __PORTAL_H

#include "Building.h"

// definitions
#define CLASS_PORTAL 'PORT'

// forward declarations
class PortalClass;

// comm tower class definition
class Portal : public Building
{
public:
	Portal(OBJ76 *obj, PortalClass *proto);
	~Portal();
	void Init(int team);
	void Cleanup(void);
	void Simulate(float dt);

	// load and save
	virtual bool Load(file fp);
	virtual bool Save(file fp);

	// start and stop the portal
	void activate(bool in);
	void deactivate();
	bool isActive()
	{ 
		return (portalState == ACTIVATED);
	}

protected:
	float activationTime;
	float beginTime;
	float endTime;
	enum PortalState { DEACTIVATED = 0, ACTIVATING, ACTIVATED, DEACTIVATING };
	int portalState;
	bool isIn;
	GAS_OBJECT *soundActivate;
protected:
};

#endif
