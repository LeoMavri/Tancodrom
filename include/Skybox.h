//
// Created by mavri on 02 Jan 2025.
//

#ifndef SKYBOX_H
#define SKYBOX_H

#include <Shader.h>
#include <pch.h>

/**
 * @brief Class representing a skybox in a 3D scene.
 */
class Skybox {
public:
    /**
     * @brief Construct a new Skybox object.
     * @param faces Vector of file paths to the six faces of the cubemap texture.
     */
    explicit Skybox(const std::vector<std::string> &faces);

    /**
     * @brief Draw the skybox.
     * @param view View matrix.
     * @param projection Projection matrix.
     */
    void Draw(const glm::mat4 &view, const glm::mat4 &projection) const;

    /**
     * @brief Set the hue of the skybox.
     * @param hue Hue value to set.
     */
    void SetSkyboxHue(float hue) const;

private:
    /**
     * @brief Load the cubemap texture from the given faces.
     * @param faces Vector of file paths to the six faces of the cubemap texture.
     */
    void LoadCubemap(const std::vector<std::string> &faces);

    /**
     * @brief Setup the skybox vertex data and buffers.
     */
    void SetupSkybox();

    Shader m_Shader; ///< Shader used to render the skybox.
    GLuint m_SkyboxVAO{}; ///< Vertex Array Object for the skybox.
    GLuint m_SkyboxVBO{}; ///< Vertex Buffer Object for the skybox.
    GLuint m_CubemapTexture{}; ///< Texture ID for the cubemap.
};

#endif // SKYBOX_H
