#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <inttypes.h>
#include <omp.h>

int main() {

    setlocale(LC_ALL, "Portuguese");

    int limite;
    int threads = 3;
    double inicio, fim, tempo;
    int8_t *x;

    printf("Digite um número: ");
    scanf("%d", &limite);

    x = (int8_t *)malloc(sizeof(int8_t) * (limite - 1));

    if(x == NULL)
        exit(1);


    inicio = omp_get_wtime();
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

    /*
    for(int i = 0; i < (limite - 1); i++) {

        if(x[i])
            printf("%d\n", i + 2);

    }
    */

    printf("Tempo de execução paralelo com %d threads: %lf.\n", threads, tempo);

    free(x);

    return 0;
}