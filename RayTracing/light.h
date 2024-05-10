/****************************************************
 * 2016-2023 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#pragma once
#include <iostream>
#include <vector>
#include "defs.h"
#include "hitrecord.h"
#include "ishape.h"

 /**
  * @struct	LightATParams
  * @brief	A light attenuation parameters.
  */

struct LightATParams {
	double constant, linear, quadratic;	//!< Parameters controlling attenuation.
	LightATParams(double C, double L, double Q) {
		constant = C;
		linear = L;
		quadratic = Q;
	}
	LightATParams(const LightATParams &params) {
		constant = params.constant;
		linear = params.linear;
		quadratic = params.quadratic;
	}
	double factor(double distance) const {
		return 1.0 / (constant + linear * distance + quadratic * distance * distance);
	}
};


color ambientColor(const color& matAmbient, const color& lightColor);
color diffuseColor(const color& matDiffuse, const color& lightColor,
	const dvec3& l, const dvec3& n);
color specularColor(const color& mat, const color& lightColor,
	double shininess,
	const dvec3& r, const dvec3& v);
color totalColor(const Material& mat, const color& lightColor,
	const dvec3& v, const dvec3& n,
	const dvec3& lightPos, const dvec3& intersectionPt,
	bool attenuationOn,
	const LightATParams& ATparams);

/**
 * @struct	LightSource
 * @brief	A generic light source.
 */

struct LightSource {
	bool isOn;			//!< True if the light is active; otherwise, has no effect.
	color lightColor;	//!< The color of this light
	LightSource(color C = white) {
		isOn = true;
		lightColor = C;
	}
	virtual color illuminate(const dvec3& interceptWorldCoords,
		const dvec3& normal,
		const Material& material,
		const Frame& eyeFrame,
		bool inShadow) const = 0;
	virtual Ray getShadowFeeler(const dvec3& interceptWorldCoords,
		const dvec3& normal,
		const Frame& eyeFrame) const = 0;
	virtual bool pointIsInAShadow(const dvec3& intercept,
		const dvec3& normal,
		const vector<VisibleIShapePtr>& objects,
		const Frame& eyeFrame) const = 0;
};

/**
 * @struct	PositionalLight
 * @brief	Represents a simple positional light source.
 */

struct PositionalLight : public LightSource {
	dvec3 pos;					//!< The position of the light.
	bool attenuationIsTurnedOn;	//!< true if attenuation is active.
	bool isTiedToWorld;			//!< true if the position is in world (or eye) coordinates.
	LightATParams atParams;

	PositionalLight(const dvec3& position, const color& C = white)
		: LightSource(C), pos(position), atParams(0.0, 1.0, 0.0) {
		attenuationIsTurnedOn = false;
		isTiedToWorld = true;
	}
	PositionalLight(const dvec3& position, const LightATParams& at, const color& C = white)
		: LightSource(C), pos(position), atParams(at) {
		attenuationIsTurnedOn = false;
		isTiedToWorld = true;
	}
	dvec3 actualPosition(const Frame& eyeFrame) const;
	virtual color illuminate(const dvec3& interceptWorldCoords,
		const dvec3& normal,
		const Material& material,
		const Frame& eyeFrame,
		bool inShadow)  const;
	virtual Ray getShadowFeeler(const dvec3& interceptWorldCoords,
		const dvec3& normal,
		const Frame& eyeFrame) const;
	virtual bool pointIsInAShadow(const dvec3& intercept, 
		const dvec3& normal, 
		const vector<VisibleIShapePtr>& objects,
		const Frame& eyeFrame) const;
};

/**
 * @struct	SpotLight
 * @brief	A spot light.
 */

struct SpotLight : public PositionalLight {
	double fov;				//!< Field of view of the light.
	dvec3 spotDir;			//!< Direction of spotlight.
	SpotLight(const dvec3& position, const dvec3& dir,
		double angleInRadians, const color& lightColor = white)
		: PositionalLight(position, lightColor), spotDir(dir),
		fov(angleInRadians) {
	}
	virtual color illuminate(const dvec3& interceptWorldCoords,
		const dvec3& normal,
		const Material& material,
		const Frame& eyeFrame,
		bool inShadow) const;
	static bool isInSpotlightCone(const dvec3& spotPos,
									const dvec3& spotDir,
									double spotFOV,
									const dvec3& intercept);
	void setDir(double dx, double dy, double dz);
};

typedef LightSource* LightSourcePtr;
typedef PositionalLight* PositionalLightPtr;
typedef SpotLight* SpotLightPtr;
