# Diagnostic Steps for ECS Debug Output Issue

## Fastest Diagnostic (15 seconds)

1. Open Windows Command Prompt (cmd.exe)
2. Navigate to project:
   ```
   cd C:\Users\nitro\Desktop\PROJECTS\HEIDIC\H_SCRIBE\PROJECTS\bouncing_balls
   ```
3. Delete the executable:
   ```
   del bouncing_balls.exe
   ```
4. In H_SCRIBE, click the white "Run" button to rebuild
5. In the cmd prompt, run the executable manually:
   ```
   bouncing_balls.exe
   ```

### Expected Outcomes:

**Outcome A**: You instantly see all debug prints including `[IMMEDIATE DEBUG] ball_count just set to 5`
- → **99% chance it's #1 (stale exe) or #5 (wrong subsystem)**
- Fix: Delete `.exe` before each build, or check build command for `-mwindows` flag

**Outcome B**: You still see nothing or it exits immediately
- → Go to #2 (wrong cwd) or #3 (early return in Vulkan init)
- Check if working directory is correct when H_SCRIBE runs the exe

---

## Check Build Timestamps

Run this to verify the exe is actually being rebuilt:

```bash
cd H_SCRIBE\PROJECTS\bouncing_balls
dir bouncing_balls.* /OD
```

Compare timestamps:
- If `.exe` is **older** than `.cpp` → stale executable issue
- If `.exe` is **newer** or same → build is happening, but wrong exe is running

---

## Check Working Directory

Add this as the very first line in `bouncing_balls.cpp` `heidic_main()` function temporarily:

```cpp
#include <filesystem>
// ... at start of heidic_main() ...
std::cout << "[DEBUG] CWD = " << std::filesystem::current_path() << "\n";
std::cout.flush();
```

If it prints `H_SCRIBE\` instead of `H_SCRIBE\PROJECTS\bouncing_balls\` → working directory issue

---

## Check for Early Return

Add checkpoints throughout `heidic_main()` to see where execution stops:

```cpp
std::cout << "[CHECKPOINT] 1 - Entering main\n"; std::cout.flush();
// ... after GLFW init ...
std::cout << "[CHECKPOINT] 2 - After GLFW init\n"; std::cout.flush();
// ... after window creation ...
std::cout << "[CHECKPOINT] 3 - After window creation\n"; std::cout.flush();
// ... after renderer init ...
std::cout << "[CHECKPOINT] 4 - After renderer init\n"; std::cout.flush();
std::cout << "[CHECKPOINT] 5 - Before ball_count\n"; std::cout.flush();
int32_t ball_count = 5;
std::cout << "[CHECKPOINT] 6 - After ball_count\n"; std::cout.flush();
```

This will show exactly where execution stops.

---

## Most Common Causes (in order of likelihood):

1. **Stale Executable** (~60% of cases)
   - H_SCRIBE runs old `.exe` that doesn't have new code
   - Fix: Delete `.exe` before each build, or verify build is actually compiling

2. **Wrong Working Directory** (~25% of cases)
   - Exe runs from `H_SCRIBE/` instead of `H_SCRIBE/PROJECTS/bouncing_balls/`
   - Program can't find shaders/files and exits early
   - Fix: Verify `cwd` parameter in `subprocess.Popen()` in `main.py`

3. **Early Return** (~10% of cases)
   - Vulkan/GLFW init fails silently
   - Program exits before reaching `ball_count = 5;`
   - Fix: Check return codes from init functions

4. **Console Subsystem Issue** (~5% of cases)
   - Exe compiled as `-mwindows` (Windows subsystem) instead of console
   - `std::cout` goes nowhere
   - Fix: Ensure build command uses console subsystem

---

## Quick Fix to Try First

Add this to `H_SCRIBE/main.py` in the `_do_build()` function, right before running the exe:

```python
# Force delete old exe before building
exe_path = os.path.join(project_dir, exe_name)
if os.path.exists(exe_path):
    try:
        os.remove(exe_path)
        self.log_lines.append(f"[DEBUG] Deleted old {exe_name}")
    except Exception as e:
        self.log_lines.append(f"[DEBUG] Could not delete {exe_name}: {e}")

# ... build command ...
# After build, verify exe exists and is newer than cpp
if os.path.exists(exe_path):
    exe_time = os.path.getmtime(exe_path)
    cpp_time = os.path.getmtime(cpp_path)
    self.log_lines.append(f"[DEBUG] .exe timestamp: {exe_time}")
    self.log_lines.append(f"[DEBUG] .cpp timestamp: {cpp_time}")
    if exe_time > cpp_time:
        self.log_lines.append("[DEBUG] Build successful - exe is newer")
    else:
        self.log_lines.append("[DEBUG] WARNING: Build may have failed - exe is older than cpp!")
```

