#include <stdio.h>
#include <signal.h>

int signo;
void handler(int nsig){
  signo = nsig;
  //ESEGUI CODICE [opzionale]
}

int main(int argc, char *argv[]){
  int num_figli;
  pid_t pids[num_figli];
  int variabili_figli[num_figli];
  if ( fork() == 0 )
    printf("creato figlio: %ld\n",getpid());
  
  //CODICE
  
  for(int i=0;i<num_figli;i++)
    kill(SIGUSR1,pids[i]);
  
  //CODICE
  
}
