@echo off
echo ========================================
echo SDL3 Setup Script for EDEN Engine
echo ========================================
echo.
echo Current directory: %CD%
echo.

REM Force continue - assume folder exists if we can see it
echo Checking for x86_64-w64-mingw32...
dir /B /AD | findstr /I "x86_64" >nul
if errorlevel 1 (
    echo ERROR: x86_64-w64-mingw32 folder not found!
    echo Please run this from the SDL3 extracted directory.
    pause
    exit /b 1
)

echo [OK] Found x86_64-w64-mingw32 folder
echo.

REM Create C:\SDL3 structure
echo Creating C:\SDL3 directory structure...
if not exist "C:\SDL3" (
    mkdir "C:\SDL3"
    if errorlevel 1 (
        echo ERROR: Failed to create C:\SDL3
        echo You may need to run as Administrator
        pause
        exit /b 1
    )
)
mkdir "C:\SDL3\include" 2>nul
mkdir "C:\SDL3\lib" 2>nul
mkdir "C:\SDL3\lib\x64" 2>nul
mkdir "C:\SDL3\bin" 2>nul
mkdir "C:\SDL3\bin\x64" 2>nul
echo [OK] Directory structure created
echo.

REM Copy headers (SDL3 uses SDL3 folder, not SDL2)
echo Copying headers...
if exist "x86_64-w64-mingw32\include\SDL3" (
    xcopy /E /I /Y "x86_64-w64-mingw32\include\SDL3" "C:\SDL3\include\SDL3"
    echo [OK] Headers copied
) else if exist "x86_64-w64-mingw32\include\SDL2" (
    echo [WARNING] Found SDL2 headers instead of SDL3
    echo This might be SDL2, not SDL3. Continuing anyway...
    xcopy /E /I /Y "x86_64-w64-mingw32\include\SDL2" "C:\SDL3\include\SDL3"
    echo [OK] Headers copied (renamed to SDL3)
) else (
    echo [ERROR] Headers not found!
    echo Looking for include folder...
    if exist "x86_64-w64-mingw32\include" (
        dir /B "x86_64-w64-mingw32\include"
    )
    pause
    exit /b 1
)
echo.

REM Copy libraries
echo Copying libraries...
if exist "x86_64-w64-mingw32\lib" (
    copy /Y "x86_64-w64-mingw32\lib\*.a" "C:\SDL3\lib\x64\"
    if errorlevel 1 (
        echo [WARNING] No .a files found, checking for .lib files...
        copy /Y "x86_64-w64-mingw32\lib\*.lib" "C:\SDL3\lib\x64\"
    )
    echo [OK] Libraries copied
) else (
    echo [ERROR] Libraries not found!
    pause
    exit /b 1
)
echo.

REM Copy DLL (SDL3.dll or SDL2.dll)
echo Copying DLL...
if exist "x86_64-w64-mingw32\bin\SDL3.dll" (
    copy /Y "x86_64-w64-mingw32\bin\SDL3.dll" "C:\SDL3\bin\x64\"
    echo [OK] SDL3.dll copied
) else if exist "x86_64-w64-mingw32\bin\SDL2.dll" (
    echo [WARNING] Found SDL2.dll instead of SDL3.dll
    echo This might be SDL2, not SDL3. Copying anyway...
    copy /Y "x86_64-w64-mingw32\bin\SDL2.dll" "C:\SDL3\bin\x64\SDL3.dll"
    echo [OK] DLL copied (renamed to SDL3.dll)
) else (
    echo [ERROR] DLL not found!
    echo Looking for DLL files...
    if exist "x86_64-w64-mingw32\bin" (
        dir /B "x86_64-w64-mingw32\bin\*.dll"
    )
    pause
    exit /b 1
)
echo.

echo ========================================
echo Verification
echo ========================================
echo.

if exist "C:\SDL3\include\SDL3\SDL.h" (
    echo [OK] Headers installed at C:\SDL3\include\SDL3\SDL.h
) else if exist "C:\SDL3\include\SDL2\SDL.h" (
    echo [WARNING] Found SDL2 headers (this might be SDL2, not SDL3)
) else (
    echo [ERROR] Headers missing!
)

if exist "C:\SDL3\lib\x64\libSDL3.a" (
    echo [OK] SDL3 libraries installed
) else if exist "C:\SDL3\lib\x64\SDL3.lib" (
    echo [OK] SDL3 libraries installed (.lib format)
) else if exist "C:\SDL3\lib\x64\libSDL2.a" (
    echo [WARNING] Found SDL2 libraries (this might be SDL2, not SDL3)
) else (
    echo [ERROR] Libraries missing!
    echo Checking what's in lib\x64...
    if exist "C:\SDL3\lib\x64" (
        dir /B "C:\SDL3\lib\x64"
    )
)

if exist "C:\SDL3\bin\x64\SDL3.dll" (
    echo [OK] SDL3.dll installed
) else (
    echo [ERROR] SDL3.dll missing!
)

echo.
echo ========================================
echo Setup Complete!
echo ========================================
echo.
echo SDL3 is now installed at C:\SDL3
echo The build system will automatically find it.
echo.
pause

