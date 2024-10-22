set(TARGET_NAMES ex_Raylib_imgui )

project(${TARGET_NAMES})
file(GLOB_RECURSE TARGET_SOURCES CONFIGURE_DEPENDS *.cpp *.h)
make_directory(${CMAKE_CURRENT_SOURCE_DIR}/imgui)
file(GLOB files_to_copy "${CMAKE_SOURCE_DIR}/sources/imgui/*")
file(COPY ${files_to_copy} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_SOURCES})
add_executable(${TARGET_NAMES})
target_link_libraries(${TARGET_NAMES} PRIVATE raylib)
target_include_directories(${TARGET_NAMES} PRIVATE  ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(${TARGET_NAMES} PRIVATE ${TARGET_SOURCES})

list(APPEND EXECUTABLES ${TARGET_NAMES})
set(EXECUTABLES "${EXECUTABLES}" CACHE INTERNAL "")