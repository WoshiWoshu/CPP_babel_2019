project(babel)
cmake_minimum_required(VERSION 2.8.12)
add_definitions("-fPIC")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5 COMPONENTS Network REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)
find_package(Boost 1.55.0 REQUIRED COMPONENTS system filesystem)

include_directories(${CMAKE_INCLUDE_PATH})
add_executable(babel_server
    server/include/Database.hpp
    server/src/Database.cpp
    server/include/Profile.hpp
    server/src/Profile.cpp
    server/include/request.hpp
    server/include/Server.hpp
    server/src/Server.cpp
    server/src/main.cpp
)
add_executable(babel_client
    client/inc/WConnection.hpp
    client/src/WConnection.cpp
    client/inc/WServer.hpp
    client/src/WServer.cpp
    client/inc/MyTcpSocket.hpp
    client/src/MyTcpSocket.cpp
    client/inc/Client.hpp
    client/src/Client.cpp
    client/inc/Friend.hpp
    client/src/Friend.cpp
    client/inc/Calling.hpp
    client/src/Calling.cpp
    client/inc/RecvCall.hpp
    client/src/RecvCall.cpp
    client/inc/Record.hpp
    client/src/Record.cpp
    client/inc/request.hpp
    client/src/main.cpp
)


target_link_libraries(babel_server ${CONAN_LIBS} Qt5::Widgets Qt5::Network ${Boost_LIBRARIES})
target_link_libraries(babel_client ${CONAN_LIBS} Qt5::Widgets Qt5::Network ${Boost_LIBRARIES})
