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
#include "ishape.h"

 /**
  * @struct	RaytracingCamera
  * @brief	Base class for cameras in raytracing applications.
  */

struct RaytracingCamera {
	RaytracingCamera(const dvec3& pos, const dvec3& lookAtPt, const dvec3& up,
		int width, int height);
	virtual Ray getRay(double x, double y) const = 0;
	Frame getFrame() const { return cameraFrame; }
	int getNX() const { return nx; }
	int getNY() const { return ny; }
	double getLeft() const { return left; }
	double getRight() const { return right; }
	double getBottom() const { return bottom; }
	double getTop() const { return top; }
protected:
	Frame cameraFrame;					//!< The camera's frame
	int nx, ny;							//!< Window size
	double left, right, bottom, top;	//!< The camera's vertical field of view

	void setupFrame(const dvec3& pos, const dvec3& lookAtPt, const dvec3& up);
	virtual void setupViewingParameters(int width, int height) = 0;
	dvec2 getProjectionPlaneCoordinates(double x, double y) const;
public:

	friend ostream& operator << (ostream& os, const RaytracingCamera& camera);
};

/**
 * @struct	PerspectiveCamera
 * @brief	Encapsulates a perspective camera for raytracing applications.
 */

struct PerspectiveCamera : public RaytracingCamera {
	PerspectiveCamera(const dvec3& pos, const dvec3& lookAtPt, const dvec3& up, double FOVRads,
		int width, int height);
	virtual Ray getRay(double x, double y) const;
	double getDistToPlane() const { return distToPlane; }
private:
	double fov;						//!< The camera's field of view
	double distToPlane;				//!< Distance to image plane
	virtual void setupViewingParameters(int width, int height);
};

/**
 * @struct	OrthographicCamera
 * @brief	Encapsulates a orthographic camera for raytracing applications.
 */

struct OrthographicCamera : public RaytracingCamera {
	OrthographicCamera(const dvec3& pos, const dvec3& lookAtPt, const dvec3& up,
		int width, int height, double scaleFactor = 1.0);
	virtual Ray getRay(double x, double y) const;
private:
	double scale;		//!< Controls the size of the image plane.
	virtual void setupViewingParameters(int width, int height);
};