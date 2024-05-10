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
#include <istream>
#include <vector>
#include <cmath>
#include <string>
#include "defs.h"

extern bool DEBUG_PIXEL;
extern int xDebug, yDebug;
void mouseUtility(int, int, int, int);
void keyboardUtility(unsigned char key, int x, int y);

void swap(double& a, double& b);
bool approximatelyEqual(double a, double b);
bool approximatelyZero(double a);
double normalizeDegrees(double degrees);
double normalizeRadians(double rads);
double rad2deg(double rads);
double deg2rad(double degs);
double min(double a, double b, double c);
double max(double a, double b, double c);
double distanceFromOrigin(double x, double y);
double distanceBetween(double x1, double y1, double x2, double y2);

void pointOnUnitCircle(double angleRads, double& x, double& y);
dvec2 pointOnCircle(const dvec2& center, double R, double angleRads);

double directionInRadians(double x1, double y1, double x2, double y2);
double directionInRadians(const dvec2& targetPt);
double directionInRadians(const dvec2& referencePt, const dvec2& targetPt);

dvec2 doubleIt(const dvec2& V);
dvec3 myNormalize(const dvec3& V);
bool isOrthogonal(const dvec3& a, const dvec3& b);
bool formAcuteAngle(const dvec3& a, const dvec3& b);
double cosBetween(const dvec2& v1, const dvec2& v2);
double cosBetween(const dvec3& v1, const dvec3& v2);
double cosBetween(const dvec4& v1, const dvec4& v2);

double map(double x, double xLow, double xHigh, double yLow, double yHigh);

vector<double> quadratic(double A, double B, double C);
int quadratic(double A, double B, double C, double roots[2]);

double areaOfParallelogram(const dvec3& v1, const dvec3& v2);
double areaOfTriangle(const dvec3& pt1, const dvec3& pt2, const dvec3& pt3);
double areaOfTriangle(double a, double b, double c);
double areaOfTriangle(double x1, double y1, double x2, double y2, double x3, double y3);

dvec3 pointingVector(const dvec3& pt1, const dvec3& pt2);
dvec3 getRow(const dmat3& mat, int row);
dvec3 getCol(const dmat3& mat, int col);
bool isInvertible(const dmat3& mat);
dmat3 addMatrices(const vector<dmat3>& M);
dmat3 multiplyMatrices(const vector<dmat3>& M);
dvec3 multiplyMatrixAndVertex(const dmat3& M, const dvec3& x);
dvec3 multiplyMatricesAndVertex(const vector<dmat3>& M, const dvec3& x);
vector<dvec3> multiplyMatrixAndVertices(const dmat3& M, const vector<dvec3>& verts);
vector<dvec3> multiplyMatricesAndVertices(const vector<dmat3>& M, const vector<dvec3>& verts);

void computeXYZFromAzimuthAndElevation(double R,
	double az, double el,
	double& x, double& y, double& z);
void computeAzimuthAndElevationFromXYZ(double x, double y, double z,
	double& R, double& az, double& el);
void computeAzimuthAndElevationFromXYZ(const dvec3& pt,
	double& R, double& az, double& el);

string extractBaseFilename(const string& str);

// 2D versions
dmat3 T(double dx, double dy);
dmat3 S(double sx, double sy);
dmat3 R(double rads);
dmat3 vertShear(double a);
dmat3 horzShear(double a);

// 3D versions
dmat4 T(double dx, double dy, double dz);
dmat4 S(double sx, double sy, double sz);
dmat4 S(double scale);
dmat4 Rx(double rads);
dmat4 Ry(double rads);
dmat4 Rz(double rads);

bool inRangeInclusive(double val, double lo, double hi);
bool inRangeExclusive(double val, double lo, double hi);
bool inRectangle(double x, double y, double left, double bottom, double right, double top);
bool inRectangle(const dvec2& pt, const dvec2& lowerLeft, const dvec2& upperRight);

/**
 * @fn	template <class T> vector< vector<T> > allocate2D(int rows, int cols)
 * @brief	Allocates a vector of vectors.
 * @tparam	T	Generic type parameter.
 * @param	rows	The number rows.
 * @param	cols	The number cols.
 * @return	The vector of vectors, having the proper dimensions.
 */

template <class T>
vector<vector<T>> allocate2D(int rows, int cols) {
	vector<vector<T>> result(rows);
	for (int r = 0; r < rows; r++) {
		result[r] = vector<T>(cols);
	}
	return result;
}

/**
 * @fn	template <class T> T weightedAverage(double W1, const T &item1, double W2, const T &item2)
 * @brief	Computes the weighted average of two items.
 * @tparam	T	Generic type parameter.
 * @param	W1   	The first weight.
 * @param	item1	The first item.
 * @param	W2   	The second weight.
 * @param	item2	The second item.
 * @return	The weighted average.
 */

template <class T>
T weightedAverage(double W1, const T& item1, double W2, const T& item2) {
	return item1 * W1 + item2 * W2;
}

/**
 * @fn	template <class T> T average(const T &a, const T &b)
 * @brief	Computes the average of two items.
 * @tparam	T	Generic type parameter.
 * @param	a	First item.
 * @param	b	Second item.
 * @return	The average value.
 */

template <class T>
T average(const T& a, const T& b) {
	return (a + b) / 2.0;
}

/**
 * @fn	template <class T> T average(const T &a, const T &b , const T &c, const T &d)
 * @brief	Computes the average of four items.
 * @tparam	T	Generic type parameter.
 * @param	a	First item.
 * @param	b	Second item.
 * @param	c	Third item.
 * @param	d	Fourth item.
 * @return	The average value.
 */

template <class T>
T average(const T& a, const T& b, const T& c, const T& d) {
	return (a + b + c + d) / 4.0;
}

/**
 * @fn	template <class T1, class T2> void addAll(vector<T1> &vec, const vector<T2> &newItems)
 * @brief	Adds all the elements in newItems to end of the vector vec.
 * @tparam	T	Generic type parameter.
 * @param [in,out]	vec			The destination vector.
 * @param 		  	newItems	The new items to be added.
 */

template <class T>
void addAll(vector<T>& vec, const vector<T>& newItems) {
	vector<T> s;
	for (typename vector<T>::const_iterator i = newItems.begin(); i != newItems.end(); i++) {
		vec.push_back(*i);
	}
}

void graphicsInit(int argc, char* argv[], const std::string& fileName,
	int width = WINDOW_WIDTH, int height = WINDOW_HEIGHT);
