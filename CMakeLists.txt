cmake_minimum_required(VERSION 3.12)
project(TetrisOpenGL VERSION 1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Change path from /src if needed, or add more directories
file(GLOB_RECURSE sources
        "${CMAKE_SOURCE_DIR}/src/*.c"
        "${CMAKE_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_SOURCE_DIR}/src/rendering/*.cpp"
        )

# Añade el archivo fuente principal
add_executable(TetrisOpenGL ${sources})

# Añade el directorio de inclusión "include" al proyecto
target_include_directories(TetrisOpenGL PUBLIC ${CMAKE_SOURCE_DIR})

find_package(glfw3 REQUIRED)

target_link_libraries(TetrisOpenGL PRIVATE glfw)

