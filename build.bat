@echo off
if exist build (
    echo [INFO] build 資料夾已存在，跳過 CMake 配置。
) else (
    echo [INFO] build 資料夾不存在，執行 CMake...
    cmake -DCMAKE_BUILD_TYPE=Debug -B build
)
echo 正在編譯專案...
cmake --build build
echo 完成！
pause
