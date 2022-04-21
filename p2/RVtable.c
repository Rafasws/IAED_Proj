#include"RVtable.h"

static int M;
static int N = 0; 
static ptrReservation *rv;
static ptrFlight *flights;

int RVhash(char *v, int M){

   int h, a = 31415, b = 27183;

   for (h = 0; *v != '\0'; v++, a = a*b % (M-1)){
      h = (a*h + *v) % M;
   }
   return h;
}

void RVinit(int m){
   int i;
   N = 0;
   M = m;
   rv = (ptrReservation *) malloc(sizeof(ptrReservation)* M);
   if(rv == NULL){
      printf("no memory.\n");
      exit(0);
   }
   for (i = 0; i < M; i++){
      rv[i] = NULL;
   }
}

void RVinsert(ptrReservation reserve) {
   int i = RVhash(reserve->reservation_code, M);
   while (rv[i]!= NULL){
      i = (i + 1) % M;
   }
   rv[i] = reserve;
   N++;
   if(N > M/2){
      RVexpand(M);
   }
}

void RVexpand(int aux){
   int i;
   ptrReservation *t = rv;
   RVinit(2*M + 1);
   for (i = 0; i < aux; i++){
      if (t[i] != NULL){
         RVinsert(t[i]);
      }
   }
   free(t);
}

ptrReservation RVsearch(char *code){
   int i = RVhash(code, M);
   while (rv[i] != NULL){
      if(strcmp(rv[i]->reservation_code, code) == 0){
         return rv[i];
      }
      else{
         i = (i + 1) % M;
      }
   }
   return NULL;
}

int RVdelete_reservation(char *code, int n){
   int j = 0, i, w;
   ptrReservation r;
   ptrFlight v;
   i = RVhash(code, M); 
   while (rv[i] != NULL){
      if (strcmp(rv[i]->reservation_code, code) == 0){
         break;
      }
      else{
         i = (i + 1) % M;
      }
   }
   if (rv[i] == NULL){
      return -1;
   }
   v = FLsearch_date(rv[i]->flight_code,rv[i]->date, n);/*veri isto urgente*/
   for(w = 0; w < (v->n_reserves - 1); w++){
      if(v->reservations[w] != NULL){
         if(strcmp(v->reservations[w]->reservation_code, code) == 0){
            v->reservations[w] = NULL;
            j++;
         }
      }
      if(j != 0){
         v->reservations[w] = v->reservations[w + 1];
         v->reservations[w+1] = NULL;
      }
      
   }
   v->n_reserves--;
   v->quantity -= rv[i]->number_passangers;
   free(rv[i]->reservation_code); 
   free(rv[i]); 
   rv[i] = NULL;
   N--;
   for (j = (i + 1) % M; rv[j] != NULL; j = (j + 1) % M, N--) {
      r = rv[j];
      rv[j] = NULL;
      RVinsert(r);
   }
   return 0;
   
}

int RVdelete(char *code){
   int j, i;
   ptrReservation v;
   i = RVhash(code, M);
   while (rv[i] != NULL){
      if (strcmp(rv[i]->reservation_code, code) == 0){
         break;
      }
      else{
         i = (i + 1) % M;
      }
   }
   if (rv[i] == NULL){
      return -1;
   }
   free(rv[i]->reservation_code); 
   free(rv[i]); 
   rv[i] = NULL;
   N--;
   for (j = (i + 1) % M; rv[j] != NULL; j = (j + 1) % M, N--) {
      v = rv[j];
      rv[j] = NULL;
      RVinsert(v);
   }
   return 0;
}

void RVdestroy(){
   int i;
   for(i = 0; i < M; i++){
      if(rv[i]!= NULL){
         free(rv[i]->reservation_code);
         free(rv[i]);
      }
   }
   free(rv);
}

ptrFlight *FLinit(){
   int i;
   flights = (ptrFlight *) malloc(sizeof(ptrFlight)* MAX_FLIGHTS);
   if(flights == NULL){
      printf("No memory.\n");
      exit(0);
   }
   for (i = 0; i < MAX_FLIGHTS; i++){
      flights[i] = NULL;
   }
   return flights;
}

void FLinsert(ptrFlight flight, int n) {
   flights[n] = flight;
}

int FLsearch(char *code, int n){
   int i;
   for(i = 0; i < n; i++){
      if((strcmp(flights[i]->code, code) == 0)){
         return i;
      }
   }
   return -1;
}
ptrFlight FLsearch_date(char *code, Date date, int n){
   int i;
   for(i = 0; i < n; i++){
      if((strcmp(flights[i]->code, code) == 0) && 
      (flights[i]->date.day == date.day) && 
      (flights[i]->date.month == date.month) &&
      (flights[i]->date.year == date.year)){
         return flights[i];
      }
   }
   return NULL;
}

int FLdelete(char *code, int counter){
   int w, j, i = FLsearch(code, counter);
   while(i > -1){ 
      if (strcmp(flights[i]->code, code) == 0){
         for(w = 0; w < flights[i]->n_reserves; w++){
            RVdelete(flights[i]->reservations[w]->reservation_code);
         }
         free(flights[i]->reservations); 
         free(flights[i]); 
         flights[i] = NULL;
         for (j = i + 1; j < counter; j++){
            flights[j-1] = flights[j];
            flights[j] = NULL;
         }
         counter--;
      }
      i = FLsearch(code, counter);
   }
   return counter;
}

void FLdestroy(int n){
   int i;
   for(i = 0; i < n; i++){
      if(flights[i]!= NULL){
         free(flights[i]->reservations);
         free(flights[i]);
      }
   }
   free(flights);
}