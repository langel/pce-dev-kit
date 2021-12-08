; Title: GRRRARRR
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
	db	$fd,$9f,$f1,$07,$fd,$03,$fe,$80	;Trk A; grrrarrr.mml: 53
	db	$04,$0e,$fc,$05,$fc,$09,$04,$0e	;Trk A; grrrarrr.mml: 68
	db	$fc,$05,$fc,$0a,$04,$06,$fc,$03	;Trk A; grrrarrr.mml: 68
	db	$fc,$0a,$04,$0e,$fc,$05,$fc,$09	;Trk A; grrrarrr.mml: 68
	db	$04,$0e,$fc,$05,$fc,$0a,$04,$06	;Trk A; grrrarrr.mml: 68
	db	$fc,$03,$fc,$0a,$04,$0e,$fc,$05	;Trk A; grrrarrr.mml: 68
	db	$fc,$09,$04,$0e,$fc,$05,$fc,$09	;Trk A; grrrarrr.mml: 68
	db	$04,$07,$fc,$03,$fc,$09,$04,$07	;Trk A; grrrarrr.mml: 68
	db	$fc,$03,$fc,$09,$04,$07,$fc,$03	;Trk A; grrrarrr.mml: 69
	db	$fc,$09,$16,$0e,$fc,$05,$17,$0e	;Trk A; grrrarrr.mml: 69
	db	$fc,$05,$04,$0e,$fc,$05,$fc,$0a	;Trk A; grrrarrr.mml: 69
	db	$0b,$0e,$fc,$05,$fc,$12,$07,$07	;Trk A; grrrarrr.mml: 70
	db	$fc,$03,$04,$0e,$fc,$05,$fc,$09	;Trk A; grrrarrr.mml: 70
	db	$04,$0e,$fc,$05,$fc,$0a,$04,$06	;Trk A; grrrarrr.mml: 71
	db	$fc,$03,$fc,$0a,$04,$0e,$fc,$05	;Trk A; grrrarrr.mml: 71
	db	$fc,$09,$04,$0e,$fc,$05,$fc,$0a	;Trk A; grrrarrr.mml: 71
	db	$04,$06,$fc,$03,$fc,$0a,$09,$05	;Trk A; grrrarrr.mml: 71
	db	$fc,$02,$fc,$02,$09,$05,$fc,$02	;Trk A; grrrarrr.mml: 72
	db	$fc,$02,$09,$06,$fc,$02,$fc,$02	;Trk A; grrrarrr.mml: 72
	db	$fc,$09,$16,$0e,$fc,$05,$17,$0e	;Trk A; grrrarrr.mml: 72
	db	$fc,$05,$04,$0e,$fc,$05,$fc,$0a	;Trk A; grrrarrr.mml: 72
	db	$04,$0e,$fc,$05,$fc,$09,$04,$07	;Trk A; grrrarrr.mml: 68
	db	$fc,$03,$fc,$09,$04,$0e,$fc,$05	;Trk A; grrrarrr.mml: 68
	db	$fc,$0a,$04,$0d,$fc,$05,$fc,$0a	;Trk A; grrrarrr.mml: 68
	db	$04,$06,$fc,$03,$fc,$0a,$04,$0e	;Trk A; grrrarrr.mml: 68
	db	$fc,$05,$fc,$09,$04,$0e,$fc,$05	;Trk A; grrrarrr.mml: 68
	db	$fc,$0a,$04,$06,$fc,$03,$fc,$0a	;Trk A; grrrarrr.mml: 68
	db	$04,$06,$fc,$03,$fc,$0a,$04,$06	;Trk A; grrrarrr.mml: 69
	db	$fc,$03,$fc,$0a,$16,$0e,$fc,$05	;Trk A; grrrarrr.mml: 69
	db	$17,$0d,$fc,$05,$04,$0e,$fc,$05	;Trk A; grrrarrr.mml: 69
	db	$fc,$0a,$0b,$0e,$fc,$05,$fc,$13	;Trk A; grrrarrr.mml: 70
	db	$07,$06,$fc,$03,$04,$0e,$fc,$05	;Trk A; grrrarrr.mml: 70
	db	$fc,$0a,$04,$0e,$fc,$05,$fc,$09	;Trk A; grrrarrr.mml: 71
	db	$04,$07,$fc,$03,$fc,$09,$04,$0e	;Trk A; grrrarrr.mml: 71
	db	$fc,$05,$fc,$09,$04,$0e,$fc,$05	;Trk A; grrrarrr.mml: 71
	db	$fc,$0a,$04,$06,$fc,$03,$fc,$0a	;Trk A; grrrarrr.mml: 71
	db	$09,$05,$fc,$02,$fc,$02,$09,$05	;Trk A; grrrarrr.mml: 72
	db	$fc,$02,$fc,$03,$09,$05,$fc,$02	;Trk A; grrrarrr.mml: 72
	db	$fc,$02,$fc,$0a,$16,$0e,$fc,$05	;Trk A; grrrarrr.mml: 72
	db	$17,$0e,$fc,$05,$fc,$09,$09,$07	;Trk A; grrrarrr.mml: 72
	db	$fc,$03,$09,$06,$fc,$03,$09,$07	;Trk A; grrrarrr.mml: 102
	db	$fc,$03,$09,$06,$fc,$03,$09,$06	;Trk A; grrrarrr.mml: 102
	db	$fc,$03,$09,$07,$fc,$03,$fc,$09	;Trk A; grrrarrr.mml: 102
	db	$09,$0e,$fc,$05,$fc,$0a,$09,$06	;Trk A; grrrarrr.mml: 102
	db	$fc,$03,$09,$07,$fc,$03,$09,$06	;Trk A; grrrarrr.mml: 102
	db	$fc,$03,$09,$07,$fc,$03,$fc,$09	;Trk A; grrrarrr.mml: 102
	db	$fc,$0a,$09,$06,$fc,$03,$09,$07	;Trk A; grrrarrr.mml: 102
	db	$fc,$03,$09,$06,$fc,$03,$09,$07	;Trk A; grrrarrr.mml: 102
	db	$fc,$03,$09,$06,$fc,$03,$09,$07	;Trk A; grrrarrr.mml: 102
	db	$fc,$03,$fc,$09,$09,$0e,$fc,$05	;Trk A; grrrarrr.mml: 102
	db	$fc,$09,$09,$07,$fc,$03,$09,$06	;Trk A; grrrarrr.mml: 102
	db	$fc,$03,$09,$07,$fc,$03,$09,$06	;Trk A; grrrarrr.mml: 102
	db	$fc,$03,$fc,$0a,$02,$06,$fc,$03	;Trk A; grrrarrr.mml: 102
	db	$09,$07,$fc,$03,$09,$06,$fc,$03	;Trk A; grrrarrr.mml: 103
	db	$09,$07,$fc,$03,$09,$06,$fc,$03	;Trk A; grrrarrr.mml: 103
	db	$09,$07,$fc,$03,$09,$06,$fc,$03	;Trk A; grrrarrr.mml: 103
	db	$fc,$0a,$04,$06,$fc,$03,$04,$07	;Trk A; grrrarrr.mml: 103
	db	$fc,$03,$fc,$09,$0b,$06,$fc,$03	;Trk A; grrrarrr.mml: 103
	db	$0b,$07,$fc,$03,$0b,$06,$fc,$03	;Trk A; grrrarrr.mml: 103
	db	$0b,$07,$fc,$03,$fc,$09,$07,$07	;Trk A; grrrarrr.mml: 103
	db	$fc,$03,$04,$06,$fc,$03,$04,$07	;Trk A; grrrarrr.mml: 104
	db	$fc,$03,$04,$06,$fc,$03,$04,$07	;Trk A; grrrarrr.mml: 104
	db	$fc,$03,$04,$06,$fc,$03,$04,$07	;Trk A; grrrarrr.mml: 104
	db	$fc,$03,$fc,$09,$0b,$07,$fc,$03	;Trk A; grrrarrr.mml: 104
	db	$0b,$06,$fc,$03,$fc,$13,$0b,$09	;Trk A; grrrarrr.mml: 104
	db	$fc,$04,$0b,$09,$fc,$03,$0b,$09	;Trk A; grrrarrr.mml: 104
	db	$fc,$04,$fc,$09,$09,$07,$fc,$03	;Trk A; grrrarrr.mml: 104
	db	$09,$06,$fc,$03,$09,$07,$fc,$03	;Trk A; grrrarrr.mml: 102
	db	$09,$06,$fc,$03,$09,$07,$fc,$03	;Trk A; grrrarrr.mml: 102
	db	$09,$06,$fc,$03,$fc,$0a,$09,$0e	;Trk A; grrrarrr.mml: 102
	db	$fc,$05,$fc,$09,$09,$07,$fc,$03	;Trk A; grrrarrr.mml: 102
	db	$09,$06,$fc,$03,$09,$07,$fc,$03	;Trk A; grrrarrr.mml: 102
	db	$09,$06,$fc,$03,$fc,$0a,$fc,$09	;Trk A; grrrarrr.mml: 102
	db	$09,$06,$fc,$03,$09,$07,$fc,$03	;Trk A; grrrarrr.mml: 102
	db	$09,$06,$fc,$03,$09,$07,$fc,$03	;Trk A; grrrarrr.mml: 102
	db	$09,$06,$fc,$03,$09,$07,$fc,$03	;Trk A; grrrarrr.mml: 102
	db	$fc,$09,$09,$0e,$fc,$05,$fc,$0a	;Trk A; grrrarrr.mml: 102
	db	$09,$06,$fc,$03,$09,$07,$fc,$03	;Trk A; grrrarrr.mml: 102
	db	$09,$06,$fc,$03,$09,$07,$fc,$03	;Trk A; grrrarrr.mml: 102
	db	$fc,$09,$02,$07,$fc,$03,$09,$06	;Trk A; grrrarrr.mml: 102
	db	$fc,$03,$09,$07,$fc,$03,$09,$06	;Trk A; grrrarrr.mml: 103
	db	$fc,$03,$09,$06,$fc,$03,$09,$07	;Trk A; grrrarrr.mml: 103
	db	$fc,$03,$09,$06,$fc,$03,$fc,$0a	;Trk A; grrrarrr.mml: 103
	db	$04,$06,$fc,$03,$04,$07,$fc,$03	;Trk A; grrrarrr.mml: 103
	db	$fc,$09,$0b,$07,$fc,$03,$0b,$06	;Trk A; grrrarrr.mml: 103
	db	$fc,$03,$0b,$07,$fc,$03,$0b,$06	;Trk A; grrrarrr.mml: 103
	db	$fc,$03,$fc,$0a,$07,$06,$fc,$03	;Trk A; grrrarrr.mml: 103
	db	$04,$07,$fc,$03,$04,$06,$fc,$03	;Trk A; grrrarrr.mml: 104
	db	$04,$07,$fc,$03,$04,$06,$fc,$03	;Trk A; grrrarrr.mml: 104
	db	$04,$07,$fc,$03,$04,$06,$fc,$03	;Trk A; grrrarrr.mml: 104
	db	$fc,$09,$0b,$07,$fc,$03,$0b,$06	;Trk A; grrrarrr.mml: 104
	db	$fc,$03,$fc,$13,$0b,$09,$fc,$04	;Trk A; grrrarrr.mml: 104
	db	$0b,$09,$fc,$04,$0b,$09,$fc,$03	;Trk A; grrrarrr.mml: 104
	db	$02,$15,$fc,$08,$fc,$09,$02,$15	;Trk A; grrrarrr.mml: 161
	db	$fc,$08,$fc,$09,$02,$1c,$fc,$0a	;Trk A; grrrarrr.mml: 161
	db	$04,$0e,$fc,$05,$fc,$09,$02,$07	;Trk A; grrrarrr.mml: 161
	db	$fc,$03,$02,$06,$fc,$03,$02,$07	;Trk A; grrrarrr.mml: 161
	db	$fc,$03,$02,$06,$fc,$03,$fc,$0a	;Trk A; grrrarrr.mml: 162
	db	$fc,$13,$00,$06,$fc,$03,$fc,$0a	;Trk A; grrrarrr.mml: 162
	db	$02,$06,$fc,$03,$02,$07,$fc,$03	;Trk A; grrrarrr.mml: 162
	db	$02,$06,$fc,$03,$fc,$0a,$fc,$12	;Trk A; grrrarrr.mml: 162
	db	$00,$07,$fc,$03,$fc,$09,$04,$07	;Trk A; grrrarrr.mml: 162
	db	$fc,$03,$04,$06,$fc,$03,$04,$07	;Trk A; grrrarrr.mml: 164
	db	$fc,$03,$fc,$09,$fc,$13,$14,$07	;Trk A; grrrarrr.mml: 164
	db	$fc,$03,$fc,$09,$04,$07,$fc,$03	;Trk A; grrrarrr.mml: 164
	db	$04,$06,$fc,$03,$04,$07,$fc,$03	;Trk A; grrrarrr.mml: 165
	db	$fc,$09,$fc,$0a,$14,$0e,$fc,$05	;Trk A; grrrarrr.mml: 165
	db	$fc,$09,$04,$06,$fc,$03,$04,$07	;Trk A; grrrarrr.mml: 165
	db	$fc,$03,$04,$06,$fc,$03,$fc,$0a	;Trk A; grrrarrr.mml: 166
	db	$fc,$13,$14,$0e,$fc,$05,$0b,$06	;Trk A; grrrarrr.mml: 166
	db	$fc,$03,$0b,$07,$fc,$03,$fc,$09	;Trk A; grrrarrr.mml: 168
	db	$0a,$1c,$fc,$0a,$fc,$0a,$02,$15	;Trk A; grrrarrr.mml: 168
	db	$fc,$07,$fc,$09,$05,$15,$fc,$08	;Trk A; grrrarrr.mml: 170
	db	$fc,$09,$02,$1c,$fc,$0a,$09,$0e	;Trk A; grrrarrr.mml: 170
	db	$fc,$05,$fc,$0a,$05,$06,$fc,$03	;Trk A; grrrarrr.mml: 170
	db	$02,$07,$fc,$03,$02,$06,$fc,$03	;Trk A; grrrarrr.mml: 171
	db	$02,$07,$fc,$03,$fc,$09,$fc,$13	;Trk A; grrrarrr.mml: 171
	db	$00,$06,$fc,$03,$fc,$0a,$02,$06	;Trk A; grrrarrr.mml: 171
	db	$fc,$03,$02,$07,$fc,$03,$02,$06	;Trk A; grrrarrr.mml: 172
	db	$fc,$03,$fc,$0a,$12,$09,$fc,$03	;Trk A; grrrarrr.mml: 172
	db	$15,$09,$fc,$04,$19,$09,$fc,$04	;Trk A; grrrarrr.mml: 172
	db	$04,$15,$fc,$07,$fc,$0a,$fc,$13	;Trk A; grrrarrr.mml: 174
	db	$14,$06,$fc,$03,$fc,$0a,$04,$06	;Trk A; grrrarrr.mml: 174
	db	$fc,$03,$04,$06,$fc,$03,$04,$07	;Trk A; grrrarrr.mml: 175
	db	$fc,$03,$fc,$09,$fc,$13,$14,$07	;Trk A; grrrarrr.mml: 175
	db	$fc,$03,$04,$06,$fc,$03,$04,$07	;Trk A; grrrarrr.mml: 175
	db	$fc,$03,$04,$06,$fc,$03,$04,$07	;Trk A; grrrarrr.mml: 176
	db	$fc,$03,$fc,$09,$fc,$13,$14,$07	;Trk A; grrrarrr.mml: 176
	db	$fc,$03,$12,$06,$fc,$03,$0b,$0e	;Trk A; grrrarrr.mml: 176
	db	$fc,$05,$fc,$0a,$0a,$1b,$fc,$0a	;Trk A; grrrarrr.mml: 178
	db	$fc,$0a,$f1,$08,$fd,$02,$34,$1c	;Trk A; grrrarrr.mml: 178
	db	$fc,$0a,$34,$09,$fc,$03,$37,$09	;Trk A; grrrarrr.mml: 181
	db	$fc,$04,$3b,$09,$fc,$04,$34,$0e	;Trk A; grrrarrr.mml: 181
	db	$fc,$05,$32,$15,$fc,$07,$3b,$09	;Trk A; grrrarrr.mml: 181
	db	$fc,$04,$37,$09,$fc,$03,$34,$10	;Trk A; grrrarrr.mml: 181
	db	$fc,$06,$34,$1c,$fc,$0a
song_000_00_lp:
	db	$fc,$ff,$ee
	db	bank(song_000_00_lp)
	dw	song_000_00_lp


song_000_01:	;Trk B
	db	$fd,$9f,$f1,$08,$fd,$02,$fc,$13	;Trk B; grrrarrr.mml: 53
	db	$fe,$80,$24,$0e,$fc,$05,$fc,$13	;Trk B; grrrarrr.mml: 76
	db	$fd,$85,$24,$04,$fc,$02,$fd,$8a	;Trk B; grrrarrr.mml: 76
	db	$24,$04,$fc,$02,$fd,$8f,$24,$05	;Trk B; grrrarrr.mml: 76
	db	$fc,$02,$fc,$13,$24,$0e,$fc,$05	;Trk B; grrrarrr.mml: 76
	db	$fc,$13,$fd,$85,$24,$04,$fc,$02	;Trk B; grrrarrr.mml: 76
	db	$fd,$8a,$24,$04,$fc,$02,$fd,$8f	;Trk B; grrrarrr.mml: 76
	db	$24,$05,$fc,$02,$fc,$13,$24,$0d	;Trk B; grrrarrr.mml: 76
	db	$fc,$05,$fc,$13,$fd,$85,$24,$05	;Trk B; grrrarrr.mml: 76
	db	$fc,$02,$fd,$8a,$24,$04,$fc,$02	;Trk B; grrrarrr.mml: 76
	db	$fd,$8f,$24,$04,$fc,$02,$fc,$13	;Trk B; grrrarrr.mml: 76
	db	$24,$0e,$fc,$05,$fc,$13,$fd,$85	;Trk B; grrrarrr.mml: 76
	db	$24,$05,$fc,$02,$fd,$8a,$24,$04	;Trk B; grrrarrr.mml: 76
	db	$fc,$02,$fd,$8f,$24,$04,$fc,$02	;Trk B; grrrarrr.mml: 76
	db	$fc,$13,$24,$0e,$fc,$05,$fc,$13	;Trk B; grrrarrr.mml: 76
	db	$fd,$85,$24,$04,$fc,$02,$fd,$8a	;Trk B; grrrarrr.mml: 76
	db	$24,$05,$fc,$02,$fd,$8f,$24,$04	;Trk B; grrrarrr.mml: 76
	db	$fc,$02,$fc,$13,$24,$0e,$fc,$05	;Trk B; grrrarrr.mml: 76
	db	$fc,$13,$fd,$85,$24,$04,$fc,$02	;Trk B; grrrarrr.mml: 76
	db	$fd,$8a,$24,$04,$fc,$02,$fd,$8f	;Trk B; grrrarrr.mml: 76
	db	$24,$05,$fc,$02,$fc,$13,$24,$0e	;Trk B; grrrarrr.mml: 76
	db	$fc,$05,$fc,$13,$fd,$85,$24,$04	;Trk B; grrrarrr.mml: 76
	db	$fc,$02,$fd,$8a,$24,$04,$fc,$02	;Trk B; grrrarrr.mml: 76
	db	$fd,$8f,$24,$05,$fc,$02,$fc,$12	;Trk B; grrrarrr.mml: 76
	db	$24,$0e,$fc,$05,$fc,$13,$fd,$85	;Trk B; grrrarrr.mml: 76
	db	$24,$05,$fc,$02,$fd,$8a,$24,$04	;Trk B; grrrarrr.mml: 76
	db	$fc,$02,$fd,$8f,$24,$04,$fc,$02	;Trk B; grrrarrr.mml: 76
	db	$fc,$13,$24,$0e,$fc,$05,$fc,$13	;Trk B; grrrarrr.mml: 76
	db	$fd,$85,$24,$04,$fc,$02,$fd,$8a	;Trk B; grrrarrr.mml: 76
	db	$24,$05,$fc,$02,$fd,$8f,$24,$04	;Trk B; grrrarrr.mml: 76
	db	$fc,$02,$fc,$13,$24,$0e,$fc,$05	;Trk B; grrrarrr.mml: 76
	db	$fc,$13,$fd,$85,$24,$04,$fc,$02	;Trk B; grrrarrr.mml: 76
	db	$fd,$8a,$24,$05,$fc,$02,$fd,$8f	;Trk B; grrrarrr.mml: 76
	db	$24,$04,$fc,$02,$fc,$13,$24,$0e	;Trk B; grrrarrr.mml: 76
	db	$fc,$05,$fc,$13,$fd,$85,$24,$04	;Trk B; grrrarrr.mml: 76
	db	$fc,$02,$fd,$8a,$24,$04,$fc,$02	;Trk B; grrrarrr.mml: 76
	db	$fd,$8f,$24,$05,$fc,$02,$fc,$13	;Trk B; grrrarrr.mml: 76
	db	$24,$0e,$fc,$05,$fc,$13,$fd,$85	;Trk B; grrrarrr.mml: 76
	db	$24,$04,$fc,$02,$fd,$8a,$24,$04	;Trk B; grrrarrr.mml: 76
	db	$fc,$02,$fd,$8f,$24,$04,$fc,$02	;Trk B; grrrarrr.mml: 76
	db	$fc,$13,$24,$0e,$fc,$05,$fc,$13	;Trk B; grrrarrr.mml: 76
	db	$fd,$85,$24,$05,$fc,$02,$fd,$8a	;Trk B; grrrarrr.mml: 76
	db	$24,$04,$fc,$02,$fd,$8f,$24,$04	;Trk B; grrrarrr.mml: 76
	db	$fc,$02,$fc,$13,$24,$0e,$fc,$05	;Trk B; grrrarrr.mml: 76
	db	$fc,$13,$fd,$85,$24,$04,$fc,$02	;Trk B; grrrarrr.mml: 76
	db	$fd,$8a,$24,$05,$fc,$02,$fd,$8f	;Trk B; grrrarrr.mml: 76
	db	$24,$04,$fc,$02,$fc,$13,$24,$0e	;Trk B; grrrarrr.mml: 76
	db	$fc,$05,$fc,$13,$fd,$85,$24,$04	;Trk B; grrrarrr.mml: 76
	db	$fc,$02,$fd,$8a,$24,$05,$fc,$02	;Trk B; grrrarrr.mml: 76
	db	$fd,$8f,$24,$04,$fc,$02,$fc,$13	;Trk B; grrrarrr.mml: 76
	db	$24,$0e,$fc,$05,$fc,$13,$fd,$85	;Trk B; grrrarrr.mml: 76
	db	$24,$04,$fc,$02,$fd,$8a,$24,$04	;Trk B; grrrarrr.mml: 76
	db	$fc,$02,$fd,$8f,$24,$05,$fc,$02	;Trk B; grrrarrr.mml: 76
	db	$29,$0a,$fc,$04,$fc,$05,$29,$0a	;Trk B; grrrarrr.mml: 106
	db	$fc,$04,$fc,$05,$29,$0a,$fc,$04	;Trk B; grrrarrr.mml: 106
	db	$fc,$04,$fc,$13,$29,$0e,$fc,$05	;Trk B; grrrarrr.mml: 106
	db	$fc,$0a,$29,$1c,$fc,$0a,$fc,$09	;Trk B; grrrarrr.mml: 106
	db	$29,$0a,$fc,$04,$fc,$05,$29,$0a	;Trk B; grrrarrr.mml: 106
	db	$fc,$04,$fc,$05,$29,$0a,$fc,$04	;Trk B; grrrarrr.mml: 106
	db	$fc,$05,$fc,$13,$29,$0e,$fc,$05	;Trk B; grrrarrr.mml: 106
	db	$fc,$09,$29,$1c,$fc,$0a,$fc,$0a	;Trk B; grrrarrr.mml: 106
	db	$29,$0a,$fc,$04,$fc,$05,$29,$0a	;Trk B; grrrarrr.mml: 110
	db	$fc,$04,$fc,$05,$29,$0a,$fc,$04	;Trk B; grrrarrr.mml: 110
	db	$fc,$05,$fc,$13,$24,$0e,$fc,$05	;Trk B; grrrarrr.mml: 110
	db	$fc,$09,$2b,$1c,$fc,$0a,$fc,$09	;Trk B; grrrarrr.mml: 110
	db	$24,$0b,$fc,$04,$fc,$04,$24,$0b	;Trk B; grrrarrr.mml: 114
	db	$fc,$04,$fc,$04,$24,$0a,$fc,$04	;Trk B; grrrarrr.mml: 114
	db	$fc,$05,$fc,$13,$2b,$0e,$fc,$05	;Trk B; grrrarrr.mml: 114
	db	$fc,$0a,$2b,$1b,$fc,$0a,$fc,$0a	;Trk B; grrrarrr.mml: 114
	db	$29,$0a,$fc,$04,$fc,$05,$29,$0a	;Trk B; grrrarrr.mml: 106
	db	$fc,$04,$fc,$05,$29,$0a,$fc,$04	;Trk B; grrrarrr.mml: 106
	db	$fc,$05,$fc,$13,$29,$0e,$fc,$05	;Trk B; grrrarrr.mml: 106
	db	$fc,$09,$29,$1c,$fc,$0a,$fc,$0a	;Trk B; grrrarrr.mml: 106
	db	$29,$0a,$fc,$04,$fc,$04,$29,$0b	;Trk B; grrrarrr.mml: 106
	db	$fc,$04,$fc,$04,$29,$0b,$fc,$04	;Trk B; grrrarrr.mml: 106
	db	$fc,$04,$fc,$13,$29,$0e,$fc,$05	;Trk B; grrrarrr.mml: 106
	db	$fc,$0a,$29,$1c,$fc,$0a,$fc,$09	;Trk B; grrrarrr.mml: 106
	db	$29,$0a,$fc,$04,$fc,$05,$29,$0a	;Trk B; grrrarrr.mml: 110
	db	$fc,$04,$fc,$05,$29,$0a,$fc,$04	;Trk B; grrrarrr.mml: 110
	db	$fc,$05,$fc,$13,$24,$0e,$fc,$05	;Trk B; grrrarrr.mml: 110
	db	$fc,$09,$2b,$1c,$fc,$0a,$fc,$0a	;Trk B; grrrarrr.mml: 110
	db	$24,$0a,$fc,$04,$fc,$05,$24,$0a	;Trk B; grrrarrr.mml: 114
	db	$fc,$04,$fc,$05,$24,$0a,$fc,$04	;Trk B; grrrarrr.mml: 114
	db	$fc,$05,$fc,$12,$2b,$0e,$fc,$05	;Trk B; grrrarrr.mml: 114
	db	$fc,$0a,$2b,$1c,$fc,$0a,$fc,$09	;Trk B; grrrarrr.mml: 114
	db	$22,$0e,$fc,$05,$fc,$0a,$22,$1c	;Trk B; grrrarrr.mml: 143
	db	$fc,$0a,$fc,$09,$22,$0e,$fc,$05	;Trk B; grrrarrr.mml: 143
	db	$fc,$09,$22,$1c,$fc,$0a,$fc,$0a	;Trk B; grrrarrr.mml: 143
	db	$22,$0e,$fc,$05,$fc,$09,$22,$1c	;Trk B; grrrarrr.mml: 143
	db	$fc,$0a,$fc,$0a,$22,$0e,$fc,$05	;Trk B; grrrarrr.mml: 143
	db	$fc,$09,$22,$1c,$fc,$0a,$fc,$09	;Trk B; grrrarrr.mml: 143
	db	$24,$0e,$fc,$05,$fc,$0a,$24,$1c	;Trk B; grrrarrr.mml: 147
	db	$fc,$0a,$fc,$09,$24,$0e,$fc,$05	;Trk B; grrrarrr.mml: 147
	db	$fc,$0a,$24,$1c,$fc,$0a,$fc,$09	;Trk B; grrrarrr.mml: 147
	db	$24,$06,$fc,$03,$24,$07,$fc,$03	;Trk B; grrrarrr.mml: 150
	db	$24,$06,$fc,$03,$fc,$0a,$24,$06	;Trk B; grrrarrr.mml: 150
	db	$fc,$03,$fc,$0a,$24,$06,$fc,$03	;Trk B; grrrarrr.mml: 150
	db	$24,$07,$fc,$03,$2b,$0e,$fc,$05	;Trk B; grrrarrr.mml: 150
	db	$fc,$09,$2a,$1c,$fc,$0a,$fc,$0a	;Trk B; grrrarrr.mml: 154
	db	$22,$0e,$fc,$05,$fc,$09,$22,$1c	;Trk B; grrrarrr.mml: 143
	db	$fc,$0a,$fc,$09,$22,$0e,$fc,$05	;Trk B; grrrarrr.mml: 143
	db	$fc,$0a,$22,$1c,$fc,$0a,$fc,$09	;Trk B; grrrarrr.mml: 143
	db	$22,$0e,$fc,$05,$fc,$0a,$22,$1b	;Trk B; grrrarrr.mml: 143
	db	$fc,$0a,$fc,$0a,$22,$0e,$fc,$05	;Trk B; grrrarrr.mml: 143
	db	$fc,$09,$22,$1c,$fc,$0a,$fc,$0a	;Trk B; grrrarrr.mml: 143
	db	$24,$0e,$fc,$05,$fc,$09,$24,$1c	;Trk B; grrrarrr.mml: 147
	db	$fc,$0a,$fc,$0a,$24,$0d,$fc,$05	;Trk B; grrrarrr.mml: 147
	db	$fc,$0a,$24,$1c,$fc,$0a,$fc,$09	;Trk B; grrrarrr.mml: 147
	db	$24,$07,$fc,$03,$24,$06,$fc,$03	;Trk B; grrrarrr.mml: 150
	db	$24,$07,$fc,$03,$fc,$09,$24,$07	;Trk B; grrrarrr.mml: 150
	db	$fc,$03,$fc,$09,$24,$07,$fc,$03	;Trk B; grrrarrr.mml: 150
	db	$24,$06,$fc,$03,$2b,$0e,$fc,$05	;Trk B; grrrarrr.mml: 150
	db	$fc,$0a,$2a,$1b,$fc,$0a,$fc,$0a	;Trk B; grrrarrr.mml: 154
	db	$24,$71,$fc,$26,$fc,$0a,$24,$1c	;Trk B; grrrarrr.mml: 182
	db	$fc,$0a,$22,$39,$fc,$13
song_000_01_lp:
	db	$fc,$ff,$ee
	db	bank(song_000_01_lp)
	dw	song_000_01_lp


song_000_02:	;Trk C
	db	$fd,$9f,$f1,$08,$fd,$02,$fc,$13	;Trk C; grrrarrr.mml: 53
	db	$27,$0e,$fc,$05,$fc,$13,$fd,$85	;Trk C; grrrarrr.mml: 77
	db	$27,$04,$fc,$02,$fd,$8a,$27,$04	;Trk C; grrrarrr.mml: 77
	db	$fc,$02,$fd,$8f,$27,$05,$fc,$02	;Trk C; grrrarrr.mml: 77
	db	$fc,$13,$27,$0e,$fc,$05,$fc,$13	;Trk C; grrrarrr.mml: 77
	db	$fd,$85,$27,$04,$fc,$02,$fd,$8a	;Trk C; grrrarrr.mml: 77
	db	$27,$04,$fc,$02,$fd,$8f,$27,$05	;Trk C; grrrarrr.mml: 77
	db	$fc,$02,$fc,$13,$27,$0d,$fc,$05	;Trk C; grrrarrr.mml: 77
	db	$fc,$13,$fd,$85,$27,$05,$fc,$02	;Trk C; grrrarrr.mml: 77
	db	$fd,$8a,$27,$04,$fc,$02,$fd,$8f	;Trk C; grrrarrr.mml: 77
	db	$27,$04,$fc,$02,$fc,$13,$27,$0e	;Trk C; grrrarrr.mml: 77
	db	$fc,$05,$fc,$13,$fd,$85,$27,$05	;Trk C; grrrarrr.mml: 77
	db	$fc,$02,$fd,$8a,$27,$04,$fc,$02	;Trk C; grrrarrr.mml: 77
	db	$fd,$8f,$27,$04,$fc,$02,$fc,$13	;Trk C; grrrarrr.mml: 77
	db	$27,$0e,$fc,$05,$fc,$13,$fd,$85	;Trk C; grrrarrr.mml: 77
	db	$27,$04,$fc,$02,$fd,$8a,$27,$05	;Trk C; grrrarrr.mml: 77
	db	$fc,$02,$fd,$8f,$27,$04,$fc,$02	;Trk C; grrrarrr.mml: 77
	db	$fc,$13,$27,$0e,$fc,$05,$fc,$13	;Trk C; grrrarrr.mml: 77
	db	$fd,$85,$27,$04,$fc,$02,$fd,$8a	;Trk C; grrrarrr.mml: 77
	db	$27,$04,$fc,$02,$fd,$8f,$27,$05	;Trk C; grrrarrr.mml: 77
	db	$fc,$02,$fc,$13,$27,$0e,$fc,$05	;Trk C; grrrarrr.mml: 77
	db	$fc,$13,$fd,$85,$27,$04,$fc,$02	;Trk C; grrrarrr.mml: 77
	db	$fd,$8a,$27,$04,$fc,$02,$fd,$8f	;Trk C; grrrarrr.mml: 77
	db	$27,$05,$fc,$02,$fc,$12,$27,$0e	;Trk C; grrrarrr.mml: 77
	db	$fc,$05,$fc,$13,$fd,$85,$27,$05	;Trk C; grrrarrr.mml: 77
	db	$fc,$02,$fd,$8a,$27,$04,$fc,$02	;Trk C; grrrarrr.mml: 77
	db	$fd,$8f,$27,$04,$fc,$02,$fc,$13	;Trk C; grrrarrr.mml: 77
	db	$27,$0e,$fc,$05,$fc,$13,$fd,$85	;Trk C; grrrarrr.mml: 77
	db	$27,$04,$fc,$02,$fd,$8a,$27,$05	;Trk C; grrrarrr.mml: 77
	db	$fc,$02,$fd,$8f,$27,$04,$fc,$02	;Trk C; grrrarrr.mml: 77
	db	$fc,$13,$27,$0e,$fc,$05,$fc,$13	;Trk C; grrrarrr.mml: 77
	db	$fd,$85,$27,$04,$fc,$02,$fd,$8a	;Trk C; grrrarrr.mml: 77
	db	$27,$05,$fc,$02,$fd,$8f,$27,$04	;Trk C; grrrarrr.mml: 77
	db	$fc,$02,$fc,$13,$27,$0e,$fc,$05	;Trk C; grrrarrr.mml: 77
	db	$fc,$13,$fd,$85,$27,$04,$fc,$02	;Trk C; grrrarrr.mml: 77
	db	$fd,$8a,$27,$04,$fc,$02,$fd,$8f	;Trk C; grrrarrr.mml: 77
	db	$27,$05,$fc,$02,$fc,$13,$27,$0e	;Trk C; grrrarrr.mml: 77
	db	$fc,$05,$fc,$13,$fd,$85,$27,$04	;Trk C; grrrarrr.mml: 77
	db	$fc,$02,$fd,$8a,$27,$04,$fc,$02	;Trk C; grrrarrr.mml: 77
	db	$fd,$8f,$27,$04,$fc,$02,$fc,$13	;Trk C; grrrarrr.mml: 77
	db	$27,$0e,$fc,$05,$fc,$13,$fd,$85	;Trk C; grrrarrr.mml: 77
	db	$27,$05,$fc,$02,$fd,$8a,$27,$04	;Trk C; grrrarrr.mml: 77
	db	$fc,$02,$fd,$8f,$27,$04,$fc,$02	;Trk C; grrrarrr.mml: 77
	db	$fc,$13,$27,$0e,$fc,$05,$fc,$13	;Trk C; grrrarrr.mml: 77
	db	$fd,$85,$27,$04,$fc,$02,$fd,$8a	;Trk C; grrrarrr.mml: 77
	db	$27,$05,$fc,$02,$fd,$8f,$27,$04	;Trk C; grrrarrr.mml: 77
	db	$fc,$02,$fc,$13,$27,$0e,$fc,$05	;Trk C; grrrarrr.mml: 77
	db	$fc,$13,$fd,$85,$27,$04,$fc,$02	;Trk C; grrrarrr.mml: 77
	db	$fd,$8a,$27,$05,$fc,$02,$fd,$8f	;Trk C; grrrarrr.mml: 77
	db	$27,$04,$fc,$02,$fc,$13,$27,$0e	;Trk C; grrrarrr.mml: 77
	db	$fc,$05,$fc,$13,$fd,$85,$27,$04	;Trk C; grrrarrr.mml: 77
	db	$fc,$02,$fd,$8a,$27,$04,$fc,$02	;Trk C; grrrarrr.mml: 77
	db	$fd,$8f,$27,$05,$fc,$02,$20,$0a	;Trk C; grrrarrr.mml: 77
	db	$fc,$04,$fc,$05,$20,$0a,$fc,$04	;Trk C; grrrarrr.mml: 107
	db	$fc,$05,$20,$0a,$fc,$04,$fc,$04	;Trk C; grrrarrr.mml: 107
	db	$fc,$13,$20,$0e,$fc,$05,$fc,$0a	;Trk C; grrrarrr.mml: 107
	db	$20,$1c,$fc,$0a,$fc,$09,$20,$0a	;Trk C; grrrarrr.mml: 107
	db	$fc,$04,$fc,$05,$20,$0a,$fc,$04	;Trk C; grrrarrr.mml: 107
	db	$fc,$05,$20,$0a,$fc,$04,$fc,$05	;Trk C; grrrarrr.mml: 107
	db	$fc,$13,$20,$0e,$fc,$05,$fc,$09	;Trk C; grrrarrr.mml: 107
	db	$20,$1c,$fc,$0a,$fc,$0a,$20,$0a	;Trk C; grrrarrr.mml: 107
	db	$fc,$04,$fc,$05,$20,$0a,$fc,$04	;Trk C; grrrarrr.mml: 111
	db	$fc,$05,$20,$0a,$fc,$04,$fc,$05	;Trk C; grrrarrr.mml: 111
	db	$fc,$13,$27,$0e,$fc,$05,$fc,$09	;Trk C; grrrarrr.mml: 111
	db	$22,$1c,$fc,$0a,$fc,$09,$27,$0b	;Trk C; grrrarrr.mml: 111
	db	$fc,$04,$fc,$04,$27,$0b,$fc,$04	;Trk C; grrrarrr.mml: 115
	db	$fc,$04,$27,$0a,$fc,$04,$fc,$05	;Trk C; grrrarrr.mml: 115
	db	$fc,$13,$22,$0e,$fc,$05,$fc,$0a	;Trk C; grrrarrr.mml: 115
	db	$22,$1b,$fc,$0a,$fc,$0a,$20,$0a	;Trk C; grrrarrr.mml: 115
	db	$fc,$04,$fc,$05,$20,$0a,$fc,$04	;Trk C; grrrarrr.mml: 107
	db	$fc,$05,$20,$0a,$fc,$04,$fc,$05	;Trk C; grrrarrr.mml: 107
	db	$fc,$13,$20,$0e,$fc,$05,$fc,$09	;Trk C; grrrarrr.mml: 107
	db	$20,$1c,$fc,$0a,$fc,$0a,$20,$0a	;Trk C; grrrarrr.mml: 107
	db	$fc,$04,$fc,$04,$20,$0b,$fc,$04	;Trk C; grrrarrr.mml: 107
	db	$fc,$04,$20,$0b,$fc,$04,$fc,$04	;Trk C; grrrarrr.mml: 107
	db	$fc,$13,$20,$0e,$fc,$05,$fc,$0a	;Trk C; grrrarrr.mml: 107
	db	$20,$1c,$fc,$0a,$fc,$09,$20,$0a	;Trk C; grrrarrr.mml: 107
	db	$fc,$04,$fc,$05,$20,$0a,$fc,$04	;Trk C; grrrarrr.mml: 111
	db	$fc,$05,$20,$0a,$fc,$04,$fc,$05	;Trk C; grrrarrr.mml: 111
	db	$fc,$13,$27,$0e,$fc,$05,$fc,$09	;Trk C; grrrarrr.mml: 111
	db	$22,$1c,$fc,$0a,$fc,$0a,$27,$0a	;Trk C; grrrarrr.mml: 111
	db	$fc,$04,$fc,$05,$27,$0a,$fc,$04	;Trk C; grrrarrr.mml: 115
	db	$fc,$05,$27,$0a,$fc,$04,$fc,$05	;Trk C; grrrarrr.mml: 115
	db	$fc,$12,$22,$0e,$fc,$05,$fc,$0a	;Trk C; grrrarrr.mml: 115
	db	$22,$1c,$fc,$0a,$fc,$09,$25,$0e	;Trk C; grrrarrr.mml: 115
	db	$fc,$05,$fc,$0a,$25,$1c,$fc,$0a	;Trk C; grrrarrr.mml: 144
	db	$fc,$09,$25,$0e,$fc,$05,$fc,$09	;Trk C; grrrarrr.mml: 144
	db	$25,$1c,$fc,$0a,$fc,$0a,$25,$0e	;Trk C; grrrarrr.mml: 144
	db	$fc,$05,$fc,$09,$25,$1c,$fc,$0a	;Trk C; grrrarrr.mml: 144
	db	$fc,$0a,$25,$0e,$fc,$05,$fc,$09	;Trk C; grrrarrr.mml: 144
	db	$25,$1c,$fc,$0a,$fc,$09,$27,$0e	;Trk C; grrrarrr.mml: 144
	db	$fc,$05,$fc,$0a,$27,$1c,$fc,$0a	;Trk C; grrrarrr.mml: 148
	db	$fc,$09,$27,$0e,$fc,$05,$fc,$0a	;Trk C; grrrarrr.mml: 148
	db	$27,$1c,$fc,$0a,$fc,$09,$27,$06	;Trk C; grrrarrr.mml: 148
	db	$fc,$03,$27,$07,$fc,$03,$27,$06	;Trk C; grrrarrr.mml: 151
	db	$fc,$03,$fc,$0a,$27,$06,$fc,$03	;Trk C; grrrarrr.mml: 151
	db	$fc,$0a,$27,$06,$fc,$03,$27,$07	;Trk C; grrrarrr.mml: 151
	db	$fc,$03,$22,$0e,$fc,$05,$fc,$09	;Trk C; grrrarrr.mml: 151
	db	$21,$1c,$fc,$0a,$fc,$0a,$25,$0e	;Trk C; grrrarrr.mml: 155
	db	$fc,$05,$fc,$09,$25,$1c,$fc,$0a	;Trk C; grrrarrr.mml: 144
	db	$fc,$09,$25,$0e,$fc,$05,$fc,$0a	;Trk C; grrrarrr.mml: 144
	db	$25,$1c,$fc,$0a,$fc,$09,$25,$0e	;Trk C; grrrarrr.mml: 144
	db	$fc,$05,$fc,$0a,$25,$1b,$fc,$0a	;Trk C; grrrarrr.mml: 144
	db	$fc,$0a,$25,$0e,$fc,$05,$fc,$09	;Trk C; grrrarrr.mml: 144
	db	$25,$1c,$fc,$0a,$fc,$0a,$27,$0e	;Trk C; grrrarrr.mml: 144
	db	$fc,$05,$fc,$09,$27,$1c,$fc,$0a	;Trk C; grrrarrr.mml: 148
	db	$fc,$0a,$27,$0d,$fc,$05,$fc,$0a	;Trk C; grrrarrr.mml: 148
	db	$27,$1c,$fc,$0a,$fc,$09,$27,$07	;Trk C; grrrarrr.mml: 148
	db	$fc,$03,$27,$06,$fc,$03,$27,$07	;Trk C; grrrarrr.mml: 151
	db	$fc,$03,$fc,$09,$27,$07,$fc,$03	;Trk C; grrrarrr.mml: 151
	db	$fc,$09,$27,$07,$fc,$03,$27,$06	;Trk C; grrrarrr.mml: 151
	db	$fc,$03,$22,$0e,$fc,$05,$fc,$0a	;Trk C; grrrarrr.mml: 151
	db	$21,$1b,$fc,$0a,$fc,$0a,$27,$71	;Trk C; grrrarrr.mml: 155
	db	$fc,$26,$fc,$0a,$27,$1c,$fc,$0a	;Trk C; grrrarrr.mml: 183
	db	$25,$39,$fc,$13
song_000_02_lp:
	db	$fc,$ff,$ee
	db	bank(song_000_02_lp)
	dw	song_000_02_lp


song_000_03:	;Trk D
	db	$fd,$9f,$f1,$08,$fd,$02,$fc,$13	;Trk D; grrrarrr.mml: 53
	db	$2b,$0e,$fc,$05,$fc,$13,$fd,$85	;Trk D; grrrarrr.mml: 78
	db	$2b,$04,$fc,$02,$fd,$8a,$2b,$04	;Trk D; grrrarrr.mml: 78
	db	$fc,$02,$fd,$8f,$2b,$05,$fc,$02	;Trk D; grrrarrr.mml: 78
	db	$fc,$13,$2b,$0e,$fc,$05,$fc,$13	;Trk D; grrrarrr.mml: 78
	db	$fd,$85,$2b,$04,$fc,$02,$fd,$8a	;Trk D; grrrarrr.mml: 78
	db	$2b,$04,$fc,$02,$fd,$8f,$2b,$05	;Trk D; grrrarrr.mml: 78
	db	$fc,$02,$fc,$13,$2b,$0d,$fc,$05	;Trk D; grrrarrr.mml: 78
	db	$fc,$13,$fd,$85,$2b,$05,$fc,$02	;Trk D; grrrarrr.mml: 78
	db	$fd,$8a,$2b,$04,$fc,$02,$fd,$8f	;Trk D; grrrarrr.mml: 78
	db	$2b,$04,$fc,$02,$fc,$13,$2b,$0e	;Trk D; grrrarrr.mml: 78
	db	$fc,$05,$fc,$13,$fd,$85,$2b,$05	;Trk D; grrrarrr.mml: 78
	db	$fc,$02,$fd,$8a,$2b,$04,$fc,$02	;Trk D; grrrarrr.mml: 78
	db	$fd,$8f,$2b,$04,$fc,$02,$fc,$13	;Trk D; grrrarrr.mml: 78
	db	$2b,$0e,$fc,$05,$fc,$13,$fd,$85	;Trk D; grrrarrr.mml: 78
	db	$2b,$04,$fc,$02,$fd,$8a,$2b,$05	;Trk D; grrrarrr.mml: 78
	db	$fc,$02,$fd,$8f,$2b,$04,$fc,$02	;Trk D; grrrarrr.mml: 78
	db	$fc,$13,$2b,$0e,$fc,$05,$fc,$13	;Trk D; grrrarrr.mml: 78
	db	$fd,$85,$2b,$04,$fc,$02,$fd,$8a	;Trk D; grrrarrr.mml: 78
	db	$2b,$04,$fc,$02,$fd,$8f,$2b,$05	;Trk D; grrrarrr.mml: 78
	db	$fc,$02,$fc,$13,$2b,$0e,$fc,$05	;Trk D; grrrarrr.mml: 78
	db	$fc,$13,$fd,$85,$2b,$04,$fc,$02	;Trk D; grrrarrr.mml: 78
	db	$fd,$8a,$2b,$04,$fc,$02,$fd,$8f	;Trk D; grrrarrr.mml: 78
	db	$2b,$05,$fc,$02,$fc,$12,$2b,$0e	;Trk D; grrrarrr.mml: 78
	db	$fc,$05,$fc,$13,$fd,$85,$2b,$05	;Trk D; grrrarrr.mml: 78
	db	$fc,$02,$fd,$8a,$2b,$04,$fc,$02	;Trk D; grrrarrr.mml: 78
	db	$fd,$8f,$2b,$04,$fc,$02,$fc,$13	;Trk D; grrrarrr.mml: 78
	db	$2b,$0e,$fc,$05,$fc,$13,$fd,$85	;Trk D; grrrarrr.mml: 78
	db	$2b,$04,$fc,$02,$fd,$8a,$2b,$05	;Trk D; grrrarrr.mml: 78
	db	$fc,$02,$fd,$8f,$2b,$04,$fc,$02	;Trk D; grrrarrr.mml: 78
	db	$fc,$13,$2b,$0e,$fc,$05,$fc,$13	;Trk D; grrrarrr.mml: 78
	db	$fd,$85,$2b,$04,$fc,$02,$fd,$8a	;Trk D; grrrarrr.mml: 78
	db	$2b,$05,$fc,$02,$fd,$8f,$2b,$04	;Trk D; grrrarrr.mml: 78
	db	$fc,$02,$fc,$13,$2b,$0e,$fc,$05	;Trk D; grrrarrr.mml: 78
	db	$fc,$13,$fd,$85,$2b,$04,$fc,$02	;Trk D; grrrarrr.mml: 78
	db	$fd,$8a,$2b,$04,$fc,$02,$fd,$8f	;Trk D; grrrarrr.mml: 78
	db	$2b,$05,$fc,$02,$fc,$13,$2b,$0e	;Trk D; grrrarrr.mml: 78
	db	$fc,$05,$fc,$13,$fd,$85,$2b,$04	;Trk D; grrrarrr.mml: 78
	db	$fc,$02,$fd,$8a,$2b,$04,$fc,$02	;Trk D; grrrarrr.mml: 78
	db	$fd,$8f,$2b,$04,$fc,$02,$fc,$13	;Trk D; grrrarrr.mml: 78
	db	$2b,$0e,$fc,$05,$fc,$13,$fd,$85	;Trk D; grrrarrr.mml: 78
	db	$2b,$05,$fc,$02,$fd,$8a,$2b,$04	;Trk D; grrrarrr.mml: 78
	db	$fc,$02,$fd,$8f,$2b,$04,$fc,$02	;Trk D; grrrarrr.mml: 78
	db	$fc,$13,$2b,$0e,$fc,$05,$fc,$13	;Trk D; grrrarrr.mml: 78
	db	$fd,$85,$2b,$04,$fc,$02,$fd,$8a	;Trk D; grrrarrr.mml: 78
	db	$2b,$05,$fc,$02,$fd,$8f,$2b,$04	;Trk D; grrrarrr.mml: 78
	db	$fc,$02,$fc,$13,$2b,$0e,$fc,$05	;Trk D; grrrarrr.mml: 78
	db	$fc,$13,$fd,$85,$2b,$04,$fc,$02	;Trk D; grrrarrr.mml: 78
	db	$fd,$8a,$2b,$05,$fc,$02,$fd,$8f	;Trk D; grrrarrr.mml: 78
	db	$2b,$04,$fc,$02,$fc,$13,$2b,$0e	;Trk D; grrrarrr.mml: 78
	db	$fc,$05,$fc,$13,$fd,$85,$2b,$04	;Trk D; grrrarrr.mml: 78
	db	$fc,$02,$fd,$8a,$2b,$04,$fc,$02	;Trk D; grrrarrr.mml: 78
	db	$fd,$8f,$2b,$05,$fc,$02,$24,$0a	;Trk D; grrrarrr.mml: 78
	db	$fc,$04,$fc,$05,$24,$0a,$fc,$04	;Trk D; grrrarrr.mml: 108
	db	$fc,$05,$24,$0a,$fc,$04,$fc,$04	;Trk D; grrrarrr.mml: 108
	db	$fc,$13,$24,$0e,$fc,$05,$fc,$0a	;Trk D; grrrarrr.mml: 108
	db	$24,$1c,$fc,$0a,$fc,$09,$24,$0a	;Trk D; grrrarrr.mml: 108
	db	$fc,$04,$fc,$05,$24,$0a,$fc,$04	;Trk D; grrrarrr.mml: 108
	db	$fc,$05,$24,$0a,$fc,$04,$fc,$05	;Trk D; grrrarrr.mml: 108
	db	$fc,$13,$24,$0e,$fc,$05,$fc,$09	;Trk D; grrrarrr.mml: 108
	db	$24,$1c,$fc,$0a,$fc,$0a,$24,$0a	;Trk D; grrrarrr.mml: 108
	db	$fc,$04,$fc,$05,$24,$0a,$fc,$04	;Trk D; grrrarrr.mml: 112
	db	$fc,$05,$24,$0a,$fc,$04,$fc,$05	;Trk D; grrrarrr.mml: 112
	db	$fc,$13,$2b,$0e,$fc,$05,$fc,$09	;Trk D; grrrarrr.mml: 112
	db	$24,$1c,$fc,$0a,$fc,$09,$2b,$0b	;Trk D; grrrarrr.mml: 112
	db	$fc,$04,$fc,$04,$2b,$0b,$fc,$04	;Trk D; grrrarrr.mml: 116
	db	$fc,$04,$2b,$0a,$fc,$04,$fc,$05	;Trk D; grrrarrr.mml: 116
	db	$fc,$13,$25,$0e,$fc,$05,$fc,$0a	;Trk D; grrrarrr.mml: 116
	db	$25,$1b,$fc,$0a,$fc,$0a,$24,$0a	;Trk D; grrrarrr.mml: 116
	db	$fc,$04,$fc,$05,$24,$0a,$fc,$04	;Trk D; grrrarrr.mml: 108
	db	$fc,$05,$24,$0a,$fc,$04,$fc,$05	;Trk D; grrrarrr.mml: 108
	db	$fc,$13,$24,$0e,$fc,$05,$fc,$09	;Trk D; grrrarrr.mml: 108
	db	$24,$1c,$fc,$0a,$fc,$0a,$24,$0a	;Trk D; grrrarrr.mml: 108
	db	$fc,$04,$fc,$04,$24,$0b,$fc,$04	;Trk D; grrrarrr.mml: 108
	db	$fc,$04,$24,$0b,$fc,$04,$fc,$04	;Trk D; grrrarrr.mml: 108
	db	$fc,$13,$24,$0e,$fc,$05,$fc,$0a	;Trk D; grrrarrr.mml: 108
	db	$24,$1c,$fc,$0a,$fc,$09,$24,$0a	;Trk D; grrrarrr.mml: 108
	db	$fc,$04,$fc,$05,$24,$0a,$fc,$04	;Trk D; grrrarrr.mml: 112
	db	$fc,$05,$24,$0a,$fc,$04,$fc,$05	;Trk D; grrrarrr.mml: 112
	db	$fc,$13,$2b,$0e,$fc,$05,$fc,$09	;Trk D; grrrarrr.mml: 112
	db	$24,$1c,$fc,$0a,$fc,$0a,$2b,$0a	;Trk D; grrrarrr.mml: 112
	db	$fc,$04,$fc,$05,$2b,$0a,$fc,$04	;Trk D; grrrarrr.mml: 116
	db	$fc,$05,$2b,$0a,$fc,$04,$fc,$05	;Trk D; grrrarrr.mml: 116
	db	$fc,$12,$25,$0e,$fc,$05,$fc,$0a	;Trk D; grrrarrr.mml: 116
	db	$25,$1c,$fc,$0a,$fc,$09,$29,$0e	;Trk D; grrrarrr.mml: 116
	db	$fc,$05,$fc,$0a,$29,$1c,$fc,$0a	;Trk D; grrrarrr.mml: 145
	db	$fc,$09,$29,$0e,$fc,$05,$fc,$09	;Trk D; grrrarrr.mml: 145
	db	$29,$1c,$fc,$0a,$fc,$0a,$29,$0e	;Trk D; grrrarrr.mml: 145
	db	$fc,$05,$fc,$09,$29,$1c,$fc,$0a	;Trk D; grrrarrr.mml: 145
	db	$fc,$0a,$29,$0e,$fc,$05,$fc,$09	;Trk D; grrrarrr.mml: 145
	db	$29,$1c,$fc,$0a,$fc,$09,$2b,$0e	;Trk D; grrrarrr.mml: 145
	db	$fc,$05,$fc,$0a,$2b,$1c,$fc,$0a	;Trk D; grrrarrr.mml: 149
	db	$fc,$09,$2b,$0e,$fc,$05,$fc,$0a	;Trk D; grrrarrr.mml: 149
	db	$2b,$1c,$fc,$0a,$fc,$09,$2b,$06	;Trk D; grrrarrr.mml: 149
	db	$fc,$03,$2b,$07,$fc,$03,$2b,$06	;Trk D; grrrarrr.mml: 152
	db	$fc,$03,$fc,$0a,$32,$06,$fc,$03	;Trk D; grrrarrr.mml: 152
	db	$fc,$0a,$32,$06,$fc,$03,$32,$07	;Trk D; grrrarrr.mml: 152
	db	$fc,$03,$25,$0e,$fc,$05,$fc,$09	;Trk D; grrrarrr.mml: 152
	db	$24,$1c,$fc,$0a,$fc,$0a,$29,$0e	;Trk D; grrrarrr.mml: 156
	db	$fc,$05,$fc,$09,$29,$1c,$fc,$0a	;Trk D; grrrarrr.mml: 145
	db	$fc,$09,$29,$0e,$fc,$05,$fc,$0a	;Trk D; grrrarrr.mml: 145
	db	$29,$1c,$fc,$0a,$fc,$09,$29,$0e	;Trk D; grrrarrr.mml: 145
	db	$fc,$05,$fc,$0a,$29,$1b,$fc,$0a	;Trk D; grrrarrr.mml: 145
	db	$fc,$0a,$29,$0e,$fc,$05,$fc,$09	;Trk D; grrrarrr.mml: 145
	db	$29,$1c,$fc,$0a,$fc,$0a,$2b,$0e	;Trk D; grrrarrr.mml: 145
	db	$fc,$05,$fc,$09,$2b,$1c,$fc,$0a	;Trk D; grrrarrr.mml: 149
	db	$fc,$0a,$2b,$0d,$fc,$05,$fc,$0a	;Trk D; grrrarrr.mml: 149
	db	$2b,$1c,$fc,$0a,$fc,$09,$2b,$07	;Trk D; grrrarrr.mml: 149
	db	$fc,$03,$2b,$06,$fc,$03,$2b,$07	;Trk D; grrrarrr.mml: 152
	db	$fc,$03,$fc,$09,$32,$07,$fc,$03	;Trk D; grrrarrr.mml: 152
	db	$fc,$09,$32,$07,$fc,$03,$32,$06	;Trk D; grrrarrr.mml: 152
	db	$fc,$03,$25,$0e,$fc,$05,$fc,$0a	;Trk D; grrrarrr.mml: 152
	db	$24,$1b,$fc,$0a,$fc,$0a,$2b,$71	;Trk D; grrrarrr.mml: 156
	db	$fc,$26,$fc,$0a,$2a,$1c,$fc,$0a	;Trk D; grrrarrr.mml: 184
	db	$2a,$39,$fc,$13
song_000_03_lp:
	db	$fc,$ff,$ee
	db	bank(song_000_03_lp)
	dw	song_000_03_lp


song_000_04:	;Trk E
	db	$fd,$9f,$f1,$08,$fd,$02,$fc,$4c	;Trk E; grrrarrr.mml: 53
	db	$fc,$4c,$fc,$4b,$fc,$39,$fd,$85	;Trk E; grrrarrr.mml: 81
	db	$34,$05,$fc,$02,$fd,$8a,$32,$04	;Trk E; grrrarrr.mml: 82
	db	$fc,$02,$fd,$8f,$32,$04,$fc,$02	;Trk E; grrrarrr.mml: 82
	db	$fc,$39,$fd,$85,$34,$04,$fc,$02	;Trk E; grrrarrr.mml: 82
	db	$fd,$8a,$32,$05,$fc,$02,$fd,$8f	;Trk E; grrrarrr.mml: 82
	db	$32,$04,$fc,$02,$fc,$13,$32,$0e	;Trk E; grrrarrr.mml: 82
	db	$fc,$05,$fc,$13,$fd,$85,$34,$04	;Trk E; grrrarrr.mml: 83
	db	$fc,$02,$fd,$8a,$32,$04,$fc,$02	;Trk E; grrrarrr.mml: 83
	db	$fd,$8f,$32,$05,$fc,$02,$fc,$13	;Trk E; grrrarrr.mml: 83
	db	$32,$0e,$fc,$05,$fc,$13,$fd,$85	;Trk E; grrrarrr.mml: 83
	db	$34,$04,$fc,$02,$fd,$8a,$32,$04	;Trk E; grrrarrr.mml: 83
	db	$fc,$02,$fd,$8f,$32,$05,$fc,$02	;Trk E; grrrarrr.mml: 83
	db	$fc,$12,$34,$0e,$fc,$05,$fc,$13	;Trk E; grrrarrr.mml: 84
	db	$fd,$85,$34,$05,$fc,$02,$fd,$8a	;Trk E; grrrarrr.mml: 84
	db	$34,$04,$fc,$02,$fd,$00,$f1,$01	;Trk E; grrrarrr.mml: 84
	db	$34,$04,$fc,$02,$3b,$06,$fc,$02	;Trk E; grrrarrr.mml: 84
	db	$37,$05,$fc,$02,$34,$06,$fc,$02	;Trk E; grrrarrr.mml: 85
	db	$3b,$06,$fc,$02,$3b,$05,$fc,$02	;Trk E; grrrarrr.mml: 85
	db	$37,$06,$fc,$02,$37,$05,$fc,$02	;Trk E; grrrarrr.mml: 85
	db	$34,$06,$fc,$02,$fc,$08,$34,$05	;Trk E; grrrarrr.mml: 85
	db	$fc,$02,$3b,$06,$fc,$02,$37,$05	;Trk E; grrrarrr.mml: 85
	db	$fc,$02,$34,$06,$fc,$02,$3b,$05	;Trk E; grrrarrr.mml: 85
	db	$fc,$02,$3b,$06,$fc,$02,$37,$06	;Trk E; grrrarrr.mml: 85
	db	$fc,$02,$37,$05,$fc,$02,$34,$06	;Trk E; grrrarrr.mml: 85
	db	$fc,$02,$fc,$07,$34,$06,$fc,$02	;Trk E; grrrarrr.mml: 85
	db	$3b,$05,$fc,$02,$37,$06,$fc,$02	;Trk E; grrrarrr.mml: 85
	db	$34,$06,$fc,$02,$3b,$05,$fc,$02	;Trk E; grrrarrr.mml: 85
	db	$3b,$06,$fc,$02,$37,$05,$fc,$02	;Trk E; grrrarrr.mml: 85
	db	$37,$06,$fc,$02,$34,$06,$fc,$02	;Trk E; grrrarrr.mml: 85
	db	$fc,$07,$34,$06,$fc,$02,$3b,$03	;Trk E; grrrarrr.mml: 85
	db	$fc,$01,$37,$03,$fc,$02,$32,$03	;Trk E; grrrarrr.mml: 86
	db	$fc,$02,$3b,$03,$fc,$02,$37,$03	;Trk E; grrrarrr.mml: 86
	db	$fc,$01,$42,$03,$fc,$02,$fc,$05	;Trk E; grrrarrr.mml: 86
	db	$42,$03,$fc,$02,$fd,$02,$f1,$08	;Trk E; grrrarrr.mml: 86
	db	$44,$04,$fc,$02,$44,$04,$fc,$02	;Trk E; grrrarrr.mml: 86
	db	$44,$05,$fc,$02,$34,$04,$fc,$02	;Trk E; grrrarrr.mml: 86
	db	$34,$04,$fc,$02,$34,$04,$fc,$02	;Trk E; grrrarrr.mml: 87
	db	$fc,$26,$fd,$85,$34,$05,$fc,$02	;Trk E; grrrarrr.mml: 87
	db	$fd,$8a,$32,$04,$fc,$02,$fd,$8f	;Trk E; grrrarrr.mml: 87
	db	$32,$04,$fc,$02,$32,$1c,$fc,$0a	;Trk E; grrrarrr.mml: 87
	db	$fc,$13,$fd,$85,$34,$04,$fc,$02	;Trk E; grrrarrr.mml: 88
	db	$fd,$8a,$36,$05,$fc,$02,$fd,$8f	;Trk E; grrrarrr.mml: 88
	db	$37,$04,$fc,$02,$34,$1c,$fc,$0a	;Trk E; grrrarrr.mml: 88
	db	$fc,$13,$fd,$85,$32,$04,$fc,$02	;Trk E; grrrarrr.mml: 89
	db	$fd,$8a,$34,$05,$fc,$02,$fd,$8f	;Trk E; grrrarrr.mml: 89
	db	$34,$04,$fc,$02,$37,$03,$fc,$02	;Trk E; grrrarrr.mml: 89
	db	$36,$03,$fc,$01,$37,$1c,$fc,$0a	;Trk E; grrrarrr.mml: 90
	db	$34,$02,$fc,$01,$34,$03,$fc,$01	;Trk E; grrrarrr.mml: 90
	db	$34,$02,$fc,$01,$fd,$8a,$34,$09	;Trk E; grrrarrr.mml: 90
	db	$fc,$03,$fd,$8c,$37,$09,$fc,$04	;Trk E; grrrarrr.mml: 90
	db	$fd,$8f,$3b,$09,$fc,$04,$f1,$07	;Trk E; grrrarrr.mml: 90
	db	$fd,$91,$fc,$4b,$fc,$4c,$fc,$4c	;Trk E; grrrarrr.mml: 126
	db	$fc,$4c,$fc,$4c,$42,$0e,$fc,$05	;Trk E; grrrarrr.mml: 126
	db	$fc,$09,$49,$1c,$fc,$0a,$fc,$09	;Trk E; grrrarrr.mml: 127
	db	$42,$0c,$fc,$04,$42,$0b,$fc,$04	;Trk E; grrrarrr.mml: 128
	db	$42,$0b,$fc,$04,$44,$0b,$fc,$04	;Trk E; grrrarrr.mml: 128
	db	$42,$0b,$fc,$04,$49,$0e,$fc,$05	;Trk E; grrrarrr.mml: 128
	db	$fc,$0a,$f8,$01,$49,$1b,$fc,$0a	;Trk E; grrrarrr.mml: 128
	db	$f8,$ff,$fc,$0a,$fd,$02,$f1,$02	;Trk E; grrrarrr.mml: 128
	db	$47,$04,$fc,$02,$44,$05,$fc,$02	;Trk E; grrrarrr.mml: 129
	db	$40,$04,$fc,$02,$49,$04,$fc,$02	;Trk E; grrrarrr.mml: 129
	db	$40,$05,$fc,$02,$49,$04,$fc,$02	;Trk E; grrrarrr.mml: 129
	db	$47,$04,$fc,$02,$44,$04,$fc,$02	;Trk E; grrrarrr.mml: 129
	db	$40,$05,$fc,$02,$49,$04,$fc,$02	;Trk E; grrrarrr.mml: 129
	db	$40,$04,$fc,$02,$49,$05,$fc,$02	;Trk E; grrrarrr.mml: 129
	db	$44,$09,$fc,$03,$57,$09,$fc,$04	;Trk E; grrrarrr.mml: 130
	db	$59,$09,$fc,$04,$47,$09,$fc,$03	;Trk E; grrrarrr.mml: 130
	db	$49,$09,$fc,$04,$40,$09,$fc,$04	;Trk E; grrrarrr.mml: 130
	db	$47,$04,$fc,$02,$44,$04,$fc,$02	;Trk E; grrrarrr.mml: 130
	db	$40,$04,$fc,$02,$49,$05,$fc,$02	;Trk E; grrrarrr.mml: 130
	db	$40,$04,$fc,$02,$49,$04,$fc,$02	;Trk E; grrrarrr.mml: 130
	db	$59,$05,$fc,$02,$44,$04,$fc,$02	;Trk E; grrrarrr.mml: 131
	db	$40,$04,$fc,$02,$49,$05,$fc,$02	;Trk E; grrrarrr.mml: 131
	db	$40,$04,$fc,$02,$49,$04,$fc,$02	;Trk E; grrrarrr.mml: 131
	db	$59,$05,$fc,$02,$44,$04,$fc,$02	;Trk E; grrrarrr.mml: 131
	db	$4b,$04,$fc,$02,$42,$05,$fc,$02	;Trk E; grrrarrr.mml: 131
	db	$44,$04,$fc,$02,$4b,$04,$fc,$02	;Trk E; grrrarrr.mml: 131
	db	$59,$05,$fc,$02,$44,$04,$fc,$02	;Trk E; grrrarrr.mml: 131
	db	$4b,$04,$fc,$02,$42,$04,$fc,$02	;Trk E; grrrarrr.mml: 131
	db	$44,$05,$fc,$02,$4b,$04,$fc,$02	;Trk E; grrrarrr.mml: 131
	db	$f8,$01,$49,$39,$fc,$13,$44,$1c	;Trk E; grrrarrr.mml: 132
	db	$fc,$0a,$4b,$1c,$fc,$0a,$f8,$ff	;Trk E; grrrarrr.mml: 132
	db	$34,$38,$fc,$13,$3b,$13,$fc,$07	;Trk E; grrrarrr.mml: 133
	db	$32,$12,$fc,$07,$35,$12,$fc,$07	;Trk E; grrrarrr.mml: 133

song_000_04_lp:
	db	$fc,$ff,$ee
	db	bank(song_000_04_lp)
	dw	song_000_04_lp


song_000_05:	;Trk F
	db	$fd,$9f,$f2,$01,$fd,$00,$f2,$00	;Trk F; grrrarrr.mml: 53
	db	$f1,$06,$f8,$00,$fd,$9f,$20,$04	;Trk F; grrrarrr.mml: 93
	db	$fc,$02,$fd,$94,$20,$05,$fc,$02	;Trk F; grrrarrr.mml: 93
	db	$fd,$8f,$20,$04,$fc,$02,$f2,$01	;Trk F; grrrarrr.mml: 93
	db	$fd,$00,$20,$06,$fc,$03,$20,$07	;Trk F; grrrarrr.mml: 93
	db	$fc,$03,$fc,$13,$fd,$85,$24,$04	;Trk F; grrrarrr.mml: 93
	db	$fc,$02,$fd,$8a,$20,$04,$fc,$02	;Trk F; grrrarrr.mml: 93
	db	$fd,$00,$20,$05,$fc,$02,$f2,$00	;Trk F; grrrarrr.mml: 93
	db	$f1,$06,$f8,$00,$fd,$9f,$20,$04	;Trk F; grrrarrr.mml: 93
	db	$fc,$02,$fd,$94,$20,$04,$fc,$02	;Trk F; grrrarrr.mml: 93
	db	$fd,$8f,$20,$05,$fc,$02,$f2,$01	;Trk F; grrrarrr.mml: 93
	db	$fd,$00,$20,$06,$fc,$03,$20,$07	;Trk F; grrrarrr.mml: 93
	db	$fc,$03,$fc,$13,$fd,$85,$24,$04	;Trk F; grrrarrr.mml: 93
	db	$fc,$02,$fd,$8a,$20,$04,$fc,$02	;Trk F; grrrarrr.mml: 93
	db	$fd,$00,$20,$05,$fc,$02,$f2,$00	;Trk F; grrrarrr.mml: 93
	db	$f1,$06,$f8,$00,$fd,$9f,$20,$04	;Trk F; grrrarrr.mml: 93
	db	$fc,$02,$fd,$94,$20,$04,$fc,$02	;Trk F; grrrarrr.mml: 93
	db	$fd,$8f,$20,$05,$fc,$02,$f2,$01	;Trk F; grrrarrr.mml: 93
	db	$fd,$00,$20,$06,$fc,$03,$20,$06	;Trk F; grrrarrr.mml: 93
	db	$fc,$03,$fc,$13,$fd,$85,$24,$05	;Trk F; grrrarrr.mml: 93
	db	$fc,$02,$fd,$8a,$20,$04,$fc,$02	;Trk F; grrrarrr.mml: 93
	db	$fd,$00,$20,$04,$fc,$02,$f2,$00	;Trk F; grrrarrr.mml: 93
	db	$fd,$9f,$20,$07,$fc,$03,$fc,$09	;Trk F; grrrarrr.mml: 94
	db	$20,$07,$fc,$03,$fc,$09,$f2,$01	;Trk F; grrrarrr.mml: 94
	db	$fd,$00,$20,$0e,$fc,$05,$fc,$0a	;Trk F; grrrarrr.mml: 94
	db	$20,$02,$fc,$01,$fd,$01,$20,$02	;Trk F; grrrarrr.mml: 94
	db	$fc,$01,$20,$02,$fc,$01,$f2,$00	;Trk F; grrrarrr.mml: 94
	db	$f1,$06,$f8,$00,$fd,$9f,$20,$04	;Trk F; grrrarrr.mml: 95
	db	$fc,$02,$fd,$94,$20,$05,$fc,$02	;Trk F; grrrarrr.mml: 95
	db	$fd,$8f,$20,$04,$fc,$02,$f2,$01	;Trk F; grrrarrr.mml: 95
	db	$fd,$00,$20,$07,$fc,$03,$20,$06	;Trk F; grrrarrr.mml: 95
	db	$fc,$03,$fc,$13,$fd,$85,$24,$04	;Trk F; grrrarrr.mml: 95
	db	$fc,$02,$fd,$8a,$20,$05,$fc,$02	;Trk F; grrrarrr.mml: 95
	db	$fd,$00,$20,$04,$fc,$02,$f2,$00	;Trk F; grrrarrr.mml: 95
	db	$f1,$06,$f8,$00,$fd,$9f,$20,$04	;Trk F; grrrarrr.mml: 95
	db	$fc,$02,$fd,$94,$20,$05,$fc,$02	;Trk F; grrrarrr.mml: 95
	db	$fd,$8f,$20,$04,$fc,$02,$f2,$01	;Trk F; grrrarrr.mml: 95
	db	$fd,$00,$20,$06,$fc,$03,$20,$07	;Trk F; grrrarrr.mml: 95
	db	$fc,$03,$fc,$13,$fd,$85,$24,$04	;Trk F; grrrarrr.mml: 95
	db	$fc,$02,$fd,$8a,$20,$04,$fc,$02	;Trk F; grrrarrr.mml: 95
	db	$fd,$00,$20,$05,$fc,$02,$f2,$00	;Trk F; grrrarrr.mml: 95
	db	$f1,$06,$f8,$00,$fd,$9f,$20,$04	;Trk F; grrrarrr.mml: 95
	db	$fc,$02,$fd,$94,$20,$04,$fc,$02	;Trk F; grrrarrr.mml: 95
	db	$fd,$8f,$20,$05,$fc,$02,$f2,$01	;Trk F; grrrarrr.mml: 95
	db	$fd,$00,$20,$06,$fc,$03,$20,$07	;Trk F; grrrarrr.mml: 95
	db	$fc,$03,$fc,$13,$fd,$85,$24,$04	;Trk F; grrrarrr.mml: 95
	db	$fc,$02,$fd,$8a,$20,$04,$fc,$02	;Trk F; grrrarrr.mml: 95
	db	$fd,$00,$20,$05,$fc,$02,$f2,$00	;Trk F; grrrarrr.mml: 95
	db	$fd,$9f,$20,$03,$fc,$01,$fc,$05	;Trk F; grrrarrr.mml: 96
	db	$20,$03,$fc,$02,$fc,$04,$20,$03	;Trk F; grrrarrr.mml: 96
	db	$fc,$02,$fc,$05,$fc,$09,$f2,$01	;Trk F; grrrarrr.mml: 96
	db	$fd,$00,$20,$03,$fc,$02,$fc,$05	;Trk F; grrrarrr.mml: 96
	db	$20,$03,$fc,$02,$fc,$04,$20,$03	;Trk F; grrrarrr.mml: 96
	db	$fc,$02,$fc,$05,$20,$02,$fc,$01	;Trk F; grrrarrr.mml: 96
	db	$fd,$01,$20,$02,$fc,$01,$20,$02	;Trk F; grrrarrr.mml: 96
	db	$fc,$01,$f2,$00,$f1,$06,$f8,$00	;Trk F; grrrarrr.mml: 96
	db	$fd,$9f,$20,$05,$fc,$02,$fd,$94	;Trk F; grrrarrr.mml: 93
	db	$20,$04,$fc,$02,$fd,$8f,$20,$04	;Trk F; grrrarrr.mml: 93
	db	$fc,$02,$f2,$01,$fd,$00,$20,$07	;Trk F; grrrarrr.mml: 93
	db	$fc,$03,$20,$06,$fc,$03,$fc,$13	;Trk F; grrrarrr.mml: 93
	db	$fd,$85,$24,$04,$fc,$02,$fd,$8a	;Trk F; grrrarrr.mml: 93
	db	$20,$05,$fc,$02,$fd,$00,$20,$04	;Trk F; grrrarrr.mml: 93
	db	$fc,$02,$f2,$00,$f1,$06,$f8,$00	;Trk F; grrrarrr.mml: 93
	db	$fd,$9f,$20,$04,$fc,$02,$fd,$94	;Trk F; grrrarrr.mml: 93
	db	$20,$05,$fc,$02,$fd,$8f,$20,$04	;Trk F; grrrarrr.mml: 93
	db	$fc,$02,$f2,$01,$fd,$00,$20,$07	;Trk F; grrrarrr.mml: 93
	db	$fc,$03,$20,$06,$fc,$03,$fc,$13	;Trk F; grrrarrr.mml: 93
	db	$fd,$85,$24,$04,$fc,$02,$fd,$8a	;Trk F; grrrarrr.mml: 93
	db	$20,$05,$fc,$02,$fd,$00,$20,$04	;Trk F; grrrarrr.mml: 93
	db	$fc,$02,$f2,$00,$f1,$06,$f8,$00	;Trk F; grrrarrr.mml: 93
	db	$fd,$9f,$20,$04,$fc,$02,$fd,$94	;Trk F; grrrarrr.mml: 93
	db	$20,$05,$fc,$02,$fd,$8f,$20,$04	;Trk F; grrrarrr.mml: 93
	db	$fc,$02,$f2,$01,$fd,$00,$20,$06	;Trk F; grrrarrr.mml: 93
	db	$fc,$03,$20,$07,$fc,$03,$fc,$13	;Trk F; grrrarrr.mml: 93
	db	$fd,$85,$24,$04,$fc,$02,$fd,$8a	;Trk F; grrrarrr.mml: 93
	db	$20,$04,$fc,$02,$fd,$00,$20,$05	;Trk F; grrrarrr.mml: 93
	db	$fc,$02,$f2,$00,$fd,$9f,$20,$06	;Trk F; grrrarrr.mml: 93
	db	$fc,$03,$fc,$0a,$20,$06,$fc,$03	;Trk F; grrrarrr.mml: 94
	db	$fc,$0a,$f2,$01,$fd,$00,$20,$0e	;Trk F; grrrarrr.mml: 94
	db	$fc,$05,$fc,$09,$20,$02,$fc,$01	;Trk F; grrrarrr.mml: 94
	db	$fd,$01,$20,$02,$fc,$01,$20,$02	;Trk F; grrrarrr.mml: 94
	db	$fc,$01,$f2,$00,$f1,$06,$f8,$00	;Trk F; grrrarrr.mml: 94
	db	$fd,$9f,$20,$05,$fc,$02,$fd,$94	;Trk F; grrrarrr.mml: 95
	db	$20,$04,$fc,$02,$fd,$8f,$20,$04	;Trk F; grrrarrr.mml: 95
	db	$fc,$02,$f2,$01,$fd,$00,$20,$07	;Trk F; grrrarrr.mml: 95
	db	$fc,$03,$20,$06,$fc,$03,$fc,$13	;Trk F; grrrarrr.mml: 95
	db	$fd,$85,$24,$05,$fc,$02,$fd,$8a	;Trk F; grrrarrr.mml: 95
	db	$20,$04,$fc,$02,$fd,$00,$20,$04	;Trk F; grrrarrr.mml: 95
	db	$fc,$02,$f2,$00,$f1,$06,$f8,$00	;Trk F; grrrarrr.mml: 95
	db	$fd,$9f,$20,$05,$fc,$02,$fd,$94	;Trk F; grrrarrr.mml: 95
	db	$20,$04,$fc,$02,$fd,$8f,$20,$04	;Trk F; grrrarrr.mml: 95
	db	$fc,$02,$f2,$01,$fd,$00,$20,$07	;Trk F; grrrarrr.mml: 95
	db	$fc,$03,$20,$06,$fc,$03,$fc,$13	;Trk F; grrrarrr.mml: 95
	db	$fd,$85,$24,$04,$fc,$02,$fd,$8a	;Trk F; grrrarrr.mml: 95
	db	$20,$05,$fc,$02,$fd,$00,$20,$04	;Trk F; grrrarrr.mml: 95
	db	$fc,$02,$f2,$00,$f1,$06,$f8,$00	;Trk F; grrrarrr.mml: 95
	db	$fd,$9f,$20,$04,$fc,$02,$fd,$94	;Trk F; grrrarrr.mml: 95
	db	$20,$05,$fc,$02,$fd,$8f,$20,$04	;Trk F; grrrarrr.mml: 95
	db	$fc,$02,$f2,$01,$fd,$00,$20,$06	;Trk F; grrrarrr.mml: 95
	db	$fc,$03,$20,$07,$fc,$03,$fc,$13	;Trk F; grrrarrr.mml: 95
	db	$fd,$85,$24,$04,$fc,$02,$fd,$8a	;Trk F; grrrarrr.mml: 95
	db	$20,$05,$fc,$02,$fd,$00,$20,$04	;Trk F; grrrarrr.mml: 95
	db	$fc,$02,$f2,$00,$fd,$9f,$20,$03	;Trk F; grrrarrr.mml: 95
	db	$fc,$02,$fc,$04,$20,$03,$fc,$02	;Trk F; grrrarrr.mml: 96
	db	$fc,$05,$20,$03,$fc,$02,$fc,$04	;Trk F; grrrarrr.mml: 96
	db	$fc,$0a,$f2,$01,$fd,$00,$20,$03	;Trk F; grrrarrr.mml: 96
	db	$fc,$01,$fc,$05,$20,$03,$fc,$02	;Trk F; grrrarrr.mml: 96
	db	$fc,$05,$20,$03,$fc,$01,$fc,$05	;Trk F; grrrarrr.mml: 96
	db	$20,$02,$fc,$01,$fd,$01,$20,$02	;Trk F; grrrarrr.mml: 96
	db	$fc,$01,$20,$03,$fc,$01,$f8,$00	;Trk F; grrrarrr.mml: 96
	db	$fc,$38,$f2,$01,$fd,$00,$20,$07	;Trk F; grrrarrr.mml: 118
	db	$fc,$03,$fc,$09,$f2,$00,$f1,$06	;Trk F; grrrarrr.mml: 118
	db	$f8,$00,$fd,$9f,$20,$07,$fc,$03	;Trk F; grrrarrr.mml: 119
	db	$fc,$09,$f2,$01,$fd,$00,$20,$07	;Trk F; grrrarrr.mml: 119
	db	$fc,$03,$f2,$00,$fd,$9f,$20,$06	;Trk F; grrrarrr.mml: 119
	db	$fc,$03,$fc,$13,$f2,$01,$fd,$00	;Trk F; grrrarrr.mml: 119
	db	$20,$07,$fc,$03,$fc,$09,$f2,$00	;Trk F; grrrarrr.mml: 119
	db	$f1,$06,$f8,$00,$fd,$9f,$20,$07	;Trk F; grrrarrr.mml: 121
	db	$fc,$03,$fc,$09,$f2,$01,$fd,$00	;Trk F; grrrarrr.mml: 121
	db	$20,$07,$fc,$03,$f2,$00,$fd,$9f	;Trk F; grrrarrr.mml: 121
	db	$20,$06,$fc,$03,$fc,$13,$f2,$01	;Trk F; grrrarrr.mml: 121
	db	$fd,$00,$20,$07,$fc,$03,$fc,$09	;Trk F; grrrarrr.mml: 121
	db	$f2,$00,$f1,$06,$f8,$00,$fd,$9f	;Trk F; grrrarrr.mml: 121
	db	$20,$06,$fc,$03,$fc,$0a,$f2,$01	;Trk F; grrrarrr.mml: 121
	db	$fd,$00,$20,$06,$fc,$03,$f2,$00	;Trk F; grrrarrr.mml: 121
	db	$fd,$9f,$20,$07,$fc,$03,$fc,$13	;Trk F; grrrarrr.mml: 121
	db	$f2,$01,$fd,$00,$20,$06,$fc,$03	;Trk F; grrrarrr.mml: 121
	db	$fc,$0a,$f2,$00,$f1,$06,$f8,$00	;Trk F; grrrarrr.mml: 121
	db	$fd,$9f,$20,$06,$fc,$03,$fc,$0a	;Trk F; grrrarrr.mml: 121
	db	$f2,$01,$fd,$00,$20,$06,$fc,$03	;Trk F; grrrarrr.mml: 121
	db	$f2,$00,$fd,$9f,$20,$07,$fc,$03	;Trk F; grrrarrr.mml: 121
	db	$fc,$13,$f2,$01,$fd,$00,$20,$06	;Trk F; grrrarrr.mml: 121
	db	$fc,$03,$fc,$0a,$f2,$00,$f1,$06	;Trk F; grrrarrr.mml: 121
	db	$f8,$00,$fd,$9f,$20,$06,$fc,$03	;Trk F; grrrarrr.mml: 121
	db	$fc,$0a,$f2,$01,$fd,$00,$20,$06	;Trk F; grrrarrr.mml: 121
	db	$fc,$03,$f2,$00,$fd,$9f,$20,$06	;Trk F; grrrarrr.mml: 121
	db	$fc,$03,$fc,$13,$f2,$01,$fd,$00	;Trk F; grrrarrr.mml: 121
	db	$20,$07,$fc,$03,$fc,$09,$f2,$00	;Trk F; grrrarrr.mml: 121
	db	$f1,$06,$f8,$00,$fd,$9f,$20,$07	;Trk F; grrrarrr.mml: 121
	db	$fc,$03,$fc,$09,$f2,$01,$fd,$00	;Trk F; grrrarrr.mml: 121
	db	$20,$07,$fc,$03,$f2,$00,$fd,$9f	;Trk F; grrrarrr.mml: 121
	db	$20,$06,$fc,$03,$fc,$13,$f2,$01	;Trk F; grrrarrr.mml: 121
	db	$fd,$00,$20,$07,$fc,$03,$fc,$09	;Trk F; grrrarrr.mml: 121
	db	$f2,$00,$f1,$06,$f8,$00,$fd,$9f	;Trk F; grrrarrr.mml: 121
	db	$20,$07,$fc,$03,$fc,$09,$f2,$01	;Trk F; grrrarrr.mml: 121
	db	$fd,$00,$20,$07,$fc,$03,$f2,$00	;Trk F; grrrarrr.mml: 121
	db	$fd,$9f,$20,$06,$fc,$03,$fc,$13	;Trk F; grrrarrr.mml: 121
	db	$f2,$01,$fd,$00,$20,$06,$fc,$03	;Trk F; grrrarrr.mml: 121
	db	$fc,$0a,$f8,$00,$fc,$39,$f2,$01	;Trk F; grrrarrr.mml: 121
	db	$fd,$00,$20,$06,$fc,$03,$fc,$0a	;Trk F; grrrarrr.mml: 118
	db	$f2,$00,$f1,$06,$f8,$00,$fd,$9f	;Trk F; grrrarrr.mml: 119
	db	$20,$06,$fc,$03,$fc,$0a,$f2,$01	;Trk F; grrrarrr.mml: 119
	db	$fd,$00,$20,$06,$fc,$03,$f2,$00	;Trk F; grrrarrr.mml: 119
	db	$fd,$9f,$20,$07,$fc,$03,$fc,$13	;Trk F; grrrarrr.mml: 119
	db	$f2,$01,$fd,$00,$20,$06,$fc,$03	;Trk F; grrrarrr.mml: 119
	db	$fc,$0a,$f2,$00,$f1,$06,$f8,$00	;Trk F; grrrarrr.mml: 119
	db	$fd,$9f,$20,$06,$fc,$03,$fc,$09	;Trk F; grrrarrr.mml: 121
	db	$f2,$01,$fd,$00,$20,$07,$fc,$03	;Trk F; grrrarrr.mml: 121
	db	$f2,$00,$fd,$9f,$20,$06,$fc,$03	;Trk F; grrrarrr.mml: 121
	db	$fc,$13,$f2,$01,$fd,$00,$20,$07	;Trk F; grrrarrr.mml: 121
	db	$fc,$03,$fc,$09,$f2,$00,$f1,$06	;Trk F; grrrarrr.mml: 121
	db	$f8,$00,$fd,$9f,$20,$07,$fc,$03	;Trk F; grrrarrr.mml: 121
	db	$fc,$09,$f2,$01,$fd,$00,$20,$07	;Trk F; grrrarrr.mml: 121
	db	$fc,$03,$f2,$00,$fd,$9f,$20,$06	;Trk F; grrrarrr.mml: 121
	db	$fc,$03,$fc,$13,$f2,$01,$fd,$00	;Trk F; grrrarrr.mml: 121
	db	$20,$07,$fc,$03,$fc,$09,$f2,$00	;Trk F; grrrarrr.mml: 121
	db	$f1,$06,$f8,$00,$fd,$9f,$20,$07	;Trk F; grrrarrr.mml: 121
	db	$fc,$03,$fc,$09,$f2,$01,$fd,$00	;Trk F; grrrarrr.mml: 121
	db	$20,$07,$fc,$03,$f2,$00,$fd,$9f	;Trk F; grrrarrr.mml: 121
	db	$20,$06,$fc,$03,$fc,$13,$f2,$01	;Trk F; grrrarrr.mml: 121
	db	$fd,$00,$20,$06,$fc,$03,$fc,$0a	;Trk F; grrrarrr.mml: 121
	db	$f2,$00,$f1,$06,$f8,$00,$fd,$9f	;Trk F; grrrarrr.mml: 121
	db	$20,$06,$fc,$03,$fc,$0a,$f2,$01	;Trk F; grrrarrr.mml: 121
	db	$fd,$00,$20,$06,$fc,$03,$f2,$00	;Trk F; grrrarrr.mml: 121
	db	$fd,$9f,$20,$07,$fc,$03,$fc,$13	;Trk F; grrrarrr.mml: 121
	db	$f2,$01,$fd,$00,$20,$06,$fc,$03	;Trk F; grrrarrr.mml: 121
	db	$fc,$0a,$f2,$00,$f1,$06,$f8,$00	;Trk F; grrrarrr.mml: 121
	db	$fd,$9f,$20,$06,$fc,$03,$fc,$0a	;Trk F; grrrarrr.mml: 121
	db	$f2,$01,$fd,$00,$20,$06,$fc,$03	;Trk F; grrrarrr.mml: 121
	db	$f2,$00,$fd,$9f,$20,$07,$fc,$03	;Trk F; grrrarrr.mml: 121
	db	$fc,$13,$f2,$01,$fd,$00,$20,$06	;Trk F; grrrarrr.mml: 121
	db	$fc,$03,$fc,$09,$f2,$00,$f1,$06	;Trk F; grrrarrr.mml: 121
	db	$f8,$00,$fd,$9f,$20,$07,$fc,$03	;Trk F; grrrarrr.mml: 121
	db	$fc,$09,$f2,$01,$fd,$00,$20,$07	;Trk F; grrrarrr.mml: 121
	db	$fc,$03,$f2,$00,$fd,$9f,$20,$06	;Trk F; grrrarrr.mml: 121
	db	$fc,$03,$fc,$13,$f2,$01,$fd,$00	;Trk F; grrrarrr.mml: 121
	db	$20,$07,$fc,$03,$fc,$09,$f2,$00	;Trk F; grrrarrr.mml: 121
	db	$f1,$06,$f8,$00,$fd,$9f,$20,$07	;Trk F; grrrarrr.mml: 140
	db	$fc,$03,$fc,$09
song_000_05_lp:
	db	$fc,$ff,$ee
	db	bank(song_000_05_lp)
	dw	song_000_05_lp

