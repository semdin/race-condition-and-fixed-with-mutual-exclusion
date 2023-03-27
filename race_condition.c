#include <stdio.h>
#include <pthread.h>

int count = 0;

void *thread_func(void *arg){
    int i;
    for(i = 0; i < 10; i++){
        count++;
        printf("%d ", count);
    }
    printf("\n\n");
    return NULL;
}

int main(){
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, thread_func, NULL);
    pthread_create(&thread2, NULL, thread_func, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("\n\ncount = %d\n", count);
    return 0;
}