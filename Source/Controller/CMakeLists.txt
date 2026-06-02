add_library(Controller)

target_sources(Controller PRIVATE
  Controller.cpp
)

target_include_directories(Controller PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)