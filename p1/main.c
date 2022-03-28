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
                add_airport(id, country, city, airports, airports_counter++);
                break;
            }
            case 'l':
                print_all_airports(airports_counter);
                break;
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
void add_airport(char id[], char country[], char city[], Airport airports[], 
int counter){
    int i = 0;
    if(counter >= MAX_AIRPORTS){
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
    for(i = 0; i < counter; i++){
        if(!(strcmp(id, airports[i].id))){
            return;
        }
    }
    strcpy(airports[counter].id, id);
    strcpy(airports[counter].country, country);
    strcpy(airports[counter].city, city);
    /*Algoritmo de ordenação por ordem alfabética*/
    printf("airport %s\n", airports[counter].id);
}
void print_all_airports(int counter){
    int i;
    for(i = 0; i < counter; i++){
        printf("%s %s %s\n", airports[i].id, airports[i].city, 
        airports[i].country);
    }
}