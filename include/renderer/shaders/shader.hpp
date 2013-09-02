#ifndef _MAKESHIFT_SHADER_HPP_
#define _MAKESHIFT_SHADER_HPP_

#include <iostream>
#include <unordered_map>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>

class Shader
{
public:
	Shader(GLenum shaderType);
	~Shader();

	void loadShader(const std::string& source);

	void init();

	inline operator GLuint () const { return shaderId; } 
private:
	GLuint shaderId;
	GLenum shaderType;
};

#endif
