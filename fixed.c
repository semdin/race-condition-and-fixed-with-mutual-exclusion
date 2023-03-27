#include <stdio.h>
#include <pthread.h>

int count = 0;
pthread_mutex_t mutex;

void *thread_func(void *arg){
    int i;
    for(i = 0; i< 10; i++){
        pthread_mutex_lock(&mutex);
        count++;
        printf("%d ", count);
        pthread_mutex_unlock(&mutex);
    }
    printf("\n\n");
    return NULL;
}

int main(){
    pthread_t thread1, thread2;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&thread1, NULL, thread_func, NULL);
    pthread_create(&thread2, NULL, thread_func, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutex);

    printf("\n\ncount = %d\n", count);
    return 0;
}