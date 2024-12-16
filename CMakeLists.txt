cmake_minimum_required(VERSION 3.30)

project(Tancodrom)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(CheckCXXCompilerFlag)

check_cxx_compiler_flag("-flto" COMPILER_SUPPORTS_FLTO)
if (COMPILER_SUPPORTS_FLTO)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -march=native -flto")
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -march=native")
endif ()

include(ProcessorCount)
ProcessorCount(N)
if (NOT N EQUAL 0)
    set(CMAKE_BUILD_PARALLEL_LEVEL ${N})
endif ()

find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    message(STATUS "Using ccache")
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif ()

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/*.h)

include_directories(include)

if (SOURCES)
    add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
else ()
    message(FATAL_ERROR "No source files found. Please check the 'src' directory.")
endif ()

target_precompile_headers(${PROJECT_NAME} PRIVATE include/pch.h)

include(FetchContent)

find_package(OpenGL REQUIRED)
message(STATUS "OpenGL found")

find_package(GLEW QUIET)
if (GLEW_FOUND)
    message(STATUS "GLEW found")
else ()
    message(STATUS "Fetching GLEW...")
    FetchContent_Declare(
            glew
            GIT_REPOSITORY https://github.com/nigels-com/glew.git
            GIT_TAG master
    )
    FetchContent_MakeAvailable(glew)
    set(GLEW_INCLUDE_DIRS ${glew_SOURCE_DIR}/include)
    set(GLEW_LIBRARIES ${glew_BINARY_DIR}/lib/libGLEW.so)
    add_library(GLEW::GLEW UNKNOWN IMPORTED)
    set_target_properties(GLEW::GLEW PROPERTIES
            IMPORTED_LOCATION ${GLEW_LIBRARIES}
            INTERFACE_INCLUDE_DIRECTORIES ${GLEW_INCLUDE_DIRS}
    )
endif ()

find_package(glfw3 QUIET)
if (glfw3_FOUND)
    message(STATUS "GLFW found")
else ()
    message(STATUS "Fetching GLFW...")
    FetchContent_Declare(
            glfw
            GIT_REPOSITORY https://github.com/glfw/glfw.git
            GIT_TAG latest
    )
    FetchContent_MakeAvailable(glfw)
    set(GLFW3_INCLUDE_DIRS ${glfw_SOURCE_DIR}/include)
    set(GLFW3_LIBRARIES ${glfw_BINARY_DIR}/src/libglfw3.a)
endif ()

find_package(glm QUIET)
if (glm_FOUND)
    message(STATUS "GLM found")
else ()
    message(STATUS "Fetching GLM...")
    FetchContent_Declare(
            glm
            GIT_REPOSITORY https://github.com/g-truc/glm.git
            GIT_TAG master
    )
    FetchContent_MakeAvailable(glm)
    set(GLM_INCLUDE_DIRS ${glm_SOURCE_DIR})
endif ()

include_directories(${GLEW_INCLUDE_DIRS} ${GLFW3_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} OpenGL::GL GLEW::GLEW ${GLFW3_LIBRARIES} glm)

if (WIN32)
    message(STATUS "Configuring for Windows")
    target_link_libraries(${PROJECT_NAME} glfw3dll)
elseif (UNIX)
    message(STATUS "Configuring for Linux")
    target_link_libraries(${PROJECT_NAME} pthread)
endif ()

add_definitions(-DSTB_IMAGE_IMPLEMENTATION)