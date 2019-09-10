project(halifax)

set(CMAKE_CXX_STANDARD 17)

file(GLOB PROJECT_SOURCES
    "*.h"
    "*.cpp"
)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})
