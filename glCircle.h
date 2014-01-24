#ifndef GL_CIRCLE
#define GL_CIRCLE

#define _USE_MATH_DEFINES
#include <math.h>

#define DELTATHETA (0.1*M_PI/180)
#define VERTEXNUM (int)(2*M_PI/DELTATHETA)
#define INDEXNUM (int)(2*VERTEXNUM)

#include "glUtility.h"

class glCircle
{
public:
	glCircle();
	~glCircle();
	void Create(GLuint *shader, float radius);
	void Render();

private:

	GLuint *shaderProgram;
	GLuint VertexBuffer;
	GLuint IndexBuffer;

	MyVertex Vertex[VERTEXNUM];
	GLuint Indices[INDEXNUM];

	float Radius;

};


#endif


