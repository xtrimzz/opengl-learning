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

const char* fsSource1 =
"#version 330 core\n"
"out vec4 frag_color;"
"void main() {"
"		frag_color = vec4(0.1f, 0.0f, 0.9f, 1.0);"
"}";

const char* fsSource2 =
"#version 330 core\n"
"out vec4 frag_color;"
"void main() {"
"		frag_color = vec4(0.5f, 0.2f, 0.0f, 1.0);"
"}";

const char* fsSource3 =
"#version 330 core\n"
"out vec4 frag_color;"
"void main() {"
"		frag_color = vec4(0.94f, 0.23f, 0.5f, 1.0);"
"}";

GLuint programID;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// setup window
	GLFWwindow* window = initWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL - Triangle");

	float triangle1[] = {
		-0.5, 0.8, 0.0,
	   -0.3, 0.1, 0.0,
	    -0.7, 0.22, 0.0
	};

	float triangle2[] = {
		0.5, 0.8, 0.0,
		0.9, 0.2, 0.0,
		0.2, 0.2, 0.0
	};

	float triangle3[] = {
		0.5, -0.1, 0.0,
		0.9, -0.9, 0.0,
		0.2, -0.85, 0.0
	};

	float triangle4[] = {
		-0.5, -0.1, 0.0,
		-0.3, -0.85, 0.0,
		-0.7, -0.85, 0.0
	};
	
	
	GLuint vao[4], vbo[4];

	//setup vertex array
	glGenBuffers(4, vbo);
	glGenVertexArrays(4, vao);

	// setup triangle 1
	
	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);

	glBindVertexArray(vao[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);

	glBindVertexArray(vao[2]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle3), triangle3, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);

	glBindVertexArray(vao[3]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle4), triangle4, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);

	// unbind data
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
		glBindVertexArray(vao[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(loadProgram(vsSource, fsSource1));
		glBindVertexArray(vao[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(loadProgram(vsSource, fsSource2));
		glBindVertexArray(vao[2]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(loadProgram(vsSource, fsSource3));
		glBindVertexArray(vao[3]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//SH08 - Delete program out of our main loop
	glDeleteProgram(programID);
	glDeleteVertexArrays(4, vao);
	glDeleteBuffers(4, vbo);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

