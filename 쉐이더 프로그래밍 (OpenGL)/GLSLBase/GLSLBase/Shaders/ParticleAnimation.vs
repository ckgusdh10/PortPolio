#version 330

in vec3 Position;
in vec2 TexPos;
in vec4 Velocity;

uniform float uTime;

out vec2 vTexPos;

const vec3 g_Gravity = vec3(0,-0.2, 0);


void main()
{
	//float newTime = uTime - Velocity.w;
	//vec3 newPos = vec3(-1000, -1000,-1000);
	//if(newTime > 0)
	//{
	//	newTime = fract(newTime/3)*3;
	//	newPos = Position.xyz + uTime * Velocity.xyz + 0.5 * g_Gravity.xyz * uTime*uTime;
	//}

	vec3 newPos = Position.xyz + uTime * Velocity.xyz;
	
    gl_Position = vec4(newPos, 1.0);

	vTexPos = TexPos;
}
