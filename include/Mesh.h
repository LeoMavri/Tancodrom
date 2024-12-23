//
// Created by mavri on 23.12.2024.
//

#ifndef MESH_H
#define MESH_H

#include <Shader.h>
#include <Texture.h>
#include <Vertex.h>
#include <pch.h>

/**
 * @class Mesh
 * @brief A class representing a mesh in a 3D model.
 */
class Mesh {
public:
    unsigned int            numVertices; ///< Number of vertices in the mesh
    std::shared_ptr<Vertex> vertices; ///< Pointer to the vertices of the mesh
    std::string             name; ///< Name of the mesh

    unsigned int                  numIndexes; ///< Number of indices in the mesh
    std::shared_ptr<unsigned int> indices; ///< Pointer to the indices of the mesh
    std::vector<Texture>          textures; ///< Textures associated with the mesh
    unsigned int                  VAO; ///< Vertex Array Object for the mesh

    /**
     * @brief Constructor for the Mesh class.
     * @param name Name of the mesh.
     * @param vertices Vector of vertices.
     * @param indices Vector of indices.
     * @param textures Vector of textures.
     */
    Mesh(const std::string &name, const std::vector<Vertex> &vertices,
         const std::vector<unsigned int> &indices, const std::vector<Texture> &textures);

    /**
     * @brief Constructor for the Mesh class.
     * @param name Name of the mesh.
     * @param numVertices Number of vertices.
     * @param vertices Shared pointer to the vertices.
     * @param numIndexes Number of indices.
     * @param indices Shared pointer to the indices.
     * @param textures Vector of textures.
     */
    Mesh(const std::string &name, unsigned int numVertices, const std::shared_ptr<Vertex> &vertices,
         unsigned int numIndexes, const std::shared_ptr<unsigned int> &indices,
         const std::vector<Texture> &textures);

    /**
     * @brief Draw the mesh.
     * @param shader Shader to use for drawing.
     */
    void Draw(const Shader &shader) const;

private:
    unsigned int VBO; ///< Vertex Buffer Object for the mesh
    unsigned int EBO; ///< Element Buffer Object for the mesh

    /**
     * @brief Set up the mesh.
     */
    void setupMesh();
};

#endif // MESH_H
