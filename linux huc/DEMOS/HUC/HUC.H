/*
 * sprite defines
 */

#define  FLIP_X_MASK 0x08
#define  FLIP_Y_MASK 0x80
#define  FLIP_MAS   0x88
#define  SIZE_MAS   0x31

#define  NO_FLIP    0x00
#define  NO_FLIP_X  0x00
#define  NO_FLIP_Y  0x00
#define  FLIP_X     0x08
#define  FLIP_Y     0x80
#define  SZ_16x16   0x00
#define  SZ_16x32   0x10
#define  SZ_16x64   0x30
#define  SZ_32x16   0x01
#define  SZ_32x32   0x11
#define  SZ_32x64   0x31

/*
 * joypad defines
 */

#define	JOY_A		0x01
#define	JOY_B		0x02
#define	JOY_SLCT	0x04
#define	JOY_STRT	0x08
#define	JOY_UP		0x10
#define	JOY_RGHT	0x20
#define	JOY_DOWN	0x40
#define	JOY_LEFT	0x80

/*
 * screen defines
 */
#define	SCR_SIZE_32x32  0x00
#define	SCR_SIZE_64x32  0x10
#define	SCR_SIZE_128x32 0x30
#define	SCR_SIZE_32x64  0x40
#define	SCR_SIZE_64x64  0x50
#define	SCR_SIZE_128x64 0x70

/*
 * lib fastcall decls
 */
/*#pragma fastcall putnumber(word dx, byte al, word di)
  #pragma fastcall putnumber(word dx, byte al, byte cl, byte ch)*/





