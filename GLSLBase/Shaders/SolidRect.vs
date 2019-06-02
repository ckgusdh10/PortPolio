#version 330

in vec3 a_Position;		
out vec4 v_Color;

void main()
{
	gl_Position  = vec4(a_Position,1);

	v_Color = vec4(0,0,0,1);
	// 0 , 1
	// 프래그먼트에서는 이 0 과 1 사이의 값으로 다 보간된다 !
}

