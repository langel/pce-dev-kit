/*	File pragma.c: 2.1 (00/08/09,04:59:24) */
/*% cc -O -c %
 *
 */

#include <stdio.h>
#include "defs.h"
#include "data.h"
#include "sym.h"

/* defines */
#define TYPE_ACC		0
#define TYPE_BYTE		1
#define TYPE_WORD		2
#define TYPE_FARPTR		3
#define TYPE_AUTO		4
#define TYPE_AUTO_BYTE	5
#define TYPE_AUTO_WORD	6
#define TYPE_AUTO_FAR	7

/* locals */
static struct fastcall  ftemp;
static struct fastcall *fastcall_tbl[256];
static char   cmd[LINESIZE];
static char  *cmdptr;

/* default pragma's */
static char *pragma_init[] = {
	/* far pointer support funcs */
	"fastcall farpeekb(farptr _fbank:_fptr)",
	"fastcall farpeekw(farptr _fbank:_fptr)",
	"fastcall farmemget(word bx, farptr _fbank:_fptr, word acc)",
	/* asm-lib wrappers */
	"fastcall load_palette(byte al, farptr bl:si, byte cl)",
	"fastcall load_bat(word di, farptr bl:si, byte cl, byte ch)",
	"fastcall load_vram(word di, farptr bl:si, word cx)",
	/* text funcs */
	"fastcall cls(word dx)",
	"fastcall set_font_color(byte al, byte acc)",
	"fastcall load_font(farptr bl:si, byte cl)",
	"fastcall load_font(farptr bl:si, byte cl, word di)",
	"fastcall load_default_font(byte dl)",
	"fastcall load_default_font(byte dl, word di)",
	"fastcall put_digit(byte, word)",
	"fastcall put_digit(byte, byte, byte)",
	"fastcall put_char(byte, word)",
	"fastcall put_char(byte, byte, byte)",
	"fastcall put_raw(word, word)",
	"fastcall put_raw(word, byte, byte)",
	"fastcall put_number(word, byte, word)",
	"fastcall put_number(word, byte, byte, byte)",
	"fastcall put_hex(word, byte, word)",
	"fastcall put_hex(word, byte, byte, byte)",
	"fastcall put_string(word, word)",
	"fastcall put_string(word, byte, byte)",
	/* gfx lib funcs */
	"fastcall vram_addr(byte al, byte acc)",
	"fastcall spr_ctrl(byte al, byte acc)",
	"fastcall get_color(word color_reg)",
	"fastcall set_color(word color_reg, word color_data) nop",
	"fastcall set_color_rgb(word color_reg, byte al, byte ah, byte acc)",
	/* map lib funcs */
	"fastcall scan_map_table(word si, word ax, word cx)",
	"fastcall load_map(byte al, byte ah, word, word, byte dl, byte dh)",
	"fastcall set_map_data(word acc)",
	"fastcall set_map_data(farptr bl:si, word ax, word acc)",
	"fastcall set_map_data(farptr bl:si, word ax, word dx, byte acc)",
	"fastcall set_tile_data(farptr bl:si, word cx, farptr al:dx)",
	"fastcall put_tile(word dx, word acc)",
	"fastcall put_tile(word dx, byte al, byte acc)",
	"fastcall get_tile(byte dl, byte acc)",
	/* misc funcs */
	"fastcall get_joy_events(byte acc)",
	"fastcall get_joy_events(byte al, byte acc)",
	"fastcall set_joy_callback(byte dl, byte al, byte ah, farptr bl:si)",
	NULL
};

/* protos */
int fastcall_look(char *fname, int nargs, struct fastcall **p);


/* ----
 * dopragma()
 * ----
 * handle pragma directive
 *
 */
dopragma()
{
	int i;

	/* make a local copy of the pragma command line */
	for (i = 0;; i++) {
		if (ch() == 0)
			break;
		cmd[i] = gch();
	}

	/* parse */
	parse_pragma();
}


/* ----
 * defpragma()
 * ----
 * default pragmas
 *
 */
defpragma()
{
	int i;

	for (i = 0;; i++) {
		if (pragma_init[i] == NULL)
			break;
		strcpy(cmd, pragma_init[i]);
		parse_pragma();
	}
}


/* ----
 * parse_pragma()
 * ----
 * parse pragma command line
 *
 */
parse_pragma()
{
	char sname[NAMESIZE];

	/* get command */
	cmdptr = cmd;

	if(!symget(sname)) {
		error ("illegal symbol name");
		return;
	}

	/* fastcall */
	if (strcmp(sname, "fastcall") == 0)
		new_fastcall(sname);

	/* others */
	else
		error ("unknown pragma");
}


/* ----
 * new_fastcall()
 * ----
 * setup a new fastcall
 *
 * ie. #pragma fastcall func(word dx, byte al, byte ah)
 *
 */
new_fastcall()
{
	struct fastcall *ptr;
	char   fname[NAMESIZE];
	char   sname[NAMESIZE];
	int    hash;
	int    cnt;
	int    i;

	ptr = &ftemp;
	cnt = 0;
	ptr->nargs = 0;
	ptr->flags = 0;
	ptr->argsize = 0;

	/* get func name */
	if(!symget(fname)) {
		error("illegal symbol name");
		return;
	}

	/* open */
	if(!strmatch("(")) {
		error ("missing bracket");
		return;
	}

	/* extract args (max. 8) */
	for (i = 0; i < 8; i++) {
		/* get type */
		if(!symget(sname)) {
			if (*cmdptr == ')')
				break;
			error ("syntax error");
			return;
		}
		if (strcmp(sname, "byte") == 0)
			ptr->argtype[i] = TYPE_BYTE;
		else if (strcmp(sname, "word") == 0)
			ptr->argtype[i] = TYPE_WORD;
		else if (strcmp(sname, "farptr") == 0)
			ptr->argtype[i] = TYPE_FARPTR;
		else {
			error ("fastcall unknown type");
			return;
		}

		/* get name */
		if(!symget(sname)) {
			if (*cmdptr != ',')
				ptr->argtype[i] = TYPE_ACC;
			else {
				ptr->argtype[i] |= TYPE_AUTO;
				ptr->argsize += ptr->argtype[i] & 0x03;
			}
		}
		else {
			if (strcmp(sname, "acc") == 0)
				/* accumulator */
				ptr->argtype[i] = TYPE_ACC;
			else {
				/* far ptr */
				if (ptr->argtype[i] == TYPE_FARPTR) {
					/* bank */
					strcpy(ptr->argname[i++], sname);
					ptr->argtype[i] = TYPE_WORD;
	
					/* addr */
					if(*cmdptr++ != ':') {
						error ("syntax error");
						return;
					}
					if(!symget(sname)) {
						error ("illegal symbol name");
						return;
					}
				}
	
				/* variable */
				strcpy(ptr->argname[i], sname);
				cnt++;
			}
		}

		/* increment arg counter */
		ptr->nargs++;

		/* next */
		if(!strmatch(","))
			break;
	}

	/* close */
	if(!strmatch(")")) {
		error ("missing bracket");
		return;
	}

	/* extra infos */
	if (cnt) {
		if (ptr->nargs > 1)
			ptr->flags |= 0x02;
	}
	if (symget(sname)) {
		if (strcmp(sname, "nop") == 0)
			ptr->flags |= 0x01;
	}

	/* check arg number */
	if (ptr->nargs == 0)
		return;

	/* copy func name */
	strcpy(ptr->fname, fname);

	/* search for multi-decl */
	if (fastcall_look(fname, ptr->nargs, NULL)) {
		error("already defined");
		return;
	}

	/* ok */
	ptr = (void *)malloc(sizeof(struct fastcall));

	if (ptr == NULL)
		error("out of memory");
	else {
		/* dup struct */
		*ptr = ftemp;

		/* add to hash table */
		hash = symhash(fname);
		ptr->next = fastcall_tbl[hash];
		fastcall_tbl[hash] = ptr;
	}
}


/* ----
 * fastcall_look()
 * ----
 * search a fastcall function
 *
 */
int
fastcall_look(char *fname, int nargs, struct fastcall **p)
{
	struct fastcall *ptr;
	struct fastcall *ref;
	int hash;
	int nb;

	/* search */
	hash = symhash(fname);
	ptr  = fastcall_tbl[hash];
	ref  = NULL;
	nb   = 0;
	while (ptr) {
		if (strcmp(ptr->fname, fname) == 0) {
			nb++;
			if (nargs != -1) {
				if (ptr->nargs == nargs)
					ref = ptr;
			}
		}
		ptr = ptr->next;
	}
	if (nargs != -1) {
		if(!ref)
			nb = 0;
	}

	/* return result */
	if (p)
	   *p = ref;
	return (nb);
}


/* ----
 * symhash()
 * ----
 * calculate the hash value of a symbol
 *
 */

int
symhash(char *sym)
{
	int  i;
	char c;
	int  hash = 0;

	/* calc hash value */
	for (i = 0;; i++) {
		c = sym[i];
		if (c == 0)
			break;
		hash += c;
		hash  = (hash << 3) + (hash >> 5) + c;
	}

	/* ok */
	return (hash & 0xFF);
}


/* ----
 * symget()
 * ----
 * extract a symbol name
 *
 */
int
symget(char *sname)
{
	int	i;

	skip_blanks();

	/* first char must be alpha */
	if (!alpha(*cmdptr))
		return (0);

	/* extract symbol name (stops at first non-alphanum char) */
	for (i = 0;; i++) {
		if(!an(*cmdptr))
			break;
		sname[i] = *cmdptr++;
	}
	sname[i] = 0;

	/* ok */
	return (1);
}


/* ----
 * strmatch()
 * ----
 * test if next input string is legal symbol name
 *
 */
int
strmatch(char *lit)
{
	int	i;

	skip_blanks();

	/* compare */
	i = streq (cmdptr, lit);
	
	if (i) {
		/* match */
		cmdptr += i;
		return (1);
	}

	/* different */
	return (0);
}


/* ----
 * skip_blanks()
 * ----
 * skips blank chars (stops at end of input line)
 *
 */
skip_blanks()
{
	while ((*cmdptr == ' ') || (*cmdptr == '\t'))
		cmdptr++;
}

