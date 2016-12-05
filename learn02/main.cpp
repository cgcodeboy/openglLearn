#include <iostream>

#include <glew.h>

#include <GLFW\glfw3.h>

#include <glm.hpp>

GLFWwindow *window;

using namespace glm;
using namespace std;

int main()
{
	const char *vertexShaderSource= {
		"#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"		
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(position.xyz,1.0);\n"
		"}\n"
	};

	const char *fragmentShaderSource = {
		"#version 330 core\n"
		"void main()\n"
		"{\n"
		"	gl_FragColor = vec4(1.0,0.0,1.0,1.0);\n"
		"}\n"
	};


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

	window = glfwCreateWindow(600,480,"learn01",NULL,NULL);
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

	static const GLfloat vertex_data[] = { 
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};

	GLuint  vao;
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1,&vbo);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertex_data),vertex_data,GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),(GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	GLint success;
	GLchar infolog[512];
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
	glCompileShader(vertexShader);
	
	glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
	if(!success)
	{
		glGetShaderInfoLog(vertexShader,512,NULL,infolog);
		std::cout<<"VertexShader conpile error:"<<infolog<<std::endl;
	}

	GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
	if(!success)
	{
		glGetShaderInfoLog(fragmentShader,512,NULL,infolog);
		std::cout<<"fragmentShader compile error:"<<infolog<<std::endl;
	}

	GLint program = glCreateProgram();
	glAttachShader(program,vertexShader);
	glAttachShader(program,fragmentShader);
	glLinkProgram(program);
	glGetProgramiv(program,GL_LINK_STATUS,&success);
	if(!success)
	{
		glGetProgramInfoLog(program,512,NULL,infolog);
		std::cout<<"program link error:"<<infolog<<std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glClearColor(0.7f,0.7f,0.7f,1.0f);
	do
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		glBindVertexArray(vao);
		glDrawArrays(GL_POLYGON,0,3);
		glBindVertexArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}while(glfwGetKey(window,GLFW_KEY_ESCAPE)!=GLFW_PRESS&&\
		glfwWindowShouldClose(window) == 0);
	glfwTerminate();
	return 0;
}