#pragma once

#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "Dependencies\glew.h"
#include "glm\gtc\matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"


class Renderer
{
public:
	Renderer(int windowSizeX, int windowSizeY);
	~Renderer();

	bool IsInitialized();
	GLuint Renderer::CreatePngTexture(char * filePath);
	void Test();

	void Lecture2();
	void Lecture3();
	void Lecture4();
	void Lecture4_2();
	void Lecture5();
	void Lecture5_2();
	void Lecture5_3();
	void Lecture5_4();
	void Lecture7();
	void Lecture7_2();
	void Lecture8();

	void drawTex();

	void Texture(float time, int line, float offset);

	void fillAll(float r, float g, float b, float a);

	void Raider(float* points, float time);

	void DrawSTParticle(float sx, float sy, float tx, float ty, float time);


	void FragAnim(float cx, float cy, float t);

	void midlleTest(float time);

	void Test(float*, float);

	void middleTerm();
	void middleTermWithColor(float time);
	void middleTermWave(float time);
	void middleFragAnim(float* centers, float time);
	void middleOperationZ(float time);
	void middleWave(float* centers, float time);

	void multipleTex();

	void oneTextureAnim(float );

	float m_targetPointX, m_targetPointY;

	void Q1();
	void Q2();

	void Wave();
	void ParticleAnimation();
	void Cube();

	void MouseRotation(float rX, float rY);
	void applyRoatation(int x, int y);
public:
	void Initialize(int windowSizeX, int windowSizeY);
	bool ReadFile(char* filename, std::string *target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(char* filenameVS, char* filenameFS);
	void CreateVertexBufferObjects();

	bool m_Initialized = false;

	unsigned int m_WindowSizeX = 0;
	unsigned int m_WindowSizeY = 0;

	GLuint m_VBOfill = 0;

	GLuint m_VBORect = 0;
	GLuint m_SolidRectShader = 0;
	GLuint m_STPtclShader = 0;
	GLuint m_testShader = 0;
	GLuint m_RaiderShader = 0;
	GLuint m_fillAllShader = 0;
	GLuint m_textureShader = 0;
	GLuint m_middleTestShader = 0;

	GLuint m_MultipleTexShader = 0;
	GLuint m_VBOLecture2 = 0;
	GLuint m_VBOLecture3 = 0;
	GLuint m_VBOLecture4 = 0;
	GLuint m_VBOLecture4_fromProf = 0;
	GLuint m_VBOLecture4_2 = 0;

	GLuint m_VBOLecture5 = 0;

	GLuint m_VBOTrianglePos = 0;

	GLuint m_VBOTriangleCol = 0;

	GLuint m_VBOTrianglePosCol_1_1 = 0;

	GLuint m_VBOTrianglePosCol_a_a = 0;

	GLuint m_VBOWave = 0;
	GLuint m_VBOWaveP = 0;

	GLuint m_VBOFragAnim = 0;

	GLuint m_ColorsLecture3 = 0;

	GLuint m_VBORaider = 0;

	GLuint m_VBOTexture = 0;


	GLuint m_TEXCheckerboard = 0;

	GLuint m_VBOMiddleRect = 0;

	GLuint m_VBOptcl = 0;
	GLuint VBO1 = 0;

	GLuint m_VBOmiddleTerm = 0;
	GLuint m_VBOmiddleColor = 0;

	GLuint m_VBOmiddleWave = 0;

	GLuint m_VBOmiddleFragAnim = 0;

	GLuint m_VBOoperationZ = 0;

	GLuint m_VBO_Q1 = 0;
	GLuint m_VBO_Q2 = 0;

	GLuint m_Q1shader = 0;
	GLuint m_Q2shader = 0;
	
	GLuint m_TextureShader = 0;
	GLuint m_VBOTextureBox = 0;
	GLuint m_VBOTextureColor = 0;

	GLuint m_VBO_PosTex = 0;

	GLuint gTextureID1 = 0;
	GLuint gTextureID2 = 0;
	GLuint gTextureID3 = 0;
	GLuint gTextureID4 = 0;
	GLuint gTextureID5 = 0;
	GLuint gTextureID6 = 0;

	GLuint gTextureIDTotal = 0;

	GLuint m_Tex_IU = 0;

	GLuint m_Tex_brick = 0;

	GLuint m_Tex_reroad = 0;

	GLuint m_Tex_Particle = 0;

	GLuint m_texParticle = 0;


	float g_time = 0.0f;
	bool isUp = false;

	GLuint gDummyVertexCount;
	GLuint VBO_DummyMesh;
	GLuint gShaderProgram = 0;
	float gtime= 0.0f;

	//ParticleAnimation
	GLuint gParticleVertexCount = 0;
	GLuint VBO_ParticleMesh = 0;

	GLuint gParticleTextureID = 0;
	GLuint m_ParticleAnimation = 0;
	GLuint gTimeStamp = 0;


	//cube
	// camera position
	glm::vec3 m_v3Camera_Position;
	
	// camera lookat position
	glm::vec3 m_v3Camera_Lookat;

	// camera up vector
	glm::vec3 m_v3Camera_Up;

	glm::mat4 m_m4Model;
	glm::mat4 m_m4OrthoProj;
	glm::mat4 m_m4View;
	glm::mat4 m_m4ProjView;

	glm::vec3 m_v3ModelTranslation;
	glm::vec3 m_v3ModelRotation;
	glm::vec3 m_v3ModelScaling;

	glm::mat4 m_m4ModelTranslation;
	glm::mat4 m_m4ModelRotation;
	glm::mat4 m_m4ModelScaling;

	GLuint m_VBO_Cube = 0;
	GLuint m_Shader_Proj = 0;

	float scaleFactor = 1.0f;
	float xRotFactor = 0.0f;
	float yRotFactor = 0.0f;
	void orthoProject();


	GLuint m_Shaer_Test1;
	GLuint m_VBO_Test1;
	void Test1();
};


