#version 330

layout(location=0) out vec4 FragColor;

in vec4 v_Color;			// 0
uniform sampler2D uTexSampler;

void main()
{

	//FragColor =  vec4(gl_PointCoord, 0, 1);
	FragColor =  texture(uTexSampler, gl_PointCoord);
}
