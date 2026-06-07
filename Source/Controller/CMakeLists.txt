add_library(Controller)

set(CONTROLLER_PRIVATE_SOURCES
    "ViewerController.cpp"
    "ModelService/ModelService.cpp"
)

set(CONTROLLER_PUBLIC_HEADERS
    "IViewObserver.h"
    "IModelProvider.h"
    "ViewerController.h"
    "IModelService.h"
)

target_sources(Controller PRIVATE
  ${CONTROLLER_PRIVATE_SOURCES}
  PUBLIC
  ${CONTROLLER_PUBLIC_HEADERS}
)

target_link_libraries(Controller PUBLIC Math)

target_include_directories(Controller PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)