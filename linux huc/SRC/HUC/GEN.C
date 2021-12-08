/*	File gen.c: 2.1 (83/03/20,16:02:06) */
/*% cc -O -c %
 *
 */

#include <stdio.h>
#include "defs.h"
#include "data.h"

static char *needargs[] = {
	"vreg",
	"vsync",
	"spr_hide", "spr_show",
	"satb_update",
	"map_load_tile",
	NULL
};

/*
 *	gen arg count
 *
 */
gnargs (char *name, int nb)
{
	char *ptr;
	int   i;

	if (name == NULL)
		return;
	for (i = 0; ; i++) {
		ptr = needargs[i];

		if (ptr == NULL)
			break;
		if (strcmp(name, ptr) == 0) {
			out_ins(I_NARGS, T_VALUE, nb);
			break;
		}
	}
}

/*
 *	return next available internal label number
 *
 */
getlabel ()
{
	return (nxtlab++);
}

/*
 *	fetch a static memory cell into the primary register
 */
getmem (char *sym)
{
	if ((sym[IDENT] != POINTER) & (sym[TYPE] == CCHAR)) {
		if (sym[STORAGE] == LSTATIC)
			out_ins(I_LDB, T_LABEL, glint(sym));
		else
			out_ins(I_LDB, T_SYMBOL, sym + NAME);
	} else {
		if (sym[STORAGE] == LSTATIC)
			out_ins(I_LDW, T_LABEL, glint(sym));
		else
			out_ins(I_LDW, T_SYMBOL, sym + NAME);
	}
}

/*
 *	fetch a hardware register into the primary register
 */
getio (char *sym)
{
	out_ins(I_CALL, T_LIB, "getvdc");
}
getvram (char *sym)
{
	out_ins(I_CALL, T_LIB, "readvram");
}

/*
 *	fetch the address of the specified symbol into the primary register
 *
 */
getloc (char *sym)
{
	int value;

	if (sym[STORAGE] == LSTATIC)
		out_ins(I_LDWI, T_LABEL, glint(sym));
	else {
		value = glint(sym) - stkp;
		out_ins(I_LDW, T_STACK, NULL);

		if (value || optimize) {
			out_ins(I_ADDWI, T_VALUE, value);
		}
	}
}

/*
 *	store the primary register into the specified static memory cell
 *
 */
putmem (char *sym)
{
	int code;

	if ((sym[IDENT] != POINTER) & (sym[TYPE] == CCHAR))
		code = I_STB;
	else
		code = I_STW;

	if (sym[STORAGE] == LSTATIC)
		out_ins(code, T_LABEL, glint(sym));
	else
		out_ins(code, T_SYMBOL, sym + NAME);
}

/*
 *	store the specified object type in the primary register
 *	at the address on the top of the stack
 *
 */
putstk (char typeobj)
{
	if (typeobj == CCHAR)
		out_ins(I_STBPS, NULL, NULL);
	else
		out_ins(I_STWPS, NULL, NULL);
	stkp = stkp + INTSIZE;
}

/*
 *	store the primary register
 *	at the address on the top of the stack
 *
 */
putio (char *sym)
{
	out_ins(I_JSR, T_LIB, "setvdc");
	stkp = stkp + INTSIZE;
}
putvram (char *sym)
{
	out_ins(I_JSR, T_LIB, "writevram");
	stkp = stkp + INTSIZE;
}

/*
 *	fetch the specified object type indirect through the primary
 *	register into the primary register
 *
 */
indirect (char typeobj)
{
	out_ins(I_STW, T_PTR, NULL);
	if (typeobj == CCHAR)
		out_ins(I_LDBP, T_PTR, NULL);
	else {
		out_ins(I_LDWP, T_PTR, NULL);
	}
}

farpeek(char *ptr)
{
	if (ptr[TYPE] == CCHAR)
		out_ins(I_FGETB, T_SYMBOL, ptr);
	else
		out_ins(I_FGETW, T_SYMBOL, ptr);
}

/*
 *	print partial instruction to get an immediate value into
 *	the primary register
 *
 */
immed (int type, int data)
{
	out_ins(I_LDWI, type, data);
}

/*
 *	push the primary register onto the stack
 *
 */
gpush ()
{
//	out_ins(I_PUSHWZ, T_VALUE, zpstkp);
//	zpstkp = zpstkp - INTSIZE;

	out_ins(I_PUSHW, T_VALUE, INTSIZE);
	stkp = stkp - INTSIZE;
}

/*
 *	push the primary register onto the stack
 *
 */
gpusharg (int size)
{
	out_ins(I_PUSHW, T_SIZE, size);
	stkp = stkp - size;
}

/*
 *	pop the top of the stack into the secondary register
 *
 */
gpop ()
{
	out_ins(I_POPW, NULL, NULL);
	stkp = stkp + INTSIZE;
}

/*
 *	swap the primary register and the top of the stack
 *
 */
swapstk ()
{
	out_ins(I_SWAPW, NULL, NULL);
}

/*
 *	call the specified subroutine name
 *
 */
gcall (char *sname, int nargs)
{
	out_ins_ex(I_CALL, T_SYMBOL, sname, nargs);
}

/*
 *         generate a bank pseudo instruction
 *
 */
gbank(unsigned char bank, unsigned short offset)
{
	out_ins(I_BANK, T_VALUE, bank);
	out_ins(I_OFFSET, T_VALUE, offset);
}

/*
 *	return from subroutine
 *
 */
gret ()
{
	out_ins(I_RTS, NULL, NULL);
}

/*
 *	perform subroutine call to value on top of stack
 *
 */
callstk (int nargs)
{
	if (nargs <= INTSIZE)
		out_ins(I_CALLS, T_STACK, 0);
	else
		out_ins(I_CALLS, T_STACK, nargs - INTSIZE);

	stkp = stkp + INTSIZE;
}

/*
 *	jump to specified internal label number
 *
 */
jump (int label)
{
	out_ins(I_LBRA, T_LABEL, label);
}

/*
 *	test the primary register and jump if false to label
 *
 */
testjump (int label, int ft)
{
	out_ins(I_TSTW, NULL, NULL);
	if (ft)
		out_ins(I_LBNE, T_LABEL, label);
	else
		out_ins(I_LBEQ, T_LABEL, label);
}

/*
 *	modify the stack pointer to the new value indicated
 *      Is it there that we decrease the value of the stack to add local vars ?
 */
int modstk (int newstkp)
{
	int	k;

//	k = galign(newstkp - stkp);
	k = newstkp - stkp;
	if (k) {
		gtext();
		out_ins(I_ADDMI, T_STACK, k);
	}
	return (newstkp);
}

/*
 *	multiply the primary register by INTSIZE
 */
gaslint ()
{
	out_ins(I_ASLW, NULL, NULL);
}

/*
 *	divide the primary register by INTSIZE
 */
gasrint()
{
	out_ins(I_ASRW, NULL, NULL);
}

/*
 *	Case jump instruction
 */
gjcase() {
	out_ins(I_JMP, T_SYMBOL, "__case");
}

/*
 *	add the primary and secondary registers
 *	if lval2 is int pointer and lval is int, scale lval
 */
gadd (int *lval, int *lval2)
{
	if (dbltest (lval2, lval)) {
		out_ins(I_ASLWS, NULL, NULL);
	}
	out_ins(I_ADDWS, NULL, NULL);
	stkp = stkp + INTSIZE;
}

/*
 *	subtract the primary register from the secondary
 *
 */
gsub ()
{
	out_ins(I_SUBWS, NULL, NULL);
	stkp = stkp + INTSIZE;
}

/*
 *	multiply the primary and secondary registers
 *	(result in primary)
 *
 */
gmult ()
{
	out_ins(I_JSR, T_LIB, "smul");
	stkp = stkp + INTSIZE;
}

/*
 *	divide the secondary register by the primary
 *	(quotient in primary, remainder in secondary)
 *
 */
gdiv ()
{
	out_ins(I_JSR, T_LIB, "sdiv");
	stkp = stkp + INTSIZE;
}

/*
 *	compute the remainder (mod) of the secondary register
 *	divided by the primary register
 *	(remainder in primary, quotient in secondary)
 *
 */
gmod ()
{
	out_ins(I_JSR, T_LIB, "smod");
	stkp = stkp + INTSIZE;
}

/*
 *	inclusive 'or' the primary and secondary registers
 *
 */
gor ()
{
	out_ins(I_ORWS, NULL, NULL);
	stkp = stkp + INTSIZE;
}

/*
 *	exclusive 'or' the primary and secondary registers
 *
 */
gxor ()
{
	out_ins(I_EORWS, NULL, NULL);
	stkp = stkp + INTSIZE;
}

/*
 *	'and' the primary and secondary registers
 *
 */
gand ()
{
	out_ins(I_ANDWS, NULL, NULL);
	stkp = stkp + INTSIZE;
}

/*
 *	arithmetic shift right the secondary register the number of
 *	times in the primary register
 *	(results in primary register)
 *
 */
gasr ()
{
	out_ins(I_JSR, T_LIB, "asr");
	stkp = stkp + INTSIZE;
}

/*
 *	arithmetic shift left the secondary register the number of
 *	times in the primary register
 *	(results in primary register)
 *
 */
gasl ()
{
	out_ins(I_JSR, T_LIB, "asl");
	stkp = stkp + INTSIZE;
}

/*
 *	two's complement of primary register
 *
 */
gneg ()
{
	out_ins(I_NEGW, NULL, NULL);
}

/*
 *	one's complement of primary register
 *
 */
gcom ()
{
	out_ins(I_COMW, NULL, NULL);
}

/*
 *	convert primary register into logical value
 *
 */
gbool ()
{
	out_ins(I_BOOLW, NULL, NULL);
}

/*
 *	logical complement of primary register
 *
 */
glneg ()
{
	out_ins(I_NOTW, NULL, NULL);
}

/*
 *	increment the primary register by 1 if char, INTSIZE if
 *      int
 */
ginc (lval) int lval[];
{
	if (lval[2] == CINT)
		out_ins(I_ADDWI, T_VALUE, 2);
	else
		out_ins(I_ADDWI, T_VALUE, 1);
}

/*
 *	decrement the primary register by one if char, INTSIZE if
 *	int
 */
gdec (lval) int lval[];
{
	if (lval[2] == CINT)
		out_ins(I_SUBWI, T_VALUE, 2);
	else
		out_ins(I_SUBWI, T_VALUE, 1);
}

/*
 *	following are the conditional operators.
 *	they compare the secondary register against the primary register
 *	and put a literl 1 in the primary if the condition is true,
 *	otherwise they clear the primary register
 *
 */

/*
 *	equal
 *
 */
geq ()
{
	out_ins(I_JSR, T_LIB, "eq");
	stkp = stkp + INTSIZE;
}

/*
 *	not equal
 *
 */
gne ()
{
	out_ins(I_JSR, T_LIB, "ne");
	stkp = stkp + INTSIZE;
}

/*
 *	less than (signed)
 *
 */
glt (int lvl)
{
	out_ins(I_JSR,  T_LIB, "lt");
	stkp = stkp + INTSIZE;
}

/*
 *	less than or equal (signed)
 *
 */
gle ()
{
	out_ins(I_JSR, T_LIB, "le");
	stkp = stkp + INTSIZE;
}

/*
 *	greater than (signed)
 *
 */
ggt ()
{
	out_ins(I_JSR, T_LIB, "gt");
	stkp = stkp + INTSIZE;
}

/*
 *	greater than or equal (signed)
 *
 */
gge ()
{
	out_ins(I_JSR, T_LIB, "ge");
	stkp = stkp + INTSIZE;
}

/*
 *	less than (unsigned)
 *
 */
gult (int lvl)
{
	out_ins(I_JSR, T_LIB, "ult");
	stkp = stkp + INTSIZE;
}

/*
 *	less than or equal (unsigned)
 *
 */
gule ()
{
	out_ins(I_JSR, T_LIB, "ule");
	stkp = stkp + INTSIZE;
}

/*
 *	greater than (unsigned)
 *
 */
gugt ()
{
	out_ins(I_JSR, T_LIB, "ugt");
	stkp = stkp + INTSIZE;
}

/*
 *	greater than or equal (unsigned)
 *
 */
guge ()
{
	out_ins(I_JSR, T_LIB, "uge");
	stkp = stkp + INTSIZE;
}

