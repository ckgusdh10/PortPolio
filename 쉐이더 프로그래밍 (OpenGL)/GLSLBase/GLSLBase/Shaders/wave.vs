#version 330

in vec3 Position;
uniform float u_time;
uniform mat4 u_ProjView;

out float val;

out vec2 texPos;

void main()
{
   vec3 pos= Position;
   //pos.z = sin(((pos.x+0.5)*2)* 3.141592  + u_time) ;
   val = sin(((pos.x+0.5)*2)* 3.141592  + u_time) ;

   pos.y += val* 0.15f;

   val = (val + 1)/2;
    gl_Position = u_ProjView * vec4(pos, 1.0);

   texPos = Position.xy + vec2(0.5,0.5);
}