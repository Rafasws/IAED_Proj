/*
 * File: main.h
 *
 * Author: Rafael Gaspar Ferreira (ist197342)
 * E-mail: rafael.gaspar@tecnico.ulisboa.pt
 *
 * Description:
 * The goal of this project is the development of
 * a flights management system in the C programming language.
 * This file provides the used librarys, all macros, the defenition of new 
 * structs and the prototypes of the functions.
 *
 * This is project 1 for subject IAED of course LEIC-T.
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

/* Maximum number of airports in the system. */
#define MAX_AIRPORTS 40

/* Maximum number of flights the system. */
#define MAX_FLIGHTS 30000

/* Maximum size of the city name. */
#define MAX_CITY_NAME 50

/* Maximum size of the country name. */
#define MAX_COUTRY_NAME 30

/* Maximum size of the airport identifier. */
#define SIZE_AIRPORT_ID 3

/* Maximum size of the flight code. */
#define SIZE_FLIGHT_CODE 6

/* Maximum capacity of the flight. */
#define MAX_CAPACITY 100

/* Minimum capacity of the flight */
#define MIN_CAPACITY 10

/* New type that represents Dates */
typedef struct Date{
    int day;
    int month;
    int year;
} Date;

/* New type that represents Time */
typedef struct Time{
    int hour;
    int minute;
}  Time;

/* New type that represents Airports */
typedef struct Airport{
    char id[SIZE_AIRPORT_ID + 1];
    char country[MAX_COUTRY_NAME + 1];
    char city[MAX_CITY_NAME + 1];
    int number_flights;
} Airport;

/* New type that represents Flights */
typedef struct Flight{
    char code[SIZE_FLIGHT_CODE + 1];
    char ap_departure[SIZE_AIRPORT_ID + 1];
    char ap_arrival[SIZE_AIRPORT_ID + 1];
    Date date;
    Time hours;
    Time duration;
    int capacity;
}Flight;

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
void add_flight(Flight flight);

/* Implements the 'p' command, that lists the flights whith a departure
* in a certain airport.
*/
void command_p();

/* Implements the 'c' command, that lists the flights whith a 
certain arrival airport.
*/
void command_c();

/* Verify if a certain airport exist in the system,
* and reurn his index in the array.
*/
int exist_airport(char ap[]);

/* Verify the input of the command_v*/
int verify_input_cmd_v(Flight flight);

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

/* Check if exist a flight whith a certain code
*retrun 0 if exist and -1 if not.
*/
int existent_flight(Flight flight);

/* Calculate the date and time of the arrival */
Flight new_date(Flight f);

/* Implements the 't' command, that advance the date*/
void comm();