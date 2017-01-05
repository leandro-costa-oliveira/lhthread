#define _GNU_SOURCE
#ifndef LHTHREAD_H
#define LHTHREAD_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

typedef struct LHTHREAD {
    int id;
    int status;
    int executar;
    pthread_t pthread;
    struct LHTHREAD *proximo;
} LHTHREAD;

LHTHREAD *lhthread_new(int id, void *);
LHTHREAD *lhthread_get(LHTHREAD *primeiro, int id);
LHTHREAD *lhthread_remove(LHTHREAD *primeiro, int id);
LHTHREAD *lhthread_append(LHTHREAD *primeiro, LHTHREAD *t);
void lhthread_free(LHTHREAD *thead);
void lhthread_join(LHTHREAD *thead);
#endif