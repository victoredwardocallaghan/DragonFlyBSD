#        @(#)Makefile	8.1 (Berkeley) 5/31/93
# $FreeBSD: src/bin/test/Makefile,v 1.6.2.1 2001/08/01 05:31:04 obrien Exp $

PROG=	test

LINKS=	${BINDIR}/test ${BINDIR}/[
MLINKS=	test.1 [.1

regress: test
	cd ${.CURDIR}/../../tools/regression/bin/test && \
	${MAKE} TEST=${.OBJDIR}/test
.include <bsd.prog.mk>
