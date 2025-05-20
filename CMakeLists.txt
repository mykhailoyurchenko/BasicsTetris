cmake_minimum_required(VERSION 3.31)
project(BasicsTetris)

set(CMAKE_CXX_STANDARD 17)

# Вкажіть каталоги з заголовками
include_directories(${CMAKE_SOURCE_DIR}/include)

# Вкажіть каталоги з бібліотеками
link_directories(${CMAKE_SOURCE_DIR}/lib)

# Додайте вихідні файли
file(GLOB SOURCES
        "src/*.cpp"
        "src/*.c"
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Якщо збирали glad самостійно, додайте libglad
# Інакше можна лінкувати лише з OpenGL
target_link_libraries(${PROJECT_NAME}
        glfw3            # бібліотека GLFW
        glad             # якщо є libglad.a/.lib
        ${CMAKE_DL_LIBS} # для динамічного завантаження на Linux
)

# На Windows автоматично лінкується opengl32
if (WIN32)
    target_link_libraries(${PROJECT_NAME} opengl32)
endif()