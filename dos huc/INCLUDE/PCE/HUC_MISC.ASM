;
; HUC_MISC.ASM  -  HuC Misc Library
;


; joy(char number)
; ----

_joy:
	  sxy
	  ldx	joy,Y
	  cla
	  rts

; joytrg(char number)
; ----

_joytrg:
	  sxy
	  ldx	joytrg,Y
	  cla
	  rts

; set_joy_callback(char num [dl], char mask [al], char keys [ah], int proc [bl:si])
; ----

_set_joy_callback.4:
	  stz	joycallback
	  lda	<_bl
	  sta	joycallback+3
	__ldw	<_si
	__stw	joycallback+4
	  ora   <_si
	  beq   .l1
	  lda	<_ah
	  sta	joycallback+2
	  lda	<_al
	  sta	joycallback+1
	  lda	#$80
	  sta	joycallback
.l1:	  rts

; get_joy_events(char num, int rst)
; ----
; return all the collected joypad events
; ----

_get_joy_events.2:
	  ldy   <_al
	  cpx	#0
	  bne	_get_joy_events.sub
	  ldx	joybuf,Y
	  cla
	  rts
_get_joy_events.1:
	  sxy
_get_joy_events.sub:
	  ldx	joybuf,Y
	  cla
	  sta	joybuf,Y
	  rts

; clear_joy_events(char mask)
; ----

_clear_joy_events:
	  stx	<_al
	  cly
	  sei
.l1:	  lsr	<_al
	  bcc	.l2
	  cla
	  sta	joybuf,Y
	  sta	joytrg,Y
	  lda	#$FF
	  sta	joyold,Y
.l2:	  iny
	  cpy	#5
	  blo	.l1
	  cli
	  rts

; poke(int offset, char val)
; ----

_poke:
	  lda	[__sp]
	  sta	<__ptr
	  ldy	#1
	  lda	[__sp],Y
	  sta	<__ptr+1
	  txa
	  sta	[__ptr]
	  addw  #2,<__sp
	  rts

; peek(int offset)
; ----

_peek:
	__stw	<__ptr
	  lda	[__ptr]
	  tax
	  cla
	  rts

; farpeekb(far void *base)
; ----

_farpeekb.1:
	  lda	<__fbank
	  tam	#3
	  lda	<__fptr+1
	  and	#$1F
	  ora	#$60
	  sta	<__fptr+1
	  lda	[__fptr]
	  tax
	  cla
	  rts

; farpeekw(far void *base)
; ----

_farpeekw.1:
	  lda	<__fbank
	  tam	#3
	  lda	<__fptr+1
	  and	#$1F
	  ora	#$60
	  sta	<__fptr+1
	  bra	_farpeekw.sub
_farpeekw.fast:
	  tam	#3
	  txa
	  and	#$1F
	  ora	#$60
	  sta	<__fptr+1
_farpeekw.sub:
	  lda	[__fptr]
	  tax
	  inc	<__fptr
	  bcc	.l1
	  inc	<__fptr+1
	  bpl	.l1
	  lda	#$60
	  sta	<__fptr+1
.l1:
	  lda	[__fptr]
	  rts

; farmemget(void *dst, far void *base, int len)
; ----

_farmemget.3:

	__stw	<_cx
	  lda	<__fbank
	  tam	#3

    ; ----
    ; split transfer if needed
    ;
	  ; -- clip length (max. 8KB)
	  cmpw	#$2000,<_cx
	  blo	.t1
	  stw	#$2000,<_cx
	  ; -- check length
.t1:	  lda	<__fptr
	  add	<_cl
	  sta	<_al
	  lda	<__fptr+1
	  and	#$1F
	  adc	<_ch
	  sta	<_ah
	  cmp	#$20
	  blo	.t2
	  ; -- calculate second-half size
	  and	#$1F
	  sta	<_dh
	  lda	<_al
	  sta	<_dl
	  subw	<_dx,<_cx
	  ; -- remap src ptr
.t2:	  lda	<__fptr+1
	  and	#$1F
	  ora	#$60
	  sta	<__fptr+1

    ; ----
    ; copy a block
    ;
	  clx
	  cly
	  dec	<_ch
	  bmi	.l4
	  ; -- main loop
.l1:	  lda	[__fptr],Y
	  sta	[_bx],Y
	  iny
	  dex
	  bne	.l1
	  ; -- inc dst ptr
	  cpy	#0
	  beq	.l2
	  tya
	  add	<_bl
	  sta	<_bl
	  bcc	.l3
.l2:	  inc	<_bh
	  ; -- inc src ptr
.l3:	  inc	<__fptr+1
	  ; -- next chunk
	  dec	<_ch
	  bpl	.l1
.l4:	  ldx	<_cl
	  stz	<_cl
	  bne	.l1

    ; ----
    ; second half
    ;
	  tstw	<_dx
	  beq	.l5
	  ; -- reload dst and cnt
	  stw	<_dx,<_cx
	  stw	#$6000,<__fptr
	  ; -- inc bank
	  tma	#3
	  inc	A
	  tam	#3
	  bra	.l1

    ; ----
    ; exit
    ;
.l5:	  rts

; rand()
; ----

_rand:
        jsr rand
      __ldw _cx
        rts

