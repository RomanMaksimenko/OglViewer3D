cmake_minimum_required(VERSION 3.29)

project(OGL3dViewer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Настройки Qt и OpenGL держать локально в UI, только target зависит от них
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(OpenGL REQUIRED)

add_subdirectory(Source)
add_subdirectory(Source/Controller)
add_subdirectory(Source/Document)
add_subdirectory(Source/Math)
add_subdirectory(Source/Model)
add_subdirectory(Source/UI)