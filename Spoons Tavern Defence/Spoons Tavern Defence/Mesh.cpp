#include "Mesh.h"

namespace spty {

    //Constructor
    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) : _vertices(vertices), _indices(indices), _textures(textures)
    {
        //Set the vertex buffers and its attribute pointers.
        setupMesh();
    }

    //Render the mesh
    void Mesh::Draw(Shader shader) const
    {
        //Bind appropriate textures
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        unsigned int heightNr = 1;

        for (unsigned int i = 0; i < _textures.size(); i++)
        {
            //Active proper texture unit before binding
            glActiveTexture(GL_TEXTURE0 + i);
            //Retrieve texture number (the N in diffuse_textureN)
            std::string number;
            std::string name = _textures[i].type;
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++);  //Transfer unsigned int to stream
            else if (name == "texture_normal")
                number = std::to_string(normalNr++);    //Transfer unsigned int to stream
            else if (name == "texture_height")
                number = std::to_string(heightNr++);    //Transfer unsigned int to stream

            //Now set the sampler to the correct texture unit
            shader.setInt(("material." + (name + number)).c_str(), i);
            //Bind the texture
            glBindTexture(GL_TEXTURE_2D, _textures[i].id);
        }

        //Draw mesh
        glBindVertexArray(_VAO);
        glDrawElements(GL_TRIANGLES, (GLsizei)_indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        //Set everything back to defaults
        glActiveTexture(GL_TEXTURE0);
    }

    MeshCollider* Mesh::getMeshCollider() const
    {
        btTriangleMesh trimesh = btTriangleMesh();

        for (int i = 0; i * 3 < _indices.size() - 1; i++)
        {
            int index0 = _indices[i * 3 + 0];
            int index1 = _indices[i * 3 + 1];
            int index2 = _indices[i * 3 + 2];


            glm::vec3 pos;

            pos = glm::vec4(_vertices[index0].position , 1.0f);
            btVector3 vertex0( Physics::glmVec3TobtVector3( pos ));

            pos = glm::vec4(_vertices[index1].position , 1.0f);
            btVector3 vertex1( Physics::glmVec3TobtVector3( pos ));

            pos = glm::vec4(_vertices[index2].position , 1.0f);
            btVector3 vertex2( Physics::glmVec3TobtVector3( pos ));

            trimesh.addTriangle(vertex0, vertex1, vertex2);
        }

        MeshCollider* mesh = new MeshCollider(trimesh);

        return mesh;
    }

    //Initializes all the buffer objects/arrays
    void Mesh::setupMesh()
    {
        //Create buffers/arrays
        glGenVertexArrays(1, &_VAO);
        glGenBuffers(1, &_VBO);
        glGenBuffers(1, &_EBO);

        glBindVertexArray(_VAO);

        //Load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

        //Set the vertex attribute pointers
        //Vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        //Vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        //Vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
        //Vertex tangent
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
        //Vertex bitangent
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));

        glBindVertexArray(0);
    }
}