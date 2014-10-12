# $FreeBSD$


LIB=	llvmipo

SRCDIR=	lib/Transforms/IPO
SRCS=	ArgumentPromotion.cpp \
	BarrierNoopPass.cpp \
	ConstantMerge.cpp \
	DeadArgumentElimination.cpp \
	ExtractGV.cpp \
	FunctionAttrs.cpp \
	GlobalDCE.cpp \
	GlobalOpt.cpp \
	IPConstantPropagation.cpp \
	InlineAlways.cpp \
	InlineSimple.cpp \
	Inliner.cpp \
	Internalize.cpp \
	LoopExtractor.cpp \
	MergeFunctions.cpp \
	PartialInlining.cpp \
	PassManagerBuilder.cpp \
	PruneEH.cpp \
	StripDeadPrototypes.cpp \
	StripSymbols.cpp

.if !defined(NO_CLANG_EXTRAS)
SRCS+=	IPO.cpp
.endif

TGHDRS=	Intrinsics

.include "../clang.lib.mk"
