/****************************************************
 * 2016-2023 Eric Bachmann and Mike Zmuda
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

Image im1("usflag.ppm");

int currLight = 0;
double angle = 0.5;
const int MAX = 20;
double z = -MAX;
double inc = 0.8;
bool isAnimated = false;
int numReflections = 0;
int antiAliasing = 1;
bool multiViewOn = false;
double spotDirX = 0;
double spotDirY = -1;
double spotDirZ = 0;

dvec3 cameraPos(6, 6, 6);
dvec3 cameraFocus(0, 0, 0);
dvec3 cameraUp = Y_AXIS;

double cameraFOV = glm::radians(120.0);

vector<PositionalLightPtr> lights = {
                        new PositionalLight(dvec3(15, 15, 15), white),
                        new SpotLight(dvec3(-15, 5, 10),
                                        dvec3(spotDirX,spotDirY,spotDirZ),
                                        glm::radians(90.0),
                                        white)
};

PositionalLightPtr posLight = lights[0];
SpotLightPtr spotLight = (SpotLightPtr)lights[1];

FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);
RayTracer rayTrace(paleGreen);
IScene scene;

void render() {
    int frameStartTime = glutGet(GLUT_ELAPSED_TIME);
    int width = frameBuffer.getWindowWidth();
    int height = frameBuffer.getWindowHeight();
    frameBuffer.clearColorBuffer();

    scene.camera = new PerspectiveCamera(cameraPos, cameraFocus, cameraUp, cameraFOV, width, height);
    rayTrace.raytraceScene(frameBuffer, numReflections, scene);

    frameBuffer.showColorBuffer();
    int frameEndTime = glutGet(GLUT_ELAPSED_TIME); // Get end time
    double totalTimeSec = (frameEndTime - frameStartTime) / 1000.0;
    cout << "Render time: " << totalTimeSec << " sec." << endl;
}

void resize(int width, int height) {
    frameBuffer.setFrameBufferSize(width, height);
    glutPostRedisplay();
}

IPlane* plane = new IPlane(dvec3(0.0, -2.0, 0.0), dvec3(0.0, 1.0, 0.0));
IPlane* clearPlane = new IPlane(dvec3(0.0, 0.0, -MAX), dvec3(0.0, 0.0, 1.0));
ISphere* sphere1 = new ISphere(dvec3(0.0, 0.0, 0.0), 4.0);
IEllipsoid* ellipsoid = new IEllipsoid(dvec3(4, 0, 5), dvec3(1, 1, 2.5));
ICylinderY* cylinderY = new ICylinderY(dvec3(8.0, 3.0, -2.0), 1.5, 3.0);
ICylinderZ* cylinderZ = new ICylinderZ(dvec3(0.0, 0.0, 8.0), 1, 3);
IDisk* disk = new IDisk(dvec3(-8,0,10), dvec3(1,0,0), 3);
ITriangle* triangle = new ITriangle(dvec3(-8, 3, 3), dvec3(-8, 8, 8), dvec3(-10, 5, 9));
IClosedCylinderY* closedCylinderY = new IClosedCylinderY(dvec3(9.0, 2.0, 2.0), 0.5, 1.5);
IConeY* coneY = new IConeY(dvec3(7,3,3), 1, 1.5);

void buildScene() {
    scene.addOpaqueObject(new VisibleIShape(plane, tin));
    scene.addTransparentObject(new TransparentIShape(clearPlane, red, 0.25));
         
    scene.addOpaqueObject(new VisibleIShape(sphere1, silver));
    scene.addOpaqueObject(new VisibleIShape(ellipsoid, copper));

    scene.addOpaqueObject(new VisibleIShape(cylinderY, gold, &im1));
    scene.addOpaqueObject(new VisibleIShape(cylinderZ, silver));
    scene.addOpaqueObject(new VisibleIShape(disk, redPlastic));
    scene.addOpaqueObject(new VisibleIShape(triangle, cyanPlastic));
    scene.addOpaqueObject(new VisibleIShape(closedCylinderY, greenRubber));
    scene.addOpaqueObject(new VisibleIShape(coneY, yellowRubber));
        
    scene.addLight(lights[0]);
    scene.addLight(lights[1]);
    lights[1]->isOn = false;
}

void incrementClamp(double& v, double delta, double lo, double hi) {
    v = glm::clamp(v + delta, lo, hi);
}

void incrementClamp(int& v, int delta, int lo, int hi) {
    v = glm::clamp(v + delta, lo, hi);
}

void timer(int id) {
    if (isAnimated) {
        z += inc;
        if (z <= -MAX) {
            inc = -inc;
        } else if (z >= MAX) {
            inc = -inc;
        }
    }
    clearPlane->a = dvec3(0, 0, z);
    glutTimerFunc(TIME_INTERVAL, timer, 0);
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    int W, H;
    const double INC = 0.5;
    switch (key) {
    case 'A':
    case 'a':    currLight = 0;
        cout << *lights[0] << endl;
        break;
    case 'B':
    case 'b':    currLight = 1;
        cout << *lights[1] << endl;
        break;
    case 'O':
    case 'o':    lights[currLight]->isOn = !lights[currLight]->isOn;
        cout << (lights[currLight]->isOn ? "ON" : "OFF") << endl;
        break;
    case 'X':
    case 'x': lights[currLight]->pos.x += (isupper(key) ? INC : -INC);
        cout << lights[currLight]->pos << endl;
        break;
    case 'Y':
    case 'y': lights[currLight]->pos.y += (isupper(key) ? INC : -INC);
        cout << lights[currLight]->pos << endl;
        break;
    case 'Z':
    case 'z': lights[currLight]->pos.z += (isupper(key) ? INC : -INC);
        cout << lights[currLight]->pos << endl;
        break;
    case 'J':
    case 'j':    spotDirX += (isupper(key) ? INC : -INC);
        spotLight->setDir(spotDirX, spotDirY, spotDirZ);
        cout << spotLight->spotDir << endl;
        break;
    case 'K':
    case 'k':    spotDirY += (isupper(key) ? INC : -INC);
        spotLight->setDir(spotDirX, spotDirY, spotDirZ);
        cout << spotLight->spotDir << endl;
        break;
    case 'L':
    case 'l':    spotDirZ += (isupper(key) ? INC : -INC);
        spotLight->setDir(spotDirX, spotDirY, spotDirZ);
        cout << spotLight->spotDir << endl;
        break;
    case 'P':
    case 'p':    isAnimated = !isAnimated;
        break;
    case '+':    antiAliasing = 3;
        cout << "Anti aliasing: " << antiAliasing << endl;
        break;
    case '-':    antiAliasing = 1;
        cout << "Anti aliasing: " << antiAliasing << endl;
        break;
    case '0':
    case '1':
    case '2':    numReflections = key - '0';
        cout << "Num reflections: " << numReflections << endl;
        break;
    case 'd':    isAnimated = !isAnimated;
        break;
    case ESCAPE:
        glutLeaveMainLoop();
        break;
    default:
        cout << (int)key << "unmapped key pressed." << endl;
    }

    glutPostRedisplay();
}

int main(int argc, char* argv[]) {
    graphicsInit(argc, argv, __FILE__);

    glutDisplayFunc(render);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseUtility);
    glutTimerFunc(TIME_INTERVAL, timer, 0);
    buildScene();

    glutMainLoop();

    return 0;
}
