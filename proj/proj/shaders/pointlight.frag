#version 330

struct Material {
	vec3 diffuse;
	vec3 ambient;
	vec3 specular;
	vec3 emissive;
	float shininess;
	int texCount;
};

struct Light {
	vec3 direction;
	vec3 color;	
}; 

// the set of lights to apply, per invocation of this shader
//const int MaxLights = 10;
//uniform Light Lights[MaxLights];

uniform Light light;
uniform Material mat;

in Data {
	vec3 normal;
	vec3 eye;
	//vec3 lightDir;
} DataIn;

out vec4 colorOut;

void main() {
	
	vec3 halfVector = normalize(light.direction + DataIn.eye);
	
	float diffuse = max(0.0, dot(DataIn.normal, light.direction));
	float specular = max(0.0, dot(DataIn.normal, halfVector));
	
	if (diffuse == 0)
		specular = 0.0;
	else
		specular = pow(specular, mat.shininess);

		
	vec3 scatteredLight = light.color * mat.diffuse.xyz;
	vec3 reflectedLight = light.color * specular;
	
	colorOut = vec4((scatteredLight + reflectedLight).xyz, 1.0);
		
	//colorOut = vec4(mat.diffuse.xyz, 1.0f);
	
	
	
	
}










/*
	vec4 spec = vec4(0.0);

	vec3 n = normalize(DataIn.normal);
	vec3 l = normalize(DataIn.lightDir);
	vec3 e = normalize(DataIn.eye);

	float intensity = max(dot(n,l), 0.0);

	
	if (intensity > 0.0) {

		vec3 h = normalize(l + e);
		float intSpec = max(dot(h,n), 0.0);
		spec = vec4(mat.specular.xyz, 1.0) * pow(intSpec, mat.shininess);
	}
	
	colorOut = max(intensity * vec4(mat.diffuse.xyz, 1.0) + spec, vec4(mat.ambient.xyz, 1.0f));
	*/

