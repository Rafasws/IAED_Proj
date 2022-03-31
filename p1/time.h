#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define ONE_YEAR_MINUTES 525600

int date_to_min(int date, int day, int month, int year);

int duration_to_min(int hour, int minutes);

void min_to_date(int minutes, int res[]);