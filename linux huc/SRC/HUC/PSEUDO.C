#include "pseudo.h"

/* local array to store internal strings */
static char str_buf[0x10000];
static int  str_idx;

/* protos */
char *new_string(int und, char *a);


/*
 * This source file includes all kind of stuff used to 'simulate' pseudo code
 * of the magic kit and so using itself pseudo C functions...
 */

void dopsdinc()
{
 int dummy; /* Used in the qstr function, I don't know its utility yet */
 int numericarg = 0; /* Number of numeric arg to test validity */

 if (amatch("pal",3))
   {
    if (!match("("))
      error("missing (");

    ol(".data"); /* David, put all the .inc pseudos in the data segment, */
                 /*        this way no more newbank() calls needed */
                 /*        for data. :) The assembler will take care */
                 /*        of everything... */

    readstr(&dummy); /* read the label name */
    prefix();
    outstr(litq2);
    outstr(":\n");
	addglb_far(litq2, CINT);

    if (!match(","))
      {
        error("missing ,");
        kill();
        return;
      }

    ot(".incpal \"");

    readqstr(&dummy); /* read the filename */

    outstr(litq2);
    outstr("\"");

    if (match(","))
      outstr(",");

    numericarg = 0;

    while (!match(")"))
      {
       numericarg++;

       number(&dummy);
       outdec(dummy);
       if (match(","))
         outstr(",");

       }

    nl();
    ol(".code");

    if (numericarg>2)
      error("Maximum 2 numeric arg for incpal(name,\"filename\" [,start_pal] [,nb_pal])");

    kill();

    }
 else
 if (amatch("bin",3))
   {
    if (!match("("))
      error("missing (");

    ol(".data");
    readstr(&dummy); /* read the label name */
    prefix();
    outstr(litq2);
    outstr(":\n");
	addglb_far(litq2, CCHAR);

    if (!match(",")) {
        error("missing ,");
        kill();
        return;
    }

    ot(".incbin \"");
    readqstr(&dummy); /* read the filename */
    outstr(litq2);
    outstr("\"\n");

    if (!match(")"))
      error("missing )");

    nl();
    ol(".code");
    kill();
   }
 else
 if (amatch("bat",3))
   {

    if (!match("("))
      error("missing (");

    ol(".data");

    readstr(&dummy); /* read the label name */
    prefix();
    outstr(litq2);
    outstr(":\n");
	addglb_far(litq2, CINT);

    if (!match(","))
      {
        error("missing ,");
        kill();
        return;
      }

    ot(".incbat \"");

    readqstr(&dummy);

    outstr(litq2);
    outstr("\"");

    if (match(","))
      outstr(",");

    numericarg = 0;

    while (!match(")"))
      {
       numericarg++;

       number(&dummy);
       outdec(dummy);
       if (match(","))
         outstr(",");

       }

    nl();
    ol(".code");

    if ((numericarg!=1) &&
        (numericarg!=3) &&
        (numericarg!=5))
      error("Either 1,3 or 5 numeric arguments are needed for incbat statement");

    kill();

    }
 else
 if (amatch("spr",3))
   {

    if (!match("("))
      error("missing (");

    ol(".data");

    readstr(&dummy); /* read the label name */
    prefix();
    outstr(litq2);
    outstr(":\n");
	addglb_far(litq2, CINT);

    if (!match(","))
      {
        error("missing ,");
        kill();
        return;
      }

    ot(".incspr \"");

    readqstr(&dummy);

    outstr(litq2);
    outstr("\"");

    if (match(","))
      outstr(",");

    numericarg = 0;

    while (!match(")"))
      {
       numericarg++;

       number(&dummy);
       outdec(dummy);
       if (match(","))
         outstr(",");

       }

    nl();
    ol(".code");

    if ((numericarg!=0) &&
        (numericarg!=2) &&
        (numericarg!=4))
      error("Either 0,2 or 4 numeric arguments are needed for incspr statement");

    kill();

    }
 else
 if (amatch("chr",3))
   {

    if (!match("("))
      error("missing (");

    ol(".data");

    readstr(&dummy); /* read the label name */
    prefix();
    outstr(litq2);
    outstr(":\n");
	addglb_far(litq2, CINT);

    if (!match(","))
      {
        error("missing ,");
        kill();
        return;
      }

    ot(".incchr \"");

    readqstr(&dummy);

    outstr(litq2);
    outstr("\"");

    if (match(","))
      outstr(",");

    numericarg = 0;

    while (!match(")"))
      {
       numericarg++;

       number(&dummy);
       outdec(dummy);
       if (match(","))
         outstr(",");

       }

    nl();
    ol(".code");

    if ((numericarg!=0) &&
        (numericarg!=2) &&
        (numericarg!=4))
      error("Either 0,2 or 4 numeric arguments are needed for incchr statement");

    kill();

    }
 else
 if (amatch("tile",4))
   {

    if (!match("("))
      error("missing (");

    ol(".data");

    readstr(&dummy); /* read the label name */
    prefix();
    outstr(litq2);
    outstr(":\n");
	addglb_far(litq2, CINT);

    if (!match(","))
      {
        error("missing ,");
        kill();
        return;
      }

    ot(".inctile \"");

    readqstr(&dummy);

    outstr(litq2);
    outstr("\"");

    if (match(","))
      outstr(",");

    numericarg = 0;

    while (!match(")"))
      {
       numericarg++;

       number(&dummy);
       outdec(dummy);
       if (match(","))
         outstr(",");

       }

    nl();
    ol(".code");

    if ((numericarg!=0) &&
        (numericarg!=2) &&
        (numericarg!=4))
      error("Either 0,2 or 4 numeric arguments are needed for inctile statement");

    kill();

    }
 else
   {
    error("Unknown include directive");
    kill();
    }
 return;
}


void dopsddef()
{
  int numericarg = 0;
  int dummy = 0;

  if (amatch("pal",3))
   {

    if (!match("("))
      error("missing (");

    ol(".data");

    readstr(); /* read the label name */
    prefix();
    outstr(litq2);
    outstr(":");
	addglb_far(litq2, CINT);

    if (!match(","))
      {
        error("missing ,");
        kill();
        return;
      }

    ot(".defpal ");

    numericarg = 0;

    while (!match(")"))
      {
       numericarg++;

       number(&dummy);
       outhexfix(dummy,3);
       if (match(","))
         outstr(",");

       }

    nl();
    ol(".code");

    if (numericarg>16)
      error("No more than 16 colors can be defined at once");

    kill();

    }
  else
 if (amatch("chr",3))
   {

    if (!match("("))
      error("missing (");

    ol(".data");

    readstr(); /* read the label name */
    prefix();
    outstr(litq2);
    outstr(":");
	addglb_far(litq2, CINT);

    if (!match(","))
      {
        error("missing ,");
        kill();
        return;
      }

    ot(".defchr ");

    numericarg = 0;

    while (!match(")"))
      {
       numericarg++;

       number(&dummy);

       switch (numericarg)
         {
          case 1:
               outhexfix(dummy,4);
               outstr(",");
               break;
          case 2:
               outdec(dummy);
               outstr(",\\");
               nl();
               break;
          case 10:
               outhexfix(dummy,8);
               break;
          default:
       	       outhexfix(dummy,8);
               outstr(",\\");
               nl();

          }

         match(",");

       }

    nl();
    ol(".code");

    if (numericarg!=10)
      error("You must enter the VRAM address, the default palette and 8 values for pattern");

    kill();

    }
  else
 if (amatch("spr",3))
   {

    if (!match("("))
      error("missing (");

    ol(".data");

    readstr(); /* read the label name */
    prefix();
    outstr(litq2);
    outstr(":");
	addglb_far(litq2, CINT);

    if (!match(","))
      {
        error("missing ,");
        kill();
        return;
      }

    ot(".defspr ");

    numericarg = 0;

    while (!match(")"))
      {
       numericarg++;

       number(&dummy);

       switch (numericarg)
         {
          case 1:
               outhexfix(dummy,4);
               outstr(",");
               break;
          case 2:
               outdec(dummy);
               outstr(",\\");
               nl();
               break;
          case 34:
               outhexfix(dummy,8);
               break;
          default:
       	       outhexfix(dummy,8);
               outstr(",");

               if (!(numericarg & 1))
                 {
                  outstr("\\");
                  nl();
                 }

          }

       match(",");

       }

    nl();
    ol(".code");

    if (numericarg!=34)
      error("You must enter the VRAM address, the default palette and 32 values for pattern");

    kill();

    }
  else
    {
      error("Unknown define directive");
      kill();
    }
 return;
 }


int outcomma()
{

   if (!match(","))
    {
      error("missing ,");
      kill();
      return 1;
    }

  outbyte(',');

  return 0;

 }

int outnameunderline()
{
  char	n[NAMESIZE];

  if (!symname(n))
    {
      error("invalid identifier");
      kill();
      return 1;
     }

  prefix();
  outstr(n);

  return 0;

 }

int outconst()
{

  int dummy;

  number(&dummy);
  outbyte('#');
  outdec(dummy);

  return 0;

 }

void doset_bgpalstatement()
{ /* syntax is
     number of the first palette to alter : integer
     name of the data for loading palettes : identifier
     [ number of palette to load : integer ]
     if last argument is missing, 1 is assumed
   */

  flush_ins();  /* David, optimize.c related */
  ot("_set_bgpal\t");

  outconst();
  if (outcomma())		return;
  if (outnameunderline())	return;
  if (!match(","))
    {
     outstr(",#");
     outdec(1);
    }
  else
    {
      outbyte(',');
      outconst();
    }

  nl();
  needbrack(")");
}

void doset_sprpalstatement()
{ /* syntax is
     number of the first palette to alter : integer
     name of the data for loading palettes : identifier
     [ number of palette to load : integer ]
     if last argument is missing, 1 is assumed
   */

  flush_ins();  /* David, optimize.c related */
  ot("_set_sprpal\t");

  outconst();
  if (outcomma())		return;
  if (outnameunderline())	return;
  if (!match(","))
    {
     outstr(",#");
     outdec(1);
    }
  else
    {
      outbyte(',');
      outconst();
    }

  nl();
  needbrack(")");
}


void doload_spritesstatement()
{ /* syntax is
     offset in vram to load data at : integer
     name of the data to transfert : identifier
     number of sprites (of size 32x64) to load : integer
   */
  flush_ins();  /* David, optimize.c related */
  ot("load_sprites\t");

  outconst();
  if (outcomma())		return;
  if (outnameunderline())	return;
  if (!match(","))
    {
     outstr(",#");
     outdec(1);
    }
  else
    {
      outbyte(',');
      outconst();
    }

  nl();
  needbrack(")");

 }

void doload_backgroundstatement()
{ /* syntax is
     name of the beginning of the data pattern : identifier
     name of the 16 palettes : identifier
     name of the bat : identifier
     width (in tiles [8x8] ) : integer
     height (in tiles [8x8] ) : integer
   */

  flush_ins();  /* David, optimize.c related */
  ot("_load_background\t");

  if (outnameunderline())	return;
  if (outcomma())		return;

  if (outnameunderline())	return;
  if (outcomma())		return;

  if (outnameunderline())	return;
  if (outcomma())		return;

  if (outconst())		return;
  if (outcomma())		return;

  if (outconst())		return;

  nl();
  needbrack(")");

 }

void
do_asm_func(int type)
{	/* syntax is
	   name of the data : identifier
	 */
	char  n[NAMESIZE];
	char *ptr;

	/* get identifier */ 
	if (!symname(n)) {
		error("invalid identifier");
		kill();
		return;
	}

	/* close function */
	needbrack(")");

	/* duplicate identifier */
	ptr = new_string(1, n);

	/* gen code */
	if (ptr)
		out_ins(I_LDWI, type, ptr);
	else
		error("out of memory");
}

char *
new_string(int und, char *a)
{
	int len;
	int tmp;

	if (a == NULL)
		return (NULL);
	len = strlen(a);
	tmp = str_idx;
	if((len + str_idx) > 0xFFF0)
		return (NULL);
	if (und)
		str_buf[str_idx++] = '_';
	strcpy(&str_buf[str_idx], a);
	str_idx += len;
	str_buf[str_idx++] = '\0';
	return (&str_buf[tmp]);
}

