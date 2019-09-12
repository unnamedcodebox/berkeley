project(server_core)

file(GLOB PROJECT_SOURCES
    "*.h"
    "*.cpp"
)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} halifax)
