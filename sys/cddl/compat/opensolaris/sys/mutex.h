/*-
 * Copyright (c) 2014 Edward O'Callaghan <eocallaghan@alterapraxis.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $DragonflyBSD$
 */

#ifndef _OPENSOLARIS_SYS_MUTEX_H_
#define	_OPENSOLARIS_SYS_MUTEX_H_

#ifdef _KERNEL

#include_next <sys/mutex.h>
#include <sys/proc.h>

#include <sys/globaldata.h>
#include <sys/mutex2.h>

typedef enum {
	MUTEX_DEFAULT = 6	/* kernel default mutex */
} kmutex_type_t;

#define	MUTEX_HELD(x)		(mutex_owned(x))
#define	MUTEX_NOT_HELD(x)	(!mutex_owned(x) || panicstr)

typedef struct mtx	kmutex_t;

#define	mutex_init(lock, desc, type, arg)	do {			\
	ASSERT((type) == 0 || (type) == MUTEX_DEFAULT);			\
	bzero((lock), sizeof(struct mtx));				\
	mtx_init((lock));			\
} while (0)

#define	mutex_enter(lock)	do {			\
	const char *_name;						\
	for (_name = #lock; *_name != '\0'; _name++) {			\
		if (*_name >= 'a' && *_name <= 'z')			\
			break;						\
	}								\
	if (*_name == '\0')						\
		_name = #lock;						\
	mtx_lock_ex_quick((lock), _name);			\
} while (0)

#define	mutex_destroy(lock)	mtx_uninit(lock)
#define	mutex_tryenter(lock)	mtx_lock_ex_try(lock)
#define	mutex_exit(lock)	mtx_unlock_ex(lock)
#define	mutex_owned(lock)	mtx_owned(lock)
#define	mutex_owner(lock)	(lock)->mtx_owner

#endif	/* _KERNEL */

#endif	/* _OPENSOLARIS_SYS_MUTEX_H_ */
