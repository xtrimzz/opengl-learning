#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
GLFWwindow* initWindow(GLuint, GLuint, const char*);
GLuint loadShader(GLenum type, const char *shaderSrc);
GLuint loadProgram(const char* vtxSrc, const char* frgSrc);