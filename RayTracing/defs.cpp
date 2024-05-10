/****************************************************
 * 2016-2023 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#include <iostream>
#include "defs.h"
#include "utilities.h"

 /**
  * @fn	void Frame::setInverse()
  * @brief	Sets the inverse based on the current parameters.
  * @see Page *** from textbook
  */

void Frame::setInverse() {
	dmat4 T;
	T[0][0] = u[0];
	T[0][1] = u[1];
	T[0][2] = u[2];

	T[1][0] = v[0];
	T[1][1] = v[1];
	T[1][2] = v[2];

	T[2][0] = w[0];
	T[2][1] = w[1];
	T[2][2] = w[2];

	T[3][0] = origin[0];
	T[3][1] = origin[1];
	T[3][2] = origin[2];

	inverse = glm::inverse(T);
}

/**
 * @fn	dvec3 Frame::toFrameCoords(const dvec3 &pt) const
 * @brief	Converts a point to a frame coordinates
 * @param	pt	Point in world coordinates.
 * @return	The frame coordinates of a point given in woord coordinates.
 */

dvec3 Frame::globalCoordToFrameCoords(const dvec3& pt) const {
	return (inverse * dvec4(pt.x, pt.y, pt.z, 1.0)).xyz();
}

/**
* @fn	dvec3 Frame::toWorldCoords(const dvec3 &pt) const
* @brief	Converts a frame coordinate into the equivalent point in world coordinates
* @param	pt	Point in frame coordinates.
* @return	The world coordinates of a point given in frame coordinates.
*/

dvec3 Frame::frameCoordsToGlobalCoords(const dvec3& pt) const {
	return origin + pt.x * u + pt.y * v + pt.z * w;
}

/**
 * @fn	dvec3 Frame::toFrameVector(const dvec3 &V) const
 * @brief	Converts a V (in world system) into equivalent frame vector.
 * @param	V	World vector to process.
 * @return	Frame vector that expresses the same direction as the original.
 */

dvec3 Frame::globalVectorToFrameVector(const dvec3& V) const {
	dvec3 A = globalCoordToFrameCoords(V);
	dvec3 B = globalCoordToFrameCoords(ORIGIN3D);
	return A - B;
}

/**
 * @fn	dvec3 Frame::toWorldVector(const dvec3 &V) const
 * @brief	Converts a V (in frame system) into equivalent world vector.
 * @param	V	Frame vector to process.
 * @return	World vector that expresses the same direction as the original.
 */

dvec3 Frame::frameVectorToWorldVector(const dvec3& V) const {
	dvec3 vectorHead = origin + u * V.x + v * V.y + w * V.z;
	dvec3 vectorTail = origin;
	return vectorHead - vectorTail;
}

/**
 * @fn	Frame Frame::createOrthoNormalBasis(const dvec3 &pos, const dvec3 &w, const dvec3 &up)
 * @brief	Creates ortho normal basis given a position and two non-parallel vectors.
 * @param	pos	The position of the new frame's origin.
 * @param	w  	"z" vector in new frame.
 * @param	up 	up vector in new frame.
 * @return	The new ortho normal basis.
 */

Frame Frame::createOrthoNormalBasis(const dvec3& pos, const dvec3& w, const dvec3& up) {
	Frame frame;
	frame.origin = pos;
	frame.w = glm::normalize(w);
	frame.u = glm::normalize(glm::cross(up, w));
	frame.v = glm::normalize(glm::cross(frame.w, frame.u));
	frame.setInverse();
	return frame;
}

/**
 * @fn	Frame Frame::createOrthoNormalBasis(const dvec3 &pos, const dvec3 &p)
 * @brief	Creates ortho normal basis given a position and one vectors.
 * @param	pos	The position of the new frame's origin.
 * @param	w  	"z" vector in new frame.
 * @return	The new ortho normal basis.
 */

Frame Frame::createOrthoNormalBasis(const dvec3& pos, const dvec3& w) {
	dvec3 wNormed = glm::normalize(w);
	int minIndex = 0;
	for (int i = 1; i < 3; i++) {
		if (w[i] < w[minIndex]) {
			minIndex = i;
		}
	}

	dvec3 fakeUp = wNormed;
	fakeUp[minIndex] = 1.0;

	return createOrthoNormalBasis(pos, w, fakeUp);
}

/**
* @fn	Frame Frame::createOrthoNormalBasis(const dmat4 &viewingMatrix)
* @brief	Creates ortho normal basis given two non-parallel vectors.
* @param	viewingMatrix The viewing matrix created by glm::lookAt
* @return	The equivalent Frame
*/

Frame Frame::createOrthoNormalBasis(const dmat4& viewingMatrix) {
	dmat4 vmInverse = glm::inverse(viewingMatrix);
	dvec3 u(vmInverse[0]);
	dvec3 v(vmInverse[1]);
	dvec3 w(vmInverse[2]);
	dvec3 eye(vmInverse[3]);
	return Frame(eye, u, v, w);
}

/**
* @fn	dmat4 Frame::toViewingMatrix()
* @brief	Returns the viewing matrix equivalent to the frame
* @return	The equivalent viewing matrix
*/

dmat4 Frame::toViewingMatrix() const {
	return glm::inverse(dmat4(u.x, u.y, u.z, 0,
		v.x, v.y, v.z, 0,
		w.x, w.y, w.z, 0,
		origin.x, origin.y, origin.z, 1));
}

/**
 * @fn	Frame::Frame()
 * @brief	Constructs a new frame equivalent to the world frame.
 */

Frame::Frame() : origin(ORIGIN3D), u(ZEROVEC), v(ZEROVEC), w(ZEROVEC) {
	setInverse();
}

/**
 * @fn	Frame::Frame(const dvec3 &O, const dvec3 &U, const dvec3 &V, const dvec3 &W)
 * @brief	Constructs a new frame given 3 orthonormal vectors (assumed to be orthonormal).
 * @param 	O	Origin of new frame.
 * @param	U	New "x" vector.
 * @param 	V	New "y" vector.
 * @param 	W	New "z" vector.
 */

Frame::Frame(const dvec3& O, const dvec3& U, const dvec3& V, const dvec3& W)
	: origin(O), u(U), v(V), w(W) {
	setInverse();
}

/**
 * @fn	void Frame::setFrame(const dvec3 &O, const dvec3 &U, const dvec3 &V, const dvec3 &W)
 * @brief	Sets the frame's axes and origin.
 * @param 	O	Origin of new frame.
 * @param	U	New "x" vector.
 * @param 	V	New "y" vector.
 * @param 	W	New "z" vector.
 */

void Frame::setFrame(const dvec3& O, const dvec3& U, const dvec3& V, const dvec3& W) {
	origin = O;
	u = U;
	v = V;
	w = W;
	setInverse();
}

