#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <cmath>
#include <cstdint>

// EDEN ENGINE Standard Library
#include "stdlib/vulkan.h"
#include "stdlib/glfw.h"
#include "stdlib/math.h"
#include "stdlib/imgui.h"


int heidic_main();

int heidic_main() {
        std::cout << "=== EDEN ENGINE Window Test ===\n" << std::endl;
        std::cout << "Initializing GLFW...\n" << std::endl;
        int32_t init_result = glfwInit();
        if ((init_result == 0)) {
            std::cout << "Failed to initialize GLFW!\n" << std::endl;
            return 0;
        }
        std::cout << "GLFW initialized.\n" << std::endl;
        std::cout << "Creating window...\n" << std::endl;
        glfwWindowHint(139265, 0);
        GLFWwindow* window = glfwCreateWindow(800, 600, "EDEN ENGINE Window", 0, 0);
        if ((window == 0)) {
            std::cout << "Failed to create window!\n" << std::endl;
            glfwTerminate();
            return 0;
        }
        std::cout << "Window created successfully!\n" << std::endl;
        std::cout << "Press ESC to close the window.\n" << std::endl;
        while ((glfwWindowShouldClose(window) == 0)) {
            glfwPollEvents();
            if ((glfwGetKey(window, 256) == 1)) {
                glfwSetWindowShouldClose(window, 1);
            }
        }
        std::cout << "Closing window...\n" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        std::cout << "Test completed!\n" << std::endl;
        return 0;
}

int main(int argc, char* argv[]) {
    heidic_main();
    return 0;
}
