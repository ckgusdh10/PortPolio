#version 330

in vec2 vTexPos;

out vec4 FragColor;

uniform sampler2D uTexture;

in vec2 v_TexPos;
in float v_Alpha;

void main()
{
    FragColor = texture(uTexture, vTexPos);
//	FragColor.a = FragColor.a * v_Alpha;
}
