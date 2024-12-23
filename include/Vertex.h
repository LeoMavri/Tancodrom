//
// Created by mavri on 23.12.2024.
//

#ifndef VERTEX_H
#define VERTEX_H

#include <pch.h>

constexpr int MAX_BONE_INFLUENCE = 4;

/**
 * @struct Vertex
 * @brief A structure representing a vertex in a 3D model.
 */
struct Vertex {
    glm::vec3 Position; ///< Position of the vertex
    glm::vec3 Normal; ///< Normal vector of the vertex
    glm::vec2 TexCoords; ///< Texture coordinates of the vertex
    glm::vec3 Tangent; ///< Tangent vector of the vertex
    glm::vec3 Bitangent; ///< Bitangent vector of the vertex
    int       m_BoneIDs[MAX_BONE_INFLUENCE]; ///< IDs of the bones influencing the vertex
    float     m_Weights[MAX_BONE_INFLUENCE]; ///< Weights of the bones influencing the vertex
};

#endif // VERTEX_H
