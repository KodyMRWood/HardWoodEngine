#pragma once

/*
* Description - Contains all the functionality to create a window
*
* Author - Kody Wood
*
*/
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifndef SHADERHANDLER
#define wWindowHint WindowHint
#define wCreateWindow InitWindow
#define wCreateFullscreenWindow InitFullScreenWindow
#define wMakeCurrentContext MakeCurrentContext
#define wCloseWindow CloseWindow
#define wDestroyWindow DestroyWindow
#endif // !SHADERHANDLER

//#define WSHADER_NO_INLINE /*Uncomment if inline is not wanted */
#ifdef WSHADER_NO_INLINE
#define WSHADER_H_FUNC static
#else
#define WSHADER_H_FUNC static inline
#endif // WSHADER_NO_INLINE

WSHADER_H_FUNC GLFWwindow* InitWindow(int width, int height, std::string windowTitle)
{
	GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "HardWood Engine", NULL /* FULLSCREEN: glfwGetPrimaryMonitor()*/, NULL);
	return window;
}

WSHADER_H_FUNC GLFWwindow* InitFullScreenWindow()
{
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "HardWood Engine", glfwGetPrimaryMonitor(), NULL);
	return window;
}

WSHADER_H_FUNC void WindowHint(const int hint, const int value)
{
	glfwWindowHint(hint, value);
}

WSHADER_H_FUNC void MakeCurrentContext(GLFWwindow* window)
{
	glfwMakeContextCurrent(window);
}

WSHADER_H_FUNC void CloseWindow(GLFWwindow* window, int shouldClose)
{
	glfwSetWindowShouldClose(window, shouldClose);
}

WSHADER_H_FUNC void DestroyWindow(GLFWwindow* window)
{
	glfwDestroyWindow(window);
}