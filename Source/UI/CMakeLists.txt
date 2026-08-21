add_library(UI)

set(UI_PRIVATE_SOURCES
    "ErrorMSG/ErrorMSG.cpp"
    "ControlButtonsView/ControlButtonsView.cpp"
    "RenderView/RenderView.cpp"
    "RenderView/Mesh.cpp"
    "RenderView/Shader.cpp"
    "RenderView/ShaderProgram.cpp"
    "ViewMainWindow/ViewMainWindow.cpp"
    "ViewFactory/ViewFactory.cpp"
)
set(UI_PUBLIC_HEADERS
    "ErrorMSG/ErrorMSG.h"
    "IControlButtonsView.h"
    "IRenderView.h"
    "ViewFactory/ViewFactory.h"
    "IView.h"
    "VisibleRect.h"
)

target_sources(UI PRIVATE
  ${UI_PRIVATE_SOURCES}
  PUBLIC
  ${UI_PUBLIC_HEADERS}
 )

target_include_directories(UI PUBLIC
   ${CMAKE_SOURCE_DIR}/Source
)

# Системный путь к папке с шейдерами
target_compile_definitions(UI PRIVATE
    SHADER_DIR="${CMAKE_SOURCE_DIR}/Source/UI/OpenGL/Shaders"
)

# target UI зависит от Qt и OpenGL
target_link_libraries(UI PUBLIC Qt6::Core Qt6::Widgets Qt6::OpenGLWidgets OpenGL::GL
                         PRIVATE Qt6::Gui GLEW::GLEW)



