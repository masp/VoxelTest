#ifndef _MAKESHIFT_MESH_HPP_
#define _MAKESHIFT_MESH_HPP_

#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/gl.h>

#include "renderer/graphics/batch.hpp"

/**
    @author Mark Asp
    @version 0.01
    @brief Stores a mesh or collection of vertex, texture, & normal data
    @details Provides an OpenGL wrapper for a vertex buffer object, texture
	buffer object, and normal buffer object.
*/

class Mesh
{

public:

    Mesh();
    virtual ~Mesh();

	void generateMesh(Batch const& batch);

    /**
	Returns a vao ID that OpenGL can use to render
	@param id The VAO ID used to render
    */
    virtual int id() const;
    virtual size_t size() const; 
    
private:
    // All of the data is bound to the vertex array object
    GLuint vao;
    
    GLuint vbo;
    GLuint tbo;

    size_t numVertices;

    void deallocate();

    Mesh(Mesh const& other);
    Mesh& operator=(Mesh const&);

};

#endif
