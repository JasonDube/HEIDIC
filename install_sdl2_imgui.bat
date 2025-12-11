@echo off
setlocal enabledelayedexpansion

echo ========================================
echo Installing SDL2 and ImGui for EDEN Engine
echo ========================================
echo.

REM Check if running as administrator (optional, but helpful)
net session >nul 2>&1
if %errorLevel% == 0 (
    echo Running with administrator privileges
) else (
    echo Running without administrator privileges (may need admin for C:\SDL2)
)
echo.

REM ========================================
REM Install SDL2
REM ========================================
echo [1/2] Installing SDL2...
echo.

set SDL2_INSTALL_DIR=C:\SDL2
set SDL2_URL=https://github.com/libsdl-org/SDL/releases/download/release-2.30.0/SDL2-devel-2.30.0-mingw.tar.gz

if exist "%SDL2_INSTALL_DIR%\include\SDL2\SDL.h" (
    echo SDL2 already installed at %SDL2_INSTALL_DIR%
    echo Skipping SDL2 installation...
) else (
    echo Downloading SDL2...
    echo URL: %SDL2_URL%
    echo.
    echo NOTE: This script will download SDL2 to a temp directory.
    echo For Windows, you may need to manually download from:
    echo https://github.com/libsdl-org/SDL/releases/download/release-2.30.0/SDL2-devel-2.30.0-mingw.tar.gz
    echo.
    echo Or use the Windows installer from:
    echo https://www.libsdl.org/download-2.0.php
    echo.
    echo After downloading, extract to %SDL2_INSTALL_DIR%
    echo.
    pause
)

REM ========================================
REM Install ImGui
REM ========================================
echo.
echo [2/2] Installing ImGui...
echo.

set IMGUI_INSTALL_DIR=third_party\imgui
set IMGUI_URL=https://github.com/ocornut/imgui/archive/refs/heads/master.zip

if exist "%IMGUI_INSTALL_DIR%\imgui.h" (
    echo ImGui already installed at %IMGUI_INSTALL_DIR%
    echo Skipping ImGui installation...
) else (
    echo Creating directory: %IMGUI_INSTALL_DIR%
    if not exist "third_party" mkdir third_party
    if not exist "%IMGUI_INSTALL_DIR%" mkdir "%IMGUI_INSTALL_DIR%"
    
    echo Downloading ImGui from GitHub...
    echo URL: %IMGUI_URL%
    echo.
    
    REM Try to download using PowerShell
    powershell -Command "& {[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12; Invoke-WebRequest -Uri '%IMGUI_URL%' -OutFile 'imgui-master.zip'}"
    
    if exist "imgui-master.zip" (
        echo Extracting ImGui...
        REM Try to extract using PowerShell
        powershell -Command "& {Expand-Archive -Path 'imgui-master.zip' -DestinationPath 'temp_imgui' -Force}"
        
        if exist "temp_imgui\imgui-master\imgui.h" (
            echo Copying ImGui files...
            xcopy /E /I /Y "temp_imgui\imgui-master\*" "%IMGUI_INSTALL_DIR%\"
            echo Cleaning up...
            rmdir /S /Q temp_imgui
            del imgui-master.zip
            echo ImGui installed successfully!
        ) else (
            echo ERROR: Failed to extract ImGui
            echo Please manually download from: https://github.com/ocornut/imgui
            echo And extract to: %IMGUI_INSTALL_DIR%
        )
    ) else (
        echo ERROR: Failed to download ImGui
        echo Please manually download from: https://github.com/ocornut/imgui
        echo And extract to: %IMGUI_INSTALL_DIR%
    )
)

echo.
echo ========================================
echo Installation Summary
echo ========================================
echo.

if exist "%SDL2_INSTALL_DIR%\include\SDL2\SDL.h" (
    echo [OK] SDL2 installed at: %SDL2_INSTALL_DIR%
) else (
    echo [MISSING] SDL2 not found at: %SDL2_INSTALL_DIR%
    echo   Please download from: https://www.libsdl.org/download-2.0.php
    echo   Extract to: %SDL2_INSTALL_DIR%
)

if exist "%IMGUI_INSTALL_DIR%\imgui.h" (
    echo [OK] ImGui installed at: %IMGUI_INSTALL_DIR%
) else (
    echo [MISSING] ImGui not found at: %IMGUI_INSTALL_DIR%
    echo   Please download from: https://github.com/ocornut/imgui
    echo   Extract to: %IMGUI_INSTALL_DIR%
)

echo.
echo ========================================
echo Next Steps
echo ========================================
echo.
echo 1. If SDL2 is missing, download and extract it manually
echo 2. Set environment variable (optional): set SDL2_PATH=%SDL2_INSTALL_DIR%
echo 3. The build system will automatically find ImGui at: %IMGUI_INSTALL_DIR%
echo.
pause

