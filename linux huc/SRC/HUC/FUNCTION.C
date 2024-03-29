/*	File function.c: 2.1 (83/03/20,16:02:04) */
/*% cc -O -c %
 *
 */

#include <stdio.h>
#include "defs.h"
#include "data.h"
#include "sym.h"

/* locals */
static INS  ins_stack[1024];
static int  ins_stack_idx;
static char ins_stack_fname[NAMESIZE];
static int  arg_list[32][2];
static int  arg_list_idx;
static int  arg_idx;
static int  func_call_stack;

/* globals */
int arg_stack_flag;
int argtop;

/* protos */
void arg_flush(int arg, int adj);
void arg_to_fptr(struct fastcall *fast, int i, int arg, int adj);

/*
 *	begin a function
 *
 *	called from "parse", this routine tries to make a function out
 *	of what follows
 *	modified version.  p.l. woods
 *
 */
void newfunc ()
{
	char n[NAMESIZE], *ptr;
	int  nbarg;

	fexitlab = getlabel();

	if (!symname (n) ) {
		error ("illegal function or declaration");
		kill ();
		return;
	}
	if (ptr = findglb (n)) {
		if (ptr[IDENT] != FUNCTION)
			multidef (n);
		else if (ptr[OFFSET] == FUNCTION)
			multidef (n);
		else
			ptr[OFFSET] = FUNCTION;
	} else
		addglb (n, FUNCTION, CINT, FUNCTION, PUBLIC);
	if (!match ("("))
		error ("missing open paren");
	flush_ins(); /* David, .proc directive support */
	ot (".proc ");
	prefix ();
	outstr (n);
	nl ();
	locptr = STARTLOC;
	argstk = 0;
	nbarg = 0;
	while (!match (")")) {
		if (symname (n)) {
			if (findloc (n))
				multidef (n);
			else {
				addloc (n, 0, 0, argstk, AUTO);
				argstk = argstk + INTSIZE;
				nbarg++;
			}
		} else {
			error ("illegal argument name");
			junk ();
		}
		blanks ();
		if (!streq (line + lptr, ")")) {
			if (!match (","))
				error ("expected comma");
		}
		if (endst ())
			break;
	}
	stkp = 0;
	argtop = argstk;
	while (argstk) {
		if (amatch ("register", 8)) {
			if (amatch("char", 4)) 
				getarg(CCHAR);
			else if (amatch ("int", 3))
				getarg(CINT);
			else
				getarg(CINT);
			ns();
		} else if (amatch ("char", 4)) {
			getarg (CCHAR);
			ns ();
		} else if (amatch ("int", 3)) {
			getarg (CINT);
			ns ();
		} else {
			error ("wrong number args");
			break;
		}
	}
	if (nbarg)      /* David, arg optimization */
		gpusharg (0);
	statement(YES);
	gnlabel(fexitlab);
	modstk (nbarg * INTSIZE);
	gret (); /* generate the return statement */
	flush_ins();    /* David, optimize.c related */
	ol (".endp");   /* David, .endp directive support */
	nl ();
	stkp = 0;
	locptr = STARTLOC;
}

/*
 *	declare argument types
 *
 *	called from "newfunc", this routine add an entry in the local
 *	symbol table for each named argument
 *	completely rewritten version.  p.l. woods
 *
 */
getarg (t)
int	t;
{
	int	j, legalname, address;
	char	n[NAMESIZE], c, *argptr;

	FOREVER {
		if (argstk == 0)
			return;
		if (match ("*"))
			j = POINTER;
		else
			j = VARIABLE;
		if (!(legalname = symname (n)))
			illname ();
		if (match ("[")) {
			while (inbyte () != ']')
				if (endst ())
					break;
			j = POINTER;
		}
		if (legalname) {
			if (argptr = findloc (n)) {
				argptr[IDENT] = j;
				argptr[TYPE] = t;
				address = argtop - glint(argptr) - 2;
				if (t == CCHAR && j == VARIABLE)
					address = address + BYTEOFF;
				argptr[OFFSET] = (address) & 0xff;
				argptr[OFFSET + 1] = (address >> 8) & 0xff;
			} else
				error ("expecting argument name");
		}
		argstk = argstk - INTSIZE;
		if (endst ())
			return;
		if (!match (","))
			error ("expected comma");
	}
}

/*
 *	perform a function call
 *
 *	called from "heir11", this routine will either call the named
 *	function, or if the supplied ptr is zero, will call the contents
 *	of HL
 *
 */
callfunction (char *ptr)
{
	extern char *new_string(int, char *);
	struct fastcall *fast;
	int call_stack_ref;
	int i, j;
	int nb;
	int adj;
	int idx;
	int	nargs;
	int cnt;

	cnt = 0;
	nargs = 0;
	fast = NULL;
	call_stack_ref = ++func_call_stack;

	/* skip blanks */
	blanks ();

	/* check if it's a special function,
	 * if yes handle it externaly
	 */
	if (ptr) {
		     if (!strcmp(ptr,"bank")) { do_asm_func(T_BANK); return; }
		else if (!strcmp(ptr,"vram")) { do_asm_func(T_VRAM); return; }
		else if (!strcmp(ptr,"pal"))  { do_asm_func(T_PAL);  return; }
		else if (!strcmp(ptr,"set_bgpal")) { doset_bgpalstatement(); return; }
		else if (!strcmp(ptr,"set_sprpal")) { doset_sprpalstatement(); return; }
		else if (!strcmp(ptr,"load_sprites")) { doload_spritesstatement(); return; }
		else if (!strcmp(ptr,"load_background")) { doload_backgroundstatement(); return; }
	}

	/* indirect call (push func address) */
	if (ptr == NULL)
		gpush ();

	/* fastcall check */
	if (ptr == NULL)
		nb = 0;
	else
		nb = fastcall_look(ptr, -1, NULL);

	/* get args */
	while (!streq (line + lptr, ")")) {
		if (endst ())
			break;
		/* fastcall func */
		if (nb) {
			if (nargs)
				stkp = stkp - INTSIZE;
			arg_stack(arg_idx++);
			expression (NO);
		}
		/* standard func */
		else {
			if (nargs)
				gpusharg (INTSIZE);
			expression (NO);
		}
		nargs = nargs + INTSIZE;
		cnt++;
		if (!match (","))
			break;
	}

	/* adjust arg stack */
	if (nb) {
		if (cnt) {
			arg_list[arg_idx - 1][1] = ins_stack_idx;
			arg_idx -= cnt;
		}
		if (arg_idx)
			ins_stack_idx  = arg_list[arg_idx - 1][1];
		else {
			ins_stack_idx  = 0;
			arg_stack_flag = 0;
		}
	}

	/* fastcall func */
	if (nb) {
		nb = fastcall_look(ptr, cnt, &fast);

		/* flush arg instruction stacks */
		if (nb) {
			/* error checking */
			if (fast->flags & 0x02) {
				if (func_call_stack != call_stack_ref) {
					char tmp[NAMESIZE+80];
					sprintf(tmp, "funcs can't be called from "
								 "inside '%s' func call", ptr);
					error(tmp);
				}
			}

			/* fastcall */
			for (i = 0, j = 0, adj = 0, idx = fast->argsize; i < cnt; i++) {
				/* flush arg stack (except for farptr's) */
				if (fast->argtype[j] != 3)
					arg_flush(arg_idx + i, adj);
	
				/* store arg */
				switch (fast->argtype[j]) {
				case 1: /* byte */
					out_ins(I_STB, T_SYMBOL, fast->argname[j]);
					break;
				case 2: /* word */
					out_ins(I_STW, T_SYMBOL, fast->argname[j]);
					break;
				case 3: /* farptr */
					arg_to_fptr(fast, j++, arg_idx + i, adj);
					break;
				case 5: /* auto byte */
					out_ins_ex(I_PHB, T_VALUE, idx, (idx==fast->argsize) ? idx : 0);
					idx -= 1;
					break;
				case 6: /* auto word */
					out_ins_ex(I_PHW, T_VALUE, idx, (idx==fast->argsize) ? idx : 0);
					idx -= 2;
					break;
				case 0: /* acc */
					break;
			 	default:
					error("fastcall internal error");
					break;
				}
	
				/* next */
				adj += INTSIZE;
				j++;
			}
		}
		else {
			/* standard call */
			for (i = 0; i < cnt;) {
				arg_flush(arg_idx + i, 0);
				i++;
				if (i < cnt)
					gpusharg (0);
			}
		}
	}
	
	/* reset func call stack */
	if (call_stack_ref == 1)
		func_call_stack = 0;

	/* close */
	needbrack (")");

	/* push number of args */
	if (nb == 0)
		gnargs(ptr, cnt);

	/* call function */
	if (ptr == NULL)
		callstk (nargs);
	else {
		if (fast) {
			if (fast->flags & 0x01)
				goto l1;
		}
		if (nb)
			gcall (ptr, cnt);
		else
			gcall (ptr, 0);
	}
l1:
	/* adjust stack */
	if (nargs > INTSIZE) {
		nargs = nargs - INTSIZE;
		stkp  = stkp + nargs;
		out_ins(I_ADDMI, T_NOP, nargs);
	}
}

/*
 * start arg instruction stacking
 *
 */
arg_stack(int arg)
{
	if (arg > 31)
		error("too many args");
	else {
		/* close previous stack */
		if (arg)
	   		arg_list[arg - 1][1] = ins_stack_idx;

		/* init new stack */
		ins_stack_idx += 4;
		arg_list[arg][0] = ins_stack_idx;
		arg_list[arg][1] = -1;
		arg_stack_flag = 1;
	}
}

/*
 * put instructions in a temporary stack (one for each func arg)
 *
 */
arg_push_ins(INS *ptr)
{
	if (ins_stack_idx < 1024)
		ins_stack[ins_stack_idx++] = *ptr;
	else {
		if (ins_stack_idx < 1025) {
			ins_stack_idx++;
			error("arg stack full");
		}
	}
}

/*
 * flush arg instruction stacks
 *
 */
void
arg_flush(int arg, int adj)
{
	INS *ins;
	int  idx;
	int  nb;
	int  i;

	if (arg > 31)
		return;
	idx = arg_list[arg][0];
	nb  = arg_list[arg][1] - arg_list[arg][0];

	for(i = 0; i < nb;) {
		/* adjust stack refs */
		i++;
		ins = &ins_stack[idx];

		if((ins->type == T_STACK) && (ins->code == I_LDW)) {
			if (i < nb) {
				ins = &ins_stack[idx + 1];
				if((ins->code == I_ADDWI) && (ins->type == T_VALUE))
					ins->data -= adj;
			}
		}

		/* flush */
		gen_ins(&ins_stack[idx++]);
	}		
}

void
arg_to_fptr(struct fastcall *fast, int i, int arg, int adj)
{
	INS  *ins, tmp;
	char *sym;
	int   idx;
	int   err;
	int   nb;

	if (arg > 31)
		return;

	idx =  arg_list[arg][0];
	nb  =  arg_list[arg][1] - arg_list[arg][0];
	ins = &ins_stack[idx];
	err =  0;

	/* check arg */
	if (nb == 0)
		err = 1;
	else if (ins->type != T_SYMBOL)
		err = 1;
	else {
		if((ins->code != I_LDWI) && (ins->code != I_LDW))
			err = 1;
		else {
			sym = (char *)ins->data;

			/* check symbol type */
			if (ins->code == I_LDW) {
				if((nb < 2) || (sym[IDENT] == VARIABLE))
					err = 1;
			}
			else {
				if((sym[IDENT] == POINTER) || (sym[IDENT] == VARIABLE))
					err = 1;
			}
		}
	}
	if (err) {
		error("can't get farptr");
		return;
	}

	/* ok */	
	if (nb == 1) {
		ins->code   = I_FARPTR;
		ins->arg[0] = (int)fast->argname[i];
		ins->arg[1] = (int)fast->argname[i+1];
		gen_ins(ins);
	}
	else {
		sym = (char *)ins->data;

		/* check symbol type */
		if (sym[FAR]) {
			tmp.code = I_FARPTR_I;
			tmp.type = T_SYMBOL;
			tmp.data = ins->data;
			tmp.arg[0] = (int)fast->argname[i];
			tmp.arg[1] = (int)fast->argname[i+1];
			ins->type = T_VALUE;
			ins->data = 0;
		}
		else {
			if(((sym[IDENT] == ARRAY) ||
				(sym[IDENT] == POINTER)) &&
				(sym[TYPE]  == CINT))
			{
				tmp.code = I_FARPTR_GET;
				tmp.type = NULL;
				tmp.data = NULL;
				tmp.arg[0] = (int)fast->argname[i];
				tmp.arg[1] = (int)fast->argname[i+1];
			}
			else {
				error("can't get farptr");
				return;
			}
		}
		arg_flush(arg, adj);
		gen_ins(&tmp);
	}
}

