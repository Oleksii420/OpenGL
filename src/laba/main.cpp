#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "shader_utils.h"

using namespace std;

int main(void) { GLFWwindow* window;
/* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


/* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

/* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glClearColor(1.0, 1.0, 1.0, 1.0);

    std::string vertexShaderName = "res/shaders/triangle.vert";
    std::string fragmentShaderName = "res/shaders/triangle.frag";
    GLuint shaderProgram = createProgram(
            vertexShaderName,
            fragmentShaderName);



    float vertices[] = {
            -0.5f, -0.5f, 0.0f,       0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.0f,      1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.0f,     1.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,      0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.0f,     1.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.0f,        0.0f, 1.0f, 0.0f,
    };




    GLuint VBO;
    GLuint VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1,&VBO);

// робимо VAO поточним (він починає записувати налаштування
    glBindVertexArray(VAO);

// 2. Робимо VBO поточним буфером (GL_ARRAY_BUFFER означає буфер для вершин)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

// 3. Копіюємо наш масив vertices у пам'ять відеокарти
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            6* sizeof(float),
            (void*)0

    );
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          6 * sizeof(float),
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

/* Loop until the user closes the window */
    do
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    } while (!glfwWindowShouldClose(window));

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}