@echo off
setlocal enabledelayedexpansion

echo ========================================
echo SDL2 Setup Script for EDEN Engine
echo ========================================
echo.
echo Current directory: %CD%
echo.

REM Check if we're in the SDL2 extracted directory
echo Checking for x86_64-w64-mingw32 folder...
set FOUND_FOLDER=0

if exist "x86_64-w64-mingw32" (
    echo [OK] Found x86_64-w64-mingw32 folder!
    set FOUND_FOLDER=1
    goto :found_folder
)

if exist ".\x86_64-w64-mingw32" (
    echo [OK] Found using .\x86_64-w64-mingw32 path
    set FOUND_FOLDER=1
    goto :found_folder
)

echo [INFO] Standard path check didn't find it, but let's check what's here...
echo.
echo Listing current directory contents:
dir /B
echo.
echo Looking for folders with "x86" in name:
dir /B /AD | findstr /I "x86"
echo.

REM If we can see it in dir listing, try to use it anyway
for /d %%d in (x86*) do (
    if /i "%%d"=="x86_64-w64-mingw32" (
        echo [OK] Found folder: %%d
        set FOUND_FOLDER=1
        goto :found_folder
    )
)

if %FOUND_FOLDER%==0 (
    echo.
    echo ERROR: Cannot find x86_64-w64-mingw32 folder!
    echo.
    echo Please make sure you're running this script from the folder that contains x86_64-w64-mingw32
    echo.
    pause
    exit /b 1
)

:found_folder
echo.
echo ========================================
echo Starting SDL2 Installation
echo ========================================
echo.

echo Found SDL2 MinGW build structure
echo.

REM Create C:\SDL2 structure
echo Creating C:\SDL2 directory structure...
if not exist "C:\SDL2" (
    echo   Creating C:\SDL2...
    mkdir "C:\SDL2"
    if errorlevel 1 (
        echo   ERROR: Failed to create C:\SDL2 - may need administrator privileges
        pause
        exit /b 1
    )
    echo   [OK] C:\SDL2 created
) else (
    echo   [OK] C:\SDL2 already exists
)

if not exist "C:\SDL2\include" (
    mkdir "C:\SDL2\include"
    echo   [OK] Created include folder
)
if not exist "C:\SDL2\lib" (
    mkdir "C:\SDL2\lib"
    echo   [OK] Created lib folder
)
if not exist "C:\SDL2\lib\x64" (
    mkdir "C:\SDL2\lib\x64"
    echo   [OK] Created lib\x64 folder
)
if not exist "C:\SDL2\bin" (
    mkdir "C:\SDL2\bin"
    echo   [OK] Created bin folder
)
if not exist "C:\SDL2\bin\x64" (
    mkdir "C:\SDL2\bin\x64"
    echo   [OK] Created bin\x64 folder
)

echo.
echo Copying files...

REM Copy headers
echo.
echo Checking for headers...
if exist "x86_64-w64-mingw32\include\SDL2" (
    echo   Found: x86_64-w64-mingw32\include\SDL2
    echo   Copying headers to C:\SDL2\include\SDL2...
    xcopy /E /I /Y "x86_64-w64-mingw32\include\SDL2" "C:\SDL2\include\SDL2"
    if errorlevel 1 (
        echo   [ERROR] Failed to copy headers!
    ) else (
        echo   [OK] Headers copied successfully
    )
) else (
    echo   [WARNING] Headers not found at x86_64-w64-mingw32\include\SDL2
    echo   Checking what's in x86_64-w64-mingw32\include...
    if exist "x86_64-w64-mingw32\include" (
        dir /B "x86_64-w64-mingw32\include"
    ) else (
        echo   x86_64-w64-mingw32\include folder doesn't exist!
    )
)

REM Copy libraries
echo.
echo Checking for libraries...
if exist "x86_64-w64-mingw32\lib" (
    echo   Found: x86_64-w64-mingw32\lib
    echo   Copying libraries to C:\SDL2\lib\x64\...
    copy /Y "x86_64-w64-mingw32\lib\*.a" "C:\SDL2\lib\x64\"
    if errorlevel 1 (
        echo   [WARNING] No .a files found or copy failed
        echo   Checking what's in x86_64-w64-mingw32\lib...
        dir /B "x86_64-w64-mingw32\lib"
    ) else (
        echo   [OK] Libraries copied successfully
        dir /B "C:\SDL2\lib\x64\*.a"
    )
) else (
    echo   [WARNING] lib folder not found at x86_64-w64-mingw32\lib
)

REM Copy DLL
echo.
echo Checking for DLL...
if exist "x86_64-w64-mingw32\bin\SDL2.dll" (
    echo   Found: x86_64-w64-mingw32\bin\SDL2.dll
    echo   Copying DLL to C:\SDL2\bin\x64\...
    copy /Y "x86_64-w64-mingw32\bin\SDL2.dll" "C:\SDL2\bin\x64\"
    if errorlevel 1 (
        echo   [ERROR] Failed to copy DLL!
    ) else (
        echo   [OK] DLL copied successfully
    )
) else (
    echo   [WARNING] SDL2.dll not found at x86_64-w64-mingw32\bin\SDL2.dll
    echo   Checking what's in x86_64-w64-mingw32\bin...
    if exist "x86_64-w64-mingw32\bin" (
        dir /B "x86_64-w64-mingw32\bin"
    ) else (
        echo   x86_64-w64-mingw32\bin folder doesn't exist!
    )
)

echo.
echo ========================================
echo Verification
echo ========================================
echo.

if exist "C:\SDL2\include\SDL2\SDL.h" (
    echo [OK] Headers: C:\SDL2\include\SDL2\SDL.h
) else (
    echo [MISSING] Headers: C:\SDL2\include\SDL2\SDL.h
)

if exist "C:\SDL2\lib\x64\libSDL2.a" (
    echo [OK] Library: C:\SDL2\lib\x64\libSDL2.a
) else if exist "C:\SDL2\lib\x64\SDL2.lib" (
    echo [OK] Library: C:\SDL2\lib\x64\SDL2.lib
) else (
    echo [MISSING] Library: C:\SDL2\lib\x64\libSDL2.a or SDL2.lib
)

if exist "C:\SDL2\bin\x64\SDL2.dll" (
    echo [OK] DLL: C:\SDL2\bin\x64\SDL2.dll
) else (
    echo [MISSING] DLL: C:\SDL2\bin\x64\SDL2.dll
)

echo.
echo ========================================
echo Setup Complete!
echo ========================================
echo.
echo SDL2 is now installed at C:\SDL2
echo The build system will automatically find it.
echo.
pause

