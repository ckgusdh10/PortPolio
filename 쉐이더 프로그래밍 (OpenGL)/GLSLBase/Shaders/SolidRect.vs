#version 330

in vec3 a_Position;		
out vec4 v_Color;

void main()
{
	gl_Position  = vec4(a_Position,1);

	v_Color = vec4(0,0,0,1);
	// 0 , 1
	// �����׸�Ʈ������ �� 0 �� 1 ������ ������ �� �����ȴ� !
}

