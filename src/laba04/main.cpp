#include <fstream>
#include <iostream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader_utils.h"
#include "texture.h"


#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

int main(void) { GLFWwindow* window;
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
    if (!window)
    {
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


    float vertices[] = {
            // -------- Передня грань (червона) --------
            0.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f, /* текстурні координати */ 0.0, 0.0,  // лівий нижній
            1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f, /* текстурні координати */ 1.0, 0.0,  // правий нижній
            1.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.0f, /* текстурні координати */ 1.0, 1.0,  // правий верхній
            0.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.0f, /* текстурні координати */ 0.0, 1.0,  // лівий верхній

            // -------- Задня грань (зелена) --------
            0.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   /* текстурні координати */ 0.0, 0.0,
            1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   /* текстурні координати */ 1.0, 0.0,
            1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f,   /* текстурні координати */ 1.0, 1.0,
            0.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f,   /* текстурні координати */ 0.0, 1.0,

            // -------- Ліва грань (синя) --------
            0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,/* текстурні координати */ 0.0, 0.0,
            0.0f, 1.0f, 0.0f,   0.0f, 0.0f, 1.0f,/* текстурні координати */ 1.0, 0.0,
            0.0f, 1.0f, 1.0f,   0.0f, 0.0f, 1.0f,/* текстурні координати */ 1.0, 1.0,
            0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,/* текстурні координати */ 0.0, 1.0,

            // -------- Права грань (жовта) --------
            1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 0.0f,   /* текстурні координати */ 0.0, 0.0,
            1.0f, 1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   /* текстурні координати */ 1.0, 0.0,
            1.0f, 1.0f, 1.0f,   1.0f, 1.0f, 0.0f,   /* текстурні координати */ 1.0, 1.0,
            1.0f, 0.0f, 1.0f,   1.0f, 1.0f, 0.0f,   /* текстурні координати */ 0.0, 1.0,

            // -------- Нижня грань (бірюзова) --------
            0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 1.0f,   /* текстурні координати */ 0.0, 0.0,
            0.0f, 0.0f, 1.0f,   0.0f, 1.0f, 1.0f,   /* текстурні координати */ 1.0, 0.0,
            1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 1.0f,   /* текстурні координати */ 1.0, 1.0,
            1.0f, 0.0f, 0.0f,   0.0f, 1.0f, 1.0f,   /* текстурні координати */ 0.0, 1.0,

            // -------- Верхня грань (фіолетова) --------
            0.0f, 1.0f, 0.0f,   1.0f, 0.0f, 1.0f,    /* текстурні координати */ 0.0, 0.0,
            1.0f, 1.0f, 0.0f,   1.0f, 0.0f, 1.0f,    /* текстурні координати */ 1.0, 0.0,
            1.0f, 1.0f, 1.0f,   1.0f, 0.0f, 1.0f,    /* текстурні координати */ 1.0, 1.0,
            0.0f, 1.0f, 1.0f,   1.0f, 0.0f, 1.0f,    /* текстурні координати */ 0.0, 1.0,
    };

    unsigned int indices[] = {
            0, 2, 1,    2, 0, 3,       // передня
            4, 5, 6,    6, 7, 4,       // задня
            8, 10, 9,   10,8,11,       // ліва
            12,13,14,   14,15,12,       // права
            16,18, 17,  18,16,19,       // нижня
            20,22,21,   22,20,23        // верхня
    };


    glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  1.5f, -3.0f),
            glm::vec3(-1.5f, -1.0f, -1.5f)
    };


    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

    bool firstMouse = true;
    float yaw   = -90.0f;
    float pitch =  0.0f;
    float lastX =  640.0f;
    float lastY =  360.0f;

    GLuint VBO;
    GLuint EBO;
    GLuint VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1, &EBO);


// робимо VAO поточним (він починає записувати налаштування
    glBindVertexArray(VAO);

// 2. Робимо VBO поточним буфером (GL_ARRAY_BUFFER означає буфер для вершин)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
// 3. Копіюємо наш масив vertices у пам'ять відеокарти
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof (indices), indices, GL_STATIC_DRAW);


    GLuint posAttribLocation = glGetAttribLocation(shaderProgram, "aPos");
    GLint texture_loc = glGetUniformLocation(shaderProgram, "uTexture");
    GLint isOutline_loc = glGetUniformLocation(shaderProgram, "isOutline");

    glVertexAttribPointer(
            posAttribLocation,
            3,
            GL_FLOAT,
            GL_FALSE,
            8* sizeof(float),
            (void*)0

    );
    glEnableVertexAttribArray(posAttribLocation);



    GLuint textureCoordsAttribLocation = glGetAttribLocation(shaderProgram, "aUV");
    glVertexAttribPointer(
            textureCoordsAttribLocation,                  // знайдена командою glGetAttribLocation позиція атрибуту у шейдері
            2,                  // 2 компоненти: u, v
            GL_FLOAT,           // тип даних
            GL_FALSE,           // не нормалізувати
            8 * sizeof(float),  // stride: 4 float-а на вершину
            (void*)(6 * sizeof(float))        // offset: починаємо з 2
    );
    glEnableVertexAttribArray(textureCoordsAttribLocation);

    glBindVertexArray(0);

    unsigned int texture = loadTexture("res/texture/brick.jpg");


    GLint model_loc = glGetUniformLocation(shaderProgram, "uModel");
    GLint view_loc = glGetUniformLocation(shaderProgram, "uView");
    GLint proj_loc = glGetUniformLocation(shaderProgram, "uProjection");


    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glm::mat4 projection = glm::perspective(
            glm::radians(45.0f),
            (float)width / (float)height,
            0.1f,
            100.0f
    );


    float currentAngle = 0.0f;
    float rotationSpeed = 2.0f;

    int activeCubeIndex = 0;
    bool tabWasPressed = false;


    float lastTime = glfwGetTime();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);



/* Loop until the user closes the window */
    do
    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

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

        yaw   += xoffset;
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


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(texture_loc, 0);

        glBindVertexArray(VAO);


        for(int i = 0; i < 3; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);

            if (i == activeCubeIndex) {
                model = glm::rotate(model, currentAngle, glm::vec3(0.0f, 1.0f, 0.0f));

                glStencilFunc(GL_ALWAYS, 1, 0xFF);
                glStencilMask(0xFF);
            } else {
                glStencilMask(0x00);
            }

            glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));
            glUniform1i(isOutline_loc, 0);
            glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
        }


        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);

        glm::mat4 outlineModel = glm::mat4(1.0f);
        outlineModel = glm::translate(outlineModel, cubePositions[activeCubeIndex]);
        outlineModel = glm::rotate(outlineModel, currentAngle, glm::vec3(0.0f, 1.0f, 0.0f));

        outlineModel = glm::scale(outlineModel, glm::vec3(1.05f, 1.05f, 1.05f));

        glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(outlineModel));
        glUniform1i(isOutline_loc, 1);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);


        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glEnable(GL_DEPTH_TEST);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        glfwPollEvents();

    } while (!glfwWindowShouldClose(window));


    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &texture);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}