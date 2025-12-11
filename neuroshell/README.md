# NEUROSHELL - Lightweight In-Game UI System

Fast compile, fast runtime UI with animated textures and effects for EDEN Engine games.

## Status

✅ **Completed:**
- Project settings integration (checkbox in SCRIBE)
- Core structure (header and implementation files)
- API design (Panel, Button, Image, Animated Texture)
- Input handling (mouse position, button clicks)
- Animation system (sprite sheets, frame timing)
- Element management (visibility, position, size, color, depth)

🔄 **In Progress:**
- Vulkan pipeline setup (shaders created, pipeline integration needed)
- Batched rendering (structure in place, rendering logic needed)

## Architecture

NEUROSHELL is designed to be:
- **Lightweight** - ~1000 lines vs ImGui's 20k+
- **Fast compile** - No heavy dependencies, pure C++/HEIDIC
- **Fast runtime** - Batched rendering, optimized for games
- **Separate** - Clean API, not tangled in engine helpers

## Shaders

Shaders are in `neuroshell/shaders/`:
- `ui.vert` - Screen-space vertex shader (pixel coords → NDC)
- `ui.frag` - Fragment shader (textured + solid color support)

Shaders need to be compiled to SPIR-V (`.spv` files) before use.

## Next Steps

1. **Complete Vulkan Pipeline Setup** in `neuroshell_init()`:
   - Load compiled shader modules (ui.vert.spv, ui.frag.spv)
   - Create descriptor set layout (for textures)
   - Create pipeline layout with push constants
   - Create graphics pipeline (screen-space, alpha blending)

2. **Complete Batched Rendering** in `neuroshell_render(VkCommandBuffer)`:
   - Build vertex/index buffers from quad batch
   - Bind pipeline and buffers
   - Draw all quads in sorted order (by depth)

3. **Texture Integration**:
   - Use TextureResource for UI textures
   - Create descriptor sets for texture binding
   - Support texture atlases for animated sprites

4. **HEIDIC Template Integration**:
   - Add NEUROSHELL externs to project templates
   - Add initialization/update/render calls in main loop

## Usage (Future HEIDIC API)

```heidic
// Initialize NEUROSHELL
if (neuroshell_is_enabled()) {
    neuroshell_init(window);
}

// Create UI elements
let panel = neuroshell_create_panel(10, 10, 200, 100);
let button = neuroshell_create_button(20, 20, 100, 30, "ui/button.png");

// In render loop
neuroshell_update(delta_time);
heidic_render_frame(window);  // Game rendering
neuroshell_render(commandBuffer);  // UI rendering (after game)
```

## Effects System (Future)

Placeholder for effects:
- Fade transitions
- Slide animations
- Scale effects
- Particle effects

