#include <iostream>

#include <GL/glew.h>
#include <stb_image.h>

#define GLM_FORCE_CTOR_INIT

#ifdef _WIN32
#include <GLM.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <glfw3.h>
#else
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#endif

#ifdef _WIN32
#pragma comment (lib, "glfw3dll.lib")
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "OpenGL32.lib")
#endif

int main()
{
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
