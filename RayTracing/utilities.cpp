/****************************************************
 * 2016-2023 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#include <iostream>
#include <istream>
#include <iomanip>
#include <cstdlib>

#include "defs.h"
#include "framebuffer.h"
#include "utilities.h"
#include "ishape.h"

/*
 * NOTE: There are several dozen functions in this file that you will implement over the course of the semester.
 * Implement only the ones listed for the given assignment (read the handout); you needn't do all of them in one sitting.
 */

 /**
  * @fn	void swap(double &a, double &b)
  * @brief	Swaps that values of two doubleing point numbers, without
  * 			using std.
  * @param [in,out]	a	First double.
  * @param [in,out]	b	Second double.
  */

void swap(double& a, double& b) {
	/* CSE 386 - todo  */
    double temp = a;
    a=b;
    b=temp;
}

/**
 * @fn	bool approximatelyEqual(double a, double b)
 * @brief	Determines if two values are approximately equal.
 * 			That is, their values within EPSILON of each other.
 * Programming constraint: Use EPSILON defined in defs.h
 * @param	a	The first value.
 * @param	b	The second value.
 * @return	true iff (a-b) is in [-EPSILON, EPSILON].
 * @test	approximatelyEqual(3.000000, 3.0000000001) --> true
 * @test	approximatelyEqual(3.000000, 3.1) --> false
*/

bool approximatelyEqual(double a, double b) {
	/* CSE 386 - todo  */
	return glm::abs(a-b) <= EPSILON;
}

/**
 * @fn	bool approximatelyZero(double a)
 * @brief	Determines if a value is approximately zero.
 * 			That is, the value is within EPSILON of zero.
 * Programming constraint: Use EPSILON defined in defs.h
 * @param	a	The value.
 * @return	true iff a is in [-EPSILON, EPSILON].
 * @test	approximatelyZero(0.0000001) --> true
 * @test	approximatelyZero(0.1) --> false
 */

bool approximatelyZero(double a) {
	/* CSE 386 - todo  */
	return approximatelyEqual(a, 0.0);
}

/**
 * @fn	double normalizeDegrees(double degrees)
 * @brief	Converts an arbitrary number of degrees to an equivalent
 * 			number of degrees in the range [0, 360). Loops should NOT
 *          be used in this function. Recursion should also not be used.
 * Programming constraint: Do not use recursion or loops. Consider using glm::mod.
 * @param	degrees	The degrees.
 * @return	Normalized degrees in the range [0, 360).
 * @test	normalizeDegrees(0) --> 0
 * @test	normalizeDegrees(1.75) --> 1.75
 * @test	normalizeDegrees(-1) --> 359
 * @test	normalizeDegrees(-721) --> 359
 */

double normalizeDegrees(double degrees) {
    return glm::mod(degrees, 360.0);
}

/**
 * @fn	double normalizeRadians(double rads)
 * @brief	Converts an arbitrary number of radians to an equivalent
 * 			number of radians in the range [0, 2*PI). Loops should NOT
 *          be used in this function.
 * Programming constraint: Do not use recursion or loops.
 * @param	rads	The radians.
 * @return	Normalized radians in the range [0, 2*PI).
 * @test	normalizeRadians(0) --> 0
 * @test	normalizeRadians(1) --> 1
 * @test	normalizeRadians(3*PI) --> 3.141.....
 * @test	normalizeRadians(-31*PI) --> 3.141.....
 */

double normalizeRadians(double rads) {
	/* CSE 386 - todo  */
    return glm::mod(rads, 2*PI);
}

/**
 * @fn	double rad2deg(double rads)
 * @brief	Converts radians to degrees.  This function behaves like glm::degrees,
 * without using glm::degrees.
 * Programming constraint: Do not glm::degrees.
 * @param	rads	The radians.
 * @return	Degrees.
 */

double rad2deg(double rads) {
	/* CSE 386 - todo  */
	return rads * 180 / PI;
}

/**
 * @fn	double deg2rad(double degs)
 * @brief	Converts degrees to radians. This function behaves like glm::radians,
 * without using glm::radians.
 * Programming constraint: Do not use glm::radians.
 * @param	degs	The degrees.
 * @return	Radians.
 */

double deg2rad(double degs) {
	/* CSE 386 - todo  */
	return degs * PI / 180;
}

/**
* @fn	double min(double A, double B, double C)
* @brief	Determines the minimum of three values, using glm::min.
* Programming constraint: Use glm::min, which provides the minimum of two numbers
* @param	A	First value.
* @param	B	Second value
* @param	C	Third value.
* @return	The minimum value.
*/

double min(double A, double B, double C) {
	/* CSE 386 - todo  */
	return glm::min(A, glm::min(B,C));
}

/**
* @fn	double max(double A, double B, double C)
* @brief	Determines the maximum of three values, using glm::max.
* Programming constraint: Use glm::max
* @param	A	First value.
* @param	B	Second value
* @param	C	Third value.
* @return	The maximum value.
*/

double max(double A, double B, double C) {
	/* CSE 386 - todo  */
	return glm::max(A, glm::max(B,C));
}

/**
* @fn	distanceFromOrigin(double x, double y)
* @brief	Determines the distance of the point (x, y) to (0, 0).
* The distance is defined by sqrt(x^2 + y^2). Note: ^ is not how
* C++ does exponentiation; you can use glm::pow instead.
* @param	x	The x coordinate
* @param	y	The y coordinate.
* @return	The distance of (x, y) to the origin.
* @test	distanceFromOrigin(0, 1) --> 1.0
* @test	distanceFromOrigin(1, 0) --> 1.0
* @test	distanceFromOrigin(1, 1) --> 1.41421356237309514547
* @test	distanceFromOrigin(-10, 30) --> 31.62277660168379256334
*/

double distanceFromOrigin(double x, double y) {
	/* CSE 386 - todo  */
    return std::sqrt(glm::pow(x, 2) + glm::pow(y, 2));
}

/**
* @fn	distanceBetween(double x1, double y1, double x2, double y2)
* @brief	Determines the distance of the point (x1, y1) to (x2, y2)
* The distance is defined by sqrt((x1-x2)^2 + (y1-y2)^2). Note: ^ is not how
* C++ does exponentiation; you can use glm::pow instead.
* @param	x1	The first x coordinate
* @param	y1	The first y coordinate.
* @param	x2	The second x coordinate
* @param	y2	The second y coordinate.
* @return	The distance between (x1, y1) and (x2, y2).
* @test	distanceBetween(0, 0, 1, 1) --> 1.41421356237309514547
* @test	distanceBetween(1, 1, 0, 0) --> 1.41421356237309514547
* @test	distanceBetween(10, 10, 11, 11) --> 1.41421356237309514547
* @test	distanceBetween(100, 100, 99, 99) --> 1.41421356237309514547
* @test	distanceBetween(54, 1, -34, -99) --> 133.2066064427737
*/

double distanceBetween(double x1, double y1, double x2, double y2) {
	/* CSE 386 - todo  */
	return std::sqrt(glm::pow(x1-x2, 2) + glm::pow(y1-y2, 2));
}

/**
 * @fn	double areaOfTriangle(double a, double b, double c)
 * @brief	Computes the area of triangle using Heron's formula.
 * @param	a length of first side.
 * @param	b length of second side.
 * @param	c length of third side.
 * @return	Area of triangle. Returns -1.0 if the triangle is illegal (i.e.
 * negative lengths). Legal values will yield v > 0.
 * @test	areaOfTriangle(3, 4, 5) --> 6
 * @test	areaOfTriangle(-3, 4, 5) --> -1
 * @test	areaOfTriangle(3, 4, 50) --> -1
 */

double areaOfTriangle(double a, double b, double c) {
	/* CSE 386 - todo  */
    if (a<=0 || b<=0 || c<=0 || a+b<=c || a+c<=b || b+c<=a) {
        return -1.0;
    }
    double s = (a+b+c)/2;
	return glm::sqrt(s*(s-a)*(s-b)*(s-c));
}

/**
 * @fn	double areaOfTriangle(double x1, double y1, double x2, double y2, double x3, double y3)
 * @brief	Computes the area of triangle formed by the three vertices (x1, y1), (x2, y2), and
 * (x3, y3). You can assume all vertices are distinct.
 * @param	x1 the x value of the first vertice
 * @param	y1 the y value of the first vertice
 * @param	x2 the x value of the second vertice
 * @param	y2 the y value of the second vertice
 * @param	x3 the x value of the third vertice
 * @param	y3 the y value of the third vertice
 * @return	Area of triangle.
 * @test	areaOfTriangle(0, 0, 3, 0, 0, 4) --> 6
 */

double areaOfTriangle(double x1, double y1, double x2, double y2, double x3, double y3) {
	/* CSE 386 - todo  */
	return areaOfTriangle(distanceBetween(x1, y1, x2, y2), distanceBetween(x2, y2, x3, y3), distanceBetween(x3, y3, x1, y1));
}

/**
 * @fn	void pointOnUnitCircle(double angleRads, double &x, double &y)
 * @brief	Determines the (x,y) position of a point on the standard
 * 			unit circle.
 * @param 		  	angleRads	The angle in radians.
 * @param [in,out]	x		 	A double to process.
 * @param [in,out]	y		 	A double to process.
 */

void pointOnUnitCircle(double angleRads, double& x, double& y) {
	/* CSE 386 - todo  */
	x = glm::cos(angleRads);
    y = glm::sin(angleRads);
}

/**
* @fn	dvec2 pointOnCircle(const dvec2 &center, double R, double angleRads)
* @brief	Computes the (x,y) value of a point on the circle centered on 'center',
* 			having radius R. The point is determined by sweeping an arc 'angleRads'.
* @param	center   	The center of the circle
* @param	R		 	Radius of circle.
* @param	angleRads	The angle in radians.
* @return	The point on the circle.
*/

dvec2 pointOnCircle(const dvec2& center, double R, double angleRads) {
	/* CSE 386 - todo  */

	return dvec2(center.x + R*glm::cos(angleRads), center.y + R*glm::sin(angleRads));
}

/**
* @fn	double directionInRadians(const dvec2 &referencePt, const dvec2 &targetPt)
* @brief	Compute the direction/heading of 'targetPt', relative
* 			to referencePt. The return angle should be in [0, 2PI)
* @param	referencePt	Reference point.
* @param	targetPt	Target point point.
* @return	A double.
* The test cases below casually use (0,0). When writing code, consider
* (0,0) to be dvec2(0,0).
* @test	directionInRadians(dvec2(0,0), dvec2(2,2)) --> 0.7853981634
* @test	directionInRadians(dvec2(2,10), dvec2(3,11)) --> 0.7853981634
* @test	directionInRadians(dvec2(2,2), dvec2(2,0)) --> 4.7123889804
* @test directionInRadians(dvec2(1,-1), dvec2(1.3420, -1.93969)) --> 5.06144
*/

double directionInRadians(const dvec2& referencePt, const dvec2& targetPt) {
	/* CSE 386 - todo  */
	return normalizeRadians(glm::atan(targetPt.y-referencePt.y,targetPt.x-referencePt.x));
}

/**
* @fn	double directionInRadians(const dvec2 &targetPt)
* @brief	Compute the direction/heading of 'targetPt', relative
* 			to the origin. The return angle should be in [0, 2PI)
* @param	targetPt	Target point point.
* @return	A double.
* @test	directionInRadians(dvec2(2,2)) --> 0.7853981634
* @test	directionInRadians(dvec2(0,-2)) --> 4.7123889804
*/

double directionInRadians(const dvec2& targetPt) {
	/* CSE 386 - todo  */
	return directionInRadians(dvec2(0,0), targetPt);
}

/**
* @fn	double directionInRadians(double x1, double y1, double x2, double y2)
* @brief	Compute the direction/heading of (x2, y2), relative
* 			to (x1, y1). The return angle should be in [0, 2PI)
* @param	x1  x coordinate of the reference point.
* @param	y1	y coordinate of the reference point.
* @param  x2    x coordinate of the target point.
* @param  y2    y coordinate of the target point.
* @return	A double.
* @test	directionInRadians(0,0,2,2) --> 0.7853981634
* @test	directionInRadians(2,10,3,11) --> 0.7853981634
* @test	directionInRadians(2,2,2,0) --> 4.7123889804
*/

double directionInRadians(double x1, double y1, double x2,  double y2) {
	/* CSE 386 - todo  */
	return directionInRadians(dvec2(x1,y1), dvec2(x2,y2));
}

/**
 * @fn	double map(double x, double fromLo, double fromHi, double toLow, double toHigh)
 * @brief	Linearly map a value from one interval to another.
 * @param 		  	x	 	x value.
 * @param 		  	fromLo 	The low value of the x range.
 * @param 		  	fromHi	The high value of the x range.
 * @param 		  	toLow 	The low value of the new range.
 * @param 		  	toHigh	The high value of the new range.
 * @test	map(2, 0, 5, 10, 11) --> 10.4
 */

double map(double x, double fromLo, double fromHi, double toLow, double toHigh) {
	/* CSE 386 - todo  */
	return (x - fromLo)/(fromHi - fromLo)*(toHigh-toLow)+toLow;
}

/**
 * @fn	vector<double> quadratic(double A, double B, double C)
 * @brief	Solves the quadratic equation, given A, B, and C.
 * 			0, 1, or 2 roots are inserted into the vector and returned.
 * 			The roots are placed into the vector sorted in ascending order.
 *          vector is somewhat like Java's ArrayList. Do a little research on
 *          it. The length of the vector will correspond to the number of roots.
 * @param	A	A.
 * @param	B	B.
 * @param	C	C.
 * @return	Vector containing the real roots.
 * @test	quadratic(1,4,3) --> [-3,-1]
 * @test	quadratic(1,0,0) --> [0]
 * @test	quadratic(-4, -2, -1) --> []
 */

vector<double> quadratic(double A, double B, double C) {
	/* CSE 386 - todo  */
	vector<double> result;	// put only the roots in here
    double delta= glm::pow(B,2)-4*A*C;
    if (delta == 0) {
        result.push_back(-B /(2*A));
    }
    if (delta > 0) {
        result.push_back((-B - glm::sqrt(delta)) / (2*A));
        result.push_back((-B + glm::sqrt(delta)) / (2*A));
        if (result[0] > result[1]) {
            swap(result[0], result[1]);
        }
    }
    
	return result;
}

/**
 * @fn	int quadratic(double A, double B, double C, double roots[2])
 * @brief	Solves the quadratic equation, given A, B, and C.
 * 			0, 1, or 2 roots are inserted into the array 'roots'.
 * 			The roots are sorted in ascending order.
 * Here is an example of how this is to be used:
 *
 * 	double roots[2];
 *	int numRoots = quadratic(1, 2, -3, roots);
 *	if (numRoots == 0) {
 *		cout << "There are no real roots" << endl;
 *	} else if (numRoots == 1) {
 *		cout << "Only one root: " << roots[0] << endl;
 *	} else if (numRoots == 2) {
 *      if (roots[0] > roots[1])
 *			cout << "Something is wrong. This should not happen" << endl;
 *		else
 *			cout << "Two roots: " << roots[0] << " and " << roots[1] << endl;
 *	} else {
 *		cout << "Something is wrong. This should not happen" << endl;
 *	}
 *
 * @param	A	 	A.
 * @param	B	 	B.
 * @param	C	 	C.
 * @param	roots	The real roots.
 * @test	quadratic(1, 4, 3, ary) --> returns 2 and fills in ary with: [-3,-1]
 * @test	quadratic(1 ,0, 0, ary) --> returns 1 and fills in ary with: [0]
 * @test	quadratic(-4, -2, -1, ary) --> returns 0 and does not modify ary.
 * @return	The number of real roots put into the array 'roots'
*/

int quadratic(double A, double B, double C, double roots[2]) {
	/* CSE 386 - todo  */
    double delta= glm::pow(B,2)-4*A*C;
	int rootCnt = 0;
    if (delta == 0) {
        rootCnt = 1;
        roots[0] = -B /(2*A);
    }
    if (delta > 0) {
        rootCnt = 2;
        roots[0] = (-B - glm::sqrt(delta)) / (2*A);
        roots[1] =(-B + glm::sqrt(delta)) / (2*A);
        if (roots[0] > roots[1]) {
            swap(roots[0], roots[1]);
        }
    }
    
	return rootCnt;
}

/**
* @fn	dvec2 doubleIt(const dvec2 &V)
* @brief	Computes 2*V
* @param	V	The vector.
* @return	2*V.
*/

dvec2 doubleIt(const dvec2& V) {
	/* CSE 386 - todo  */
	return 2.0 * V;
}

/**
* @fn	dvec3 myNormalize(const dvec3 &V)
* @brief	Computes the normalization of V, without calling glm::normalize.
*           The input vector is not be the zero vector.
* Programming constraint: Do NOT use glm::normalize
* @param	V	The vector.
* @return	Normalized vector V.
*/

dvec3 myNormalize(const dvec3& V) {
	/* CSE 386 - todo  */
	return (1/glm::length(V))*V;
}

/**
* @fn	bool isOrthogonal(const dvec3 &a, const dvec3 &b)
* @brief	Determines if two vectors are orthogonal, or nearly orthogonal. The inputs are non-zero vectors.
Two vectors are nearly orthogonal if the cosine of the angle formed by these
two vectors is approximatelyZero().
* @param	a	The first vector.
* @param	b	The second vector.
* @return	True iff the two vector are orthogonal.
*/

bool isOrthogonal(const dvec3& a, const dvec3& b) {
	/* CSE 386 - todo  */
    return approximatelyZero(glm::dot(a,b));
}

/**
* @fn	bool formAcuteAngle(const dvec3 &a, const dvec3 &b)
* @brief	Determines if two vectors form an angle that is < 90 degrees. The inputs are non-zero vectors.
* Programming constraint: Do NOT use acos, atan, or asin (you CAN use dot, cos, etc)
* @param	a	The first vector.
* @param	b	The second vector.
* @return	True iff the two vectors form an acute angle.
*/

bool formAcuteAngle(const dvec3& a, const dvec3& b) {
	return glm::dot(a,b) > 0;
}

/**
 * @fn	double cosBetween(const dvec2 &v1, const dvec2 &v2)
 * @brief	Cosine between v1 and v2. The inputs are non-zero vectors.
 * @param	v1	The first vector.
 * @param	v2	The second vector.
 * @test	cosBetween(dvec2(1.0, 0.0), dvec2(1.0, 0.0)) --> 1.0
 * @test	cosBetween(dvec2(1.0, 0.0), dvec2(1.0, 1.0)) --> 0.707107
 * @test	cosBetween(dvec2(-1.0, glm::sqrt(3.0)), dvec2(-1.0, 0.0)) --> 0.5
 * @test	cosBetween(dvec2(-1.0, glm::sqrt(3.0)), dvec2(1.0, glm::sqrt(3.0))) --> 0.5
 * @return	The cosine between v1 and v2.
 */

double cosBetween(const dvec2& v1, const dvec2& v2) {
	/* CSE 386 - todo  */
	return glm::dot(v1, v2)/(glm::length(v1)*glm::length(v2));
}

/**
 * @fn	double cosBetween(const dvec3 &v1, const dvec3 &v2)
 * @brief	Computes the cosine between v1 and v2.
 * @param	v1	The first vector.
 * @param	v2	The second vector.
 * @return	A double.
 */

double cosBetween(const dvec3& v1, const dvec3& v2) {
	/* CSE 386 - todo  */
	return glm::dot(v1, v2)/(glm::length(v1)*glm::length(v2));
}

/**
 * @fn	double cosBetween(const dvec4 &v1, const dvec4 &v2)
 * @brief	Computes the cosine between v1 and v2.
 * @param	v1	The first vector.
 * @param	v2	The second vector.
 * @return	A double.
 */

double cosBetween(const dvec4& v1, const dvec4& v2) {
	/* CSE 386 - todo  */
	double cos = glm::dot(v1, v2) / (glm::length(v1) * glm::length(v2));
	return cos;
}

/**
 * @fn	double areaOfParallelogram(const dvec3 &v1, const dvec3 &v2)
 * @brief	Computes the area of parallelogram, given two vectors eminating
 * 			from the same corner of the parallelogram.
 * @param	v1	The first vector.
 * @param	v2	The second vector.
 * @test	areaOfParallelogram(dvec3(1.0, 0.0, 0.0), dvec3(0.0, 1.0, 0.0)) --> 1.0
 * @test	areaOfParallelogram(dvec3(1.0, 1.0, 1.0), dvec3(1.0, 0.0, 1.0)) --> 1.41421
 * @return	Area of parallelogram.
 */

double areaOfParallelogram(const dvec3& v1, const dvec3& v2) {
	/* CSE 386 - todo  */
	return glm::length(glm::cross(v1, v2));
}

/**
 * @fn	double areaOfTriangle(const dvec3 &pt1, const dvec3 &pt2, const dvec3 &pt3)
 * @brief	Computes the area of triangle.
 * Programming constraint: use areaOfParalellogram to solve this one.
 * @param	pt1	The first point.
 * @param	pt2	The second point.
 * @param	pt3	The third point.
 * @test	areaOfTriangle(dvec3(0.0, 0.0, 0.0), dvec3(1.0, 0.0, 0.0), dvec3(0.0, 1.0, 0.0)) --> 0.5
 * @test	areaOfTriangle(dvec3(-10.0, -10.0, -10.0), dvec3(-11.0, -10.0, -10.0), dvec3(-10.0, -11.0, -10.0)) --> 0.5
 * @return	Area of triangle.
 */

double areaOfTriangle(const dvec3& pt1, const dvec3& pt2, const dvec3& pt3) {
	/* CSE 386 - todo  */
    dvec3 v1 = pt2 - pt1;
    dvec3 v2 = pt3 - pt1;
	return areaOfParallelogram(v1, v2)/2;
}

/**
* @fn	dvec3 pointingVector(const dvec3 &pt1, const dvec3 &pt2)
* @brief	Computes unit-length pointing vector.
* @param	pt1	The first point.
* @param	pt2	The second point.
* @return	Unit length vector that points from pt1 toward pt2.
*/

dvec3 pointingVector(const dvec3& pt1, const dvec3& pt2) {
	/* CSE 386 - todo  */
	return glm::normalize(pt2 - pt1);
}

/**
* @fn	dvec3 getRow(const dmat3 &mat, int row)
* @brief	Retrieves a particular row out of a matrix.
* @param	mat	The matrix.
* @param	row	The row.
* @return	The extracted row.
*/

dvec3 getRow(const dmat3& mat, int row) {
	/* CSE 386 - todo  */
	return dvec3(mat[0][row], mat[1][row], mat[2][row]);
}

/**
 * @fn	dvec3 getCol(const dmat3 &mat, int col)
 * @brief	Retrieves a particular column out of a matrix.
 * @param	mat	The matrix.
 * @param	col	The column.
 * @return	The extracted column.
 */

dvec3 getCol(const dmat3& mat, int col) {
	/* CSE 386 - todo  */
	return dvec3(mat[col][0], mat[col][1], mat[col][2]);
}

/**
 * @fn	bool isInvertible(const dmat3 &mat)
 * @brief	Determines if mat is invertible. A matrix is invertible if
 *			its determinant is not 0.
 * @param	mat	The matrix.
 * @return	true if invertible, false if not.
 */

bool isInvertible(const dmat3& mat) {
	/* CSE 386 - todo  */
	return glm::determinant(mat) != 0;
}

/**
 * @fn	dmat3 addMatrices(const vector<dmat3> &M)
 * @brief	Adds the several matrices together. Assume the vector has length > 0.
 * @param	M	Vector of matrices.
 * @return	M[0]+M[1]+...+M[m-1]
 */

dmat3 addMatrices(const vector<dmat3>& M) {
	/* CSE 386 - todo  */
    dmat3 result (0,0,0,0,0,0,0,0,0);
    for (dmat3 i : M) {
        result += i;
    }
	return result;
}

/**
 * @fn	dmat3 multiplyMatrices(const vector<dmat3> &M)
 * @brief	Multiply many matrices together. Assume the vector has length > 0.
 * @param	M	The vector of matrices.
 * @return	Returns M[0]*M[1]*...M[m-1].
 */

dmat3 multiplyMatrices(const vector<dmat3>& M) {
	/* CSE 386 - todo  */
	dmat3 result;
    for (dmat3 i : M) {
        result *= i;
    }
	return result;
}

/**
 * @fn	dvec3 multiplyMatrixAndVertex(const dmat3 &M, const dvec3 &x)
 * @brief	Multiply matrix and vertex
 * @param	M	A matrix.
 * @param	x	A vector.
 * @return	Returns M*x.
 */

dvec3 multiplyMatrixAndVertex(const dmat3& M, const dvec3& x) {
	/* CSE 386 - todo  */
	return M * x;
}

/**
 * @fn	dvec3 multiplyMatricesAndVertex(const vector<dmat3> &M, const dvec3 &x)
 * @brief	Multiply matrices and vertex.
 * @param	M	A vector of matrices to process. Assume the vector has length > 0.
 * @param	x	The vertex to process.
 * @return	Returns the result of M[0]*M[1]*...M[n-1]*x
 */

dvec3 multiplyMatricesAndVertex(const vector<dmat3>& M, const dvec3& x) {
	/* CSE 386 - todo  */
	return multiplyMatrices(M) * x;
}

/**
 * @fn	vector<dvec3> multiplyMatrixAndVertices(const dmat3 &M, const vector<dvec3> &verts)
 * @brief	Returns the vector containing: <M*verts[0], M*verts[1], ... M*verts[n-1]>
 * @param	M	 	A dmat3 to process.
 * @param	verts	The vertices.
 * @return	Returns the vector: <M*verts[0], M*verts[1], ... M*verts[n-1]>
 */

vector<dvec3> multiplyMatrixAndVertices(const dmat3& M, const vector<dvec3>& verts) {
	/* CSE 386 - todo  */
	vector<dvec3> result;
    for (auto i : verts) {
        result.push_back(M * i);
    }
	return result;
}

/**
 * @fn	vector<dvec3> multiplyMatricesAndVertices(const vector<dmat3> &M, const vector<dvec3> &verts)
 * @brief	Multiply matrices and vertices
 * @param	M	 	Vector of matrices. Assume the vector has length > 0.
 * @param	verts	Vector of vertices.
 * @return	Returns:
 *		<M[0]*M[1]*...M[m-1]*verts[0], M[0]*M[1]*...M[m-1]*verts[1], ... M[0]*M[1]*...M[m-1]*verts[n-1]>
 */

vector<dvec3> multiplyMatricesAndVertices(const vector<dmat3>& M, const vector<dvec3>& verts) {
	/* CSE 386 - todo  */
    dmat3 r = multiplyMatrices(M);
	return multiplyMatrixAndVertices(r, verts);
}

/**
* @fn	dmat3 T(double dx, double dy)
* @brief	Creates the 3x3 translation matrix for 2D systems.
* @param	dx	x translation factor.
* @param	dy	y translation factor.
* @return	The translation matrix.
*/

dmat3 T(double dx, double dy) {
	return dmat3(1, 0, 0, 0, 1, 0, dx, dy, 1);
}

/**
 * @fn	dmat3 S(double sx, double sy)
 * @brief	Creates the 3x3 scaling matrix for 2D systems.
 * @param	sx	x scale factor.
 * @param	sy	y scale factor.
 * @return	The scaling matrix.
 */

dmat3 S(double sx, double sy) {
	return dmat3(sx, 0, 0, 0, sy, 0, 0, 0, 1);
}

/**
 * @fn	dmat3 R(double rads)
 * @brief	Returns 3x3 rotation matrix for 2D rotations.
 * @param	rads	Radians to rotate.
 * @return	The rotation matrix.
 */

dmat3 R(double rads) {
	return dmat3(cos(rads), sin(rads), 0, -sin(rads), cos(rads), 0, 0, 0, 1);
}

/**
 * @fn	dmat3 horzShear(double a)
 * @brief	Horizontal shear.
 * @param	a	Shearing parameter.
 * @return	The 3x3 shearing matrix.
 */

dmat3 horzShear(double a) {
	return dmat3(1, 0, 0, a, 1, 0, 0, 0, 1);
}

/**
 * @fn	dmat3 vertShear(double a)
 * @brief	Vertical shear.
 * @param	a	Shearing parameter.
 * @return	The 3x3 shearing matrix.
 */

dmat3 vertShear(double a) {
	return dmat3(1, a, 0, 0, 1, 0, 0, 0, 1);
}

/**
* @fn	dmat4 T(double dx, double dy, double dz)
* @brief	Creates the 4x4 translation matrix for 3D systems.
* @param	dx	The x translation factor.
* @param	dy	The y translation factor.
* @param	dz	The z translation factor.
* @return	The 4x4 translation matrix for 3D systems.
*/

dmat4 T(double dx, double dy, double dz) {
	/* CSE 386 - todo  */
	return glm::translate(dvec3(dx, dy, dz));
}

/**
* @fn	dmat4 S(double sx, double sy, double sz)
* @brief	Creates the 4x4 scaling matrix for 3D systems.
* @param	sx	The x scaling factor.
* @param	sy	The y scaling factor.
* @param	sz	The z scaling factor.
* @return	The 4x4 scaling matrix for 3D systems.
*/

dmat4 S(double sx, double sy, double sz) {
	/* CSE 386 - todo  */
	return glm::scale(dvec3(sx, sy, sz));
}

/**
* @fn	dmat4 S(double scale)
* @brief	Creates the 4x4 scaling matrix for 3D systems.
* @param	scale	The scale.
* @return	The 4x4 [uniform] scaling matrix for 3D systems.
*/

dmat4 S(double scale) {
	/* CSE 386 - todo  */
	return S(scale, scale, scale);
}

/**
* @fn	dmat3 Rx(double rads)
* @brief	Creates the 4x4 rotation matrix for 3D systems.
* @param	rads	Rotation amount, in radians.
* @return	The 4x4 matrix for rotation about the +x axis.
*/

dmat4 Rx(double rads) {
	/* CSE 386 - todo  */
	return glm::rotate(rads, dvec3(1.0, 0.0, 0.0));
}

/**
* @fn	dmat3 Ry(double rads)
* @brief	Creates the 4x4 rotation matrix for 3D systems.
* @param	rads	Rotation amount, in radians.
* @return	The 4x4 matrix for rotation about the +y axis.
*/

dmat4 Ry(double rads) {
	/* CSE 386 - todo  */
	return glm::rotate(rads, dvec3(0.0, 1.0, 0.0));
}

/**
* @fn	dmat3 Rz(double rads)
* @brief	Creates the 4x4 rotation matrix for 3D systems.
* @param	rads	Rotation amount, in radians.
* @return	The 4x4 matrix for rotation about the +z axis.
*/

dmat4 Rz(double rads) {
	/* CSE 386 - todo  */
	return glm::rotate(rads, dvec3(0.0, 0.0, 1.0));
}

/**
* @fn	void computeXYZFromAzimuthAndElevation(double R, double az, double el,
*												double &x, double &y, double &z)
* @brief	Computes (x,y,z), given a specific azimuth/elevation angles.
* @param 		  	R 	The radius of the sphere.
* @param 		  	az	Azimuth
* @param 		  	el	Elevation.
* @param [in,out]	x 	A double to process.
* @param [in,out]	y 	A double to process.
* @param [in,out]	z 	A double to process.
*/

void computeXYZFromAzimuthAndElevation(double R,
	double az, double el,
	double& x, double& y, double& z) {
	z = R * std::cos(el) * std::cos(az);
	x = R * std::cos(el) * std::sin(az);
	y = R * std::sin(el);
}

/**
* @fn	void computeAzimuthAndElevationFromXYZ(double x, double y, double z,
*												double &R, double &az, double &el)
* @brief	Calculates the azimuth and elevation from xyz
* @param 		  	x 	The x coordinate.
* @param 		  	y 	The y coordinate.
* @param 		  	z 	The z coordinate.
* @param [in,out]	R 	The radius of the sphere.
* @param [in,out]	az	Azimuth.
* @param [in,out]	el	Elevation.
*/

void computeAzimuthAndElevationFromXYZ(double x, double y, double z,
	double& R, double& az, double& el) {
	R = glm::length(dvec3(x, y, z));
	az = std::atan2(x, z);
	el = std::atan2(y, glm::length(dvec2(x, z)));
}

/**
* @fn	void computeAzimuthAndElevationFromXYZ(const dvec3 &pt, double &R, double &az, double &el)
* @brief	Compute the azimuth/elevation (relative to the origin) of the point (x,y,z)
* @param 		  	pt	The point - (x,y,z).
* @param [in,out]	R 	The radius of the sphere.
* @param [in,out]	az	Azimuth.
* @param [in,out]	el	Elevation.
*/

void computeAzimuthAndElevationFromXYZ(const dvec3& pt,
	double& R, double& az, double& el) {
	computeAzimuthAndElevationFromXYZ(pt.x, pt.y, pt.z, R, az, el);
}

bool inRangeInclusive(double val, double lo, double hi) {
	return val >= lo && val <= hi;
}

bool inRangeExclusive(double val, double lo, double hi) {
	return val > lo && val < hi;
}

/**
* @fn	bool inRectangle(double x, double y, double left, double bottom, double right, double top)
* @brief	Determines if (x,y) is inside (or on) a rectangle.
* @param	x	  	The x coordinate.
* @param	y	  	The y coordinate.
* @param	left  	The left edge of rectangle.
* @param	bottom	The bottom edge of rectangle.
* @param	right 	The right edge of rectangle.
* @param	top   	The top edge of rectangle.
* @return	true iff (x,y) is in/on the rectangle.
*/

bool inRectangle(double x, double y, double left, double bottom, double right, double top) {
	return inRangeInclusive(x, left, right) &&
		inRangeInclusive(y, bottom, top);
}

/**
* @fn	bool inRectangle(const dvec2 &pt, const dvec2 &lowerLeft, const dvec2 &upperRight)
* @brief	Determines if (x,y) is inside (or on) a rectangle.
* @param	pt		  	The point - (x,y)
* @param	lowerLeft 	The lower left corner of the rectangle - (left, bottom).
* @param	upperRight	The upper right corner of the rectangle - (right, top).
* @return	true iff (x,y) is in/on the rectangle.
*/

bool inRectangle(const dvec2& pt, const dvec2& lowerLeft, const dvec2& upperRight) {
	return inRangeInclusive(pt.x, lowerLeft.x, upperRight.x) &&
		inRangeInclusive(pt.y, lowerLeft.y, upperRight.y);
}

/**
* @fn	string extractBaseFilename(const string &str)
* @brief	Extracts the base filename described by str
* @param	str	The string.
* @return	The extracted base filename.
* @test	extractBaseFileName("/usr/etc/hosts.txt") --> "hosts.txt"
*/

string extractBaseFilename(const string& str) {
#ifdef WINDOWS
	size_t pos = str.rfind('\\');
#else
	size_t pos = str.rfind('/');
#endif
	return str.substr(pos + 1);
}

bool DEBUG_PIXEL = false;
int xDebug = -1, yDebug = -1;

void mouseUtility(int b, int s, int x, int y) {
#ifndef CONSOLE_ONLY
	if (s == GLUT_DOWN) {
		xDebug = x;
		yDebug = glutGet(GLUT_WINDOW_HEIGHT) - y - 1;
		glutPostRedisplay();
		cout << "(" << xDebug << "," << yDebug << ") = " << endl;
	}
#endif
}

void keyboardUtility(unsigned char key, int x, int y) {
#ifndef CONSOLE_ONLY
	switch (key) {
	case ESCAPE:		glutLeaveMainLoop();
		break;
	default:	cout << (int)key << "unmapped key pressed." << endl;
	}

	glutPostRedisplay();
#endif
}

void graphicsInit(int argc, char* argv[], const std::string& windowName, int width, int height) {
#ifndef WINDOWS
	setenv("DISPLAY", ":0.0", 1);
#endif
#ifndef CONSOLE_ONLY
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(width, height);
	std::string title = username + std::string(" -- ") + extractBaseFilename(windowName);
	glutCreateWindow(title.c_str());
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
#endif
}
