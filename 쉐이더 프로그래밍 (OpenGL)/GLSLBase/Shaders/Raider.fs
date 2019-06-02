#version 330

// f0 ---> {0,0,0,1} -----> f50 {0.5, 0,0,1} ----> f100 ==> {1,0,0,1}
layout(location=0) out vec4 FragColor;

uniform float u_time;
uniform vec2 u_points[4];

in vec2 v_Pos;

void main()
{
    float finalColor = 0;
    float pointColor = 0;

    for(int i = 0; i < 4; ++i)
    {
        vec2 segment = u_points[i].xy - v_Pos;
        float r = 1 - length(segment);
        if( r > 0.95 )
        {
           r = 0.8;
        }
        else
        {
            r = 0;
        }
        pointColor += r;
    }
	
    float temp = length(v_Pos);
    float newTime = fract(u_time); //0~1

    if(newTime + 0.02 > temp && newTime - 0.02 < temp)
    {
        finalColor = 0.4 * pointColor + 0.2;///////////////
    }

    if(finalColor == 0)
        discard;
   
    FragColor = vec4(finalColor, finalColor, finalColor, 1);
}

