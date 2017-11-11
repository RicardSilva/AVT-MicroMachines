#version 330


layout (location = 0)in vec4 position;
layout (location = 1)in vec3 normal; 
layout (location = 2)in vec2 texCoord; 

uniform mat4 m_pvm;
uniform mat4 m_viewModel;
uniform mat3 m_normal;

out Data {
	vec4 pos;
	vec3 normal;
	vec3 eye;
	vec2 texCoord;
} DataOut;

out float visibility;

const float density = 0.005;
const float gradient = 1.3;
void main () {
	
	vec4 pos = m_viewModel * position;
	DataOut.pos = pos;
	DataOut.normal = normalize(m_normal * normal);
	DataOut.eye = normalize(vec3(-pos));
	DataOut.texCoord = texCoord;
	float distance = length(pos.xyz);
	visibility = exp(-pow((distance*density), gradient));
	visibility = clamp(visibility, 0.0 ,1.0);
	gl_Position = m_pvm * position;	
}