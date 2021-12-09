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
	sei      
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

	; enable background and sprites
	lda #$05   ; select the control register
	sta $0000
	lda #$c8   ; enable bits 3, 6 and 7
	sta $0002
	lda #$00
	sta $0003

	; setup hblank interrupt at scanline 4
	lda #$06   ; select the RCR register
	sta $0000
	; first scanline is #$40 or #64
	lda #$40
	sta $0002  ; write lo byte
	lda #$01
	sta $0003  ; write hi byte

	; enable interrupts
	cli

	ldy #$00

loop:

	jmp loop                    ;do our infinite wait loop


irq1:
	sei
	lda $0000
	inc zp_test + 10
	inc $2020
	lda #$00
	sta $0402
	sta $0403
	iny
	tya 
	;and #$03
	sta $0404
	sta $0405
	sta zp_test
	sta $2000
	sta $2004
	inc $2022
	sta $2200
	sta $2222
	sta $2333
	sta $3000
	sta $3ffe
	sta $3fff
	cli
	rti

	.include "windows huc\include\pce\font.inc"

	; we are still inside bank $00
	; IRQ1 VDC interrupt vector
	.org $fff8
	.dw irq1
	; program reset vector
	.org $fffe     
	.dw start_up
      
;#end
