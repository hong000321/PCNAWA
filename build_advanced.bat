@echo off
chcp 65001 > nul
setlocal enabledelayedexpansion

echo.
echo ===============================================
echo       고급 CMake 빌드 스크립트
echo ===============================================
echo.

REM 설정 변수
set PROJECT_DIR=C:\Users\hong0\Desktop\study\miniProject1
set BUILD_DIR=%PROJECT_DIR%\build

REM 명령행 인수 처리
set BUILD_TYPE=Debug
set CLEAN_BUILD=false
set RUN_AFTER_BUILD=false

:parse_args
if "%~1"=="" goto start_build
if /i "%~1"=="clean" set CLEAN_BUILD=true
if /i "%~1"=="release" set BUILD_TYPE=Release
if /i "%~1"=="debug" set BUILD_TYPE=Debug
if /i "%~1"=="run" set RUN_AFTER_BUILD=true
shift
goto parse_args

:start_build
echo 🔧 빌드 설정:
echo    - 빌드 타입: %BUILD_TYPE%
echo    - 클린 빌드: %CLEAN_BUILD%
echo    - 빌드 후 실행: %RUN_AFTER_BUILD%
echo.

REM 프로젝트 디렉토리로 이동
cd /d "%PROJECT_DIR%"
if errorlevel 1 (
    echo ❌ 오류: 프로젝트 디렉토리를 찾을 수 없습니다.
    goto error_exit
)

REM 클린 빌드인 경우 build 디렉토리 삭제
if "%CLEAN_BUILD%"=="true" (
    echo 🧹 클린 빌드: build 디렉토리 삭제 중...
    if exist "%BUILD_DIR%" (
        rmdir /s /q "%BUILD_DIR%"
        if errorlevel 1 (
            echo ❌ build 디렉토리 삭제 실패
            goto error_exit
        )
    )
    echo ✅ 클린 완료
    echo.
)

REM build 디렉토리 생성 및 이동
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd /d "%BUILD_DIR%"

REM CMake 설정
echo 🔧 CMake 설정 중... (빌드 타입: %BUILD_TYPE%)
cmake .. -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
if errorlevel 1 (
    echo ❌ CMake 설정 실패
    goto error_exit
)

REM 빌드 실행
echo 🔨 빌드 실행 중...
cmake --build . --config %BUILD_TYPE%
if errorlevel 1 (
    echo ❌ 빌드 실패
    goto error_exit
)

echo.
echo ✅ 빌드 성공!

REM 실행 파일 찾기
set EXE_PATH=
if exist "%BUILD_DIR%\%BUILD_TYPE%\*.exe" (
    for %%f in ("%BUILD_DIR%\%BUILD_TYPE%\*.exe") do set EXE_PATH=%%f
) else if exist "%BUILD_DIR%\*.exe" (
    for %%f in ("%BUILD_DIR%\*.exe") do set EXE_PATH=%%f
)

if defined EXE_PATH (
    echo 📁 실행 파일: !EXE_PATH!
    
    if "%RUN_AFTER_BUILD%"=="true" (
        echo.
        echo 🚀 프로그램 실행 중...
        echo ===============================================
        "!EXE_PATH!"
        echo ===============================================
    )
) else (
    echo ⚠️  실행 파일을 찾을 수 없습니다.
)

echo.
echo 🎉 모든 작업 완료!
goto normal_exit

:error_exit
echo.
echo ❌ 스크립트 실행 중 오류가 발생했습니다.
pause
exit /b 1

:normal_exit
echo.
echo 사용법:
echo   %~nx0 [옵션]
echo.
echo 옵션:
echo   clean    - 클린 빌드 (build 폴더 삭제 후 빌드)
echo   release  - Release 모드로 빌드
echo   debug    - Debug 모드로 빌드 (기본값)
echo   run      - 빌드 후 프로그램 자동 실행
echo.
echo 예시:
echo   %~nx0 clean release run
echo.
pause