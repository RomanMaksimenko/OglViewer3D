add_library(UI)

set(UI_PRIVATE_SOURCES
    "ControlButtonsView/ControlButtonsView.cpp"
    "RenderView/RenderView.cpp"
    "ViewMainWindow/ViewMainWindow.cpp"
    "ViewFactory/ViewFactory.cpp"
)
set(UI_PUBLIC_HEADERS
    "IControlButtonsView.h"
    "IRenderView.h"
    "ViewFactory/ViewFactory.h"
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
target_link_libraries(UI PUBLIC Qt6::Core Qt6::Widgets Qt6::OpenGLWidgets OpenGL::GL
                         PRIVATE Qt6::Gui)



