/*
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
 * Copyright (c) 1993 Jan-Simon Pendry
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)procfs_machdep.c	8.3 (Berkeley) 1/27/94
 *
 * From:
 * $FreeBSD: src/sys/i386/i386/procfs_machdep.c,v 1.14 1999/10/11 14:50:03 peter Exp $
 * $DragonFly: src/sys/platform/pc64/amd64/procfs_machdep.c,v 1.2 2007/09/24 03:24:45 yanyh Exp $
 */

/*
 * Functions to be implemented here are:
 *
 * procfs_read_regs(lwp, regs)
 *	Get the current user-visible register set from the process
 *	and copy it into the regs structure (<machine/reg.h>).
 *	The process is stopped at the time read_regs is called.
 *
 * procfs_write_regs(lwp, regs)
 *	Update the current register set from the passed in regs
 *	structure.  Take care to avoid clobbering special CPU
 *	registers or privileged bits in the PSL.
 *	Depending on the architecture this may have fix-up work to do,
 *	especially if the IAR or PCW are modified.
 *	The process is stopped at the time write_regs is called.
 *
 * procfs_read_fpregs, procfs_write_fpregs
 *	deal with the floating point register set, otherwise as above.
 *
 * procfs_read_dbregs, procfs_write_dbregs
 *	deal with the processor debug register set, otherwise as above.
 *
 * procfs_sstep(lwp)
 *	Arrange for the process to trap after executing a single instruction.
 *
 */

#include <sys/param.h>
#include <sys/proc.h>
#include <sys/ptrace.h>
#include <sys/vnode.h>
#include <sys/reg.h>
#include <machine/md_var.h>
#include <vfs/procfs/procfs.h>

#include <vm/vm.h>
#include <sys/lock.h>
#include <vm/pmap.h>
#include <vm/vm_map.h>

int
procfs_read_regs(struct lwp *lp, struct reg *regs)
{
	return (fill_regs(lp, regs));
}

int
procfs_write_regs(struct lwp *lp, struct reg *regs)
{
	return (set_regs(lp, regs));
}

int
procfs_read_dbregs(struct lwp *lp, struct dbreg *dbregs)
{
	return (fill_dbregs(lp, dbregs));
}

int
procfs_write_dbregs(struct lwp *lp, struct dbreg *dbregs)
{
	return (set_dbregs(lp, dbregs));
}

/*
 * Ptrace doesn't support fpregs at all, and there are no security holes
 * or translations for fpregs, so we can just copy them.
 */

int
procfs_read_fpregs(struct lwp *lp, struct fpreg *fpregs)
{
	return (fill_fpregs(lp, fpregs));
}

int
procfs_write_fpregs(struct lwp *lp, struct fpreg *fpregs)
{
	return (set_fpregs(lp, fpregs));
}

int
procfs_sstep(struct lwp *lp)
{
	return (ptrace_single_step(lp));
}
