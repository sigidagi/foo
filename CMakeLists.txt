cmake_minimum_required(VERSION 2.6)

project(fooAlive)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_CXX_FLAGS "-g --std=c++11 ")

#set(CMAKE_EXE_LINKER_FLAGS "-Wl, -E ")
#find_package(Lua)

find_package(ZMQ 4.1.0)
if (NOT ZMQ_FOUND)
message(FATAL_ERROR "ZMQ verion 4.1.0 not found! ...download zmq from:
        http://download.zeromq.org/zeromq-4.1.0-rc1.tar.gz")
endif()

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    )

link_directories(${CMAKE_BINARY_DIR}/lib)

set(FOO_SOURCE
    src/main.cpp
)

add_executable(${PROJECT_NAME}  ${FOO_SOURCE})
target_link_libraries(${PROJECT_NAME}
        zmq
    )

set(CMAKE_INSTALL_PREFIX "/usr")

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        )
