dutyenve_table:
dutyenve_lp_table:


softenve_table:
	dw	softenve_000
	dw	softenve_001
	dw	softenve_002
	dw	softenve_003
	dw	softenve_004
	dw	softenve_005
softenve_lp_table:
	dw	softenve_lp_000
	dw	softenve_lp_001
	dw	softenve_lp_002
	dw	softenve_lp_003
	dw	softenve_lp_004
	dw	softenve_lp_005

softenve_000:
	db	$11,$08,$05,$03,$02
softenve_lp_000:
	db	$00,$ff
softenve_001:
	db	$19,$14,$13,$12,$11,$0f,$0c,$07
	db	$05,$03,$02,$01
softenve_lp_001:
	db	$00,$ff
softenve_002:
	db	$13,$16,$07,$11,$12,$04,$06,$02
	db	$01
softenve_lp_002:
	db	$00,$ff
softenve_003:
	db	$0c,$15,$1e,$1b,$1a
softenve_lp_003:
	db	$17,$ff
softenve_004:
	db	$00,$00,$01,$01,$01,$01,$01,$02
	db	$02,$02,$02,$02,$03,$03,$03,$04
	db	$04,$04,$04,$05,$05,$05,$05,$06
	db	$06,$07,$07,$07,$07,$07,$08,$08
	db	$08,$09,$09,$09,$09,$0a,$0a,$0a
softenve_lp_004:
	db	$0b,$ff
softenve_005:
	db	$1e,$1a,$17,$16,$15,$14,$13,$12
	db	$10,$0f,$0e,$0d,$0c
softenve_lp_005:
	db	$0b,$ff

pitchenve_table:
	dw	pitchenve_000
	dw	pitchenve_001
	dw	pitchenve_002
pitchenve_lp_table:
	dw	pitchenve_lp_000
	dw	pitchenve_lp_001
	dw	pitchenve_lp_002

pitchenve_000:
pitchenve_lp_000:
	db	$00,$ff
pitchenve_001:
pitchenve_lp_001:
	db	$7f,$ff
pitchenve_002:
pitchenve_lp_002:
	db	$01,$ff

arpeggio_table:
arpeggio_lp_table:


lfo_data:
fds_data_table:
fds_effect_select:
fds_4088_data:


n106_channel:
	db	0
n106_wave_init:
n106_wave_table:


vrc7_data_table:


dpcm_data:

; begin DPCM samples

; end DPCM samples


pce_data_table:
	dw	0
	dw	0
	dw	pce_002

pce_002:
	db	$00,$02,$04,$05,$08,$0a,$0c,$0e
	db	$10,$12,$13,$15,$16,$18,$1b,$1d
	db	$1f,$1c,$1a,$18,$16,$14,$12,$10
	db	$0f,$0d,$0b,$09,$07,$06,$04,$02


xpcm_data:


	.include	"turboass.h"
