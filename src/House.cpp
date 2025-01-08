//
// Created by mavri on 08 Jan 2025.
//

#include "House.h"

House::House(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation,
             GLFWwindow *window, Camera *pCamera) :
    Entity(position, size, rotation, "house", window, pCamera) {

    static Model *cachedModel = nullptr;
    if (!cachedModel) {
        cachedModel = new Model("../models/House/house_damaged.obj", false);
    }

    m_Model = std::make_unique<Model>(*cachedModel);
}

void House::Update(float DeltaTime) {
    // nothing, it's a house :p
}
