#include "FLtable.h"

static const int M = MAX_FLIGHTS;
static int N = 0;
static ptrFlight *flights;

ptrFlight *FLinit(){
   int i;
   flights = (ptrFlight *) malloc(sizeof(ptrFlight)* M);
   for (i = 0; i < M; i++){
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
   N++;
}

ptrFlight FLsearch(char *code, Date date){
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

int delete(char *code){
   int j, w, i = 0;
   ptrFlight v; 
   while (flights[i]!=NULL && i < MAX_FLIGHTS){
      if (strcmp(flights[i]->code, code) == 0){
         break;
      }
      else{
         i++;
      }
   }
   if (flights[i] == NULL){
      return -1;
   }
   for(w = 0; w < flights[i]->capacity; w++){
      if(flights[i]->reservations[w] == NULL){
         break;
      }
      free(flights[i]->reservations[w]);
   }
   free(flights[i]->reservations); 
   free(flights[i]); 
   flights[i] = NULL;
   for (j = i + 1; flights[j] != NULL; j++) {
      v = flights[j];
      flights[i++] = flights[j];
      FLinsert(v);
   }
   return 0;
}

void FLdestroy(){
   int i;
   for(i = 0; i < M; i++){
      if(flights[i]!= NULL){
         free(flights[i]->reservations);
         free(flights[i]);
      }
   }
   free(flights);
}