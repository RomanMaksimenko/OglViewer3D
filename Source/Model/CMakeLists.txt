add_library(Model)

set(MODEL_PRIVATE_SOURCES
    "Model.cpp"
)

set(MODEL_PUBLIC_HEADERS
   "IModelSerializer.h"
   "IModelService.h"
)

target_sources(Model PRIVATE
     ${MODEL_PRIVATE_SOURCES}
     PUBLIC
     ${MODEL_PUBLIC_HEADERS}
 )

target_include_directories(Model PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}
)