add_library(ReVengine-Engine "ReVengine.cpp") #No need to add header files

target_include_directories(ReVengine-Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) #adds current dir of this file to include path of engine dir, Public so everyone that links with this can access there files lol

target_link_libraries(ReVengine-Engine PUBLIC soloud "${D3D11_LIBRARY}" "D3DX11_LIBRARY") #link soLoud to engine, name "soload" is the "target_name"
target_include_directories(ReVengine-Engine PUBLIC ${soloud_SOURCE_DIR}/include)

#target_link_libraries(${PROJECT_NAME} PUBLIC dxgi d3d11)
#target_link_libraries(ReVengine-Engine "${D3D11_LIBRARY}" "D3DX11_LIBRARY")

# Define the resource directory
set(RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")

# Copy the resources folder to the build directory
add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${RESOURCES_DIR}"
        "${CMAKE_BINARY_DIR}/resources"
    COMMENT "Copying resources to build directory"
)

# Ensure the resources are copied before the actual build starts
add_dependencies(ReVengine-Engine copy_resources)