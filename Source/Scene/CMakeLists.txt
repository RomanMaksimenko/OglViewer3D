add_library(Scene)

set(SCENE_PRIVATE_SOURCES 
  "Scene.cpp"
  "ProjectionParams.cpp"
  "Camera/Camera.cpp"
  "Frustum/Plane.cpp"
  "Frustum/Frustum.cpp")  

set(SCENE_PUBLIC_HEADERS
  "Scene.h")
set(SCENE_PRIVATE_HEADERS
  "Frustum/Plane.h"
  "Frustum/Frustum.h")

target_sources(Scene PRIVATE
  ${SCENE_PRIVATE_SOURCES}
  ${SCENE_PRIVATE_HEADERS}
  PUBLIC
  ${SCENE_PUBLIC_HEADERS}
 )

 target_include_directories(Scene PUBLIC
   ${CMAKE_SOURCE_DIR}/Source
)

target_link_libraries(Scene PRIVATE Core Math)