#ifndef _MAKESHIFT_TEXTURE_HPP_
#define _MAKESHIFT_TEXTURE_HPP_

#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include <png.h>
#include "utils/GLError.hpp"
#include "renderer/shaders/program.hpp"

class Texture
{

public:
	Texture();
	~Texture();

	bool loadTexture(std::string const&& path);
	bool upload(Program& program, std::string const& name);

	inline size_t getWidth() const { return width; }
	inline size_t getHeight() const { return height; }

private:
	GLuint textureID;
	
	size_t width;
	size_t height;

};


#endif
