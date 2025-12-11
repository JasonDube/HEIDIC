@echo off
echo ========================================
echo SDL2 Setup Script for EDEN Engine
echo ========================================
echo.
echo Current directory: %CD%
echo.

REM Force continue - assume folder exists if we can see it
echo Checking for x86_64-w64-mingw32...
dir /B /AD | findstr /I "x86_64" >nul
if errorlevel 1 (
    echo ERROR: x86_64-w64-mingw32 folder not found!
    echo Please run this from the SDL2 extracted directory.
    pause
    exit /b 1
)

echo [OK] Found x86_64-w64-mingw32 folder
echo.

REM Create C:\SDL2 structure
echo Creating C:\SDL2 directory structure...
if not exist "C:\SDL2" (
    mkdir "C:\SDL2"
    if errorlevel 1 (
        echo ERROR: Failed to create C:\SDL2
        echo You may need to run as Administrator
        pause
        exit /b 1
    )
)
mkdir "C:\SDL2\include" 2>nul
mkdir "C:\SDL2\lib" 2>nul
mkdir "C:\SDL2\lib\x64" 2>nul
mkdir "C:\SDL2\bin" 2>nul
mkdir "C:\SDL2\bin\x64" 2>nul
echo [OK] Directory structure created
echo.

REM Copy headers
echo Copying headers...
if exist "x86_64-w64-mingw32\include\SDL2" (
    xcopy /E /I /Y "x86_64-w64-mingw32\include\SDL2" "C:\SDL2\include\SDL2"
    echo [OK] Headers copied
) else (
    echo [ERROR] Headers not found!
    pause
    exit /b 1
)
echo.

REM Copy libraries
echo Copying libraries...
if exist "x86_64-w64-mingw32\lib" (
    copy /Y "x86_64-w64-mingw32\lib\*.a" "C:\SDL2\lib\x64\"
    echo [OK] Libraries copied
) else (
    echo [ERROR] Libraries not found!
    pause
    exit /b 1
)
echo.

REM Copy DLL
echo Copying DLL...
if exist "x86_64-w64-mingw32\bin\SDL2.dll" (
    copy /Y "x86_64-w64-mingw32\bin\SDL2.dll" "C:\SDL2\bin\x64\"
    echo [OK] DLL copied
) else (
    echo [ERROR] DLL not found!
    pause
    exit /b 1
)
echo.

echo ========================================
echo Verification
echo ========================================
echo.

if exist "C:\SDL2\include\SDL2\SDL.h" (
    echo [OK] Headers installed
) else (
    echo [ERROR] Headers missing!
)

if exist "C:\SDL2\lib\x64\libSDL2.a" (
    echo [OK] Libraries installed
) else (
    echo [ERROR] Libraries missing!
)

if exist "C:\SDL2\bin\x64\SDL2.dll" (
    echo [OK] DLL installed
) else (
    echo [ERROR] DLL missing!
)

echo.
echo ========================================
echo Setup Complete!
echo ========================================
echo.
pause

