cmake_minimum_required(VERSION 3.10)
project(RK)

set(CPACK_PACKAGE_NAME "RK")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Oleg Shatrov")
set(CPACK_GENERATOR DEB)
include(CPack)

add_subdirectory(class)
add_subdirectory(test)
add_subdirectory(third-party/gtest)
add_executable(main main.cpp)
target_link_libraries(main class)
