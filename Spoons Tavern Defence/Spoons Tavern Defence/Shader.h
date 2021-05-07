#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace spty {
	class Shader
	{
	//Variables
	public:
		unsigned int id_;

	//Functions
	public:
		//Constructors
		Shader();
		Shader(std::string const&& vertexPath, std::string const&& fragmentPath, std::string const&& geometryPath = "");

		void use() const;

		//Utility functions for setting shader values

		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;

		void setVec2(const std::string& name, glm::vec2 value);
		void setVec3(const std::string& name, glm::vec3 value) const;
		void setVec4(const std::string& name, glm::vec4 value) const;

		void setMat2(const std::string& name, glm::mat2 value) const;
		void setMat3(const std::string& name, glm::mat3 value) const;
		void setMat4(const std::string& name, glm::mat4 value) const;

	private:


		void checkCompileErrors(GLuint shader, std::string type) const;
	};
}