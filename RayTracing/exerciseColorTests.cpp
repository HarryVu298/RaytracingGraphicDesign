#include <iostream>
#include "defs.h"
#include "io.h"
#include "light.h"
#include "camera.h"

	int main(int argc, char* argv[]) {

		// This example is the one used in the handout we covered in class.
		dvec3 eyePos(3.0, 0.0, 1.0);

		dvec3 interceptPt(5.0, 2.0, -3.0);
		dvec3 pointToRight(4.0, 4.0, 0.0);
		dvec3 pointToLeft(0.0, 0.0, 0.0);

		color L1color(0.6, 0.6, 0.7);
		dvec3 L1pos(6.0, 1.0, 0.0);

		color mat1amb(0.4, 0.5, 0.6);
		color mat1diff(0.9, 1.0, 0.9);
		color mat1spec(0.9, 0.8, 0.7);

		dvec3 V1 = pointToRight - interceptPt;
		dvec3 V2 = pointToLeft - interceptPt;
		dvec3 n = glm::normalize(glm::cross(V1, V2));
		dvec3 v = glm::normalize(eyePos - interceptPt);
		dvec3 l = glm::normalize(L1pos - interceptPt);
		dvec3 r = glm::normalize(2.0 * glm::dot(l, n) * n - l);

		cout << "n: " << n << endl;
		cout << "v: " << v << endl;
		cout << "l: " << l << endl;
		cout << "r: " << r << endl;
		cout << endl;

		cout << "Ambient: " << ambientColor(mat1amb, L1color) << endl;
		cout << "Diffuse: " << diffuseColor(mat1diff, L1color, l, n) << endl;
		cout << "Specular: " << specularColor(mat1spec, L1color, 1.0, r, v) << endl;

		Material mat1(mat1amb, mat1diff, mat1spec, 1.0);
		LightATParams atParams(1.0, 2.0, 0.0);
		bool useAttenuation = false;

		cout << "Total: " << totalColor(mat1, L1color, v, n, L1pos, interceptPt, useAttenuation, atParams) << endl;
		cout << endl;

		cout << "Attenuation factor: " << atParams.factor(glm::distance(L1pos, interceptPt)) << endl;

		cout << endl;

		cout << "Tests involving negative dot products" << endl;
		dvec3 wonkyL = glm::normalize(dvec3(-1.0, -1.0, -1.0));
		cout << "Diffuse with negative l dot n: " << diffuseColor(mat1diff, L1color, wonkyL, n) << endl;
		dvec3 wonkyV = glm::normalize(dvec3(-1.0, -1.0, -1.0));
		cout << "Specular with negative r dot v shininess = 1.5: " << specularColor(mat1spec, L1color, 1.5, r, wonkyV) << endl;
		cout << "Specular with negative r dot v shininess = 4.0: " << specularColor(mat1spec, L1color, 4.0, r, wonkyV) << endl;
		cout << "Specular with positive r dot v shininess = 1.5: " << specularColor(mat1spec, L1color, 1.5, r, v) << endl;

		cout << endl;

		vector<VisibleIShapePtr> objs;

		cout << "illuminate tests" << endl << endl;
		PositionalLight light1(L1pos, atParams, L1color);

		PerspectiveCamera pCamera(eyePos, interceptPt, Y_AXIS, PI_2, WINDOW_WIDTH, WINDOW_HEIGHT);

		cout << "Light on: FALSE   Shadow: FALSE    Attenuation on: FALSE" << endl;
		light1.isOn = false; light1.attenuationIsTurnedOn = false;
		cout << light1.illuminate(interceptPt, n, mat1, pCamera.getFrame(), false) << endl;

		cout << "Light on: FALSE   Shadow: FALSE    Attenuation on: TRUE " << endl;
		light1.isOn = false; light1.attenuationIsTurnedOn = true;
		cout << light1.illuminate(interceptPt, n, mat1, pCamera.getFrame(), false) << endl;

		cout << "Light on: FALSE   Shadow: TRUE     Attenuation on: FALSE" << endl;
		light1.isOn = false; light1.attenuationIsTurnedOn = false;
		cout << light1.illuminate(interceptPt, n, mat1, pCamera.getFrame(), true) << endl;

		cout << "Light on: FALSE   Shadow: TRUE     Attenuation on: TRUE" << endl;
		light1.isOn = false; light1.attenuationIsTurnedOn = true;
		cout << light1.illuminate(interceptPt, n, mat1, pCamera.getFrame(), true) << endl;

		cout << "Light on: TRUE   Shadow: FALSE    Attenuation on: FALSE" << endl;
		light1.isOn = true; light1.attenuationIsTurnedOn = false;
		cout << light1.illuminate(interceptPt, n, mat1, pCamera.getFrame(), false) << endl;

		cout << "Light on: TRUE   Shadow: FALSE    Attenuation on: TRUE " << endl;
		light1.isOn = true; light1.attenuationIsTurnedOn = true;
		cout << light1.illuminate(interceptPt, n, mat1, pCamera.getFrame(), false) << endl;

		cout << "Light on: TRUE   Shadow: TRUE     Attenuation on: FALSE" << endl;
		light1.isOn = true; light1.attenuationIsTurnedOn = false;
		cout << light1.illuminate(interceptPt, n, mat1, pCamera.getFrame(), true) << endl;

		cout << "Light on: TRUE   Shadow: TRUE     Attenuation on: TRUE" << endl;
		light1.isOn = true; light1.attenuationIsTurnedOn = true;
		cout << light1.illuminate(interceptPt, n, mat1, pCamera.getFrame(), true) << endl;

		return 0;
	}
/*
ExerciseColorTests
n: [ 0.5773502692 -0.5773502692 0.5773502692 ]
v: [ -0.4082482905 -0.4082482905 0.8164965809 ]
l: [ 0.3015113446 -0.3015113446 0.9045340337 ]
r: [ 0.7035264707 -0.7035264707 0.1005037815 ]

Ambient: [ 0.24 0.3 0.42 ]
Diffuse: [ 0.4700096711 0.5222329679 0.5483446163 ]
Specular: [ 0.04431293675 0.03938927711 0.04020988705 ]
Total: [ 0.7543226078 0.861622245 1 ]

Attenuation factor: 0.1310058042

Tests involving negative dot products
Diffuse with negative l dot n: [ 0 0 0 ]
Specular with negative r dot v shininess = 1.5: [ 0 0 0 ]
Specular with negative r dot v shininess = 4.0: [ 0 0 0 ]
Specular with positive r dot v shininess = 1.5: [ 0.01269401244 0.01128356661 0.01151864092 ]

illuminate tests

Light on: FALSE   Shadow: FALSE    Attenuation on: FALSE
[ 0 0 0 ]
Light on: FALSE   Shadow: FALSE    Attenuation on: TRUE
[ 0 0 0 ]
Light on: FALSE   Shadow: TRUE     Attenuation on: FALSE
[ 0 0 0 ]
Light on: FALSE   Shadow: TRUE     Attenuation on: TRUE
[ 0 0 0 ]
Light on: TRUE   Shadow: FALSE    Attenuation on: FALSE
[ 0.7543226078 0.861622245 1 ]
Light on: TRUE   Shadow: FALSE    Attenuation on: TRUE
[ 0.3073792469 0.3735757739 0.497104056 ]
Light on: TRUE   Shadow: TRUE     Attenuation on: FALSE
[ 0.24 0.3 0.42 ]
Light on: TRUE   Shadow: TRUE     Attenuation on: TRUE
[ 0.24 0.3 0.42 ]
*/
