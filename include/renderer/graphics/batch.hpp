#ifndef _MAKESHIFT_BATCH_HPP
#define _MAKESHIFT_BATCH_HPP

#include <vector>
#include <glm/glm.hpp>

class Batch
{

public:

	void start();

	void vertices(std::vector<glm::vec3> const& argVertices);

	void textures(std::vector<glm::vec2> const& argTextures);

	inline int size() const { return vertices_.size(); }

private:
	std::vector<glm::vec3> vertices_;
	std::vector<glm::vec2> texCoords_;

	friend class Mesh; // So that the Mesh class can directly access and upload the data to OpenGL without any performance penalty
};

#endif /* _MAKESHIFT_BATCH_HPP */
