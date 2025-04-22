cmake_minimum_required(VERSION 4.0.0)
project(game-of-life)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "/usr/lib/cmake/SFML")
find_package(SFML 3.0 COMPONENTS Graphics Window System REQUIRED)

set(SOURCE_FILES 
	src/main.cpp
	src/globals.cpp
	src/renderer.cpp
	src/grid.cpp)

include_directories(include)

add_executable(game ${SOURCE_FILES})

target_link_libraries(game PRIVATE
	
    /usr/lib/libsfml-graphics.so
    /usr/lib/libsfml-window.so
    /usr/lib/libsfml-system.so
	-Wall -Wextra -O7
)

