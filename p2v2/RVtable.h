#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "time.h"

int RVhash(char *, int);

void RVinit(int);

void RVinsert(ptrReservation);

void RVexpand();

ptrReservation RVsearch(char *);

int RVdelete(char *);

void RVdestroy();
