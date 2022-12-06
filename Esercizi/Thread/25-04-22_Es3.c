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
int **mat;
int n;

void* do_ops(void* args){
  
}

void mat_init(){
  mat = malloc(n*sizeof(int*));
  for(int i=0;i<n;i++)
    mat[i] = malloc(n*sizeof(int));
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      mat[i][j] = rand()%256;
}

void prt_mat(){
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      printf(" %d ",mat[i][j]);
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
  n = atoi(argv[1]);
  mat_init();
  prt_mat();
  return 0;
}
