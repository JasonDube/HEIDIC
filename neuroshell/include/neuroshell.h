// NEUROSHELL - Lightweight In-Game UI System
// Fast compile, fast runtime UI with animated textures and effects
// Separate from engine helpers - clean, minimal API

#ifndef NEUROSHELL_H
#define NEUROSHELL_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
struct GLFWwindow;

// Vulkan forward declarations (needed for VkCommandBuffer)
typedef struct VkCommandBuffer_T* VkCommandBuffer;

// ============================================================================
// Core Initialization
// ============================================================================

// Initialize NEUROSHELL (call once after Vulkan renderer is initialized)
// Returns 1 on success, 0 on failure
int neuroshell_init(struct GLFWwindow* window);

// Shutdown NEUROSHELL (call once at cleanup)
void neuroshell_shutdown();

// Check if NEUROSHELL is enabled and initialized
bool neuroshell_is_enabled();

// ============================================================================
// Frame Updates
// ============================================================================

// Update NEUROSHELL (call each frame before rendering)
// Updates animations, effects, input state
void neuroshell_update(float delta_time);

// Render all UI elements (call within render pass, after game rendering)
// commandBuffer: Current Vulkan command buffer (must be in active render pass)
void neuroshell_render(VkCommandBuffer commandBuffer);

// ============================================================================
// UI Elements
// ============================================================================

// UI Element ID (opaque handle)
// Note: Using int32_t for HEIDIC compatibility (HEIDIC doesn't have u32 type yet)
typedef int32_t NeuroshellElementID;
#define NEUROSHELL_INVALID_ID 0

// Element types
typedef enum {
    NEUROSHELL_PANEL,
    NEUROSHELL_BUTTON,
    NEUROSHELL_IMAGE,
    NEUROSHELL_TEXT,
    NEUROSHELL_PROGRESS_BAR
} NeuroshellElementType;

// Create a panel (container with background)
// x, y: screen position in pixels (top-left origin)
// width, height: size in pixels
// Returns element ID or NEUROSHELL_INVALID_ID on failure
NeuroshellElementID neuroshell_create_panel(float x, float y, float width, float height);

// Create a button
// x, y: screen position in pixels
// width, height: size in pixels
// texture_path: path to button texture (can be NULL for colored button)
// Returns element ID or NEUROSHELL_INVALID_ID on failure
NeuroshellElementID neuroshell_create_button(float x, float y, float width, float height, const char* texture_path);

// Create an image/icon
// x, y: screen position in pixels
// width, height: size in pixels
// texture_path: path to image texture
// Returns element ID or NEUROSHELL_INVALID_ID on failure
NeuroshellElementID neuroshell_create_image(float x, float y, float width, float height, const char* texture_path);

// ============================================================================
// Font System (Sprite Sheet Fonts)
// ============================================================================

// Font ID (opaque handle)
typedef int32_t NeuroshellFontID;
#define NEUROSHELL_INVALID_FONT_ID 0

// Load a font from a sprite sheet image
// font_path: path to font sprite sheet (PNG or DDS)
// Auto-detects: assumes 16×16 grid (256 chars) in ASCII order (0-255)
// Returns font ID or NEUROSHELL_INVALID_FONT_ID on failure
NeuroshellFontID neuroshell_load_font(const char* font_path);

// Create a text element
// x, y: screen position in pixels (top-left of first character)
// text: string to display (ASCII characters only)
// font_id: font to use (from neuroshell_load_font)
// char_width, char_height: size of each character in pixels
// Returns element ID or NEUROSHELL_INVALID_ID on failure
NeuroshellElementID neuroshell_create_text(
    float x, float y,
    const char* text,
    NeuroshellFontID font_id,
    float char_width, float char_height
);

// Update text string for a text element
void neuroshell_set_text_string(NeuroshellElementID text_id, const char* text);

// ============================================================================
// Animated Textures
// ============================================================================

// Create an animated texture from a sprite sheet
// texture_path: path to sprite sheet texture
// frame_width, frame_height: size of each frame in pixels
// frame_count: total number of frames
// fps: frames per second for animation
// Returns element ID or NEUROSHELL_INVALID_ID on failure
NeuroshellElementID neuroshell_create_animated_texture(
    float x, float y, float width, float height,
    const char* texture_path,
    int frame_width, int frame_height, int frame_count, float fps
);

// Set animation state for an element
// element_id: element to animate
// playing: true to play, false to pause
// loop: true to loop, false to play once
void neuroshell_set_animation_state(NeuroshellElementID element_id, bool playing, bool loop);

// ============================================================================
// Element Properties
// ============================================================================

// Set element visibility
void neuroshell_set_visible(NeuroshellElementID element_id, bool visible);

// Set element position
void neuroshell_set_position(NeuroshellElementID element_id, float x, float y);

// Set element size
void neuroshell_set_size(NeuroshellElementID element_id, float width, float height);

// Set element color tint (RGBA, 0.0-1.0)
void neuroshell_set_color(NeuroshellElementID element_id, float r, float g, float b, float a);

// Set element depth (Z-order, higher = on top)
void neuroshell_set_depth(NeuroshellElementID element_id, float depth);

// ============================================================================
// Input Handling
// ============================================================================

// Check if a button was clicked this frame
// Returns true if clicked, false otherwise
bool neuroshell_is_button_clicked(NeuroshellElementID button_id);

// Get mouse position in screen coordinates
void neuroshell_get_mouse_position(float* x, float* y);

// ============================================================================
// Effects (Foundation for future expansion)
// ============================================================================

// Effect types (for future implementation)
typedef enum {
    NEUROSHELL_EFFECT_NONE,
    NEUROSHELL_EFFECT_FADE,
    NEUROSHELL_EFFECT_SLIDE,
    NEUROSHELL_EFFECT_SCALE,
    NEUROSHELL_EFFECT_PARTICLE
} NeuroshellEffectType;

// Apply effect to element (placeholder for future implementation)
void neuroshell_apply_effect(NeuroshellElementID element_id, NeuroshellEffectType effect_type, float duration);

#ifdef __cplusplus
}
#endif

#endif // NEUROSHELL_H

