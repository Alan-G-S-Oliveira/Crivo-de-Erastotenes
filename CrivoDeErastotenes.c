#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <omp.h>

typedef struct {

    int numero;
    int primo;

} Numero;

int main() {

    int limite;
    int threads = omp_get_num_procs() / 2;
    double inicio, fim, paralelo, sequencial;
    Numero *x;

    printf("Digite um número: ");
    scanf("%d", &limite);

    x = (Numero *)malloc(sizeof(Numero) * (limite - 1));

    if(x == NULL)
        exit(1);


    inicio = omp_get_wtime();
    #pragma omp parallel num_threads(threads)
    {
        #pragma omp for
        for(int i = 0; i < (limite - 1); i++) {

            x[i].numero = i + 2;
            x[i].primo = 1;

        }
    }

    for(int i = 0; i < (limite - 1); i++) {

        if(x[i].primo) {

            #pragma omp parallel num_threads(threads)
            {

                #pragma omp for
                for(int j = i + 1; j < (limite - 1); j++){

                    if(x[j].numero % x[i].numero == 0)
                        x[j].primo = 0;

                }

            }

        }
        
    }
    fim = omp_get_wtime();

    paralelo = fim - inicio;

    inicio = omp_get_wtime();
    for(int i = 0; i < (limite - 1); i++) {

        x[i].numero = i + 2;
        x[i].primo = 1;

    }

    for(int i = 0; i < (limite - 1); i++) {

        if(x[i].primo) {

            for(int j = i + 1; j < (limite - 1); j++){

                if(x[j].numero % x[i].numero == 0)
                    x[j].primo = 0;

            }

        }
        
    }
    fim = omp_get_wtime();

    sequencial = fim - inicio;

    for(int i = 0; i < (limite - 1); i++) {

        if(x[i].primo)
            printf("%d\n", x[i].numero);

    }

    printf("Tempo de execução sequncial: %lf.\n", sequencial);
    printf("Tempo de execução paralelo com %d threads: %lf.\n", threads, paralelo);
    printf("Speed up: %lf.\n", sequencial / paralelo);
    printf("Eficiência: %lf.\n\n", (sequencial / paralelo) / threads);

    free(x);

    return 0;
}