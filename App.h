#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class App {
    public:
        App();
        ~App();

        void _render();

        virtual void render() = 0;
        virtual void update() = 0;

        void updateMousePosition(const int &x, const int &y);

    protected:
        glm::vec4       m_clearColor;
        GLfloat         m_depthBufferDefault;
        glm::mat4       m_projectionMatrix;
        glm::vec2       m_mousePosition;

    private:
        void beginRender();
        void endRender();

};
