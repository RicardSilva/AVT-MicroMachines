#version 330

uniform sampler2D textureMap;
uniform vec4 matDiffuse;
uniform int textureMode;
in Data {
	//int mode;
	vec2 texC;
} DataIn;

out vec4 colorOut;


void main() {

if(textureMode == 0) {
	vec4 color = texture(textureMap, DataIn.texC);	
	colorOut = vec4(color.xyz, 0.7);
}
else if (textureMode == 1) {
	vec4 color = texture(textureMap, DataIn.texC);	
	colorOut = color * matDiffuse;
}
else if (textureMode == 2) {
	vec4 color = texture(textureMap, DataIn.texC);	
	colorOut = color;
}	

	
}