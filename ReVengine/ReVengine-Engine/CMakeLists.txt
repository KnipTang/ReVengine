add_library(ReVengine-Engine
    "ReVengine.cpp"
    "Rev_CoreSystems.cpp"
    "Rendering/RenderWindow.cpp"
    "Rendering/Direct3D11/WindowHandler.cpp" 
    "Sound/Rev_Sound.cpp"
    "Sound/Rev_SoundImpl.cpp"
    "Sound/SoLoud/Rev_SoLoud.cpp"
) #No need to add header files

target_include_directories(ReVengine-Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) #adds current dir of this file to include path of engine dir, Public so everyone that links with this can access there files lol


#"${D3D11_LIBRARY}" "D3DX11_LIBRARY"
target_link_libraries(ReVengine-Engine PUBLIC 
    soloud 
    dxgi d3d11 
    SDL2::SDL2 SDL2::SDL2main
) #link libs to engine, name "soload" is the "target_name"

target_include_directories(ReVengine-Engine PUBLIC 
    ${soloud_SOURCE_DIR}/include
)


set(RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")

add_custom_target(copy_engine_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${RESOURCES_DIR}"
        "${CMAKE_BINARY_DIR}/engine_resources"
    COMMENT "Copying resources to build directory"
)

# add this as a dependency to the engine
add_dependencies(ReVengine-Engine copy_engine_resources)



set(DIRECTX11_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Rendering")

set(SHADERS_DIR "${DIRECTX11_DIR}/shaders")
set(SHADERS_OUT_DIR "${CMAKE_BINARY_DIR}/Rendering/shaders")

# make shader output dir
file(MAKE_DIRECTORY "${SHADERS_OUT_DIR}")

function(compile_shader IN_FILE OUT_FILE PROFILE ENTRY FILES_LIST)
    add_custom_command(
        OUTPUT ${OUT_FILE}
        COMMAND fxc.exe /T ${PROFILE} /E ${ENTRY} /Fo ${OUT_FILE} ${IN_FILE}
        DEPENDS ${IN_FILE}
        VERBATIM
    )
     
    list(APPEND ${FILES_LIST} ${OUT_FILE})

    set(${FILES_LIST} "${${FILES_LIST}}" PARENT_SCOPE)
endfunction()

#Compiling vertex shaders
foreach(FILE ${SHADERS_DIR}/VertexShader.hlsl)
    get_filename_component(SHADER_NAME ${FILE} NAME_WE) # get shader name without extension
    
    compile_shader(${FILE} ${SHADERS_OUT_DIR}/${SHADER_NAME}.cso vs_5_0 vs_main COMPILED_SHADER_FILES)
endforeach()

foreach(FILE ${SHADERS_DIR}/PixelShader.hlsl)
    get_filename_component(SHADER_NAME ${FILE} NAME_WE) # get shader name without extension
    
    compile_shader(${FILE} ${SHADERS_OUT_DIR}/${SHADER_NAME}.cso ps_5_0 ps_main COMPILED_SHADER_FILES)
endforeach()

message("Adding CUSTOM TARGET on ${COMPILED_SHADER_FILES}")

add_custom_target(compile_shaders DEPENDS ${COMPILED_SHADER_FILES})
add_dependencies(ReVengine-Engine compile_shaders)