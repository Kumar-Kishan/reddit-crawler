cmake_minimum_required(VERSION 3.0.0)
project(crawler VERSION 0.0.1)

# Later for testing
# include(CTest)
# enable_testing()

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(opt/cpr)
add_subdirectory(opt/json)

include_directories("${CMAKE_SOURCE_DIR}/includes")
include_directories(${CPR_INCLUDE_DIRS})

file(GLOB SRC "src/*.cpp")


add_executable(crawler ${SRC})
target_link_libraries(crawler ${CPR_LIBRARIES})
target_link_libraries(crawler nlohmann_json::nlohmann_json)


set_target_properties(crawler
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)