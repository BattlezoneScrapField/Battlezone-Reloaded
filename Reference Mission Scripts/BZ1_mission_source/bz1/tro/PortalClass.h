#ifndef __PORTALCLASS_H
#define __PORTALCLASS_H

#include "BuildingClass.h"

// portal metaclass definition
class PortalClass : public BuildingClass
{
public:
	PortalClass(void);
	PortalClass(PortalClass *proto, PrjID config);
	~PortalClass();
	GameObject *Build(OBJ76 *obj);
	GameObjectClass *BuildClass(PrjID config);

public:

	float activationTime;
	char soundActivate[16];
};

#endif
