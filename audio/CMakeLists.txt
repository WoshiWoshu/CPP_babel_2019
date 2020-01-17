project(Babel)
cmake_minimum_required(VERSION 2.8.12)
add_definitions("-fPIC")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
set(CMAKE_CXX_FLAGS "-g3")

find_package(Qt5Widgets CONFIG REQUIRED)

include_directories(${CMAKE_INCLUDE_PATH})
add_executable(babel
    Record.cpp
    Record.hpp
    main.cpp
)
target_link_libraries(babel ${CONAN_LIBS} Qt5::Widgets)
