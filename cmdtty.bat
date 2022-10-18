@echo off

:: root directory.
set ANTH_HOME=%~dp0
if %ANTH_HOME:~-1%==\ (
    ::remove backslash at the end.
    set ANTH_HOME=%ANTH_HOME:~0,-1%
)

:: prompt string.
prompt $e[32m$p$s$e[37m$g$e[0m$s

:: environment.
set PATH=^
%ANTH_HOME%\bin;^
%ANTH_HOME%\lib;^
%PATH%

:: commands.
doskey cd    = cd  /d $1
doskey ls    = dir /d $*
doskey open  = start "" $*
doskey which = where $*

:: user rc.
if exist %ANTH_HOME%\urc.bat (
    call %ANTH_HOME%\urc.bat
)
