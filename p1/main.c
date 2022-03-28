#include "main.h"

Airport airports[MAX_AIRPORTS];

int airports_counter = 0;

int main(){

    char command;

    for(;;){
        scanf("%c", &command);

        switch(command){
            case 'a':{
                char id[4], country[MAX_COUTRY_NAME], city[MAX_CITY_NAME];
                scanf(" %s %s %[^\n]", id, country, city);
                add_airport(id, country, city, airports, airports_counter);
                break;
            }
            case 'l':
            case 'v':
            case 'p':
            case 'c':
            case 't':
            case 'q':
                return 0;
            default :
                break;
        }
    }
}

void add_airport(char id[], char country[], char city[], Airport airports[], int counter){
    if(counter >= MAX_AIRPORTS){
        printf("too many airports");
    }
    strcpy(airports[counter].id, id);
    strcpy(airports[counter].country, country);
    strcpy(airports[counter].city, city);
    printf("airport %s\n", airports[airports_counter++].id);
}