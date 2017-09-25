#version 330 core

//in vec2 exTexcoord;

out vec4 FragmentColor;

uniform vec3 Color;
//uniform sampler2D Texture;

void main(void){

	FragmentColor = vec4(Color, 1.0f);
	
  //FragmentColor = texture(Texture, exTexcoord);
	//if(FragmentColor.a < 0.5)
    //discard;
}