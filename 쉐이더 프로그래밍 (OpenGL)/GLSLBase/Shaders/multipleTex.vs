#version 330

in vec3 a_Position;	
in vec2 TexPos;

out vec2 vTexPos;

void main()
{
	gl_Position  = vec4(a_Position,1);
	vTexPos = TexPos;
}

