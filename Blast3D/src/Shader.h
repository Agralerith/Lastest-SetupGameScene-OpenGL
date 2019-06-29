#pragma once

#include <string>
#include <GL/glew.h>
#include <unordered_map>
#include "Matrix.h"

enum ShaderType
{
	NONE = -1, VERTEX_SHADER, FRAGMENT_SHADER
};

struct ShaderSource
{
	std::string vertexShader;
	std::string fragmentShader;
};

class Shader
{
private:
	unsigned int m_RendererID;
	unsigned int m_vShader, m_fShader;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	bool CheckCompileLinkError(PFNGLGETSHADERIVPROC checkErrorFunction,
		PFNGLGETSHADERINFOLOGPROC GetInfoLog, GLenum type, GLuint id);

	ShaderSource ExtractShaderSourceFile(const std::string& filepath);
	void CompileShader(const std::string& vSource, const std::string& fSource);

	void SetUniform1i(const std::string& name, int v0);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniforMat4f(const std::string& name, const Matrix4& matrix);
	int GetUniformLocation(const std::string& name);
};