#include <iostream>
#include "defs.h"
#include "io.h"
#include "light.h"
#include "camera.h"

void checkItOut(const dvec3& spotPos, const dvec3& spotDir, double spotFOV,
	const dvec3& intercept) {
	cout << "Pos: " << spotPos <<
		" Dir: " << spotDir <<
		" FOV: " << spotFOV <<
		" Intercept: " << intercept << "   " << (SpotLight::isInSpotlightCone(spotPos, spotDir, spotFOV, intercept) ? "true" : "false") << endl;
}

int main(int argc, char* argv[]) {
	dvec3 centerSpotlight(0.0, 1.0, 0.0);
	dvec3 leftSpotlight(-1.0, 1.0, 0.0);
	dvec3 rightSpotlight(+1.0, 1.0, 0.0);

	dvec3 straightDown(0.0, -1.0, 0.0);
	dvec3 towardRight = glm::normalize(dvec3(1.0, -1.0, 0.0));
	dvec3 towardLef = glm::normalize(dvec3(-1.0, -1.0, 0.0));

	dvec3 spotPos[] = { leftSpotlight, centerSpotlight, rightSpotlight };
	dvec3 spotDir[] = { straightDown, towardRight, towardLef };
	double fovs[] = { PI_3, 0.8*PI };

	dvec3 intercepts[] = { dvec3(-1.0, 0.0, 0.0), ORIGIN3D, dvec3(+1.0, 0.0, 0.0) };

	for (const dvec3& dir : spotDir) {
		for (const dvec3& pos : spotPos) {
			for (const dvec3& i : intercepts) {
				for (const double fov : fovs) {
					checkItOut(pos, dir, fov, i);
				}
			}
		}
	}

	cout << endl << "Other examples:" << endl;
	checkItOut(dvec3(1.0, 1.0, 1.0), glm::normalize(dvec3(-1.0, -1.0, -1.0)), PI_3, dvec3(0.0, 0.0, 0.0));
	checkItOut(dvec3(1.0, 1.0, 1.0), glm::normalize(dvec3(-1.0, -1.0, -1.0)), PI_3, dvec3(-2.0, 0.0, 0.0));
	checkItOut(dvec3(1.0, 1.0, 1.0), glm::normalize(dvec3(-1.0, -1.0, -1.0)), PI_3, dvec3(+2.0, 0.0, 0.0));
	checkItOut(dvec3(1.0, 1.0, 1.0), glm::normalize(dvec3(-1.0, -1.0, -1.0)), PI_3, dvec3(-5.0, 0.0, -5.0));
	checkItOut(dvec3(1.0, 1.0, 1.0), glm::normalize(dvec3(-1.0, -1.0, -1.0)), PI_3, dvec3(-10.0, 0.0, -10.0));
	checkItOut(dvec3(1.0, 1.0, 1.0), glm::normalize(dvec3(-1.0, -1.0, -1.0)), PI_3, dvec3(-10.0, -10.0, -10.0));
	checkItOut(dvec3(1.0, 1.0, 1.0), glm::normalize(dvec3(-1.0, -1.0, -1.0)), PI_3, dvec3(10.0, 10.0, 10.0));


	cout << endl << "Spotlight::illuminate" << endl;
	{
		color spotColor(1.0, 1.0, 1.0);
		dvec3 spotPos(0.0, 1.0, 0.0);
		dvec3 spotDir(0.0, -1.0, 0.0);
		LightATParams spotATParams(1.0, 2.0, 0.0);
		bool useAttenuation = false;

		dvec3 eyePos = spotPos;
		dvec3 eyeFocus(0.0, 0.0, 0.0);
		PerspectiveCamera pCamera(eyePos, eyeFocus, Y_AXIS, PI_2, 100, 100);

		SpotLight spot(spotPos, spotDir, PI_2, spotColor);

		dvec3 n(0.0, 0.0, 1.0);

		cout << spot.illuminate(dvec3(0.0, 0.0, 0.0), dvec3(0.0, 1.0, 0.0), tin, pCamera.getFrame(), false) << endl;
		cout << spot.illuminate(dvec3(0.0, 0.0, 0.0), dvec3(0.0, 1.0, 0.0), tin, pCamera.getFrame(), true) << endl;
		cout << spot.illuminate(dvec3(1.0, 0.0, 0.0), dvec3(0.0, 1.0, 0.0), tin, pCamera.getFrame(), false) << endl;
		cout << spot.illuminate(dvec3(1.0, 0.0, 0.0), dvec3(0.0, 1.0, 0.0), tin, pCamera.getFrame(), true) << endl;
	}

	return 0;
}
/*
SpotlightCone
Pos: [ -1 1 0 ] Dir: [ 0 -1 0 ] FOV: 1.047197551 Intercept: [ -1 0 0 ]   true
Pos: [ -1 1 0 ] Dir: [ 0 -1 0 ] FOV: 2.513274123 Intercept: [ -1 0 0 ]   true
Pos: [ -1 1 0 ] Dir: [ 0 -1 0 ] FOV: 1.047197551 Intercept: [ 0 0 0 ]   false
Pos: [ -1 1 0 ] Dir: [ 0 -1 0 ] FOV: 2.513274123 Intercept: [ 0 0 0 ]   true
Pos: [ -1 1 0 ] Dir: [ 0 -1 0 ] FOV: 1.047197551 Intercept: [ 1 0 0 ]   false
Pos: [ -1 1 0 ] Dir: [ 0 -1 0 ] FOV: 2.513274123 Intercept: [ 1 0 0 ]   true
Pos: [ 0 1 0 ] Dir: [ 0 -1 0 ] FOV: 1.047197551 Intercept: [ -1 0 0 ]   false
Pos: [ 0 1 0 ] Dir: [ 0 -1 0 ] FOV: 2.513274123 Intercept: [ -1 0 0 ]   true
Pos: [ 0 1 0 ] Dir: [ 0 -1 0 ] FOV: 1.047197551 Intercept: [ 0 0 0 ]   true
Pos: [ 0 1 0 ] Dir: [ 0 -1 0 ] FOV: 2.513274123 Intercept: [ 0 0 0 ]   true
Pos: [ 0 1 0 ] Dir: [ 0 -1 0 ] FOV: 1.047197551 Intercept: [ 1 0 0 ]   false
Pos: [ 0 1 0 ] Dir: [ 0 -1 0 ] FOV: 2.513274123 Intercept: [ 1 0 0 ]   true
Pos: [ 1 1 0 ] Dir: [ 0 -1 0 ] FOV: 1.047197551 Intercept: [ -1 0 0 ]   false
Pos: [ 1 1 0 ] Dir: [ 0 -1 0 ] FOV: 2.513274123 Intercept: [ -1 0 0 ]   true
Pos: [ 1 1 0 ] Dir: [ 0 -1 0 ] FOV: 1.047197551 Intercept: [ 0 0 0 ]   false
Pos: [ 1 1 0 ] Dir: [ 0 -1 0 ] FOV: 2.513274123 Intercept: [ 0 0 0 ]   true
Pos: [ 1 1 0 ] Dir: [ 0 -1 0 ] FOV: 1.047197551 Intercept: [ 1 0 0 ]   true
Pos: [ 1 1 0 ] Dir: [ 0 -1 0 ] FOV: 2.513274123 Intercept: [ 1 0 0 ]   true
Pos: [ -1 1 0 ] Dir: [ 0.7071067812 -0.7071067812 0 ] FOV: 1.047197551 Intercept: [ -1 0 0 ]   false
Pos: [ -1 1 0 ] Dir: [ 0.7071067812 -0.7071067812 0 ] FOV: 2.513274123 Intercept: [ -1 0 0 ]   true
Pos: [ -1 1 0 ] Dir: [ 0.7071067812 -0.7071067812 0 ] FOV: 1.047197551 Intercept: [ 0 0 0 ]   true
Pos: [ -1 1 0 ] Dir: [ 0.7071067812 -0.7071067812 0 ] FOV: 2.513274123 Intercept: [ 0 0 0 ]   true
Pos: [ -1 1 0 ] Dir: [ 0.7071067812 -0.7071067812 0 ] FOV: 1.047197551 Intercept: [ 1 0 0 ]   true
Pos: [ -1 1 0 ] Dir: [ 0.7071067812 -0.7071067812 0 ] FOV: 2.513274123 Intercept: [ 1 0 0 ]   true
Pos: [ 0 1 0 ] Dir: [ 0.7071067812 -0.7071067812 0 ] FOV: 1.047197551 Intercept: [ -1 0 0 ]   false
Pos: [ 0 1 0 ] Dir: [ 0.7071067812 -0.7071067812 0 ] FOV: 2.513274123 Intercept: [ -1 0 0 ]   false
Pos: [ 0 1 0 ] Dir: [ 0.7071067812 -0.7071067812 0 ] FOV: 1.047197551 Intercept: [ 0 0 0 ]   false
Pos: [ 0 1 0 ] Dir: [ 0.7071067812 -0.7071067812 0 ] FOV: 2.513274123 Intercept: [ 0 0 0 ]   true
Pos: [ 0 1 0 ] Dir: [ 0.7071067812 -0.7071067812 0 ] FOV: 1.047197551 Intercept: [ 1 0 0 ]   true
Pos: [ 0 1 0 ] Dir: [ 0.7071067812 -0.7071067812 0 ] FOV: 2.513274123 Intercept: [ 1 0 0 ]   true
Pos: [ 1 1 0 ] Dir: [ 0.7071067812 -0.7071067812 0 ] FOV: 1.047197551 Intercept: [ -1 0 0 ]   false
Pos: [ 1 1 0 ] Dir: [ 0.7071067812 -0.7071067812 0 ] FOV: 2.513274123 Intercept: [ -1 0 0 ]   false
Pos: [ 1 1 0 ] Dir: [ 0.7071067812 -0.7071067812 0 ] FOV: 1.047197551 Intercept: [ 0 0 0 ]   false
Pos: [ 1 1 0 ] Dir: [ 0.7071067812 -0.7071067812 0 ] FOV: 2.513274123 Intercept: [ 0 0 0 ]   false
Pos: [ 1 1 0 ] Dir: [ 0.7071067812 -0.7071067812 0 ] FOV: 1.047197551 Intercept: [ 1 0 0 ]   false
Pos: [ 1 1 0 ] Dir: [ 0.7071067812 -0.7071067812 0 ] FOV: 2.513274123 Intercept: [ 1 0 0 ]   true
Pos: [ -1 1 0 ] Dir: [ -0.7071067812 -0.7071067812 0 ] FOV: 1.047197551 Intercept: [ -1 0 0 ]   false
Pos: [ -1 1 0 ] Dir: [ -0.7071067812 -0.7071067812 0 ] FOV: 2.513274123 Intercept: [ -1 0 0 ]   true
Pos: [ -1 1 0 ] Dir: [ -0.7071067812 -0.7071067812 0 ] FOV: 1.047197551 Intercept: [ 0 0 0 ]   false
Pos: [ -1 1 0 ] Dir: [ -0.7071067812 -0.7071067812 0 ] FOV: 2.513274123 Intercept: [ 0 0 0 ]   false
Pos: [ -1 1 0 ] Dir: [ -0.7071067812 -0.7071067812 0 ] FOV: 1.047197551 Intercept: [ 1 0 0 ]   false
Pos: [ -1 1 0 ] Dir: [ -0.7071067812 -0.7071067812 0 ] FOV: 2.513274123 Intercept: [ 1 0 0 ]   false
Pos: [ 0 1 0 ] Dir: [ -0.7071067812 -0.7071067812 0 ] FOV: 1.047197551 Intercept: [ -1 0 0 ]   true
Pos: [ 0 1 0 ] Dir: [ -0.7071067812 -0.7071067812 0 ] FOV: 2.513274123 Intercept: [ -1 0 0 ]   true
Pos: [ 0 1 0 ] Dir: [ -0.7071067812 -0.7071067812 0 ] FOV: 1.047197551 Intercept: [ 0 0 0 ]   false
Pos: [ 0 1 0 ] Dir: [ -0.7071067812 -0.7071067812 0 ] FOV: 2.513274123 Intercept: [ 0 0 0 ]   true
Pos: [ 0 1 0 ] Dir: [ -0.7071067812 -0.7071067812 0 ] FOV: 1.047197551 Intercept: [ 1 0 0 ]   false
Pos: [ 0 1 0 ] Dir: [ -0.7071067812 -0.7071067812 0 ] FOV: 2.513274123 Intercept: [ 1 0 0 ]   false
Pos: [ 1 1 0 ] Dir: [ -0.7071067812 -0.7071067812 0 ] FOV: 1.047197551 Intercept: [ -1 0 0 ]   true
Pos: [ 1 1 0 ] Dir: [ -0.7071067812 -0.7071067812 0 ] FOV: 2.513274123 Intercept: [ -1 0 0 ]   true
Pos: [ 1 1 0 ] Dir: [ -0.7071067812 -0.7071067812 0 ] FOV: 1.047197551 Intercept: [ 0 0 0 ]   true
Pos: [ 1 1 0 ] Dir: [ -0.7071067812 -0.7071067812 0 ] FOV: 2.513274123 Intercept: [ 0 0 0 ]   true
Pos: [ 1 1 0 ] Dir: [ -0.7071067812 -0.7071067812 0 ] FOV: 1.047197551 Intercept: [ 1 0 0 ]   false
Pos: [ 1 1 0 ] Dir: [ -0.7071067812 -0.7071067812 0 ] FOV: 2.513274123 Intercept: [ 1 0 0 ]   true

Other examples:
Pos: [ 1 1 1 ] Dir: [ -0.5773502692 -0.5773502692 -0.5773502692 ] FOV: 1.047197551 Intercept: [ 0 0 0 ]   true
Pos: [ 1 1 1 ] Dir: [ -0.5773502692 -0.5773502692 -0.5773502692 ] FOV: 1.047197551 Intercept: [ -2 0 0 ]   true
Pos: [ 1 1 1 ] Dir: [ -0.5773502692 -0.5773502692 -0.5773502692 ] FOV: 1.047197551 Intercept: [ 2 0 0 ]   false
Pos: [ 1 1 1 ] Dir: [ -0.5773502692 -0.5773502692 -0.5773502692 ] FOV: 1.047197551 Intercept: [ -5 0 -5 ]   true
Pos: [ 1 1 1 ] Dir: [ -0.5773502692 -0.5773502692 -0.5773502692 ] FOV: 1.047197551 Intercept: [ -10 0 -10 ]   false
Pos: [ 1 1 1 ] Dir: [ -0.5773502692 -0.5773502692 -0.5773502692 ] FOV: 1.047197551 Intercept: [ -10 -10 -10 ]   true
Pos: [ 1 1 1 ] Dir: [ -0.5773502692 -0.5773502692 -0.5773502692 ] FOV: 1.047197551 Intercept: [ 10 10 10 ]   false

Spotlight::illuminate
[ 0.866666 0.862745 1 ]
[ 0.105882 0.058824 0.113725 ]
[ 0 0 0 ]
[ 0 0 0 ]
*/
