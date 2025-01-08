//
// Created by mavri on 06 Jan 2025.
//

#include "Terrain.h"
Terrain::Terrain(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation,
                 const std::string &name, GLFWwindow *window, Camera *pCamera) :
    Entity(position, size, rotation, name, window, pCamera) {
    m_Model = std::make_unique<Model>("../models/Terrain/Grass.obj", true);
}

void Terrain::Update(const float DeltaTime) {
    // todo
}
