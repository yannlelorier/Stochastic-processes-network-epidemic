cmake_minimum_required(VERSION 3.1)

project(Stochastic_epidemic_simulation)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread -g -pedantic")

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

##set(CMAKE_BUILD_TYPE Debug)

#set(CMAKE_CXX_FLAGS "-std=c++11")

## Threads
find_package(Threads)

## In most cases better set in the CMake cache
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

## SFML
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(Stochastic_epidemic_simulation gillespie.cpp GraphViewer.cpp)
target_link_libraries(Stochastic_epidemic_simulation sfml-graphics sfml-window sfml-system ${CMAKE_THREAD_LIBS_INIT})
