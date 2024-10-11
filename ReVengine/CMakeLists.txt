cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

project ("ReVengine")

include(FetchContent)

find_library(D3D11_LIBRARY d3d11.lib     PATHS     "$ENV{DXSDK_DIR}/Lib/x86" "C:/Program Files (x86)/Microsoft DirectX SDK/Lib/x86"     DOC "The directory where d3d11.lib resides")  
find_library(D3DX11_LIBRARY d3dx11.lib     PATHS     "$ENV{DXSDK_DIR}/Lib/x86" "C:/Program Files (x86)/Microsoft DirectX SDK/Lib/x86"     DOC "The directory where d3dx11.lib resides") 

# Download and configure SDL2
FetchContent_Declare(
  SDL2
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG release-2.30.8 #To get specific version of SDL
  OVERRIDE_FIND_PACKAGE
)

FetchContent_MakeAvailable(SDL2)

FetchContent_Declare(
  soLoud
  GIT_REPOSITORY https://git.allpurposem.at/mat/SoLoud-CMake.git
  #SOURCE_SUBDIR contrib #Because the main cmakeList file isnt in the main dir
)

FetchContent_MakeAvailable(soLoud)

set(SOLOUD_BACKEND_SDL2 OFF) #disable soloud_backend_sdl2

add_subdirectory ("ReVengine-Engine")
add_subdirectory ("ReVengine-Game")