@echo off

if exist "Builds" (
    echo Directory builds\ already exists.
) else (
    echo Creating builds directory...
    mkdir builds
)


pushd builds
cmake -G "Visual Studio 17 2022" -A x64 ..
popd