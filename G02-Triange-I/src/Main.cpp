#include "Utils.h"

// vertex and fragrament Shader
const char* vsSource  = R"glsl(
    #version 330 core
	layout (location = 0) in vec3 pos;
	void main(){ 
		   gl_Position = vec4(pos, 1.0);
		}
)glsl";

const char* fsSource = R"glsl(
	 #version 330 core
	 
	 uniform vec3 triangleColor;
	 out vec4 fragColor;
	 void main() {
			fragColor = vec4(triangleColor, 1.0);
	}
)glsl";
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
	
	// create program
	programID = loadProgram(vsSource, fsSource);
	glUseProgram(programID);
	GLuint vao, vbo;
	//gen buffer and vertex Array
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleA), triangleA, GL_STATIC_DRAW);

	// binding buffer to array
	GLint posAttrib = glGetAttribLocation(programID, "pos");
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), nullptr);
	glEnableVertexAttribArray(posAttrib);

	
	GLint tUniColor = glGetUniformLocation(programID, "triangleColor");
	glUniform3f(tUniColor, 0.0f, 1.0f, 0.0f);


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

