/*
 * sched.h
 *
 *  Created on: 2016Äê6ÔÂ28ÈÕ
 *      Author: xopenlee
 */

#ifndef SCHED_H_
#define SCHED_H_

extern int PthreadCreate(const char *name, unsigned int prio,
		PTHREADFUNC func, void *args);

#endif /* SCHED_H_ */
