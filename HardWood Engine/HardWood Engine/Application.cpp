#define GLFW_INCLUDE_NONE
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

//OpenGL Dependencies
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>
//Proprietary
#include "linmath.h"
#include "ShaderHandler.h";
//#include "wMath.h"

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
"#version 410\n"
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";

static const char* vertex_shader_text_test = R"GLSL(
#version 410
uniform mat4 MVP;
attribute vec3 vCol;
attribute vec2 vPos;
varying vec3 color;
void main()
{
    gl_Position = MVP * vec4(vPos, 0.0, 1.0);
    color = vCol;
})GLSL";

const char* fileDir = "../HardWood Engine/BaseVertex.glsl";
static const char* vertex_shader_text_test2 = LoadShaderChar(fileDir);

//--- Fragment Shader ---//
static const char* fragment_shader_text =
"#version 410\n"
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
	GLuint vertex_buffer, vertex_shader, fragment_shader, program;
	GLint mvp_location, vpos_location, vcol_location;

	glfwSetErrorCallback(Error_Callback);

	/* Initialize the library */
	if (!glfwInit()) {
		return -1;
	}


	/* Create a windowed mode window and its OpenGL context */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "HardWood Engine", NULL, NULL);
	//window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Christine Is The Best: The Game", glfwGetPrimaryMonitor(), NULL); /* FULL SCREEN MODE */

	if (!window) {
		glfwTerminate();
		return -1;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSetKeyCallback(window, Key_Callback);
	//PFNGLUSEPROGRAMPROC glUseProgram = (PFNGLUSEPROGRAMPROC) glfwGetProcAddress("glUseProgram");
	glfwSwapInterval(1);

	// NOTE: OpenGL error checks have been omitted for brevity

	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Create Vertex Shader
	vertex_shader = wShaderInit(GL_VERTEX_SHADER, 1, &vertex_shader_text_test2, NULL);
	std::cout << *vertex_shader_text_test2 << std::endl;

	if (!WShaderErrorCompiled(vertex_shader))
	{
		glDeleteShader(vertex_shader);
		return -1;
	}

	// Create Fragment Shader
	fragment_shader = wShaderInit(GL_FRAGMENT_SHADER, 1, &fragment_shader_text, NULL);
	if (!WShaderErrorCompiled(fragment_shader))
	{
		glDeleteShader(fragment_shader);
		return -1;
	}

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	mvp_location = glGetUniformLocation(program, "MVP");
	vpos_location = glGetAttribLocation(program, "vPos");
	vcol_location = glGetAttribLocation(program, "vCol");

	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
		sizeof(vertices[0]), (void*)0);
	glEnableVertexAttribArray(vcol_location);
	glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
		sizeof(vertices[0]), (void*)(sizeof(float) * 2));

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		float ratio;
		int width, height;
		mat4x4 m, p, mvp;

		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		mat4x4_identity(m);
		mat4x4_rotate_Z(m, m, (float)glfwGetTime());
		mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		mat4x4_mul(mvp, p, m);

		glUseProgram(program);
		glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)mvp);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}