// UI Window Manager - Abstraction layer for game interface windows
// Supports SDL2 + ImGui for creating separate windows for HUD, menus, inventory, etc.
// This is an optional feature that can be enabled/disabled per project

#ifndef UI_WINDOW_MANAGER_H
#define UI_WINDOW_MANAGER_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Initialize UI window manager (call once at startup)
// Returns true on success, false on failure
bool ui_manager_init();

// Check if UI manager is enabled (reads from project config or compile-time flag)
bool ui_manager_is_enabled();

// Update UI windows (process input, update state) - call each frame
void ui_manager_update();

// Render UI windows - call each frame after game rendering
void ui_manager_render();

// Shutdown UI window manager (call once at cleanup)
void ui_manager_shutdown();

#ifdef __cplusplus
}
#endif

#endif // UI_WINDOW_MANAGER_H

