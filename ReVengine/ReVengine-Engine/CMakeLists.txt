add_library(ReVengine-Engine "ReVengine.cpp") #No need to add header files

target_include_directories(ReVengine-Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) #adds current dir of this file to include path of engine dir, Public so everyone that links with this can access there files lol

