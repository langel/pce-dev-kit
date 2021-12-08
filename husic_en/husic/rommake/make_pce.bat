SET PCE_INCLUDE=..\;..\hescode\;..\include\pce
..\bin\hmckc -i %1.mml
..\bin\pceas -raw makepce.s
copy makepce.pce %1.pce
