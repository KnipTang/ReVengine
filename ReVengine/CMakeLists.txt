cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 20)

project(ReVengine LANGUAGES C CXX)

include(FetchContent)

find_package(SDL2 CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(glm CONFIG REQUIRED)

FetchContent_Declare(
  soLoud
  GIT_REPOSITORY https://git.allpurposem.at/mat/SoLoud-CMake.git
)
FetchContent_MakeAvailable(soLoud)

add_subdirectory ("ReVengine-Engine")
add_subdirectory ("ReVengine-Game")