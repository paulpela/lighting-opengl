#include "config.h"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "App.h"

App::App() {
    m_clearColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    m_depthBufferDefault = 1.0f;
    m_projectionMatrix = glm::perspective(50.0f, (float) SCREEN_X / (float) SCREEN_Y, 1.0f, 1000.0f);
}

App::~App() {

}

void App::beginRender() {
    glClearBufferfv(GL_COLOR, 0, glm::value_ptr(m_clearColor));
    glClearBufferfv(GL_DEPTH, 0, &m_depthBufferDefault);
}

void App::endRender() {
    glutSwapBuffers();
}

void App::updateMousePosition(const int &x, const int &y) {
    m_mousePosition.x = (GLfloat) x;
    m_mousePosition.y = (GLfloat) y;
}

void App::_render() {
    beginRender();
    render();
    endRender();
}
