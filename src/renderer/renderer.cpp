#include "renderer/renderer.hpp"

void Renderer::renderMesh(Mesh const& mesh)
{
	glBindVertexArray(mesh.id());

	glDrawArrays(GL_TRIANGLES, 0, mesh.size());	

	glBindVertexArray(0);
}
