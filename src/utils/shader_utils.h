#ifndef OPENGL_START_SHADER_UTILS_H
#define OPENGL_START_SHADER_UTILS_H
#include <string>

#include "glad/glad.h"

using namespace std;


string LoadShaderFromFile(const string &filePath);
GLuint createShader(string &filePath, GLuint shaderType);
GLuint createProgram(
        string &vertexShaderName,
        string &fragmentShaderName);

#endif //OPENGL_START_SHADER_UTILS_H