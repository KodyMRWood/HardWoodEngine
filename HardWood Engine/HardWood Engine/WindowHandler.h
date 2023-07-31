#pragma once

/*
* Description - Contains all the functionality to create a window
*
* Author - Kody Wood
*
*/


#ifndef SHADERHANDLER
#define wCreateWindow InitWindow
#endif // !SHADERHANDLER

//#define WSHADER_NO_INLINE /*Uncomment if inline is not wanted */
#ifdef WSHADER_NO_INLINE
#define WSHADER_H_FUNC static
#else
#define WSHADER_H_FUNC static inline
#endif // WSHADER_NO_INLINE


