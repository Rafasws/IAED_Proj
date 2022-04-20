/*
 * File: types.h
 *
 * Author: Rafael Gaspar Ferreira (ist197342)
 * E-mail: rafael.gaspar@tecnico.ulisboa.pt
 *
 * Description:
 * The goal of this project is the development of
 * a flights management system in the C programming language.
 * This file provides the used librarys, all macros,and the defenition of new 
 * structs.
 *
 * This is project 2 for subject IAED of course LEIC-T.
 */

/* Maximum number of airports in the system. */
#define MAX_AIRPORTS 40

/* Maximum number of flights the system. */
#define MAX_FLIGHTS 30

/* Maximum size of the city name. */
#define MAX_CITY_NAME 50

/* Maximum size of the country name. */
#define MAX_COUTRY_NAME 30

/* Maximum size of the airport identifier. */
#define SIZE_AIRPORT_ID 3

/* Maximum size of the flight code. */
#define SIZE_FLIGHT_CODE 6

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

/* New type that represents Reservations */
typedef struct Reservation{

   char *reservation_code;
   Date date;
   char *flight_code;
   int number_passangers;

}*ptrReservation;/* Data type that is a pointer to a struct Reservation */

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
    int quantity;
    int n_reserves;
    ptrReservation *reservations;
}*ptrFlight;

