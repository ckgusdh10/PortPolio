#version 330

layout(location=0) out vec4 FragColor;

//in float a;

float pi = 3.141592;
 

uniform float u_time;
uniform vec2 u_centers[2];

in vec2 v_Pos;

//uniform float u_radius;

// uniform float u_time; // sector1

void main()
{
	//if(fract(u_time) < a && fract(u_time) + 0.05> a )
	//	FragColor = vec4(1);
	//else
	//	FragColor = vec4(0);			// sector1
	


	//float l = length(v_Pos);
	//
	//if(l < fract(u_radius))
	//	FragColor = vec4(v_Color,1);
	//else
	//	FragColor = vec4(0);
	//FragColor = vec4(0);
	//
	//for(int i = 0;i< 4;i++)
	//{
	//	if(u_time +1 > u_centers[i].z)
	//	{
	//		float newTime = u_time - u_centers[i].z -1;
	//
	//		float dist = length(vec3(v_Pos,1) - u_centers[i]) * 2 * pi;
	//	
	//		FragColor += vec4(sin(dist* 5 - newTime));
	//	}
	//}

	for(int i =0; i< 4;i++)
	{
		float dist = length(v_Pos - u_centers[i]) * 2 * pi;

			FragColor += vec4(sin (dist * 10- u_time* 10));
	}
}
