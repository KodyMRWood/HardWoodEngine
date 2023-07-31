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

#ifndef SHADERHANDLER
#define wLoadShader LoadShader
#define wShaderInit InitShader
#define wInitProgram InitProgram
#define wUseProgram UseProgram
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


/* A simple function that will read a file into an allocated char pointer buffer */
WSHADER_H_FUNC char* LoadShader(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;

	fptr = fopen(file, "rb");
	if (!fptr)
	{
		return NULL;
	}
	fseek(fptr, 0, SEEK_END);
	length = ftell(fptr);
	buf = (char*)malloc(length + 1);
	fseek(fptr, 0, SEEK_SET);
	fread(buf, length, 1, fptr);
	fclose(fptr);
	buf[length] = 0; //Null terminator

	return buf;
}

WSHADER_H_FUNC std::string LoadShaderString(const char* file)
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

WSHADER_H_FUNC GLuint InitShader(const GLenum &shaderType, const GLsizei &numStrings, const  GLchar* const* &shaderName, const GLint* &length)
{
	GLuint vertex_shader = glCreateShader(shaderType);
	glShaderSource(vertex_shader, numStrings, shaderName, length);
	glCompileShader(vertex_shader);
	return vertex_shader;
}

WSHADER_H_FUNC void InitProgram(GLuint &program, const GLuint &vertexShader, const GLuint &fragmentShader)
{
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
}

WSHADER_H_FUNC void InitProgram(GLuint &program, const GLuint vertexShader[], const GLuint fragmentShader[])
{

}

WSHADER_H_FUNC void UseProgram(const GLuint &program)
{
	glUseProgram(program);
}

WSHADER_H_FUNC void DeleteShader(GLuint &shader)
{
	glDeleteShader(shader);
}

//--- SHADER ERROR CHECKS ---//
WSHADER_H_FUNC void ShaderCheckError(const GLuint &shader, const GLenum &errorCheck, GLint *ret)
{
	glGetShaderiv(shader,errorCheck,ret);
}
WSHADER_H_FUNC void ShaderCheckType(const GLuint &shader, GLint* ret)
{
	glGetShaderiv(shader, GL_SHADER_TYPE, ret);
}
WSHADER_H_FUNC void ShaderCheckDeleted(const GLuint &shader, GLint* ret)
{
	glGetShaderiv(shader, GL_DELETE_STATUS, ret);
}
WSHADER_H_FUNC bool ShaderCheckCompiled(const GLuint &shader)
{
	GLint ret = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &ret);
	return ret;
}
WSHADER_H_FUNC void ShaderCheckLogLength(const GLuint &shader, GLint* ret)
{
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, ret);
}
WSHADER_H_FUNC void ShaderCheckSourceLength(const GLuint &shader, GLint* ret)
{
	glGetShaderiv(shader, GL_SHADER_SOURCE_LENGTH, ret);
}
