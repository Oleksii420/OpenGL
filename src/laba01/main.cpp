#include <iostream>
#include <valarray>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "shader_utils.h"
#include "texture.h"

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
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    string vertexShaderName = "res/shaders/triangle.vert";
    string fragmentShaderName = "res/shaders/triangle.frag";
    GLuint shaderProgram = createProgram(
            vertexShaderName,
            fragmentShaderName);


    float vertices[] = {
            /* координати */  -0.25f, -0.25f,  /* тестурні координати */  0.0f, 0.0f,  //  0
            /* координати */   0.25f, -0.25f,  /* тестурні координати */  1.0f, 0.0f, // 1
            /* координати */   0.25f, 0.25f,   /* тестурні координати */  1.0f, 1.0f, // 2
            /* координати */  -0.25f, 0.25f,   /* тестурні координати */  0.0f, 1.0f, // 3
    };

    unsigned int indices[] = {
            0, 1, 2, // перший трикутник
            0, 2, 3, // другий трикутник
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

    GLint shiftUniformPos = glGetUniformLocation(shaderProgram, "uShift");
    GLuint posAttribLocation = glGetAttribLocation(shaderProgram, "aPos");
    GLint texture_loc = glGetUniformLocation(shaderProgram, "uTexture");

    glVertexAttribPointer(
            posAttribLocation,
            2,
            GL_FLOAT,
            GL_FALSE,
            4* sizeof(float),
            (void*)0

    );
    glEnableVertexAttribArray(posAttribLocation);


    GLuint textureCoordsAttribLocation = glGetAttribLocation(shaderProgram, "aUV");
    glVertexAttribPointer(
            textureCoordsAttribLocation,                  // знайдена командою glGetAttribLocation позиція атрибуту у шейдері
            2,                  // 2 компоненти: u, v
            GL_FLOAT,           // тип даних
            GL_FALSE,           // не нормалізувати
            4 * sizeof(float),  // stride: 4 float-а на вершину
            (void*)(2 * sizeof(float))        // offset: починаємо з 2
    );
    glEnableVertexAttribArray(textureCoordsAttribLocation);

    glBindVertexArray(0);

    unsigned int texture1 = loadTexture("res/texture/girl.jpg");
    unsigned int texture2 = loadTexture("res/texture/house.jpg");
    unsigned int texture3 = loadTexture("res/texture/cat.jpg");


/* Loop until the user closes the window */
    do
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);



        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glUniform2f(shiftUniformPos, -0.6f, 0.0f);
        glUniform1i(texture_loc, 0);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glUniform2f(shiftUniformPos, 0.0f, 0.0f);
        glUniform1i(texture_loc, 0);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture3);
        glUniform2f(shiftUniformPos, 0.6f, 0.0f);
        glUniform1i(texture_loc, 0);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);


        /* Poll for and process events */
        glfwPollEvents();
    } while (!glfwWindowShouldClose(window));

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &texture1);
    glDeleteTextures(1, &texture2);
    glDeleteTextures(1, &texture3);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}