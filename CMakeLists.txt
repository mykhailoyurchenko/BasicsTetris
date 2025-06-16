cmake_minimum_required(VERSION 3.28)
project(Tetris LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (WIN32)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")
endif()

include(FetchContent)

# Налаштування статичної збірки SFML
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_BUILD_EXAMPLES OFF)
set(SFML_USE_STATIC_STD_LIBS TRUE)
set(BUILD_SHARED_LIBS OFF)

FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
)
FetchContent_MakeAvailable(SFML)

add_executable(main
        "main.cpp"
        "Code/MenuState.cpp"  "src/States.h"   "Code/PlayState.cpp" "Code/GameState.cpp" "src/Game.h" "src/TetrisMenu.h" "Code/TetrisMenu.cpp"  "Code/PauseState.cpp"
        "Code/GameOverState.cpp"
)

target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/src)
set_property(TARGET main PROPERTY CXX_STANDARD 17)

# Копіювання ресурсів
add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/src/texture"
        "$<TARGET_FILE_DIR:main>/src/texture"
)

add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/src/fonts"
        "$<TARGET_FILE_DIR:main>/src/fonts"
)
