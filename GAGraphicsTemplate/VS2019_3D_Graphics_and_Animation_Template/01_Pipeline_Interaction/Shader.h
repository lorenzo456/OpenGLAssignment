#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

class Shader
{
public:
	Shader(std::string shaderName, GLenum shaderType);
	GLuint ReturnShader();
private:
	std::string name;
	GLuint shaderType;
	std::string ReadShader(std::string name);
	void CheckErrorShader(GLuint shader);
};

