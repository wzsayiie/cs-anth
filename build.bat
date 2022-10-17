@echo off

setlocal

cd %~dp0

:: directories.
if not exist bin ( md bin )
if not exist lib ( md lib )

:: host.dll.
cl  /nologo /LD /Fe"lib\host.dll" /I"libhost" libhost\*_all.c libhost\*_win.c
del *.obj

:: extend.lib.
cl  /nologo /c /I"libextend" /I"libhost" /I"libspec" libextend\*.c
lib /nologo /out:lib\extend.lib *.obj
del *.obj

:: spec.lib.
cl  /nologo /c /I"libextend" /I"libhost" /I"libspec" libspec\*.c
lib /nologo /out:lib\spec.lib *.obj
del *.obj

endlocal
