/****************************************************
 * 2016-2022 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#include <ctime>
#include <utility>
#include <cctype>
#include <ctime> 

#include "colorandmaterials.h"
#include "framebuffer.h"
#include "iscene.h"
#include "ishape.h"
#include "raytracer.h"
#include "camera.h"
#include "image.h"
#include <ctime>
#include <utility>
#include <cctype>
#include <ctime> 

FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);
Image im("usflag.ppm");

double angle = 0.0;
bool isAnimated = true;

double cameraFOV = PI_2;

IScene theScene;

RayTracer rayTrace(paleGreen);

PositionalLightPtr posLight = new PositionalLight(dvec3(10.0, 15.0, 15.0), white);

void buildScene() {
	IShapePtr cylinder1 = new ICylinderY(dvec3(0, 0, 0), 3.0, 10.0);
	IShapePtr cylinder2 = new ICylinderY(dvec3(6, 0, -8), 2.0, 5.0);
	IShapePtr cylinder3 = new ICylinderY(dvec3(10, 0, 0), 3.0, 5.0);
	IShapePtr disk1 = new IDisk(dvec3(-5, 0, 6), dvec3(0, 0, 1), 3);
	IShapePtr disk2 = new IDisk(dvec3(-9, 0, 5), dvec3(0, 0, 1), 3);

	theScene.addOpaqueObject(new VisibleIShape(cylinder1, gold, &im));
	theScene.addOpaqueObject(new VisibleIShape(cylinder2, brass));
	theScene.addOpaqueObject(new VisibleIShape(cylinder3, gold, &im));
	theScene.addOpaqueObject(new VisibleIShape(disk1, gold, &im));
	theScene.addOpaqueObject(new VisibleIShape(disk2, brass));

	theScene.addLight(posLight);
}
void render() {
	int frameStartTime = glutGet(GLUT_ELAPSED_TIME);

	double R = 9;
	double rads = glm::radians(angle);
	dvec3 cameraPos = dvec3(R * std::cos(-rads), R, R * std::sin(-rads));
	int width = frameBuffer.getWindowWidth();
	int height = frameBuffer.getWindowHeight();

	theScene.camera = new PerspectiveCamera(cameraPos, ORIGIN3D, Y_AXIS, cameraFOV, width, height);

	frameBuffer.clearColorBuffer();
	rayTrace.raytraceScene(frameBuffer, 0, theScene);
	int frameEndTime = glutGet(GLUT_ELAPSED_TIME);
	double totalTimeSec = (frameEndTime - frameStartTime) / 1000.0;

	cout << "Render time: " << totalTimeSec << " sec." << endl;
}

void resize(int width, int height) {
	frameBuffer.setFrameBufferSize(width, height);
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	switch (std::toupper(key)) {
	case 'P':
		isAnimated = !isAnimated;
		break;
	case ESCAPE:
		glutLeaveMainLoop();
		break;
	default:
		cout << key << " key pressed." << endl;
	}
	glutPostRedisplay();
}

void timer(int id) {
	glutTimerFunc(TIME_INTERVAL, timer, 0);
	if (!isAnimated) return;
	angle += 5.0;
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
	frameBuffer.setClearColor(paleGreen);

	graphicsInit(argc, argv, __FILE__);

	glutDisplayFunc(render);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(TIME_INTERVAL, timer, 0);
	glutMouseFunc(mouseUtility);

	buildScene();

	glutMainLoop();
	return 0;
}
