#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <omp.h>

int main() {

    int limite;
    int threads = omp_get_num_procs() / 2;
    double inicio, fim, tempo;
    int *x;

    printf("Digite um número: ");
    scanf("%d", &limite);

    x = (int *)malloc(sizeof(int) * (limite - 1));

    if(x == NULL)
        exit(1);


    tempo = omp_get_wtime();
    #pragma omp parallel num_threads(threads)
    {
        #pragma omp for
        for(int i = 0; i < (limite - 1); i++)
            x[i] = 1;

    }

    for(int i = 0; i * i < (limite - 1); i++) {

        if(x[i]) {

            #pragma omp parallel num_threads(threads)
            {

                #pragma omp for
                for(int j = (i + 2) * (i + 2) - 2; j < (limite - 1); j += (i + 2))
                    x[j] = 0;

            }

        }
        
    }
    fim = omp_get_wtime();

    tempo = fim - inicio;

    for(int i = 0; i < (limite - 1); i++) {

        if(x[i])
            printf("%d\n", i + 2);

    }

    printf("Tempo de execução paralelo com %d threads: %lf.\n", threads, tempo);

    free(x);

    return 0;
}