#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N 15
#define RIGHT (num + 1)%pnum
#define LEFT (num + 4)%pnum

int pnum=0;
enum {thinking,eating,hungry} state[N];
sem_t mutex; 
sem_t S[N]; 

void *philospher(void* num){
    while(1){
        sleep(1);
        take_fork(num);
        sleep(0);
        put_fork(num);
    }
}

void take_fork(int num){
    sem_wait(&mutex);
    state[num] = hungry;
    test(num);
    sem_post(&mutex);
    if (state[num] != eating){
        sem_wait(&S[num]);
    }
}

void put_fork(int num){
    sem_wait(&mutex);
    state[num] = thinking;
     printf("Philosopher %d putting fork %d and %d down\n", 
           num + 1, LEFT + 1, RIGHT + 1); 
    printf("Philosopher %d is thinking\n", num + 1); 
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

void test(int num){
    if(state[num]==hungry && state[LEFT]!= eating && state[RIGHT]!=eating){
        state[num]=eating;
        sleep(2);
        printf("Philosopher %d takes fork %d and %d\n", 
                      num + 1, LEFT + 1, RIGHT + 1); 
  
        printf("Philosopher %d is Eating\n", num + 1); 
        sem_post(&S[num]);
    }
}
void main(){
    int i,j,phil[10];
    printf("Enter the no of Philioshper: ");
    scanf("%d",&pnum);
    for (i = 0; i < pnum; i++) 
        phil[i]=i;
    pthread_t thread_id[pnum];
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
