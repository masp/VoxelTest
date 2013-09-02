#include "renderer/shaders/shader.hpp"

Shader::Shader(GLenum argShaderType) : shaderId(0), shaderType(argShaderType) 
{
}

Shader::~Shader()
{
	glDeleteShader(shaderId);
}

void Shader::init()
{
	shaderId = glCreateShader(shaderType);	
}

void Shader::loadShader(const std::string& source)
{
	const char * c_str = source.c_str();
	glShaderSource(shaderId, 1, &c_str, NULL);

	glCompileShader(shaderId);

	GLint status;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shaderId, infoLogLength, NULL, strInfoLog);

		const char* strShaderType = NULL;
		switch (shaderType)
		{
			case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
			case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
			case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
		}

		std::cout << "Compile error in " << strShaderType << " shader:" << std::endl;
		std::cout << strInfoLog;
		delete[] strInfoLog;
	}
}
