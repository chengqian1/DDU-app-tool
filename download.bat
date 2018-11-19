@echo off
del winscp1.txt
setlocal EnableDelayedExpansion
for /f "delims=" %%i in (winscp.txt) do (
set var=%%i
set var=!var:password=%2!
set var=!var:192.168.100.100=%1!
set var=!var:D:\bat\FILE.tar.gz=%3!
echo !var!>>winscp1.txt 
) 
D:\WinSCP\WinSCP.exe /console /script=D:\Documents\QTcode\build-DownloadF-Desktop_Qt_5_9_1_MinGW_32bit-Release\winscp1.txt
If errorlevel 1 (
    Echo download failed
    exit /B 1
) Else (
    Echo download success
    exit /B 2
)
del winscp1.txt
