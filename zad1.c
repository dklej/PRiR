#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "err.h"
#include "time.h"



int main{
	int pid,a,b;
	
	for(int i=0; i<rand()%100; i++){
		pid = fork();
		while(a>b){
			a = rand()%10;
			b = rand()%100;
		}
		pole(a,b,pid);
		
	}

}

double f(x){
	return 4*x*x - 6*x + 5;
}

double pole(int a, int b, int n){
	double h = (b-a)/n;
	double s = 0.0;
	double pA = f(a);
	double pB;
	
	for(int i=1; i<=n; i++){
		pB = f(a+h*i);
		s += (pA + pB);
		pA = pB;
	}
	return s*0.5*h
}
