@echo off
SET errors=0
FOR /L %%G IN (0,1,1000) DO (call :subroutine)

echo %errors%

GOTO :eof

:subroutine

call OS2.exe >nul
set /a "errors=%errors%+%ERRORLEVEL%"

GOTO :eof