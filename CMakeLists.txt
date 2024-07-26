cmake_minimum_required(VERSION 3.0)

project(SLFG)

set(SFML_DIR "path/to/SFML/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

set(CMAKE_CXX_STANDARD 11)

add_executable(SLFG
        main.cpp
)

target_link_libraries(SLFG sfml-graphics sfml-audio)
