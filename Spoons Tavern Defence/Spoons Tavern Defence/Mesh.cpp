#include "Mesh.h"

namespace spty {

    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
        : vertices_(vertices), indices_(indices), textures_(textures)
    {
        setupMesh();
    }

    void Mesh::draw(Shader shader) const
    {
        //Bind appropriate textures
        unsigned int diffuseNr  = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr   = 1;
        unsigned int heightNr   = 1;

        for (unsigned int i = 0; i < textures_.size(); i++)
        {
            //Active proper texture unit before binding
            glActiveTexture(GL_TEXTURE0 + i);
            //Retrieve texture number (the N in diffuse_textureN)
            std::string number;
            std::string name = textures_[i].type;
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++);
            else if (name == "texture_normal")
                number = std::to_string(normalNr++);
            else if (name == "texture_height")
                number = std::to_string(heightNr++);

            //Now set the sampler to the correct texture unit
            shader.setInt(("material." + (name + number)).c_str(), i);
            //Bind the texture
            glBindTexture(GL_TEXTURE_2D, textures_[i].id);
        }

        //Draw mesh
        glBindVertexArray(VAO_);
        glDrawElements(GL_TRIANGLES, (GLsizei)indices_.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        //Set everything back to defaults
        glActiveTexture(GL_TEXTURE0);
    }

    MeshCollider* Mesh::getMeshCollider() const
    {
        btTriangleMesh trimesh = btTriangleMesh();

        for (long i = 0; i * 3l < indices_.size() - 1; i++)
        {
            int index0 = indices_[i * 3l + 0];
            int index1 = indices_[i * 3l + 1];
            int index2 = indices_[i * 3l + 2];

            btVector3 vertex0( Physics::glmVec3TobtVector3( vertices_[index0].position ) );
            btVector3 vertex1( Physics::glmVec3TobtVector3( vertices_[index1].position ) );
            btVector3 vertex2( Physics::glmVec3TobtVector3( vertices_[index2].position ) );

            trimesh.addTriangle(vertex0, vertex1, vertex2);
        }

        MeshCollider* mesh = new MeshCollider(trimesh);

        return mesh;
    }

    void Mesh::setupMesh()
    {
        //Create buffers/arrays
        glGenVertexArrays(1, &VAO_);
        glGenBuffers(1, &VBO_);
        glGenBuffers(1, &EBO_);

        glBindVertexArray(VAO_);

        //Load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, VBO_);
        glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(Vertex), &vertices_[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int), &indices_[0], GL_STATIC_DRAW);

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