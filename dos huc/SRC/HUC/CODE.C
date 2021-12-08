/*	File code.c: 2.2 (84/08/31,10:05:13) */
/*% cc -O -c %
 *
 */

#include <stdio.h>
#include "defs.h"
#include "data.h"

/* locals */
static int segment;

/* externs */
extern int arg_stack_flag;

/*
 *	print all assembler info before any code is generated
 *
 */
header ()
{
	outstr("; Small C HuC6280 (v0.2, 08/Nov/97)\n;\n");
	outstr("; Taken to HuC (22/Feb/00)\n;\n");
	outstr("HUC\t= 1\n");
	outstr("\t.include \"startup.asm\"\n");
	outstr("\t.data\n");
	outstr("\t.bank DATA_BANK\n\t.org $6000\n");
	gtext ();
	nl ();
}

gdata ()
{
	if (segment == 1) {
		segment  = 0;
		ol (".bss");
	}
}

gtext ()
{
	if (segment == 0) {
		segment  = 1;
		ol (".code");
	}
}

/*
 *	print pseudo-op  to define a byte
 *
 */
defbyte ()
{
	ot (".db\t");
}

/*
 *	print pseudo-op to define storage
 *
 */
defstorage ()
{
	ot (".ds\t");
}

/*
 *	print pseudo-op to define a word
 *
 */
defword ()
{
	ot (".dw\t");
}

/*
 *	output instructions
 *
 */
out_ins(int code, int type, int data)
{
	INS tmp;

	tmp.code = code;
	tmp.type = type;
	tmp.data = data;
	gen_ins(&tmp);
}

out_ins_ex(int code, int type, int data, int imm)
{
	INS tmp;

	tmp.code = code;
	tmp.type = type;
	tmp.data = data;
	tmp.imm  = imm;
	gen_ins(&tmp);
}

gen_ins(INS *tmp)
{
	if (arg_stack_flag)
		/* queue instructions */
		arg_push_ins(tmp);
	else {
		/* generate code */
		if (optimize)
			push_ins(tmp);
		else
			gen_code(tmp);
	}
}

/*
 *	gen assembly code
 *
 */
gen_code(INS *tmp)
{
	int code;
	int type;
	int data;
	int imm;

	code = tmp->code;
	type = tmp->type;
	data = tmp->data;
	imm  = tmp->imm;

	if (type == T_NOP)
		return;

	switch (code) {
	case I_FARPTR:
		ot("__farptr\t");

		switch (type) {
		case T_LABEL:
			outlabel(data);
			break;
		case T_SYMBOL:
			outsymbol(data);
			break;
		}
		outstr(",");
		outsymbol(tmp->arg[0]);
		outstr(",");
		outsymbol(tmp->arg[1]);
		nl();
		break;

	case I_FARPTR_I:
		ot("__farptr_i\t");
		outsymbol(data);
		outstr(",");
		outsymbol(tmp->arg[0]);
		outstr(",");
		outsymbol(tmp->arg[1]);
		nl();
		break;

	case I_FARPTR_GET:
		ot("__farptr_get\t");
		outsymbol(tmp->arg[0]);
		outstr(",");
		outsymbol(tmp->arg[1]);
		nl();
		break;

	case I_FGETB:
		ot("__farptr_i\t");
		outsymbol(data);
		nl();
		ol("__fgetb");
		break;

	case I_FGETW:
		ot("__farptr_i\t");
		outsymbol(data);
		nl();
		ol("  jsr\t_farpeekw.fast");
		break;

	case I_VGETW:
		ol("__ldw\tvideo_data");
		break;

	case I_VPUTW:
		ol("__stw\tvideo_data");
		break;

	case I_NARGS:
		ot("  ldy\t#");
		outdec(data);
		nl();
		break;

	case I_LDB:
		ot("__ldb\t");

		switch (type) {
		case T_LABEL:
			outlabel(data);
			break;
		default:
			outsymbol(data);
			break;
		}
		nl();
		break;

	case I_LDBP:
		ol("__ldbp\t__ptr");
		break;

	case I_LDW:
		ot("__ldw\t");

		switch (type) {
		case T_SYMBOL:
			outsymbol(data);
			break;
		case T_LABEL:
			outlabel(data);
			break;
		case T_STACK:
			outstr("__stack");
			break;
		}
		nl();
		break;

	case I_LDWI:
		ot("__ldwi\t");

		switch (type) {
		case T_VALUE:
			outdec(data);
			break;
		case T_LABEL:
			outlabel(data);
			break;
		case T_SYMBOL:
			outsymbol(data);
			break;
		case T_STRING:
			outlabel(litlab);
			outbyte('+');
			outdec(data);
			break;
		case T_BANK:
			outstr("BANK(");
			outstr(data);
			outstr(")");
			break;
		case T_VRAM:
			outstr("VRAM(");
			outstr(data);
			outstr(")");
			break;
		case T_PAL:
			outstr("PAL(");
			outstr(data);
			outstr(")");
			break;
		}
		nl();
		break;

	case I_LDWP:
		ol("__ldwp\t__ptr");
		break;

	case I_STB:
		ot("  stx\t");

		switch (type) {
		case T_LABEL:
			outlabel(data);
			break;
		default:
			outsymbol(data);
			break;
		}
		nl();
		break;

	case I_STBPS:
		ol("__stbps");
		break;

	case I_STW:
		ot("__stw\t");

		switch (type) {
		case T_LABEL:
			outlabel(data);
			break;
		case T_SYMBOL:
			outsymbol(data);
			break;
		case T_PTR:
			outstr("__ptr");
			break;
		}
		nl();
		break;
	
	case I_STWPS:
		ol("__stwps");
		break;

	case I_ADDWI:
		ot("__addwi\t");
		outdec(data);
		nl();
		break;

	case I_ADDWS:
		ol("__addws");
		break;

	case I_ADDMI:
		ot("__addmi\t");
		outdec(data);
		outstr(",__stack");
		nl();
		break;

	case I_SUBWI:
		ot("__subwi\t");
		outdec(data);
		nl();
		break;

	case I_SUBWS:
		ol("__subws");
		break;

	case I_ORWS:
		ol("__orws");
		break;

	case I_EORWS:
		ol("__eorws");
		break;

	case I_ANDWS:
		ol("__andws");
		break;

	case I_ASLW:
		ol("__aslw");
		break;

	case I_ASLWS:
		ol("__aslws");
		break;

	case I_ASRW:
		ol("__asrw");
		break;

	case I_COMW:
		ol("__comw");
		break;

	case I_NEGW:
		ol("__negw");
		break;

	case I_SWAPW:
		ol("__swapw");
		break;

	case I_EXTW:
		ol("__extw");
		break;

	case I_BOOLW:
		ol("__boolw");
		break;

	case I_NOTW:
		ol("__notw");
		break;

	case I_JMP:
		ot("  jmp\t");
		outsymbol(data);
		nl();
		break;

	case I_JSR:
		ot("  jsr\t");

		switch (type) {
		case T_SYMBOL:
			outsymbol(data);
			break;
		case T_LIB:
			outstr(data);
			break;
		}
		nl();
		break;

	case I_CALL:
		switch (type) {
		case T_SYMBOL:
			ot("  call\t");
			outsymbol(data);
			if (imm) {
				outstr(".");
				outdec(imm);
			}
			break;
		case T_LIB:
			ot("  jsr\t");
			outstr(data);
			break;
		}
		nl();
		break;

	case I_CALLS:
		ot("__calls\t");
		outdec(data);
		nl();
		break;

	case I_RTS:
		ol("  rts");
		break;

	case I_PUSHW:
		ol("__pushw");
		break;

	case I_PHB:
		ot("__phb\t");
		outdec(data);
		if (imm) {
			outstr(",");
			outdec(imm);
		}
		nl();
		break;

	case I_PHW:
		ot("__phw\t");
		outdec(data);
		if (imm) {
			outstr(",");
			outdec(imm);
		}
		nl();
		break;

	case I_POPW:
		ol("__popw");
		break;

	case I_TSTW:
		ol("__tstw");
		break;

	case I_LBRA:
		ot("__lbra\t");
		outlabel(data);
		nl();
		break;

	case I_LBEQ:
		ot("__lbeq\t");
		outlabel(data);
		nl();
		break;

	case I_LBNE:
		ot("__lbne\t");
		outlabel(data);
		nl();
		break;

	case I_BANK:
		ot(".bank\t");
		switch (type) {
		case T_VALUE:
			outdec(data);
			break;
		default:
			error("bank type switching not handled");
			break;
		}
		nl();
		break;

	case I_OFFSET:
		ot(".org\t");
		switch (type) {
		case T_VALUE:
			outhex((unsigned short)data);
			break;
		default:
			error("org type setting not handled");
			break;
		}
		nl();
		break;

	default:
		gen_asm(tmp);
		break;
	}
}

