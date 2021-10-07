// A simple fragment shader
#version 410

in vec4 fColor;
in vec3 fNormal;
in vec4 fPosition;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float specularPower;

uniform vec3 lightDirection;
uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform float lightSpecularPower;

uniform vec4 cameraPosition;

out vec4 Fragcolor;

void main() 
{
	
	vec3 surfaceNormal = normalize(fNormal);
	vec3 lightNormal = normalize(lightDirection);

	//vec4 lightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);


	// Color = ambientColor + diffuseColor + specularColor
	// Calculate ambient color
	vec4 ambientColor = vec4(Ka, 1.0f) * lightAmbient;

	// Calculate diffuse color
	float lambertTerm = max(0, min(1, dot(-lightNormal, surfaceNormal)));
	vec4 diffuseColor = vec4(Kd, 1.0f) * lightDiffuse * lambertTerm;

	// Calculate the specular color
	vec3 surfaceToView = normalize(cameraPosition.xyz - fPosition.xyz);
	vec3 reflectionNormal = reflect(lightNormal, surfaceNormal);
	float specularTerm = dot(surfaceToView, reflectionNormal);
	specularTerm = max(0.0f, specularTerm);
	specularTerm = pow(specularTerm, specularPower);
	vec4 specularColor = vec4(Ks, 1) * lightSpecular * specularTerm;
		
	Fragcolor = ambientColor + diffuseColor + specularColor;
}