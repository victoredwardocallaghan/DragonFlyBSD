# $FreeBSD$

#.include <src.opts.mk>

#SUBDIR=	${_tests} ${_zfs} ${_zpool}
SUBDIR=	${_zfs} ${_zpool}

#.if ${NO_TESTS} != "no"
#_tests=	tests
#.endif

.if ${NO_ZFS} != "no"
_zfs=	zfs
_zpool=	zpool
.endif

.include <bsd.subdir.mk>
