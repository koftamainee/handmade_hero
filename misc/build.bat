@echo off

mkdir build
pushd build

dir
cl /Zi ..\code\win32_main.cpp user32.lib

popd