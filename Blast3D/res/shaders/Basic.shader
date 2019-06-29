#shader vertex
#version 330

uniform mat4 u_MVP;

in layout(location= 0) vec3 position;
in layout(location = 1) vec3 in_Color;

out vec3 v_Color;

void main()
{
	gl_Position = u_MVP * vec4(position, 1.0);
	v_Color = in_Color;
}


#shader fragment
#version 330

in vec3 v_Color;
out vec4 fragColor;

void main()
{
	fragColor = vec4(v_Color, 1.0);
}