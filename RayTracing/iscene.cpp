/****************************************************
 * 2016-2023 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#include "iscene.h"

/**
 * @fn	void IScene::addOpaqueObject(const VisibleIShapePtr obj)
 * @brief	Adds an visible object to the scene
 * @param	obj	The object to be added.
 */

void IScene::addOpaqueObject(const VisibleIShapePtr obj) {
	opaqueObjs.push_back(obj);
}

/**
 * @fn	void IScene::addTransparentObject(const TransparentIShapePtr obj, double alpha)
 * @brief	Adds a transparent object to the scene
 * @param	obj  	The transparent object to be added.
 */

void IScene::addTransparentObject(const TransparentIShapePtr obj) {
	transparentObjs.push_back(obj);
}

/**
 * @fn	void IScene::addLight(const PositionalLightPtr light)
 * @brief	Adds a positional light to the scene.
 * @param	light	The light to be added.
 */

void IScene::addLight(const LightSourcePtr light) {
	lights.push_back(light);
}
