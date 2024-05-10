#include "ishape.h"
#include "io.h"

void displayHitRecord(const HitRecord& hit) {
	if (hit.t != FLT_MAX) {
		cout << "t=" << hit.t << " intercept=" << hit.interceptPt << " normal=" << hit.normal << endl;
	} else {
		cout << "t=" << hit.t << endl;
	}
}

void checkEm(const char *name, const IShape& shape) {
	Ray ray1(dvec3(0, 0, 0), glm::normalize(dvec3(0, 0.5, -1)));	// Viewing rays are normalized
	Ray ray2(dvec3(0, 0, 0), glm::normalize(dvec3(0, 0, -1)));
	Ray ray3(dvec3(0, 0, 0), dvec3(0, -0.5, -1));
    Ray ray4(dvec3(0,0,0), dvec3(1/sqrt(3),1/sqrt(3),1/sqrt(3)));

	HitRecord hit1;
	HitRecord hit2;
	HitRecord hit3;
    HitRecord hit4;

	shape.findClosestIntersection(ray1, hit1);
	shape.findClosestIntersection(ray2, hit2);
	shape.findClosestIntersection(ray3, hit3);
    shape.findClosestIntersection(ray4, hit4);

	cout << name << endl;
	cout << "==============" << endl;
	displayHitRecord(hit1);
	displayHitRecord(hit2);
	displayHitRecord(hit3);
    displayHitRecord(hit4);
	cout << endl;
}

int main(int argc, char* argv[]) {
	double s3 = -1.0/glm::sqrt(3.0);
	checkEm("Plane", IPlane(dvec3(0, -1, 0), dvec3(0, 1, 0)));	// normal vectors will be unit length
	checkEm("Sphere", ISphere(dvec3(0.0, 0, -1.0), 0.75));
    checkEm("Sphere", ISphere(dvec3(2,1,2), 1));
	checkEm("Disk1", IDisk(dvec3(0, 0, -1), dvec3(0, 0, 1), 1.0));
	checkEm("Disk2", IDisk(dvec3(0, 0, -10), dvec3(0, 0, 1), 1.0));

	return 0;
}
/*
Plane
==============
t=3.40282e+38
t=3.40282e+38
t=2.23607 intercept=[ 0 -1 -2 ] normal=[ 0 1 0 ]

Sphere
==============
t=0.2923474621 intercept=[ 0 0.1307417596 -0.2614835193 ] normal=[ 0 0.1743223462 0.984688641 ]
t=0.25 intercept=[ 0 0 -0.25 ] normal=[ 0 0 1 ]
t=0.2923474621 intercept=[ 0 -0.1307417596 -0.2614835193 ] normal=[ 0 -0.1743223462 0.984688641 ]

Disk1
==============
t=1.118033989 intercept=[ 0 0.5 -1 ] normal=[ 0 0 1 ]
t=1 intercept=[ 0 0 -1 ] normal=[ 0 0 1 ]
t=1.118033989 intercept=[ 0 -0.5 -1 ] normal=[ 0 0 1 ]

Disk2
==============
t=3.402823466e+38
t=10 intercept=[ 0 0 -10 ] normal=[ 0 0 1 ]
t=3.402823466e+38
*/
