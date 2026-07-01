#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int readCount = 0;
sem_t resource;
sem_t readTry;
sem_t rmutex;

void *reader(void *arg) {
    int id = *(int *)arg;

    sem_wait(&readTry);
    sem_wait(&rmutex);

    readCount++;
    if (readCount == 1)
        sem_wait(&resource);

    sem_post(&rmutex);
    sem_post(&readTry);

    printf("Reader %d is reading\n", id);
    sleep(1);

    sem_wait(&rmutex);

    readCount--;
    if (readCount == 0)
        sem_post(&resource);

    sem_post(&rmutex);

    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;

    sem_wait(&readTry);
    sem_wait(&resource);

    printf("Writer %d is writing\n", id);
    sleep(2);

    sem_post(&resource);
    sem_post(&readTry);

    return NULL;
}

int main() {
    pthread_t r[5], w;
    int rid[5] = {1, 2, 3, 4, 5};
    int wid = 1;

    sem_init(&resource, 0, 1);
    sem_init(&readTry, 0, 1);
    sem_init(&rmutex, 0, 1);

    for (int i = 0; i < 5; i++)
        pthread_create(&r[i], NULL, reader, &rid[i]);

    pthread_create(&w, NULL, writer, &wid);

    for (int i = 0; i < 5; i++)
        pthread_join(r[i], NULL);

    pthread_join(w, NULL);

    sem_destroy(&resource);
    sem_destroy(&readTry);
    sem_destroy(&rmutex);

    return 0;
}