project(berkeley_server_tests)

file(GLOB PROJECT_SOURCES
    "*.h"
    "*.cpp"
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
#include_directories(../src)
target_link_libraries(${PROJECT_NAME} pthread gtest halifax server_core)
