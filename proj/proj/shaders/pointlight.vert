#version 330

uniform mat4 m_pvm;
uniform mat4 m_viewModel;
uniform mat3 m_normal;

in vec4 position;
in vec2 texCoord; 
in vec3 normal; 

out Data {
	vec4 pos;
	vec3 normal;
	vec3 eye;
	vec2 texCoord;
} DataOut;

void main () {

	vec4 pos = m_viewModel * position;
	DataOut.pos = pos;
	DataOut.normal = normalize(m_normal * normal);
	DataOut.eye = normalize(vec3(-pos));
	DataOut.texCoord = texCoord;

	gl_Position = m_pvm * position;	
}