/*
 * Copyright (c) 2014 The DragonFly Project.  All rights reserved.
 *
 * This code is derived from software contributed to The DragonFly Project
 * by Matthew Dillon <dillon@backplane.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of The DragonFly Project nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
/*
 * Input event user and device API
 */

#ifndef _SYS_INPUT_H_
#define _SYS_INPUT_H_

#include <sys/linux_types.h>
#include <contrib/linux/include/uapi/linux/input.h>

struct inputev {
	int dummy;
};

typedef struct inputev inputev_t;

#ifdef _KERNEL

void inputev_init(inputev_t *iev, const char *id);
void inputev_register(inputev_t *iev);
void inputev_deregister(inputev_t *iev);
void inputev_sync(inputev_t *iev);
int inputev_read(inputev_t *iev, struct uio *uio, int ioflag);
int inputev_ioctl(inputev_t *iev, u_long cmd, void *data);
void inputev_mt_sync_frame(inputev_t *iev);

void inputev_set_evbit(inputev_t *iev, int bit);
void inputev_set_keybit(inputev_t *iev, int bit);
void inputev_set_propbit(inputev_t *iev, int bit);
void inputev_set_abs_params(inputev_t *iev, u_int axis,
			int min, int max, int fuzz, int flat);
void inputev_set_res(inputev_t *iev, u_int axis, int val);

void inputev_mt_slot(inputev_t *iev, int slot);
void inputev_mt_report_slot_state(inputev_t *iev, u_int code, int good);
void inputev_report_key(inputev_t *iev, u_int code, int val); /* EV_KEY */
void inputev_report_rel(inputev_t *iev, u_int code, int val); /* EV_REL */
void inputev_report_abs(inputev_t *iev, u_int code, int val); /* EV_ABS */

#endif

#endif
