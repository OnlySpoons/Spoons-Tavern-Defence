#include "Shader.h"

namespace spty {

	Shader::Shader()
		: id_(0)
	{
	}

	Shader::Shader(std::string const&& vertexPath, std::string const&& fragmentPath, std::string const&& geometryPath)
	{
		//Retrieve vertex/fragment/geometry source code from filePath
		std::string vertexCode, fragmentCode, geometryCode;
		std::ifstream vShaderFile, fShaderFile, gShaderFile;

		//Ensure ifstream objects can throw exceptions
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			//Open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;

			//Read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			//Close file handlers
			vShaderFile.close();
			fShaderFile.close();

			//Convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();

			//Check if geometry shader path is present
			if (geometryPath != "")
			{
				gShaderFile.open(geometryPath);
				std::stringstream gShaderStream;
				gShaderStream << gShaderFile.rdbuf();
				gShaderFile.close();
				geometryCode = gShaderStream.str();
			}
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		//Compile shaders
		unsigned int vertex, fragment;

		//Vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");

		//Fragment shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");

		//Geometry shader
		unsigned int geometry;
		if (geometryPath != "")
		{
			const char* gShaderCode = geometryCode.c_str();
			geometry = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometry, 1, &gShaderCode, NULL);
			glCompileShader(geometry);
			checkCompileErrors(geometry, "GEOMETRY");
		}

		//Shader program
		id_ = glCreateProgram();
		glAttachShader(id_, vertex);
		glAttachShader(id_, fragment);
		if (geometryPath != "")
			glAttachShader(id_, geometry);
		glLinkProgram(id_);
		checkCompileErrors(id_, "PROGRAM");

		//Delete the shaders
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		if (geometryPath != "")
			glDeleteShader(geometry);
	}

	//Use the shader
	void Shader::use() const
	{
		glUseProgram(id_);
	}

	void Shader::setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(id_, name.c_str()), (int)value);
	}

	void Shader::setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
	}

	void Shader::setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(id_, name.c_str()), value);
	}

	void Shader::setVec2(const std::string& name, glm::vec2 value)
	{
		glUniform2fv(glGetUniformLocation(id_, name.c_str()), 1, glm::value_ptr(value));
	}

	void Shader::setVec3(const std::string& name, glm::vec3 value) const
	{
		glUniform3fv(glGetUniformLocation(id_, name.c_str()), 1, glm::value_ptr(value));
	}

	void Shader::setVec4(const std::string& name, glm::vec4 value) const
	{
		glUniform4fv(glGetUniformLocation(id_, name.c_str()), 1, glm::value_ptr(value));
	}

	void Shader::setMat2(const std::string& name, glm::mat2 value) const
	{
		glUniformMatrix2fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::setMat3(const std::string& name, glm::mat3 value) const
	{
		glUniformMatrix3fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::setMat4(const std::string& name, glm::mat4 value) const
	{
		glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::checkCompileErrors(GLuint shader, std::string type) const
	{
		GLint success;
		GLchar infoLog[1024];
		std::string seperator = "\n -- --------------------------------------------------- -- ";

		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::" << type << "_SHADER_COMPILATION_ERROR\n" << infoLog << seperator  << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR\n" << infoLog << seperator << std::endl;
			}
		}
	}
}