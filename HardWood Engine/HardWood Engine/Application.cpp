#define GLFW_INCLUDE_NONE
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

//OpenGL Dependencies
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdio.h>

#include "wMath.h"

static const struct
{
    float x, y;
    float r, g, b;
} vertices[3] =
{
    { -0.6f, -0.4f, 1.f, 0.f, 0.f },
    {  0.6f, -0.4f, 0.f, 1.f, 0.f },
    {   0.f,  0.6f, 0.f, 0.f, 1.f }
};

//--- Vertex Shader ---//
static const char* vertex_shader_text =
"#version 110\n"
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";

//--- Fragment Shader ---//
static const char* fragment_shader_text =
"#version 110\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";


void Error_Callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Christine Is The Best: The Game", NULL, NULL);
    if (!window)
    {
        glfwSetErrorCallback(Error_Callback);
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        mat4 newMat = { {1.0f,2.0f,3.0f,4.0f},
                        {4.0f,5.0f,6.0f,1.0f},
                        {4.0f,5.0f,6.0f,1.0f},
                        {7.0f,8.0f,9.0f,1.0f}};

        mat4 oldMat = { {9.0f,8.0f,7.0f,1.0f},
                        {6.0f,5.0f,4.0f,1.0f},
                        {6.0f,5.0f,4.0f,1.0f},
                        {3.0f,2.0f,1.0f,1.0f}};
        mat4 res;

        mat4_mul(res,newMat,oldMat);
        mat4_print(res);
       
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}