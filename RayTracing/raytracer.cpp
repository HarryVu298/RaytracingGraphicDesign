/****************************************************
 * 2016-2023 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/
#include "raytracer.h"
#include "ishape.h"
#include "io.h"

 /**
  * @fn	RayTracer::RayTracer(const color &defa)
  * @brief	Constructs a raytracers.
  * @param	defa	The clear color.
  */

RayTracer::RayTracer(const color& defa)
	: defaultColor(defa) {
}

/**
 * @fn	void RayTracer::raytraceScene(FrameBuffer &frameBuffer, int depth, const IScene &theScene) const
 * @brief	Raytrace scene
 * @param [in,out]	frameBuffer	Framebuffer.
 * @param 		  	depth	   	The current depth of recursion.
 * @param 		  	theScene   	The scene.
 */

void RayTracer::raytraceScene(FrameBuffer& frameBuffer, int depth,
	const IScene& theScene) const {
	const RaytracingCamera& camera = *theScene.camera;
	const vector<VisibleIShapePtr>& objs = theScene.opaqueObjs;
    const vector<TransparentIShapePtr>& transparentObjs = theScene.transparentObjs;
	const vector<LightSourcePtr>& lights = theScene.lights;
	color defaultColor = frameBuffer.getClearColor();

	for (int y = 0; y < frameBuffer.getWindowHeight(); ++y) {
		for (int x = 0; x < frameBuffer.getWindowWidth(); ++x) {
//			DEBUG_PIXEL = (x == xDebug && y == yDebug);
//			if (DEBUG_PIXEL) {
//				cout << "";
//			}
			/* CSE 386 - todo  */
			Ray ray = camera.getRay(x, y);
			OpaqueHitRecord hit;
            VisibleIShape::findIntersection(ray, objs, hit);
            TransparentHitRecord transparentHit;
            TransparentIShape::findIntersection(ray, transparentObjs, transparentHit);
            color Color;
			if (hit.t != FLT_MAX) {
                // Interate through all the lights
                for (int i = 0; i < lights.size(); i++) {
                    // Determine whether the point is in shadow
                    bool pointInShadow = theScene.lights[i]->pointIsInAShadow(hit.interceptPt, hit.normal, objs, camera.getFrame());
                    // Rendering back faces condition
                    if (glm::dot(ray.dir, hit.normal) > 0) {
                        Color += theScene.lights[i]->illuminate(hit.interceptPt, -hit.normal, hit.material, camera.getFrame(), pointInShadow);
                    } else {
                        Color += theScene.lights[i]->illuminate(hit.interceptPt, hit.normal, hit.material, camera.getFrame(), pointInShadow);
                    }
                    
                    if (hit.texture != nullptr) {
                        Color += hit.texture->getPixelUV(hit.u, hit.v);
                        Color *= 0.5;
                    }
                    
                    // Hit transparent object
                    if (transparentHit.t != FLT_MAX && transparentHit.t < hit.t) {
                        Color = (1-transparentHit.alpha) * Color + transparentHit.alpha * transparentHit.transColor;
                    }
                }
            } else if (transparentHit.t != FLT_MAX) {
                Color += (1-transparentHit.alpha)*defaultColor + transparentHit.alpha*transparentHit.transColor;
                
            }
			
            // Reflection
            Ray rayForReflection = Ray(hit.interceptPt + EPSILON * hit.normal, ray.dir - 2 * glm::dot(ray.dir, hit.normal)*hit.normal);
            Color += 0.3*traceIndividualRay(rayForReflection, theScene, depth);
            frameBuffer.setColor(x, y, glm::clamp(Color,0.0,1.0));
            frameBuffer.showAxes(x, y, ray, 0.25);            // Displays R/x, G/y, B/z axes
		}
	}

	frameBuffer.showColorBuffer();
}

/**
 * @fn	color RayTracer::traceIndividualRay(const Ray &ray,
 *											const IScene &theScene,
 *											int recursionLevel) const
 * @brief	Trace an individual ray.
 * @param	ray			  	The ray.
 * @param	theScene	  	The scene.
 * @param	recursionLevel	The recursion level.
 * @return	The color to be displayed as a result of this ray.
 */

color RayTracer::traceIndividualRay(const Ray& ray, const IScene& theScene, int recursionLevel) const {
	/* CSE 386 - todo  */
	// This might be a useful helper function.
    if (recursionLevel == 0) return black;
    const RaytracingCamera& camera = *theScene.camera;
    const vector<VisibleIShapePtr>& objs = theScene.opaqueObjs;
    const vector<TransparentIShapePtr>& transparentObjs = theScene.transparentObjs;
    const vector<LightSourcePtr>& lights = theScene.lights;
    OpaqueHitRecord hit;
    VisibleIShape::findIntersection(ray, objs, hit);
    color Color;
    if (hit.t != FLT_MAX) {
        for (int i = 0; i < lights.size(); i++) {
            bool pointInShadow = theScene.lights[i]->pointIsInAShadow(hit.interceptPt, hit.normal, objs, camera.getFrame());
            // Rendering backface condition
            if (glm::dot(ray.dir, hit.normal) > 0) {
                Color += theScene.lights[i]->illuminate(hit.interceptPt, -hit.normal, hit.material, camera.getFrame(), pointInShadow);
            } else {
                Color += theScene.lights[i]->illuminate(hit.interceptPt, hit.normal, hit.material, camera.getFrame(), pointInShadow);
            }
            
            if (hit.texture != nullptr) {
                Color += hit.texture->getPixelUV(hit.u, hit.v);
                Color *= 0.5;
            }
        }
    } else {
        return black;
    }
    Ray rayForReflection = Ray(hit.interceptPt + EPSILON * hit.normal, ray.dir - 2 * glm::dot(ray.dir, hit.normal)*hit.normal);
    return Color + 0.3 * traceIndividualRay(rayForReflection, theScene, recursionLevel - 1);
}
