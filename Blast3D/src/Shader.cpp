#include "Shader.h"
#include <fstream>
#include <iostream>
#include "GLEssential.h"

Shader::Shader(const std::string & filepath)
{
	ShaderSource shaderSource = ExtractShaderSourceFile(filepath);
	CompileShader(shaderSource.vertexShader, shaderSource.fragmentShader);
}

Shader::~Shader()
{
	glDetachShader(m_RendererID, m_vShader);
	glDetachShader(m_RendererID, m_fShader);
	glDeleteProgram(m_RendererID);
}

ShaderSource Shader::ExtractShaderSourceFile(const std::string& filepath)
{
	std::ifstream input;
	input.open(filepath);

	if (!input.is_open())
	{
		std::cout << "GLSL source code at " << filepath << "could not be opened !" << std::endl;
		std::cin.get();
		exit(EXIT_SUCCESS);
	}
	else
	{
		ShaderType shaderType = NONE;
		std::string shaderSource[2];
		std::string line;
		while (!input.eof())
		{
			std::getline(input, line);
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
				{
					shaderType = VERTEX_SHADER;
				}
				else if (line.find("fragment") != std::string::npos)
				{
					shaderType = FRAGMENT_SHADER;
				}
			}
			else
			{
				if (shaderType != NONE)
					shaderSource[(int)shaderType].append(line + "\n");
			}
		}

		return { shaderSource[0], shaderSource[1] };
	}
}

void Shader::CompileShader(const std::string& vSource, const std::string& fSource)
{
	m_vShader = glCreateShader(GL_VERTEX_SHADER);
	m_fShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char *source;
	source = vSource.c_str();
	glShaderSource(m_vShader, 1, &source, nullptr);

	source = fSource.c_str();
	glShaderSource(m_fShader, 1, &source, nullptr);

	glCompileShader(m_vShader);
	glCompileShader(m_fShader);

	if (!CheckCompileLinkError(glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS, m_vShader) ||
		!CheckCompileLinkError(glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS, m_vShader))
	{
		ASSERT(false);
	}

	/* Create program */
	m_RendererID = glCreateProgram();

	glAttachShader(m_RendererID, m_vShader);
	glAttachShader(m_RendererID, m_fShader);

	glLinkProgram(m_RendererID);

	if (!CheckCompileLinkError(glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS, m_RendererID))
		ASSERT(false);

	glValidateProgram(m_RendererID);
}

void Shader::SetUniform1i(const std::string & name, int v0)
{
	glUniform1i(GetUniformLocation(name), v0);
}

void Shader::SetUniform4f(const std::string & name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniforMat4f(const std::string & name, const Matrix4& matrix)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, matrix.get());
}

int Shader::GetUniformLocation(const std::string & name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())	// if name is found
	{
		return m_UniformLocationCache[name];
	}

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));

	if (location == -1)
	{
		std::cout << "[Warning] : ( " << name << " ) could not find location ! " << std::endl;
	}
	else
		m_UniformLocationCache[name] = location;

	return location;
}

bool Shader::CheckCompileLinkError(PFNGLGETSHADERIVPROC checkErrorFunction,
	PFNGLGETSHADERINFOLOGPROC GetInfoLog, GLenum type, GLuint id)
{
	GLint status;
	checkErrorFunction(id, type, &status);

	if (status == GL_FALSE)
	{
		GLint maxLength;
		checkErrorFunction(id, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar *infoLog = new GLchar[maxLength];
		GetInfoLog(id, maxLength, nullptr, infoLog);

		std::cout << (type == GL_COMPILE_STATUS ? "Compilation Error !" : "Linking Error !") << std::endl
			<< "OpenGL : " << infoLog << std::endl;
		std::cin.get();

		delete[] infoLog;
		return false;
	}
	return true;
}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}
