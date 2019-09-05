project(berkeley_server)

file(GLOB PROJECT_SOURCES
    "*.h"
    "*.cpp"
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} gtest gmock)
