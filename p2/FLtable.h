#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "RVtable.h"

ptrFlight *FLinit();

void FLinsert(ptrFlight);

void FLexpand();

ptrFlight FLsearch(char *, Date);

int FLdelete(char *);

void FLdestroy();
