#include "Utils.h"

// vertex and fragrament Shader
const char* vsSource  = 
" #version 330 core\n"
	"layout(location = 0) in vec3 pos;"
	"void main()"
		"{ "
		"    gl_Position = vec4(pos, 1.0);"
		"}";
const char* fsSource = 
	"#version 330 core\n"
	"out vec4 frag_color;"
	"void main() {"
	"		frag_color = vec4(0.2f, 0.43f, 0.6f, 1.0);"
	"}";
GLuint programID;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// setup window
	GLFWwindow* window = initWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL - Triangle");

	float triangleA[] = {
		0.34, 0.6, 0.0,
	   -0.45, -0.23, 0.0,
	    0.8, -0.5, 0.0
	};
	
	GLuint vao, vbo;
	//setup vertex array
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//setup vertex buffer
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleA), triangleA, GL_STATIC_DRAW);

	// binding buffer to array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	//OPT: unbinding buffer and array obj
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		programID = loadProgram(vsSource, fsSource);
		glUseProgram(programID);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES,0, 3);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//SH08 - Delete program out of our main loop
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

