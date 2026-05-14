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


    glm::mat4 view = glm::lookAt(
            glm::vec3(-2.0f, 1.5f, -4.0f), // позиція камери
            glm::vec3(0.0f, 0.0f, 0.0f), // куди дивимось
            glm::vec3(0.0f, 1.0f, 0.0f) // вектор вгору
    );

    glm::mat4 projection = glm::perspective(
            glm::radians(45.0f),
            (float)width / (float)height,
            0.1f,
            100.0f
    );

    float rectX = 0.0f;
    float rectY = 0.0f;
    float speed = 2.0f;

    float currentAngle = 0.0f;
    float rotationSpeed = 2.0f;



    float lastTime = glfwGetTime();


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);



/* Loop until the user closes the window */
    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очищаємо не лише полотно, на якому малюємо, але й буфер глибини

        glUseProgram(shaderProgram);



        auto model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(rectX, rectY, 0.0f));
        model = glm::rotate(model, currentAngle, glm::vec3 (0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(projection));


        float currentTime = glfwGetTime();
        float delTime = (float)(currentTime - lastTime);
        lastTime = currentTime;

        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
            rectX -= speed * delTime;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
            rectX += speed * delTime;
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
            rectY += speed * delTime;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
            rectY -= speed * delTime;
        }

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float normMouseX = (2.0f * mouseX) / width - 1.0f;
        float normMouseY = 1.0f - (2.0f * mouseY) / height;
        float halfSize = 0.25;

        glm::vec4 cubePosWorld = model * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        glm::vec4 cubePosNDC = projection * view * cubePosWorld;

        float screenX = cubePosNDC.x / cubePosNDC.w;
        float screenY = cubePosNDC.y / cubePosNDC.w;

        float screenHalfSize = halfSize / cubePosNDC.w;

        bool isHovered = (normMouseX > screenX - screenHalfSize &&
                          normMouseX < screenX + screenHalfSize &&
                          normMouseY > screenY - screenHalfSize &&
                          normMouseY < screenY + screenHalfSize);

        if (isHovered) {
            currentAngle += rotationSpeed * delTime;
        }else {
            currentAngle += 0.0f;
        }

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1f(texture_loc, 0);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
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