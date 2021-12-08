SET PCE_INCLUDE=..\;..\hescode\;..\include\pce
..\bin\hmckc -i %1.mml
..\bin\pceas -raw makehes.s
copy makehes.pce %1.hes
