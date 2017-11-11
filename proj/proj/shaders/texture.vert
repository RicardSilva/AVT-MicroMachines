#version 330

uniform mat4 m_pvm;
uniform mat4 m_viewModel;
uniform int textureMode;

layout (location = 0)in vec4 position;
layout (location = 1)in vec3 normal; 
layout (location = 2)in vec2 texCoord; 

out Data {
	vec2 texC;
	//int mode;
} DataOut;

void main () {

	DataOut.texC = texCoord;
	//DataOut.mode = 1 * textureMode;
	if(textureMode == 2)
		gl_Position = m_viewModel *  position;
	else
		gl_Position = m_pvm * position;	
}