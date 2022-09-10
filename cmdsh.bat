@echo off

::root directory.
set ANTH_HOME=%~dp0
if %ANTH_HOME:~-1%==\ (
    ::remove backslash at the end.
    set ANTH_HOME=%ANTH_HOME:~0,-1%
)

::"path".
set PATH=%PATH%;%ANTH_HOME%\bin

::commands.
doskey cat   = type $*
doskey cd    = cd /d $1
doskey clear = cls
doskey ls    = dir /d $*
doskey mv    = move $*
doskey open  = start "" $*
doskey which = where $*

::shell configuration.
prompt $p$s%%$s

::user configutation.
if exist %ANTH_HOME%\ucfg.bat (
    call %ANTH_HOME%\ucfg.bat
)
