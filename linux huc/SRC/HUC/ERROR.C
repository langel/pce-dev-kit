/*	File error.c: 2.1 (83/03/20,16:02:00) */
/*% cc -O -c %
 *
 */

#include <stdio.h>
#include "defs.h"
#include "data.h"
#include "error.h"

void error (char *ptr)
{
	FILE *tempfile;

	if (output == NULL) {
		printf("internal error : %s\n", ptr);
		return;
	}

	tempfile = output;
	output = stdout;
	doerror(ptr);
	output = tempfile;
	doerror(ptr);
	errcnt++;
}

void doerror(char* ptr)
{
	int k;
        comment ();
        outstr(" ERROR: ");
        if (inclsp)
          outstr(inclstk_name[inclsp-1]);
        else
          outstr(fname_copy);
        outbyte('(');
        outdec(line_number);
        outbyte(')');
        nl();
	comment ();
	outstr (line);
	nl ();
	comment ();
	k = 0;
	while (k < lptr) {
		if (line[k] == 9)
			tab ();
		else
			outbyte (' ');
		k++;
	}
	outbyte ('^');
	nl ();
	comment ();
	outstr ("******  ");
	outstr (ptr);
	outstr ("  ******");
	nl ();
}
