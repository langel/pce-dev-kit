    ;#listing2.asm
    ;------------

	.zp
	.org $010
zp_test: .ds 1
	.bss
 	.org $2680
vsync_cnt:	.ds 1	; counter for 'wait_vsync' routine 
    
	.code
	.bank $00
	.org $e000

start_up:
	; disable interrupts
	sei                         ;disable interrupts
	; initialize SP to $ff
	lda #$ff
	txs
	; map hardware bank to MPR0
	; $0000 - $1fff
	lda #$ff 
	tam #$00
	; map ram bank to MPR1
	; $2000 - $3fff
	lda #$f8     
	tam #$01
	; set 1st byte of ram to desired default value
	lda #$00
	sta $2000
	; propogate 1st byte value to all of ram
	tii $2000, $2001, $1fff

	ldy #$00

loop:
	iny
	lda #$00
	sta $0402
	tya 
	;and #$03
	sta $0404
	sta $0404
	sta zp_test
	sta $2000
	sta $2004
	sta $2200
	sta $2222
	sta $2333
	sta $3000
	sta $3ffe
	sta $3fff

	jmp loop                    ;do our infinite wait loop

	.include "INCLUDE\PCE\FONT.INC"

	; we are still inside bank $00
	; skip to end of 8k segment/bank
	.org $fffe     
	; setup the reset vector to our start_up label position
	.dw start_up
      
;#end
