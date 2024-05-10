/****************************************************
 * 2016-2023 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#pragma once

#include "utilities.h"
#include "framebuffer.h"
#include "camera.h"
#include "iscene.h"

 /**
  * @struct	RayTracer
  * @brief	Encapsulates the functionality of a ray tracer.
  */

struct RayTracer {
	color defaultColor;			//!< the color to use if no intersection is present.
	RayTracer(const color& defaultColor);
	void raytraceScene(FrameBuffer& frameBuffer, int depth,
		const IScene& theScene) const;
protected:
	color traceIndividualRay(const Ray& ray, const IScene& theScene, int recursionLevel) const;
};