@echo off

setlocal

cd %~dp0

:: create library directories.
if not exist bin ( md bin )
if not exist lib ( md lib )

:: build the host library:
pushd alibh

cl  /nologo             ^
    /LD                 ^
    /Fe"..\lib\h.dll"   ^
    *_all.c             ^
    *_win.c

del *.obj

popd

:: build cmdsh:
cl  /nologo             ^
    /Fe"cmdsh"          ^
    /I"alibc"           ^
    /I"alibh"           ^
    /I"srcutils"        ^
    alibc\libgen.c      ^
    srcutils\strutil.c  ^
    cmdsh.c             ^
    lib\h.lib

del  *.obj
copy lib\h.dll h.dll

endlocal
