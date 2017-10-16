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
	bool isActive;
	int type;
	vec4 position;
	vec4 direction;
	vec3 color;	
	float intensity;
	
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
	
	float spotCosCutoff; 
	float spotExponent;
}; 

// the set of lights to apply, per invocation of this shader
const int MaxLights = 9;
uniform Light lights[MaxLights];

uniform Light light;
uniform Material mat;

in Data {
	vec4 pos; 
	vec3 normal;
	vec3 eye;
} DataIn;

out vec4 colorOut;


vec4 calcDirLight(Light light, vec3 normal, vec3 viewDir) {

	vec4 lightDir4 = normalize(-light.direction);
	vec3 lightDir = vec3(lightDir4);
	float diff = max(0.0, dot(normal, lightDir));
	
	vec3 HalfVector = normalize(lightDir + viewDir);
	float spec = max(0.0, dot(normal, HalfVector));
	
	// surfaces facing away from the light (negative dot products)
	// won’t be lit by the directional light
	if (diff == 0.0)
		spec = 0.0;
	else
		spec = pow(spec, mat.shininess); // sharpen the highlight
		
	vec3 diffuse = light.color * diff * mat.diffuse;
	vec3 specular = light.color * spec * mat.specular;
	return vec4((diffuse + specular).xyz, 1.0);
}

vec4 calcPointLight(Light light, vec4 position, vec3 normal, vec3 viewDir) {

	vec4 lightDirection4 = light.position - position;
	vec3 lightDirection = vec3(lightDirection4);
	float lightDistance = length(lightDirection);
	
	// normalize the light direction vector, so
	// that a dot products give cosines
	lightDirection = lightDirection / lightDistance;
	
	// model how much light is available for this fragment
	float attenuation = 1.0 / (light.constantAttenuation 
	+ light.linearAttenuation * lightDistance 
	+ light.quadraticAttenuation * lightDistance * lightDistance);
	
	// the direction of maximum highlight also changes per fragment
	vec3 halfVector = normalize(lightDirection + viewDir);
	
	float diff = max(0.0, dot(normal, lightDirection));
	float spec = max(0.0, dot(normal, halfVector));
	
	if (diff == 0.0)
		spec = 0.0;
	else
		spec = pow(spec, mat.shininess);
				
	vec3 diffuse = light.color * diff * mat.diffuse * attenuation;
	vec3 specular = light.color * spec * mat.specular * attenuation;
	return vec4((diffuse + specular).xyz, 1.0);

}

vec4 calcSpotLight(Light light, vec4 position, vec3 normal, vec3 viewDir) {
	
	vec4 lightDirection4 = light.position - position;
	vec3 lightDirection = vec3(lightDirection4);
	float lightDistance = length(lightDirection);
	lightDirection = lightDirection / lightDistance;
	
	float attenuation = 1.0 / (light.constantAttenuation 
	+ light.linearAttenuation * lightDistance 
	+ light.quadraticAttenuation * lightDistance * lightDistance);
	
	// how close are we to being in the spot?
	float spotCos = dot(lightDirection, (vec3(-light.direction)));
	// attenuate more, based on spot-relative position
	if (spotCos < light.spotCosCutoff)
		attenuation = 0.0;
	else
		attenuation *= pow(spotCos, light.spotExponent);
	
	vec3 halfVector = normalize(lightDirection + viewDir);
	
	float diff = max(0.0, dot(normal, lightDirection));
	float spec = max(0.0, dot(normal, halfVector));
	if (diff == 0.0)
		spec = 0.0;
	else
		spec = pow(spec, mat.shininess);
		
	vec3 diffuse = light.color * diff * mat.diffuse * attenuation;
	vec3 specular = light.color * spec * mat.specular * attenuation;
	
	return vec4((diffuse + specular).xyz, 1.0);

}

void main() {

	colorOut = vec4(0);
	colorOut += vec4(mat.ambient.xyz, 1);
	for (int i = 0; i < MaxLights; i++) {
		Light light = lights[i];
		if(light.isActive) {
			if(light.type == 0)
				//colorOut += vec4(0);
				colorOut += calcDirLight(light, DataIn.normal, DataIn.eye) * light.intensity;
			else if (light.type == 1)
				colorOut += calcPointLight(light, DataIn.pos, DataIn.normal, DataIn.eye) * light.intensity;
				//colorOut += vec4(0);
			else if (light.type == 2)
				colorOut += calcSpotLight(light, DataIn.pos, DataIn.normal, DataIn.eye) * light.intensity;
		}
	}
	
	
	//colorOut = vec4(lights[7].color.xyz, 1.0f);
	//colorOut = vec4(DataIn.pos.x / 2000 + 1, DataIn.pos.y / 2000 + 1, DataIn.pos.z / 2000 + 1, 1);
	
}