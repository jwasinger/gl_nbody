CMAKE_MINIMUM_REQUIRED		(VERSION 2.8)
CMAKE_POLICY				(SET CMP0002 OLD)


PROJECT 					(gl_nbody)

INCLUDE 					(FindPkgConfig)
PKG_SEARCH_MODULE 			(SDL2 REQUIRED sdl2)

FIND_PACKAGE				(OpenGL REQUIRED)

SET(LIB_GLEW 			${PROJECT_SOURCE_DIR}/external_libs/glew-1.10.0/lib/libGLEW.so.1.10.0)
SET(GLEW_INCLUDE_DIR 	${PROJECT_SOURCE_DIR}/external_libs/glew-1.10.0/include/GL)

INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIR}
					${SDL2_INCLUDE_DIRS}
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
						${LIB_GLEW}
						${SDL2_LIBRARIES}
					    ${OPENGL_LIBRARIES})


