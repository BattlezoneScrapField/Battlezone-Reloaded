#ifndef __PORTALBLOB_H
#define __PORTALBLOB_H

#include "GameFeature.h"
#include <Vector>

class PortalBlob : public GameFeature
{
public:
	void PreLoad(void);
	void AddBlob(SPHERE &sphere, float scale, bool in);
	virtual void Submit(CAMERA *camera);
	virtual void Reset();

protected:

	struct Blob
	{
		SPHERE sphere;
		float scale;
		bool in;
	};

	Blob blobList[16];
	Blob *blobPtr;
	long blobInTexture;
	long blobOutTexture;
	long blobIndex;
	long blobFrames;
	long blobVariance;
};

extern PortalBlob portalBlob;

#endif