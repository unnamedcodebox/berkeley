project(berkeley_server)

file(GLOB PROJECT_SOURCES
    "*.h"
    "*.cpp"
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} halifax server_core)
