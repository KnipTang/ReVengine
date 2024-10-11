add_executable(ReVengine-Game WIN32 "Game.cpp") #No need to add header files

target_link_libraries(ReVengine-Game ReVengine-Engine) #links Game to Engine lib(dll)