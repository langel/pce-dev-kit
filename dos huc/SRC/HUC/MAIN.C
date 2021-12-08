/*	File main.c: 2.7 (84/11/28,10:14:56)
 *
 * PC Engine C Compiler
 * Made by <unknown guy>, hacked to work on Pc Engine by David Michel
 * resumed work by Zeograd
 *
 * 00/02/22 : added oldargv variable to show real exe name in usage function
 */
/*% cc -O -c %
 *
 */

#include <stdio.h>
#include "defs.h"
#include "data.h"

int main (int argc,char* argv[])
{
	char	*p,*bp;
	char** oldargv = argv;
	int smacptr;
	macptr = 0;
	ctext = 0;
	argc--; argv++;
	errs = 0;
	aflag = 1;
	optimize = 2;	/* -O2 by default */
	while (p = *argv++)
		if (*p == '-') while (*++p)
			switch(*p) {
				case 't': case 'T':
					ctext = 1;
					break;
				case 's': case 'S':
					sflag = 1;
					break;
				case 'c': case 'C':
					cflag = 1;
					break;
				case 'a': case 'A':
					aflag = 0;
					break;
				case 'd': case 'D':
					bp = ++p;
					if (!*p) usage(oldargv[0]);
					while (*p && *p != '=') p++;
					if (*p == '=') *p = '\t';
					while (*p) p++;
					p--;
					defmac(bp);
					break;
				case 'o': case 'O':
					/* David, made -O equal to -O2
					 * I'm too lazy to tape -O2 each time :)
					 */
					if (!p[1]) optimize = 2;
					else       optimize = atoi(++p);
					break;
				default:
					usage(oldargv[0]);
			}
			else break;

	smacptr = macptr;
	if (!p)
		usage(oldargv[0]);
	printf("HuC (v1.4.2)\n");
	init_path();
	while (p) {
		errfile = 0;
		if (extension(p) == 'c') {
			glbptr = STARTGLB;
			locptr = STARTLOC;
			wsptr = ws;
			inclsp =
			iflevel =
			skiplevel =
			swstp =
			litptr =
			stkp =
			errcnt =
			ncmp =
			lastst =
			quote[1] =
			line_number = 0;
			macptr = smacptr;
			input2 = NULL;
			quote[0] = '"';
			cmode = 1;
			glbflag = 1;
			nxtlab = 0;
			litlab = getlabel ();
			defmac("end\tmemory");
			addglb("memory", ARRAY, CCHAR, 0, EXTERN);
			addglb("stack", ARRAY, CCHAR, 0, EXTERN);
			rglbptr = glbptr;
			addglb ("etext", ARRAY, CCHAR, 0, EXTERN);
			addglb ("edata", ARRAY, CCHAR, 0, EXTERN);
			/* PCE specific externs */
			addglb ("font_base", VARIABLE, CINT, 0, EXTERN);
			addglb_far("vdc", CINT);
			addglb_far("vram", CCHAR);
			/* end specific externs */
			defpragma();
			defmac("short\tint");
			defmac("huc6280\t1");
			defmac("huc\t1");
//			initmac();
			/*
			 *	compiler body
			 */
			if (!openin (p))
				return;
			if (!openout ())
				return;
			header ();
//			gtext ();
			parse ();
			fclose (input);
//			gdata ();
			dumplits ();
			dumpglbs ();
			errorsummary ();
//			trailer ();
			fclose (output);
			pl ("");
			errs = errs || errfile;
#ifndef	NOASLD
		}
		if (!errfile && !sflag) {
				errs = errs || assemble(p);
		}
#else
		} else {
			fputs("Don't understand file ", stderr);
			fputs(p, stderr);
			errs = 1;
		}
#endif
		p = *argv++;
	}
// David, removed because link() doesn't exist
//
//#ifndef	NOASLD
//	if (!errs && !sflag && !cflag)
//		errs = errs || link();
//#endif
	exit(errs != 0);
}

FEvers()
{
	outstr("\tFront End (2.7,84/11/28)");
}

usage(char* exename)
{
	fprintf(stderr,"HuC (v1.4.2, 2000/08/31)\n\n");
	fprintf(stderr,"usage: %s [-tcsa] [-dSYM[=VALUE]] [-o<value>] files\n", exename);
	exit(1);
}

/*
 *	process all input text
 *
 *	at this level, only static declarations, defines, includes,
 *	and function definitions are legal.
 *
 */
parse ()
{
	while (!feof (input)) {

		if (amatch ("extern", 6))
			dodcls(EXTERN);
		else if (amatch ("static",6))
			dodcls(STATIC);
		else if (amatch ("const",5))
			dodcls(CONST);
		else if (dodcls(PUBLIC)) ;
		else if (match ("#asm"))
			doasm ();
		else if (match ("#include"))
			doinclude ();
		else if (match ("#define"))
			dodefine();
		else if (match ("#undef"))
			doundef();
		else if (match ("#pragma"))
			dopragma();
//		else if (match("#newbank")) /* Zeograd, not original code */
//			donewbank();
		else if (match("#inc"))     /* Zeograd, not original code */
			dopsdinc();
		else if (match("#def"))     /* Zeograd, not original code */
			dopsddef();
		else
			newfunc ();
		blanks ();
	}
	if (optimize)
		flush_ins();
}

/*
 *		parse top level declarations
 */

dodcls(int stclass)
{
	int err;

	blanks();
	if (amatch("char", 4))
		err = declglb(CCHAR, stclass);
	else if (amatch("int", 3))
		err = declglb(CINT, stclass);
	else if (stclass == PUBLIC)
		return(0);
	else
		err = declglb(CINT, stclass);
	if (err)
		kill ();
	else
		ns ();
	return(1);
}


/*
 *	dump the literal pool
 */
dumplits ()
{
	int	j, k;

	if ((litptr == 0) && (const_nb == 0))
		return;
	outstr("\t.data\n");
	outstr("\t.bank CONST_BANK\n\t.org $4000\n");
	if (litptr) {
		outlabel (litlab);
		col ();
		k = 0;
		while (k < litptr) {
			defbyte ();
			j = 8;
			while (j--) {
				outdec (litq[k++] & 127);
				if ((j == 0) | (k >= litptr)) {
					nl ();
					break;
				}
				outbyte (',');
			}
		}
	}
	if (const_nb)
		dump_const ();
}

/*
 *	dump all static variables
 */
dumpglbs ()
{
	int i = 1;
	int	j;

	if (glbflag) {
		cptr = rglbptr;
		while (cptr < glbptr) {
			if (cptr[IDENT] != FUNCTION) {
//				ppubext(cptr);
				if (cptr[STORAGE] != EXTERN) {
					if (i) {
						i = 0;
						nl();
						gdata();
					}
					prefix ();
					outstr (cptr);
					outstr (":\t");
					defstorage ();
					j = glint(cptr);
					if ((cptr[TYPE] == CINT) ||
					    (cptr[IDENT] == POINTER))
						j = j * INTSIZE;
					outdec (j);
					nl ();
				}
			} else {
//				fpubext(cptr);
			}
			cptr = cptr + SYMSIZ;
		}
	}
	if (i) {
		nl();
		gdata();
	}
	outstr("__arg:\n");
}

/*
 *	report errors
 */
errorsummary ()
{
	if (ncmp)
		error ("missing closing bracket");
	nl ();
	comment ();
	outdec (errcnt);
	if (errcnt) errfile = YES;
	outstr (" error(s) in compilation");
	nl ();
	comment();
	ot("literal pool:");
	outdec(litptr);
	nl();
	comment();
	ot("constant pool:");
	outdec(const_size);
	nl();
	comment();
	ot("global pool:");
	outdec(glbptr-rglbptr);
	nl();
	comment();
	ot("Macro pool:");
	outdec(macptr);
	nl();
	pl (errcnt ? "Error(s)" : "No errors");
}

extension(s)
char *s;
{
	s += strlen(s) - 2;
	if (*s == '.')
		return(*(s+1));
	return(' ');
}

assemble(s)
char	*s; {
	char buf[100];
        strcpy(buf, s);
	buf[strlen(buf)-1] = 's';
#ifdef DJGPP
	return(execlp("pceas.exe","pceas.exe",""/*"-m"*/,buf,0));
#elif defined(linux)
	return(execlp("pceas","pceas",buf,0));
#else
  #error Add calling sequence depending on your OS
#endif
}

