#version 330


in vec3 a_Position;	

out vec2 v_Pos;

void main()
{
	gl_Position  = vec4(a_Position,1);

	//v_Color = vec4(0.8,0.4,0.5,1);

	v_Pos = a_Position.xy;
}

