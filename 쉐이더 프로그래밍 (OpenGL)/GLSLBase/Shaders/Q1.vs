#version 330


in vec3 a_Position;	
in float a_Info;

uniform float u_time;
float pi = 3.141592;

void main()
{
	//	 gl_Position  = vec4(sin(u_time)* 0.5,cos(u_time)*0.5, 0,1); �������� 0.5�� ����� ���� �̵�

	// float newX = (fract(u_time) -0.5) * 2;	// -1 ~ 1
	// float newY = sin(newX * 3.0* pi);
	// gl_Position  = vec4(newX, newY, 0,1);	// �ֱⰡ 3�� ���ΰ�� ���� �̵�

	float newX = (fract(u_time) -0.5) * 2;	// -1 ~ 1
	float newY = sin(newX * 2.0* pi) * a_Info;
	gl_Position  = vec4(newX, newY, 0,1);	// �ֱⰡ 2�� ���ΰ�� ����, a_Info��ŭ�� �������� �̵�
}

