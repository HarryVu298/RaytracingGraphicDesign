/****************************************************
 * 2016-2023 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#include "vertexdata.h"
#include "utilities.h"
#include "ishape.h"

 /**
  * @fn	VertexData::VertexData(const dvec4 &P, const dvec4 &norm,
								 const Material &mat, const dvec3 &WP)
  * @brief	Constructor
  * @param	P			Current coordinate.
  * @param	norm		Normal vector
  * @param	mat			Material
  * @param	WP			World position.
  */

VertexData::VertexData(const dvec4& P,
	const dvec3& norm,
	const Material& mat,
	const dvec3& WP) :
	pos(P), normal(glm::normalize(norm)), material(mat), worldPos(WP) {
}

/**
 * @fn	VertexData::VertexData(double w1, const VertexData &vd1, double w2, const VertexData &vd2)
 * @brief	Constructs object using weighted average of two VertexData objects.
 * @param	w1 	Weight #1.
 * @param	vd1	VertexData #1.
 * @param	w2 	Weight #2.
 * @param	vd2	VertexData #2.
 */

VertexData::VertexData(double w1, const VertexData& vd1,
	double w2, const VertexData& vd2)
	: pos(weightedAverage(w1, vd1.pos, w2, vd2.pos)),
	normal(weightedAverage(w1, vd1.normal, w2, vd2.normal)),
	material(weightedAverage(w1, vd1.material, w2, vd2.material)),
	worldPos(weightedAverage(w1, vd1.worldPos, w2, vd2.worldPos)) {
}

/**
 * @fn	void VertexData::addTriVertsAndComputeNormal(vector<VertexData> &verts,
 *													const dvec4 &V1, const dvec4 &V2, const dvec4 &V3,
 *													const Material &mat)
 * @brief	Adds a triangle vertices and computes normal, adding vertices to end of verts.
 *          Vertices are specified in counterclockwise order.
 * @param [in,out]	verts	The vector of vertices.
 * @param 		  	V1   	The first vertice
 * @param 		  	V2   	The second vertice.
 * @param 		  	V3   	The third vertice.
 * @param 		  	mat  	Material.
 */

void VertexData::addTriVertsAndComputeNormal(vector<VertexData>& verts,
	const dvec4& V1,
	const dvec4& V2,
	const dvec4& V3,
	const Material& mat) {
	dvec3 n = normalFrom3Points(V1.xyz(), V2.xyz(), V3.xyz());
	dvec4 nHomogenous(n.x, n.y, n.z, 0);
	verts.push_back(VertexData(V1, nHomogenous, mat));
	verts.push_back(VertexData(V2, nHomogenous, mat));
	verts.push_back(VertexData(V3, nHomogenous, mat));
}

/**
 * @fn	VertexData operator* (double w, const VertexData &data)
 * @brief	Multiplication operator for VertexData objects
 * @param	w   	The scalar multiplier.
 * @param	data	Vertex data to scale.
 * @return	The scaled Vertex data.
 */

VertexData operator * (double w, const VertexData& data) {
	VertexData result(w * data.pos, w * data.normal, w * data.material, w * data.worldPos);
	return result;
}

/**
 * @fn	VertexData VertexData::operator+ (const VertexData &other) const
 * @brief	Addition operator for VertexData objects
 * @param	other	The 2nd VertexData object.
 * @return	The raw summation of the two VertexData objects
 */

VertexData VertexData::operator + (const VertexData& other) const {
	VertexData result(*this);
	result.material += other.material;
	result.normal += other.normal;
	result.pos += other.pos;
	result.worldPos += other.worldPos;
	return result;
}
