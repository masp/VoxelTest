#ifndef _MAKESHIFT_RENDERER_HPP_
#define _MAKESHIFT_RENDERER_HPP_

#include <GL/glew.h>
#include <GL/gl.h>
#include "renderer/graphics/mesh.hpp"

class Renderer
{

public:
	
	void renderMesh(Mesh const& mesh);

};

#endif
