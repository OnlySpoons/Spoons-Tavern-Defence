#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "stb_image.h"

#include "Shader.h"
#include "Mesh.h"

namespace spty {
	class Model
	{
	//Variables
	private:
		std::vector<Texture> texturesLoaded_;
		std::vector<Mesh> meshes_;
		std::vector<glm::mat4> transforms_;

		std::string directory_;
		bool gammaCorrection_;

	//Functions
	public:
		//Constructors
		Model();
		Model(std::string const& path, bool gamma = false);

		void draw(const Shader shader, const glm::mat4& model) const;

		CompoundCollider* getCompoundShape() const;

	private:
		inline glm::mat4 aiMatrix4x4ToGlm(const aiMatrix4x4& from);
		inline glm::vec3 aiVector3DToGlm(const aiVector3D& from);

		void loadModel(std::string const& path);

		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);

		std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
		unsigned int TextureFromFile(const char* path, bool gamma = false);
	};
}