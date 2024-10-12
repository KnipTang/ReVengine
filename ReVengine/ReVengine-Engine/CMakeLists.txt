add_library(ReVengine-Engine "ReVengine.cpp" "DirectX11/RenderWindow.cpp" "DirectX11/WindowHandler.h" "DirectX11/WindowHandler.cpp") #No need to add header files

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



# Define the resource directory
set(RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")
set(DIRECTX11_DIR "${CMAKE_CURRENT_SOURCE_DIR}/DirectX11")

# Copy the resources folder to the build directory
add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${RESOURCES_DIR}"
        "${CMAKE_BINARY_DIR}/resources"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${DIRECTX11_DIR}"
        "${CMAKE_BINARY_DIR}/DirectX11"
    COMMENT "Copying resources to build directory"
)

# Ensure the resources are copied before the actual build starts
add_dependencies(ReVengine-Engine copy_resources)


# Define the directories for shaders
set(SHADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
set(SHADERS_OUT_DIR "${CMAKE_BINARY_DIR}/shaders")

# List all your HLSL shaders
set(SHADERS
    ${SHADERS_DIR}/shader.hlsl
)

# Ensure the output directory for shaders exists
file(MAKE_DIRECTORY "${SHADERS_OUT_DIR}")

# Function to compile HLSL shaders
function(compile_shader INPUT_SHADER OUTPUT_SHADER PROFILE)
    add_custom_command(
        OUTPUT ${OUTPUT_SHADER}
        COMMAND fxc.exe /T ${PROFILE} /Fo ${OUTPUT_SHADER} ${INPUT_SHADER}
        DEPENDS ${INPUT_SHADER}
        COMMENT "Compiling HLSL shader ${INPUT_SHADER} to ${OUTPUT_SHADER}"
    )
endfunction()

# Iterate over the shaders and set up compile commands
foreach(SHADER ${SHADERS})
    get_filename_component(SHADER_NAME ${SHADER} NAME_WE)  # Get shader name without extension

    
    # Compile vertex and pixel shaders
    compile_shader(${SHADER} ${SHADERS_OUT_DIR}/${SHADER_NAME}.cso vs_5_0)  # For vertex shaders
   # compile_shader(${SHADER} ${SHADERS_OUT_DIR}/${SHADER_NAME}.cso ps_5_0)  # For pixel shaders

    # Optionally add more for other shader types (geometry, hull, etc.)
endforeach()

# Add a custom target to compile all shaders
add_custom_target(compile_shaders ALL DEPENDS ${SHADERS_OUT_DIR})

add_dependencies(ReVengine-Engine compile_shaders)