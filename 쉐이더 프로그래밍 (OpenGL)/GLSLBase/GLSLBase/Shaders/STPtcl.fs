#version 330
//V0==>(0,0,0,1) v1==>1,0,0,1
//f0==>0,0,0,1 f100==>1,0,0,1  ´ë·«
layout(location=0) out vec4 FragColor;

//in vec4 v_Color;
//uniform float u_Time;
in vec2 v_FragPos; 

uniform sampler2D u_Texture;

void main()
{
	vec2 texPos = gl_PointCoord;
	FragColor= texture(u_Texture,texPos);
	//FragColor = vec4(gl_PointCoord,0,1);
}
