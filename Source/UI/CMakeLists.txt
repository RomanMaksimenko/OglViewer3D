add_library(UI)

set(UI_PRIVATE_SOURCES
    "ControlButtonsView/ControlButtonsView.cpp"
)
set(UI_PUBLIC_HEADERS
    "IControlButtonsView.h"
)

target_sources(UI PRIVATE
  ${UI_PRIVATE_SOURCES}
  PUBLIC
  ${UI_PUBLIC_HEADERS}
 )

target_include_directories(UI PUBLIC
   ${CMAKE_SOURCE_DIR}/Source
)

# target UI зависит от Qt и OpenGL
target_link_libraries(UI PUBLIC Qt6::Core Qt6::Widgets OpenGL::GL)



