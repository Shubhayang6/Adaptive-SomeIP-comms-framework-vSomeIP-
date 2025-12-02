cmake_minimum_required(VERSION 3.10)
project(autosar_adaptive_someip_demo)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(vsomeip3 REQUIRED)

include_directories(
    ${VSOMEIP_INCLUDE_DIRS}
)

add_executable(service src/service.cpp)
target_link_libraries(service vsomeip3)

add_executable(client src/client.cpp)
target_link_libraries(client vsomeip3)
