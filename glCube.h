#ifndef GL_CUBE
#define GL_CUBE

#define VERTEXNUM 8
#define INDEXNUM 24

#include "..\glUtility.h"
#include "..\matrix.h"

class glCube
{
public:
	glCube();
	~glCube();
	void Create(GLuint *shader);
	void Render();
	void Translation(Vector3 translate);
	void Rotation(Matrix4x4 rotate);
	void Scalation(Vector3 scale);
private:

	GLuint *shaderProgram;

	GLuint VertexBuffer;
	GLuint IndexBuffer;

	MyVertex Vertex[VERTEXNUM];
	GLuint Indices[INDEXNUM];

	GLint positionAttributeLocation;
	GLint colorAttributeLocation;


	Matrix4x4 modelMatrix;
	GLuint modelMatLocation;


};





#endif