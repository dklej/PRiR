#include <stdio.h>
#include <mpi.h>
int main(int argc, char** argv) {
	int id; 
	int p; 
	float a; 
	float b; 
	int n; 
	float h; 
	float lokal_a; 
	float lokal_b; 
	int lokal_n; 
	float calka; 
	float suma; 
	int zrodlo; 
	int docel = 0; 
	int typ = 0; 
	MPI_Status status; 
	float obl_calke(float lokal_a, float lokal_b, int lokal_n, float h); 
	void wez_dane(float* ods_a, float* ods_b, int* ods_n, int id, int p);
	MPI_Init(&argc, &argv); 
	MPI_Comm_rank(MPI_COMM_WORLD, &id); 
	MPI_Comm_size(MPI_COMM_WORLD, &p); 
	wez_dane(&a, &b, &n, id, p);
	h = (b - a) / (float)n; 
	lokal_n = n / p; 
	lokal_a = a + (float)id *
	(float)lokal_n * h; 
	lokal_b = lokal_a + (float)lokal_n * h; 
	calka = obl_calke(lokal_a, lokal_b, lokal_n, h);
	if (id == 0) { 
		suma = calka;
		for (zrodlo = 1; zrodlo < p; zrodlo++) {
			MPI_Recv(&calka, 1, MPI_FLOAT, zrodlo, typ, MPI_COMM_WORLD, &status);
			suma = suma + calka;
		}
	}
	else { 
		MPI_Send(&calka, 1, MPI_FLOAT, docel, typ, MPI_COMM_WORLD);
	}
	if (id == 0) {
		printf("Liczba procesow: %d\n", p);
		printf("Przy n = %d trapezach, przyblizenie calki\n", n);
		printf("w granicach od %f do %f wynosi %f\n", a, b, suma);
	}
	MPI_Finalize();
	return 0;
}
float obl_calke(float lokal_a, float lokal_b, int lokal_n, float h) {
	float calka; 
	float x;
	int i;
	float f(float x);
	calka = (f(lokal_a) + f(lokal_b)) / 2.0;
	x = lokal_a;
	for (i = 1; i <= lokal_n - 1; i++) {
	x = x + h;
	calka = calka + f(x);
	}
	calka = calka * h;
	return calka;

	float f(float x) {
	float wart;

	wart = x * x;
	return wart;
	} 
	void wez_dane(float* ods_a, float* ods_b /* wyj */, int* ods_n /* wyj */, int id /* wej */, int p /* wej */) {
		int zrodlo = 0;
		int docel;
		int typ;
		MPI_Status status;
		if (id == 0) { 
			printf("Wprowadz a, b oraz n\n");
			scanf("%f %f %d", ods_a, ods_b, ods_n);
			for (docel = 1; docel < p; docel++) {
				typ = 0;
				MPI_Send(ods_a, 1, MPI_FLOAT, docel, typ, MPI_COMM_WORLD);
				typ = 1;
				MPI_Send(ods_b, 1, MPI_FLOAT, docel, typ, MPI_COMM_WORLD);
				typ = 2;
				MPI_Send(ods_n, 1, MPI_INT, docel, typ, MPI_COMM_WORLD);
			}
		}
		else {
			typ = 0;
			MPI_Recv(ods_a, 1, MPI_FLOAT, zrodlo, typ,
			MPI_COMM_WORLD, &status);
			typ = 1;
			MPI_Recv(ods_b, 1, MPI_FLOAT, zrodlo, typ,
			MPI_COMM_WORLD, &status);
			typ = 2;
			MPI_Recv(ods_n, 1, MPI_INT, zrodlo, typ,
			MPI_COMM_WORLD, &status);
		}
	}
}
