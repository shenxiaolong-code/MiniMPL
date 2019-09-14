@echo off
@title %0
:Input
cls
@echo pls input file name (xxx.h or xxx.hpp)
set /p headFile=
if not {"%headFile%"}=={""} (
call %~dp0\creatNewFiles.bat %headFile%
set headFile=
)

pause
goto :Input