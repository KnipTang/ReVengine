cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

project ("ReVengine"  LANGUAGES C CXX)

include(FetchContent)

find_library(D3D11_LIBRARY d3d11.lib     PATHS     "$ENV{DXSDK_DIR}/Lib/x86" "C:/Program Files (x86)/Microsoft DirectX SDK/Lib/x86"     DOC "The directory where d3d11.lib resides")  
find_library(D3DX11_LIBRARY d3dx11.lib     PATHS     "$ENV{DXSDK_DIR}/Lib/x86" "C:/Program Files (x86)/Microsoft DirectX SDK/Lib/x86"     DOC "The directory where d3dx11.lib resides") 

find_package(SDL2 CONFIG REQUIRED)

FetchContent_Declare(
  soLoud
  GIT_REPOSITORY https://git.allpurposem.at/mat/SoLoud-CMake.git
)

FetchContent_MakeAvailable(soLoud)

add_subdirectory ("ReVengine-Engine")
add_subdirectory ("ReVengine-Game")