// main.cpp
#include <glad/glad.h>           // OpenGL-завантажувач функцій
#include <GLFW/glfw3.h>          // Вікна та контекст

#include <iostream>

// Обробник натискання клавіш
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main() {
    // 1) Ініціалізація GLFW
    if (!glfwInit()) {
        std::cerr << "Помилка: не вдалося ініціалізувати GLFW\n";
        return -1;
    }

    // Запити OpenGL 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // Core profile :contentReference[oaicite:0]{index=0}

    // 2) Створити вікно
    GLFWwindow* window = glfwCreateWindow(800, 600, "Test OpenGL", nullptr, nullptr);
    if (!window) {
        std::cerr << "Помилка: не вдалося створити GLFW вікно\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    // 3) Завантажити всі вказівники OpenGL через GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Помилка: не вдалося завантажити GLAD\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // 4) Основний цикл рендерингу
    while (!glfwWindowShouldClose(window)) {
        // Очистити екран (темно-синій фон)
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Обмін буферів та обробка подій
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 5) Прибирання ресурсів
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
