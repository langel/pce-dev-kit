@REM THIS SETTING SHOULD BE ALL YOU NEED TO CHANGE
@set HUC_HOME=c:\huc

@path=%path%;%HUC_HOME%\bin
@set PCE_INCLUDE=%HUC_HOME%\include\pce

@cls
@REM Clean


@REM Compile, assemble, and link
huc -O2 1.c

@REM Run
@REM "C:\Documents and Settings\User\Desktop\nesterJ\nesterJ.exe" .\invaders.nes
@REM @call run