# $FreeBSD$


LIB=	llvmipa

SRCDIR=	lib/Analysis/IPA
SRCS=	CallGraph.cpp \
	CallGraphSCCPass.cpp \
	CallPrinter.cpp \
	FindUsedTypes.cpp \
	GlobalsModRef.cpp \
	InlineCost.cpp

.if !defined(NO_CLANG_EXTRAS)
SRCS+=	IPA.cpp
.endif

TGHDRS=	Intrinsics

.include "../clang.lib.mk"
