/*
 * File: main.c
 *
 * Author: Rafael Gaspar Ferreira (ist197342)
 * E-mail: rafael.gaspar@tecnico.ulisboa.pt
 *
 * Description:
 * The goal of this project is the development of
 * a flights management system in the C programming language.
 *
 * This is project 1 for subject IAED of course LEIC-T.
 */
#include "main.h"

/* Array of structures that represent the airports in the system, 
* in alphabetic order. */
Airport airports[MAX_AIRPORTS];

/* Array of structures that represent the flights in the system, 
* in order of creation. */
ptrFlight *flights;

/* The number of airports currently being stored in the system. */
int airports_counter = 0;

/* The number of flights currently being stored in the system. */
int flights_counter = 0;

/* Current date in the system*/
Date init_date;

/* Reads a char, and call the function of the command. */
int main(){
    char command;
    RVinit(11);
    flights = FLinit();
    init_date.day = 1;
    init_date.month = 1;
    init_date.year = 2022;
    for(;;){
        scanf("%c", &command);
        switch(command){
            case 'q':
                RVdestroy();
                FLdestroy(flights_counter);
                return 0;
            case 'a':
                command_a();
                break;
            case 'l':
                command_l();
                break;
            case 'v':
                command_v();
                break;
            case 'p':
                command_p();
                break;
            case 'c':
                command_c();
                break;
            case 't':
                comm();
                break;
            case 'r':
                command_r();
                break;
            case 'e':
                command_e();
                break;
            default :
                break;
        }
    }
}

void command_a(){
    char id[SIZE_AIRPORT_ID + 1];
    char country[MAX_COUTRY_NAME + 1], city[MAX_CITY_NAME +1];
    scanf("%s %s %[^\n]s", id, country, city);
    if(verify_input_cmd_a(id) == -1){
        return;
    }
    add_airport(id, country, city);

}
void command_l(){
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
void command_v(){
    char a;
    ptrFlight flight;
    scanf("%c", &a);
    if(a == '\n'){
        print_all_flights();
    }
    else{
        flight = (ptrFlight) malloc(sizeof(struct Flight));
        if(flight == NULL){
            printf("No memory.\n");
            free(flight);
            RVdestroy();
            FLdestroy(flights_counter);
            exit(0);
        }
        scanf("%s %s %s %d-%d-%d %d:%d %d:%d %d", 
        flight->code, flight->ap_departure, flight->ap_arrival, 
        &flight->date.day, &flight->date.month, &flight->date.year, 
        &flight->hours.hour, &flight->hours.minute, &flight->duration.hour, 
        &flight->duration.minute, &flight->capacity);
        if(verify_input_cmd_v(flight) == -1){
            free(flight);
            return;
        }
        add_flight(flight);
    }
}
void command_p(){
    int i, j, k, len = 0;
    char ap[SIZE_AIRPORT_ID + 1];
    int f[MAX_FLIGHTS];
    scanf(" %s", ap);
    if(exist_airport(ap) == -1){
        printf("%s: no such airport ID\n", ap);
        return;
    }
    for(i = 0; i < flights_counter; i++){
        if(flights[i] != NULL){
            if(!(strcmp(flights[i]->ap_departure, ap))){
                f[len++] = i;
            }
        }
    }
    for (j = 0; j < len - 1; ++j) {
        for (i = 0; i < len - j - 1; ++i) {
            if (equal_dates(flights[f[i]]->date, flights[f[i+1]]->date) > 0) {
                k = f[i];
                f[i] = f[i + 1];
                f[i + 1] = k;
            }
            else if(equal_dates(flights[f[i]]->date,flights[f[i+1]]->date)==0){
                if(equal_time(flights[f[i]]->hours,flights[f[i+1]]->hours)>0){
                    k = f[i];
                    f[i] = f[i + 1];
                    f[i + 1] = k;
                }
            }
        }
    }
    for(i = 0; i < len; i++){
        printf("%s %s %2.2d-%2.2d-%4.4d %2.2d:%2.2d\n", flights[f[i]]->code, 
        flights[f[i]]->ap_arrival, flights[f[i]]->date.day,
        flights[f[i]]->date.month, flights[f[i]]->date.year, 
        flights[f[i]]->hours.hour, flights[f[i]]->hours.minute);
    }
}
void command_c(){
    int i, j, len = 0;
    char ap[SIZE_AIRPORT_ID + 1];
    struct Flight k, f[MAX_FLIGHTS];
    scanf(" %s", ap);
    if(exist_airport(ap) == -1){
        printf("%s: no such airport ID\n", ap);
        return;
    }
    for(i = 0; i < flights_counter; i++){
        if(flights[i] != NULL){
            if(!(strcmp(flights[i]->ap_arrival, ap))){
                f[len] = new_date(flights[i]);
                len++;
            }
        }
    }
    for (j = 0; j < len - 1; ++j) {
        for (i = 0; i < len - j - 1; ++i) {
            if (equal_dates(f[i].date, f[i+1].date) > 0) {
                k = f[i];
                f[i] = f[i + 1];
                f[i + 1] = k;
            }
            else if(equal_dates(f[i].date, f[i+1].date) == 0){
                if(equal_time(f[i].hours, f[i+1].hours) > 0){
                    k = f[i];
                    f[i] = f[i + 1];
                    f[i + 1] = k;
                }
            }
        }
    }

    for(i = 0; i < len; i++){
        printf("%s %s %2.2d-%2.2d-%4.4d %2.2d:%2.2d\n", f[i].code, 
        f[i].ap_departure, f[i].date.day, f[i].date.month, f[i].date.year, 
        f[i].hours.hour, f[i].hours.minute);
    }
}
void comm(){
    int day, month, year;
    Date d;
    scanf(" %d-%d-%d", &day, &month, &year);
    d.day = day;
    d.month = month;
    d.year = year;
    if(verify_date(d) == -1){
        printf("invalid date\n");
        return;
    }
    init_date.day = d.day;
    init_date.month = d.month;
    init_date.year = d.year;
    printf("%2.2d-%2.2d-%4.4d\n", init_date.day, init_date.month, 
    init_date.year);
}
int verify_input_cmd_a(char id[]){
    int i = 0;
    if(strlen(id) != SIZE_AIRPORT_ID){
        printf("invalid airport ID\n");
        return -1;
    }
    
    while(id[i] != '\0'){
        if (id[i] < 'A' || id[i] > 'Z'){
            printf("invalid airport ID\n");
            return -1;
        }
        i++;
    }
    if(airports_counter == MAX_AIRPORTS){
        printf("too many airports\n");
        return -1;
    }
    for(i = 0; i < airports_counter; i++){
        if(!(strcmp(id, airports[i].id))){
            printf("duplicate airport\n");
            return -1;
        }
    }
    return 0;
}
int verify_input_cmd_v(ptrFlight flight){
    if(verify_flight_code(flight->code) == -1){
        printf("invalid flight code\n");
        return -1;
    }
    if(FLsearch_date(flight->code, flight->date, flights_counter) != NULL){
        printf("flight already exists\n");
        return -1;
    }
    if(exist_airport(flight->ap_departure) == -1){
        printf("%s: no such airport ID\n", flight->ap_departure);
        return -1;
    }
    if(exist_airport(flight->ap_arrival) == -1){
        printf("%s: no such airport ID\n", flight->ap_arrival);
        return -1;
    }
    if(flights_counter >= MAX_FLIGHTS){
        printf("too many flights\n");
        return -1;
    }
    if(verify_date(flight->date) == -1){
        printf("invalid date\n");
        return -1;
    }
    if(flight->duration.hour >= 12){
        if(flight->duration.hour == 12 && flight->duration.minute > 0){
            printf("invalid duration\n");
            return -1;
        }
        else if(flight->duration.hour > 12){
            printf("invalid duration\n");
            return -1;
        }
    }
    if(flight->capacity < MIN_CAPACITY){
        printf("invalid capacity\n");
        return -1;
    }
    return 0;
}

void insert_airport_sorted(Airport ap){ 
    int i;

    for(i = airports_counter - 1; 
    (i >= 0 && (strcmp(ap.id,airports[i].id) < 0)); i--){
        airports[i + 1] = airports[i];
    }   
    airports[i + 1] = ap;
}
void add_airport(char id[], char country[], char city[]){
    strcpy(airports[airports_counter].id, id);
    strcpy(airports[airports_counter].country, country);
    strcpy(airports[airports_counter].city, city);
    airports[airports_counter].number_flights = 0;
    printf("airport %s\n", airports[airports_counter].id);
    insert_airport_sorted(airports[airports_counter]);
    airports_counter++;
}
void print_all_airports(){
    int i;
    for(i = 0; i < airports_counter; i++){
        print_one_airport(airports[i].id);
    }
}
void print_one_airport(char id[]){
    int i;
    if((i = exist_airport(id)) == -1){
        printf("%s: no such airport ID\n", id);
    }
    else{
        printf("%s %s %s %d\n", airports[i].id, airports[i].city, 
        airports[i].country, airports[i].number_flights);
    }
}
int exist_airport(char ap[]){
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
void print_all_flights(){
    int i;
    for(i = 0; i < flights_counter; i++){
        if(flights[i] != NULL){
            printf("%s %s %s %2.2d-%2.2d-%2.2d %2.2d:%2.2d\n", 
            flights[i]->code, flights[i]->ap_departure, flights[i]->ap_arrival,
            flights[i]->date.day, flights[i]->date.month, flights[i]->date.year,
            flights[i]->hours.hour, flights[i]->hours.minute); 
        }
    }
}
void add_flight(ptrFlight flight){
    int i;
    flight->quantity = 0;
    flight->n_reserves = 0;
    flight->reservations = (ptrReservation *)malloc(sizeof(ptrReservation)* 
    flight->capacity);
    if(flight->reservations == NULL){
        printf("No memory.\n");
        free(flight->reservations);
        free(flight);
        RVdestroy();
        FLdestroy(flights_counter);
        exit(0);
    }
    for(i = 0; i < flight->capacity; i++){
        flight->reservations[i] = NULL;
    }
    airports[exist_airport(flight->ap_departure)].number_flights++;
    FLinsert(flight, flights_counter);
    flights_counter++;
}
int verify_flight_code(char code[]){
    int i = 0;
    if(strlen(code) < 3|| strlen(code) > SIZE_FLIGHT_CODE){
        return -1;
    }
    while(code[i] != '\0'){
        if(i == 0 || i == 1){
            if (code[i] < 'A' || code[i] > 'Z'){
                return -1;
            }
        }
        else if(i == 2){
            if (code[i] < '1' || code[i] > '9'){
                return -1;
            }
        }
        else{
            if (code[i] < '0' || code[i] > '9'){
                return -1;
            }
        }
        i++;
    }
    return 0; 
}
int verify_date(Date date){
    int res = equal_dates(date, init_date);
    Date newdate;
    newdate.day = init_date.day;
    newdate.month = init_date.month;
    newdate.year = init_date.year + 1;
    if(res == -1){
        return -1;
    }
    else if(res == 0){
        return 0;
    }
    else{
        if(equal_dates(date, newdate) == 1){
            return -1;
        }
        else{
            return 0;
        }
    }
}
int equal_dates(Date date1,Date date2){
    if(date1.year > date2.year){
        return 1;
    }
    else if(date1.year < date2.year){
        return -1;
    }
    else{
        if(date1.month > date2.month){
        return 1;
        }
        else if(date1.month < date2.month){
            return -1;
        }
        else{
            if(date1.day > date2.day){
                return 1;
            }
            else if(date1.day < date2.day){
                return -1;
            }
            else{
                return 0;
            }

        }
    }
}
int existent_flight(ptrFlight flight){
    int i;
    for(i = 0; i < (2 * MAX_FLIGHTS); i++){
        if(flights[i] != NULL){
            if(!(strcmp(flight->code, flights[i]->code)) && 
            (equal_dates(flight->date, flights[i]->date) == 0)){
                return -1;
            }
        }
    }
    return 0;
}
int equal_time(Time h1, Time h2){
    if(h1.hour > h2.hour){
        return 1;
    }
    else if(h1.hour < h2.hour){
        return -1;
    }
    else{
        if(h1.minute > h2.minute){
            return 1;
        }
        else if(h1.minute < h2.minute){
            return -1;
        }
        else{
            return 0;
        }
    }
}
struct Flight new_date(ptrFlight f){
    int d = 0;
    int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    struct Flight newflight;
    strcpy(newflight.code, f->code);
    strcpy(newflight.ap_departure, f->ap_departure);
    newflight.date.day = f->date.day;
    newflight.date.month = f->date.month;
    newflight.date.year = f->date.year;
    newflight.hours.hour = f->hours.hour;
    newflight.hours.minute = f->hours.minute;

    if((newflight.hours.minute+= f->duration.minute) >= 60){
        newflight.hours.minute %= 60;
        newflight.hours.hour++;
    }
    if((newflight.hours.hour+= f->duration.hour) >= 24){
        newflight.hours.hour %= 24;
        d++;
    }
    if(d != 0){
        if((newflight.date.day+=1) > days[newflight.date.month]){
            newflight.date.day = 1;
            newflight.date.month++;
        }
        if (newflight.date.month > 12){
            newflight.date.month = 1;
            newflight.date.year++;
        }
    }
    return newflight;
}
int verify_input_cmd_r(ptrFlight f,char*flight_code, Date d, char *code, int n){
    if(verify_reservation_code(code) == -1){
        printf("invalid reservation code\n");
        return -1;
    }
    if(f == NULL){
        printf("%s: flight does not exist\n", flight_code);
        return -1;
    }
    if(RVsearch(code) != NULL){
        printf("%s: flight reservation already used\n", code);
        return -1;    
    }
    if((f->quantity + n) > f->capacity){
        printf("too many reservations\n");
        return -1;
    }
    if(verify_date(d) == -1){
        printf("invalid date\n");
        return -1;
    }
    if(n <= 0){
        printf("invalid passenger number\n");
        return -1;
    }
    return 0;
}
void print_reservations(ptrFlight flight){
    int i;
    quickSort(flight->reservations, 0, flight->n_reserves - 1);
    for(i = 0; i < flight->n_reserves; i++){
        printf("%s %d\n", flight->reservations[i]->reservation_code, 
        flight->reservations[i]->number_passangers);
    }
}
void command_r(){
    char a, flight_code[SIZE_FLIGHT_CODE + 1];
    Date data;
    ptrFlight flight;
    scanf("%s %d-%d-%d", flight_code, &data.day, &data.month, &data.year);
    flight = FLsearch_date(flight_code, data, flights_counter);
    scanf("%c", &a);
    if(a == '\n'){
        if(flight == NULL){
            printf("%s: flight does not exist\n", flight_code);
            return;
        }
        if(verify_date(data) == -1){
            printf("invalid date\n");
            return;
        }
        print_reservations(flight);
    }
    else{
        char *code;
        int number_passangers;
        code = read_reservation_code();
        scanf("%d", &number_passangers);
        
        if(verify_input_cmd_r(flight,flight_code, data, code, number_passangers)
        == -1){
            free(code);
            return;
        }
        add_reservation(flight, data, code, number_passangers);
    }
}
void add_reservation(ptrFlight f, Date d, char *code, int n){
    ptrReservation reserva;
    reserva = (ptrReservation) malloc(sizeof( struct Reservation));
    if(reserva == NULL){
        printf("No memory.\n");
        free(reserva);
        RVdestroy();
        FLdestroy(flights_counter);
        exit(0);
    }
    reserva->reservation_code = code;
    reserva->date = d;
    strcpy(reserva->flight_code, f->code);
    reserva->number_passangers = n;
    f->quantity += n;
    f->reservations[f->n_reserves] = reserva;
    f->n_reserves++;
    RVinsert(reserva);
}
char *read_reservation_code(){
    char b;
    int i = 0;
    char *code, buffer[11];
    scanf("%10s", buffer);
    i = i + strlen(buffer);
    code = (char *) malloc(sizeof(char)*(i+1));
    if(code == NULL){
        printf("No memory.\n");
        free(code);
        RVdestroy();
        FLdestroy(flights_counter);
        exit(0);
    }
    strcpy(code,buffer);
    while(strlen(buffer) == 10){
        scanf("%c", &b);
        if(b == ' ' || b == '	' || b == '\n'){
            break;
        }
        else{
            buffer[0] = b;
            buffer[1] ='\0';
            scanf("%9[^'\n', ' ', '	']", buffer+1);
            i = i + strlen(buffer);
            code = (char *) realloc(code, sizeof(char)*(i+1));
            if(code == NULL){
                printf("No memory.\n");
                free(code);
                RVdestroy();
                FLdestroy(flights_counter);
                exit(0);
            }
            strcat(code, buffer);
        }
    }
    return code;
}

void command_e(){
    char *code = read_reservation_code();
    int aux;
    if(strlen(code) < 10){
       aux = FLdelete(code, flights_counter);
        if(aux == flights_counter){
            printf("not found\n");
        }
        else{
            flights_counter = aux;
        }
    }
    else{
        if(RVdelete_reservation(code, flights_counter) == -1){
            printf("not found\n");
        }
    }
    free(code);
}
int verify_reservation_code(char *code){
    int i;
    if(strlen(code) < 10){
        return -1;
    }
    for(i = 0; i < (int) strlen(code); i++){
        if(!((code[i] >= '0' && code[i] <= '9') ||
        (code[i] >= 'A' && code[i] <= 'Z'))){
            return -1;
        }
    }
    return 0;
}

void quickSort(ptrReservation *arr, int low, int high){
    int pi;
    if (low < high){
        pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
void swap(ptrReservation *a, ptrReservation *b){
    ptrReservation r = *a;
    *a = *b;
    *b = r;
}

int partition (ptrReservation *arr, int low, int high){
    int i = low-1;
    int j = high;
    ptrReservation v = arr[high];
    while (i < j) {
        while (strcmp(arr[++i]->reservation_code, v->reservation_code) < 0);
        while (strcmp(v->reservation_code, arr[--j]->reservation_code) < 0){
            if (j == low){
                break;
            }
        }
        if (i < j){
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i], &arr[high]);
    return i;
}