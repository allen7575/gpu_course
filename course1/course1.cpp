#include "../window.h"
#include "../glUtility.h"
#include <stdio.h>

///////////////////////////////
#define _USE_MATH_DEFINES
#include <math.h>

#define EPICYCLOID 1
#define HYPOTROCHOID 0
#define VERTEXNUM 360
///////////////////////////////

Window window;

struct Vertex
{
    float x, y, z;
    float r, g, b;
};

GLuint vertexBuffer;
GLuint indexBuffer;
GLuint shaderProgram;

void InitResources()
{
    //load shader
    shaderProgram = CreateProgram("vertexShader.glsl", "pixelShader.glsl");

	///////////////////////////////////////////////////////////////
    struct Vertex triangleVertices[VERTEXNUM];
    GLuint triangleIndices[VERTEXNUM];

	//generate triangle vertex buffer
	if(EPICYCLOID){ 
		for(int i=0; i<VERTEXNUM; i++)
		{
			//Epicycloid
			float theta = i*47*M_PI/180;
			float k,k_1,r;
			r=0.2;
			k=2.1;
			k_1 = k+1;
			//triangleVertices[i].x = cos(theta);
			//triangleVertices[i].y = sin(theta);
			triangleVertices[i].x = r*k_1*cos(theta)-r*cos(k_1*theta);
			triangleVertices[i].y = r*k_1*sin(theta)-r*sin(k_1*theta);
			triangleVertices[i].z = -1;

			triangleVertices[i].r = cos(theta);
			triangleVertices[i].g = sin(theta);
			triangleVertices[i].b = theta/VERTEXNUM;

			triangleIndices[i]=i;
		};
	};

	if(HYPOTROCHOID){ 
		for(int i=0; i<VERTEXNUM; i++)
		{
			//Hypotrochoid
			float theta = i*77*M_PI/180;
			float R,r,d;
			R=5;
			r=3;
			d=5;
			//triangleVertices[i].x = cos(theta);
			//triangleVertices[i].y = sin(theta);
			triangleVertices[i].x = 0.1*((R-r)*cos(theta)+d*cos((R/r-1)*theta));
			triangleVertices[i].y = 0.1*((R-r)*sin(theta)-d*sin((R/r-1)*theta));
			triangleVertices[i].z = -1;

			triangleVertices[i].r = cos(theta);
			triangleVertices[i].g = sin(theta);
			triangleVertices[i].b = theta/VERTEXNUM;

			triangleIndices[i]=i;
		};

	};
	///////////////////////////////////////////////////////

	///////////////////////////////////////////////////////
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * VERTEXNUM, triangleVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * VERTEXNUM, triangleIndices, GL_STATIC_DRAW);
	///////////////////////////////////////////////////////
}

void Render()
{
    glClearColor(0.5, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(shaderProgram);
    GLint positionAttributeLocation = glGetAttribLocation(shaderProgram, "position");
    GLint colorAttributeLocation = glGetAttribLocation(shaderProgram, "color");

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glEnableVertexAttribArray(positionAttributeLocation);
    glVertexAttribPointer(positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
    glEnableVertexAttribArray(colorAttributeLocation);
    glVertexAttribPointer(colorAttributeLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (GLvoid*)(sizeof(float) * 3));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    //glDrawArrays(GL_TRIANGLES, 0, 3);
    //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

	/////////////////////////////////////////////////////////////
	//glDrawElements(GL_LINES, VERTEXNUM, GL_UNSIGNED_INT, 0);
	glDrawElements(GL_TRIANGLES, VERTEXNUM, GL_UNSIGNED_INT, 0);
	/////////////////////////////////////////////////////////////

    SwapBuffers(window.hdc);
}

void main()
{
    if(!InitWindow(700, 700, window))
        return;
    
    if(!InitGL(window.hwnd, 0))
        return;

    InitResources();
    
    MSG msg = {0};
    while( WM_QUIT != msg.message )
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
            //if( GetMessage( &msg, NULL, 0, 0 ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        Render();
    }
}