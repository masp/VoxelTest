#include "world/chunk.hpp"

Chunk::Chunk() : chunkData(16 * 16 * 16)
{
    // Initialize all the memory
    for (uint8_t x = 0; x < 16; x++)
    {
		for (uint8_t z = 0; z < 16; z++)
		{
			uint8_t height = x * z / 16;
			for (uint8_t y = 0; y < height; y++)
			{
				chunkData[getIndex(x, y, z)] = 1;
			}
		}
	}

}

Chunk::~Chunk()
{
}

void Chunk::addCube(Batch& batch, uint8_t x, uint8_t y, uint8_t z)
{
	std::vector<glm::vec3> vertices(6 * 6);
	std::vector<glm::vec2> texCoords(6 * 6);

    glm::vec3 v0(x, y, z);
    glm::vec3 v1(x, y + 1.0f, z);
    glm::vec3 v2(x + 1.0f, y, z);
    glm::vec3 v3(x + 1.0f, y + 1.0f, z);
    glm::vec3 v4(x, y + 1.0f, z + 1.0f);
    glm::vec3 v5(x, y, z + 1.0f);
    glm::vec3 v6(x + 1.0f, y, z + 1.0f);
    glm::vec3 v7(x + 1.0f, y + 1.0f, z + 1.0f);   

	glm::vec2 t0(0.0f, 0.0f);
	glm::vec2 t1(0.0f, 1.0f);
	glm::vec2 t2(1.0f, 0.0f);
	glm::vec2 t3(1.0f, 1.0f);

    // Front Face
    vertices.push_back(v1); vertices.push_back(v0); vertices.push_back(v2);
	texCoords.push_back(t1); texCoords.push_back(t0); texCoords.push_back(t2);
    vertices.push_back(v2); vertices.push_back(v3); vertices.push_back(v1);
	texCoords.push_back(t2); texCoords.push_back(t3); texCoords.push_back(t1);
    
    // Right Face
	vertices.push_back(v3); vertices.push_back(v2); vertices.push_back(v6);
	texCoords.push_back(t1); texCoords.push_back(t0); texCoords.push_back(t2);
	vertices.push_back(v6); vertices.push_back(v7); vertices.push_back(v3);
	texCoords.push_back(t2); texCoords.push_back(t3); texCoords.push_back(t1);

    // Back Face
	vertices.push_back(v7); vertices.push_back(v6); vertices.push_back(v5);
	texCoords.push_back(t1); texCoords.push_back(t0); texCoords.push_back(t2);
	vertices.push_back(v5); vertices.push_back(v4); vertices.push_back(v7);
	texCoords.push_back(t2); texCoords.push_back(t3); texCoords.push_back(t1);

    // Left Face
	vertices.push_back(v4); vertices.push_back(v5); vertices.push_back(v0);
	texCoords.push_back(t1); texCoords.push_back(t0); texCoords.push_back(t2);
	vertices.push_back(v0); vertices.push_back(v1); vertices.push_back(v4);
	texCoords.push_back(t2); texCoords.push_back(t3); texCoords.push_back(t1);

    // Top Face
	vertices.push_back(v4); vertices.push_back(v1); vertices.push_back(v3);
	texCoords.push_back(t1); texCoords.push_back(t0); texCoords.push_back(t2);
	vertices.push_back(v3); vertices.push_back(v7); vertices.push_back(v4);
	texCoords.push_back(t2); texCoords.push_back(t3); texCoords.push_back(t1);

    // Bottom Face
	vertices.push_back(v0); vertices.push_back(v5); vertices.push_back(v6);
	texCoords.push_back(t1); texCoords.push_back(t0); texCoords.push_back(t2);
	vertices.push_back(v6); vertices.push_back(v2); vertices.push_back(v0);
	texCoords.push_back(t2); texCoords.push_back(t3); texCoords.push_back(t1);

	batch.vertices(vertices);
	batch.textures(texCoords);
}


void Chunk::build()
{
	Batch batch;
	batch.start();
    for (uint8_t x = 0; x < 16 ; x++)
    {
		for (uint8_t y = 0; y < 16; y++)
		{
			for (uint8_t z = 0; z < 16; z++)
			{
				if (getBlockId(x, y, z) == 0) continue;
				if (getBlockId(x + 1, y, z) != 0 &&
					getBlockId(x, y + 1, z) != 0 &&
					getBlockId(x, y, z + 1) != 0 &&
					getBlockId(x - 1, y, z) != 0 &&
					getBlockId(x, y - 1, z) != 0 &&
					getBlockId(x, y, z - 1) != 0) continue;
				addCube(batch, x, y, z);
			}
		}
    }
	mesh_.generateMesh(batch);
}

uint32_t Chunk::getBlockId(uint8_t x, uint8_t y, uint8_t z)
{
    if (x >= 16 || x < 0) return 0;
    if (y >= 16 || y < 0) return 0;
    if (z >= 16 || z < 0) return 0;

    return chunkData[getIndex(x, y, z)];
}

void Chunk::setBlock(uint8_t x, uint8_t y, uint8_t z, uint32_t val)
{
    if (x >= 16 || x < 0) return;
    if (y >= 16 || y < 0) return;
    if (z >= 16 || z < 0) return;
	
    chunkData[getIndex(x, y, z)] = val;
}
