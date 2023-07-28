#pragma once
/*
* Description - Contains all the functionality to call, load and handling of the shaders that the application may need
*
* Author - Kody Wood
*
*/
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <limits>

#ifndef SHADERHANDLER
#define wShaderInit InitShader
#define wShaderDelete DeleteShader
//--- Error Defines ---//
#define WShaderError ShaderCheckError
#define WShaderErrorType ShaderCheckType
#define WShaderErrorDelete ShaderCheckDeleted
#define WShaderErrorCompiled ShaderCheckCompiled
#define WShaderErrorLogLength ShaderCheckLogLength
#define WShaderErrorSourceLength ShaderCheckSourceLength
#endif // !SHADERHANDLER


//#define WSHADER_NO_INLINE /*Uncomment if inline is not wanted */
#ifdef WSHADER_NO_INLINE
#define WSHADER_H_FUNC static
#else
#define WSHADER_H_FUNC static inline
#endif // WSHADER_NO_INLINE

WSHADER_H_FUNC std::string LoadShader(const char* file)
{
	std::ifstream shaderFile;

	std::string tempString = "";
	std::string retString = "";
	shaderFile.open(file);

	if (shaderFile.fail())
	{
		exit(-1);
	}

	while (!shaderFile.eof())
	{
		std::getline(shaderFile, tempString);
		retString += tempString+"\n";
	}
	shaderFile.close();
	return retString;
}

WSHADER_H_FUNC GLuint InitShader(const GLenum shaderType, const GLsizei numStrings, const  GLchar* const* shaderName, const GLint* length)
{
	GLuint vertex_shader = glCreateShader(shaderType);
	glShaderSource(vertex_shader, numStrings, shaderName, length);
	glCompileShader(vertex_shader);
	return vertex_shader;
}

WSHADER_H_FUNC void DeleteShader(GLuint shader)
{
	glDeleteShader(shader);
}

//--- SHADER ERROR CHECKS ---//
WSHADER_H_FUNC void ShaderCheckError(GLuint shader, GLenum errorCheck, GLint *ret)
{
	glGetShaderiv(shader,errorCheck,ret);
}
WSHADER_H_FUNC void ShaderCheckType(GLuint shader, GLint* ret)
{
	glGetShaderiv(shader, GL_SHADER_TYPE, ret);
}
WSHADER_H_FUNC void ShaderCheckDeleted(GLuint shader, GLint* ret)
{
	glGetShaderiv(shader, GL_DELETE_STATUS, ret);
}
WSHADER_H_FUNC bool ShaderCheckCompiled(GLuint shader)
{
	GLint ret = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &ret);
	return ret;
}
WSHADER_H_FUNC void ShaderCheckLogLength(GLuint shader, GLint* ret)
{
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, ret);
}
WSHADER_H_FUNC void ShaderCheckSourceLength(GLuint shader, GLint* ret)
{
	glGetShaderiv(shader, GL_SHADER_SOURCE_LENGTH, ret);
}
