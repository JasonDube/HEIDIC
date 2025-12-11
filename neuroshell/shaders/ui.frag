#version 450

// UI fragment shader
// Supports textured and solid-color quads

layout(location = 0) in vec2 fragUV;
layout(location = 1) in vec4 fragColor;

layout(location = 0) out vec4 outColor;

layout(binding = 1) uniform sampler2D uiTexture;

layout(push_constant) uniform UIPushConstants {
    int hasTexture;  // 0 = solid color, 1 = textured
} pc;

void main() {
    if (pc.hasTexture == 1) {
        // Sample texture and apply color tint
        vec4 texColor = texture(uiTexture, fragUV);
        outColor = texColor * fragColor;
    } else {
        // Solid color
        outColor = fragColor;
    }
}

