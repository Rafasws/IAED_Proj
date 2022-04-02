#include "main.h"

Airport airports[MAX_AIRPORTS];
Flight flights[MAX_FLIGHTS];
int airports_counter = 0;
int flights_counter = 0;
Date init_date;

int main(){
    char command;
    init_date.day = 1;
    init_date.month = 1;
    init_date.year = 2022;
    for(;;){
        scanf("%c", &command);
        switch(command){
            case 'q':
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
            default :
                break;
        }
    }
}

void command_a(){
    char id[SIZE_AIRPORT_ID + 1];
    char country[MAX_COUTRY_NAME + 1], city[MAX_CITY_NAME +1];
    scanf("%s %s %[^\n]", id, country, city);
    if(verify_input_cmd_a(id) == -1){
        return;
    }
    add_airport(id, country, city);

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

void command_v(){
    char a;
    Flight flight;
    scanf("%c", &a);
    if(a == '\n'){
        print_all_flights();
    }
    else{
        scanf("%s %s %s %d-%d-%d %d:%d %d:%d %d", 
        flight.code, flight.ap_departure, flight.ap_arrival, 
        &flight.date.day, &flight.date.month, &flight.date.year, 
        &flight.hours.hour, &flight.hours.minute, &flight.duration.hour, 
        &flight.duration.minute, &flight.capacity);
        if(verify_input_cmd_v(flight) == -1){
            return;
        }
        add_flight(flight);
    }
}
void print_all_flights(){
    int i;
    for(i = 0; i < flights_counter; i++){
        printf("%s %s %s %2.2d-%2.2d-%2.2d %2.2d:%2.2d\n", flights[i].code,
        flights[i].ap_departure, flights[i].ap_arrival, flights[i].date.day,
        flights[i].date.month, flights[i].date.year, flights[i].hours.hour,
        flights[i].hours.minute); 
    }
}
void add_flight(Flight flight){
    strcpy(flights[flights_counter].code, flight.code);
    strcpy(flights[flights_counter].ap_departure, flight.ap_departure);
    strcpy(flights[flights_counter].ap_arrival, flight.ap_arrival);
    flights[flights_counter].date.day = flight.date.day;
    flights[flights_counter].date.month = flight.date.month;
    flights[flights_counter].date.year = flight.date.year;
    flights[flights_counter].hours.hour = flight.hours.hour;
    flights[flights_counter].hours.minute = flight.hours.minute;
    flights[flights_counter].duration.hour = flight.duration.hour;
    flights[flights_counter].duration.minute = flight.duration.minute;
    flights[flights_counter].capacity = flight.capacity;
    airports[exist_airport(flight.ap_departure)].number_flights++;
    flights_counter++;
}
int verify_input_cmd_v(Flight flight){
    if(verify_flight_code(flight.code) == -1){
        printf("invalid flight code\n");
        return -1;
    }
    if(existent_flight(flight) == -1){
        printf("flight already exists\n");
        return -1;
    }
    if(exist_airport(flight.ap_departure) == -1){
        printf("%s: no such airport ID\n", flight.ap_departure);
        return -1;
    }
    if(exist_airport(flight.ap_arrival) == -1){
        printf("%s: no such airport ID\n", flight.ap_arrival);
        return -1;
    }
    if(flights_counter >= MAX_FLIGHTS){
        printf("too many flights\n");
        return -1;
    }
    if(verify_date(flight.date) == -1){
        printf("invalid date\n");
        return -1;
    }
    if(flight.duration.hour >= 12){
        if(flight.duration.hour == 12 && flight.duration.minute > 0){
            printf("invalid duration\n");
            return -1;
        }
        else if(flight.duration.hour > 12){
            printf("invalid duration\n");
            return -1;
        }
    }
    if(flight.capacity > MAX_CAPACITY && flight.capacity < MIN_CAPACITY){
        printf("invalid capacity\n");
        return -1;
    }
    return 0;
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
int existent_flight(Flight flight){
    int i;
    for(i = 0; i < flights_counter; i++){
        if(!(strcmp(flight.code, flights[i].code)) && 
        (equal_dates(flight.date, flights[i].date) == 0)){
            return -1;
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
        if(!(strcmp(flights[i].ap_departure, ap))){
            f[len++] = i;
        }
    }
    for (j = 0; j < len - 1; ++j) {
        for (i = 0; i < len - j - 1; ++i) {
            if (equal_dates(flights[f[i]].date, flights[f[i+1]].date) > 0) {
                k = f[i];
                f[i] = f[i + 1];
                f[i + 1] = k;
            }
            else if(equal_dates(flights[f[i]].date, flights[f[i+1]].date) == 0){
                if(equal_time(flights[f[i]].hours, flights[f[i+1]].hours) > 0){
                    k = f[i];
                    f[i] = f[i + 1];
                    f[i + 1] = k;
                }
            }
        }
    }
    for(i = 0; i < len; i++){
        printf("%s %s %2.2d-%2.2d-%4.4d %2.2d:%2.2d\n", flights[f[i]].code, 
        flights[f[i]].ap_arrival, flights[f[i]].date.day,
        flights[f[i]].date.month, flights[f[i]].date.year, 
        flights[f[i]].hours.hour, flights[f[i]].hours.minute);
    }
}
void command_c(){
    int i, j, len = 0;
    char ap[SIZE_AIRPORT_ID + 1];
    Flight k, f[MAX_FLIGHTS];
    scanf(" %s", ap);
    if(exist_airport(ap) == -1){
        printf("%s: no such airport ID\n", ap);
        return;
    }
    for(i = 0; i < flights_counter; i++){
        if(!(strcmp(flights[i].ap_arrival, ap))){
            f[len] = new_date(flights[i]);
            len++;
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

Flight new_date(Flight f){
    int d = 0;
    int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if((f.hours.minute+= f.duration.minute) >= 60){
        f.hours.minute %= 60;
        f.hours.hour++;
    }
    if((f.hours.hour+= f.duration.hour) >= 24){
        f.hours.hour %= 24;
        d++;
    }
    if(d != 0){
        if((f.date.day+=1) > days[f.date.month]){
            f.date.day = 1;
            f.date.month++;
        }
        if (f.date.month > 12){
            f.date.month = 1;
            f.date.year++;
        }
    }
    return f;
}