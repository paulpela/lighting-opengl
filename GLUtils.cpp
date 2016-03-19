#include "config.h"

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

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
    extern MyApp *g_app;

    if(button == 2) {
        if(state == 0) {
            g_app->updateLightDirection(true);
        } else {
            g_app->updateLightDirection(false);
        }
    }

    if(button == 3 && state == 0) {
        g_app->move(glm::vec3(0.0f, 0.0f, MOVEMENT_SPEED));
    }

    if(button == 4 && state == 0) {
        g_app->move(glm::vec3(0.0f, 0.0f, -MOVEMENT_SPEED));
    }
}

void keyboardHandler(unsigned char key, int x, int y) {
    if(key == 'q') {
        exit(0);
    }

    extern MyApp *g_app;

    switch(key) {
        case 'w':
            g_app->updateShininess(+10.0f);
            break;
        case 's':
            g_app->updateShininess(-10.0f);
            break;
        case 'x':
            g_app->switchSpecular();
            break;
        case 'e':
            g_app->updateRimLightPower(1.0f);
            break;
        case 'd':
            g_app->updateRimLightPower(-1.0f);
            break;
        case 'c':
            g_app->switchRimLight();
            break;
        case ' ':
            g_app->pauseRotation();
            break;
        case '+':
            g_app->move(glm::vec3(0.0f, 0.0f, MOVEMENT_SPEED));
            break;
        case '-':
            g_app->move(glm::vec3(0.0f, 0.0f, -MOVEMENT_SPEED));
            break;
    }
}

void keyboardHandlerSpecial(int key, int x, int y) {
    extern MyApp *g_app;

    switch(key) {
        case GLUT_KEY_LEFT:
            g_app->move(glm::vec3(-MOVEMENT_SPEED, 0.0f, 0.0f));
            break;
        case GLUT_KEY_RIGHT:
            g_app->move(glm::vec3(MOVEMENT_SPEED, 0.0f, 0.0f));
            break;
        case GLUT_KEY_UP:
            g_app->move(glm::vec3(0.0f, MOVEMENT_SPEED, 0.0f));
            break;
        case GLUT_KEY_DOWN:
            g_app->move(glm::vec3(0.0f, -MOVEMENT_SPEED, 0.0f));
            break;
    }
}

void onResize(int x, int y) {
    glViewport(0, 0, x, y);
}

void mouseMotion(int x, int y) {
    extern MyApp *g_app;
    g_app->updateMousePosition(x, y);
}

void passiveMouseMotion(int x, int y) {
    extern MyApp *g_app;
    g_app->updateMousePosition(x, y);
}
