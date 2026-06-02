add_library(Document)

target_sources(Document PRIVATE
    Document.cpp
)

target_include_directories(Document PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)