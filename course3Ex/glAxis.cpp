#include "..\glAxis.h"
#include "..\matrix.h"

glAxis::glAxis()
{
	shaderProgram = NULL;
}

glAxis::~glAxis()
{

}

void glAxis::Create(GLuint *shader)
{
	shaderProgram = shader;

	Vertex[0].position = Vector3(0,0,0);
	Vertex[1].position = Vector3(1,0,0);
	Vertex[2].position = Vector3(0,1,0);
	Vertex[3].position = Vector3(0,0,1);
	Vertex[4].position = Vector3(0.8,0.1,0.1);
	Vertex[5].position = Vector3(0.1,0.8,0.1);
	Vertex[6].position = Vector3(0.1,0.1,0.8);
	Vertex[7].position = Vector3(0.8,-0.1,-0.1);
	Vertex[8].position = Vector3(-0.1,0.8,-0.1);
	Vertex[9].position = Vector3(-0.1,-0.1,0.8);

	Vertex[0].color = Vector3(1,1,1);
	for(int i=0;i<3;i++){
		Vertex[i*3+1].color = Vector3(1,0,0);
		Vertex[i*3+2].color = Vector3(0,1,0);
		Vertex[i*3+3].color = Vector3(0,0,1);
	}



	glGenBuffers(1,&VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex), Vertex, GL_STATIC_DRAW);


	GLuint TempIndices[INDEXNUM] = {
		0,1,
		0,2,
		0,3,
		1,4,
		2,5,
		3,6,
		1,7,
		2,8,
		3,9
	};

	for(int i=0; i<INDEXNUM; i++)
	{
		Indices[i] = TempIndices[i];
	}

	glGenBuffers(1,&IndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);


}

void glAxis::Render()
{
	GLint positionAttributeLocation = glGetAttribLocation(*shaderProgram, "position");
	GLint colorAttributeLocation = glGetAttribLocation(*shaderProgram, "color");

	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);

	glEnableVertexAttribArray(positionAttributeLocation);
	glVertexAttribPointer(positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glEnableVertexAttribArray(colorAttributeLocation);
	glVertexAttribPointer(colorAttributeLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (GLvoid*)(sizeof(float) * 3));


	Matrix4x4 modelMatrix = Translate(Vector3(0, 0, 0) ) * Scale(Vector3(1, 1, 1));
	GLuint modelMatLocation = glGetUniformLocation(*shaderProgram, "modelMatrix");

	glUniformMatrix4fv(modelMatLocation, 1, GL_TRUE, modelMatrix.FloatPtr());

	glDrawElements(GL_LINES,INDEXNUM,GL_UNSIGNED_INT,0);


}