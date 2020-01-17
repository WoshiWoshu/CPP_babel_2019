project(babel_client)
cmake_minimum_required(VERSION 2.8.12)
add_definitions("-fPIC")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_FLAGS "-I ./inc")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5 COMPONENTS Network REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)

include_directories(${CMAKE_INCLUDE_PATH})
add_executable(babel_client
    inc/WConnection.hpp
    src/WConnection.cpp
    inc/WServer.hpp
    src/WServer.cpp
    inc/MyTcpSocket.hpp
    src/MyTcpSocket.cpp
    inc/Client.hpp
    src/Client.cpp
    inc/Friend.hpp
    src/Friend.cpp
    inc/Calling.hpp
    src/Calling.cpp
    inc/RecvCall.hpp
    src/RecvCall.cpp
    inc/Record.hpp
    src/Record.cpp
    inc/request.hpp
    src/main.cpp
)
target_link_libraries(babel_client ${CONAN_LIBS} Qt5::Widgets Qt5::Network)
