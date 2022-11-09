#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"
#include"shader.h"


const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;
void frame_buffer_size_callback(GLFWwindow* window, int width, int height);
void frame_buffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	return;
}
glm::vec3 CarmeraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 CarmeraFront = glm::vec3(0.0f, 0.0f, -1.0f);
float deltaTime = 0.0f;
float lastFrame = 0.0f;
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		CarmeraPosition = CarmeraPosition + cameraSpeed * CarmeraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		CarmeraPosition = CarmeraPosition - cameraSpeed * CarmeraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		CarmeraPosition = CarmeraPosition - glm::normalize(glm::cross(CarmeraFront, up))*cameraSpeed;
	}if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		CarmeraPosition = CarmeraPosition + glm::normalize(glm::cross(CarmeraFront, up))*cameraSpeed;
	}
	return;
}


void change_state(int num) {
	float vertex[] = {
		// 位置              // 颜色
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
	};
	unsigned int indices[] = {
		0,1,2
	};
	unsigned int VAO[2], VBO[2], EBO[2];
	glGenBuffers(2, VBO);
	//glGenBuffers(2., EBO);
	glGenVertexArrays(2, VAO);

	glBindVertexArray(VAO[num]);
	//每一个程序只有一个element array和一个array buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO[num]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), &vertex, GL_STATIC_DRAW);

	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[num]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);*/

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return;
}
float yaw = -90.0f, pitch = 0.0f;
bool first_mouse = 1;
float lastX = 400, lastY = 300;
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (first_mouse) {
		lastX = xpos;
		lastY = ypos;
		first_mouse = 0;
	}
	
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;


	float sensitive = 0.05f;
	xoffset *= sensitive;
	yoffset *= sensitive;
	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0)
		pitch = -89.0;
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	CarmeraFront = glm::normalize(front);


}
float fov = 45.0;
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (fov >= 1.0f && fov <= 55.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 55.0f)
		fov = 55.0f;
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "learngl", NULL, NULL);
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
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	/*float vertices[] = { -0.5,-0.5,0,
		0.5,-0.5,0,
		0,0.5,0 };
	float texCoords[] = {
		0.0 ,0.0,
		1.0 ,0.0,
		0.5 ,1.0
	};*/
//ri和fv是什么单词的缩写？
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//unsigned int vertex_shader;
	//vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertex_shader, 1, &vertextShaderSource, NULL);
	//glCompileShader(vertex_shader);
	//int shader_success;
	//char infoLog[512];
	//glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &shader_success);
	//if (!shader_success) {
	//	glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
	//	std::cout << infoLog << std::endl;
	//}


	//unsigned int frag_shader;
	//frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(frag_shader, 1, &fragShaderSource, NULL);
	//glCompileShader(frag_shader);

	//unsigned int shader_program;
	//shader_program = glCreateProgram();
	//glAttachShader(shader_program, vertex_shader);
	//glAttachShader(shader_program, frag_shader);
	//glLinkProgram(shader_program);

	//unsigned int link_success;
	//char* link_info[512];
	//glGetProgramiv(shader_program, GL_LINK_STATUS,(GLint*)&link_success);
	//if (!link_success) {
	//	glGetProgramInfoLog(shader_program, 512, NULL, (GLchar*)link_info);
	//	std::cout << link_info;
	//}

	//glUseProgram(shader_program);
	//glDeleteShader(vertex_shader);
	//glDeleteShader(frag_shader);


	
	/*unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);*/


	//1.画两个彼此相连的三角形
	
	
	


	//unsigned int VAO, VBO, EBO;
	//glGenBuffers(1, &EBO);
	//glGenBuffers(1, &VBO);
	//glGenVertexArrays(1, &VAO);
	//glBindVertexArray(VAO);
	////这里的target指的是什么？
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	Shader myshader = Shader("vertexShader.vs", "fragmentShader.txt");
	Shader borderShader = Shader("vertexShader.vs", "shaderColor.txt");
	//正方体的数据坐标
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  1.0f, 0.0f,0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 0.0f,0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 0.0f,0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 0.0f,0.0f,
	-0.5f, -0.5f, -0.5f,  1.0f, 0.0f,0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 1.0f,0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 1.0f,0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f, 1.0f,0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f, 1.0f,0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 1.0f,0.0f,

	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,1.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 0.0f,0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 1.0f,0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 1.0f,0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 1.0f,0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f, 0.0f,1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f, 0.0f,1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
	};
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_KEEP, GL_KEEP, GL_REPLACE);
	glDepthFunc(GL_LESS);
	//change_state(0);
	//多个立方体的位置
	glm::vec3 cubePositions[] = {
	  glm::vec3(0.0f,  0.0f,  0.0f),
	  glm::vec3(2.0f,  5.0f, -15.0f),
	  glm::vec3(-1.5f, -2.2f, -2.5f),
	  glm::vec3(-3.8f, -2.0f, -12.3f),
	  glm::vec3(2.4f, -0.4f, -3.5f),
	  glm::vec3(-1.7f,  3.0f, -7.5f),
	  glm::vec3(1.3f, -2.0f, -2.5f),
	  glm::vec3(1.5f,  2.0f, -2.5f),
	  glm::vec3(1.5f,  0.2f, -1.5f),
	  glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	

	while (!glfwWindowShouldClose(window)) {

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0, 1, 0));
		/*trans = glm::translate(trans, glm::vec3(0.6, 0.6, 0));
		trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));*/
		

		float r = 8.0f;
		float x_coor = sin(glfwGetTime()) * r;
		float z_coor = cos(glfwGetTime()) * r;
		
		//进一步的改变view矩阵创建lookat矩阵来让原来的
		glm::mat4 view = glm::mat4(1.0f);
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		view = glm::lookAt(
			//相机位置
			CarmeraPosition,
			//观测点
			CarmeraPosition + CarmeraFront,
			//选定上向量
			up
		);
		/*
		1.先指定位置向量，是坐标的z轴
		2.再指定观测的目标点，然后用相机的位置减去目标点就是方向向量（相反数）
		3.定义上向量，一般是原坐标系的y，然后做叉乘，得到新坐标系的x正方向
		4.方向z叉右得到y
		*/

		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(fov), (float)(8 / 6), 0.1f, 100.0f);


		glClearColor(0.2, 0.3, 0.3, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);

		float currentFrame = glfwGetTime();
		
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);
		myshader.use();
		myshader.setMatrix("model", model);
		myshader.setMatrix("view", view);
		myshader.setMatrix("projection", projection);
		/*glUseProgram(shader_program);*/
		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		/*float timeVal = glfwGetTime();
		float greenVal = sin(timeVal) / 2 + 0.5;
		int vertexLocation = glGetUniformLocation(shader_program, "ourColor");
		glUniform4f(vertexLocation, 0, greenVal, 0, 1);*/
		
		
		//在绘制片段的地方，都会被更新为参考值
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		//启用写入
		glStencilMask(0xFF);
		glBindVertexArray(VAO);
		
		for (int i = 0; i < 10; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0, 0.3, 0.5));
			if (i % 3 == 0) {
				model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0, 0.3, 0.5));
			}
			myshader.setMatrix("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//只有不等于1的地方会通过测试
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		//不更新模板
		glStencilMask(0x00);
		glDisable(GL_DEPTH_TEST);
		//选择shader
		borderShader.use();
		//画边框
		//borderShader.setMatrix("model", model);
		borderShader.setMatrix("view", view);
		borderShader.setMatrix("projection", projection);
		glBindVertexArray(VAO);
		for (int i = 0; i < 10; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0, 0.3, 0.5));
			if (i % 3 == 0) {
				model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0, 0.3, 0.5));
			}
			model = glm::scale(model, glm::vec3(1.1, 1.1, 1.1));
			borderShader.setMatrix("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//恢复两个写入和测试
		glStencilMask(0xFF);
		glStencilFunc(GL_ALWAYS, 0, 0xFF);
		glEnable(GL_DEPTH_TEST);




;		glfwSwapBuffers(window);
		glfwSetScrollCallback(window, scroll_callback);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;

}