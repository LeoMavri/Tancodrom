//
// Created by mavri on 06 Jan 2025.
//

#ifndef TERRAIN_H
#define TERRAIN_H
#include "Entity.h"

class Terrain : public Entity {
public:
    Terrain(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation,
            const std::string &name, GLFWwindow *window, Camera *pCamera);
    ~Terrain() override = default;

    void Update() override;
};

#endif // TERRAIN_H
