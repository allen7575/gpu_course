#include "..\glCircle.h"
#include "..\matrix.h"

glCircle::glCircle(){
	shaderProgram = NULL;
	Radius = 1;
}

glCircle::~glCircle(){

}

void glCircle::Create(GLuint *shader, float radius){

	shaderProgram = shader;
	Radius = radius;

	for(int i=0; i<VERTEXNUM; i++){
		Vertex[i].position = Vector3(Radius*sin(DELTATHETA*i), Radius*cos(DELTATHETA*i), 0);
		Vertex[i].color = Vector3(((float)i/VERTEXNUM),0,0);
	}

	glGenBuffers(1, &VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), Vertex, GL_STATIC_DRAW);


	for(int i=0; i<VERTEXNUM; i++){
		Indices[2*i] = i;
		Indices[2*i+1] = i+1;
	}
	Indices[2*VERTEXNUM-1] = 0;

	glGenBuffers(1, &IndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

void glCircle::Render(){

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
