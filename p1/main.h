#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#include "time.h"

#define MAX_AIRPORTS 40
#define MAX_FLIGHTS 30000
#define MAX_CITY_NAME 50
#define MAX_COUTRY_NAME 30
#define SIZE_AIRPORT_ID 3
#define MAX_SIZE_FLIGHT_CODE 6
#define MAX_CAPACITY 100
#define MIN_CAPACITY 10
#define TWELVE_HOURS_MINUTES 720

typedef struct Airport{
    char id[SIZE_AIRPORT_ID + 1];
    char country[MAX_COUTRY_NAME + 1];
    char city[MAX_COUTRY_NAME + 1];
    int number_flights;
} Airport;

typedef struct Flight{
    char code[MAX_SIZE_FLIGHT_CODE + 1];
    char ap_departure[SIZE_AIRPORT_ID + 1];
    char ap_arrival[SIZE_AIRPORT_ID + 1];
    int date;
    int hour;
    int duration;
    int capacity;
}Flight;

void add_airport();

void print_airports();

void print_all_airports();

int verify_airport(char ap[]);

void print_one_airport(char id[]);

void insert_airport_sorted(Airport ap);

void flights_actions();

void print_all_flights();

int add_flight(Flight flight);

void print_flights_dp_airport();

void print_flights_ar_airport();

void advance_date();