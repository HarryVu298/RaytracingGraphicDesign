/****************************************************
 * 2016-2021 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted..
 ****************************************************/

#include <ctime>
#include <vector>
#include "defs.h"
#include "utilities.h"
#include "framebuffer.h"
#include "colorandmaterials.h"
#include "light.h"
#include "eshape.h"
#include "vertexops.h"
#include "fragmentops.h"
#include "iscene.h"

 /*
 Use this version of FragmentOps::processFragment:
 void FragmentOps::processFragment(FrameBuffer& frameBuffer, const dvec3& eyePositionInWorldCoords,
									 const vector<LightSourcePtr> lights,
									 const Fragment& fragment,
									 const Frame& eyeFrame) {
	 const dvec3& eyePos = eyePositionInWorldCoords;

	 double Z = fragment.windowPos.z;
	 int X = (int)fragment.windowPos.x;
	 int Y = (int)fragment.windowPos.y;
	 double oldZ = frameBuffer.getDepth(X, Y);
	 bool passDepthTest = !performDepthTest || Z < oldZ;

	 if (passDepthTest) {
		 color result = fragment.material.ambient;
		 if (!readonlyColorBuffer) {
			 frameBuffer.setColor(X, Y, result);
		 }
		 if (!readonlyDepthBuffer) {
			 frameBuffer.setDepth(X, Y, Z);
		 }
	 }
 } 

 */

vector<LightSourcePtr> lights = {
								new PositionalLight(dvec3(10, 10, 10), white)
};
const int W = 250;
const int H = W;
int which = 0;
FrameBuffer frameBuffer(W, H);

PipelineMatrices pipeMats;
dmat4& viewingMatrix = pipeMats.viewingMatrix;
dmat4& projectionMatrix = pipeMats.projectionMatrix;
dmat4& viewportMatrix = pipeMats.viewportMatrix;

void square(double x, double y, double z, color C, double radius = 0.5) {
	static dmat4 I;
	dvec4 center(x, y, z, 1);
	double D = radius;
	VertexData a(center + dvec4(-D, -D, 0, 0), Z_AXIS, C);
	VertexData b(center + dvec4(D, -D, 0, 0), Z_AXIS, C);
	VertexData c(center + dvec4(D, D, 0, 0), Z_AXIS, C);
	VertexData d(center + dvec4(-D, D, 0, 0), Z_AXIS, C);
	EShapeData verts = { a, b, c, a, c, d };
	VertexOps::render(frameBuffer, verts, lights, I, pipeMats, true);
}
void func0() {
	FragmentOps::performDepthTest = true;
	FragmentOps::readonlyDepthBuffer = false;
	FragmentOps::readonlyColorBuffer = false;
	square(-0.5f, -0.5f, -2.0f, red);
	square(0.0f, 0.0f, -3.0f, green);
	square(0.5f, 0.5f, -4.0f, blue);
}
void func1() {
	FragmentOps::performDepthTest = true;
	FragmentOps::readonlyDepthBuffer = true;
	FragmentOps::readonlyColorBuffer = false;
	square(-0.5f, -0.5f, -2.0f, red);
	square(0.0f, 0.0f, -3.0f, green);
	square(0.5f, 0.5f, -4.0f, blue);
}
void func2() {
	FragmentOps::performDepthTest = false;
	FragmentOps::readonlyDepthBuffer = false;
	FragmentOps::readonlyColorBuffer = false;
	square(-0.5f, -0.5f, -2.0f, red);
	square(0.0f, 0.0f, -3.0f, green);
	square(0.5f, 0.5f, -4.0f, blue);
}
void func3() {
	FragmentOps::performDepthTest = true;
	FragmentOps::readonlyDepthBuffer = false;
	FragmentOps::readonlyColorBuffer = true;
	square(-0.5f, -0.5f, -2.0f, red);

	FragmentOps::readonlyColorBuffer = false;
	square(0.0f, 0.0f, -3.0f, green);
	square(0.5f, 0.5f, -4.0f, blue);
}
void func4() {
	// Note the different rendering order, here:
	FragmentOps::performDepthTest = true;
	FragmentOps::readonlyDepthBuffer = false;
	FragmentOps::readonlyColorBuffer = true;

	square(0.0f, 0.0f, -3.0f, green);

	FragmentOps::readonlyColorBuffer = false;
	square(0.5f, 0.5f, -4.0f, blue);

	square(-0.5f, -0.5f, -2.0f, red);
}

void func5() {
	FragmentOps::performDepthTest = true;
	FragmentOps::readonlyDepthBuffer = false;
	FragmentOps::readonlyColorBuffer = true;
	square(-0.5f, -0.5f, -2.0f, red);

	FragmentOps::readonlyColorBuffer = false;
	square(0.0f, 0.0f, -3.0f, green);

	FragmentOps::readonlyColorBuffer = true;
	square(0.5f, 0.5f, -4.0f, blue);
}
void func6() {
	FragmentOps::performDepthTest = true;
	FragmentOps::readonlyDepthBuffer = false;
	FragmentOps::readonlyColorBuffer = false;
	square(-0.5f, -0.5f, -2.0f, red);
	square(0.5f, 0.5f, -4.0f, blue);

	FragmentOps::performDepthTest = false;
	FragmentOps::readonlyDepthBuffer = false;
	FragmentOps::readonlyColorBuffer = false;
	square(0.0f, 0.0f, -3.0f, green);
}
void func7() {
	FragmentOps::performDepthTest = true;
	FragmentOps::readonlyDepthBuffer = false;
	FragmentOps::readonlyColorBuffer = false;
	square(0.5, 0.5, -4.0, blue);

	FragmentOps::performDepthTest = true;
	FragmentOps::readonlyDepthBuffer = false;
	FragmentOps::readonlyColorBuffer = true;
	square(-0.5, -0.5, -2.0, red);

	FragmentOps::readonlyColorBuffer = false;
	square(0.0, 0.0, -3.0, green);
}
void func8() {
	FragmentOps::performDepthTest = false;
	FragmentOps::readonlyDepthBuffer = false;
	FragmentOps::readonlyColorBuffer = true;
	square(-0.5, -0.5, -2.0, red);

	FragmentOps::performDepthTest = true;
	FragmentOps::readonlyDepthBuffer = false;
	FragmentOps::readonlyColorBuffer = false;
	square(0.0, 0.0, -3.0, green);

	FragmentOps::performDepthTest = false;
	FragmentOps::readonlyDepthBuffer = false;
	FragmentOps::readonlyColorBuffer = false;
	square(0.5, 0.5, -4.0, blue);
}


void resize(int width, int height) {
	frameBuffer.setFrameBufferSize(width, height);
	glutPostRedisplay();
}
void render() {
	int width = frameBuffer.getWindowWidth();
	int height = frameBuffer.getWindowHeight();
	double AR = (double)width / height;
	viewingMatrix = glm::lookAt(ORIGIN3D, dvec3(0, 0, -1), Y_AXIS);

	double vvWidth = 4.0;
	double vvHeight = vvWidth / AR;
	double left = -vvWidth / 2.0;
	double right = -left;
	double bottom = -vvHeight / 2.0;
	double top = -bottom;
	projectionMatrix = glm::ortho(left, right, bottom, top, 0.0, 10.0);
	viewportMatrix = VertexOps::getViewportTransformation(0, width, 0, height);

	frameBuffer.clearColorAndDepthBuffers();
	switch (which) {
	case 0: func0(); break;
	case 1: func1(); break;
	case 2: func2(); break;
	case 3: func3(); break;
	case 4: func4(); break;
	case 5: func5(); break;
	case 6: func6(); break;
	case 7: func7(); break;
	case 8: func8(); break;
	}
	frameBuffer.showColorBuffer();
}
void keyboard(unsigned char key, int x, int y) {
	const double INC = 0.5;
	if (key == ESCAPE) {
		glutLeaveMainLoop();
	} else {
		which = (which + 1) % 9;
		char buf[100];
		sprintf(buf, "%d", which);
		glutSetWindowTitle(buf);
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
	graphicsInit(argc, argv, "0", W, H);

	which = 0;
	glutDisplayFunc(render);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseUtility);
	resize(400, 400);

	frameBuffer.setClearColor(lightGray);

	glutMainLoop();

	return 0;
}
