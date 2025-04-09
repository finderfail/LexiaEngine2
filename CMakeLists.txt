cmake_minimum_required(VERSION 3.10)
project(LexiaEditor)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

if (SDL2_FOUND)
    message(STATUS "SDL2 found: ${SDL2_INCLUDE_DIRS}")
    include_directories(${SDL2_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "SDL2 not found. Please install with Homebrew: brew install sdl2")
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

target_link_libraries(engine_lib PRIVATE SDL2::SDL2)

# --- Set the output name for the engine library ---
set_target_properties(engine_lib PROPERTIES OUTPUT_NAME "engine")

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

target_link_libraries(editor_exe
    engine_lib
    SDL2::SDL2
)

# --- Output settings ---
set_target_properties(editor_exe PROPERTIES OUTPUT_NAME ${EDITOR_BIN})
set_target_properties(editor_exe PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${EXECUTABLE_OUTPUT_PATH}")