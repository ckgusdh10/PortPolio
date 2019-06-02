#version 330

in vec4 v_Color;

uniform vec3 u_LightPos;
uniform vec3 u_CameraPos;

const float c_Ambient = 0.2f;
const float c_Diffuse = 0.7f;
const float c_Specular = 0.7f;

in vec3 v_Normal;
in vec3 v_Pos;

out vec4 FragColor;

void main()
{
   vec3 lightDir = normalize(u_LightPos - v_Pos);
   vec3 viewDir = normalize(u_CameraPos - v_Pos);
   vec3 reflectDir = reflect(-lightDir, v_Normal);

   float ambient = 1.f;
   float diffuse = max(0,dot(lightDir,v_Normal));
   float specular = pow(max(0,dot(viewDir,reflectDir)), 128);
   
   
    FragColor.rgb =
      (   c_Ambient * ambient + 
         c_Diffuse * diffuse +
         c_Specular * specular ) * v_Color.rgb;

   FragColor.a = v_Color.a;
}