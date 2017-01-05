#include "lhthread.h"

LHTHREAD *lhthread_new(int id, void *worker) {
    LHTHREAD *thread = NULL;
    int rc;
    char name[255];
    
    thread = malloc (sizeof(LHTHREAD));
    if(thread){
        thread->id = id;
        thread->status = 0;
        thread->executar = 1;
        thread->proximo  = NULL;
        rc = pthread_create(&thread->pthread, NULL, worker, (void *) thread);
        if (rc){
            printf("PTHREAD CREATE ERROR [%d] %s\n", rc, strerror(rc));
            lhthread_free(thread);
            return NULL;
        } else {
            memset(name,'\0',255);
            sprintf(name,"lhthread-%d",id);
            #ifdef __USE_GNU
            pthread_setname_np(thread->pthread,name);
            #endif
        }
    }
    return thread;
}

LHTHREAD *lhthread_get(LHTHREAD *primeiro, int id){
    LHTHREAD *t = NULL;
    
    t = primeiro;
    while(t) {
        // printf(",%d", t->id);
        if(t->id == id){
            return t;
        }
        t = t->proximo;
    }
    
    // printf(" NOT FOUND\n"); fflush(stdout);
    return NULL;
}

// Retorna o primeiro.
LHTHREAD *lhthread_remove(LHTHREAD *primeiro, int id) {
    LHTHREAD *cur, *prior;

    cur   = primeiro;
    prior = NULL;
    while(cur){
        // se achei o que quero remover.
        if(cur->id == id){
            // ESTOU NO PRIMEIRO REGISTRO.
            if(prior==NULL){
                // NAO TENHO UM ANTERIOR, ALTERAR O REGISTRO GLOBAL.
                prior = cur->proximo;
                lhthread_free(cur);
                return prior;
            } else {
                // FARIA O ANTERIOR APONTAR PRO PROXIMO
                prior->proximo = cur->proximo;
                lhthread_free(cur);
                return primeiro; // NÃO FOI ALTERADO O COMEÇO DA FILA
            }
        }

        prior = cur; // armazena o atual, que sera o anterior.
        cur   = cur->proximo; // avanca um registro
    }

    // necessario para caso nao ache a thread.
    return primeiro;
}

void lhthread_free(LHTHREAD *thread) {
    if(thread){
        free(thread);
    }
}

void lhthread_join(LHTHREAD *thread) {
    if(thread){
        pthread_join(thread->pthread, NULL);
    }
}

LHTHREAD *lhthread_append(LHTHREAD *primeiro, LHTHREAD *t) {
    LHTHREAD *tmp = primeiro;
    
    // Se não iniciou a lista, retorna t;
    if(primeiro == NULL) return t;
    
    // Avança até chegar no último registro, onde proximo == NULL
    while(tmp->proximo) {
        tmp = tmp->proximo;
    }
    
    // Armazena T no ultimo registor, e retorna o ponteiro pro primeiro
    tmp->proximo = t;
    return primeiro;
}