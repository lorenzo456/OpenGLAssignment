#version 430 core

out vec4 color;

in VS_OUT
{
    vec2 tc;
    vec3 normals;
} fs_in;

uniform mat4 model_matrix;
uniform float deltaTime;
layout(binding=0) uniform sampler2D tex;

void main(void){
	//color = vec4((texture(tex, vec2(0.5,0.5)).xyz), 1.0);
	color = vec4(1.0,texture(tex, fs_in.tc).xy, 1.0);
	//color = vec4(fs_in.normals, 1.0);
}
