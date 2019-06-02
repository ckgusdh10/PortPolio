#version 330

in vec2 vTexPos;

out vec4 FragColor;

uniform float uTime;

uniform float uAnimStep;

uniform sampler2D uTexSampler;

void main()
{
    vec2 newTexPos = vec2(vTexPos.x, 
							uAnimStep/6.0 + vTexPos.y/6.0);
    FragColor = texture(uTexSampler, newTexPos);
}
