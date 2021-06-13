rem hexstrp Cyrus_tapir2mod.TZX 11CA02A604A604DC01B803 11E602C204C2045A027203 Cyrus_tapir2mod_b11.TZX
rem forfiles /m *.tzx /C "cmd /c hexstrp @file 11CA02A604A604DC01B803 11E602C204C2045A027203 @fname_b11.hsp
forfiles /m *.tzx /C "cmd /c hexstrp @file CA02A604A604DC01B803 E602C204C2045A027203 @fname_b11.hsp
mkdir EP64TZX
move *.hsp EP64TZX
cd EP64TZX
ren *.hsp *.tzx
cd..
PAUSE
