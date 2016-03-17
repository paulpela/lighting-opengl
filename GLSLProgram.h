#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

class GLSLProgram {
public:
    GLSLProgram();
    ~GLSLProgram();

    void addVertexShader(const std::string &shaderPath);
    void addFragmentShader(const std::string &shaderPath);
    void addTessellationControlShader(const std::string &shaderPath);
    void addTessellationEvaluationShader(const std::string &shaderPath);
    void addGeometryShader(const std::string &shaderPath);
    void addComputeShader(const std::string &shaderPath);
    void compile();

    void start();
    void stop();

    GLuint getProgramID();

    GLint getUniformLocation(const std::string &uniformName);

    bool setUniformMatrix(const std::string &uniformName, const glm::mat3 &matrix);
    bool setUniformMatrix(const std::string &uniformName, const glm::mat4 &matrix);
    bool setUniformFloat(const std::string &uniformName, const GLfloat &value);
    bool setUniformInt(const std::string &uniformName, const GLint &value);
    bool setUniformVector(const std::string &uniformName, const glm::vec2 &value);
    bool setUniformVector(const std::string &uniformName, const glm::vec3 &value);
    bool setUniformVector(const std::string &uniformName, const glm::vec4 &value);

private:
    GLuint m_programID;
    
    GLuint loadShaderFromFile(const std::string &filePath, GLenum shaderType);
    void freeProgram();
    void printProgramLog(GLuint program);
    void printShaderLog(GLuint shader);
    void loadShader(const std::string &shaderPath, GLenum type);
};
