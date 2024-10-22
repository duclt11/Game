Set(FETCHCONTENT_QUIET FALSE)

set(dep raygui)
add_git_dependency(
    ${dep} 
    https://github.com/raysan5/raygui.git   
    4.0  
)

FetchContent_GetProperties(${dep})

set(dep tracy)
add_git_dependency(
    ${dep}
    https://github.com/wolfpld/tracy.git 
    v0.11.0 
)

FetchContent_GetProperties(${dep})
list(APPEND LIBRARIES Tracy::TracyClient)
#add new dependencies here
# raylib

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples

set(dep raylib)
add_git_dependency(
    ${dep}
    https://github.com/raysan5/raylib.git 
    5.0
)

FetchContent_GetProperties(${dep})
list(APPEND LIBRARIES ${dep})


set(dep catch2)
add_git_dependency(
    ${dep}
    https://github.com/catchorg/Catch2.git 
    v3.6.0
)
    
FetchContent_GetProperties(${dep})
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
list(APPEND LIBRARIES_FOR_TEST  Catch2 )
list(APPEND LIBRARIES_FOR_TEST  Catch2WithMain )

set(RAPIDJSON_BUILD_DOC CACHE INTERNAL "")
set(RAPIDJSON_BUILD_EXAMPLES CACHE INTERNAL "")
set(RAPIDJSON_BUILD_TESTS CACHE INTERNAL "")
set(RAPIDJSON_BUILD_THIRDPARTY_GTEST CACHE INTERNAL "")
set(dep rapidjson)
add_git_dependency(
    ${dep}
    https://github.com/Tencent/rapidjson.git  
    v1.1.0
)
    
FetchContent_GetProperties(${dep})

# imgui files

add_git_dependency(
    RlImGui
    https://github.com/raylib-extras/rlImGui.git
    head
)

file(REMOVE_RECURSE ${CMAKE_SOURCE_DIR}/libs/RlImGui/examples)

file(GLOB files_to_copy "${CMAKE_SOURCE_DIR}/libs/RlImGui/*")
file(COPY ${files_to_copy} DESTINATION ${CMAKE_SOURCE_DIR}/sources/imgui)



add_git_dependency(
    imgui
    https://github.com/ocornut/imgui.git
    head
)

file(REMOVE_RECURSE ${CMAKE_SOURCE_DIR}/libs/imgui/examples)
file(REMOVE_RECURSE ${CMAKE_SOURCE_DIR}/libs/imgui/misc)
file(REMOVE_RECURSE ${CMAKE_SOURCE_DIR}/libs/imgui/backends)
file(REMOVE_RECURSE ${CMAKE_SOURCE_DIR}/libs/imgui/.editorconfig)
file(REMOVE_RECURSE ${CMAKE_SOURCE_DIR}/libs/imgui/.github)
    
file(GLOB files_to_copy "${CMAKE_SOURCE_DIR}/libs/imgui/*")
file(COPY ${files_to_copy} DESTINATION ${CMAKE_SOURCE_DIR}/sources/imgui)


# ldtk loader
set(LDTK_BUILD_API_TEST OFF CACHE INTERNAL "")
set(LDTK_BUILD_SFML_EXAMPLE OFF CACHE INTERNAL "")
set(LDTK_BUILD_SDL_EXAMPLE OFF CACHE INTERNAL "" )
set(LDTK_BUILD_RAYLIB_EXAMPLE OFF CACHE INTERNAL "" )

set(dep LDtkLoader)
add_git_dependency(
    ${dep}
    https://github.com/Madour/LDtkLoader.git 
    1.5.3.1 
)
FetchContent_GetProperties(${dep})

# add the dependency here to be linked
list(APPEND LIBRARIES ${dep})

# box2d

set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE) # don't build the supplied examples

set(dep box2d)
add_git_dependency(
    ${dep}
    https://github.com/erincatto/box2d.git
    head
)

# add the dependency here to be linked
list(APPEND LIBRARIES ${dep})


set(dep raygui)
add_git_dependency(
    ${dep}
    https://github.com/raysan5/raygui.git 
    4.0 
)
FetchContent_GetProperties(${dep})
# jolt physics

set(DOUBLE_PRECISION OFF)
set(GENERATE_DEBUG_SYMBOLS ON)
set(CROSS_PLATFORM_DETERMINISTIC OFF)
set(INTERPROCEDURAL_OPTIMIZATION ON)
set(FLOATING_POINT_EXCEPTIONS_ENABLED OFF)
set(OBJECT_LAYER_BITS 16)
set(USE_SSE4_1 ON)
set(USE_SSE4_2 ON)
set(USE_AVX ON)
set(USE_AVX2 ON)
set(USE_AVX512 OFF)
set(USE_LZCNT ON)
set(USE_TZCNT ON)
set(USE_F16C ON)
set(USE_FMADD ON)


FetchContent_Declare(
        JoltPhysics
        GIT_REPOSITORY "https://github.com/jrouwe/JoltPhysics"
        GIT_TAG "v5.0.0"
        SOURCE_SUBDIR "Build"
    )
FetchContent_MakeAvailable(JoltPhysics)

set(CMAKE_EXE_LINKER_FLAGS_DISTRIBUTION "${CMAKE_EXE_LINKER_FLAGS_RELEASE}")
    
# add the dependency here to be linked
list(APPEND LIBRARIES Jolt)
