

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int counter = 0;
pthread_mutex_t lock;

/* Thread function for demonstrating multithreading and synchronization */
void *work(void *arg)
{
    int id = *(int *)arg;

    for (int i = 0; i < 5; i++)
    {
        /*
         * Mutex lock is used before updating the shared counter.
         * This prevents race condition because only one thread
         * can enter this critical section at a time.
         */
        pthread_mutex_lock(&lock);

        counter++;
        printf("Thread %d is working. Counter = %d\n", id, counter);

        pthread_mutex_unlock(&lock);

        sleep(1);
    }

    return NULL;
}

/* Simple Round Robin scheduling simulation */
void round_robin_scheduler()
{
    int n = 3;
    int time_quantum = 2;

    int process_id[] = {1, 2, 3};
    int burst_time[] = {5, 4, 6};
    int remaining_time[] = {5, 4, 6};

    int time = 0;
    int completed = 0;

    printf("\nRound Robin Scheduling Simulation\n");
    printf("Time Quantum = %d units\n\n", time_quantum);

    while (completed < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (remaining_time[i] > 0)
            {
                if (remaining_time[i] > time_quantum)
                {
                    time += time_quantum;
                    remaining_time[i] -= time_quantum;

                    printf("Process P%d executed for %d units. Remaining time = %d\n",
                           process_id[i], time_quantum, remaining_time[i]);
                }
                else
                {
                    time += remaining_time[i];

                    printf("Process P%d executed for %d units. Process completed at time %d\n",
                           process_id[i], remaining_time[i], time);

                    remaining_time[i] = 0;
                    completed++;
                }
            }
        }
    }
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

    /*
     * Deadlock prevention:
     * The program uses only one mutex and unlocks it immediately
     * after the critical section. Therefore, circular waiting does
     * not occur and deadlock is avoided.
     */
    round_robin_scheduler();

    return 0;
}
