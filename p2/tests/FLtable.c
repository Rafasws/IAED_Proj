#include "FLtable.h"

static ptrFlight *flights;

ptrFlight *FLinit(){
   int i;
   flights = (ptrFlight *) malloc(sizeof(ptrFlight)* MAX_FLIGHTS);
   for (i = 0; i < MAX_FLIGHTS; i++){
      flights[i] = NULL;
   }
   return flights;
}

void FLinsert(ptrFlight flight) {
   int i = 0;
   while (flights[i] != NULL){
      i++;
   }
   flights[i] = flight;
}

ptrFlight FLsearch(char *code){
   int i = 0;
   while (flights[i] != NULL){
      if((strcmp(flights[i]->code, code) == 0)){
         return flights[i];
      }
      else{
         i++;
      }
   }
   return NULL;
}
ptrFlight FLsearch_date(char *code, Date date){
   int i = 0;
   while (flights[i] != NULL){
      if((strcmp(flights[i]->code, code) == 0) && 
      (flights[i]->date.day == date.day) && 
      (flights[i]->date.month == date.month) &&
      (flights[i]->date.year == date.year)){
         return flights[i];
      }
      else{
         i++;
      }
   }
   return NULL;
}

int FLdelete(char *code){
   int j, counter = 0, i = 0;
   ptrFlight v; 
   while (flights[i] != NULL && i < MAX_FLIGHTS){
      if (strcmp(flights[i]->code, code) == 0){
         free(flights[i]->reservations); 
         free(flights[i]); 
         flights[i] = NULL;
         for (j = i + 1; flights[j] != NULL; j++){
            v = flights[j];
            flights[j] = NULL;
            FLinsert(v);
         }
         counter++;
      }
      else{
         i++;
      }
   }
   if (counter == 0){
      return -1;
   }
   return 0;
}

void FLdestroy(){
   int i;
   for(i = 0; i < MAX_FLIGHTS; i++){
      if(flights[i]!= NULL){
         free(flights[i]->reservations);
         free(flights[i]);
      }
   }
   free(flights);
}