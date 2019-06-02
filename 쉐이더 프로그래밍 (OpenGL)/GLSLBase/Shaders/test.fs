#version 330

layout(location=0) out vec4 FragColor;

in vec2 v_Pos;

uniform float u_time;
uniform vec2 u_Center[4];

float pi = 3.141592;
 
void main()
{
	for(int i = 0 ;i< 4;i++)
	{
		vec2 pos = v_Pos;

		float dist = length(pos  - u_Center[i]) * 2 * pi;

		FragColor += vec4(sin(dist*10 - u_time));
	}
}
