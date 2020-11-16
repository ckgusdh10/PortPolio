#version 330


in vec4 Position;
out vec2 v_FragPos;
uniform float u_Time;
uniform float u_Width;
uniform float u_Ratio;
uniform vec2 startPos;
uniform vec2 endPos;

void main()
{
	float getX,getY;
	float temp=u_Time+1;
	vec2 dir=endPos-startPos;
	vec2 rotateVector;


	if(temp>Position.x)
	{
		float newTime=temp-Position.x;
		newTime=fract(newTime/2)*2;
		float angle=3.141592/2;
		mat2 rotMat=mat2(cos(angle),sin(angle),-sin(angle),cos(angle));
		float noise=(sin(newTime*3.141592*Position.z))* (Position.w*(newTime)/2);
		rotateVector=rotMat* normalize(dir)*noise;

		getX=startPos.x+dir.x*( newTime)/2+rotateVector.x;
		getY=startPos.y+dir.y*newTime/2+rotateVector.y;
	}
	else
	{
		getX=10;
		getY=10;
	}

	gl_PointSize = 50;
	gl_Position=vec4(getX,getY,0,1);

	v_FragPos=Position.xy;
}



