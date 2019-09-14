
echo off
if not {%~1}=={} (set dt=%~1) else set dt=2

Echo deleting unversioned controned svn file and directroy......
set /a files=0
set /a directorys=0
for /f "usebackq tokens=1,*" %%i in ( ` svn status "%cd%\.." ^| find "?" ` ) do ( 
if exist "%%j\" 	rd /S /Q 			"%%j" & set /a directorys=%directorys%+1
if exist "%%j" 		del /F /Q /A:-S 	"%%j" & set /a files=%files%+1
)
echo [summary] delete %files% files and %directorys% directorys%

ping -n %dt% 127.0.0.1 > nul
echo.