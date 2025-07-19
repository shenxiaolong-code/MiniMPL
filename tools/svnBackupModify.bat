::backup modify src file in directory .\mt_tf\source
::copy the update src from SVN 
@echo off
rem add common directory to %path%
where srcSvnBackupModify.bat 1>nul 2>nul || set path=%path%;%~dp0..\..shell_script\batch_env\common\;

call srcSvnBackupModify.bat "%~dp0.."
call sleep.bat 6



