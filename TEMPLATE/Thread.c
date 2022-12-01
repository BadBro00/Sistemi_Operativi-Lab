#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
//STRUCT CONDIVISA
struct shared{
   pthread_mutex_t mutex;
   int idx;
   int dim;
   int **mat;
}shared;
//ROUTINE DEL THREAD
void* do_ops(void* args){
  printf("TID: %ld\n", pthread_self());
  
  //ESEGUI CODICE
  
  pthread_exit(NULL);
}
//ALLOCAZIONE DINAMICA ED INIZIALIZZAZIONE DELLA MATRICE
void mat_init(){
  shared.mat = malloc(shared.dim * sizeof(int*)); 
  for(int i=0;i<shared.dim;i++){
     mypars.mat[i] = malloc(shared.dim * sizeof(int));
  }
  for(int i=0;i<shared.dim;i++)
    for(int j=0;j<shared.dim;j++)
      shared.mat[i][j] = rand()%256;
}
//MAIN
int main(int argc,char *argv[]){
  if(argc != 2){
    fprintf(stderr,"Uso: ./a.out <int>\n");
    exit(-1);
  }
  shared.dim = atoi(argv[1]);
  
  //CODICE
  
  pthread_t tids[shared.dim];
  for(int i=0;i<shared.dim;i++)
    pthread_create(&tids[i],NULL,do_ops,NULL);
  for(int i=0;i<shared.dim;i++)
    pthread_join(tids[i],NULL)
  return 0;
}
