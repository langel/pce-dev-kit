    ;#listing2.asm
    ;------------

timerport    .equ $0C00
timer_cnt    .equ timerport
timer_ctrl   .equ timerport+1        

	.zp
saw_counter: .ds 1
	.org $010
fine_tune: .ds 1
	.bss
 	.org $2680
vsync_cnt:	.ds 1	; counter for 'wait_vsync' routine 
    
	.code
	.bank $00
	.org $e000

start_up:
	; disable interrupts
	sei      
	; select the 7.16 MHz clock
	csh
	; clear decimal flag
	cld
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

	; clear all of RAM
	; set 1st byte of ram to desired default value
	lda #$00
	sta $2000
	; propogate 1st byte value to all of ram
	tii $2000, $2001, $1fff

	; reset timer?
	stz timer_ctrl
	; set timer
	lda #$00
	sta timer_cnt
	lda #$01
	sta timer_ctrl

	; init VDC
	lda #$05  ; CR
	sta $0000
	lda #$00
	sta $0002
	sta $0003
	lda #$06  ; RCR
	sta $0000
	lda #$00
	sta $0002
	sta $0003
	lda #$07  ; BXR
	sta $0000
	lda #$00
	sta $0002
	sta $0003
	lda #$08  ; BYR
	sta $0000
	lda #$00
	sta $0002
	sta $0003
	lda #$09  ; MWR
	sta $0000
	lda #$00  ; bits 4-6 set bg virtual size
	sta $0002
	lda #$00
	sta $0003
	lda #$0a  ; HSR
	sta $0000
	lda #$02
	sta $0002
	lda #$02
	sta $0003
	lda #$0b  ; HDR
	sta $0000
	lda #$1f
	sta $0002
	lda #$04
	sta $0003
	lda #$0c  ; VPR (video sync register)
	sta $0000
	lda #$02
	sta $0002
	lda #$10
	sta $0003
	lda #$0d  ; VDW
	sta $0000
	lda #$e7
	sta $0002
	lda #$00
	sta $0003
	lda #$0e  ; VCR
	sta $0000
	lda #$0c
	sta $0002
	lda #$00
	sta $0003
	lda #$0f  ; DCR
	sta $0000
	lda #$10
	sta $0002
	lda #$00
	sta $0003
	lda #$13  ; SATB
	sta $0000
	lda #$00
	sta $0002
	lda #$7f
	sta $0003



	; enable background and sprites
	lda #$05   ; select the control register
	sta $0000
	lda #$cc   ; enable bits 3, 4, 6 and 7
	sta $0002
	lda #$00
	sta $0003

	; setup hblank interrupt at scanline 4
	lda #$06   ; select the RCR register
	sta $0000
	; first scanline is #$40 or #64
	lda #$80
	sta $0002  ; write lo byte
	lda #$00
	sta $0003  ; write hi byte


	; fill palette data
	ldy #$00
	lda #$00
	sta $0402
	sta $0403
.palfill:
	tya
	sta $0404
	lda #$00
	sta $0405
	iny
	bne .palfill
.palfill2:
	tya
	sta $0404
	lda #$01
	sta $0405
	iny
	bne .palfill2


	; fill VRAM Bg Attribute Table
	lda #$00
	sta $0000
	sta $0002
	sta $0003
	lda #$02
	sta $0000
	ldy #$00
.batfill:
	lda #$10
	tya
	lsr A
	lsr A
	lsr A
	sta $0002
	;lda #$00
	tya
	asl A
	asl A
	asl A
	asl A
	sta $0003
	iny
	bne .batfill
.batfill2:
	lda #$10
	tya
	lsr A
	lsr A
	sta $0002
	;lda #$00
	tya
	asl A
	asl A
	asl A
	asl A
	sta $0003
	iny
	bne .batfill2
	
	; write to tile $10
	lda #$00
	sta $0000
	sta $0002
	lda #$10
	sta $0003
	lda #$02
	sta $0000
	ldy #$00
.tilefill:
	tya
	sta $0002
	lda #$00
	sta $0003
	iny
	bne .tilefill
	ldy #$00
.tilefill2:
	tya
	sta $0002
	lda #$00
	sta $0003
	iny
	bne .tilefill2
.tilefill3:
	tya
	sta $0002
	lda #$00
	sta $0003
	iny
	bne .tilefill3
.tilefill4:
	tya
	sta $0002
	lda #$00
	sta $0003
	iny
	bne .tilefill4

	; enable interrupts
	cli



; INIT PSG
init_psg:
	lda #$ff  ; global volume full
	sta $0801

; SQAURE WAVE channel 0 (wavetable)
	lda #$00  ; select channel 0
	sta $0800
	lda #$4e  ; fine tune
	sta $0802
	sta fine_tune
	lda #$05  ; coarse tune
	sta $0803
	lda #$40  ; reset wavetable position
	sta $0804
	lda #$00  ; turn off to enable wave write
	sta $0804
	ldy #$00  ; write wave table loop
.loading_square:
	lda square,y
	sta $0806
	iny
	cpy #$20
	bne .loading_square
	lda #$ff  ; set L/R volume full
	sta $0805 
	lda #$9f  ; enable channel and full volume
	sta $0804
; TURN OFF channel 0
; so we can hear channel 5
	lda #$00
	sta $0804

; SAW WAVE channel 5 (pcm / DDA)
	lda #$05
	sta $0800
	lda #$40
	sta $0804
	lda #$00
	sta $0804
	;sta $0804
	lda #$00
	sta $0802
	sta $0803
	lda #$ff  ; set L/R volume full
	sta $0805 
	lda %11011111 ; set Channel and DDA to on / Volume full
	sta $0804

	lda #$03
	sta $0800
	lda #$00
	sta $0802
	sta $0803
	sta $0806
	lda %11000000 ; set Channel and DDA to on / Volume full
	sta $0804
	lda #$ff  ; set L/R volume full
	sta $0805 


	lda #$04
	sta $0800
	lda #$ff  ; set L/R volume full
	sta $0805 
	lda #$00
	sta $0804
	lda %11011111 ; set Channel and DDA to on / Volume full
	sta $0804


loop:
	jmp loop                    ;do our infinite wait loop



timer_saw:
	pha
	phx
	phy
	stz $1403 ; reset timer
	;lda $0000 ; get saw delta position
	lda #$05 ; use channel 5
	sta $0800
	inc saw_counter
	lda saw_counter
	sta $0806 ; stash into DDA
	lda #$01
	sta timer_ctrl ; reset timer?
	ply
	plx
	pla
	rti


irq1:
	pha
	phx
	phy
	; READ THE STATUS REGISTER TO
	; RESET THE VDC IRQ FLAG
	lda $0000
	; increment fine tune
	lda #$00 ; use channel 0
	sta $0800
	inc fine_tune
	lda fine_tune
	sta $0802
	; check loop counter position
	inc $2020
	lda $2020
	cmp #$08
	bne .cleanup
	; rotate bg color
	lda #$00
	sta $0402
	sta $0403
	inc $2021
	lda $2021
	sta $0404
	; reset loop
	lda #$00
	sta $2020
.cleanup:
	ply
	plx
	pla
	rti

interrupt_rti:
	rti

square:
	.db $1b,$1d,$1e,$1e,$1f,$1f,$1f,$1f,$1f,$1f,$1f,$1f,$1e,$1e,$1d,$1b,$04,$02,$01
	.db $01,$00,$00,$00,$00,$00,$00,$00,$00,$01,$01,$02,$04

	.include "windows huc\include\pce\font.inc"

	; we are still inside bank $00
	; IRQ1 VDC interrupt vector
;	.org $fff8
;	.dw irq1
	.org $fff6
	.dw interrupt_rti
	.dw irq1
	.dw timer_saw
	.dw interrupt_rti
	.dw interrupt_rti
	; program reset vector
	.org $fffe     
	.dw start_up
      
;#end
