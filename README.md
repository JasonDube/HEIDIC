# HEIDIC v2

A clean, basic implementation of the HEIDIC language, starting from scratch with just the core language features.

## Overview

HEIDIC v2 is a statically-typed, compiled language that compiles to C++. This version focuses on the basic language features without Vulkan/GLFW integration.

## Features

### Basic Types
- `i32` - 32-bit signed integer
- `i64` - 64-bit signed integer
- `f32` - 32-bit floating point
- `f64` - 64-bit floating point
- `bool` - Boolean (`true` or `false`)
- `string` - String type
- `void` - No return value

### Composite Types
- Arrays: `[T]` - Dynamic array of type T
- Structs: User-defined data structures
- Components: Special structs for ECS (Entity Component System)
- Math types: `Vec2`, `Vec3`, `Vec4`, `Mat4`

### Language Features
- Variables with type inference
- Functions
- Control flow: `if/else`, `while`, `loop`
- Operators: arithmetic, comparison, logical
- Built-in `print()` function

## Building

```bash
cd heidic_v2
cargo build --release
```

## Usage

### Compile a HEIDIC v2 file

```bash
cargo run -- compile examples/hello.hd
```

This will generate a `hello.cpp` file in the same directory.

### Compile the generated C++

```bash
g++ -std=c++17 -O3 examples/hello.cpp -o hello
./hello
```

## Example

See `examples/hello.hd` for a complete example.

## Project Structure

```
heidic_v2/
├── src/
│   ├── main.rs          # Compiler entry point
│   ├── lexer.rs         # Lexical analysis
│   ├── parser.rs        # Syntax parsing
│   ├── ast.rs           # Abstract syntax tree
│   ├── type_checker.rs  # Type checking
│   └── codegen.rs       # C++ code generation
├── examples/
│   └── hello.hd         # Example program
├── Cargo.toml
└── README.md
```

## Differences from HEIDIC v1

- **No Vulkan types**: Removed all Vulkan-specific types (VkInstance, VkDevice, etc.)
- **No GLFW types**: Removed GLFW-specific types
- **No Vulkan includes**: Removed Vulkan/GLFW header includes from generated code
- **Cleaner codebase**: Focused on core language features only

## Future Enhancements

- Add more built-in functions
- Improve error messages
- Add more language features as needed
- Add Vulkan/GLFW support when ready

