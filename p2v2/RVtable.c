#include"RVtable.h"

static int M;
static int N = 0; 
static ptrReservation *rv;

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
   for (i = 0; i < M; i++){
      rv[i] = NULL;
   }
}

void RVinsert(ptrReservation reserve) {
   int i = RVhash(reserve->reservation_code, M);
   while (rv[i]!= NULL){
      i++;
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
         i++;
      }
   }
   return NULL;
}

int RVdelete(char *code){
   int j, i;
   ptrReservation v;
   i = RVhash(code, M); 
   while (rv[i]!=NULL){
      if (strcmp(rv[i]->reservation_code, code) == 0){
         break;
      }
      else{
         i++;
      }
   }
   if (rv[i] == NULL){
      return -1;
   }
   free(rv[i]->reservation_code); 
   free(rv[i]); 
   rv[i] = NULL;
   for (j = i + 1; rv[j] != NULL; j = j + 1) {
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