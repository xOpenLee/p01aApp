/*
 * sched.h
 *
 *  Created on: 2016��7��17��
 *      Author: xopenlee
 */

#ifndef SCHED_H_
#define SCHED_H_

typedef void(*PTHREADFUNC)(void*);

extern int PthreadCreate(const char *name, unsigned int prio,
		PTHREADFUNC func, void *args);



#endif /* SCHED_H_ */
