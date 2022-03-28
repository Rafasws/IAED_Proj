#include "main.h"

Airport airports[MAX_AIRPORTS];
int airports_counter = 0;
Date d;

int main(){
    char command;
    
    d.day = 1;
    d.month = 1; 
    d.year = 2022;

    for(;;){
        scanf("%c", &command);

        switch(command){
            case 'a':{
                char id[SIZE_AIRPORT_ID], country[MAX_COUTRY_NAME];
                char city[MAX_CITY_NAME];
                scanf(" %s %s %[^\n]", id, country, city);
                add_airport(id, country, city, airports);
                break;
            }
            case 'l':{
                char a[SIZE_AIRPORT_ID];
            /*imprimir apenas os aeroportos pedidos*/
                while(scanf("%s",a) == 1){
                    print_airport(a);
                }
                print_all_airports(airports_counter);
                break;
            }
            case 'v':
            case 'p':
            case 'c':
            case 't':{
                int day, month, year;
                scanf(" %d-%d-%d", &day, &month, &year);
                advance_date(day, month, year);
                break;
            }
            case 'q':
                return 0;
            default :
                break;
        }
    }
}

void add_airport(char id[], char country[], char city[], Airport airports[]){
    int i = 0;
    if(airports_counter >= MAX_AIRPORTS){
        printf("too many airports\n");
        return;
    }

    while(id[i] != '\0'){
        if (id[i] < 'A' || id[i] > 'Z'){
            printf("invalid airport ID\n");
            return;
        }
        i++;
    }
    for(i = 0; i < airports_counter; i++){
        if(!(strcmp(id, airports[i].id))){
            printf("duplicate airport\n");
            return;
        }
    }
    strcpy(airports[airports_counter].id, id);
    strcpy(airports[airports_counter].country, country);
    strcpy(airports[airports_counter].city, city);
    /*Algoritmo de ordenação por ordem alfabética*/
    printf("airport %s\n", airports[airports_counter++].id);
}

void print_all_airports(int counter){
    int i;
    for(i = 0; i < counter; i++){
        printf("%s %s %s\n", airports[i].id, airports[i].city, 
        airports[i].country);
    }
}

void print_airport(char id[]){
    int i;
    for(i = 0; i < airports_counter; i++){
        if(!(strcmp(id, airports[airports_counter].id))){
            printf("%s %s %s\n", airports[i].id, airports[i].city, 
            airports[i].country);
        }
    }
    printf("%s: no such airport ID", id);
}

void advance_date(int day, int month, int year){
    d.day = day;
    d.month = month;
    d.year = year;
    printf("%2.2d-%2.2d-%4.4d\n", d.day, d.month, d.year);
    /*condições de paragem de avanço de data*/
}