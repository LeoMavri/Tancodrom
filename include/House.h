//
// Created by mavri on 08 Jan 2025.
//

#ifndef HOUSE_H
#define HOUSE_H
#include "Entity.h"

/**
 * @class House
 * @brief A class representing a house entity in a 3D environment.
 *
 * The House class inherits from the Entity class and represents a house in the game world.
 * It uses a cached model to optimize performance.
 */
class House final : public Entity {
public:
    /**
     * @brief Constructor for the House class.
     * @param position Initial position of the house.
     * @param size Size of the house.
     * @param rotation Initial rotation of the house.
     * @param window Pointer to the GLFW window.
     * @param pCamera Pointer to the camera.
     */
    House(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation,
          GLFWwindow *window, Camera *pCamera);

    /**
     * @brief Destructor for the House class.
     */
    ~House() override = default;

    /**
     * @brief Update the house entity.
     * @param DeltaTime Time elapsed since the last frame.
     */
    void Update(float DeltaTime) override;
};

#endif // HOUSE_H
