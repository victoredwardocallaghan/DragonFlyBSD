# $FreeBSD$

#.include <src.opts.mk>

SUBDIR=	${_zdb} \
	${_zhack}

#.if ${NO_TESTS} != "no"
#_tests=	tests
#.endif

.if ${NO_ZFS} != "no"
.if ${NO_LIBTHR} != "no"
_zdb=	zdb
_zhack=	zhack
.endif
.endif

.include <bsd.subdir.mk>
