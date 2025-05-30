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
    "MenuState.cpp" "src/MenuState.h" "src/States.h" "States.cpp" "src/playState.h" "playState.cpp")

target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/src)

# ��������� �������� texture
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/src/texture"
    "$<TARGET_FILE_DIR:main>/src/texture"
)

# ��������� �������� fonts
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/src/fonts"
    "$<TARGET_FILE_DIR:main>/src/fonts"
)
