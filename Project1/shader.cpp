#include"shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexcode;
	std::string fragmentcode;
	std::ifstream vShaderfile;
	std::ifstream fShaderfile;

	vShaderfile.open(vertexPath);
	fShaderfile.open(fragmentPath);

	std::stringstream vShaderStream, fShaderStream;
	vShaderStream << vShaderfile.rdbuf();
	fShaderStream << fShaderfile.rdbuf();
	vShaderfile.close();
	fShaderfile.close();
	vertexcode = vShaderStream.str();
	fragmentcode = fShaderStream.str();

	const char* vShaderCode = vertexcode.c_str();
	const char* fShaderCode = fragmentcode.c_str();

	unsigned int vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}
void Shader::use(){
	glUseProgram(ID);
}
void Shader::setBool(const std::string& name, bool value) {
	unsigned int location = glGetUniformLocation(ID, name.c_str());
	glUniform1i(location, (int)value);
}void Shader::setInt(const std::string& name, int value) {
	unsigned int location = glGetUniformLocation(ID, name.c_str());
	glUniform1i(location, value);
}
void Shader::setFloat(const std::string& name, float value) {
	unsigned int location = glGetUniformLocation(ID, name.c_str());
	glUniform1f(location, value);
}

void Shader::setMatrix(const std::string& name, glm::mat4 trans)
{
	unsigned int transformLoc = glGetUniformLocation(ID, name.c_str());
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
}

void Shader::setVec3(const std::string& name, glm::vec3 myvec3)
{
	unsigned int theVec = glGetUniformLocation(ID, name.c_str());
	glUniform3fv(theVec, 1, &myvec3[0]);
}

