add_library(Scene)

set(SCENE_PRIVATE_SOURCES 
 "Scene.cpp")

set(SCENE_PUBLIC_HEADERS
  "Scene.h")

target_sources(Scene PRIVATE
  ${SCENE_PRIVATE_SOURCES}
  PUBLIC
  ${SCENE_PUBLIC_HEADERS}
 )

 target_include_directories(Scene PUBLIC
   ${CMAKE_SOURCE_DIR}/Source
)

target_link_libraries(Scene PRIVATE Core Math)