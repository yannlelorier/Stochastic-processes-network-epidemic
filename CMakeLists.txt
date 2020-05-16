cmake_minimum_required(VERSION 3.1)

project(covid-sim)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)
#set(CMAKE_CXX_FLAGS "-std=c++11")

## In most cases better set in the CMake cache
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(covid-sim test_tree.cpp GraphViewer.cpp)
target_link_libraries(covid-sim sfml-graphics sfml-window sfml-system)