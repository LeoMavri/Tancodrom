//
// Created by mavri on 16.12.2024.
//

#ifndef PCH_H
#define PCH_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

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

#endif //PCH_H
