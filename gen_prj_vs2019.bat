@echo off

if exist "builds" (
    echo Directory builds\ already exists.
) else (
    echo Creating builds directory...
    mkdir builds
)


pushd builds
cmake -G "Visual Studio 16 2019" -A x64 ..
popd