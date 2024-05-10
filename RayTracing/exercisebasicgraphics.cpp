/****************************************************
 * 2016-2023 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#include <ctime>
#include <vector>
#include "defs.h"
#include "utilities.h"
#include "framebuffer.h"
#include "colorandmaterials.h"
#include "rasterization.h"
#include "io.h"

FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

void render() {
	frameBuffer.clearColorBuffer();
	drawLine(frameBuffer, 0, 0, 100, 100, red);
	drawLine(frameBuffer, 100, 100, 200, 100, blue);
	frameBuffer.showColorBuffer();
}

void resize(int width, int height) {
	frameBuffer.setFrameBufferSize(width, height);
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
    std::cout << approximatelyEqual(1.0, 1.000001) << std::endl;
    
    // Test pointingVector
    std::cout << "\nTesting pointingVector:" << std::endl;
    std::cout <<  pointingVector(glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(1.0, 0.0, 0.0)) << std::endl; // [1, 0, 0]
    std::cout <<  pointingVector(glm::dvec3(1.0, 2.0, 3.0), glm::dvec3(4.0, 5.0, 6.0)) << std::endl; // Normalized [3, 3, 3]
    std::cout <<  pointingVector(glm::dvec3(-1.0, -1.0, -1.0), glm::dvec3(1.0, 1.0, 1.0)) << std::endl; // Normalized [2, 2, 2]
    std::cout <<  pointingVector(glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(-1.0, -1.0, -1.0)) << std::endl; // Normalized [-1, -1, -1]
    std::cout <<  pointingVector(glm::dvec3(1.0, 1.0, 0.0), glm::dvec3(1.0, 1.0, 1.0)) << std::endl; // [0, 0, 1]
    std::cout <<  pointingVector(glm::dvec3(2.0, 2.0, 2.0), glm::dvec3(2.0, 2.0, 3.0)) << std::endl; // [0, 0, 1]
    std::cout <<  pointingVector(glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(0.0, 1.0, 0.0)) << std::endl; // [0, 1, 0]
    std::cout <<  pointingVector(glm::dvec3(1.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 0.0)) << std::endl; // [-1, 0, 0]
    std::cout <<  pointingVector(glm::dvec3(0.0, 1.0, 1.0), glm::dvec3(0.0, 2.0, 2.0)) << std::endl; // [0, 1, 1] normalized
    std::cout <<  pointingVector(glm::dvec3(-1.0, 0.0, -1.0), glm::dvec3(1.0, 0.0, 1.0)) << std::endl; // [2, 0, 2] normalized



    

    return 0;
    

//	graphicsInit(argc, argv, __FILE__);
//
//	glutDisplayFunc(render);
//	glutReshapeFunc(resize);
//	glutKeyboardFunc(keyboardUtility);
//	glutMouseFunc(mouseUtility);
//
//	frameBuffer.setClearColor(paleGreen);
//
//	glutMainLoop();
//
//	return 0;
}
