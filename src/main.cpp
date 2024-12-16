#include "../include/pch.h"

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
