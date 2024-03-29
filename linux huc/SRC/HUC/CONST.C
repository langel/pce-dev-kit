/*	File const.c: 2.1 (00/07/17,16:02:19) */
/*% cc -O -c %
 *
 */

#include <stdio.h>
#include "defs.h"
#include "data.h"
#include "sym.h"

/* protos */
void add_buffer (char *p, char c);


/*
 *	setup a new const array
 *
 */
new_const()
{
	const_ptr = &const_var[const_nb];
	const_val_idx  = const_val_start;
	const_data_idx = const_data_start;
}


/*
 *	add a const array
 *
 */
add_const(int typ)
{
	if((const_data_idx >= MAX_CONST_DATA) || (const_val_idx >= MAX_CONST_VALUE))
		error("too much constant data (> 8KB)");
	if (const_nb >= MAX_CONST)
		error("too much constant arrays");
	else {
		const_ptr->sym   = cptr;
		const_ptr->typ   = typ;
		const_ptr->size  = const_val_idx - const_val_start;
		const_ptr->data  = const_val_start;
		const_val_start  = const_val_idx;
		const_data_start = const_data_idx;
		const_nb++;
	}
}


/*
 *	array initializer
 *
 */
array_initializer(int typ, int id, int stor)
{
	int nb;
	int k;
	int i;

	nb = 0;
	k  = needsub ();

	if (stor == CONST)
		new_const();
	if (match ("=")) {
		if (stor != CONST)
			error ("can't initialize non-const arrays");
		if(!match ("{")) {
			error ("syntax error");
			return (-1);
		}
		if(!match ("}")) {
			for (;;) {
				if (match ("}")) {
					error ("value missing");
					break;
				}
				if (match (",")) {
					error ("value missing");
					continue;
				}
				if ((ch() == '\"') && (id == POINTER))
					i = get_string_ptr(typ);
				else
					i = get_raw_value();
				nb++;
				blanks();
				if (const_val_idx < MAX_CONST_VALUE)
					const_val[const_val_idx++] = i;
				if ((ch() != ',') && (ch() != '}')) {
					error("syntax error");
					return (-1);
				}
				if (match ("}"))
					break;
				gch();
			}
		}
		if (k == 0)
			k = nb;
		if (nb > k) {
			nb = k;
			error ("excess elements in array initializer");
		}
	}
	if (stor == CONST) {
		while (nb < k) {
			nb++;
			if (const_val_idx < MAX_CONST_VALUE)
				const_val[const_val_idx++] = -1;
		}
	}
	return (k);
}


/*
 *  add a string to the literal pool and return a pointer (index) to it
 *
 */
get_string_ptr(int typ)
{
	int  num[1];

	if (typ == CINT)
		error("incompatible pointer type");
	if (qstr(num))
		return (-(num[0] + 1024));
	else
		return (-1);
}


/*
 *  get value raw text
 *
 */
get_raw_value()
{
	char  c;
	char  tmp[LINESIZE+1];
	char *ptr;
	int   level;
	int   flag;
	int   start;

	flag  = 0;
	level = 0;
	start = const_data_idx;
	ptr   = tmp;

	for (;;) {
		c = ch();

		/* discard blanks */
		if ((c == ' ') || (c == '\t')) {
			gch();
			continue;
		}
		/* paranthesis */
		if (c == '(')
			level++;
		else if (c == ')')
			level--;
		/* comma separator */
		else if (c == ',') {
			if (level == 0)
				break;
		}
		/* end */
		else if ((c == 0) || (c == '}')) {
			if (level)
				error("syntax error");
			break;
		}

		/* parse */
		if (an(c)) {
			flag  = 1;
		   *ptr++ = c;
		}
		else {
			/* add buffer */
			if (flag) {
				flag = 0;
			   *ptr  = '\0';
				ptr  = tmp;
				add_buffer(tmp, c);
			}

			/* add char */
			if (const_data_idx < MAX_CONST_DATA)
				const_data[const_data_idx++] = c;
		}
		gch();
	}
	/* add buffer */
	if (flag) {
	   *ptr = '\0';
		add_buffer(tmp, c);
	}
	/* close string */
	if (const_data_idx < MAX_CONST_DATA)
		const_data[const_data_idx++] = '\0';

	return (start);
}


/*
 *	add a string to the constant pool
 *  handle underscore
 *
 */
void add_buffer (char *p, char c)
{
	/* underscore */
	if (alpha(*p)) {
		if (c != '(') {
			if (const_data_idx < MAX_CONST_DATA)
				const_data[const_data_idx++] = '_';
		}
	}

	/* string */
	while (*p) {
		if (const_data_idx < MAX_CONST_DATA)
			const_data[const_data_idx++] = *p;
		p++;
	}
}


/*
 *	dump the constant pool
 *
 */
dump_const ()
{
	int	i, j, k;
	int size;
	int c;

	if (const_nb) {
		const_ptr = const_var;

		for (i = 0; i < const_nb; i++) {
			size = const_ptr->size;
			cptr = const_ptr->sym;
			cptr[STORAGE] = EXTERN;
			prefix ();
			outstr (cptr);
			outstr (":");
			nl();
			j = const_ptr->data;

			while (size) {
				k = const_val[j++];

				if (cptr[TYPE] == CCHAR) {
					defbyte ();
					const_size += 1;
				} else {
					defword ();
					const_size += 2;
				}
				if ((k == -1) || (k >= MAX_CONST_DATA))
					outstr("0");
				else if (k <= -1024) {
					k = (-k) - 1024;
					outlabel(litlab);
					outbyte('+');
					outdec(k);
				}
				else
					outstr(&const_data[k]);
				nl();
				size--;
			}
			const_ptr++;
		}
	}
}

