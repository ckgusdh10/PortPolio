#version 330

layout(location=0) out vec4 FragColor;

const float pi = 3.141592;

in vec2 v_Pos;

void main()
{
	// float distance = length(v_Pos);	// 0 ~ 1
	// float grayScale = sin(distance * pi * 4 ); // 0 ~ 4
	// FragColor = vec4(grayScale);						// 파동 모양 만들기
	
	// float distance1 = length(v_Pos - vec2(-1,0));
	// float distance2 = length(v_Pos - vec2(1,0));
	// if(distance1 < 1 ||  distance2 < 1)
	// {
	// 	FragColor = vec4(1);
	// }
	// else
	// 	FragColor = vec4(0);							// 반원 두개 그리기 if문 써서


	float distance1 = length(v_Pos - vec2(-1,0));
	float distance2 = length(v_Pos - vec2(1,0));
	
	float grayScale1 = 1-floor(clamp(distance1,0,1));
	float grayScale2 = 1-floor(clamp(distance2,0,1));
	
	FragColor = vec4(grayScale1 + grayScale2);		// 반원 두개 if안쓰고 그리기 -> 틀림.... OneMinus 안함..

}
