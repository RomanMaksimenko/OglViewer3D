add_library(Math)

set(MATH_PRIVATE_SOURCES
    "AxisAlignedBoundedBox.cpp"    
    "Matrix.cpp"
    "MathUtils.cpp"
    "Vector3f.cpp"
)

set(MATH_PUBLIC_HEADERS
    "AxisAlignedBoundedBox.h"
    "Matrix.h"
    "MathUtils.h"
    "Vector3f.h"
    "Vertex.h"
)

target_sources(Math PRIVATE
    ${MATH_PRIVATE_SOURCES}
    PUBLIC
    ${MATH_PUBLIC_HEADERS})

target_include_directories(Math PUBLIC
    ${CMAKE_SOURCE_DIR}/Source
)

# target Math зависит от Core
target_link_libraries(Math PRIVATE Core)