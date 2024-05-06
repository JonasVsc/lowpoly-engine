#include"triangle.h"

lowpoly::triangle::triangle()
{

	glGenVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);

	glGenBuffers(1, &buf);
	glBindBuffer(GL_ARRAY_BUFFER, buf);

	vertices[0] = -1.0f;
	vertices[1] = -1.0f;
	vertices[2] = -1.0f;

	vertices[3] =  0.0f;
	vertices[4] =  1.0f;
	vertices[5] = -1.0f;

	vertices[6] =  1.0f;
	vertices[7] = -1.0f;
	vertices[8] = -1.0f;

	

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}
void lowpoly::triangle::draw(GLuint shaderProgram)
{
	glUseProgram(shaderProgram);
	glBindVertexArray(vertex_array_object);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}
