#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#include "RVtable.h"

void add_airport();

void print_airports();

void print_all_airports();

int verify_airport(char ap[]);

void print_one_airport(char id[]);

void insert_airport_sorted(Airport ap);

void flights_actions();

void print_all_flights();

int add_flight(ptrFlight flight);

void print_flights_dp_airport();

void print_flights_ar_airport();

void advance_date();

void command_r();

void command_e();