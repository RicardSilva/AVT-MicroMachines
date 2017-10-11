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

vec4 CalcDirLight(Light light, vec3 normal, vec3 viewDir) {
	vec3 lightDir = normalize(-light.direction);
	// Diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// Specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), mat.shininess);
	// Combine results
	vec3 ambient = light.color * mat.ambient;
	vec3 diffuse = light.color * diff * mat.diffuse;
	vec3 specular = light.color * spec * mat.specular;
	
	return vec4((ambient + diffuse + specular).xyz, 1.0);
}

vec4 CalcDirLight2(Light light, vec3 normal, vec3 viewDir) {

	vec3 lightDir = normalize(-light.direction);
	float diff = max(0.0, dot(normal, lightDir));
	
	vec3 HalfVector = normalize(lightDir + viewDir);
	float spec = max(0.0, dot(normal, HalfVector));
	
	// surfaces facing away from the light (negative dot products)
	// won’t be lit by the directional light
	if (diff == 0.0)
		spec = 0.0;
	else
		spec = pow(spec, mat.shininess); // sharpen the highlight
		
	vec3 ambient = light.color * mat.ambient;	
	vec3 diffuse = light.color * diff * mat.diffuse;
	vec3 specular = light.color * spec * mat.specular;
	return vec4((ambient + diffuse + specular).xyz, 1.0);
}

void main() {
	colorOut = CalcDirLight(light, DataIn.normal, DataIn.eye);
	//colorOut = vec4(mat.ambient.xyz, 1.0f);
	//colorOut = vec4(DataIn.normal.x / 2 + 0.5, DataIn.normal.y / 2 + 0.5, DataIn.normal.z / 2 + 0.5, 1.0f);
	
	
	
}