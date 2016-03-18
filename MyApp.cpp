#include "config.h"

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "MyApp.h"
#include "GLSLProgram.h"

void MyApp::render() {
    m_shader->start();
    
    glm::mat4 modelViewMatrix = glm::mat4(1);
    glm::vec3 translation = glm::vec3(0.0f, 5.0f, -60.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 rotationY = glm::vec3(0.0f, 1.0f, 0.0f);
    modelViewMatrix = glm::translate(modelViewMatrix, translation);
    modelViewMatrix = glm::translate(modelViewMatrix, m_movementModifier);
    modelViewMatrix = glm::rotate(modelViewMatrix, glm::radians(180.0f), rotation);
    modelViewMatrix = glm::rotate(modelViewMatrix, glm::radians(m_counter / 4.0f), rotationY);

    m_shader->setUniformMatrix("modelViewMatrix", modelViewMatrix);
    m_shader->setUniformMatrix("projectionMatrix", m_projectionMatrix);
    m_shader->setUniformVector("lightDirection", m_lightDirection);
    m_shader->setUniformFloat("shininess", m_shininess);
    m_shader->setUniformFloat("rimPower", m_rimLightPower);
    m_shader->setUniformInt("specularOn", m_isSpecularOn);
    m_shader->setUniformInt("rimLightOn", m_isRimLightOn);

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 300000, GL_UNSIGNED_INT, 0);

    m_shader->stop();
}

MyApp::MyApp() : App() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    m_shader = new GLSLProgram();
    m_shader->addVertexShader("shaders/shader.vs");
    m_shader->addFragmentShader("shaders/shader.fs");
    m_shader->compile();

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(NUM_BUFFERS, m_buffers);

    glBindBuffer(GL_ARRAY_BUFFER, m_buffers[VERTICES]);
    extern const int num_vertices;
    extern GLfloat vertices[49990 * 3];
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_buffers[NORMALS]);
    extern const int num_normals;
    extern GLfloat normals[49990 * 3];
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[INDICES]);
    extern const int num_indices;
    extern GLuint indices[300000];
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    m_lightDirection = glm::vec3(0.0f, 0.0f, 2.0f);

    m_counter = 0.0f;

    m_shininess = 27.8974f;
    m_rimLightPower = 1.0f;

    m_isSpecularOn = false;
    m_isRimLightOn = false;

    m_movementModifier = glm::vec3(0.0f, 0.0f, 0.0f);
}

MyApp::~MyApp() {
    delete m_shader;
}


void MyApp::update() {
    if(!m_isPaused) {
        m_counter += 1.0f;
    }

    m_lightDirection.x = -(m_mousePosition.x - (float) SCREEN_X / 2);
    m_lightDirection.y = m_mousePosition.y - (float) SCREEN_Y / 2;
}

void MyApp::updateShininess(float value) {
    m_shininess += value;

    if(m_shininess < 1.0f) {
        m_shininess = 1.0f;
    }
    
    if(m_shininess > 254.0f) {
        m_shininess = 254.0f;
    }
}

void MyApp::updateRimLightPower(float value) {
    m_rimLightPower += value;
}

void MyApp::switchSpecular() {
    m_isSpecularOn = m_isSpecularOn ? false : true;
}

void MyApp::switchRimLight() {
    m_isRimLightOn = m_isRimLightOn ? false : true;
}

void MyApp::pauseRotation() {
    m_isPaused = m_isPaused ? false : true;
}

void MyApp::move(const glm::vec3 &displacement) {
    m_movementModifier.x += displacement.x;
    m_movementModifier.y += displacement.y;
    m_movementModifier.z += displacement.z;
}
