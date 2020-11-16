/*
Copyright 2018 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"

Renderer* g_Renderer = NULL;

float g_time = 0;
float mouseX = 0;
float mouseY = 0;
float g_prevX;
float g_prevY;
int g_LBState = GLUT_UP;
float mouseOldPosX = 0;
float mouseOldPosY = 0;
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	// Renderer Test
	//g_Renderer->fillAll(1, 0, 0, 1);
	
	g_time += 0.01;
		
	float centers[] = { -0.5,-0.5,
						0.5,0.5,
						-0.5,0.5,
						0.5,-0.5
						};

	//g_Renderer->Cube();										// 큐브 (마우스로 회전 가능)

	g_Renderer->DrawSTParticle(-1.0, 0, 1.0, 0.0, g_time);	// 물방울 파티클 이펙트
	
	//g_Renderer->FragAnim(0, 0,g_time);						// 파동 이펙트
	//g_Renderer->Test(centers, g_time);						// 물결 이펙트
	//g_Renderer->Raider(centers, g_time);						// 레이더 이펙트
	
	//g_Renderer->oneTextureAnim(g_time);						// 텍스쳐 이펙트

	//g_Renderer->Test1();										// 텍스쳐 
	//g_Renderer->Texture(g_time, 3, 0.5);						// 텍스쳐 타일
	//g_Renderer->Wave();										// 텍스쳐 웨이브

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	/*mouseX = (float)(x - 250) / 250.0f;
	mouseY = -(float)(y - 250) / 250.0f;
	std::cout << x << std::endl;
	std::cout << y << std::endl;
	g_time = 1.0;*/


	// state : GLUT_DOWN, GLUT_UP
	// button : GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouseOldPosX = x;
		mouseOldPosY = y;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		mouseX = x;
		mouseY = y;

		int xgap = mouseX - mouseOldPosX;
		int ygap = mouseY - mouseOldPosY;

		g_Renderer->applyRoatation(xgap, ygap);
	}
	RenderScene();
}

void MouseMove(int x, int y)
{
	RenderScene();
}



void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("GLSL KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	//glutMouseFunc(MouseMove);
	glutSpecialFunc(SpecialKeyInput);


	
	glutMainLoop();

	delete g_Renderer;

	return 0;
}

