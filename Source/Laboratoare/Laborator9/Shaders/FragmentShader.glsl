#version 330

in vec3 FragPos;
in vec3 Normal;

uniform vec3 objectColor;

uniform vec3 lightPosition1;
uniform vec3 lightColor1;

uniform vec3 lightPosition2;
uniform vec3 lightColor2;

layout(location = 0) out vec4 out_color;

vec3 phong(vec3 objectColor, vec3 lightPosition, vec3 lightColor) {

	// Ambient lighting
	float ambientStrength = 0.8;
	vec3 ambient = ambientStrength * lightColor;

	// Diffuse lighting
	vec3 norm = normalize(Normal);
	vec3 lightDirection = normalize(lightPosition - FragPos);

	float diff = max(dot(norm, lightDirection), 0.0);
	vec3 diffuse = diff * lightColor;

	// Putting it all together
	vec3 result = (ambient + diffuse) * objectColor;

	return result;
}

void main()
{


	//vec3 col = vec3(0.25, 0.25, 0.75);
	vec3 color1 = phong(objectColor, lightPosition1, lightColor1);
	vec3 color2 = phong(color1, lightPosition2, lightColor2);

	out_color = vec4(color2, 1.0);


	//out_color = vec4(lightColor1, 1.0);

}