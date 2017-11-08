#version 330

uniform sampler2D textureMap;
uniform int mode;
uniform vec4 matDiffuse;

in Data {
	vec2 texC;
} DataIn;

out vec4 colorOut;


void main() {

if(mode == 0) {
	vec4 color = texture(textureMap, DataIn.texC);	
	colorOut = vec4(color.xyz, 0.7);
}
else {
	vec4 color = texture(textureMap, DataIn.texC);	
	colorOut = color * matDiffuse;
}
	
	
	
}