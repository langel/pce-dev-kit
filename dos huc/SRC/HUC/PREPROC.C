/*	File preproc.c: 2.3 (84/11/27,11:47:40) */
/*% cc -O -c %
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "data.h"
#include "preproc.h"

/* path separator */
#if defined(DJGPP) || defined(MSDOS) || defined(WIN32)
#define PATH_SEPARATOR '\\'
#define PATH_SEPARATOR_STRING "\\"
#else
#define PATH_SEPARATOR '/'
#define PATH_SEPARATOR_STRING "/"
#endif

/* locals */
static char incpath[10][256];

/*
 *  init the include paths
 */
void
init_path(void)
{
	char *p,*pl;
	int	  i, l;

	p = getenv("PCE_INCLUDE");

	if (p == NULL)
		return;
	for (i = 0; i < 10; i++) {
		pl = strchr(p, ';');

		if (pl == NULL)
			l = strlen(p);
		else
			l = pl - p;
		if (l) {
			strncpy(incpath[i], p, l);
			p += l;
			while (*p == ';')
				p++;
		}
		incpath[i][l] = '\0';
		if (l) {
			if (incpath[i][l - 1] != PATH_SEPARATOR)
				strcat(incpath[i],   PATH_SEPARATOR_STRING);
		}
	}
}

/*
 *  open a file - browse paths
 */
FILE *
file_open(char *name, char *mode)
{
	FILE *fp = NULL;
	char  testname[256];
	int	  i;

	for (i = 0; i < 10; i++) {
		if (strlen(incpath[i])) {
			strcpy(testname, incpath[i]);
			strcat(testname, name);
			strcpy(inclstk_name[inclsp], testname);
			fp = fopen(testname, mode);
			if (fp != NULL) break;
		}
	}

	return (fp);
}

/*
 *	open an include file
 */
void doinclude ()
{
	char	*p;
	FILE	*inp2;

	blanks ();
	if (inp2 = fixiname ())
		if (inclsp < INCLSIZ) {
                        inclstk_line[inclsp] = line_number;
                        line_number = 0;
			inclstk[inclsp++] = input2;
			input2 = inp2;
		} else {
			fclose (inp2);
			error ("too many nested includes");
		}
	else {
		error ("Could not open include file");
	}
	kill ();
}

/*
 *	fixiname - remove "brackets" around include file name
 */
FILE* fixiname ()
{
	char  c1, c2, *p, *ibp;
	char  buf[LINESIZE];
	char  buf2[LINESIZE*2];
	FILE *fp;

	ibp = &buf[0];
	c1 = gch ();
	c2 = (c1 == '"') ? '"' : '>';
	if  ((c1 != '"') && (c1 != '<')) {
		error ("incorrect file name delimiter");
		return (NULL);
	}
	for (p = line + lptr; *p;) {
		if (*p == c2)
			 break;
		if((*p == '\\') && (p[1] == '\\'))
			 p++;
		*ibp++ = *p++;
	}
	if (*p != c2) {
		error ("file name delimiter missing");
		return (NULL);
	}
	*ibp = 0;
	fp = NULL;
	strcpy(inclstk_name[inclsp], buf);
	if ((c1 == '<') || ((fp = fopen(buf, "r")) == NULL)) {
		if (strlen(DEFLIB)) {
			strcpy(buf2, DEFLIB);
			strcat(buf2, buf);
			strcpy(inclstk_name[inclsp], buf2);
			fp = fopen(buf2, "r");
		}
		if (fp == NULL)
			fp = file_open(buf, "r");
	}
	return(fp);
}

/*
 *	"asm" pseudo-statement
 *
 *	enters mode where assembly language statements are passed
 *	intact through parser
 *
 */
void doasm ()
{
	flush_ins(); /* David - optimize.c related */
	cmode = 0;
	FOREVER {
		readline ();
		if (match ("#endasm"))
			break;
		if (feof (input))
			break;
		outstr (line);
		nl ();
	}
	kill ();
	cmode = 1;
}

void dodefine ()
{
	addmac();
}

void doundef ()
{
	int	mp;
	char	sname[NAMESIZE];

	if (!symname(sname)) {
		illname();
		kill();
		return;
	}

	if (mp = findmac(sname))
		delmac(mp);
	kill();
}

void preprocess ()
{
	if (ifline()) return;
	while (cpp());
}

void doifdef (int ifdef)
{
	char sname[NAMESIZE];
	int k;

	blanks();
	++iflevel;
	if (skiplevel) return;
	k = symname(sname) && findmac(sname);
	if (k != ifdef) skiplevel = iflevel;
}

int ifline()
{
	FOREVER {
		readline();
		if (feof(input)) return(1);
		if (match("#ifdef")) {
			doifdef(YES);
			continue;
		} else if (match("#ifndef")) {
			doifdef(NO);
			continue;
		} else if (match("#else")) {
			if (iflevel) {
				if (skiplevel == iflevel) skiplevel = 0;
				else if (skiplevel == 0) skiplevel = iflevel;
			} else noiferr();
			continue;
		} else if (match("#endif")) {
			if (iflevel) {
				if (skiplevel == iflevel) skiplevel = 0;
				--iflevel;
			} else noiferr();
			continue;
		}
		if (!skiplevel) return(0);
	}
}

/* 
 *           noiferr
 * Input : nothing
 * Output : nothing
 * 
 * Called when a #if statement is lacking
 * 
 */

void noiferr()
{
	error("no matching #if...");
}


int cpp ()
{
	int	k;
	char	c, sname[NAMESIZE];
	int	tog;
	int	cpped;		/* non-zero if something expanded */

	cpped = 0;
	/* don't expand lines with preprocessor commands in them */
	if (!cmode || line[0] == '#') {
		/* except #inc/#def commands */
		if (!match("#inc") && !match("#def"))
			return(0);
	}

	mptr = lptr = 0;
	while (ch ()) {
		if ((ch () == ' ') | (ch () == 9)) {
			keepch (' ');
			while ((ch () == ' ') | (ch () == 9))
				gch ();
		} else if (ch () == '"') {
			keepch (ch ());
			gch ();
			while (ch () != '"') {
				if (ch () == 0) {
					error ("missing quote");
					break;
				}
				if (ch() == '\\') keepch(gch());
				keepch (gch ());
			}
			gch ();
			keepch ('"');
		} else if (ch () == '\'') {
			keepch ('\'');
			gch ();
			while (ch () != '\'') {
				if (ch () == 0) {
					error ("missing apostrophe");
					break;
				}
				if (ch() == '\\') keepch(gch());
				keepch (gch ());
			}
			gch ();
			keepch ('\'');
		} else if ((ch () == '/') & (nch () == '*')) {
			inchar ();
			inchar ();
			while ((((c = ch ()) == '*') & (nch () == '/')) == 0)
				if (c == '$') {
					inchar ();
					tog = TRUE;
					if (ch () == '-') {
						tog = FALSE;
						inchar ();
					}
					if (alpha (c = ch ())) {
						inchar ();
						toggle (c, tog);
					}
				} else {
					if (ch () == 0)
						readline ();
					else
						inchar ();
					if (feof (input))
						break;
				}
			inchar ();
			inchar ();
		} else if (an (ch ())) {
			k = 0;
			while (an (ch ())) {
				if (k < NAMEMAX)
					sname[k++] = ch ();
				gch ();
			}
			sname[k] = 0;
			if (k = findmac (sname)) {
				cpped = 1;
				while (c = macq[k++])
					keepch (c);
			} else {
				k = 0;
				while (c = sname[k++])
					keepch (c);
			}
		} else
			keepch (gch ());
	}
	keepch (0);
	if (mptr >= MPMAX)
		error ("line too long");
	lptr = mptr = 0;
	while (line[lptr++] = mline[mptr++]);
	lptr = 0;
	return(cpped);
}

int keepch (char c)
{
	mline[mptr] = c;
	if (mptr < MPMAX)
		mptr++;
	return (c);
}

void defmac(char* s)
{
	kill();
	strcpy(line, s);
	addmac();
}

void addmac ()
{
	char	sname[NAMESIZE];
	int	k;
	int	mp;

	if (!symname (sname)) {
		illname ();
		kill ();
		return;
	}
	if (mp = findmac(sname)) {
		error("Duplicate define");
		delmac(mp);
	}
	k = 0;
	while (putmac (sname[k++]));
	while (ch () == ' ' | ch () == 9)
		gch ();
	while (putmac (gch ()));
	if (macptr >= MACMAX)
		error ("macro table full");
}

void delmac(int mp)
{
	--mp; --mp;	/* step over previous null */
	while (mp >= 0 && macq[mp]) macq[mp--] = '%';
}
	

int putmac (char c)
{
	macq[macptr] = c;
	if (macptr < MACMAX)
		macptr++;
	return (c);
}

int findmac (char* sname)
{
	int	k;

	k = 0;
	while (k < macptr) {
		if (astreq (sname, macq + k, NAMEMAX)) {
			while (macq[k++]);
			return (k);
		}
		while (macq[k++]);
		while (macq[k++]);
	}
	return (0);
}

void toggle (char name, int onoff)
{
	switch (name) {
	case 'C':
		ctext = onoff;
		break;
	}
}

