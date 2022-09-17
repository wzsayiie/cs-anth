@echo off

setlocal

cd %~dp0

:: create library directories.
if not exist bin ( md bin )
if not exist lib ( md lib )

:: build libraries:
cl  /nologo /LD /Fe"lib\ah.dll" /I"libah" libah\*_all.c libah\*_win.c
del *.obj

cl  /nologo /c /I"libac" /I"libaex" /I"libah" libac\*.c
lib /nologo /out:lib\ac.lib *.obj
del *.obj

cl  /nologo /c /I"libac" /I"libaex" /I"libah" libaex\*.c
lib /nologo /out:lib\aex.lib *.obj
del *.obj

:: build cmdsh:
copy lib\ah.dll ah.dll

cl  /nologo     ^
    /Fe"cmdsh"  ^
    /I"libac"   ^
    /I"libaex"  ^
    /I"libah"   ^
    lib\ac.lib  ^
    lib\aex.lib ^
    lib\ah.lib  ^
    cmdsh.c

del *.obj

endlocal
