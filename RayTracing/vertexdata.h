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
#include "colorandmaterials.h"

 /**
  * @struct	VertexData
  * @brief	A vertex data. Used for Pipeline graphics.
  */

struct VertexData {
	dvec4 pos;			//!< Processed coordinate.
	dvec3 normal;		//!< transformed normal vector.
	dvec3 worldPos;		//!< Saved world position, for lighting calculations.
	Material material;	//!< This vertex's material.

	VertexData(const dvec4& pos, const dvec3& norm,
		const Material& mat, const dvec3& worldPos);
	VertexData(const dvec4& pos) : VertexData(pos, dvec4(0, 0, 1, 0), bronze, ORIGIN3D) {
	}
	VertexData(const dvec4& pos, const dvec3& norm, const Material& mat) :
		VertexData(pos, norm, mat, ORIGIN3D) {
	}
	VertexData(double w1, const VertexData& vd1, double w2, const VertexData& vd2);
	static void addTriVertsAndComputeNormal(vector<VertexData>& verts,
		const dvec4& V1, const dvec4& V2, const dvec4& V3,
		const Material& mat);
	VertexData operator + (const VertexData& other) const;
};

VertexData operator * (double w, const VertexData& V1);
