//
// Created by mavri on 23.12.2024.
//

#ifndef TEXTURE_H
#define TEXTURE_H

/**
 * @struct Texture
 * @brief A structure representing a texture in a 3D model.
 */
struct Texture {
    unsigned int id; ///< ID of the texture
    std::string  type; ///< Type of the texture (e.g., diffuse, specular)
    std::string  path; ///< Path to the texture file
};

#endif // TEXTURE_H
