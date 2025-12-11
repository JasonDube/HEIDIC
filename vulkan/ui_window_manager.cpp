// UI Window Manager Implementation
// Creates separate SDL3 windows with ImGui for game interfaces (HUD, menus, inventory, etc.)

#include "../stdlib/ui_window_manager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

// Check if UI windows are enabled via compile-time flag or runtime config
#ifdef ENABLE_UI_WINDOWS
    #define UI_WINDOWS_ENABLED_BY_DEFAULT true
#else
    #define UI_WINDOWS_ENABLED_BY_DEFAULT false
#endif

// SDL3 and ImGui includes (if available)
#ifdef USE_SDL3_UI
    #include <SDL3/SDL.h>
    // Note: We don't include SDL_main.h because we're not using SDL_main() entry point
    #ifdef USE_IMGUI
        #include "imgui.h"
        #include "imgui_impl_sdl3.h"
        #include "imgui_impl_sdlrenderer3.h"
    #endif
#elif defined(USE_SDL2_UI)
    // Fallback to SDL2 for compatibility
    #include <SDL2/SDL.h>
    #ifdef USE_IMGUI
        #include "imgui.h"
        #include "imgui_impl_sdl2.h"
        #include "imgui_impl_sdlrenderer2.h"
    #endif
#endif

// Global state
static bool g_uiManagerEnabled = UI_WINDOWS_ENABLED_BY_DEFAULT;
static bool g_uiManagerInitialized = false;

#ifdef USE_SDL3_UI
static SDL_Window* g_uiWindow = nullptr;
static SDL_Renderer* g_uiRenderer = nullptr;
#ifdef USE_IMGUI
static ImGuiContext* g_uiImGuiContext = nullptr;
#endif
#elif defined(USE_SDL2_UI)
static SDL_Window* g_uiWindow = nullptr;
static SDL_Renderer* g_uiRenderer = nullptr;
#ifdef USE_IMGUI
static ImGuiContext* g_uiImGuiContext = nullptr;
#endif
#endif

// Helper function to convert string to lowercase
static std::string toLower(const std::string& str) {
    std::string result = str;
    for (char& c : result) {
        if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';
        }
    }
    return result;
}

// Read project config to check if UI windows are enabled
static bool readProjectConfig() {
    // Try to read .project_config file from current directory
    std::ifstream configFile(".project_config");
    if (!configFile.is_open()) {
        // Try parent directory (project root)
        configFile.open("../.project_config");
        if (!configFile.is_open()) {
            return UI_WINDOWS_ENABLED_BY_DEFAULT;
        }
    }
    
    std::string line;
    while (std::getline(configFile, line)) {
        // Parse "enable_ui_windows=true" or "enable_ui_windows=False" (case-insensitive)
        if (line.find("enable_ui_windows=") == 0) {
            std::string value = line.substr(18); // Skip "enable_ui_windows="
            std::string lowerValue = toLower(value);
            if (lowerValue == "true" || lowerValue == "1" || lowerValue == "yes") {
                return true;
            } else if (lowerValue == "false" || lowerValue == "0" || lowerValue == "no") {
                return false;
            }
        }
    }
    
    return UI_WINDOWS_ENABLED_BY_DEFAULT;
}

extern "C" bool ui_manager_is_enabled() {
    // Read config on first call if not yet initialized
    static bool configRead = false;
    if (!configRead) {
        g_uiManagerEnabled = readProjectConfig();
        configRead = true;
        std::cout << "[UI Manager] Config read: UI windows " << (g_uiManagerEnabled ? "enabled" : "disabled") << std::endl;
    }
    return g_uiManagerEnabled;
}

extern "C" bool ui_manager_init() {
    if (g_uiManagerInitialized) {
        std::cout << "[UI Manager] Already initialized" << std::endl;
        return true;
    }
    
    // Check if UI windows are enabled (this will read config on first call)
    if (!ui_manager_is_enabled()) {
        std::cout << "[UI Manager] UI windows disabled in project config" << std::endl;
        return false;
    }
    
#ifdef USE_SDL3_UI
    std::cout << "[UI Manager] Initializing SDL3 UI windows..." << std::endl;
    
    // Initialize SDL3
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "[UI Manager] ERROR: Failed to initialize SDL3: " << SDL_GetError() << std::endl;
        return false;
    }
    
    // Create SDL3 window for UI
    g_uiWindow = SDL_CreateWindow("EDEN UI Window", 400, 600, SDL_WINDOW_RESIZABLE);
    
    if (!g_uiWindow) {
        std::cerr << "[UI Manager] ERROR: Failed to create SDL3 window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    
    // Position UI window next to the main Vulkan window (800px wide, so position at x=800)
    SDL_SetWindowPosition(g_uiWindow, 800, 0);
    
    // Create SDL3 renderer (SDL3 API: window, driver name (nullptr = default))
    g_uiRenderer = SDL_CreateRenderer(g_uiWindow, nullptr);
    if (!g_uiRenderer) {
        std::cerr << "[UI Manager] ERROR: Failed to create SDL3 renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(g_uiWindow);
        SDL_Quit();
        return false;
    }
    
#ifdef USE_IMGUI
    // Setup ImGui context for UI window
    IMGUI_CHECKVERSION();
    g_uiImGuiContext = ImGui::CreateContext();
    ImGui::SetCurrentContext(g_uiImGuiContext);
    
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    
    // Setup ImGui style
    ImGui::StyleColorsDark();
    
    // Setup Platform/Renderer backends for SDL3
    ImGui_ImplSDL3_InitForSDLRenderer(g_uiWindow, g_uiRenderer);
    ImGui_ImplSDLRenderer3_Init(g_uiRenderer);
    
    std::cout << "[UI Manager] ImGui initialized for SDL3 window" << std::endl;
#endif
    
    g_uiManagerInitialized = true;
    std::cout << "[UI Manager] Initialized successfully!" << std::endl;
    return true;
#elif defined(USE_SDL2_UI)
    std::cout << "[UI Manager] Initializing SDL2 UI windows..." << std::endl;
    
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "[UI Manager] ERROR: Failed to initialize SDL2: " << SDL_GetError() << std::endl;
        return false;
    }
    
    // Create SDL2 window for UI
    g_uiWindow = SDL_CreateWindow(
        "EDEN UI Window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        400, 600,
        SDL_WINDOW_RESIZABLE
    );
    
    if (!g_uiWindow) {
        std::cerr << "[UI Manager] ERROR: Failed to create SDL2 window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    
    // Position UI window next to the main Vulkan window (800px wide, so position at x=800)
    SDL_SetWindowPosition(g_uiWindow, 800, 0);
    
    // Create SDL2 renderer
    g_uiRenderer = SDL_CreateRenderer(g_uiWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!g_uiRenderer) {
        std::cerr << "[UI Manager] ERROR: Failed to create SDL2 renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(g_uiWindow);
        SDL_Quit();
        return false;
    }
    
#ifdef USE_IMGUI
    // Setup ImGui context for UI window
    IMGUI_CHECKVERSION();
    g_uiImGuiContext = ImGui::CreateContext();
    ImGui::SetCurrentContext(g_uiImGuiContext);
    
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    
    // Setup ImGui style
    ImGui::StyleColorsDark();
    
    // Setup Platform/Renderer backends for SDL2
    ImGui_ImplSDL2_InitForSDLRenderer(g_uiWindow, g_uiRenderer);
    ImGui_ImplSDLRenderer2_Init(g_uiRenderer);
    
    std::cout << "[UI Manager] ImGui initialized for SDL2 window" << std::endl;
#endif
    
    g_uiManagerInitialized = true;
    std::cout << "[UI Manager] Initialized successfully!" << std::endl;
    return true;
#else
    std::cout << "[UI Manager] WARNING: SDL3/SDL2 UI support not compiled in (USE_SDL3_UI or USE_SDL2_UI not defined)" << std::endl;
    std::cout << "[UI Manager] UI windows disabled" << std::endl;
    g_uiManagerEnabled = false;
    return false;
#endif
}

extern "C" void ui_manager_update() {
    if (!g_uiManagerInitialized || !g_uiManagerEnabled) {
        return;
    }
    
#ifdef USE_SDL3_UI
    // Process SDL3 events
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
#ifdef USE_IMGUI
        ImGui_ImplSDL3_ProcessEvent(&event);
#endif
        // SDL3 uses different event types - check for window close events
        if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
            // Window close requested - could signal shutdown or just hide window
            // For now, we'll just continue (window stays open)
        }
    }
    
#ifdef USE_IMGUI
    // Start new ImGui frame
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    
    // Example UI window (can be customized by game code)
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(380, 580), ImGuiCond_FirstUseEver);
    
    if (ImGui::Begin("EDEN UI Window", nullptr, ImGuiWindowFlags_None)) {
        ImGui::Text("UI Window Manager");
        ImGui::Separator();
        ImGui::Text("This is a separate UI window!");
        ImGui::Text("You can add HUD, menus, inventory, etc. here.");
        ImGui::Separator();
        ImGui::Text("Application average %.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);
    }
    ImGui::End();
#endif
#elif defined(USE_SDL2_UI)
    // Process SDL2 events
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
#ifdef USE_IMGUI
        ImGui_ImplSDL2_ProcessEvent(&event);
#endif
        if (event.type == SDL_QUIT) {
            // Window closed - could signal shutdown or just hide window
            // For now, we'll just continue (window stays open)
        }
    }
    
#ifdef USE_IMGUI
    // Start new ImGui frame
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    
    // Example UI window (can be customized by game code)
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(380, 580), ImGuiCond_FirstUseEver);
    
    if (ImGui::Begin("EDEN UI Window", nullptr, ImGuiWindowFlags_None)) {
        ImGui::Text("UI Window Manager");
        ImGui::Separator();
        ImGui::Text("This is a separate UI window!");
        ImGui::Text("You can add HUD, menus, inventory, etc. here.");
        ImGui::Separator();
        ImGui::Text("Application average %.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);
    }
    ImGui::End();
#endif
#endif
}

extern "C" void ui_manager_render() {
    if (!g_uiManagerInitialized || !g_uiManagerEnabled) {
        return;
    }
    
#ifdef USE_SDL3_UI
#ifdef USE_IMGUI
    // Render ImGui
    ImGui::Render();
    
    // Clear renderer
    SDL_SetRenderDrawColor(g_uiRenderer, 30, 30, 40, 255);
    SDL_RenderClear(g_uiRenderer);
    
    // Render ImGui draw data
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), g_uiRenderer);
    
    // Present
    SDL_RenderPresent(g_uiRenderer);
#endif
#elif defined(USE_SDL2_UI)
#ifdef USE_IMGUI
    // Render ImGui
    ImGui::Render();
    
    // Clear renderer
    SDL_SetRenderDrawColor(g_uiRenderer, 30, 30, 40, 255);
    SDL_RenderClear(g_uiRenderer);
    
    // Render ImGui draw data
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
    
    // Present
    SDL_RenderPresent(g_uiRenderer);
#endif
#endif
}

extern "C" void ui_manager_shutdown() {
    if (!g_uiManagerInitialized) {
        return;
    }
    
#ifdef USE_SDL3_UI
#ifdef USE_IMGUI
    if (g_uiImGuiContext) {
        ImGui::SetCurrentContext(g_uiImGuiContext);
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext(g_uiImGuiContext);
        g_uiImGuiContext = nullptr;
    }
#endif
    
    if (g_uiRenderer) {
        SDL_DestroyRenderer(g_uiRenderer);
        g_uiRenderer = nullptr;
    }
    
    if (g_uiWindow) {
        SDL_DestroyWindow(g_uiWindow);
        g_uiWindow = nullptr;
    }
    
    SDL_Quit();
#elif defined(USE_SDL2_UI)
#ifdef USE_IMGUI
    if (g_uiImGuiContext) {
        ImGui::SetCurrentContext(g_uiImGuiContext);
        ImGui_ImplSDLRenderer2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext(g_uiImGuiContext);
        g_uiImGuiContext = nullptr;
    }
#endif
    
    if (g_uiRenderer) {
        SDL_DestroyRenderer(g_uiRenderer);
        g_uiRenderer = nullptr;
    }
    
    if (g_uiWindow) {
        SDL_DestroyWindow(g_uiWindow);
        g_uiWindow = nullptr;
    }
    
    SDL_Quit();
#endif
    
    g_uiManagerInitialized = false;
    std::cout << "[UI Manager] Shutdown complete" << std::endl;
}

