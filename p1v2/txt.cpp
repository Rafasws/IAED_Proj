
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
    printf("%2.2d-%2.2d-%4.4d %2.2d:%2.2d\n", f.date.day, f.date.month, 
    f.date.year,f.hours.hour, f.hours.minute);
}

/*int main(){
    Flight f;
    f.date.day = 31;
    f.date.month = 12;
    f.date.year = 2022;
    f.hours.hour = 13;
    f.hours.minute = 0;
    f.duration.hour = 12;
    f.duration.minute = 0;
    new_date(f);
    printf("%2.2d-%2.2d-%4.4d %2.2d: %2.2d\n", f.date.day, f.date.month, 
    f.date.year,f.hours.hour, f.hours.minute);
    return 0;
}*/