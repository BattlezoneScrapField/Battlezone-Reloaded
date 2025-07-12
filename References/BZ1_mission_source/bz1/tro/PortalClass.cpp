#include "GameCommon.h"

#include "Portal.h"
#include "PortalClass.h"


// prototype portal class
PortalClass portalClass;


// ================
// PORTAL CLASS
// ================

//
// PORTAL CLASS PROTOTYPE CONSTRUCTOR
//
PortalClass::PortalClass(void)
: BuildingClass()
{
	sig = CLASS_PORTAL;
	label = "portal";
	categoryMin = TEAM_SLOT_MIN_PORTAL;
	categoryMax = TEAM_SLOT_MAX_PORTAL;
	activationTime = 1.0;
	soundActivate[0] = '\0';
}

//
// PORTAL CLASS INSTANCE CONSTRUCTOR
//
PortalClass::PortalClass(PortalClass *proto, PrjID config)
: BuildingClass(proto, config)
{
	ParameterDB p(odf);
	p.Get("activationTime",  &activationTime,  proto->activationTime);
	p.Get("soundActivate", soundActivate, proto->soundActivate);
}

//
// PORTAL CLASS DESTRUCTOR
//
PortalClass::~PortalClass()
{
}

//
// BUILD A NEW PORTAL CLASS
//
GameObjectClass *PortalClass::BuildClass(PrjID config)
{
	return new PortalClass(this, config);
}

//
// BUILD A NEW PORTAL
//
GameObject *PortalClass::Build(OBJ76 *obj)
{
	return new Portal(obj, this);
}


