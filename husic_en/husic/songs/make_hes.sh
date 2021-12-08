#!/bin/sh

export PCE_INCLUDE="../;../hescode;../include/pce"
../bin/hmckc -i $1.mml
../bin/pceas -raw makehes.s
mv makehes.pce $1.hes
