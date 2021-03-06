/*
 * File: main.h
 *
 * Author: Rafael Gaspar Ferreira (ist197342)
 * E-mail: rafael.gaspar@tecnico.ulisboa.pt
 *
 * Description:
 * The goal of this project is the development of
 * a flights management system in the C programming language.
 * This file provides the prototypes of the functions.
 *
 * This is project 1 for subject IAED of course LEIC-T.
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "RVtable.h"

/* Implements the 'a' command, that adds a new airport to the system.*/
void command_a();

/* Verify the input of the command_a*/
int verify_input_cmd_a(char id[]);

/* Use the insertion sort to mantain the airports in th system, 
* in alphabetic order. 
*/
void insert_airport_sorted(Airport ap);

/*add a airport to the system*/
void add_airport(char id[], char country[], char city[]);

/* Implements the 'l' command that lists all airpots in the system.*/
void command_l();

/* Print all all airport in the system*/
void print_all_airports();

/* Print a airport with certain identifier*/
void print_one_airport(char id[]);

/* Implements the 'v' command, that either adds a new flight to the system,
 * or lists all flights in the system.
 */
void command_v();

/* Print all flights in the system. */
void print_all_flights();

/* Add a flight to the system*/
void add_flight(ptrFlight flight);

/* Implements the 'p' command, that lists the flights whith a departure
* in a certain airport.
*/
void command_p();

/* Implements the 'c' command, that lists the flights whith a 
* certain arrival airport.
*/
void command_c();

/* Verify if a certain airport exist in the system,
* and reurn his index in the array.
*/
int exist_airport(char ap[]);

/* Verify the input of the command_v*/
int verify_input_cmd_v(ptrFlight flight);

/* Verify if a flight code is valid*/
int verify_flight_code(char code[]);

/* Compare two Date, return 0 if the date1 == date2
* return 1 if date1 > date2, and return -1 if
* date1 < date2.
*/
int equal_dates(Date date1,Date date2);

/* Compare two Times, return 0 if the h1 == h2
* return 1 if h1 > h2, and return -1 if
* h1 < h2.
*/
int equal_time(Time h1, Time h2);

/* Check if the date is valid*/
int verify_date(Date date);

/* Calculate the date and time of the arrival */
struct Flight new_date(ptrFlight f);

/* Implements the 't' command, that advance the date*/
void comm();

ptrFlight existent_flight_date_code(char *, Date);

/* Implements the 'r' command, that either adds a new reservation to the system,
 * or lists the certain flights reservations.
 */
void command_r();

/* Read a string from the standart input with unknown length,  dynamically
 * allocates required memory and return a pointer to to that memory space.
 */
char *read_reservation_code();

/* Implements the 'e' command, that either remove a reservation of the system,
 * or remove certain flight and all his reservationsof the system.
 */
void command_e();

/* Verify if a reservation code is valid*/
int verify_reservation_code(char *);

/*Add a airport to the system*/
void add_reservation(ptrFlight, Date, char *, int);

/* Verify the input of the command_r*/
int verify_input_cmd_r(ptrFlight,char *, Date, char *, int);

/*Prints flight reservations saved in th ptrFlight */
void print_reservations(ptrFlight);

/* The next and last 3 functions, it's part of the sort algorithm used
* in the project. 
 */
void quickSort(ptrReservation *arr, int low, int high);

void swap(ptrReservation *a, ptrReservation *b);

int partition (ptrReservation *arr, int low, int high);