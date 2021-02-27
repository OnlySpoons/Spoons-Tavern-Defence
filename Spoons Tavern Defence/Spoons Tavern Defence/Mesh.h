#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

namespace Spoonity {

    //Vertex data
    struct Vertex
    {
        //Position
        glm::vec3 position;
        //Normal
        glm::vec3 normal;
        //TexCoords
        glm::vec2 texCoords;
        //Tangent
        glm::vec3 tangent;
        //Bitangent
        glm::vec3 bitangent;
    };

    //Texture data
    struct Texture
    {
        unsigned int id;
        std::string type;
        std::string path;
    };

    class Mesh {

        //Variables
    private:
        //Mesh Data
        std::vector<Vertex> _vertices;
        std::vector<unsigned int> _indices;
        std::vector<Texture> _textures;
        unsigned int _VAO, _VBO, _EBO;

        //Functions
    public:

        //Constructor
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

        //Render the mesh
        void Draw(Shader shader) const;

    private:

        //Initializes all the buffer objects/arrays
        void setupMesh();
    };
}