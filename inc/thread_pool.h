#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <pthread.h>
#include "global.h"
typedef struct Task Task;
typedef struct ThreadPool ThreadPool;

struct Task{
    void (*function)(void*);
    void* arg;
    Task* next;
};

struct ThreadPool{
    pthread_mutex_t lock;
    pthread_cond_t notify;
    pthread_cond_t task_done;
    pthread_t* threads;
    Task* task_queue_head;
    Task* task_queue_tail;
    size_t task_finished_num;
    size_t task_finished_num_target;
    int thread_num;
    bool shutdown;
};

ThreadPool* init_thread_pool(int thread_num);
void* worker_thread(void* arg);
bool push_task(ThreadPool* pool, void (*function)(void* arg), void* arg);
bool threadpool_destroy(ThreadPool* pool, int flags);

#endif