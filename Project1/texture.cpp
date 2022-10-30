#include<glad/glad.h>
#include<GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include<iostream>
const char* vertexShaderSource = "#version 330 core\n"
"layout(location=0) in vec3 aPos;\n"
"layout(location=1) in vec3 aColor;\n"
"layout(location=2) in vec3 aTexCoord;\n"
"out vec3 ourColor;\n"
"out vec2 TexCoord;\n"
"void main(){\n"
"{\n"
"gl_Position=vec4(aPos,1.0);\n "
"ourColor=aColor;\n "
"TexCoord=vec2(aTexCoord.x,aTexCoord.y);\n "
"}\n";
const char* fragShaderSource = "#version 330 core\n"
"in vec3 ourColor;\n"
"in vec2 TexCoord;\n"
"out vec4 FragColor;\n"
"uniform sampler2D texturel;\n"
"void main(){\n"
"{\n"
"FragColor=texture(texturel,TexCoord);\n"
"}\n";


void frame_buffer_size_callback(GLFWwindow* window, int width, int height);
void frame_buffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	return;
}


int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "learngl", NULL, NULL);
	if (window == NULL) {
		std::cout << "出错啦！";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	float vertices[] = {
		//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
	};
	unsigned int indices[] = {
		0,1,3,
		1,2,3
	};
	
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2);




	
	unsigned int texture;
	glGenBuffers(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//设置纹理的环绕方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//设置纹理的过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	//创建shader
	unsigned int vertex, fragment, ID;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexShaderSource, NULL);
	glCompileShader(vertex);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragShaderSource, NULL);
	glCompileShader(fragment);

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	glUseProgram(ID);


	int width, height, nrChannels;
	unsigned char* data = stbi_load("C:\\Users\\11634\\Desktop\\container.jpg", &width, &height, &nrChannels, 0);
	//提供纹理数据
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		std::cout << width << " " << height;
			//自动生成多级渐远纹理
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "failed to load image!";
	}
	stbi_image_free(data);//s释放图像的内存

	
	
	unsigned int textureLoc = glGetUniformLocation(ID, "texturel");
	glUniform1i(textureLoc, 0);


	


	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2, 0.3, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		
		//glBindTexture(GL_TEXTURE_2D, texture);
		
		glBindTexture(GL_TEXTURE_2D, texture);
		glUseProgram(ID);
		//unsigned int textureLoc = glGetUniformLocation(ID, "texturel");
		//glUniform1i(textureLoc, 0);
		glBindVertexArray(VAO);
		//glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
		
		glfwSwapBuffers(window);


		
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	glfwTerminate();

	return 0;
}

