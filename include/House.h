//
// Created by mavri on 08 Jan 2025.
//

#ifndef HOUSE_H
#define HOUSE_H
#include "Entity.h"

class House final : public Entity {
public:
    House(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation,
          GLFWwindow *window, Camera *pCamera);
    ~House() override = default;

    void Update(float DeltaTime) override;
};

#endif // HOUSE_H
