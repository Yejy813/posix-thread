#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

/*******************************************
 *  pthread_attr_setdetachstate
********************************************/

void *thread_function(void *arg);
char message[] = "hello world";
int thread_finished = 0;

int main(int argc, char *argv[])
{
    int res;
    pthread_t a_thread;
    pthread_attr_t thread_attr;

    res = pthread_attr_init(&thread_attr);
    if (res != 0)
    {
        perror("Attribute creation failed");
        exit(EXIT_FAILURE);
    }

    res = pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);
    if (res != 0)
    {
        perror("setting detached attribute failed");
        exit(EXIT_FAILURE);
    }

    // Create Thread
    res = pthread_create(&a_thread, &thread_attr, thread_function, (void *)message);
    if (res != 0)
    {
        perror("Thread create failed");
        exit(EXIT_FAILURE);
    }

    (void)pthread_attr_destroy(&thread_attr);

    while (!thread_finished)
    {
        printf("Wait for thraed to say it's finished...\n");
        sleep(1);
    }

    printf("Other thraed to finished, bye!\n");
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg)
{
    printf("thread_function is running. arg was: %s\n", (char *)arg);
    sleep(4);
    printf("Second thraed setting finished flag, and exiting now\n");
    thread_finished = 1;
    pthread_exit(NULL);
}
