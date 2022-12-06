/*Si realizzi un programma in POSIX C che effettui i seguenti task:
   
   1) Lancia N thread per calcolare la somma di ciascuna riga di una
      matrice N*N di interi, allocata dinamicamente, generati in un
      intervallo [0,255]
   
   2) Il calcolo della somma degli elementi di ciascuna riga deve essere
      effettuato concorrentemente su tutte le righe, secondo la seguente
      modelità:
        i) Il thread i-simo con i pari, calcola la somma degli elementi 
           di indice pari della riga i-sima
        ii) Il thread i-simo con i dispari, calcola la somma degli elementi
            di indice dispari della riga i-sima
   3) Calcolate le somme parziali, si provveda a ricercarne il minimo ed a
      stamparlo a video.    
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct mypars{
   int **mat;
   int n;
   int idx;
   pthread_mutex_t mutex;
   int *part_sums;
}sh;

   
void* do_ops(void* args){
   pthread_mutex_lock(&sh.mutex);
   int idx = sh.idx-1;
   //printf("Thread: %ld\nIl mio idx è: %d\n",pthread_self(),sh.idx);
   if(idx%2){
      for(int i=0;i<sh.n;i++){
         if(i%2)
            sh.part_sums[idx] += sh.mat[idx][i];
      }
   }else{
      for(int i=0;i<sh.n;i++){
         if(!i%2)
            sh.part_sums[idx] += sh.mat[idx][i];
      }
   }
   sh.idx++;
   pthread_mutex_unlock(&sh.mutex);
   pthread_exit(NULL);
}

void* print_sum(void* args){
   for(int i=0;i<sh.n;i++)
      printf("part_sums[%d] = %d\n",i,sh.part_sums[i]); 
   int sum = 0;
   for(int i=0;i<sh.n;i++){
      sum += sh.part_sums[i];
   }
   int min = sh.part_sums[0];
   for(int i=0;i<sh.n;i++)
      if(sh.part_sums[i] < min)
         min = sh.part_sums[i];
   printf("La somma totale è: %d\nIl minimo delle somme parziali è: %d\n",sum,min);
   pthread_exit(NULL);
}

void mat_init(){
  sh.mat = malloc(sh.n*sizeof(int*));
  for(int i=0;i<sh.n;i++)
    sh.mat[i] = malloc(sh.n*sizeof(int));
  for(int i=0;i<sh.n;i++)
    for(int j=0;j<sh.n;j++)
      sh.mat[i][j] = rand()%256;
}

void prt_mat(){
  for(int i=0;i<sh.n;i++){
    for(int j=0;j<sh.n;j++){
      printf(" %d ",sh.mat[i][j]);
    }
    printf("\n");
  }    
}

int main(int argc,char *argv[]){
  srand(time(NULL));
  if(argc != 2){
    fprintf(stderr,"Uso: ./a.out <int>\n");
    exit(-1);
  }
  sh.n = atoi(argv[1]);
  sh.part_sums = malloc(sh.n*sizeof(int));
  mat_init();
  prt_mat();
  pthread_t tids[sh.n];
  for(int i=0;i<sh.n;i++){
     sh.idx = i;
     pthread_create(&tids[i],NULL,do_ops,NULL);
  }
  for(int i=0;i<sh.n;i++)
     pthread_join(tids[i],NULL);
  pthread_t last;
  pthread_create(&last,NULL,print_sum,NULL);
  pthread_join(last,NULL);
  return 0;
}
