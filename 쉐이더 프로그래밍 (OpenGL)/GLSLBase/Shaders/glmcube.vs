#version 330

in vec3 a_Position;
in vec3 a_Normal;
in vec4 a_Color;

uniform mat4 u_ProjView;
uniform mat4 u_Model;
uniform mat4 u_Rotation;

uniform float u_time;

out vec4 v_Color;
out vec3 v_Normal;
out vec3 v_Pos;

void main()
{
  // vec3 pos = a_Position;
  // pos.z += sin(u_time+ pos.x * 3.141592 ) * 0.5;
  // gl_Position = u_ProjView * vec4(pos, 1.f);
  // gl_Position.z +=  sin(u_time ) + gl_Position.x;




  gl_Position = u_ProjView * u_Model * vec4(a_Position, 1.f);

  v_Color = a_Color;

  v_Normal = (u_Rotation * vec4(a_Normal, 0.f)).xyz;

  v_Pos = (u_Model * vec4(a_Position,1.f)).xyz;

}