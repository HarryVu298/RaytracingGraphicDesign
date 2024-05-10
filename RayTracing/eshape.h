/****************************************************
 * 2016-2023 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#pragma once

#include <utility>
#include <iostream>
#include "vertexdata.h"
#include "framebuffer.h"
#include "light.h"

typedef vector<VertexData> EShapeData;

/**
 * @struct	EShape
 * @brief	This class contains functions that create explicitly represented shapes.
 * 			This class is used within pipeline applications. The objects returned by
 * 			these routines are vectors of VertexData, where each successive triplet
 * 			is a triangle.
 */

struct EShape {
	static EShapeData createETriangle(const Material& mat,
		const dvec4& A, const dvec4& B, const dvec4& C);
	static EShapeData createEDisk(const Material& mat, int slices = DEFAULT_SLICES);
	static EShapeData createECylinder(const Material& mat, int slices = DEFAULT_SLICES);
	static EShapeData createECone(const Material& mat, int slices = DEFAULT_SLICES);
	static EShapeData createECheckerBoard(const Material& mat1, const Material& mat2, double WIDTH, double HEIGHT, int DIV);
	static EShapeData createEObj(const string& filename);
};
