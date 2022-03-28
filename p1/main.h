#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX_AIRPORTS 40
#define MAX_FLIGHTS 30000
#define MAX_CITY_NAME 50
#define MAX_COUTRY_NAME 30
#define SIZE_AIRPORT_ID 4

typedef struct Date{
    int day;
    int month;
    int year;
} Date;

typedef struct Hour{
    int hours;
    int minutes;
} Hour;

typedef struct Airport{
    char id[SIZE_AIRPORT_ID];
    char country[MAX_COUTRY_NAME];
    char city[MAX_COUTRY_NAME];
} Airport;

void add_airport(char id[], char country[], char city[], Airport airports[]);

void print_all_airports(int counter);

void print_airport(char id[]);

void advance_date(int day, int month, int year);