#include "stdafx.h"
#include "Renderer.h"

Renderer::Renderer(int windowSizeX, int windowSizeY)
{
	Initialize(windowSizeX, windowSizeY);
}


Renderer::~Renderer()
{
}

unsigned char * loadBMPRaw(const char * imagepath, unsigned int& outWidth, unsigned int& outHeight)
{
	printf("Reading image %s\n", imagepath);
	outWidth = -1;
	outHeight = -1;
	// Data read from the header of the BMP file
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = NULL;
	fopen_s(&file ,imagepath, "rb");

	if (!file)
	{
		printf("Image could not be opened\n");
		return NULL;
	}

	if (fread(header, 1, 54, file) != 54)
	{
		printf("Not a correct BMP file\n");
		return NULL;
	}

	if (header[0] != 'B' || header[1] != 'M')
	{
		printf("Not a correct BMP file\n");
		return NULL;
	}

	if (*(int*)&(header[0x1E]) != 0)
	{
		printf("Not a correct BMP file\n");
		return NULL;
	}

	if (*(int*)&(header[0x1C]) != 24)
	{
		printf("Not a correct BMP file\n");
		return NULL;
	}

	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	outWidth = *(int*)&(header[0x12]);
	outHeight = *(int*)&(header[0x16]);

	if (imageSize == 0)
		imageSize = outWidth * outHeight * 3;

	if (dataPos == 0)
		dataPos = 54;

	data = new unsigned char[imageSize];

	fread(data, 1, imageSize, file);

	fclose(file);

	return data;
}

void Renderer::Initialize(int windowSizeX, int windowSizeY)
{
	m_targetPointX = 0;
	m_targetPointY = 0;

	//Set window size
	m_WindowSizeX = windowSizeX;
	m_WindowSizeY = windowSizeY;

	//Load shaders
	m_SolidRectShader = CompileShaders("./Shaders/SolidRect.vs", "./Shaders/SolidRect.fs");
	m_STPtclShader = CompileShaders("./Shaders/STPtcl.vs", "./Shaders/STPtcl.fs");
	m_testShader = CompileShaders("./Shaders/test.vs", "./Shaders/test.fs");
	m_RaiderShader = CompileShaders("./Shaders/Raider.vs", "./Shaders/Raider.fs");
	m_fillAllShader = CompileShaders("./Shaders/fillAll.vs", "./Shaders/fillAll.fs");
	m_textureShader = CompileShaders("./Shaders/texture.vs", "./Shaders/texture.fs");
	m_middleTestShader = CompileShaders("./Shaders/middleTest.vs", "./Shaders/middleTest.fs");
	m_Q1shader = CompileShaders("./Shaders/Q1.vs", "./Shaders/Q1.fs");
	m_Q2shader = CompileShaders("./Shaders/Q2.vs", "./Shaders/Q2.fs");

	m_TextureShader = CompileShaders("./Shaders/drawTexture.vs", "./Shaders/drawTexture.fs");
	m_MultipleTexShader = CompileShaders("./Shaders/multipleTex.vs", "./Shaders/multipleTex.fs");
	gShaderProgram = CompileShaders("./Shaders/wave.vs", "./Shaders/wave.fs");
	m_ParticleAnimation = CompileShaders("./Shaders/ParticleAnimation.vs", "./Shaders/ParticleAnimation.fs");
	m_Shader_Proj = CompileShaders("./Shaders/glmcube.vs", "./Shaders/glmcube.fs");
	m_Shaer_Test1 = CompileShaders("./Shaders/Test1.vs", "./Shaders/Test1.fs");
	//Create VBOs
	CreateVertexBufferObjects();


	//Initialize camera settings
	m_v3Camera_Position = glm::vec3(0.f, 0.f, 5.f);
	m_v3Camera_Lookat = glm::vec3(0.f, 0.f, 0.f);
	// 바라보는 위치
	m_v3Camera_Up = glm::vec3(0.f, 1.f, 0.f);

	m_m4View = glm::lookAt(m_v3Camera_Position, m_v3Camera_Lookat, m_v3Camera_Up);

	//Initialize projection matrix
	m_m4OrthoProj = glm::perspectiveRH(45.f, (float)m_WindowSizeX / (float)windowSizeY, 0.f, 10.f);


	//Initialize projection-view matrix
	m_m4ProjView = m_m4OrthoProj * m_m4View;

	//Initialize transforms
	m_v3ModelTranslation = glm::vec3(0.f, 0.f, 0.f);
	m_v3ModelRotation = glm::vec3(0.f, 0.f, 0.f);
	m_v3ModelScaling = glm::vec3(1.f, 1.f, 1.f);

	m_m4ModelTranslation = glm::translate(glm::mat4(1.f), m_v3ModelTranslation);
	m_m4ModelRotation = glm::eulerAngleXYZ(m_v3ModelRotation.x, m_v3ModelRotation.y, m_v3ModelRotation.z);
	m_m4ModelScaling = glm::scale(glm::mat4(1.f), m_v3ModelScaling);

	m_m4Model = m_m4ModelTranslation * m_m4ModelRotation * m_m4ModelScaling;

	m_Tex_Particle = CreatePngTexture("particle4.png");

	if (m_SolidRectShader > 0 && m_VBORect > 0)
	{
		m_Initialized = true;
	}
}

bool Renderer::IsInitialized()
{
	return m_Initialized;
}

GLuint Renderer::CreatePngTexture(char * filePath)

{



	GLuint temp;

	glGenTextures(1, &temp);



	//Load Pngs

	// Load file and decode image.

	std::vector<unsigned char> image;

	unsigned width, height;

	unsigned error = lodepng::decode(image, width, height, filePath);



	glBindTexture(GL_TEXTURE_2D, temp);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);



	return temp;

}

void Renderer::CreateVertexBufferObjects()
{
	float rect[]
		=
	{
		-1.0, 1.0, 0.f, 
		-1.0, -1.0, 0.f, 
		1.0, 1.0, 0.f, //Triangle1
		-1.0, -1.0, 0.f,
		1.0, 1.0, 0.f,
		1.0, -1.0, 0.f, //Triangle2
	};

	glGenBuffers(1, &m_VBORect);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);

	/////////////////////////////////////////////////////////////////////////////
	float vertices2[]
		=
	{ 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f, };			// vs in -> vec3

	glGenBuffers(1, &m_VBOLecture2);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	float vertices3[]
		=
	{ 0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f };		// vs in -> vec4

	glGenBuffers(1, &m_VBOLecture3);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);

	float colors3[]
		=
	{
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f
	};

	glGenBuffers(1, &m_ColorsLecture3);
	glBindBuffer(GL_ARRAY_BUFFER, m_ColorsLecture3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors3), colors3, GL_STATIC_DRAW);

	float vertices4[]
		=
	{ 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f, 0.0f };		// vs in -> vec4

	glGenBuffers(1, &m_VBOLecture4);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices4), vertices4, GL_STATIC_DRAW);

	float vertices4_fromProf[]
		=
	{ -0.5, 0.0, 0.0, 0.0,
		0.5, 0.0, 0.0, 1.0 };		// vs in -> vec4
						// w값을 ver의 output으로 사용할 것임
	glGenBuffers(1, &m_VBOLecture4_fromProf);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture4_fromProf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices4_fromProf), vertices4_fromProf, GL_STATIC_DRAW);

	float vertices5[]
		=
	{
		-0.7, 0.3, 0.0, 0.0,
		0.5, -0.2, 0.0, 0.2,
		0.4, 0.9, 0.0, 0.4,
		-0.2, -0.5, 0.0, 0.6,
		0.8, 0.1, 0.0, 0.8,
		-0.7, 0.3, 0.0, 1.0,

	};		// vs in -> vec4
									// w값을 ver의 output으로 사용할 것임
	glGenBuffers(1, &m_VBOLecture5);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture5);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices5), vertices5, GL_STATIC_DRAW);


	float Position[9]
		=
	{
		0.0, 1.0, 0.0,
		-1.0, -1.0, 0.0,
		1.0, -1.0, 0.0 };

	glGenBuffers(1, &m_VBOTrianglePos);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTrianglePos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Position), Position, GL_STATIC_DRAW);

	float Color[12]
		=
	{
		1.0, 1.0, 1.0, 1.0,
		1.0, 0.0,0.0, 1.0,
		0.0, 0.0, 1.0, 1.0 };


	glGenBuffers(1, &m_VBOTriangleCol);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTriangleCol);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Color), Color, GL_STATIC_DRAW);

	float PositionColor[24] =
	{
		0.0, 1.0, 0.0, 1.0,					// pos
		1.0, 1.0, 1.0, 1.0,					// col
		-1.0, -1.0, 0.0, 1.0,				// pos
		1.0, 0.0, 0.0, 1.0,					// col
		1.0, -1.0, 0.0, 1.0,				// pos
		0.0, 0.0, 1.0, 1.0 };				// col

	// 

	glGenBuffers(1, &m_VBOTrianglePosCol_1_1);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTrianglePosCol_1_1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(PositionColor), PositionColor, GL_STATIC_DRAW);


	float PositionColor2[21]
		=
	{
		0.0, 1.0, 0.0,
		-1.0, -1.0, 0.0,
		1.0, -1.0, 0.0,
		1.0, 1.0, 1.0, 1.0,
		1.0, 0.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 1.0 };

	glGenBuffers(1, &m_VBOTrianglePosCol_a_a);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTrianglePosCol_a_a);
	glBufferData(GL_ARRAY_BUFFER, sizeof(PositionColor2), PositionColor2, GL_STATIC_DRAW);

	int pointCount = 500;
	float* wavePoints = new float[pointCount * 3];
	for (int i = 0;i < pointCount;i++)
	{
		//wavePoints[i * 3] = (((float)i / (float)pointCount) - 0.5f) * 2.0f;
		wavePoints[i * 3] = (((float)i / (float)(pointCount)) - 0.5f) * 2.0f;	// start time

		wavePoints[(i * 3) + 1] = (float)rand() / (float)RAND_MAX;				// period
		wavePoints[(i * 3) + 2] = (float)rand() / (float)RAND_MAX;				// width

		if (((float)rand() / (float)RAND_MAX) > 0.5)
			wavePoints[i * 3 + 2] *= -1.f;
	}


	glGenBuffers(1, &m_Tex_Particle);
	glBindBuffer(GL_ARRAY_BUFFER, m_Tex_Particle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(pointCount * 3), wavePoints, GL_STATIC_DRAW);


	float wavaPoint[3]
		=
	{
		-1.0, 0.0 ,0.0
	};

	glGenBuffers(1, &m_VBOWaveP);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOWaveP);
	glBufferData(GL_ARRAY_BUFFER, sizeof(wavaPoint), wavaPoint, GL_STATIC_DRAW);



	float fragAnim[]
		=
	{
		-1.0, 1.0, 0.f,
		-1.0, -1.0, 0.f,
		1.0, 1.0, 0.f,			//Triangle1

		1.0, 1.0, 0.f,
		-1.0, -1.0, 0.f,
		1.0, -1.0, 0.f		//Triangle2
	};
	glGenBuffers(1, &m_VBOFragAnim);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOFragAnim);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fragAnim), fragAnim, GL_STATIC_DRAW);


	float raiderRect[]
		=
	{
		-1.0, 1.0, 0.f,
		-1.0, -1.0, 0.f,
		1.0, 1.0, 0.f, //Triangle1

		1.0, 1.0, 0.f,
		-1.0, -1.0, 0.f,
		1.0, -1.0, 0.f, //Triangle2
	};
	glGenBuffers(1, &m_VBORaider);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORaider);
	glBufferData(GL_ARRAY_BUFFER, sizeof(raiderRect), raiderRect, GL_STATIC_DRAW);

	float fillRect[]
		=
	{
		-1.0, 1.0, 0.f,
		-1.0, -1.0, 0.f,
		1.0, 1.0, 0.f, //Triangle1

		1.0, 1.0, 0.f,
		-1.0, -1.0, 0.f,
		1.0, -1.0, 0.f, //Triangle2
	};
	glGenBuffers(1, &m_VBOfill);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOfill);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fillRect), fillRect, GL_STATIC_DRAW);

	float texCoord[]
		=
	{
		-0.5, 0.5, 0.f,		0.0f, 1.0f,			// x, y, z, s, t
		-0.5, -0.5, 0.f,	0.0f, 0.0f,
		0.5, 0.5, 0.f,		1.0f, 1.0f,			//Triangle1

		-0.5, -0.5, 0.f,	0.0f, 0.0f,
		0.5, -0.5, 0.f,		1.0f, 0.0f, 			//Triangle2
		0.5, 0.5, 0.f,		1.0f, 1.0f

	};
	glGenBuffers(1, &m_VBOTexture);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTexture);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_STATIC_DRAW);
	/////////////////////////////////////////////////////////////////////////////

	static const GLulong checkerboard[] =
	{
		0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
		0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
		0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
		0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
		0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
		0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
		0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
		0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF
	};

	glGenTextures(1, &m_TEXCheckerboard);
	glBindTexture(GL_TEXTURE_2D, m_TEXCheckerboard);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkerboard);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	float testVertex[]
		=
	{
		//-1.0f, 1.0f,0.0f,
		//-1.0f, -1.0f, 0.0f,
		//1.0f, 1.0f, 0.0f,

		//-1.0f, -1.0f, 0.0f,
		//1.0f, -1.0f, 0.0f,
		//1.0f, 1.0f, 0.0f		// rect

		0.0f, 0.7f, 0.0f, 0.0f,
		0.3f, -0.7f, 0.0f, 0.2f,
		-0.7f, 0.0f,0.0f, 0.4f,
		0.7f, 0.0f, 0.0f, 0.6f,
		-0.3f, -0.7f, 0.0f, 0.8f,
		0.0f, 0.7f, 0.0f, 1.0f,

	};
	glGenBuffers(1, &m_VBOMiddleRect);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOMiddleRect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(testVertex), testVertex, GL_STATIC_DRAW);


	int size = 500;
	float* testPtcl = new float[size * 3];

	for (int i = 0;i < 500;i++)
	{
		testPtcl[i * 3] = (((float)i / (float)(size)) - 0.5f) * 2.0f;
		testPtcl[i * 3 + 1] = (float)rand() / (float)RAND_MAX;
		testPtcl[i * 3 + 2] = (float)rand() / (float)RAND_MAX;

		if (((float)rand() / (float)RAND_MAX) > 0.5)
			testPtcl[i * 3 + 2] *= -1.f;
	}

	glGenBuffers(1, &m_VBOptcl);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOptcl);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(size * 3), testPtcl, GL_STATIC_DRAW);


	float middleTerm[]
		=
	{
		-1.0, 1.0, 0.0,
		-1.0, -1.0, 0.0,
		1.0,  1.0, 0.0,

		1.0, 1.0, 0.0,
		1.0, -1.0, 0.0,
		-1.0, -1.0, 0.0
	};

	glGenBuffers(1, &m_VBOmiddleTerm);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOmiddleTerm);
	glBufferData(GL_ARRAY_BUFFER, sizeof(middleTerm), middleTerm, GL_STATIC_DRAW);




	float middleColor[]
		=
	{
		1.0,0.0,0.0,
		0.0,1.0,0.0,
		0.0,0.0,1.0,

		1.0,0.0,0.0,
		0.0,1.0,0.0,
		0.0,0.0,1.0,
	};

	glGenBuffers(1, &m_VBOmiddleColor);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOmiddleColor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(middleColor), middleColor, GL_STATIC_DRAW);

	int middleSize = 500;
	float* middlePoints = new float[middleSize * 3];

	for (int i = 0;i < middleSize;i++)
	{
		middlePoints[i * 3] = ((float)(i) / (float)(middleSize)-0.5f) * 2.0f;
		middlePoints[i * 3 + 1] = 0;
		middlePoints[i * 3 + 2] = 0;

	}


	/*float sinVertices[]
		=
	{
		-1.0,0.0,			0.0, 0.0, 0.0,
		-0.8,0.0,			0.0, 0.2, 0.2,
		-0.6,0.0,			0.0, 0.4, 0.4,
		-0.4,0.0,			0.0, 0.6, 0.6,
		-0.2,0.0,			0.0, 0.8, 0.8,

		0.0,0.0,			0.0, 1.0, 1.0,

		0.2,0.0,			0.2, 1.0, 0.0,
		0.4,0.0,			0.4, 1.0, 0.0,
		0.6,0.0,			0.6, 1.0, 0.0,
		0.8,0.0,			0.8, 1.0, 0.0,
		1.0,0.0,			1.0, 1.0, 0.0
	};*/

	glGenBuffers(1, &m_VBOmiddleWave);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOmiddleWave);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (middleSize*3), middlePoints, GL_STATIC_DRAW);

	float operationVertices[]
		=
	{
		-1.0f,0.0f,-1.0f,
		1.0f,0.0f,1.0f
	};

	glGenBuffers(1, &m_VBOoperationZ);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOoperationZ);
	glBufferData(GL_ARRAY_BUFFER, sizeof(operationVertices), operationVertices, GL_STATIC_DRAW);

	float q1[]
		=
	{
		0.0,0.0,0.0,	1.0,
		0.0,0.0,0.0,	0.5
	};
	glGenBuffers(1, &m_VBO_Q1);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_Q1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(q1), q1, GL_STATIC_DRAW);

	float q2[]
		=
	{
		-1.0, 1.0, 0.f,
		-1.0, -1.0, 0.f,
		1.0, 1.0, 0.f, //Triangle1


		-1.0, -1.0, 0.f,
		1.0, 1.0, 0.f,
		1.0, -1.0, 0.f//Triangle2
	};
	glGenBuffers(1, &m_VBO_Q2);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_Q2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(q2), q2, GL_STATIC_DRAW);



	float vertPosTex[30] =
	{
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f, 
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f, 
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f
	};
	glGenBuffers(1, &m_VBOTextureBox);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTextureBox);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertPosTex), vertPosTex, GL_STATIC_DRAW);

	GLulong textureSmile[]
		=
	{
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};

	glGenTextures(1, &m_VBOTextureColor);
	glBindTexture(GL_TEXTURE_2D, m_VBOTextureColor);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureSmile);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	
	glGenBuffers(1, &m_VBO_PosTex);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_PosTex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertPosTex), vertPosTex, GL_STATIC_DRAW);

	

	glGenTextures(1, &gTextureID1);
	glBindTexture(GL_TEXTURE_2D, gTextureID1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureSmile);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	GLulong textureSmile1[]
		=
	{
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};
	glGenTextures(1, &gTextureID2);
	glBindTexture(GL_TEXTURE_2D, gTextureID2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureSmile1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	GLulong textureSmile2[]
		=
	{
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};
	glGenTextures(1, &gTextureID3);
	glBindTexture(GL_TEXTURE_2D, gTextureID3);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureSmile2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	GLulong textureSmile3[]
		=
	{
		0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};
	glGenTextures(1, &gTextureID4);
	glBindTexture(GL_TEXTURE_2D, gTextureID4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureSmile3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	GLulong textureSmile4[]
		=
	{
		0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};
	glGenTextures(1, &gTextureID5);
	glBindTexture(GL_TEXTURE_2D, gTextureID5);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureSmile4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	GLulong textureSmile5[]
		=
	{
		0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};
	glGenTextures(1, &gTextureID6);
	glBindTexture(GL_TEXTURE_2D, gTextureID6);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureSmile5);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	GLulong textureSmileTotal[]
		=
	{
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,

		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,

		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,

		0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,

		0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,

		0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};
	glGenTextures(1, &gTextureIDTotal);
	glBindTexture(GL_TEXTURE_2D, gTextureIDTotal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 48, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureSmileTotal);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);



	unsigned int x, y;
	unsigned char * temp = loadBMPRaw("./textures/IU.bmp",x, y);

	glGenTextures(1, &m_Tex_IU);
	glBindTexture(GL_TEXTURE_2D, m_Tex_IU);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_BGR, GL_UNSIGNED_BYTE,temp);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	unsigned int x1, y1;
	unsigned char * temp1 = loadBMPRaw("./textures/reroad.bmp", x1, y1);

	glGenTextures(1, &m_Tex_reroad);
	glBindTexture(GL_TEXTURE_2D, m_Tex_reroad);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x1, y1, 0, GL_BGR, GL_UNSIGNED_BYTE, temp1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	float basePosX = -0.5f;
	float basePosY = -0.5f;
	float targetPosX = 0.5f;
	float targetPosY = 0.5f;

	int pointCountX = 32;
	int pointCountY = 32;

	float width = targetPosX - basePosX;
	float height = targetPosY - basePosY;

	float* point = new float[pointCountX*pointCountY * 2];
	float* vertices = new float[(pointCountX - 1)*(pointCountY - 1) * 2 * 3 * 3];
	gDummyVertexCount = (pointCountX - 1)*(pointCountY - 1) * 2 * 3;

	//Prepare points
	for (int x = 0; x < pointCountX; x++)
	{
		for (int y = 0; y < pointCountY; y++)
		{
			point[(y*pointCountX + x) * 2 + 0] = basePosX + width * (x / (float)(pointCountX - 1));
			point[(y*pointCountX + x) * 2 + 1] = basePosY + height * (y / (float)(pointCountY - 1));
		}
	}

	//Make triangles
	int vertIndex = 0;
	for (int x = 0; x < pointCountX - 1; x++)
	{
		for (int y = 0; y < pointCountY - 1; y++)
		{
			//Triangle part 1
			vertices[vertIndex] = point[(y*pointCountX + x) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[(y*pointCountX + x) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + (x + 1)) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + (x + 1)) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + x) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + x) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;

			//Triangle part 2
			vertices[vertIndex] = point[(y*pointCountX + x) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[(y*pointCountX + x) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[(y*pointCountX + (x + 1)) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[(y*pointCountX + (x + 1)) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + (x + 1)) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + (x + 1)) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
		}
	}

	glGenBuffers(1, &VBO_DummyMesh);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_DummyMesh);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(pointCountX - 1)*(pointCountY - 1) * 2 * 3 * 3, vertices, GL_STATIC_DRAW);

	//ParticleAnimation
	int particleCount = 500;
	float particleSize = 0.05f;
	float particleInitPosX = 0.0f;
	float particleInitPosY = 0.25f;

	float* particleVertices = new float[particleCount * 2 * 3 * (3 + 2 + 4)];
	int particleFloatCount = particleCount * 2 * 3 * (3 + 2 + 4);
	gParticleVertexCount = particleCount * 2 * 3;

	int particleVertIndex = 0;

	for (int i = 0; i < particleCount; i++)
	{
		float randomValueX = 0.f;
		float randomValueY = 0.f;
		float randomValueZ = 0.f;
		float randomStartTime = 0.f;
		float velocityScale = 0.5f;

		randomValueX = (rand() / (float)RAND_MAX - 0.5)*velocityScale;
		randomValueY = (rand() / (float)RAND_MAX - 0.5)*velocityScale;
		randomValueZ = 0.f;
		randomStartTime = (rand() / (float)RAND_MAX)*20.f;

		particleVertices[particleVertIndex] = -particleSize / 2.f + particleInitPosX;
		particleVertIndex++;
		particleVertices[particleVertIndex] = -particleSize / 2.f + particleInitPosY;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 0.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 0.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 0.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueX;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueY;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueZ;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomStartTime;
		particleVertIndex++;

		particleVertices[particleVertIndex] = particleSize / 2.f + particleInitPosX;
		particleVertIndex++;
		particleVertices[particleVertIndex] = -particleSize / 2.f + particleInitPosY;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 0.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 1.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 0.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueX;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueY;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueZ;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomStartTime;
		particleVertIndex++;

		particleVertices[particleVertIndex] = particleSize / 2.f + particleInitPosX;
		particleVertIndex++;
		particleVertices[particleVertIndex] = particleSize / 2.f + particleInitPosY;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 0.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 1.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 1.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueX;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueY;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueZ;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomStartTime;
		particleVertIndex++;

		particleVertices[particleVertIndex] = -particleSize / 2.f + particleInitPosX;
		particleVertIndex++;
		particleVertices[particleVertIndex] = -particleSize / 2.f + particleInitPosY;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 0.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 0.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 0.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueX;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueY;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueZ;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomStartTime;
		particleVertIndex++;

		particleVertices[particleVertIndex] = particleSize / 2.f + particleInitPosX;
		particleVertIndex++;
		particleVertices[particleVertIndex] = particleSize / 2.f + particleInitPosY;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 0.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 1.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 1.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueX;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueY;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueZ;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomStartTime;
		particleVertIndex++;

		particleVertices[particleVertIndex] = -particleSize / 2.f + particleInitPosX;
		particleVertIndex++;
		particleVertices[particleVertIndex] = particleSize / 2.f + particleInitPosY;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 0.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 0.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 1.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueX;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueY;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueZ;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomStartTime;
		particleVertIndex++;
	}

	glGenBuffers(1, &VBO_ParticleMesh);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_ParticleMesh);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*particleFloatCount, particleVertices, GL_STATIC_DRAW);

	GLulong textureParticle[]
		=
	{
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000,
		0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000,
		0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	};
	glGenTextures(1, &gParticleTextureID);
	glBindTexture(GL_TEXTURE_2D, gParticleTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 5, 5, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureParticle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	// cube
	{
		float temp = 0.5f;

		float cube[] = {
			-temp, -temp, temp, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f, //x, y, z, nx, ny, nz, r, g, b, a
			temp, temp, temp, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f,
			-temp, temp, temp, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f,
			-temp, -temp, temp, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f,
			temp, -temp, temp, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f,
			temp, temp, temp, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f, // first face : R

			temp, -temp, temp, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, //x, y, z, nx, ny, nz, r, g, b, a
			temp, temp, -temp, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f,
			temp, temp, temp, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f,
			temp, -temp, temp, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, //x, y, z, nx, ny, nz, r, g, b, a
			temp, -temp, -temp, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f,
			temp, temp, -temp, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, //second face : G

			-temp, temp, temp, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 1.f, //x, y, z, nx, ny, nz, r, g, b, a
			temp, temp, -temp, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 1.f,
			-temp, temp, -temp, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 1.f,
			-temp, temp, temp, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 1.f, //x, y, z, nx, ny, nz, r, g, b, a
			temp, temp, temp, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 1.f,
			temp, temp, -temp, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 1.f, //third face : B

			-temp, -temp, -temp, 0.f, 0.f, -1.f, 1.f, 1.f, 0.f, 1.f, //x, y, z, nx, ny, nz, r, g, b, a
			-temp, temp, -temp, 0.f, 0.f, -1.f, 1.f, 1.f, 0.f, 1.f,
			temp, temp, -temp, 0.f, 0.f, -1.f, 1.f, 1.f, 0.f, 1.f,
			-temp, -temp, -temp, 0.f, 0.f, -1.f, 1.f, 1.f, 0.f, 1.f, //x, y, z, nx, ny, nz, r, g, b, a
			temp, temp, -temp, 0.f, 0.f, -1.f, 1.f, 1.f, 0.f, 1.f,
			temp, -temp, -temp, 0.f, 0.f, -1.f, 1.f, 1.f, 0.f, 1.f, //fourth face : R+G (yellow)

			-temp, -temp, temp, -1.f, 0.f, 0.f, 1.f, 0.f, 1.f, 1.f, //x, y, z, nx, ny, nz, r, g, b, a 
			-temp, temp, temp, -1.f, 0.f, 0.f, 1.f, 0.f, 1.f, 1.f,
			-temp, temp, -temp, -1.f, 0.f, 0.f, 1.f, 0.f, 1.f, 1.f,
			-temp, -temp, temp, -1.f, 0.f, 0.f, 1.f, 0.f, 1.f, 1.f, //x, y, z, nx, ny, nz, r, g, b, a 
			-temp, temp, -temp, -1.f, 0.f, 0.f, 1.f, 0.f, 1.f, 1.f,
			-temp, -temp, -temp, -1.f, 0.f, 0.f, 1.f, 0.f, 1.f, 1.f, // fifth face : R+B (purple)

			-temp, -temp, temp, 0.f, -1.f, 0.f, 0.f, 1.f, 1.f, 1.f, //x, y, z, nx, ny, nz, r, g, b, a 
			temp, -temp, -temp, 0.f, -1.f, 0.f, 0.f, 1.f, 1.f, 1.f,
			temp, -temp, temp, 0.f, -1.f, 0.f, 0.f, 1.f, 1.f, 1.f,
			-temp, -temp, temp, 0.f, -1.f, 0.f, 0.f, 1.f, 1.f, 1.f, //x, y, z, nx, ny, nz, r, g, b, a 
			-temp, -temp, -temp, 0.f, -1.f, 0.f, 0.f, 1.f, 1.f, 1.f,
			temp, -temp, -temp, 0.f, -1.f, 0.f, 0.f, 1.f, 1.f, 1.f, //sixth face : G+B (Cyan)
		};

		glGenBuffers(1, &m_VBO_Cube);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO_Cube);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
	}
	
	{
		float vertices[24] =
		{
			-0.5f, 0.5f, 0.0f, 0.0f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f,
			0.5f, 0.5f, 0.0f, 1.0f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f, -0.5f, 0.0f, 1.0f
		};

		float vert_G[24] =
		{
			-0.5f, 0.5f, 0.0f, 0.0f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f,
			0.5f, 0.5f, 0.0f, 1.0f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f, -0.5f, 0.0f, 1.0f
		};
		float vertPosTex[30] =
		{
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
		};


		glGenBuffers(1, &m_VBO_Test1);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO_Test1);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertPosTex), vertPosTex, GL_STATIC_DRAW);

	}

}



void Renderer::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	//쉐이더 오브젝트 생성
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	//쉐이더 코드를 쉐이더 오브젝트에 할당
	glShaderSource(ShaderObj, 1, p, Lengths);

	//할당된 쉐이더 코드를 컴파일
	glCompileShader(ShaderObj);

	GLint success;
	// ShaderObj 가 성공적으로 컴파일 되었는지 확인
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];

		//OpenGL 의 shader log 데이터를 가져옴
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		printf("%s \n", pShaderText);
	}

	// ShaderProgram 에 attach!!
	glAttachShader(ShaderProgram, ShaderObj);
}

bool Renderer::ReadFile(char* filename, std::string *target)
{
	std::ifstream file(filename);
	if (file.fail())
	{
		std::cout << filename << " file loading failed.. \n";
		file.close();
		return false;
	}
	std::string line;
	while (getline(file, line)) {
		target->append(line.c_str());
		target->append("\n");
	}
	return true;
}

GLuint Renderer::CompileShaders(char* filenameVS, char* filenameFS)
{
	GLuint ShaderProgram = glCreateProgram(); //빈 쉐이더 프로그램 생성

	if (ShaderProgram == 0) { //쉐이더 프로그램이 만들어졌는지 확인
		fprintf(stderr, "Error creating shader program\n");		// 오래된 컴이나 gpu가 없던가 하면 opgl 지원 X
	}

	std::string vs, fs;

	//shader.vs 가 vs 안으로 로딩됨
	if (!ReadFile(filenameVS, &vs)) {
		printf("Error compiling vertex shader\n");
		return -1;
	};

	//shader.fs 가 fs 안으로 로딩됨
	if (!ReadFile(filenameFS, &fs)) {
		printf("Error compiling fragment shader\n");
		return -1;
	};

	// ShaderProgram 에 vs.c_str() 버텍스 쉐이더를 컴파일한 결과를 attach함
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	// ShaderProgram 에 fs.c_str() 프레그먼트 쉐이더를 컴파일한 결과를 attach함
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	//Attach 완료된 shaderProgram 을 링킹함
	glLinkProgram(ShaderProgram);

	//링크가 성공했는지 확인
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);

	if (Success == 0) {
		// shader program 로그를 받아옴
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error linking shader program\n" << ErrorLog;
		return -1;
	}

	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error validating shader program\n" << ErrorLog;
		return -1;
	}

	glUseProgram(ShaderProgram);
	std::cout << filenameVS << ", " << filenameFS << " Shader compiling is done.\n";

	return ShaderProgram;
}

void Renderer::Test()
{
	float newX, newY;

	glUseProgram(m_SolidRectShader);

	int attribPosition = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(attribPosition);
}


///////////////////////////////////////////////////////////////////////////

void Renderer::Lecture2()
{
	glUseProgram(m_SolidRectShader);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

}

void Renderer::Lecture3()
{
	glUseProgram(m_SolidRectShader);
	/*
		GLint id0 = glGetAttribLocation(m_SolidRectShader, "a_Position");
		GLint id1 = glGetAttribLocation(m_SolidRectShader, "a_Color");
	*/
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture3);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_ColorsLecture3);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	GLint uid = glGetUniformLocation(m_SolidRectShader, "u_Scale");

	if (!isUp)
	{
		g_time += 0.0001f;
		if (g_time >= 1.0f)
			isUp = !isUp;
	}
	else
	{
		g_time -= 0.0001f;
		if (g_time <= 0.0f)
			isUp = !isUp;
	}

	glUniform1f(uid, g_time);

	glDrawArrays(GL_TRIANGLES, 0, 3);

}

void Renderer::Lecture4()
{
	glUseProgram(m_SolidRectShader);
	/*
	GLint id0 = glGetAttribLocation(m_SolidRectShader, "a_Position");
	GLint id1 = glGetAttribLocation(m_SolidRectShader, "a_Color");
	*/
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture4_fromProf);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	/*
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, m_ColorsLecture3);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);*/

	GLint uid = glGetUniformLocation(m_SolidRectShader, "moveX");


	glUniform1f(uid, g_time);

	glDrawArrays(GL_LINES, 0, 2);

}

void Renderer::Lecture4_2()
{
	glUseProgram(m_SolidRectShader);
	/*
	GLint id0 = glGetAttribLocation(m_SolidRectShader, "a_Position");
	GLint id1 = glGetAttribLocation(m_SolidRectShader, "a_Color");
	*/
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	GLint uid = glGetUniformLocation(m_SolidRectShader, "moveX");

	g_time += 0.0005;

	glUniform1f(uid, g_time);

	glDrawArrays(GL_TRIANGLES, 0, 6);

}

void Renderer::Lecture5()		// line animation
{
	glUseProgram(m_SolidRectShader);
	/*
	GLint id0 = glGetAttribLocation(m_SolidRectShader, "a_Position");
	GLint id1 = glGetAttribLocation(m_SolidRectShader, "a_Color");
	*/
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture5);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//GLint uid = glGetUniformLocation(m_SolidRectShader, "moveX");

	//scaleFactor += 0.0005;

	//glUniform1f(uid, scaleFactor);

	GLint uid = glGetUniformLocation(m_SolidRectShader, "moveX");

	g_time += 0.0005;

	glUniform1f(uid, g_time);

	glDrawArrays(GL_LINE_LOOP, 0, 6);

}

void Renderer::Lecture5_2()
{
	glUseProgram(m_SolidRectShader);

	GLuint attribPos = glGetAttribLocation(m_SolidRectShader, "a_Position");
	GLuint attribCol = glGetAttribLocation(m_SolidRectShader, "a_Color");

	glEnableVertexAttribArray(attribPos);
	glEnableVertexAttribArray(attribCol);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTrianglePos);
	glVertexAttribPointer(attribPos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTriangleCol);
	glVertexAttribPointer(attribCol, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::Lecture5_3()
{
	glUseProgram(m_SolidRectShader);

	GLuint attribPos = glGetAttribLocation(m_SolidRectShader, "a_Position");
	GLuint attribCol = glGetAttribLocation(m_SolidRectShader, "a_Color");

	glEnableVertexAttribArray(attribPos);
	glEnableVertexAttribArray(attribCol);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTrianglePosCol_1_1);
	glVertexAttribPointer(attribPos, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glVertexAttribPointer(attribCol, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(4 * sizeof(float)));
	// 간격				// 시작점
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::Lecture5_4()
{
	glUseProgram(m_SolidRectShader);

	GLuint attribPos = glGetAttribLocation(m_SolidRectShader, "a_Position");
	GLuint attribCol = glGetAttribLocation(m_SolidRectShader, "a_Color");

	glEnableVertexAttribArray(attribPos);
	glEnableVertexAttribArray(attribCol);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTrianglePosCol_a_a);
	glVertexAttribPointer(attribPos, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(attribCol, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(9 * sizeof(float)));
	// 간격				// 시작점
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::Lecture7()
{
	glUseProgram(m_SolidRectShader);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOWave);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	GLint uid = glGetUniformLocation(m_SolidRectShader, "u_time");

	g_time += 0.0005;
	//if (scaleFactor > 1.0f)
	//	scaleFactor = -1.0f;
	glUniform1f(uid, g_time);

	glPointSize(2);
	glDrawArrays(GL_POINTS, 0, 500);
}

void Renderer::Lecture7_2()
{
	glUseProgram(m_SolidRectShader);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOWaveP);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	GLint uid = glGetUniformLocation(m_SolidRectShader, "u_time");

	g_time += 0.0005;
	//if (scaleFactor > 1.0f)
	//	scaleFactor = -1.f;

	glUniform1f(uid, g_time);

	glPointSize(10);
	glDrawArrays(GL_POINTS, 0, 3);
}


void Renderer::Lecture8()
{
	glUseProgram(m_STPtclShader);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOWave);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	GLint uid = glGetUniformLocation(m_STPtclShader, "u_time");
	GLint xpos = glGetUniformLocation(m_STPtclShader, "x_Pos");
	GLint ypos = glGetUniformLocation(m_STPtclShader, "y_Pos");

	g_time += 0.0005;
	//if (scaleFactor > 1.0f)
	//	scaleFactor = -1.0f;
	glUniform1f(uid, g_time);
	glUniform1f(xpos, m_targetPointX);
	glUniform1f(ypos, m_targetPointY);

	glPointSize(2);
	glDrawArrays(GL_POINTS, 0, 500);
}


void Renderer::DrawSTParticle(float sx, float sy, float tx, float ty, float time)
{
	glUseProgram(m_STPtclShader);
	glEnable(GL_BLEND);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, m_Tex_Particle);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	GLint utime = glGetUniformLocation(m_STPtclShader, "u_time");
	GLint us = glGetUniformLocation(m_STPtclShader, "u_S");
	GLint ue = glGetUniformLocation(m_STPtclShader, "u_E");


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Tex_Particle);

	//if (scaleFactor > 1.0f)
	//	scaleFactor = -1.0f;
	glUniform1f(utime, time);
	glUniform2f(us, sx, sy);
	glUniform2f(ue, tx, ty);

	glPointSize(2);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_POINT_SPRITE);
	glDrawArrays(GL_POINTS, 0, 500);
}

void Renderer::FragAnim(float cx, float cy, float t)
{
	glUseProgram(m_testShader);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOFragAnim);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	GLint time = glGetUniformLocation(m_testShader, "u_time");
	GLint uc = glGetUniformLocation(m_testShader, "u_center");

	glUniform1f(time, t);
	glUniform2f(uc, cx, cy);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::Test(float* centers, float time)
{
	glUseProgram(m_testShader);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOFragAnim);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	GLint utime = glGetUniformLocation(m_testShader, "u_time");
	glUniform1f(utime, time);

	GLint uCenters = glGetUniformLocation(m_testShader, "u_Center");
	glUniform2fv(uCenters, 4, centers);

	glDrawArrays(GL_TRIANGLES, 0, 6);

}


void Renderer::fillAll(float r, float g, float b, float a)
{
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(m_fillAllShader);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOfill);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	GLint ur = glGetUniformLocation(m_fillAllShader, "r");
	GLint ug = glGetUniformLocation(m_fillAllShader, "g");
	GLint ub = glGetUniformLocation(m_fillAllShader, "b");
	GLint ua = glGetUniformLocation(m_fillAllShader, "a");

	glUniform1f(ur, r);
	glUniform1f(ug, g);
	glUniform1f(ub, b);
	glUniform1f(ua, a);


	glDrawArrays(GL_TRIANGLES, 0, 6);

	//glDisable(GL_BLEND);
}


void Renderer::Raider(float* points, float time)
{
	glUseProgram(m_RaiderShader);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOFragAnim);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	GLint utime = glGetUniformLocation(m_RaiderShader, "u_time");
	glUniform1f(utime, time);

	GLint uCenters = glGetUniformLocation(m_RaiderShader, "u_points");
	glUniform2fv(uCenters, 4, points);


	glDrawArrays(GL_TRIANGLES, 0, 6);
}


void Renderer::drawTex()
{

	glUseProgram(m_textureShader);

	GLuint uSampler = glGetUniformLocation(m_textureShader, "uTexSampler");
	glUniform1i(uSampler, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TEXCheckerboard);

	GLuint attribPos = glGetAttribLocation(m_textureShader, "a_Position");
	GLuint attribTex = glGetAttribLocation(m_textureShader, "TexPos");

	glEnableVertexAttribArray(attribPos);
	glEnableVertexAttribArray(attribTex);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTexture);
	glVertexAttribPointer(attribPos, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glVertexAttribPointer(attribTex, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

	// 0	1	2	3	4	
	// x	y	z	s	t

	// x1	y1	z1	s1	t1

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(attribPos);
	glDisableVertexAttribArray(attribTex);


}


void Renderer::midlleTest(float time)
{
	//glUseProgram(m_middleTestShader);

	//glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, m_VBOMiddleRect);

	//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//GLuint utime = glGetUniformLocation(m_middleTestShader, "u_time");

	//glUniform1f(utime, time);

	//glDrawArrays(GL_LINE_LOOP, 0, 6);


	glUseProgram(m_middleTestShader);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOptcl);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	GLuint utime = glGetUniformLocation(m_middleTestShader, "u_time");

	glUniform1f(utime, time);

	glDrawArrays(GL_POINTS, 0, 500);
}

void Renderer::middleTerm()
{
	glUseProgram(m_middleTestShader);

	glEnableVertexAttribArray(0);

	//GLuint id0 = glGetAttribLocation(m_middleTestShader, "a_Position");
	//glEnableVertexAttribArray(id0);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOmiddleTerm);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(0 * sizeof(float)));

	GLuint utime = glGetUniformLocation(m_VBOmiddleTerm, "u_time");

	glUniform1f(utime, 0.5f);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::middleTermWithColor(float time)
{

	glUseProgram(m_middleTestShader);

	GLuint pos = glGetAttribLocation(m_middleTestShader, "a_Position");
	GLuint col = glGetAttribLocation(m_middleTestShader, "a_Color");

	GLuint r = glGetUniformLocation(m_middleTestShader, "u_radius");


	glEnableVertexAttribArray(pos);
	glEnableVertexAttribArray(col);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOmiddleTerm);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOmiddleColor);
	glVertexAttribPointer(col, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glUniform1f(r, time);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::middleTermWave(float time)
{
	glUseProgram(m_middleTestShader);


	GLuint pos = glGetAttribLocation(m_middleTestShader, "a_Position");
	GLuint col = glGetAttribLocation(m_middleTestShader, "a_Color");

	glEnableVertexAttribArray(pos);
	glEnableVertexAttribArray(col);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOmiddleWave);
	//glVertexAttribPointer(pos, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	//glVertexAttribPointer(col, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(2* sizeof(float)) );

	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	GLuint utime = glGetUniformLocation(m_middleTestShader, "u_time");
	glUniform1f(utime, time);

	glPointSize(2);
	glDrawArrays(GL_POINTS, 0, 500);
}

void Renderer::middleFragAnim(float* centers, float time)
{
	glUseProgram(m_middleTestShader);

	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	GLuint ucenter = glGetUniformLocation(m_middleTestShader, "u_centers");
	GLuint utime = glGetUniformLocation(m_middleTestShader, "u_time");

	glUniform3fv(ucenter, 4, centers);
	glUniform1f(utime, time);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::middleOperationZ(float time)
{
	glUseProgram(m_middleTestShader);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	GLuint utime = glGetUniformLocation(m_middleTestShader, "u_time");
	glUniform1f(utime, time);

	glDrawArrays(GL_LINES, 0, 6);
}

void Renderer::middleWave(float* centers, float time)
{
	glUseProgram(m_middleTestShader);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	GLuint utime = glGetUniformLocation(m_middleTestShader, "u_time");
	glUniform1f(utime, time);

	GLuint ucenter = glGetUniformLocation(m_middleTestShader, "u_centers");
	glUniform2fv(ucenter,2, centers);

	glDrawArrays(GL_TRIANGLES, 0, 6);

}



void Renderer::Q1()
{
	static float gTime = 0.0f;
	GLuint shader = m_Q1shader;

	glUseProgram(shader);

	GLuint aPos = glGetAttribLocation(m_Q1shader, "a_Position");
	GLuint aInfo = glGetAttribLocation(m_Q1shader, "a_Info");

	GLuint utime = glGetUniformLocation(m_Q1shader, "u_time");
	glUniform1f(utime, gTime);

	glEnableVertexAttribArray(aPos);
	glEnableVertexAttribArray(aInfo);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_Q1);
	glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glVertexAttribPointer(aInfo, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (GLvoid*) (sizeof(float)*3));

	glPointSize(10);
	glDrawArrays(GL_POINTS, 0, 2);

	glDisableVertexAttribArray(aPos);
	glDisableVertexAttribArray(aInfo);
	gTime += 0.0001;
}

void Renderer::Q2()
{
	static float gTime = 0.0f;
	GLuint shader = m_Q2shader;

	glUseProgram(shader);

	GLuint aPos = glGetAttribLocation(m_Q2shader, "a_Position");

	glEnableVertexAttribArray(aPos);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_Q2);
	glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glPointSize(10);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(aPos);
	gTime += 0.0001;
}



void Renderer::Texture(float time, int line, float offset)
{
	glUseProgram(m_TextureShader);

	GLuint uSampler = glGetUniformLocation(m_TextureShader, "uTextureSlot");
	glUniform1i(uSampler, 0);
	GLuint uSampler1 = glGetUniformLocation(m_TextureShader, "uTextureSlot1");
	glUniform1i(uSampler1, 1);

	GLuint utime = glGetUniformLocation(m_TextureShader, "u_Time");
	glUniform1f(utime, time);

	GLuint uline = glGetUniformLocation(m_TextureShader, "u_Line");
	glUniform1i(uline, line);

	GLuint uoffset = glGetUniformLocation(m_TextureShader, "u_Offset");
	glUniform1f(uoffset, offset);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Tex_IU);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_Tex_reroad);

	GLuint attribPos = glGetAttribLocation(m_TextureShader, "a_Position");
	GLuint attribTex = glGetAttribLocation(m_TextureShader, "TexPos");

	glEnableVertexAttribArray(attribPos);
	glEnableVertexAttribArray(attribTex);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_PosTex);
	glVertexAttribPointer(attribPos, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glVertexAttribPointer(attribTex, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));


	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::multipleTex()
{
	static int num = 0;
	glUseProgram(m_MultipleTexShader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gTextureID1);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gTextureID2);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, gTextureID3);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, gTextureID4);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, gTextureID5);

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, gTextureID6);

	int uniformTex = glGetUniformLocation(m_MultipleTexShader, "uTexSampler");
	glUniform1i(uniformTex, num);

	int attrribPosition = glGetAttribLocation(m_MultipleTexShader, "a_Position");
	int attrribTexPos = glGetAttribLocation(m_MultipleTexShader, "TexPos");

	glEnableVertexAttribArray(attrribPosition);
	glEnableVertexAttribArray(attrribTexPos);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_PosTex);
	glVertexAttribPointer(attrribPosition, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glVertexAttribPointer(attrribTexPos, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

	glDrawArrays(GL_TRIANGLES, 0, 6);


	num++;
	if (num > 5)
		num = 0;
	//Sleep(1000);
}

void Renderer::oneTextureAnim(float time)
{
	static int num = 0;
	glUseProgram(m_MultipleTexShader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gTextureIDTotal);

	int uniformTex = glGetUniformLocation(m_MultipleTexShader, "uTexSampler");
	glUniform1i(uniformTex, 0);

	int utime = glGetUniformLocation(m_MultipleTexShader, "uTime");
	glUniform1f(utime, 0);

	int uanimstep = glGetUniformLocation(m_MultipleTexShader, "uAnimStep");
	glUniform1f(uanimstep, num);

	int attrribPosition = glGetAttribLocation(m_MultipleTexShader, "a_Position");
	int attrribTexPos = glGetAttribLocation(m_MultipleTexShader, "TexPos");

	glEnableVertexAttribArray(attrribPosition);
	glEnableVertexAttribArray(attrribTexPos);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_PosTex);
	glVertexAttribPointer(attrribPosition, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glVertexAttribPointer(attrribTexPos, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	num++;
	if (num > 5)
		num = 0;
	Sleep(200);
}


void Renderer::Wave()
{
	//glUseProgram(gShaderProgram);

	//GLuint samplerTex = glGetUniformLocation(gShaderProgram, "u_Tex");
	//glUniform1i(samplerTex, 0);
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, m_Tex_IU);

	//GLuint uniformTime = glGetUniformLocation(gShaderProgram, "u_Time");
	//glUniform1f(uniformTime, gtime);
	//gtime += 0.005;
	//
	//int attrribPosition = glGetAttribLocation(gShaderProgram, "Position");

	//glEnableVertexAttribArray(attrribPosition);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO_DummyMesh);
	//glVertexAttribPointer(attrribPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

	///*int attrribPosition = glGetAttribLocation(gShaderProgram, "Position");
	//int attrribTexPos = glGetAttribLocation(gShaderProgram, "TexPos");

	//glEnableVertexAttribArray(attrribPosition);
	//glEnableVertexAttribArray(attrribTexPos);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO_DummyMesh);
	//glVertexAttribPointer(attrribPosition, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	//glVertexAttribPointer(attrribTexPos, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));*/


	//glDrawArrays(GL_LINE_STRIP, 0, gDummyVertexCount);

	glUseProgram(gShaderProgram);


	int attrribPosition = glGetAttribLocation(gShaderProgram, "Position");

	GLuint utime = glGetUniformLocation(gShaderProgram, "u_time");
	glUniform1f(utime, gtime);
	gtime += 0.01;
	GLuint utex = glGetUniformLocation(gShaderProgram, "uTextureSlot");
	glUniform1i(utex, 0);

	GLuint projView = glGetUniformLocation(gShaderProgram, "u_ProjView");

	glUniformMatrix4fv(projView, 1, GL_FALSE, &m_m4ProjView[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Tex_IU);


	glEnableVertexAttribArray(attrribPosition);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_DummyMesh);
	glVertexAttribPointer(attrribPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);



	//glDrawArrays(GL_TRIANGLES, 0, gDummyVertexCount);
	glDrawArrays(GL_LINE_STRIP, 0, gDummyVertexCount);
}

void Renderer::ParticleAnimation()
{
	glUseProgram(m_ParticleAnimation);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int uniformTime = glGetUniformLocation(m_ParticleAnimation, "uTime");
	glUniform1f(uniformTime, gTimeStamp);
	gTimeStamp += 0.001;

	int uniformTexture = glGetUniformLocation(m_ParticleAnimation, "uTexture");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gParticleTextureID);
	glUniform1i(uniformTexture, 0);


	int attrribPosition = glGetAttribLocation(m_ParticleAnimation, "Position");
	int attrribTexPos = glGetAttribLocation(m_ParticleAnimation, "TexPos");
	int attrribVel = glGetAttribLocation(m_ParticleAnimation, "Velocity");

	glEnableVertexAttribArray(attrribPosition);
	glEnableVertexAttribArray(attrribTexPos);
	glEnableVertexAttribArray(attrribVel);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_ParticleMesh);
	glVertexAttribPointer(attrribPosition, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), 0);
	glVertexAttribPointer(attrribTexPos, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	glVertexAttribPointer(attrribVel, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (GLvoid*)(5 * sizeof(float)));

	glDrawArrays(GL_TRIANGLES, 0, gParticleVertexCount);


}

void Renderer::Cube()
{
	GLuint shader = m_Shader_Proj;

	glUseProgram(shader);

	glEnable(GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	GLuint projView = glGetUniformLocation(shader, "u_ProjView");
	GLuint model = glGetUniformLocation(shader, "u_Model");
	GLuint rotation = glGetUniformLocation(shader, "u_Rotation");
	GLuint camera = glGetUniformLocation(shader, "u_CameraPos");
	GLuint light = glGetUniformLocation(shader, "u_LightPos");

	glUniformMatrix4fv(projView, 1, GL_FALSE, &m_m4ProjView[0][0]);
	glUniformMatrix4fv(model, 1, GL_FALSE, &m_m4Model[0][0]);
	glUniformMatrix4fv(rotation, 1, GL_FALSE, &m_m4ModelRotation[0][0]);
	glUniform3f(light, 2, 0, 0);
	glUniform3f(camera, m_v3Camera_Position.x, m_v3Camera_Position.y, m_v3Camera_Position.z);


	int attribPosition = glGetAttribLocation(shader, "a_Position");
	int attribNormal = glGetAttribLocation(shader, "a_Normal");
	int attribColor = glGetAttribLocation(shader, "a_Color");

	glEnableVertexAttribArray(attribPosition);
	glEnableVertexAttribArray(attribNormal);
	glEnableVertexAttribArray(attribColor);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_Cube);

	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 10, 0);
	glVertexAttribPointer(attribNormal, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (GLvoid*)(sizeof(float) * 3));
	glVertexAttribPointer(attribColor, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (GLvoid*)(sizeof(float) * 6));

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisableVertexAttribArray(attribPosition);
	glDisableVertexAttribArray(attribNormal);
	glDisableVertexAttribArray(attribColor);

}

void Renderer::MouseRotation(float rX, float rY)
{
	
	m_v3ModelRotation = glm::vec3(rX, rY, 0.f);
	m_v3ModelScaling = glm::vec3(1.f, 1.f, 1.f);

	m_m4ModelTranslation = glm::translate(glm::mat4(1.f), m_v3ModelTranslation);
	m_m4ModelRotation = glm::eulerAngleXYZ(m_v3ModelRotation.x, m_v3ModelRotation.y, m_v3ModelRotation.z);
	m_m4ModelScaling = glm::scale(glm::mat4(1.f), m_v3ModelScaling);

	m_m4Model = m_m4ModelTranslation * m_m4ModelRotation * m_m4ModelScaling;
}

void Renderer::applyRoatation(int x, int y)
{
	float xRot = (float)x / 500;
	float yRot = (float)y / 500;

	xRotFactor += xRot;
	yRotFactor += yRot;
	m_v3ModelRotation = glm::vec3(yRotFactor, xRotFactor, 0.f);

	m_m4ModelTranslation
		=
		glm::translate(glm::mat4(1.f), m_v3ModelTranslation);

	m_m4ModelRotation
		=
		glm::eulerAngleXYZ(m_v3ModelRotation.x, m_v3ModelRotation.y, m_v3ModelRotation.z);

	m_m4ModelScaling
		=
		glm::scale(glm::mat4(1.f), m_v3ModelScaling);


	m_m4Model
		= m_m4ModelTranslation * m_m4ModelRotation * m_m4ModelScaling;
}

void Renderer::orthoProject()
{
	GLuint shader = m_Shader_Proj;

	glUseProgram(shader);

	glEnable(GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//glm::mat4 rot  = glm::rotate(m_m4ProgView, g_time,m_v3Camera_Up);

	g_time += 0.001f;

	GLuint projView = glGetUniformLocation(shader, "u_ProjView");
	GLuint uRot = glGetUniformLocation(shader, "u_Rotation");

	GLuint uModel = glGetUniformLocation(shader, "u_Model");

	GLuint utime = glGetUniformLocation(shader, "u_time");

	GLuint uCamera = glGetUniformLocation(shader, "u_CameraPos");
	GLuint uLight = glGetUniformLocation(shader, "u_LightPos");


	glUniformMatrix4fv(projView, 1, GL_FALSE, &m_m4ProjView[0][0]);
	glUniformMatrix4fv(uModel, 1, GL_FALSE, &m_m4Model[0][0]);
	glUniformMatrix4fv(uRot, 1, GL_FALSE, &m_m4ModelRotation[0][0]);
	glUniform3f(uLight, 2, 1, 0);
	glUniform3f(uCamera, m_v3Camera_Position.x,
		m_v3Camera_Position.y,
		m_v3Camera_Position.z);

	glUniform1f(utime, g_time);
	int attribPosition = glGetAttribLocation(shader, "a_Position");
	int attribNormal = glGetAttribLocation(shader, "a_Normal");
	int attribColor = glGetAttribLocation(shader, "a_Color");

	glEnableVertexAttribArray(attribPosition);
	glEnableVertexAttribArray(attribNormal);
	glEnableVertexAttribArray(attribColor);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_Cube);

	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 10, 0);
	glVertexAttribPointer(attribNormal, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (GLvoid*)(sizeof(float) * 3));
	glVertexAttribPointer(attribColor, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (GLvoid*)(sizeof(float) * 6));

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisableVertexAttribArray(attribPosition);
	glDisableVertexAttribArray(attribNormal);
	glDisableVertexAttribArray(attribColor);

}

void Renderer::Test1()
{
	GLuint shader = m_Shaer_Test1;

	glUseProgram(shader);

	GLuint tex = glGetUniformLocation(shader, "u_TexPos");
	glUniform1i(tex, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Tex_IU);

	int attrribPosition = glGetAttribLocation(shader, "Position");
	GLint texPos = glGetAttribLocation(shader, "a_TexPos");

	glEnableVertexAttribArray(attrribPosition);
	glEnableVertexAttribArray(texPos);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_Test1);
	glVertexAttribPointer(attrribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glVertexAttribPointer(texPos, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

	glDrawArrays(GL_TRIANGLES, 0, 6);

}
