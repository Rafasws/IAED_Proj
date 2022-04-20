#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "RVtable.h"

ptrFlight *FLinit();

void FLinsert(ptrFlight);

void FLexpand();

ptrFlight FLsearch_date(char *, Date);

ptrFlight FLsearch(char *code);

int FLdelete(char *);

void FLdestroy();
