#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

#define INTERVALOS 100000000 // Número de intervalos para la aproximación

double calcular_pi(int procesador, int cantidad) {
    double suma_local = 0.0;
    double intervalo = 1.0 / INTERVALOS;
    double x;
    
    for (int i = procesador; i < INTERVALOS; i += cantidad) {
        x = (i + 0.5) * intervalo;
        suma_local += 4.0 / (1.0 + x * x);
    }
    
    return suma_local * intervalo;
}

void main(int argc, char *argv[]) {
    int procesador, cantidad;
    double suma_total, pi_local, pi_total;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &procesador);
    MPI_Comm_size(MPI_COMM_WORLD, &cantidad);

    pi_local = calcular_pi(procesador, cantidad);

    MPI_Reduce(&pi_local, &pi_total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (procesador == 0) {
        printf("Valor de PI calculado: %.16f\n", pi_total);
    }

    MPI_Finalize();
}
