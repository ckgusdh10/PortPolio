#version 330

layout(location=0) out vec4 FragColor;

uniform sampler2D uTextureSlot;            // IU
uniform sampler2D uTextureSlot1;         // reroad

uniform float u_Time;
uniform int u_Line;
uniform float u_Offset;
in vec2 vTexPos;

void main()
{
   float tY =  fract(vTexPos.y * u_Line);

   float tX = fract(vTexPos.x * u_Line + floor(vTexPos.y* u_Line)* u_Offset) ;
   
   
   vec4 t1 = texture(uTextureSlot,  vec2(tX,tY));
   

   FragColor = t1;
}