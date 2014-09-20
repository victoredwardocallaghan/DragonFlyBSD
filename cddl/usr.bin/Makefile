# $FreeBSD$

#.include <src.opts.mk>

SUBDIR= \
#	ctfconvert \
#	ctfdump \
#	ctfmerge \
	sgsmsg \
	${_zinject} \
	${_zlook} \
	${_zstreamdump} \
	${_ztest}

#.if ${NO_TESTS} != "no"
#_tests=	tests
#.endif

.if ${NO_ZFS} != "no"
_zinject= zinject
#_zlook= zlook
.if ${NO_LIBTHR} != "no"
_ztest=	ztest
_zstreamdump = zstreamdump
.endif
.endif

.include <bsd.subdir.mk>
