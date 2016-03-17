#include "config.h"

#include <iostream>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "GLUtils.h"
#include "MyApp.h"

MyApp *g_app;

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitContextProfile(GLUT_CORE_PROFILE | GLUT_DEBUG);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE | GLUT_RGBA);
    glutInitWindowSize(SCREEN_X, SCREEN_Y);
    glutCreateWindow(argv[0]);

    if(glewInit() != GLEW_OK) {
        exit(1);
    }

    glutDisplayFunc(render);
    glutKeyboardFunc(keyboardHandler);
    glutMouseFunc(mouseHandler);
    glutReshapeFunc(onResize);
    glutTimerFunc(1000/FPS, mainLoop, 0);
    glutPassiveMotionFunc(passiveMouseMotion);

#ifdef FULLSCREEN
    glutFullScreen();
#endif

    glViewport(0, 0, SCREEN_X, SCREEN_Y);

    g_app = new MyApp();

    glutMainLoop();

    return 0;
}
