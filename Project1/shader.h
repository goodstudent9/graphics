#pragma once
#include<glad/glad.h>
#include<cstring>
#include<fstream>
#include<sstream>
#include<iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	unsigned int ID;
	Shader(const char* vertexPath, const char* fragmentPath);

	void use();
	void setBool(const std::string &name, bool value);
	void setInt(const std::string& name, int val);
	void setFloat(const std::string& name, float val);
	void setMatrix(const std::string& name, glm::mat4 trans);
	void setVec3(const std::string& name, glm::vec3 myvec3);
};