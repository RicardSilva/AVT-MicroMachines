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
	int type;
	vec3 position;
	vec3 direction;
	vec3 color;	
	float intensity;
	
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
}; 

// the set of lights to apply, per invocation of this shader
//const int MaxLights = 10;
//uniform Light Lights[MaxLights];

uniform Light light;
uniform Material mat;

in Data {
	vec4 pos; 
	vec3 normal;
	vec3 eye;
} DataIn;

out vec4 colorOut;


vec4 calcDirLight(Light light, vec3 normal, vec3 viewDir) {

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

vec4 calcPointLight(Light light, vec4 position, vec3 normal, vec3 viewDir) {

	vec3 lightDirection = light.position - vec3(position);
	float lightDistance = length(lightDirection);
	
	// normalize the light direction vector, so
	// that a dot products give cosines
	lightDirection = lightDirection / lightDistance;
	
	// model how much light is available for this fragment
	float attenuation = 1.0 / (light.constantAttenuation + light.linearAttenuation * lightDistance +
	light.quadraticAttenuation * lightDistance * lightDistance);
	
	// the direction of maximum highlight also changes per fragment
	vec3 halfVector = normalize(lightDirection + viewDir);
	
	float diff = max(0.0, dot(normal, lightDirection));
	float spec = max(0.0, dot(normal, halfVector));
	
	if (diff == 0.0)
		spec = 0.0;
	else
		spec = pow(spec, mat.shininess);
		
	vec3 ambient = light.color * mat.ambient;		
	vec3 diffuse = light.color * diff * mat.diffuse * attenuation;
	vec3 specular = light.color * spec * mat.specular * attenuation;
	return vec4((ambient + diffuse + specular).xyz, 1.0);

}

void main() {
	colorOut = calcDirLight(light, DataIn.normal, DataIn.eye);
	//colorOut = vec4(matAmbient.xyz, 1.0f);
	//colorOut = vec4(DataIn.normal.x / 2 + 0.5, DataIn.normal.y / 2 + 0.5, DataIn.normal.z / 2 + 0.5, 1.0f);
	
	
	
}