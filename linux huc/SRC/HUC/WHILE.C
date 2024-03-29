/*	File while.c: 2.1 (83/03/20,16:02:22) */
/*% cc -O -c %
 *
 */

#include <stdio.h>
#include "defs.h"
#include "data.h"
#include "while.h"

addwhile (ptr)
int	ptr[];
{
	int	k;

	if (wsptr == WSMAX) {
		error ("too many active whiles");
		return;
	}
	k = 0;
	while (k < WSSIZ)
		*wsptr++ = ptr[k++];
}

delwhile ()
{
	if (readwhile ())
		wsptr = wsptr - WSSIZ;
}

int* readwhile ()
{
	if (wsptr == ws) {
		error ("no active do/for/while/switch");
		return (0);
	} else
		return (wsptr-WSSIZ);
}

int* findwhile ()
{
	int	*ptr;

	for (ptr = wsptr; ptr != ws;) {
		ptr = ptr - WSSIZ;
		if (ptr[WSTYP] != WSSWITCH)
			return (ptr);
	}
	error ("no active do/for/while");
	return NULL;
}

int* readswitch ()
{
	int	*ptr;

	if (ptr = readwhile ())
		if (ptr[WSTYP] == WSSWITCH)
			return (ptr);
	return (0);
}

addcase (val)
int	val;
{
	int	lab;

	if (swstp == SWSTSZ)
		error ("too many case labels");
	else {
		swstcase[swstp] = val;
		swstlab[swstp++] = lab = getlabel ();
		gnlabel (lab);
	}
}
