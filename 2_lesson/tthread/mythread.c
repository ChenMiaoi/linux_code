#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>

void* thread_run(void* arg)
{
    printf("%s : %lx, pid : %d\n", (char*)arg, pthread_self(), getpid());
    sleep(5);
    return (void*)10;
}

int main()
{
    pthread_t tid;
    tid = pthread_create(&tid, NULL, thread_run, "thread1");

    printf("main : %lx, pid : %d\n", pthread_self(), getpid());
    sleep(2);

    void* ret = NULL;
    pthread_join(tid, &ret);
    printf("thread quit code : %d\n", (int)ret);
}