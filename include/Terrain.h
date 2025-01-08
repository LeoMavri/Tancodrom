//
// Created by mavri on 06 Jan 2025.
//

#ifndef TERRAIN_H
#define TERRAIN_H
#include "Entity.h"

/**
 * @class Terrain
 * @brief Represents a terrain entity in the scene, inheriting from Entity.
 *
 * The Terrain class is responsible for representing and managing a terrain entity within the scene.
 * It inherits from the Entity class and provides specific functionality for terrain objects.
 */
class Terrain final : public Entity {
public:
    /**
     * @brief Constructs a Terrain object.
     * @param position The initial position of the terrain.
     * @param size The size of the terrain.
     * @param rotation The rotation of the terrain.
     * @param name The name of the terrain.
     * @param window The GLFW window associated with the terrain.
     * @param pCamera Pointer to the camera associated with the terrain.
     */
    Terrain(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation,
            const std::string &name, GLFWwindow *window, Camera *pCamera);

    /**
     * @brief Default destructor.
     */
    ~Terrain() override = default;

    /**
     * @brief Updates the terrain's state.
     * @param DeltaTime The time elapsed since the last update.
     */
    void Update(float DeltaTime) override;
};
#endif // TERRAIN_H
