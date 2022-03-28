#include<stdio.h>
#include <string.h>

#define MAX_AIRPORTS 40
#define MAX_FLIGHTS 30000
#define MAX_CITY_NAME 50
#define MAX_COUTRY_NAME 30



typedef struct Airport{
    char id[4];
    char country[MAX_COUTRY_NAME];
    char city[MAX_COUTRY_NAME];
} Airport;

void add_airport(char id[], char country[], char city[], Airport airports[], int counter);