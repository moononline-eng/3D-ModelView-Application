#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, const void* offset)
{
	VBO.Bind();
	// Configure the Vertex Attribute for OpenGL so it can properly read the VBO
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	// Enable the Vertex Array Attribute for OpenGL
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(ID);

}
void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}