/*
 * File: RVtable.c
 *
 * Author: Rafael Gaspar Ferreira (ist197342)
 * E-mail: rafael.gaspar@tecnico.ulisboa.pt
 *
 * Description:
 * The goal of this project is the development of
 * a flights management system in the C programming language.
 * This file provides the functions prototypes used in RVtable.c
 *
 * This is project 2 for subject IAED of course LEIC-T.
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "types.h"

/* Hash function*/
int RVhash(char *, int);

/* Create and reserves memory for the ptrReservation array*/
void RVinit(int);

/* Insert a reservation in the ptrReservation array */
void RVinsert(ptrReservation);

/* Increase the size of ptrReservation array*/
void RVexpand(int);

/*Look for a reservation in the ptrReservation array,
* with a given code,and return his ptrReservation*/
ptrReservation RVsearch(char *);

/*Delete a reservation, free the memory, 
* and rearrange the ptrReservation array*/
int RVdelete(char *);

/*Delete a reservation, free the memory, 
* and rearrange the ptrReservation array and the 
* and the corresponding flight reservation array*/
int RVdelete_reservation(char *, int);

/*delete all reservations and free the memory*/
void RVdestroy();

/*Initialize and reserve memory for the ptrFlight arry*/
ptrFlight *FLinit();

/* Insert a flight in the ptrFlight array */
void FLinsert(ptrFlight, int);

/*Look for a flight in the ptrFlight array,
* with a given code and date,and return his ptrFlight*/
ptrFlight FLsearch_date(char *, Date, int);

/* Look for the first flight in the ptrFlight with 
* a certain code, and returns its index*/
int FLsearch(char *, int);

/*Delete a flight and all its reservations free the memory, 
* and rearrange the ptrFlight array*/
int FLdelete(char *, int);

/*Delete all flights and all its reservations, 
* and free the memory*/
void FLdestroy(int);