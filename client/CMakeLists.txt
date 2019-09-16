project(berkeley_client)

file(GLOB PROJECT_SOURCES
    "*.h"
    "*.cpp"
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} halifax)
