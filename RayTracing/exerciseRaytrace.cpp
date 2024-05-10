/****************************************************
 * 2016-2022 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#include <ctime>
#include "defs.h"
#include "io.h"
#include "ishape.h"
#include "framebuffer.h"
#include "raytracer.h"
#include "iscene.h"
#include "light.h"
#include "image.h"
#include "camera.h"
#include "rasterization.h"

PositionalLightPtr posLight = new PositionalLight(dvec3(10, 10, 10), white);
vector<PositionalLightPtr> lights = { posLight };

FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);
RayTracer rayTrace(paleGreen);

dvec3 cameraPos(0, 5, 10);
dvec3 cameraFocus(0, 5, 0);
dvec3 cameraUp = Y_AXIS;
double cameraFOV = PI_2;

IScene scene;

void render() {
	int frameStartTime = glutGet(GLUT_ELAPSED_TIME);
	int width = frameBuffer.getWindowWidth();
	int height = frameBuffer.getWindowHeight();

	scene.camera = new PerspectiveCamera(cameraPos, cameraFocus, cameraUp, cameraFOV, width, height);
	rayTrace.raytraceScene(frameBuffer, 0, scene);

	int frameEndTime = glutGet(GLUT_ELAPSED_TIME); // Get end time
	double totalTimeSec = (frameEndTime - frameStartTime) / 1000.0;
	cout << "Render time: " << totalTimeSec << " sec." << endl;
}

void resize(int width, int height) {
	frameBuffer.setFrameBufferSize(width, height);
	glutPostRedisplay();
}

void buildScene() {
	IShape* plane = new IPlane(dvec3(0.0, -2.0, 0.0), dvec3(0.0, 1.0, 0.0));
	ISphere* sphere1 = new ISphere(dvec3(0.0, 0.0, 0.0), 2.0);
	ISphere* sphere2 = new ISphere(dvec3(-2.0, 0.0, -8.0), 2.0);
	IEllipsoid* ellipsoid = new IEllipsoid(dvec3(4.0, 0.0, 3.0), dvec3(2.0, 1.0, 2.0));
	IDisk* disk = new IDisk(dvec3(15.0, 0.0, 0.0), dvec3(0.0, 0.0, 1.0), 5.0);
    IDisk* disk2 = new IDisk(dvec3(-10.0, 0.0, 0.0), dvec3(1.0, 1.0, 0.0), 3.0);

	scene.addOpaqueObject(new VisibleIShape(plane, tin));
	scene.addOpaqueObject(new VisibleIShape(sphere1, silver));
	scene.addOpaqueObject(new VisibleIShape(sphere2, bronze));
	scene.addOpaqueObject(new VisibleIShape(ellipsoid, redPlastic));
	scene.addOpaqueObject(new VisibleIShape(disk, cyanPlastic));
    scene.addOpaqueObject(new VisibleIShape(disk2, polishedSilver));

	scene.addLight(lights[0]);
}
int main(int argc, char* argv[]) {
	graphicsInit(argc, argv, __FILE__);

	glutDisplayFunc(render);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboardUtility);
	glutMouseFunc(mouseUtility);

	buildScene();

	glutMainLoop();

	return 0;
}
