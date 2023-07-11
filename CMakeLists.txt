cmake_minimum_required(VERSION 3.14)

project(server LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR};${CMAKE_MODULE_PATH}")

set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS         ON)  # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network)

find_package(Boost 1.82.0 REQUIRED)

add_executable(${PROJECT_NAME} main.cpp server_base.cpp server_base.h)

if(Boost_FOUND)
    target_include_directories(${PROJECT_NAME} PRIVATE ${boost_INCLUDE_DIRS})
    target_link_libraries(server ${Boost_LIBRARIES})
    include_directories(${Boost_INCLUDE_DIRS})
endif()

target_link_libraries(server Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(server Qt${QT_VERSION_MAJOR}::Network)
target_link_libraries(server ${Boost_LIBRARIES})

install(TARGETS server
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
