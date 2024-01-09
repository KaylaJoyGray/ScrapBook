cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_CPPCHECK "cppcheck")
#set(CMAKE_CXX_FLAGS "-pg")

project(tile_engine VERSION 0.1)

# Add SDL2 CMake files
# https://github.com/aminosbh/sdl2-cmake-modules/blob/master/README.md
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED SDL_image)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

include_directories(
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_SOURCE_DIR}/SDL/include
	${PROJECT_SOURCE_DIR}/SDL/src
)

file(GLOB tile_engine_files
	"${PROJECT_SOURCE_DIR}/include/*.hpp"
	"${PROJECT_SOURCE_DIR}/SDL/include/*.hpp"
	"${PROJECT_SOURCE_DIR}/src/*.cpp"
	"${PROJECT_SOURCE_DIR}/SDL/src/*.cpp"
)

add_executable(main main.cpp ${tile_engine_files})

target_link_libraries(main SDL2::Main ${SDL2IMAGE_LIBRARIES} SDL2::Image)
