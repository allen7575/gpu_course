#ifndef GL_AXIS
#define GL_AXIS

#define VERTEXNUM 10
#define INDEXNUM 18

#include "glUtility.h"

class glAxis
{
public:
	glAxis();
	~glAxis();
	void Create(GLuint *shader);
	void Render();
private:

	GLuint *shaderProgram;
	GLuint VertexBuffer;
	GLuint IndexBuffer;

	MyVertex Vertex[VERTEXNUM];
	GLuint Indices[INDEXNUM];

	

};


#endif
