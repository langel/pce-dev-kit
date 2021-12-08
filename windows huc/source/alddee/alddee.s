; Small C HuC6280 (v0.2, 08/Nov/97)
;
; Taken to HuC (22/Feb/00)
;
;
; This file generated by HuC (v3.21, 2005/04/09, Denki release)
; on Sun Jan 29 22:05:59 2012
;

HUC	= 1

	.include "startup.asm"
	.data
	.bank DATA_BANK

	.code

	.proc _initialize
	load_sprites	#28672,_playerframe0,#1
	load_sprites	#28928,_playerframe1,#1
	load_sprites	#29184,_peg,#1
	load_sprites	#29440,_spiky,#1
	load_sprites	#29696,_playerattackingframe,#1
	load_sprites	#29952,_weapon,#1
	  call	_init_satb
	_load_background	_special_bg,_special_pal,_special_bat,#32,#28
	__ldwi	1
	  ldy	#1
	  call	_vsync
	_set_sprpal	#0,_playerframe0_pal,#1
	_set_sprpal	#1,_playerframe1_pal,#1
	_set_sprpal	#2,_peg_colors,#1
	_set_sprpal	#3,_special_pal,#1
	_set_sprpal	#4,_spiky_pal,#1
	_set_sprpal	#5,_weapon_pal,#1
	__ldwi	_spikyX
	__pushw
	__ldwi	20
	__negw
	__stwps
	__ldwi	_spikyX
	__addwi	2
	__pushw
	__ldwi	20
	__negw
	__pushw
	__ldwi	2
	  jsr	smul
	__pushw
	__ldwi	3
	  jsr	sdiv
	__stwps
	__ldwi	_spikyX
	__addwi	4
	__pushw
	__ldwi	0
	__stwps
	__ldwi	_spikyX
	__addwi	6
	__pushw
	__ldwi	20
	__pushw
	__ldwi	2
	  jsr	smul
	__pushw
	__ldwi	3
	  jsr	sdiv
	__stwps
	__ldwi	_spikyX
	__addwi	8
	__pushw
	__ldwi	20
	__stwps
	__ldwi	_spikyX
	__addwi	10
	__pushw
	__ldwi	20
	__pushw
	__ldwi	2
	  jsr	smul
	__pushw
	__ldwi	3
	  jsr	sdiv
	__stwps
	__ldwi	_spikyX
	__addwi	12
	__pushw
	__ldwi	0
	__stwps
	__ldwi	_spikyX
	__addwi	14
	__pushw
	__ldwi	20
	__negw
	__pushw
	__ldwi	2
	  jsr	smul
	__pushw
	__ldwi	3
	  jsr	sdiv
	__stwps
	__ldwi	_spikyY
	__pushw
	__ldwi	0
	__stwps
	__ldwi	_spikyY
	__addwi	2
	__pushw
	__ldwi	20
	__negw
	__pushw
	__ldwi	2
	  jsr	smul
	__pushw
	__ldwi	3
	  jsr	sdiv
	__stwps
	__ldwi	_spikyY
	__addwi	4
	__pushw
	__ldwi	20
	__negw
	__stwps
	__ldwi	_spikyY
	__addwi	6
	__pushw
	__ldwi	20
	__negw
	__pushw
	__ldwi	2
	  jsr	smul
	__pushw
	__ldwi	3
	  jsr	sdiv
	__stwps
	__ldwi	_spikyY
	__addwi	8
	__pushw
	__ldwi	0
	__stwps
	__ldwi	_spikyY
	__addwi	10
	__pushw
	__ldwi	20
	__pushw
	__ldwi	2
	  jsr	smul
	__pushw
	__ldwi	3
	  jsr	sdiv
	__stwps
	__ldwi	_spikyY
	__addwi	12
	__pushw
	__ldwi	20
	__stwps
	__ldwi	_spikyY
	__addwi	14
	__pushw
	__ldwi	20
	__pushw
	__ldwi	2
	  jsr	smul
	__pushw
	__ldwi	3
	  jsr	sdiv
	__stwps
	__ldwi	2
	  call	_spr_set
	__ldwi	135
	  call	_spr_x
	__ldwi	65
	  call	_spr_y
	__ldwi	29184
	  call	_spr_pattern
	__ldwi	185
	  stx	_al
	__ldwi	0
	  call	_spr_ctrl.2
	__ldwi	2
	  call	_spr_pal
	__ldwi	1
	  call	_spr_pri
	__ldwi	3
	  call	_spr_set
	__ldwi	135
	  call	_spr_x
	__ldwi	105
	  call	_spr_y
	__ldwi	29184
	  call	_spr_pattern
	__ldwi	185
	  stx	_al
	__ldwi	0
	  call	_spr_ctrl.2
	__ldwi	2
	  call	_spr_pal
	__ldwi	1
	  call	_spr_pri
	__ldwi	4
	  call	_spr_set
	__ldwi	135
	  call	_spr_x
	__ldwi	145
	  call	_spr_y
	__ldwi	29184
	  call	_spr_pattern
	__ldwi	185
	  stx	_al
	__ldwi	0
	  call	_spr_ctrl.2
	__ldwi	2
	  call	_spr_pal
	__ldwi	1
	  call	_spr_pri
	__ldwi	5
	  call	_spr_set
	__ldwi	140
	  call	_spr_x
	__ldwi	145
	  call	_spr_y
	__ldwi	29440
	  call	_spr_pattern
	__ldwi	185
	  stx	_al
	__ldwi	17
	  call	_spr_ctrl.2
	__ldwi	4
	  call	_spr_pal
	__ldwi	1
	  call	_spr_pri
	__ldwi	6
	  call	_spr_set
	__ldwi	140
	  call	_spr_x
	__ldwi	105
	  call	_spr_y
	__ldwi	29440
	  call	_spr_pattern
	__ldwi	185
	  stx	_al
	__ldwi	17
	  call	_spr_ctrl.2
	__ldwi	4
	  call	_spr_pal
	__ldwi	1
	  call	_spr_pri
	__ldwi	7
	  call	_spr_set
	__ldwi	140
	  call	_spr_x
	__ldwi	65
	  call	_spr_y
	__ldwi	29440
	  call	_spr_pattern
	__ldwi	185
	  stx	_al
	__ldwi	17
	  call	_spr_ctrl.2
	__ldwi	4
	  call	_spr_pal
	__ldwi	1
	  call	_spr_pri
LL1:

	  rts
	.endp

	.proc _hide_sprite
	__pushw
	__ldw_s	0
	  call	_spr_set
	__ldwi	260
	  call	_spr_x
	__ldwi	230
	  call	_spr_y
LL2:

	__addmi	2,__stack
	  rts
	.endp

	.proc _animate_spiky
	__pushw
	__addmi	-2,__stack
	__ldw_s	2
	__pushw
	__ldwi	32
	  jsr	smod
	__pushw
	__ldwi	4
	  jsr	sdiv
	__stw_s	0
	__ldwi	5
	  call	_spr_set
	__ldwi	123
	__pushw
	__ldw_s	2
	__aslw
	__addwi	_spikyX
	__stw	__ptr
	__ldwp	__ptr
	__addws
	  call	_spr_x
	__ldwi	53
	__pushw
	__ldw_s	2
	__aslw
	__addwi	_spikyY
	__stw	__ptr
	__ldwp	__ptr
	__addws
	  call	_spr_y
	__ldwi	6
	  call	_spr_set
	__ldwi	123
	__pushw
	__ldw_s	2
	__aslw
	__addwi	_spikyX
	__stw	__ptr
	__ldwp	__ptr
	__addws
	  call	_spr_x
	__ldwi	93
	__pushw
	__ldw_s	2
	__aslw
	__addwi	_spikyY
	__stw	__ptr
	__ldwp	__ptr
	__addws
	  call	_spr_y
	__ldwi	7
	  call	_spr_set
	__ldwi	123
	__pushw
	__ldw_s	2
	__aslw
	__addwi	_spikyX
	__stw	__ptr
	__ldwp	__ptr
	__addws
	  call	_spr_x
	__ldwi	133
	__pushw
	__ldw_s	2
	__aslw
	__addwi	_spikyY
	__stw	__ptr
	__ldwp	__ptr
	__addws
	  call	_spr_y
LL3:

	__addmi	4,__stack
	  rts
	.endp

	.proc _animate_player
	__pushw
	__ldwi	0
	  call	_spr_set
	__ldw_s	4
	  call	_spr_x
	__ldw_s	2
	  call	_spr_y
	__ldw_s	0
	__stw	<__temp
	__ldwi	0
	  jsr	eqzp
	__lbeq	LL5
	__ldw_s	6
	__pushw
	__ldwi	30
	  jsr	smod
	__stw	<__temp
	__ldwi	15
	  jsr	ltzp
	__lbeq	LL6
	__ldwi	28672
	  call	_spr_pattern
	__lbra	LL7
LL6:

	__ldwi	28928
	  call	_spr_pattern
LL7:

	__lbra	LL8
LL5:

	__ldwi	29696
	  call	_spr_pattern
LL8:

	__ldwi	185
	  stx	_al
	__ldwi	17
	  call	_spr_ctrl.2
	__ldwi	0
	  call	_spr_pal
	__ldwi	1
	  call	_spr_pri
LL4:

	__addmi	8,__stack
	  rts
	.endp

	.proc _animate_enemy
	__pushw
	__ldwi	1
	  call	_spr_set
	__ldw_s	2
	  call	_spr_x
	__ldw_s	0
	  call	_spr_y
	__ldw_s	4
	__pushw
	__ldwi	30
	  jsr	smod
	__stw	<__temp
	__ldwi	15
	  jsr	ltzp
	__lbeq	LL10
	__ldwi	28672
	  call	_spr_pattern
	__lbra	LL11
LL10:

	__ldwi	28928
	  call	_spr_pattern
LL11:

	__ldwi	185
	  stx	_al
	__ldwi	25
	  call	_spr_ctrl.2
	__ldwi	3
	  call	_spr_pal
	__ldwi	1
	  call	_spr_pri
LL9:

	__addmi	6,__stack
	  rts
	.endp

	.proc _level1
	__addmi	-16,__stack
	__ldwi	0
	__stw	_level1BarrierDestroyed
	__stwi_s	20,14
	__stwi_s	90,12
	__ldw_s	14
	__addwi	200
	__stw_s	8
	__ldw_s	12
	__stw_s	6
	  call	_initialize
	__stwi_s	1,4
	__stwi_s	0,0
LL13:

LL14:

LL15:

	__ldw_s	0
	__incw_s	0
	__ldwi	1
	  ldy	#1
	  call	_vsync
	__ldw_s	2
	  call	_joy
	__andwi	1
	__tstw
	__lbeq	LL17
	__stwi_s	1,10
	__ldw_s	14
	__stw	<__temp
	__ldwi	80
	  jsr	gtzp
	__lbeq	LL19
	__ldw_s	14
	__stw	<__temp
	__ldwi	85
	  jsr	lezp
LL19:

	__boolw
	__tstw
	__lbeq	LL18
	__ldwi	1
	__stw	_level1BarrierDestroyed
LL18:

	__ldw_s	8
	__pushw
	__ldw_s	16
	__subws
	__stw	<__temp
	__ldwi	17
	  jsr	ltzp
	__lbeq	LL21
	__ldw_s	6
	__pushw
	__ldw_s	14
	__subws
	__stw	<__temp
	__ldwi	10
	  jsr	ltzp
	__lbeq	LL22
	__ldw_s	12
	__pushw
	__ldw_s	8
	__subws
	__stw	<__temp
	__ldwi	10
	  jsr	ltzp
LL22:

	__boolw
LL21:

	__boolw
	__tstw
	__lbeq	LL20
	__ldwi	1
	  call	_hide_sprite
	__stwi_s	0,4
LL20:

	__lbra	LL23
LL17:

	__stwi_s	0,10
	__ldw_s	2
	  call	_joy
	__andwi	16
	__tstw
	__lbeq	LL24
	__ldw_s	12
	__stw	<__temp
	__ldwi	20
	  jsr	gtzp
	__lbeq	LL25
	__ldw_s	12
	__subwi	1
	__stw_s	12
	__addwi	1
LL25:

	__lbra	LL26
LL24:

	__ldw_s	2
	  call	_joy
	__andwi	64
	__tstw
	__lbeq	LL27
	__ldw_s	12
	__stw	<__temp
	__ldwi	153
	  jsr	ltzp
	__lbeq	LL28
	__ldw_s	12
	__incw_s	12
LL28:

LL27:

LL26:

	__ldw_s	2
	  call	_joy
	__andwi	128
	__tstw
	__lbeq	LL30
	__ldw_s	14
	__stw	<__temp
	__ldwi	0
	  jsr	gtzp
LL30:

	__boolw
	__tstw
	__lbeq	LL29
	__ldw_s	14
	__subwi	1
	__stw_s	14
	__addwi	1
	__lbra	LL31
LL29:

	__ldw_s	2
	  call	_joy
	__andwi	32
	__tstw
	__lbeq	LL33
	__ldw_s	14
	__stw	<__temp
	__ldwi	225
	  jsr	ltzp
LL33:

	__boolw
	__tstw
	__lbeq	LL32
	__ldw	_level1BarrierDestroyed
	__stw	<__temp
	__ldwi	1
	  jsr	eqzp
	__lbne	LL35
	__ldw_s	14
	__stw	<__temp
	__ldwi	85
	  jsr	ltzp
LL35:

	__boolw
	__tstw
	__lbeq	LL34
	__ldw_s	14
	__pushw
	__ldw_s	10
	__subwi	16
	  jsr	lt
	__lbne	LL37
	__ldw_s	4
	__stw	<__temp
	__ldwi	0
	  jsr	eqzp
LL37:

	__boolw
	__tstw
	__lbeq	LL36
	__ldw_s	14
	__incw_s	14
LL36:

LL34:

LL32:

LL31:

LL23:

	__ldw	_level1BarrierDestroyed
	__stw	<__temp
	__ldwi	1
	  jsr	eqzp
	__lbeq	LL39
	__ldw_s	4
	__stw	<__temp
	__ldwi	1
	  jsr	eqzp
LL39:

	__boolw
	__tstw
	__lbeq	LL38
	__ldw_s	0
	__pushw
	__ldwi	2
	  jsr	smod
	__stw	<__temp
	__ldwi	0
	  jsr	eqzp
	__lbeq	LL40
	__ldw_s	6
	__pushw
	__ldw_s	14
	  jsr	gt
	__lbeq	LL41
	__ldw_s	6
	__subwi	1
	__stw_s	6
	__addwi	1
LL41:

	__ldw_s	6
	__pushw
	__ldw_s	14
	  jsr	lt
	__lbeq	LL42
	__ldw_s	6
	__incw_s	6
LL42:

	__ldw_s	8
	__pushw
	__ldw_s	16
	__subws
	__stw	<__temp
	__ldwi	16
	  jsr	gtzp
	__lbeq	LL43
	__ldw_s	8
	__subwi	1
	__stw_s	8
	__addwi	1
LL43:

LL40:

LL38:

	__ldw_s	0
	__pushw
	__ldw_s	16
	__pushw
	__ldw_s	16
	__pushw
	__ldw_s	16
	  call	_animate_player
	__ldw_s	4
	__stw	<__temp
	__ldwi	1
	  jsr	eqzp
	__lbeq	LL44
	__ldw_s	0
	__pushw
	__ldw_s	10
	__pushw
	__ldw_s	10
	  call	_animate_enemy
LL44:

	__ldw	_level1BarrierDestroyed
	__stw	<__temp
	__ldwi	0
	  jsr	eqzp
	__lbeq	LL45
	__ldw_s	0
	  call	_animate_spiky
	__lbra	LL46
LL45:

	__ldwi	5
	  call	_hide_sprite
	__ldwi	6
	  call	_hide_sprite
	__ldwi	7
	  call	_hide_sprite
LL46:

	__ldw_s	4
	__stw	<__temp
	__ldwi	0
	  jsr	eqzp
	__lbeq	LL47
	__ldwi	5
	  call	_spr_set
	__ldwi	130
	  call	_spr_x
	__ldwi	45
	  call	_spr_y
	__ldwi	29952
	  call	_spr_pattern
	__ldwi	185
	  stx	_al
	__ldwi	0
	  call	_spr_ctrl.2
	__ldwi	5
	  call	_spr_pal
	__ldwi	1
	  call	_spr_pri
	__ldw_s	14
	__stw	<__temp
	__ldwi	110
	  jsr	gtzp
	__lbeq	LL49
	__ldw_s	14
	__stw	<__temp
	__ldwi	130
	  jsr	ltzp
LL49:

	__boolw
	__tstw
	__lbeq	LL50
	__ldw_s	12
	__stw	<__temp
	__ldwi	30
	  jsr	gtzp
LL50:

	__boolw
	__tstw
	__lbeq	LL51
	__ldw_s	12
	__stw	<__temp
	__ldwi	50
	  jsr	ltzp
LL51:

	__boolw
	__tstw
	__lbeq	LL48
	__ldwi	0
	__lbra	LL12
LL48:

LL47:

	  ldy	#0
	  call	_satb_update
	__lbra	LL15
LL16:

LL12:

	__addmi	16,__stack
	  rts
	.endp

	.proc _animate_level2_spiky
	__pushw
	__addmi	-2,__stack
	__ldw_s	2
	__pushw
	__ldwi	32
	  jsr	smod
	__pushw
	__ldwi	4
	  jsr	sdiv
	__stw_s	0
	__ldwi	5
	  call	_spr_set
	__ldwi	200
	__pushw
	__ldw_s	2
	__aslw
	__addwi	_spikyX
	__stw	__ptr
	__ldwp	__ptr
	__addws
	  call	_spr_x
	__ldwi	25
	__pushw
	__ldw_s	2
	__aslw
	__addwi	_spikyY
	__stw	__ptr
	__ldwp	__ptr
	__addws
	  call	_spr_y
LL52:

	__addmi	4,__stack
	  rts
	.endp

	.proc _move_bullet
	__pushw
	__ldw_s	4
	  call	_spr_set
	__ldw_s	2
	  call	_spr_x
	__ldw_s	0
	  call	_spr_y
LL53:

	__addmi	6,__stack
	  rts
	.endp

	.proc _level2
	__addmi	-22,__stack
	__stwi_s	0,0
	__stwi_s	20,20
	__stwi_s	90,18
	__stwi_s	270,6
	__stwi_s	0,2
	__stwi_s	212,8
	__stwi_s	37,4
	  call	_initialize
	__stwi_s	0,10
	__stwi_s	30,14
	_load_background	_special_bg,_special_pal,_special_bat,#32,#28
	__ldwi	1
	  ldy	#1
	  call	_vsync
	__ldwi	7
	  call	_hide_sprite
	__ldwi	2
	  call	_hide_sprite
	__ldwi	3
	  call	_hide_sprite
	__ldwi	4
	  call	_hide_sprite
	__ldwi	6
	  call	_spr_set
	__ldwi	200
	  call	_spr_x
	__ldwi	25
	  call	_spr_y
	__stwi_s	0,12
LL55:

LL56:

LL57:

	__ldw_s	10
	__incw_s	10
	__ldwi	1
	  ldy	#1
	  call	_vsync
	__ldw_s	12
	  call	_joy
	__andwi	1
	__tstw
	__lbeq	LL60
	__ldw_s	20
	__stw	<__temp
	__ldwi	160
	  jsr	gezp
LL60:

	__boolw
	__tstw
	__lbeq	LL61
	__ldw_s	18
	__stw	<__temp
	__ldwi	45
	  jsr	ltzp
LL61:

	__boolw
	__tstw
	__lbeq	LL59
	__stwi_s	1,16
	__ldw_s	14
	__subwi	1
	__stw_s	14
	__addwi	1
	__lbra	LL62
LL59:

	__stwi_s	0,16
	__ldw_s	12
	  call	_joy
	__andwi	16
	__tstw
	__lbeq	LL63
	__ldw_s	18
	__stw	<__temp
	__ldwi	20
	  jsr	gtzp
	__lbeq	LL64
	__ldw_s	18
	__subwi	1
	__stw_s	18
	__addwi	1
LL64:

	__lbra	LL65
LL63:

	__ldw_s	12
	  call	_joy
	__andwi	64
	__tstw
	__lbeq	LL66
	__ldw_s	18
	__stw	<__temp
	__ldwi	153
	  jsr	ltzp
	__lbeq	LL67
	__ldw_s	18
	__incw_s	18
LL67:

LL66:

LL65:

	__ldw_s	12
	  call	_joy
	__andwi	128
	__tstw
	__lbeq	LL69
	__ldw_s	20
	__stw	<__temp
	__ldwi	0
	  jsr	gtzp
LL69:

	__boolw
	__tstw
	__lbeq	LL68
	__ldw_s	20
	__subwi	1
	__stw_s	20
	__addwi	1
	__lbra	LL70
LL68:

	__ldw_s	12
	  call	_joy
	__andwi	32
	__tstw
	__lbeq	LL72
	__ldw_s	20
	__stw	<__temp
	__ldwi	162
	  jsr	ltzp
LL72:

	__boolw
	__tstw
	__lbeq	LL71
	__ldw_s	20
	__incw_s	20
LL71:

LL70:

LL62:

	__ldw_s	10
	__pushw
	__ldw_s	22
	__pushw
	__ldw_s	22
	__pushw
	__ldw_s	22
	  call	_animate_player
	__ldw_s	10
	  call	_animate_level2_spiky
	__ldw_s	10
	__pushw
	__ldwi	140
	  jsr	smod
	__stw	<__temp
	__ldwi	0
	  jsr	eqzp
	__lbeq	LL73
	__stwi_s	212,6
	__stwi_s	37,2
	__stwi_s	1,0
LL73:

	__ldw_s	10
	__pushw
	__ldwi	140
	  jsr	smod
	__stw	<__temp
	__ldwi	70
	  jsr	eqzp
	__lbeq	LL74
	__stwi_s	212,8
	__stwi_s	37,4
	__stwi_s	1,0
LL74:

	__ldw_s	0
	__stw	<__temp
	__ldwi	1
	  jsr	eqzp
	__lbeq	LL75
	__ldw_s	2
	__incw_s	2
	__ldw_s	8
	__subwi	1
	__stw_s	8
	__addwi	1
	__ldw_s	4
	__incw_s	4
	__ldwi	2
	__pushw
	__ldw_s	8
	__pushw
	__ldw_s	6
	  call	_move_bullet
	__ldwi	3
	__pushw
	__ldw_s	10
	__pushw
	__ldw_s	8
	  call	_move_bullet
LL75:

	  ldy	#0
	  call	_satb_update
	__ldw_s	14
	__stw	<__temp
	__ldwi	0
	  jsr	eqzp
	__lbeq	LL76
	__lbra	LL54
LL76:

	__lbra	LL57
LL58:

LL54:

	__addmi	22,__stack
	  rts
	.endp

	.proc _gameover
	__addmi	-2,__stack
	  call	_initialize
	__stwi_s	0,0
LL78:

	__ldw_s	0
	__stw	<__temp
	__ldwi	9
	  jsr	ltzp
	__lbne	LL80
	__lbra	LL81
LL79:

	__ldw_s	0
	__incw_s	0
	__lbra	LL78
LL80:

	__ldw_s	0
	  call	_hide_sprite
	__lbra	LL79
LL81:

	  ldy	#0
	  call	_satb_update
	_load_background	_gameover_bg,_gameover_pal,_special_bat,#32,#28
LL77:

	__addmi	2,__stack
	  rts
	.endp

	.proc _main
	__addmi	-258,__stack
	__lea_s	2
	__stw_s	0
	__ldwi	LL0+0
	__stw_s	0
	  call	_level1
	  call	_level2
	  call	_gameover
LL82:

	__addmi	258,__stack
	  rts
	.endp

	.data
	.dw $0
_playerframe0:
	.incspr "graphics\p0.pcx",0,0,2,2
	.code
	.data
	.dw $0
_playerframe0_pal:
	.incpal "graphics\p0.pcx",0,1
	.code
	.data
	.dw $0
_playerframe1:
	.incspr "graphics\p1.pcx",0,0,2,2
	.code
	.data
	.dw $0
_playerframe1_pal:
	.incpal "graphics\p1.pcx",0,1
	.code
	.data
	.dw $0
_playerattackingframe:
	.incspr "graphics\pattacking.pcx",0,0,2,2
	.code
	.data
	.dw $0
_playerattackingframe_pal:
	.incpal "graphics\pattacking.pcx",0,1
	.code
	.data
	.dw $0
_peg:
	.incspr "graphics\peg.pcx",0,0,1,1
	.code
	.data
	.dw $0
_peg_colors:
	.incpal "graphics\peg.pcx",0,1
	.code
	.data
	.dw $0
_weapon:
	.incspr "graphics\weapon.pcx",0,0,1,1
	.code
	.data
	.dw $0
_weapon_pal:
	.incpal "graphics\weapon.pcx",0,1
	.code
	.data
	.dw $0
_spiky:
	.incspr "graphics\spiky.pcx",0,0,2,2
	.code
	.data
	.dw $0
_spiky_pal:
	.incpal "graphics\spiky.pcx",0,1
	.code
	.data
	.dw $0800
_special_bg:
	.incchr "graphics\background.pcx",32,28
	.code
	.data
	.dw $0
_special_pal:
	.incpal "graphics\background.pcx"
	.code
	.data
	.dw $0
_special_bat:
	.incbat "graphics\background.pcx",4096,32,28
	.code
	.data
	.dw $0800
_gameover_bg:
	.incchr "graphics\gameover.pcx",32,28
	.code
	.data
	.dw $0
_gameover_pal:
	.incpal "graphics\gameover.pcx"
	.code
	.data
	.bank CONST_BANK
	.org $4000
LL0:
	.db	65,108,100,100,101,101,32,98
	.db	121,32,83,101,98,97,115,116
	.db	105,97,110,32,77,105,104,97
	.db	105,44,32,50,48,49,50,46
	.db	32,73,32,100,114,101,97,109
	.db	101,100,32,116,104,101,32,100
	.db	101,115,105,103,110,32,97,110
	.db	100,32,110,97,109,101,44,32
	.db	97,102,116,101,114,32,97,110
	.db	32,101,118,101,110,105,110,103
	.db	32,111,102,32,116,114,121,105
	.db	110,103,32,116,111,32,102,105
	.db	103,117,114,101,32,111,117,116
	.db	32,97,32,110,101,119,32,103
	.db	97,109,101,32,105,100,101,97
	.db	32,116,111,32,99,111,100,101
	.db	46,0

	.bss
_level1BarrierDestroyed:		.ds	2
_spikyX:		.ds	16
_spikyY:		.ds	16
__arg:

;0 error(s) in compilation
;	literal pool:130
;	constant pool:0
;	global pool:1600
;	Macro pool:1433
