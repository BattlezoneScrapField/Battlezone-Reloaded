#include "GameCommon.h"

extern "C" {
#include "views.h"
#include "ZSorting.h"
#include "sprites.h"
}

#include "PortalBlob.h"
#include "FunUtils.h"

using namespace std;

// the "stock" luma level
extern "C" float TerrainIntensity;

// instance of portal blob
PortalBlob portalBlob;

//
// PORTAL BLOB INITIALIZATION
//
void PortalBlob::PreLoad(void)
{
	// open parameter odf
	ParameterDB p("portblob.odf");

	// get blob sprite index
	char spriteName[16];
	p.Get("blobInTexture",  spriteName,   "rpuff.0");
	blobInTexture = GetSpriteIndex(spriteName);
	p.Get("blobOutTexture",  spriteName,   "bpuff.0");
	blobOutTexture = GetSpriteIndex(spriteName);

	// get number of animation frames
	p.Get("blobFrames",   &blobFrames,   14);

	// get number of variance frames
	p.Get("blobVariance", &blobVariance, 3);

	// initialize state
	blobIndex = 0;
	blobPtr = blobList;
}



//
// ADD A BLOB TO THE BLOB LIST
//
void PortalBlob::AddBlob(SPHERE &sphere, float scale, bool in)
{
	scale = min<float>(1.0, scale);
	scale = max<float>(0.0, scale);
	if ((blobInTexture > 0) &&
		(blobOutTexture > 0) &&
		(View_Record.Current_View != TWO_D_VIEW) &&
		(View_Record.Current_View != EDIT_VIEW) &&
		(ResolutionMode > 0))
	{
		if (blobPtr < &blobList[SIZEOF(blobList)])
		{
			blobPtr->sphere = sphere;
			blobPtr->scale = scale;
			blobPtr->in = in;
			blobPtr++;
		}
#ifdef _DEBUG
		else
		{
			Trace("Portal blob list overflow\n");
		}
#endif
	}
}



//
// SUBMIT ALL PORTAL BLOBS
//
void PortalBlob::Submit(CAMERA *camera)
{
	// round down
	long rounding = Set_Rounding(Round_Down);

	// advance the offset index
	blobIndex++;
	if (blobIndex >= blobVariance)
		blobIndex = 0;
	
	// draw all active blobs
	for (Blob *blob = blobList; blob < blobPtr; blob++)
	{
		// get the blob's sphere
		SPHERE sphere = blob->sphere;

		// convert blob into camera coordinates
		Vector_Transform(&sphere.origin, &sphere.origin, 1, &camera->Matrix);
		
		// if the blob is visible...
		if (Camera_Bounding_Sphere_Test (camera, &sphere.origin, sphere.radius) <= 0)
		{
			// calculate frame to draw
			FLOAT2INT blobFrame;
			blobFrame.f = blob->scale * blobFrames + Float2Int;
			blobFrame.i += (blob->in ? blobInTexture : blobOutTexture) + blobIndex;

			// generate the sprite polygon
			LPZSORTING renderObj = ZSORTBorrow();
			renderObj->Type = SPRITE_POLY;
			renderObj->vcnt = 0;
			renderObj->Skin_Color.Color = blobFrame.i;
			renderObj->Bitmap_Operation = ALPHA_PIXELS | CENTER_JUSTIFY;
			
			SPRITE_POLY_ENTITY *sprite = (SPRITE_POLY_ENTITY *)renderObj->Vertex;
			float iz = 1.0f / sphere.origin.z;
			sprite->x = camera->Orig_x + camera->Const_x * sphere.origin.x * iz;
			sprite->y = camera->Orig_y + camera->Const_y * sphere.origin.y * iz;
			sprite->z = sphere.origin.z;
			sprite->dx = 2.0f * camera->Const_x * sphere.radius * iz;
			sprite->dy = -2.0f * camera->Const_y * sphere.radius * iz;
			sprite->worldOrigin = sphere.origin;
			sprite->worldRadius = sphere.radius;

			renderObj->Z_Value = sphere.origin.z - sphere.radius;
			ZSORTAdd(renderObj->Z_Value);
		}
	}

	
	// reset blob pointer
	//blobPtr = blobList;  // done in Reset

	// restore rounding
	Set_Rounding(rounding);
}

void PortalBlob::Reset()
{
	// reset blob pointer
	blobPtr = blobList;
}