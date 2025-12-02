cmake_minimum_required(VERSION 3.10)
project(vsomeip_demo)

set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig REQUIRED)
pkg_check_modules(VSOMEIP REQUIRED vsomeip3)

include_directories(${VSOMEIP_INCLUDE_DIRS})
link_directories(${VSOMEIP_LIBRARY_DIRS})

add_executable(service src/service.cpp)
target_link_libraries(service ${VSOMEIP_LIBRARIES})

add_executable(client src/client.cpp)
target_link_libraries(client ${VSOMEIP_LIBRARIES})
