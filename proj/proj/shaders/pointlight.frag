#version 330
out vec4 colorOut;

struct Materials {
	vec3 diffuse;
	vec3 ambient;
	vec3 specular;
	vec3 emissive;
	float shininess;
	int texCount;
};

uniform Materials mat;

in Data {
	vec3 normal;
	vec3 eye;
	vec3 lightDir;
} DataIn;

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