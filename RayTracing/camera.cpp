/****************************************************
 * 2016-2023 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#include "camera.h"

 /**
  * @fn	RaytracingCamera::RaytracingCamera(const dvec3 &viewingPos,
  *											const dvec3 &lookAtPt, const dvec3 &up)
  * @brief	Constructs a raytracing camera.
  * @param	viewingPos	Location of camera.
  * @param	lookAtPt  	A focus point in front of the camera..
  * @param	up		  	Up vector.
  */

RaytracingCamera::RaytracingCamera(const dvec3& viewingPos, const dvec3& lookAtPt, const dvec3& up,
	int width, int height) {
	setupFrame(viewingPos, lookAtPt, up);
}

/**
 * @fn	void RaytracingCamera::setupFrame(const dvec3& viewingPos, const dvec3& lookAtPt, const dvec3& up)
 * @brief	Change configuration parameters of this camera. This is called to update
 *          the camera frame - camera origin, u, v, and w. The last line of this function will
 *			be a call to cameraFrame.setFrame();
 * @param	viewingPos	The new viewing position.
 * @param	lookAtPt  	A new focus point point.
 * @param	up		  	Up vector.
 */

void RaytracingCamera::setupFrame(const dvec3& viewingPos, const dvec3& lookAtPt, const dvec3& up) {
	dvec3 viewingDirection = lookAtPt - viewingPos;
	dvec3 w = glm::normalize(-viewingDirection);
	dvec3 u = glm::normalize(glm::cross(up, w));
	dvec3 v = glm::normalize(glm::cross(w, u));
	cameraFrame.setFrame(viewingPos, u, v, w);
}

/**
 * @fn	PerspectiveCamera::PerspectiveCamera(const dvec3 &pos, const dvec3 &lookAtPt,
 *												const dvec3 &up, double FOVRads)
 * @brief	Constructs a perspective camera.
 * @param	pos			The position of the camera.
 * @param	lookAtPt	A focus point in front of the camera.
 * @param	up			Up vector.ve
 * @param	FOVRads 	The field of view in radians.
 */

PerspectiveCamera::PerspectiveCamera(const dvec3& pos, const dvec3& lookAtPt, const dvec3& up,
	double FOVRads,
	int width, int height)
	: RaytracingCamera(pos, lookAtPt, up, width, height) {
	fov = FOVRads;
	setupViewingParameters(width, height);
}

/**
 * @fn	OrthographicCamera::OrthographicCamera(const dvec3 &pos, const dvec3 &lookAtPt,
 *												const dvec3 &up, double ppwu)
 * @brief	Constructs an orthographic camera.
 * @param	pos			Position of camera.
 * @param	lookAtPt	A focus point in front of the camera.
 * @param	up			Up vector.
 * @param   width       Width of window.
 * @param   height      Height of window.
 * @param   scaleFactor Factor that scales the size viewing volume. When scaleFacter = 1,
 *						the viewing volume's width and height will match the window size.
 *                      When the scaleFactor is 0.5, it will be half the size of the window.
 *                      This value should be small if the objects in the scene are relatively
 *                      small when compared to the window's size, which is often in 100s of pixels.
 */

OrthographicCamera::OrthographicCamera(const dvec3& pos, const dvec3& lookAtPt, const dvec3& up,
	int width, int height, double scaleFactor)
	: RaytracingCamera(pos, lookAtPt, up, width, height) {
	scale = scaleFactor;
	setupViewingParameters(width, height);
}

/**
 * @fn	dvec2 RaytracingCamera::getProjectionPlaneCoordinates(double x, double y) const
 * @brief	Gets projection plane coordinates at (x, y).
 * @param	x	The x coordinate.
 * @param	y	The y coordinate.
 * @return	Projection plane coordinates.
 */

dvec2 RaytracingCamera::getProjectionPlaneCoordinates(double x, double y) const {
	dvec2 s;
	s.x = map(x + 0.5, 0, nx, left, right);
	s.y = map(y + 0.5, 0, ny, bottom, top);
	return s;
}

/**
 * @fn	void PerspectiveCamera::setupViewingParameters(int W, int H)
 * @brief	Calculates the viewing parameters associated with this camera.
 *          Called after construction of camera.
 * @param	W	The width of window.
 * @param	H	The height of window.
 */

void PerspectiveCamera::setupViewingParameters(int W, int H) {
	nx = W;
	ny = H;

	double fov_2 = fov / 2.0;
	distToPlane = 1.0 / std::tan(fov_2);

	top = 1.0;
	bottom = -top;

	right = top * ((double)nx / ny);
	left = -right;
}

/**
 * @fn	void OrthographicCamera::setupViewingParameters(int W, int H)
 * @brief	Calculates the viewing parameters associated with this camera.
 *          Called after construction of camera.
 * @param	W	The width of window.
 * @param	H	The height of window.
 */

void OrthographicCamera::setupViewingParameters(int W, int H) {
	nx = W;
	ny = H;

	top = H / 2.0;
	bottom = -top;

	right = top * (double)W / H;
	left = -right;

	left *= scale;
	right *= scale;
	bottom *= scale;
	top *= scale;
}

/**
 * @fn	Ray OrthographicCamera::getRay(double x, double y) const
 * @brief	Determines camera ray going through projection plane at (x, y), in direction -w.
 * @param	x	The x coordinate.
 * @param	y	The y coordinate.
 * @return	The ray through the projection plane at (x, y), in direction -w.
 */

Ray OrthographicCamera::getRay(double x, double y) const {
	dvec2 uv = getProjectionPlaneCoordinates(x, y);
	return Ray(cameraFrame.origin + uv.x * cameraFrame.u + uv.y * cameraFrame.v, -cameraFrame.w);
}

/**
 * @fn	Ray PerspectiveCamera::getRay(double x, double y) const
 * @brief	Determines ray eminating from camera through the projection plane at (x, y).
 * @param	x	The x coordinate.
 * @param	y	The y coordinate.
 * @return	The ray eminating from camera through the projection plane at (x, y).
 */

Ray PerspectiveCamera::getRay(double x, double y) const {
	dvec2 uv = getProjectionPlaneCoordinates(x, y);
	dvec3 rayDirection = glm::normalize(-distToPlane * cameraFrame.w +
		uv.x * cameraFrame.u +
		uv.y * cameraFrame.v);
	return Ray(cameraFrame.origin, rayDirection);
}

/**
* @fn	ostream &operator << (ostream &os, const RaytracingCamera &camera)
* @brief	Output stream for cameras.
* @param	os		Output stream.
* @param	camera  The camera.
*/

ostream& operator << (ostream& os, const RaytracingCamera& camera) {
	os << "Camera info:" << endl;
	os << "Frame" << endl;
	os << camera.cameraFrame << endl;
	return os;
}
