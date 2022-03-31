#include "time.h"

int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int date_to_min(int date, int day, int month, int year){

    int i, time = (day - 1) * 24 * 60;
    for(i = 1; i <= (month - 1); i++){
        time += days[i] * 24 * 60;
    }
    time += (year - 2022) * 365 * 24 * 60;

    if(time < date && time > date + ONE_YEAR_MINUTES){
        return -1;
    }

    return time;
}

int duration_to_min(int hour, int minutes){
    int time =  hour * 60 + minutes;
    return time;
}

void min_to_date(int minutes, int res[]){
    int i, j = 1;
    res[4] = 2022 + (minutes / (60 * 24 * 365));
    minutes %= (60 * 24 * 365);
    i = minutes;
    while((i / (days[j] * 24 * 60)) > 0){
        minutes -= (days[j] * 24 *60);
        i = minutes;
        j++;
    }
    res[3] = j;
    res[2] = (minutes / (24 * 60)) + 1;
    minutes %= (24 * 60);
    res[0] = minutes / 60;
    minutes %= 60;
    res[1] = minutes;
    return;  
}
/*int main(){
    int time, res[5]; 
    time = duration_to_min(12,1);
    printf("%d\n", time);
    min_to_date(time, res);
    printf("%d-%d-%d %d:%d \n", res[2], res[3], res[4], res[0], res[1]);
    return 0;

}*/
