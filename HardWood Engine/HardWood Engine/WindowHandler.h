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
#endif // !SHADERHANDLER

//#define WSHADER_NO_INLINE /*Uncomment if inline is not wanted */
#ifdef WSHADER_NO_INLINE
#define WSHADER_H_FUNC static
#else
#define WSHADER_H_FUNC static inline
#endif // WSHADER_NO_INLINE

WSHADER_H_FUNC void InitWindow()
{

}

WSHADER_H_FUNC void WindowHint(const int hint, const int value)
{
	glfwWindowHint(hint, value);
}