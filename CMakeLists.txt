cmake_minimum_required(VERSION 3.20)
project(beta_ajedrez)

set(CMAKE_CXX_STANDARD 14)

set(SFML_ROOT "C:/SFML/v32/SFML-2.5.1")
set(SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)

# Buscar un nuevo paquete
find_package(SFML COMPONENTS graphics audio REQUIRED)

add_executable(beta_ajedrez main.cpp)

target_link_libraries(beta_ajedrez sfml-graphics sfml-audio)