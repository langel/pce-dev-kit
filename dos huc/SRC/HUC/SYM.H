#ifndef _SYM_H
#define _SYM_H

#include "data.h"

char* findglb(char*);

char* findloc(char*);

char* addglb (char* sname, char id, char typ, int value, int stor);

char* addloc (char* sname, char id, char typ, int value, int stclass);

void multidef (char* sname);

void illname (void);

#endif
