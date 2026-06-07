#include <vector>
#include <iostream>
#include <cstddef>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader_utils.h"
#include "texture.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "load_obj.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>



using namespace std;



int main(void) {
    GLFWwindow *window;
/* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


/* Create a windowed mode window and its OpenGL context */
    auto width = 1280;
    auto height = 720;
    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

/* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    string vertexShaderName = "res/shaders/rect.vert";
    string fragmentShaderName = "res/shaders/rect.frag";
    GLuint shaderProgram = createProgram(
            vertexShaderName,
            fragmentShaderName);



    // === 1. МАСИВИ НАЛАШТУВАНЬ АРТЕФАКТІВ ===
    std::string modelPaths[3] = {
            "res/texture/Jar.obj",      // ВАЗА (Золото)
            "res/texture/13032_Claymore_Sword_v1_l3.obj",    // МЕЧ (Срібло)
            "res/texture/Emeraldobj1.obj"       // ГЕМ (Смарагд)
    };


    float modelScales[3] = {
            0.05f,
            0.05f,
            0.02f };

    int indexCounts[3];


    GLuint VAO[3], VBO[3], EBO[3];
    glGenVertexArrays(3, VAO);
    glGenBuffers(3, VBO);
    glGenBuffers(3, EBO);


    GLuint posAttribLocation = glGetAttribLocation(shaderProgram, "aPos");
    GLint normalAttribLocation = glGetAttribLocation(shaderProgram, "aNormal");
    GLuint textureCoordsAttribLocation = glGetAttribLocation(shaderProgram, "aUV");


    glm::vec3 cubePositions[] = {
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(4.0f, 1.0f, -0.0f),
            glm::vec3(-4.0f, 3.0f, 1.0f)
    };


    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 15.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    bool firstMouse = true;
    float yaw = -90.0f;
    float pitch = 0.0f;
    float lastX = 640.0f;
    float lastY = 360.0f;



    for (int i = 0; i < 3; i++) {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        loadOBJ(modelPaths[i].c_str(), vertices, indices);
        indexCounts[i] = indices.size();

        glBindVertexArray(VAO[i]);

        // Завантажуємо вершини
        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        // Завантажуємо індекси
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);


        glVertexAttribPointer(posAttribLocation,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              sizeof(Vertex),
                              (void *) offsetof(Vertex, Position));
        glEnableVertexAttribArray(posAttribLocation);


        if (normalAttribLocation != -1) {
            glVertexAttribPointer(normalAttribLocation,
                                  3, GL_FLOAT,
                                  GL_FALSE,
                                  sizeof(Vertex),
                                  (void *) offsetof(Vertex, Normal));
            glEnableVertexAttribArray(normalAttribLocation);
        }

        glVertexAttribPointer(textureCoordsAttribLocation,
                              2,
                              GL_FLOAT,
                              GL_FALSE,
                              sizeof(Vertex),
                              (void *) offsetof(Vertex, TexCoords));
        glEnableVertexAttribArray(textureCoordsAttribLocation);
    }
    glBindVertexArray(0);


        GLint model_loc = glGetUniformLocation(shaderProgram, "uModel");
        GLint view_loc = glGetUniformLocation(shaderProgram, "uView");
        GLint proj_loc = glGetUniformLocation(shaderProgram, "uProjection");


        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        glm::mat4 projection = glm::perspective(
                glm::radians(45.0f),
                (float) width / (float) height,
                0.1f,
                100.0f
        );


        float currentAngle = 0.0f;
        float rotationSpeed = 2.0f;

        int activeCubeIndex = 0;
        bool tabWasPressed = false;


        float lastTime = glfwGetTime();

        glEnable(GL_DEPTH_TEST);


/* Loop until the user closes the window */
        do {

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            float currentTime = glfwGetTime();
            float delTime = (currentTime - lastTime);
            lastTime = currentTime;

            float cameraSpeed = 2.5f * delTime;

            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                cameraPos += cameraSpeed * cameraFront;
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                cameraPos -= cameraSpeed * cameraFront;

            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

            bool tabIsPressed = (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS);

            if (tabIsPressed && !tabWasPressed) {
                activeCubeIndex++;
                if (activeCubeIndex >= 3) {
                    activeCubeIndex = 0;
                }
            }
            tabWasPressed = tabIsPressed;

            currentAngle += rotationSpeed * delTime;

            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);

            if (firstMouse) {
                lastX = xpos;
                lastY = ypos;
                firstMouse = false;
            }


            float xoffset = xpos - lastX;
            float yoffset = lastY - ypos;
            lastX = xpos;
            lastY = ypos;

            float sensitivity = 0.1f;
            xoffset *= sensitivity;
            yoffset *= sensitivity;

            yaw += xoffset;
            pitch += yoffset;

            if (pitch > 89.0f) pitch = 89.0f;
            if (pitch < -89.0f) pitch = -89.0f;


            glm::vec3 front;
            front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            front.y = sin(glm::radians(pitch));
            front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
            cameraFront = glm::normalize(front);

            glUseProgram(shaderProgram);

            glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);


            glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(projection));




            glUniform3f(glGetUniformLocation(shaderProgram, "viewPos"), cameraPos.x, cameraPos.y, cameraPos.z);


            glm::vec3 lightPos = cubePositions[activeCubeIndex] + glm::vec3(0.0f, 2.0f, 5.0f);
            glUniform3f(glGetUniformLocation(shaderProgram, "light.position"), lightPos.x, lightPos.y, lightPos.z);


            glUniform3f(glGetUniformLocation(shaderProgram, "light.ambient"), 0.05f, 0.05f, 0.05f);
            glUniform3f(glGetUniformLocation(shaderProgram, "light.diffuse"), 1.0f, 0.9f, 0.8f);
            glUniform3f(glGetUniformLocation(shaderProgram, "light.specular"), 2.0f, 2.0f, 2.0f);


            glUniform1f(glGetUniformLocation(shaderProgram, "light.constant"), 1.0f);
            glUniform1f(glGetUniformLocation(shaderProgram, "light.linear"), 0.09f); // Було 0.22
            glUniform1f(glGetUniformLocation(shaderProgram, "light.quadratic"), 0.032f); // Було 0.20



            for(int i = 0; i < 3; i++) {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                model = glm::scale(model, glm::vec3(modelScales[i], modelScales[i], modelScales[i]));

                if (i == activeCubeIndex) {
                    model = glm::rotate(model, currentAngle, glm::vec3(0.0f, 0.0f, 1.0f));
                }

                glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));


                if (i == 0) {
                    //ЗОЛОТО
                    glUniform3f(glGetUniformLocation(shaderProgram, "material.ambient"), 0.24725,	0.1995	,0.0745);
                    glUniform3f(glGetUniformLocation(shaderProgram, "material.diffuse"), 0.75164,	0.60648	,0.22648);
                    glUniform3f(glGetUniformLocation(shaderProgram, "material.specular"), 0.628281,	0.555802,	0.366065);
                    glUniform1f(glGetUniformLocation(shaderProgram, "material.shininess"), 27.9f);
                }
                else if (i == 1) {
                    //СРІБЛО
                    glUniform3f(glGetUniformLocation(shaderProgram, "material.ambient"), 0.19225	,0.19225	,0.19225);
                    glUniform3f(glGetUniformLocation(shaderProgram, "material.diffuse"), 0.50754	,0.50754	,0.50754);
                    glUniform3f(glGetUniformLocation(shaderProgram, "material.specular"), 0.508273	,0.508273,	0.508273);
                    glUniform1f(glGetUniformLocation(shaderProgram, "material.shininess"), 27.9f);
                }
                else if (i == 2) {
                    //СМАРАГД
                    glUniform3f(glGetUniformLocation(shaderProgram, "material.ambient"), 0.0215f, 0.1745f, 0.0215f);
                    glUniform3f(glGetUniformLocation(shaderProgram, "material.diffuse"), 0.07568f, 0.61424f, 0.07568f);
                    glUniform3f(glGetUniformLocation(shaderProgram, "material.specular"), 0.633f, 0.727811f, 0.633f);
                    glUniform1f(glGetUniformLocation(shaderProgram, "material.shininess"), 76.8f);
                }


                glBindVertexArray(VAO[i]);
                glDrawElements(GL_TRIANGLES, indexCounts[i], GL_UNSIGNED_INT, 0);
            }

            glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
            glStencilMask(0x00);


            glStencilMask(0xFF);
            glStencilFunc(GL_ALWAYS, 1, 0xFF);
            glEnable(GL_DEPTH_TEST);

            glfwSwapBuffers(window);
            glfwPollEvents();

        } while (!glfwWindowShouldClose(window));



    glDeleteBuffers(3, VBO);
    glDeleteVertexArrays(3, VAO);
    glDeleteBuffers(3, EBO);
    glDeleteProgram(shaderProgram);

        glfwTerminate();
        return 0;
    }