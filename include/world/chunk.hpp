#ifndef _MAKESHIFT_CHUNK_HPP_
#define _MAKESHIFT_CHUNK_HPP_

#include <vector>
#include <memory>
#include "renderer/graphics/mesh.hpp"
#include <glm/glm.hpp>

class Chunk
{

public:
	Chunk();

	~Chunk();

	uint32_t getBlockId(uint8_t x, uint8_t y, uint8_t z);

	void setBlock(uint8_t x, uint8_t y, uint8_t z, uint32_t val);

	void build();

	inline Mesh const& mesh() const { return mesh_; }

private:	
	static inline uint8_t getIndex(uint8_t x, uint8_t y, uint8_t z)
	{
		return x + 16 * (y + 16 * z);
	}

	void addCube(Batch& batch, uint8_t x, uint8_t y, uint8_t z);

	std::vector<uint8_t> chunkData; 
	Mesh mesh_;
};

#endif
