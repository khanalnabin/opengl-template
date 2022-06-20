#include "../include/Shader.hpp"

Shader::Shader() {}
Shader::Shader(const char *vertexPath, const char *fragmentPath) {
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

	} catch (std::ifstream::failure &e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what()
		          << std::endl;
	}

	const char *vShaderCode = vertexCode.c_str();
	const char *fShaderCode = fragmentCode.c_str();

	unsigned int vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	CheckCompileErrors(vertex, "VERTEX");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	CheckCompileErrors(fragment, "FRAGMENT");

	// shader program
	m_RendererID = glCreateProgram();
	glAttachShader(m_RendererID, vertex);
	glAttachShader(m_RendererID, fragment);
	glLinkProgram(m_RendererID);
	CheckCompileErrors(m_RendererID, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}
void Shader::Use() const { glUseProgram(m_RendererID); }

void Shader::CheckCompileErrors(GLuint shader, std::string type) {
	int success;
	char infoLog[1024];

	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATON_ERROR of type: " << type
			          << "\n"
			          << infoLog << std::endl;
		}
	} else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type
			          << "\n"
			          << infoLog << std::endl;
		}
	}
}

void Shader::SetBool(const std::string &name, bool value) const {
	glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void Shader::SetInt(const std::string &name, int value) const {
	glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::SetFloat(const std::string &name, float value) const {
	glUniform1f(glGetUniformLocation(m_RendererID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::SetVec2(const std::string &name, const glm::vec2 &value) const {
	glUniform2fv(glGetUniformLocation(m_RendererID, name.c_str()), 1,
	             &value[0]);
}
void Shader::SetVec2(const std::string &name, float x, float y) const {
	glUniform2f(glGetUniformLocation(m_RendererID, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void Shader::SetVec3(const std::string &name, const glm::vec3 &value) const {
	glUniform3fv(glGetUniformLocation(m_RendererID, name.c_str()), 1,
	             &value[0]);
}
void Shader::SetVec3(const std::string &name, float x, float y, float z) const {
	glUniform3f(glGetUniformLocation(m_RendererID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::SetVec4(const std::string &name, const glm::vec4 &value) const {
	glUniform4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1,
	             &value[0]);
}
void Shader::SetVec4(const std::string &name, float x, float y, float z,
                     float w) const {
	glUniform4f(glGetUniformLocation(m_RendererID, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::SetMat2(const std::string &name, const glm::mat2 &mat) const {
	glUniformMatrix2fv(glGetUniformLocation(m_RendererID, name.c_str()), 1,
	                   GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::SetMat3(const std::string &name, const glm::mat3 &mat) const {
	glUniformMatrix3fv(glGetUniformLocation(m_RendererID, name.c_str()), 1,
	                   GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::SetMat4(const std::string &name, const glm::mat4 &mat) const {
	glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1,
	                   GL_FALSE, &mat[0][0]);
}
