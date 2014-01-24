#include <stdio.h>
#include "../window.h"
#include "../glUtility.h"
#include "../vector.h"
#include "../matrix.h"
#include "../Timer.h"
#include "../camera.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "../stb_truetype.h"

#include "../glMouseControl.h"
#include "../glKeyboardControl.h"
#include "../glCircle.h"
#include "../glAxis.h"
#include "../glCube.h"

Window window;

GLuint boxVertexBuffer;
GLuint boxIndexBuffer;

MyInputListener *inputlistener;
glMouseControl *mousecontrolptr;
glKeyboardControl *keyboardcontrol;
glCircle *circleptr;
glAxis *axisptr;
glCube *cubeptr[2];


GLuint shaderProgram;
MyPerspectiveCamera camera;

double frameTime = 16;

float cameraMoveSpeed = 2.f;
float cameraTurnSpeed = 1.f;


struct BitmapChar
{
	wchar_t c;
	int width;
	int height;
	unsigned char* bitmap;
};

BitmapChar attackOnTitan[16];
BitmapChar attackOnTitanCh[5];

BitmapChar FPS[5];
const wchar_t* FPSstr = L"000.0";

const wchar_t* attackOnTitanStr = L"Attack on Titan!";
const wchar_t* AttackOnTitanChStr = L"¶iÀ»ªº¥¨¤H";

unsigned char ttf_buffer[(1<<25)];
void InitResources()
{
	//load shader
	shaderProgram = CreateProgram("vertexShader.glsl", "pixelShader.glsl");

	//boxVertexBuffer = CreateCubeVertexBuffer();
	//boxIndexBuffer = CreateWireCubeIndexBuffer();

	inputlistener = new MyInputListener();
	SetInputListener(inputlistener);

	mousecontrolptr = new glMouseControl(inputlistener, &camera);

	circleptr = new glCircle();
	circleptr->Create(&shaderProgram, 2.5);

	axisptr = new glAxis();
	axisptr->Create(&shaderProgram);

	cubeptr[0] = new glCube();
	cubeptr[0]->Create(&shaderProgram);
	cubeptr[0]->Translation(Vector3(-4, -1.8, 0));
	cubeptr[0]->Scalation(Vector3(1,1,1));

	cubeptr[1] = new glCube();
	cubeptr[1]->Create(&shaderProgram);
	cubeptr[1]->Translation(Vector3(-5, 1.8, 0));
	cubeptr[1]->Scalation(Vector3(1.5,1.5,1.5));

	keyboardcontrol = new glKeyboardControl(inputlistener, cubeptr[0]);

	stbtt_fontinfo font;
    fread(ttf_buffer, 1, (1<<25), fopen("c:/windows/fonts/ARIALUNI.TTF", "rb"));
	stbtt_InitFont(&font, ttf_buffer, stbtt_GetFontOffsetForIndex(ttf_buffer,0));

	//attack on titan !!!
	for(int i = 0; i < 16; i++)
	{
		attackOnTitan[i].c = attackOnTitanStr[i];
		int s = 32;
		attackOnTitan[i].bitmap = stbtt_GetCodepointBitmap(&font, 0,stbtt_ScaleForPixelHeight(&font, s), attackOnTitan[i].c, 
			&attackOnTitan[i].width, &attackOnTitan[i].height, 0,0);
	}

    for(int i = 0; i < 5; i++)
    {
        attackOnTitanCh[i].c = AttackOnTitanChStr[i];
        int s = 32;
        attackOnTitanCh[i].bitmap = stbtt_GetCodepointBitmap(&font, 0,stbtt_ScaleForPixelHeight(&font, s), attackOnTitanCh[i].c, 
            &attackOnTitanCh[i].width, &attackOnTitanCh[i].height, 0,0);
    }
}





void RenderFPS(float frametime){

	//sprintf(FPSstr,"%f.1",frametime);





}


void RenderAttackOnTitan()
{
	int rasterPos = -100;

	GLint modelMatLocation = glGetUniformLocation(shaderProgram, "modelMatrix");
	GLint cubeColorLocation = glGetUniformLocation(shaderProgram, "cubeColor");

	for(int i = 0; i < 16; i++)
	{
		int width = attackOnTitan[i].width;
		int height = attackOnTitan[i].height;

		if(attackOnTitan[i].c == L' ')
		{
			rasterPos += 5;
		}

		for(int j = 0; j < height; j++)
		{
			for(int k = 0; k < width; k++)
			{
				unsigned char colorValue = attackOnTitan[i].bitmap[(height - j - 1) * width + k];

				if(colorValue > 0)
				{
					Matrix4x4 modelMatrix = Translate(Vector3( 15, (float)(rasterPos + k), (float)(j)) ) * Scale(Vector3(0.5, 0.5, 0.5));
					glUniformMatrix4fv(modelMatLocation, 1, GL_TRUE, modelMatrix.FloatPtr());
					Vector3 cubeColor(1, 0, 0);
					glUniform3fv(cubeColorLocation, 1, &cubeColor[0]);
					glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
				}				
			}
		}
		rasterPos += (width + 2);
	}

	rasterPos = -60;
    for(int i = 0; i < 5; i++)
    {
        int width = attackOnTitanCh[i].width;
        int height = attackOnTitanCh[i].height;

        if(attackOnTitanCh[i].c == L' ')
        {
            rasterPos += 5;
        }

        for(int j = 0; j < height; j++)
        {
            for(int k = 0; k < width; k++)
            {
                unsigned char colorValue = attackOnTitanCh[i].bitmap[(height - j - 1) * width + k];

                if(colorValue > 0)
                {
                    Matrix4x4 modelMatrix = Translate(Vector3( 10, (float)(rasterPos + k), (float)(j) + 15) ) * Scale(Vector3(0.5, 0.5, 0.5));
                    glUniformMatrix4fv(modelMatLocation, 1, GL_TRUE, modelMatrix.FloatPtr());
                    Vector3 cubeColor(1, 0, 0);
                    glUniform3fv(cubeColorLocation, 1, &cubeColor[0]);
                    glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
                }				

            }
        }
        rasterPos += (width + 2);
    }
}

void Render(double frameTime)
{

	glClearColor(0.5, 0.5, 0.5, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderProgram);
	//GLint positionAttributeLocation = glGetAttribLocation(shaderProgram, "position");
	//GLint colorAttributeLocation = glGetAttribLocation(shaderProgram, "color");

	//GLint modelMatLocation = glGetUniformLocation(shaderProgram, "modelMatrix");
	GLint viewMatLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
	GLint projectionMatLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
	//GLint cubeColorLocation = glGetUniformLocation(shaderProgram, "cubeColor");

    Matrix4x4 viewMatrix = camera.ViewMatrix();
    Matrix4x4 projectionMatrix = camera.SimplePerspective();
	//Vector3 cubeColor(1, 1, 1);

	glUniformMatrix4fv(viewMatLocation, 1, GL_TRUE, viewMatrix.FloatPtr());
	glUniformMatrix4fv(projectionMatLocation, 1, GL_TRUE, projectionMatrix.FloatPtr() );
	//glUniform3fv(cubeColorLocation, 1, &cubeColor[0]);

	//glBindBuffer(GL_ARRAY_BUFFER, boxVertexBuffer);
	//glEnableVertexAttribArray(positionAttributeLocation);
	//glVertexAttribPointer(positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	//glEnableVertexAttribArray(colorAttributeLocation);
	//glVertexAttribPointer(colorAttributeLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (GLvoid*)(sizeof(float) * 3));

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boxIndexBuffer);

	////draw first box
	//Matrix4x4 modelMatrix = Translate(Vector3(-4, -1.8, 0) ) * Scale(Vector3(1, 1, 1));
	//glUniformMatrix4fv(modelMatLocation, 1, GL_TRUE, modelMatrix.FloatPtr());
	//glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);

	////draw second box
	//modelMatrix = Translate(Vector3(-5, 1.8, 0) ) * Scale(Vector3(1.5, 1.5, 1.5));
	//glUniformMatrix4fv(modelMatLocation, 1, GL_TRUE, modelMatrix.FloatPtr());
	//glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);

	//attack on titan!!!
	//RenderAttackOnTitan();

	mousecontrolptr->MouseControlRender();

	keyboardcontrol->KeyboardControlRender();

	circleptr->Render();
	axisptr->Render();
	cubeptr[0]->Render();
	cubeptr[1]->Render();

	SwapBuffers(window.hdc);

}

void main()
{
    FastTimer::Initialize();

	if(!InitWindow(800, 800, window))
		return;

	if(!InitGL(window.hwnd, 4))
		return;

	InitResources();

    FastTimer timer;

    timer.Start();
	MSG msg = {0};
	while( WM_QUIT != msg.message )
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
			//if( GetMessage( &msg, NULL, 0, 0 ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		Render(frameTime);

	}
    timer.End();
    frameTime = timer.GetDurationInMillisecnds();
}