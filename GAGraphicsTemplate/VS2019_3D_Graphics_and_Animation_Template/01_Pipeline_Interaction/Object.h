#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Mesh.h"	

class Object 
{
public:
	Object(std::string tex = "");
	void SetPostion(glm::vec3 newPosition);
	void SetRotation(glm::vec3 newRotation);
	void SetScale(glm::vec3 newScale);
	void Update(GLuint program, float deltaTime, glm::mat4 &viewMatrix, glm::mat4 &proj_Matrix);
	void Load(string path);
	void LoadTexture();
protected:
private:
	Mesh mesh;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	GLuint	texture;
	bool	hasTexture;
	std::string texturePath;
};