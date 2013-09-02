#ifndef _MAKESHIFT_PROGRAM_HPP_
#define _MAKESHIFT_PROGRAM_HPP_

#include "renderer/shaders/shader.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <GL/glew.h>
#include <GL/gl.h>

class Program
{
public:
	Program();
	~Program();
	
	bool attachShader(const Shader& shader);

	// Uniforms!
	bool setUniform(std::string const& uniform, glm::mat4 matrix);
	bool setUniform(std::string const& uniform, GLuint uint);

	bool link();
	void use();
	void stop();
	void init();
	inline operator GLuint () { return programId; }
private:
	GLuint programId;	

};

#endif
