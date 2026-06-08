add_library(Model)

set(MODEL_PRIVATE_SOURCES
    "Serializer/ModelSerializer.cpp"
)

set(MODEL_PUBLIC_HEADERS
   "IModel.h"
   "IModelSerializer.h"
   "Creator.h"
)

target_sources(Model PRIVATE
     ${MODEL_PRIVATE_SOURCES}
     PUBLIC
     ${MODEL_PUBLIC_HEADERS}
 )

target_include_directories(Model PUBLIC
   ${CMAKE_SOURCE_DIR}/Source
)