#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "err.h"
#include "time.h"

int main{
	int pid;
  int n = rand()%5000;
  double suma = 0.0;
	
	for(int i=0; i<n; i++){
		pid = fork();
  }
  if(pid != 0){
  int d = 3;
  int suma = 1;
    for(int i=0; i<n; i++){
		  suma -= 1/d;
      d += 2;
    }
    printf("Suma PI procesu %d wynosi: %f",%getpid(), suma);
  }
  
    

}
