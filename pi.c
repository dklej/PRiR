#include "mpi.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <math.h>
#include <sys/wait.h>
#include "err.h"
#include "time.h"

        int main(argc,argv)
        int argc;
        char *argv[];
        {
          int done = 0;
          int n, myid, numprocs, i;
          double PI = 3.141592653589793238462643; 
          double temppi, pi, h, sum, x;

          MPI_Init(&argc, &argv);
          MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
          MPI_Comm_rank(MPI_COMM_WORLD,&myid);
          while (!done)
          {
            if (tempid == 0) {
              printf("Wpisz ilosć wątków do obliczenia: ");
              scanf("%d",&n);
            }
            MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
            if (n == 0) 
              break;

            h = 1.0 / (double) n;
            sum = 0.0;
            for (i = tempid + 1; i <= n; i += numprocs) {
              x = h * ((double)i - 0.5);
              sum += 4.0 / (1.0 + x*x);
            }
            temppi = h * sum;

            MPI_Reduce(&temppi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

            if (tempid == 0)
              printf("Wartosć PI wynosi: %.16f, Błąd obliczeń wynosi: %.16f\n", pi, fabs(pi - PI));
          }
          MPI_Finalize();
          return 0;
        }
