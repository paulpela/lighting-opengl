#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "App.h"
#include "GLSLProgram.h"

class MyApp : public App {
    public:
        MyApp();
        ~MyApp();

        void render();
        void update();

        void updateShininess(float value);
        void updateRimLightPower(float value);
    private:
        GLSLProgram    *m_shader;

        enum {
            VERTICES,
            INDICES,
            NORMALS,
            NUM_BUFFERS
        } m_buffer_types;

        GLuint          m_VAO;
        GLuint          m_buffers[NUM_BUFFERS];
        glm::vec3       m_lightDirection;
        GLfloat         m_shininess;
        GLfloat         m_rimLightPower;

        GLfloat         m_counter;
};
