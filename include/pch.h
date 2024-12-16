//
// Created by mavri on 16.12.2024.
//

#ifndef PCH_H
#define PCH_H

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <GL/glew.h>
#include "stb_image.h"

#define GLM_FORCE_CTOR_INIT

#ifdef _WIN32
#include <GLM.hpp>
#include <glfw3.h>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#else
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif

#endif // PCH_H
