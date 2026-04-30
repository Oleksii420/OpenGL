#include "shader_utils.h"
#include "sstream"
#include "iostream"
#include "fstream"
#include "string"
#include "glad/glad.h"

string LoadShaderFromFile(const string &filePath){
    ifstream ShaderFile(filePath);
    if (!ShaderFile.is_open()) {
        cerr << "Не вдалося відкрити файл: " << filePath << endl;
        return "";
    }
    stringstream buffer;
    buffer << ShaderFile.rdbuf();
    return buffer.str();
}

GLuint createShader(string &filePath, GLuint shaderType){
    string shaderCode_str = LoadShaderFromFile(filePath);
    const char* shaderCode = shaderCode_str.c_str();

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);


    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        cerr << "Помилка компіляції шейдера:\n" << filePath << "\n" <<infoLog << endl;
    }

    return shader;
}

GLuint createProgram(string &vertexShaderName,string &fragmentShaderName){
    GLuint vertexShader = createShader(vertexShaderName, GL_VERTEX_SHADER);
    GLuint fragmentShader  = createShader(fragmentShaderName, GL_FRAGMENT_SHADER);
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteProgram(vertexShader);
    glDeleteProgram(fragmentShader);
    return shaderProgram;
}