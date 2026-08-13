add_library(Core)

set(CORE_PRIVATE_SOURCES
"RW/RWUtils.cpp"
"Exceptions/ApplicationException.cpp"
)
set(CORE_PUBLIC_HEADERS
"RW/RWUtils.h"
"Exceptions/ApplicationException.h"
"Exceptions/FileException.h"
"Exceptions/ShaderException.h"
)

target_sources(Core PRIVATE
  ${CORE_PRIVATE_SOURCES}
  PUBLIC
  ${CORE_PUBLIC_HEADERS}
 )

target_include_directories(Core PUBLIC
   ${CMAKE_SOURCE_DIR}/Source
)




