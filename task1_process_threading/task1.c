#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int counter = 0;
pthread_mutex_t lock;

/* Thread function */
void *work(void *arg)
{
    int id = *(int *)arg;

    for(int i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&lock);

        counter++;
        printf("Thread %d is working. Counter = %d\n", id, counter);

        pthread_mutex_unlock(&lock);

        sleep(1);
    }

    return NULL;
}

int main()
{
    pthread_t t1, t2, t3;

    int id1 = 1;
    int id2 = 2;
    int id3 = 3;

    printf("Starting 3 threads...\n\n");

    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, work, &id1);
    pthread_create(&t2, NULL, work, &id2);
    pthread_create(&t3, NULL, work, &id3);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    pthread_mutex_destroy(&lock);

    printf("\nAll threads finished.\n");
    printf("Final Counter Value = %d\n", counter);

    return 0;
}
