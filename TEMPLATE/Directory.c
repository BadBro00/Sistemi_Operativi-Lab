#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
  DIR *dp;
  struct dirent *dir;
  struct stat fs;
  
  dp = opendir(argv[1]);
  while((dir = readdir(dp) != NULL){
    int r = stat(dir->d_name,&fs);
    
    if(r != -1){
      //CODICE     
    }
    else{
      perror("stat");
    }
    
    //CODICE
  }
}
