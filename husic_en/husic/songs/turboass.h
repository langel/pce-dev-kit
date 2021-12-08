; Title: TURBOASS
; Composer: B-KNOX
; Maker: Maker
; Programer: PUKE7

	.include "define.inc"
	.if TOTAL_SONGS > 1
song_addr_table:
	dw	song_000_track_table
	.if (ALLOW_BANK_SWITCH)
song_bank_table:
	dw	song_000_bank_table
	.endif ; ALLOW_BANK_SWITCH
	.endif ; TOTAL_SONGS > 1
sound_data_table:
	dw	song_000_00
	dw	song_000_01
	dw	song_000_02
	dw	song_000_03
	dw	song_000_04
	dw	song_000_05
	.if (ALLOW_BANK_SWITCH)
sound_data_bank:
	db	bank(song_000_00)
	db	bank(song_000_01)
	db	bank(song_000_02)
	db	bank(song_000_03)
	db	bank(song_000_04)
	db	bank(song_000_05)
loop_point_table:
	dw	song_000_00_lp
	dw	song_000_01_lp
	dw	song_000_02_lp
	dw	song_000_03_lp
	dw	song_000_04_lp
	dw	song_000_05_lp
loop_point_bank:
	db	bank(song_000_00_lp)
	db	bank(song_000_01_lp)
	db	bank(song_000_02_lp)
	db	bank(song_000_03_lp)
	db	bank(song_000_04_lp)
	db	bank(song_000_05_lp)

	.endif

song_000_00:	;Trk A
	db	$fd,$9f,$f1,$07,$fd,$03,$fd,$04	;Trk A; turboass.mml: 35
	db	$fe,$80,$32,$83,$34,$83,$39,$83	;Trk A; turboass.mml: 96
	db	$3b,$83,$32,$83,$34,$82,$39,$83	;Trk A; turboass.mml: 96
	db	$37,$83,$32,$83,$34,$83,$39,$83	;Trk A; turboass.mml: 100
	db	$3b,$83,$32,$83,$34,$83,$39,$83	;Trk A; turboass.mml: 104
	db	$37,$83,$39,$82
song_000_00_lp:
	db	$fc,$ff,$ee
	db	bank(song_000_00_lp)
	dw	song_000_00_lp


song_000_01:	;Trk B
	db	$fd,$9f,$f1,$08,$fd,$02,$fd,$04	;Trk B; turboass.mml: 35
	db	$fe,$80,$35,$83,$37,$83,$30,$83	;Trk B; turboass.mml: 97
	db	$32,$83,$35,$83,$37,$82,$30,$83	;Trk B; turboass.mml: 97
	db	$2b,$83,$25,$83,$27,$83,$20,$83	;Trk B; turboass.mml: 101
	db	$22,$83,$25,$83,$27,$83,$20,$83	;Trk B; turboass.mml: 105
	db	$3b,$83,$20,$82
song_000_01_lp:
	db	$fc,$ff,$ee
	db	bank(song_000_01_lp)
	dw	song_000_01_lp


song_000_02:	;Trk C
	db	$fd,$9f,$f1,$08,$fd,$02,$fd,$04	;Trk C; turboass.mml: 35
	db	$39,$83,$3b,$83,$34,$83,$35,$83	;Trk C; turboass.mml: 98
	db	$39,$83,$3b,$82,$34,$83,$22,$42	;Trk C; turboass.mml: 102
	db	$20,$41,$29,$83,$2b,$83,$24,$83	;Trk C; turboass.mml: 102
	db	$25,$83,$29,$83,$2b,$83,$24,$83	;Trk C; turboass.mml: 106
	db	$32,$83,$24,$82
song_000_02_lp:
	db	$fc,$ff,$ee
	db	bank(song_000_02_lp)
	dw	song_000_02_lp


song_000_03:	;Trk D
	db	$fd,$9f,$f1,$08,$fd,$02,$fd,$04	;Trk D; turboass.mml: 35
	db	$fc,$83,$fc,$83,$fc,$83,$fc,$83	;Trk D; turboass.mml: 99
	db	$fc,$83,$fc,$82,$fc,$83,$fc,$83	;Trk D; turboass.mml: 103
	db	$fc,$83,$fc,$83,$fc,$83,$fc,$83	;Trk D; turboass.mml: 107
	db	$fc,$83,$fc,$83,$3b,$83,$3b,$83	;Trk D; turboass.mml: 111

song_000_03_lp:
	db	$fc,$ff,$ee
	db	bank(song_000_03_lp)
	dw	song_000_03_lp


song_000_04:	;Trk E
	db	$fd,$9f,$f1,$08,$fd,$02,$f1,$02	;Trk E; turboass.mml: 35
	db	$fd,$05,$fc,$83,$fc,$83,$fc,$83	;Trk E; turboass.mml: 39
	db	$fc,$83,$fc,$83,$fc,$82,$fc,$83	;Trk E; turboass.mml: 113
	db	$fc,$83,$fc,$83,$fc,$83,$19,$10	;Trk E; turboass.mml: 113
	db	$19,$11,$fc,$10,$19,$11,$19,$10	;Trk E; turboass.mml: 114
	db	$fc,$10,$1b,$11,$1b,$10,$fc,$10	;Trk E; turboass.mml: 114
	db	$17,$11,$17,$10,$fc,$10,$17,$11	;Trk E; turboass.mml: 115
	db	$17,$10,$12,$11,$12,$10,$fc,$10	;Trk E; turboass.mml: 115
	db	$12,$11,$15,$10,$fc,$10,$17,$11	;Trk E; turboass.mml: 116
	db	$14,$10,$fc,$10,$14,$11,$14,$10	;Trk E; turboass.mml: 117
	db	$fc,$11,$17,$10,$14,$10,$14,$2c	;Trk E; turboass.mml: 117
	db	$14,$2c,$14,$2b,$fc,$83,$10,$42	;Trk E; turboass.mml: 119
	db	$10,$82
song_000_04_lp:
	db	$fc,$ff,$ee
	db	bank(song_000_04_lp)
	dw	song_000_04_lp


song_000_05:	;Trk F
	db	$fd,$9f,$f2,$01,$fd,$00,$f8,$01	;Trk F; turboass.mml: 35
	db	$f2,$00,$f1,$02,$fd,$01,$20,$10	;Trk F; turboass.mml: 65
	db	$f8,$00,$f2,$01,$fd,$00,$1b,$09	;Trk F; turboass.mml: 66
	db	$1b,$08,$f8,$02,$f2,$01,$fd,$02	;Trk F; turboass.mml: 66
	db	$12,$10,$f8,$00,$f2,$01,$fd,$00	;Trk F; turboass.mml: 67
	db	$1b,$10,$f8,$01,$f2,$00,$f1,$02	;Trk F; turboass.mml: 68
	db	$fd,$01,$20,$11,$f8,$00,$f2,$01	;Trk F; turboass.mml: 65
	db	$fd,$00,$1b,$08,$1b,$08,$f8,$02	;Trk F; turboass.mml: 66
	db	$f2,$01,$fd,$02,$12,$11,$f8,$00	;Trk F; turboass.mml: 67
	db	$f2,$01,$fd,$00,$1b,$10,$f8,$01	;Trk F; turboass.mml: 68
	db	$f2,$00,$f1,$02,$fd,$01,$20,$10	;Trk F; turboass.mml: 65
	db	$f8,$00,$f2,$01,$fd,$00,$1b,$08	;Trk F; turboass.mml: 66
	db	$1b,$09,$f8,$02,$f2,$01,$fd,$02	;Trk F; turboass.mml: 66
	db	$12,$10,$f8,$00,$f2,$01,$fd,$00	;Trk F; turboass.mml: 67
	db	$1b,$10,$f8,$02,$f2,$01,$fd,$02	;Trk F; turboass.mml: 68
	db	$12,$11,$f8,$00,$f2,$01,$fd,$00	;Trk F; turboass.mml: 69
	db	$1b,$08,$1b,$08,$f8,$02,$f2,$01	;Trk F; turboass.mml: 70
	db	$fd,$02,$12,$10,$f8,$00,$f2,$01	;Trk F; turboass.mml: 69
	db	$fd,$00,$1b,$09,$1b,$08,$f8,$01	;Trk F; turboass.mml: 70
	db	$f2,$00,$f1,$02,$fd,$01,$20,$10	;Trk F; turboass.mml: 65
	db	$f8,$00,$f2,$01,$fd,$00,$1b,$08	;Trk F; turboass.mml: 66
	db	$1b,$09,$f8,$02,$f2,$01,$fd,$02	;Trk F; turboass.mml: 66
	db	$12,$10,$f8,$00,$f2,$01,$fd,$00	;Trk F; turboass.mml: 67
	db	$1b,$10,$f8,$01,$f2,$00,$f1,$02	;Trk F; turboass.mml: 68
	db	$fd,$01,$20,$11,$f8,$00,$f2,$01	;Trk F; turboass.mml: 65
	db	$fd,$00,$1b,$08,$1b,$08,$f8,$02	;Trk F; turboass.mml: 66
	db	$f2,$01,$fd,$02,$12,$10,$f8,$00	;Trk F; turboass.mml: 67
	db	$f2,$01,$fd,$00,$1b,$11,$f8,$01	;Trk F; turboass.mml: 68
	db	$f2,$00,$f1,$02,$fd,$01,$20,$10	;Trk F; turboass.mml: 65
	db	$f8,$00,$f2,$01,$fd,$00,$1b,$08	;Trk F; turboass.mml: 66
	db	$1b,$08,$f8,$02,$f2,$01,$fd,$02	;Trk F; turboass.mml: 66
	db	$12,$11,$f8,$00,$f2,$01,$fd,$00	;Trk F; turboass.mml: 67
	db	$1b,$10,$f8,$02,$f2,$01,$fd,$02	;Trk F; turboass.mml: 68
	db	$12,$11,$f8,$00,$f2,$01,$fd,$00	;Trk F; turboass.mml: 69
	db	$1b,$08,$1b,$08,$f8,$02,$f2,$01	;Trk F; turboass.mml: 70
	db	$fd,$02,$12,$10,$f8,$00,$f2,$01	;Trk F; turboass.mml: 69
	db	$fd,$00,$1b,$08,$1b,$09,$f8,$01	;Trk F; turboass.mml: 70
	db	$f2,$00,$f1,$02,$fd,$01,$20,$10	;Trk F; turboass.mml: 72
	db	$f8,$00,$f2,$01,$fd,$00,$1b,$08	;Trk F; turboass.mml: 73
	db	$1b,$08,$f8,$02,$f2,$01,$fd,$02	;Trk F; turboass.mml: 73
	db	$12,$11,$f8,$00,$f2,$01,$fd,$00	;Trk F; turboass.mml: 74
	db	$1b,$10,$f8,$01,$f2,$00,$f1,$02	;Trk F; turboass.mml: 75
	db	$fd,$01,$20,$10,$f8,$00,$f2,$01	;Trk F; turboass.mml: 72
	db	$fd,$00,$1b,$09,$1b,$08,$f8,$02	;Trk F; turboass.mml: 73
	db	$f2,$01,$fd,$02,$12,$10,$f8,$00	;Trk F; turboass.mml: 74
	db	$f2,$01,$fd,$00,$1b,$11,$f8,$01	;Trk F; turboass.mml: 75
	db	$f2,$00,$f1,$02,$fd,$01,$20,$10	;Trk F; turboass.mml: 72
	db	$f8,$00,$f2,$01,$fd,$00,$1b,$08	;Trk F; turboass.mml: 73
	db	$1b,$08,$f8,$02,$f2,$01,$fd,$02	;Trk F; turboass.mml: 73
	db	$12,$11,$f8,$00,$f2,$01,$fd,$00	;Trk F; turboass.mml: 74
	db	$1b,$10,$f8,$01,$f2,$00,$f1,$02	;Trk F; turboass.mml: 75
	db	$fd,$01,$20,$10,$f8,$00,$f2,$01	;Trk F; turboass.mml: 76
	db	$fd,$00,$1b,$09,$1b,$08,$f8,$01	;Trk F; turboass.mml: 77
	db	$f2,$00,$f1,$02,$fd,$01,$20,$10	;Trk F; turboass.mml: 76
	db	$f8,$00,$f2,$01,$fd,$00,$1b,$08	;Trk F; turboass.mml: 77
	db	$1b,$08,$f8,$01,$f2,$00,$f1,$02	;Trk F; turboass.mml: 77
	db	$fd,$01,$20,$11,$f8,$00,$f2,$01	;Trk F; turboass.mml: 79
	db	$fd,$00,$1b,$08,$1b,$08,$f8,$02	;Trk F; turboass.mml: 80
	db	$f2,$01,$fd,$02,$12,$11,$f8,$00	;Trk F; turboass.mml: 81
	db	$f2,$01,$fd,$00,$1b,$10,$f8,$01	;Trk F; turboass.mml: 82
	db	$f2,$00,$f1,$02,$fd,$01,$20,$10	;Trk F; turboass.mml: 79
	db	$f8,$00,$f2,$01,$fd,$00,$1b,$08	;Trk F; turboass.mml: 80
	db	$1b,$09,$f8,$02,$f2,$01,$fd,$02	;Trk F; turboass.mml: 80
	db	$12,$10,$f8,$00,$f2,$01,$fd,$00	;Trk F; turboass.mml: 81
	db	$1b,$10,$f8,$01,$f2,$00,$f1,$02	;Trk F; turboass.mml: 82
	db	$fd,$01,$20,$11,$f8,$00,$f2,$01	;Trk F; turboass.mml: 79
	db	$fd,$00,$1b,$08,$1b,$08,$f8,$02	;Trk F; turboass.mml: 80
	db	$f2,$01,$fd,$02,$12,$10,$f8,$00	;Trk F; turboass.mml: 81
	db	$f2,$01,$fd,$00,$1b,$11,$f8,$01	;Trk F; turboass.mml: 82
	db	$f2,$00,$f1,$02,$fd,$01,$20,$10	;Trk F; turboass.mml: 83
	db	$f8,$00,$f2,$01,$fd,$00,$1b,$08	;Trk F; turboass.mml: 84
	db	$1b,$09,$f8,$01,$f2,$00,$f1,$02	;Trk F; turboass.mml: 84
	db	$fd,$01,$20,$08,$20,$08,$20,$10	;Trk F; turboass.mml: 85
	db	$f8,$01,$f2,$00,$f1,$02,$fd,$01	;Trk F; turboass.mml: 87
	db	$20,$83,$fc,$83,$fc,$83,$fc,$83	;Trk F; turboass.mml: 87
	db	$fc,$83,$fc,$83,$fc,$83,$fc,$41	;Trk F; turboass.mml: 89
	db	$f8,$01,$f2,$00,$f1,$02,$fd,$01	;Trk F; turboass.mml: 90
	db	$24,$10,$f8,$00,$f2,$01,$fd,$00	;Trk F; turboass.mml: 90
	db	$1b,$11,$1b,$10,$1b,$11,$f8,$01	;Trk F; turboass.mml: 91
	db	$f2,$00,$f1,$02,$fd,$01,$24,$82	;Trk F; turboass.mml: 132

song_000_05_lp:
	db	$fc,$ff,$ee
	db	bank(song_000_05_lp)
	dw	song_000_05_lp

