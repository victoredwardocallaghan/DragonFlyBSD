# $FreeBSD$

#.include <src.opts.mk>

SUBDIR=	${_zdb} \
	${_zhack}

#.if ${MK_TESTS} != "no"
#_tests=	tests
#.endif

.if ${MK_ZFS} != "no"
.if ${MK_LIBTHR} != "no"
_zdb=	zdb
_zhack=	zhack
.endif
.endif

.include <bsd.subdir.mk>
