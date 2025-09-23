cmake_minimum_required(VERSION 3.16)
project(GearShiftControl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Incluye tus headers
include_directories(include)

# Encuentra todos los .cpp en Src
file(GLOB_RECURSE SOURCES "Src/*.cpp")

# Define el ejecutable
add_executable(program ${SOURCES})

# Indica dónde se generará el ejecutable
set_target_properties(program PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

# Linkea las librerías necesarias
target_link_libraries(program pthread wiringPi)
