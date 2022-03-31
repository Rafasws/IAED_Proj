#include "main.h"

Airport airports[MAX_AIRPORTS];
Flight flights[MAX_FLIGHTS];
int airports_counter = 0;
int flights_counter = 0;
int init_date = 0;

int main(){
    char command;

    for(;;){
        scanf("%c", &command);

        switch(command){
            case 'a':{
                char id[SIZE_AIRPORT_ID], country[MAX_COUTRY_NAME];
                char city[MAX_CITY_NAME];
                scanf(" %s %s %[^\n]", id, country, city);
                if(add_airport(id, country, city) == 0){
                    airports_counter++;
                }
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
                char a;
                int day, month, year, hours, minutes, dt_hours, dt_minutes;
                Flight flight;

                scanf("%c", &a);
                if(a == '\n'){
                    print_all_flights();
                }
                else{
                    scanf(" %s %s %s %d-%d-%d %d:%d %d:%d %d", 
                    flight.code, flight.ap_departure, flight.ap_arrival, 
                    &day, &month, &year, &hours, &minutes, &dt_hours, 
                    &dt_minutes, &flight.capacity);
                    flight.date = date_to_min(init_date, day, month, year);
                    flight.hour = duration_to_min(hours, minutes);
                    flight.duration = duration_to_min(dt_hours, dt_minutes);
                    if(add_flight(flight) == 0){
                        flights_counter++;
                    }
                }
                break;
            }
            case 'p':{/*
                char ap[SIZE_AIRPORT_ID];
                print_flights_dp_airport(ap);
                break;*/
            }
            case 'c':{/*
                char ap[SIZE_AIRPORT_ID];
                print_flights_ar_airport(ap);*/
                break;
            }
            case 't':{
                int day, month, year;
                scanf(" %d-%d-%d", &day, &month, &year);
                if(date_to_min(init_date, day, month, year) == -1){
                    printf("invalid date\n");
                }
                else{
                    init_date = date_to_min(init_date, day, month, year);
                    printf("%2.2d-%2.2d-%4.4d\n", day, month, year);
                }
                break;
            }
            case 'q':
                return 0;
            default :
                break;
        }
    }
}

int add_airport(char newid[], char country[], char city[]){
    int i = 0;
    while(newid[i] != '\0'){
        if (newid[i] < 'A' || newid[i] > 'Z'){
            printf("invalid airport ID\n");
            return -1;
        }
        i++;
    }
    if(airports_counter >= MAX_AIRPORTS){
        printf("too many airports\n");
        return -1;
    }
    for(i = 0; i < airports_counter; i++){
        if(!(strcmp(newid, airports[i].id))){
            printf("duplicate airport\n");
            return -1;
        }
    }
    strcpy(airports[airports_counter].id, newid);
    strcpy(airports[airports_counter].country, country);
    strcpy(airports[airports_counter].city, city);
    airports[airports_counter].number_flights = 0;
    printf("airport %s\n", airports[airports_counter].id);
    insert_airport_sorted(airports[airports_counter]);
    return 0;
}

void print_all_airports(int counter){
    int i;
    for(i = 0; i < counter; i++){
        print_airport(airports[i].id);
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

void insert_airport_sorted(Airport ap){ 
    int i;

    for(i = airports_counter - 1; 
    (i >= 0 && (strcmp(ap.id,airports[i].id) < 0)); i--){
        airports[i + 1] = airports[i];
    }   
    airports[i + 1] = ap;
}

int add_flight(Flight flight){

    int i = 0;
    if(strlen(flight.code) > 6){
        printf("invalid flight code\n");
            return -1;
    }
    while(flight.code[i] != '\0'){
        if(i == 0 || i == 1){
            if (flight.code[i] < 'A' || flight.code[i] > 'Z'){
                printf("invalid flight code\n");
                return -1;
            }
        }
        else{
            if (flight.code[i] < '0' || flight.code[i] > '9'){
                printf("invalid flight code\n");
                return -1;
            }
        }
        i++;
    }
    
    for(i = 0; i < flights_counter; i++){
        if(!(strcmp(flight.code, flights[i].code)) 
        && flight.date == flights[i].date){
            printf("flight alredy exists\n");
            return -1;
        }
    }
    for(i = 0; i < airports_counter; i++){
        if(!(strcmp(flight.ap_departure, airports[i].id))){
            break;
        }
    }
    if(!(i < airports_counter)){
        printf("%s: no such airport ID\n", flight.ap_departure);
        return -1;
    }
    for(i = 0; i < airports_counter; i++){
        if(!(strcmp(flight.ap_arrival, airports[i].id))){
            break;
        }
    }
    if(!(i < airports_counter)){
        printf("%s: no such airport ID\n", flight.ap_arrival);
        return -1;
    }
    if(flights_counter >= MAX_FLIGHTS){
        printf("too many flights\n");
        return -1;
    }
    if(flight.date == -1){
        printf("invalid date\n");
        return -1;
    }
    if(flight.duration > TWELVE_HOURS_MINUTES ){
        printf("invalid duration\n");
        return -1;
    }
    if(flight.capacity > MAX_CAPACITY && flight.capacity < MIN_CAPACITY){
        printf("invalid capacity\n");
        return -1;
    }
    strcpy(flights[flights_counter].code, flight.code);
    strcpy(flights[flights_counter].ap_departure, flight.ap_departure);
    strcpy(flights[flights_counter].ap_arrival, flight.ap_arrival);
    flights[flights_counter].date = flight.date;
    flights[flights_counter].hour = flight.hour;
    flights[flights_counter].duration = flight.duration;
    flights[flights_counter].capacity = flight.capacity;
    return 0;
}

void print_all_flights(){
    int i;
    int res[5];
    for(i = 0; i < flights_counter; i++){
        min_to_date((flights[i].date + flights[i].hour), res);
        printf("%s %s %s %2.2d-%2.2d-%2.2d %2.2d:%2.2d\n", flights[i].code,
        flights[i].ap_departure, flights[i].ap_arrival, res[2], res[3], res[4],
        res[0], res[1]);
    }
}

void print_flights_dp_airport(char ap[]){
    int i, j = 0;
    int flights_dp_airport[MAX_FLIGHTS];
    for(i = 0; i < flights_counter; i++){
        if(!(strcmp(flights[i].ap_departure, ap))){
            flights_dp_airport[j++] = flights[i].date + flights[i].hour;
        }
    }
    mergeSort(flights_dp_airport, 0, j);
    for(i = 0; i < j; i++){
        /*printf("%s %s %2.2d:%2.2d %2.2d-%2.2d-%4.4d",);*/
    }
}
void print_flights_ar_airport(char ap[]){
    int i, j = 0;
    int flights_ar_airport[MAX_FLIGHTS];
    for(i = 0; i < flights_counter; i++){
        if(!(strcmp(flights[i].ap_arrival, ap))){
            flights_ar_airport[j++] = flights[i].date + flights[i].hour;
        }
    }
    mergeSort(flights_ar_airport, 0, j);
    for(i = 0; i < j; i++){
        /*printf("%s %s %2.2d:%2.2d %2.2d-%2.2d-%4.4d",);*/
    }
}
void merge(int arr[], int l, int m, int r){
    int i, j, k;
    int left[m - l + 1], right[r - m];
    
  
    
  
    for (i = 0; i < n1; i++)
        left[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        right[j] = arr[m + 1 + j];

    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = left[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = right[j];
        j++;
        k++;
    }
}
void mergeSort(int arr[], int l, int r){
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
  
        merge(arr, l, m, r);
    }
}
void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}
/*int main()
{
    int arr[] = { 12, 11, 13, 5, 6, 7 };
    int arr_size = sizeof(arr) / sizeof(arr[0]);
  
    printf("Given array is \n");
    printArray(arr, arr_size);
  
    mergeSort(arr, 0, arr_size - 1);
  
    printf("\nSorted array is \n");
    printArray(arr, arr_size);
    return 0;
}*/