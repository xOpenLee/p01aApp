/*
 * sched.c
 *
 *  Created on: 2016Äê7ÔÂ17ÈÕ
 *      Author: xopenlee
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sched.h"

#define NAME_LEN 32


typedef struct pthread {
    char name[NAME_LEN];
    unsigned int prio;
    PTHREADFUNC func;
    void *args;
    struct pthread *next;
}PTHREAD;

static struct pthread *PthreadListHead = NULL;

static unsigned char PthreadIsRuning = 0;

static int PthreadRun(void)
{

    if (PthreadListHead == NULL) {
        printf("#ERR: PthreadListHead NULL Err.\n");
        return -1;
    }

    if (PthreadIsRuning == 1)
        return -2;

    PthreadIsRuning = 1;

    while(PthreadListHead != NULL) {
        PthreadListHead->func(PthreadListHead->args);
        PthreadListHead = PthreadListHead->next;
    }

    PthreadIsRuning = 0;
    return 0;
}

static int PthreadPrint(void)
{
    struct pthread *mPthreadList = NULL;

    if (PthreadListHead == NULL) {
        printf("#ERR: PthreadListHead NULL Err.\n");
        return -1;
    }

    mPthreadList = PthreadListHead;
    do {
        printf("#INFO: Pthread Print name = %s, prio = %d\n",
              mPthreadList->name, mPthreadList->prio);
        mPthreadList = mPthreadList->next;
    }while(mPthreadList != PthreadListHead);

    return 0;

}

static int PthreadInsert(const char *name, unsigned int prio, PTHREADFUNC func, void *args)
{
    struct pthread *mPthreadList = NULL, *mPthreadListNext = PthreadListHead->next;

    if (name == NULL) {
        printf("#ERR: PthreadInsert name NULL.\n");
        return -1;
    }

    if (func == NULL) {
        printf("#ERR: PthreadInsert func NULL.\n");
        return -2;
    }

    if (PthreadListHead == NULL) {
        printf("#ERR: PthreadListHead NULL Err.\n");
        return -4;
    }


    mPthreadList = (struct pthread*)malloc(sizeof(struct pthread));
    if (mPthreadList == NULL) {
        printf("#ERR: malloc mPthreadList Err.\n");
        return -3;
    }

    memcpy(mPthreadList->name, name, NAME_LEN);
    mPthreadList->prio = prio;
    mPthreadList->func = func;
    mPthreadList->args = args;

    mPthreadList->next = mPthreadListNext;
    PthreadListHead->next = mPthreadList;

    return 0;
}

int PthreadCreate(const char *name, unsigned int prio, PTHREADFUNC func, void *args)
{
    if (name == NULL) {
        printf("#ERR: PthreadCreate name NULL.\n");
        return -1;
    }

    if (func == NULL) {
        printf("#ERR: PthreadCreate func NULL.\n");
        return -2;
    }

    if (PthreadListHead == NULL) {
        PthreadListHead = (struct pthread*)malloc(sizeof(struct pthread));
        if (PthreadListHead == NULL) {
            printf("#ERR: malloc PthreadListHead Err.\n");
            return -3;
        }
        memcpy(PthreadListHead->name, name, NAME_LEN);
        PthreadListHead->prio = prio;
        PthreadListHead->func = func;
        PthreadListHead->args = args;
        PthreadListHead->next = PthreadListHead;
        PthreadRun();
        return 0;
    }

    return PthreadInsert(name, prio, func, args);
}

