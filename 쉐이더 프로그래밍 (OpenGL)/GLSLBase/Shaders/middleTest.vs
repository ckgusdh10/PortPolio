#version 330


//in vec4 a_Position;	
//out float a; // sector1

in vec3 a_Position;
//in vec3 a_Color;

float pi =  3.141592;
out vec2 v_Pos;

void main()
{
	// gl_Position  = vec4(a_Position.xyz,1);

	// a = a_Position.a; // sector1


	//vec2 newPos = vec2(-10,-10);
	//
	//
	//float newTime = a_Position.x + u_time -1;
	//
	//newTime = fract(newTime);
	//
	//newPos = vec2(fract(newTime), 0); 
	////newPos = vec2(newTime, sin(newTime * pi * a_Position.y) * a_Position.z);
	//
	//newPos.y += sin(newTime * pi * a_Position.y) * a_Position.z * 0.2;
	//
	//
	//gl_Position = vec4(newPos,0,1);		// sector2

	// gl_Position = vec4(a_Position,1);
	// v_Color = a_Color;
	// v_Pos = a_Position.xy;

	// gl_Position = vec4(a_Position,0,1);
	// 
	// float sinY = sin((a_Position.x - u_time)* pi *5) * 0.5;
	// 
	// gl_Position.y = sinY;
	// mat2 rot = mat2(cos(pi/4),sin(pi/4), -sin(pi/4), cos(pi/4));
	// 
	// vec2 pos = gl_Position.xy;
	// 
	// //pos *= rot;
	// 
	// gl_Position.xy = pos;
	// 
	// v_Color = a_Color;

	gl_Position = vec4(a_Position,1);

	v_Pos = gl_Position.xy;
}

