rem bbe -e s/\x11\xCA\x02\xA6\x04\xA6\x04\xDC\x01\xB8\x03/\x11\xE6\x02\xC2\x04\xC2\x04\x5A\x02\x72\x03/g Cyrus_tapir2mod.TZX -o Cyrus_tapir2mod_id11.TZX
forfiles /m *.tzx /C "cmd /c bbe -e s/\x11\xCA\x02\xA6\x04\xA6\x04\xDC\x01\xB8\x03/\x11\xE6\x02\xC2\x04\xC2\x04\x5A\x02\x72\x03/g @file -o @fname_id11.bbe
mkdir EPTZX
move *.bbe EPTZX
cd EPTZX
ren *.bbe *.tzx
cd..
PAUSE
