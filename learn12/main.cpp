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

	const char *screenVertexShaderSource = {
		"#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"layout (location = 1) in vec2 texcoord;\n"
		"out vec2 Texcoord;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(position.xyz,1.0);\n"
		"	Texcoord = texcoord;\n"
		"}\n"
	};

	const char *screenFragmentShaderSource = {
		"#version 330 core\n"
		"in vec2 Texcoord;\n"
		"uniform sampler2D texture1;\n"
		"void main()\n"
		"{\n"
		"	gl_FragColor = texture(texture1,Texcoord.xy);\n"
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

	static GLfloat quad_data[] = {
		-1.0f,-1.0f,0.0f,	0.0f,0.0f,
		1.0f,-1.0f,0.0f,	1.0f,0.0f,
		1.0f,1.0f,0.0f,	1.0f,1.0f,
		1.0f,1.0f,0.0f,	1.0f,1.0f,
		-1.0f,1.0f,0.0f,	0.0f,1.0f
		-1.0f,-1.0f,0.0f,	0.0f,0.0f,
	};

	glEnable(GL_DEPTH_TEST);

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

	GLuint quadVao;
	glGenVertexArrays(1,&quadVao);
	glBindVertexArray(quadVao);

	GLuint quadVbo;
	glGenBuffers(1,&quadVbo);
	glBindBuffer(GL_ARRAY_BUFFER,quadVbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertex_data),vertex_data,GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),(GLvoid*)0);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),(GLvoid*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	// frame buffer
	GLuint fbo;
	glGenFramebuffers(1,&fbo);
	glBindFramebuffer(GL_FRAMEBUFFER,fbo);

	GLuint textureColorBuffer;
	glGenTextures(1,&textureColorBuffer);
	glBindTexture(GL_TEXTURE_2D,textureColorBuffer);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,600,480,0,GL_RGB,GL_UNSIGNED_BYTE,NULL);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D,0);
	glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,textureColorBuffer,0);

	GLuint rbo;
	glGenRenderbuffers(1,&rbo);
	glBindRenderbuffer(GL_RENDERBUFFER,rbo);
	glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH24_STENCIL8,600,480);
	glBindRenderbuffer(GL_RENDERBUFFER,0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER,rbo);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		cout<<"framebuffer error"<<endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER,0);

	GLint success;
	GLchar infolog[512];
	//Α’·½Με program
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

	//quad program
	GLuint quadVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(quadVertexShader,1,&screenVertexShaderSource,NULL);
	glCompileShader(quadVertexShader);
	
	glGetShaderiv(quadVertexShader,GL_COMPILE_STATUS,&success);
	if(!success)
	{
		glGetShaderInfoLog(quadVertexShader,512,NULL,infolog);
		std::cout<<"VertexShader conpile error:"<<infolog<<std::endl;
	}

	GLint quadFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(quadFragmentShader,1,&screenFragmentShaderSource,NULL);
	glCompileShader(quadFragmentShader);
	glGetShaderiv(quadFragmentShader,GL_COMPILE_STATUS,&success);
	if(!success)
	{
		glGetShaderInfoLog(quadFragmentShader,512,NULL,infolog);
		std::cout<<"fragmentShader compile error:"<<infolog<<std::endl;
	}

	GLint quadProgram = glCreateProgram();
	glAttachShader(quadProgram,quadVertexShader);
	glAttachShader(quadProgram,quadFragmentShader);
	glLinkProgram(quadProgram);
	glGetProgramiv(quadProgram,GL_LINK_STATUS,&success);
	if(!success)
	{
		glGetProgramInfoLog(quadProgram,512,NULL,infolog);
		std::cout<<"program link error:"<<infolog<<std::endl;
	}

	glDeleteShader(quadVertexShader);
	glDeleteShader(quadFragmentShader);

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
	
	float i = 0.0f;
	do
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glClearColor(0.7f,0.7f,0.7f,1.0f);
		glEnable(GL_DEPTH_TEST);
		glUseProgram(program);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,texture[0]);
		glUniform1i(glGetUniformLocation(program,"texture1"),0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D,texture[1]);
		glUniform1i(glGetUniformLocation(program,"texture2"),1);
		
		glm::mat4 Projection = glm::perspective(45.0f,(GLfloat)600/480,0.1f,100.0f);
		glm::mat4 View = glm::lookAt(glm::vec3(0.0f,2.0f,0.01f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,1.0f));
		glm::mat4 Model = glm::mat4(1.0f);
		Model = glm::rotate(Model,i,glm::vec3(1.0f,1.0f,1.0f));
		glm::mat4 MVP = Projection*View*Model;

		glUniformMatrix4fv(MVPLocation,1,GL_FALSE,glm::value_ptr(MVP));
		glUniformMatrix4fv(ModelLocation,1,GL_FALSE,glm::value_ptr(Model));

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES,0,36);
		glBindVertexArray(0);

		glBindFramebuffer(GL_FRAMEBUFFER,0);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.1f,0.1f,0.7f,1.0f);
		glDisable(GL_DEPTH_TEST);
		glUseProgram( quadProgram);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,textureColorBuffer);
		glUniform1i(glGetUniformLocation(quadProgram,"texture1"),0);
		glBindVertexArray(quadVao);
		glDrawArrays(GL_POLYGON,0,6);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D,0);
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

