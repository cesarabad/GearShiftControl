cmake_minimum_required(VERSION 3.16)
project(GearShiftControl CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Incluye headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# Busca todos los .cpp
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/Src/*.cpp)

# Define el ejecutable en bin/program
add_executable(${PROJECT_SOURCE_DIR}/bin/program ${SOURCES})

# Bibliotecas necesarias
find_library(WIRINGPI_LIB wiringPi)
target_link_libraries(${PROJECT_SOURCE_DIR}/bin/program PRIVATE ${WIRINGPI_LIB} pthread)
