cmake_minimum_required(VERSION 3.28)
project(Tetris LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main
    "main.cpp"
    "MenuState.cpp"  "src/States.h"   "PlayState.cpp" "GameState.cpp" "src/Game.h" "src/TetrisMenu.h" "TetrisMenu.cpp" )

target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Копіювання директорії texture
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/src/texture"
    "$<TARGET_FILE_DIR:main>/src/texture"
)
# Копіювання директорії fonts
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/src/fonts"
    "$<TARGET_FILE_DIR:main>/src/fonts"
)
