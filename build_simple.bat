@echo off
chcp 65001 > nul

set RUN_AFTER_BUILD=%1

echo 🔨 CMake 빌드 시작...

cd /d "C:\Users\hong0\Desktop\study\miniProject1"

if not exist build mkdir build
cd build

echo ⚙️  CMake 설정...
cmake ..

if errorlevel 1 (
    echo ❌ CMake 설정 실패!
    pause
    exit /b 1
)

echo 🔧 빌드 중...
cmake --build .

if errorlevel 1 (
    echo ❌ 빌드 실패!
    pause
    exit /b 1
)

echo ✅ 빌드 완료!

REM 실행 파일 찾기
set EXE_PATH=
if exist "Debug\*.exe" (
    for %%f in ("Debug\*.exe") do set EXE_PATH=%%f
) else if exist "Release\*.exe" (
    for %%f in ("Release\*.exe") do set EXE_PATH=%%f
) else if exist "*.exe" (
    for %%f in ("*.exe") do set EXE_PATH=%%f
)

REM 첫 번째 인자가 "run"이면 새로운 PowerShell에서 실행
if /i "%RUN_AFTER_BUILD%"=="run" (
    if defined EXE_PATH (
        echo 🚀 새로운 PowerShell에서 프로그램 실행 중...
        echo 실행 파일: %EXE_PATH%
        start powershell -NoExit -Command "$Host.UI.RawUI.WindowSize = New-Object System.Management.Automation.Host.Size(120, 30); $Host.UI.RawUI.BufferSize = New-Object System.Management.Automation.Host.Size(120, 3000); Clear-Host; cd '%CD%'; Write-Host '🎮 프로그램 실행:' -ForegroundColor Green; Write-Host '%EXE_PATH%' -ForegroundColor Cyan; Write-Host ''; & '.\%EXE_PATH%'"
    ) else (
        echo ⚠️  실행 파일을 찾을 수 없습니다.
    )
) else (
    if defined EXE_PATH (
        echo 📁 실행 파일: %EXE_PATH%
        echo 💡 실행하려면: build_simple.bat run
    )
)

pause