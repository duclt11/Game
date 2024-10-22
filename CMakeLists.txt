cmake_minimum_required(VERSION 3.22)

project(GAME CXX)

set(CMAKE_CXX_STANDARD 17)

##########################################################################################
# project settings
##########################################################################################

option(BUILD_TESTING "Build tests" ON)

#####################################
# Copy Exe and dll , lib  to bin
#####################################
set(COMMON_EXPORT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/release")

set(CMAKE_VS_DEBUGGER_WORKING_DIRECTORY "${COMMON_EXPORT_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "$<0:>${COMMON_EXPORT_PATH}") # .exe and .dll
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "$<0:>${COMMON_EXPORT_PATH}") # .so and .dylib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "$<0:>${COMMON_EXPORT_PATH}") # .lib and .a


##########################################################################################
# pre lib include settings
##########################################################################################

# this is here to ensure the runtime is linked staticly for msvc
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}  /MT ")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE}  /MTd ")
endif()

if (NOT DEFINED PLATFORM)
    set(PLATFORM "default")
endif()


foreach(CONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${CONFIG} CONFIG_UPPER)
    set(CMAKE_${CONFIG_UPPER}_POSTFIX "_${CONFIG_UPPER}") 
endforeach()

##########################################################################################
# Add dependencies with FetchContent
##########################################################################################

# libraries array to be linked
set(LIBRARIES "")
set(LIBRARIES_FOR_TEST "")

include(InstallRequiredSystemLibraries)
include(FetchContent)
include("cmake/Utils.cmake")
include("cmake/Dependencies.cmake")



##########################################################################################
# Project executable setup
##########################################################################################

# Define PROJECT_INCLUDE to be the path to the include directory of the project
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/sources/")

# Adding our source files
# Define PROJECT_SOURCES as a list of all source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/sources/*.cpp" "${CMAKE_CURRENT_LIST_DIR}/sources/*.h")
file(GLOB_RECURSE PROJECT_RESOURCES CONFIGURE_DEPENDS resources/*.*)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${PROJECT_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${PROJECT_RESOURCES})

# Declaring our executable
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES} ${PROJECT_RESOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})

# Includes imgui source

make_directory(../sources/imgui)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/sources/imgui 
    ${CMAKE_CURRENT_LIST_DIR}/libs/rapidjson/include 
    ${CMAKE_CURRENT_LIST_DIR}/libs/raygui/src)


# add target properties such as debug postfix and MSVC runtime

set(CMAKE_VS_DEBUGGER_WORKING_DIRECTORY "${COMMON_EXPORT_PATH}")
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
set_source_files_properties( ${PROJECT_RESOURCES} PROPERTIES HEADER_FILE_ONLY TRUE)

##########################################################################################
# compiler settings
##########################################################################################

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -pthread")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARIES} -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic)
        
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARIES} -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARIES} -static-intel -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_link_libraries( ${PROJECT_NAME} PRIVATE ${LIBRARIES})
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup") 
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /SUBSYSTEM:CONSOLE")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /SUBSYSTEM:WINDOWS") 
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARIES})
endif()



##########################################################################################
# custom commands
##########################################################################################

set(EXECUTABLES ${PROJECT_NAME} CACHE INTERNAL "" )

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

add_subdirectory(examples)

# copy assets over into the build dir for the executable to have them for debug/run reasons

add_custom_target(copyAssetsOver
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/resources
        ${CMAKE_CURRENT_BINARY_DIR}/resources
        COMMENT "Copying assets to build directory"
)

foreach(EXECUTABLE ${EXECUTABLES})
  add_dependencies(${EXECUTABLE} copyAssetsOver) 
endforeach()

foreach(CONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${CONFIG} CONFIG_UPPER)
    set_target_properties(${EXECUTABLES} ${LIBRARIES_FOR_TEST} PROPERTIES ${CONFIG_UPPER}_POSTFIX "${CMAKE_${CONFIG_UPPER}_POSTFIX}")
endforeach()

##########################################################################################
# Project build settings
##########################################################################################


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")

if(WIN32)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -mconsole")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -mwindows")
  endif()    
endif()


# Set common compiler flags
# SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wswitch")
# Set common compiler flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")


# Ensure that hot-reload is enabled for VS
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /ZI")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SAFESEH:NO")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO")
endif()

