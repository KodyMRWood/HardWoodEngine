#define GLFW_INCLUDE_NONE
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>


void Error_Callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
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