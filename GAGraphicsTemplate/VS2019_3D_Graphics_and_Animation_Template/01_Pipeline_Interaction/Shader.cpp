#include "Shader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
Shader::Shader(std::string shaderName, GLenum shaderType)
{
	name = shaderName;	
	this->shaderType = shaderType;
}

std::string Shader::ReadShader(std::string name) {
	std::string vs_text;
	std::ifstream vs_file(name);

	std::string vs_line;
	if (vs_file.is_open()) {

		while (getline(vs_file, vs_line)) {
			vs_text += vs_line;
			vs_text += '\n';
		}
		vs_file.close();
	}
	return vs_text;
}

GLuint Shader::ReturnShader()
{
	std::string vs_text = ReadShader(name); const char* vs_source = vs_text.c_str();
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &vs_source, NULL);
	glCompileShader(shader);
	CheckErrorShader(shader);
	return shader;
}

void  Shader::CheckErrorShader(GLuint shader) {
	// Get log lenght
	GLint maxLength;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

	// Init a string for it
	std::vector<GLchar> errorLog(maxLength);

	if (maxLength > 1) {
		// Get the log file
		glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

		std::cout << "--------------Shader compilation error-------------\n";
		std::cout << errorLog.data();
	}
}