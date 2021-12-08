#ifndef _INCLUDE_PREPROC_H
#define _INCLUDE_PREPROC_H

void doinclude ();

FILE* fixiname ();

void doasm ();

void dodefine ();

void doundef ();

void preprocess ();

void doifdef (int ifdef);

int ifline();

void noiferr();

int cpp ();

int keepch (char c);

void defmac(char* s);

void addmac ();

void delmac(int mp);

int putmac (char c);

int findmac (char* sname);

void toggle (char name, int onoff);

#endif
