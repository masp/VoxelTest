#include "renderer/shaders/program.hpp"

Program::Program() : programId(0)
{
}

Program::~Program()
{
	glDeleteProgram(programId);	
}

void Program::init()
{
	programId = glCreateProgram();
}

bool Program::setUniform(std::string const& uniform, glm::mat4 matrix)
{
    GLint loc = glGetUniformLocation(programId, uniform.c_str());
    if (loc == -1) return false;
    
    glUniformMatrix4fv(loc, 1, GL_FALSE, &matrix[0][0]);

    return true;
}

bool Program::setUniform(std::string const& uniform, GLuint uint)
{
	GLint loc = glGetUniformLocation(programId, uniform.c_str());
	if (loc == -1) return false;

	glUniform1i(loc, uint);

	return true;
}

bool Program::attachShader(const Shader& shader)
{
	glAttachShader(programId, shader);
	return true;
}

bool Program::link()
{
	glLinkProgram(programId);
	return true;
}

void Program::use()
{
	glUseProgram(programId);
}

void Program::stop()
{
	glUseProgram(0);
}
