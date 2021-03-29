@echo off
rem -----------------Configuration-----------------
set UPXDIR="C:\Users\Ferlix\Desktop\upx-3.96-win64"
set MINGWDIR="C:\Program Files\CodeBlocks\MinGW\bin"
rem -----------------------------------------------
cls
title Aerox Builder
echo Aerox builder by Legacy. Fails silently. Check your build after running.
del /f /q main.exe main.upx.exe > NUL
set SRCDIR=%CD%
echo Compiling...
cd %MINGWDIR%
gcc %SRCDIR%\main.c -o %SRCDIR%\main.exe -O3 -lwsock32 -w
echo Packing...
%UPXDIR%\upx -9 -f %SRCDIR%\main.exe -o %SRCDIR%\main.upx.exe > NUL
cd %SRCDIR%
echo Done.