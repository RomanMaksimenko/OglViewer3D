add_library(Model)

target_sources(Model PRIVATE
    Model.cpp
)

target_include_directories(Model PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}
)