#include <iostream>
#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <sstream>
#include <iostream>

using std::ostringstream;

// settings
// Global Variables 
const char* APP_TITLE = "Introduction - Hello Window 1";
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 450;
GLFWwindow* window = NULL;

void framebuffer_size_callback(GLFWwindow* win, int width, int height);
void processInput(GLFWwindow *win);
void showFPS(GLFWwindow * win);
bool initOpenGL();


int main() {

	if (initOpenGL())
	{
		// render loop
		// -----------
		while (!glfwWindowShouldClose(window))
		{
			//display frames per secs
			//-----------------------
			showFPS(window);
			// input
			// -----
			processInput(window);

			// render
			// ------
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);


			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			// -------------------------------------------------------------------------------
			glfwSwapBuffers(window);
			glfwPollEvents();
		}// end while !glfwWinodwShouldClose
	}
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;

}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *win)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(win, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* win, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

//Initialize GLFW and OpenGL
//--------------------------
bool initOpenGL()
{
	// glfw: initialize and configure
	// ------------------------------
	if (!glfwInit())
	{
		//An error occured
		std::cerr << "GLFW initialization failed" << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

														 // glfw window creation
														 // --------------------
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, APP_TITLE, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	return true;
}

//Show Frames Per Seconds --------------------------
//--------------------------------------------------
void showFPS(GLFWwindow * win)
{

	//frame counts
	static int frameCount = 0;
	static double prevSecs = 0.0;

	double currentSecs = glfwGetTime(); // secs since GLFW started

	double elapsedSecs{};

	elapsedSecs = currentSecs - prevSecs;

	//Limit text update to 4 times / secs
	if (elapsedSecs > 0.25)
	{
		prevSecs = currentSecs;
		double fps = (double)frameCount / elapsedSecs;
		double msPerFrame = 1000.0 / fps;

		ostringstream outs;
		outs.precision(3);
		outs << std::fixed << APP_TITLE << " " << " FPS: " << fps << " " << " FrameTime: " << msPerFrame << "(ms)";
		glfwSetWindowTitle(win, outs.str().c_str());

		frameCount = 0;
	}

	frameCount++;
}
