
@echo off
cls
::global/system/
::git config --global core.autocrlf false

cd /d "%~dp0.."
call :getGithubCredential   github_credi
set "github_miniMpl_repo=https://%github_credi%github.com/ShenXiaolong1976/MiniMPL.git"
set "github_miniMpl_repo_2=https://%github_credi%github.com/ShenXiaolong1976/gitPratice.git"
set "github_miniMpl_repo_recommand=%github_miniMpl_repo%"
echo used github repo:
echo %github_miniMpl_repo_recommand%

if exist .git rd/s/q .git

echo.
echo clone remote git repo
git clone %github_miniMpl_repo_recommand%

echo.
echo copy git config foler .git to current folder
call :gitName "%github_miniMpl_repo_recommand%" repoName
xcopy/s "%repoName%\.git" .git\  >nul
rd /s/q "%repoName%"
git config core.autocrlf false

echo.
echo add current change to git
git add .

echo.
echo current git cache status
git stage
git status

echo.
echo.
echo ******************* !!! Confirm !!!************************************
echo press any key to confir pushing any change to remote git server!
pause >nul

echo.
echo.
echo commit change
git commit -m "push to git from svn. %date% , %time%"

echo.
echo push to git server.
git push

echo.
echo Done
goto :END

:gitName
set %~2=%~n1
goto :eof

:getGithubCredential
if defined github_pwd set %~1=%github_user%:%github_pwd%@
goto :eof

:END
:: https://ShenXiaolong1976:xlshen1976@github.com/ShenXiaolong1976/MiniMPL.git
pause