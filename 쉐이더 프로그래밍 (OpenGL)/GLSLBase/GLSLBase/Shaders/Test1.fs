#version 330

out vec4 FragColor;

uniform sampler2D u_Texture;

in vec2 v_TexPos;


void main()
{
	//if(v_Grey > 0.5)
	//	FragColor = vec4(1,0,0,1);
	//else
	//	FragColor = vec4(0,0,0,0);
	
	//float newColor = floor(v_Grey * 2);
	//FragColor = vec4(newColor, 0, 0, 1);

	FragColor = texture(u_Texture, v_TexPos);
}
