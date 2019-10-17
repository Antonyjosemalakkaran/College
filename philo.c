#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int pnum=0;
void main(){
    int i,j,phil[10];
    printf("Enter the no of Philioshper: ");
    scanf("%d",&pnum);
    for (i = 0; i < pnum; i++) 
        phil[i]=i;
    enum {thinking,eating,hungry} state[pnum];
    pthread_t thread_id[pnum];
    sem_t mutex; 
    sem_t S[pnum];
    sem_init(&mutex, 0, 1);
    for (i = 0; i < pnum; i++) 
        sem_init(&S[i], 0, 0);
    for (i = 0; i < pnum; i++) {
        pthread_create(&thread_id[i], NULL, 
                       philospher, &phil[i]); 
        printf("Philosopher %d is thinking\n", i + 1); 
    }
    for (i = 0; i < pnum; i++) 
        pthread_join(thread_id[i], NULL); 
    
     
}
