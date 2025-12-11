# ELECTROSCRIBE Refactoring Analysis

## Current Issues

### 1. **Single Responsibility Principle Violations**
The `Editor` class (3695 lines total) handles too many responsibilities:
- Text editing and cursor management
- File I/O and project management
- Build pipeline (compile, build, hotload)
- UI rendering (drawing editor, panels, scrollbars, menus)
- Event handling (partially in `main()`)
- Syntax highlighting
- Scrollbar calculations (4 different methods with similar logic)
- Clipboard operations (duplicated code)

### 2. **Code Duplication**

#### Clipboard Operations (Lines 2838-2880, 2935-2977)
- Identical clipboard copying logic appears twice (log and terminal)
- ~40 lines duplicated with only variable names changed
- **Solution**: Extract to `_copy_to_clipboard(text, success_message)` method

#### Scrollbar Calculations (Lines 695-819)
- 4 similar methods: `calc_scrollbar()`, `calc_hscrollbar()`, `calc_log_vscrollbar()`, `calc_terminal_vscrollbar()`
- Similar logic with slight variations
- **Solution**: Create generic `ScrollbarCalculator` class or unified method with parameters

#### Scrollbar Drawing (Lines 1138-1308)
- Similar drawing code repeated 3 times (editor, log, terminal)
- **Solution**: Extract to `_draw_scrollbar(surface, scrollbar_data, is_horizontal)` method

#### Panel Drawing (Lines 1185-1308)
- Log and terminal panels have nearly identical structure
- **Solution**: Extract to `_draw_text_panel(surface, lines, header_color, header_text, ...)` method

### 3. **Long Methods**

#### `draw()` - ~350 lines (967-1311)
- Handles menu, editor, log panel, terminal panel
- **Solution**: Split into `_draw_menu()`, `_draw_editor()`, `_draw_log_panel()`, `_draw_terminal_panel()`

#### `main()` - ~900 lines (2787-3689)
- Massive event handling loop
- **Solution**: Extract event handlers to separate methods or `EventHandler` class

#### `_do_build()` - ~350 lines (1609-1953)
- Complex build command construction
- **Solution**: Extract to `BuildConfig` class or separate methods for each build step

#### `hotload_dll()` - ~230 lines (1955-2185)
- Complex DLL replacement logic
- **Solution**: Extract DLL management to `HotloadManager` class

### 4. **Magic Numbers and Strings**
- Hardcoded colors, sizes scattered throughout
- String literals for actions: `"new"`, `"load"`, `"save"`, etc.
- **Solution**: Move to constants or enums

### 5. **Tight Coupling**
- Editor class directly manipulates pygame surfaces
- Event handling mixed with business logic
- **Solution**: Introduce abstraction layers (UI components, event handlers)

## Proposed Refactoring Structure

```
ELECTROSCRIBE/
├── main.py (simplified - just initialization and main loop)
├── editor/
│   ├── __init__.py
│   ├── editor.py (core text editing logic)
│   ├── file_manager.py (file I/O, project management)
│   ├── build_manager.py (compile, build, hotload)
│   └── syntax_highlighter.py (syntax highlighting)
├── ui/
│   ├── __init__.py
│   ├── components/
│   │   ├── scrollbar.py (unified scrollbar handling)
│   │   ├── text_panel.py (log/terminal panel)
│   │   ├── menu_bar.py (menu buttons)
│   │   └── editor_view.py (editor rendering)
│   └── clipboard.py (clipboard operations)
├── dialogs/
│   ├── __init__.py
│   ├── project_picker.py
│   ├── shader_picker.py
│   ├── text_input.py
│   └── project_settings.py
└── config.py (all constants and configuration)
```

## Priority Refactoring Tasks

### High Priority (Immediate Benefits)
1. **Extract clipboard operations** - Eliminates ~40 lines of duplication
2. **Extract scrollbar drawing** - Eliminates ~60 lines of duplication
3. **Split `draw()` method** - Improves readability and maintainability
4. **Extract panel drawing** - Eliminates ~80 lines of duplication

### Medium Priority (Better Organization)
5. **Create `BuildManager` class** - Isolates build logic
6. **Create `ScrollbarCalculator` class** - Unifies scrollbar logic
7. **Extract event handlers** - Simplifies `main()` function
8. **Move constants to `config.py`** - Centralizes configuration

### Low Priority (Long-term Improvements)
9. **Create UI component classes** - Better separation of concerns
10. **Add abstraction layers** - Reduce pygame coupling
11. **Create `HotloadManager` class** - Isolate hotload logic

## Estimated Impact

- **Lines of code reduction**: ~200-300 lines through deduplication
- **Method complexity**: Reduce average method length from ~50 to ~20 lines
- **Maintainability**: Significantly improved through separation of concerns
- **Testability**: Much easier to test isolated components

## Migration Strategy

1. **Phase 1**: Extract utility functions (clipboard, scrollbar drawing) - Low risk
2. **Phase 2**: Split large methods (`draw()`, `main()`) - Medium risk
3. **Phase 3**: Extract classes (BuildManager, etc.) - Higher risk, requires testing
4. **Phase 4**: Reorganize into modules - Requires careful import management

## Notes

- Keep backward compatibility during refactoring
- Test after each phase
- Consider keeping old code commented for reference initially
- Document new structure as you go

