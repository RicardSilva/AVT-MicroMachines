#version 330

struct Materials {
	vec3 diffuse;
	vec3 ambient;
	vec3 specular;
	vec3 emissive;
	float shininess;
	int texCount;
};

struct LightProperties {
	bool isEnabled; // true to apply this light in this invocation
	
	bool isLocal; // true for a point light or a spotlight,
				  // false for a directional light
				  
	bool isSpot; // true if the light is a spotlight
	
	vec3 ambient; // light’s contribution to ambient light
	
	vec3 position; // location of light, if is Local is true,
				   // otherwise the direction toward the light
	vec3 color; // color of light
				   
	vec3 halfVector; // direction of highlights for directional light
	vec3 coneDirection; // spotlight attributes
	
	float spotCosCutoff;
	float spotExponent;
	
	float constantAttenuation; // local light attenuation coefficients
	float linearAttenuation;
	float quadraticAttenuation;
}; 

// the set of lights to apply, per invocation of this shader
const int MaxLights = 10;
uniform LightProperties Lights[MaxLights];

uniform Materials mat;

in Data {
	vec3 normal;
	vec3 eye;
	vec3 lightDir;
} DataIn;

out vec4 colorOut;

void main() {

	colorOut = vec4(mat.diffuse.xyz, 1.0f);
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
	
	
	
}