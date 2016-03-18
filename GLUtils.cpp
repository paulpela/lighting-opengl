#include "config.h"

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "GLUtils.h"
#include "MyApp.h"

void render() {
    extern MyApp *g_app;
    g_app->_render();
}

void update() {
    extern MyApp *g_app;
    g_app->update();
}

void mainLoop(int t) {
    update();
    render();
    glutTimerFunc(1000/FPS, mainLoop, t);
}

void mouseHandler(int button, int state, int x, int y) {

}

void keyboardHandler(unsigned char key, int x, int y) {
    if(key == 'q') {
        exit(0);
    }

    extern MyApp *g_app;

    if(key == 'w') {
        g_app->updateShininess(+10.0f);
    }

    if(key == 's') {
        g_app->updateShininess(-10.0f);
    }

    if(key == 'x') {
        g_app->switchSpecular();
    }

    if(key == 'e') {
        g_app->updateRimLightPower(1.0f);
    }

    if(key == 'd') {
        g_app->updateRimLightPower(-1.0f);
    }

    if(key == 'c') {
        g_app->switchRimLight();
    }

    if(key == ' ') {
        g_app->pauseRotation();
    }
}

void onResize(int x, int y) {
    glViewport(0, 0, x, y);
}

void passiveMouseMotion(int x, int y) {
    extern MyApp *g_app;
    g_app->updateMousePosition(x, y);
}
