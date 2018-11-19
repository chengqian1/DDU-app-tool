D:\WinSCP\WinSCP.exe /console /command "option batch abort" "option confirm off" "open scp://root:%2@%1 -rawsettings KEX=dh-group1-sha1" "exit"
IF errorlevel 1 (
	Echo log in failed
	exit /B 11 
) Else (
	Echo log in success
	exit /B 22)
exit