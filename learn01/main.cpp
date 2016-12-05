#include <iostream>

#include <glew.h>

#include <GLFW\glfw3.h>

#include <glm.hpp>

GLFWwindow *window;

using namespace glm;
using namespace std;

int main()
{
	if(!glfwInit())
	{
		cout<<"glfw init error"<<endl;
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_RESIZABLE,GL_TRUE);

	window = glfwCreateWindow(1000,800,"learn01",NULL,NULL);
	glfwMakeContextCurrent(window);
	if(window == NULL)
	{
		cout<<"create window error"<<endl;
		glfwTerminate();
		return -1;
	}

	if(glewInit()!= GLEW_OK)
	{
		cout<<"glew init error"<<endl;
		return -1;
	}

	do
	{
		glClearColor(0.7f,0.7f,0.7f,1.0f);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}while(glfwGetKey(window,GLFW_KEY_ESCAPE)!=GLFW_PRESS&&\
		glfwWindowShouldClose(window) == 0);
	glfwTerminate();
	return 0;
}