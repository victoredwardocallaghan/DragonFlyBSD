# $FreeBSD$


SUBDIR=	clang clang-tblgen tblgen

.if !defined(TOOLS_PREFIX)
.if !defined(NO_CLANG_EXTRAS)
SUBDIR+=bugpoint \
	llc \
	lli \
	llvm-ar \
	llvm-as \
	llvm-bcanalyzer \
	llvm-diff \
	llvm-dis \
	llvm-extract \
	llvm-link \
	llvm-mc \
	llvm-nm \
	llvm-objdump \
	llvm-rtdyld \
	macho-dump \
	opt
.endif

.if !defined(NO_LLDB)
SUBDIR+=lldb
.endif
.endif # TOOLS_PREFIX

SUBDIR_PARALLEL=

.include <bsd.subdir.mk>
