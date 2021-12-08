;
; HUC.ASM  -  HuC Internal Library
;

; ----
; local variables

	  .bss
_vdc      .ds 20*2

          .zp
__sign
__remain  .ds 2

          .code
          .mlist

; ----
; eq
; ----
; test egality of two words
; ----
; IN :  First word on the C stack
;       Another word in A:X
; ----
; OUT : word A:X equals 0 is the two args are egals
;       else non nul
; ----
; REMARK : signed compatible
; ----

                ; old version is 75 bytes long
                ; new version is 31 bytes long (58% shorter :)

eq:
   ldy #1       ; will return false by default
   sax
   cmp [__stack]
   bne .eq_end

   sax
   cmp [__stack],Y
   bne .eq_end

   cly          ; will return true

.eq_end:
   __addmi	2,__stack

   tya          ; if Y was 1, return A=X=0 -> false
   dec A        ; if Y was 0, return A=255 -> true

   clx

   rts

; ----
; lt
; ----
; compare two words
; ----
; IN :  First word on the C stack
;       Another word in A:X
; ----
; OUT : word A:X is non nul if pushed word is strictly lower than
;       the word in A:X else nul
; ----

lt:     ; signed version
   ldy #1
   cmp #$80
   bcs lt_primary_minus

	; if here, the A:X value is positive

   sta __temp
   lda [__stack], Y
   cmp #$80
   bcs cmp_ok   ; stack value is negative, so reply OK

   lda __temp   ; stack value is also positive, so just go for the unsigned version
   jmp ult_y1

cmp_ok:
   __addmi      2,__stack
   lda #$FF
   clx
   rts
   
lt_primary_minus:

	; if here, the A:X value is negative

   sta __temp
   lda [__stack], Y
   cmp #$80
   bcs getA_ult ; stack value is also negative, so restore A val from
			; __temp and call ult

   bra cmp_false

getA_ult:
   lda __temp

ult:    ; unsigned version
   ldy #1       ; false by default

ult_y1: ; same thing but Y is assumed to be egal to 1

   cmp [__stack],Y
   bcc .lt_end ; hibyte of the reg var < hibyte of the pushed var
   beq .lt_must_test_lobyte

   cly          ; set result to true
   bra .lt_end

.lt_must_test_lobyte:
   sax
   cmp [__stack]
   bcc .lt_end       ; lobyte of the reg var < lobyte of the pushed var
   beq .lt_end
   cly               ; set result to true

.lt_end:
   __addmi      2,__stack

   tya          ; if Y was 1, return A=X=0 -> false
   dec A        ; if Y was 0, return A=255 -> true

   clx
   rts


; ----
; gt
; ----
; compare two words
; ----
; IN :  First word on the C stack
;       Another word in A:X
; ----
; OUT : word A:X is non nul if pushed word is strictly greater than
;       the word in A:X else nul
; ----

gt:     ; signed version of >
   ldy #1
   cmp #$80
   bcs .gt_primary_minus

	; if here, the A:X value is positive

   sta __temp
   lda [__stack], Y
   cmp #$80
   bcs cmp_false ; stack value is negative, so reply False

   lda __temp   ; stack value is also positive, so just go for the unsigned version
   jmp ugt_y1   ; we spare one instruction, since we already have Y=1

.gt_primary_minus:

	; if here, the A:X value is negative

   sta __temp
   lda [__stack], Y
   cmp #$80
   bcs getA_ugt ; stack value is also negative, so restore A val from
			; __temp and call ugt
   bra cmp_ok

cmp_false:
   __addmi      2,__stack
   cla
   clx
   rts

getA_ugt:       ; we grab back the value of A before entering the unsigned
		; version of >
   lda __temp

ugt:    ; unsigned version of >

   ldy #1

ugt_y1: ; unsigned version of >, assuming Y = 1

   cmp [__stack],Y
   beq .gt_must_test_lobyte
   bcs .gt_end ; hibyte of the reg var >= hibyte of the pushed var
   cly
   bra .gt_end

.gt_must_test_lobyte
   sax
   cmp [__stack]
   bcs .gt_end       ; lobyte of the reg var >= lobyte of the pushed var
   cly

.gt_end:
   __addmi      2,__stack
   tya
   dec A
   clx
   rts

; ----
; ge
; ----
; compare two signed words
; ----
; IN :  First word on the C stack
;       Another word in A:X
; ----
; OUT : word A:X is non nul if pushed word is greater or egal to
;       the word in A:X else nul
; ----

ge:     ; signed version of >
    jsr lt
    inc A   ; assuming that true is represented by A = 255
    rts

; ----
; uge
; ----
; compare two unsigned signed words
; ----
; IN :  First word on the C stack
;       Another word in A:X
; ----
; OUT : word A:X is non nul if pushed word is greater or egal to
;       the word in A:X else nul
; ----

uge:    ; unsigned version of >
    jsr ult
    inc A   ; assuming that true is represented by A = 255
    rts

; ----
; ne
; ----
; compare two words
; ----
; IN :  First word on the C stack
;       Another word in A:X
; ----
; OUT : word A:X is non nul if pushed word is diferent from
;       the word in A:X else nul
; ----
; REMARK : signed compatible
; ----

ne:
    jsr eq
    inc A   ; we're assuming that X = 0, and A = 0 if false (of course)
	    ; but A = 255 if true
    rts

; ----
; le
; ----
; compare two signed words
; ----
; IN :  First word on the C stack
;       Another word in A:X
; ----
; OUT : word A:X is non nul if pushed word is lower or egal to
;       the word in A:X else nul
; ----

le:     ; signed version
    jsr gt
    inc A       ; assuming that A=255 if true
    rts

; ----
; ule
; ----
; compare two unsigned words
; ----
; IN :  First word on the C stack
;       Another word in A:X
; ----
; OUT : word A:X is non nul if pushed word is lower or egal to
;       the word in A:X else nul
; ----

ule:    ; unsigned version
    jsr ugt
    inc A       ; assuming that A=255 if true
    rts


; ----
; asl
; ----
; shift the pushed word left by the register word
; ----
; IN :  First word on the C stack
;       Another word in A:X
; ----
; OUT : Register word egals the previous pushed value
;       shifted left by A:X
; ----
; REMARK : only the lower byte of the right operand is taken in account
;          signed compatible
; ----
asl:
   stx __temp
   __ldwp __stack
   ldy __temp
   beq .asl_end
   sta __temp
   sax

.asl_begin
   asl a
   rol __temp
   dey
   bne .asl_begin

   sax
   lda __temp
.asl_end
   __addmi 2, __stack
   rts


; ----
; asr
; ----
; shift the pushed word right by the register word
; ----
; IN :  First word on the C stack
;       Another word in A:X
; ----
; OUT : Register word egals the previous pushed value
;       shifted right by A:X
; ----
; REMARK : only the lower byte of the right operand is taken in account
;          signed compatible
; ----
asr:
   stx __temp
   __ldwp __stack
   ldy __temp
   beq .asr_end
   sta __temp
   sax

.asr_begin
   cpx #$80
   ror __temp
   ror a

   dey
   bne .asr_begin

   sax
   lda __temp
.asr_end
   __addmi 2, __stack
   rts


; ----
; smul
; ----
; multiply two SIGNED words
; ----
; IN :  First word on the C stack
;       Another word in A:X
; ----
; OUT : Register word egals the previous pushed value
;       multiplied by A:X
; ----

smul:
        stz __sign      ; until we call umul, __sign keeps the sign parity
			; of operand
	cmp #$80
        bcc smul_no_invert_primary

	__negw

	inc __sign      ; __sign ++

smul_no_invert_primary:

	sta __temp
	ldy #1
	lda [__stack],Y
	cmp #$80
        bcc smul_no_invert_secondary

	inc __sign      ; this time, no optimisation possible, IMHO :)
			; are you sure? :))
	stx __temp+1

	lda [__stack]
	tax
	lda [__stack],Y ; we assumed Y = 1 since we set it at the beginning of
                        ; smul_no_invert_primary
	__negw
	sta [__stack],Y
	sax
	sta [__stack]

	ldx __temp+1

smul_no_invert_secondary:

	lda __sign
	pha
        lda __temp      ; saved at the beginning of smul_no_invert_primary
			; where we're sure we passed

        jsr umul

	say
	pla
	and #$01
        beq smul_end

	say
	__negw
	rts

smul_end:
	say
	rts


; ----
; umul
; ----
; multiply two UNSIGNED words
; ----
; IN :  First word on the C stack
;       Another word in A:X
; ----
; OUT : Register word egals the previous pushed value
;       multiplied by A:X
; ----

umul:
	__stw	<__temp+2 ; bx
	__ldwp	__stack
	__stw	<__temp   ; ax
	  jsr	umul16
	__addmi	2, __stack
	__ldw	<__ptr
	  rts
umul16:
	  lda	<__temp+3
	  ora	<__temp+1
	  beq	umul8
	  stwz	<__ptr
	  ldy	#16

.l1:	  aslw	<__ptr
	  aslw	<__temp+2
	  bcc	.l2
	  addw	<__temp,<__ptr
.l2:	  dey
	  bne	.l1
	  rts
umul8:
	  lda	<__temp+2
	  sta	<__ptr+1
	  cla
	  ldy	#8

.l1:	  asl	A
	  rol	<__ptr+1
	  bcc	.l2
	  add	<__temp
	  bcc	.l2
	  inc	<__ptr+1
.l2:	  dey
	  bne	.l1

	  sta	<__ptr
	  rts


; ----
; sdiv
; ----
; divide two SIGNED words
; ----
; IN :  First word on the C stack
;       Another word in A:X
; ----
; OUT : Register word egals the previous pushed value
;       divided by A:X
; ----

sdiv:
	stz __sign      ; until we call udiv, __sign keeps the sign parity
			; of operand
	cmp #$80
	bcc sdiv_no_invert_primary

	__negw

	inc __sign      ; __sign ++

sdiv_no_invert_primary:

	sta __temp
	ldy #1
	lda [__stack],Y
	cmp #$80
        bcc sdiv_no_invert_secondary

	inc __sign

	stx __temp+1

	lda [__stack]
	tax
	lda [__stack],Y ; we assumed Y = 1 since we set it at the beginning of
			; sdiv_no_invert_primary
	__negw
	sta [__stack],Y
	sax
	sta [__stack]

	ldx __temp+1

sdiv_no_invert_secondary:

	lda __sign
	pha
	lda __temp      ; saved at the beginning of sdiv_no_invert_primary
			; where we're sure we passed
	jsr udiv

	say
	pla
	and #$01
	beq sdiv_end

	say
	__negw
	rts

sdiv_end:
	say
	rts


; ----
; udiv
; ----
; divide two UNSIGNED words
; ----
; IN :  First word on the C stack
;       Another word in A:X
; ----
; OUT : Register word egals the previous pushed value
;       divided by A:X
; ----

udiv:
	__stw   __ptr
	__ldwp  __stack
	__stw   __temp

	lda     #0
	sta     __remain+1
	ldy     #16
.sdiv_begin:    asl     __temp
	rol     __temp+1
	rol     a
	rol     __remain+1
	pha
	cmp     __ptr
	lda     __remain+1
	sbc     __ptr+1
	bcc     .sdiv_end
	sta     __remain+1
	pla
	sbc     __ptr
	pha
	inc     __temp
.sdiv_end:      pla
	dey
	bne     .sdiv_begin
	sta     __remain

	__addmi 2, __stack
	__ldw __temp

	rts


; ----
; smod
; ----
; give the integer remainder of the two words
; ----
; IN :  First word on the C stack
;       Another word in A:X
; ----
; OUT : Register word egals the remainder of the division of the
;       pushed value by A:X
; ----
; REMARK : signed NON compatible
; ----

smod:
umod:
        __stw   __ptr
        __ldwp  __stack
        __stw   __temp

        lda	#0
 	sta	__remain+1
 	ldy	#16
.smod_begin:	asl	__temp
	rol	__temp+1
	rol	a
	rol	__remain+1
	pha
	cmp	__ptr
	lda	__remain+1
	sbc	__ptr+1
	bcc	.smod_end
	sta	__remain+1
	pla
	sbc	__ptr
	pha
	inc	__temp
.smod_end:	pla
	dey
	bne	.smod_begin
	sta	__remain

        __addmi 2, __stack
        __ldw __remain

	rts


; ----
; ___case
; ----
; implement a switch instruction in C
; ----
; IN :  primary register (A:X) contain the discriminant value
;       i.e. the one that will be checked against those indicated in the
;       various case instructions
;       On the stack, a pointer is passed
;       This is a pointer toward an array
;       Each item of this array is a 4 bytes long structure
;       The structure is the following :
;         WORD value_to_check
;         WORD label_to_jump_to
;       We have to parse the whole array in order to compare the primary
;       register with all the 'value_to_check' field. If we ever find that
;       the primary register is egal to such a value, we must jump to the
;       corresponding 'label_to_jump_to'.
;       The default value (which also means that we reached the end of the
;       array) can be recognized with its 'label_to_jump_to' field set to 0.
;       Then the 'value_to_check' field become the default label we have to
;       use for the rest of the execution.
; ----
; OUT : The execution goes to another place
; ----
; REMARK : Also use __remain variable as a temporary value
; ----
___case:
  __stw __remain ; store the value to check to
  __ldwp __stack
  __stw __ptr ; __ptr contain the address of the array

  __addmi 2, __stack

.begin_case:
  __addmi 2, __ptr
  __ldwp __ptr
  __tstw
  __lbeq .end_case_default

  __addmi -2, __ptr

  __ldwp __ptr

  __addmi -2, __stack
  __stwp __stack

  __addmi 4, __ptr

  __ldw __remain

  jsr eq
  __tstw
  __lbeq .begin_case

  __addmi -2, __ptr
  __ldwp __ptr
  __stw __temp

  jmp [__temp]

.end_case_default:      ; if we haven't found any corresponding value
			; then we jump to the default supplied label

  __addmi -2, __ptr
  __ldwp __ptr
  __stw __temp

  jmp [__temp]


; ----
; hook
; ----
; indirect call to sub-routine
; ----
; IN :  sub-routine addr in __ptr
; ----

hook:
	jmp	[__ptr]

; ----
; setvdc
; ----
; set a vdc register
; ----
; IN : - reg index on the C stack
;      - value in A:X
; ----

setvdc:
	tay
	lda	[__sp]
	lsr	A
	; --
	cmp	#$09
	beq	.l3
	cmp	#$0A
	blo	.l1
	cmp	#$0F
	blo	.l2
	; --
.l1:	sta	<vdc_reg
	sta	video_reg
	stx	video_data_l
	sty	video_data_h
	; --
	cmp	#$02
	beq	.l2
	; --
	asl	A
	sax
	sta	_vdc,X
	tya
	sta	_vdc+1,X
.l2:	addw	#2,<__sp
	rts	
	; -- reg $09
.l3:	txa
	and	#$70
	lsr	A
	lsr	A
	lsr	A
	lsr	A
	jsr	set_bat_size
	bra	.l2

; ----
; getvdc
; ----
; get vdc register content
; ----
; IN : reg index in A:X
; ----
; OUT: vdc register in A:X
; ----

getvdc:
	cpx	#4
	beq	.l1
	; --
	sxy
	ldx	_vdc,Y
	lda	_vdc+1,Y
	rts	
	; --
.l1:	lda	#2
	sta	<vdc_reg
	sta	video_reg
	ldx	video_data_l
	lda	video_data_h
	rts

; ----
; writevram
; ----
; IN : - data on the C stack
;      - vram address in A:X
; ----

writevram:
	tay
	stz	<vdc_reg
	stz	video_reg
	lda	[__sp]
	sta	video_data_l
	incw	<__sp
	lda	[__sp]
	sta	video_data_h
	incw	<__sp
	vreg	#2
	stx	video_data_l
	sty	video_data_h
	rts

; ----
; readvram
; ----
; IN : vram address in A:X
; ----
; OUT: data in A:X
; ----

readvram:
	ldy	#1
	sty	<vdc_reg
	sty	video_reg
	stx	video_data_l
	sta	video_data_h
	vreg	#$02
	ldx	video_data_l
	lda	video_data_h
	rts

