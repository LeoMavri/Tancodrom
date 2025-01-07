#ifndef SHADER_H
#define SHADER_H

#include <pch.h>

/**
 * @class Shader
 * @brief A class for handling OpenGL shader programs.
 */
class Shader {
public:
    /**
     * @brief Constructor for the Shader class.
     * @param vertexPath Path to the vertex shader source file.
     * @param fragmentPath Path to the fragment shader source file.
     */
    Shader(const std::string_view &vertexPath, const std::string_view &fragmentPath);

    /**
     * @brief Destructor for the Shader class.
     */
    ~Shader();

    /**
     * @brief Use the shader program.
     */
    void Use() const;

    /**
     * @brief Get the ID of the shader program.
     * @return The ID of the shader program.
     */
    [[nodiscard]] unsigned int GetID() const;

    unsigned int loc_model_matrix; ///< Location of the model matrix uniform
    unsigned int loc_view_matrix; ///< Location of the view matrix uniform
    unsigned int loc_projection_matrix; ///< Location of the projection matrix uniform

    /**
     * @brief Set an integer uniform in the shader.
     * @param name Name of the uniform.
     * @param value Value to set.
     */
    void SetInt(const std::string &name, int value) const;

    /**
     * @brief Set a float uniform in the shader.
     * @param name Name of the uniform.
     * @param value Value to set.
     */
    void SetFloat(const std::string &name, const float &value) const;

    /**
     * @brief Set a vec3 uniform in the shader.
     * @param name Name of the uniform.
     * @param value Value to set.
     */
    void SetVec3(const std::string &name, const glm::vec3 &value) const;

    /**
     * @brief Set a vec3 uniform in the shader.
     * @param name Name of the uniform.
     * @param x X component of the vec3.
     * @param y Y component of the vec3.
     * @param z Z component of the vec3.
     */
    void SetVec3(const std::string &name, float x, float y, float z) const;

    void SetVec4(const std::string &name, const glm::vec4 &value) const;

    void SetVec4(const std::string &name, float x, float y, float z, float w) const;

    /**
     * @brief Set a mat4 uniform in the shader.
     * @param name Name of the uniform.
     * @param mat Matrix to set.
     */
    void SetMat4(const std::string &name, const glm::mat4 &mat) const;

    // TODO: Make a getter / setter for this
    unsigned int ID; ///< ID of the shader program
private:
    /**
     * @brief Initialize the shader program.
     * @param vertexPath Path to the vertex shader source file.
     * @param fragmentPath Path to the fragment shader source file.
     */
    void Init(const std::string_view &vertexPath, const std::string_view &fragmentPath);

    /**
     * @brief Check for shader compilation or linking errors.
     * @param shader Shader ID.
     * @param type Type of shader (VERTEX, FRAGMENT, PROGRAM).
     */
    static void CheckCompileErrors(unsigned int shader, const std::string &type);
};

#endif // SHADER_H
