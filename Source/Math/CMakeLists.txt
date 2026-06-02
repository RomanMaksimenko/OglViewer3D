add_library(Math)

target_sources(Math PRIVATE
    Math.cpp
)

target_include_directories(Math PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)