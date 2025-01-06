cmake_minimum_required(VERSION 3.10)
project(LexiaEditor)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# --- Source directories ---
set(ENGINE_SRC_DIR "engine/src")
set(ENGINE_INCLUDE_DIR "engine/include")
set(ENGINE_LIB_DIR "lib")
set(EDITOR_SRC_DIR "editor/src")

# --- Executable name ---
set(EDITOR_BIN "editor")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}")

# --- SDL2 Setup ---
find_package(SDL2 REQUIRED)

if(NOT SDL2_FOUND)
  message(FATAL_ERROR "SDL2 not found. Please set SDL2_DIR.")
endif()

if (DEFINED ENV{SDL2_DIR})
    set(SDL2_PATH $ENV{SDL2_DIR})
    message(STATUS "Using SDL2 from environment variable SDL2_DIR: ${SDL2_PATH}")
    
    set(SDL2_INCLUDE_DIR ${SDL2_PATH}/include CACHE PATH "SDL2 Include Directory")
    set(SDL2_LIB_DIR ${SDL2_PATH}/lib CACHE PATH "SDL2 Library Directory")

    include_directories(${SDL2_INCLUDE_DIR})
    link_directories(${SDL2_LIB_DIR})
else()
   message(STATUS "Using system SDL2")
   include_directories(${SDL2_INCLUDE_DIRS})
endif()

# --- Engine library ---
add_library(engine_lib STATIC
    ${ENGINE_SRC_DIR}/Screen.cpp
    ${ENGINE_SRC_DIR}/Map.cpp
    ${ENGINE_SRC_DIR}/Player.cpp
    ${ENGINE_SRC_DIR}/Raycaster.cpp
    ${ENGINE_SRC_DIR}/Config.cpp
)

target_include_directories(engine_lib PUBLIC
    ${ENGINE_INCLUDE_DIR}
)

if(NOT DEFINED ENV{SDL2_DIR})
     target_link_libraries(engine_lib PRIVATE SDL2::SDL2)
endif()


# --- Editor executable ---
add_executable(editor_exe
    ${EDITOR_SRC_DIR}/EditorWindow.cpp
    ${EDITOR_SRC_DIR}/MapEditor.cpp
    ${EDITOR_SRC_DIR}/ConfigEditor.cpp
    ${EDITOR_SRC_DIR}/ProjectManager.cpp
    ${EDITOR_SRC_DIR}/Compiler.cpp
    ${EDITOR_SRC_DIR}/main.cpp
)

target_include_directories(editor_exe PRIVATE
    ${ENGINE_INCLUDE_DIR}
)

if(NOT DEFINED ENV{SDL2_DIR})
    target_link_libraries(editor_exe 
        engine_lib
        SDL2::SDL2
    )
else()
     target_link_libraries(editor_exe 
        engine_lib
    )
endif()

set_target_properties(editor_exe PROPERTIES OUTPUT_NAME ${EDITOR_BIN})
set_target_properties(editor_exe PROPERTIES  RUNTIME_OUTPUT_DIRECTORY "${EXECUTABLE_OUTPUT_PATH}")