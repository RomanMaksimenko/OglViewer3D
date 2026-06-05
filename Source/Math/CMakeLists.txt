add_library(Math)

set(MATH_PRIVATE_SOURCES
    "Math.cpp"
)

set(MATH_PUBLIC_HEADERS
    "Matrix.h"
)

target_sources(Math PRIVATE
    ${MATH_PRIVATE_SOURCES}
    PUBLIC
    ${MATH_PUBLIC_HEADERS})

target_include_directories(Math PUBLIC
    ${CMAKE_SOURCE_DIR}/Source
)