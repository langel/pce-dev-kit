/*	File io.c: 2.1 (83/03/20,16:02:07) */
/*% cc -O -c %
 *
 */

#include <stdio.h>
#include "defs.h"
#include "data.h"

/*
 *	open input file
 * Input : char* p
 * Output : int error code
 * 
 * Try to open the file whose filename is p, return YES if opened, else NO
 * Updates fname with the actual opened name
 * input is the handle of the opened file
 * 
 */
openin (p) char *p;
{
	strcpy(fname, p);
        strcpy(fname_copy, fname);
	fixname (fname);
	if (!checkname (fname))
		return (NO);
	if ((input = fopen (fname, "r")) == NULL) {
		pl ("Open failure\n");
		return (NO);
	}
	kill ();
	return (YES);
}

/*
 *	open output file
 * Input : nothing but uses global fname
 * Output : nothing but fname contain the name of the out file now
 * 
 * Guess the name of the outfile thanks to the input one and try to open it
 * In case of succes returns YES and output is the handle of the opened file
 * else returns NO
 * 
 */
openout ()
{
   outfname (fname);
   if ((output = fopen (fname, "w")) == NULL) {
      pl ("Open failure : ");
      pl (fname);
      pl ("\n");
      return (NO);
      }
   kill ();
   return (YES);
}

/*
 *	change input filename to output filename
 * Input : char* s
 * Output : char* s is updated
 * 
 * Simply replace the last letter of s by 's'
 * Used to return "file.s" from "file.c"
 * 
 */
outfname (s)
char	*s;
{
	while (*s)
		s++;
	*--s = 's';
}

/*
 *	remove NL from filenames
 * Input : char* s
 * Output : char* s is updated
 * 
 * if any, remove the trailing newline char from the s string
 * 
 */
fixname (s)
char	*s;
{
	while (*s && *s++ != EOL);
	if (!*s) return;
	*(--s) = 0;
}

/*
 *	check that filename is "*.c"
 * Input : char* s
 * Output : int
 * 
 * verify that the 2 last letter of s are ".c", returns YES in this case,
 * else NO
 * 
 */
checkname (s)
char	*s;
{
	while (*s)
		s++;
	if (*--s != 'c')
		return (NO);
	if (*--s != '.')
		return (NO);
	return (YES);
}

/*
 *             kill
 * Input : nothing
 * Output : nothing but updates lptr and line[lptr]
 * 
 * lptr and line[lptr] are set to zero what appears to clear the current 
 * input line
 * 
 */
kill ()
{
	lptr = 0;
	line[lptr] = 0;
}

/*
 *            readline
 * Input : nothing
 * Output : nothing
 * 
 * This function seems to fill line and lptr variables with a line of text
 * coming either form an included file or the main one
 * 
 */

void readline (void)
{
	int	k;
	FILE	*unit;

	FOREVER {
		if (feof (input))
			return;
		if ((unit = input2) == NULL)
			unit = input;
		kill ();
		while ((k = fgetc (unit)) != EOF) {
			if ((k == '\r') | (k == EOL) | (lptr >= LINEMAX))
				break;
			line[lptr++] = k;
		}
		line_number++;
		line[lptr] = 0;
		if (k <= 0)
			if (input2 != NULL) {
				input2 = inclstk[--inclsp];
				line_number = inclstk_line[inclsp];
				fclose (unit);
			}
		if (lptr) {
			if ((ctext) & (cmode)) {
				flush_ins();
				comment ();
				outstr (line);
				nl ();
			}
			lptr = 0;
			return;
		}
	}
}

/*
 *              inbyte
 * Input : nothing
 * Output : int, (actualy char)
 * 
 * Uses the preprocessor as much as possible to get readable data
 * then read the next char and make lptr points to the next one
 * 
 */

inbyte ()
{
	while (ch () == 0) {
		if (feof (input))
			return (0);
		preprocess ();
	}
	return (gch ());
}

/*
 *               inchar
 * Input : nothing
 * Output : int, (actualy char)
 * 
 * Returns the current char, making lptr points to the next one
 * If the buffer if empty, fill it with next line from input
 * 
 */
inchar ()
{
	if (ch () == 0)
		readline ();
	if (feof (input))
		return (0);
	return (gch ());
}

/*
 *              gch
 * Input : nothing
 * Output : int, (actualy char)
 * 
 * If the pointed char (by line and lptr) is 0, return this value
 * else return the current pointed char and advance the lptr to point
 * on the following char
 * 
 */
gch ()
{
	if (ch () == 0)
		return (0);
	else
		return (line[lptr++] & 127);
}

/*
 *                 nch
 * Input : nothing
 * Output : int, (actualy char)
 * 
 * If called when the pointed char is at the end of the line, return 0
 * else return the following char
 * Doesn't change line nor lptr variable
 * 
 */
nch ()
{
	if (ch () == 0)
		return (0);
	else
		return (line[lptr + 1] & 127);
}

/*
 *           ch
 * 
 * Input : nothing but use global line and lptr variables
 * Output : int, (actually char), corresponding to the current pointed char
 *    during the parsing
 * 
 * Appears to be the major function used during the parsing.
 * The global variables line and lptr aren't changed
 *
 */

ch ()
{
	return (line[lptr] & 127);
}

/*
 *	print a carriage return and a string only to console
 *
 */
pl (str)
char	*str;
{
	int	k;

	k = 0;
	putchar (EOL);
	while (str[k])
		putchar (str[k++]);
}

/*
 *	glabel - generate label
 */
glabel (lab)
char	*lab;
{
	flush_ins(); /* David - optimize.c related */
	prefix ();
	outstr (lab);
	col ();
	nl ();
}

/*
 *	gnlabel - generate numeric label
 */
gnlabel (nlab)
int	nlab;
{
	flush_ins(); /* David - optimize.c related */
	outlabel (nlab);
	col ();
	nl ();
}

/*
 *	Output internal generated label prefix
 */
olprfix() {
	outstr("LL");
}

/*
 *	Output a label definition terminator
 */
col ()
{
	outstr (":\n");
}

/*
 *	begin a comment line for the assembler
 *
 */
comment ()
{
	outbyte (';');
}

/*
 *	Output a prefix in front of user labels
 */
prefix () {
	outbyte ('_');
}

/*
 *               tab
 * Input : nothing
 * Output : nothing
 * 
 * Write a tab charater in the assembler file
 * 
 */
tab ()
{
	outbyte (9);
}

/*
 *               ol
 * Input : char* ptr
 * Output : nothing
 * 
 * Writes the string ptr to the assembler file, preceded by a tab, ended by
 * a newline
 * 
 */
ol (ptr)
char ptr[];
{
	ot (ptr);
	nl ();
}

/* 
 *                ot
 * Input : char* ptr
 * Output : nothing
 * 
 * Writes the string ptr to the assembler file, preceded by a tab
 * 
 */
ot (ptr)
char ptr[];
{
	tab ();
	outstr (ptr);
}

/*
 *            nl
 * Input : nothing
 * Output : nothing
 * 
 * Display a newline in the assembler file
 * 
 */

nl ()
{
	outbyte (EOL);
}

/*
 *         outsymbol
 * Input : char* ptr
 * Output : nothing
 * 
 * Writes the string ptr preceded with the result of the function prefix
 * 
 */
outsymbol (ptr)
char *ptr;
{
	prefix ();
	outstr (ptr);
}

/*
 *	print specified number as label
 */
outlabel (label)
int	label;
{
	olprfix ();
	outdec (label);
}

/*
 *  Output a decimal number to the assembler file
 */
/*
outdec (int number)
{
	int	k, zs;
	char	c;

	if (number == -32768) {
		outstr ("-32768");
		return;
	}
	zs = 0;
	k = 10000;
	if (number < 0) {
		number = (-number);
		outbyte ('-');
	}
	while (k >= 1) {
		c = number / k + '0';
		if ((c != '0' | (k == 1) | zs)) {
			zs = 1;
			outbyte (c);
		}
		number = number % k;
		k = k / 10;
	}
}
*/

/* Newer version, shorter and certainly faster */
outdec(int number)
{
 char s[10];
 int i = 0;

 sprintf(s,"%d",number);

 while (s[i])
   outbyte(s[i++]);

 }

/*
 *  Output an hexadecimal unsigned number to the assembler file
 */

/*
outhex (int number)
{
	int	k, zs;
	char	c;

	zs = 0;
        k = 0x10000000;

        outbyte('$');

	while (k >= 1) {
		c = number / k;
                if (c <= 9)
                  c += '0';
                else
                  c += 'A' - 10;

		outbyte (c);

		number = number % k;
		k = k / 16;
	}
}
*/

/* Newer version, shorter and certainly faster */
outhex (int number)
{
	int	i = 0;
	char	s[10];

        outbyte('$');

        sprintf(s,"%0X",number);

        while (s[i])
          outbyte(s[i++]);

}

/*
 * Output an hexadecimal number with a certain number of digits
 */
outhexfix (int number, int length)
{
	int	i = 0;
	char	s[10];
        char	format[10];

        outbyte('$');

        sprintf(format,"%%0%dX", length);

        sprintf(s,format,number);

        while (s[i])
          outbyte(s[i++]);

}


/*
 *             outbyte
 * Input : char c
 * Output : same as input, c
 * 
 * if c is different of zero, write it to the output file
 * 
 */

outbyte (c)
char	c;
{
	if (c == 0)
		return (0);
	fputc (c, output);
	return (c);
}

/*
 *               outstr
 * Input : char*, ptr
 * Output : nothing
 * 
 * Send the input char* to the assembler file
 * 
 */

outstr (ptr)
char	ptr[];
{
	int	k;

	k = 0;
	while (outbyte (ptr[k++]));
}

