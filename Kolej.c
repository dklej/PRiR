#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "mpi.h"


#define REZERWA 700
#define KOLEJ 1
#define START 2
#define LOT 3
#define KONIEC_JAZDY 4
#define KATASTROFA 5
#define TANKUJ 2000
int paliwo = 2000;
int LADUJ=1, NIE_LADUJ=0;
int iProc;
int nr_procesu;
int nr_poc;
int ilosc_pociagow;
int ilosc_torow=4;
int zajete_tory=0;
int tag=1;
int send[2];
int order[2];
MPI_Status mpi_status;
void Wyslij(int nr_poc, int stan)
{
	send[0]=nr_poc;
	send[1]=stan;
	MPI_Send(&send, 2, MPI_INT, 0, tag, MPI_COMM_WORLD);
	sleep(1);
}
void Kolej(int iProc){
	int nr_poc,status;
	ilosc_pociagow = iProc - 1;
	printf("Symulator kolei PKP \n");
	printf("=========================== \n");
	sleep(2);
	while(ilosc_torow<=ilosc_pociagow){
		MPI_Recv(&order,2,MPI_INT,MPI_ANY_SOURCE,tag,MPI_COMM_WORLD, &mpi_status);
		nr_poc=order[0];
		status=order[1];
		if(status==1){
			printf("Pociąg %d stoi na stacji \n", nr_poc);
		}
		if(status==2){
			printf("Pociąg %d pozwolenie na start z toru nr %d\n", nr_poc, zajete_tory);
			zajete_tory--;
		}
		if(status==3){
			printf("Pociąg %d jedzie \n", nr_poc);
		}
		if(status==4){
			if(zajete_tory<ilosc_torow){
				zajete_tory++;
				MPI_Send(&LADUJ, 1, MPI_INT, nr_poc, tag, MPI_COMM_WORLD);
			}
			else{
				MPI_Send(&NIE_LADUJ, 1, MPI_INT, nr_poc, tag, MPI_COMM_WORLD);
			}
		}
		if(status==5){
			ilosc_pociagow--;
			printf(" POCIAG SIĘ SPÓŹNIŁ - PKP W FORMIE \n");
		}
	}
	printf(" STOP \n");
}
void Pociag(){
	int stan,suma,i;
	stan=LOT;
	while(1){
		if(stan==1){
			if(rand()%2==1){
			stan=START;
			paliwo=TANKUJ;
			printf("Pociąg %d zaraz ruszy \n",nr_procesu);
			Wyslij(nr_procesu,stan);
			}
			else{
				Wyslij(nr_procesu,stan);
			}
		}
		else if(stan==2){
			printf("Pociag wyjechał ze stacji %d\n",nr_procesu);
			stan=LOT;
			Wyslij(nr_procesu,stan);
		}
		else if(stan==3){
			paliwo-=rand()%500;
			if(paliwo<=REZERWA){
				stan=KONIEC_JAZDY;
				Wyslij(nr_procesu,stan);
			}
			else{
				for(i=0; rand()%10000;i++);
			}
		}
		else if(stan==4){
			int temp;
			MPI_Recv(&temp, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &mpi_status);
			if(temp==LADUJ){
			stan=KOLEJ;
			printf("Pociag jest na stacji:  %d\n",nr_procesu);
			}
			else
			{
				paliwo-=rand()%500;
				if(paliwo>0){
					Wyslij(nr_procesu,stan);
				}
				else{
					stan=KATASTROFA;
					printf("SPÓŹNIŁEM SIĘ \n");
					Wyslij(nr_procesu,stan);
					return;
				}
			}
		}
	}
}
int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&nr_procesu);
	MPI_Comm_size(MPI_COMM_WORLD,&iProc);
	srand(time(NULL));
	if(nr_procesu == 0)
		Kolej(iProc+1);
	else
		Pociag();

	MPI_Finalize();
	return 0;
}
