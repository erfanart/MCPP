cmake_minimum_required(VERSION 3.16)
project(MCPP LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_library(mcpp
    src/server.cc
    src/stdio_transport.cc
    src/rpc.cc
    src/schema.cc
)
target_include_directories(mcpp PUBLIC include)

# find_package(nlohmann_json REQUIRED)
# target_link_libraries(mcpp PUBLIC nlohmann_json::nlohmann_json)
add_executable(mcpp-iot examples/iot_server/main.cc)
target_link_libraries(mcpp-iot PRIVATE mcpp)
