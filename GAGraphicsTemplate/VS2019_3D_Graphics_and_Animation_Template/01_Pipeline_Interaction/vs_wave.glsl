#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 tc;
layout (location = 2) in vec3 normals;

out VS_OUT
{
    vec2 tc;
    vec3 normals;
} vs_out;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;
uniform float deltaTime;
uniform float random;

void main(void)
{
float dir = 0;
	if(sin(position.x * deltaTime * 2) < 0)
	{
		dir = 1;
	}
	float num = 0.5*(1+sin(2 * 3.14 * 0.5 * deltaTime));

    //gl_Position = proj_matrix * view_matrix * model_matrix * vec4(position.x,position.y,position.z, 1.0);
	//gl_Position = proj_matrix * view_matrix * model_matrix * vec4(position.x,(position.y + abs(-2)) * deltaTime ,position.z, 1.0);
	//gl_Position = proj_matrix * view_matrix * model_matrix * vec4(position.x,position.y,position.z, 1.0);
    gl_Position = proj_matrix * view_matrix * model_matrix * vec4(position.x,(position.y /*- (position.y)*/) + 0.1 * sin((deltaTime * 5) + 10 * position.x),position.z, 1.0);
	//gl_Position = proj_matrix * view_matrix * model_matrix * vec4(position.x + 0.1 * sin((deltaTime * random) + 10 * position.z),(position.y /* - (position.y)*/) + 0.1 * sin((deltaTime * 5) + 10 * position.x),position.z, 1.0);

    vs_out.tc = tc;
    vs_out.normals = normals;
}
