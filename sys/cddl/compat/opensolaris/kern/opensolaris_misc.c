/*-
 * Copyright (c) 2007 Pawel Jakub Dawidek <pjd@FreeBSD.org>
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
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include <sys/param.h>
#include <sys/jail.h>
#include <sys/kernel.h>
#include <sys/libkern.h>
#include <sys/limits.h>
#include <sys/misc.h>
#include <sys/sysctl.h>
#include <sys/utsname.h>

char hw_serial[11] = "0";

struct utsname utsname = {
	.machine = MACHINE
};

// XXX Same as utsname.h header
#define MAX_UTSNAME 32

static void
opensolaris_utsname_init(void *arg)
{
	strncpy(utsname.sysname, ostype, (MAX_UTSNAME - 1));
	// struct jail_v0 jv0 -> jv0.hostname perhaps??
	// utsname.nodename = prison0.pr_hostname;
	// strncpy(utsname.nodename, jv0.hostname, (MAX_UTSNAME - 1));
	strncpy(utsname.release, osrelease, (MAX_UTSNAME - 1));
	snprintf(utsname.version, sizeof(utsname.version), "%d", osreldate);
}
SYSINIT(opensolaris_utsname_init, SI_BOOT1_TUNABLES, SI_ORDER_ANY,
    opensolaris_utsname_init, NULL);
