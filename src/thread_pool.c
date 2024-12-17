#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "thread_pool.h"
#include "global.h"

ThreadPool* init_thread_pool(int thread_num){
    ThreadPool* pool=malloc(sizeof(ThreadPool));
    if (pool)
    {
        pool->thread_num=thread_num;
        pool->shutdown=false;
        pool->task_queue_head=NULL;
        pool->task_queue_tail=NULL;
        pool->task_finished_num=0;
        pool->task_finished_num_target=0;

        if (pthread_mutex_init(&(pool->lock),NULL)!=0)
        {
            free(pool);
            return NULL;
        }
        
        if (pthread_cond_init(&(pool->notify), NULL)!=0) {
            pthread_mutex_destroy(&(pool->lock));
            free(pool);
            return NULL;
        }

        if (pthread_cond_init(&(pool->task_done), NULL)!=0) {
            pthread_cond_destroy(&(pool->notify));
            pthread_mutex_destroy(&(pool->lock));
            free(pool);
            return NULL;
        }

        pool->threads = (pthread_t*)malloc(sizeof(pthread_t) * thread_num);
        if (pool->threads == NULL) {
            pthread_mutex_destroy(&(pool->lock));
            pthread_cond_destroy(&(pool->notify));
            pthread_cond_destroy(&(pool->task_done));
            free(pool);
            return NULL;
        }

        for (int i = 0; i < thread_num; ++i) {
            if (pthread_create(&(pool->threads[i]), NULL, worker_thread, (void*)pool) != 0) {
                threadpool_destroy(pool, 0);
                return NULL;
            }
        }

    }
    
    return pool;
}


void* worker_thread(void* arg) {
    ThreadPool* pool = (ThreadPool*)arg;

    while (1) {
        pthread_mutex_lock(&(pool->lock));

        while (pool->task_queue_head == NULL && !pool->shutdown) {
            pthread_cond_wait(&(pool->notify), &(pool->lock));
        }

        if (pool->shutdown) {
            break;
        }

        Task* task = pool->task_queue_head;
        pool->task_queue_head = pool->task_queue_head->next;
        if (pool->task_queue_head == NULL) {
            pool->task_queue_tail = NULL;
        }

        pthread_mutex_unlock(&(pool->lock));

        (*(task->function))(task->arg);

        pthread_mutex_lock(&(pool->lock));
        pool->task_finished_num++;

        if (pool->task_finished_num_target == pool->task_finished_num)
        {
            pthread_cond_signal(&(pool->task_done));
        }
        
        pthread_mutex_unlock(&(pool->lock));

        free(task);
    }

    pthread_mutex_unlock(&(pool->lock));
    pthread_exit(NULL);

    return NULL;
}



bool push_task(ThreadPool* pool, void (*function)(void* arg), void* arg) {
    if (pool == NULL || function == NULL) {
        return false;
    }

    Task* new_task = (Task*)malloc(sizeof(Task));
    if (new_task == NULL) {
        return false;
    }

    new_task->function = function;
    new_task->arg = arg;
    new_task->next = NULL;

    pthread_mutex_lock(&(pool->lock));


    if (pool->task_queue_head == NULL) {
        pool->task_queue_head = new_task;
        pool->task_queue_tail = new_task;
    } else {
        pool->task_queue_tail->next = new_task;
        pool->task_queue_tail = new_task;
    }

    pthread_cond_signal(&(pool->notify));
    pthread_mutex_unlock(&(pool->lock));

    return true;
}


bool threadpool_destroy(ThreadPool* pool, int flags) {
    if (pool == NULL) {
        return false;
    }

    pthread_mutex_lock(&(pool->lock));
    pool->shutdown = 1;
    pthread_cond_broadcast(&(pool->notify));
    pthread_mutex_unlock(&(pool->lock));

    for (int i = 0; i < pool->thread_num; ++i) {
        pthread_join(pool->threads[i], NULL);
    }


    free(pool->threads);
    Task* task = pool->task_queue_head;
    while (task != NULL) {
        Task* tmp = task;
        task = task->next;
        free(tmp);
    }

    pthread_mutex_destroy(&(pool->lock));
    pthread_cond_destroy(&(pool->notify));
    pthread_cond_destroy(&(pool->task_done));
    free(pool);

    return true;
}



