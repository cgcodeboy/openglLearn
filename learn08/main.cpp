#include <iostream>

#include <glew.h>

#include <GLFW\glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <SOIL.h>

GLFWwindow *window;

using namespace glm;
using namespace std;

float angl = 0.0f;
void key_callback(GLFWwindow *window,int key,int scancode,int action,int mode)
{
	if(key==GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window,GL_TRUE);		
	}
	if(key == GLFW_KEY_A&&action == GLFW_PRESS)
	{
		angl += 0.01f;
		cout<<"A press"<<endl;
	}
	if(key == GLFW_KEY_D&&action == GLFW_PRESS)
	{
		angl -= 0.01f;
		cout<<"D press"<<endl;
	}
}

int main()
{
	const char *vertexShaderSource= {
		"#version 330 core\n"
		"uniform mat4 MVP;\n"
		"uniform mat4 Model;\n"
		"layout (location = 0) in vec3 position;\n"	
		"layout (location = 1) in vec3 texcoord;\n"
		"out vec3 Texcoord;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = MVP*vec4(position.xyz,1.0);\n"
		"	Texcoord = texcoord;\n"
		"}\n"
	};

	const char *fragmentShaderSource = {
		"#version 330 core\n"
		"in vec3 Texcoord;\n"
		"uniform sampler2D texture1;\n"
		"uniform sampler2D texture2;\n"
		"void main()\n"
		"{\n"
		"	gl_FragColor = mix(texture(texture1,Texcoord.xy),texture(texture2,Texcoord.xy),0.1);\n"
		"}\n"
	};

	//mix(texture(texture1,Texcoord.xy),texture(texture2,Texcoord.xy),0.1)


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
	glfwSetKeyCallback(window,key_callback);

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
		// Positions          // Texture Coords
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	 };

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	GLuint  vao;
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1,&vbo);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertex_data),vertex_data,GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),(GLvoid*)0);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),(GLvoid*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
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

	GLuint texture[2];
	unsigned char *image;
	int width,height;
	glGenTextures(2,texture);
	glBindTexture(GL_TEXTURE_2D,texture[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	image = SOIL_load_image("002.png",&width,&height,0,SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D,0);

	glBindTexture(GL_TEXTURE_2D,texture[1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	image = SOIL_load_image("003.png",&width,&height,0,SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D,0);

	GLuint MVPLocation = glGetUniformLocation(program, "MVP");
	GLuint ModelLocation = glGetUniformLocation(program,"Model");

	glClearColor(0.7f,0.7f,0.7f,1.0f);
	float i = 0.0f;
	do
	{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
		glUseProgram(program);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,texture[0]);
		glUniform1i(glGetUniformLocation(program,"texture1"),0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D,texture[1]);
		glUniform1i(glGetUniformLocation(program,"texture2"),1);
		
		glm::mat4 Projection = glm::perspective(4.0f,(GLfloat)600/480,0.1f,100.0f);
		glm::mat4 View = glm::lookAt(glm::vec3(0.0f,1.0f,1.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,1.0f));
		glm::mat4 Model = glm::mat4(1.0f);
		Model = glm::rotate(Model,i,glm::vec3(1.0f,1.0f,1.0f));
		glm::mat4 MVP = Projection*View*Model;

		glUniformMatrix4fv(MVPLocation,1,GL_FALSE,glm::value_ptr(MVP));
		glUniformMatrix4fv(ModelLocation,1,GL_FALSE,glm::value_ptr(Model));

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES,0,36);
		glBindVertexArray(0);
		glUseProgram(0);

		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);

		glUseProgram(program);

		float scale = 1.1f;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,texture[0]);
		glUniform1i(glGetUniformLocation(program,"texture1"),0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D,texture[1]);
		glUniform1i(glGetUniformLocation(program,"texture2"),1);
		
		/*
		glm::mat4 Projection = glm::perspective(4.0f,(GLfloat)600/480,0.1f,100.0f);
		glm::mat4 View = glm::lookAt(glm::vec3(0.0f,3.0f,3.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,1.0f));
		glm::mat4 Model = glm::mat4(1.0f);
		Model = glm::rotate(Model,i,glm::vec3(1.0f,1.0f,1.0f));
		*/
		Model = glm::scale(Model,glm::vec3(scale,scale,scale));
		MVP = Projection*View*Model;

		glUniformMatrix4fv(MVPLocation,1,GL_FALSE,glm::value_ptr(MVP));
		glUniformMatrix4fv(ModelLocation,1,GL_FALSE,glm::value_ptr(Model));

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES,0,36);
		glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
		i+=angl;
	}
	while(glfwGetKey(window,GLFW_KEY_ESCAPE)!=GLFW_PRESS&&\
		glfwWindowShouldClose(window) == 0);
	glfwTerminate();
	return 0;
}

