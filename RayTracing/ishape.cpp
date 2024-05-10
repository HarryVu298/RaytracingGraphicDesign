/****************************************************
 * 2016-2023 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#include <vector>
#include "ishape.h"
#include "io.h"

 /**
  * @fn	IShape::IShape()
  * @brief	Constructs a default IShape, centered at the origin.
  */

IShape::IShape() {
}

/**
 * @fn	void IShape::getTexCoords(const dvec3 &pt, double &u, double &v) const
 * @brief	Computes the tex coordinate of a point on the surface. The default
 * 			return value is (0, 0)
 * @param 		  	pt	The coordinate to process
 * @param [in,out]	u 	The u, in (u, v).
 * @param [in,out]	v 	The v, in (u, v).
 */

void IShape::getTexCoords(const dvec3& pt, double& u, double& v) const {
	u = v = 0;
}

/**
 * @fn	dvec3 IShape::movePointOffSurface(const dvec3 &pt, const dvec3 &n)
 * @brief	Compute point that is slightly off surface.
 * @param	pt	Intersection point.
 * @param	n 	Normal vector at pt.
 * @return	The point that is approximately EPSILON off the surface.
 */

dvec3 IShape::movePointOffSurface(const dvec3& pt, const dvec3& n) {
	/* CSE 386 - todo  */
	return pt + EPSILON * n;
}

/**
 * @fn	VisibleIShape::VisibleIShape(IShapePtr shapePtr, const Material &mat)
 * @brief	Represents an visible, implicit shape.
 * @param	shapePtr	Pointer to the implicit shape.
 * @param	mat			Material
 */

VisibleIShape::VisibleIShape(IShapePtr shapePtr, const Material& mat, Image* image)
	: material(mat), shape(shapePtr) {
	texture = image;
}

/**
 * @fn	void VisibleIShape::findClosestIntersection(const Ray &ray, HitRecord &hit) const
 * @brief	Identifies the closest intersection
 * @param 		  	ray	The ray.
 * @param [in,out]	hit	The hit that repesents the closest "hit".
 */

void VisibleIShape::findClosestIntersection(const Ray& ray, OpaqueHitRecord& hit) const {
	/* 386 - todo */
    shape->findClosestIntersection(ray, hit);
    if (hit.t != FLT_MAX) {
        hit.material = material;
    }
    hit.texture = texture;
    if (hit.texture != nullptr)
        shape->getTexCoords(hit.interceptPt, hit.u, hit.v);
}

/**
 * @fn	HitRecord VisibleIShape::findIntersection(const Ray &ray, const vector<VisibleIShapePtr> &surfaces)
 * @brief	Searches for the first intersection
 * @param	ray			The ray.
 * @param	surfaces	The surfaces in the scene.
 * @param   theHit      The closest intersection that is in front of the camera.
 */

void VisibleIShape::findIntersection(const Ray& ray, const vector<VisibleIShapePtr>& surfaces,
	OpaqueHitRecord& theHit) {
	/* CSE 386 - todo  */
    theHit.t = FLT_MAX;
    // Cycle through all the shapes and fill in the hit record
    for (unsigned int i = 0; i < surfaces.size(); i++) {
        OpaqueHitRecord thisHit;
        surfaces[i]->findClosestIntersection(ray, thisHit);
        if (thisHit.t < theHit.t) {
            theHit = thisHit;
        }
    }
}

/**
 * @fn	TransparentIShape::VisibleIShape(IShapePtr shapePtr, const color& C, double a)
 * @brief	Constructs a transparent, implicit shape.
 * @param	shapePtr	Pointer to the implicit shape.
 * @param	C			Color of transparent object
 * @param	a			Alpha value of transparent object
 */

TransparentIShape::TransparentIShape(IShapePtr shapePtr, const color& C, double a)
	: c(C), shape(shapePtr), alpha(a) {
}

/**
 * @fn	void TransparentIShape::findClosestIntersection(const Ray &ray, HitRecord &hit) const
 * @brief	Identifies the closest intersection
 * @param 		  	ray	The ray.
 * @param [in,out]	hit	The hit that repesents the closest "hit".
 */

void TransparentIShape::findClosestIntersection(const Ray& ray, TransparentHitRecord& hit) const {
	/* 386 - todo */
    shape->findClosestIntersection(ray, hit);
    if (hit.t != FLT_MAX) {
        hit.transColor = c;
        hit.alpha = alpha;
    }
}

/**
 * @fn	HitRecord VisibleIShape::findIntersection(const Ray &ray, const vector<VisibleIShapePtr> &surfaces)
 * @brief	Searches for the first intersection
 * @param	ray			The ray.
 * @param	surfaces	The surfaces in the scene.
 * @param   theHit      The closest intersection that is in front of the camera.
 */

void TransparentIShape::findIntersection(const Ray& ray, const vector<TransparentIShapePtr>& surfaces,
	TransparentHitRecord& theHit) {
	/* CSE 386 - todo  */
    theHit.t = FLT_MAX;
    // Cycle through all the shapes and fill in the hit record
    for (unsigned int i = 0; i < surfaces.size(); i++) {
        TransparentHitRecord thisHit;
        surfaces[i]->findClosestIntersection(ray, thisHit);
        if (thisHit.t < theHit.t) {
            theHit = thisHit;
        }
    }
}

/**
 * @fn	IDisk::IDisk()
 * @brief	Implicit representation of an implicit disk. Create a unit circle, centered
 *          on the origin, and lying on the x-y plane.
 */

IDisk::IDisk()
	: IShape(), center(ORIGIN3D), n(Y_AXIS), radius(1.0) {
}

/**
 * @fn	IDisk::IDisk(const dvec3 &pos, const dvec3 &normal, double rad)
 * @brief	Implicit representation of an implicit disk.
 * @param	pos   	Center of disk.
 * @param	normal	Normal vector of disk.
 * @param	rad   	Radius of disk.
 */

IDisk::IDisk(const dvec3& pos, const dvec3& normal, double rad)
	: IShape(), center(pos), n(glm::normalize(normal)), radius(rad) {
}

/**
 * @fn	void IDisk::findClosestIntersection(const Ray &ray, HitRecord &hit) const
 * @brief	Identifies the nearest intersection
 * @param 		  	ray	The ray.
 * @param [in,out]	hit	The hit.
 */

void IDisk::findClosestIntersection(const Ray& ray, HitRecord& hit) const {
	/* CSE 386 - todo  */
    double num = glm::dot(center - ray.origin, n);
    double denom = glm::dot(ray.dir, n);
    if (denom == 0) {
        hit.t = FLT_MAX;
        return;
    } else {
        double t = num / denom;
//        if (DEBUG_PIXEL) {
//            cout << "";
//        }
        if (t < 0 || glm::distance(ray.origin + t * ray.dir, center) > radius) {
//        if (t < 0) {
            hit.t = FLT_MAX;
        } else {
            // Got a legit hit!
            hit.t = t;
            hit.interceptPt = ray.origin + t * ray.dir;
            hit.normal = n;
        }
    }
}

/**
 * @fn	void IDisk::getTexCoords(const dvec3& pt, double& u, double& v) const
 * @brief	Determines the tex coords for a surface coordinate (x, y, z)
 * @param 		  	pt	The surface point
 * @param [in,out]	u	The U coordinate
 * @param [in,out]	v	The V coordinate
 */

void IDisk::getTexCoords(const dvec3& pt, double& u, double& v) const {
	// The following works only for disks oriented with a normal vector = <0, 0, 1>
	u = map(pt.x, center.x - radius, center.x + radius, 0.0, 1.0);
	v = map(pt.y, center.y - radius, center.y + radius, 0.0, 1.0);
	v = 1.0 - v;
}

/**
 * @fn	ISphere::ISphere(const dvec3 & position, double radius)
 * @brief	Implicit representation of a 3D sphere.
 * @param	position	The center of the sphere.
 * @param	radius  	The radius of the sphere.
 */

/**
* @fnITriangle::ITriangle(const dvec3 &A, const dvec3 &B, const dvec3 &C)
* @briefConstructs and implicit representation of a triangle, given three vertices
* presented in counterclockwise order.
* @param A First vertex.
* @param B Second vertex.
* @param C Third vertex.
*/
ITriangle::ITriangle(const dvec3& A, const dvec3& B, const dvec3& C) : IShape(), a(A), b(B), c(C) {

}
/**
* @fn void ITriangle::findClosestIntersection(const Ray &ray, HitRecord &hit) const
* @brief Searches for the nearest intersection
* @param ray The ray.
* @param [in,out] hit record.
*/
void ITriangle::findClosestIntersection(const Ray& ray, HitRecord& hit) const {
    dvec3 n = normalFrom3Points(a, b, c);
    IPlane plane(a, n);
    plane.findClosestIntersection(ray, hit);
    if (hit.t != FLT_MAX && !inside(hit.interceptPt)) {
        hit.t = FLT_MAX;
    }
}
/**
* @fn bool ITriangle::inside(const dvec3 &pt) const
* @brief Insides the given point
* @param pt The point.
* @return true iff the point is inside the triangle.
*/

bool ITriangle::inside(const dvec3& pt) const {
    // Fill this in with the area method
    double A = areaOfTriangle(pt, a, b);
    double B = areaOfTriangle(pt, b, c);
    double C = areaOfTriangle(pt, a, c);
    return approximatelyEqual(A+B+C, areaOfTriangle(a, b, c));
}

ISphere::ISphere(const dvec3& position, double radius)
	: IQuadricSurface(QuadricParameters::sphereQParams(radius), position) {
}

/**
 * @fn	void ISphere::getTexCoords(const dvec3 &pt, double &u, double &v) const
 * @brief	Gets texture coordinates for a point on the surface.
 * @param 		  	pt	The point on the surface.
 * @param [in,out]	u 	The u in the (u, v) texture coordinates.
 * @param [in,out]	v 	The v in the (u, v) texture coordinates.
 */

void ISphere::getTexCoords(const dvec3& pt, double& u, double& v) const {
	double az, el;
	double R;
	dvec3 delta = pt - center;
	computeAzimuthAndElevationFromXYZ(delta, R, az, el);
	u = map(az, -PI, PI, 0.0, 1.0);
	v = 1.0 - map(el, -PI_2, PI_2, 0.0, 1.0);
}

/**
 * @fn	QuadricParameters::QuadricParameters()
 * @brief	Default constructor
 */

QuadricParameters::QuadricParameters()
	: QuadricParameters(vector<double> {1, 1, 1, 0, 0, 0, 0, 0, 0, -1}) {
}

/**
 * @fn	QuadricParameters::QuadricParameters(const vector<double> &items)
 * @brief	Constructor using 10 values.
 * @param	items	The items.
 */

QuadricParameters::QuadricParameters(const vector<double>& items)
	: A(items[0]), B(items[1]), C(items[2]), D(items[3]),
	E(items[4]), F(items[5]), G(items[6]), H(items[7]),
	I(items[8]), J(items[9]) {
}

/**
 * @fn	QuadricParameters::QuadricParameters(double a, double b, double c, double d,
 *											double e, double , double g, double h, double i,
 *											double j)
 * @brief	Constructor
 * @param	a	Quadric parameter A.
 * @param	b	Quadric parameter B.
 * @param	c	Quadric parameter C.
 * @param	d	Quadric parameter D.
 * @param	e	Quadric parameter E.
 * @param	f	Quadric parameter F.
 * @param	g	Quadric parameter G.
 * @param	h	Quadric parameter H.
 * @param	i	Quadric parameter I.
 * @param	j	Quadric parameter J.
 */

QuadricParameters::QuadricParameters(double a, double b, double c, double d, double e, double f,
	double g, double h, double i, double j)
	: QuadricParameters(vector<double> {a, b, c, d, e, f, g, h, i, j}) {
}

/**
 * @fn	QuadricParameters QuadricParameters::cylinderXQParams(double R)
 * @brief	Constructs the parameters for a cylinder oriented along the x axis.
 * @param	R	Radius of cylinder.
 * @return	The QuadricParameters.
 */

QuadricParameters QuadricParameters::cylinderXQParams(double R) {
	double R2 = R * R;
	return QuadricParameters(0.0, 1.0 / R2, 1.0 / R2, 0, 0, 0, 0, 0, 0, -1);
}

/**
 * @fn	QuadricParameters QuadricParameters::cylinderYQParams(double R)
 * @brief	Constructs the parameters for a cylinder oriented along the y axis.
 * @param	R	Radius of cylinder.
 * @return	The QuadricParameters.
 */

QuadricParameters QuadricParameters::cylinderYQParams(double R) {
	double R2 = R * R;
	return QuadricParameters(1.0 / R2, 0, 1.0 / R2, 0, 0, 0, 0, 0, 0, -1);
}

/**
 * @fn	QuadricParameters QuadricParameters::cylinderZQParams(double R)
 * @brief	Constructs the parameters for a cylinder oriented along the z axis.
 * @param	R	Radius of cylinder.
 * @return	The QuadricParameters.
 */

QuadricParameters QuadricParameters::cylinderZQParams(double R) {
	double R2 = R * R;
	return QuadricParameters(1.0 / R2, 1.0 / R2, 0, 0, 0, 0, 0, 0, 0, -1);
}

/**
 * @fn	QuadricParameters QuadricParameters::sphereQParams(double R)
 * @brief	Constructs the parameters for a sphere centered on the origin.
 * @param	R	Radius of cylinder.
 * @return	The QuadricParameters.
 */

QuadricParameters QuadricParameters::sphereQParams(double R) {
	double R2 = R * R;
	return QuadricParameters(1, 1, 1, 0, 0, 0, 0, 0, 0, -R2);
}

/**
 * @fn	QuadricParameters QuadricParameters::ellipsoidQParams(dvec3 sz)
 * @brief	Ellipoid parameters
 * @param	sz	Size of ellipsoid.
 * @return	The QuadricParameters.
 */

QuadricParameters QuadricParameters::ellipsoidQParams(const dvec3& sz) {
	dvec3 size = sz * sz;
	return QuadricParameters(1.0 / size.x, 1.0 / size.y, 1.0 / size.z,
		0, 0, 0, 0, 0, 0, -1);
}

/**
 * @fn	QuadricParameters QuadricParameters::cylinderXQParams(double R)
 * @brief	Constructs the parameters for a cylinder oriented along the x axis.
 * @param	R	Radius of cylinder.
 * @return	The QuadricParameters.
 */

QuadricParameters QuadricParameters::coneYQParams(double R, double H) {
	double R2 = glm::pow(H, 2.0) / glm::pow(R, 2.0);
	return QuadricParameters(R2, -1.0, R2, 0, 0, 0, 0, 0, 0, 0);
}

/**
 * @fn	IPlane::IPlane(const dvec3 &point, const dvec3 &normal)
 * @brief	Constructor
 * @param	point 	A point on the plane.
 * @param	normal	The plane's normal.
 */

IPlane::IPlane(const dvec3& point, const dvec3& normal)
	: IShape(), a(point), n(normalize(normal)) {
}

/**
 * @fn	IPlane::IPlane(const vector<dvec3> &vertices)
 * @brief	Constructor
 * @param	vertices	The three vertices.
 */

IPlane::IPlane(const vector<dvec3>& vertices)
	: IShape() {
	a = vertices[0];
	n = glm::normalize(glm::cross(vertices[2] - vertices[1], vertices[0] - vertices[1]));
}

/**
 * @fn	IPlane::IPlane(const dvec3 &p0, const dvec3 &p1, const dvec3 &p2)
 * @brief	Constructor
 * @param	p0	The p 0.
 * @param	p1	The first dvec3.
 * @param	p2	The second dvec3.
 */

IPlane::IPlane(const dvec3& p0, const dvec3& p1, const dvec3& p2)
	: IShape(), a(p1), n(glm::normalize(glm::cross(p2 - p1, p0 - p1))) {
}

IPlane::IPlane()
	: IShape(), a(ORIGIN3D), n(Z_AXIS) {
}

/**
 * @fn	bool IPlane::onFrontSide(const dvec3 &point) const
 * @brief	Determines if point is on the "front side of plane"
 * @param	point	The point.
 * @return	True if it succeeds, false if it fails.
 */

bool IPlane::onFrontSide(const dvec3& point) const {
	// If dot product is positive the point is on the "positive" side of the plane
	bool onFront = glm::dot(point.xyz() - a, n) >= 0.0;
	return onFront;
}

/**
 * @fn	void IPlane::findClosestIntersection(const Ray &ray, HitRecord &hit) const
 * @brief	Find the HitRecord for this plane and the passed Ray. The t value of
 *          the HitRecord will be MAX_FLT, if there is no intersection. There are
 *          two ways to produce a non-existant intersection:
 *              1. The ray is parallel to the plane
 * 				2. The intersection is behind the ray's origin
 * @param 		  	ray	The ray.
 * @param [in,out]	hit	The hit.
 */
// IPlane - a, n
// Ray - origin, dir
// HitRecord - t, interceptPt, normal

void IPlane::findClosestIntersection(const Ray& ray, HitRecord& hit) const {
	/* CSE 386 - todo  */
    double num = glm::dot(a - ray.origin, n);
    double denom = glm::dot(ray.dir, n);
    if (denom == 0) {
        hit.t = FLT_MAX;
        return;
    } else {
        double t = num / denom;
        if (t < 0) {
            hit.t = FLT_MAX;
        } else {
            // Got a legit hit!
            hit.t = t;
            hit.interceptPt = ray.origin + t * ray.dir;
            hit.normal = n;
        }
    }
}

/**
 * @fn	void IPlane::findIntersection(const dvec3 &p1, const dvec3 &p2, double &t) const
 * @brief	Searches for the first intersection between a line segment. Used in the pipeline.
 * @param 	p1	The first point
 * @param 	p2	The second piont.
 * @param [in,out]	t 	The value of t where the intersection takes place.
 */

void IPlane::findIntersection(const dvec3& p1, const dvec3& p2, double& t) const {
	double d1 = glm::dot(p1.xyz() - a, n);
	double d2 = glm::dot(p2.xyz() - a, n);

	// Find the paramter of the intercept with the plane
	t = d1 / (d1 - d2);
}

/**
* @fn	dvec3 normalFrom3Points(const dvec3 &pt0, const dvec3 &pt1, const dvec3 &pt2)
* @brief	Computes a unit-length normal vector from 3 points, specified in counterclockwise order.
* @param	pt0	The first point.
* @param	pt1	The second point.
* @param	pt2	The third point.
* @return	Normal vector.
*/

dvec3 normalFrom3Points(const dvec3& pt0, const dvec3& pt1, const dvec3& pt2) {
	dvec3 v1 = pt1 - pt0;
	dvec3 v2 = pt2 - pt0;
	dvec3 cross = glm::normalize(glm::cross(v1, v2));
	return cross;
}

/**
* @fn	dvec3 normalFrom3Points(const vector<dvec3> pts)
* @brief	Computes a unit-length normal vector from 3 points, specified in counterclockwise order.
* @param	pts	The points.
* @return	The normal vector.
*/

dvec3 normalFrom3Points(const vector<dvec3>& pts) {
	return normalFrom3Points(pts[0], pts[1], pts[2]);
}
/**
* @fn	bool equalPlanes(const IPlane& p1, const IPlane& p2)
* @brief	Determines if two IPlanes are identical.
* @param	p1 The first IPlane
* @param    p2 The second IPlane
* @return	true iff the planes consist of the same points and have
*           the same positive and negative sides. You can assume
*			that perfect arithmetic is performed (i.e., no errors
*			are introduced).
* Some tests that can be put into main:
int main(int argc, char *argv[]) {
	IPlane p1(dvec3(0, 0, 0), dvec3(0, 1, 0));
	IPlane p2(dvec3(1, 0, 1), dvec3(0, 2, 0));
	IPlane p3(dvec3(0, 1, 0), dvec3(0, 1, 0));
	IPlane p4(dvec3(0, 0, 0), dvec3(1, 1, 0));
	IPlane p5(dvec3(-1, 1, 0), dvec3(1, 1, 0));

	IPlane planes[] = { p1, p2, p3, p4, p5 };
	for (int i = 0; i < 5; i++) {
		for (int j=0; j<5; j++)
			cout << equalPlanes(planes[i], planes[j]) << ' ';
		cout << endl;
	}
	return 0;
}
Output:
	1 1 0 0 0
	1 1 0 0 0
	0 0 1 0 0
	0 0 0 1 1
	0 0 0 1 1
*/

bool equalPlanes(const IPlane& p1, const IPlane& p2) {
	// CSE 386 - todo
	return false;
}

/**
 * @fn	IQuadricSurface::IQuadricSurface(const QuadricParameters &params, const dvec3 &position)
 * @brief	Constructs an implicit representation of a QuadricSurface.
 * @param	params  	Options for controlling the operation.
 * @param	position	The position.
 */

IQuadricSurface::IQuadricSurface(const QuadricParameters& params, const dvec3& position)
	: IShape(), qParams(params), center(position) {
	twoA = 2.0 * qParams.A;
	twoB = 2.0 * qParams.B;
	twoC = 2.0 * qParams.C;
}

/**
 * @fn	IQuadricSurface::IQuadricSurface(const vector<double> &params, const dvec3 &position)
 * @brief	Constructs an implicit representation of a QuadricSurface.
 * @param	params  	Quadric parameters.
 * @param	position	The position of the quadric.
 */

IQuadricSurface::IQuadricSurface(const vector<double>& params,
	const dvec3& position)
	: IQuadricSurface(QuadricParameters(params), position) {
}

/**
 * @fn	IQuadricSurface::IQuadricSurface(const dvec3 &position)
 * @brief	Constructs an implicit representation of a QuadricSurface.
 * @param	position	The position of the quadric.
 */

IQuadricSurface::IQuadricSurface(const dvec3& position)
	: IQuadricSurface(QuadricParameters(), position) {
}

/**
 * @fn	void IQuadricSurface::computeAqBqCq(const Ray &ray, double &Aq, double &Bq, double &Cq) const
 * @brief	Calculates the aq bq cq
 * @param 		  	ray	The ray.
 * @param [in,out]	Aq 	The aq.
 * @param [in,out]	Bq 	The bq.
 * @param [in,out]	Cq 	The cq.
 */

void IQuadricSurface::computeAqBqCq(const Ray& ray, double& Aq, double& Bq, double& Cq) const {
	dvec3 Ro = ray.origin - center;
	const dvec3& Rd = ray.dir;
	const double& A = qParams.A;
	const double& B = qParams.B;
	const double& C = qParams.C;
	const double& D = qParams.D;
	const double& E = qParams.E;
	const double& F = qParams.F;
	const double& G = qParams.G;
	const double& H = qParams.H;
	const double& I = qParams.I;
	const double& J = qParams.J;
	Aq = A * (Rd.x * Rd.x) +
		B * (Rd.y * Rd.y) +
		C * (Rd.z * Rd.z) +
		D * (Rd.x * Rd.y) +
		E * (Rd.x * Rd.z) +
		F * (Rd.y * Rd.z);

	Bq = twoA * Ro.x * Rd.x +
		twoB * Ro.y * Rd.y +
		twoC * Ro.z * Rd.z +
		D * (Ro.x * Rd.y + Ro.y * Rd.x) +
		E * (Ro.x * Rd.z + Ro.z * Rd.x) +
		F * (Ro.y * Rd.z + Ro.z * Rd.y) +
		G * Rd.x + H * Rd.y + I * Rd.z;

	Cq = A * (Ro.x * Ro.x) +
		B * (Ro.y * Ro.y) +
		C * (Ro.z * Ro.z) +
		D * (Ro.x * Ro.y) +
		E * (Ro.x * Ro.z) +
		F * (Ro.y * Ro.z) +
		G * Ro.x +
		H * Ro.y +
		I * Ro.z + J;
}

/**
 * @fn	int IQuadricSurface::findIntersections(const Ray &ray, HitRecord hits[2]) const
 * @brief	Identifies the intersections that appear in front of the viewer. These
 *          are sorted by distance from viewer.
 * @param	ray 	The ray.
 * @param	hits	The hits.
 * @return	The found intersections.
 */

int IQuadricSurface::findIntersections(const Ray& ray, HitRecord hits[2]) const {
	double Aq, Bq, Cq;
	computeAqBqCq(ray, Aq, Bq, Cq);
	double roots[2];

	int numRoots = quadratic(Aq, Bq, Cq, roots);
	int numIntersections = 0;

	for (int i = 0; i < numRoots; i++) {
		if (roots[i] > 0) {
			const double& t = roots[i];
			hits[numIntersections].t = t;
			hits[numIntersections].interceptPt = ray.origin + t * ray.dir;
			const dvec3& intercept = hits[numIntersections].interceptPt;
			hits[numIntersections].normal = normal(intercept);
			numIntersections++;
		}
	}

	return numIntersections;
}

/**
 * @fn	void IQuadricSurface::findClosestIntersection(const Ray &ray, HitRecord &hit) const
 * @brief	Searches for the nearest intersection
 * @param 		  	ray	The ray.
 * @param [in,out]	hit	The hit.
 */

void IQuadricSurface::findClosestIntersection(const Ray& ray, HitRecord& hit) const {
	HitRecord hits[2];
	hit.t = FLT_MAX;

	int numIntercepts = findIntersections(ray, hits);
	if (numIntercepts == 1 && hits[0].t > 0) {
		hit.t = hits[0].t;
		hit.interceptPt = hits[0].interceptPt;
		hit.normal = normal(hit.interceptPt);
	} else if (numIntercepts == 2) {
		if (hits[0].t > 0) {
			hit.t = hits[0].t;
			hit.interceptPt = hits[0].interceptPt;
			hit.normal = normal(hit.interceptPt);
		} else if (hits[1].t > 0) {
			hit.t = hits[1].t;
			hit.interceptPt = hits[1].interceptPt;
			hit.normal = normal(hit.interceptPt);
		}
	}
}

/**
 * @fn	dvec3 IQuadricSurface::normal(const dvec3 &P) const
 * @brief	Normals the given p
 * @param	P	A dvec3 to process.
 * @return	A dvec3.
 */

dvec3 IQuadricSurface::normal(const dvec3& P) const {
	const double& A = qParams.A;
	const double& B = qParams.B;
	const double& C = qParams.C;
	const double& D = qParams.D;
	const double& E = qParams.E;
	const double& F = qParams.F;
	const double& G = qParams.G;
	const double& H = qParams.H;
	const double& I = qParams.I;
	const double& J = qParams.J;
	dvec3 pt = P - center;
	dvec3 normal(twoA * pt.x + D * pt.y + E * pt.z + G,
		twoB * pt.y + D * pt.x + F * pt.z + H,
		twoC * pt.z + E * pt.x + F * pt.y + I);
	return glm::normalize(normal);
}

/**
 * @fn	ICylinder::ICylinder(const dvec3 &pos, double R, double L, const QuadricParameters &qParams)
 * @brief	Constructs an implicit representation of a cylinder.
 * @param	pos	   	The position.
 * @param	R	   	Radius.
 * @param	L	   	Length of cylinder.
 * @param	qParams	Quadric parameters.
 */

ICylinder::ICylinder(const dvec3& pos, double R, double L,
	const QuadricParameters& qParams)
	: IQuadricSurface(qParams, pos), radius(R), length(L) {
}

/**
 * @fn	ICone::ICone(const dvec3 &pos, double R, double H, const QuadricParameters &qParams)
 * @brief	Constructs an implicit representation of a cylinder.
 * @param	pos	   	The position.
 * @param	R	   	Radius at the base of the cone.
 * @param	H	   	Height of cone.
 * @param	qParams	Quadric parameters.
 */

ICone::ICone(const dvec3& pos, double R, double H, const QuadricParameters& qParams)
	: IQuadricSurface(qParams, pos), radius(R), height(H) {
}

/**
 * @fn	IConeY::IConeY(const dvec3 &pos, double rad, double height)
 * @brief	Constructor for a cone oriented with the y axis. There is no
 *          "bottom-lid" to the cone. The center can be at the cone's tip,
 *			or at the center of the base. The height will be H.
 * @param	pos	The position.
 * @param	rad	The radius of the cone at its base.
 * @param	H   The height of the cone.
 */

IConeY::IConeY(const dvec3& pos, double rad, double H)
	: ICone(pos, rad, H, QuadricParameters::coneYQParams(rad, H)) {
}

/**
 * @fn	void ICone::findClosestIntersection(const Ray &ray, HitRecord &hit) const
 * @brief	Searches for the nearest intersection
 * @param 		  	ray	The ray.
 * @param [in,out]	hit	The hit.
 */

void IConeY::findClosestIntersection(const Ray& ray, HitRecord& hit) const {
	static HitRecord hits[2];
	int numHits = IQuadricSurface::findIntersections(ray, hits);

    for (int i = 0; i < numHits; i++) {
        if (hits[i].interceptPt.y <= center.y && hits[i].interceptPt.y >= center.y - height) {
            hit = hits[i];
            break;
        } else {
            hit.t = FLT_MAX;
        }
    }
	return;
}

/**
 * @fn	ICylinderY::ICylinderY(const dvec3 &pos, double rad, double len)
 * @brief	Default constructor
 */

ICylinderY::ICylinderY()
	: ICylinder(ORIGIN3D, 1.0, 1.0, QuadricParameters::cylinderYQParams(1.0)) {
}

/**
 * @fn	ICylinderY::ICylinderY(const dvec3 &pos, double rad, double len)
 * @brief	Constructor
 * @param	pos	The position.
 * @param	rad	The radians.
 * @param	len	The length.
 */

ICylinderY::ICylinderY(const dvec3& pos, double rad, double len)
	: ICylinder(pos, rad, len, QuadricParameters::cylinderYQParams(rad)) {
}

/**
 * @fn	void ICylinderY::findClosestIntersection(const Ray &ray, HitRecord &hit) const
 * @brief	Searches for the nearest intersection
 * @param 		  	ray	The ray.
 * @param [in,out]	hit	The hit.
 */

void ICylinderY::findClosestIntersection(const Ray& ray, HitRecord& hit) const {
	HitRecord hits[2];
	int numHits = IQuadricSurface::findIntersections(ray, hits);

    for (int i = 0; i < numHits; i++) {
        if (hits[i].interceptPt.y >= center.y - length/2 && hits[i].interceptPt.y <= center.y + length/2) {
            hit = hits[i];
            break;
        } else {
            hit.t = FLT_MAX;
        }
    }
}

/**
* @fn	void ICylinderY::getTexCoords(const dvec3 &pt, double &u, double &v) const
* @brief	Gets tex coordinates
* @param 		  	pt	The point.
* @param [in,out]	u 	Tex coordinate u.
* @param [in,out]	v 	Tex coordinate v.
*/

void ICylinderY::getTexCoords(const dvec3& pt, double& u, double& v) const {
	/* CSE 386 - todo  */
    u = map(directionInRadians(center.x, center.z, pt.x, pt.z), 0, 2*PI, 0, 1);
    v = map(pt.y, center.y - length/2, center.y + length/2, 0, 1);
    v = 1- v;
}

/**
 * @fn    ICylinderY::ICylinderY(const dvec3 &pos, double rad, double len)
 * @brief    Constructor
 * @param    pos    The position.
 * @param    rad    The radius.
 * @param    len    The length.
 */
IClosedCylinderY::IClosedCylinderY(const dvec3& pos, double rad, double len)
    : body(pos, rad, len), top(pos + dvec3(0,len/2,0), dvec3(0,1,0), rad), bottom(pos - dvec3(0,len/2,0), dvec3(0,-1,0), rad) {
}

/**
 * @fn    void IClosedCylinderY::findClosestIntersection(const Ray &ray, HitRecord &hit) const
 * @brief    Searches for the nearest intersection
 * @param               ray    The ray.
 * @param [in,out]    hit    The hit.
 */
void IClosedCylinderY::findClosestIntersection(const Ray& ray, HitRecord& hit) const {
    HitRecord currHit;
    hit.t = FLT_MAX;
    body.findClosestIntersection(ray, currHit);
    if (currHit.t < hit.t) {
        hit = currHit;
    }
    top.findClosestIntersection(ray, currHit);
    if (currHit.t < hit.t) {
        hit = currHit;
    }
    
    bottom.findClosestIntersection(ray, currHit);
    if (currHit.t < hit.t) {
        hit = currHit;
    }
}

/**
* @fn    void IClosedCylinderY::getTexCoords(const dvec3 &pt, double &u, double &v) const
* @brief    Gets tex coordinates
* @param               pt    The point.
* @param [in,out]    u     Tex coordinate u.
* @param [in,out]    v     Tex coordinate v.
*/

void IClosedCylinderY::getTexCoords(const dvec3& pt, double& u, double& v) const {
    /* CSE 386 - todo  */
    u = map(directionInRadians(body.center.x, body.center.z, pt.x, pt.z), 0, 2*PI, 0, 1);
    v = map(pt.y, body.center.y - body.length/2, body.center.y + body.length/2, 0, 1);
    v = 1- v;
}


/**
 * @fn    ICylinderZ::ICylinderZ(const dvec3 &pos, double rad, double len)
 * @brief    Default constructor
 */

ICylinderZ::ICylinderZ()
    : ICylinder(ORIGIN3D, 1.0, 1.0, QuadricParameters::cylinderZQParams(1.0)) {
}

/**
 * @fn    ICylinderZ::ICylinderZ(const dvec3 &pos, double rad, double len)
 * @brief    Constructor
 * @param    pos    The position.
 * @param    rad    The radians.
 * @param    len    The length.
 */

ICylinderZ::ICylinderZ(const dvec3& pos, double rad, double len)
    : ICylinder(pos, rad, len, QuadricParameters::cylinderZQParams(rad)) {
}

/**
 * @fn    void ICylinderZ::findClosestIntersection(const Ray &ray, HitRecord &hit) const
 * @brief    Searches for the nearest intersection
 * @param               ray    The ray.
 * @param [in,out]    hit    The hit.
 */

void ICylinderZ::findClosestIntersection(const Ray& ray, HitRecord& hit) const {
    HitRecord hits[2];
    int numHits = IQuadricSurface::findIntersections(ray, hits);

    for (int i = 0; i < numHits; i++) {
        if (hits[i].interceptPt.z >= center.z - length/2 && hits[i].interceptPt.z <= center.z + length/2) {
            hit = hits[i];
            break;
        } else {
            hit.t = FLT_MAX;
        }
    }
}

/**
* @fn    void ICylinderZ::getTexCoords(const dvec3 &pt, double &u, double &v) const
* @brief    Gets tex coordinates
* @param               pt    The point.
* @param [in,out]    u     Tex coordinate u.
* @param [in,out]    v     Tex coordinate v.
*/

void ICylinderZ::getTexCoords(const dvec3& pt, double& u, double& v) const {
    /* CSE 386 - todo  */
    u = map(directionInRadians(center.x, center.y, pt.x, pt.y), 0, 2*PI, 0, 1);
    v = map(pt.z, center.z - length/2, center.z + length/2, 0, 1);
    v = 1 - v;
}
/**
 * @fn	IEllipsoid::IEllipsoid(const dvec3 &position, const dvec3 &sz)
 * @brief	Constructs an implicit representation of an ellipsoid.
 * @param	position	The center of ellipsoid.
 * @param	sz			The size of ellipsoid.
 */



IEllipsoid::IEllipsoid(const dvec3& position, const dvec3& sz)
	: IQuadricSurface(QuadricParameters::ellipsoidQParams(sz), position) {
}
