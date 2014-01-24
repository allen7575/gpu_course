#include "..\glCube.h"
//#include "..\matrix.h"

glCube::glCube()
{
	shaderProgram = NULL;
	modelMatrix = Translate(Vector3(0, 0, 0));
	
}

glCube::~glCube()
{

}

void glCube::Create(GLuint *shader)
{
	shaderProgram = shader;
	
	positionAttributeLocation = glGetAttribLocation(*shaderProgram, "position");
	colorAttributeLocation = glGetAttribLocation(*shaderProgram, "color");
	modelMatLocation = glGetUniformLocation(*shaderProgram, "modelMatrix");


	Vertex[0].position = Vector3(1, 1, 1);
	Vertex[1].position = Vector3(1, 1, -1);
	Vertex[2].position = Vector3(1, -1, 1);
	Vertex[3].position = Vector3(1, -1, -1);
	Vertex[4].position = Vector3(-1, 1, 1);
	Vertex[5].position = Vector3(-1, 1, -1);
	Vertex[6].position = Vector3(-1, -1, 1);
	Vertex[7].position = Vector3(-1, -1, -1);

	for(int i = 0; i < VERTEXNUM; i++)
	{
		Vertex[i].color = Vector3(1, 0, 0);
	}

	glGenBuffers(1, &VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), Vertex, GL_STATIC_DRAW);


	GLuint TempIndices[INDEXNUM] = {
		0, 2,
		1, 3,
		5, 7,
		4, 6,
		0, 4,
		1, 5,
		3, 7,
		2, 6,
		0, 1,
		4, 5,
		6, 7,
		2, 3
	};

	for (int i=0; i<INDEXNUM; i++)
	{
		Indices[i] = TempIndices[i];
	}


	glGenBuffers(1, &IndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);


}

void glCube::Render()
{
	//GLint positionAttributeLocation = glGetAttribLocation(*shaderProgram, "position");
	//GLint colorAttributeLocation = glGetAttribLocation(*shaderProgram, "color");

	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);

	glEnableVertexAttribArray(positionAttributeLocation);
	glVertexAttribPointer(positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glEnableVertexAttribArray(colorAttributeLocation);
	glVertexAttribPointer(colorAttributeLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (GLvoid*)(sizeof(float) * 3));


	//Matrix4x4 modelMatrix = Translate(Vector3(0, 0, 0) ) * Scale(Vector3(1, 1, 1));
	//GLuint modelMatLocation = glGetUniformLocation(*shaderProgram, "modelMatrix");

	glUniformMatrix4fv(modelMatLocation, 1, GL_TRUE, modelMatrix.FloatPtr());

	glDrawElements(GL_LINES,INDEXNUM,GL_UNSIGNED_INT,0);

}

void glCube::Translation(Vector3 translate)
{
	modelMatrix *= Translate(translate);
}

void glCube::Scalation(Vector3 scale)
{
	modelMatrix *= Scale(scale);
}
