add_library(ReVengine-Engine
    "ReVengine.cpp"
    "DirectX11/RenderWindow.cpp"
    "DirectX11/WindowHandler.h"
    "DirectX11/WindowHandler.cpp") #No need to add header files

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
set(DIRECTX11_DIR "${CMAKE_CURRENT_SOURCE_DIR}/DirectX11")

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${RESOURCES_DIR}"
        "${CMAKE_BINARY_DIR}/resources"
    COMMENT "Copying resources to build directory"
)

# add this as a dependency to the engine
add_dependencies(ReVengine-Engine copy_resources)

set(SHADERS_DIR "${DIRECTX11_DIR}/shaders")
set(SHADERS_OUT_DIR "${CMAKE_BINARY_DIR}/DirectX11/shaders")

# make shader output dir
file(MAKE_DIRECTORY "${SHADERS_OUT_DIR}")

function(compile_shader IN_FILE OUT_FILE PROFILE ENTRY COMPILED_SHADER_FILES)
    add_custom_command(
        OUTPUT ${OUT_FILE}
        COMMAND fxc.exe /T ${PROFILE} /E ${ENTRY} /Fo ${OUT_FILE} ${IN_FILE}
        DEPENDS ${IN_FILE}
        VERBATIM
    )
     
    list(APPEND COMPILED_SHADER_FILES ${OUT_FILE})

    set(${COMPILED_SHADER_FILES} "${${COMPILED_SHADER_FILES}}" PARENT_SCOPE)
endfunction()

foreach(FILE ${SHADERS_DIR}/shader.hlsl)
    get_filename_component(SHADER_NAME ${FILE} NAME_WE) # get shader name without extension
    
    compile_shader(${FILE} ${SHADERS_OUT_DIR}/${SHADER_NAME}_v.cso vs_5_0 vs_main COMPILED_SHADER_FILES)
    compile_shader(${FILE} ${SHADERS_OUT_DIR}/${SHADER_NAME}_p.cso ps_5_0 ps_main COMPILED_SHADER_FILES)

endforeach()

message("Adding CUSTOM TARGET on ${COMPILED_SHADER_FILES}")

add_custom_target(compile_shaders DEPENDS ${COMPILED_SHADER_FILES})
add_dependencies(ReVengine-Engine compile_shaders)