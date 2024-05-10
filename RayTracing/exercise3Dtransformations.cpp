/****************************************************
 * 2016-2021 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted..
 ****************************************************/

#include <ctime> 
#include <iostream>
#include <vector>
#include "eshape.h"
#include "io.h"
#include "light.h"
#include "vertexops.h"

PositionalLightPtr theLight = new PositionalLight(dvec3(2, 1, 3), white);
vector<LightSourcePtr> lights = { theLight };

PipelineMatrices pipeMats;
dmat4 &viewingMatrix = pipeMats.viewingMatrix;
dmat4 &projectionMatrix = pipeMats.projectionMatrix;
dmat4 &viewportMatrix = pipeMats.viewportMatrix;

const double WIDTH = 10.0;
const int DIV = 20;

dvec3 position(0, 1, 5);
double angle = 0;
bool isMoving = true;
const double SPEED = 0.1;

FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

EShapeData plane = EShape::createECheckerBoard(copper, polishedCopper, 5, 5, 10);
EShapeData cone1 = EShape::createECone(gold, DEFAULT_SLICES);
EShapeData cone2 = EShape::createECone(brass, DEFAULT_SLICES);
EShapeData disk = EShape::createEDisk(greenPlastic, DEFAULT_SLICES);
EShapeData cyl1 = EShape::createECylinder(silver, DEFAULT_SLICES);
EShapeData cyl2 = EShape::createECylinder(silver, DEFAULT_SLICES);
EShapeData tri = EShape::createETriangle(cyanPlastic, 
										dvec4(0,0,0,1), dvec4(1,0,0,1), dvec4(1,1,0,1));
EShapeData mario = EShape::createEObj("mario.obj");

void renderObjects() {
	VertexOps::render(frameBuffer, plane, lights, dmat4(), pipeMats, true);
	VertexOps::render(frameBuffer, cone1, lights, T(-1, 2, 0)*S(0.25)*Rx(angle), pipeMats, true);
	VertexOps::render(frameBuffer, cone2, lights, Ry(angle)*T(2, 1, 0)*Rx(angle), pipeMats, true);
	VertexOps::render(frameBuffer, disk, lights, T(0, 1, 0)*Ry(angle)*S(0.5), pipeMats, true);
	VertexOps::render(frameBuffer, cyl1, lights, T(2,0,0), pipeMats, true);
	VertexOps::render(frameBuffer, cyl2, lights, T(-2, 1, 0)*Rx(PI_2), pipeMats, true);
	VertexOps::render(frameBuffer, tri, lights, T(0, 2, 0) * Rx(angle), pipeMats, true);
    VertexOps::render(frameBuffer, mario, lights, Ry(angle)*S(0.01), pipeMats, true);
}

static void render() {
	frameBuffer.clearColorAndDepthBuffers();
	int width = frameBuffer.getWindowWidth();
	int height = frameBuffer.getWindowHeight();
	viewingMatrix = glm::lookAt(position, ORIGIN3D, Y_AXIS);
	double AR = (double)width / height;
	projectionMatrix = glm::perspective(PI_3, AR, 0.5, 80.0);
	viewportMatrix = VertexOps::getViewportTransformation(0, width, 0, height);
	renderObjects();
	frameBuffer.showAxes(viewingMatrix, projectionMatrix, viewportMatrix, 
							BoundingBoxi(0, width, 0, height));
	frameBuffer.showColorBuffer();
}

void resize(int width, int height) {
	frameBuffer.setFrameBufferSize(width, height);
	double AR = (double)width / height;

	viewportMatrix = VertexOps::getViewportTransformation(0, width, 0, height);
	projectionMatrix = glm::perspective(PI_3, AR, 0.5, 80.0);

	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y) {
	const double INC = 0.5;
	switch (key) {
	case 'X':
	case 'x': theLight->pos.x += (isupper(key) ? INC : -INC);
				cout << theLight->pos << endl;
				break;
	case 'Y':
	case 'y': theLight->pos.y += (isupper(key) ? INC : -INC);
				cout << theLight->pos << endl;
				break;
	case 'Z':
	case 'z': theLight->pos.z += (isupper(key) ? INC : -INC);
				cout << theLight->pos << endl;
				break;
	case 'P':
	case 'p':	isMoving = !isMoving;
				break;
	case 'C':
	case 'c':	break;
	case ESCAPE:
				glutLeaveMainLoop();
				break;
	default:
				cout << (int)key << "unmapped key pressed." << endl;
	}

	glutPostRedisplay();
}

static void timer(int id) {
	if (isMoving) {
		angle += glm::radians(5.0);
	}
	glutTimerFunc(100, timer, 0);
	glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    dmat4 viewpoint(50,0,0,0,0,50,0,0,0,0,1,0,50,50,0,1);
    dmat4 prj(0.5,0,0,0,0,1,0,0,0,0,-1.1,-1,0,0,-2.1,0);
    dmat4 viewingmatrix(-1,0,0,0,0,0,1,0,0,1,0,0,1,0,-5,1);
    dmat4 model(0.1,0,0,0,0,0.1,0,0,0,0,0.1,0,-10,0,1,1);
    
    auto result1 = prj * viewingmatrix * model * glm::dvec4(-10,10,0,1);
    auto result2 = prj * viewingmatrix * model * glm::dvec4(40,10,0,1);
    auto result3 = prj * viewingmatrix * model * glm::dvec4(20,10,10,1);

    std::cout << viewpoint * glm::dvec4(result1.x/4, result1.y/4, result1.z/4, result1.w/4) << std::endl;
    std::cout << viewpoint *glm::dvec4(result2.x/4, result2.y/4, result2.z/4, result2.w/4) << std::endl;
    std::cout << viewpoint *glm::dvec4(result3.x/4, result3.y/4, result3.z/4, result3.w/4) << std::endl;
    return 1;
    graphicsInit(argc, argv, __FILE__);
    

	glutDisplayFunc(render);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(100, timer, 0);
	glutMouseFunc(mouseUtility);
	frameBuffer.setClearColor(lightGray);
		
	glutMainLoop();

	return 0;
}
