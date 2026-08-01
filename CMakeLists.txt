cmake_minimum_required(VERSION 3.29)

project(OGL3dViewer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Настройки Qt и OpenGL держать локально в UI, только target зависит от них
find_package(Qt6 REQUIRED COMPONENTS Core Widgets OpenGLWidgets Gui)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
message(STATUS "ENV CMAKE_PREFIX_PATH = $ENV{CMAKE_PREFIX_PATH}")
message(STATUS "CMAKE_PREFIX_PATH = ${CMAKE_PREFIX_PATH}")
message(STATUS "GLEW_FOUND        = ${GLEW_FOUND}")
message(STATUS "GLEW_INCLUDE_DIRS = ${GLEW_INCLUDE_DIRS}")
message(STATUS "GLEW_INCLUDE_DIR  = ${GLEW_INCLUDE_DIR}")
message(STATUS "GLEW_LIBRARIES    = ${GLEW_LIBRARIES}")
message(STATUS "GLEW_LIBRARY      = ${GLEW_LIBRARY}")
message(STATUS "GLEW_VERSION      = ${GLEW_VERSION}")

add_subdirectory(Source)
add_subdirectory(Source/Controller)
add_subdirectory(Source/Math)
add_subdirectory(Source/Model)
add_subdirectory(Source/UI)