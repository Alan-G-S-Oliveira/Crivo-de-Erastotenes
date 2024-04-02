#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <mpi.h>

int main() {

    //Iniciando MPI
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int limite;
    int *x;

    if(rank == 0) {

        printf("Digite um número: ");
        scanf("%d", &limite);

        MPI_Scatter(&limite, 1, MPI_INT, &limite, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }

    x = (int *)malloc(sizeof(int) * (limite - 1));

    MPI_Finalize();
    return 0;
}