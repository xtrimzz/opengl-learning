#include "Utils.h"

// Creating window and its set up
// ------------------------------
GLFWwindow * initWindow(GLuint SCR_W, GLuint SCR_H, const char * TITLE)
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

														 // glfw window creation
														 // --------------------
	GLFWwindow* win = glfwCreateWindow(SCR_W, SCR_H, TITLE, NULL, NULL);
	if (win == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(win);
	glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return nullptr;
	}

	return win;

}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}



// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


///
// Create a shader object, load the shader source, and
// compile the shader.
//
GLuint loadShader(GLenum type, const char *shaderSrc)
{

	GLint compiled = 0;
	GLuint shader = 0;

	// Create the shader object
	shader = glCreateShader(type);

	if (shader == 0) return 0;


	// Load the shader source
	glShaderSource(shader, 1, &shaderSrc, NULL);

	// Compile the shader
	glCompileShader(shader);

	// Check the compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
	{
		GLint infoLen = 0;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			GLchar *infoLog = (GLchar*)malloc(infoLen);

			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			std::cout<< "Error compiling shader: " <<  infoLog << "\n";

			free(infoLog);
		}

		glDeleteShader(shader);
		return 0;
	}

	return shader;

}


///
// Create the program object for compilation
//
GLuint loadProgram(const char* vtxSrc, const char* frgSrc)
{
	GLuint vertexShader = 0;
	GLuint fragmentShader = 0;
	GLuint programObj = 0;
	GLint linked = GL_FALSE;

	// Create the program object
	programObj = glCreateProgram();

	if (programObj == 0)
		return 0;

	// Load the vertex/fragment shaders
	vertexShader = loadShader(GL_VERTEX_SHADER, vtxSrc);
	fragmentShader = loadShader(GL_FRAGMENT_SHADER, frgSrc);

	//Attach shader to program Object
	glAttachShader(programObj, vertexShader);
	glAttachShader(programObj, fragmentShader);

	// Link the program
	glLinkProgram(programObj);

	// Check the link status
	glGetProgramiv(programObj, GL_LINK_STATUS, &linked);

	if (!linked)
	{
		GLint infoLen = 0;

		glGetProgramiv(programObj, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			GLchar *infoLog = (GLchar*)malloc(infoLen);

			glGetProgramInfoLog(programObj, infoLen, NULL, infoLog);
			std::cout << "Error linking program : " << infoLog << std::endl;

			free(infoLog);
		}

		glDeleteProgram(programObj);
		return false;
	}
	return programObj;
}
