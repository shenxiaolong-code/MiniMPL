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
::set default quick config
rem call :quickConfig_MiniMPL
call :quickConfig_OsBase

::override default config
if not defined projectName 		set projectName=OsBase
if not defined componmentName   set componmentName=thread
::set subFolderName=innerDetail
if not defined subFolderName 	set subFolderName=
:: innerImplement indicates current header file lies in src\...\inc folder, instead of include folder
if not defined innerImplement 	set innerImplement=0

:: set namespace config
if not defined bAddNamespace 	set bAddNamespace=0
if not defined defNamespace 	set defNamespace=MiniMPL
if not defined MPLProject 		set MPLProject=MiniMPL

if not defined UseComponmentFolderInCpp     set UseComponmentFolderInCpp=0

::set svn config
if not defined bAddIntoSvn 		            set bAddIntoSvn=1
if not defined bGuardHeadWithProjectName 	set bGuardHeadWithProjectName=0

::set test config
::********************Config end*****************************************
pushd %~dp0..\
set rootDir=%cd%\sources
popd
set fullFileName=%~1
set hpp_=.hpp
set h_=.h
set testFolderName=UnitTests
set tcKitFolderName=UnitTestKit

::set comment head info
set AuthorInfo=Shen.Xiaolong ^(2009-%date:~0,4%^) , xlshen@126.com  xlshen2002@hotmail.com
set CopyrightInfo=free to use / modify / sale in free and commercial software with those head comments.

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
goto :End

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
set UseComponmentFolderInCpp=
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
rem path is used in source file (.h/.hpp/.cpp), tailed with '/'
rem dir is used file system path, tailed with '\'
set subFolder_Path=
set subFolder_Dir=
if not {%subFolderName%}=={} (
set subFolder_Path=%subFolderName%/
set subFolder_Dir=%subFolderName%\
)
set projectPath=%rootDir%\%projectName%
set projectPath_UT=%rootDir%\UnitTest\UT_%projectName%
set headFolder=include
set innerHead_Path=
if {%innerImplement%}=={1} (
set headFolder=src
set innerHead_Path=inc/
)
goto :eof

:SetFilePath
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
call :SetMiddleVars
set innerHead_Dir=
if {%innerImplement%}=={1} set innerHead_Dir=inc\
set headFile=%projectPath%\%headFolder%\%componmentName%\%subFolder_Dir%%innerHead_Dir%%fileName%%extName%
set cppComponment_Dir=
if {%UseComponmentFolderInCpp%}=={1} set cppComponment_Dir=%componmentName%\
if {%extName%}=={%h_%} (
set cppFile=%projectPath%\src\%cppComponment_Dir%%subFolder_Dir%%fileName%.cpp
)
set testCppFile=%projectPath_UT%\src\%cppComponment_Dir%%subFolder_Dir%tc_%fileName%.cpp

set testConfig_project=%projectPath_UT%\testconfig_%projectName%.h
set testEntry_project=%projectPath_UT%\UT_%projectName%.cpp
::set testConfig_global=%rootDir%\testconfig.h

::***********************************************************************
::call :dumpOutFile
goto :eof

:CreateHeadFile
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
if {%headFile%}=={} goto :eof
call :CreateFolder %headFile%
if {%bGuardHeadWithProjectName%}=={1} (
set guard_head_File=__%upperProjectName%_%upperFileName%_%upperExtName%__
) else (
set guard_head_File=__%upperFileName%_%upperExtName%__
)
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

:CreateCppFile
if {%EchoCmd%}=={1} @echo [Enter %~nx0] commandLine: %0 %*
if {%cppFile%}=={} goto :eof
call :CreateFolder %cppFile%
@echo create "%cppFile%"
(
@if {%innerImplement%}=={1} @echo #include "%innerHead_Path%%fileName%%extName%"
@if not {%innerImplement%}=={1} @echo #include ^<%componmentName%/%subFolder_Path%%fileName%%extName%^>
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
if {%bGuardHeadWithProjectName%}=={1} (
set guard_Test_head_File=__%upperTestProjectName%_TEST_%upperFileName%_%upperExtName%__
) else (
set guard_Test_head_File=__TEST_%upperFileName%_%upperExtName%__
)
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
@if Not {%subFolderName%}=={} set testconfigPath=../
@if {%UseComponmentFolderInCpp%}=={1} set testconfigPath=%testconfigPath%../
@echo #include "testconfig_%projectName%.h"
@echo #include ^<MiniMPL/macro_init.h^>
@echo /***********************************************************************************************************************
@echo * Description         : test file for ^<%projectName%/%fileName%%extName%^>
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
@echo #if defined^(RUN_EXAMPLE_%NameMacro%^) ^&^& !defined(COMPILE_EXAMPLE_%NameMacro%^)
@echo     #define COMPILE_EXAMPLE_%upperFileName%
@echo #endif
@echo.
@echo //#undef RUN_EXAMPLE_%upperFileName%
@echo //#undef COMPILE_EXAMPLE_%upperFileName%
@echo.
@echo ////////////////////////////////////////////usage ^& test demo code//////////////////////////////////////////////////////////
@echo #ifdef COMPILE_EXAMPLE_%upperFileName%
@echo #include ^<%componmentName%/%subFolder_Path%%innerHead_Path%%fileName%%extName%^>
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
@echo         ALWAYS_COMPILE_MSG("NO Test context for <%componmentName%/%subFolder_Path%%innerHead_Path%%fileName%%extName%>"^);
@echo.
@echo     }
@echo.
@echo #ifdef RUN_EXAMPLE_%upperFileName%
@echo     InitRunFunc(TestCase_%fileName%^);
@echo #else //else of RUN_EXAMPLE_%upperFileName%
@echo.
@echo ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
@echo     #if defined^(RUN_WARNING_NO_TESTCASE_RUN^)
@echo     GLOBALVAR^(RUN_%NameMacro%^)=^(outputTxtV^(TXT^("[Unit test run disabled] %fileName%%extName%\n%%s(%%d)\n"^),TXT^(__FILE__^),__LINE__^),1^);
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
@echo     GLOBALVAR^(COMPILE_%NameMacro%^)=^(outputTxtV^(TXT^("[Unit test compile disabled] %fileName%%extName%\n%%s(%%d)\n"^),TXT^(__FILE__^),__LINE__^),1^);
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

:quickConfig_MiniMPL
set projectName=MiniMPL
set componmentName=MiniMPL
set UseComponmentFolderInCpp=0
:: set namespace config
set bAddNamespace=1
set defNamespace=MiniMPL
goto :eof

:quickConfig_OsBase
set projectName=OsBase
:: set namespace config
set defNamespace=OS_Win32
set UseComponmentFolderInCpp=1
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

:toFirstLowerCase
if {%EchoCmd%}=={1} @echo [%~nx0] commandLine: %0 %*
call set "%~1= %%%~1%%"
REM make first character lower case
for %%a in ("A=a" "B=b" "C=c" "D=d" "E=e" "F=f" "G=g" "H=h" "I=i"
            "J=j" "K=k" "L=l" "M=m" "N=n" "O=o" "P=p" "Q=q" "R=r"
            "S=s" "T=t" "U=u" "V=v" "W=w" "X=x" "Y=y" "Z=z"
            "?=?" "?=?" "??=??") do (
    call set "%~1=%%%~1:%%~a%%"
)
call set "%~1=%%%~1: =%%"
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