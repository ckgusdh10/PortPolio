#version 330

out vec4 FragColor;
in float val;
uniform sampler2D uTextureSlot;

in vec2 texPos;

void main()
{
    FragColor = vec4(val) * texture(uTextureSlot,texPos);

   //FragColor = vec4(texPos,0,1);
}