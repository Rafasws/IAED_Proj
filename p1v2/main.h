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
#define SIZE_FLIGHT_CODE 6
#define MAX_CAPACITY 100
#define MIN_CAPACITY 10

typedef struct Date{
    int day;
    int month;
    int year;
} Date;
typedef struct Time{
    int hour;
    int minute;
}  Time;
typedef struct Airport{
    char id[SIZE_AIRPORT_ID + 1];
    char country[MAX_COUTRY_NAME + 1];
    char city[MAX_COUTRY_NAME + 1];
    int number_flights;
} Airport;
typedef struct Flight{
    char code[SIZE_FLIGHT_CODE + 1];
    char ap_departure[SIZE_AIRPORT_ID + 1];
    char ap_arrival[SIZE_AIRPORT_ID + 1];
    Date date;
    Time hours;
    Time duration;
    int capacity;
}Flight;

void command_a();

int verify_input_cmd_a(char id[]);

void insert_airport_sorted(Airport ap);

void add_airport(char id[], char country[], char city[]);

void command_l();

void print_all_airports();

void print_one_airport(char id[]);

void command_v();

void print_all_flights();

void add_flight(Flight flight);

void command_p();

void command_c();

int exist_airport(char ap[]);

int verify_input_cmd_v(Flight flight);

int verify_flight_code(char code[]);

int equal_dates(Date date1,Date date2);

int equal_time(Time h1, Time h2);

int verify_date(Date date);

int existent_flight(Flight flight);

Flight new_date(Flight f);

void comm();