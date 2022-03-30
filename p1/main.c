#include "main.h"

Airport airports[MAX_AIRPORTS];
Flight flights[MAX_FLIGHTS];
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
                add_airport(id, country, city);
                break;
            }
            case 'l':{
                char a, id[MAX_AIRPORTS][SIZE_AIRPORT_ID];
                int i;
                scanf("%c", &a);
                if(a == '\n'){
                    print_all_airports(airports_counter);
                }
                else{
                    while(a != '\n'){
                        scanf("%s", id[i]);
                        print_airport(id[i++]);
                        scanf("%c", &a);
                    }
                }
                break;
            }
            case 'v':{
                
            }
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

void add_airport(char newid[], char country[], char city[]){
    int i = 0;
    if(airports_counter >= MAX_AIRPORTS){
        printf("too many airports\n");
        return;
    }

    while(newid[i] != '\0'){
        if (newid[i] < 'A' || newid[i] > 'Z'){
            printf("invalid airport ID\n");
            return;
        }
        i++;
    }
    for(i = 0; i < airports_counter; i++){
        if(!(strcmp(newid, airports[i].id))){
            printf("duplicate airport\n");
            return;
        }
    }
    strcpy(airports[airports_counter].id, newid);
    strcpy(airports[airports_counter].country, country);
    strcpy(airports[airports_counter].city, city);
    airports[airports_counter].number_flights = 0;
    printf("airport %s\n", airports[airports_counter].id);
    insert_airport_sorted(airports[airports_counter]);
    airports_counter++;
}

void print_all_airports(int counter){
    int i;
    for(i = 0; i < counter; i++){
        printf("%s %s %s %d\n", airports[i].id, airports[i].city, 
        airports[i].country, airports[i].number_flights);
    }
}

void print_airport(char id[]){
    int i;
    for(i = 0; i < airports_counter; i++){
        if(!(strcmp(id, airports[i].id))){
            printf("%s %s %s %d\n", airports[i].id, airports[i].city, 
            airports[i].country, airports[i].number_flights);
            return;
        }
    }
    printf("%s: no such airport ID\n", id);
}

void advance_date(int day, int month, int year){
    d.day = day;
    d.month = month;
    d.year = year;
    printf("%2.2d-%2.2d-%4.4d\n", d.day, d.month, d.year);
    /*condições de paragem de avanço de data*/
}

void insert_airport_sorted(Airport ap){ 
    int i;

    for(i = airports_counter - 1; 
    (i >= 0 && (strcmp(ap.id,airports[i].id) < 0)); i--){
        airports[i + 1] = airports[i];
    }
        
    airports[i + 1] = ap;
}