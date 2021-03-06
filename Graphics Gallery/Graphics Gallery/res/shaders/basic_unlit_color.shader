#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

uniform mat4 u_MVP;

out vec4 fColor;

void main()
{
	fColor = color;
	gl_Position = u_MVP * vec4(position, 1.0f);
}

#shader fragment
#version 330 core

in vec4 fColor;
layout(location = 0) out vec4 color;

void main()
{
	color = fColor;
}
