/*
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 * Copyright (c) 1988, 1989 by Adam de Boor
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
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
 *	from: @(#)lst.h	8.1 (Berkeley) 6/6/93
 * $FreeBSD: src/usr.bin/make/lst.h,v 1.9 1999/08/28 01:03:32 peter Exp $
 * $DragonFly: src/usr.bin/make/lst.h,v 1.9 2004/12/08 11:26:39 okumoto Exp $
 */

/*-
 * lst.h --
 *	Header for using the list library
 */
#ifndef _LST_H_
#define	_LST_H_

#include	<sys/param.h>
#include	<stdlib.h>
#include	"sprite.h"

/*
 * Structure of a list node.
 */
struct LstNode {
	struct LstNode	*prevPtr;   /* previous element in list */
	struct LstNode	*nextPtr;   /* next in list */
	int	useCount:8; /* Count of functions using the node. Node may not
			     * be deleted until count goes to 0 */
 	int	flags:8;    /* Node status flags */
	void	*datum;	    /* datum associated with this element */
};
typedef	struct	LstNode	*LstNode;

/*
 * Flags required for synchronization
 */
#define	LN_DELETED  	0x0001      /* List node should be removed when done */

typedef enum {
	LstHead, LstMiddle, LstTail, LstUnknown
} LstWhere;

/*
 * The list itself
 */
struct Lst {
	LstNode  	firstPtr; /* first node in list */
	LstNode  	lastPtr;  /* last node in list */
	Boolean	  	isCirc;	  /* true if the list should be considered
				   * circular */
	/*
	 * fields for sequential access
	 */
	LstWhere	atEnd;	  /* Where in the list the last access was */
	Boolean	  	isOpen;	  /* true if list has been Lst_Open'ed */
	LstNode  	curPtr;	  /* current node, if open. NULL if
				   * *just* opened */
	LstNode  	prevPtr;  /* Previous node, if open. Used by
				   * Lst_Remove */
};
typedef	struct	Lst	*Lst;

/*
 * NOFREE can be used as the freeProc to Lst_Destroy when the elements are
 *	not to be freed.
 * NOCOPY performs similarly when given as the copyProc to Lst_Duplicate.
 */
#define	NOFREE		((void (*)(void *)) 0)
#define	NOCOPY		((void * (*)(void *)) 0)

#define	LST_CONCNEW	0   /* create new LstNode's when using Lst_Concat */
#define	LST_CONCLINK	1   /* relink LstNode's when using Lst_Concat */

/*
 * Creation/destruction functions
 */
/* Create a new list */
Lst		Lst_Init(Boolean);
/* Duplicate an existing list */
Lst		Lst_Duplicate(Lst, void * (*)(void *));
/* Destroy an old one */
void		Lst_Destroy(Lst, void (*)(void *));

/*
 * Functions to modify a list
 */
/* Insert an element before another */
ReturnStatus	Lst_Insert(Lst, LstNode, void *);
/* Insert an element after another */
ReturnStatus	Lst_Append(Lst, LstNode, void *);
/* Place an element at the front of a lst. */
ReturnStatus	Lst_AtFront(Lst, void *);
/* Place an element at the end of a lst. */
ReturnStatus	Lst_AtEnd(Lst, void *);
/* Remove an element */
ReturnStatus	Lst_Remove(Lst, LstNode);
/* Replace a node with a new value */
ReturnStatus	Lst_Replace(LstNode, void *);
/* Concatenate two lists */
ReturnStatus	Lst_Concat(Lst, Lst, int);

/*
 * Node-specific functions
 */
/* Return first element in list */
LstNode		Lst_First(Lst);
/* Return last element in list */
LstNode		Lst_Last(Lst);
/* Return successor to given element */
LstNode		Lst_Succ(LstNode);
/* Get datum from LstNode */
void *	Lst_Datum(LstNode);

/*
 * Functions for entire lists
 */
/* Find an element in a list */
LstNode		Lst_Find(Lst, void *, int (*)(void *, void *));
/* Find an element starting from somewhere */
LstNode		Lst_FindFrom(Lst, LstNode, void *, int (*cProc)(void *, void *));
/*
 * See if the given datum is on the list. Returns the LstNode containing
 * the datum
 */
LstNode		Lst_Member(Lst, void *);
/* Apply a function to all elements of a lst */
void		Lst_ForEach(Lst, int (*)(void *, void *), void *);
/*
 * Apply a function to all elements of a lst starting from a certain point.
 * If the list is circular, the application will wrap around to the
 * beginning of the list again.
 */
void		Lst_ForEachFrom(Lst, LstNode, int (*)(void *, void *), void *);
/*
 * these functions are for dealing with a list as a table, of sorts.
 * An idea of the "current element" is kept and used by all the functions
 * between Lst_Open() and Lst_Close().
 */
/* Open the list */
ReturnStatus	Lst_Open(Lst);
/* Next element please */
LstNode		Lst_Next(Lst);
/* Done yet? */
Boolean		Lst_IsAtEnd(Lst);
/* Finish table access */
void		Lst_Close(Lst);

/*
 * for using the list as a queue
 */
/* Place an element at tail of queue */
ReturnStatus	Lst_EnQueue(Lst, void *);
/* Remove an element from head of queue */
void *	Lst_DeQueue(Lst);

/*
 * LstValid (L) --
 *	Return TRUE if the list L is valid
 */
#define Lst_Valid(L)	(((L) == NULL) ? FALSE : TRUE)

/*
 * LstNodeValid (LN, L) --
 *	Return TRUE if the LstNode LN is valid with respect to L
 */
#define Lst_NodeValid(LN, L)	(((LN) == NULL) ? FALSE : TRUE)

/*
 * Lst_IsEmpty(L) --
 *	TRUE if the list L is empty.
 */
#define Lst_IsEmpty(L)	(!Lst_Valid(L) || (L)->firstPtr == NULL)


#endif /* _LST_H_ */
