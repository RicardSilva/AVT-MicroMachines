#version 330

uniform mat4 m_pvm;
uniform mat4 m_viewModel;
uniform mat3 m_normal;

in vec3 position;
in vec3 normal; 

out Data {
	vec3 normal;
	vec3 eye;
} DataOut;

void main () {

	vec4 pos = m_viewModel * vec4(position.xyz, 1.0);

	DataOut.normal = normalize(m_normal * normal);
	DataOut.eye = normalize(vec3(-pos));

	gl_Position = m_pvm * vec4(position.xyz, 1.0);	
}