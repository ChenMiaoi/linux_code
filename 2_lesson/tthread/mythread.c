#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* thread_run(void* arg)
{
    while (1) {
        printf("%s : %lx, pid : %d\n", (char *) arg, pthread_self(), getpid());
        sleep(5);
    }
    //pthread_exit((void*)10);
    //exit(10);
}

int main()
{
    pthread_t tid;
    pthread_create(&tid, NULL, thread_run, "thread1");

    printf("main : %lx, pid : %d\n", pthread_self(), getpid());
    sleep(10);
    pthread_cancel(tid);
    printf("new thread %lx be cancel!\n", tid);

    void* ret = NULL;
    pthread_join(tid, &ret);
    printf("thread quit code : %d\n", (long long)ret);
    return 100;
}