# $FreeBSD$

#.include <src.opts.mk>

#	libctf
SUBDIR=	libavl \
	libnvpair \
	libumem \
	libuutil \
	${_libzfs_core} \
	${_libzfs} \
	${_libzpool}

.if ${NO_ZFS} != "no"
_libzfs_core=	libzfs_core
_libzfs=	libzfs
.if ${NO_LIBTHR} != "no"
_libzpool=	libzpool
.endif
.endif

.include <bsd.subdir.mk>
