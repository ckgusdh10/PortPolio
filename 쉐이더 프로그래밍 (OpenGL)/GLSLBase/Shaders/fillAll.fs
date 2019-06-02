#version 330

layout(location=0) out vec4 FragColor;

uniform float r;
uniform float g;
uniform float b;
uniform float a;
 
void main()
{
	FragColor = vec4(r,g,b,a);
}
