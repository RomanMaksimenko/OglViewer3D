add_library(Graphics)

set(GRAPHICS_PRIVATE_SOURCES 
  "Image.cpp")  

set(GRAPHICS_PUBLIC_HEADERS
  "Image.h")

target_sources(Graphics PRIVATE
  ${GRAPHICS_PRIVATE_SOURCES}
  PUBLIC
  ${GRAPHICS_PUBLIC_HEADERS}
 )

 target_include_directories(Graphics PUBLIC
   ${CMAKE_SOURCE_DIR}/Source
)

target_link_libraries(Graphics PUBLIC stb_image)