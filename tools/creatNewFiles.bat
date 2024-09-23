::this script used to create cpp file (.h/.cpp or .hpp) and according unit test file (test_xxx.hpp or test_xxx.cpp).
::directory structure refer to folderLayout.txt
::usage: creatNewFiles.bat myClassName
::example1: creatNewFiles.bat myName.h
::myName.h/myName.cpp/test_myName.cpp will be created by specified directory structure (it is decided by "folderLayout")
::example2: creatNewFiles.bat myName.hpp
::myName.hpp/test_myName.hpp/hppTestList.cpp will be created by specified directory structure (it is decided by "folderLayout")
::if hppTestList.cpp already exists, script only updates hppTestList.cpp.
::if NO extension name, default extension name is .h

@set EchoEnable=0
@set EchoCmd=0
@if {%EchoEnable%}=={1} ( @echo on ) else ( @echo off )
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*

@title %0 %*
if not defined NotResetVarialbe call :undefVariable
::********************Config begin***************************************
call :quickConfig_MiniMPL
rem call :quickConfig_OsBase
call :quickConfig_default
call :execute %*
goto :End

:quickConfig_default
::set default quick config for not defined config. it is also complete config example
::for .h/.cpp, innerImplement indicates current header file lies in src\...\inc folder, instead of include folder
::for .hpp, innerImplement indicates current header file lies in include\innerDetail folder, instead of include folder directly
if not defined innerImplement 	            set innerImplement=0
:: set namespace config
if not defined bAddNamespace 	            set bAddNamespace=0
if not defined MPLProject 		            set MPLProject=MiniMPL
::override default config
if not defined componmentName               set componmentName=%projectName%

::set svn config
if not defined bAddIntoSvn 		            set bAddIntoSvn=1
if not defined bGuardHeadWithProjectName 	set bGuardHeadWithProjectName=1

::set general folder name
if not defined srcFolderName                set srcFolderName=src
if not defined headFolderName               set headFolderName=include
if not defined innerFolerName_hpp           set innerFolerName_hpp=innerDetail
if not defined innerFolerName_h             set innerFolerName_h=inc

::set test config
goto :eof
::********************Config end*****************************************

:quickConfig_MiniMPL
set projectName=MiniMPL
::set subFolderName=innerDetail
:: set namespace config
set bAddNamespace=1
set defNamespace=MiniMPL
set headFolderName=include/%projectName%
goto :eof

:quickConfig_OsBase
set projectName=OsBase
:: set namespace config
set componmentName=thread
set subFolderName=
set bAddNamespace=0
set defNamespace=OS_Win32
goto :eof

::example
:: projectName\implmentFolerName\componmentName\innerFolerName_hpp\.hpp
:: projectName\implmentFolerName\componmentName\innerFolerName_h\.h
:: MiniMPL\include\MiniMPL\featureSrc.h
:: MiniMPL\include\MiniMPL\innerDetail\featureSrc.hpp
:: MiniMPL\src\featureSrc.cpp
:: OsBase\include\thread\featureSrc.h
:: OsBase\src\thread\inc\featureSrc.h
:: OsBase\src\thread\featureSrc.cpp
:: name variable
:: ProjectName  , headFolderName , srcFolderName , innerFolerName_hpp , innerFolerName_h

:execute
pushd %~dp0..\
set rootDir=%cd%\sources
popd
set fullFileName=%~1
set hpp_=.hpp
set h_=.h
set testFolderName=UnitTests
set tcKitFolderName=UnitTestKit

::set comment head info
set "AuthorInfo=Shen.Xiaolong ^(at %date%^) , xlshen@126.com  xlshen2002@hotmail.com"
set "CopyrightInfo=free to use / modify / sale in free and commercial software with those head comments."

if {%fullFileName%}=={} @echo Empty parameter & goto :End
call :parseFileName %fullFileName%
if not {%~2}=={} set modeDelete=1
if {%~2}=={} set modeDelete=0

call :resetFile
call :SetFilePath
call :SetUpperCaseMacro
::Only clear file
if {%modeDelete%}=={1} call :revertAdd & goto :End

call :CreateHeadFile
call :CreateCppFile
call :CreateTestHeadFile
call :CreateTestCppFile
call :CreateTestMainEntry
goto :eof

:resetFile
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
set subFolder_Path=
set headFile=
set cppFile=
set testCppFile=
goto :eof

:undefVariable
set projectName=
set componmentName=
set subFolderName=
set bAddNamespace=
set defNamespace=
set MPLProject=
set bAddIntoSvn=
set bGuardHeadWithProjectName=
set innerImplement=
goto :eof

:dumpOutFile
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
@echo dump output files:
@echo headFile=%headFile%
@echo cppFile=%cppFile%
@echo testCppFile=%testCppFile%
@echo.
goto :eof

:SetMiddleVars
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
set projectPath=%rootDir%\%projectName%
set projectPath_UT=%rootDir%\UnitTest\UT_%projectName%

if      {"%projectName%"}=={"%componmentName%"} set implementComponmentName=
if not  {"%projectName%"}=={"%componmentName%"} set implementComponmentName=%componmentName%

rem path is used in source file (.h/.hpp/.cpp), tailed with '/'
rem dir is used file system path, tailed with '\'
set subFolder_Path=
set subFolder_Dir=
if not {%subFolderName%}=={} (
set subFolder_Path=%subFolderName%/
set subFolder_Dir=%subFolderName%\
)

set implementFolder=%headFolderName%
set innerHead_Path=
if {%innerImplement%}=={1} (
set implementFolder=%srcFolderName%
set innerHead_Path=%innerFolerName_h%/
)
goto :eof

:SetFilePath
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
call :SetMiddleVars
call :SetFilePath%extName%

set testCppFile=%projectPath_UT%\%srcFolderName%\%middlePathH%\tc_%fileName%.cpp
call :normizePath testCppFile

set testConfig_project=%projectPath_UT%\testconfig_%projectName%.h
set testEntry_project=%projectPath_UT%\UT_%projectName%.cpp
::set testConfig_global=%rootDir%\testconfig.h

::***********************************************************************
::call :dumpOutFile
goto :eof


:SetFilePath.h
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
if      {"%innerImplement%"}=={"1"}     set "middlePathH=%implementComponmentName%\%innerFolerName_h%"
if not  {"%innerImplement%"}=={"1"}     set "middlePathH=%implementComponmentName%\"

::e.g. OsBase\src\thread\inc
if      {"%innerImplement%"}=={"1"}     set implmentFolerName=%srcFolderName%
::e.g. MiniMPL\include\MiniMPL\innerDetail
if not  {"%innerImplement%"}=={"1"}     set implmentFolerName=%headFolderName%

set "headFile=%projectPath%\%implmentFolerName%\%middlePathH%\%fileName%%extName%"
call :normizePath headFile

set cppFile=%projectPath%\%srcFolderName%\%implementComponmentName%\%fileName%.cpp
call :normizePath cppFile
goto :eof

:SetFilePath.hpp
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
if      {"%innerImplement%"}=={"1"}     set "middlePathH=%implementComponmentName%\%innerFolerName_hpp%"
if not  {"%innerImplement%"}=={"1"}     set "middlePathH=%implementComponmentName%"
set implmentFolerName=%headFolderName%
set "headFile=%projectPath%\%implmentFolerName%\%middlePathH%\%fileName%%extName%"
call :normizePath headFile
goto :eof

:normizePath
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
call set _tmpPath=%%%~1%%
if not defined _tmpPath goto :eof
if not {"%_tmpPath:\\=\%"}=={"%_tmpPath%"} set "_tmpPath=%_tmpPath:\\=\%"
if not {"%_tmpPath://=/%"}=={"%_tmpPath%"} set "_tmpPath=%_tmpPath://=/%"
set "%~1=%_tmpPath%"
if not {"%_tmpPath%"}=={"%_tmpPath:\\=\%"} call :normizePath %~1
if not {"%_tmpPath%"}=={"%_tmpPath://=/%"} call :normizePath %~1
goto :eof

:toIncludePath
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
call set "_tmpPath1=%~1"
call :normizePath _tmpPath1
set "%~2=%_tmpPath1:\=/%"
goto :eof

:CreateHeadFile
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
if {%headFile%}=={} goto :eof
call :CreateFolder %headFile%
if      {"%bGuardHeadWithProjectName%"}=={"1"}  set guard_head_File=__%upperProjectName%_%upperFileName%_%upperExtName%__
if not  {"%bGuardHeadWithProjectName%"}=={"1"}  set guard_head_File=__%upperFileName%_%upperExtName%__
@echo create "%headFile%"
(
@echo #ifndef %guard_head_File%
@echo #define %guard_head_File%
@echo /***********************************************************************************************************************
@echo * Description         :
@echo * Author              : %AuthorInfo%
@echo * Copyright           : %CopyrightInfo%
@echo ***********************************************************************************************************************/
@echo #include ^<%MPLProject%/libConfig.h^>
@echo.
@echo.
if {%bAddNamespace%}=={1} (
@echo namespace %defNamespace%
@echo {
@echo.
@echo.
@echo }
) else (
@echo.
@echo.
@echo.
@echo.
)
@echo.
@echo.
@echo #endif // %guard_head_File%
) > %headFile%
call :AddSvn %headFile%
exit /b 0

::create cpp file for .h file
:CreateCppFile
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
if {%cppFile%}=={} goto :eof
call :CreateFolder %cppFile%
call :toIncludePath     "%middlePathH%\%fileName%%extName%"     _tmpInclude
@echo create "%cppFile%"
(
@echo #include "%_tmpInclude%"
@echo.
@echo.
if {%bAddNamespace%}=={1} (
@echo namespace %defNamespace%
@echo {
@echo.
@echo.
@echo.
@echo.
@echo }
)
) > %cppFile%
call :AddSvn %cppFile%
exit /b 0

:CreateTestHeadFile
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
if {%testHeadFile%}=={} goto :eof
call :CreateFolder %testHeadFile%
if      {"%bGuardHeadWithProjectName%"}=={"1"}  set guard_Test_head_File=__%upperTestProjectName%_TEST_%upperFileName%_%upperExtName%__
if not  {"%bGuardHeadWithProjectName%"}=={"1"}  set guard_Test_head_File=__TEST_%upperFileName%_%upperExtName%__
@echo create "%testHeadFile%"
(
@echo #ifndef %guard_Test_head_File%
@echo #define %guard_Test_head_File%
call :generateTestFileBody
@echo #endif // %guard_Test_head_File%
) > %testHeadFile%
call :AddToTestConfigList
call :AddSvn %testHeadFile%
exit /b 0

:CreateTestCppFile
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
if {%testCppFile%}=={} goto :eof
call :CreateFolder %testCppFile%
@echo create "%testCppFile%"
(
call :generateTestFileBody
) > %testCppFile%
call :AddToTestConfigList
call :AddSvn %testCppFile%
exit /b 0

:generateTestFileBody
set testconfigPath=../
if not {"%projectName%"}=={"%componmentName%"} set testconfigPath=%testconfigPath%../
call :toIncludePath "%middlePathH%\%fileName%%extName%" testedHeadFile
@echo #include "%testconfigPath%testconfig_%projectName%.h"
@echo #include ^<MiniMPL/macro_init.h^>
@echo /***********************************************************************************************************************
@echo * Description         : test file for ^<%testedHeadFile%^>
@echo * Author              : %AuthorInfo%
@echo * Copyright           : %CopyrightInfo%
@echo * usage demo          : #define RUN_EXAMPLE_%upperFileName% to run this demo
@echo ***********************************************************************************************************************/
@echo #define RUN_EXAMPLE_%upperFileName%
@echo.
@echo #ifdef COMPILE_EXAMPLE_ALL
@echo     #define COMPILE_EXAMPLE_%upperFileName%
@echo #endif
@echo.
@echo #ifdef RUN_EXAMPLE_ALL
@echo     #define RUN_EXAMPLE_%upperFileName%
@echo #endif
@echo.
@echo #if defined^(RUN_EXAMPLE_%upperFileName%^) ^&^& !defined(COMPILE_EXAMPLE_%upperFileName%^)
@echo     #define COMPILE_EXAMPLE_%upperFileName%
@echo #endif
@echo.
@echo //#undef RUN_EXAMPLE_%upperFileName%
@echo //#undef COMPILE_EXAMPLE_%upperFileName%
@echo.
@echo ////////////////////////////////////////////usage ^& test demo code//////////////////////////////////////////////////////////
@echo #ifdef COMPILE_EXAMPLE_%upperFileName%
@echo #include ^<%testedHeadFile%^>
@echo #include ^<%tcKitFolderName%/tc_tracer.h^>
@echo.
@echo namespace UnitTest
@echo {
@echo.
@if {%bAddNamespace%}=={1} (
@echo     using namespace %defNamespace%;
@echo.
)
@echo     inline void TestCase_%fileName%(^)
@echo     {
@echo         PrintTestcase(^);
@echo         ASSERT_AND_LOG_INFO(0,(TXT("Not implemented"^)^)^);	
@echo         Static_Assert(0^);
@echo         ALWAYS_COMPILE_MSG("NO Test context for <%testedHeadFile%>"^);
@echo.
@echo     }
@echo.
@echo #ifdef RUN_EXAMPLE_%upperFileName%
@echo     InitRunFunc(TestCase_%fileName%^);
@echo #else //else of RUN_EXAMPLE_%upperFileName%
@echo.
@echo ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
@echo     #if defined^(RUN_WARNING_NO_TESTCASE_RUN^)
@echo     GLOBALVAR^(RUN_%upperFileName%^)=^(outputTxtV^(TXT^("[Unit test run disabled] %fileName%%extName%\n%%s(%%d)\n"^) TXT^(__FILE__^) MAKESTR(__LINE__)^),1^);
@echo     #endif
@echo.
@echo     #if defined^(BUILD_WARNING_NO_TESTCASE_RUN^)
@echo     #pragma message ^(__FILE__ "(" MAKESTRA^(__LINE__^) "):No test code is runing for \"%fileName%%extName%\"."^)
@echo     #endif
@echo #endif  	// RUN_EXAMPLE_%upperFileName%
@echo }
@echo.
@echo #else //else of COMPILE_EXAMPLE_%upperFileName%
@echo     #if defined^(RUN_WARNING_NO_TESTCASE_COMPILE^)
@echo     GLOBALVAR^(COMPILE_%upperFileName%^)=^(outputTxtV^(TXT^("[Unit test compile disabled] %fileName%%extName%\n%%s(%%d)\n"^) TXT^(__FILE__^) MAKESTR(__LINE__)^),1^);
@echo     #endif
@echo.
@echo     #if defined^(BUILD_WARNING_NO_TESTCASE_COMPILE^)
@echo     #pragma message ^(__FILE__ "(" MAKESTRA^(__LINE__^) "):No test code is compiled for \"%fileName%%extName%\"."^)
@echo     #endif
@echo #endif // COMPILE_EXAMPLE_%upperFileName%
@echo.
goto :eof

:CreateTestMainEntry
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
if exist %testEntry_project% goto :eof
call :CreateFolder %testEntry_project%
@echo create "%testEntry_project%"
(
@echo //UT_%projectName%.cpp : Defines the entry point for the console application.
@echo #include ^<MiniMPL/macro_traceLog.h^>
@echo.
@echo int main(int argc, char* argv[]^)
@echo {
@echo.
@echo    TRACE_COMPILE(^);
@echo    return 0;
@echo }
@echo.
) > %testEntry_project%
call :AddSvn %testEntry_project%
exit /b 0

goto :eof

:AddToTestConfigList
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
if exist %testConfig_project% (
@echo update %testConfig_project%
rem differ RUN_EXAMPLE_ABC and RUN_EXAMPLE_ABCDE
for /f "usebackq" %%i in ( ` type %testConfig_project% ^| find /c "RUN_EXAMPLE_%upperFileName%  " ` ) do if {%%i}=={0} call :InsertStringInlast2Line %testConfig_project% "// #define RUN_EXAMPLE_%upperFileName%  "
) else (
(
@echo /***********************************************************************************************************************
@echo * Description         : test config file for project %projectName%
@echo *                       open/close macro to enable/disable test case for specified test file.
@echo * Author              : %AuthorInfo%
@echo * Copyright           : %CopyrightInfo%
@echo ***********************************************************************************************************************/
@echo #include ^<UnitTestKit/testconfig.h^>
@echo.
@echo.
@echo // #define RUN_EXAMPLE_%upperFileName%  
) >> %testConfig_project%
call :AddSvn %testConfig_project%
)
goto :eof

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
@echo mkdir %CreateFolderImplFlodName%
mkdir %CreateFolderImplFlodName%
svn add %CreateFolderImplFlodName:~1,-2%
)
goto :eof

:AddSvn
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
if not exist "%~1" @echo "%~1" doesn't exist & goto :eof
if {%bAddIntoSvn%}=={1} (
pushd %~dp1
@echo add file "%~1" to SVN (source code manager^)
svn add %~nx1 1>nul 2>nul
popd
@echo.
)
exit /b 0

:revertAdd
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
call :deleteFile %headFile%
call :deleteFile %cppFile%
call :deleteFile %testCppFile%
call :RevertRunMacro "#define RUN_EXAMPLE_%upperFileName%  "
if not exist "%rootDir%\UnitTest\%UT_featureFolder%UT_%projectName%\src\" (
call :deleteFile %testConfig_project%
call :deleteFile %testEntry_project%
)
goto :eof

:deleteFile
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
call :revertSvnFile "%~1"
if exist "%~1" del /q/f "%~1"
call :checkDeleteEmptyFolder "%~dp1"
goto :eof

:revertSvnFile
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
svn revert "%~1" | find /v "Skipped '"
goto :eof

:checkDeleteEmptyFolder
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
if not exist "%~1" (
goto :eof
)
call :deleteUnversionedFiles "%~1"
for /f "usebackq" %%i in ( ` dir/b "%~1" ^| find /c /v "" ` ) do if {%%i}=={0} call :checkDeleteEmptyFolderImpl "%~dp1"
goto :eof

:checkDeleteEmptyFolderImpl
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
set checkDeleteEmptyFolderImplFolderName="%~dp1"
svn revert --depth infinity "%checkDeleteEmptyFolderImplFolderName:~1,-2%"
@echo delete directory %checkDeleteEmptyFolderImplFolderName%
rd /Q %checkDeleteEmptyFolderImplFolderName%
@echo.
pushd "%~dp1.."
set upperPath="%cd%\"
popd
call :checkDeleteEmptyFolder %upperPath%
goto :eof

:deleteUnversionedFiles
if {%EchoCmd%}=={1} @echo [%~nx0] commandLine: %0 %*
if not exist "%~1" goto :eof
set targetPath=%~1
set /a files=0
set /a directorys=0
for /f "usebackq tokens=2" %%i in ( ` svn status "%targetPath:~0,-1%" ^| find "?" ` ) do ( 
if exist %%i\   rd /S /Q  %%i
if exist %%i    del /F /Q /A:-S %%i
)
@echo.
goto :eof

:parseFileName
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
set fileName=%~n1
call :toFirstLowerCase fileName
set extName=%~x1
if {%extName%}=={} set extName=.h
goto :eof

:SetUpperCaseMacro
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
set upperFileName=%fileName%
call :toUpper upperFileName
set upperProjectName=%projectName%
call :toUpper upperProjectName
set upperTestProjectName=%testFolderName%
call :toUpper upperTestProjectName
set upperExtName=%extName%
if not {%extName%}=={} (
set upperExtName=%extName:.=%
call :toUpper upperExtName
)
goto :eof

:toUpper  
if {%EchoCmd%}=={1} @echo [%~nx0] commandLine: %0 %*
if not defined %~1 EXIT /b
for %%a in ("a=A" "b=B" "c=C" "d=D" "e=E" "f=F" "g=G" "h=H" "i=I"
            "j=J" "k=K" "l=L" "m=M" "n=N" "o=O" "p=P" "q=Q" "r=R"
            "s=S" "t=T" "u=U" "v=V" "w=W" "x=X" "y=Y" "z=Z" "?=?"
            "?=?" "??=??") do (
    call set %~1=%%%~1:%%~a%%
)
goto :eof

:toLower
if {%EchoCmd%}=={1} @echo [%~nx0] commandLine: %0 %*
call set "%~1= %%%~1%%"
for %%a in ("A=a" "B=b" "C=c" "D=d" "E=e" "F=f" "G=g" "H=h" "I=i"
            "J=j" "K=k" "L=l" "M=m" "N=n" "O=o" "P=p" "Q=q" "R=r"
            "S=s" "T=t" "U=u" "V=v" "W=w" "X=x" "Y=y" "Z=z"
            "?=?" "?=?" "??=??") do (
    call set "%~1=%%%~1:%%~a%%"
)
call set "%~1=%%%~1: =%%"
goto :eof

:toFirstLowerCase
if {%EchoCmd%}=={1} @echo [%~nx0] commandLine: %0 %*
call set "_tmptoFirstLowerCase=%%%~1%%"
set "_tmptoFirstLowerCase1=%_tmptoFirstLowerCase:~0,1%"
call :toLower _tmptoFirstLowerCase1
set "%~1=%_tmptoFirstLowerCase1%%_tmptoFirstLowerCase:~1%"
goto :eof

:InsertStringInlast2Line
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

:RevertRunMacro
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
if {"%~1"}=={} goto :eof
if not exist "%testConfig_project%" goto :eof
for /f "usebackq" %%i in ( ` svn status  "%testConfig_project%" ^| find /c /i "testConfig" ` ) do set iCount=%%i
if {%iCount%}=={0} goto :eof
set oriTestConfig_project=%tmp%\testconfig_%projectName%.h
if exist %oriTestConfig_project% del /f /q %oriTestConfig_project%
move %testConfig_project% %oriTestConfig_project% 1>NUL
type %oriTestConfig_project% | find /v "%~1" >> %testConfig_project%
goto :eof

:End
if {%EchoCmd%}=={1} @echo [Leave %~nx0] commandLine: %0 %*