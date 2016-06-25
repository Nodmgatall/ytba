
project(ytba)
cmake_minimum_required(VERSION 3.0)

file(GLOB_RECURSE sources src/*.cpp src/*.hpp)
add_definitions("-g -Wall -Wextra -pedantic -Werror -std=c++14 -Wno-unused-parameter")

include(FindPkgConfig)
pkg_check_modules(URHO3D REQUIRED Urho3D)

find_package(Threads)

MESSAGE(STATUS "------------------------> " ${URHO3D_INCLUDE_DIRS}) 
MESSAGE(STATUS "------------------------> " ${URHO3D_LIBRARIES})
MESSAGE(STATUS "------------------------> " ${URHO3D_LIBRARY_DIRS})

MESSAGE(STATUS "------------------------> " ${URHO3D_HOME}) 
set(ENTITYX_BUILD_TESTING false CACHE BOOL "")
add_subdirectory(entityx)
add_subdirectory(glm)
include_directories(SYSTEM
    ${URHO3D_INCLUDE_DIRS}
    entityx/
    src/)

link_directories(
    ${URHO3D_LIBRARY_DIRS})

add_executable(ytba ${sources})
target_link_libraries(ytba
    ${CMAKE_THREAD_LIBS_INIT}
    ${URHO3D_LIBRARIES}
    entityx)


