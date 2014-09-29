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
 * $FreeBSD$
 * $DragonflyBSD$
 */

#ifndef _OPENSOLARIS_SYS_RWLOCK_H_
#define	_OPENSOLARIS_SYS_RWLOCK_H_

#include <sys/proc.h>
#include <sys/globaldata.h>
#include <sys/mutex2.h>

#ifdef _KERNEL

typedef enum {
	RW_DEFAULT = 4		/* kernel default rwlock */
} krw_type_t;

typedef enum {
	RW_WRITER,
	RW_READER
} krw_t;

typedef	struct mtx	krwlock_t;

#define	RW_READ_HELD(x)		(rw_read_held((x)))
#define	RW_WRITE_HELD(x)	(rw_write_held((x)))
#define	RW_LOCK_HELD(x)		(rw_lock_held((x)))
#define	RW_ISWRITER(x)		(rw_iswriter(x))

#define	rw_init(lock, desc, type, arg)	do {				\
	ASSERT((type) == 0 || (type) == RW_DEFAULT);			\
	bzero((lock), sizeof(struct mtx));				\
	mtx_init((lock));				\
} while (0)
#define	rw_destroy(lock)	mtx_uninit(lock)
#define	rw_enter(lock, how)	do {					\
	const char *_name;						\
	for (_name = #lock; *_name != '\0'; _name++) {			\
		if (*_name >= 'a' && *_name <= 'z')			\
			break;						\
	}								\
	if (*_name == '\0')						\
		_name = #lock;						\
	if ((how) == RW_READER)						\
		mtx_lock_sh_quick(lock, _name);						\
	else /* if ((how) == RW_WRITER) */				\
		mtx_lock_ex_quick(lock, _name);						\
} while (0)

#define	rw_tryenter(lock, how)	((how) == RW_READER ? mtx_lock_sh_try(lock) : mtx_lock_ex_try(lock))
#define	rw_exit(lock)		mtx_unlock(lock)
#define	rw_downgrade(lock)	mtx_downgrade(lock)
#define	rw_tryupgrade(lock)	mtx_upgrade_try(lock)

#define	rw_read_held(lock)	mtx_islocked(lock)

#define	rw_write_held(lock)	mtx_owned(lock)
#define	rw_lock_held(lock)	(rw_read_held(lock) || rw_write_held(lock))
#define	rw_iswriter(lock)	mtx_owned(lock)
#define	rw_owner(lock)	(lock)->mtx_owner

#endif	/* defined(_KERNEL) */

#endif	/* _OPENSOLARIS_SYS_RWLOCK_H_ */
