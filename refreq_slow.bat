rem hexec Cyrus_tapir2mod.TZX CA02A604A604DC01B803 E602C204C2045A027203 Cyrus_tapir2mod_id11.TZX
rem forfiles /m *.tzx /C "cmd /c hexec @file 11CA02A604A604DC01B803 11E602C204C2045A027203 @fname_id11.xec
forfiles /m *.tzx /C "cmd /c hexec @file CA02A604A604DC01B803 E602C204C2045A027203 @fname_id11.xec
forfiles /m *.tzx /C "cmd /c hexec @file CA02A604A604DC01B803 D606F00AF00A7805BE07 @fname_slow_id11.xec
mkdir EP64TZX
move *.xec EP64TZX
cd EP64TZX
ren *.xec *.tzx
cd..
PAUSE
