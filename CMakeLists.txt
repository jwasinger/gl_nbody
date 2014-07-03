CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(SET CMP0002 OLD)

PROJECT(gl_nbody C CXX)

ADD_EXECUTABLE(gl_nbody src/main.cpp)
set_target_properties(gl_nbody PROPERTIES LINKER_LANGUAGE CXX)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(gl_nbody ${SDL2_LIBRARIES})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries(gl_nbody ${OPENGL_LIBRARIES})

add_subdirectory("src")
include_directories(${PROJECT_SOURCE_DIR}/include)


