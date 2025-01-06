//
// Created by mavri on 18.12.2024.
//

#ifndef MODEL_H
#define MODEL_H

#include <Mesh.h>
#include <Shader.h>
#include <Texture.h>
#include <pch.h>

/**
 * @brief Loads a texture from file.
 * @param path Path to the texture file.
 * @param directory Directory containing the texture file.
 * @param gamma Whether to apply gamma correction.
 * @return The ID of the loaded texture.
 */
unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

/**
 * @class Model
 * @brief A class that handles loading the model, the textures, and the shaders.
 */
class Model {
public:
    std::vector<Texture> textures_loaded; ///< Stores all the textures loaded so far, optimization
                                          ///< to make sure textures aren't loaded more than once.
    std::vector<Mesh> meshes; ///< Vector of meshes in the model.
    std::string       directory; ///< Directory containing the model files.
    bool              gammaCorrection; ///< Whether to apply gamma correction.

    /**
     * @brief Constructor for the Model class.
     * @param path Filepath to the 3D model.
     * @param bSmoothNormals Whether to smooth normals.
     * @param gamma Whether to apply gamma correction.
     */
    Model(std::string const &path, bool bSmoothNormals, bool gamma = false);

    /**
     * @brief Destructor for the Model class.
     */
    virtual ~Model() = default;

    /**
     * @brief Draws the model, and thus all its meshes.
     * @param shader Shader to use for drawing.
     */
    virtual void Draw(const Shader &shader);

    [[nodiscard]] unsigned int GetTextureID() const;

private:
    /**
     * @brief Loads a model with supported ASSIMP extensions from file and stores the resulting
     * meshes in the meshes vector.
     * @param path Filepath to the 3D model.
     * @param bSmoothNormals Whether to smooth normals.
     */
    void loadModel(std::string const &path, bool bSmoothNormals);

    /**
     * @brief Processes a node in a recursive fashion. Processes each individual mesh located at the
     * node and repeats this process on its children nodes (if any).
     * @param node Node to process.
     * @param scene Scene containing the node.
     */
    void processNode(const aiNode *node, const aiScene *scene);

    /**
     * @brief Processes a mesh.
     * @param nodeName Name of the node containing the mesh.
     * @param mesh Mesh to process.
     * @param scene Scene containing the mesh.
     * @return The processed mesh.
     */
    Mesh processMesh(const std::string &nodeName, const aiMesh *mesh, const aiScene *scene);

    /**
     * @brief Checks all material textures of a given type and loads the textures if they're not
     * loaded yet. The required info is returned as a Texture struct.
     * @param mat Material to check.
     * @param type Type of texture.
     * @param typeName Name of the texture type.
     * @return Vector of loaded textures.
     */
    std::vector<Texture> loadMaterialTextures(const aiMaterial *mat, const aiTextureType &type,
                                              const std::string &typeName);
};

#endif // MODEL_H
