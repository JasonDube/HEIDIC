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

extern "C" {
    void heidic_glfw_vulkan_hints();
}
extern "C" {
    int32_t heidic_init_renderer(GLFWwindow* window);
}
extern "C" {
    void heidic_render_frame(GLFWwindow* window);
}
extern "C" {
    void heidic_cleanup_renderer();
}
extern "C" {
    void heidic_sleep_ms(int32_t milliseconds);
}

int heidic_main();

int heidic_main() {
        std::cout << "=== EDEN ENGINE Spinning Triangle Test ===\n" << std::endl;
        std::cout << "Initializing GLFW...\n" << std::endl;
        int32_t init_result = glfwInit();
        if ((init_result == 0)) {
            std::cout << "Failed to initialize GLFW!\n" << std::endl;
            return 0;
        }
        std::cout << "GLFW initialized.\n" << std::endl;
        heidic_glfw_vulkan_hints();
        std::cout << "Creating window...\n" << std::endl;
        GLFWwindow* window = glfwCreateWindow(800, 600, "EDEN ENGINE Spinning Triangle", 0, 0);
        if ((window == 0)) {
            std::cout << "Failed to create window!\n" << std::endl;
            glfwTerminate();
            return 0;
        }
        std::cout << "Window created.\n" << std::endl;
        std::cout << "Initializing Vulkan renderer...\n" << std::endl;
        int32_t renderer_init = heidic_init_renderer(window);
        if ((renderer_init == 0)) {
            std::cout << "Failed to initialize renderer!\n" << std::endl;
            glfwDestroyWindow(window);
            glfwTerminate();
            return 0;
        }
        std::cout << "Renderer initialized!\n" << std::endl;
        std::cout << "Starting render loop...\n" << std::endl;
        std::cout << "You should see a spinning triangle!\n" << std::endl;
        std::cout << "Press ESC or close the window to exit.\n" << std::endl;
        while ((glfwWindowShouldClose(window) == 0)) {
            glfwPollEvents();
            if ((glfwGetKey(window, 256) == 1)) {
                glfwSetWindowShouldClose(window, 1);
            }
            heidic_render_frame(window);
            heidic_sleep_ms(16);
        }
        std::cout << "Cleaning up...\n" << std::endl;
        heidic_cleanup_renderer();
        glfwDestroyWindow(window);
        glfwTerminate();
        std::cout << "Done!\n" << std::endl;
        return 0;
}

int main(int argc, char* argv[]) {
    heidic_main();
    return 0;
}
