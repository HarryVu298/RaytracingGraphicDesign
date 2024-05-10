/****************************************************
 * 2016-2023 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#pragma once
#include <vector>
#include <map>
#include "defs.h"
#include "light.h"
#include "camera.h"
#include "light.h"
#include "eshape.h"
#include "ishape.h"

 /**
  * @struct	IScene
  * @brief	Represents an scene of implicitly represented objects. Used mostly in ray tracing.
  */

struct IScene {
	vector<LightSourcePtr> lights;				//!< All the lights in the scene
	vector<VisibleIShapePtr> opaqueObjs;			//!< All the visible objects in the scene
	vector<TransparentIShapePtr> transparentObjs;	//!< All the transparent objects in the scene
	RaytracingCamera* camera;						//!< The one camera in the scene
	void addOpaqueObject(const VisibleIShapePtr obj);
	void addTransparentObject(const TransparentIShapePtr obj);
	void addLight(const LightSourcePtr light);
};
