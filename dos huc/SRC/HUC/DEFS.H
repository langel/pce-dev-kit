/*	File defs.h: 2.1 (83/03/21,02:07:20) */

#ifndef INCLUDE_DEFS_H
#define INCLUDE_DEFS_H

/*
 *	INTSIZE is the size of an integer in the target machine
 *	BYTEOFF is the offset of an byte within an integer on the
 *		target machine. (ie: 8080,pdp11 = 0, 6809 = 1,
 *		360 = 3)
 *	This compiler assumes that an integer is the SAME length as
 *	a pointer - in fact, the compiler uses INTSIZE for both.
 */

#define	INTSIZE	2
#define	BYTEOFF	0

#define T_NOP		-1
#define T_VALUE		 1
#define T_LABEL		 2
#define T_SYMBOL	 3
#define T_PTR		 4
#define T_STACK		 5
#define T_STRING	 6
#define T_LIB		 7
#define T_SIZE		 8
#define T_BANK		 9
#define T_VRAM		10
#define T_PAL		11

#define I_LDB		 1
#define I_LDBP		 2
#define I_LDW		 3
#define I_LDWI		 4
#define I_LDWP		 5
#define I_STB		 6
#define I_STBPS		 7
#define I_STW		 8
#define I_STWPS		 9
#define I_ADDWI		 10
#define I_ADDWS		 11
#define I_ADDMI		 12
#define I_SUBWI		 13
#define I_SUBWS		 14
#define I_ORWS		 15
#define I_EORWS		 16
#define I_ANDWS		 17
#define I_ASLW		 18
#define I_ASLWS		 19
#define I_ASRW		 20
#define I_COMW		 21
#define I_NEGW		 22
#define I_SWAPW		 23
#define I_EXTW		 24
#define I_BOOLW		 25
#define I_NOTW		 26
#define I_JMP		 27
#define I_JSR		 28
#define I_RTS		 29
#define I_CALL		 30
#define I_CALLS      31
#define I_PUSHW      32
#define I_POPW       33
#define I_TSTW       34
#define I_LBRA       35
#define I_LBEQ       36
#define I_LBNE       37
#define I_BANK       38
#define I_OFFSET     39
#define I_FARPTR     40
#define I_FARPTR_I   41
#define I_FARPTR_GET 42
#define I_FGETB      43
#define I_FGETW      44
#define I_VGETW      45
#define I_VPUTW      46
#define I_NARGS      47
#define I_PHB        48
#define I_PHW        49


#define	FOREVER	for(;;)
#define	FALSE	0
#define	TRUE	1
#define	NO	0
#define	YES	1

/* miscellaneous */

#define	EOS	0
#define	EOL	10
#define	BKSP	8
#define	CR	13
#define	FFEED	12
#define TAB	9

/* symbol table parameters */

/* old values, too restrictive
 * #define	SYMSIZ	14
 * #define	SYMTBSZ	32768
 * #define	NUMGLBS	1500
 */
#define SYMSIZ	32
#define SYMTBSZ	131072
#define NUMGLBS	2048

#define	STARTGLB	symtab
#define	ENDGLB	(STARTGLB+NUMGLBS*SYMSIZ)
#define	STARTLOC	(ENDGLB+SYMSIZ)
#define	ENDLOC	(symtab+SYMTBSZ-SYMSIZ)

/* symbol table entry format */

/* old values, too restrictive
 * #define	NAME	0
 * #define	IDENT	9
 * #define	TYPE	10
 * #define	STORAGE	11
 * #define	OFFSET	12
 */

#define NAME    0
#define IDENT   26
#define TYPE    27
#define STORAGE 28
#define FAR     29
#define OFFSET  30

/* system-wide name size (for symbols) */

/* old values, too restrictive
 * #define	NAMESIZE	9
 * #define	NAMEMAX	8
 */

#define NAMESIZE	26
#define NAMEMAX	25

/* possible entries for "ident" */

#define	VARIABLE	1
#define	ARRAY	2
#define	POINTER	3
#define	FUNCTION	4

/* possible entries for "type" */

#define	CCHAR	1
#define	CINT	2

/* possible entries for storage */

#define	PUBLIC	1
#define	AUTO	2
#define	EXTERN	3

#define	STATIC	4
#define	LSTATIC	5
#define	DEFAUTO	6
#define	CONST	7
/* "do"/"for"/"while"/"switch" statement stack */

#define	WSTABSZ	100
#define	WSSIZ	7
#define	WSMAX	ws+WSTABSZ-WSSIZ

/* entry offsets in "do"/"for"/"while"/"switch" stack */

#define	WSSYM	0
#define	WSSP	1
#define	WSTYP	2
#define	WSCASEP	3
#define	WSTEST	3
#define	WSINCR	4
#define	WSDEF	4
#define	WSBODY	5
#define	WSTAB	5
#define	WSEXIT	6

/* possible entries for "wstyp" */

#define	WSWHILE	0
#define	WSFOR	1
#define	WSDO	2
#define	WSSWITCH	3

/* "switch" label stack */

#define	SWSTSZ	100

/* literal pool */

#define	LITABSZ	8192
#define	LITMAX	LITABSZ-1

/* input string */

#define	LITMAX2	LITABSZ-1

/* input line */

#define	LINESIZE	150
#define	LINEMAX	(LINESIZE-1)
#define	MPMAX	LINEMAX

/* macro (define) pool */

#define	MACQSIZE	16384
#define	MACMAX	(MACQSIZE-1)

/* "include" stack */

#define	INCLSIZ	3

/* statement types (tokens) */

#define	STIF	1
#define	STWHILE	2
#define	STRETURN	3
#define	STBREAK	4
#define	STCONT	5
#define	STASM	6
#define	STEXP	7
#define	STDO	8
#define	STFOR	9
#define	STSWITCH	10

#define DEFLIB	""

/* pseudo instruction structure */

typedef struct {
	int code;
	int type;
	int data;
	int imm;
	int arg[2];
} INS;

/* constant array struct */

#define MAX_CONST        1024
#define MAX_CONST_VALUE  8192
#define MAX_CONST_DATA  65536

struct const_array {
	char *sym;
	int   typ;
	int   size;
	int   data;
};

/* fastcall func struct */

struct fastcall {
	struct fastcall *next;
	char   fname[NAMESIZE];
	int    nargs;
	int    argsize;
	int    flags;
	char   argtype[8];
	char   argname[8][NAMESIZE];
};

#endif

