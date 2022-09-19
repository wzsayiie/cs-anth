@echo off

setlocal

cd %~dp0

:: create library directories.
if not exist bin ( md bin )
if not exist lib ( md lib )

:: build libraries:
cl  /nologo /LD /Fe"lib\host.dll" /I"libhost" libhost\*_all.c libhost\*_win.c
del *.obj

cl  /nologo /c /I"libextend" /I"libhost" /I"libspec" libextend\*.c
lib /nologo /out:lib\extend.lib *.obj
del *.obj

cl  /nologo /c /I"libextend" /I"libhost" /I"libspec" libspec\*.c
lib /nologo /out:lib\spec.lib *.obj
del *.obj

:: build cmdsh:
copy lib\host.dll host.dll

cl  /nologo        ^
    /Fe"cmdsh"     ^
    /I"libextend"  ^
    /I"libhost"    ^
    /I"libspec"    ^
    lib\extend.lib ^
    lib\host.lib   ^
    lib\spec.lib   ^
    cmdsh.c

del *.obj

endlocal
