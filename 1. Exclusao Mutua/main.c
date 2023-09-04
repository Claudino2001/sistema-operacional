#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define THREADS 100

// Função correspondente a Thread de adição
void *funcao_soma(void *arg);

// Função correspondente a Thread de subtração
void *funcao_subtrai(void *arg);

// Variaveis Globais
long variavel_global = 0;
sem_t sem;

int main(void){
    
    int i;
    
    // Declarando as 200 Threads
    pthread_t somaThreads[THREADS];
    pthread_t subtraiThreads[THREADS];
    
    sem_init(&sem, 0, 1); // Inicializando o semáforo

    // Executando cada uma das 200 Threads
    for(i=0; i<THREADS; i++){
        pthread_create(&somaThreads[i], NULL, funcao_soma, NULL);
        pthread_create(&subtraiThreads[i], NULL, funcao_subtrai, NULL);
    }
    
    // Finalizando cada uma das 200 Threads
    for(i=0; i<THREADS; ++i){
        pthread_join(somaThreads[i], NULL);
        pthread_join(subtraiThreads[i], NULL);
    }

    // O resultado esperado é zero
    printf("Memória Compartilhada = %ld\n", variavel_global);

    return 0;
}

void *funcao_soma(void *arg) {
    sem_wait(&sem);
    int a = variavel_global;
    a = a + 1;
    sleep(0.1);
    variavel_global = a;
    sem_post(&sem);
}

void *funcao_subtrai(void *arg) {
    sem_wait(&sem);
    int a = variavel_global;
    a = a - 1;
    sleep(0.1);
    variavel_global = a;
    sem_post(&sem);
}