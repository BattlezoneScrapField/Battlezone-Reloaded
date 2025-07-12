#include "GameCommon.h"

#include "Portal.h"
#include "PortalClass.h"
#include "PortalBlob.h"

#include "ControlPanel.h"
#include "BettyVoice.h"


// ==========
// PORTAL
// ==========

//
// PORTAL CONSTRUCTOR
//
Portal::Portal(OBJ76 *obj, PortalClass *proto)
: Building(obj, proto)
{
	activationTime = proto->activationTime;
	portalState = DEACTIVATED;
	beginTime = 0.0;
	endTime = 0.0;
	isIn = FALSE;
	soundActivate = NULL;
}

//
// PORTAL DESTRUCTOR
//
Portal::~Portal()
{
}

//
// PORTAL INITIALIZATION
//
void Portal::Init(int team)
{
	// call parent initialization
	Building::Init(team);
}

//
// PORTAL CLEANUP
//
void Portal::Cleanup(void)
{
	// call parent cleanup
	Building::Cleanup();
}


//
// PORTAL SIMULATION
//
void Portal::Simulate(float dt)
{
	_ASSERTE(activationTime > 0.0);
	bool on = false;
	float ratio = 1.0;

	// do our portal blob
	switch (portalState)
	{
	case DEACTIVATED:
		break;
	case ACTIVATING:
		{
		on = true;
		if (endTime < Get_Time())
		{
			portalState = ACTIVATED;
			ratio = 0.0;
		}
		else
		{
			float diff = endTime - Get_Time();
			ratio = diff / activationTime;
		}
		break;
		}
	case ACTIVATED:
		on = true;
		ratio = 0.0f;
		break;
	case DEACTIVATING:
		{
		if (endTime < Get_Time())
		{
			portalState = DEACTIVATED;
			//ratio = 1.0;
		}
		else
		{
			on = true;
			float diff = Get_Time() - beginTime;
			ratio = diff / activationTime;
		}

		break;
		}
	default:
		_DEBUGMSG0("Invalid portalState");
		break;
	}

	// if we want this on, then turn it on
	if (on)
	{
		SPHERE sphere = GetSphere();
		Vector_Transform(&sphere.origin, &sphere.origin, 1, &GetTransform());	
		// slamp ratio to [0.0, 1.0]
		ratio = max<float>(ratio, 0.0);
		ratio = min<float>(ratio, 1.0);
		portalBlob.AddBlob(sphere, ratio, isIn);
	}

	// call parent simulation
	Building::Simulate(dt);
}

bool Portal::Load(file fp)
{
	bool ret = true;

	if (version < 2004)
	{
		ret = ret && Building::Load(fp);
		return ret;
	}

	ret = ret && in(fp, &portalState, sizeof(portalState));
	ret = ret && in(fp, &beginTime, sizeof(beginTime));
	ret = ret && in(fp, &endTime, sizeof(endTime));
	ret = ret && in(fp, &isIn, sizeof(isIn));

	ret = ret && Building::Load(fp);
	return ret;
}

bool Portal::Save(file fp)
{
	bool ret = true;

	ret = ret && out(fp, &portalState, sizeof(portalState), "portalState");
	ret = ret && out(fp, &beginTime, sizeof(beginTime), "portalBeginTime");
	ret = ret && out(fp, &endTime, sizeof(endTime), "portalEndTime");
	ret = ret && out(fp, &isIn, sizeof(isIn), "isIn");
	
	ret = ret && Building::Save(fp);
	return ret;
}

void Portal::activate(bool in)
{
	isIn = in;
	if (portalState == ACTIVATED ||
		portalState == ACTIVATING)
		return;

	// are we deactivating?
	if (portalState == DEACTIVATING)
	{
		// get the elapsed time already
		float diff = endTime - Get_Time();
		beginTime = Get_Time() - diff;
		endTime = beginTime + activationTime;
		portalState = ACTIVATING;
	}
	else /* if (portalState == DEACTIVE) */
	{
		beginTime = Get_Time();
		endTime = beginTime + activationTime;
		portalState = ACTIVATING;

		// start the sound
		PortalClass *pClass = (PortalClass*)objClass;

		if (pClass->soundActivate[0] != '\0')
		{
			GAS_CTRL gc;
			InitGASCtrl(&gc);
			gc.flags = (GAS_CAT_EXPLOSION << GCFT_CATEGORY0);
			//gc.flags = GCF_SAVE_ON_PAUSE;
			GAS_PREP_INFO gpi;
			InitGASPrep(&gpi);
			//gpi.loopMode = GAS_LOOP_UNTIL_STOP;
			gpi.pri = GAS_PRI_NORM;
			StartGASEvent(pClass->soundActivate, obj, &gc, &gpi);
		}
	}
}

void Portal::deactivate()
{
	if (portalState == DEACTIVATED ||
		portalState == DEACTIVATING)
		return;

	// are we activating?
	if (portalState == ACTIVATING)
	{
		// get the elapsed time already
		float diff = endTime - Get_Time();
		beginTime = Get_Time() - diff;
		endTime = beginTime + activationTime;
		portalState = DEACTIVATING;
	}
	else /* if (portalState == ACTIVE) */
	{
		beginTime = Get_Time();
		endTime = beginTime + activationTime;
		portalState = DEACTIVATING;
	}
}