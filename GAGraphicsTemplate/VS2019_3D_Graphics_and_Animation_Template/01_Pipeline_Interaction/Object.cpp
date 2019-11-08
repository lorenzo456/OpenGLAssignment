#include "Object.h"
#include "Mesh.h"
#include "../../Libraries/stb_image/stb_image.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <glm/glm.hpp>
#include "../../Libraries/glm-0.9.9.6/glm/gtx/transform.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



Object::Object(std::string tex) {
	if (tex != "") {
		texturePath = tex;
		LoadTexture();
		hasTexture = true;
	}

	SetPostion(glm::vec3(0.0f, 0.0f, 5.0f));
	SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
}

void Object::Update(GLuint program, float deltaTime, glm::mat4 &viewMatrix, glm::mat4 &proj_matrix) 
{

	if (hasTexture)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(program, "tex"), 0);
	}

	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);
	modelMatrix = glm::rotate(modelMatrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::scale(modelMatrix, scale);

	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj_matrix"), 1, GL_FALSE, &proj_matrix[0][0]);
	glUniform1f(glGetUniformLocation(program, "deltaTime"), deltaTime);
	//printf("Delta time is: %f ", deltaTime);

	float random = ((float)rand()) / (float)RAND_MAX;
	float range = 5 - 2;
	random = (random * range) + 2;
	glUniform1f(glGetUniformLocation(program, "random"), 0);
	//printf("Random number is: %f", random);



	mesh.Draw();
}

void Object::LoadTexture() 
{
	string name = texturePath;
	glGenTextures(1, &texture);

	int iWidth, iHeight, iChannels;
	unsigned char* iData = stbi_load(name.c_str(), &iWidth, &iHeight, &iChannels, 0);

	glBindTexture(GL_TEXTURE_2D, texture); 

	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, iWidth, iHeight);

	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, iWidth, iHeight, GL_RGBA, GL_UNSIGNED_BYTE, iData);

	/*
	// This only works for 2D Textures...
	// Set the texture wrapping parameters (next lecture)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture filtering parameters (next lecture)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Generate mipmaps (next lecture)
	glGenerateMipmap(GL_TEXTURE_2D);
	*/
}

void Object::Load(string path)
{
	mesh.LoadModel(path);
}

void Object::SetPostion(glm::vec3 newPosition)
{
	position = newPosition;
}

void Object::SetRotation(glm::vec3 newRotation)
{
	rotation = newRotation;
}

void Object::SetScale(glm::vec3 newScale)
{
	scale = newScale;
}
