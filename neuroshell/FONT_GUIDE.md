# NEUROSHELL Font System Guide

## Font Format Specification

**16×16 Grid (256 characters)**
- Image size: Any size divisible by 16 (e.g., 256×256, 512×512, 128×128)
- Grid layout: 16 columns × 16 rows = 256 characters
- Character order: **ASCII 0-255** (left-to-right, top-to-bottom)
  - Row 0: ASCII 0-15
  - Row 1: ASCII 16-31
  - Row 2: ASCII 32-47 (space, !, ", #, $, %, &, ', (, ), *, +, comma, -, ., /)
  - Row 3: ASCII 48-63 (0-9, :, ;, <, =, >, ?)
  - Row 4: ASCII 64-79 (@, A-O)
  - Row 5: ASCII 80-95 (P-Z, [, \, ], ^, _, `)
  - Row 6: ASCII 96-111 (`, a-o)
  - Row 7: ASCII 112-127 (p-z, {, |, }, ~, DEL)
  - Rows 8-15: Extended ASCII (128-255)

## Where to Get Fonts

### Free Font Resources:

1. **ShlomiRex - Pixelated ASCII Font** (itch.io)
   - URL: `https://shlomirex.itch.io/pixelated-ascii-font`
   - Includes 16×16 pixel fonts with sprite sheets

2. **DINOBYTE Bitmap Font** (itch.io)
   - URL: `https://mby.itch.io/dinobyte`
   - 16×16 glyph PNG with codepage 437 (Extended ASCII)

3. **16×16 Pixel Font Bundle** (itch.io)
   - URL: `https://marvinz.itch.io/16x16-pixel-font-bundle`
   - Multiple 16×16 pixel fonts, editable

4. **Sprite Font Generator** (Online Tool)
   - URL: `https://kodaloid.com/tools/sprite-font-generator/`
   - Generate sprite fonts from system fonts
   - Customize size and export as PNG

5. **FontSprite** (itch.io)
   - URL: `https://adamstrange.itch.io/fontsprite`
   - Editor for creating/editing sprite fonts

## Usage in NEUROSHELL

```c
// Load font (call once after neuroshell_init)
NeuroshellFontID font_id = neuroshell_load_font("path/to/font.png");

// Create text element
NeuroshellElementID text_id = neuroshell_create_text(
    100.0f, 100.0f,        // x, y position (pixels)
    "Hello, World!",       // text string
    font_id,               // font ID
    16.0f, 16.0f           // character width, height (pixels)
);

// Update text string
neuroshell_set_text_string(text_id, "New text!");

// Set text color
neuroshell_set_color(text_id, 1.0f, 1.0f, 1.0f, 1.0f);  // White
```

## Creating Your Own Font

1. Create a 256×256 pixel image (or any size divisible by 16)
2. Divide into 16×16 grid (each cell = 16×16 pixels)
3. Draw characters in ASCII order (0-255)
4. Save as PNG or DDS
5. Load with `neuroshell_load_font()`

## Notes

- **Fixed-width**: All characters are the same size (simplest, fastest)
- **Auto-detection**: NEUROSHELL automatically detects 16×16 grid from image dimensions
- **ASCII mapping**: Characters map directly to ASCII codes (no lookup table needed)
- **Fast rendering**: All characters batched into single draw call per font

