#include <stdio.h>
#include <mpi.h>
int main(int argc, char** argv) {
int id; /* identyfikator (ranga) procesu */
int p; /* liczba procesow */
float a; /* lewy koniec przedzialu */
float b; /* prawy koniec przedzialu */
int n; /* liczba przedzialow (trapezow) */
float h; /* dlugosc przedzialu */
float lokal_a; /* lokalny, lewy koniec przedzialu */
float lokal_b; /* lokalny, prawy koniec przedzialu */
int lokal_n; /* lokalna liczba przedzialow */
float calka; /* lokalna wartosc calki */
float suma; /* pelna wartosc calki */
int zrodlo; /* identyfikator procesu zrodlowego */
int docel = 0; /* identyfikator procesu docelowego, tj. procesu 0 */
int typ = 0; /* typ (znacznik) wiadomosci */
MPI_Status status; /* status powrotu dla funkcji receive */
float obl_calke(float lokal_a, float lokal_b, /* funkcja lokalnego */
int lokal_n, float h); /* obliczania calki */
void wez_dane(float* ods_a, float* ods_b, int* ods_n, int id, int p);
MPI_Init(&argc, &argv); /* inicjacja MPI */
MPI_Comm_rank(MPI_COMM_WORLD, &id); /* zwraca identyfikator procesu */
MPI_Comm_size(MPI_COMM_WORLD, &p); /* zwraca liczbe procesow */
wez_dane(&a, &b, &n, id, p);
h = (b - a) / (float)n; /* h jest to samo dla wszystkich procesow */
lokal_n = n / p; /* ta sama liczba przedzialow w kazdym procesie */
lokal_a = a + (float)id *
(float)lokal_n * h; /* wyznaczenie lewego i prawego */
lokal_b = lokal_a + (float)lokal_n * h; /* konca przedzialu */
calka = obl_calke(lokal_a, lokal_b, lokal_n, h);
if (id == 0) { /* dla procesu 0 */
suma = calka;
for (zrodlo = 1; zrodlo < p; zrodlo++) {
9
MPI_Recv(&calka, 1, MPI_FLOAT, zrodlo, typ,
MPI_COMM_WORLD, &status);
suma = suma + calka;
}
}
else { /* dla procesow o numerach != 0 */
/* wyslanie lokalnej wartosci calki */
MPI_Send(&calka, 1, MPI_FLOAT, docel, typ, MPI_COMM_WORLD);
}
/* drukowanie wyniku */
if (id == 0) {
printf("Liczba procesow: %d\n", p);
printf("Przy n = %d trapezach, przyblizenie calki\n", n);
printf("w granicach od %f do %f wynosi %f\n", a, b, suma);
}
/* zamkniecie MPI */
MPI_Finalize();
return 0;
}
float obl_calke(float lokal_a, float lokal_b,
int lokal_n, float h) {
float calka; /* lokalna wartosc calki */
float x;
int i;
float f(float x); /* funkcja ktora calkujemy */
calka = (f(lokal_a) + f(lokal_b)) / 2.0;
x = lokal_a;
for (i = 1; i <= lokal_n - 1; i++) {
x = x + h;
calka = calka + f(x);
}
calka = calka * h;
return calka;
} /* obl_calke */
float f(float x) {
float wart;
/* obliczenie f(x) */
wart = x * x;
return wart;
} /* f */
/* Funkcja wez_dane sluzaca do czytania wartosci a, b oraz n.
* Parametry wejsciowe:
* 1. int id: identyfikator procesu.
* 2. int p: liczba procesow.
* Parametry wyjsciowe:
* 1. float* ods_a: odsylacz do lewego konca przedzialu.
* 2. float* ods_b: odsylacz do prawego konca przedzialu.
* 3. int* ods_n: odsylacz do liczby przedzialow (trapezow).
* Dzialanie:
10
* 1. Proces 0 prosi o dane a, b oraz n, oraz odczytuje ich wartosci.
* 2. Proces 0 przesyla te wartosci do pozostalych procesow.
*/
void wez_dane(float* ods_a /* wyj */,
float* ods_b /* wyj */,
int* ods_n /* wyj */,
int id /* wej */,
int p /* wej */) {
int zrodlo = 0; /* dane uzywane w MPI_Send i MPI_Recv */
int docel;
int typ;
MPI_Status status;
if (id == 0) { /* dla procesu 0 */
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
