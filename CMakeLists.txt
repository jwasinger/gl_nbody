CMAKE_MINIMUM_REQUIRED		(VERSION 2.8)
CMAKE_POLICY				(SET CMP0002 OLD)


PROJECT 					(gl_nbody)

INCLUDE 					(FindPkgConfig)
FIND_PACKAGE				(OpenGL REQUIRED)
PKG_SEARCH_MODULE 			(SDL2 REQUIRED sdl2)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS}
					${OPENGL_INCLUDE_DIRS}
					${PROJECT_SOURCE_DIR}/include)


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

FILE(GLOB gl_nbody_SRC 
	"src/*.cpp"	
)

FILE(GLOB gl_nbody_HEADERS
	"include/*.h"
)

add_executable(gl_nbody ${gl_nbody_SRC} ${gl_nbody_HEADERS})

TARGET_LINK_LIBRARIES(	gl_nbody 
						${SDL2_LIBRARIES}
					    ${OPENGL_LIBRARIES})

#add_subdirectory("src")
#add_subdirectory("include")



#file(GLOB gl_nbody_HEADERS "include/*.h")
#add_executable(gl_nbody ${gl_nbody_HEADERS})

#ADD_EXECUTABLE(gl_nbody src/main.cpp)


