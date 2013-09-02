#include "renderer/graphics/batch.hpp"

void Batch::start()
{
	vertices_.clear();
	texCoords_.clear();
}

void Batch::vertices(std::vector<glm::vec3> const& argVertices)
{
	vertices_.insert(vertices_.end(), argVertices.begin(), argVertices.end());	
}

void Batch::textures(std::vector<glm::vec2> const& argTextures)
{
	texCoords_.insert(texCoords_.end(), argTextures.begin(), argTextures.end());
}
	
