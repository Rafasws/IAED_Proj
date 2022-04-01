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
            case 'a':
                add_airport();
                break;
            case 'l':
                print_airports();
                break;
            case 'v':
                flights_actions();
                break;
            case 'p':
                print_flights_dp_airport();
                break;
            case 'c':
                print_flights_ar_airport();
                break;
            case 't':
                advance_date();
                break;
            case 'q':
                return 0;
            default :
                break;
        }
    }
}

void add_airport(){
    int i = 0;
    char newid[SIZE_AIRPORT_ID + 1], country[MAX_COUTRY_NAME + 1], city[MAX_CITY_NAME +1];
    scanf(" %s %s %[^\n]", newid, country, city);
    while(newid[i] != '\0'){
        if (newid[i] < 'A' || newid[i] > 'Z'){
            printf("invalid airport ID\n");
            return;
        }
        i++;
    }
    if(!(strlen(newid) == SIZE_AIRPORT_ID)){
        printf("invalid airport ID\n");
        return;
    }
    if(airports_counter >= MAX_AIRPORTS){
        printf("too many airports\n");
        return;
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
    return;
}

void print_all_airports(){
    int i;
    for(i = 0; i < airports_counter; i++){
        print_one_airport(airports[i].id);
    }
}

void print_airports(){
    char a, id[MAX_AIRPORTS][SIZE_AIRPORT_ID + 1];
    int i = 0;
    scanf("%c", &a);
    if(a == '\n'){
        print_all_airports();
    }
    else{
        while(a != '\n'){
            scanf("%s", id[i]);
            print_one_airport(id[i++]);
            scanf("%c", &a);
        }
    }
}

void print_one_airport(char id[]){
    int i;
    if((i = verify_airport(id)) == -1){
        printf("%s: no such airport ID\n", id);
    }
    else{
        printf("%s %s %s %d\n", airports[i].id, airports[i].city, 
        airports[i].country, airports[i].number_flights);
    }
}

void insert_airport_sorted(Airport ap){ 
    int i;

    for(i = airports_counter - 1; 
    (i >= 0 && (strcmp(ap.id,airports[i].id) < 0)); i--){
        airports[i + 1] = airports[i];
    }   
    airports[i + 1] = ap;
}

void flights_actions(){
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

}
int verify_airport(char ap[]){
    int i;
    for(i = 0; i < airports_counter; i++){
        if(!(strcmp(ap, airports[i].id))){
            break;
        }
    }
    if(!(i < airports_counter)){
        return -1;
    }
    return i;
}
int add_flight(Flight flight){

    int i = 0;
    if(strlen(flight.code) < 3|| strlen(flight.code) > MAX_SIZE_FLIGHT_CODE){
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
        else if(i == 2){
            if (flight.code[i] < '1' || flight.code[i] > '9'){
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
            printf("flight already exists\n");
            return -1;
        }
    }

    if(verify_airport (flight.ap_departure) == -1){
        printf("%s: no such airport ID\n", flight.ap_departure);
        return -1;
    }
    if(verify_airport (flight.ap_arrival) == -1){
        printf("%s: no such airport ID\n", flight.ap_arrival);
        return -1;
    }
    if(flights_counter == MAX_FLIGHTS){
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
    for(i = 0; i < airports_counter; i++){
        if(!(strcmp(flights[flights_counter].ap_departure, airports[i].id))){
            ++airports[i].number_flights;
            break;
        }
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

void print_flights_dp_airport(){
    int i, j = 0, k, w, arr[MAX_FLIGHTS], res[5];
    char ap[SIZE_AIRPORT_ID + 1];
    scanf(" %s", ap);
    if(verify_airport(ap) == -1){
        printf("%s: no such airport ID\n", ap);
    }
    for(i = 0; i < flights_counter; i++){
        if(!(strcmp(flights[i].ap_departure, ap))){
            arr[j++] = i;
        }
    }
    for (i = 1; i < j; i++) {
        k = arr[i];
        w = i - 1;
        while (w >= 0 && ((flights[arr[w]].hour + flights[arr[w]].date) > (flights[k].hour + flights[k].date))){
            arr[w + 1] = arr[w];
            w --;
        }
        arr[w + 1] = k;
    }
    for(i = 0; i < j; i++){
        int minutes =  flights[arr[i]].hour + flights[arr[i]].date;
        min_to_date(minutes, res);
        printf("%s %s %2.2d-%2.2d-%4.4d %2.2d:%2.2d\n", flights[arr[i]].code, 
        flights[arr[i]].ap_arrival, res[2], res[3], res[4], res[0], res[1]);
    }
}
void print_flights_ar_airport(){
    int i, j = 0, k, w, arr[MAX_FLIGHTS], res[5];
    char ap[SIZE_AIRPORT_ID + 1];
    scanf(" %s", ap);
    if(verify_airport(ap) == -1){
        printf("%s: no such airport ID\n", ap);
    }
    for(i = 0; i < flights_counter; i++){
        if(!(strcmp(flights[i].ap_arrival, ap))){
            arr[j++] = i;
        }
    }
    for (i = 1; i < j; i++) {
        k = arr[i];
        w = i - 1;
        while (w >= 0 && ((flights[arr[w]].hour + flights[arr[w]].date + flights[arr[w]].duration) > (flights[k].hour + flights[k].date + flights[k].duration))){
            arr[w + 1] = arr[w];
            w--;
        }
        arr[w + 1] = k;
    }  
    for(i = 0; i < j; i++){
        int minutes =  flights[arr[i]].hour + flights[arr[i]].date + flights[arr[i]].duration;
        min_to_date(minutes, res);
        printf("%s %s %2.2d-%2.2d-%4.4d %2.2d:%2.2d\n", flights[arr[i]].code, 
        flights[arr[i]].ap_departure, res[2], res[3], res[4], res[0], res[1]);
    }
}
void advance_date(){
    int day, month, year, time;
    scanf(" %d-%d-%d", &day, &month, &year);
    time = date_to_min(init_date, day, month, year);
    if(time == -1 || time > init_date + ONE_YEAR_MINUTES){
        printf("invalid date\n");
    }
    else{
        init_date = date_to_min(init_date, day, month, year);
        printf("%2.2d-%2.2d-%4.4d\n", day, month, year);
    }
}