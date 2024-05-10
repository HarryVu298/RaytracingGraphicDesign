/****************************************************
 * 2016-2023 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#pragma once

#include "defs.h"
#include "framebuffer.h"
#include "light.h"
#include "vertexdata.h"
#include "iscene.h"
#include "rasterization.h"

 /**
  * @class	PipelineMatrices
  * @brief	Class to encapsulate the final three matrices used in the graphics pipeline.
  */

struct PipelineMatrices {
	dmat4 viewingMatrix;
	dmat4 projectionMatrix;
	dmat4 viewportMatrix;
};

/**
 * @class	VertexOps
 * @brief	Class to encapsulate the methods related to vertex processing for Pipeline graphics.
 */

class VertexOps {
public:
	static vector<IPlane> allButNearNDCPlanes;		//!< 5 of the 6 planes of the 2x2x2 cube.

	static void processTriangleVertices(FrameBuffer& frameBuffer, const dvec3& eyePos,
		const vector<LightSourcePtr>& lights,
		const vector<VertexData>& objectCoords,
		const dmat4& modelingMatrix,
		const PipelineMatrices& pipeMats,
		bool renderBackfaces);
	static void processLineSegments(FrameBuffer& frameBuffer, const dvec3& eyePos,
		const vector<LightSourcePtr>& lights,
		const vector<VertexData>& objectCoords,
		const dmat4& modelingMatrix,
		const PipelineMatrices& pipeMats);
	static void render(FrameBuffer& frameBuffer, const vector<VertexData>& verts,
		const vector<LightSourcePtr>& lights,
		const dmat4& modelingMatrix,
		const PipelineMatrices& pipeMats,
		bool renderBackfaces
	);
	static dmat4 getViewportTransformation(int left, int width, int bottom, int height);
protected:
	static vector<VertexData> clipAgainstPlane(vector<VertexData>& verts, const IPlane& plane);
	static vector<VertexData> clipPolygon(const vector<VertexData>& clipCoords,
		const vector<IPlane>& planes);
	static vector<VertexData> clipLineSegments(const vector<VertexData>& clipCoords,
		const vector<IPlane>& planes);
	static vector<VertexData> processBackwardFacingTriangles(const vector<VertexData>& triangleVerts,
		bool renderBackfaces);
	static vector<VertexData> transformVerticesToWorldCoordinates(const dmat4& modelMatrix,
		const vector<VertexData>& vertices);
	static vector<VertexData> transformVertices(const dmat4& TM, const vector<VertexData>& vertices);
};
