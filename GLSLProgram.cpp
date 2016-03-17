#include <fstream>
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GLSLProgram.h"

GLSLProgram::GLSLProgram() {
    m_programID = glCreateProgram();
}

GLSLProgram::~GLSLProgram() {
    freeProgram();
}

void GLSLProgram::compile() {
    glLinkProgram(m_programID);

    GLint programLinked = GL_FALSE;
    glGetProgramiv(m_programID, GL_LINK_STATUS, &programLinked);
    if(programLinked != GL_TRUE) {
        std::cerr << "[GLSLP " << this << "] Error while linking program " << m_programID << "\n";
        printProgramLog(m_programID);
        glDeleteProgram(m_programID);
        m_programID = 0;
    }
}

void GLSLProgram::addVertexShader(const std::string &shaderPath) {
    loadShader(shaderPath, GL_VERTEX_SHADER);
}

void GLSLProgram::addFragmentShader(const std::string &shaderPath) {
    loadShader(shaderPath, GL_FRAGMENT_SHADER);
}

void GLSLProgram::addTessellationControlShader(const std::string &shaderPath) {
    loadShader(shaderPath, GL_TESS_CONTROL_SHADER);
}

void GLSLProgram::addTessellationEvaluationShader(const std::string &shaderPath) {
    loadShader(shaderPath, GL_TESS_EVALUATION_SHADER);
}

void GLSLProgram::addGeometryShader(const std::string &shaderPath) {
    loadShader(shaderPath, GL_GEOMETRY_SHADER);
}

void GLSLProgram::addComputeShader(const std::string &shaderPath) {
    loadShader(shaderPath, GL_COMPUTE_SHADER);
}

void GLSLProgram::loadShader(const std::string &shaderPath, GLenum type) {
    GLuint shaderID = loadShaderFromFile(shaderPath, type);
    glAttachShader(m_programID, shaderID);
    glDeleteShader(shaderID);
}

GLuint GLSLProgram::loadShaderFromFile(const std::string &filePath, GLenum shaderType) {
    GLuint shaderID = 0;

    std::string shaderString;
    std::ifstream sourceFile(filePath.c_str());

    if(sourceFile) {
        shaderString.assign(std::istreambuf_iterator<char>(sourceFile), std::istreambuf_iterator<char>());

        shaderID = glCreateShader(shaderType);
        const GLchar *shaderSource = shaderString.c_str();
        glShaderSource(shaderID, 1, (const GLchar **)&shaderSource, NULL);

        glCompileShader(shaderID);

        GLint shaderCompiled = GL_FALSE;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderCompiled);
        if(shaderCompiled != GL_TRUE) {
            std::cerr << "[Shader " << this << "] Error while compiling shader " << shaderID << " from " << filePath << "\n";
            printShaderLog(shaderID);
            glDeleteShader(shaderID);
            shaderID = 0;
            return 0;
        }
    } else {
        std::cerr << "[Shader " << this << "] Error. Unable to open file: " << filePath << "\n";
        return 0;
    }

    return shaderID;
}

inline void GLSLProgram::freeProgram() {
    if(m_programID) {
        glDeleteProgram(m_programID);
    }
}

void GLSLProgram::start() {
    if(glIsProgram(m_programID)) {
        glUseProgram(m_programID);

        GLenum error = glGetError();
        if(error != GL_NO_ERROR) {
            std::cerr << "[Shader " << this << "] Error while binding program " << m_programID << ". " << gluErrorString(error) << "\n";
            printProgramLog(m_programID);
        }
    }
}

void GLSLProgram::stop() {
    glUseProgram(0);
}

GLuint GLSLProgram::getProgramID() {
    return m_programID;
}

void GLSLProgram::printProgramLog(GLuint program) {
    if(glIsProgram(program)) {
        int infoLogLength = 0;
        int maxLength = 0;

        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        char *infoLog = new char[maxLength];

        glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);

        if(infoLogLength > 0) {
            printf("%s\n", infoLog);
        }

        delete[] infoLog;
    } else {
        std::cerr << "[Shader " << this << "] Error. Program " << program << " is not a valid program.\n";
    }
}

void GLSLProgram::printShaderLog(GLuint shader) {
    if(glIsShader(shader)) {
        int infoLogLength = 0;
        int maxLength = 0;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        char *infoLog = new char[maxLength];

        glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);

        if(infoLogLength > 0) {
            printf("%s\n", infoLog);
        }

        delete[] infoLog;
    } else {
        std::cerr << "[Shader " << this << "] Error. Shader " << shader << " is not a valid shader.\n";
    }
}

GLint GLSLProgram::getUniformLocation(const std::string &uniformName) {
    return glGetUniformLocation(m_programID, uniformName.c_str());
}


bool GLSLProgram::setUniformMatrix(const std::string &uniformName, const glm::mat3 &matrix) {
    GLuint location = getUniformLocation(uniformName);

    if(location == -1) return false;

    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));

    return true;
}

bool GLSLProgram::setUniformMatrix(const std::string &uniformName, const glm::mat4 &matrix) {
    GLuint location = getUniformLocation(uniformName);

    if(location == -1) return false;

    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));

    return true;
}

bool GLSLProgram::setUniformFloat(const std::string &uniformName, const GLfloat &value) {
    GLuint location = getUniformLocation(uniformName);

    if(location == -1) return false;

    glUniform1f(location, value);

    return true;
}

bool GLSLProgram::setUniformInt(const std::string &uniformName, const GLint &value) {
    GLuint location = getUniformLocation(uniformName);

    if(location == -1) return false;

    glUniform1i(location, value);

    return true;
}

bool GLSLProgram::setUniformVector(const std::string &uniformName, const glm::vec2 &value) {
    GLuint location = getUniformLocation(uniformName);

    if(location == -1) return false;

    glUniform2fv(location, 1, glm::value_ptr(value));

    return true;
}

bool GLSLProgram::setUniformVector(const std::string &uniformName, const glm::vec3 &value) {
    GLuint location = getUniformLocation(uniformName);

    if(location == -1) return false;

    glUniform3fv(location, 1, glm::value_ptr(value));

    return true;
}

bool GLSLProgram::setUniformVector(const std::string &uniformName, const glm::vec4 &value) {
    GLuint location = getUniformLocation(uniformName);

    if(location == -1) return false;

    glUniform4fv(location, 1, glm::value_ptr(value));

    return true;
}

