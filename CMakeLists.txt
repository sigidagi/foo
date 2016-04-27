cmake_minimum_required(VERSION 2.6)

project(fooLua)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_CXX_FLAGS "-g --std=c++14 ")
find_package(Lua)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${LUA_INCLUDE_DIR}
    )

link_directories(${CMAKE_BINARY_DIR}/lib)

set(FOO_SOURCE
    src/main.cpp
)

add_executable(${PROJECT_NAME}  ${FOO_SOURCE})
target_link_libraries(${PROJECT_NAME} 
    ${LUA_LIBRARIES}
    dl
)

set(CMAKE_INSTALL_PREFIX "/usr")

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        )
