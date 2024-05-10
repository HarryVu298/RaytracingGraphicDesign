/****************************************************
 * 2016-2023 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#include <cmath>
#include "rasterization.h"

 /**
 * @fn	template <class T> T barycentricWeighting(double w1, double w2, double w3,
 *													const T &i1, const T &i2, const T &i3)
 * @brief	Computes the Barycentric weighting of three values.
 * @tparam	T	Generic type parameter.
 * @param	w1	The first weight.
 * @param	w2	The second weight.
 * @param	w3	The third weight.
 * @param	i1	The first item.
 * @param	i2	The second item.
 * @param	i3	The third item.
 * @return	The Barycentric weighting of the three items.
 */

template <class T>
T barycentricWeighting(double w1, double w2, double w3, const T& i1, const T& i2, const T& i3) {
	return w1 * i1 + w2 * i2 + w3 * i3;
}

/**
 * @fn	void drawVerticalLine(FrameBuffer &fb, int x, int bottom, int top, const color &rgb)
 * @brief	Draw vertical line
 * @param [in,out]	fb	  	Framebuffer
 * @param 		  	x	  	The x coordinate.
 * @param 		  	bottom	Bottom.
 * @param 		  	top   	Top.
 * @param 		  	rgb   	Color.
 */

static void drawVerticalLine(FrameBuffer& fb, int x, int bottom, int top, const color& rgb) {
	const int H = fb.getWindowHeight();
	const int W = fb.getWindowWidth();

	if (bottom > top) {
		std::swap(bottom, top);
	}

	bottom = bottom < 0 ? 0 : bottom;
	top = top >= H ? H - 1 : top;
	for (int y = bottom; y <= top; y++) {
		if (inRectangle((double)x, (double)y, 0.0, 0.0, W - 1.0, H - 1.0))
			fb.setColor(x, y, rgb);
	}
}

/**
 * @fn	void drawHorizontalLine(FrameBuffer &fb, int y, int left, int right, const color &rgb)
 * @brief	Draw horizontal line
 * @param [in,out]	fb   	Framebuffer
 * @param 		  	y	 	The y coordinate.
 * @param 		  	left 	Left.
 * @param 		  	right	Right.
 * @param 		  	rgb  	Color.
 */

static void drawHorizontalLine(FrameBuffer& fb, int y, int left, int right, const color& rgb) {
	const int H = fb.getWindowHeight();
	const int W = fb.getWindowWidth();

	if (left > right) {
		std::swap(left, right);
	}
	left = left < 0 ? 0 : left;
	right = right >= W ? W - 1 : right;
	for (int x = left; x <= right; x++) {
		if (inRectangle((double)x, (double)y, 0.0, 0.0, W - 1.0, H - 1.0))
			fb.setColor(x, y, rgb);
	}
}

/**
 * @fn	void drawBresenhamLine(FrameBuffer &fb, const dvec2 &p1, const dvec2 &p2, const color &rgb)
 * @brief	Draw line using bresenham's algorithm
 * @param [in,out]	fb 	Framebuffer.
 * @param 		  	p1 	First point.
 * @param 		  	p2 	Second point.
 * @param 		  	rgb	Color.
 */

static void drawBresenhamLine(FrameBuffer& fb,
	const dvec2& p1,
	const dvec2& p2, const color& rgb) {
	const int H = fb.getWindowHeight();
	const int W = fb.getWindowWidth();

	int x0 = (int)p1.x;
	int y0 = (int)p1.y;
	int x1 = (int)p2.x;
	int y1 = (int)p2.y;

	int dx = std::abs(x1 - x0);
	int dy = std::abs(y1 - y0);

	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;

	int err = dx - dy;

	if (inRectangle((double)x0, (double)y0, 0.0, 0.0, W - 1.0, H - 1.0)) {
		fb.setColor(x0, y0, rgb);
	}

	while (x0 != x1 || y0 != y1) {
		int e2 = err << 1;

		if (e2 > -dy) {
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx) {
			err += dx;
			y0 += sy;
		}

		if (inRectangle((double)x0, (double)y0, 0.0, 0.0, W - 1.0, H - 1.0)) {
			fb.setColor(x0, y0, rgb);
		}
	}
}

/**
 * @fn	void drawLine(FrameBuffer &fb, const dvec2 &A, const dvec2 &B, const color &rgb)
 * @brief	Draw line
 * @param [in,out]	fb 	Framebuffer.
 * @param 		  	A  	First endpoint.
 * @param 		  	B  	Second endpoint.
 * @param 		  	rgb	Color.
 */

void drawLine(FrameBuffer& fb, const dvec2& A, const dvec2& B, const color& rgb) {
	if (A.x == B.x) {
		drawVerticalLine(fb, (int)A.x, (int)A.y, (int)B.y, rgb);
	} else if (A.y == B.y) {
		drawHorizontalLine(fb, (int)A.y, (int)A.x, (int)B.x, rgb);
	} else {
		drawBresenhamLine(fb, A.xy(), B.xy(), rgb);
	}
}

/**
 * @fn	void drawLine(FrameBuffer &frameBuffer, int x1, int y1, int x2, int y2, const color &C)
 * @brief	Draw line from (x1, y1) to (x2, y2)
 * @param [in,out]	frameBuffer	Framebuffer.
 * @param 		  	x1  x value of first corner
 * @param 		  	y1  y value of first corner
 * @param 		  	x2  x second of first corner
 * @param 		  	y2  y value of second corner
 * @param 		  	C   The color
 */

void drawLine(FrameBuffer& frameBuffer, int x1, int y1, int x2, int y2, const color& C) {
	drawLine(frameBuffer, dvec2(x1, y1), dvec2(x2, y2), C);
}

/**
 * @fn	void drawArc(FrameBuffer &fb, const dvec2 &center, double R,
 *						double startRads, double lengthInRads, const color &rgb)
 * @brief	Draw arc on xy plane, using traditional x-y axis orientation. Zero degrees is
 * 			+x axis, 90 degrees, is +y axis, etc.
 * @param [in,out]	fb				Framebuffer.
 * @param 		  	center			The center of the "circle".
 * @param 		  	R				Radius.
 * @param 		  	startRads   	The start of the arc, in radians.
 * @param 		  	lengthInRads	The length of the arc, in radians.
 * @param 		  	rgb				Color.
 */

void drawArc(FrameBuffer& fb, const dvec2& center, double R,
	double startRads, double lengthInRads, const color& rgb) {
	double lengthInPixels = 2 * PI * R;
	int DIV = (int)std::fmax((lengthInPixels / 5), 4);
	double radInc = lengthInRads / DIV;
	for (int i = 0; i < DIV; i++) {
		double a1 = startRads + i * radInc;
		double a2 = a1 + radInc;
		dvec2 pt1 = pointOnCircle(center, R, a1);
		dvec2 pt2 = pointOnCircle(center, R, a2);
		drawLine(fb, pt1, pt2, rgb);
	}
}

/**
 * @fn	void drawWirePolygon(FrameBuffer &fb, const vector<dvec3> &pts, const color &rgb)
 * @brief	Draw wire polygon
 * @param [in,out]	fb 	Framebuffere.
 * @param 		  	pts	The vertices of the polygon.
 * @param 		  	rgb	Color.
 */

void drawWirePolygon(FrameBuffer& fb, const vector<dvec3>& pts, const color& rgb) {
	for (unsigned int i = 1; i < pts.size(); i++) {
		drawLine(fb, pts[i - 1].xy(), pts[i].xy(), rgb);
	}
	drawLine(fb, pts[0].xy(), pts[pts.size() - 1].xy(), rgb);
}

/**
 * @fn	void drawAxisOnWindow(FrameBuffer &fb)
 * @brief	Draw the x & y axis on window, centered on window
 * @param [in,out]	fb	Framebuffer.
 */

void drawAxisOnWindow(FrameBuffer& fb) {
	int W = fb.getWindowWidth();
	int H = fb.getWindowHeight();
	int W2 = W / 2;
	int H2 = H / 2;
	drawHorizontalLine(fb, H2, 0, W - 1, red);
	drawVerticalLine(fb, W2, 0, H - 1, green);
}

/**
 * @fn	double cheapNonPerspectiveCorrectInterpolationForLines(const dvec2 &start, const dvec2 &end,
 *																const dvec2 &online)
 * @brief	Cheap non perspective correct interpolation for lines
 * @param	start 	The starting vertex.
 * @param	end   	The ending vertex
 * @param	online	The 2D point to interpolate.
 * @return	Interpolated value.
 */

static double cheapNonPerspectiveCorrectInterpolationForLines(const dvec2& start, const dvec2& end,
	const dvec2& online) {
	return glm::length(online - start) / glm::length(end - start);
}

/**
 * @fn	void drawVerticalLine(FrameBuffer &frameBuffer, const dvec3 &eyePos,
 *									const vector<LightSourcePtr> &lights,
 *									VertexData v0, VertexData v1, const dmat4 &viewingMatrix)
 * @brief	Draw vertical line
 * @param [in,out]	frameBuffer  	Framebuffer.
 * @param 		  	eyePos		 	Eye position.
 * @param 		  	lights		 	Vector of lights in scene.
 * @param 		  	v0			 	The first endpoint.
 * @param 		  	v1			 	The second endpoint.
 * @param 		  	eyeFrame	    The camera's frame.
 */

static void drawVerticalLine(FrameBuffer& frameBuffer, const dvec3& eyePos,
	const vector<LightSourcePtr>& lights, VertexData v0, VertexData v1,
	const Frame& eyeFrame) {
	if (v1.pos.y < v0.pos.y) {
		std::swap(v0, v1);
	}

	double zDifference = v1.pos.z - v0.pos.z;

	for (double y = v0.pos.y; y < v1.pos.y; y++) {
		// Interpolate vertex attributes
		double weight = cheapNonPerspectiveCorrectInterpolationForLines(v0.pos.xy(),
			v1.pos.xy(),
			dvec2(v0.pos.x, y));

		Fragment fragment;

		// Interpolate vertex attributes using alpha, beta, and gamma weights
		double oneMinusW = 1.0 - weight;
		fragment.material = weightedAverage(oneMinusW, v0.material, weight, v1.material);
		double z = weightedAverage(oneMinusW, v0.pos.z, weight, v1.pos.z);
		fragment.worldNormal = weightedAverage(oneMinusW, v0.normal, weight, v1.normal);
		fragment.worldPos = weightedAverage(oneMinusW, v0.worldPos, weight, v1.worldPos);
		fragment.windowPos = dvec3(v0.pos.x, y, z);

		FragmentOps::processFragment(frameBuffer, eyePos, lights, fragment, eyeFrame);
	}
}

/**
 * @fn	static void drawHorizontalLine(FrameBuffer &frameBuffer, const dvec3 &eyePos,
 *										const vector<LightSourcePtr> &lights,
 *										VertexData v0, VertexData v1, const Frame &eyeFrame)
 * @brief	Draw horizontal line
 * @param [in,out]	frameBuffer  	Framebuffer.
 * @param 		  	eyePos		 	Eye position.
 * @param 		  	lights		 	Vector of lights in scene.
 * @param 		  	v0			 	The first endpoint.
 * @param 		  	v1			 	The second endpoint.
 * @param 		  	eyeFrame		The camera frame.
 */

static void drawHorizontalLine(FrameBuffer& frameBuffer, const dvec3& eyePos,
	const vector<LightSourcePtr>& lights, VertexData v0, VertexData v1,
	const Frame& eyeFrame) {
	if (v1.pos.x < v0.pos.x) {
		std::swap(v0, v1);
	}

	for (double x = v0.pos.x; x < v1.pos.x; x++) {
		// Interpolate vertex attributes
		double weight = cheapNonPerspectiveCorrectInterpolationForLines(v0.pos.xy(),
			v1.pos.xy(),
			dvec2(x, v0.pos.y));

		Fragment fragment;

		// Interpolate vertex attributes using alpha, beta, and gamma weights
		fragment.material = weightedAverage(1.0 - weight, v0.material, weight, v1.material);
		double z = weightedAverage(1 - weight, v0.pos.z, weight, v1.pos.z);
		fragment.worldNormal = weightedAverage(1.0 - weight, v0.normal, weight, v1.normal);
		fragment.worldPos = weightedAverage(1.0 - weight, v0.worldPos, weight, v1.worldPos);
		fragment.windowPos = dvec3(x, v1.pos.y, z);

		FragmentOps::processFragment(frameBuffer, eyePos, lights, fragment, eyeFrame);
	}
}

/**
 * @fn	static void midPointLine(FrameBuffer &frameBuffer, const dvec3 &eyePos, const vector<LightSourcePtr> &lights, VertexData v0, VertexData v1, const dmat4 &viewingMatrix)
 * @brief	Middle point line
 * @param [in,out]	frameBuffer  	Framebuffer.
 * @param 		  	eyePos		 	Eye position.
 * @param 		  	lights		 	Vector of lights in scene.
 * @param 		  	v0			 	The first endpoint.
 * @param 		  	v1			 	The second endpoint.
 * @param 		  	eyeFrame		The camera frame.
 */

static void midPointLine(FrameBuffer& frameBuffer, const dvec3& eyePos,
	const vector<LightSourcePtr>& lights, VertexData v0, VertexData v1,
	const Frame& eyeFrame) {
	if (v1.pos.x < v0.pos.x) {
		std::swap(v0, v1);
	}

	// Calculate slope of the line
	double m = (v1.pos.y - v0.pos.y) / (v1.pos.x - v0.pos.x);

	if (m > 0 && m < 1.0) { // For slope in (0,1] More "run" than "rise"
		double y = v0.pos.y;

		for (double x = v0.pos.x; x < v1.pos.x; x += 1.0) {

			// Interpolate vertex attributes
			double weight = cheapNonPerspectiveCorrectInterpolationForLines(v0.pos.xy(),
				v1.pos.xy(),
				dvec2(x, y));

			Fragment fragment;

			// Interpolate vertex attributes using alpha, beta, and gamma weights
			fragment.material = weightedAverage(1.0 - weight, v0.material, weight, v1.material);
			double z = weightedAverage(1 - weight, v0.pos.z, weight, v1.pos.z);
			fragment.worldNormal = weightedAverage(1.0 - weight, v0.normal, weight, v1.normal);
			fragment.worldPos = weightedAverage(1.0 - weight, v0.worldPos, weight, v1.worldPos);
			fragment.windowPos = dvec3(x, y, z);

			FragmentOps::processFragment(frameBuffer, eyePos, lights, fragment, eyeFrame);

			// Evaluate the implicit equation for the line to determine if
			// the line will be above the midpoint between the pixel centers.
			double fXY = (v0.pos.y - v1.pos.y) * (x + 1.0) +
				(v1.pos.x - v0.pos.x) * (y + 0.5) +
				v0.pos.x * v1.pos.y - v1.pos.x * v0.pos.y;

			if (fXY < 0) {
				y += 1.0;
			}
		}
	} else if (m > 1) { // For slope in (1,infinity] More "run" than "rise"
		double x = v0.pos.x;

		for (double y = v0.pos.y; y < v1.pos.y; y += 1.0) {

			// Interpolate vertex attributes
			double weight = cheapNonPerspectiveCorrectInterpolationForLines(v0.pos.xy(),
				v1.pos.xy(),
				dvec2(x, y));

			Fragment fragment;

			// Interpolate vertex attributes using alpha, beta, and gamma weights
			fragment.material = weightedAverage(1.0 - weight, v0.material, weight, v1.material);
			double z = weightedAverage(1 - weight, v0.pos.z, weight, v1.pos.z);
			fragment.worldNormal = weightedAverage(1.0 - weight, v0.normal, weight, v1.normal);
			fragment.worldPos = weightedAverage(1.0 - weight, v0.worldPos, weight, v1.worldPos);
			fragment.windowPos = dvec3(x, y, z);

			FragmentOps::processFragment(frameBuffer, eyePos, lights, fragment, eyeFrame);

			// Evaluate the implicit equation for the line to determine if
			// the line will be left or right the midpoint between the pixel centers.
			double fXY = (v0.pos.y - v1.pos.y) * (x + 0.5) +
				(v1.pos.x - v0.pos.x) * (y + 1.0) +
				v0.pos.x * v1.pos.y - v1.pos.x * v0.pos.y;

			if (fXY > 0) {
				x += 1.0;
			}
		}
	} else if (m >= -1.0 && m < 0) { // For slope in [-1,0) More "run" than "rise"
		double y = v0.pos.y;
		double x = v0.pos.x;

		for (double x = v0.pos.x; x < v1.pos.x; x += 1.0) {
			// Interpolate vertex attributes
			double weight = cheapNonPerspectiveCorrectInterpolationForLines(v0.pos.xy(),
				v1.pos.xy(),
				dvec2(x, y));

			Fragment fragment;

			// Interpolate vertex attributes using alpha, beta, and gamma weights
			fragment.material = weightedAverage(1.0 - weight, v0.material, weight, v1.material);
			double z = weightedAverage(1 - weight, v0.pos.z, weight, v1.pos.z);
			fragment.worldNormal = weightedAverage(1.0 - weight, v0.normal, weight, v1.normal);
			fragment.worldPos = weightedAverage(1.0 - weight, v0.worldPos, weight, v1.worldPos);
			fragment.windowPos = dvec3(x, y, z);

			FragmentOps::processFragment(frameBuffer, eyePos, lights, fragment, eyeFrame);

			// Evaluate the implicit equation for the line to determine if
			// the line will be below the midpoint between the pixel centers.
			double fXY = (v0.pos.y - v1.pos.y) * (x + 1.0) +
				(v1.pos.x - v0.pos.x) * (y - 0.5) +
				v0.pos.x * v1.pos.y - v1.pos.x * v0.pos.y;

			if (fXY > 0) {
				y -= 1.0;
			}
		}
	} else if (m < -1) { // For slope in [-infinity,-1) More "run" than "rise"
		double x = v0.pos.x;

		for (double y = v0.pos.y; y > v1.pos.y; y -= 1.0) {

			// Interpolate vertex attributes
			double weight = cheapNonPerspectiveCorrectInterpolationForLines(v0.pos.xy(),
				v1.pos.xy(),
				dvec2(x, y));

			Fragment fragment;

			// Interpolate vertex attributes using alpha, beta, and gamma weights
			fragment.material = weightedAverage(1.0 - weight, v0.material, weight, v1.material);
			double z = weightedAverage(1 - weight, v0.pos.z, weight, v1.pos.z);
			fragment.worldNormal = weightedAverage(1.0 - weight, v0.normal, weight, v1.normal);
			fragment.worldPos = weightedAverage(1.0 - weight, v0.worldPos, weight, v1.worldPos);
			fragment.windowPos = dvec3(x, y, z);

			FragmentOps::processFragment(frameBuffer, eyePos, lights, fragment, eyeFrame);

			// Evaluate the implicit equation for the line to determine if
			// the line will be left or right the midpoint between the pixel centers.
			double fXY = (v0.pos.y - v1.pos.y) * (x + 0.5) +
				(v1.pos.x - v0.pos.x) * (y - 1.0) +
				v0.pos.x * v1.pos.y - v1.pos.x * v0.pos.y;

			if (fXY < 0) {
				x += 1.0;
			}
		}
	}
}

/**
 * @fn	void drawLine(FrameBuffer &frameBuffer, const dvec3 &eyePos,
 *						const vector<LightSourcePtr> &lights,
 *						const VertexData &v0, const VertexData &v1, const Frame &eyeFrame)
 * @brief	Draw line
 * @param [in,out]	frameBuffer  	Framebuffer.
 * @param 		  	eyePos		 	Eye position.
 * @param 		  	lights		 	Vector of lights in scene.
 * @param 		  	v0			 	The first endpoint.
 * @param 		  	v1			 	The second endpoint.
 * @param 		  	eyeFrame		The camera frame.
 */

void drawLine(FrameBuffer& frameBuffer, const dvec3& eyePos,
	const vector<LightSourcePtr>& lights,
	const VertexData& v0, const VertexData& v1,
	const Frame& eyeFrame) {
	if (v0.pos.x == v1.pos.x) {
		drawVerticalLine(frameBuffer, eyePos, lights, v0, v1, eyeFrame);
	} else if (v0.pos.y == v1.pos.y) {
		drawHorizontalLine(frameBuffer, eyePos, lights, v0, v1, eyeFrame);
	} else {
		midPointLine(frameBuffer, eyePos, lights, v0, v1, eyeFrame);
	}
}

/**
 * @fn	void drawManyLines(FrameBuffer &frameBuffer, const dvec3 &eyePos,
 *							const vector<LightSourcePtr> &lights,
 *							const vector<VertexData> &vertices, const Frame &eyeFrame)
 * @brief	Draw many lines
 * @param [in,out]	frameBuffer  	Framebuffer.
 * @param 		  	eyePos		 	Eye position.
 * @param 		  	lights		 	Vector of lights in scene.
 * @param 		  	vertices	 	Vector of vertice-pairs.
 * @param 		  	eyeFrame		The camera frame.
 */

void drawManyLines(FrameBuffer& frameBuffer, const dvec3& eyePos,
	const vector<LightSourcePtr>& lights,
	const vector<VertexData>& vertices,
	const Frame& eyeFrame) {
	for (unsigned int i = 0; (i + 1) < vertices.size(); i += 2) {
		drawLine(frameBuffer, eyePos, lights, vertices[i], vertices[i + 1], eyeFrame);
	}
}

/**
 * @fn	void drawWireFrameTriangle(FrameBuffer &frameBuffer, const dvec3 &eyePos,
 *									const vector<LightSourcePtr> &lights,
 *									const VertexData &v0, const VertexData &v1, const VertexData &v2,
 *									const Frame &eyeFrame)
 * @brief	Draw wire frame triangle.
 * @param [in,out]	frameBuffer  	Framebuffer.
 * @param 		  	eyePos		 	Eye position.
 * @param 		  	lights		 	Vector of lights in scene.
 * @param 		  	v0			 	First VertexData.
 * @param 		  	v1			 	Second VertexData.
 * @param 		  	v2			 	Third VertexData.
 * @param 		  	eyeFrame		The camera frame.
 */

void drawWireFrameTriangle(FrameBuffer& frameBuffer,
	const dvec3& eyePos,
	const vector<LightSourcePtr>& lights,
	const VertexData& v0,
	const VertexData& v1,
	const VertexData& v2,
	const Frame& eyeFrame) {
	drawLine(frameBuffer, eyePos, lights, v0, v1, eyeFrame);
	drawLine(frameBuffer, eyePos, lights, v1, v2, eyeFrame);
	drawLine(frameBuffer, eyePos, lights, v2, v0, eyeFrame);
}

/**
 * @fn	void drawManyWireFrameTriangles(FrameBuffer &frameBuffer, const dvec3 &eyePos,
 *										const vector<LightSourcePtr> &lights,
 *										const vector<VertexData> &vertices, const Frame &eyeFrame)
 * @brief	Draw many wire frame triangles
 * @param [in,out]	frameBuffer  	Framebuffer.
 * @param 		  	eyePos		 	Eye position.
 * @param 		  	lights		 	Vector of lights in scene.
 * @param 		  	vertices	 	The vector of vertex-triplets.
 * @param 		  	eyeFrame		The camera frame.
 */

void drawManyWireFrameTriangles(FrameBuffer& frameBuffer,
	const dvec3& eyePos,
	const vector<LightSourcePtr>& lights,
	const vector<VertexData>& vertices,
	const Frame& eyeFrame) {
	for (unsigned int i = 0; (i + 2) < vertices.size(); i += 3) {
		drawWireFrameTriangle(frameBuffer, eyePos, lights,
			vertices[i], vertices[i + 1], vertices[i + 2], eyeFrame);
	}
}

/**
 * @fn	static inline double f01(const VertexData &v0, const VertexData &v1, const VertexData &v2, double x, double y)
 * @brief	Computes f01. Implicit equation for the line between v0 and v1.
 * @see		*** page in textbook.
 * @param	v0	v0.
 * @param	v1	v1.
 * @param	v2	v2.
 * @param	x 	x coordinate.
 * @param	y 	y coordinate.
 * @return	f01.
 */

static inline double f01(const VertexData& v0, const VertexData& v1, const VertexData& v2,
	double x, double y) {
	return (v0.pos.y - v1.pos.y) * x + (v1.pos.x - v0.pos.x) * y +
		(v0.pos.x * v1.pos.y) - (v1.pos.x * v0.pos.y);

}

/**
 * @fn	static inline double f12(const VertexData &v0, const VertexData &v1, const VertexData &v2,
 *									double x, double y)
 * @brief	Computes f12. Implicit equation for the line between v1 and v2.
 * @see		*** page in textbook.
 * @param	v0	v0.
 * @param	v1	v1.
 * @param	v2	v2.
 * @param	x 	x coordinate.
 * @param	y 	y coordinate.
 * @return	f12.
 */

static inline double f12(const VertexData& v0, const VertexData& v1, const VertexData& v2,
	double x, double y) {
	return (v1.pos.y - v2.pos.y) * x + (v2.pos.x - v1.pos.x) * y +
		(v1.pos.x * v2.pos.y) - (v2.pos.x * v1.pos.y);

}

/**
 * @fn	static inline double f20(const VertexData &v0, const VertexData &v1, const VertexData &v2,
 *									double x, double y)
 * @brief	Computes f20. Implicit equation for the line between v2 and v0.
 * @see		*** page in textbook.
 * @param	v0	v0.
 * @param	v1	v1.
 * @param	v2	v2.
 * @param	x 	x coordinate.
 * @param	y 	y coordinate.
 * @return	f02.
 */

static inline double f20(const VertexData& v0, const VertexData& v1, const VertexData& v2,
	double x, double y) {
	return (v2.pos.y - v0.pos.y) * x + (v0.pos.x - v2.pos.x) * y +
		(v2.pos.x * v0.pos.y) - (v0.pos.x * v2.pos.y);
}

/**
 * @fn	void drawFilledTriangle(FrameBuffer &frameBuffer, const dvec3 &eyePos,
 *								const vector<LightSourcePtr> &lights,
 *								const VertexData &v0, const VertexData &v1, const VertexData &v2,
 *								const dmat4 &viewingMatrix)
 * @brief	Draw filled triangle.
 * @param [in,out]	frameBuffer  	Framebuffer.
 * @param 		  	eyePos		 	Eye position.
 * @param 		  	lights		 	Vector of lights in scene.
 * @param 		  	v0			 	v0.
 * @param 		  	v1			 	v1.
 * @param 		  	v2			 	v2.
 * @param               eyeFrame        The camera's frame.
 */

void drawFilledTriangle(FrameBuffer& frameBuffer, const dvec3& eyePos,
	const vector<LightSourcePtr>& lights,
	const VertexData& v0, const VertexData& v1, const VertexData& v2,
	const Frame& eyeFrame) {
	// Find minimimum and maximum x and y limits for the triangle
	double xMin = glm::floor(min(v0.pos.x, v1.pos.x, v2.pos.x));
	double xMax = glm::ceil(max(v0.pos.x, v1.pos.x, v2.pos.x));
	double yMin = glm::floor(min(v0.pos.y, v1.pos.y, v2.pos.y));
	double yMax = glm::ceil(max(v0.pos.y, v1.pos.y, v2.pos.y));

	double fAlpha = f12(v0, v1, v2, v0.pos.x, v0.pos.y);
	double fBeta = f20(v0, v1, v2, v1.pos.x, v1.pos.y);
	double fGamma = f01(v0, v1, v2, v2.pos.x, v2.pos.y);

	for (double y = yMin; y <= yMax; y++) {
		for (double x = xMin; x <= xMax; x++) {
			// Calculate the weights for inperpolation
			// If any weight is negative, the fragment is not in the triangle
			double alpha = f12(v0, v1, v2, x, y) / fAlpha;
			double beta = f20(v0, v1, v2, x, y) / fBeta;
			double gamma = f01(v0, v1, v2, x, y) / fGamma;

			// Determine if the pixel position is inside the triangle
			if (alpha >= 0 && beta >= 0 && gamma >= 0) {
				if ((alpha > 0 || fAlpha * f12(v0, v1, v2, -1, -1) > 0) &&
					(beta > 0 || fBeta * f20(v0, v1, v2, -1, -1) > 0) &&
					(gamma > 0 || fGamma * f01(v0, v1, v2, -1, -1) > 0)) {
					Fragment fragment;

					// Interpolate vertex attributes using alpha, beta, and gamma weights
					fragment.material = barycentricWeighting(alpha, beta, gamma,
						v0.material, v1.material, v2.material);
					fragment.worldNormal = barycentricWeighting(alpha, beta, gamma,
						v0.normal, v1.normal, v2.normal);
					fragment.worldPos = barycentricWeighting(alpha, beta, gamma,
						v0.worldPos, v1.worldPos, v2.worldPos);
					double z = barycentricWeighting(alpha, beta, gamma,
						v0.pos.z, v1.pos.z, v2.pos.z);
					fragment.windowPos = dvec3(x, y, z);
					FragmentOps::processFragment(frameBuffer, eyePos, lights, fragment, eyeFrame);
				}
			}
		}
	}
}

/**
 * @fn	void drawManyFilledTriangles(FrameBuffer &frameBuffer, const dvec3 &eyePos, const vector<LightSourcePtr> &lights, const vector<VertexData> &vertices, const dmat4 &viewingMatrix)
 * @brief	Draw many filled triangles,
 * @param [in,out]	frameBuffer  	Framebuffer.
 * @param 		  	eyePos		 	Eye position.
 * @param 		  	lights		 	Vector of lights in scene.
 * @param 		  	vertices	 	The vector of vertice-triplets.
 * @param 		  	eyeFrame    	The camera's frame.
 */

void drawManyFilledTriangles(FrameBuffer& frameBuffer, const dvec3& eyePos,
	const vector<LightSourcePtr>& lights, const vector<VertexData>& vertices,
	const Frame& eyeFrame) {
	for (int i = 0; i < (int)vertices.size() - 2; i += 3) {
		const VertexData& Vi = vertices[i];
		const VertexData& Vi1 = vertices[i + 1];
		const VertexData& Vi2 = vertices[i + 2];
		drawFilledTriangle(frameBuffer, eyePos, lights, Vi, Vi1, Vi2, eyeFrame);
	}
}
