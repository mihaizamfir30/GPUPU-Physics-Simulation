#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec3 FragPos;
out vec3 Normal;

void main()
{
	Normal = v_normal;
	FragPos = vec3(Model * vec4(v_position, 1.0));
	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
