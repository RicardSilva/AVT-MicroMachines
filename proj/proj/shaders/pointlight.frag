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
} DataIn;

out vec4 colorOut;

void main() {

	vec3 lightDir = -light.direction;
	vec3 halfVector = normalize(lightDir + DataIn.eye / 2);
	
	float diffuse = max(0.0, dot(DataIn.normal, lightDir));
	float specular = max(0.0, dot(DataIn.normal, halfVector));
	
	if (diffuse == 0)
		specular = 0.0;
	else
		specular = pow(specular, mat.shininess);

		
	vec3 scatteredLight = mat.ambient.xyz + light.color * diffuse;
	vec3 reflectedLight = light.color * mat.specular.xyz * specular * 0.5;
	
	colorOut = vec4((mat.diffuse.xyz * scatteredLight + reflectedLight).xyz, 1.0);
		
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

