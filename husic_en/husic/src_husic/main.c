/* HuSIC simple loader 
  Please see license in the package to use this code 
  
  History : 
  2004-03-04 : created by BouKiCHi
  2005-01-19 : rewritten by BouKiCHi
  2007-04-11 : rewritten by BouKiCHi
*/

#asm

  .data
  .bank CONST_BANK
  .org $4400

 _sound_dat:
	dw	sound_data_table	; 0
	dw	loop_point_table	; 1
	dw	softenve_table		; 2
	dw	softenve_lp_table	; 3
	dw	pitchenve_table		; 4
	dw	pitchenve_lp_table	; 5
	dw	lfo_data		    ; 6
	dw	sound_data_bank		; 7
	dw	loop_point_bank		; 8
	dw	arpeggio_table		; 9
	dw	arpeggio_lp_table	; 10

_pcewav:
	dw	pce_data_table

_xpcmdata
	dw	xpcm_data
	
;	.include "songdata.h"
	.bank CONST_BANK
	.include "effect.h"


;------------------------------
; PCM timer routines
	.code
	.bank START_BANK

_timer_pcm
	pha
	phx
	phy


	lda	<__temp
	sta	<__tmr_tmp
	lda	<__temp+1
	sta	<__tmr_tmp+1

;	lda	<__temp+2
;	sta	<__tmr_tmp+2
;	lda	<__temp+3
;	sta	<__tmr_tmp+3

	lda	<__ptr
	sta	<__tmr_ptr
	lda	<__ptr+1
	sta	<__tmr_ptr+1

	lda	<_bx
	sta	<__tmr_bx
	lda	<_bx+1
	sta	<__tmr_bx+1


	tma	#page(_pcm_intr)
	pha
	map	_pcm_intr
	jsr	_pcm_intr
	pla
	tam	#page(_pcm_intr)

	lda	<__tmr_tmp
	sta	<__temp
	lda	<__tmr_tmp+1
	sta	<__temp+1

;	lda	<__tmr_tmp+2
;	sta	<__temp+2
;	lda	<__tmr_tmp+3
;	sta	<__temp+3


	lda	<__tmr_ptr
	sta	<__ptr
	lda	<__tmr_ptr+1
	sta	<__ptr+1

	lda	<__tmr_bx
	sta	<_bx
	lda	<__tmr_bx+1
	sta	<_bx+1

	sta   irq_status
	cli

	ply
	plx
	pla


	rti


_vsync_drv
	lda	<__temp
	sta	<__vs_tmp
	lda	<__temp+1
	sta	<__vs_tmp+1

	lda	<__ptr
	sta	<__vs_ptr
	lda	<__ptr+1
	sta	<__vs_ptr+1

	lda	<_bx
	sta	<__vs_bx
	lda	<_bx+1
	sta	<__vs_bx+1


	tma	#page(_drv_intr)
	pha
	map	_drv_intr
	jsr	_drv_intr
	pla
	tam	#page(_drv_intr)

	lda	<__vs_tmp
	sta	<__temp
	lda	<__vs_tmp+1
	sta	<__temp+1

	lda	<__vs_ptr
	sta	<__ptr
	lda	<__vs_ptr+1
	sta	<__ptr+1

	lda	<__vs_bx
	sta	<_bx
	lda	<__vs_bx+1
	sta	<_bx+1

	rts

           .zp
__tmr_tmp   .ds 8
__tmr_ptr   .ds 2
__tmr_bx    .ds 2
__vs_tmp   .ds 2
__vs_ptr   .ds 2
__vs_bx    .ds 2


	; restore segment and bank
	.code
	.bank START_BANK

#endasm

/*  HuC's standard header */
#include "huc.h"
 /* HuSIC's core( main code ) */
#include "hus.c"

main()
{
	int count,x;

	count = 0;

	disp_off(); cls();

	/*  initalizes font fg color */
	for(x=1; x < 15; x++) 
		set_color(x,511);

	load_default_font();
	disp_on();

	put_string("INITIALIZES HuSIC DRIVER",5,5);
	drv_init();
	put_string("OK",5,6);

	while(1) 
	{
		vsync();
	}

}



