/****************************************************
 * 2016-2023 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#pragma once
#pragma warning( disable : 26451 )

#include <iostream>
#include <istream>
#include <vector>
#include <cmath>
#include <memory>
#include <limits>

 // Glut takes care of all the system-specific chores required for creating windows, 
 // initializing OpenGL contexts, and handling input events
#include <GL/freeglut.h>

#define GLM_FORCE_CTOR_INIT
#define GLM_FORCE_SWIZZLE  // Enable GLM "swizzle" operators

// Basic GLM functionality
#include <glm/glm.hpp> 
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

using std::cout;
using std::endl;
using std::vector;
using std::ostream;
using std::istream;
using std::string;

using glm::dvec2;
using glm::ivec2;
using glm::dvec3;
using glm::dvec4;
using glm::dmat2;
using glm::dmat3;
using glm::dmat4;

const std::string username = "vukm";
const double EPSILON = 1.0E-3;		//!< default value used for "SMALL" tolerances.

const int TIME_INTERVAL = 100;		//!< default time interval used timers.
const int WINDOW_WIDTH = 500;		//!< default window width.
const int WINDOW_HEIGHT = 250;		//!< default window height.
const unsigned char ESCAPE = 27;	//!< escape key.
const int DEFAULT_SLICES = 8;				//!< default value used when slicing up a curved object.

const double PI = 3.14159265358979323846264338327950288419716939937510582097494;	//!< pi
const double TWO_PI = 2 * PI;		//!< 2pi	(360 degrees)
const double PI_2 = PI / 2.0;		//!< pi/2	(90 degrees)
const double PI_3 = PI / 3.0;		//!< pi/3	(60 degrees)
const double PI_4 = PI / 4.0;		//!< pi/4	(45 degrees)
const double PI_6 = PI / 6.0;		//!< pi/6	(30 degrees)

const dvec3 ORIGIN3D(0.0, 0.0, 0.0);			//!< (0, 0, 0)
const dvec2 ORIGIN2D(0.0, 0.0);					//!< (0, 0)

const dvec3 ZEROVEC(0.0, 0.0, 0.0);			//!< <0, 0, 0>
const dvec3 X_AXIS(1.0, 0.0, 0.0);			//!< <1, 0, 0>
const dvec3 Y_AXIS(0.0, 1.0, 0.0);			//!< <0, 1, 0>
const dvec3 Z_AXIS(0.0, 0.0, 1.0);			//!< <0, 0, 1>

/**
 * @class	BoundingBoxi
 * @brief	A bounding box in 2D, with integer positions and widths.
 */

struct BoundingBoxi {
	int lx;			//!< lower left corner's x value
	int width;		//!< width of box
	int ly;			//!< lower left corner's y value
	int height;		//!< height of box
	BoundingBoxi(int left, int width, int bottom, int height) {
		lx = left;
		this->width = width;
		ly = bottom;
		this->height = height;
	}
	double aspectRatio() const {
		return (double)width / height;
	}
};

/**
 * @struct	Frame
 * @brief	Represents a coordinate frame
 */

struct Frame {
	dvec3 u;		//!< frame's "x" axis
	dvec3 v;		//!< frame's "y" axis
	dvec3 w;		//!< frame's "z" axis
	dvec3 origin;	//!< location of frame's origin
	dmat4 inverse;	//!< The inverse of the frame's transformation
	Frame();
	Frame(const dvec3& O, const dvec3& U, const dvec3& V, const dvec3& W);
	dvec3 globalCoordToFrameCoords(const dvec3& pt) const;
	dvec3 frameCoordsToGlobalCoords(const dvec3& pt) const;
	dvec3 globalVectorToFrameVector(const dvec3& v) const;
	dvec3 frameVectorToWorldVector(const dvec3& v) const;
	void setFrame(const dvec3& O, const dvec3& U, const dvec3& V, const dvec3& W);
	static Frame createOrthoNormalBasis(const dvec3& pos, const dvec3& w, const dvec3& up);
	static Frame createOrthoNormalBasis(const dvec3& pos, const dvec3& w);
	static Frame createOrthoNormalBasis(const dmat4& viewingMatrix);
	dmat4 toViewingMatrix() const;
	friend ostream& operator <<(ostream& os, const Frame& frame);
protected:
	void setInverse();
};
