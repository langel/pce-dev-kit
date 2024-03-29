;
; Hu-C internal include file
;


; variables
; ----

           .zp
__sp
__stack    .ds 2
__arg_idx  .ds 1
__temp     .ds 4
__ptr      .ds 2
__fbank    .ds 1
__fptr     .ds 2


; macros
; ----

	.macro __farptr
	 ldy	#bank(\1)
	 sty	\2
	 ldy	#low(\1)
	 sty	\3
	 ldy	#high(\1)
	 sty	\3+1
	.endm

	.macro __farptr_i
	 sax
	 add	#low(\1)
	.if (\# = 3)
	 sta	<\3
	.else
	 sta	<__fptr
	.endif
	 sax
	 adc	#high(\1) & $1F
	.if (\# = 3)
	 sta	<\3+1
	.else
	 tax
	.endif
	 rol	A
	 rol	A
	 rol	A
	 rol	A
	 and	#$F
	 add	#bank(\1)
	.if (\# = 3)
	 sta	<\2
	.endif
	.endm

	.macro __farptr_get
	 stx	<\1
	 ldy	#2
	 lda	[__ptr],Y
	 sta	<\2
	 iny
	 lda	[__ptr],Y
	 sta	<\2+1
	.endm

	.macro __fgetb
	 tam	#3
	 txa
	 and	#$1F
	 ora	#$60
	 sta	<__fptr+1
	 lda	[__fptr]
	 tax
	 clx
	.endm

__ldb	.macro
	.if (\# = 2)
	 clx
	 lda	\1
	 clc
	 adc	#low(\2)
	 sax
	 adc	#high(\2)
	.else
	 ldx	\1
       __extw
       	.endif
	.endm

__ldbp	.macro
	 lda	[\1]
	 tax
       __extw
	.endm

__stbps	.macro
       __stw	<__temp
       __ldwp	 __stack
       __stw	<__ptr
       __ldw	<__temp
	 sax
	 sta	[__ptr]
	 sax
       __addmi	2,__stack
	.endm

__ldw	.macro
	.if (\# = 2)
	 lda	\1
	 clc
	 adc	#low(\2)
	 tax
	 lda	\1+1
	 adc	#high(\2)
	.else
	 ldx	\1
	 lda	\1+1
	.endif
	.endm

__ldwp	.macro
	 lda	[\1]
	 tax
	 ldy	#1
	 lda	[\1],Y
	.endm

__ldwi	.macro
	 ldx	#low(\1)
	 lda	#high(\1)
	.endm

__stw	.macro
	 stx	\1
	 sta	\1+1
	.endm

__stwp	.macro
	 sax
	 sta	[\1]
	 sax
	 ldy	#1
	 sta	[\1],Y
	.endm

__stwps	.macro
       __stw	<__temp
       __ldwp	 __stack
       __stw	<__ptr
       __ldw	<__temp
       __stwp	 __ptr
       __addmi	2,__stack
	.endm

__pushw	.macro
       __submi	2,__stack
         sax
	 sta	[__stack]
	 sax
	 ldy	#1
	 sta	[__stack],Y
	.endm

__popw	.macro
	 lda	[__stack]
	 tax
	 ldy	#1
	 lda	[__stack],Y
       __addmi	2,__stack
	.endm

__calls	.macro
	 pha
	 ldy	#\1
	 lda	[__stack],Y
	 sta	<__ptr
	 incw	<__stack
	 lda	[__stack],Y
	 sta	<__ptr+1
	 incw	<__stack
	 pla
	 jsr	hook
	.endm

__swapw	.macro
	 pha
	 ldy	#1
	 lda	[__stack],Y
	 sta	<__temp
	 lda	[__stack]
	 sax
	 sta	[__stack]
	 pla
	 sta	[__stack],Y
	 lda	<__temp
	.endm


; TODO : check if we need pha/pla or not
__tstw	.macro
         ; pha
	 stx	<__temp
	 ora	<__temp
	 ; pla
	.endm

__aslw	.macro
	 sax
	 asl	A
	 sax
	 rol	A
	.endm

__aslws	.macro
	 asl	[__stack]
	 ldy	#1
	 rol	[__stack],Y
	.endm

__asrw	.macro
	 cmp	#$80
	 ror	A
	 sax
	 ror	A
	 sax
	.endm

__extw	.macro
;	 txa	; signed
;	 cla
;	 bpl	.x_\@
;	 dec	A
;.x_\@:
	 cla	; unsigned
	.endm

__comw	.macro
	 sax
	 eor	#$FF
	 sax
	 eor	#$FF
	.endm

__negw	.macro
	 sax
	 eor	#$FF
	 clc
	 adc	#1
	 sax
	 eor	#$FF
	 adc	#0
	.endm

__boolw	.macro
	 stx	<__temp
	 ora	<__temp
	 clx
	 beq	.x\@
	 inx
.x\@	 cla
	.endm

__notw	.macro
	 stx	<__temp
	 ora	<__temp
	 clx
	 bne	.x\@
	 inx
.x\@	 cla
	.endm

__addw	.macro
	 clc
	 sax
	 adc	\1
	 sax
	 adc	\1+1
	.endm	

__addwi	.macro
	 clc
	 sax
	 adc	#low(\1)
	 sax
	 adc	#high(\1)
	.endm	

__addmi	.macro
	 pha
	 clc
	 lda	<\2
	 adc	#low(\1)
	 sta	<\2
	 lda	<\2+1
	 adc	#high(\1)
	 sta	<\2+1
	 pla
	.endm	

__subwi	.macro
	 sec
	 sax
	 sbc	#low(\1)
	 sax
	 sbc	#high(\1)
	.endm	

__submi	.macro
	 pha
	 sec
	 lda	<\2
	 sbc	#low(\1)
	 sta	<\2
	 lda	<\2+1
	 sbc	#high(\1)
	 sta	<\2+1
	 pla
	.endm	

__addws	.macro
	 sax
	 clc
	 adc	[__stack]
	 sax
	 ldy	#1
	 adc	[__stack],Y
       __addmi 2, __stack
	.endm

__subws	.macro
	stx	<__temp
	sta	<__temp+1
	sec
	lda	[__stack]
	sbc	<__temp
	tax
	ldy	#1
	lda	[__stack],Y
	sbc	<__temp+1
	__addmi	2, __stack
	.endm

__orws	.macro
	 sax
	 ora	[__stack]
	 sax
	 ldy	#1
	 ora	[__stack],Y
       __addmi	2,__stack
	.endm

__andws	.macro
	 sax
	 and	[__stack]
	 sax
	 ldy	#1
	 and	[__stack],Y
       __addmi	2,__stack
	.endm

__eorws	.macro
	 sax
	 eor	[__stack]
	 sax
	 ldy	#1
	 eor	[__stack],Y
       __addmi	2,__stack
	.endm

__lbra	.macro
	 jmp	\1
	.endm

__lbeq	.macro
	 bne	.x\@
	 jmp	\1
.x\@
	.endm

__lbne	.macro
	 beq	.x\@
	 jmp	\1
.x\@
	.endm

__call	.macro
	 call   \1
	.endm

_set_bgpal .macro
	 set_bgpal \1,\2,\3
	.endm

_set_sprpal .macro
	 set_sprpal \1,\2,\3
	.endm

_load_background .macro
	 vload $1000,\1,#$4000
	 vsync
	 set_bgpal #0, \2,#16
	 batcpy #$0, \3, \4, \5
	.endm

