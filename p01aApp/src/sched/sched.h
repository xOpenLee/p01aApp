/*
 * sched.h
 *
 *  Created on: 2016��6��28��
 *      Author: xopenlee
 */

#ifndef SCHED_H_
#define SCHED_H_

extern int PthreadCreate(const char *name, unsigned int prio,
		PTHREADFUNC func, void *args);

#endif /* SCHED_H_ */
