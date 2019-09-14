::@set EchoEnable=1
::@set EchoCmd=1
@if {%EchoEnable%}=={1} ( @echo on ) else ( @echo off )
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*

set targetFolderName=
set bShowCopy=1

pushd %~dp0..
set libDir=%cd%
popd

rem for %%* in (.) do set libName=%%~nx*
for %%* in (%libDir%) do set libName=%%~nx*
if {%targetFolderName%}=={} set targetFolderName=%libName%_%~2%date:~0,4%%date:~5,2%%date:~8,2%_%time:~0,2%%time:~3,2%%time:~6,2%
set targetFolderName=%targetFolderName: =0%
set targetPath=%libDir%\%targetFolderName%
call :deleteUnversionedFiles "%libDir%\sources"
if exist "%targetPath%" rmdir /S /Q "%targetPath%"
::xcopy/s "%libDir%\sources"  "%targetPath%\"
call :copyDir tools 1>NUL
call :copyDir sources\MiniMPL 1>NUL
call :copyDir sources\UnitTest\UnitTestKit 1>NUL
call :copyDir sources\UnitTest\UT_MiniMPL 1>NUL
copy "%libDir%\sources\KitLibTest.sln"  "%targetPath%\sources"
rem %targetPath%\sources\KitLibTest.sln
goto :End

:openAllRunExample
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
if {%2}=={} goto :eof
if not exist "%~1" @echo %~2 >> "%~1" & goto :eof
if exist $ del /f/q $
set /a n=0,m=0
for /f "usebackq delims=" %%a in (` findstr /n .* %~1 `) do set /a m+=1
( for /f "usebackq tokens=1,* delims=:" %%a in (` findstr /n .* %~1 `) do (
  @set /a n+=1
  @set /a "1/(m-n)" 2>nul || @echo %~2
  @echo.%%b
)) >> $
del /q/f "%~1"
move $ "%~1" >nul
exit /b 0

:copyDir
if not exist "%libDir%\%~1" echo No "%libDir%\%~1" & goto :eof
call :CreateFolder "%targetPath%\%~1"
xcopy/s "%libDir%\%~1"  "%targetPath%\%~1\"
goto :End

:CreateFolder
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
if {%~1}=={} goto :eof
call :CreateFolderImpl "%~dp1"
goto :eof

:CreateFolderImpl
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
set CreateFolderImplFlodName="%~dp1"
if not exist %CreateFolderImplFlodName% (
if not exist "%~dp1..\" call :CreateFolder "%~dp1..\"
echo mkdir %CreateFolderImplFlodName%
mkdir %CreateFolderImplFlodName%
)
goto :eof

:deleteUnversionedFiles
if {%EchoCmd%}=={1} @echo [%~nx0] commandLine: %0 %*
if not exist "%~1" echo path doesn't exist & goto :End
Echo deleting unversioned controned svn file and directroy......
set /a files=0
set /a directorys=0
for /f "usebackq tokens=2" %%i in ( ` svn status "%~1" ^| find "?" ` ) do ( 
if exist %%i\ 		rd /S /Q 			%%i & set /a directorys=!directorys!+1
if exist %%i 		del /F /Q /A:-S 	%%i & set /a files=!files!+1
)
echo [summary] delete !files! files and !directorys! directorys!
echo.
set createSolution=1
set useIncrediBuild=0
goto :eof

:End
if {%EchoCmd%}=={1} @echo [Leave %~nx0] commandLine: %0 %*