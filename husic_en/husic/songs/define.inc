TOTAL_SONGS	equ	$01
SOUND_GENERATOR	equ	$00
PTRDPCM		equ	 4
PTRFDS		equ	 5
PTRVRC7		equ	 5
PTRVRC6		equ	 5
PTRN106		equ	 5
PTRFME7		equ	 5
PTRMMC5		equ	 5
PTR_TRACK_END		equ	 5
PITCH_CORRECTION		equ	 0
DPCM_RESTSTOP		equ	 0
DPCM_BANKSWITCH		equ	 0
DPCM_EXTRA_BANK_START		equ	 1
BANK_MAX_IN_4KB		equ	(0 + 0)*2+1
ALLOW_BANK_SWITCH		equ	1
BANKSWITCH_INIT_MACRO	.macro
	db	0,1,0,0,0,0,0,0
	.endm
TITLE	.macro
	db	$54, $55, $52, $42, $4f, $41, $53, $53
	db	$00, $00, $00, $00, $00, $00, $00, $00
	db	$00, $00, $00, $00, $00, $00, $00, $00
	db	$00, $00, $00, $00, $00, $00, $00, $00
	.endm
COMPOSER	.macro
	db	$42, $2d, $4b, $4e, $4f, $58, $00, $00
	db	$00, $00, $00, $00, $00, $00, $00, $00
	db	$00, $00, $00, $00, $00, $00, $00, $00
	db	$00, $00, $00, $00, $00, $00, $00, $00
	.endm
MAKER	.macro
	db	$4d, $61, $6b, $65, $72, $00, $00, $00
	db	$00, $00, $00, $00, $00, $00, $00, $00
	db	$00, $00, $00, $00, $00, $00, $00, $00
	db	$00, $00, $00, $00, $00, $00, $00, $00
	.endm


