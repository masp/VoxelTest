#include "renderer/graphics/mesh.hpp"

Mesh::Mesh() : vao(0), vbo(0), tbo(0)
{ }

Mesh::~Mesh()
{
    deallocate();
}

void Mesh::generateMesh(Batch const& batch)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &tbo);

	numVertices = batch.vertices_.size();

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec3), &batch.vertices_[0], GL_STREAM_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	glBindBuffer(GL_ARRAY_BUFFER, tbo);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec2), &batch.texCoords_[0], GL_STREAM_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 0, 0);

	glBindVertexArray(0);
}

void Mesh::deallocate()
{
    glDeleteVertexArrays(1, &vao);

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &tbo);
}

int Mesh::id() const { return vao; }

size_t Mesh::size() const { return numVertices; }
