#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "types.h"

int RVhash(char *, int);

void RVinit(int);

void RVinsert(ptrReservation);

void RVexpand();

ptrReservation RVsearch(char *);

int RVdelete(char *);

int RVdelete_reservation(char *, int);

void RVdestroy();


ptrFlight *FLinit();

void FLinsert(ptrFlight, int);

ptrFlight FLsearch_date(char *, Date, int);

int FLsearch(char *, int);

int FLdelete(char *, int);

void FLdestroy(int);