#include "ishape.h"
#include "io.h"
#include "utilities.h"


bool isOnPlane(const IPlane& plane, const dvec3& pt) {
	dvec3 delta = pt - plane.a;
	double dp = glm::dot(delta, plane.n);
	return approximatelyZero(dp);
}

string msg(bool inout) {
	return inout ? "IN" : "OUT";
}

// The x value of the plane's normal vector must <> 0 for this to work
void systematic(const dvec3& a, const dvec3& b, const dvec3& c, const ITriangle tri) {
	dvec3 mins(min(a.x, b.x, c.x), min(a.y, b.y, c.y), min(a.z, b.z, c.z));
	dvec3 maxs(max(a.x, b.x, c.x), max(a.y, b.y, c.y), max(a.z, b.z, c.z));

	IPlane plane(a, b, c);
	dvec3 n = plane.n;

	// Generate a bunch of points on the plane. These will be in the vicinity
	// of the triangle. Some will be inside, some outside.
	const double N = 2;
	const dvec3 delta = maxs - mins;
	const double DX = delta.x > 0 ? delta.x / N : 0.01;
	const double DY = delta.y > 0 ? delta.y / N : 0.01;
	const double DZ = delta.z > 0 ? delta.z / N : 0.01;

	mins = mins - dvec3(0.01, 0.02, 0.03);
	maxs = maxs + dvec3(0.01, 0.02, 0.03);

	for (double z = mins.z; z <= maxs.z; z += DZ) {
		for (double y = mins.y; y <= maxs.y; y += DY) {
			dvec2 pt(y, z);
			double x = (glm::dot(n.yz(), a.yz()) - glm::dot(n.yz(), pt) + n.x * a.x) / n.x;
			cout << x << ' ' << y << ' ' << z << ' ' << msg(tri.inside(dvec3(x, y, z))) << endl;
			//			cout << isOnPlane(plane, dvec3(x, y, z)) << endl;
		}
	}
}

int main(int argc, char* argv[]) {
	dvec3 A(0, 0, 0);
	dvec3 B(0, 1, 0);
	dvec3 C(0, 1, 1);

	ITriangle tri1(A, B, C);

	// Your method needs to tolerate tiny errors in computation

	cout << "Tri 1 - explicit values" << endl;
	cout << msg(tri1.inside(dvec3(0.0000000, 0.0000003, 0.0000001))) << endl;
	cout << msg(tri1.inside(dvec3(0.0000000001, 0.5000001, 0.0000001))) << endl;
	cout << msg(tri1.inside(dvec3(-0.000000000001, 0.500000, 0.050001))) << endl;
	cout << msg(tri1.inside(dvec3(0.0000000000, 0.500000, 0.600000))) << endl;
	cout << msg(tri1.inside(dvec3(0.0000000, 0.9000000, 0.8000000))) << endl;
	cout << msg(tri1.inside(dvec3(0.00000001, 0.9999990, 0.5000000))) << endl;
	cout << msg(tri1.inside(dvec3(0.0000000, 0.00000001, -0.010000))) << endl;

	dvec3 J(-5, 5, 5);
	dvec3 K(-5, 5, 0);
	dvec3 L(-6, 10, 0);

	ITriangle tri2(J, K, L);

	cout << "Tri 2 - explicit values" << endl;

	cout << msg(tri2.inside(dvec3(-5.3345638528770358, 6.6728192643851800, 2.7209448476279947))) << endl;
	cout << msg(tri2.inside(dvec3(-5.1187482051806317, 5.5937410259031548, 1.0331078092452692))) << endl;
	cout << msg(tri2.inside(dvec3(-5.2039294101678664, 6.0196470508393256, 2.3564421223345260))) << endl;

	cout << "Tri 1 - systematic " << endl;
	systematic(A, B, C, tri1);

	cout << "Tri 2 - systematic " << endl;
	systematic(J, K, L, tri2);

	return 0;
}

/*
Tri 1 - explicit values
IN
IN
IN
OUT
IN
IN
OUT
Tri 2 - explicit values
IN
IN
IN
Tri 1 - systematic
0 -0.02 -0.03 OUT
0 0.48 -0.03 OUT
0 0.98 -0.03 OUT
0 -0.02 0.47 OUT
0 0.48 0.47 IN
0 0.98 0.47 IN
0 -0.02 0.97 OUT
0 0.48 0.97 OUT
0 0.98 0.97 IN
Tri 2 - systematic
-4.996 4.98 -0.03 OUT
-5.496 7.48 -0.03 OUT
-5.996 9.98 -0.03 OUT
-4.996 4.98 2.47 OUT
-5.496 7.48 2.47 IN
-5.996 9.98 2.47 OUT
-4.996 4.98 4.97 OUT
-5.496 7.48 4.97 OUT
-5.996 9.98 4.97 OUT

*/