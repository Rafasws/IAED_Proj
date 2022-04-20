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

int RVdelete_reservation(char *);

void RVdestroy();


ptrFlight *FLinit();

void FLinsert(ptrFlight);

void FLexpand();

ptrFlight FLsearch_date(char *, Date);

ptrFlight FLsearch(char *code);

int FLdelete(char *);

void FLdestroy();