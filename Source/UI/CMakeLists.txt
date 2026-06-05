add_library(UI)

target_sources(UI PRIVATE
  UI.cpp
)

target_include_directories(UI PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}
)

# target UI зависит от Qt и OpenGL
target_link_libraries(UI PUBLIC Qt6::Core Qt6::Widgets OpenGL::GL)



