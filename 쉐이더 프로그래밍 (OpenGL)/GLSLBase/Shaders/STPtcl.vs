#version 330

//in vec3 a_Position;		// (a_ = attribute 명시 )
							// in -> 입력

in vec3 a_Position;		
//in vec4 a_Color;

out vec4 v_Color;

uniform float u_time;

uniform vec2 u_S;
uniform vec2 u_E;

mat2 rotMat;
vec2 pos;

void main()
{

	float pi = 3.141592;

	vec2 newPos = vec2(-10,-10);

	vec2 k = u_E - u_S;

	mat2 rot = mat2(cos(pi/2),sin(pi/2), -sin(pi/2), cos(pi/2));

	vec2 verti = normalize(rot *k);

	if(u_time + 1 > a_Position.x)
	{
		float newTime = u_time - a_Position.x;

		newTime = fract(newTime);

		float temp = sin(newTime * 3.141592 * a_Position.y) * a_Position.z * 0.2 ;

		newPos = u_S + k * newTime;
		newPos += verti * temp;
	}

	gl_Position  = vec4
	(
		newPos.x ,
		newPos.y ,
		0,
		1
	);

	gl_PointSize = 50;


	v_Color = vec4(1,1,1,1);
	// 0 , 1
	// 프래그먼트에서는 이 0 과 1 사이의 값으로 다 보간된다 !
}

