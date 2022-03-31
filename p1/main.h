#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#include "time.h"

#define MAX_AIRPORTS 40
#define MAX_FLIGHTS 30000
#define MAX_CITY_NAME 51
#define MAX_COUTRY_NAME 31
#define SIZE_AIRPORT_ID 4
#define MAX_SIZE_FLIGHT_CODE 7
#define MAX_CAPACITY 100
#define MIN_CAPACITY 10
#define FRIST_DAY 1
#define FRIST_MONTH 1
#define FRIST_YEAR 2022
#define TWELVE_HOURS_MINUTES 720

typedef struct Airport{
    char id[SIZE_AIRPORT_ID];
    char country[MAX_COUTRY_NAME];
    char city[MAX_COUTRY_NAME];
    int number_flights;
} Airport;

typedef struct Flight{
    char code[MAX_SIZE_FLIGHT_CODE];
    char ap_departure[SIZE_AIRPORT_ID];
    char ap_arrival[SIZE_AIRPORT_ID];
    int date;
    int hour;
    int duration;
    int capacity;
}Flight;

int add_airport(char id[], char country[], char city[]);

void print_all_airports(int counter);

void print_airport(char id[]);

void advance_date(int day, int month, int year);

void insert_airport_sorted(Airport key);

void print_all_flights();

int add_flight(Flight flight);

void print_flights_dp_airport(char ap[]);

void print_flights_ar_airport(char ap[]);

void merge(int arr[], int l, int m, int r);

void mergeSort(int arr[], int l, int r);