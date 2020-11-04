#version 330

layout(location=0) out vec4 FragColor;

uniform sampler2D uTexSampler;

in vec2 vTexPos;

void main()
{
	//FragColor = vec4(vTexPos, 0, 1);
	FragColor =texture(uTexSampler,  fract(vTexPos*2)) + vec4(0,0,1,1);

}
