/****************************************************
 * 2016-2023 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#pragma once
#include "framebuffer.h"
#include "light.h"

 /**
  * @enum	fogType
  * @brief	Represents the different types of fog processing.
  */

enum class FogType { NO_FOG, LINEAR_FOG, EXPONENTIAL_FOG, EXPONENTIAL_2_FOG };

/**
 * @struct	FogParams
 * @brief	A fog parameters.
 */

struct FogParams {
	double start, end, density;
	FogType type;
	color color;
	FogParams() {
		start = 0.0;
		end = 1.0;
		density = 1.0;
		type = FogType::NO_FOG;
	}
	double fogFactor(const dvec3& fragPos, const dvec3& eyePos) const;
};

/**
 * @struct	Fragment
 * @brief	Represents the information relevant to a single fragment. Think
 * 			of a fragment as a pixel competing to get into the framebuffer.
 */

struct Fragment {
	dvec3 windowPos;	//!< (x, y) is window coordinate. z is depth.
	Material material;	//!< Material to use
	dvec3 worldNormal;	//!< Transformed normal vector from early in pipeline
	dvec3 worldPos;		//!< Saved position from early in the pipeline
};

/**
 * @class	FragmentOps
 * @brief	Class to encapsulate the methods related to fragment processing.
 */

class FragmentOps {
public:
	static bool performDepthTest;		//!< True ==> use depth buffer. Typically true
	static bool readonlyDepthBuffer;	//!< True ==> rendering will not affect depth buffer. Typically false
	static bool readonlyColorBuffer;	//!< True ==> rendering will not affect color buffer. Typically false
	static FogParams fogParams;			//!< Parameters controlling fog effects.
	static void processFragment(FrameBuffer& frameBuffer, const dvec3& eyePositionInWorldCoords,
		const vector<LightSourcePtr> lights,
		const Fragment& fragment,
		const Frame& eyeFrame);
protected:
	static color applyFog(const color& destColor,
		const dvec3& eyePos, const dvec3& fragPos);
	static color applyBlending(double alpha, const color& src, const color& dest);
	static color applyLighting(const Fragment& fragment,
		const dvec3& eyePositionInWorldCoords,
		const vector<LightSourcePtr>& lights,
		const Frame& eyeFrame);
};
